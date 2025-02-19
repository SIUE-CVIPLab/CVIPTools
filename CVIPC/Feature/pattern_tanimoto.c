/***************************************************************************
* =========================================================================
*
*			 CVIPtools - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: pattern_tanimoto.c 
*		  Expanded Name: Pattern classification tanimoto metric similarity
*			 Parameters: Pointers pointing to the file names of training and 
*						 test set, error code
*				 Return: Number of entries in training set
*           Description: It contains the function to read the feature data from
*						 training and test set file, and calls lower level function
*						 to calculate the distance between every each entry in the 
*						 training and test set. Make a temp file to store the 
*						 information 
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

#include "stdio.h"
#include "math.h"
#include "float.h"
#include "stdlib.h"
#include "string.h"

#define MAX_CASE 128

extern float tanimoto_metric(float *vector1, float *vector2, int n, int *err_code);

int pattern_tanimoto(char *file_tt, char *file_tr, int *err_code)
{
	float	*a,*b;
	float	tanimoto = 0.0;
	int		r, c, temp; // r is row
	int		i,j,jj,m,n;
	int		g=0;
	char	ch_tr, ch_tt;
	char	img_tr[MAX_CASE], img_tt[MAX_CASE];
	char	class_tr[MAX_CASE], class_tt[MAX_CASE];

	FILE	* fp_tr;
	FILE	* fp_tt;
	FILE	* fp_temp;

	char	*libvar;
	char	tempfile[MAX_CASE] = "CVIPtemp.txt";
	char	*file_temp = &tempfile[0];

	// Gets the path of "TEMP" from LIB environment variable

	libvar = getenv( "TEMP" );
	strcpy(file_temp,libvar);
	strcat(file_temp,"\\CVIPtemp.txt");


	if ((fp_tr = fopen(file_tr, "r")) ==NULL)
	{
		printf("Error! pattern_tanimoto.c. Can't open , read or create file.");
		printf("%s\n",file_tr);
		*err_code = 7;
		return(1);
	}
	if ((fp_tt = fopen(file_tt, "r")) ==NULL)
	{
		printf("Error! pattern_tanimoto.c. Can't open , read or create file.");
		printf("%s\n",file_tt);
		fclose(fp_tr);
		*err_code = 7;
		return(1);
	}
	if ((fp_temp = fopen(file_temp, "w+")) ==NULL)
	{
		printf("Error! pattern_tanimoto.c. Can't open , read or create file.");
		printf("%s\n",file_temp);
		fclose(fp_tr);
		fclose(fp_tt);
		*err_code = 7;
		return(1);
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
		printf("Error! pattern_tanimoto.c. There is more than one header in the training set.");
		printf("%s\n",file_tr);
		fclose(fp_tr);
		fclose(fp_tt);
		fclose(fp_temp);
		*err_code = 13;
		return(1);
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
		printf("Error! pattern_tanimoto.c. There is more than one header in the test set.");
		printf("%s\n",file_tt);
		fclose(fp_tr);
		fclose(fp_tt);
		fclose(fp_temp);
		*err_code = 13;
		return(1);
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
			printf("Error! pattern_tanimoto.c. The header in the training and test files don't match.");
			fclose(fp_temp);
			fclose(fp_tr);
			fclose(fp_tt);
			*err_code = 1;
			return(1);
		}		
	}
	
	// Jumps to the data line
	fseek(fp_tr, 65, 1);
	fseek(fp_tt, 65, 1);

	// Gets the image name
	fscanf(fp_tt, "%s", &img_tt);

	// Gets row and column values from the test set
	fscanf(fp_tt, "%d",&r);
	ch_tt=fgetc(fp_tt);
	fscanf(fp_tt, "%d",&c);
	ch_tt=fgetc(fp_tt);
	ch_tt = fgetc(fp_tt);

	// Counts the number of features in a data line
	// If the character is between 0~9 or is "-", it is required
	// otherwise it is the end of that data line
	// therefore the class name can not be started with 0~9 or "-"

	i=0;			// Number of data columns
	while ((((int)ch_tt > 47) && ((int)ch_tt < 58) ) || ((int)ch_tt == 45))
	{	
		// Arranges the position of file pointer
		fseek(fp_tt, -1, 1);

		// Gets a number
		fscanf(fp_tt, "%f", &tanimoto);
		
		// Skip " " (blank spaces)
		ch_tt=fgetc(fp_tt);	
		ch_tt=fgetc(fp_tt);
		i++;	
	}

	j=0;			// Number of data rows in training set
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

	jj=0;			// Number of data rows in the test set
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

	// Memory allocation
	a = malloc(i*sizeof(float));
	if(!a)
	{
		printf("\nError! pattern_tanimoto.c. Memory allocation error.");
		fclose(fp_temp);
		fclose(fp_tr);
		fclose(fp_tt);
		*err_code = 9;
		return(1);
	}

	b = malloc(i*sizeof(float));
	if(!b)
	{
		printf("\nError! pattern_tanimoto.c. Memory allocation error.");
		fclose(fp_temp);
		fclose(fp_tr);
		fclose(fp_tt);
		*err_code = 9;
		return(1);
	}

	// Rearranges the position of file pointer
	while (fgetc(fp_tt) != '*')
	{
		fgetc(fp_tt);
	}
	while (fgetc(fp_tr) != '*')
	{
		fgetc(fp_tr);
	}
	fseek(fp_tt, 65, 1);
	fseek(fp_tr, 65, 1);

	// Reads data from training and test files and calculates the distance or similarity measure

	for(m=0;m<jj;m++)
	{
		// Reads one data line from test file
		// Gets the image name
		fscanf(fp_tt, "%s", &img_tt);

		// Gets row and column values from the test set
		fscanf(fp_tt, "%d",&r);
		ch_tt=fgetc(fp_tt);
		fscanf(fp_tt, "%d",&c);
		ch_tt=fgetc(fp_tt);

		// Gets the vectors
		for(g=0;g<i;g++)
		{	
			// Gets a number and sends it to b[]
			fscanf(fp_tt, "%f", &b[g]);
			
			// Skip " " (blank spaces)
			ch_tt=fgetc(fp_tt);	
			
		}
		ch_tt=fgetc(fp_tt);	
		
		// Gets the class name from the test set
		if((int)ch_tt == 10)
		{
			fseek(fp_tt, -1, 1);
			strcpy(class_tt, "NoClassName");
		}
		else 
		{
			fseek(fp_tt, -1, 1);
			fscanf(fp_tt,"%s",class_tt);
		}	

		// Reads the data in the training file and calculates the distance/similarity measure for each entry in the test file
		for(n=0;n<j;n++)
		{
			
			// Gets image name
			fscanf(fp_tr, "%s", &img_tr);							
			
			// Skips row and column in training set
			fscanf(fp_tr, "%d",&temp);
			ch_tr=fgetc(fp_tr);
			fscanf(fp_tr, "%d",&temp);
			ch_tr=fgetc(fp_tr);
			
			for(g=0;g<i;g++)
			{
				// Gets a number and send it to a[]
				fscanf(fp_tr, "%f", &a[g]);
				// Skip " " (blank spaces)
				ch_tr=fgetc(fp_tr);
			}	
			ch_tr=fgetc(fp_tr);	
			
			// Gets the class name from the training set
			if((int)ch_tr == 10)
			{
				printf("Error! pattern_tanimoto.c. Every entry in training set should have a class name.");
				fclose(fp_temp);
				fclose(fp_tr);
				fclose(fp_tt);
				*err_code = 10;
				free(a);
				free(b);
				return(1);
			}
			else 
			{
				fseek(fp_tr, -1, 1);
				fscanf(fp_tr,"%s",class_tr);
			}	
			
			// Calls the tanimoto metric distance measure function
			tanimoto = tanimoto_metric(a, b, i, err_code);
			if(*err_code !=0)
			{
				fclose(fp_temp);
				fclose(fp_tr);
				fclose(fp_tt);
				*err_code = 10;
				free(a);
				free(b);
				return(1);
			}
		
			// Writes name of image in testing set to temp.txt file
			fprintf(fp_temp,"%s ",&img_tt);
			fprintf(fp_temp,"%s ",&img_tr);

			// Writes the row and column coodinates
			fprintf(fp_temp,"%d %d %f ", r, c, tanimoto);

			// Writes the classes
			fprintf(fp_temp,"%s ",&class_tt);
			fprintf(fp_temp,"%s\n",&class_tr);

			ch_tr=fgetc(fp_tr);	
		}
		
		ch_tt=fgetc(fp_tt);	

		// Sets fp_tr to the beginning of the data in training set
		rewind(fp_tr);
		while (fgetc(fp_tr) != '*')
		{
			fgetc(fp_tr);
		}

		fseek(fp_tr, 65, 1);
	}
	
	fclose(fp_tr);
	fclose(fp_tt);
	fclose(fp_temp);
	free(a);
	free(b);
	return j;
}