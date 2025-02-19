/**************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: xvq.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Mon May 31 15:08:56 CDT 1999
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): 
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1996 SIUE - by Scott Umbaugh and .
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
** $Log: xvq.c,v $
** Revision 1.27  2000/11/27 04:20:18  ycheng
** a minor change.
**
** Revision 1.26  2000/10/06 01:45:19  ycheng
** some minor changes.
**
** Revision 1.25  2000/07/03 19:41:57  ycheng
** added some functions so that now user can have more choice to choose when doing XVQ.
** Now you can decide which kind of file type you want to save the compressed data, which
** kind of remap type you want, and whether you want to quantize DC term or not.
**
** Revision 1.24  2000/01/05 23:09:58  ycheng
** revised the display message of the size of the original raw data.
**
** Revision 1.23  1999/12/17 17:58:56  ycheng
** add the correct display message about the size of original raw data.
**
** Revision 1.22  1999/11/23 23:40:02  ycheng
** added the header file for Win32.
**
** Revision 1.21  1999/11/21 05:00:41  ycheng
** an non-color image should not be permitted to be pre-processed by PCT. so when this happen, an warning should occur.
**
** Revision 1.20  1999/11/21 02:37:17  ycheng
** when reading xvq compressed files from disk, a temporary file had been written and read to/from '.cvip_temp' directory. So the path of '.cvip_temp' must been found by the program itself.
**
** Revision 1.19  1999/11/15 19:00:48  ycheng
** add function XVQ_read_decompression() to the file.
**
** Revision 1.18  1999/11/11 22:47:33  lguo
** imag_format was changed to XVQ, instead of VQ
**
** Revision 1.17  1999/11/08 02:02:42  lguo
** at the end, the image_format is set to be VQ
**
** Revision 1.16  1999/10/28 01:59:20  lguo
** nothing was changed.
**
** Revision 1.15  1999/08/22 22:38:27  lguo
** now grey level img will be converted to color img when a pct scheme chose.
**
** Revision 1.14  1999/05/31 22:12:51  lguo
** add some comments
**
** Revision 1.13  1999/05/31 20:09:23  lguo
** header added
**
*
****************************************************************************/
/**************************************************************************
*
*             File Name: xvq.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Mon May 31 14:07:41 CDT 1999
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): 
*                        Southern Illinois University @ Edwardsville
*
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <math.h>
#include <string.h>
#include "CVIPtoolkit.h"
#include "CVIPdef.h"
#include "wavelet.h"
#include "CVIPtransform.h"
#include "CVIPtools.h"
#include "vector_quant.h"
#include "vector_data.h"
#ifndef WIN32
#include <unistd.h>
#include <pwd.h>
#include <dirent.h>
#else
#include <io.h>
#include <direct.h>
#endif

   extern  int VQ_set_vector_height[];
   extern  int VQ_set_vector_width[];
   extern  int VQ_set_vector_entries[];
   
Image *band_remap(Image *image, Image *outputImage, int remap_type, int begin_rows, int end_rows, int begin_cols, int end_cols, float *min_max);
Image *logremap(Image *imgP, int band);
Image *power_remap(Image *imgP, int band);
Image *inverse_band_remap(Image *temp_image, Image *outputImage, int remap_type, int begin_rows, int end_rows, int begin_cols, int end_cols, float min, float max, float minimum);
float *min_max_Image(Image *image);


Image	*xvq_compress(Image *image, int xform, int scheme, char *filename, int file_type, int remap_type, int dc)
{
	return xvq(image, xform, scheme, filename, file_type, remap_type, dc);
}

/****************************************************************************************************
	xvq(Image *img, int xform, int scheme, char *filename, int file_type, int remap_type, int dc)
	can be devided into 3 modules:
		1, according to xform, process different xforms, push the history
		2, accroding to scheme, do VQ
		3, inverse xform
*****************************************************************************************************/	
Image	*xvq(Image *image, int xform, int scheme, char *filename, int file_type, int remap_type, int dc)
  {	int	maxsz, size, block_size, lowband;
	HISTORY stuff;
	Image	*temp_image;
	char	*code_book;
	int  	**hptr;
	float 	**hptr1;
	int	pct;/*1 means pct xformed*/
	long	size_original;
	long	size_compressed;
	struct  stat s_buf;        /*structure used to contain file info */
	float	comp_ratio;

	float	*min_max, range[10][2], min;

	Image 	*outputImage, *Img;
	IMAGE_FORMAT image_format;
  	COLOR_FORMAT color_space;
   	FORMAT       data_format;
	unsigned     no_of_rows, no_of_cols, no_of_bands;
	int 	r, c, bands, i;
	float	**img_i, **img_o, **img;
	float	sum[3], sum_temp[3]; 


/*************************************************************************************
	this part (part 1) is to 
		
		indentify if it is color img
		zero-padding the image 
		cast into float type
		if scheme==9, which means we r using customized set, set the proper set of width
		heights, and entry
*************************************************************************************/
	code_book = (char *)calloc(13, sizeof(char));
	strcpy(code_book, "temp_cdbook");
	if (scheme==0 || scheme >=11)
	{	fprintf(stdout, "scheme is not applicable\n");
		return NULL;
	}
	
  /*Acturally the 'if' command below is useless because this error has been warned in 'CVIPimage.c' file.*/
	if ((image->bands != 3)&&((xform==2)||(xform==4)))
	{	/*Image	*temp_img[3];*/
		/*temp_img[0]=temp_img[1]=temp_img[2]=image;*/
		/*image = assemble_bands( temp_img, 3);*/
	        fprintf(stdout, "This is not a color image. So it can't be pre-processed by PCT.\n");
	        return NULL;
	} 
 
 
	pct = (int)((image->bands == 3)&&((xform==2)||(xform==4)));
	maxsz=MAX(image->image_ptr[0]->rows, image->image_ptr[0]->cols);
	maxsz=(int) pow(2,((int)(log(maxsz-1)/log(2))+1));
/*	fprintf(stdout, "maxsz=%d\n", maxsz);*/
	size_original = image->image_ptr[0]->rows * image->image_ptr[0]->cols * image->bands;
	(void)zero_pad(image, maxsz, maxsz);
/**/	fprintf(stdout, "zero padded \n");
	
	 if(image->image_ptr[0]->data_type !=CVIP_FLOAT)
      		(void) cast_Image(image, CVIP_FLOAT);
/*************************************************************************************
	this part (part 2) is to do PCT xform and save history
*************************************************************************************/
	if ( pct !=0)
	{
		image = pct_color(image, CVIP_NO, NULL, 1);
/*	view_Image( image ,"PCTed");*/	
	}/*end of PCT part */
	
	/*fprintf(stdout, "\ndc = %d\n", dc);*/
/*************************************************************************************
	this part (part 3) is to do DCT xform and save history
*************************************************************************************/
     if (xform == 1 || xform==2) /*1 - DCT; 2 - PCT_DCT*/
      {
	block_size = image->image_ptr[0]->rows;
	image = dct_transform(image, block_size);
	
	if(dc == 1) /*Keep DC in history*/
	{
	  fprintf(stdout, "\nKeep DC Value in history\n");
	  
	  for(bands = 0; bands < getNoOfBands_Image(image); bands ++)
          {
            sum[bands] = 0.0;
            img = getData_Image(image, bands);
            /*fprintf(stdout, "\nimg[0][0] = %f  ", img[0][0]);*/
          
            for(r = 0; r < getNoOfRows_Image(image); r++)
              for(c = 0; c < getNoOfCols_Image(image); c++)
              {
                if((r != 0) || (c != 0))
                  sum[bands] = img[r][c] + sum[bands]; 
              }
            sum_temp[bands] = img[0][0];
            img[0][0] = sum[bands] / (float)((getNoOfRows_Image(image)) * (getNoOfCols_Image(image)));
						sum[bands] = sum_temp[bands];
           /* fprintf(stdout, "\nafter img[0][0] = %f ", img[0][0]);  */
          }
        }
	
   	if(file_type ==1) /*CVIP_FLOAT*/
   	{
   	  stuff=(HISTORY)NULL;
   	  stuff=(HISTORY)calloc(1, sizeof(struct history));
   	  stuff->packetP = (PACKET *)calloc(1, sizeof(PACKET));
          stuff->packetP->dsize=4;
   	  stuff->packetP->dtype=(CVIP_TYPE *)calloc(4, sizeof(CVIP_TYPE));
   	  for(i=0; i<4; i++)
   	    stuff->packetP->dtype[i]=CVIP_INTEGER;
   	    stuff->packetP->dptr=(void **)calloc(4, sizeof(void *));
   	  hptr=(int **)NULL;
   	  hptr=(int **)calloc(4, sizeof(int *));
   	  for(i=0; i<4; i++)
  	    hptr[i]=(int *)calloc(1, sizeof(int));
  	  hptr[0][0]=block_size;
  	  hptr[1][0]=file_type; /*1 - CVIP_FLOAT; 2 - CVIP_BYTE; 3 - CVIP_SHORT*/
	  hptr[2][0]=remap_type; /*1 - Linear_remap ; 2 - LOG_remap*/
	  hptr[3][0]=dc; /*1 - keep DC in the history; 2 - quantize DC*/
	  stuff->packetP->dptr=(void **)hptr;
   	  stuff->next=(HISTORY)NULL;
   	  stuff->ftag=DCTXFORM;
   	}
   	else if(file_type == 2 || file_type == 3) /*2 - CVIP_BYTE; 3 - CVIP_SHORT*/
   	{
   	  no_of_rows =  getNoOfRows_Image(image);
     	  no_of_cols =  getNoOfCols_Image(image);
  	  no_of_bands = getNoOfBands_Image(image);
	  image_format = getFileFormat_Image(image);
	  color_space = getColorSpace_Image(image);
	  data_format = getDataFormat_Image(image);
          
          if(file_type == 2)
          {
            fprintf(stdout, "\nCVIP_BYTE\n");
            outputImage = new_Image(image_format, color_space, no_of_bands, no_of_rows, no_of_cols, CVIP_BYTE, data_format);
	  }
	  else if(file_type == 3)
	  {
	    fprintf(stdout, "\nCVIP_SHORT\n");
	    outputImage = new_Image(image_format, color_space, no_of_bands, no_of_rows, no_of_cols, CVIP_SHORT, data_format);
	  }
	
	  min_max = (float *)calloc(2, sizeof(float));
	  min_max = min_max_Image(image);
	  min = min_max[0];
	  /*fprintf(stdout, "\nafter wavelet: min = %f, max = %f\n", min_max[0], min_max[1]);*/
	
	if(remap_type == 1) /* linear remap */
	  fprintf(stdout, "\nLinear_Remap\n");
	
	if(remap_type == 2) /* log remap */
	{
	  fprintf(stdout, "\nLOG_Remap\n");
	  for(bands = 0; bands < no_of_bands; bands++)
	  {
	    img_i = getData_Image(image, bands);
	    for(r = 0; r < no_of_rows; r++)
	      for(c = 0; c < no_of_cols; c++)
	      { 
	        img_i[r][c] = img_i[r][c] + fabs(min);
	        /*if(img_i[r][c] < 0)
	          fprintf(stdout, "\nERROR: img_i[%d][%d] = %f", r, c, img_i[r][c]);*/
	      }
	  }
	}

	  /* Convert the file data type and doing log remap or linear remap according to the 10 bands because acturally the image 
	     is compressed by these 10 bands */
	     
	  outputImage = band_remap(image, outputImage, remap_type, 0, (image->image_ptr[0]->rows)/8, 0, (image->image_ptr[0]->cols)/8, min_max);
	  range[0][0] = min_max[0];
	  range[0][1] = min_max[1];
	
	  outputImage = band_remap(image, outputImage, remap_type, 0, (image->image_ptr[0]->rows)/8, (image->image_ptr[0]->cols)/8, (image->image_ptr[0]->cols)/4, min_max);
	  range[1][0] = min_max[0];
	  range[1][1] = min_max[1];
	
	  outputImage = band_remap(image, outputImage, remap_type, (image->image_ptr[0]->rows)/8, (image->image_ptr[0]->rows)/4, 0, (image->image_ptr[0]->cols)/8, min_max);
	  range[2][0] = min_max[0];
	  range[2][1] = min_max[1];

	  outputImage = band_remap(image, outputImage, remap_type, (image->image_ptr[0]->rows)/8, (image->image_ptr[0]->rows)/4, (image->image_ptr[0]->cols)/8, (image->image_ptr[0]->cols)/4, min_max);
	  range[3][0] = min_max[0];
	  range[3][1] = min_max[1];

	  outputImage = band_remap(image, outputImage, remap_type, 0, (image->image_ptr[0]->rows)/4, (image->image_ptr[0]->cols)/4, (image->image_ptr[0]->cols)/2, min_max);
	  range[4][0] = min_max[0];
	  range[4][1] = min_max[1];

	  outputImage = band_remap(image, outputImage, remap_type, (image->image_ptr[0]->rows)/4, (image->image_ptr[0]->rows)/2, 0, (image->image_ptr[0]->cols)/4, min_max);
	  range[5][0] = min_max[0];
	  range[5][1] = min_max[1];

	  outputImage = band_remap(image, outputImage, remap_type, (image->image_ptr[0]->rows)/4, (image->image_ptr[0]->rows)/2, (image->image_ptr[0]->cols)/4, (image->image_ptr[0]->cols)/2, min_max);
	  range[6][0] = min_max[0];
	  range[6][1] = min_max[1];

	  outputImage = band_remap(image, outputImage, remap_type, 0, (image->image_ptr[0]->rows)/2, (image->image_ptr[0]->cols)/2, (image->image_ptr[0]->cols), min_max);
	  range[7][0] = min_max[0];
	  range[7][1] = min_max[1];

      	  outputImage = band_remap(image, outputImage, remap_type, (image->image_ptr[0]->rows)/2, (image->image_ptr[0]->rows), 0, (image->image_ptr[0]->cols)/2, min_max);
	  range[8][0] = min_max[0];
	  range[8][1] = min_max[1];

	  outputImage = band_remap(image, outputImage, remap_type, (image->image_ptr[0]->rows)/2, (image->image_ptr[0]->rows), (image->image_ptr[0]->cols)/2, (image->image_ptr[0]->cols), min_max);
	  range[9][0] = min_max[0];
	  range[9][1] = min_max[1];

   	  stuff=(HISTORY)NULL;
     	  stuff=(HISTORY)calloc(1, sizeof(struct history));
   	  stuff->packetP = (PACKET *)calloc(1, sizeof(PACKET));
   	  if(dc == 1)
   	  {
   	    stuff->packetP->dsize=28;
   	    stuff->packetP->dtype=(CVIP_TYPE *)calloc(28, sizeof(CVIP_TYPE));
   	    stuff->packetP->dptr=(void **)calloc(28, sizeof(void *));
   	  }
   	  else if(dc == 0)
   	  {
   	    stuff->packetP->dsize=25;
   	    stuff->packetP->dtype=(CVIP_TYPE *)calloc(25, sizeof(CVIP_TYPE));
   	    stuff->packetP->dptr=(void **)calloc(25, sizeof(void *));
   	  }
   	  stuff->packetP->dtype[0]=CVIP_INTEGER;
   	  stuff->packetP->dtype[1]=CVIP_INTEGER;
   	  stuff->packetP->dtype[2]=CVIP_INTEGER;
   	  stuff->packetP->dtype[3]=CVIP_INTEGER;
   	  if(dc == 1)
   	  {
   	    for(i=4; i<28; i++)
   	      stuff->packetP->dtype[i]=CVIP_FLOAT;
   	  }
   	  else if(dc == 0)
   	  {
   	    for(i=4; i<25; i++)
   	      stuff->packetP->dtype[i]=CVIP_FLOAT;
   	  }
  	
   	  hptr=(int **)NULL;
   	  hptr=(int **)calloc(4, sizeof(int *));
	  hptr[0]=(int *)calloc(1, sizeof(int));
	  hptr[1]=(int *)calloc(1, sizeof(int));
	  hptr[2]=(int *)calloc(1, sizeof(int));
	  hptr[3]=(int *)calloc(1, sizeof(int));
	 
	  hptr[0][0]=block_size; 
	  hptr[1][0]=file_type;
	  hptr[2][0]=remap_type;
	  hptr[3][0]=dc;
	
	  if(dc == 1)
	  {
	    hptr1=(float **)NULL;
	    hptr1=(float **)calloc(24, sizeof(float *));
	    for(i=0; i<24; i++)
              hptr1[i]=(float *)calloc(1, sizeof(float));
          }
          else if(dc == 0)
          {
            hptr1=(float **)NULL;
	    hptr1=(float **)calloc(21, sizeof(float *));
	    for(i=0; i<22; i++)
              hptr1[i]=(float *)calloc(1, sizeof(float));
          }
	
	  hptr1[0][0]=range[0][0];
	  hptr1[1][0]=range[0][1];
	  hptr1[2][0]=range[1][0];
	  hptr1[3][0]=range[1][1];
	  hptr1[4][0]=range[2][0];
	  hptr1[5][0]=range[2][1];
	  hptr1[6][0]=range[3][0];
	  hptr1[7][0]=range[3][1];
	  hptr1[8][0]=range[4][0];
	  hptr1[9][0]=range[4][1];
	  hptr1[10][0]=range[5][0];
	  hptr1[11][0]=range[5][1];
	  hptr1[12][0]=range[6][0];
  	  hptr1[13][0]=range[6][1];
	  hptr1[14][0]=range[7][0];
	  hptr1[15][0]=range[7][1];
	  hptr1[16][0]=range[8][0];
	  hptr1[17][0]=range[8][1];
	  hptr1[18][0]=range[9][0];
	  hptr1[19][0]=range[9][1];
	  hptr1[20][0]=min;
	  if(dc == 1)
	  {
	    hptr1[21][0]=sum[0];
	    hptr1[22][0]=sum[1];
	    hptr1[23][0]=sum[2];
	  }
	  
  	  stuff->packetP->dptr[0]=(void *)hptr[0];
  	  stuff->packetP->dptr[1]=(void *)hptr[1];
  	  stuff->packetP->dptr[2]=(void *)hptr[2];
  	  stuff->packetP->dptr[3]=(void *)hptr[3];

  	  if(dc == 1)
  	  {
  	    for(i=0; i<24; i++)
  	      stuff->packetP->dptr[i+4]=(void *)hptr1[i];
  	  }
  	  else if(dc == 0)
  	  {
  	    for(i=0; i<21; i++)
  	      stuff->packetP->dptr[i+4]=(void *)hptr1[i];
  	  }
  	
   	  stuff->next=(HISTORY)NULL;
   	  stuff->ftag=DCTXFORM;
   	}
   	
   	if ( pct ==0)/*no pct xform*/
	        history_add(image, stuff);  
	else /*PCTed*/
	  {	history_get(image, PCT)->next = stuff;
	  }
	  
      }

	
/*************************************************************************************
	this part (part 3) is to do wavelet xform and save history
*************************************************************************************/
     if ((xform ==3)||(xform ==4)) /* 3 - DWT, 4 - PCT_DWT */
      {
	fprintf(stdout, "Performing Wavelet Xform:  10 subbands, Wavelet=daub4...\n");
	lowband =(int)(image->image_ptr[0]->rows)>>2;
	/*fprintf(stdout, "\nlowband = % d", lowband);*/
	image=(Image *)wavdaub4_transform(image, 1, lowband);
	        	
	if(file_type == 1)
	{
	  stuff=(HISTORY)NULL;
   	  stuff=(HISTORY)calloc(1, sizeof(struct history));
   	  stuff->packetP = (PACKET *)calloc(1, sizeof(PACKET));
   	  stuff->packetP->dsize=5;
   	  stuff->packetP->dtype=(CVIP_TYPE *)calloc(5, sizeof(CVIP_TYPE));
   	  for(i=0; i<5; i++)
   	    stuff->packetP->dtype[i]=CVIP_INTEGER;
//      stuff->packetP->dptr=(void **)calloc(5, sizeof(void *));
   	  hptr=(int **)NULL;
   	  hptr=(int **)calloc(5, sizeof(int *));
	  for(i=0; i<5; i++)
  	    hptr[i]=(int *)calloc(1, sizeof(int));
  	  hptr[0][0]=2; /* 1=haar, 2=daub4 			*/
	  hptr[1][0]=lowband /*3*/; /* 1=4 fbands, 2=7fbands, 3=10fbands */
  	  hptr[2][0]=file_type;
	  hptr[3][0]=remap_type;
	  hptr[4][0]=dc;
  	  stuff->packetP->dptr=(void **)hptr;
   	  stuff->next=(HISTORY)NULL;
   	  stuff->ftag=WAVELET;
	}
	else if(file_type == 2 || file_type == 3)  /*2 -- CVIP_BYTE, 3 -- CVIP_SHORT*/
	{
	  no_of_rows =  getNoOfRows_Image(image);
     	  no_of_cols =  getNoOfCols_Image(image);
  	  no_of_bands = getNoOfBands_Image(image);
	  image_format = getFileFormat_Image(image);
	  color_space = getColorSpace_Image(image);
	  data_format = getDataFormat_Image(image);
          if(file_type == 2)
          {
            fprintf(stdout, "\nCVIP_BYTE\n");
            outputImage = new_Image(image_format, color_space, no_of_bands, no_of_rows, no_of_cols, CVIP_BYTE, data_format);
	  }
	  else if(file_type == 3)
	  {
	    fprintf(stdout, "\nCVIP_SHORT\n");
	    outputImage = new_Image(image_format, color_space, no_of_bands, no_of_rows, no_of_cols, CVIP_SHORT, data_format);
	  }
	
	  min_max = (float *)calloc(2, sizeof(float));
	  min_max = min_max_Image(image);
	  min = min_max[0];
	 /* fprintf(stdout, "\nafter wavelet: min = %f, max = %f\n", min_max[0], min_max[1]);*/
	
	if(remap_type == 1) /* linear_reamp */
	  fprintf(stdout, "\nLinear_Remap\n");
	  
	if(remap_type == 2) /*Log_remap*/
	{
	  fprintf(stdout, "\nLOG_Remap\n");
	  for(bands = 0; bands < no_of_bands; bands++)
	  {
	    img_i = getData_Image(image, bands);
	    for(r = 0; r < no_of_rows; r++)
	      for(c = 0; c < no_of_cols; c++)
	      { 
	        img_i[r][c] = img_i[r][c] + fabs(min);
	        /*if(img_i[r][c] < 0)
	          fprintf(stdout, "\nERROR: img_i[%d][%d] = %f", r, c, img_i[r][c]);*/
	      }
	  }
	}
	  
	  /* Convert the file data type and doing log remap or linear remap according to the 10 bands because acturally the image 
	     is compressed by these 10 bands */
	     
	  outputImage = band_remap(image, outputImage, remap_type, 0, (image->image_ptr[0]->rows)/8, 0, (image->image_ptr[0]->cols)/8, min_max);
	  range[0][0] = min_max[0];
	  range[0][1] = min_max[1];
	
	  outputImage = band_remap(image, outputImage, remap_type, 0, (image->image_ptr[0]->rows)/8, (image->image_ptr[0]->cols)/8, (image->image_ptr[0]->cols)/4, min_max);
	  range[1][0] = min_max[0];
	  range[1][1] = min_max[1];
	
	  outputImage = band_remap(image, outputImage, remap_type, (image->image_ptr[0]->rows)/8, (image->image_ptr[0]->rows)/4, 0, (image->image_ptr[0]->cols)/8, min_max);
	  range[2][0] = min_max[0];
	  range[2][1] = min_max[1];

	  outputImage = band_remap(image, outputImage, remap_type, (image->image_ptr[0]->rows)/8, (image->image_ptr[0]->rows)/4, (image->image_ptr[0]->cols)/8, (image->image_ptr[0]->cols)/4, min_max);
	  range[3][0] = min_max[0];
	  range[3][1] = min_max[1];

	  outputImage = band_remap(image, outputImage, remap_type, 0, (image->image_ptr[0]->rows)/4, (image->image_ptr[0]->cols)/4, (image->image_ptr[0]->cols)/2, min_max);
	  range[4][0] = min_max[0];
	  range[4][1] = min_max[1];

	  outputImage = band_remap(image, outputImage, remap_type, (image->image_ptr[0]->rows)/4, (image->image_ptr[0]->rows)/2, 0, (image->image_ptr[0]->cols)/4, min_max);
	  range[5][0] = min_max[0];
	  range[5][1] = min_max[1];

	  outputImage = band_remap(image, outputImage, remap_type, (image->image_ptr[0]->rows)/4, (image->image_ptr[0]->rows)/2, (image->image_ptr[0]->cols)/4, (image->image_ptr[0]->cols)/2, min_max);
	  range[6][0] = min_max[0];
	  range[6][1] = min_max[1];

	  outputImage = band_remap(image, outputImage, remap_type, 0, (image->image_ptr[0]->rows)/2, (image->image_ptr[0]->cols)/2, (image->image_ptr[0]->cols), min_max);
	  range[7][0] = min_max[0];
	  range[7][1] = min_max[1];

      	  outputImage = band_remap(image, outputImage, remap_type, (image->image_ptr[0]->rows)/2, (image->image_ptr[0]->rows), 0, (image->image_ptr[0]->cols)/2, min_max);
	  range[8][0] = min_max[0];
	  range[8][1] = min_max[1];

	  outputImage = band_remap(image, outputImage, remap_type, (image->image_ptr[0]->rows)/2, (image->image_ptr[0]->rows), (image->image_ptr[0]->cols)/2, (image->image_ptr[0]->cols), min_max);
	  range[9][0] = min_max[0];
	  range[9][1] = min_max[1];

   	  stuff=(HISTORY)NULL;
     	  stuff=(HISTORY)calloc(1, sizeof(struct history));
   	  stuff->packetP = (PACKET *)calloc(1, sizeof(PACKET));
   	  stuff->packetP->dsize=26;
   	  stuff->packetP->dtype=(CVIP_TYPE *)calloc(26, sizeof(CVIP_TYPE));
   	  stuff->packetP->dtype[0]=CVIP_INTEGER;
   	  stuff->packetP->dtype[1]=CVIP_INTEGER;
   	  stuff->packetP->dtype[2]=CVIP_INTEGER;
   	  stuff->packetP->dtype[3]=CVIP_INTEGER;
   	  stuff->packetP->dtype[4]=CVIP_INTEGER;
   	  for(i=5; i<26; i++)
   	    stuff->packetP->dtype[i]=CVIP_FLOAT;
  	  stuff->packetP->dptr=(void **)calloc(26, sizeof(void *));
  	
   	  hptr=(int **)NULL;
   	  hptr=(int **)calloc(5, sizeof(int *));
	  hptr[0]=(int *)calloc(1, sizeof(int));
	  hptr[1]=(int *)calloc(1, sizeof(int));
	  hptr[2]=(int *)calloc(1, sizeof(int));
	  hptr[3]=(int *)calloc(1, sizeof(int));
	  hptr[4]=(int *)calloc(1, sizeof(int));
	 
	  hptr[0][0]=2; /* 1=haar, 2=daub4 			*/
	  hptr[1][0]=lowband /*3*/; /* 1=4 fbands, 2=7fbands, 3=10fbands */
	  hptr[2][0]=file_type;
	  hptr[3][0]=remap_type;
	  hptr[4][0]=dc;
	
	  hptr1=(float **)NULL;
	  hptr1=(float **)calloc(21, sizeof(float *));
	  for(i=0; i<21; i++)
            hptr1[i]=(float *)calloc(1, sizeof(float));
	 
	  hptr1[0][0]=range[0][0];
	  hptr1[1][0]=range[0][1];
	  hptr1[2][0]=range[1][0];
	  hptr1[3][0]=range[1][1];
	  hptr1[4][0]=range[2][0];
	  hptr1[5][0]=range[2][1];
	  hptr1[6][0]=range[3][0];
	  hptr1[7][0]=range[3][1];
	  hptr1[8][0]=range[4][0];
	  hptr1[9][0]=range[4][1];
	  hptr1[10][0]=range[5][0];
	  hptr1[11][0]=range[5][1];
	  hptr1[12][0]=range[6][0];
  	  hptr1[13][0]=range[6][1];
	  hptr1[14][0]=range[7][0];
	  hptr1[15][0]=range[7][1];
	  hptr1[16][0]=range[8][0];
	  hptr1[17][0]=range[8][1];
	  hptr1[18][0]=range[9][0];
	  hptr1[19][0]=range[9][1];
	  hptr1[20][0]=min; /* the minimum value of the image */
	   
  	  stuff->packetP->dptr[0]=(void *)hptr[0];
  	  stuff->packetP->dptr[1]=(void *)hptr[1];
  	  stuff->packetP->dptr[2]=(void *)hptr[2];
  	  stuff->packetP->dptr[3]=(void *)hptr[3];
  	  stuff->packetP->dptr[4]=(void *)hptr[4];
  	
  	  for(i=0; i<21; i++)
  	    stuff->packetP->dptr[i+5]=(void *)hptr1[i];
  	
   	  stuff->next=(HISTORY)NULL;
   	  stuff->ftag=WAVELET;
   	}
   	
   	if ( pct ==0)/*no pct xform*/
	        history_add(image, stuff);  
	else /*PCTed*/
	  {	history_get(image, PCT)->next = stuff;
	  }
      }

/*************************************************************************************
	this part (part 4) is to do VQ compression and decompression
*************************************************************************************/
/**/	fprintf(stdout, "\nbegin to VQ \n");
	
	if(file_type == 1)
	{
	  if (vq_compress(image,
			filename, 
			1,	/* cdbook is in file*/
			0, 	/* not fixed cdbook */
			10, 	/* erro threshold */
			code_book,	/* useless */
			64,	/* # of entries, useless*/
			4, 	/*rows_per_vector, useless*/
			4, 	/*cols_per_vector, useless*/
			scheme ) != 1) 
	   {	return NULL;
	   }
	   
	  if (stat(filename, &s_buf)==0)
	  {
	    size_compressed =(long)s_buf.st_size;
	    comp_ratio = (float)size_original /(float)size_compressed;
	    fprintf(stdout, "\n\tThe original raw data occupies %ld bytes", size_original);
	    fprintf(stdout, "\n\tThe compressed data occupies %ld bytes", size_compressed);
	    fprintf(stdout, "\n\tThe Compression Ratio : %.2f \n\n", comp_ratio);
	  }
	
	  if ( (temp_image = (Image *)vq_decompress(filename)) == (Image *) NULL) 
	  {	return NULL;
	  }
	  
	  /*view_Image(temp_image, "VQed");*/
	}
	else if(file_type == 2 || file_type == 3)
	{
	  history_copy(image, outputImage);
  	  if (vq_compress(outputImage,
			filename, 
			1,	/* cdbook is in file*/
			0, 	/* not fixed cdbook */
			10, 	/* erro threshold */
			code_book,	/* useless */
			64,	/* # of entries, useless*/
			4, 	/*rows_per_vector, useless*/
			4, 	/*cols_per_vector, useless*/
			scheme ) != 1) 
	   {	return NULL;
	   }
	   
	  if (stat(filename, &s_buf)==0 && file_type == 3)
	  {
	    size_compressed =(long)s_buf.st_size;
	    comp_ratio = (float)size_original /(float)size_compressed;
	    fprintf(stdout, "\n\tThe original raw data occupies %ld bytes", size_original);
	    fprintf(stdout, "\n\tThe compressed data occupies %ld bytes", size_compressed);
	    fprintf(stdout, "\n\tThe Compression Ratio : %.2f \n\n", comp_ratio);
	  }
	
	  if ( (outputImage = (Image *)vq_decompress(filename)) == (Image *) NULL) 
	  {	return NULL;
	  }
	
	  /*view_Image(outputImage, "outputImage after VQ decompressed");	*/
	
	  if ( (temp_image = (Image *)vq_decompress(filename)) == (Image *) NULL) 
	  {	return NULL;
	  }
	}
	
	(void) cast_Image(temp_image, CVIP_FLOAT);
	
  	history_copy(image, temp_image);
  	
 	
/*	fprintf(stdout, "begin to inverse xform \n");*/
	/* free history memory */
	for(i=0; i<stuff->packetP->dsize; i++) 
		free(stuff->packetP->dptr[i]);
	free(stuff->packetP->dtype);
	free(stuff->packetP);
	free(stuff);
	free(hptr);        

/*************************************************************************************
	this part (part 6) is to do DCT inverse xform;
	now the image is changed to temp_image
*************************************************************************************/
     if (xform == 1 || xform==2)
      {
	if ( pct ==0) /*no pct xform*/
   		stuff=history_get(temp_image, DCTXFORM);
   	else /*PCTed*/
   	  {	stuff=history_get(temp_image, PCT)->next;
   	  }
        
        hptr=(int **)NULL;
   	hptr=(int **)calloc(4, sizeof(int *));
	for(i=0; i<4; i++)
	 hptr[i]=(int *)calloc(1, sizeof(int));
	for(i=0; i<4; i++)
   	  hptr[i]=(int *)stuff->packetP->dptr[i];

        fprintf(stdout, "\nfile_type = %d,  remap_type = %d,  dc = %d\n", hptr[1][0], hptr[2][0], hptr[3][0]);  
        
        if(hptr[1][0] == 2 || hptr[1][0] == 3)
        {
          if(hptr[3][0] == 1)
	  {
	    for(i=0; i<24; i++)
   	      hptr1[i]=(float *)stuff->packetP->dptr[i+4];
   	  }
   	  else if(hptr[3][0] == 0)
          {
            for(i=0; i<21; i++)
   	    hptr1[i]=(float *)stuff->packetP->dptr[i+4];
          }
   	    
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[2][0], 0, (image->image_ptr[0]->rows)/8, 0, (image->image_ptr[0]->cols)/8, hptr1[0][0], hptr1[1][0], hptr1[20][0]);
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[2][0], 0, (image->image_ptr[0]->rows)/8, (image->image_ptr[0]->cols)/8, (image->image_ptr[0]->cols)/4, hptr1[2][0], hptr1[3][0], hptr1[20][0]);
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[2][0], (image->image_ptr[0]->rows)/8, (image->image_ptr[0]->rows)/4, 0, (image->image_ptr[0]->cols)/8, hptr1[4][0], hptr1[5][0], hptr1[20][0]);
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[2][0], (image->image_ptr[0]->rows)/8, (image->image_ptr[0]->rows)/4, (image->image_ptr[0]->cols)/8, (image->image_ptr[0]->cols)/4, hptr1[6][0], hptr1[7][0], hptr1[20][0]);
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[2][0], 0, (image->image_ptr[0]->rows)/4, (image->image_ptr[0]->cols)/4, (image->image_ptr[0]->cols)/2, hptr1[8][0], hptr1[9][0], hptr1[20][0]);
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[2][0], (image->image_ptr[0]->rows)/4, (image->image_ptr[0]->rows)/2, 0, (image->image_ptr[0]->cols)/4, hptr1[10][0], hptr1[11][0], hptr1[20][0]);
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[2][0], (image->image_ptr[0]->rows)/4, (image->image_ptr[0]->rows)/2, (image->image_ptr[0]->cols)/4, (image->image_ptr[0]->cols)/2, hptr1[12][0], hptr1[13][0], hptr1[20][0]);
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[2][0], 0, (image->image_ptr[0]->rows)/2, (image->image_ptr[0]->cols)/2, (image->image_ptr[0]->cols), hptr1[14][0], hptr1[15][0], hptr1[20][0]);
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[2][0], (image->image_ptr[0]->rows)/2, (image->image_ptr[0]->rows), 0, (image->image_ptr[0]->cols)/2, hptr1[16][0], hptr1[17][0], hptr1[20][0]);
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[2][0], (image->image_ptr[0]->rows)/2, (image->image_ptr[0]->rows), (image->image_ptr[0]->cols)/2, (image->image_ptr[0]->cols), hptr1[18][0], hptr1[19][0], hptr1[20][0]);
          /*view_Image(temp_image, "after inverse band remap");*/
   	    
   	  if(hptr[3][0] == 1)
   	  {
   	    fprintf(stdout, "Retrieve DC Value\n");
   	    
   	    sum[0] = hptr1[21][0];
   	    sum[1] = hptr1[22][0];
   	    sum[2] = hptr1[23][0];
	    for(bands = 0; bands < getNoOfBands_Image(temp_image); bands ++)
            {
              img = getData_Image(temp_image, bands);
              img[0][0] = sum[bands];

              /*fprintf(stdout, "img[0][0] = %f\n", img[0][0]);  */
            }
          }
	}
	
        block_size = hptr[0][0];
   	image = idct_transform(temp_image,block_size);
	history_copy(temp_image, image );
        if(image == NULL) return NULL ;
