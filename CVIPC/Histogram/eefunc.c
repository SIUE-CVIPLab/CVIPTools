#ifndef __EEFUNC_C
#define __EEFUNC_C

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "eefunc.h"
#include "ee.h"


/*************************************************************************
**                                                                       **
** Some custom math functions...   Note that they must be prototyped     **
** above (if your compiler requires it)                                  **
**                                                                       **
** deg( x )             Converts x radians to degrees.                   **
** rad( x )             Converts x degrees to radians.                   **
**                                                                       **
 *************************************************************************/

double deg( double x )
	{
	return( x * 180.0 / M_PI );
	}
double rad( double x )
	{
	return( x * M_PI / 180.0 );
	}
double p2f(double P,double i,int n)
	{
	return(P*pow(1+i,n));
	}
double f2p(double F,double i,int n)
	{
	return(F/pow(1+i,n));
	}
double f2a(double F,double i,int n)
	{
	return(F*i/(pow(1+i,n)-1));
	}
double p2a(double P,double i,int n)
	{
	return(P*i*pow(1+i,n)/(pow(1+i,n)-1));
	}
double a2f(double A,double i,int n)
	{
	return(A*(pow(1+i,n)-1)/i);
	}
double a2p(double A,double i,int n)
	{
	return(A*(pow(1+i,n)-1)/(i*pow(1+i,n)));
	}
double impulse(double x)
	{
	if(x==0)
		return 1;
	else
		return 0;
	}
double step(double x)
	{
	if(x>=0)
		return 1;
	else
		return 0;
	}
double ramp(double x)
	{
	if(x>=0)
		return x;
	else
		return 0;
	}
double randf(double low,double high)
	{
	register double diff;
	register double rnum;
	diff=high-low;
	rnum=rand()/((double)32767);
	if (diff<0)
		{
		fprintf(stderr,"randf: Invalid function parameters\n");
		exit(1);
		}
	return(rnum*diff+low);
	}
double randi(double low,double high)
	{
	if(low>=high)
		{
		fprintf(stderr,"randi: Invalid function parameters\n");
		exit(1);
		}
	return (int)(randf(low,high)+0.5);
	}
double gauss(double x,double variance,double mean)
	{
	return(exp(-pow(x-mean,2)/(2*pow(variance,2)))/(variance*sqrt(2*M_PI)));
	}
		
#endif
