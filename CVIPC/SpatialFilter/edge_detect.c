/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: edge_detect.c
*           Description: The purpose of this program is to demonsrate various   
*			 techniques used in edge detection.  The techniques
*			 implemented will primarily be spatial domain oriented;
*			 i.e. 2-D convolution using masks.  Note: more info.on
*			 each individual edge detection technique can be        
*			 found at the head of each function.
*			 
*         Related Files: masks.h, Imakefile
*   Initial Coding Date: 1/29/92
*           Portability: Standard (ANSI) C
*             Credit(s): Gregory Hance, Kun Luo
*                        Southern Illinois University @ Edwardsville
*			 Memory Leak checked by Kun Luo
*
** Copyright (C) 1993 SIUE - by Gregory Hance, Kun Luo.
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
** $Log: edge_detect.c,v $
** Revision 1.22  1997/08/06 19:27:58  wzheng
** type cast for all kinds of edge detetors
**
** Revision 1.21  1997/05/18 05:53:32  yawei
** changed IN ==> inMatrix, OUT ==> outMatrix to avoid name
** conflict with WIN32
**
** Revision 1.20  1997/03/08 01:02:53  yawei
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
** Revision 1.19  1997/01/15 17:20:35  yawei
** Global Change:  IMAGE ==> Image
**
 * Revision 1.18  1996/12/30  22:03:15  yawei
 * Changed old style function prototype declaration.
 *
 * Revision 1.17  1996/12/30  21:55:32  yawei
 * Changed old function prototypes to ANSI C format.
 *
 * Revision 1.16  1996/12/24  21:58:22  yawei
 * 1) Changed function names:
 *   edgeDetect_Image ==> edge_detect_setup
 *   edgeDetect_Image_tcl ==> edge_detect_filter
 * 2) Changed other functions to "static"
 *
 * Revision 1.15  1996/12/24  20:22:20  yawei
 * Changed convolve_Image ==> convolve_filter
 *
 * Revision 1.14  1996/11/04  18:41:36  akjoele
 * Removed internal declaration of get_mask() from this file
 * to header file, so it can be called by other functions.
 *
 * Revision 1.13  1996/08/14  22:38:20  wli
 * make program works well when -1 is passed to thresh of edge_detect_filter()
 *
 * Revision 1.12  1996/02/06  17:57:24  mzuke
 * changed prompt at line 220 from 'Do you wish
 * to threshold the result' to 'Do you wish to
 * perform a binary threshold ....'
 *
 * Revision 1.11  1996/01/24  02:46:10  kluo
 * change so that edge detectors can be used by cviptcl
 *
 * Revision 1.10  1995/11/02  14:17:49  akjoele
 * Removed exit () statements, replaced with return(NULL).  Also corrected
 * error messages so they indicate which function is reporting the
 * error.
 *
 * Revision 1.9  1995/09/05  22:16:13  kluo
 * add fflush to change it
 * stop at prompt for threshold
 *
 * Revision 1.8  1995/09/01  00:28:06  kluo
 * change to ask thresold for every value.
 *
 * Revision 1.7  1995/08/30  23:58:58  kluo
 * add robinson, pyramid, extend sobel
 *
 * Revision 1.6  1995/08/23  23:44:21  kluo
 * add kirsch
 *
 * Revision 1.5  1995/03/03  00:44:10  luok
 * add threshold option to the other three edge detection method
 * besides sobel and fri-chen
 *
 * Revision 1.4  1995/02/15  21:28:46  luok
 * fix a lot of memory leaks in this file
 *
 * Revision 1.3  1995/01/14  01:42:59  luok
 * fix the bug where the menu was screwed up. When robert should be called the krish is called instead.
 * it is due to the fact that the program constant is redefined. but
 * in edge_detect it still followed the old convention
 *
 * Revision 1.2  1995/01/14  01:26:18  luok
 * check file into RCS
 *
 * Revision 1.1  1993/06/02  07:54:16  hanceg
 * Initial revision
 *
*
****************************************************************************/
/* Define Preprocessor statements */
#include "CVIPimage.h"
#include "CVIPdef.h"
#include "CVIPfs.h" 
#include <limits.h>
#include "CVIPmap.h" 

static void bubble_sort(float array[], short int n);
static void threshold_image(Image *inputImage,int thres);
static MATRIX *roberts_gradient( MATRIX *Image_ARRAY, int bflg, int choice);
static Image *sobel_Image(Image *cvipImage,int size);
static MATRIX *sobel( MATRIX *Image_ARRAY, int dimension);
static Image *sobel_setup(Image *cvipImage);
static MATRIX *kirsch(MATRIX *inMatrix, KIRSCH_MASK *masks);
static KIRSCH_MASK *create_kirsch_masks(int n, int bias_choice);
static Image *kirsch_edge(Image *inputImage, int interactive);
static MATRIX *frei_chen(MATRIX *inMatrix, int dimension, int bias_choice,
	int proj_choice, int thresh, int threshold);
static Image *robinson_edge(Image *inputImage, int interactive);
static Image * pyramid_Image(Image *cvipImage);


/****************************************************************
                   Name: edge_detection
          Expanded Name: edge detection
             Parameters: <input_Image> - pointer to input Image structure
                Returns: pointer to Image structure containing edge detected
			 Image.
            Description: front-end to the edge detection routines used by
			 the CVIPtools shell interface.
	    Diagnostics: nada.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

Image *edge_detect_setup(Image *imageP, int program)
{
char *choice;
int mask_choice, mask_size;
int bias_choice = 0,proj_choice=0,thresh=0;
int threshold = -1,threshold1=0;


printf("Apply smoothing filter?"); /* give option to first smooth the image */
choice = (char *) malloc(5);
choice = gets(choice);

if( (*choice == 'y') || (*choice == 'Y') )
{
   printf("\nWhich type of smoothing/lowpass filter do\n");
   printf("you wish to implement?\n");
   printf("1) Gaussian blurr filter.\n");
   printf("2) Generic lowpass filter 1.\n");
   printf("3) Generic lowpass filter 2.\n");
   printf("4) Neighborhood average filter.\n");
   printf("Choose(1 <-> 4)?");
   mask_choice = atoi(gets(choice));
}
else
   mask_choice = -1;


/* Decide which technique to implement based on the users specification */

if(program != EDGE_KIRSCH && program != EDGE_ROBINSON && 
	program !=EDGE_PYRAMID){
   printf("Keep D.C. bias?");
   choice = gets(choice);
   if( (*choice == 'y') || (*choice == 'Y') )
      bias_choice++;
}
        
if(program == EDGE_LAPLACIAN) {
   printf("\nDo you wish to use Laplacian mask 1 or 2?\n");
   printf("1 => { {0,-1,0}, {-1,4,-1}, {0,-1,0} }\n");
   printf("2 => { {1,-2,1}, {-2,4,-2}, {1,-2,1} }\n");
   printf("Your choice?"); 
   mask_size = atoi(gets(choice));
}

      


if(program == EDGE_SOBEL) {
    int kernel;

    fflush(stdin);
    while(1){
    	printf("Please enter the kernel dimension(3,5,7 only):");
    	scanf("%d",&kernel);
	if(kernel == 3 || kernel == 5 || kernel == 7)
	    break;
	else
	    fprintf(stderr,"Wrong selection\n");
    }
    mask_size = kernel;
}

