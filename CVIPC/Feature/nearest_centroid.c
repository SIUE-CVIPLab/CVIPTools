/***************************************************************************
* =========================================================================
*
*			 CVIPtools - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: nearest_centroid.c 
*		  Expanded Name: Nearest centroid function
*			 Parameters: Pointers pointing to the file names of training and test
*						 set, nomalization and distance/similarity option,
*						 specified min and max, constant r_softmax, r_minkowski
*				 Return: error code
*           Description: It contains the function to call lower level functions to 
*						 calculate centroids for each class in the training set, 
*						 normalize the feature files, calculate the distance/
*						 similarity between each sample in test set to all samples 
*						 in training set, use nearest neighbor algorithm to find 
*						 the closest match sample in the centroid training set to 
*						 the sample in the test set,calculate the STATISTICS, write 
*						 all the useful information in the output file
*   Initial Coding Date: May 26, 2005
*Last Modification Made: July 8, 2005
*           Portability: Standard (ANSI) C
*             Credit(s): Husain Kagalwalla, Geer Shuang, Amit Kharbanda
*                        Southern Illinois University at Edwardsville
*
*		  Copyright (c): 1995-2005 SIUE - Scott Umbaugh
****************************************************************************/

/*
** include header file_trs
*/

#include	"stdio.h"
#include	"math.h"
#include	"float.h"
#include	"stdlib.h"
#include	"string.h"
#include	"CVIPpattern.h"

