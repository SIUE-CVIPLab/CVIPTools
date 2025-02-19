/***************************************************************************
* =========================================================================
*
*			 CVIPtools - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: range_normalize.c 
*		  Expanded Name: Range normalization calculation
*			 Parameters: Pointers pointing to a matrix, size of the matrix,
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


float **range_normalize(float **vector, int i, int j, int option, int *err_code)
{
    int c,r,cnt =0 , flg =0 , flg1 = 0;
	float min; 
	float max;
	float vectorrange1 = 0.0;
	
	switch(option)
	{
	// Normalization for Training set
	case 0:

		for(c = 0 ; c < i; c++)  
		{
			min = (float)(pow(10,38)*3.4);
			max = (float)(pow(10,-38)*(-3.4));
			for (r = 0; r < j; r++)
			{
				if( vector[r][c] < min )
				{
					min = vector[r][c];	// Calculates the minimum value in the feature vector
				}
				if(vector[r][c] > max)
				{
					max = vector[r][c]; // Calculates the maximum value in the feature vector
				}
			}	
			
			vectorrange1 = max - min;	// Calculates the range for the feature vector
		
			if (vectorrange1 == 0.0)
			{
				printf("\nWarning! range_normalize.c. Data range of the %dth column data is 0 in training set. Data was normalized to 0!",c+3);
				for(r=0;r<j;r++)
				{
					vector[r][c] = 0.0;
				}
				vector[j][c] = vectorrange1;
				vector[j+1][c]=min;
			}
			else
			{
				for(r=0;r<j;r++)
				{
					vector[r][c] = vector[r][c] / vectorrange1; // Normalizes the feature vector
				}
				vector[j][c] = vectorrange1;
				vector[j+1][c]=min;
			}
			
			    
		     
		}

		break;

	// Normalization for Test set
	case 1:
        flg1 = 0;
		for(c = 0 ; c < i; c++)  
		{	
			min = vector[j-1][c];
			max = vector[j-2][c]+ min ;
			flg = 0;
		
			if(vector[j-2][c] == 0.0)
			{
				printf("\nWarning! range_normalize.c. Data was normalized to 0 in test set, because data range for the %dth column is 0 in training set.",c+3);
				for(r=0;r<j-1;r++)
				{
					vector[r][c] = 0.0;
				}
			}
			else
			{
				for(r=0;r<j-2;r++)
				{
					

					if (vector[r][c] > max || vector[r][c] < min)		// Clips the out of range values
					{
						if( vector[r][c] > max)
							vector[r][c] = max;		
						else
							vector[r][c] = min;		
						cnt++;											// Counts the total number of out of range feature values in Range-Normalized Test Set
						flg++;
					}
						vector[r][c] = vector[r][c] / vector[j-2][c];	// Normalizes the feature vector
				}
				if(flg != 0)
					flg1++;												// Counts the number of features having out of range values
			}			
		}
		
		printf("\nTotal number of out of range feature values in Range-Normalized Test Set: %d  and number of features having out of range values : %d ", cnt, flg1);
		printf("\nNote that 'Projection' feature may consists of more than one feature value\n");
		break;
	default:
		printf("Error! range_noralize.c. Option selection error.");
		exit(0);
		break;
	}	
	return vector;
}