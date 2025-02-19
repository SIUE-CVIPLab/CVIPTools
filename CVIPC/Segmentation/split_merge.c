/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: split_merge.c
*           Description: contains supporting routines for splitNmerge.c.
*         Related Files: splitNmerge.c, splitNmerge.h, Imakefile
*   Initial Coding Date: Tue Jun  1 12:02:16 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Gregory Hance
*                        Southern Illinois University @ Edwardsville
*
* Copyright (C) 1993 SIUE - by Gregory Hance.
*
* Permission to use, copy, modify, and distribute this software and its
* documentation for any purpose and without fee is hereby granted, provided
* that the above copyright notice appear in all copies and that both that
* copyright notice and this permission notice appear in supporting
* documentation.  This software is provided "as is" without express or
* implied warranty.
*
 RCS (Revision Control System) Information
 ...Added automatically by RCS

* $Log: split_merge.c $
* Revision 1.12  1997/07/18 15:18:48  wzheng
* Extract_Texture_Features(... &tf_usage);
*
* Revision 1.11  1997/03/08 17:01:08  yawei
* Swaped CVIP_YES and CVIP_NO
*
* Revision 1.10  1997/03/08 00:44:04  yawei
* Name Changes:
* 	BOOLEAN ==> CVIP_BOOLEAN
* 	FALSE ==> CVIP_YES
* 	TRUE ==> CVIP_NO
* 	BYTE ==> CVIP_BYTE
* 	SHORT ==> CVIP_SHORT
* 	INTEGER ==> CVIP_INTEGER
* 	FLOAT ==> CVIP_FLOAT
* 	DOUBLE ==> CVIP_DOUBLE
* 	TYPE ==> CVIP_TYPE
*
* Revision 1.9  1997/03/08 00:43:58  yawei
* Name Changes:
* 	CVIP_BOOLEAN ==> CVIP_CVIP_BOOLEAN
* 	CVIP_YES ==> CVIP_YES
* 	CVIP_NO ==> CVIP_NO
* 	CVIP_BYTE ==> CVIP_CVIP_BYTE
* 	CVIP_SHORT ==> CVIP_CVIP_SHORT
* 	CVIP_INTEGER ==> CVIP_CVIP_INTEGER
* 	CVIP_FLOAT ==> CVIP_CVIP_FLOAT
* 	CVIP_DOUBLE ==> CVIP_CVIP_DOUBLE
* 	CVIP_TYPE ==> CVIP_TYPE
*
* Revision 1.8  1997/01/15 17:08:53  yawei
* Global Change:  Image ==> Image
*
* Revision 1.7  1996/12/23  20:25:04  yawei
* *** empty log message ***
*
* Revision 1.6  1996/12/23  20:03:49  yawei
* Changed filename PCT_Image ==> pct
*
* Revision 1.5  1996/12/23  16:03:14  yawei
* Fixed bug in the setup function
*
* Revision 1.4  1996/12/23  00:46:24  yawei
* Changed header file splitnMerge.h ==> split_merge.h
*
* Revision 1.3  1996/12/22  21:31:16  yawei
* Changed filename
*    MRS_SetUp.c ==> split_merge.c
*
* Revision 1.2  1996/08/14  22:25:11  wli
* 'split_merge' and 'multi_resolution' in cviptcl
* call split_merge() in MRS_SetUp.c now
*
* Revision 1.1  1994/10/30  17:58:24  hanceg
* CVIPtools1.0 source file - G. Hance
*
* Revision 1.1  1993/06/02  04:48:33  hanceg
* Initial revision
*
****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "CVIPdef.h"
#include "CVIPtoolkit.h"
#include "split_merge.h"
#include "CVIPtexture.h"
#include "CVIPtransform.h"