/*	fprintf(stdout, "inverse dct done \n");*/
      }

/*************************************************************************************
	this part (part 6) is to do wavelet inverse xform;
	now the image is changed to temp_image
*************************************************************************************/
     if (xform == 4 || xform==3)
      {	
      	int	**hptr;
	if ( pct ==0) /*no pct xform*/
   		stuff=history_get(temp_image, WAVELET);
   	else /*PCTed*/
   	  {	stuff=history_get(temp_image, PCT)->next;
   	  }
   	
  	hptr=(int **)NULL;
   	hptr=(int **)calloc(5, sizeof(int *));
	for(i=0; i<5; i++)
	 hptr[i]=(int *)calloc(1, sizeof(int));
	for(i=0; i<5; i++)
   	  hptr[i]=(int *)stuff->packetP->dptr[i];
	
	fprintf(stdout, "\nfile_type = %d,  remap_type = %d,  dc = %d\n", hptr[2][0], hptr[3][0], hptr[4][0]);  
	
	if(hptr[2][0] == 2 || hptr[2][0] == 3)
  	{
   	  for(i=0; i<21; i++)
   	    hptr1[i]=(float *)stuff->packetP->dptr[i+5];
   	
         temp_image = inverse_band_remap(temp_image, outputImage, hptr[3][0], 0, (image->image_ptr[0]->rows)/8, 0, (image->image_ptr[0]->cols)/8, hptr1[0][0], hptr1[1][0], hptr1[20][0]);
         temp_image = inverse_band_remap(temp_image, outputImage, hptr[3][0], 0, (image->image_ptr[0]->rows)/8, (image->image_ptr[0]->cols)/8, (image->image_ptr[0]->cols)/4, hptr1[2][0], hptr1[3][0], hptr1[20][0]);
         temp_image = inverse_band_remap(temp_image, outputImage, hptr[3][0], (image->image_ptr[0]->rows)/8, (image->image_ptr[0]->rows)/4, 0, (image->image_ptr[0]->cols)/8, hptr1[4][0], hptr1[5][0], hptr1[20][0]);
         temp_image = inverse_band_remap(temp_image, outputImage, hptr[3][0], (image->image_ptr[0]->rows)/8, (image->image_ptr[0]->rows)/4, (image->image_ptr[0]->cols)/8, (image->image_ptr[0]->cols)/4, hptr1[6][0], hptr1[7][0], hptr1[20][0]);
         temp_image = inverse_band_remap(temp_image, outputImage, hptr[3][0], 0, (image->image_ptr[0]->rows)/4, (image->image_ptr[0]->cols)/4, (image->image_ptr[0]->cols)/2, hptr1[8][0], hptr1[9][0], hptr1[20][0]);
         temp_image = inverse_band_remap(temp_image, outputImage, hptr[3][0], (image->image_ptr[0]->rows)/4, (image->image_ptr[0]->rows)/2, 0, (image->image_ptr[0]->cols)/4, hptr1[10][0], hptr1[11][0], hptr1[20][0]);
         temp_image = inverse_band_remap(temp_image, outputImage, hptr[3][0], (image->image_ptr[0]->rows)/4, (image->image_ptr[0]->rows)/2, (image->image_ptr[0]->cols)/4, (image->image_ptr[0]->cols)/2, hptr1[12][0], hptr1[13][0], hptr1[20][0]);
         temp_image = inverse_band_remap(temp_image, outputImage, hptr[3][0], 0, (image->image_ptr[0]->rows)/2, (image->image_ptr[0]->cols)/2, (image->image_ptr[0]->cols), hptr1[14][0], hptr1[15][0], hptr1[20][0]);
         temp_image = inverse_band_remap(temp_image, outputImage, hptr[3][0], (image->image_ptr[0]->rows)/2, (image->image_ptr[0]->rows), 0, (image->image_ptr[0]->cols)/2, hptr1[16][0], hptr1[17][0], hptr1[20][0]);
         temp_image = inverse_band_remap(temp_image, outputImage, hptr[3][0], (image->image_ptr[0]->rows)/2, (image->image_ptr[0]->rows), (image->image_ptr[0]->cols)/2, (image->image_ptr[0]->cols), hptr1[18][0], hptr1[19][0], hptr1[20][0]);
         /*view_Image(temp_image, "after inverse band remap 10");*/
        }
   	 
   	switch(hptr[0][0]) {
      		case 1: image=(Image *)wavhaar_transform(temp_image, -1, hptr[1][0]);
              		break;
      		case 2: image=(Image *)wavdaub4_transform(temp_image, -1, hptr[1][0]);
              		break;
      		default: fprintf(stderr, "wvq_setup(): Warning: Error detected in history structure\n");
	      		break;
   		}
	history_copy(temp_image, image );
      }

