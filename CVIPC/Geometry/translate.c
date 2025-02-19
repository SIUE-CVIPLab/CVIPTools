/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: translate.c
*           Description: This file contains two types of functions.
*			 One is to translate image, which moves the origin
*			 of the image and the whole  image to the specified 
*			 position.
*			 The other type is to cut and paste the image, which
*			 moves only a part of the image to the specified 
*			 position.
*			 The function  to implement cut and paste or translate
*			 is actually the same one, translate. It contains
*			 nine arguments:
*			    Image *cvipImage, contains input image data 
*			    CVIP_BOOLEAN do_wrap,  specifies whether to wrap it or
*				not in translate image. If do_wrap is True,
*				then the function will wrap the image.
*			    int y_off, 
*			    int x_off, position to start from. In translate
*				image, this point should be the origin(0,0).
*			    int y_mount,
*			    int x_mount, area of the image that will be moved.
*				In translate image, these two arguments 
*				should be the height and width of the whole 
*				image.
*			    int y_slide, the distance to change in y direction.
*			    int x_slide, the distance to change in x direction.
*			    float fill_out, the value with which to fill the
*			        area left when the original image has been 
*				moved. This argument won't be used when do_wrap 
*				is CVIP_YES.
*			 There are two separate setup functions for two types
*			 of operation, translate_setup and CutPaste_Setup. Both
*			 setups are used in CVIPtools. They act interactively.
*
*
*         Related Files: 
*   Initial Coding Date: Thu Jul 27 16:45:45 CDT 1995
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
 $Log: translate.c,v $
 Revision 1.13  1998/03/30 19:54:40  smakam
 included history stuff in the image

 Revision 1.12  1997/07/23 21:33:12  wzheng
 do_warp -> do_wrap

 Revision 1.11  1997/06/16 19:04:01  yawei
 added cast to translate, so compile on SGI

 Revision 1.10  1997/05/03 00:20:43  yawei
 modified to handle COMPLEX image, and all data types.

 Revision 1.9  1997/03/08 17:07:19  yawei
 Swaped CVIP_YES and CVIP_NO

 Revision 1.8  1997/03/08 01:01:44  yawei
 Name Changes:
 	BOOLEAN ==> CVIP_BOOLEAN
 	FALSE ==> CVIP_NO
 	TRUE ==> CVIP_YES
 	BYTE ==> CVIP_BYTE
 	SHORT ==> CVIP_SHORT
 	INTEGER ==> CVIP_INTEGER
 	FLOAT ==> CVIP_FLOAT
 	DOUBLE ==> CVIP_DOUBLE
 	TYPE ==> CVIP_TYPE

 Revision 1.7  1997/01/15 17:19:55  yawei
 Global Change:  IMAGE ==> Image

 * Revision 1.6  1996/12/17  22:23:10  yawei
 * Changed:
 *  Translate_Image          ==> translate
 *
 * Revision 1.5  1995/07/27  23:06:11  kluo
 * add the header
 *
 * Revision 1.4  1995/07/18  16:03:38  mzuke
 * changesd prompts in
 * translate setup
 *
 * Revision 1.3  1995/07/17  18:58:21  mzuke
 * changed the prompts
 * in CutPaste_Setup
 *
 * Revision 1.2  1995/07/14  20:31:29  kluo
 * add new function
 *
 * Revision 1.1  1995/07/12  02:08:10  kluo
 * Initial revision
 *
****************************************************************************/

#include <CVIPimage.h>
#include <CVIPmatrix.h>
#include <CVIPdef.h>
#include <CVIPgeometry.h>
#include <CVIPhistory.h>
#include <CVIPtyp.h>

Image * CutPaste_Setup(Image *cvipImage){
    int x_off, y_off,x_slide,y_slide,y_mount=-1,x_mount=-1,way;
    float fill_out;

    fflush(stdin);
    printf("\nThe area that you move will be referred to as a 'block'.\n");
    printf("Enter the row of the upper-left pixel of your block: ");
    scanf("%d",&y_off);
    printf("Enter the column of the upper-left pixel of your block: ");
    scanf("%d",&x_off);
    printf("Enter the width of the block: ");
    scanf("%d",&y_mount);
    printf("Enter the height of the block: ");
    scanf("%d",&x_mount);
    printf("Enter the vertical slide (in pixels): ");
    scanf("%d",&y_slide);
    printf("Enter the horizontal slide (in pixels): ");
    scanf("%d",&x_slide);
    printf("\nAfter your block moves, it will leave behind a blank space.\n");
    printf("Enter a constant value (0-255) to use in filling the blank space: ");
    scanf("%f",&fill_out); 
    return translate(cvipImage,CVIP_NO, y_off,x_off,y_mount,x_mount,
			y_slide,x_slide,fill_out);
}