static CVIP_BOOLEAN IDM_Texture_Test(Image *srcImage, QUAD *quadROI, void *paramP)
{
	CVIP_BOOLEAN pass = CVIP_YES;
	unsigned int band, row, col;
	unsigned int pixels = quadROI->dx * quadROI->dy;
	if (pixels >= 4)
	{
		byte **bP=0;
		TEXTURE *features[4];
		TEXTURE_FEATURE_MAP tf_usage;
		unsigned int half_dx = (quadROI->dx)/2;
		unsigned int half_dy = (quadROI->dy)/2;
		unsigned int distance, quadrant, start_row, start_col;
		float energy, inertia, IDM, entropy, correlation;
		float error, portion, *ptmp = (float*)paramP;

		if ((bP = (byte **)calloc(pixels, sizeof(int *))) == NULL)
		{
			printf("\nNot enough memory to allocate data array\n");
			return CVIP_NO;
		}

		portion = *ptmp++;
		distance = (int)*ptmp;

		tf_usage.ASM = 1;
		tf_usage.contrast = 1;
		tf_usage.correlation= 1;
		tf_usage.variance=0;
		tf_usage.IDM = 1;
		tf_usage.sum_avg = 0;
		tf_usage.sum_var = 0;
		tf_usage.sum_entropy = 0;
		tf_usage.entropy = 1;
		tf_usage.diff_var = 0;
		tf_usage.diff_entropy = 0;
		tf_usage.meas_corr1 = 0;
		tf_usage.meas_corr2 = 0;
		tf_usage.max_corr_coef = 0;

		for (band = 0; (pass == CVIP_YES) && (band < srcImage->bands); band++)
		{
			energy = 0;
			inertia = 0;
			IDM = 0;
			entropy = 0;
			correlation = 0;
			for (quadrant = 0; quadrant < 4; quadrant++)
			{
				start_row = quadROI->y + (half_dy*(quadrant%2));
				start_col = quadROI->x + (half_dx*(quadrant/2));
				for (row = 0; row < half_dy; row++, start_row++)
					bP[row]  = (byte *)srcImage->bandP[band]->rptr[start_row] + start_col;
				features[quadrant] = (TEXTURE *)Extract_Texture_Features(distance, bP, half_dy, half_dx, &tf_usage);
				energy +=  features[quadrant]->ASM[4];
				inertia +=  features[quadrant]->contrast[4];
				IDM +=  features[quadrant]->IDM[4];
				entropy +=  features[quadrant]->entropy[4];
				correlation += features[quadrant]->correlation[4];
			}
			energy /= 4.0;
			inertia /= 4.0;
			IDM /= 4.0;
			entropy /= 4.0;
			correlation /= 4.0;
			for (quadrant = 0; quadrant < 4; quadrant++)
			{
				error = abs(features[quadrant]->ASM[4] - energy);
				if (error > abs(energy * portion))
					pass = CVIP_NO;
				error = abs(features[quadrant]->contrast[4] - inertia);
				if (error > abs(inertia * portion))
					pass = CVIP_NO;
				error = abs(features[quadrant]->IDM[4] - IDM);
				if (error > abs(IDM * portion))
					pass = CVIP_NO;
				error = abs(features[quadrant]->entropy[4] - entropy);
				if (error > abs(entropy * portion))
					pass = CVIP_NO;
				error = abs(features[quadrant]->correlation[4] - correlation);
				if (error > abs(correlation * portion))
					pass = CVIP_NO;
				free(features[quadrant]);
			}
		} /* End of 'band' for loop */
		free(bP);
	} /* End of pixels if statement */
	if (pass == CVIP_YES)
	{
		double mean;
		byte **pData;
		for (band = 0; band < srcImage->bands; band++)
		{
			mean = 0.0;
			pData = getData_Image(srcImage, band);
			for (row = quadROI->y; row < (quadROI->y + quadROI->dy); row++)
			{
				for(col = quadROI->x; col < (quadROI->x + quadROI->dx); col++)
					mean += pData[row][col];
			}
			quadROI->data[band] = (byte)(mean/pixels);
		}
	}
	return pass;
}  /* End of IDM Texture Test */