/*************************************************************************************
	this part (part 8) is to do inverse PCT xform 
*************************************************************************************/
	if ( pct == 1)
	{
		image = pct_color(image, CVIP_NO, NULL, 2);
	}/*end of inverse PCT part */

	/*view_Image( image ,"final");*/
   	image->image_format = XVQ;
   	image = remap_Image(image, CVIP_BYTE,0,255);

   	if(file_type == 1)
   	{
   	  delete_Image(temp_image);
   	}
   	else if(file_type == 2 || file_type == 3)
   	{
   	  free(min_max);
   	  delete_Image(outputImage);
   	  delete_Image(temp_image);
   	}
   	
 	return image;
  }/*end of xvq(Image *img, int xform, int scheme, char *filename) */


Image *xvq_decompress(char *filename)
{    
    FILE		*fp;
	Image       *decodeImage;

    if((fp=fopen(filename,"rb"))==NULL){
	printf("cannot open file to read\n");
	return NULL; 
    }
    decodeImage = read_Image(filename, CVIP_YES);;
    fclose(fp);

    return decodeImage;
}

/*********************************************************************************
**  	Function XVQ_read_decompression() is called by  function xdr_compress() **
**      in file "cviptovip.c". 						        **
**      This function is used for reading XVQ_compressed image files with 	**
**	VIP structure from disk.  						**
**      Because XVQ_compressed image files is saved as VIP structure, now 	**
**	the pointer 'fp' points to the raw data in VIP structure. in fact,	**
** 	The raw data in VIP structure is the original XVQ_compressed image	**
**	files.									**
**	The useful part of imgP is its history. its history stores the 		**
**	necessary data for doing the inverse transform.				**
********************************************************************************/
Image *XVQ_read_decompression(FILE *fp, Image *imgP) 
{
   HISTORY 	stuff;
   Image 	*temp_image;
   int 		data;
   int 		block_size;
   
   FILE		*fptr;
   char		*filename;
   
   int		**hptr;
   float 	**hptr1;
   Image 	*outputImage;
   int 		i, bands;
   float	**img, dc[3];
      
   #ifndef WIN32
     struct passwd *pwentry;
   #endif
   
   filename = (char *)calloc(150, sizeof(char));
   
   #ifndef WIN32
     pwentry = getpwuid(getuid()); /*get home directory of the user*/
     strcpy(filename, pwentry->pw_dir);
     strcat(filename, "/xvq.cvip_temp/"); 
     //strcat(filename, "temp_file");
   #else
     if(getenv("temp"))
     {
       strcpy(filename, getenv("temp"));
       strcat(filename, "\\xvq.cvip_temp");
      // strcat(filename, "\\temp_file");
     }
     else
     {
       strcpy(filename, "\\temp\\xvq.cvip_temp");
      // strcat(filename, "\\temp_file");
     }
   #endif
   
   /*error_CVIP("filename = %s", filename);*/
   
   if((fptr = fopen(filename, "wb")) == NULL)
   {
     error_CVIP("XVQ_read_decompression", "cannot open new file");
   }

   data = getc(fp);
   while(data != EOF)
   {
     fputc(data, fptr);
     data = getc(fp);
   }
   fclose(fptr);
   
   if ((temp_image = (Image *)vq_decompress(filename)) == (Image *) NULL) 
	   {	
	     error_CVIP("VQ decompression fail", " return NULL");
	     return NULL;
	   }
   
/************************************************************************
** the history of imgP stores the necessary data for inverse transform. 
************************************************************************/
 	  history_copy(imgP, temp_image );
/*   view_Image( temp_image ,"VQed");*/

   (void) cast_Image(temp_image, CVIP_FLOAT);
  

  /*fprintf(stdout, "begin to inverse xform \n");*/



/***************************************************************************
**	this part is to do DCT inverse xform;				  **
**	now the imgP is changed to temp_image				  **
***************************************************************************/
     if(history_check(DCTXFORM, temp_image))
     {
     	if (!(history_check(PCT, temp_image))) /*no pct xform*/
   		stuff=history_get(temp_image, DCTXFORM);
   	else /*PCTed*/
   	  {	stuff=history_get(temp_image, PCT)->next;
   	  }
        
        hptr=(int **)NULL;
   	hptr=(int **)calloc(4, sizeof(int *));
	for(i=0; i<4; i++)
	 hptr[i]=(int *)calloc(1, sizeof(int));
	for(i=0; i<4; i++)
   	  hptr[i]=(int *)stuff->packetP->dptr[i];
   	  
        fprintf(stdout, "\nfile_type = %d,  remap_type = %d,  dc = %d\n", hptr[1][0], hptr[2][0], hptr[3][0]);  

        if(hptr[1][0] == 2 || hptr[1][0] == 3)
        {
          if(hptr[3][0] == 1)
	  {
	    hptr1=(float **)NULL;
	    hptr1=(float **)calloc(24, sizeof(float *));
	    for(i=0; i<24; i++)
   	      hptr1[i]=(float *)stuff->packetP->dptr[i+4];
   	  }
   	  else if(hptr[3][0] == 0)
          {
            hptr1=(float **)NULL;
	    hptr1=(float **)calloc(21, sizeof(float *));
            for(i=0; i<21; i++)
   	    hptr1[i]=(float *)stuff->packetP->dptr[i+4];
          }
   	  
   	  if ((outputImage = (Image *)vq_decompress(filename)) == (Image *) NULL) 
	  {	
	     error_CVIP("VQ decompression fail", " return NULL");
	     return NULL;
	  }
	     
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[2][0], 0, (temp_image->image_ptr[0]->rows)/8, 0, (temp_image->image_ptr[0]->cols)/8, hptr1[0][0], hptr1[1][0], hptr1[20][0]);
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[2][0], 0, (temp_image->image_ptr[0]->rows)/8, (temp_image->image_ptr[0]->cols)/8, (temp_image->image_ptr[0]->cols)/4, hptr1[2][0], hptr1[3][0], hptr1[20][0]);
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[2][0], (temp_image->image_ptr[0]->rows)/8, (temp_image->image_ptr[0]->rows)/4, 0, (temp_image->image_ptr[0]->cols)/8, hptr1[4][0], hptr1[5][0], hptr1[20][0]);
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[2][0], (temp_image->image_ptr[0]->rows)/8, (temp_image->image_ptr[0]->rows)/4, (temp_image->image_ptr[0]->cols)/8, (temp_image->image_ptr[0]->cols)/4, hptr1[6][0], hptr1[7][0], hptr1[20][0]);
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[2][0], 0, (temp_image->image_ptr[0]->rows)/4, (temp_image->image_ptr[0]->cols)/4, (temp_image->image_ptr[0]->cols)/2, hptr1[8][0], hptr1[9][0], hptr1[20][0]);
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[2][0], (temp_image->image_ptr[0]->rows)/4, (temp_image->image_ptr[0]->rows)/2, 0, (temp_image->image_ptr[0]->cols)/4, hptr1[10][0], hptr1[11][0], hptr1[20][0]);
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[2][0], (temp_image->image_ptr[0]->rows)/4, (temp_image->image_ptr[0]->rows)/2, (temp_image->image_ptr[0]->cols)/4, (temp_image->image_ptr[0]->cols)/2, hptr1[12][0], hptr1[13][0], hptr1[20][0]);
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[2][0], 0, (temp_image->image_ptr[0]->rows)/2, (temp_image->image_ptr[0]->cols)/2, (temp_image->image_ptr[0]->cols), hptr1[14][0], hptr1[15][0], hptr1[20][0]);
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[2][0], (temp_image->image_ptr[0]->rows)/2, (temp_image->image_ptr[0]->rows), 0, (temp_image->image_ptr[0]->cols)/2, hptr1[16][0], hptr1[17][0], hptr1[20][0]);
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[2][0], (temp_image->image_ptr[0]->rows)/2, (temp_image->image_ptr[0]->rows), (temp_image->image_ptr[0]->cols)/2, (temp_image->image_ptr[0]->cols), hptr1[18][0], hptr1[19][0], hptr1[20][0]);
          /*view_Image(temp_image, "after inverse band remap");*/
   	    
   	  if(hptr[3][0] == 1)
   	  {
   	    dc[0] = hptr1[21][0];
   	    dc[1] = hptr1[22][0];
   	    dc[2] = hptr1[23][0];
	    for(bands = 0; bands < getNoOfBands_Image(temp_image); bands ++)
            {
              img = getData_Image(temp_image, bands);
              img[0][0] = dc[bands];
          
              fprintf(stdout, "Retrieve DC Value");
              fprintf(stdout, "\nBand %d", bands);
              fprintf(stdout, "\timg[0][0] = %f  ", img[0][0]);  
            }
          }
	}

        block_size = hptr[0][0];
   	imgP = idct_transform(temp_image,block_size);
	history_copy(temp_image, imgP );
        if(imgP == NULL) return NULL;
	fprintf(stdout, "inverse dct done \n");
	
	delete_Image(outputImage);
     }
