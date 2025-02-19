#ifndef __EEFUNC_H
#define __EEFUNC_H

/*************************************************************************
**                                                                       **
** PROTOTYPES FOR EXTERNAL MATH FUNCTIONS                                **
**                                                                       **
 *************************************************************************/

/*************************************************************************
**                                                                       **
** PROTOTYPES FOR CUSTOM MATH FUNCTIONS                                  **
**                                                                       **
 *************************************************************************/

double deg(double radians);		/* Converts radians to degrees */
double rad(double degrees);		/* Converts degrees to radians */
double p2f(double P,double i,int n);	/* Single Payment Compound Amount 
					   returns future worth
					   P - present value
					   i - interest rate
					   n - compounding periods */
double f2p(double F,double i,int n);	/* Single Payment Present Worth
					   Returns Present Worth
					   F - future worth
					   i - interest rate
					   n - compounding periods */
double f2a(double F,double i,int n);	/* Uniform Series Sinking Fund
					   Returns Annual Amount
					   F - future worth
					   i - interest rate
					   n - compounding periods */
double p2a(double P,double i,int n);	/* Capital Recovery
					   Returns Annual Amount
					   P - present worth
					   i - interest rate
					   n - compounding periods */
double a2f(double A,double i,int n);	/* Uniform Series Compound Amount
					   Returns Future Worth
					   A - annual amount
					   i - interest rate
					   n - compounding periods */
double a2p(double A,double i,int n);	/* Uniform Series Present Worth
					   Returns Present Worth
					   A - annual amount
					   i - interest rate
					   n - compounding periods */
double impulse(double x);		/* Impulse Function
					   Returns 1 if x = 0, else
					   returns 0 */
double step(double x);			/* Step Function
					   Returns 1 if x >= 0, else
					   returns 0 */
double ramp(double x);			/* Ramp Function
					   Returns x if x >= 0, else
					   returns 0 */
double randf(double low,double high);	/* Random float
					   Returns random floating
					   point number between 'low'
					   and 'high' */
double randi(double low,double high);	/* Random integer
					   Returns random integer
					   between 'low' and 'high'.
					   Calles randf and rounds its
					   return value to the nearest
					   integer */
double gauss(double x,double variance,double mean);
					/* Gaussian Distribution */
					   				   

#endif
