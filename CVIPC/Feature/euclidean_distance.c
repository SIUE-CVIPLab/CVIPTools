/***************************************************************************
* =========================================================================
*
*			 CVIPtools - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: euclidean_distance.c 
*		  Expanded Name: Euclidean distance measure calculation
*			 Parameters: Pointers pointing to the two vectors, size of the vectors
*				 Return: The distance value
*           Description: It contains the function to calculate the euclidean distance,
*						 a distance measure	
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

float euclidean_distance(float *vector1, float *vector2, int n)
{
	float euclidean=0.0;  
	int	i;

	for (i=0; i<n;i++)
	{
		euclidean = euclidean + (vector1[i] - vector2[i]) * (vector1[i] - vector2[i]);
	}
	euclidean = (float)sqrt(euclidean);
	return (euclidean);
}