/***************************************************************************
**		this part is to do wavelet inverse xform;                 **
**		now the imgP is changed to temp_image			  **
***************************************************************************/
     if(history_check(WAVELET, temp_image))
      {	
	if (!(history_check(PCT, temp_image))) /*no pct xform*/
   		stuff=history_get(temp_image, WAVELET);
   	else /*PCTed*/
   	  {	stuff=history_get(temp_image, PCT)->next;
   	  }
   	
   	hptr=(int **)NULL;
   	hptr=(int **)calloc(5, sizeof(int *));
	for(i=0; i<5; i++)
	 hptr[i]=(int *)calloc(1, sizeof(int));
	for(i=0; i<5; i++)
   	  hptr[i]=(int *)stuff->packetP->dptr[i];
   	
   	fprintf(stdout, "\nfile_type = %d,  remap_type = %d,  dc = %d\n", hptr[2][0], hptr[3][0], hptr[4][0]);  
   	
   	if(hptr[2][0] == 2 || hptr[2][0] == 3)
   	{
   	  if ((outputImage = (Image *)vq_decompress(filename)) == (Image *) NULL) 
	   {	
	     error_CVIP("VQ decompression fail", " return NULL");
	     return NULL;
	   }
	   
	  hptr1=(float **)NULL;
	  hptr1=(float **)calloc(21, sizeof(float *));
	  for(i=0; i<21; i++)
            hptr1[i]=(float *)calloc(1, sizeof(float));
	   for(i=0; i<21; i++)
   	    hptr1[i]=(float *)stuff->packetP->dptr[i+5];
	
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[3][0], 0, (temp_image->image_ptr[0]->rows)/8, 0, (temp_image->image_ptr[0]->cols)/8, hptr1[0][0], hptr1[1][0], hptr1[20][0]);
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[3][0], 0, (temp_image->image_ptr[0]->rows)/8, (temp_image->image_ptr[0]->cols)/8, (temp_image->image_ptr[0]->cols)/4, hptr1[2][0], hptr1[3][0], hptr1[20][0]);
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[3][0], (temp_image->image_ptr[0]->rows)/8, (temp_image->image_ptr[0]->rows)/4, 0, (temp_image->image_ptr[0]->cols)/8, hptr1[4][0], hptr1[5][0], hptr1[20][0]);
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[3][0], (temp_image->image_ptr[0]->rows)/8, (temp_image->image_ptr[0]->rows)/4, (temp_image->image_ptr[0]->cols)/8, (temp_image->image_ptr[0]->cols)/4, hptr1[6][0], hptr1[7][0], hptr1[20][0]);
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[3][0], 0, (temp_image->image_ptr[0]->rows)/4, (temp_image->image_ptr[0]->cols)/4, (temp_image->image_ptr[0]->cols)/2, hptr1[8][0], hptr1[9][0], hptr1[20][0]);
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[3][0], (temp_image->image_ptr[0]->rows)/4, (temp_image->image_ptr[0]->rows)/2, 0, (temp_image->image_ptr[0]->cols)/4, hptr1[10][0], hptr1[11][0], hptr1[20][0]);
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[3][0], (temp_image->image_ptr[0]->rows)/4, (temp_image->image_ptr[0]->rows)/2, (temp_image->image_ptr[0]->cols)/4, (temp_image->image_ptr[0]->cols)/2, hptr1[12][0], hptr1[13][0], hptr1[20][0]);
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[3][0], 0, (temp_image->image_ptr[0]->rows)/2, (temp_image->image_ptr[0]->cols)/2, (temp_image->image_ptr[0]->cols), hptr1[14][0], hptr1[15][0], hptr1[20][0]);
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[3][0], (temp_image->image_ptr[0]->rows)/2, (temp_image->image_ptr[0]->rows), 0, (temp_image->image_ptr[0]->cols)/2, hptr1[16][0], hptr1[17][0], hptr1[20][0]);
          temp_image = inverse_band_remap(temp_image, outputImage, hptr[3][0], (temp_image->image_ptr[0]->rows)/2, (temp_image->image_ptr[0]->rows), (temp_image->image_ptr[0]->cols)/2, (temp_image->image_ptr[0]->cols), hptr1[18][0], hptr1[19][0], hptr1[20][0]);
          /*view_Image(temp_image, "after inverse band remap 10");*/
          
          delete_Image(outputImage);
   	}
   	
   	switch(hptr[0][0]) {
      		case 1: imgP=(Image *)wavhaar_transform(temp_image, -1, hptr[1][0]);
              		break;
      		case 2: imgP=(Image *)wavdaub4_transform(temp_image, -1, hptr[1][0]);
              		break;
      		default: fprintf(stderr, "wvq_setup(): Warning: Error detected in history structure\n");
	      		break;
   		}
	history_copy(temp_image, imgP);
	fprintf(stdout, "inverse dwt done \n");
      }

