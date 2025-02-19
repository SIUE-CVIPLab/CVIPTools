/***************************************************************************
* =========================================================================
*
*			 CVIPtools - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: tanimoto_metric.c 
*		  Expanded Name: Tanimoto metric distance measure calculation
*			 Parameters: Pointers pointing to the two vectors, size of the vectors
*				 Return: The similarity value
*           Description: It contains the function to calculate the tanimoto
*						 metric, a similarity measure 
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

float tanimoto_metric(float *vector1, float *vector2, int n, int *err_code)
{
	float tanimoto = 0.0;
	float ab = 0.0, a = 0.0, b = 0.0;
	int i;

	for (i=0; i<n;i++)
	{
		ab = ab + vector1[i]*vector2[i];
		a = a + vector1[i]*vector1[i];
		b = b + vector2[i]*vector2[i];
	}
	if ((a+b-ab) == 0.0)
	{
		printf("\nError! tanimoto_metric.c. Divisor can't be 0.");
		*err_code = 5;
		return tanimoto;
	}
	else
	{
		tanimoto = (float)fabs(ab/(a+b-ab));
		return tanimoto;
	}	
}