int nearest_centroid(char *file_tt, char *file_tr, char *file_out, int option_normalize, int option_distance, float s_min, float s_max, float r_softmax, int r_minkowski)
{
	struct temp
	{		
		char	data1[MAX_CASE];
		char	data2[MAX_CASE];
		char	data3[MAX_CASE];
		char	data4[MAX_CASE];
		float	class_ed;
		char	class_tt[MAX_CASE];
		char	class_tp[MAX_CASE];
	};

	struct	temp te[2]; 

	int		i ,y = 0,n,m,g,h,sum,k;
	int		no_of_entries_tr,no_of_entries_tt;
	
	char	tempfile[MAX_CASE] = "CVIPtemp.txt";
	char	*file_temp = &tempfile[0];
	char	ch_tr;
	char	ch_temp;
	char	*libvar;
	char	temp[MAX_CASE];
	char	temp1[MAX_CASE];
	char	temp2[MAX_CASE];
	char	*file_tr_temp = &temp[0];
	char	*file_tt_temp = &temp1[0];
	char	*file_tr_cen = &temp2[0];
	char	*p;
	char	**class_st_tt;
	char	**class_st_id;
	char	**class_list;
	char	**st;
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
		printf("Error! nearest_centroid.c. Can't open , read or create file.");
		printf("%s\n",file_tr);
		return(7);
	}
	

	if ((fp_out = fopen(file_out, "w+")) == NULL)
	{
		printf("Error! nearest_centroid.c. Can't open , read or create file.");
		printf("%s\n",file_out);
		fclose(fp_tr);
		return(7);
	}

	// Writes the header from tr file into output file

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

	fprintf(fp_out,"%s","\n*** PATTERN CLASSIFICATION HEADER ***\n");
	fprintf(fp_out,"%s","Classification Algorithm: Nearest Centroid\n");	

	err_code = nearest_centroid_set(file_tr, err_code);
	if(*err_code !=0)
	{
		fclose(fp_out);
		n = *err_code;
		return(n);
	}

	strcpy(file_tr_cen,file_tr);
	p = strchr(file_tr_cen,'.');
	strcpy(p,"_centroid.txt");
	// Normalization performed
	switch(option_normalize)
	{
	case 0:	
		fprintf(fp_out,"%s","Data Normalization: None\n");
		strcpy(file_tt_temp,file_tt);
		strcpy(file_tr_temp,file_tr_cen);
		break;
	case 1:	
		err_code = pattern_range_normalize(file_tr_cen, file_tt, err_code);
		if(*err_code !=0)
		{
			fclose(fp_out);
			n = *err_code;
			return(n);
		}

		strcpy(file_tt_temp,file_tt);
		p = strchr(file_tt_temp,'.');
		strcpy(p,"_norm.txt");

		strcpy(file_tr_temp,file_tr_cen);
		p = strchr(file_tr_temp,'.');
		strcpy(p,"_norm.txt");

		fprintf(fp_out,"%s","Data Normalization: Range-normalization\n");
		break;
	case 2:			
		err_code = pattern_unit_vector_normalization(file_tr_cen, file_tt, err_code);
		if(*err_code !=0)
		{
			fclose(fp_out);
			n = *err_code;
			return(n);
		}

		strcpy(file_tt_temp,file_tt);
		p = strchr(file_tt_temp,'.');
		strcpy(p,"_norm.txt");

		strcpy(file_tr_temp,file_tr_cen);
		p = strchr(file_tr_temp,'.');
		strcpy(p,"_norm.txt");

		fprintf(fp_out,"%s","Data Normalization: Unit Vector Normalization\n");
		break;

	case 3:	
		err_code = pattern_standard_normal_density_normalization(file_tr_cen, file_tt, err_code);
		if(*err_code !=0)
		{
			fclose(fp_out);
			n = *err_code;
			return(n);
		}
		
		strcpy(file_tt_temp,file_tt);
		p = strchr(file_tt_temp,'.');
		strcpy(p,"_norm.txt");

		strcpy(file_tr_temp,file_tr_cen);
		p = strchr(file_tr_temp,'.');
		strcpy(p,"_norm.txt");

		fprintf(fp_out,"%s","Data Normalization: Standard Normal Density Normalization\n");
		break;
	case 4:	
		err_code = pattern_min_max_normalization(file_tr_cen, file_tt, s_min, s_max, err_code);
		if(*err_code !=0)
		{
			fclose(fp_out);
			n = *err_code;
			return(n);
		}
				
		strcpy(file_tt_temp,file_tt);
		p = strchr(file_tt_temp,'.');
		strcpy(p,"_norm.txt");

		strcpy(file_tr_temp,file_tr_cen);
		p = strchr(file_tr_temp,'.');
		strcpy(p,"_norm.txt");

		fprintf(fp_out,"%s","Data Normalization: Min-max Normalization\tSmin = ");
		fprintf(fp_out,"%f; Smax = %f\n", s_min, s_max);
		break;
	case 5:	
		err_code = pattern_softmax_scaling_normalization(file_tr_cen, file_tt, r_softmax, err_code);
		if(*err_code !=0)
		{
			fclose(fp_out);
			n = *err_code;
			return(n);
		}
				
		strcpy(file_tt_temp,file_tt);
		p = strchr(file_tt_temp,'.');
		strcpy(p,"_norm.txt");

		strcpy(file_tr_temp,file_tr_cen);
		p = strchr(file_tr_temp,'.');
		strcpy(p,"_norm.txt");

		fprintf(fp_out,"%s","Data Normalization: Softmax Normalization\tr = ");
		fprintf(fp_out,"%f\n", r_softmax);
		break;
	default:
		printf("Error! nearest_centroid.c. Option selection error on normalization.");
		fclose(fp_out);
		return(6);
		break;
	}

	// Distance/Similarity measure performed
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
		printf("Error! nearest_centroid.c. Option selection error on distance or similarity measure.");
		fclose(fp_out);
		return(8);
		break;
	}

	
	if ((fp = fopen(file_temp, "r")) == NULL)
	{
		printf("Error! nearest_centroid.c. Can't open , read or create file.");
		printf("%s\n",file_temp);
		fclose(fp_out);
		return(7);
	}
	fprintf(fp_out,"%s","Training Set File: ");
	fprintf(fp_out,"%s\n", file_tr);
	fprintf(fp_out,"%s","Testing Set File: ");
	fprintf(fp_out,"%s\n", file_tt);

	// Calls the nearest_centroid_set function, and applies the nearest neighbor algorithm

	


	fprintf(fp_out,"%s","Centroid Training Set File: ");
	fprintf(fp_out,"%s\n", file_tr_cen);
	// Prints the header in the output file according to type of normalization selected by the user 
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
		printf("Error! nearest_centroid.c. Option selection error on normalization.");
		fclose(fp_out);
		fclose(fp);
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

	rewind(fp);
	no_of_entries_tt = i/no_of_entries_tr;

	// Memory allocation

	class_st_tt = malloc(no_of_entries_tt*sizeof(char *));
	if(!class_st_tt)
		{
			printf("\nError! nearest_centroid.c. Memory allocation error.");
			fclose(fp_out);
			fclose(fp);
			return(9);
		}
	for(n=0;n<no_of_entries_tt;n++)
	{
		class_st_tt[n] = malloc(MAX_CASE*sizeof(char));
		if(!class_st_tt[n])
		{
			printf("\nError! nearest_centroid.c. Memory allocation error.");
			fclose(fp_out);
			fclose(fp);
			return(9);
		}
	}

	class_st_id = malloc(no_of_entries_tt*sizeof(char *));
	if(!class_st_id)
		{
			printf("\nError! nearest_centroid.c. Memory allocation error.");
			fclose(fp_out);
			fclose(fp);
			return(9);
		}
	for(n=0;n<no_of_entries_tt;n++)
	{
		class_st_id[n] = malloc(MAX_CASE*sizeof(char));
		if(!class_st_id[n])
			{
				printf("\nError! nearest_centroid.c. Memory allocation error.");
				fclose(fp_out);
				fclose(fp);
				return(9);
			}

	}

	class_list = malloc((no_of_entries_tt+no_of_entries_tt)*sizeof(char *));
	if(!class_list)
		{
			printf("\nError! nearest_centroid.c. Memory allocation error.");
			fclose(fp_out);
			fclose(fp);
			return(9);
		}
	for(n=0;n<(no_of_entries_tt+no_of_entries_tt);n++)
	{
		class_list[n] = malloc(MAX_CASE*sizeof(char));
		if(!class_list[n])
			{
				printf("\nError! nearest_centroid.c. Memory allocation error.");
				fclose(fp_out);
				fclose(fp);
				return(9);
			}
	}

	st = malloc(i*sizeof(int *));
	if(!st)
		{
			printf("\nError! nearest_centroid.c. Memory allocation error.");
			fclose(fp_out);
			fclose(fp);
			return(9);
		}
	for(n=0;n<i;n++)
	{
		st[n] = malloc((no_of_entries_tt+no_of_entries_tt)*sizeof(int));
		if(!st[n])
		{
			printf("\nError! nearest_centroid.c. Memory allocation error.");
			fclose(fp_out);
			fclose(fp);
			return(9);
		}

	}
	
	// Nearest neighbor method performed for similarity measure 
	if((option_distance == 4) || (option_distance == 5))
	{
		// Reads one set of data in the matrix
		g = 0;
		for(m = 0; m<(no_of_entries_tt); m++)
		{
			te[1].class_ed = (float)(pow(10,-38)*(-3.4));
			for(n = m*no_of_entries_tr ; n < (m+1)*no_of_entries_tr; n++)  
			{
				fscanf(fp,"%s %s %s %s %f %s %s",te[0].data1,te[0].data2,te[0].data3,te[0].data4,&te[0].class_ed,te[0].class_tt,te[0].class_tp);
				if (te[0].class_ed > te[1].class_ed)
				{				
					strcpy(te[1].data1,te[0].data1);
					strcpy(te[1].data3,te[0].data3);
					strcpy(te[1].data4,te[0].data4);
					te[1].class_ed = te[0].class_ed;
					strcpy(te[1].class_tt,te[0].class_tt);	
					strcpy(te[1].class_tp,te[0].class_tp);
				}
			}

			fprintf(fp_out,"%s %s %s ",&te[1].data1,&te[1].data3,&te[1].data4);
			fprintf(fp_out,"%s ",&te[1].class_tt);
			fprintf(fp_out,"%s ",&te[1].class_tp);
			fprintf(fp_out,"%f\n",te[1].class_ed);
			strcpy(class_st_tt[m],te[1].class_tt);	
			strcpy(class_st_id[m],te[1].class_tp);

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

		// Finds the greatest similarity entry
		k = g;
		for(m = 0; m<(no_of_entries_tt); m++)
		{

			y = 0;		
			for(h=0;h<k+1;h++)
			{
				if(strcmp(class_st_id[m],class_list[h])==0)
				{
					y = 1;
				}
			}
			if(y==0)
			{
				strcpy(class_list[k],class_st_id[m]);
				k++;
			}
		}
		
		// Data Statistics 
		fprintf(fp_out,"\n\n%s\n","*** STATISTICS ***");
		fprintf(fp_out,"%s\n","#: Class in the Test File");
		fprintf(fp_out,"%s\n\n","@: Class identified");
		for(m = 0; m<g; m++)
		{
			fprintf(fp_out,"#%d. %s\n",m+1,class_list[m]);
		}
		for(m = 0; m<k; m++)
		{
			fprintf(fp_out,"\n@%d. %s",m+1,class_list[m]);
		}

		fprintf(fp_out,"\n\n%s","   |    ");	

		for(m = 0; m<k; m++)
		{
			fprintf(fp_out,"@%d\t",m+1);
		}
		fprintf(fp_out,"%s\n","% Correct");
		
		fprintf(fp_out,"%s","---+----");		

		for(m = 0; m<k; m++)
		{
			fprintf(fp_out,"%s","--------");
		}
		fprintf(fp_out,"%s","----------");

		for(m = 0; m<g; m++)
		{
			for(n=0;n<k; n++)
			{
				st[m][n]=0;
			}
		}

		for(m = 0; m<g; m++)
		{
			for(n=0;n<k; n++)
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
	
		for(m = 0; m<g; m++)
		{
			(int)sum = 0;
			fprintf(fp_out,"\n#%d |\t",m+1);
			for (n=0;n<k;n++)
			{
				fprintf(fp_out,"%d\t",st[m][n]);
				sum = sum + st[m][n];
			}
			percentage = (float)((float)st[m][m]/(float)sum*100.0);
			(int)st[m][n];
			(int)k;
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

		for(n=0;n<(no_of_entries_tt+no_of_entries_tt);n++)
		{
			free(class_list[n]);
		}
		free(class_list);

		for(n=0;n<i;n++)
		{
			free(st[n]);
		}
		free(st);
		n = *err_code;
		free(err_code);
		return(n);
	}

	// Nearest neighbor method performed for distance measure 
	else
	{
		// Reads one set of data in the matrix
		g = 0;
		for(m = 0; m<(no_of_entries_tt); m++)
		{
			te[1].class_ed = (float)(pow(10,38)*3.4);
			for(n = m*no_of_entries_tr ; n < (m+1)*no_of_entries_tr; n++)  
			{
				fscanf(fp,"%s %s %s %s %f %s %s",te[0].data1,te[0].data2,te[0].data3,te[0].data4,&te[0].class_ed,te[0].class_tt,te[0].class_tp);
				if (te[0].class_ed < te[1].class_ed)
				{				
					strcpy(te[1].data1,te[0].data1);
					strcpy(te[1].data3,te[0].data3);
					strcpy(te[1].data4,te[0].data4);
					te[1].class_ed = te[0].class_ed;
					strcpy(te[1].class_tt,te[0].class_tt);	
					strcpy(te[1].class_tp,te[0].class_tp);
				}
			}

			fprintf(fp_out,"%s %s %s ",&te[1].data1,&te[1].data3,&te[1].data4);
			fprintf(fp_out,"%s ",&te[1].class_tt);
			fprintf(fp_out,"%s ",&te[1].class_tp);
			fprintf(fp_out,"%f\n",te[1].class_ed);
			strcpy(class_st_tt[m],te[1].class_tt);	
			strcpy(class_st_id[m],te[1].class_tp);

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

		// Finds the smallest distance entry
		k = g;
		for(m = 0; m<(no_of_entries_tt); m++)
		{			
			y = 0;		
			for(h=0;h<k+1;h++)
			{
				if(strcmp(class_st_id[m],class_list[h])==0)
				{
					y = 1;
				}
			}
			if(y==0)
			{
				strcpy(class_list[k],class_st_id[m]);
				k++;
			}
		}
		 
		// Data Statistics
		fprintf(fp_out,"\n\n%s\n","*** STATISTICS ***");
		fprintf(fp_out,"%s\n","#: Class in the Test File");
		fprintf(fp_out,"%s\n\n","@: Class identified");
		for(m = 0; m<g; m++)
		{
			fprintf(fp_out,"#%d. %s\n",m+1,class_list[m]);
		}
		for(m = 0; m<k; m++)
		{
			fprintf(fp_out,"\n@%d. %s",m+1,class_list[m]);
		}

		fprintf(fp_out,"\n\n%s","   |    ");	

		for(m = 0; m<k; m++)
		{
			fprintf(fp_out,"@%d\t",m+1);
		}
		fprintf(fp_out,"%s\n","% Correct");
		
		fprintf(fp_out,"%s","---+----");		

		for(m = 0; m<k; m++)
		{
			fprintf(fp_out,"%s","--------");
		}
		fprintf(fp_out,"%s","----------");

		for(m = 0; m<g; m++)
		{
			for(n=0;n<k; n++)
			{
				st[m][n]=0;
			}
		}

		for(m = 0; m<g; m++)
		{
			for(n=0;n<k; n++)
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
	
		for(m = 0; m<g; m++)
		{
			(int)sum = 0;
			fprintf(fp_out,"\n#%d |\t",m+1);
			for (n=0;n<k;n++)
			{
				fprintf(fp_out,"%d\t",st[m][n]);
				sum = sum + st[m][n];
			}
			percentage = (float)((float)st[m][m]/(float)sum*100.0);
			(int)st[m][n];
			(int)k;
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

		for(n=0;n<(no_of_entries_tt+no_of_entries_tt);n++)
		{
			free(class_list[n]);
		}
		free(class_list);

		for(n=0;n<i;n++)
		{
			free(st[n]);
		}
		free(st);
		n = *err_code;
		free(err_code);
		return(n);
	}

}