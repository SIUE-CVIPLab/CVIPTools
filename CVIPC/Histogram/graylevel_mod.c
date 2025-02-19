/******************************************************************************
    ======================================================================
    Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
    ======================================================================

                   Name: graylevel_mod.c
          Expanded Name: gray level modification

             Parameters: Pointer to input image of type Image
			 the starting gray level value
			 the ending gray level value
			 gray level value that the starting gray level value will
			   be modified to be
			 slope of the straight line

                Returns: pointer to a new image with specified gray level values
			 modified.

            Description: The input image can be of any data type: CVIP_BYTE,
                         CVIP_SHORT, CVIP_INTEGER, CVIP_FLOAT and CVIP_DOUBLE.

            Diagnostics: None

    Initial Coding Date: 7/1/96
Last Modifications Made: 7/8/96
             References: None

		 Author: 

		Wenxing Li:
        		MODCOMPUTE(type_,dtype_); 
			Image * gray_linear(Image * inputImage, double start, double end, 
		      			      double s_gray, double slope, int change); 

		Kun Luo:
			Image *gray_multiply_Setup(Image *input);
			Image *gray_multiply(Image *input,float ratio);

		Yansheng Wei:
			Image *gray_multiply2(Image *input,float ratio);

          Southern Illinois University @ Edwardsville


 RCS (Revision Control System) Information
 ...Added automatically by RCS 

* $Log: graylevel_mod.c,v $
* Revision 1.9  1997/05/06 20:11:08  yawei
* renamed macro name
*
* Revision 1.8  1997/04/16 14:43:31  yawei
* modified gray_linear to work on multiband image
*
* Revision 1.7  1997/03/08 00:54:24  yawei
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
* Revision 1.6  1997/01/16 21:05:20  yawei
* manual changes
*
 * Revision 1.5  1996/12/30  17:54:19  yawei
 * GrayLin_Image ==> gray_linear
 *
 * Revision 1.4  1996/12/30  17:47:48  yawei
 * added RCS log
 *

*******************************************************************************/


#include <math.h>
#include "CVIPimage.h"
#include "CVIPhisto.h"


#define MAXCVIP_SHORT    pow(2, (sizeof(short)*8 - 1)) - 1
#define MINCVIP_SHORT   (pow(2, (sizeof(short)*8 - 1))*(-1))
#define INTMAX	    pow(2, (sizeof(int)*8 - 1)) - 1
#define INTMIN     (pow(2, (sizeof(int)*8 - 1))*(-1))

#define MODCOMPUTE(type_,dtype_)\
 { register double 	value;\
   register double	pixel;\
   register unsigned	i, j;\
   for (i=0; i<rows; i++)\
     for (j=0; j<cols; j++)\
      { pixel = (double)(((type_ **)inimage)[i][j]);\
        if (pixel < start || pixel > end)\
	  { if (change) ((type_ **)outimage)[i][j] = (type_)pixel;\
	    else ((type_ **)outimage)[i][j] = (type_)0; \
	  } \
	else \
	  { value = s_gray + slope*(pixel - start); \
 	    switch(dtype_)\
             { case CVIP_BYTE: if (value>255) value=255; if (value<0) value=0; break;\
	       case CVIP_SHORT:   if (value>MAXCVIP_SHORT) value = MAXCVIP_SHORT; \
			     if (value<MINCVIP_SHORT) value = MINCVIP_SHORT;	  break;\
	       case CVIP_INTEGER: if (value>INTMAX)   value = INTMAX; \
			     if (value<INTMIN)   value = INTMIN;	  break;\
	       default:      break;\
	     }\
	    ((type_ **)outimage)[i][j] = (type_)value;\
	  }\
       }\
 }


/* a real image which can be any data type */
Image * gray_linear(Image * inputImage, double start, double end,
	double s_gray, double slope, int change, int band)
{
 Image 		* outputImage;
 void	       ** inimage, ** outimage;
 unsigned int 	  rows,  cols;
 CVIP_TYPE		  data_type;
 int bands = getNoOfBands_Image(inputImage), band_no;
 FORMAT format = getDataFormat_Image(inputImage);


 if (format == COMPLEX ) {
 	delete_Image(inputImage);
	perror_CVIP("gray_linear",
		"Gray_linear not applicable to COMPLEX image");
 	return (Image *)NULL;
 }
 if (band >= bands) {
 	delete_Image(inputImage);
	perror_CVIP("gray_linear",
		"band number too big");
 	return (Image *)NULL;
 }
 rows = inputImage->image_ptr[0]->rows;
 cols = inputImage->image_ptr[0]->cols;
 data_type = inputImage->image_ptr[0]->data_type;
 outputImage = duplicate_Image(inputImage);


 for (band_no = 0; band_no < bands; band_no++) {
	if (band < 0 || band == band_no) {
 		inimage = (void **)getData_Image(inputImage, band_no);
 		outimage= (void **)getData_Image(outputImage, band_no);
	 	switch(data_type) {
		   case CVIP_BYTE:    MODCOMPUTE(byte,CVIP_BYTE)   	break;
 	 	  	case CVIP_SHORT:   MODCOMPUTE(short,CVIP_SHORT)  	break;
 	 	  	case CVIP_INTEGER: MODCOMPUTE(int,CVIP_INTEGER)    	break;
 	   	case CVIP_FLOAT:   MODCOMPUTE(float,CVIP_FLOAT)  	break;
 	   	case CVIP_DOUBLE:  MODCOMPUTE(double,CVIP_DOUBLE) 	break;
	  }
	}
 }

 delete_Image(inputImage);
 return outputImage;
}


Image *gray_multiply_Setup(Image *input){
   unsigned int choice;
   float ratio;

   if(input->bandP[0]->data_type != CVIP_BYTE){
	fprintf(stderr,"This operation requires that input image is CVIP_BYTE\n");
	return NULL;
   }
   fflush(stdin);
   printf("\n\tEnter the multiplier:");
   scanf("%f",&ratio);
   return gray_multiply(input,ratio);
}

Image *gray_multiply(Image *input,float ratio){
   byte **image;
   int bands,x,y,no_of_bands,rows,cols;
   long temp;

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
             temp*=ratio;
             if(temp>255)
                 image[y][x]=255;
             else if(temp<1)
                image[y][x]=0;
             else
                image[y][x]=temp;                                   
          }
            
       }
   }
   return input;
}

Image *gray_multiply2(Image *input,float ratio){
   float **image;
   int bands,x,y,no_of_bands,rows,cols;

   if(getDataType_Image(input)!=CVIP_FLOAT) cast_Image(input, CVIP_FLOAT);

   no_of_bands = getNoOfBands_Image(input);
   rows = getNoOfRows_Image(input);
   cols = getNoOfCols_Image(input);
   for(bands=0; bands < no_of_bands; bands++){
      image =(float **)getData_Image(input, bands);
      for(y=0; y < rows; y++) 
          for(x=0; x < cols; x++) image[y][x] *= ratio;
   }
   return input;
}
