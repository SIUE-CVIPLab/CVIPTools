/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: median_cut.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Sun Dec 22 11:11:09 CST 1996
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Jef Poskanzer
*
** Copyright (C) 1989, 1991 by Jef Poskanzer.
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
** $Log: median_cut.c,v $
** Revision 1.8  1997/03/08 17:01:12  yawei
** Swaped CVIP_YES and CVIP_NO
**
** Revision 1.7  1997/03/08 00:44:07  yawei
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
** Revision 1.6  1996/12/24 15:39:26  yawei
** tried to fix the median_cut bug, not complete
**
 * Revision 1.5  1996/12/23  18:30:27  yawei
 * Changed filename MedianCut.c ==> median_cut.c
 *
 * Revision 1.4  1996/12/23  00:43:12  yawei
 * Changed (const Image) to (Image ) in the setup function.
 *
 * Revision 1.3  1996/12/22  23:10:48  yawei
 * Changed so the mediancut_setup won't copy the input Image structure.
 * OK
 *
 * Revision 1.2  1996/12/22  17:12:58  yawei
 * ColorHistogram * medianCut_Image ==> Image *median_cut_segment
 *
*
****************************************************************************/

#include "CVIPtoolkit.h"
#include "CVIPdef.h"
#include "median_cut.h"
#include <stdlib.h>

#define MAXCOLORS 32767
#define MAXPIXVAL 255

#define LARGE_NORM
/* #define LARGE_LUM */

/* #define REP_CENTER_BOX */
/* #define REP_AVERAGE_COLORS */
#define REP_AVERAGE_PIXELS

typedef struct {
	int ind;
	int colors;
	int sum;
} box;

typedef box* box_vector; 

#define lumin_Color(p) ( 0.299 * getRed_Color(p) + 0.587 * getGrn_Color(p) + 0.114 * getBlu_Color(p) )

static ColorHistogram *mediancut (ColorHistogram *chP, int sum, int newcolors);
static int redcompare(const void *cm1, const void *cm2);
static int greencompare(const void *cm1, const void *cm2);
static int bluecompare(const void *cm1, const void *cm2);
static int sumcompare(const void *b1, const void *b2 );

Image	*
median_cut_setup (
	Image 	*imgP
)
{
	Image		*mcsP, *freP;
	unsigned	newcolors;
	Color		bg = {0, 0, 0};

	mcsP = imgP;

	print_CVIP("\nPlease enter the number of desired colors: ");
 	newcolors = getUInt_CVIP(10, 2, 1000);
	print_CVIP("\n");

	mcsP = median_cut_segment(mcsP, newcolors, CVIP_NO, bg);

	return mcsP;
}

