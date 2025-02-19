/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: sct_split.c
*           Description: Spherical Coordinate transform split
*         Related Files: sct_split.h
*   Initial Coding Date: Sun May 30 14:48:14 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Kun Luo
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1993 SIUE - by Kun Luo.
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
** $Log: sct_split.c,v $
** Revision 1.10  1996/12/30 22:23:09  yawei
** y_split -> A_split
** x_split -> B_split
**
 * Revision 1.9  1996/12/23  16:42:59  yawei
 * Changed function prototype:
 *    Image *SCTsplit_Image(Image **imgP,int,int )
 * ==>Image *sct_split_segment(Image *imgP,int,int )
 *
 * Revision 1.8  1996/12/23  16:10:39  yawei
 * Changed filename SCTsplit.c ==> sct_split.c
 *
 * Revision 1.7  1996/11/25  16:49:45  yawei
 * fixed SCT bug
 *
 * Revision 1.6  1996/11/20  18:23:54  akjoele
 * fixed a few memory leaks.
 *
 * Revision 1.5  1996/11/19  04:09:27  yawei
 * incomplete fixing SCT bug
 *
 * Revision 1.4  1996/11/04  18:43:23  akjoele
 * Preliminary work to ferret out SCT core bug.  Not fixed.
 *
 * Revision 1.3  1996/01/23  22:29:33  kluo
 * change prompt
 *
 * Revision 1.2  1996/01/17  03:45:19  kluo
 * change to allow different split
 *
 *
*
****************************************************************************/
#include "CVIPcolor.h"
#include "CVIPdef.h"
#include "sct_split.h"

static void 
findStats(
	byte **		cvecP, 
	byte *		splitP_a,
	byte *		splitP_b, 
	unsigned int 	vdim,
	int 		A_split,
	int 		B_split, 
	byte **		r_avg,
        byte **		g_avg, 
	byte **		b_avg
);

static void 
colorSplit(
	float **	cvecP, 
	byte *		splitP_a,
	byte *		splitP_b, 
	unsigned int 	vdim, 
        float 		*a_avg, 
	float 		*b_avg
);

static void 
sctMinMax(
	float **	svecP, 
	unsigned int 	vdim,
	float *		a_avg,
	float *		b_avg,
	int		A_split,
	int		B_split 
);


Image *
sct_split_setup(
	Image	*imgP
)
{
	int B_split, A_split;

	fflush(stdin);
	printf("Enter number of colors along Angle A axis:");
	scanf("%d",&B_split);
	printf("Enter number of colors along Angle B axis:");
	scanf("%d",&A_split);

	imgP=sct_split_segment(imgP,A_split, B_split);

	return imgP;
}

Image *
sct_split_segment (
	Image *imgP, int A_split, int B_split
)
{
   	unsigned int 	rows, cols, bands, imgdim;
	float		a_avg[2],b_avg[2];
   	register int 	i;
   	float 		**cvecP;
   	byte 		**origP;
   	byte 		*splitP_a, *splitP_b, **ravg, **gavg, **bavg;
   	Image 		*sctP, *temP;

   	/* 
	** simplify some variables
	*/
   	rows 	= getNoOfRows_Image(imgP);
   	cols 	= getNoOfCols_Image(imgP);
   	bands 	= getNoOfBands_Image(imgP);

   	imgdim = rows*cols;

	ravg = (byte**)malloc(A_split*sizeof(byte*));
	gavg = (byte**)malloc(A_split*sizeof(byte*));
	bavg = (byte**)malloc(A_split*sizeof(byte*));
	*ravg = (byte*)malloc(B_split*A_split*sizeof(byte));
	*gavg = (byte*)malloc(B_split*A_split*sizeof(byte));
	*bavg = (byte*)malloc(B_split*A_split*sizeof(byte));

	for(i=1;i<A_split;i++){
	    ravg[i] = &ravg[0][B_split*i];
	    gavg[i] = &gavg[0][B_split*i];
	    bavg[i] = &bavg[0][B_split*i];
        }

	/* make a copy of the original image, since it will be chnaged */
	temP = (Image *)duplicate_Image(imgP);

   sctP = (Image *) colorxform(imgP, SCT, NULL, NULL, 1);
	/* no need to delete imP, which shares data with sctP */
	imgP = temP;

   cvecP = (float **) malloc(sizeof(float *)*3);
   origP = (byte **) malloc(sizeof(byte *)*3);

	getBandVector_Image(sctP, cvecP);
	getBandVector_Image(imgP, origP);

	print_CVIP("performing SCT/center split ...\n");	
	
   sctMinMax(cvecP, imgdim, a_avg, b_avg,A_split, B_split);


   splitP_a = (byte *) malloc(imgdim*sizeof(byte));
	splitP_b = (byte *) malloc(imgdim*sizeof(byte));
   colorSplit(cvecP, splitP_a, splitP_b, imgdim, a_avg, b_avg);

   	
   findStats(origP, splitP_a, splitP_b, imgdim,A_split,B_split, ravg, 
		gavg, bavg);


   	for(i=0; i < imgdim; i++)
		if(splitP_a[i] != 255) {
      			origP[0][i] = ravg[splitP_a[i]][splitP_b[i]];
      			origP[1][i] = gavg[splitP_a[i]][splitP_b[i]];
      			origP[2][i] = bavg[splitP_a[i]][splitP_b[i]];
		} 

   delete_Image(sctP);
/*	free(cvecP[0]); These space has already been freed by delete_Image(sctP)
	free(cvecP[1]);
	free(cvecP[2]); */
   	free(cvecP);
/*	free(origP[0]); This doesn't need to be freed, since they points to the 
	free(origP[1]); data of the output image
	free(origP[2]); */
   	free(origP);
   free(splitP_a);
	free(splitP_b);
	free(*ravg); free(*gavg);free(*bavg);
	free(ravg); free(gavg);free(bavg);
	return(imgP);	

} 
/* 
** End of function - sct_split_segment(...) 
*/
   

