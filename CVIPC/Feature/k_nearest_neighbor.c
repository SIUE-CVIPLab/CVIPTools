/***************************************************************************
* =========================================================================
*
*			 CVIPtools - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: k_nearest_neighbor.c 
*		  Expanded Name: k nearest neighbor function
*			 Parameters: Pointers pointing to the file names of training and test
*						 set, nomalization and distance/similarity option,
*						 specified min and max, constant r_softmax, r_minkowski
*				 Return: error code
*           Description: It contains the function to call lower level functions to 
*						 normalize the feature files, calculates the distance/
*						 similarity between each sample in the test set to all 
*						 sample in the training set , uses K-nearest neighbor
*						 algorithm to find the closest match sample in training 
*						 set to the sample in the test set,calculates the STATISTICS,
*						 and writes all the useful information in the output file
*   Initial Coding Date: May 26, 2005
*Last Modification Made: July 8, 2005
*           Portability: Standard (ANSI) C
*             Credit(s): Husain Kagalwalla, Geer Shuang, Amit Kharbanda
*                        Southern Illinois University at Edwardsville
*
*		  Copyright (c): 1995-2005 SIUE - Scott Umbaugh
****************************************************************************/

/*
** include header files
*/

#include	"math.h"
#include	"stdio.h"
#include	"stdlib.h"
#include	"string.h"
#include	"CVIPpattern.h"