static CVIP_BOOLEAN
BinTest(
	Image 	*srcImage,
	QUAD 	*quadROI,
	void 	*paramP
)
{
   register int i, j, k;
   unsigned int yoffset, gray_level[3][256], highest[3][4] = {0,0,0,0},temp[4], sum, max,mean[3];
   byte *bP=0, pass , *meanP = (byte *) paramP ;
   float threshold,*ftmp = (float *) paramP;
   char *fn = "Bin Test";

   threshold = *ftmp;
   yoffset = quadROI->y + quadROI->dy;
   for(k = 0; k < srcImage->bands; k++)
     for(i= 0; i < 256; i++, bP++)
	gray_level[k][i] = 0;

   for(k = 0; k < srcImage->bands; k++) {
      for(j = quadROI->y; j < yoffset; j++) {
         bP  = (byte *) srcImage->bandP[k]->rptr[j] + quadROI->x;
            for(i= 0; i < quadROI->dx; i++, bP++)
		gray_level[k][(int)(*bP)]++;

	      }
    }

   pass = CVIP_YES;
/***** Sort the 4 most occurring gray levels  ********/
   for(k = 0; k < srcImage->bands; k++) {
        temp[0] = temp[1] = temp[2] = temp[3] = 257;
	for (j = 0; j < 4; j++)
	  {
	   sum = 0;
	  for (i=0; i < 256; i++)
	    {
	    if ((i != temp[0]) && (i != temp[1]) && (i != temp[2]) && (i != temp[3]))
	      if (gray_level[k][highest[k][j]] <= gray_level[k][i])
		highest[k][j] = i;
	    }
	   temp[j] = highest[k][j];
	  /* printf("\nHighest[%d][%d] = %d, gray_level = %d",k,j,highest[k][j],gray_level[k][temp[j]]);*/
	  }
     for (i = 0; i < 256; i++)
	temp[0] += gray_level[k][i]*(abs(i-highest[k][0]));
     if ((float)temp[0]/(float)((quadROI->dx)*(quadROI->dy)) > threshold)
	pass = CVIP_NO;



    }

  if ((pass == CVIP_YES) || (((quadROI->dx)*(quadROI->dy)) < 3))
	{
        for(k=0; k < srcImage->bands; k++)
          quadROI->data[k] = highest[k][0];

        return CVIP_YES;


   }
   else
	{
      return CVIP_NO;
	}
}



static CVIP_BOOLEAN
VarianceTest(
	Image 	*srcImage,
	QUAD 	*quadROI,
	void 	*paramP
)
 {

   register int i, j, k;
   unsigned int yoffset, meansum[3]={0,0,0}, varsum[3]={0,0,0}, mean[3], pass, close_count;
   float stddev[3];
   double temp_d;
   byte *bP=0, *meanP = (byte *)paramP;
   float max_std, percentage, *ftmp = (float *)paramP;
   char *fn = "Variance Test";


   max_std = (float) *ftmp;
   ftmp++;
   percentage = (float) *ftmp;

   yoffset = quadROI->y + quadROI->dy;
   for(k = 0; k < srcImage->bands; k++) {
      for(j = quadROI->y; j < yoffset; j++) {
         bP  = (byte *) srcImage->bandP[k]->rptr[j] + quadROI->x;
            for(i= 0; i < quadROI->dx; i++, bP++)
		{
                meansum[k] += *bP;
		varsum[k] += (*bP)*(*bP);
		}

      }

      	mean[k] = ROUND(((float)meansum[k])/((quadROI->dx)*(quadROI->dy)));
	temp_d = (double)((float) (varsum[k]/((quadROI->dx)*(quadROI->dy))) - (mean[k]*mean[k]));
   	stddev[k] = (float) sqrt((double)(temp_d+.0001));


   }
    pass = 1;
   for(k = 0; k < srcImage->bands; k++) {
      close_count = 0;
      for(j = quadROI->y; j < yoffset; j++) {
         bP  = (byte *) srcImage->bandP[k]->rptr[j] + quadROI->x;
            for(i= 0; i < quadROI->dx; i++, bP++)
		{

		if ((abs(mean[k]-(int)(*bP))) <= (2*stddev[k]))
			close_count++;
             	}

      }

  	temp_d =  (float)(close_count)/(float)((quadROI->dx)*(quadROI->dy));

      	if ( (temp_d <= percentage) || (stddev[k] > (float) max_std))
		pass = 0;


   }
  if ((pass != 0) || (quadROI->dx==2) || (quadROI->dy==2))
	{
        for(k=0; k < srcImage->bands; k++)
          quadROI->data[k] = mean[k];

        return CVIP_YES;


   }
   else
	{
      return CVIP_NO;
	}
}





