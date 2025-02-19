/***************************************************************************
* =========================================================================
*
*			 CVIPtools - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: vector_inner_product.c 
*		  Expanded Name: Vector inner product similarity measure calculation
*			 Parameters: Pointers pointing to the two vectors, size of the vectors
*				 Return: The similarity value
*           Description: It contains the function to calculate the vector
*						 inner product, a similarity measure
*   Initial Coding Date: May 26, 2005
*Last Modification Made: July 8, 2005
*           Portability: Standard (ANSI) C
*             Credit(s): Husain Kagalwalla, Geer Shuang, Amit Kharbanda , Hari Siva Kumar Reddy Bhogala
*                        Southern Illinois University at Edwardsville
*
*		  Copyright (c): 1995-2005 SIUE - Scott Umbaugh
****************************************************************************/

/*
** include header files
*/

#include "math.h"

float vector_inner_product(float *vector1, float *vector2, int n)
{
	float vector_inner = 0.0;
	int i;
	double magnitude1= 0.0,magnitude2= 0.0;

	for (i=0; i<n;i++)
	{
		vector_inner = vector_inner + vector1[i]*vector2[i];
		magnitude1 = magnitude1 + vector1[i]*vector1[i];
		magnitude2 = magnitude2 + vector2[i]*vector2[i];
	}
	magnitude1 = sqrt(magnitude1);
	magnitude2 = sqrt(magnitude2);

	return (vector_inner)/(magnitude1*magnitude2);
}