int k_nearest_neighbor(char *file_tt, char *file_tr, char *file_out, int option_normalize, int option_distance, int k, float s_min, float s_max, float r_softmax, int r_minkowski)
{	
	char	**data1;
	char	**data2;
	int		*data3;
	int		*data4;
	float	*class_ed;
	char	**class_tt;
	char	**class_tp;
	int		*count;

	int		i ,y = 0,n,m,j,h,g,q,sum;
	int		no_of_entries_tr;
	int		no_of_entries_tt;
	
	float	temp;
	char	ch_tr;
	char	ch_temp;
	char	temp1[MAX_CASE];
	int		temp2;
	int		temp3;
	char	temp4[MAX_CASE];
	char	temp5[MAX_CASE];
	char	temp6[MAX_CASE];
	char	temp7[MAX_CASE];
	char	tempfile[MAX_CASE] = "CVIPtemp.txt";
	char	*file_tr_temp = &temp6[0];
	char	*file_tt_temp = &temp7[0];
	char	*file_temp = &tempfile[0];
	char	*libvar;
	char	*p;
	
	char	**class_st_tt;
	char	**class_st_id;
	char	**class_list;
	int		**st;
	float	percentage;
	int		*err_code;

	FILE	*fp;
	FILE	*fp_tr;
	FILE	*fp_out;

	err_code = malloc(sizeof(int));
	*err_code = 0;

	// Gets the value of the LIB environment variable

	libvar = getenv( "TEMP" );
	strcpy(file_temp,libvar);
	strcat(file_temp,"\\CVIPtemp.txt");
	
	
	if ((fp_tr = fopen(file_tr, "r")) == NULL)
	{
		printf("Error! k_nearest_neighbor.c. Can't open , read or create file.");
		printf("%s\n",file_tr);
		return(7);
	}
	
	if ((fp_out = fopen(file_out, "w+")) ==NULL)
	{
		fclose(fp_tr);
		printf("Error! k_nearest_neighbor.c. Can't open , read or create file.");
		printf("%s\n",file_out);
		return(7);
	}

	// Writes the header from training file into output file

	ch_tr=fgetc(fp_tr);
	while (ch_tr != '*')
	{
		fputc(ch_tr, fp_out);
		ch_tr=fgetc(fp_tr);
	}
	for (i=0;i<65;i++)
	{
		fputc(ch_tr, fp_out);
		ch_tr=fgetc(fp_tr);
	}
	fclose(fp_tr);

	// Prints the output file header

	fprintf(fp_out,"%s","\n*** PATTERN CLASSIFICATION HEADER ***\n");
	fprintf(fp_out,"%s","Classification Algorithm: K-nearest Neighbor\t");
	fprintf(fp_out,"k = %d\n",k);

	// Normalization performed

	switch(option_normalize)
	{
	case 0:	
		fprintf(fp_out,"%s","Data Normalization: None\n");
		strcpy(file_tt_temp,file_tt);
		strcpy(file_tr_temp,file_tr);
		break;
	case 1:	
		err_code = pattern_range_normalize(file_tr, file_tt, err_code);
		
		if(*err_code !=0)
		{
			fclose(fp_out);
			n = *err_code;
			return(n);
		}

		strcpy(file_tt_temp,file_tt);
		p = strchr(file_tt_temp,'.');
		strcpy(p,"_norm.txt");

		strcpy(file_tr_temp,file_tr);
		p = strchr(file_tr_temp,'.');
		strcpy(p,"_norm.txt");

		fprintf(fp_out,"%s","Data Normalization: Range-normalization\n");
		break;
	case 2:	
		err_code = pattern_unit_vector_normalization(file_tr, file_tt, err_code);
		if(*err_code !=0)
		{
			fclose(fp_out);
			n = *err_code;
			return(n);
		}

		strcpy(file_tt_temp,file_tt);
		p = strchr(file_tt_temp,'.');
		strcpy(p,"_norm.txt");

		strcpy(file_tr_temp,file_tr);
		p = strchr(file_tr_temp,'.');
		strcpy(p,"_norm.txt");

		fprintf(fp_out,"%s","Data Normalization: Unit Vector Normalization\n");
		break;
	case 3:	
		err_code = pattern_standard_normal_density_normalization(file_tr, file_tt, err_code);
		if(*err_code !=0)
		{
			fclose(fp_out);
			n = *err_code;
			return(n);
		}

		strcpy(file_tt_temp,file_tt);
		p = strchr(file_tt_temp,'.');
		strcpy(p,"_norm.txt");

		strcpy(file_tr_temp,file_tr);
		p = strchr(file_tr_temp,'.');
		strcpy(p,"_norm.txt");

		fprintf(fp_out,"%s","Data Normalization: Standard Normal Density Normalization\n");
		break;
	case 4:	
		err_code = pattern_min_max_normalization(file_tr, file_tt, s_min, s_max, err_code);
		if(*err_code !=0)
		{
			fclose(fp_out);
			n = *err_code;
			return(n);
		}

		strcpy(file_tt_temp,file_tt);
		p = strchr(file_tt_temp,'.');
		strcpy(p,"_norm.txt");

		strcpy(file_tr_temp,file_tr);
		p = strchr(file_tr_temp,'.');
		strcpy(p,"_norm.txt");

		fprintf(fp_out,"%s","Data Normalization: Min-max Normalization\tSmin = ");
		fprintf(fp_out,"%f; Smax = %f\n", s_min, s_max);
		break;
	case 5:	
		err_code = pattern_softmax_scaling_normalization(file_tr, file_tt, r_softmax, err_code);
		if(*err_code !=0)
		{
			fclose(fp_out);
			n = *err_code;
			return(n);
		}

		strcpy(file_tt_temp,file_tt);
		p = strchr(file_tt_temp,'.');
		strcpy(p,"_norm.txt");

		strcpy(file_tr_temp,file_tr);
		p = strchr(file_tr_temp,'.');
		strcpy(p,"_norm.txt");

		fprintf(fp_out,"%s","Data Normalization: Softmax Normalization\tr = ");
		fprintf(fp_out,"%f\n", r_softmax);
		break;
	default:
		printf("Error! k_nearest_neighbor.c. Option selection error on normalization.");
		fclose(fp_out);
		return(6);
		break;
	}

	// Distance or similarity measure performed

	switch(option_distance)
	{
	case 0:	
		fprintf(fp_out,"%s","Distance Measure: Euclidean Distance\n");
		no_of_entries_tr = pattern_euclidean(file_tt_temp, file_tr_temp, err_code);
		if(*err_code !=0)
		{
			fclose(fp_out);
			n = *err_code;
			return(n);
		}
		break;
	case 1:	
		fprintf(fp_out,"%s","Distance Measure: City Block Value Metric\n");
		no_of_entries_tr = pattern_city_block(file_tt_temp, file_tr_temp, err_code);
		if(*err_code !=0)
		{
			fclose(fp_out);
			n = *err_code;
			return(n);
		}
		break;
	case 2:	
		fprintf(fp_out,"%s","Distance Measure: Maximum Value Metric\n");
		no_of_entries_tr = pattern_maximum(file_tt_temp, file_tr_temp, err_code);
		if(*err_code !=0)
		{
			fclose(fp_out);
			n = *err_code;
			return(n);
		}
		break;
	case 3:	
		fprintf(fp_out,"%s","Distance Measure: Minkowski Distance\tr = ");
		fprintf(fp_out,"%d\n",r_minkowski);
		no_of_entries_tr = pattern_minkowski(file_tt_temp, file_tr_temp, r_minkowski, err_code);
		if(*err_code !=0)
		{
			fclose(fp_out);
			n = *err_code;
			return(n);
		}
		break;
	case 4:	
		fprintf(fp_out,"%s","Similarity Measure: Vector Inner Product\n");
		no_of_entries_tr = pattern_vector_inner_product(file_tt_temp, file_tr_temp, err_code);
		if(*err_code !=0)
		{
			fclose(fp_out);
			n = *err_code;
			return(n);
		}
		break;
	case 5:	
		fprintf(fp_out,"%s","Similarity Measure: Tanimoto Metric\n");
		no_of_entries_tr = pattern_tanimoto(file_tt_temp, file_tr_temp, err_code);
		if(*err_code !=0)
		{
			fclose(fp_out);
			n = *err_code;
			return(n);
		}
		break;
	default:
		printf("Error! k_nearest_neighbor.c. Option selection error on distance or similarity measure.");
		fclose(fp_out);
		return(8);
		break;
	}

	// Checks the value of k

	if ((k > no_of_entries_tr) || k<=0)
	{
		printf("\nError! k_nearest_neighbor.c. k can't be greater than the numner of entries in the training set or less or equals to 0.");
		fclose(fp_out);
		return(2);
	}

	// Prints the output file header

	fprintf(fp_out,"%s","Test Set File: ");
	fprintf(fp_out,"%s\n", file_tt);
	fprintf(fp_out,"%s","Training Set File: ");
	fprintf(fp_out,"%s\n", file_tr);

	switch(option_normalize)
	{
	case 0:	
		break;
	case 1:
		fprintf(fp_out,"%s","Normalized Training Set File: ");
		fprintf(fp_out,"%s\n", file_tr_temp);
		fprintf(fp_out,"%s","Normalized Test Set File: ");
		fprintf(fp_out,"%s\n", file_tt_temp);
		break;
	case 2:	
		fprintf(fp_out,"%s","Normalized Training Set File: ");
		fprintf(fp_out,"%s\n", file_tr_temp);
		fprintf(fp_out,"%s","Normalized Test Set File: ");
		fprintf(fp_out,"%s\n", file_tt_temp);
		break;
	case 3:
		fprintf(fp_out,"%s","Normalized Training Set File: ");
		fprintf(fp_out,"%s\n", file_tr_temp);
		fprintf(fp_out,"%s","Normalized Test Set File: ");
		fprintf(fp_out,"%s\n", file_tt_temp);
		break;
	case 4:	
		fprintf(fp_out,"%s","Normalized Training Set File: ");
		fprintf(fp_out,"%s\n", file_tr_temp);
		fprintf(fp_out,"%s","Normalized Test Set File: ");
		fprintf(fp_out,"%s\n", file_tt_temp);
		break;
	case 5:
		fprintf(fp_out,"%s","Normalized Training Set File: ");
		fprintf(fp_out,"%s\n", file_tr_temp);
		fprintf(fp_out,"%s","Normalized Test Set File: ");
		fprintf(fp_out,"%s\n", file_tt_temp);
		break;
	default:
		printf("Error! k_nearest_neighbor.c. Option selection error on normalization.");
		fclose(fp_out);
		return(6);
		break;
	}

	fprintf(fp_out,"%s","Output File: ");
	fprintf(fp_out,"%s\n\n", file_out);
	
	fprintf(fp_out,"%s", "1. Image Name in Test Set\n");
	fprintf(fp_out,"%s", "2. Object's row coordinate in Test Set\n");
	fprintf(fp_out,"%s", "3. Object's column coordinate in Test Set\n");
	fprintf(fp_out,"%s", "4. Class in Test Set\n");
	fprintf(fp_out,"%s", "5. Class in Training Set\n");
	fprintf(fp_out,"%s", "6. Value of Distance or Similarity Measure\n");
	fprintf(fp_out,"%s", "*** END OF PATTERN CLASSIFICATION HEADER ***\n\n\n");

	if ((fp = fopen(file_temp, "r")) ==NULL)
	{
		printf("Error! k_nearest_neighbor.c. Can't open , read or create file.");
		printf("%s\n",file_temp);
		fclose(fp_out);
		return(7);
	}

	// Counts the no. of entries in the temp file

	i = 0;
	ch_temp=fgetc(fp);
	while(ch_temp !=EOF)
	{
		if ((int)ch_temp == 10)
		{
			i++;
		}		
		ch_temp=fgetc(fp);
	}

	// Computes the no. of entries in test file

	no_of_entries_tt = i/no_of_entries_tr;

	rewind(fp);

	// Memory allocation

	data1 = malloc(no_of_entries_tr*sizeof(char *));
	if(!data1)
	{
		printf("\nError! k_nearest_neighbor.c. Memory allocation error.");
		fclose(fp_out);
		fclose(fp);
		return(9);
	}
	for(n=0;n<no_of_entries_tr;n++)
	{
		data1[n] = malloc(MAX_CASE*sizeof(char));
		if(!data1[n])
		{
			printf("\nError! k_nearest_neighbor.c. Memory allocation error.");
			fclose(fp_out);
			fclose(fp);
			return(9);
		}
	}

	data2 = malloc(no_of_entries_tr*sizeof(char *));
	if(!data2)
	{
		printf("\nError! k_nearest_neighbor.c. Memory allocation error.");
		fclose(fp_out);
		fclose(fp);
		return(9);
	}
	for(n=0;n<no_of_entries_tr;n++)
	{
		data2[n] = malloc(MAX_CASE*sizeof(char));
		if(!data2[n])
		{
			printf("\nError! k_nearest_neighbor.c. Memory allocation error.");
			fclose(fp_out);
			fclose(fp);
			return(9);
		}
	}

	class_tt = malloc(no_of_entries_tr*sizeof(char *));
	if(!class_tt)
	{
		printf("\nError! k_nearest_neighbor.c. Memory allocation error.");
		fclose(fp_out);
		fclose(fp);
		return(9);
	}
	for(n=0;n<no_of_entries_tr;n++)
	{
		class_tt[n] = malloc(MAX_CASE*sizeof(char));
		if(!class_tt[n])
		{
			printf("\nError! k_nearest_neighbor.c. Memory allocation error.");
			fclose(fp_out);
			fclose(fp);
			return(9);
		}
	}

	class_tp = malloc(no_of_entries_tr*sizeof(char *));
	if(!class_tp)
	{
		printf("\nError! k_nearest_neighbor.c. Memory allocation error.");
		fclose(fp_out);
		fclose(fp);
		return(9);
	}
	for(n=0;n<no_of_entries_tr;n++)
	{
		class_tp[n] = malloc(MAX_CASE*sizeof(char));
		if(!class_tp[n])
		{
			printf("\nError! k_nearest_neighbor.c. Memory allocation error.");
			fclose(fp_out);
			fclose(fp);
			return(9);
		}
	}

	data3 = malloc(no_of_entries_tr*sizeof(int));
	if(!data3)
	{
		printf("\nError! k_nearest_neighbor.c. Memory allocation error.");
		fclose(fp_out);
		fclose(fp);
		return(9);
	}
	
	data4 = malloc(no_of_entries_tr*sizeof(int));
	if(!data4)
	{
		printf("\nError! k_nearest_neighbor.c. Memory allocation error.");
		fclose(fp_out);
		fclose(fp);
		return(9);
	}
	class_ed = malloc(no_of_entries_tr*sizeof(float));
	if(!class_ed)
	{
		printf("\nError! k_nearest_neighbor.c. Memory allocation error.");
		fclose(fp_out);
		fclose(fp);
		return(9);
	}
	count = malloc(no_of_entries_tr*sizeof(int));
	if(!count)
	{
		printf("\nError! k_nearest_neighbor.c. Memory allocation error.");
		fclose(fp_out);
		fclose(fp);
		return(9);
	}
	
	class_st_tt = malloc(no_of_entries_tt*sizeof(char *));
	if(!class_st_tt)
	{
		printf("\nError! k_nearest_neighbor.c. Memory allocation error.");
		fclose(fp_out);
		fclose(fp);
		return(9);
	}
	for(n=0;n<no_of_entries_tt;n++)
	{
		class_st_tt[n] = malloc(MAX_CASE*sizeof(char));
		if(!class_st_tt[n])
		{
			printf("\nError! k_nearest_neighbor.c. Memory allocation error.");
			fclose(fp_out);
			fclose(fp);
			return(9);
		}

	}

	class_st_id = malloc(no_of_entries_tt*sizeof(char *));
	if(!class_st_id)
	{
		printf("\nError! k_nearest_neighbor.c. Memory allocation error.");
		fclose(fp_out);
		fclose(fp);
		return(9);
	}
	for(n=0;n<no_of_entries_tt;n++)
	{
		class_st_id[n] = malloc(MAX_CASE*sizeof(char));
		if(!class_st_id[n])
		{
			printf("\nError! k_nearest_neighbor.c. Memory allocation error.");
			fclose(fp_out);
			fclose(fp);
			return(9);
		}
	}

	class_list = malloc((no_of_entries_tr+no_of_entries_tt)*sizeof(char *));
	if(!class_list)
	{
		printf("\nError! k_nearest_neighbor.c. Memory allocation error.");
		fclose(fp_out);
		fclose(fp);
		return(9);
	}

	for(n=0;n<(no_of_entries_tr+no_of_entries_tt);n++)
	{
		class_list[n] = malloc(MAX_CASE*sizeof(char));
		if(!class_list[n])
		{
			printf("\nError! k_nearest_neighbor.c. Memory allocation error.");
			fclose(fp_out);
			fclose(fp);
			return(9);
		}

	}

	st = malloc(no_of_entries_tr*sizeof(int *));
	if(!st)
	{
		printf("\nError! k_nearest_neighbor.c. Memory allocation error.");
		fclose(fp_out);
		fclose(fp);
		return(9);
	}
	for(n=0;n<no_of_entries_tr;n++)
	{
		st[n] = malloc((no_of_entries_tr+no_of_entries_tt)*sizeof(int));
		if(!st[n])
		{
			printf("\nError! k_nearest_neighbor.c. Memory allocation error.");
			fclose(fp_out);
			fclose(fp);
			return(9);
		}
	}


	// K Nearest Neighbor algorithm starts for similarity measure 

	if((option_distance == 4) || (option_distance == 5))
	{
		g = 0;
		for(m = 0; m<(no_of_entries_tt); m++)
		{
			// Reads one set of data for one entry in test set from temp file

			for (n = 0; n < no_of_entries_tr; n++)
			{
				fscanf(fp,"%s %s %d %d %f %s %s",data1[n],data2[n],&data3[n],&data4[n],&class_ed[n],class_tt[n],class_tp[n]);
				ch_temp=fgetc(fp);
			}

			// Reorders the set of data according to class_ed

			for (j = 0; j < k; j++)
			{
				for (n = 0; n < no_of_entries_tr - 1 - j; n++)
				{
					if(class_ed[n] > class_ed[n+1])
					{					
						strcpy(temp1,data1[n]);
						temp2 = data3[n];
						temp3 = data4[n];
						strcpy(temp4,class_tt[n]);
						strcpy(temp5,class_tp[n]);
						temp = class_ed[n];

						strcpy(data1[n],data1[n+1]);
						data3[n] = data3[n+1];
						data4[n] = data4[n+1];
						strcpy(class_tt[n],class_tt[n+1]);
						strcpy(class_tp[n],class_tp[n+1]);
						class_ed[n] = class_ed[n+1];
					
						strcpy(data1[n+1],temp1);
						data3[n+1] = temp2;
						data4[n+1] = temp3;
						strcpy(class_tt[n+1],temp4);
						strcpy(class_tp[n+1],temp5);
						class_ed[n+1] = temp;
					}				
				}
			}

			// Resets the value of count to 0

			for(j=no_of_entries_tr - 1;j>no_of_entries_tr - 1 - k;j--)
			{
				count[j]=0;
			}

			// Counts how many matches appear for each entry

			for (j = no_of_entries_tr - 1; j > no_of_entries_tr - 1 - k; j--)
			{
				for (n = no_of_entries_tr - 1; n>no_of_entries_tr - 1 - k; n--)
				{
					if(strcmp(class_tp[j], class_tp[n]) == 0)
					{
						count[j]++;	
					}
				}
			}

			// Rearranges the order according to the count and class_ed

			y = 0;
			for (j=no_of_entries_tr - k;j<no_of_entries_tr - 1;j++)
			{
				if(count[j]>count[j+1])
				{
					n = count[j];
					strcpy(temp1,data1[j]);
					temp2 = data3[j];
					temp3 = data4[j];
					strcpy(temp4,class_tt[j]);
					strcpy(temp5,class_tp[j]);
					temp = class_ed[j];	

					count[j] = count[j+1];
					strcpy(data1[j],data1[j+1]);
					data3[j] = data3[j+1];
					data4[j] = data4[j+1];
					strcpy(class_tt[j],class_tt[j+1]);
					strcpy(class_tp[j],class_tp[j+1]);
					class_ed[j] = class_ed[j+1];	

					count[j+1] = n;
					strcpy(data1[j+1], temp1);
					data3[j+1] = temp2;
					data4[j+1] = temp3;
					strcpy(class_tt[j+1], temp4);
					strcpy(class_tp[j+1], temp5);
					class_ed[j+1] = temp;
					y = 1;
				}
				else if (count[j] == count[j+1])
				{
					if (class_ed[j] > class_ed[j+1])
					{
						strcpy(temp1,data1[j]);
						temp2 = data3[j];
						temp3 = data4[j];
						strcpy(temp4,class_tt[j]);
						strcpy(temp5,class_tp[j]);
						temp = class_ed[j];
							
						strcpy(data1[j],data1[j+1]);
						data3[j] = data3[j+1];
						data4[j] = data4[j+1];
						strcpy(class_tt[j],class_tt[j+1]);
						strcpy(class_tp[j],class_tp[j+1]);
						class_ed[j] = class_ed[j+1];
								
						strcpy(data1[j+1], temp1);
						data3[j+1] = temp2;
						data4[j+1] = temp3;
						strcpy(class_tt[j+1], temp4);
						strcpy(class_tp[j+1], temp5);
						class_ed[j+1] = temp;
					}
				}
				else
				{
					y = 1;
				}
			}

			// Prints the result for one set of entry

			if(y == 1)
			{			
				fprintf(fp_out,"%s %d %d %s %s ",data1[no_of_entries_tr-1], data3[no_of_entries_tr-1], data4[no_of_entries_tr-1], class_tt[no_of_entries_tr-1], class_tp[no_of_entries_tr-1]);
				fprintf(fp_out,"%f\n",class_ed[no_of_entries_tr-1]);
			}
			else if (y == 0)
			{
				fprintf(fp_out,"%s %d %d %s %s ",data1[no_of_entries_tr-1], data3[no_of_entries_tr-1], data4[no_of_entries_tr-1], class_tt[no_of_entries_tr-1], class_tp[no_of_entries_tr-1]);
				fprintf(fp_out,"%f",class_ed[no_of_entries_tr-1]);
				fprintf(fp_out,"\t%s\n","NOTE: The k nearest samples have all different or all the same class names. Nearest neighbor operation performed.");
			}	
			
			strcpy(class_st_tt[m],class_tt[no_of_entries_tr-1]);	
			strcpy(class_st_id[m],class_tp[no_of_entries_tr-1]);			

			y = 0;		
			for(h=0;h<g+1;h++)
			{
				if(strcmp(class_st_tt[m],class_list[h])==0)
				{
					y = 1;
				}
			}	

			if(y==0)
			{
				strcpy(class_list[g],class_st_tt[m]);
				g++;
			}	
		}

		// Frees the  memory

		for(n=0;n<no_of_entries_tr;n++)
		{
			free(data1[n]);
			}
		free(data1);

		for(n=0;n<no_of_entries_tr;n++)
		{
			free(data2[n]);
		}
		free(data2);	

		for(n=0;n<no_of_entries_tr;n++)
		{
			free(class_tt[n]);
		}
		free(class_tt);
		
		for(n=0;n<no_of_entries_tr;n++)
		{
			free(class_tp[n]);
		}
		free(class_tp);

		free(data3);
		free(data4);
		free(class_ed);
		free(count);

		// Finds the the list of class name in test set and the identified class name

		q = g;
		for(m = 0; m<(no_of_entries_tt); m++)
		{
			
			y = 0;		
			for(h=0;h<q+1;h++)
			{
				if(strcmp(class_st_id[m],class_list[h])==0)
				{
					y = 1;
				}
			}
			if(y==0)
			{
				strcpy(class_list[q],class_st_id[m]);
				q++;
			}
		}

		// STATISTICS header

		fprintf(fp_out,"\n\n%s\n","*** STATISTICS ***");
		fprintf(fp_out,"%s\n","#: Class in the Test File");
		fprintf(fp_out,"%s\n\n","@: Class identified");
		for(m = 0; m<g; m++)
		{
			fprintf(fp_out,"#%d. %s\n",m+1,&class_list[m][0]);
		}
		for(m = 0; m<q; m++)
		{
			fprintf(fp_out,"\n@%d. %s",m+1,&class_list[m][0]);
		}	

		fprintf(fp_out,"\n\n%s","   |    ");
	
		for(m = 0; m<q; m++)
		{
			fprintf(fp_out,"@%d\t",m+1);
		}
		fprintf(fp_out,"%s\n","% Correct");

		fprintf(fp_out,"%s","---+----");	

		for(m = 0; m<q; m++)
		{
			fprintf(fp_out,"%s","--------");
		}
		fprintf(fp_out,"%s","----------");	

		// STATISTICS calculation

		for(m = 0; m<g; m++)
		{
			for(n=0;n<q; n++)
			{
				st[m][n]=0;
			}
		}

		for(m = 0; m<g; m++)
		{
			for(n=0;n<q; n++)
			{
				for(h=0;h<(no_of_entries_tt);h++)
				{
					if((strcmp(class_st_tt[h],class_list[m])==0) && (strcmp(class_st_id[h],class_list[n])==0))
					{
						st[m][n]++;
					}
				}
			}
		}

		// Prints the result

		for(m = 0; m<g; m++)
		{
			(int)sum = 0;
			fprintf(fp_out,"\n#%d |\t",m+1);
			for (n=0;n<q;n++)
			{
				fprintf(fp_out,"%d\t",st[m][n]);
				sum = sum + st[m][n];
			}
			percentage = (float)((float)st[m][m]/(float)sum*100.0);
			(int)st[m][n];
			(int)q;
			fprintf(fp_out,"%4.2f",percentage);
			fprintf(fp_out,"%c",'%');
		}

		fclose(fp);
		fclose(fp_out);

		for(n=0;n<no_of_entries_tt;n++)
		{
			free(class_st_tt[n]);
		}
		free(class_st_tt);	

		for(n=0;n<no_of_entries_tt;n++)
		{
			free(class_st_id[n]);
		}
		free(class_st_id);

		for(n=0;n<(no_of_entries_tr+no_of_entries_tt);n++)
		{
			free(class_list[n]);
		}
		free(class_list);	

		for(n=0;n<no_of_entries_tr;n++)
		{
			free(st[n]);
		}
		free(st);
		n = *err_code;
		free(err_code);
		return(n);
	}

	// K Nearest Neighbor algorithm starts for distance measure

	else
	{
		g = 0;
		for(m = 0; m<(no_of_entries_tt); m++)
		{
			for (n = 0; n < no_of_entries_tr; n++)
			{
				fscanf(fp,"%s %s %d %d %f %s %s",data1[n],data2[n],&data3[n],&data4[n],&class_ed[n],class_tt[n],class_tp[n]);
				ch_temp=fgetc(fp);
			}
			for (j = 0; j < k; j++)
			{
				for (n = 0; n < no_of_entries_tr - 1 - j; n++)
				{
					if(class_ed[n] < class_ed[n+1])
					{					
						strcpy(temp1,data1[n]);
						temp2 = data3[n];
						temp3 = data4[n];
						strcpy(temp4,class_tt[n]);
						strcpy(temp5,class_tp[n]);
						temp = class_ed[n];

						strcpy(data1[n],data1[n+1]);
						data3[n] = data3[n+1];
						data4[n] = data4[n+1];
						strcpy(class_tt[n],class_tt[n+1]);
						strcpy(class_tp[n],class_tp[n+1]);
						class_ed[n] = class_ed[n+1];
					
						strcpy(data1[n+1],temp1);
						data3[n+1] = temp2;
						data4[n+1] = temp3;
						strcpy(class_tt[n+1],temp4);
						strcpy(class_tp[n+1],temp5);
						class_ed[n+1] = temp;
					}				
				}
			}
			for(j=no_of_entries_tr - 1;j>no_of_entries_tr - 1 - k;j--)
			{
				count[j]=0;
			}
		
			for (j = no_of_entries_tr - 1; j > no_of_entries_tr - 1 - k; j--)
			{
				for (n = no_of_entries_tr - 1; n>no_of_entries_tr - 1 - k; n--)
				{
					if(strcmp(class_tp[j], class_tp[n]) == 0)
					{
						count[j]++;	
					}
				}
			}
			y = 0;
			for (j=no_of_entries_tr - k;j<no_of_entries_tr - 1;j++)
			{
				if(count[j]>count[j+1])
				{
					n = count[j];
					strcpy(temp1,data1[j]);
					temp2 = data3[j];
					temp3 = data4[j];
					strcpy(temp4,class_tt[j]);
					strcpy(temp5,class_tp[j]);
					temp = class_ed[j];	

					count[j] = count[j+1];
					strcpy(data1[j],data1[j+1]);
					data3[j] = data3[j+1];
					data4[j] = data4[j+1];
					strcpy(class_tt[j],class_tt[j+1]);
					strcpy(class_tp[j],class_tp[j+1]);
					class_ed[j] = class_ed[j+1];	

					count[j+1] = n;
					strcpy(data1[j+1], temp1);
					data3[j+1] = temp2;
					data4[j+1] = temp3;
					strcpy(class_tt[j+1], temp4);
					strcpy(class_tp[j+1], temp5);
					class_ed[j+1] = temp;
					y = 1;
				}
				else if (count[j] == count[j+1])
				{
					if (class_ed[j] < class_ed[j+1])
					{
						strcpy(temp1,data1[j]);
						temp2 = data3[j];
						temp3 = data4[j];
						strcpy(temp4,class_tt[j]);
						strcpy(temp5,class_tp[j]);
						temp = class_ed[j];
							
						strcpy(data1[j],data1[j+1]);
						data3[j] = data3[j+1];
						data4[j] = data4[j+1];
						strcpy(class_tt[j],class_tt[j+1]);
						strcpy(class_tp[j],class_tp[j+1]);
						class_ed[j] = class_ed[j+1];
								
						strcpy(data1[j+1], temp1);
						data3[j+1] = temp2;
						data4[j+1] = temp3;
						strcpy(class_tt[j+1], temp4);
						strcpy(class_tp[j+1], temp5);
						class_ed[j+1] = temp;
					}
				}
				else
				{
					y = 1;
				}
			}

			if(y == 1)
			{			
				fprintf(fp_out,"%s %d %d %s %s ",data1[no_of_entries_tr-1], data3[no_of_entries_tr-1], data4[no_of_entries_tr-1], class_tt[no_of_entries_tr-1], class_tp[no_of_entries_tr-1]);
				fprintf(fp_out,"%f\n",class_ed[no_of_entries_tr-1]);
			}
			else if (y == 0)
			{
				fprintf(fp_out,"%s %d %d %s %s ",data1[no_of_entries_tr-1], data3[no_of_entries_tr-1], data4[no_of_entries_tr-1], class_tt[no_of_entries_tr-1], class_tp[no_of_entries_tr-1]);
				fprintf(fp_out,"%f",class_ed[no_of_entries_tr-1]);
				fprintf(fp_out,"\t%s\n","NOTE: The k nearest samples have all different or all the same class names. Nearest neighbor operation performed.");
			}	
			
			strcpy(class_st_tt[m],class_tt[no_of_entries_tr-1]);	
			strcpy(class_st_id[m],class_tp[no_of_entries_tr-1]);			

			y = 0;		
			for(h=0;h<g+1;h++)
			{
				if(strcmp(class_st_tt[m],class_list[h])==0)
				{
					y = 1;
				}
			}	

			if(y==0)
			{
				strcpy(class_list[g],class_st_tt[m]);
				g++;
			}	
		}

		for(n=0;n<no_of_entries_tr;n++)
		{
			free(data1[n]);
			}
		free(data1);

		for(n=0;n<no_of_entries_tr;n++)
		{
			free(data2[n]);
		}
		free(data2);	

		for(n=0;n<no_of_entries_tr;n++)
		{
			free(class_tt[n]);
		}
		free(class_tt);
		
		for(n=0;n<no_of_entries_tr;n++)
		{
			free(class_tp[n]);
		}
		free(class_tp);

		free(data3);
		free(data4);
		free(class_ed);
		free(count);

		q = g;
		for(m = 0; m<(no_of_entries_tt); m++)
		{			
			y = 0;		
			for(h=0;h<q+1;h++)
			{
				if(strcmp(class_st_id[m],class_list[h])==0)
				{
					y = 1;
				}
			}
			if(y==0)
			{
				strcpy(class_list[q],class_st_id[m]);
				q++;
			}
		}

		// STATISTICS header

		fprintf(fp_out,"\n\n%s\n","*** STATISTICS ***");
		fprintf(fp_out,"%s\n","#: Class in the Test File");
		fprintf(fp_out,"%s\n\n","@: Class identified");
		for(m = 0; m<g; m++)
		{
			fprintf(fp_out,"#%d. %s\n",m+1,&class_list[m][0]);
		}
		for(m = 0; m<q; m++)
		{
			fprintf(fp_out,"\n@%d. %s",m+1,&class_list[m][0]);
		}	

		fprintf(fp_out,"\n\n%s","   |    ");
	
		for(m = 0; m<q; m++)
		{
			fprintf(fp_out,"@%d\t",m+1);
		}
		fprintf(fp_out,"%s\n","% Correct");

		fprintf(fp_out,"%s","---+----");	

		for(m = 0; m<q; m++)
		{
			fprintf(fp_out,"%s","--------");
		}
		fprintf(fp_out,"%s","----------");	

		// STATISTICS calculation

		for(m = 0; m<g; m++)
		{
			for(n=0;n<q; n++)
			{
				st[m][n]=0;
			}
		}

		for(m = 0; m<g; m++)
		{
			for(n=0;n<q; n++)
			{
				for(h=0;h<(no_of_entries_tt);h++)
				{
					if((strcmp(class_st_tt[h],class_list[m])==0) && (strcmp(class_st_id[h],class_list[n])==0))
					{
						st[m][n]++;
					}
				}
			}
		}
	
		// Prints the result

		for(m = 0; m<g; m++)
		{
			(int)sum = 0;
			fprintf(fp_out,"\n#%d |\t",m+1);
			for (n=0;n<q;n++)
			{
				fprintf(fp_out,"%d\t",st[m][n]);
				sum = sum + st[m][n];
			}
			percentage = (float)((float)st[m][m]/(float)sum*100.0);
			(int)st[m][n];
			(int)q;
			fprintf(fp_out,"%4.2f",percentage);
			fprintf(fp_out,"%c",'%');
		}

		fclose(fp);
		fclose(fp_out);

		for(n=0;n<no_of_entries_tt;n++)
		{
			free(class_st_tt[n]);
		}
		free(class_st_tt);	

		for(n=0;n<no_of_entries_tt;n++)
		{
			free(class_st_id[n]);
		}
		free(class_st_id);

		for(n=0;n<(no_of_entries_tr+no_of_entries_tt);n++)
		{
			free(class_list[n]);
		}
		free(class_list);	

		for(n=0;n<no_of_entries_tr;n++)
		{
			free(st[n]);
		}
		free(st);
		n = *err_code;
		free(err_code);
		return(n);
	}

}