/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: hist_slide.c
*           Description: This file contains function for two types of 
*			 operations, histogram shrink(or stretch), histogram
*			 slide.
*			 Histogram shrink and stretch is implemented in
*			 HistMan_Setup, which takes one argument, input
*			 image pointer. It asks for the upper and lower 
*			 limit histogram of the output image, then it 
*			 calls remap_Image to map the image to the destined
*			 histogram range.
*
*			 Histogram slide is implemented in function
*			 hist_slide. There are two arguments:
*			    Image *input, pointer contains image data
*			    int   slide, amount of slide, can be positive
*				or negative. When it is negative, it makes
*				image darker. When it is positive, it makes
*				image brighter.
*			 HistSlide_Setup is a setup function for hist_slide
*			 It acts interactively.
*
*         Related Files: 
*   Initial Coding Date: Thu Jul 27 18:11:42 CDT 1995
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
*  $Log: hist_slide.c,v $
*  Revision 1.10  1997/03/08 00:54:31  yawei
*  Name Changes:
*  	BOOLEAN ==> CVIP_BOOLEAN
*  	FALSE ==> CVIP_NO
*  	TRUE ==> CVIP_YES
*  	BYTE ==> CVIP_BYTE
*  	SHORT ==> CVIP_SHORT
*  	INTEGER ==> CVIP_INTEGER
*  	FLOAT ==> CVIP_FLOAT
*  	DOUBLE ==> CVIP_DOUBLE
*  	TYPE ==> CVIP_TYPE
*
*  Revision 1.9  1997/01/15 17:14:32  yawei
*  Global Change:  IMAGE ==> Image
*
 * Revision 1.8  1996/12/30  19:02:45  yawei
 * filename: hist_man.c ==> hist_slide.c
 *
 * Revision 1.7  1996/12/30  18:48:35  yawei
 * HistSlide_Image ==> hist_slide
 *
 * Revision 1.6  1996/11/07  23:03:29  yawei
 * Moved gray_multiply to graylevel_mod.c
 *
 * Revision 1.5  1996/11/07  21:33:51  yawei
 * Changed function names GrayLin_Setup, GrayLin_Image to gray_multiply_Setup, gray_multiply.
 *
 * Revision 1.4  1995/07/27  23:28:56  kluo
 * add header
 *
 * Revision 1.3  1995/07/23  16:15:03  mzuke
 * changed prompt in GrayLin_Setup
 *
 * Revision 1.2  1995/07/18  20:12:29  kluo
 * add gray scale modification
 *
 * Revision 1.1  1995/07/14  20:31:50  kluo
 * Initial revision
****************************************************************************/
#include <CVIPtoolkit.h>
#include <CVIPimage.h>
#include <CVIPmatrix.h>
#include <CVIPhisto.h>

static int get_extre_data(Image *input, int choice);

Image* hist_slide(Image *input,int slide){
   byte **image;
   int temp;
   int bands,x,y,no_of_bands,rows,cols;

   if(input->bandP[0]->data_type != CVIP_BYTE){
	fprintf(stderr,"This operation requires that input image is CVIP_BYTE\n");
	return NULL;
   }
   no_of_bands = getNoOfBands_Image(input);
   rows = getNoOfRows_Image(input);
   cols = getNoOfCols_Image(input);
   for(bands=0; bands < no_of_bands; bands++){
      image = getData_Image(input, bands);
      for(y=0; y < rows; y++) {
          for(x=0; x < cols; x++) {
              temp=image[y][x];
              temp+=slide;
              if(temp>255)
                 temp=255;
              else if(temp < 0)
                 temp=0;
              image[y][x]=temp;
          }
      }
   }
   return input;
}

static int get_extre_data(Image *input, int choice){
   byte **image;
   int bands,x,y,no_of_bands,rows,cols;
   int result;

   no_of_bands = getNoOfBands_Image(input);
   rows = getNoOfRows_Image(input);
   cols = getNoOfCols_Image(input);
   for(bands=0; bands < no_of_bands; bands++){
      image = getData_Image(input, bands);
      if(bands ==0)
         result=image[0][0];
      for(y=0; y < rows; y++) {
          for(x=0; x < cols; x++) {
             if(choice == 1){
                if(result<(int)image[y][x])
                    result=image[y][x];
	     }
             else{
                if(result>(int)image[y][x])
                    result=image[y][x];
	     }
          }
      }
   }
   return result;
}

Image* HistMan_Setup(Image *input){
   int upper, lower;
   Image *tempImage;
   fflush(stdin);
   if(input->bandP[0]->data_type != CVIP_BYTE){
	fprintf(stderr,"This operation requires that input image is CVIP_BYTE\n");
	return NULL;
   }
   printf("\n\tEnter the upper limit of the desired histogram(1-255):");
   scanf("%d",&upper);
   printf("\tEnter the lower limit of the desired histogram(0-254):");
   scanf("%d",&lower);
   if(upper > 255)
	upper = 255;
   else if(upper < 1)
	upper = 1;
   if(lower < 0)
	lower = 0;
   else if(lower > 254)
	lower = 254;
   tempImage = remap_Image(input,CVIP_BYTE,lower,upper);
   delete_Image(input);
   return tempImage;
}


Image* HistSlide_Setup(Image *input){
   int max,min;
   int slide;
   int up;
   char yes=0;

   if(input->bandP[0]->data_type != CVIP_BYTE){
	fprintf(stderr,"This operation requires that input image is CVIP_BYTE\n");
	return NULL;
   }
   max=255 - get_extre_data(input,1);
   min=get_extre_data(input,0);
   do{
      fflush(stdin);
      printf("\n\t1)Slide up\n\t2)Slide down");
      printf("\n\t   Enter the choice:");
      scanf("%d",&slide); 
      printf("\nEnter the slide value");
      if(slide == 1){
         printf("(max %d without losing information):",max);
         up=1;
      }  
      else{
         max = min;
         printf("(max %d without losing information):",min);
         up= -1;
      }
      scanf("%d",&slide);
      fflush(stdin);
      if(slide > max){
         printf("\nThe value you entered exceeds the maximum limit, which will\n cause the message loss on the input image,\n you still want to continue?(y/n)");
         yes=getchar();
      }
      else
         yes='y';
   }while(yes != 'y');  
   slide *= up ;
   return hist_slide(input,slide);
}