Image * translate_setup(Image *cvipImage){
    int x_off=0, y_off=0,x_slide,y_slide,y_mount,x_mount,way;
    float fill_out;
    CVIP_BOOLEAN  do_wrap = CVIP_YES;
 
    y_mount = cvipImage->bandP[0]->rows;
    x_mount = cvipImage->bandP[0]->cols;
    fflush(stdin);
    printf("\n\t    Translate image\n");
    printf("\n\t1) Wrap image around");
    printf("\n\t2) Fill blank spaces with constant\n");
    printf("\nYour choice: ");
    scanf("%d",&way);
    if(way != 1){
	do_wrap = CVIP_NO;
        printf("\nEnter a constant value (0-255) to use in filling the blank space: ");
        scanf("%f",&fill_out);
    }
    printf("\nEnter the slide amount in vertical direction (in pixels):");
    scanf("%d",&y_slide);
    printf("Enter the slide amount in horizontal direction( in pixels):");
    scanf("%d",&x_slide);
    return translate(cvipImage,do_wrap, y_off,x_off,y_mount,x_mount,
			y_slide,x_slide,fill_out);
}

Image *translate(Image *cvipImage, CVIP_BOOLEAN do_wrap, int y_off, int x_off,
	int y_mount,int x_mount,int y_slide, int x_slide, float fill_out){
    Image *resultImage;
    int rows, cols, bands, no_of_bands,y,x;
    float **imaget,**images, **Iimaget, **Iimages, *datarange, min, max;
    FORMAT format = getDataFormat_Image(cvipImage);
    CVIP_TYPE type = getDataType_Image(cvipImage);
    int x_start,x_end,y_start,y_end;
    int x_final,y_final;
    int i,j;
    HISTORY stuff;

    bands = getNoOfBands_Image(cvipImage);   
    rows =  getNoOfRows_Image(cvipImage);   
    cols =  getNoOfCols_Image(cvipImage);
    y_start = y_off;
    y_end = y_start + y_mount;
    x_start = x_off;
    x_end = x_start + x_mount;
    if(x_end < x_start)
	    SWAP(x_end,x_start);
    if(y_end < y_start)
	    SWAP(y_end,y_start);     
    if(x_start < 0)
	x_start = 0;
    if(x_end >= cols)
	x_end = cols-1;
    if(y_start < 0)
	y_start = 0;
    if(y_end >= rows)
	y_end = rows-1;

    if(type != CVIP_FLOAT){
    	if (!cast_Image(cvipImage, CVIP_FLOAT)) {
		error_CVIP("translate", "image cast failed");
		delete_Image(cvipImage);
		return (Image*)NULL;
	}
    }
    datarange = (float *)getDataRange_Image(cvipImage);
    if (format == COMPLEX) {
	min = datarange[bands*4];
	max = datarange[bands*4+1];
    } else {
	min = datarange[bands*2];
	max = datarange[bands*2+1];
    }
    if (datarange) free(datarange);

    resultImage = duplicate_Image(cvipImage);
    for(no_of_bands=0;no_of_bands < bands;no_of_bands++){
       images = getData_Image(cvipImage,no_of_bands);
       imaget = getData_Image(resultImage,no_of_bands);
       if (format == COMPLEX) {
            Iimages = getImagData_Image(cvipImage,no_of_bands);
            Iimaget = getImagData_Image(resultImage,no_of_bands);
       }
       if(!do_wrap){
          for(y=0;y<rows;y++){
              for(x=0;x<cols;x++){
                 if(y<=y_end&&y>=y_start&&x<=x_end&&x>=x_start)
                 imaget[y][x] = fill_out;
              }
          }
          if (format == COMPLEX) {
              for(y=0;y<rows;y++){
                  for(x=0;x<cols;x++){
                     if(y<=y_end&&y>=y_start&&x<=x_end&&x>=x_start)
                     Iimaget[y][x] = fill_out;
                  }
              }
	  }
        }
        for(y=0;y<rows;y++){
            for(x=0;x<cols;x++){
          	if((!do_wrap)&&(y < y_start || y > y_end)){ continue; }
          	if((!do_wrap)&&(x < x_start || x > x_end)){ continue; }
          	x_final = x + x_slide;
          	y_final = y + y_slide;
          	if(do_wrap == CVIP_YES){
          	    while(x_final < 0) x_final += cols;
          	    while(x_final >= cols) x_final -= cols;
          	    while(y_final < 0) y_final += rows;
          	    while(y_final >= rows) y_final -= rows;
          	    imaget[y_final][x_final] = images[y][x];
          	} else{
          	    if(y_final < rows && y_final >= 0){
          	       if(x_final < cols && x_final >= 0){
          	          imaget[y_final][x_final] = images[y][x];
          	        }
          	    }
          	}
	    }
        }
	if (format == COMPLEX) {
           for(y=0;y<rows;y++){
               for(x=0;x<cols;x++){
             	if((!do_wrap)&&(y < y_start || y > y_end)){ continue; }
             	if((!do_wrap)&&(x < x_start || x > x_end)){ continue; }
             	x_final = x + x_slide;
             	y_final = y + y_slide;
             	if(do_wrap == CVIP_YES){
             	    while(x_final < 0) x_final += cols;
             	    while(x_final >= cols) x_final -= cols;
             	    while(y_final < 0) y_final += rows;
             	    while(y_final >= rows) y_final -= rows;
             	    Iimaget[y_final][x_final] = Iimages[y][x];
             	} else{
             	    if(y_final < rows && y_final >= 0){
             	       if(x_final < cols && x_final >= 0){
             	          Iimaget[y_final][x_final] = Iimages[y][x];
             	        }
             	    }
             	}
   	      }
           }
	}
    }
    delete_Image(cvipImage);
    stuff=(HISTORY)malloc(sizeof(struct history));
    stuff->packetP = (PACKET *)malloc(sizeof(PACKET));
    stuff->packetP->dsize=4;
    stuff->packetP->dtype=(CVIP_TYPE *)malloc(3*sizeof(CVIP_TYPE)+sizeof(CVIP_BOOLEAN));
    stuff->packetP->dtype[0]=CVIP_INTEGER;
    stuff->packetP->dtype[1]=CVIP_INTEGER;
    stuff->packetP->dtype[2]=CVIP_FLOAT;
    stuff->packetP->dtype[3]=CVIP_YES;
    stuff->packetP->dptr = (void**)malloc(sizeof(void*)*stuff->packetP->dsize);
    stuff->packetP->dptr[0]=(void *)malloc(sizeof(int));
    stuff->packetP->dptr[1]=(void *)malloc(sizeof(int));
    stuff->packetP->dptr[2]=(void *)malloc(sizeof(float));
    stuff->packetP->dptr[3]=(void *)malloc(sizeof(CVIP_BOOLEAN));
    memcpy((void *)stuff->packetP->dptr[0], (const void *)&y_slide, sizeof(int));
    memcpy((void *)stuff->packetP->dptr[1], (const void *)&x_slide, sizeof(int));
    memcpy((void *)stuff->packetP->dptr[2], (const void *)&fill_out, sizeof(float));
    memcpy((void *)stuff->packetP->dptr[3], (const void *)&do_wrap, sizeof(CVIP_BOOLEAN));
    stuff->next=(HISTORY)NULL;
    stuff->ftag=TRANSLATE;
    if (type < CVIP_FLOAT) {
      printf("remapped to %f and %f\n", min, max);
      cvipImage = (Image *)remap_Image(resultImage, type,
			(unsigned) min, (unsigned) max);
      if (resultImage) delete_Image(resultImage);
      if(cvipImage) {
    	history_add(cvipImage, stuff);
	stuff=NULL;
	return cvipImage;
      }
    } else {
    	history_add(resultImage, stuff);
	stuff=NULL;
	return resultImage;
      }
}

