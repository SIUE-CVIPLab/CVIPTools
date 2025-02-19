/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: CVIP_textureSetUp.c
*           Description: contains supporting routines for Texture Extraction
*         Related Files: cvip_texture.c, CVIPtexture.h
*   Initial Coding Date: July 8 1996
*           Portability: Standard (ANSI) C
*             Credit(s): Steve Costello
*                        Southern Illinois University @ Edwardsville
*
*   GUI_Texture_SetUp() Modified by Wenxing Li on 7/12/1996 for:
*	  add extern TEXTURE * Extract_Texture_Features();
*	  labeled image can only be CVIP_INTEGER image;
* 
*
** Copyright (C) 1996 SIUE - by Steve Costello.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
*
****************************************************************************/
#include "CVIPtoolkit.h"
#include "CVIPdef.h"
#include "CVIPimage.h"
#include "string.h"
#include "math.h"
#include "CVIPsegment.h"
#include "stdio.h"
#include "string.h"
#include "CVIPtexture.h"
#include "CVIPtransform.h"

/****************************************************************
                   Name: texture
             Parameters: <ImgP> - pointer to source IMAGE structure
			 <segP> - pointer to labeled Image structure
			 <band> - the band of the source image to be worked on
			 <r> -  the row co-ordinate of the object
			 <c> -  the columb co-ordinate of the object
			 <hex_equiv> - the hex equivalent of the Texture feature map	
			 <distance> - the pixel distance to calculate the co-occurence matrix
                Returns: pointer to Texture Feature structure (see CVIPtexture.h)
            Description: front-end routine for TextureFeatureExtraction(...) called by
			 the new GUI CVIPtools program.
              Credit(s): Steve Costello
		         Southern Illinois University @ Edwardsville
****************************************************************/

extern TEXTURE * Extract_Texture_Features();

TEXTURE * texture(
	const Image *ImgP,
 	const Image *segP,
	int band,
	int r,
	int c,
	long int hex_equiv,
	int distance
	)
{
// TODO Evan :unsigned char **bP, *iP;
  unsigned char **bP, *iP=0;
  int   * sP;
  int  i,j, row, col, label, not_label=0;
  TEXTURE_FEATURE_MAP tf_usage;
  Image *dupP;
  TEXTURE  * P;

  col = ImgP->bandP[band]->cols;
  row = ImgP->bandP[band]->rows;
  dupP = duplicate_Image(ImgP);

  tf_usage.ASM = (hex_equiv & 0x0001)/0x0001;
  tf_usage.contrast = (hex_equiv & 0x0002)/0x0002;
  tf_usage.correlation= (hex_equiv & 0x0004)/0x0004;
  tf_usage.variance= (hex_equiv & 0x0008)/0x0008;
  tf_usage.IDM = (hex_equiv & 0x0010)/0x0010;
  tf_usage.sum_avg = (hex_equiv & 0x0020)/0x0020;
  tf_usage.sum_var = (hex_equiv & 0x0040)/0x0040;
  tf_usage.sum_entropy = (hex_equiv & 0x0080)/0x0080;
  tf_usage.entropy = (hex_equiv & 0x0100)/0x0100;
  tf_usage.diff_var = (hex_equiv & 0x0200)/0x0200;
  tf_usage.diff_entropy = (hex_equiv & 0x0400)/0x0400;
  tf_usage.meas_corr1 = (hex_equiv & 0x0800)/0x0800;
  tf_usage.meas_corr2 = (hex_equiv & 0x1000)/0x1000;
  tf_usage.max_corr_coef = (hex_equiv & 0x2000)/0x2000;

/* Get the label pointed to by r and c coordinates */
  sP = (int *) segP->bandP[0]->rptr[r];
  sP += c;
  label = *sP;

  bP = (unsigned char **)dupP->image_ptr[band]->rptr;

/* Store only labeled object in the array */
  for(j = 0; j < row; j++) {
	sP = (int *) segP->bandP[0]->rptr[j];
 	for (i=0;i < col; i++, iP++, sP++) { 
		if (*sP != label)   /* if not the labeled object, set to zero */
			bP[j][i] = 0;
 	      	}
	}
 
 P = Extract_Texture_Features(distance, bP, row, col, &tf_usage);
 
 delete_Image(dupP);
 return (P);


}  /*  End of Texture Setup */