if(program == EDGE_ROBERTS){
printf("\nEdge detection:\n");
printf("===============\n");
printf("(1) Regular gradient-\n");
printf("    G[f(x,y)] = {[f(x,y)-f(x+1,y)]^2 + [f(x,y)-f(x,y+1)]^2}^1/2\n");
printf("(2) Robert's gradient-\n");
printf("    G[f(x,y)] = |f(x,y)-f(x+1,y+1)| + |f(x+1,y)-f(x,y+1)|\n");
printf("Choose your gradient(1 or 2)?");
mask_size = atoi(gets(choice));
}


if(program == EDGE_PREWITT) {
   printf("Enter the kernel dimension?");
   mask_size = atoi(gets(choice));
}

if(program == EDGE_FREI) {
   printf("\nChoose the preferred projection:\n");
   printf("===============================\n");
   printf("1) Project onto edge subspace\n");
   printf("2) Project onto line subspace\n");
   printf("3) Show complete projection\n");
   printf("   including average subspace\n");
   printf("Choose (1<->3)?");
   threshold1 = atoi(gets(choice));
   printf("Set a threshold?");
   gets(choice);
   if( (*choice == 'y') || (*choice == 'Y') ) {
      printf("\nChoose one of the following:\n");
      printf("===========================\n");
      printf("1) Set threshold on edge projection\n");
      printf("2) Set threshold on line projection\n");
      printf("3) Smallest angle between the two above\n");
      printf("Choose ( 1<->3)?");
      thresh = atoi(gets(choice));
      if( thresh != 3 ) {
         printf("Enter a threshold for the angle in radians?");
	 proj_choice = atoi(gets(choice));
      }
   }
}
   fflush(stdin);
   printf("\n\nDo you wish to perform a binary threshold on the resulting image?");
   gets(choice);
   if( (*choice == 'y') || (*choice == 'Y') ){
      printf("Choose a threshold?");
      threshold = atoi(gets(choice));
   }

free(choice);
return edge_detect_filter(imageP,program,mask_choice,mask_size,bias_choice,
		threshold,threshold1,thresh,proj_choice);
}


Image *edge_detect_filter(Image *imageP, int program, int mask_choice, 
		int mask_size, int keep_dc, int threshold,
		int threshold1, int thresh,int thr)
{
MATRIX *KERNEL;
MATRIX *temp_MATRIX;
KIRSCH_MASK *masks;
int dimension;
int bias_choice = 0;
Image *cvipImage;

    if(imageP->bandP[0]->data_type < CVIP_SHORT){
        cast_Image(imageP,CVIP_SHORT);
        fprintf(stderr,"Image is cast into CVIP_SHORT");
    }
    else if(imageP->bandP[0]->data_type > CVIP_SHORT){
        cvipImage = (Image*)remap_Image(imageP,CVIP_SHORT,0,255);
        fprintf(stderr,"Image is remapped into CVIP_BYTE");
        delete_Image(imageP);
        imageP = cvipImage;
        cvipImage = NULL;
    }

if (thresh == -1) thresh = 0;

if(mask_choice > 0 && mask_choice < 5)
{
	if (mask_choice == 1)
		mask_choice = 4;
	else if (mask_choice == 4)
		mask_choice = 1;
   KERNEL = get_mask( (MASK_TYPE) (mask_choice-1), 3);
   fprintf(stderr,"\n                            Lowpass Mask:\n");
   fprintf(stderr,"                            ==============");
   matrix_print(KERNEL);

   if(imageP->bands == 1){
      temp_MATRIX = imageP->image_ptr[0]; 
      imageP->image_ptr[0] = convolve(imageP->image_ptr[0], KERNEL);
      delete_Matrix(temp_MATRIX);
   }
   else {
      temp_MATRIX = imageP->image_ptr[0]; 
      imageP->image_ptr[0] = convolve(imageP->image_ptr[0], KERNEL);
      delete_Matrix(temp_MATRIX);
      temp_MATRIX = imageP->image_ptr[1]; 
      imageP->image_ptr[1] = convolve(imageP->image_ptr[1], KERNEL);
      delete_Matrix(temp_MATRIX);
      temp_MATRIX = imageP->image_ptr[2]; 
      imageP->image_ptr[2] = convolve(imageP->image_ptr[2], KERNEL);
      delete_Matrix(temp_MATRIX);
   }
   delete_Matrix(KERNEL);
}


/* Decide which technique to implement based on the users specification */
         
if(program == EDGE_LAPLACIAN) {
   mask_choice = mask_size;
   KERNEL = get_mask( (MASK_TYPE) (LAPLACIAN_MASK+2*mask_choice+keep_dc), 3);
   fprintf(stderr,"\n                    Laplacian Mask:\n");
   fprintf(stderr,"                    ==============");
   matrix_print(KERNEL);
   if(imageP->bands == 1) {
      temp_MATRIX = imageP->image_ptr[0]; 
      imageP->image_ptr[0] = convolve(imageP->image_ptr[0], KERNEL);
      delete_Matrix(temp_MATRIX);
   }
   else {
      temp_MATRIX = imageP->image_ptr[0]; 
      imageP->image_ptr[0] = convolve(imageP->image_ptr[0], KERNEL);
      delete_Matrix(temp_MATRIX);
      temp_MATRIX = imageP->image_ptr[1]; 
      imageP->image_ptr[1] = convolve(imageP->image_ptr[1], KERNEL);
      delete_Matrix(temp_MATRIX);
      temp_MATRIX = imageP->image_ptr[2]; 
      imageP->image_ptr[2] = convolve(imageP->image_ptr[2], KERNEL);
      delete_Matrix(temp_MATRIX);
   }
}

      

if(program == EDGE_ROBERTS) {
   if(keep_dc == 1)
      bias_choice++;
   if(imageP->bands == 1){
      temp_MATRIX = imageP->image_ptr[0];
      imageP->image_ptr[0] = (MATRIX *) roberts_gradient(imageP->image_ptr[0], bias_choice,mask_size);
      delete_Matrix(temp_MATRIX);
   }
   else {
      temp_MATRIX = imageP->image_ptr[0];      
      imageP->image_ptr[0] = (MATRIX *) roberts_gradient(imageP->image_ptr[0], bias_choice,mask_size);
      delete_Matrix(temp_MATRIX);
      temp_MATRIX = imageP->image_ptr[1]; 
      imageP->image_ptr[1] = (MATRIX *) roberts_gradient(imageP->image_ptr[1], bias_choice,mask_size);
      delete_Matrix(temp_MATRIX);
      temp_MATRIX = imageP->image_ptr[2]; 
      imageP->image_ptr[2] = (MATRIX *) roberts_gradient(imageP->image_ptr[2], bias_choice,mask_size);
      delete_Matrix(temp_MATRIX);
   }
}

if(program == EDGE_SOBEL) {
    int warning = 0;
    if(mask_size >=7){
	mask_size = 7;
	warning = 1;
    }
    else if(mask_size >= 5){
	mask_size = 5;
	warning = 1;
    }
    else if(mask_size != 3){
	mask_size = 3;
	warning = 1;
    }
    if(warning)
	fprintf(stderr,"EDGE_SOBEL:kernel size is changed to %d",mask_size);
    imageP = sobel_Image(imageP,mask_size);	
}

if(program == EDGE_PYRAMID){
    imageP = pyramid_Image(imageP);
}

if(program == EDGE_ROBINSON){
    imageP = robinson_edge(imageP,1);
}

if(program == EDGE_KIRSCH){
   imageP = kirsch_edge(imageP,1);
}

if(program == EDGE_PREWITT) {
   dimension = mask_size;
   if(imageP->bands == 1) {
      masks = (KIRSCH_MASK *) create_kirsch_masks(dimension/2,keep_dc); 
      temp_MATRIX = imageP->image_ptr[0]; 
      imageP->image_ptr[0] = (MATRIX *) kirsch(imageP->image_ptr[0], masks);
      delete_Matrix(temp_MATRIX);
   }
   else {
      masks = (KIRSCH_MASK *) create_kirsch_masks(dimension/2,keep_dc);
      temp_MATRIX = imageP->image_ptr[0]; 
      imageP->image_ptr[0] = (MATRIX *) kirsch(imageP->image_ptr[0], masks);
      delete_Matrix(temp_MATRIX);
      temp_MATRIX = imageP->image_ptr[1]; 
      imageP->image_ptr[1] = (MATRIX *) kirsch(imageP->image_ptr[1], masks);
      delete_Matrix(temp_MATRIX);
      temp_MATRIX = imageP->image_ptr[2]; 
      imageP->image_ptr[2] = (MATRIX *) kirsch(imageP->image_ptr[2], masks);
      delete_Matrix(temp_MATRIX);
   }
   free(*(masks->vertical));
   free(masks->vertical);
   free(*(masks->horizontal));
   free(masks->horizontal);
   free(*(masks->diag1));
   free(masks->diag1);
   free(*(masks->diag2));
   free(masks->diag2);
   free(masks);
}

if(program == EDGE_FREI) {
   if(imageP->bands == 1){     
      temp_MATRIX = imageP->image_ptr[0]; 
      imageP->image_ptr[0] = (MATRIX *) frei_chen(imageP->image_ptr[0], 3,keep_dc, threshold1,thresh,thr);
      delete_Matrix(temp_MATRIX);
   }
   else {
      temp_MATRIX = imageP->image_ptr[0]; 
      imageP->image_ptr[0] = (MATRIX *) frei_chen(imageP->image_ptr[0], 3,keep_dc, threshold1,thresh,thr);
      delete_Matrix(temp_MATRIX);
      temp_MATRIX = imageP->image_ptr[1]; 
      imageP->image_ptr[1] = (MATRIX *) frei_chen(imageP->image_ptr[1], 3,keep_dc,threshold1,thresh,thr);
      delete_Matrix(temp_MATRIX);
      temp_MATRIX = imageP->image_ptr[2]; 
      imageP->image_ptr[2] = (MATRIX *) frei_chen(imageP->image_ptr[2], 3,keep_dc,threshold1,thresh,thr);
      delete_Matrix(temp_MATRIX);
   }
}

if(threshold >= 0){
      threshold_image(imageP,threshold);
   }
return imageP;
}







