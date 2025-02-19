/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: Spline.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Mon Jul 12 18:57:57 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Gregory Hance
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1993 SIUE - by Gregory Hance.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
* RCS (Revision Control System) Information
* ...Added automatically by RCS 
*
** $Log: Spline.c,v $
** Revision 1.2  1997/05/21 14:18:09  yawei
** added binary fopen() for WIN32
**
** Revision 1.1  1994/10/30 17:58:23  hanceg
** CVIPtools1.0 source file - G. Hance
**
*
****************************************************************************/
#include "CVIPtoolkit.h"
#include "DermVis.h"
#include <errno.h>

#define WHITE 255U

#ifndef MOD
#define MOD(A, B) ((A)/(B) - (int )(A)/(B)) * (B)
#endif

#ifndef SPLINE_ORDER
#define SPLINE_ORDER 3
#endif

#define DELTA_X  1
#define NO_DELTA 0
#define DELTA_Y  2
#define MAX_NUMBER_OF_POINTS 512U


/* global variables make programming really easy */
unsigned long
   litpixelper = 0,
   litpixelarea;
double
   localperimeter = 0.0,
   areacor = 0.0,
   newareacor = 0.0;
unsigned int
   minx = 512, miny = 512,
   maxx = 0 , maxy = 0;

/* private functions */
static double blend( int i, int k, double u );
static int splinepoint( unsigned *x, unsigned *y, double u, int numpnts, double *newx, double *newy );



void drawPnts_Border(
	Border imageP,
	unsigned number_of_points,
	unsigned *xP,
	unsigned *yP)
{
   register int i;

   for(i=0; i < number_of_points; i++)
      setPixel_Image(imageP,byte,xP[i],yP[i],0,1);

}
      