Image *
median_cut_segment(
	Image *imgP,
	int newcolors,
	CVIP_BOOLEAN is_bg,
	Color bg
)
{
	byte **cvecP, mask;
	register byte *rP, *gP, *bP;
	unsigned imgsize, no_pixels = 0;
    	int rows, cols;
    	register int i;
    	register int ind;
	Color pixel;
	ColorMap colormap;
	ColorHistogram *chP, *newchP;
	ColorHashTable *chtP;
	const char *fn = "median_cut_segment";

	chP = new_ColorHist();

	mask = MAXPIXVAL;

	rows = getNoOfRows_Image(imgP);
	cols = getNoOfCols_Image(imgP);
	imgsize = rows*cols;

	cvecP = (byte **) malloc(3*sizeof(byte *));
	getBandVector_Image(imgP, cvecP);

	/*
	** Step 2: attempt to make a histogram of the colors, unclustered.
	** If at first we don't succeed, lower maxval to increase color
	** coherence and try again.  This will eventually terminate, with
	** maxval at worst 15, since 32^3 is approximately MAXCOLORS.
	*/
	for(;;) {

		msg_CVIP(fn, "making histogram...\n" );
		compute_ColorHist(chP, imgP, MAXCOLORS);
	    	if (chP->histogram != NULL)
			break;
		mask <<= 1;
	    	msg_CVIP(fn, "too many colors!\n" );
	    	msg_CVIP(fn, "reducing pixel sample range to [%u - %u] to improve clustering...\n", ((byte) ~mask)+1, mask);
		rP = cvecP[0];
		gP = cvecP[1]; 
		bP = cvecP[2];
	    	for(i = 0; i < imgsize; i++, rP++, gP++, bP++ ) {
			*rP &= mask;
			*gP &= mask;
			*bP &= mask;
		}
	}
	msg_CVIP(fn, "%u colors found\n", chP->no_of_colors );	

	if(is_bg)
		dropColor_ColorHist(chP, bg, &no_pixels); 

	/*
	** Step 3: apply median-cut to histogram, making the new colormap.
	*/
	msg_CVIP(fn, "choosing %d colors...\n", newcolors );
	newchP = mediancut( chP, imgsize - no_pixels, newcolors );
	colormap = newchP->histogram;
	delete_ColorHist(chP);
   

    	/*
   	** Step 4: map the colors in the image to their closest match in the
    	** new colormap, and write 'em out.
    	*/

    	msg_CVIP(fn, "mapping image to new colors...\n" );

    	chtP = new_ColorHT();

	rP = cvecP[0];
	gP = cvecP[1];
	bP = cvecP[2];
	
    	for (i = 0; i < imgsize; i++, rP++, gP++, bP++ ) {
	
		/* 
		 * Check hash table to see if what we have already matched this
		 * color. 
		 */

		
		assign_Color(pixel,*rP,*gP,*bP);

		if(is_bg && equal_Color(pixel,bg)) continue;

		ind = lookUpColor_ColorHT( chtP, pixel );

	   	if ( ind == -1 ) { /* search colormap for closest match. */

			register int j, r, g, b;
			register long dist, newdist;

			dist = 2000000000;

			for (j = 0; j < newcolors; j++) {

		    		r = getRed_Color( colormap[j].pixel );
		    		g = getGrn_Color( colormap[j].pixel );
		    		b = getBlu_Color( colormap[j].pixel );
		    		newdist = ( *rP - r ) * ( *rP - r ) +
			      	  	  ( *gP - g ) * ( *gP - g ) +
			      	  	  ( *bP - b ) * ( *bP - b );
		    		if ( newdist < dist ) {
					ind = j;
					dist = newdist;
				}

		    	}

		   	addObject_ColorHT(chtP, pixel, ind);
		}	

	    	*rP = getRed_Color(colormap[ind].pixel);
		*gP = getGrn_Color(colormap[ind].pixel);
		*bP = getBlu_Color(colormap[ind].pixel);
		
		colormap[ind].value++;
	}

print_ColorHist(newchP);
delete_ColorHT(chtP);
delete_ColorHist(newchP);
free(cvecP);
return imgP;
}

/*
** Here is the fun part, the median-cut colormap generator.  This is based
** on Paul Heckbert's paper "Color Image Quantization for Frame Buffer
** Display", SIGGRAPH '82 Proceedings, page 297.
*/