/****************************************************************
   Format: void threshold_image(Image *,int)
   Description: This function is done specifically for edge_detection only.
                It assumed the input is short and is real image.

   Credit: Kun Luo
*****************************************************************/
static void threshold_image(Image *inputImage,int thres){
   int x, y,row,col;
   short **real;
   int band;
   row= inputImage->bandP[0]->rows;
   col= inputImage->bandP[0]->cols;
   for(band=0;band<inputImage->bands;band++){
       real=getData_Image(inputImage,band);
       for(y=0;y<row;y++){
	   for(x=0;x<col;x++){
	       real[y][x]=(real[y][x]<thres)?0:255;
           }
       }
   }
}

/***********************************************************************
* This is real kirsch edge, other ones are for prewitt actually. remember we
* changed original kirsch edge to prewitt edge. Then we added new kirsch
*
* Author Kun Luo
***********************************************************************/
   
   
static Image *kirsch_edge(Image *inputImage, int interactive){
    Image *cvipImage;
    int  mask_array[] = {-3, -3, -3, -3, -3, 5, 5, 5};
    int  convert[] = {0,1,2,7,-1,3,6,5,4};
    int y, x, bands, no_of_bands, rows, cols, sub_y, sub_x;
    short **image, **image_d;
    int seq, order,count, maximum, comp;

    if(inputImage->bandP[0]->data_type < CVIP_SHORT){
	cast_Image(inputImage,CVIP_SHORT);
	fprintf(stderr,"Image is cast into CVIP_SHORT");
    }
    else if(inputImage->bandP[0]->data_type > CVIP_SHORT){
	cvipImage = (Image*)remap_Image(inputImage,CVIP_SHORT,SHRT_MIN,SHRT_MAX);
	fprintf(stderr,"Image is remapped into CVIP_BYTE");
        delete_Image(inputImage);
	inputImage = cvipImage;
	cvipImage = NULL;
    }
    
    cvipImage = (Image*)duplicate_Image(inputImage);
    bands = getNoOfBands_Image(inputImage);   
    rows =  getNoOfRows_Image(inputImage);   
    cols =  getNoOfCols_Image(inputImage);
    if(interactive)
	fprintf(stderr,"\nWe use the following 8 masks:");
    for(no_of_bands=0;no_of_bands<bands;no_of_bands++){
	image = getData_Image(inputImage,no_of_bands);
	image_d = getData_Image(cvipImage,no_of_bands);
    	for(y=1; y<rows-1; y++){
	    for(x=1; x<cols-1; x++){
		maximum = 0;
		for(seq = 0; seq < 8; seq++){
		    count = 0;
		    comp = 0;
		    if(interactive && no_of_bands == 0 && x==1 && y==1)
			fprintf(stderr,"\n\t");
	    	    for(sub_y = y-1; sub_y <= y+1; sub_y++){
			for(sub_x = x-1; sub_x <= x+1; sub_x++){
			    if(interactive && no_of_bands == 0 && x==1&&y==1){
				if(count == 4)
				    fprintf(stderr,"0,\t");
				else
 				    fprintf(stderr,"%d,\t",
				      mask_array[(convert[count]+seq)%8]);
 				if(count == 2 || count == 5 || count ==8)
 				    fprintf(stderr,"\n\t");
			    }
			    if(count != 4){
 			    	comp += mask_array[(convert[count]+seq)%8]
						* image[sub_y][sub_x];
			    }
			    count++;
			}
		    }
		    if(abs(maximum) < abs(comp))
			maximum = comp;
		}
		image_d[y][x] = abs(maximum);
	    }
	}
    }
    fprintf(stderr,"\n");
    (void)delete_Image(inputImage);
    return cvipImage;
}


Image * sobel_setup(Image *cvipImage){
    int kernel;

    fflush(stdin);
    while(1){
    	printf("Please enter the kernel dimension(3,5,7 only):");
    	scanf("%d",&kernel);
	if(kernel == 3 || kernel == 5 || kernel == 7)
	    break;
	else
	    fprintf(stderr,"Wrong selection\n");
    }

    return sobel_Image(cvipImage,kernel);
}

