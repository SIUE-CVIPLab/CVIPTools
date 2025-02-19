/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: unsharp.c
*           Description: the file contains program to implement unsharp mask
*			 The function call takes five arguments
*			    Image *inputImage, image image data
*			    int lower, the lower limit for shrink histogram 
*			    int upper, the upper limit for shrink histogram
*			    float low_clip, % clip low end for hist stretch
*			    float high_clip,% clip high end for hist stretch
* 			 There is a setup function Unsharp_Setup
*
*         Related Files: 
*   Initial Coding Date: Mon Jul 31 12:40:18 CDT 1995
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
** $Log: unsharp.c,v $
** Revision 1.8  1997/03/08 01:03:17  yawei
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
** Revision 1.7  1997/01/15 17:21:04  yawei
** Global Change:  IMAGE ==> Image
**
 * Revision 1.6  1996/12/27  05:32:01  yawei
 * Unsharp_Image ==> unsharp_filter
 *
 * Revision 1.5  1996/12/24  20:23:22  yawei
 * Changed convolve_Image ==> convolve_filter
 *
 * Revision 1.4  1996/11/14  01:48:17  sumbaug
 * Modified the file header to include the % (percent) clip parameters
 * These were added for the new hist_stretch function, so thta the user can
 * specify a percentage of pixels to clip at min and max levels to get
 * a good stretch.
 *
 * Revision 1.3  1996/11/14  00:06:37  yawei
 * Changed Unsharp to take another two parameters (low percent and
 * high percent).
 *
 * Revision 1.2  1995/07/31  17:42:43  kluo
 * add header
 *
*
****************************************************************************/
#include <CVIPtoolkit.h>
#include <CVIPtools.h>
#include <CVIPhisto.h>
#include <CVIPspfltr.h>

Image *unsharp_setup(Image *inputImage){
    int upper, lower;
	 float low_clip, high_clip;
  
    printf("Enter the upper limit for shrink operation:");
    scanf("%d",&upper);
    printf("Enter the lower limit for shrink operation:");
    scanf("%d",&lower);
    printf("Enter the lower clip percentage for stretch operation:");
    scanf("%f",&low_clip);
    printf("Enter the higher clip percentage for stretch operation:");
    scanf("%f",&high_clip);
    return unsharp_filter(inputImage,lower, upper, low_clip, high_clip);
}

Image* unsharp_filter(Image *inputImage, int lower, int upper,
		float low_clip, float high_clip){
    Image *copyImage, *tempImage;
    Matrix *mask;
    
    if(inputImage->bandP[0]->data_type != CVIP_BYTE){
	fprintf(stderr,"Image is remapped into CVIP_BYTE\n");
	copyImage = remap_Image(inputImage,CVIP_BYTE,0,255);
	delete_Image(inputImage);
	inputImage = copyImage;
    }
    copyImage = duplicate_Image(inputImage);
    mask = (Matrix*)get_default_filter(LOWPASS_SPATIAL,3,0);
    printf("\nConvolving image with low pass filter....\n");
    copyImage = (Image*)convolve_filter(copyImage,mask);
    printf("\nShrink image to the range (%d,%d)\n",lower, upper);
    tempImage = remap_Image(copyImage,CVIP_BYTE,lower,upper);
    delete_Image(copyImage);
    copyImage = tempImage;
    printf("\nSubtract remapped image from the original image.");
    tempImage = (Image*)subtract_Image(inputImage,copyImage);
    printf("\nStretch the output image\n");
/*    copyImage = remap_Image(tempImage,CVIP_BYTE,0,255);*/
    copyImage = hist_stretch(tempImage,0,255,low_clip, high_clip);
    delete_Image(tempImage);
    delete_Matrix(mask);
    return copyImage;
}