static CVIP_BOOLEAN
stdDevTest(
	Image 	*imgP,
	QUAD 	*quadP,
	void 	*paramP
)
{

   	register int 	i, j;
   	unsigned int 	yoffset, meansum = (0), varsum = (0),
			no_of_pixels, count_pixels = (0);
	float		var, stddev, mean;
   	byte 		*bP=0, *meanP = (byte *) paramP, bdata;
   	char 		*fn = "mean_test";

   	yoffset = quadP->y + quadP->dy;
      	for(j = quadP->y; j < yoffset; j++) {
         	bP  = (byte *) imgP->bandP[0]->rptr[j] + quadP->x;
            	for(i= 0; i < quadP->dx; i++, bP++) {
			if(*bP) {
				count_pixels++;
               			meansum += *bP;
				varsum	+= (*bP)*(*bP);
			}
		}
     	}

	if(!count_pixels)
		count_pixels = 1;

      	mean 	= ((float)meansum)/count_pixels;
 	var 	= ((float)varsum)/count_pixels - mean*mean;
   	stddev 	= (float) sqrt((double)var);

   	if(stddev < 10.0) {
		bdata = (byte) ROUND(mean);
		if(bdata >= *meanP)
      			quadP->data[0] = 255;
		else
			quadP->data[0] = 1;
      		return CVIP_YES;
   	}
   	else if (quadP->dx==1 || quadP->dy==1) {
      		quadP->data[0] = 0;
      		return CVIP_YES;
   	}
   	else
      		return CVIP_NO;
}