static Image *sobel_Image(Image *cvipImage,int size){
    Image *testImage;
    Matrix *horiz, *vert;
    int x, y, count;
    int rows, cols, no_of_bands, bands;
    int midpoint;
    short ** image_s, **image_d;

    if(cvipImage->bandP[0]->data_type < CVIP_SHORT){
	cast_Image(cvipImage,CVIP_BYTE);
	fprintf(stderr,"Image is cast into CVIP_SHORT\n");
    }
    else if(cvipImage->bandP[0]->data_type > CVIP_SHORT){
	testImage = (Image*)remap_Image(cvipImage,CVIP_SHORT,SHRT_MIN, SHRT_MAX);
	fprintf(stderr,"Image is remapped into CVIP_SHORT\n");
	delete_Image(cvipImage);
	cvipImage = testImage;
    }
   
    horiz = new_Matrix(size, size, CVIP_FLOAT, REAL);
    midpoint = size/2;
    for(y=0;y<size;y++){
	for(x=0;x<size;x++){
	    if(x<midpoint && y< midpoint)
		setRealVal_Matrix(horiz,float,y,x,-1);
	    else if(y == midpoint)
		setRealVal_Matrix(horiz,float,y,x,0);
	    else if(x < midpoint && y > midpoint)
		setRealVal_Matrix(horiz,float,y,x,1);
	    else if(x == midpoint && y < midpoint)
		setRealVal_Matrix(horiz,float,y,x,-2);
	    else if(x == midpoint && y > midpoint)
		setRealVal_Matrix(horiz,float,y,x,2);
	    else if(x > midpoint && y < midpoint)
		setRealVal_Matrix(horiz,float,y,x,-1);
	    else if(x > midpoint && y > midpoint)
		setRealVal_Matrix(horiz,float,y,x,1);
	}
    } 
    vert = transpose_Matrix(horiz);
    print_Matrix(horiz);
    print_Matrix(vert);
    testImage = duplicate_Image(cvipImage);
    cvipImage = convolve_filter(cvipImage,horiz);
    testImage = convolve_filter(testImage,vert);
    rows = cvipImage->bandP[0]->rows;
    cols = cvipImage->bandP[0]->cols;
    no_of_bands = cvipImage->bands;
    
    for(bands = 0; bands< no_of_bands;bands++){
	image_s = getData_Image(cvipImage,bands);
	image_d = getData_Image(testImage,bands);
	for(y = 0; y< rows; y++){
	    for(x = 0; x < cols; x++){
			image_d[y][x] = sqrt((image_d[y][x]*image_d[y][x])+(image_s[y][x]*image_s[y][x]));
		/*if(abs(image_s[y][x]) > abs(image_d[y][x]))
		    image_d[y][x] = abs(image_s[y][x]);
		else
		    image_d[y][x] = abs(image_d[y][x]);*/
	    }
	}
    }
    delete_Image(cvipImage);
    delete_Matrix(horiz);
    delete_Matrix(vert);

    return testImage;
}

static Image * pyramid_Image(Image *cvipImage){
    Image *testImage;
    Matrix *horiz, *vert;
    int x, y, count;
    int rows, cols, no_of_bands, bands;
    int midpoint;
    short ** image_s, **image_d;

    if(cvipImage->bandP[0]->data_type < CVIP_SHORT){
	cast_Image(cvipImage,CVIP_BYTE);
	fprintf(stderr,"Image is cast into CVIP_SHORT\n");
    }
    else if(cvipImage->bandP[0]->data_type > CVIP_SHORT){
	testImage = (Image*)remap_Image(cvipImage,CVIP_SHORT,SHRT_MIN, SHRT_MAX);
	fprintf(stderr,"Image is remapped into CVIP_SHORT\n");
	delete_Image(cvipImage);
	cvipImage = testImage;
    }
   
    horiz = new_Matrix(7, 7, CVIP_FLOAT, REAL);
    midpoint = 3;
    for(y=0;y<7;y++){
	for(x=0;x<7;x++){
	    if( x < midpoint)
		setRealVal_Matrix(horiz,float,y,x,1);
	    if( x > midpoint)
		setRealVal_Matrix(horiz,float,y,x,-1);
	    if( (x == 1 || x == 2) && (y > 0 && y < 6))
		setRealVal_Matrix(horiz,float,y,x,2);
	    if( (x == 4 || x == 5) && (y > 0 && y < 6))
		setRealVal_Matrix(horiz,float,y,x,-2);
	    if( x == 2 && (y > 1 && y < 5))
		setRealVal_Matrix(horiz,float,y,x,3);
	    if( x == 4 && (y > 1 && y < 5))
		setRealVal_Matrix(horiz,float,y,x,-3);
	    if(x == 3)
		setRealVal_Matrix(horiz,float,y,x,0);
	}
    } 
    vert = transpose_Matrix(horiz);
    print_Matrix(horiz);
    print_Matrix(vert);
    testImage = duplicate_Image(cvipImage);
    cvipImage = convolve_filter(cvipImage,horiz);
    testImage = convolve_filter(testImage,vert);
    rows = cvipImage->bandP[0]->rows;
    cols = cvipImage->bandP[0]->cols;
    no_of_bands = cvipImage->bands;
    
    for(bands = 0; bands< no_of_bands;bands++){
	image_s = getData_Image(cvipImage,bands);
	image_d = getData_Image(testImage,bands);
	for(y = 0; y< rows; y++){
	    for(x = 0; x < cols; x++){
		if(abs(image_s[y][x]) > abs(image_d[y][x]))
		    image_d[y][x] = abs(image_s[y][x]);
		else
		    image_d[y][x] = abs(image_d[y][x]);
	    }
	}
    }
    delete_Image(cvipImage);
    delete_Matrix(horiz);
    delete_Matrix(vert);

    return testImage;
}




