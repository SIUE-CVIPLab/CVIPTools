/****************************************************************
                   Name: krish_filter
          Expanded Name: krish edge detection filter
             Parameters: <input_Image> - pointer to input Image structure
                Returns: pointer to Image structure containing edge detected
			 Image.
              Credit(s): Hari Krishna Akkineni
		         Southern Illinois University @ Edwardsville
****************************************************************/
/****************************************************************************/
/* Define Preprocessor statements */
#include "CVIPimage.h"
#include "CVIPdef.h"
#include "CVIPfs.h" 
#include <limits.h>
#include "CVIPmap.h"
#include <CVIPtoolkit.h>
#include <CVIPview.h>
#include <CVIPconvert.h>
#include <math.h>
 

static MATRIX *get_mask(MASK_TYPE type, int dimension);
static void threshold_image(Image *inputImage,int thres);
static Image *kirsch_edge(Image *inputImage, Image *pdirImage);

Image *kirsch_filter(Image *imageP, Image *pdirimage, int mask_choice, 
		int mask_size, int keep_dc, int threshold)
{
MATRIX *KERNEL;
MATRIX *temp_MATRIX;
KIRSCH_MASK *masks;
int dimension;
int bias_choice = 0;
Image *cvipImage, *direction_Image, *magImage;
direction_Image = new_Image(imageP->image_format, imageP->color_space, imageP->bands,
                            getNoOfRows_Image(imageP),getNoOfCols_Image(imageP), CVIP_FLOAT, REAL);
	/*convole filter takes only short ot byte inputs*/

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
cvipImage = NULL;
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
magImage = kirsch_edge(imageP,direction_Image);
*pdirimage = *(duplicate_Image(direction_Image));
delete_Image(direction_Image);
if(threshold >= 0){
      threshold_image(magImage,threshold);
   }
return magImage;
}

