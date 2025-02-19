/***************************************************************************
* =========================================================================
*
*			 CVIPtools - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: nearest_centroid_set.c 
*		  Expanded Name: Nearest centroid setup function
*			 Parameters: Pointers pointing to the file names of training, error code
*				 Return: error code
*           Description: It contains the function to read feature data from
*						 training set file, calculates the centroid for each class 
*						 and creates new centroid training file 
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

#include "stdio.h"
#include "math.h"
#include "float.h"
#include "stdlib.h"
#include "string.h"

#define MAX_CASE 128

int *nearest_centroid_set(char *file_tr, int *err_code)
{
	float	**vector;
	int		r, c; 
	int		i=0,j=0,m=0,n=0,h=0,y=0,k=0,cnt=0;
	char	ch;
	char	temp[MAX_CASE];
	char	temp1[MAX_CASE];
	char	*file_tr_temp = &temp[0];
	char	*p;
	char	*pp = &temp1[0];
	char	**img;
	char	**class_name;
	char	**class_list;
	FILE	* fp_tr;
	FILE	* fp_tr_temp;
	
	// Gets the centroid file name
	strcpy(file_tr_temp,file_tr);
	p = strchr(file_tr_temp,'.');
	strcpy(p,"_centroid.txt");	
	p = strchr(file_tr_temp,'\\');
	if(p==NULL)
	{
		strcpy(pp,file_tr_temp);
	}
	else
	{
		while(p!=NULL)
		{
			strcpy(pp,p);
			p++;
			p = strchr(p,'\\');	
		}
		pp++;
	}	

	if ((fp_tr = fopen(file_tr, "r")) ==NULL)
	{
		printf("Error! nearest_centroid_set.c. Can't open , read or create file.");
		printf("%s\n",file_tr);
		*err_code = 7;
		return(err_code);
	}

	if ((fp_tr_temp = fopen(file_tr_temp, "w+")) ==NULL)
	{
		printf("Error! nearest_centroid_set.c. Can't open , read or create file.");
		printf("%s\n",file_tr_temp);
		fclose(fp_tr);
		*err_code = 7;
		return(err_code);
	}

	// Checks for '*' symbol to check the number of headers in the file

	ch=fgetc(fp_tr);
	
	i = 0;
	while(ch != EOF)		// Training file
	{
		if(ch == '*')
		{
			i++;
		}
		ch=fgetc(fp_tr);
	}
	if(i>6)
	{
		printf("Error! nearest_centroid.c. There is more than one header in the training set.");
		printf("%s\n",file_tr);
		fclose(fp_tr);
		fclose(fp_tr_temp);
		*err_code = 13;
		return(err_code);
	}

	rewind(fp_tr);

	// Prints the header into the centroid file
	ch=fgetc(fp_tr);
	while (ch != '*')
	{
		fputc(ch, fp_tr_temp);
		ch=fgetc(fp_tr);
	}
	for (i=0;i<64;i++)
	{
		fputc(ch, fp_tr_temp);
		ch=fgetc(fp_tr);
	}
	fprintf(fp_tr_temp,"%s\n","");

	// Gets the image name
	fscanf(fp_tr, "%s", &temp[0]);

	// Gets row and column from training set
	fscanf(fp_tr, "%d",&m);
	ch=fgetc(fp_tr);
	fscanf(fp_tr, "%d",&n);
	ch=fgetc(fp_tr);
	ch = fgetc(fp_tr);

	// Counts the number of features in a data line
	// If the character is between 0~9 or is "-", it is required
	// otherwise it is the end of that data line
	// therefore the class name can not be started with 0~9 or "-"

	i=0;		// Number of data columns

	while ((((int)ch > 47) && ((int)ch < 58) ) || ((int)ch == 45))
	{	
		// Arranges the position of file pointer
		fseek(fp_tr, -1, 1);

		// Gets a number and sends it to temp[]
		fscanf(fp_tr, "%s", &temp[0]);

		// Skip " " (blank spaces)
		ch=fgetc(fp_tr);	
		ch=fgetc(fp_tr);
		i++;	
	}

	// Counts how many entries (rows) are in training file
	j=0;
	while(ch != EOF)
	{
		if((int)ch == 10)
		{
			ch=fgetc(fp_tr);
			j++;
		}
		else
		{
			ch=fgetc(fp_tr);
		}
	}
	j = j/2;
	rewind(fp_tr);

	// Memory allocation
	vector = malloc(j*sizeof(float *));
	if(!vector)
	{
		printf("\nError! nearest_centroid_set.c. Memory allocation error.");
		fclose(fp_tr);
		fclose(fp_tr_temp);
		*err_code = 9;
		return(err_code);
	}
	for(n=0;n<j;n++)
	{
		vector[n] = malloc(i*sizeof(float *));
		if(!vector[n])
		{
			printf("\nError! nearest_centroid_set.c. Memory allocation error.");
			fclose(fp_tr);
			fclose(fp_tr_temp);
			*err_code = 9;
			return(err_code);
		}
	}

	img = malloc(j*sizeof(char *));
	if(!img)
	{
		printf("\nError! nearest_centroid_set.c. Memory allocation error.");
		fclose(fp_tr);
		fclose(fp_tr_temp);
		*err_code = 9;
		return(err_code);
	}
	for(n=0;n<j;n++)
	{
		img[n] = malloc(MAX_CASE*sizeof(char));
		if(!img[n])
		{
			printf("\nError! nearest_centroid_set.c. Memory allocation error.");
			fclose(fp_tr);
			fclose(fp_tr_temp);
			*err_code = 9;
			return(err_code);
		}
	}

	class_name = malloc(j*sizeof(char *));
	if(!class_name)
	{
		printf("\nError! nearest_centroid_set.c. Memory allocation error.");
		fclose(fp_tr);
		fclose(fp_tr_temp);
		*err_code = 9;
		return(err_code);
	}
	for(n=0;n<j;n++)
	{
		class_name[n] = malloc(MAX_CASE*sizeof(char));
		if(!class_name[n])
		{
			printf("\nError! nearest_centroid_set.c. Memory allocation error.");
			fclose(fp_tr);
			fclose(fp_tr_temp);
			*err_code = 9;
			return(err_code);
		}
	}

	class_list = malloc(j*sizeof(char *));
	if(!class_list)
	{
		printf("\nError! nearest_centroid_set.c. Memory allocation error.");
		fclose(fp_tr);
		fclose(fp_tr_temp);
		*err_code = 9;
		return(err_code);
	}
	for(n=0;n<j;n++)
	{
		class_list[n] = malloc(MAX_CASE*sizeof(char));
		if(!class_list[n])
		{
			printf("\nError! nearest_centroid_set.c. Memory allocation error.");
			fclose(fp_tr);
			fclose(fp_tr_temp);
			*err_code = 9;
			return(err_code);
		}
	}

	ch=fgetc(fp_tr);
	while (ch != '*')
	{
		ch=fgetc(fp_tr);
	}
	for (n=0;n<63;n++)
	{
		ch=fgetc(fp_tr);
	}


	ch=fgetc(fp_tr);

	// Reads data in metric(numbers) and arrays(class and image name)
	for(n=0;n<j;n++)
	{
		// Gets the image name
		fscanf(fp_tr, "%s", img[n]);
		
		// Gets row and column from training set
		fscanf(fp_tr, "%d",&r);
		ch=fgetc(fp_tr);
		fscanf(fp_tr, "%d",&c);
		ch=fgetc(fp_tr);

		for(m=0;m<i;m++)
		{	
			fscanf(fp_tr, "%f", &vector[n][m]);

			// Skip " " (blank spaces)
			ch=fgetc(fp_tr);
		}

		ch=fgetc(fp_tr);
		// Gets the class from training set
		if((int)ch == 10)
		{
			printf("Error! nearest_centroid_set.c. Every entry in training set should have a class name.");
			fclose(fp_tr);
			fclose(fp_tr_temp);
			*err_code = 10;
			for(n=0;n<j;n++)
			{
				free(vector[n]);
			}
			free(vector);
			
			for(n=0;n<j;n++)
			{
				free(img[n]);
			}
			free (img);
			
			for(n=0;n<j;n++)
			{
				free(class_name[n]);
			}
			free(class_name);
			for(n=0;n<j;n++)
			{
				free(class_list[n]);
			}
			free(class_list);
			return(err_code);
		}
		else 
		{
			fseek(fp_tr, -1, 1);
			fscanf(fp_tr,"%s",class_name[n]);
		}	
		ch=fgetc(fp_tr);
		ch=fgetc(fp_tr);
	}
	fclose(fp_tr);

	n=0;	
	// Loop for entering unique class names into a list 
	for(m = 0; m<j; m++)
	{
		y = 0;		
		for(h=0;h<n+1;h++)
		{
			if(strcmp(class_name[m],class_list[h])==0)
			{
				y = 1;
			}
		}

		if(y==0)
		{
			strcpy(class_list[n],class_name[m]);
			n++;
		}
	}

	// Combines all the samples with the same class name and calculates the mean for them
	for(m = 0; m<n; m++)
	{
		cnt=0;
		for(k=0;k<j;k++)
		{
			if((strcmp(class_name[k],class_list[m])==0) && (cnt==0))
			{
				for(h=0;h<i;h++)
				{
					vector[m][h] = vector[k][h];
				}
				cnt++;
			}
			else if((strcmp(class_name[k],class_list[m])==0) && (cnt!=0))
			{
				for(h=0;h<i;h++)
				{
					vector[m][h] = vector[m][h] + vector[k][h];
				}	
				cnt++;
			}
		}
		
		for(h=0;h<i;h++)
		{
			if(cnt==0)
			{
				printf("Error! nearest_centroid.c. Divisor is 0. Please check the data in the training set feature file. There may be no sample in the training set.");
				fclose(fp_tr_temp);
				*err_code = 11;
				for(n=0;n<j;n++)
				{
					free(vector[n]);
				}
				free(vector);

				for(n=0;n<j;n++)
				{
					free(img[n]);
				}
				free (img);
				
				for(n=0;n<j;n++)
				{
					free(class_name[n]);
				}
				free(class_name);
				for(n=0;n<j;n++)
				{
					free(class_list[n]);
				}
				free(class_list);
				return(err_code);
			}
			else
			{
				vector[m][h] = vector[m][h]/cnt ;
			}			
		}	
	}
	// Prints the  result to the centorid training file
	for (m=0;m<n;m++)
	{
		fprintf(fp_tr_temp,"%s %d %d ",pp, 0 ,0);
		for(k=0;k<i;k++)
		{
			fprintf(fp_tr_temp,"%f ", vector[m][k]);
		}

		fprintf(fp_tr_temp,"%s\n\n", class_list[m]);
	}

	fclose(fp_tr_temp);
	for(n=0;n<j;n++)
	{
		free(vector[n]);
	}
	free(vector);

	for(n=0;n<j;n++)		
	{
		free(img[n]);
	}
	free (img);

	for(n=0;n<j;n++)		
	{
		free(class_name[n]);
	}
	free(class_name);
	for(n=0;n<j;n++)		
	{
		free(class_list[n]);
	}
	free(class_list);
	return(err_code);
}