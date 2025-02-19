/***************************************************************************
* =========================================================================
*
*			 CVIPtools - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: city_block.c 
*		  Expanded Name: City block metric distance measure calculation
*			 Parameters: Pointers pointing to the two vectors, size of the vectors
*				 Return: The distance value
*           Description: It contains the function to calculate the city block 
*						 or absolute value metric, a distance measure 
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

float city_block(float *vector1, float *vector2, int n)
{
	float city_block = 0.0;
	int i;

	for (i=0; i<n;i++)
	{
		city_block = city_block + (float)fabs(vector1[i]-vector2[i]);
	}
	return city_block;
}