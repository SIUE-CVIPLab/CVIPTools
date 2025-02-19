/***************************************************************************
* =========================================================================
*
*			 CVIPtools - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: pattern_unit_vector_normalization.c 
*		  Expanded Name: Pattern classification unit vector normalization
*			 Parameters: Pointers pointing to the file names of training and 
*						 test set, error code
*				 Return: error code
*           Description: It contains the function to read the feature data from
*						 training and test set files, and calls lower level function 
*						 to normalize the data. Creates new feature files for 
*						 training and test sets which includes the normalized data
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

extern float **unit_vector_normalization(float **vector, int i, int j, int option, int *err_code);

int *pattern_unit_vector_normalization(char *file_tr, char *file_tt, int *err_code)
{	
	float	**vector;
	float	*b;
	int		*r, *c; // r is row, c is column
	int		i=0;
	int		j=0;
	int		jj=0;
	int		g=0;
	int		n,m;
	int		size;
	char	ch, ch_tt,ch_tr;
	char	temp[MAX_CASE];
	char	temp1[MAX_CASE];
	char	*file_tr_temp = &temp[0];
	char	*file_tt_temp = &temp1[0];
	char	*p;
	char	**img;
	char	**class_name;
	FILE	* fp_tr;
	FILE	* fp_tt;
	FILE	* fp_tr_temp;
	FILE	* fp_tt_temp;

	if ((fp_tr = fopen(file_tr, "r")) ==NULL)
	{
		printf("Error! pattern_unit_vector_normalization.c. Can't open , read or create file.");
		printf("%s\n",file_tr);
		*err_code = 7;
		return(err_code);
	}

	if ((fp_tt = fopen(file_tt, "r")) ==NULL)
	{
		printf("Error! pattern_unit_vector_normalization.c. Can't open , read or create file.");
		printf("%s\n",file_tt);
		fclose(fp_tr);
		*err_code = 7;
		return(err_code);
	}

	ch_tr=fgetc(fp_tr);
	ch_tt=fgetc(fp_tt);
	
	// Checks for '*' symbol to check the number of headers in the file

	i = 0;
	while(ch_tr != EOF)			// Training file
	{
		if(ch_tr == '*')
		{
			i++;
		}
		ch_tr=fgetc(fp_tr);
	}
	if(i>6)
	{
		printf("Error! pattern_unit_vector_normalization.c. There is more than one header in the training set.");
		printf("%s\n",file_tr);
		fclose(fp_tr);
		fclose(fp_tt);
		*err_code = 13;
		return(err_code);
	}
	i = 0;
	while(ch_tt != EOF)			// Test file
	{
		if(ch_tt == '*')
		{
			i++;
		}
		ch_tt=fgetc(fp_tt);
	}
	if(i>6)
	{
		printf("Error! pattern_unit_vector_normalization.c. There is more than one header in the test set.");
		printf("%s\n",file_tt);
		fclose(fp_tr);
		fclose(fp_tt);
		*err_code = 13;
		return(err_code);
	}

	rewind(fp_tr);
	rewind(fp_tt);

	ch_tr=fgetc(fp_tr);
	ch_tt=fgetc(fp_tt);

	// To check whether the features in the training and the test file are same

	while ((ch_tt != '*') || (ch_tr != '*'))
	{
		if ((ch_tr == ch_tt))
		{
			ch_tt=fgetc(fp_tt);	
			ch_tr=fgetc(fp_tr);
		}
		else
		{
			printf("Error! pattern_unit_vector_normalization.c. The header in the training and test files don't match.");
			fclose(fp_tr);
			fclose(fp_tt);
			*err_code = 1;
			return(err_code);
		}		
	}

	fseek(fp_tr, 66, 1);

	// Gets image name
	fscanf(fp_tr, "%s", &temp[0]);

	// Gets row and column from the training set
	fscanf(fp_tr, "%d",&m);
	ch_tr=fgetc(fp_tr);
	fscanf(fp_tr, "%d",&n);
	ch_tr=fgetc(fp_tr);
	ch_tr = fgetc(fp_tr);

	// Counts the number of features in a data line
	// If the character is between 0~9 or is "-", it is required
	// otherwise it is the end of that data line
	// therefore the class name can not be started with 0~9 or "-"

	i=0;		// Number of data columns
	while ((((int)ch_tr > 47) && ((int)ch_tr < 58) ) || ((int)ch_tr == 45))
	{	
		// Arranges the position of file pointer
		fseek(fp_tr, -1, 1);

		// Gets a number and sends it to b[]
		fscanf(fp_tr, "%s", &temp[0]);

		// Skip " " (blank spaces)
		ch_tr=fgetc(fp_tr);	
		ch_tr=fgetc(fp_tr);
		i++;	
	}

	j=0;		// Number of data rows
	while(ch_tr != EOF)
	{
		if((int)ch_tr == 10)
		{
			ch_tr=fgetc(fp_tr);
			j++;
		}
		else
		{
			ch_tr=fgetc(fp_tr);
		}
	}
	j = j/2;
	rewind(fp_tr);


	fseek(fp_tt, 66, 1);

	ch_tt=fgetc(fp_tt);

	jj=0;
	while(ch_tt != EOF)
	{
		if((int)ch_tt == 10)
		{
			ch_tt=fgetc(fp_tt);
			jj++;
		}
		else
		{
			ch_tt=fgetc(fp_tt);
		}
	}
	jj = jj/2;
	rewind(fp_tt);
	if(jj>j)
	{
		size = jj+1;
	}
	else
	{
		size = j+1;
	}
	
	// Memory allocation
	vector = malloc(size*sizeof(float *));
	if(!vector)
	{
		printf("\nError! pattern_unit_vector_normalization.c. Memory allocation error.");
		fclose(fp_tr);
		fclose(fp_tt);
		*err_code = 9;
		return(err_code);
	}
	for(n=0;n<size;n++)
	{
		vector[n] = malloc(i*sizeof(float));
		if(!vector[n])
		{
			printf("\nError! pattern_unit_vector_normalization.c. Memory allocation error.");
			fclose(fp_tr);
			fclose(fp_tt);
			*err_code = 9;
			return(err_code);
		}
	}

	r = malloc(size*sizeof(int));
	if(!r)
	{
		printf("\nError! pattern_unit_vector_normalization.c. Memory allocation error.");
		fclose(fp_tr);
		fclose(fp_tt);
		*err_code = 9;
		return(err_code);
	}

	c = malloc(size*sizeof(int));
	if(!c)
	{
		printf("\nError! pattern_unit_vector_normalization.c. Memory allocation error.");
		fclose(fp_tr);
		fclose(fp_tt);
		*err_code = 9;
		return(err_code);
	}

	b = malloc(i*sizeof(float));
	if(!b)
	{
		printf("\nError! pattern_unit_vector_normalization.c. Memory allocation error.");
		fclose(fp_tr);
		fclose(fp_tt);
		*err_code = 9;
		return(err_code);
	}

	img = malloc((size-1)*sizeof(char *));
	if(!img)
	{
		printf("\nError! pattern_unit_vector_normalization.c. Memory allocation error.");
		fclose(fp_tr);
		fclose(fp_tt);
		*err_code = 9;
		return(err_code);
	}
	for(n=0;n<size-1;n++)
	{
		img[n] = malloc(MAX_CASE*sizeof(char));
		if(!img[n])
		{
			printf("\nError! pattern_unit_vector_normalization.c. Memory allocation error.");
			fclose(fp_tr);
			fclose(fp_tt);
			*err_code = 9;
			return(err_code);
		}
	}

	class_name = malloc((size-1)*sizeof(char *));
	if(!class_name)
	{
		printf("\nError! pattern_unit_vector_normalization.c. Memory allocation error.");
		fclose(fp_tr);
		fclose(fp_tt);
		*err_code = 9;
		return(err_code);
	}
	for(n=0;n<size-1;n++)
	{
		class_name[n] = malloc(MAX_CASE*sizeof(char));
		if(!class_name[n])
		{
			printf("\nError! pattern_unit_vector_normalization.c. Memory allocation error.");
			fclose(fp_tr);
			fclose(fp_tt);
			*err_code = 9;
			return(err_code);
		}
	}


//********************training file******************************
	
	// Generates the normalized training file name
	strcpy(file_tr_temp,file_tr);
	p = strchr(file_tr_temp,'.');
	strcpy(p,"_norm.txt");

	if ((fp_tr_temp = fopen(file_tr_temp, "w+")) ==NULL)
	{
		printf("Error! pattern_unit_vector_normalization.c. Can't open , read or create file.");
		printf("%s\n",file_tr_temp);
		fclose(fp_tr);
		fclose(fp_tt);
		*err_code = 7;
		for(n=0;n<size;n++)
		{
			free(vector[n]);
		}
		free(vector);

		for(n=0;n<size-1;n++)		
		{
			free(img[n]);
		}
		free (img);

		for(n=0;n<size-1;n++)		
		{
			free(class_name[n]);
		}
		free(class_name);

		free(r);
		free(c);		
		free(b);
		return(err_code);
	}

	ch=fgetc(fp_tr);
	while (ch != '*')
	{
		fputc(ch, fp_tr_temp);
		ch=fgetc(fp_tr);
	}
	for (n=0;n<63;n++)
	{
		fputc(ch, fp_tr_temp);
		ch=fgetc(fp_tr);
	}

	fprintf(fp_tr_temp,"%s","\n\n");

	ch=fgetc(fp_tr);	
	
	for(m=0;m<j;m++)
	{
		// Gets image name
		fscanf(fp_tr, "%s", img[m]);
		
		// Gets row and column from training set
		fscanf(fp_tr, "%d",&r[m]);
		ch=fgetc(fp_tr);
		fscanf(fp_tr, "%d",&c[m]);
		ch=fgetc(fp_tr);
	
		for(g=0;g<i;g++)
		{	
			// Gets a number and send it to b[]
			fscanf(fp_tr, "%f", &vector[m][g]);

			// Skip " " (blank spaces)
			ch=fgetc(fp_tr);	
		}

		ch=fgetc(fp_tr);

		//Gets the class name from the training set

		if((int)ch == 10)
		{
			printf("Error! pattern_unit_vector_normalization.c. Every entry in training set should have a class name.");
			fclose(fp_tr);
			fclose(fp_tt);
			fclose(fp_tr_temp);
			*err_code = 10;
			for(n=0;n<size;n++)
			{
				free(vector[n]);
			}
			free(vector);

			for(n=0;n<size-1;n++)		
			{
				free(img[n]);
			}
			free (img);

			for(n=0;n<size-1;n++)		
			{
				free(class_name[n]);
			}
			free(class_name);

			free(r);
			free(c);		
			free(b);
			return(err_code);
		}
		else 
		{
			fseek(fp_tr, -1, 1);
			fscanf(fp_tr,"%s",class_name[m]);
		}	
		
		ch=fgetc(fp_tr);
	}
	fclose(fp_tr);	

	// Unit Vector Normalization procedure called 
	vector = unit_vector_normalization(vector,i,j,0,err_code);
	if(*err_code !=0)
	{
		fclose(fp_tt);
		fclose(fp_tr_temp);
		for(n=0;n<size;n++)
		{
			free(vector[n]);
		}
		free(vector);

		for(n=0;n<size-1;n++)		
		{
			free(img[n]);
		}
		free (img);

		for(n=0;n<size-1;n++)		
		{
			free(class_name[n]);
		}
		free(class_name);

		free(r);
		free(c);		
		free(b);
		return(err_code);
	}

	for (m=0;m<j;m++)
	{
		fprintf(fp_tr_temp,"%s %d %d ", img[m], r[m] ,c[m]);
		for(n=0;n<i;n++)
		{
			fprintf(fp_tr_temp,"%f ", vector[m][n]);
		}
		fprintf(fp_tr_temp,"%s\n\n", class_name[m]);

	}
	fclose(fp_tr_temp);	
//********************end of training file*************************************
	
	// The function returns the normalization information.
	// It will be used in test set normalization, therefore it is saved in b[]

	for(n=0;n<i;n++)
	{
		b[n] = vector[j][n];
	}

//********************test file************************************************

	// Generates the normalized test file name
	strcpy(file_tt_temp,file_tt);
	p = strchr(file_tt_temp,'.');
	strcpy(p,"_norm.txt");

	if ((fp_tt_temp = fopen(file_tt_temp, "w+")) ==NULL)
	{
		printf("Error! pattern_unit_vector_normalization.c. Can't open , read or create file.");
		printf("%s\n",file_tt_temp);
		fclose(fp_tt);
		*err_code = 7;
		for(n=0;n<size;n++)
		{
			free(vector[n]);
		}
		free(vector);

		for(n=0;n<size-1;n++)		
		{
			free(img[n]);
		}
		free (img);

		for(n=0;n<size-1;n++)		
		{
			free(class_name[n]);
		}
		free(class_name);

		free(r);
		free(c);		
		free(b);
		return(err_code);
	}

	ch=fgetc(fp_tt);
	while (ch != '*')
	{
		fputc(ch, fp_tt_temp);
		ch=fgetc(fp_tt);
	}
	for (n=0;n<63;n++)
	{
		fputc(ch, fp_tt_temp);
		ch=fgetc(fp_tt);
	}

	fprintf(fp_tt_temp,"%s","\n\n");

	ch=fgetc(fp_tt);	
	
	for(m=0;m<jj;m++)
	{
		// Gets image name
		fscanf(fp_tt, "%s", img[m]);
		
		// Gets row and column from test set
		fscanf(fp_tt, "%d",&r[m]);
		ch=fgetc(fp_tt);
		fscanf(fp_tt, "%d",&c[m]);
		ch=fgetc(fp_tt);

		for(g=0;g<i;g++)
		{	
			// Gets a number and send it to b[]
			fscanf(fp_tt, "%f", &vector[m][g]);

			// Skip " " (blank spaces)
			ch=fgetc(fp_tt);	
			
		}

		ch=fgetc(fp_tt);

		// Gets the class name from the test set

		if((int)ch == 10)
		{
			fseek(fp_tt, -1, 1);
			strcpy(class_name[m], "NoClassName");
		}
		else 
		{
			fseek(fp_tt, -1, 1);
			fscanf(fp_tt,"%s",class_name[m]);
		}	
		
		ch=fgetc(fp_tt);
	}
	fclose(fp_tt);
	
	for(n=0;n<i;n++)
	{
		vector[jj][n] = b[n];
	}

	// Range Normalization procedure called 
	vector = unit_vector_normalization(vector,i,jj+1,1,err_code);
	if(*err_code !=0)
	{
		fclose(fp_tt_temp);
		for(n=0;n<size;n++)
		{
			free(vector[n]);
		}
		free(vector);

		for(n=0;n<size-1;n++)		
		{
			free(img[n]);
		}
		free (img);

		for(n=0;n<size-1;n++)		
		{
			free(class_name[n]);
		}
		free(class_name);

		free(r);
		free(c);		
		free(b);
		return(err_code);
	}

	for (m=0;m<jj;m++)
	{
		fprintf(fp_tt_temp,"%s %d %d ", img[m], r[m] ,c[m]);
		for(n=0;n<i;n++)
		{
			fprintf(fp_tt_temp,"%f ", vector[m][n]);
		}
		fprintf(fp_tt_temp,"%s\n\n", class_name[m]);

	}

	fclose(fp_tt_temp);

	for(n=0;n<size;n++)
	{
		free(vector[n]);
	}
	free(vector);

	for(n=0;n<size-1;n++)		
	{
		free(img[n]);
	}
	free (img);

	for(n=0;n<size-1;n++)		
	{
		free(class_name[n]);
	}
	free(class_name);

	free(r);
	free(c);		
	free(b); 
	return(err_code);
}