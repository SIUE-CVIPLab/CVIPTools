/***************************************************************************
* =========================================================================
*
*			 CVIPtools - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: maximum_value_metric.c 
*		  Expanded Name: Maximum value metric distance measure calculation
*			 Parameters: Pointers pointing to the two vectors, size of the vectors
*				 Return: The distance value
*           Description: It contains the function to calculate the maximum
*						 value metric, a distance measure
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

float maximum_value_metric(float *vector1, float *vector2, int n)
{
	float maximum_value_metric = 0.0, temp = 0.0;
	int i;
	
	for (i=0; i<n;i++)
	{	
		temp = (float)fabs(vector1[i]-vector2[i]);
		if ( temp > maximum_value_metric)
		{
			maximum_value_metric = temp;
		}
	}
	return maximum_value_metric;
}