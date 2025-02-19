/***************************************************************************
* =========================================================================
*
*			 CVIPtools - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: softmax_scaling.c 
*		  Expanded Name: Softmax normalization calculation
*			 Parameters: Pointers pointing to a matrix, size of the matrix,
*						 conatant parameter r,
*						 training/test set option, error code
*				 Return: The normalized matrix
*           Description: It contains the function to normalize each column in the 
*						 matrix. Option 0 is to normalize training set. Option 1 is 
*						 to normalize test set
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
#include "stdlib.h"

float **softmax_scaling(float **vector, int i, int j, float r_softmax, int option, int *err_code)
{
	int		r,c;
	float	mean_vector = 0.0;
	float	sigma = 0.0;
	float	snd = 0.0;
	
	switch(option)	
	{
	// Normalization for Training set
	case 0:

		for(c=0;c<i;c++)
		{		
			mean_vector = 0.0;
			sigma = 0.0;
			for(r=0;r<j;r++)
			{
				mean_vector = mean_vector + vector[r][c];	
			}

			mean_vector = mean_vector/j;		// Calculates the mean of the feature vector

			for( r =0;r<j;r++)					// Calculates the standard deviation (sigma) of the feature vector
			{
				sigma = sigma + ((vector[r][c] - mean_vector)*(vector[r][c] - mean_vector));				
			}
	
			sigma = (float)sqrt(sigma/(j));

			if ((sigma * r_softmax) == 0.0)
			{
				printf("\nWarning! softmax_scaling.c. Data range of the %dth column data is 0 in training set. Data was normalized to 0!",c+3);
				for(r=0;r<j;r++)
				{
					vector[r][c] = 0.0;
				}

				vector[j][c] = mean_vector;
				vector[j+1][c] = r_softmax*sigma;
			}
			else
			{
				for(r=0;r<j;r++)				// Normalizes the feature vector
				{
					vector[r][c] = (vector[r][c] - mean_vector) / (r_softmax*sigma);
					vector[r][c] = 1/(1+(float)exp(-vector[r][c]));
				}

				vector[j][c] = mean_vector;
				vector[j+1][c] = r_softmax*sigma;
			}
		}
		break;	

	// Normalization for Test set
	case 1:	

		for(c = 0 ; c < i; c++)  
		{	
			if(vector[j-1][c] == 0)
			{			
				printf("\nWarning! softmax_scaling.c. Data was normalized to 0 in test set, because data range for the %dth column is 0 in training set.",c+3);
				for(r=0;r<j-2;r++)
				{
					vector[r][c] = 0.0;
				}	
			}
			else
			{
				for(r=0;r<j-2;r++)				// Normalizes the feature vector
				{
					vector[r][c] = (vector[r][c] - vector[j-2][c])/ vector[j-1][c];
					vector[r][c] = 1/(1+(float)exp(-vector[r][c]));
				}
			}		
		}			
		break;
	default:
		printf("Error! softmax_scaling.c. Option selection error.");
		exit(0);
		break;
	}
	return vector;
}