/**************************************************************************
**		this part is to do inverse PCT xform                     **
**************************************************************************/
	if (history_check(PCT, temp_image))
	{
	  imgP = pct_color(imgP, CVIP_NO, NULL, 2);
	}/*end of inverse PCT part */

        /*view_Image( imgP ,"final");	*/
   	imgP = remap_Image( imgP, CVIP_BYTE,0,255);

        delete_Image(temp_image);

 	return imgP; 
}


/* This function is to do the log remap for an image. */

Image *logremap(Image 	*imgP, int band)
{
  	Image  		*remP,*remP1;
	IMAGE_FORMAT 	format;
  	HISTORY 	stuff;
  	char 		bsize[6], *assign="spectrum",
			*strP = NULL;
	float		**rdataP, **idataP, N, **odataP;
    	int 		h, w, x, y, color=0, bands, k, m, *hptr, block_size;
  	double 		temp, temp1;
	char		*fn = "logMap_Image";
	
  	if(getDataType_Image(imgP) != CVIP_FLOAT)
     		(void) cast_Image(imgP, CVIP_FLOAT);

  	bands	= getNoOfBands_Image(imgP);
  	h 	= getNoOfRows_Image(imgP);
  	w 	= getNoOfCols_Image(imgP);

	if(band > bands-1) {
		error_CVIP(fn,"The maximum band number is %d\n",bands-1);
		band = bands-1;
	}
	if(band==-1 && bands == 3)  
  		remP = new_Image(PPM,RGB,bands,h,w,CVIP_FLOAT,REAL);
	else
		remP = new_Image(PGM,GRAY_SCALE,1,h,w,CVIP_FLOAT,REAL);

	if(remP == NULL)
	{
		delete_Image(imgP);
		return(NULL);
	}
	
			/* Not COMPLEX */
		for (k = 0; k < bands; k++) 
		{
			if(band != -1) k = band;
			rdataP = getRealData_Matrix(getBand_Image(imgP, k));
			if(band ==-1)
			odataP = getRealData_Matrix(getBand_Image(remP, k));
			else
			odataP = getRealData_Matrix(getBand_Image(remP, 0));

  			/*fprintf(stdout, "\nlog remap");*/
  			for(y = 0; y < h; y++) 
    			for(x = 0; x < w; x++) {
        			/*if(y == 0 && x ==0)
        			  fprintf(stdout, "\nI[%d][%d] = %f", y, x, rdataP[y][x]);*/
				
				temp = (double)(rdataP[y][x]);
				
				/*odataP[y][x] = (float)log10(1.0+temp);*/
				odataP[y][x] = (float)log10(1.0+temp) / log10(1.05);
      				/*if(y == 0 && x ==0)
      				  fprintf(stdout, "\nI[%d][%d] = %f", y, x, odataP[y][x]);*/
      				if(temp < 0.0)
      				  fprintf(stdout, "\nI[%d][%d] = %f", y, x, rdataP[y][x]);
    			} 
			if(band !=-1)
			break;
		}
	
	
	if (imgP) delete_Image(imgP);

	return remP;
}