/****************************************************************
   Format: void threshold_image(Image *,int)
   Description: This function is done specifically for edge_detection only.
                It assumed the input is short and is real image.

   Credit: Hari Krishna Akkineni
*****************************************************************/
static void threshold_image(Image *inputImage,int thres){
   int x, y,row,col;
  float **real;
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
* This is new kirsch edge function, 2009
*
* Author Hari Krishna Akkineni
***********************************************************************/
   
   
static Image *kirsch_edge(Image *inputImage, Image *pdirimage){
       Image  *magImage, *dirImage;
	int r0[]={-3,-3,5,-3,0,5,-3,-3,5},r1[]={-3,5,5,-3,0,5,-3,-3,-3},r2[]={5,5,5,-3,0,-3,-3,-3,-3},r3[]={5,5,-3,5,0,-3,-3,-3,-3},r4[]={5,-3,-3,5,0,-3,5,-3,-3},r5[]={-3,-3,-3,5,0,-3,5,5,-3},r6[]={-3,-3,-3,-3,0,-3,5,5,5},r7[]={-3,-3,-3,-3,0,5,-3,5,5};
	float temp0,temp1,temp2,temp3,temp4,temp5,temp6,temp7;
     int y, x, bands, no_of_bands, rows, cols, sub_y, sub_x;
	 short **image;
	float **image_d,**image_m;
    int seq, order,count, comp;
	float maximum,value;
   	IMAGE_FORMAT image_format1;

COLOR_FORMAT color_space1;

CVIP_TYPE data_type1;

FORMAT data_format1;

image_format1 = (inputImage)->image_format;

color_space1 = (inputImage)->color_space;

data_format1 = getDataFormat_Image(inputImage);

data_type1 = getDataType_Image(inputImage);

 bands = getNoOfBands_Image(inputImage);   
    rows =  getNoOfRows_Image(inputImage);   
    cols =  getNoOfCols_Image(inputImage);
    magImage = new_Image(image_format1, color_space1, bands, rows,cols, CVIP_FLOAT, data_format1);

	dirImage = new_Image(image_format1, color_space1, bands, rows,cols, CVIP_FLOAT, data_format1);

    
	//fprintf(stderr,"\nWe use the following 8 masks:");
   for(no_of_bands=0;no_of_bands<bands;no_of_bands++)
   {
	   image = getData_Image(inputImage,no_of_bands);
	   image_m = getData_Image(magImage,no_of_bands);
	   image_d = getData_Image(dirImage,no_of_bands);
	   for(y=1; y<rows-1; y++)
	   {
		   for(x=1; x<cols-1; x++)
		   {
			   maximum = 0.0;
			   count = 0;
			   temp0=temp1=temp2=temp3=temp4=temp5=temp6=temp7=0.0f;
			   if( no_of_bands == 0 && x==1 && y==1)
				   fprintf(stderr,"\n\t");
			   for(sub_y = y-1; sub_y <= y+1; sub_y++){
				   for(sub_x = x-1; sub_x <= x+1; sub_x++){
					   temp0+= r0[count] * image[sub_y][sub_x];
					   temp1+= r1[count] * image[sub_y][sub_x];
					   temp2+= r2[count] * image[sub_y][sub_x];
					   temp3+= r3[count] * image[sub_y][sub_x];
					   temp4+= r4[count] * image[sub_y][sub_x];
					   temp5+= r5[count] * image[sub_y][sub_x];
					   temp6+= r6[count] * image[sub_y][sub_x];
					   temp7+= r7[count] * image[sub_y][sub_x];			
					   count++;
				   }
			   }
			   
			    if((maximum) < (temp0))
			   {
				   maximum = temp0;
				   value   = 0.0f;
			   
			       if((maximum) < (temp1))
				   {
					   maximum = temp1;
					   value   = PI/4.0f;
				   }
				   if((maximum) < (temp2))
				   {
					   maximum = temp2;
					   value   = PI/2.0f;
				   }
				   if((maximum) < (temp3))
				   {
					   maximum = temp3;
					   value   = 3.0f*PI/4.0f;
				   }
				   if((maximum) < (temp4))
				   {
					   maximum = temp4;
					   value   = PI;
				   }
				   if((maximum) < (temp5))
				   {
					   maximum = temp5;
					   value   = -3.0f*PI/4.0f;
				   }
				   if((maximum) < (temp6))
				   {
					   maximum = temp6;
					   value   = -PI/2.0f;
				   }
				   if((maximum) < (temp7))
				   {
					   maximum = temp7;
					   value   = -PI/4.0f;
				   }
			   }
			   else if ((maximum) < (temp1))
			   {
				   maximum = temp1;
				   value   = PI/4.0f;
				   if((maximum) < (temp2))
				   {
					   maximum = temp2;
					   value   = PI/2.0f;
				   }
				   if((maximum) < (temp3))
				   {
					   maximum = temp3;
					   value   = 3.0f*PI/4.0f;			   
				   }
				   if((maximum) < (temp4))
				   {
					   maximum = temp4;
					   value   = PI;
				   }
				   if((maximum) < (temp5))
				   {
					   maximum = temp5;
					   value   = -3.0f*PI/4.0f;
				   }
				   if((maximum) < (temp6))
				   {
					   maximum = temp6;
					   value   = -PI/2.0f;
				   }
				   if((maximum) < (temp7))
				   {
					   maximum = temp7;
					   value   = -PI/4.0f;
				   }
			   }
			   else if ((maximum) < (temp2))
			   {
				   maximum = temp2;
				   value   = PI/2.0f;
				   
				   if((maximum) < (temp3))
				   {
					   maximum = temp3;
					   value   = 3.0f*PI/4.0f;
				   }
				   if((maximum) < (temp4))
				   {
					   maximum = temp4;
					   value   = PI;
				   }
				   if((maximum) < (temp5))
				   {
					   maximum = temp5;
					   value   = -3.0f*PI/4.0f;
				   }
				   if((maximum) < (temp6))
				   {
					   maximum = temp6;
					   value   = -PI/2.0f;
				   }
				   if((maximum) < (temp7))
				   {
					   maximum = temp7;
					   value   = -PI/4.0f;
				   }
			   }
			   else if ((maximum) < (temp3))
			   {
				   maximum = temp3;
				   value   = 3.0f*PI/4.0f;
			   
				   if((maximum) < (temp4))		
				   {
					   maximum = temp4;
					   value   = PI;
				   }
				   if((maximum) < (temp5))
				   {
					   maximum = temp5;
					   value   = -3.0f*PI/4.0f;
				   }
				   if((maximum) < (temp6))
				   {
					   maximum = temp6;
					   value   = -PI/2.0f;
				   }
				   if((maximum) < (temp7))
				   {
					   maximum = temp7;
					   value   = -PI/4.0f;
				   }
			   }
			   else if((maximum) < (temp4))
			   {
				   maximum = temp4;
				   value   = PI;
			   
				   if((maximum) < (temp5))
				   {
					   maximum = temp5;
					   value   = -3.0f*PI/4.0f;
				   }
				   if((maximum) < (temp6))
				   {
					   maximum = temp6;
					   value   = -PI/2.0f;
				   }
				   if((maximum) < (temp7))
				   {
					   maximum = temp7;
					   value   = -PI/4.0f;
				   }
			   }
			   else if ((maximum) < (temp5))
			   {
				   maximum = temp5;
				   value   = -3.0f*PI/4.0f;
			   
				   if((maximum) < (temp6))
				   {
					   maximum = temp6;
					   value   = -PI/2.0f;
				   }
				   if((maximum) < (temp7))
				   {
					   
					   maximum = temp7;
					   value   = -PI/4.0f;
				   }
			   }
			   else if ((maximum) < (temp6))
			   {
				   maximum = temp6;
				   value   = -PI/2.0f;
			   
				   if((maximum) < (temp7))
				   {
					   maximum = temp7;
					   value   = -PI/4.0f;
				   }
			   }
			   else if ((maximum) < (temp7))
			   {
				   maximum = temp7;
				   value   = -PI/4.0f;
			   }
			   else 
			   {
				   maximum = 0.0f;
				   value   = 0.0f;
			   }
			   
			   image_m[y][x] = (maximum);
			   image_d[y][x] = value;
		   }
	   }  
   }
	*pdirimage = *(duplicate_Image(dirImage));
	delete_Image(dirImage);
   //(void)delete_Image(inputImage);
   return magImage;
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


static MATRIX *get_mask(MASK_TYPE type, int dimension)
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

