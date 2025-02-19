/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: homomorphic.c
*           Description: This file contain the code for homomorphic filter.
*			 It has a setup function, which is called in 
*			 CVIPtools, to get the upper, lower limit and cutoff
*			 frequency of the filter. Another function which do
*			 read work is homomorphic. There is a third
*			 function call, get_function, which will return a 
*			 floating point array containing the distribution of
*			 the filter mask.
*
*         Related Files: 
*   Initial Coding Date: 12/01/94
*           Portability: Standard (ANSI) C
*             Credit(s): Kun Luo
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1994,1995 SIUE - by Kun Luo
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
*  $Log: homomorphic.c,v $
*  Revision 1.14  1997/03/08 00:53:35  yawei
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
*  Revision 1.13  1997/01/15 17:14:11  yawei
*  Global Change:  IMAGE ==> Image
*
 * Revision 1.12  1997/01/07  20:18:05  sumbaug
 * modified final CVIP_BYTE clip to a remap. Results not much different, so
 * chnaged back to original method. May need further testing of this idea,
 * but book deadline is in two days...later...
 *
 * Revision 1.11  1997/01/02  16:52:55  akjoele
 * lint check fixes.
 * .;
 *
 * Revision 1.10  1996/12/30  16:33:11  yawei
 * delete input Image when return NULL
 *
 * Revision 1.9  1996/12/30  16:24:26  yawei
 * homomorphic_filter ==> homomorphic
 *
 * Revision 1.8  1996/12/28  06:39:06  yawei
 * blockwise_fft ==> fft_transform
 * inverse_fft   ==> ifft_transform
 *
 * Revision 1.7  1995/04/04  19:12:51  luok
 * truncate off teh zero padding staff
 *
 * Revision 1.6  1995/03/31  19:43:57  luok
 * change the prompt so that the limit of cutoff frequency is displayed
 *
 * Revision 1.5  1995/03/29  18:34:47  luok
 * change the remap function to trun function.
 *
 * Revision 1.4  1995/03/27  20:34:09  luok
 * change it so that it will let the user to choose the cutoff freq.
 *
 * Revision 1.3  1995/03/27  16:29:41  luok
 * change the prompt of asking for upper and lower freq. gain.
 *
 * Revision 1.2  1995/03/22  18:17:59  luok
 * check RCS works or not.
 *
 * Revision 1.1  1995/03/22  18:13:31  luok
 * Initial revision
 *
*****************************************************************************/
#include "CVIPtoolkit.h"
#include "CVIPdef.h"
#include "CVIPimage.h"
#include "CVIPmap.h"
#include "CVIPtransform.h"
#include "CVIPxformfilter.h"
#include <limits.h>



static float * get_function(int size,int cutoff);

Image *homomorphic_setup(Image *cvipImage){
   float upper, lower;
   int cutoff;
   int limit=1;
   int bigger;
   bigger = (cvipImage->bandP[0]->rows>cvipImage->bandP[0]->cols)?
		cvipImage->bandP[0]->rows:cvipImage->bandP[0]->cols;
   while(limit < bigger)
	limit *=2; 
   do{
      fflush(stdin);
      printf("\n\tEnter the upper frequency gain:");
      scanf("%f",&upper);
      printf("\n\tEnter the lower frequency gain:");
      scanf("%f",&lower);
      if(upper>0&&lower>0&&upper>=lower)
          break;
      else
          fprintf(stderr,"Error in input data!\n");
   }while(1);
   fflush(stdin);
   printf("\n\tEnter the cutoff frequency(from 1 to %d):",limit/2);
   scanf("%d",&cutoff);
   return (homomorphic(cvipImage,upper,lower,cutoff));
}

