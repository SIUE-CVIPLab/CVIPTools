/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: nightvision.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Sat Dec 28 22:31:08 CST 1996
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Unknown
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1996 SIUE - by Scott Umbaugh.
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
** $Log: nightvision.c,v $
** Revision 1.5  1997/03/08 17:06:28  yawei
** Swaped CVIP_YES and CVIP_NO
**
** Revision 1.4  1997/03/08 00:59:59  yawei
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
** Revision 1.3  1997/01/16 21:29:04  yawei
** Global Change:  Image_FORMAT ==> IMAGE_FORMAT
**
 * Revision 1.2  1997/01/15  17:18:04  yawei
 * Global Change:  IMAGE ==> Image
 *
 * Revision 1.1  1996/12/29  04:33:14  yawei
 * Initial revision
 *
*
****************************************************************************/
#include "CVIPtools.h"
#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPimage.h"
#include "CVIPfs.h"
#include "CVIPhisto.h"
#include "threshold.h"
#include "CVIPspfltr.h"

Image* acuity_nightvision_setup(Image *cvipImage)
{
    int choice, threshold;
    char reason;

    fflush(stdin);
    printf("Do you want to view the night vision?(y/n)");
    reason = getchar();
    if(reason == 'y'){
       fflush(stdin);
	fprintf(stdout, "Enter The threshold value:");
	scanf("%d", &threshold);
	
    }
    else{
       fflush(stdin);
       printf("Enter the desired visual acuity\n");
       printf("(E.g.: Enter 50 for 20/50, 20 for 20/20) :");
       scanf("%d",&choice);
    }
    return acuity_nightvision_filter(cvipImage,reason,threshold, choice);
}

Image *acuity_nightvision_filter(Image *cvipImage,char reason, int threshold, 
		int choice){

    IMAGE_FORMAT 	format,format1;     	/* the input image format */
    Image		*cvipImage1;             
    int		done = CVIP_NO,decision,cols,rows;
    Matrix		*outM;
    unsigned int value;

    cols =  getNoOfCols_Image(cvipImage);
    rows =  getNoOfRows_Image(cvipImage);
    outM = get_default_filter(BLUR_SPATIAL,7,0);
    if(reason == 'y'){
       fflush(stdin);
       cvipImage = threshold_segment(cvipImage,threshold,CVIP_YES);
       choice = 6;
       while(choice > 0){
          choice--;
          cvipImage = convolve_filter(cvipImage,outM);
       }
    }
    else{
       fflush(stdin);
       printf("Enter the desired visual acuity\n");
       printf("(E.g.: Enter 50 for 20/50, 20 for 20/20) :");
       scanf("%d",&choice);
       choice = (choice - 20) / 5;
       while(choice > 0){
          choice--;
          cvipImage = convolve_filter(cvipImage,outM);
       }
    }
    if(reason == 'y')
        cvipImage1 = remap_Image(cvipImage,CVIP_BYTE,0,175);
    else
	cvipImage1 = remap_Image(cvipImage,CVIP_BYTE,0,255);
    delete_Image(cvipImage);
    if(reason == 'y'){
       cvipImage = new_Image(PPM,RGB,3,rows,cols,CVIP_BYTE,REAL);
       copy_Matrix(cvipImage1->bandP[0],cvipImage->bandP[1]);
    }
    else{
	cvipImage = cvipImage1;
    }
    return cvipImage;    
} 
  
             
