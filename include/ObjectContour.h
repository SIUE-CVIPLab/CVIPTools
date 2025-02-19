/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: ObjectContour.h
*           Description: 
*         Related Files: 
*   Initial Coding Date: Wed Sep 15 14:28:39 CDT 1993
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Gregory Hance
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
** $Log: ObjectContour.h,v $
 * Revision 1.3  1996/06/11  04:55:20  wli
 * no_of_vectors is changed back to 'int'
 *
 * Revision 1.2  1996/06/11  04:17:40  wli
 * change no_of_vectors from int to long
 *
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
*
****************************************************************************/
#if !defined( CONTOUR_DEFINED )

   #define CONTOUR_DEFINED

   #include "CVIPtoolkit.h"

/*****************************************************************************
*
*	Structure definitions
*
*****************************************************************************/

/***	a Vector is one link in a simple chain that follows
	the edge of a contour from sample point to sample point	***/

struct vector
{
	short		dir;
	struct vector *	next;
};

typedef struct vector	Vector;

struct ChainCodeType 
{
	int start_y;
	int start_x;
	int elev;
	int no_of_vectors;

	Vector *chain;
};


typedef struct ChainCodeType ChainCode;

/***	these are the 'dir' values in a Vector:

	0	right
	1	right and up
	2	up
	3	left and up
	4	left
	5	left and down
	6	down
	7	right and down		***/

extern ChainCode *new_ChainCode( int start_y, int start_x, int elev );
extern void report_ChainCode( ChainCode *ccP );
extern short build_ChainCode( ChainCode *ccP, Image *imageP, int x_min, int y_min, int x_max, int y_max );
extern void getXY_ChainCode(ChainCode *ccP, int **xP, int **yP);
extern void draw_ChainCode(ChainCode *ccP, Image *imageP);
extern int print_ChainCode(ChainCode *ccP, const char *name);
extern void delete_ChainCode( ChainCode *ccP );
extern ChainCode *read_ChainCode(const char *name);




#endif /* CONTOUR_DEFINED */