/* This function is to do the inverse remap for an image that has been log remapped. */

Image *power_remap(Image *imgP, int band)
{
  	Image  		*remP,*remP1;
	IMAGE_FORMAT 	format;
  	HISTORY 	stuff;
  	char 		bsize[6], *assign="spectrum",
			*strP = NULL;
	float		**rdataP, **idataP, N, **odataP;
    	int 		h, w, x, y, color=0, bands, k, m, *hptr, block_size;
  	double 		temp;
	char		*fn = "logMap_Image";

  	if(getDataType_Image(imgP) != CVIP_FLOAT)
     		(void) cast_Image(imgP, CVIP_FLOAT);

  	bands	= getNoOfBands_Image(imgP);
  	h 	= getNoOfRows_Image(imgP);
  	w 	= getNoOfCols_Image(imgP);

	if(band > bands-1) {
		error_CVIP(fn,"The maximum band number is %d\n",bands-1);
		band = bands-1;
	}
	if(band==-1 && bands == 3)  
  		remP = new_Image(PPM,RGB,bands,h,w,CVIP_FLOAT,REAL);
	else
		remP = new_Image(PGM,GRAY_SCALE,1,h,w,CVIP_FLOAT,REAL);

	if(remP == NULL)
	{
		delete_Image(imgP);
		return(NULL);
	}
	
			/* Not COMPLEX */
		for (k = 0; k < bands; k++) 
		{
			if(band != -1) k = band;
			rdataP = getRealData_Matrix(getBand_Image(imgP, k));
			if(band ==-1)
			odataP = getRealData_Matrix(getBand_Image(remP, k));
			else
			odataP = getRealData_Matrix(getBand_Image(remP, 0));

  			/*fprintf(stdout, "\ninverse log remap\n");*/
  			for(y = 0; y < h; y++) 
    			for(x = 0; x < w; x++) {
        			/*if(y == 0 && x ==0)
        			  fprintf(stdout, "\nI[%d][%d] = %f", y, x, rdataP[y][x]);*/
				/*temp = (double)pow(10, rdataP[y][x]);*/
				temp = (double)pow(1.05, rdataP[y][x]);
      				odataP[y][x] = (float)(temp - 1.0);
      				
    			} 
			if(band !=-1)
			break;
		}
	

	if (imgP) delete_Image(imgP);

	return remP;
}