/****************************************************************
                   Name: predicate_test
          Expanded Name: predicate test
             Parameters: <srcImage> - pointer to Image structure
			 <quadROI> - pointer to QUAD structure
			 <paramP> - pointer to any other parameters needed (in
			 this case an array containing the global mean of each
			 data band)
                Returns: CVIP_YES or CVIP_NO.
            Description: example predicate test module to be used with the
			 split_merge_generic(...) routine. This predicate test
			 function will return a value of CVIP_YES if the region
			 pointed to by <quadROI> is completely uniform, and
			 will return a value of CVIP_NO if the region exhibits any
	 		 form of nonuniformity.
			 global mean.
	    Diagnostics: none.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

static CVIP_BOOLEAN
predicate_test(
	Image 	*srcImage,
	QUAD 	*quadROI,
	void 	*paramP
)
{

   register int i, j, k;
   unsigned int yoffset, nonuniform=0;
   byte *bP=0;
   char *fn = "predicate_test";

   yoffset = quadROI->y + quadROI->dy;

   for(k = 0; k < srcImage->bands; k++)
      for(j = quadROI->y; j < yoffset; j++) {
         bP  = (byte *) srcImage->bandP[k]->rptr[j] + quadROI->x;
            for(i= 0; i < quadROI->dx-1; i++, bP++)
               nonuniform += abs(*bP - *(bP+1));
      }

   if( !nonuniform || quadROI->dx==1 || quadROI->dy==1 ) {
      for(k=0; k < srcImage->bands; k++)
         quadROI->data[k] = ((byte **)srcImage->bandP[k]->rptr)[quadROI->y][quadROI->x];
      return CVIP_YES;
   }
   else
      return CVIP_NO;
}


/****************************************************************
                   Name: mean_test
          Expanded Name: mean test
             Parameters: <srcImage> - pointer to Image structure
			 <quadROI> - pointer to QUAD structure
			 <paramP> - pointer to any other parameters needed
			 (none in this case)
                Returns: CVIP_YES or CVIP_NO.
            Description: example predicate test module to be used with the
			 split_merge_generic(...) routine. This predicate test
			 function will return a value of CVIP_YES if the local mean
			 of the region pointed to by <quadROI> is greater than
			 the global mean of <srcImage>, and will return a value
			 of CVIP_NO if the local mean is less than or equal to the
			 global mean.
	    Diagnostics: none.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

static CVIP_BOOLEAN
mean_test(
	Image 	*srcImage,
	QUAD 	*quadROI,
	void 	*paramP
)
{

   register int i, j, k;
   unsigned int yoffset, meansum[3]={0,0,0}, mean[3];
   byte *bP=0, *meanP = (byte *) paramP;
   char *fn = "mean_test";

   yoffset = quadROI->y + quadROI->dy;

   for(k = 0; k < srcImage->bands; k++) {
      for(j = quadROI->y; j < yoffset; j++) {
         bP  = (byte *) srcImage->bandP[k]->rptr[j] + quadROI->x;
            for(i= 0; i < quadROI->dx; i++, bP++)
               meansum[k] += *bP;
      }
      mean[k] = ROUND(((float)meansum[k])/((quadROI->dx)*(quadROI->dy)));
   }

   j=0;
   while( (j<srcImage->bands) && (mean[j] > meanP[j]) ) j++;
   if(j == srcImage->bands) {
      for(k=0; k < srcImage->bands; k++)
         quadROI->data[k] = mean[k];
      return CVIP_YES;
   }
   else if (quadROI->dx==1 || quadROI->dy==1) {
      for(k=0; k < srcImage->bands; k++) quadROI->data[k] = 0;
      return CVIP_YES;
   }
   else
      return CVIP_NO;
}



/****************************************************************
                   Name: split_merge_segment
          Expanded Name: split and merge set-up
             Parameters: <srcImage> - pointer to source Image structure
			 <level> - the level to begin procedure
			 <choice> - Predicate test chosen
				    (1) pure uniformity
			  	    (2) local mean vs. global
				    (3) local std. deviation vs. global mean
				    (4) Number of pixels within 2 x standard deviation
				    (5) Bin test
			<Run_PCT> - Choice to run PCT on color images
			 <parameters> - Cutoff value usage determined by predicate test
                Returns: ponter to Image structure containing segmented
			 image.
            Description: front-end routine for split_merge_generic(...) called by
			 the new CVIPtools program.
	    Diagnostics: same as split_merge_generic(...).
              Credit(s): Steve Costello, Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

Image *
split_merge_segment (
	Image 	*imgP,	/* <srcImage> */
	unsigned int level,
	unsigned int choice,
	void *parameters,
	CVIP_BOOLEAN Run_PCT
)
{
	Image		*smsP, *freP;
   	unsigned int 	meansum[3] = {0,0,0};
   	QUAD_LIST 	listQUAD, quadROI, prevQUAD;
   	register 	int i, j, k;
   	byte 		*bP=0, mean[3];
	float		meanf[3],*ftmp = (float *) parameters;
	char		*command;
	int n=1, m=1;

	smsP = imgP;
	if((getNoOfBands_Image(imgP) > 1) && (Run_PCT == CVIP_YES)) {
		if( (smsP = pct(smsP, CVIP_NO, NULL)) == (Image *) NULL)  {
			error_CVIP("split_merge_segment","could not perform PCT!");
			delete_Image(smsP);
			return (Image *)NULL;;
		}
		(void) cropBands_Image(smsP, 2);
		freP = smsP;
		smsP = remap_Image(smsP, CVIP_BYTE, 0, 255);
		delete_Image(freP);
	}
    // Zero Padding
	while((n<getNoOfRows_Image(smsP))||(m<getNoOfCols_Image(smsP)))
	{
		if(n<getNoOfRows_Image(smsP))
			n*=2;
		if(m<getNoOfCols_Image(smsP))
			m*=2;
	}
	if((n!=getNoOfRows_Image(smsP))||(m!=getNoOfCols_Image(smsP)))
	{
		zero_pad(smsP, n, m);
	}/*end of zero padding*/

	switch(choice)
	{
   	case 1:
   	  /*
   	     pure uniformity:
   	       - the test is considered CVIP_YES if the
   	         region is completely uniform
   	       - the test is considered CVIP_NO if the
   	         region exhibits any nonuniformity
	  */
      		listQUAD = (QUAD_LIST) split_merge_generic(smsP, predicate_test, NULL,level);
		break;
   	case 2:
	  /*
	     local mean vs. global:
   	        - the test is considered CVIP_YES if the
   	          local mean is greater than the global
   	        - the test is considered CVIP_NO if the
   	          local mean is less than or equal to the global
	  */
      		for(k = 0; k < smsP->bands; k++) {
         		for(j = 0; j < smsP->bandP[0]->rows; j++) {
            			bP  = (byte *) smsP->bandP[k]->rptr[j];
               			for(i= 0; i < smsP->bandP[0]->cols; i++, bP++)
                  			meansum[k] += *bP;
         		}
         		mean[k] = (byte ) ROUND(((float)meansum[k])/
                   	((smsP->bandP[0]->rows)*(smsP->bandP[0]->cols)));
      		}
      		listQUAD = (QUAD_LIST) split_merge_generic(smsP, mean_test, mean, level);
   		break;
	case 3:
	  /*
 	     local std. deviation vs. global mean:
   	        - the test is considered CVIP_YES if the
   	          local std. deviation is less than 10% of the global mean\n
   	        - the test is considered CVIP_NO if the
   	          local std. deviation is grater than 10%
	  */
		for(k = 0; k < smsP->bands; k++) {
         		for(j = 0; j < smsP->bandP[0]->rows; j++) {
            			bP  = (byte *) smsP->bandP[k]->rptr[j];
               			for(i= 0; i < smsP->bandP[0]->cols; i++, bP++)
                  			meansum[k] += *bP;
         		}
         		mean[k] = (byte ) ROUND(((float)meansum[k])/
                   	((smsP->bandP[0]->rows)*(smsP->bandP[0]->cols)));
      		}
      		listQUAD = (QUAD_LIST) split_merge_generic(smsP, stdDevTest, mean, level);
		break;
   	case 4:
	  /*
 	     Number of pixels within 2 x standard deviation:
   	        - the test is considered CVIP_YES if at least 80%
   	          of the pixels are within 2 sigma (local) of the mean (local)
   	        - the test is considered CVIP_NO otherwise
	  */
		meanf[0] = *ftmp;
		ftmp++;
		meanf[1] = *ftmp;
      		listQUAD = (QUAD_LIST) split_merge_generic(smsP/*imgP*/, VarianceTest, meanf,level);
		break;
   	case 5:
	  /*
	     Bin test:
   	        - the test is considered CVIP_YES if at least 80%
   	          of the pixels have a gray level within 20 of each other
   	        - the test is considered CVIP_NO otherwise
	  */
		meanf[0] = *ftmp;
    		listQUAD = (QUAD_LIST) split_merge_generic(smsP, BinTest, meanf,level);
		break;
	case 6:
	default:
		meanf[0] = *ftmp;
		ftmp++;
		meanf[1] = *ftmp;
	 	listQUAD = (QUAD_LIST) split_merge_generic(smsP, IDM_Texture_Test, meanf, level);
		break;
	}
  	quadROI = listQUAD;

   	while(quadROI != NULL) {
      		smsP = (Image *) quadtree2ras(smsP, quadROI->q);
      		prevQUAD = quadROI;
      		quadROI = quadROI->next;
      		free(prevQUAD);
   	}

return smsP;
}