static Image *robinson_edge(Image *inputImage, int interactive){
    Image *cvipImage;
    int  mask_array[] = {0,-1,-2,-1,0,1,2,1};
    int  convert[] = {0,1,2,7,-1,3,6,5,4};
    int y, x, bands, no_of_bands, rows, cols, sub_y, sub_x;
    short **image, **image_d;
    int seq, order,count, maximum, comp;

    if(inputImage->bandP[0]->data_type < CVIP_SHORT){
	cast_Image(inputImage,CVIP_SHORT);
	fprintf(stderr,"Image is cast into CVIP_SHORT");
    }
    else if(inputImage->bandP[0]->data_type > CVIP_SHORT){
	cvipImage = (Image*)remap_Image(inputImage,CVIP_SHORT,SHRT_MIN,SHRT_MAX);
	fprintf(stderr,"Image is remapped into CVIP_BYTE");
        delete_Image(inputImage);
	inputImage = cvipImage;
	cvipImage = NULL;
    }
    
    cvipImage = (Image*)duplicate_Image(inputImage);
    bands = getNoOfBands_Image(inputImage);   
    rows =  getNoOfRows_Image(inputImage);   
    cols =  getNoOfCols_Image(inputImage);
    if(interactive)
	fprintf(stderr,"\nWe use the following 8 masks:");
    for(no_of_bands=0;no_of_bands<bands;no_of_bands++){
	image = getData_Image(inputImage,no_of_bands);
	image_d = getData_Image(cvipImage,no_of_bands);
    	for(y=1; y<rows-1; y++){
	    for(x=1; x<cols-1; x++){
		maximum = 0;
		for(seq = 0; seq < 8; seq++){
		    count = 0;
		    comp = 0;
		    if(interactive && no_of_bands == 0 && x==1 && y==1)
			fprintf(stderr,"\n\t");
	    	    for(sub_y = y-1; sub_y <= y+1; sub_y++){
			for(sub_x = x-1; sub_x <= x+1; sub_x++){
			    if(interactive && no_of_bands == 0 && x==1&&y==1){
				if(count == 4)
				    fprintf(stderr,"0,\t");
				else
 				    fprintf(stderr,"%d,\t",
				      mask_array[(convert[count]+seq)%8]);
 				if(count == 2 || count == 5 || count ==8)
 				    fprintf(stderr,"\n\t");
			    }
			    if(count != 4){
 			    	comp += mask_array[(convert[count]+seq)%8]
						* image[sub_y][sub_x];
			    }
			    count++;
			}
		    }
		    if(abs(maximum) < abs(comp))
			maximum = comp;
		}
		image_d[y][x] = abs(maximum);
	    }
	}
    }
    fprintf(stderr,"\n");
    (void)delete_Image(inputImage);
    return cvipImage;
}




      
/****************************************************************
                   Name: get_mask
          Expanded Name: get mask
             Parameters: <dimension> - dimension of mask kernel (e.g. 3 => 3x3)
			 <MASK_TYPE> - an enumerated data type indicating which
			 mask to fetch from masks.h
                Returns: pointer to MATRIX structure
            Description: creates a new instance of a MATRIX structure
			 containing a mask kernel from the kernels defined
			 above.
	    Diagnostics: none.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/


MATRIX *get_mask(MASK_TYPE type, int dimension)
{
   MATRIX *KERNEL;
   float **kernel;
   int x, y, count=0;

   KERNEL = matrix_allocate(dimension, dimension, CVIP_FLOAT, REAL);   
   kernel = (float **) KERNEL->rptr;

   if(dimension == 3) {
      for (y=0; y < KERNEL->rows; y++)
         for (x=0; x < KERNEL->cols; x++) {
            kernel[y][x] = MASK3x3[type].kernel[count];
            count++;
	 }
   }
   else if(dimension == 5) {
      for (y=0; y < KERNEL->rows; y++)
         for (x=0; x < KERNEL->cols; x++) {
            kernel[y][x] = MASK5x5[type].kernel[count];
            count++;
	 }
   }
   else {
      fprintf(stderr, "The mask size %d is not supported\n", dimension);
      return(NULL);
   }
   return(KERNEL);
}


/****************************************************************
                   Name: roberts_gradient
          Expanded Name:      "
             Parameters: <Image_ARRAY> - MATRIX pointer pointing to one band
			 of image data
              		 <bflg> - a flag indicating whether to keep the D.C.
			 bias
                Returns: pointer to MATRIX structure.
            Description: using Robert's edge finding technique
	    Diagnostics: nada
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

   
static MATRIX *roberts_gradient( MATRIX *Image_ARRAY, int bflg, int choice) {
MATRIX *outMatrix;
int x, y;
long edge1, edge2;
short int *inptr1, *inptr2, *outptr;
char *string;

outMatrix = matrix_allocate(Image_ARRAY->rows, Image_ARRAY->cols, Image_ARRAY->data_type, REAL);

inptr2 = (short int *) Image_ARRAY->rptr[0];
for (y=1; y < (Image_ARRAY->rows); y++) {            /* Loop 'de loop */
   if(y%16 == 0) fprintf(stderr," .");
   inptr1 = inptr2;
   inptr2 = (short int *) Image_ARRAY->rptr[y];
   outptr = (short int *) outMatrix->rptr[y-1];

   if (choice == 2)
   {
     for (x=0; x <Image_ARRAY->cols-1; x++) {         /* Loop 'de loop 'de la */
         if ((inptr1[x] + inptr1[x+1] + inptr2[x] + inptr2[x+1])){
            edge1 = inptr1[x] - inptr2[x+1]; /* Robert's gradient */
            if (edge1 < 0)
               edge1 = -edge1;
            edge2 = inptr2[x] - inptr1[x+1];
            if (edge2 < 0)
               edge2 = -edge2;
            if(bflg)
               outptr[x] = edge1 + edge2 + inptr1[x];
	    else
	       outptr[x] = edge1 + edge2;
         }
      }
   }
   else
   {
     for (x=0; x <Image_ARRAY->cols-1; x++) {         /* Loop 'de loop 'de la */
        if ((inptr1[x] + inptr1[x+1] + inptr2[x] + inptr2[x+1]))
        {
           edge1  = inptr1[x] - inptr2[x+1]; /* Regular gradient */
           edge1  = edge1*edge1;
           edge2  = inptr2[x] - inptr1[x+1];
           edge2  = edge2*edge2;
           if(bflg)
              outptr[x] =(int) (sqrt((double) (edge1 + edge2)) + 0.5) + inptr1[x];
	   else
	      outptr[x] =(int) (sqrt((double) (edge1 + edge2)) + 0.5);
        }
     }
   }
}
printf("\n");
return(outMatrix);
}



/****************************************************************
                   Name: sobel
          Expanded Name:  "
             Parameters: <Image_ARRAY> - MATRIX pointer pointing to one band
			 of image data
         		 <dimension> - dimension of the filter kernel
			 - (not used yet )
                Returns: pointer to MATRIX structure.
            Description: using Sobel's edge finding technique
	    Diagnostics: nada
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/


static MATRIX *sobel( MATRIX *Image_ARRAY, int dimension)
{

  MATRIX    *outMatrix, *VS, *HS, *KERNEL;  
  short int *out, *vs, *hs;
  float **kernel;
  int       i, j, threshold, bias_choice=0, thresh_choice=0;
  short int  temp1, temp2, min, max;
  double    avg, size;
  char *choice;


  if (Image_ARRAY->data_type != CVIP_SHORT){
    printf("\nError:  Input file is not of integer type.\n");
    return(NULL);
  }

  size = (double) Image_ARRAY->rows * (double) Image_ARRAY->cols;


   outMatrix = Image_ARRAY;

/* Vertical Sobel Operator */
   KERNEL = (MATRIX *) get_mask(SOB_V, dimension);
   
   printf("Keep D.C. bias?");
   choice = (char *) malloc(5);
   choice = gets(choice);
   if( (*choice == 'y') || (*choice == 'Y') )
      bias_choice++;
   
   if(bias_choice) {
      kernel = (float **) KERNEL->rptr;
      kernel[1][1] += 1.0;
   }

   printf("\n                        Vertical Sobel Operator:\n");
   printf("                        =======================\n");   
   matrix_print(KERNEL);
   
   
/* Convolve the smoothed matrix with the vertical Sobel kernel */
   VS = convolve(outMatrix, KERNEL);
   delete_Matrix(KERNEL);