/* This function is to do the remap within a band. 
** image is the input image and outputImage is the output image.*/

Image *band_remap(Image *image, Image *outputImage, int remap_type, int begin_rows, int end_rows, int begin_cols, int end_cols, float *min_max)
{
   Image	*sub_image;
   IMAGE_FORMAT image_format;
   COLOR_FORMAT color_space;
   CVIP_TYPE    data_type, data_type_o;
   FORMAT       data_format;
   float   	**img_i, **img_sub; 
   byte		**img_o, **img_sub1;
   short	**img_o_s, ** img_sub1_s;
   
   int		r, c, bands;
   unsigned 	no_of_rows, no_of_cols, no_of_bands;
   
   float 	*min_max_sub;
   
   no_of_rows =  end_rows - begin_rows;
   no_of_cols =  end_cols - begin_cols;

   no_of_bands = getNoOfBands_Image(image);
   image_format = getFileFormat_Image(image);
   color_space = getColorSpace_Image(image);
   data_format = getDataFormat_Image(image);
   data_type = getDataType_Image(image);
   data_type_o = getDataType_Image(outputImage);

   sub_image = new_Image(image_format, color_space, no_of_bands, no_of_rows, no_of_cols, data_type, data_format);
   
   for(bands = 0; bands < no_of_bands; bands++)
   {
   	img_i = getData_Image(image, bands);
   	img_sub = getData_Image(sub_image, bands);
   	
   	for(r = 0; r < no_of_rows; r++)
   	  for(c= 0; c < no_of_cols; c++)
   	  {
   	    img_sub[r][c] = img_i[begin_rows + r][begin_cols + c];
   	  }
   }
   
   min_max_sub = (float *)calloc(2, sizeof(float));
   min_max_sub = min_max_Image(sub_image);
   /*fprintf(stdout, "\nsub_image before logremap: min_sub = %f, max_sub = %f\n, min = %f, max = %f", min_max_sub[0], min_max_sub[1], min_max[0], min_max[1]);*/
   
   (void)history_copy(image, sub_image);
   
   if(remap_type == 2)
   {
     sub_image = logremap(sub_image, -1);
   }
   min_max_sub = min_max_Image(sub_image);
   min_max[0] = min_max_sub[0];
   min_max[1] = min_max_sub[1];
   /*fprintf(stdout, "\n\nsub_image after logremap: min_sub = %f, max_sub = %f\n, min = %f, max = %f", min_max_sub[0], min_max_sub[1], min_max[0], min_max[1]);*/
   
   if(data_type_o == CVIP_BYTE)
   {
     /*fprintf(stdout, "\nband_remap :CVIP_BYTE\n");*/
     sub_image = remap_Image(sub_image, CVIP_BYTE, 0, 255);
   }
   else if(data_type_o == CVIP_SHORT)
   {
     /*fprintf(stdout, "\nband_remap : CVIP_SHORT\n");*/
     sub_image = remap_Image(sub_image, CVIP_SHORT, 0, 32767);

   }
   data_type = getDataType_Image(sub_image);
   /*fprintf(stdout, "\nafter remap to float: data_type = %d", data_type);*/

   for(bands = 0; bands < no_of_bands; bands++)
   {
   	if(data_type_o == CVIP_BYTE)
   	{
   	  img_sub1 = getData_Image(sub_image, bands);
   	  img_o = getData_Image(outputImage, bands);
   	  
   	  for(r = 0; r < no_of_rows; r++)
   	  for(c= 0; c < no_of_cols; c++)
   	  {
   	    img_o[begin_rows + r][begin_cols + c] = img_sub1[r][c];
   	  }
   	}
   	else if(data_type_o == CVIP_SHORT)
   	     {
   	       img_sub1_s = getData_Image(sub_image, bands);
   	       img_o_s = getData_Image(outputImage, bands);
   	       
   	       for(r = 0; r < no_of_rows; r++)
   	       for(c= 0; c < no_of_cols; c++)
   	       {
   	         img_o_s[begin_rows + r][begin_cols + c] = img_sub1_s[r][c];
   	       }
   	     }
   }
   
   delete_Image(sub_image);
   free(min_max_sub);
   
   return outputImage;

}

/* This function is to do the inverse remap wthin a band with the image is decompressed.
**outputImage is the input image and temp_image is the output image.	*/

