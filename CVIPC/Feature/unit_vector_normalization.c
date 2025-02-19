/***************************************************************************
* =========================================================================
*
*			 CVIPtools - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: unit_vector_normalization.c 
*		  Expanded Name: Unit vector normalization calculation
*			 Parameters: Pointers pointing to a matrix, size of the matrix,
*						 training/test set option, error code
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

float **unit_vector_normalization(float **vector, int i, int j, int option, int *err_code)
{   
	float	euclidean = 0.0;
	int		c,r,cnt=0, flg =0 , flg1 = 0;


	switch(option)
	{
	// Normalization for Training set
	case 0:
		for(c = 0 ; c < i; c++)  
		{
			euclidean = 0.0;
			for (r = 0; r < j; r++)
			{
				euclidean = euclidean + vector[r][c] * vector[r][c];
			}				
			euclidean = (float)sqrt(euclidean); // Calculates the euclidean distance of the feature vector

			if (euclidean == 0.0)
			{
				printf("\nWarning! unit_vector_normalization.c. Data range of the %dth column data is 0 in training set. Data was normalized to 0!",c+3);
				for(r=0;r<j;r++)
				{
					vector[r][c] = 0.0;
				}
				vector[j][c] = euclidean;		
			}
			else
			{
				for(r=0;r<j;r++)
				{
					vector[r][c] = vector[r][c] / euclidean;	// Normalizes the feature vector
				}
				vector[j][c] = euclidean;
			}
		}	
		break;
	
	// Normalization for Test set
	case 1:
		flg1=0;
		for(c = 0 ; c < i; c++)  
		{	
			flg=0;
			if(vector[j-1][c] == 0)
			{
				printf("\nWarning! unit_vector_normalization.c. Data was normalized to 0 in test set, because data range for the %dth column is 0 in training set.",c+3);
				for(r=0;r<j-1;r++)
				{
					vector[r][c] = 0.0;
				}
			}
			else
			{
				for(r=0;r<j-1;r++)
				{
					vector[r][c] = vector[r][c] / vector[j-1][c];	// Normalizes the feature vector
					if (vector[r][c] > 1 || vector[r][c] < -1)		// Clips the out of range values
					{
						if( vector[r][c] > 1)
							vector[r][c] = 1;
						else
							vector[r][c] = -1;
						cnt++;										// Counts the total number of out of range feature values in Unit-Vector Normalized Test Set
						flg = 1;
					}
				}

			}

			if(flg == 1)
				{
					flg1++;											// Counts the number of features having out of range values
					flg = 0;
				}			
		}
	
		printf("\nTotal number of out of range feature values in Unit-Vector Normalized Test Set: %d  and number of features having out of range values : %d ", cnt, flg1);
		printf("\nNote that 'Projection' feature may consists of more than one feature value\n");
		break;

	default:
		printf("Error! unit_vector_normalization.c. Option selection error.");
		exit(0);
		break;
	}	
	return vector;
}