/* Horizontal Sobel Operator */
   KERNEL = (MATRIX *) get_mask(SOB_H, dimension);
   
   if(bias_choice) {
      kernel = (float **) KERNEL->rptr;
      kernel[1][1] += 1.0;
   }
   
   printf("\n                        Horizontal Sobel Operator:\n");
   printf("                        =========================\n");
   matrix_print(KERNEL);
   
   printf("\n\nDo you wish to threshold the result?");
   choice = gets(choice);
   if( (*choice == 'y') || (*choice == 'Y') )
      thresh_choice++;
   
/* Convolve the smoothed matrix with the horizontal Sobel kernel */
  HS = convolve(outMatrix, KERNEL);

/*  Take the larger of the magnitudes of the two matrices,
  over write the outMatrix matrix with the result,  while finding
  the min, max and average gradient values */

  min = 10000;
  max = 0;
  avg = 0.0;
  for (i=0; i < HS->rows; i++){
    hs  = (short int *)HS->rptr[i];
    vs = (short int *)VS->rptr[i];
    out = (short int *)outMatrix->rptr[i];
    for (j=0; j < HS->cols; j++){
      temp1 = abs(hs[j]);
      temp2 = abs(vs[j]);
      temp1 = temp1 > temp2 ? temp1 : temp2;
       if(thresh_choice) {
          min = (temp1<min) ? temp1 : min;
          max = (temp1>max) ? temp1 : max;
          avg += temp1;
       }
      out[j] = temp1;
    }
  }

   avg = avg/size;

/* Compare the magnitudes of the edges to a threshold */
if(thresh_choice) {
  printf("\nThe min, max and average of the gradients are:\n");
  printf("  Min = %8d\n", min);
  printf("  Max = %8d\n", max);
  printf("  Avg = %8.1f\n", avg);


 /* Get the threshold value as a user input */
  printf("Choose a threshold?");
  threshold = atoi(gets(choice));

/* Compare each edge value in the edge matrix with the user supplied
   threshold and create detection matrix (white on black) */

  for (i=0; i < outMatrix->rows; i++){
     out = (short int *)outMatrix->rptr[i];
     for (j=0; j < outMatrix->cols; j++)
        out[j] = (out[j] > threshold) ? 255 : 0;
   }
}
delete_Matrix(KERNEL);
delete_Matrix(HS);
delete_Matrix(VS);
free (choice);
return(outMatrix);
}


/****************************************************************
                   Name: create_kirsch_masks
          Expanded Name: create kirsch masks
             Parameters: <n> - dimension of Kirsh kernel divided by two minus
			 the remainder (e.g. n for a 3x3 kernel would be 1)
                Returns: pointer to KIRSCH_MASK structure
            Description: creates a Kirsch mask of a given size
	    Diagnostics: nada
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/


static KIRSCH_MASK *create_kirsch_masks(int n, int bias_choice)
{
   KIRSCH_MASK *masks;
   MATRIX *H, *V, *D1, *D2;
   int y, x, dim;
   short int *inptr;
   
   masks = (KIRSCH_MASK *) calloc(1,sizeof(KIRSCH_MASK)); /* see masks.h */
   masks->n = n;  

   dim = n*2 + 1;
     
   H = (MATRIX *) matrix_allocate(dim, dim, CVIP_SHORT, REAL ); 
   V = (MATRIX *) matrix_allocate(dim, dim, CVIP_SHORT, REAL );
   D1 = (MATRIX *) matrix_allocate(dim, dim, CVIP_SHORT, REAL );
   D2 = (MATRIX *) matrix_allocate(dim, dim, CVIP_SHORT, REAL );
   
   
   for(y=0; y < dim; y++)  {
      inptr = (short int *) H->rptr[y];      
      for(x=0; x < dim; x++) {
         if(x <  n)
	    *inptr = -1;
	 else if(x == n) {
	    *inptr = 0;
	    if( (y==n) && bias_choice)
	       *inptr = 1;
	  }
	 else
	    *inptr = 1;
	 inptr++;
      }
    }  
    masks->vertical = (short **) H->rptr;
                                          /* create horizontal edge template */
    printf("\nHorizontal edge template:\n");
    printf("========================\n");
    matrix_print(H);
    
    
    for(y=0; y < dim; y++)  {
      inptr = (short int *) V->rptr[y];      
      for(x=0; x < dim; x++) {
         if(y <  n)
	    *inptr = 1;
	 else if(y == n) {
	    *inptr = 0;
	    if( (x==n) && bias_choice )
	       *inptr = 1;
	 }
	 else
	    *inptr = -1;
	 inptr++;
      }
    }  
    masks->horizontal = (short **) V->rptr;
                                            /* create vertical edge template */
    printf("\nVertical edge template:\n");
    printf("========================\n");
    matrix_print(V);
    
    for(y=0; y < dim; y++)  {
      inptr = (short int *) D1->rptr[y];      
      for(x=0; x < dim; x++) {
         if( x > y )
	    *inptr = 1;
	 else if( x < y )
	    *inptr = -1;
	 else {
	    *inptr = 0;
	    if( (x==n) && (y==n) && bias_choice )
	       *inptr = 1;
	 }
	 inptr++;
      }
    }  
    masks->diag1 = (short **) D1->rptr;
                                      /* create first diagonal edge template */
    printf("\nSW <-> NE edge template:\n");
    printf("========================\n");
    matrix_print(D1);

  
    for(y=0; y < dim; y++)  {
      inptr = (short int *) D2->rptr[y];      
      for(x=0; x < dim; x++) {
         if( x < (dim -1 -y) )
	    *inptr = 1;
	 else if(x > (dim -1 -y) )
	    *inptr = -1;
	 else {
	    *inptr = 0;
	    if( (x==n) && (y==n) && bias_choice )
	       *inptr = 1;
	 }
	 inptr++;
      }
    }  
    masks->diag2 = (short **) D2->rptr;
                                    /* create second diagonal edge template */
    printf("\nSE <-> NW edge template:\n");
    printf("========================\n");
    matrix_print(D2);
    free(H);
    free(V);
    free(D1);
    free(D2);
    return(masks);
    
}


/****************************************************************
                   Name: kirsch
          Expanded Name:  "
             Parameters: <inMatrix> - MATRIX pointer pointing to one band of
			 image data
			 <masks> - pointer to KIRSCH_MASK structure
                Returns: pointer to MATRIX structure.
            Description: uses Kirsch's edge finding technique.
	    Diagnostics: nada.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/


static MATRIX *kirsch(MATRIX *inMatrix, KIRSCH_MASK *masks)
{
  MATRIX    *outMatrix;
  short int *v, *h, *d1, *d2;
  
  int       row, column, i, j, normal_factor;
  int       kernel_rows, kernel_cols, dead_rows, dead_cols;
  short int *outptr, *inptr;
  float  sumval[4];

/* Both matrices must be integer type */

  if (inMatrix->data_type != CVIP_SHORT){
    printf("\nError: Input matrix in Kirsch is not CVIP_SHORT type\n");
    return(NULL);
  }


/* Allocate memory for the output matrix */

  outMatrix = matrix_allocate(inMatrix->rows, inMatrix->cols, inMatrix->data_type, inMatrix->data_format);  


/* Set the size of the kernel rows and columns */ 
  kernel_rows = masks->n*2 + 1;
  kernel_cols = masks->n*2 + 1;

  dead_rows = kernel_rows/2;
  dead_cols = kernel_cols/2;
  