void readPntFile_Border(
	const char *pnt_file, 
	unsigned *no_of_points,
	unsigned **xP,
	unsigned **yP
)
{
   FILE *infP;
   int check_fp;
  
   errno = 0;

	#ifndef WIN32
   if ( (infP = fopen(pnt_file, "r")) == NULL ) {
	#else
   if ( (infP = fopen(pnt_file, "rb")) == NULL ) {
	#endif
      fprintf(stderr, "Open of %s for input failed: %s\n", pnt_file, strerror(errno));
      return;
   }

   *xP = (unsigned *) malloc(sizeof(unsigned)*MAX_NUMBER_OF_POINTS);
   *yP = (unsigned *) malloc(sizeof(unsigned)*MAX_NUMBER_OF_POINTS);

   if( *xP == NULL || *yP == NULL ) {
      fprintf(stderr, "could not allocate memory for control arrays.\n");
      return;
   }

   *no_of_points = 0;

   do {

      check_fp = fscanf(infP, "%u %u",*xP+*no_of_points, *yP+*no_of_points);
      (*no_of_points)++;

   } while( check_fp != EOF );

  (*no_of_points)--;

   fclose(infP);
}

   

void drawSpline_Border(
	Border imageP,
        unsigned number_of_points,
	unsigned *xP,
	unsigned *yP
)
{
   byte **dP;
   unsigned char
      pixelchange = NO_DELTA,
      direction;
   int
      bounce,
      intx, inty,
      lastintx, lastinty;
   double
      blah,
      steps = 30.0,
      increment,
      x, y,
      avex, avey,
      lastx, lasty,
      max2x, max2y, min2x, min2y,
      diffx, diffy, maxdiff,
      u;
      
   dP = (byte **) getData_Matrix(getBand_Image(imageP,0));

   increment = 1/steps;

   /* find an estimate of the center of the tumor */
   avex = avey = 0.0;
   for(intx = 0;intx < number_of_points;intx++)
   {
      avex += (double) xP[intx];
      avey += (double) yP[intx];
   }
   avex = avex/(double)number_of_points;
   avey = avey/(double)number_of_points;

   /* find the first point in the spline */
   u = 0.0;
   splinepoint( xP, yP , u , number_of_points , &x , &y );
   lastx = x;
   lasty = y;
   intx = lastintx = (int)x;
   inty = lastinty = (int)y;
   dP[inty][intx] = WHITE;

   while(u <= number_of_points)
   {
      
      /* find the next point in the spline */
      u += increment;
      splinepoint( xP , yP , u , number_of_points , &x , &y );

      /* find some information about that point */
      diffx = x - lastx;
      diffy = y - lasty;
      if( diffx < 0.0)
	 diffx = 0.0 - diffx;
      if( diffy < 0.0)
	 diffy = 0.0 - diffy;
      maxdiff = diffx;
      if(diffy > diffx)
	 maxdiff = diffy;

      /*
      ** THIS SECTION OF CODE CHANGED 22.FEB.93
      ** change the number of steps between points if there is a need
      */
      if( ( (maxdiff<.80)&&(bounce<8) ) || (maxdiff > 1.0) )
      {
	 bounce++;
	 u = u - increment;
	 steps = (maxdiff/.9) * steps;
	 increment = 1/steps;
      }
      /* use this point for the spline */
      else
      {
	 /* find the integer value of this x,y pair */
	 intx = (int)x;
	 inty = (int)y;

	 /* find the direction to the middle from this x,y pair */
	 direction = 0;
	 if(x > avex)           /* to the right of middle */
	    direction |= 0x1;
	 if(y > avey)           /* below middle */
	    direction |= 0x2;

	 /* calculate the perimeter */
	 localperimeter += sqrt( (diffx)*(diffx)+(diffy)*(diffy) );

	/* calculate the old area correction */
	blah = (diffy)*(diffx)/2;
	newareacor -= blah;
	areacor += blah;
	if(diffx>diffy)
	   areacor += diffx * fabs( (double)inty - y);
	else
	   areacor += diffy * fabs( (double)intx - x);

	/* find the maximum and minimum x and y for the last 2 x,y pairs */
	if(lastx > x )
	{
	   max2x = lastx;
	   min2x = x;
	}
	else
	{
	   max2x = x;
	   min2x = lastx;
	}

	if(lasty > y )
	{
	   max2y = lasty;
	   min2y = y;
	}
	else
	{
	   max2y = y;
	   min2y = lasty;
	}
	 /* find the max and min points in the spline for future use */
	 if( (intx != lastintx) || (inty != lastinty) )
	 {
	    areacor -= 1;
	    litpixelper++;
	    if(intx < minx) minx = intx;
	    if(inty < miny) miny = inty;
	    if(intx > maxx) maxx = intx;
	    if(inty > maxy) maxy = inty;
	    if( intx != lastintx )
	    {
	       if(pixelchange == DELTA_Y)
	       {
		  switch(direction)
		  {
		     case 0: /* middle is down and right */
			areacor -= ( lastx - (double)(lastintx) )*
				   ( lasty - (double)(lastinty) );
			break;
		     case 1: /* middle is down and left */
			areacor -= ( (double)(lastintx +1) - lastx)*
				   ( lasty - (double)(lastinty) );
			break;
		     case 2: /* middle is up and right */
			areacor -= ( lastx - (double)(lastintx) )*
				   ( (double)(lastinty +1) - lasty);
			break;
		     case 3: /* middle is up and left */
			areacor -= ( (double)(lastintx +1) - lastx)*
				   ( (double)(lastinty +1) - lasty);
		  }
	       }
	       pixelchange = DELTA_X;
	       if ( direction & 0x2 )
		  newareacor -= diffx * ( (double)(inty+1) - max2y );
	       else
		  newareacor -= diffx * ( min2y - (double)(inty) );
	    }
	    else
	    {
	       if(pixelchange == DELTA_X)
	       {
		  switch(direction)
		  {
		     case 0: /* middle is down and right */
			areacor -= ( lastx - (double)(lastintx) )*
				   ( lasty - (double)(lastinty) );
			break;
		     case 1: /* middle is down and left */
			areacor -= ( (double)(lastintx +1) - lastx)*
				   ( lasty - (double)(lastinty) );
			break;
		     case 2: /* middle is up and right */
			areacor -= ( lastx - (double)(lastintx) )*
				   ( (double)(lastinty +1) - lasty);
			break;
		     case 3: /* middle is up and left */
			areacor -= ( (double)(lastintx +1) - lastx)*
				   ( (double)(lastinty +1) - lasty);
		  }
	       }
	       pixelchange = DELTA_Y;
	       if( direction & 0x1 )
		  newareacor -= diffy * ( (double)(intx + 1) - max2x );
	       else
		  newareacor -= diffy * ( min2x - (double)(intx) );
	    }
	 }
	 else
	 {
	    switch(direction)
	    {
	       case 0:
		  if(pixelchange == DELTA_X)
		     direction = 0;
		  else
		     direction = 3;
		  break;
	       case 1:
		  if(pixelchange == DELTA_X)
		     direction = 0;
		  else
		     direction = 1;
		  break;
	       case 2:
		  if(pixelchange == DELTA_X)
		     direction = 2;
		  else
		     direction = 3;
		  break;
	       case 3:
		  if(pixelchange == DELTA_X)
		     direction = 2;
		  else
		     direction = 1;
		  break;
	    }
	    switch(direction)
	    {
	       case 0:
		  newareacor -= diffx * ( min2y - (double)(inty));
		  break;
	       case 1:
		  newareacor -= diffy * ( (double)(intx + 1) - max2x );
		  break;
	       case 2:
		  newareacor -= diffx * ( (double)(inty+1) - max2y );
		  break;
	       case 3:
		  newareacor -= diffy * ( min2x - (double)(intx) );
		  break;
	    }
	 }

	 /* save the old int values and make the new ones */
	 lastx = x;
	 lasty = y;
	 lastintx = intx;
	 lastinty = inty;

	 /* find the rectangle that encloses the image */
	 if(intx > maxx) maxx = intx;
	 if(intx < minx) minx = intx;
	 if(inty > maxy) maxy = inty;
	 if(inty < miny) miny = inty;

	 dP[inty][intx] = WHITE;
	 bounce = 0;
      }
   }
}


/*
** the bspline function
*/
static int splinepoint( 
	unsigned *x, 
	unsigned *y,
	double u,
	int numpnts, 
	double *newx, 
	double *newy )
{
   int
      n,
      curpnt;
   double
      tempx = 0.0,
      tempy = 0.0,
      bl;

   /* find the next point */
   curpnt = numpnts - (int)u;
   if(curpnt == numpnts)
      curpnt = 0;
   for(n = 0 ; n < SPLINE_ORDER ; n++ )
   {
      bl = blend( 0, SPLINE_ORDER , MOD(curpnt + u ,numpnts) );
      tempx += bl * x[curpnt];
      tempy += bl * y[curpnt];
      curpnt++;
      if(curpnt == numpnts)
	 curpnt = 0;
   }

   *newx = tempx;
   *newy = tempy;
}

static double blend( int i, int k, double u )
{
   double N;
   register diff, n1;

   if (k == 1)
   {
      if ( ( i <= u ) && ( u < (i+1) ) )
	 N = 1;
      else
	 N = 0;
   }
   else
   {
      diff = k-1;
      if (diff != 0)
      {
	 N = (u - (i) ) * blend(i, k-1, u)/diff;
	 N += ( (i+k) - u) * blend(i+1, k-1, u)/diff;
      }
      else
	 N = 0;
   }
   return(N);
}