static void 
sctMinMax(
	float **	svecP, 
	unsigned int 	vdim,
	float *		a_avg,
	float *		b_avg,
	int		A_split,
	int		B_split 
)
{
	register int 	i, j,d;
	float amin=450, amax=0, bmin=450, bmax=0;


	for (i=0; i < vdim; i++)
   		if (svecP[0][i] != 0 ) {
       			amax = MAX(amax, svecP[1][i]);
      			bmax = MAX(bmax, svecP[2][i]);
      			amin = MIN(amin, svecP[1][i]);
      			bmin = MIN(bmin, svecP[2][i]);
		}

	a_avg[0] = amin ;
	a_avg[1] = (amax-amin)/A_split;
	b_avg[0] = bmin ;
	b_avg[1] = (bmax-bmin)/B_split;
	
}

static void 
colorSplit(
	float **	cvecP, 
	byte *		splitP_a,
	byte *		splitP_b, 
	unsigned int 	vdim, 
        float 		*a_avg, 
	float 		*b_avg
)
{
 	register int 	i=0;
	float temp;

 	for (; i<vdim; i++, splitP_a++,splitP_b++)
     		if (cvecP[0][i] != 0) {
			temp = cvecP[1][i] - a_avg[0];
			temp /= a_avg[1];
			temp -= 0.1;
			if(temp<0.0)
			    temp = 0;
/*			*splitP_a = (int)temp; */
			*splitP_a = (byte)temp;
			temp = cvecP[2][i] - b_avg[0];
			temp /= b_avg[1];
			temp -= 0.1;
			if(temp<0.0)
			    temp = 0;
/*			*splitP_b = (int)temp; */
			*splitP_b = (byte)temp; 
     		}
     		else
        		*splitP_a = *splitP_b = 255;

return;
}

static void 
findStats(
	byte **		cvecP, 
	byte *		splitP_a,
	byte *		splitP_b, 
	unsigned int 	vdim,
	int 		A_split,
	int 		B_split, 
	byte **		r_avg,
        byte **		g_avg, 
	byte **		b_avg
)
{
 	register int 	i=0,j;
 	long 		**rsum, **bsum, **gsum, **count;

	rsum = (long**)malloc(A_split*sizeof(long*));
	gsum = (long**)malloc(A_split*sizeof(long*));
	bsum = (long**)malloc(A_split*sizeof(long*));
	count = (long**)malloc(A_split*sizeof(long*));
	*rsum = (long*)calloc(B_split*A_split,sizeof(long));
	*gsum = (long*)calloc(B_split*A_split,sizeof(long));
	*bsum = (long*)calloc(B_split*A_split,sizeof(long));
	*count = (long*)calloc(B_split*A_split,sizeof(long));

	for(i=1;i<A_split;i++){
	    rsum[i] = &rsum[0][B_split*i];
	    gsum[i] = &gsum[0][B_split*i];
	    bsum[i] = &bsum[0][B_split*i];
	    count[i] = &count[0][B_split*i];
        }


 	for (i=0; i<vdim; i++, splitP_a++,splitP_b++)
     		if (*splitP_a != 255) {
        		rsum[*splitP_a][*splitP_b] += cvecP[0][i];
        		gsum[*splitP_a][*splitP_b] += cvecP[1][i];
        		bsum[*splitP_a][*splitP_b] += cvecP[2][i];
        		count[*splitP_a][*splitP_b]++;
 		}

 	for (j=0; j < A_split; j++) {
	    for(i=0; i< B_split;i++){
		if(count[j][i] == 0)
		    count[j][i] = 1;
    		r_avg[j][i] = rsum[j][i]/count[j][i];
    		g_avg[j][i] = gsum[j][i]/count[j][i];
    		b_avg[j][i] = bsum[j][i]/count[j][i];
	    }
 	}

	free(*rsum);
	free(*bsum);
	free(*gsum);
	free(*count);
	free(rsum);
	free(bsum);
	free(gsum);
	free(count);

}