/* Calculate the normalization factor for the kernel matrix */
   normal_factor = 1;


/* Make sure the normalization factor is not 0 */
  if(!normal_factor) normal_factor = 1;

  fprintf(stderr, "\n\n");
  fprintf(stderr, "Convolving... ");
  for (row=0; row<(inMatrix->rows)-kernel_rows+1; row++){

    if(row%16 == 0) fprintf(stderr, "%4d",row);

    outptr = (short int *) outMatrix->rptr[row+dead_rows];
    for (column=0; column<(inMatrix->cols)-kernel_cols+1; column++){

    for(i=0; i < 4; i++) 
      sumval[i] = 0;
      for (i=0; i<kernel_rows; i++){
        inptr = (short int *) inMatrix->rptr[i+row];     /* row offset */
        inptr = inptr + column;                   /* col offset */
        v = (short int *) masks->vertical[i];
	h = (short int *) masks->horizontal[i];
	d1 = (short int *) masks->diag1[i];
	d2 = (short int *) masks->diag2[i];
	for (j=0; j<kernel_cols; j++) {
          sumval[0]  += (*inptr) * (*v++);
	  sumval[1]  += (*inptr) * (*h++);
	  sumval[2]  +=(*inptr) * (*d1++);
          sumval[3]  += (*inptr) * (*d2++);
          inptr++;
        }
      }
      for(i=0; i < 4; i++) 
         sumval[i] = abs(sumval[i]);

      bubble_sort(sumval, 4);            

      outptr[column+dead_cols] = ROUND( sumval[0]/normal_factor );
      
    }
  }
  printf("\n");

  return(outMatrix);  
}

/*
 * bubble sort function - I'm not sure where it's used but I'll keep it around!
 */

static void bubble_sort(float array[], short int n)
{
   float *array_o, *temp2;
   float temp1;
   int i;

   array_o = array;

   do {
       temp1 = *array_o;
       array = array_o;
       for( i=1; i < n; i++) {
         temp2 = array;
         if( *temp2 < *(++array) ) {
            temp1 = *array;
            *array = *temp2;        
            *temp2 = temp1;
            }
      }
   }
   while(temp1 != *array_o);
 
}


/****************************************************************
                   Name: frei_chen
          Expanded Name: frei chen
             Parameters: <inMatrix> - MATRIX pointer pointing to one band of
			 image data
 			 <dimension> - dimension of edge kernel
			 - (not currently used)
                Returns: pointer to MATRIX structure
            Description: uses Frei and Chen's edge finding technique.
	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

static MATRIX *frei_chen(MATRIX *inMatrix, int dimension, int bias_choice,
	int proj_choice, int thresh, int threshold)
{
  MATRIX    *outMatrix, *W1_E, *W2_E, *W3_E, *W4_E, *W5_L, *W6_L, *W7_L, *W8_L,*W9_A;  
  int       row, column, i, j, normal_factor;
  int       kernel_rows, kernel_cols, dead_rows, dead_cols;
  short int *outptr, *inptr;
  float  sumval[9],  *w1_e, *w2_e, *w3_e, *w4_e, *w5_l, *w6_l, *w7_l, *w8_l,*w9_a;
  float sum_e_total, sum_l_total, **kernel_ptr;
  double theta_e, theta_l, theta_a, mag_e, mag_l, mag_total, mag, theta_l_count=0, theta_e_count=0, size;
  char *choice, *module_name = "frei_chen";

  double angle;

  angle = (double)threshold * 3.14f / 180.0f;

/* Both matrices must be integer type */

  if (inMatrix->data_type != CVIP_SHORT){
    printf("\nError: Input matrix in frei-chen is not CVIP_SHORT type\n");
    return(NULL);
  }

  size = (double) inMatrix->rows * (double) inMatrix->cols;

/* Allocate memory for the output matrix */


   
   if(    ( (proj_choice == 1) && ( (thresh == 2) || (thresh == 3) ) )
       || ( (proj_choice == 2) && ( (thresh == 1) || (thresh == 3) ) )   ) 
      printf("%s: A nonsensical choice! Who knows what will happen?\n", module_name);
      
  outMatrix = matrix_allocate(inMatrix->rows, inMatrix->cols, inMatrix->data_type, inMatrix->data_format);  

if( (proj_choice == 1) || (proj_choice == 3) || thresh) {
  W1_E = (MATRIX *) get_mask(W1, dimension);
  
  if(bias_choice) {
     kernel_ptr = (float **) W1_E->rptr;
     kernel_ptr[1][1] += 1.0;
  }
  printf("\n                       Vertical edge template:\n");
  printf("                       ======================\n");
  matrix_print(W1_E);
}

if( (proj_choice == 1) || (proj_choice == 3) || thresh) {  
  W2_E = (MATRIX *) get_mask(W2, dimension);
  
  if(bias_choice) {
     kernel_ptr = (float **) W2_E->rptr;
     kernel_ptr[1][1] += 1.0;
  }
  printf("\n                       Horizontal edge template:\n");
  printf("                       ========================\n");
  matrix_print(W2_E);
}


if( (proj_choice == 1) || (proj_choice == 3) || thresh) {  
  W3_E = (MATRIX *) get_mask(W3, dimension);
  
  if(bias_choice) {
     kernel_ptr = (float **) W3_E->rptr;
     kernel_ptr[1][1] += 1.0;
  }  
  printf("\n                       Diagonal edge template:\n");
  printf("                       =======================\n");
  matrix_print(W3_E);
}


if( (proj_choice == 1) || (proj_choice == 3) || thresh) {  
  W4_E = (MATRIX *) get_mask(W4, dimension);
  
  if(bias_choice) {
     kernel_ptr = (float **) W4_E->rptr;
     kernel_ptr[1][1] += 1.0;
  }  
  printf("\n                       Diagonal edge template:\n");
  printf("                       =======================\n");
  matrix_print(W4_E);
}

  
if( (proj_choice == 2) || (proj_choice == 3) || thresh) {
  W5_L = (MATRIX *) get_mask(W5, dimension);
  
  if(bias_choice) {
     kernel_ptr = (float **) W5_L->rptr;
     kernel_ptr[1][1] += 1.0;
  }  
  printf("\n                         Line template #1:\n");
  printf("                         ================\n");
  matrix_print(W5_L);
}

  
if( (proj_choice == 2) || (proj_choice == 3) || thresh) {  
  W6_L = (MATRIX *) get_mask(W6, dimension);
  
  if(bias_choice) {
     kernel_ptr = (float **) W6_L->rptr;
     kernel_ptr[1][1] += 1.0;
  }  
  printf("\n                         Line template #2:\n");
  printf("                         ================\n");
  matrix_print(W6_L);
}

  
if( (proj_choice == 2) || (proj_choice == 3) || thresh) {  
  W7_L = (MATRIX *) get_mask(W7, dimension);
  
if(bias_choice) {
     kernel_ptr = (float **) W7_L->rptr;
     kernel_ptr[1][1] += 1.0;
  }  
  printf("\n                        Line template #3:\n");
  printf("                        ================\n");
  matrix_print(W7_L);
}

  
if( (proj_choice == 2) || (proj_choice == 3) || thresh) {  
  W8_L = (MATRIX *) get_mask(W8, dimension);

  if(bias_choice) {
     kernel_ptr = (float **) W8_L->rptr;
     kernel_ptr[1][1] += 1.0;
  }  
  printf("\n                        Line template #4:\n");
  printf("                        ================\n");
  matrix_print(W8_L);
}

  
if((proj_choice == 3) || thresh) {  
  W9_A = (MATRIX *) get_mask(W9, dimension);
  
  if(bias_choice) {
     kernel_ptr = (float **) W9_A->rptr;
     kernel_ptr[1][1] += 1.0;
  }  
  printf("\n                  \"Average\" subspace template:\n");
  printf("                   ===========================\n");
  matrix_print(W9_A);
}

  

