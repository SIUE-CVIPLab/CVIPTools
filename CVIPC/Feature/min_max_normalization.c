/***************************************************************************
* =========================================================================
*
*			 CVIPtools - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: min_max_normalization.c 
*		  Expanded Name: Min max normalization calculation
*			 Parameters: Pointers pointing to a matrix, size of the matrix
*						 spesified min and max value, training/test set option,
*						 error code
*				 Return: The normalized matrix
*           Description: It contains the function to normalize each column in the 
*						 matrix. Option 0 is to normalize training set. Option 1 is 
*						 to normalize test set
*   Initial Coding Date: May 26, 2005
*Last Modification Made: December 1, 2005
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
#include "stdlib.h"

float **min_max_normalization(float **vector, int i, int j, float s_min, float s_max, int option, int *err_code)
{
	int		c,r,cnt = 0 ,flg1 = 0 , flg =0;
	float	min; 
	float	max;

		

	switch(option)	
	{
	// Normalization for Training set
	case 0:
		for(c=0;c<i;c++)
		{	
			min = (float)(pow(10,38)*3.4);
			max = (float)(pow(10,-38)*(-3.4));
			for (r = 0; r < j; r++)
			{
				if( vector[r][c] < min )
				{
					min = vector[r][c];		// Calculates the minimum value in the feature vector
				}
				if(vector[r][c] > max)
				{
					max = vector[r][c];		// Calculates the maximum value in the feature vector
				}
			}	

			if (s_max <= s_min)
			{
				printf("\nError! min_max_normalization.c. s_min can't be greater than or equals to s_max.");
				*err_code = 3;
				return vector;
			}
			else if (((max - min) * (s_max-s_min)) == 0.0)
			{
				printf("\nWarning! min_max_normalization.c. Data range of the %dth column data is 0 in training set. Data was normalized to 0!",c+3);
				for(r=0;r<j;r++)
				{
					vector[r][c] = 0.0; 
				}

				vector[j][c] = min;
				vector[j+1][c] = max;
			}
			else
			{
				for(r=0;r<j;r++)
				{
					vector[r][c] = (((vector[r][c] - min)/(max - min)) * (s_max-s_min)) + s_min;	// Normalizes the feature vector
				}

				vector[j][c] = min;
				vector[j+1][c] = max;
			}
		}
		break;	

	// Normalization for Test set
	case 1:	
		flg1=0;
		for(c = 0 ; c < i; c++)  
		{	
			flg=0;
			if(vector[j-2][c]==vector[j-1][c])
			{
				printf("\nWarning! min_max_normalization.c. Data was normalized to 0 in test set, because data range for the %dth column is 0 in training set.",c+3);
				for(r=0;r<j-2;r++)
				{
					vector[r][c] = 0.0; 
				}
			}
			else
			{
				for(r=0;r<j-2;r++)
				{
					// Normalizes the feature vector
					vector[r][c] = (((vector[r][c] - vector[j-2][c])/(vector[j-1][c] - vector[j-2][c]))*(s_max-s_min)) + s_min;		
					if (vector[r][c] > s_max || vector[r][c] < s_min)		// Clips the out of range values
					{
						if( vector[r][c] > s_max)
							vector[r][c] = s_max;
						else
							vector[r][c] = s_min;
						cnt++;												// Counts the total number of out of range feature values in Normalized Min-Max Test Set
						flg = 1;
					}
				}
				

			}
			
			if(flg == 1)
				{
					flg1 ++;												// Counts the number of features having out of range values
					flg = 0;
				}

		}			
		
		printf("\nTotal number of out of range feature values in Normalized Min-Max Test Set: %d  and number of features having out of range values : %d ", cnt, flg1);
		printf("\nNote that 'Projection' feature may consists of more than one feature value\n");
		break;
		
	default:
		printf("Error! min_max_normalization.c. Option selection error.");
		exit(0);
		break;
	}
	return vector;
}
	




