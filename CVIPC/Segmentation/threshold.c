/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: threshold.c
*           Description: it contains the function to threshold a image
*			 threshold_segment. it has one argument, a image
*			 pointer. It will ask for the threshold value
*			 for a input image, then it threshold it, pixels
*			 which have value greater than thresold will be
*			 set to 255, those smaller will be set to zero.
*
*         Related Files: 
*   Initial Coding Date: Mon Jul 31 11:31:56 CDT 1995
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Kun Luo
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1995 SIUE - by Kun Luo.
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
*   $Log: threshold.c,v $
*   
*   Revision1.13   2006/07/25  Wenjun Bian
*   1.//delete "inputImage = duplicate_Image(inputImage);", it is not the right way to duplicate image 
*   2.free memory: 	  free(imgvecP );
*               	  free(new_val);
*   3. the way to invoke remap_Image() will cause memory leak. 
*
*
*   Revision 1.12  1997/03/08 17:01:29  yawei
*   Swaped CVIP_YES and CVIP_NO
*
*   Revision 1.11  1997/03/08 00:44:47  yawei
*   Name Changes:
*   	BOOLEAN ==> CVIP_BOOLEAN
*   	FALSE ==> CVIP_NO
*   	TRUE ==> CVIP_YES
*   	BYTE ==> CVIP_BYTE
*   	SHORT ==> CVIP_SHORT
*   	INTEGER ==> CVIP_INTEGER
*   	FLOAT ==> CVIP_FLOAT
*   	DOUBLE ==> CVIP_DOUBLE
*   	TYPE ==> CVIP_TYPE
*
*   Revision 1.10  1997/01/15 17:09:10  yawei
*   Global Change:  IMAGE ==> Image
*
 * Revision 1.9  1996/12/23  18:38:48  yawei
 * Changed function prototype.
 *
 * Revision 1.8  1996/11/15  20:58:06  yawei
 * Changd binary thresholding so it can output multiband image
 *
 * Revision 1.7  1996/11/15  01:19:48  yawei
 * Changed the thresholding so it works properly.
 * And, it handles any number of bands.
 *
 * Revision 1.6  1996/11/14  04:57:07  yawei
 * Added another parameter threshval_inbyte to threshold_segment.
 * if threshval_inbyte = 1, the threshval is in given in CVIP_BYTE range
 * if threshval_inbyte = 0, the threshval is given in the original data type.
 *
 * Revision 1.5  1995/08/23  17:12:52  akjoele
 * Added a threshold_setup() function.  This enables users to call threshold_segment() and specify the threshold value in the call.
 *
 * Revision 1.4  1995/07/31  16:35:26  kluo
 * add header.
 *
 * Revision 1.3  1995/06/30  18:45:32  kluo
 * check file in
 *
 * Revision 1.2  1995/05/08  20:52:33  luok
 * add header
*
****************************************************************************/
#include <stdio.h>
#include "CVIPtools.h"
#include "CVIPimage.h"
#include "CVIPdef.h"
#include "CVIPmap.h"
#include "limits.h"
#include "threshold.h"
#include <float.h>
Image *threshold_setup(Image *inputImage) {
	unsigned int threshval, thresh_inbyte;
	CVIP_BOOLEAN inbyte;

	fprintf(stdout, "Enter The threshold value:");
	scanf("%d", &threshval);
	fprintf(stdout, "Is the threshold value in CVIP_BYTE (1/0):");
	scanf("%d", &thresh_inbyte);
	inbyte = (thresh_inbyte) ? CVIP_YES : CVIP_NO;
	inputImage=(Image *) threshold_segment(inputImage, threshval, inbyte);
	return(inputImage);
}

Image *threshold_segment(Image *inputImage, int threshval,
	CVIP_BOOLEAN thresh_inbyte)
{
	    Image *temp;
        float            **image,
		 	 /*2-d matrix data pointer */
			*new_val;
		  double min = 0.0, max = 0.0;
		  void     **imgvecP;
		  CVIP_TYPE     dt = getDataType_Image(inputImage);
        int             y,              /* row index */
                        x,              /* column index */
                        i;          /* band index */
 
        unsigned int    rows,           /* number of rows in image */
                        cols,           /* number of columns in image */
                        no_of_bands,    /* number of image bands */
                        imgsize;
		  if (getDataFormat_Image(inputImage) == COMPLEX) return (Image *)NULL;


		  //
		  //inputImage = duplicate_Image(inputImage);
		  if (cast_Image(inputImage, CVIP_FLOAT) == 1) 
                fprintf(stderr,"\nThe input Image is cast into CVIP_FLOAT type\n");

        cols =  getNoOfCols_Image(inputImage);
        rows =  getNoOfRows_Image(inputImage);
		  imgsize = rows * cols;
        no_of_bands = getNoOfBands_Image(inputImage);
		  imgvecP = (void **) malloc(sizeof(void *)*no_of_bands);
		  getBandVector_Image((Image *)inputImage, imgvecP);
		  new_val = (float *) malloc(sizeof(float)* no_of_bands);

		for (i = 0; i < no_of_bands; i++) 	 {
			new_val[i] = threshval;
			if (thresh_inbyte == CVIP_YES) {
				min = findMinVal_Vector(imgvecP[i], imgsize, CVIP_FLOAT);
				max = findMaxVal_Vector(imgvecP[i], imgsize, CVIP_FLOAT);
				new_val[i] = new_val[i] * (max-min) / 255 + min;		
			}

		  printf("Threshval used on the CVIP_BYTE iamge is %10.0f for band %d\n",
			new_val[i], i);
        	image = getData_Image(inputImage,i);

        for(y=0; y < rows; y++) {
                for(x=0; x < cols; x++) {
                        if(image[y][x] > new_val[i]){
                                image[y][x] = 255;
                        }
                        else{ 
                                image[y][x] = 0;
                        }
                }
        }
		}
      fprintf(stderr,"\nThe ouput Image is mapped into CVIP_BYTE type\n");

	  //return (Image *)remap_Image((const Image *)inputImage,CVIP_BYTE,0,255);
	  free(imgvecP );
	  free(new_val);
	  
	  temp=(Image *)remap_Image((const Image *)inputImage,CVIP_BYTE,0,255);
	  delete_Image(inputImage);
	  
	  inputImage=temp;
	  
	  return inputImage;
}