Image *inverse_band_remap(Image *temp_image, Image *outputImage, int remap_type, int begin_rows, int end_rows, int begin_cols, int end_cols, float min, float max, float minimum)
{
   Image	*sub_image;
   IMAGE_FORMAT image_format;
   COLOR_FORMAT color_space;
   CVIP_TYPE    data_type;
   FORMAT       data_format;
   byte   	**img_i, **img_sub1;
   short   	**img_i_s, **img_sub1_s; 
   float	**img_o, **img_sub2;
   float	**img_R, **img_G, **img_B, **img_o_R, **img_o_G, **img_o_B;
   
   int		r, c, bands, count;
   unsigned 	no_of_rows, no_of_cols, no_of_bands;
   
   float	*min_max_sub, *min_max;
   
   float	temp1, temp2;
   
   int		pct = 0, count_R = 0, count_G = 0, count_B = 0;
   CVIP_BOOLEAN R = CVIP_NO, G = CVIP_NO, B = CVIP_NO;
   
   no_of_rows =  end_rows - begin_rows;
   no_of_cols =  end_cols - begin_cols;

   no_of_bands = getNoOfBands_Image(outputImage);
   image_format = getFileFormat_Image(outputImage);
   color_space = getColorSpace_Image(outputImage);
   data_format = getDataFormat_Image(outputImage);
   data_type = getDataType_Image(outputImage);

   /*fprintf(stdout, "\nenter band_remap");*/
   sub_image = new_Image(image_format, color_space, no_of_bands, no_of_rows, no_of_cols, data_type, data_format);
   /*fprintf(stdout, "\ndata_type = %d\n", data_type);*/
   
   for(bands = 0; bands < no_of_bands; bands++)
   {
      if(data_type == CVIP_BYTE)
      {
   	img_i = getData_Image(outputImage, bands);
   	img_sub1 = getData_Image(sub_image, bands);
   	
   	for(r = 0; r < no_of_rows; r++)
   	  for(c= 0; c < no_of_cols; c++)
   	  {
   	    img_sub1[r][c] = img_i[begin_rows + r][begin_cols + c];
   	    
   	  }
      }
      else if(data_type == CVIP_SHORT)
      {
        img_i_s = getData_Image(outputImage, bands);
   	img_sub1_s = getData_Image(sub_image, bands);
   	
   	for(r = 0; r < no_of_rows; r++)
   	  for(c= 0; c < no_of_cols; c++)
   	  {
   	    img_sub1_s[r][c] = img_i_s[begin_rows + r][begin_cols + c];
   	    
   	  }
      }
   }
   (void) cast_Image(sub_image, CVIP_FLOAT);
   
   (void)history_copy(temp_image, sub_image);
   if(history_check(PCT, sub_image))
   {
     pct = 1;
   }
   
   min_max_sub = (int *)calloc(2, sizeof(int));
   min_max_sub = min_max_Image(sub_image);
   /*fprintf(stdout, "\nsub_image before power_remap: min_sub = %f, max_sub = %f\n", min_max_sub[0], min_max_sub[1]);
   fprintf(stdout, "\n\t min = %f, max = %f\n", min, max);*/
   
  if((min_max_sub[0] == 0.0) && (min_max_sub[1] == 0.0))
  {
     /*fprintf(stdout, "\nenter ZERO!!!");*/
     for(bands = 0; bands < no_of_bands; bands++)
     {
   	img_sub2 = getData_Image(sub_image, bands);
   	img_o = getData_Image(temp_image, bands);
   	
   	for(r = 0; r < no_of_rows; r++)
   	  for(c= 0; c < no_of_cols; c++)
   	  {
   	    img_o[begin_rows + r][begin_cols + c] = 0.0;
   	  }
     }
  }
  else
  {
   if(pct == 0) /* no PCT has been performed */
   {
   for(bands = 0; bands < no_of_bands; bands++)
     {
   	img_sub2 = getData_Image(sub_image, bands);
   	   	
   	for(r = 0; r < no_of_rows; r++)
   	  for(c= 0; c < no_of_cols; c++)
   	  {
   	    if(data_type == CVIP_BYTE)
   	    { 
   	      /*if(bands == 0 && r == 0 && c == 0)
   	        fprintf(stdout, "\nCVIP_BYTE\n");*/
   	      img_sub2[r][c] = (img_sub2[r][c] - 0.0) * fabs(max -min) / (255.0 - 0.0) + min;
   	    }
   	    else if(data_type == CVIP_SHORT)
   	    { 
   	      /*if(bands == 0 && r == 0 && c == 0)
   	        fprintf(stdout, "\nCVIP_SHORT\n");*/
   	      img_sub2[r][c] = (img_sub2[r][c] - 0.0) * fabs(max -min) / (32767.0 - 0.0) + min;
   	    }
   	  }
     }
      
   data_type = getDataType_Image(sub_image);
   /*fprintf(stdout, "\nafter remap to float: data_type = %d", data_type);*/
   min_max = (float *)calloc(2, sizeof(float));
   min_max = min_max_Image(sub_image);
   /*fprintf(stdout, "\nafter float->float: [%f, %f]\n", min_max[0], min_max[1]);*/
   
   if(remap_type == 2 || remap_type == 3)
   {
     sub_image = power_remap(sub_image, -1);
   }
   min_max_sub = min_max_Image(sub_image);
  /* fprintf(stdout, "\nsub_image after power_remap: min_sub = %f, max_sub = %f\n", min_max_sub[0], min_max_sub[1]);*/
   
     for(bands = 0; bands < no_of_bands; bands++)
     {
   	img_sub2 = getData_Image(sub_image, bands);
   	img_o = getData_Image(temp_image, bands);
   	
   	for(r = 0; r < no_of_rows; r++)
   	  for(c= 0; c < no_of_cols; c++)
   	  {
   	    if(remap_type == 2)
   	      img_o[begin_rows + r][begin_cols + c] = img_sub2[r][c] - fabs(minimum);
   	    else if(remap_type == 1)
   	           img_o[begin_rows + r][begin_cols + c] = img_sub2[r][c];
   	  }
     }
   }
   else if(pct == 1)
   {
     img_R = getData_Image(sub_image, 0);
     img_G = getData_Image(sub_image, 1);
     img_B = getData_Image(sub_image, 2);
     
     for(r = 0; r < no_of_rows; r++)
   	  for(c= 0; c < no_of_cols; c++)
   	  {
   	    if(img_R[r][c] == 0.0)
   	    {
   	      count_R = count_R + 1;
   	    }
   	    if(img_G[r][c] == 0.0)
   	    {
   	      count_G = count_G + 1;
   	    }
   	    if(img_B[r][c] == 0.0)
   	    {
   	      count_B = count_B + 1;
   	    }
   	  }
     if(count_R == (no_of_rows * no_of_cols))
     {
        R = CVIP_YES;
     }
     if(count_G == (no_of_rows * no_of_cols))
     {
        G = CVIP_YES;
     }
     if(count_B == (no_of_rows * no_of_cols))
     {
        B = CVIP_YES;
     }
     
     
       for(bands = 0; bands < no_of_bands; bands++)
       {
   	img_sub2 = getData_Image(sub_image, bands);
   	   	
   	for(r = 0; r < no_of_rows; r++)
   	  for(c= 0; c < no_of_cols; c++)
   	  {
   	    if(data_type == CVIP_BYTE)
   	    { 
   	      /*if(bands == 0 && r == 0 && c == 0)
   	        fprintf(stdout, "\nCVIP_BYTE\n");*/
   	      img_sub2[r][c] = (img_sub2[r][c] - 0.0) * fabs(max -min) / (255.0 - 0.0) + min;
   	    }
   	    else if(data_type == CVIP_SHORT)
   	    { 
   	      /*if(bands == 0 && r == 0 && c == 0)
   	        fprintf(stdout, "\nCVIP_SHORT\n");*/
   	      img_sub2[r][c] = (img_sub2[r][c] - 0.0) * fabs(max -min) / (32767.0 - 0.0) + min;
   	    }
   	  }
       }
       
       if(remap_type == 2)
       {
         sub_image = power_remap(sub_image, -1);
       }
       min_max_sub = min_max_Image(sub_image);
       /*fprintf(stdout, "\nsub_image after power_remap: min_sub = %f, max_sub = %f\n", min_max_sub[0], min_max_sub[1]);*/

     img_R = getData_Image(sub_image, 0);
     img_G = getData_Image(sub_image, 1);
     img_B = getData_Image(sub_image, 2);
     
     img_o_R = getData_Image(temp_image, 0);
     img_o_G = getData_Image(temp_image, 1);
     img_o_B = getData_Image(temp_image, 2);
   
     for(r = 0; r < no_of_rows; r++)
   	  for(c= 0; c < no_of_cols; c++)
   	  {	
            if(!R) 
            { 
              if(remap_type == 2)
                img_o_R[begin_rows + r][begin_cols + c] = img_R[r][c] - fabs(minimum);
              else if(remap_type == 1)
                     img_o_R[begin_rows + r][begin_cols + c] = img_R[r][c];
            }
            else
              { 
              img_o_R[begin_rows + r][begin_cols + c] = 0.0;
              }
       
            if(!G)
            {
              if(remap_type == 2)
                img_o_G[begin_rows + r][begin_cols + c] = img_G[r][c] - fabs(minimum);
              else if(remap_type == 1)
                img_o_G[begin_rows + r][begin_cols + c] = img_G[r][c];
            }
            else
              { 
              img_o_G[begin_rows + r][begin_cols + c] = 0.0;
              }
         
            if(!B)
            {
              if(remap_type == 2)
                img_o_B[begin_rows + r][begin_cols + c] = img_B[r][c] - fabs(minimum);
              else if(remap_type == 1)
                   img_o_B[begin_rows + r][begin_cols + c] = img_B[r][c];
            }
            else
              { 
              img_o_B[begin_rows + r][begin_cols + c] = 0.0;
              }
          }	  
   }
   
   }
   delete_Image(sub_image);
   free(min_max_sub);
   
   return temp_image;
}


/* This function is to find the minimum and maximum value of the image. */

float *min_max_Image(Image *image)
{
   int  	no_of_bands, imgsize, rows, cols;
   float   	*min_maxP = NULL;
   int		r, c, bands;
   float	**img;
   float 	min, max;
   
   /*(void)cast_Image(image, CVIP_FLOAT);*/
   
   no_of_bands = getNoOfBands_Image(image);
   rows = getNoOfRows_Image(image);
   cols = getNoOfCols_Image(image);
   
   min_maxP  = (float *)calloc(2, sizeof(float));
   
   for(bands = 0; bands < no_of_bands; bands++)
   {
     img = getData_Image(image, bands);
     for(r = 0; r < rows; r++)
       for(c = 0; c < cols; c++)
       {
         if(bands == 0 && r == 0 && c == 0)
         {
           min = img[r][c];
           max = img[r][c];
         }
         else
         {
           if(min > img[r][c])
             min = img[r][c];
           if(max < img[r][c])
             max = img[r][c];
         }   
       }
   }
   
   min_maxP[0] = min;
   min_maxP[1] = max;
 
   return min_maxP;  
}