static ColorHistogram *
mediancut( 
	ColorHistogram *chP, 
	int sum,
	int newcolors
)
{
	ColorHistogram *newchP;
	ColorMap colormap, chist;
	box_vector bv;
	register int bi, i;
	int boxes, colors;
	const char *fn = "mediancut";

	chist = chP->histogram;
	colors = chP->no_of_colors;

   bv = (box_vector) malloc( sizeof(box) * newcolors );

	newchP = new_ColorHist();
	newchP->no_of_colors = newcolors;
	colormap = newchP->histogram =
	(ColorMap) calloc(newcolors, sizeof(ColorHistObject));
    	if ( bv == NULL || colormap == NULL ) {
		error_CVIP(fn, "out of memory" );
		return NULL;
	}

    	/*
    	** Set up the initial box.
    	*/
   	bv[0].ind = 0;
    	bv[0].colors = colors;
    	bv[0].sum = sum;
    	boxes = 1;

    	/*
    	** Main loop: split boxes until we have enough.
    	*/
    	while ( boxes < newcolors ) {

		register int indx, clrs;
		int sm;
		register int minr, maxr, ming, maxg, minb, maxb, v;
		int halfsum, lowersum;

		/*
		** Find the first splittable box.
		*/
		for ( bi = 0; bi < boxes; ++bi )
	    		if ( bv[bi].colors >= 2 )
				break;
		if ( bi == boxes )
	    		break;	/* ran out of colors! */
		indx = bv[bi].ind;
		clrs = bv[bi].colors;
		sm = bv[bi].sum;

		/*
		** Go through the box finding the minimum and maximum of each
		** component - the boundaries of the box.
		*/
		minr = maxr = getRed_Color( chist[indx].pixel );
		ming = maxg = getGrn_Color( chist[indx].pixel );
		minb = maxb = getBlu_Color( chist[indx].pixel );
		for ( i = 1; i < clrs; ++i ) {
	    		v = getRed_Color( chist[indx + i].pixel );
	    		if ( v < minr ) minr = v;
	    		if ( v > maxr ) maxr = v;
	    		v = getGrn_Color( chist[indx + i].pixel );
	    		if ( v < ming ) ming = v;
	    		if ( v > maxg ) maxg = v;
	    		v = getBlu_Color( chist[indx + i].pixel );
	    		if ( v < minb ) minb = v;
	    		if ( v > maxb ) maxb = v;
	    	}

	/*
	** Find the largest dimension, and sort by that component.  I have
	** included two methods for determining the "largest" dimension;
	** first by simply comparing the range in RGB space, and second
	** by transforming into luminosities before the comparison.  You
	** can switch which method is used by switching the commenting on
	** the LARGE_ defines at the beginning of this source file.
	*/

#ifdef LARGE_NORM

		if ( maxr - minr >= maxg - ming && maxr - minr >= maxb - minb )
	    		qsort((char*) &(chist[indx]), clrs, 
			sizeof(ColorHistObject), redcompare );
		else if ( maxg - ming >= maxb - minb )
	    		qsort( (char*) &(chist[indx]), clrs,
			sizeof(ColorHistObject), greencompare );
		else
	    		qsort( (char*) &(chist[indx]), clrs, 
			sizeof(ColorHistObject), bluecompare );
#endif /*LARGE_NORM*/

#ifdef LARGE_LUM
{
	pixel p;
	float rl, gl, bl;

	assign_Color(p, maxr - minr, 0, 0);
	rl = lumin_Color(p);
	assign_Color(p, 0, maxg - ming, 0);
	gl = lumin_Color(p);
	assign_Color(p, 0, 0, maxb - minb);
	bl = lumin_Color(p);

	if ( rl >= gl && rl >= bl )
		qsort( (char*) &(chist[indx]), clrs, 
		sizeof(ColorHistObject), redcompare );
	else if ( gl >= bl )
	    	qsort( (char*) &(chist[indx]), clrs, 
		sizeof(ColorHistObject), greencompare );
	else
	    	qsort( (char*) &(chist[indx]), clrs, 
		sizeof(ColorHistObject), bluecompare );
}
#endif /*LARGE_LUM*/
	
	/*
	** Now find the median based on the counts, so that about half the
	** pixels (not colors, pixels) are in each subdivision.
	*/
	lowersum = chist[indx].value;
	halfsum = sm / 2;
	for ( i = 1; i < clrs - 1; ++i ) {
		if ( lowersum >= halfsum )
			break;
	    	lowersum += chist[indx + i].value;
	}

	/*
	** Split the box, and sort to bring the biggest boxes to the top.
	*/
	bv[bi].colors = i;
	bv[bi].sum = lowersum;
	bv[boxes].ind = indx + i;
	bv[boxes].colors = clrs - i;
	bv[boxes].sum = sm - lowersum;
	++boxes;
	qsort( (char*) bv, boxes, sizeof(box), sumcompare );
}

    /*
    ** Ok, we've got enough boxes.  Now choose a representative color for
    ** each box.  There are a number of possible ways to make this choice.
    ** One would be to choose the center of the box; this ignores any structure
    ** within the boxes.  Another method would be to average all the colors in
    ** the box - this is the method specified in Heckbert's paper.  A third
    ** method is to average all the pixels in the box.  You can switch which
    ** method is used by switching the commenting on the REP_ defines at
    ** the beginning of this source file.
    */
    	for ( bi = 0; bi < boxes; ++bi ) {

#ifdef REP_CENTER_BOX

		register int indx = bv[bi].ind;
		register int clrs = bv[bi].colors;
		register int minr, maxr, ming, maxg, minb, maxb, v;

		minr = maxr = getRed_Color( chist[indx].pixel );
		ming = maxg = getGrn_Color( chist[indx].pixel );
		minb = maxb = getBlu_Color( chist[indx].pixel );
		for ( i = 1; i < clrs; ++i ) {
	    		v = getRed_Color( chist[indx + i].pixel );
	    		minr = MIN( minr, v );
	    		maxr = MAX( maxr, v );
	    		v = getGrn_Color( chist[indx + i].pixel );
	    		ming = MIN( ming, v );
	    		maxg = MAX( maxg, v );
	    		v = getBlu_Color( chist[indx + i].pixel );
	    		minb = MIN( minb, v );
	    		maxb = MAX( maxb, v );
	    	}
		assign_Color(
	    	colormap[bi].pixel, ( minr + maxr ) / 2, ( ming + maxg ) / 2,
	    	( minb + maxb ) / 2 );

#endif /*REP_CENTER_BOX*/

#ifdef REP_AVERAGE_COLORS

	register int indx = bv[bi].ind;
	register int clrs = bv[bi].colors;
	register long r = 0, g = 0, b = 0;

	for ( i = 0; i < clrs; ++i ) {
		r += getRed_Color( chist[indx + i].pixel );
	    	g += getGrn_Color( chist[indx + i].pixel );
	    	b += getBlu_Color( chist[indx + i].pixel );
	}
	r = r / clrs;
	g = g / clrs;
	b = b / clrs;
	assign_Color( colormap[bi].pixel, r, g, b );

#endif /*REP_AVERAGE_COLORS*/

#ifdef REP_AVERAGE_PIXELS
	register int indx = bv[bi].ind;
	register int clrs = bv[bi].colors;
	register long r = 0, g = 0, b = 0, sum = 0;

	for ( i = 0; i < clrs; ++i ) {
		r += 	getRed_Color( chist[indx + i].pixel ) * 
			chist[indx + i].value;
	    	g += 	getGrn_Color( chist[indx + i].pixel ) * 
			chist[indx + i].value;
	    	b += 	getBlu_Color( chist[indx + i].pixel ) * 
			chist[indx + i].value;
	    	sum += 	chist[indx + i].value;
	}
	r = r/sum;
	if ( r > MAXPIXVAL ) r = MAXPIXVAL;	/* avoid math errors */
	g = g/sum;
	if ( g > MAXPIXVAL ) g = MAXPIXVAL;
	b = b/sum;
	if ( b > MAXPIXVAL ) b = MAXPIXVAL;
	assign_Color( colormap[bi].pixel, r, g, b );

#endif /*REP_AVERAGE_PIXELS*/
}

/*
** All done.
*/
return newchP;

}

static int
redcompare(
	const void *cm1, 
	const void *cm2
)
{
	return 	(int) getRed_Color( ((ColorMap) cm1)->pixel ) - 
		(int) getRed_Color( ((ColorMap) cm2)->pixel );
}

static int
greencompare(
	const void *cm1, 
	const void *cm2 
)
{
	return 	(int) getGrn_Color( ((ColorMap) cm1)->pixel ) - 
		(int) getGrn_Color( ((ColorMap) cm2)->pixel );
}

static int
bluecompare( 
	const void *cm1, 
	const void *cm2 
)
{
	return 	(int) getBlu_Color( ((ColorMap) cm1)->pixel ) - 
		(int) getBlu_Color( ((ColorMap) cm2)->pixel );
}

static int
sumcompare( 
	const void *b1, 
	const void *b2 
)
{
	return ((box_vector) b2)->sum - ((box_vector) b1)->sum;
}