/* multiresolution is defined the same as split_merge, only with the
 * level fixed == 0.
 */
Image *
multi_resolution_segment (
	Image    *imgP,   /* <srcImage> */
	unsigned int choice,
	void *parameters,
	CVIP_BOOLEAN Run_PCT
) {
	return split_merge_segment (imgP, 0, choice, parameters, Run_PCT);
}

/****************************************************************
                   Name: split_merge_setup
          Expanded Name: split and merge set-up
             Parameters: <srcImage> - pointer to source Image structure
                Returns: Image * containing segmented image.
            Description: front-end routine for split_merge_segment(...)
									called by the other CVIPtools programs.
	    Diagnostics: same as split_merge_generic(...).
              Credit(s): Gregory Hance, Yansheng Wei
		         Southern Illinois University @ Edwardsville
****************************************************************/

Image *
split_merge_setup (Image 	*imgP)
{
	Image		*smsP, *freP;
   unsigned int 	level, choice;
   char 		command[30];
   const char 	*fn = "split_merge_setup";
   register 	int i, j, k;
	void *  parameter = (void *)malloc(2*sizeof(float));
	CVIP_BOOLEAN Run_PCT = CVIP_NO;

   fprintf(stderr, "\n%s: Enter the level to begin procedure - ", fn);
   level = (unsigned int) atoi(gets(command));

   fprintf(stderr, "%s: Choose a predicate test...\n", fn);
   fprintf(stderr, "%s:\n%s\n", fn,
"   1) Pure Uniformity: region considered homogeneous if \n\
      completely uniform, i.e. all the pixels have the \n\
      same gray value. \n\
   2) Local Mean vs. Global Mean: region is considered\n\
      homogeneous if the local mean is greater than the \n\
      global mean. \n\
   3) Local Standard Deviation vs. Global Mean: region\n\
      is considered homogeneous if the local standard \n\
      deviation is less than 10% of the global mean.\n\
   4) Variance test: region is considered homogeneous if\n\
      at least a given percentage of the pixels are within \n\
      2 sigma of the local mean, unless the standard \n\
      deviation exceeds a maximum threshold. \n\
      Parameters:\n\
   5) Weighted gray level distance: region is considered \n\
      homogeneous if a computed value is less than the \n\
      chosen threshold.\n\
   6) Texture homogeneity: region considered homogeneous\n\
      if computed texture features of all quadrants of the\n\
      region are within the given similarity measure.");

   fprintf(stderr, "%s: Your Choice - ", fn);
   choice = (unsigned int) atoi(gets(command));
   fprintf(stderr, "\n");
	switch (choice) {
		case 1: case 2: case 3:
			*((float *)parameter) = -1;
			*((float *)parameter + 1) = -1;
			break;
		case 4:
			fprintf(stderr, "Input the percentage value:");
			*((float *)parameter) = atof(gets(command));
			fprintf(stderr, "Input the Threshold value:");
			*((float *)parameter + 1) = atof(gets(command));
			break;
		case 5:
			fprintf(stderr, "Input the threshold value:");
			*((float *)parameter) = atof(gets(command));
			*((float *)parameter + 1) = -1;
			break;
		case 6:
			fprintf(stderr, "Input the similarity value:");
			*((float *)parameter) = atof(gets(command));
			fprintf(stderr, "Input the pixel distance:");
			*((float *)parameter + 1) = atof(gets(command));
			break;
		default:
			fprintf(stderr,
				"Incorrect choice: %d, choice 1 is used instead\n", choice);
			*((float *)parameter) = -1;
			*((float *)parameter + 1) = -1;
	}

	smsP = duplicate_Image(imgP);
	if(getNoOfBands_Image(imgP) > 1) {
		fprintf(stderr, "Run PCT (y/n):");
		switch (getchar()) {
			case 'y': case 'Y':
				Run_PCT = CVIP_YES;
				getchar();
				break;
			case 'n': case 'N':
				getchar();
				break;
		}
	}
	return split_merge_segment(smsP, level, choice,
		(void *)parameter, Run_PCT);
}

