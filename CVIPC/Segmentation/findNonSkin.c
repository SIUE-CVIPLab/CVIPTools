/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: findNonSkin.c
*           Description: Dermvis class code for masking out nonskin from
*			 an RGB skin tumor image.
*         Related Files: findNonSkin.h
*   Initial Coding Date: Fri Sep 24 15:22:50 CDT 1993
*           Portability: Standard (ANSI) C
*            References: UMR dermvis group, wvs[,rhm][,rpm]@ee.umr.edu
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
** $Log: findNonSkin.c,v $
** Revision 1.2  1997/03/08 00:44:38  yawei
** Name Changes:
** 	BOOLEAN ==> CVIP_BOOLEAN
** 	FALSE ==> CVIP_YES
** 	TRUE ==> CVIP_NO
** 	BYTE ==> CVIP_BYTE
** 	SHORT ==> CVIP_SHORT
** 	INTEGER ==> CVIP_INTEGER
** 	FLOAT ==> CVIP_FLOAT
** 	DOUBLE ==> CVIP_DOUBLE
** 	TYPE ==> CVIP_TYPE
**
** Revision 1.1  1994/10/30 17:58:25  hanceg
** CVIPtools1.0 source file - G. Hance
**
*
****************************************************************************/
#include "CVIPtoolkit.h"
#include "DermVis.h"
#include "CVIPdef.h"

static int isNonSkin_RGB( byte r, byte g, byte b, int i, int j );

#define SHADOW		1
#define FLASH		2

#define	SHADOWBOUND	3

#define REDFACTOR 	0.70
#define SHADOWTHRESH	70
#define RGTHRESH1   	1.15
#define RGTHRESH2   	1.3
#define GBTHRESH	1.5

#define NONSKIN 	0xFF
#define SKIN		0x00

/*
** global variables
*/
unsigned 	height, width, hbound, wbound;

Image * 
findNonSkin_DVis(
	Image *imageP
)
{
	Image *maskP;
	byte *rP, *gP, *bP, **bvecP, *mP, r;
	unsigned bands;
	register int i, j;
	float rg, rin;

	height 	= getNoOfRows_Image(imageP);
	width	= getNoOfCols_Image(imageP);
	bands 	= getNoOfBands_Image(imageP);

	maskP = new_Image( PBM, BINARY, 1, height, width, CVIP_BYTE, REAL);

	bvecP = (byte **) malloc(3*sizeof(byte *));
	getBandVector_Image(imageP, bvecP);
	getBandVector_Image(maskP, &mP);

	rP = bvecP[0];
	gP = bvecP[1];
	bP = bvecP[2];

	hbound = height	>> SHADOWBOUND;
	wbound = width	>> SHADOWBOUND;

	for(i=0; i < height; i++)
		for(j=0; j < width; j++, mP++, rP++, gP++, bP++)
			*mP = (isNonSkin_RGB( *rP, *gP, *bP, i, j)) 
			? SKIN : NONSKIN;


	free(bvecP);
	return maskP;
}


static int
isNonSkin_RGB(
	byte	r,
	byte 	g,
	byte	b,
	int	i,
	int	j
)
{
	float	rg;
	byte	rin;

	/*
	** check for shadows 
	*/
   	if( 	( r < SHADOWTHRESH) &&
		( ( ( i < hbound ) ||
		  ( i >= (height-hbound) ) ) ||
		  ( ( j < wbound ) ||
		  ( j >= (width-wbound) ) ) )
 	)
      		return SHADOW;
   	/* 
	** obvious not a skin patch
	*/
   	else if( ( g > r) || ( b > r) )
      		return FLASH;
   	/* 
	** more work
	*/
   	else {
      		rin = ROUND( REDFACTOR * ((float) r) );

      		if( ( g > rin ) || (b > rin ) ) {
         		rg = g ? ((float) r) / ((float) g) : ((float) r);

         		if( rg < RGTHRESH1 )
            			return FLASH;
         		else if ( rg < RGTHRESH2 )
            			if( (b ? (((double) g) / ((float) b)) : g) < GBTHRESH )
               				return FLASH;
		}
   	}

return SKIN;
}
