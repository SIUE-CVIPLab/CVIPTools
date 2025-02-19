/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: hist_thresh.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Thu Dec  2 15:51:36 CST 1993
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Gregory Hance, Charles Stacey
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
** $Log: hist_thresh.c,v $
** Revision 1.7  1997/07/06 21:13:52  wzheng
** *** empty log message ***
**
** Revision 1.6  1997/03/08 17:01:26  yawei
** Swaped CVIP_YES and CVIP_NO
**
** Revision 1.5  1997/03/08 00:44:44  yawei
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
** Revision 1.4  1996/12/23 20:03:32  yawei
** Changed filename PCT_Image ==> pct
**
 * Revision 1.3  1996/12/21  00:58:59  yawei
 * Changed filename to "hist_thresh.c"
 *
 * Revision 1.2  1996/12/21  00:42:55  yawei
 *    Image *ATS_SetUp(const Image *imgP)
 * ==>Image *hist_thresh_segment(const Image *imgP)
 *
 *    int adaptThresh_Image( Image *imgP, unsigned nom )
 * ==>Image *hist_thresh_gray(Image *imgP)
 *    (This function is not currently in the Book, it works on single band image,
 *     the original nom doesn't do anything)
 *
 * Revision 1.1  1994/10/30  17:58:21  hanceg
 * CVIPtools1.0 source file - G. Hance
 *
*
****************************************************************************/
#include "CVIPtoolkit.h"
#include "hist_thresh.h"
#include "CVIPdef.h"

#ifdef SQRT_2PI
#undef SQRT_2PI
#endif
#define SQRT_2PI      2.506628275

static int findPeaks( double *vecP, linked_list	**listP );
static int formMapHist(byte *mapP, int n, linked_list *listP);

static int
formGausian(
	float		tore,
	float		len,
	double		*ser
)
{
    	double 		neg_two_tore_sqr, c;
    	int 		i, j;
    
    	neg_two_tore_sqr = -2.0 * tore * tore;
    	c = 1.0 / SQRT_2PI / tore;
        
    	for (i = 0, j = -len/2; i < len; i++, j++) {
        	ser[i] = c * exp(j * j / neg_two_tore_sqr);
    	}
    
    	return 1;
}


typedef struct {
	int	lower;
	int	peak;
	int	upper;
} PeakObject;

static void
freePeakObject(
	void	*objP
)
{
	free(objP);
}

static void
printPeakObject(
	void 	*objP,
	FILE	*fP
)
{
	PeakObject	*oP = objP;

	fprintf(fP, "lower = %d\n", oP->lower);
	fprintf(fP, " peak = %d\n", oP->peak);
	fprintf(fP, "upper = %d\n\n", oP->upper);
}


Image *
hist_thresh_gray(
	Image 		*imgP,	/* pointer to image structure */
	float tore /* variance */
)
{
	const char	*fn = "hist_thresh_gray";
	byte		*bP, **bvecP, map[256];
	int		len;
	register int	i;
	unsigned	rows, cols, no_of_pixels, bands, peaks;
	double 		dhisto[256], dgauss[256], dderiv[256], *dkern;
	double 		deriv[2] = {-1.0, 1.0};
	//float		tore = 5.0;
	linked_list	*listP;

	rows = getNoOfRows_Image(imgP);
	cols = getNoOfCols_Image(imgP);
	bands = getNoOfBands_Image(imgP);
	bvecP = (byte **) malloc(sizeof(byte *)*bands);
	no_of_pixels = rows*cols;
	getBandVector_Image(imgP, bvecP);
	bP = *bvecP;

	if( !findHisto_Vector(bP, rows*cols, dhisto, 0, 255, CVIP_DOUBLE) ) {
		error_CVIP(fn, "could not find histogram!\n");
		return (Image *)NULL;
	}
		
	len = (int) (10 * tore - 1);

	dkern = (double*)malloc(sizeof(double) * len);

	(void) memcpy((void *)dgauss, (void *)dhisto, sizeof(double)*256);
	formGausian(tore, (float) len, dkern);
	convolve_Vector(dgauss, dkern, 256, len);

	(void) memcpy((void *)dderiv, (void *)dgauss, sizeof(double)*256);
	convolve_Vector(dderiv, deriv, 256, 2);

	/*
	printHisto_Vector("histo1.txt", dhisto, CVIP_DOUBLE, 0, 255, 0);
	printHisto_Vector("histo2.txt", dgauss, CVIP_DOUBLE, 0, 255, 0);
	printHisto_Vector("histo3.txt", dderiv, CVIP_DOUBLE, 0, 255, 0);
	*/

	(void) findPeaks(dderiv, &listP);

	peaks =  size_LL(listP);
	print_CVIP("\nfound %u modes\n\n", peaks);
	
 	print_LL(listP, printPeakObject, stderr);

/*	delete_LL(listP, freePeakObject);*/

	(void) formMapHist(map, 256, listP);
	delete_LL(listP, freePeakObject);

	for(i=0; i < no_of_pixels; i++, bP++)
		*bP = map[*bP];

	free(bvecP);
	return imgP;
}

static int
formMapHist(
	byte		*mapP,
	int		n,
	linked_list	*listP
)
{

	register int	i;
	PeakObject	*objP;

	(void) bzero(mapP, n*sizeof(byte));

	head_LL(listP);

	for(;;) {

		objP = retrieve_LL(listP);

		for(i=objP->lower; i <= objP->upper; i++)
			mapP[i] = objP->peak;

		if(istail_LL(listP)) break;
		next_LL(listP);

	}

	return 1;
}
		
		

static int
findPeaks(
	double		*vecP,
	linked_list	**listP
)
{
	linked_list	*lP;
	register int	i;
	PeakObject	*oP;
	int 		lower, peak, upper;

	*listP = lP = new_LL();

	/* 
	** skip black -- this gray value tends to bias the histo. 
	*/
	i=1; 

	while(i < 256) {

		/*
		** find lower valley
		*/
		for(; (i < 256) && (vecP[i] <= 0); i++);
		lower = i;
	
		/*
		** find peak
		*/
		for(; (i < 256) && (vecP[i] > 0); i++);
		peak = i-1;


		/*
		** find upper valley
		*/
		for(; (i < 256) && (vecP[i] < 0); i++);
		upper = i-1;

		if(upper == peak) break;

		oP = (PeakObject *) malloc(sizeof(PeakObject));
		oP->lower = lower;
		oP->peak = peak;
		oP->upper = upper;

 		addnext_LL(lP, oP);

	}

	return 1;
}


Image	*
hist_thresh_segment (Image	*imgP, float tore)
{
	Image	*freP;

	if(getNoOfBands_Image(imgP) > 1) {
		if( (imgP = pct(imgP, CVIP_NO, NULL)) == (Image *)NULL ) {
			error_CVIP("main","could not perform PCT!");
			return NULL;;
		}
		(void) cropBands_Image(imgP, 2);
		freP = imgP;
		imgP = remap_Image(imgP, CVIP_BYTE, 0, 255);
		delete_Image(freP);
	}

	return hist_thresh_gray(imgP, tore);
}

