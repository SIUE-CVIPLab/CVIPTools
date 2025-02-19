/***************************************************************************
* =========================================================================
*
*			 CVIPtools - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: minkowski_distance.c 
*		  Expanded Name: Minkowski metric distance measure calculation
*			 Parameters: Pointers pointing to the two vectors, positive integer constant,
*						 size of the vectors, error code
*				 Return: The distance value
*           Description: It contains the function to calculate the minkowski 
*						 distance, a distance measure
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

#include "math.h"
#include "stdio.h"

float minkowski_distance(float *vector1, float *vector2, int r, int n, int *err_code)
{
	float minkowski = 0.0;
	int i;
	if (r <= 0 )
	{
		printf("\nError! minkowski.c. r in minkowski should be a positive integer.");
		*err_code = 12;
		return minkowski;
	}

	for (i=0; i<n;i++)
	{
		minkowski = minkowski + (float)pow(((float)fabs(vector1[i]-vector2[i])), r);
	} 

	minkowski =(float)pow(minkowski, (1/(float)r));
	return minkowski;
}