Image * homomorphic(Image *cvipImage1,float upper, float lower,
				int cutoff){
   Image	       *cvipImage;
   int		       rows,cols,bands,no_of_bands,x,y,result,oldr,oldc;
   float               **data1,**data2,*map,dist,temp;
   CVIP_TYPE 		data_type;
   oldr=rows = getNoOfRows_Image(cvipImage1);
   oldc=cols = getNoOfCols_Image(cvipImage1);
   no_of_bands = getNoOfBands_Image(cvipImage1);
   data_type = cvipImage1->bandP[0]->data_type;
   if(cvipImage1->bandP[0]->data_type<CVIP_FLOAT && (!cast_Image(cvipImage1,CVIP_FLOAT))){
       fprintf(stderr,"Error:cast_Image\n");
		 delete_Image(cvipImage1);
       return (Image*)NULL;
   } 
   if(cvipImage1->bandP[0]->data_type>CVIP_FLOAT){
       fprintf(stderr,"Error:The maximum precision for an image is CVIP_FLOAT");
		 delete_Image(cvipImage1);
       return (Image*)NULL;
   }
   fprintf(stderr,"\n\tPerforming logarithm ....");
   for(bands=0;bands<no_of_bands;bands++){ 
      data1=getData_Image(cvipImage1,bands);
      for(y=0;y<rows;y++){
         for(x=0;x<cols;x++){
             temp=data1[y][x];
             if(temp>0)
                data1[y][x]=log(data1[y][x]);
             else
                data1[y][x]=0;
         }
      }
   }
   temp = (rows>cols)?rows:cols;
   result = 2;
   while(result<temp) 
      result*=2;
   map=get_function(result,cutoff); 
   for(y=0;y<result/2;y++)
       map[y]=lower+(upper-lower)*map[y];
   fprintf(stderr,"\n\tPerforming Forward FFT ...\n");
   cvipImage1=fft_transform(cvipImage1,result);
      for(bands=0;bands<no_of_bands;bands++){
      float tempdata; 
      data1=getData_Image(cvipImage1,bands);
      data2=getImagData_Image(cvipImage1,bands);
      for(y=0;y<result;y++){
         for(x=0;x<result;x++){
            dist=sqrt((float)(x-result/2)*(x-result/2)+
			(float)(y-result/2)*(y-result/2));
            if(dist<result/2){
                tempdata=data1[y][x];
                data1[y][x]=tempdata*map[(int)dist];
                tempdata=data2[y][x];
                data2[y][x]=tempdata*map[(int)dist];
            }
            else{
                tempdata=data1[y][x];
                data1[y][x]=tempdata*map[result/2-1];
                tempdata=data2[y][x];
                data2[y][x]=tempdata*map[result/2-1];
            }
         }
      }
   } 
   free(map); 
   cvipImage1=ifft_transform(cvipImage1,result);
   fprintf(stderr,"\n\tPerforming exponential...\n");
   rows = getNoOfRows_Image(cvipImage1);
   cols = getNoOfCols_Image(cvipImage1);
   for(bands=0;bands<no_of_bands;bands++){
      data1=getData_Image(cvipImage1,bands);
      for(y=0;y<rows;y++){
         for(x=0;x<cols;x++){
             if(data1[y][x]!=0.0)
                data1[y][x]=exp((float)data1[y][x]);
         }
      }
   } 
   cvipImage = new_Image(getFileFormat_Image(cvipImage1),getColorSpace_Image(
			cvipImage1),no_of_bands,oldr,oldc,data_type,REAL);
   switch(data_type){
	case CVIP_BYTE:{
	/*cvipImage = remap_Image(cvipImage1, CVIP_BYTE, 0, 255);*/
	     byte **new_data;
   	     for(bands=0;bands<no_of_bands;bands++){
                data1=getData_Image(cvipImage1,bands);
	        new_data = getData_Image(cvipImage,bands);
      	        for(y=0;y<oldr;y++){
                    for(x=0;x<oldc;x++){
		       if(data1[y][x]>255)
			   new_data[y][x] = 255;
		       else if(data1[y][x]<0)
			   new_data[y][x] = 0;
		       else
			   new_data[y][x] = data1[y][x];

                    } 
                }
             }
	     } 
	     break;
	case CVIP_SHORT:{
	     short **new_data;
   	     for(bands=0;bands<no_of_bands;bands++){
                data1=getData_Image(cvipImage1,bands);
	        new_data = getData_Image(cvipImage,bands);
      	        for(y=0;y<oldr;y++){
                    for(x=0;x<oldc;x++){
		       if(data1[y][x]>SHRT_MAX)
			   new_data[y][x] = 255;
		       else if(data1[y][x]<SHRT_MIN)
			   new_data[y][x] = 0;
		       else
			   new_data[y][x] = data1[y][x];
                    }
                }
             }
	     } 
	     break;
	case CVIP_INTEGER:{
	     long **new_data;
   	     for(bands=0;bands<no_of_bands;bands++){
                data1=getData_Image(cvipImage1,bands);
	        new_data = getData_Image(cvipImage,bands);
      	        for(y=0;y<oldr;y++){
                    for(x=0;x<oldc;x++){
		       if(data1[y][x]>LONG_MAX)
			   new_data[y][x] = 255;
		       else if(data1[y][x]<LONG_MIN)
			   new_data[y][x] = 0;
		       else
			   new_data[y][x] = data1[y][x];
                    }
                }
             }
	     } 
	     break;
	case CVIP_FLOAT:
		{
			float **new_data;

   	     for(bands=0;bands<no_of_bands;bands++){
                data1=getData_Image(cvipImage1,bands);
				new_data = getData_Image(cvipImage,bands);
      	        for(y=0;y<oldr;y++)
                    for(x=0;x<oldc;x++)
		       		   new_data[y][x] = data1[y][x];           
		 }
		}
		break;
   }
   delete_Image(cvipImage1);
   return cvipImage;
}

static float * get_function(int size,int cutoff){
	/* <--- the size of the image applied*/
   float *map;
   int x;
   float upperx;

   size/=2;
   map=(float *)calloc(sizeof(float),size);
   upperx=3.14/(cutoff);
   for(x=0;x<size;x++){
       if(x<=cutoff)
          map[x]= 1-cos(x*upperx);
       else
          map[x]=map[x-1];
   }
   return (float *)map;
}