/* Set the size of the kernel rows and columns */ 
  kernel_rows = dimension;
  kernel_cols = dimension;

  dead_rows = kernel_rows/2;
  dead_cols = kernel_cols/2;
  
/* Calculate the normalization factor for the kernel matrix */
   normal_factor = 1;


/* Make sure the normalization factor is not 0 */
  if(!normal_factor) normal_factor = 1;

  fprintf(stderr, "\n\n");
  fprintf(stderr, "Convolving... ");
  for (row=0; row<(inMatrix->rows)-kernel_rows+1; row++){

    if(row%16 == 0) fprintf(stderr, "%4d",row);

    outptr = (short int *) outMatrix->rptr[row+dead_rows];
    for (column=0; column<(inMatrix->cols)-kernel_cols+1; column++){

    for(i=0; i < 9; i++) 
      sumval[i] = 0;
      for (i=0; i<kernel_rows; i++){
        inptr = (short int *) inMatrix->rptr[i+row];     /* row offset */
        inptr = inptr + column;                   /* col offset */
	if( (proj_choice == 1) || (proj_choice == 3) || thresh) {
           w1_e =  (float *) W1_E->rptr[i];
	   w2_e =  (float *) W2_E->rptr[i];
	   w3_e =  (float *) W3_E->rptr[i];
	   w4_e =  (float *) W4_E->rptr[i];
	}
	if( (proj_choice == 2) || (proj_choice == 3) || thresh) {
           w5_l =  (float *) W5_L->rptr[i];
	   w6_l =  (float *) W6_L->rptr[i];
	   w7_l =  (float *) W7_L->rptr[i];
	   w8_l =  (float *) W8_L->rptr[i];
	}
	if( (proj_choice == 3) || thresh) 
           w9_a =  (float *) W9_A->rptr[i];
	for (j=0; j<kernel_cols; j++) {
	  if( (proj_choice == 1) || (proj_choice == 3) || thresh) {
             sumval[0]  += (*inptr) * (*w1_e++);
	     sumval[1]  += (*inptr) * (*w2_e++);
	     sumval[2]  +=(*inptr) * (*w3_e++);
             sumval[3]  += (*inptr) * (*w4_e++);
	   }
	   if( (proj_choice == 2) || (proj_choice == 3) || thresh) {
             sumval[4]  += (*inptr) * (*w5_l++);
	     sumval[5]  += (*inptr) * (*w6_l++);
	     sumval[6]  +=(*inptr) * (*w7_l++);
             sumval[7]  += (*inptr) * (*w8_l++);
	   }
	   if( (proj_choice == 3) || thresh) 
             sumval[8]  += (*inptr) * (*w9_a++);
          inptr++;
        }
      }

      if( (proj_choice == 3) || thresh) 
         if(sumval[8] == 0)                               /* Necessary to avoid floating point overflow */
            sumval[8]++;

      if( (proj_choice == 1) || (proj_choice == 3) || thresh) 
         sum_e_total = 0;
      if( (proj_choice == 2) || (proj_choice == 3) || thresh) 
         sum_l_total = 0;

      if( (proj_choice == 1) || (proj_choice == 3) || thresh) 
         for(i=0; i < 4; i++) 
            sum_e_total += sumval[i]*sumval[i];

      if( (proj_choice == 2) || (proj_choice == 3) || thresh) 
         for(i=4; i < 8; i++) 
            sum_l_total += sumval[i]*sumval[i];

      if( (proj_choice == 1) || (proj_choice == 3) || thresh) 
         mag_e = sqrt( (double) sum_e_total);
      if( (proj_choice == 2) || (proj_choice == 3) || thresh) 
         mag_l = sqrt( (double) sum_l_total);
      if( (proj_choice == 3) || thresh )
         mag_total = sqrt( (double) sum_l_total + sum_e_total + sumval[8]*sumval[8]);

      if( (thresh==1) || (thresh==3) ) {     
         theta_e = acos( (double) mag_e/mag_total);
	 theta_e_count += theta_e;
      } 
      if( (thresh==2) || (thresh==3) ) {      
         theta_l = acos( (double) mag_l/mag_total);
	 theta_l_count += theta_l;
      }
      
	 
      if(proj_choice == 1) {               /* edge space projection */
         if(thresh) {
	    if(theta_e < angle)
               mag = mag_e;
	    else
	       mag = 0;
	 }
	 else
	    mag = mag_e;
      } 	 
      else if (proj_choice == 2) {         /* line space projection */
         if(thresh) {
	    if(theta_l < angle)
               mag = mag_l;
	    else
	       mag = 0;
	 }
	 else
	    mag = mag_l;
      } 	 
      else {                               /* complete projection */
         if(thresh) {
	    if(thresh == 1) {
               if(mag_e > mag_l) {
	          if(theta_e < angle)
	             mag = mag_e;
		  else
		     mag = 0;
	       }
	       else
	          mag = mag_l;
	    }
            else if(thresh == 2) {
               if(mag_e > mag_l)
	          mag = mag_e; 
	       else { 
	          if(theta_l < angle)
	             mag = mag_l;
		  else
		     mag = 0;
	       }
	    }
	    else {
	       if(theta_l < theta_e)
	          mag = mag_l;
	       else
	          mag = mag_e;
	    }
         }
         else
            if(mag_e > mag_l)
	       mag = mag_e;
	    else
	       mag = mag_l;
       }
      
       
      /* theta_a = acos( (double) sumval[8]/mag_total);    */   
/* Not currently used in this implementation */

      outptr[column+dead_cols] = ROUND( mag/normal_factor );
      
    }
  }
  printf("\n\n");
  if( (thresh==1) || (thresh==3) )
     printf("The average angle for the edge subspace is %g.\n", theta_e_count/size);
  if( (thresh==1) || (thresh==3) )
     printf("The average angle for the line subspace is %g.\n", theta_l_count/size);
  if( (proj_choice == 1) || (proj_choice == 3) || thresh) {
     delete_Matrix(W1_E);
     delete_Matrix(W2_E);
     delete_Matrix(W3_E);
     delete_Matrix(W4_E);
  }
  if( (proj_choice == 2) || (proj_choice == 3) || thresh) {
     delete_Matrix(W5_L);
     delete_Matrix(W6_L);
     delete_Matrix(W7_L);
     delete_Matrix(W8_L);
  }
  if( (proj_choice == 3) || thresh) 
     delete_Matrix(W9_A);

  return(outMatrix);  
}



