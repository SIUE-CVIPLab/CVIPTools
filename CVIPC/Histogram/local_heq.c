/***************************************************************************
*
*             File Name: local_heq.c
*           Description: Local Histogram Equalization.
*                  Performs histogram equalization on local areas of
*                  user-selectable size.
*                  Will cast any CVIP_INTEGER, CVIP_FLOAT or CVIP_DOUBLE image into CVIP_SHORT.
*                  Will operate directly on images of type CVIP_SHORT and CVIP_BYTE.
*         Related Files: 
*   Initial Coding Date: Thu Feb 22 08:09:12 CST 1996
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Arve Kjoelen
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1996 SIUE - by Scott Umbaugh and Arve Kjoelen.
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
** $Log: local_heq.c,v $
** Revision 1.6  1997/07/11 21:22:06  smakam
** avoided by zero division which occurs when we try to local histeq large images
**
** Revision 1.5  1997/03/08 00:54:21  yawei
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
** Revision 1.4  1996/12/31 04:00:23  yawei
** local_heq ==> local_histeq
**
*
****************************************************************************/
#include <stdio.h>
#include "CVIPimage.h"
#include "CVIPdef.h"
#include "CVIPcolor.h"
#include "CVIPhisto.h"

Image *local_histeq_setup(Image *in) {
   int rows, cols, blocksize, mb=0;

/*
 * make sure we can handle the size.
 */  
   if(in->image_ptr[0]->data_type > CVIP_SHORT) 
      in=condRemap_Image(in, CVIP_SHORT, 0, 32767);

   rows=(int)in->image_ptr[0]->rows;
   cols=(int)in->image_ptr[0]->cols;

   fprintf(stdout, "Please enter the size of the local blocks\n");
   blocksize=(int)getInt_CVIP(10, 2, MIN(rows, cols));
   if(in->bands>1) {
      fprintf(stdout, "This function will preserve relative colors.  Please\n");
      fprintf(stdout, "select the band on which you wish to calculate the\n");
      fprintf(stdout, "histogram (0=Red, 1=Green, 2=Blue)\n");
      mb=getInt_CVIP(10,0,2);
   }
   in=(Image *)local_histeq(in, blocksize, mb);
   return(in);
}

Image *local_histeq(Image *in, int size, int mb) {
   Image *out, *cpy;
   int i, j, k, rows, cols, num, l1, l2, bands, off;
   int yiq=0, tmp;
   float *dist, *cum, mult, *norm, min, max, tmp1;
   short *sptr;
   byte *bptr;
   CVIP_TYPE dt;

   dt=in->image_ptr[0]->data_type;
   mult=1.0/(size*size);
   bands=in->bands;
   off=(size-1)/2;
   rows=in->image_ptr[0]->rows;
   cols=in->image_ptr[0]->cols;
   out=clone_Image(in, CVIP_FLOAT);
   
   if(dt>CVIP_SHORT) {
      fprintf(stderr, "local_histeq: Image not of type CVIP_BYTE or CVIP_SHORT\n");
      return(in);
   }
   else if(dt==CVIP_SHORT) {
      dist=(float *)malloc(sizeof(float)*32768);
      cum=(float *)malloc(sizeof(float)*32768);
      num=32768;
   }
   else { /* must be byte at this point */
      dist=(float *)malloc(sizeof(float)*256);
      cum=(float *)malloc(sizeof(float)*256);
      num=256;
   }

/*
 * calculate limits - with big blocksizes, we won't be
 * able to do the edges of the image.
 */
   rows-=(size);
   cols-=(size);
   mult*=(float)num;


/*
 * Calculate the Probability Density Function of each block.
 */
   fprintf(stderr, "Working - Row # ");
   for(i=0; i<rows; i++) {
      if(!(i%8)) fprintf(stderr, "%4d\b\b\b\b", i);
      for(j=0; j<cols; j++) { 
         l1=0;
	 if(!j) {
            for(k=0; k<num; k++) dist[k]=0.0;
            while(l1<size) {
               l2=0;
               if(dt==CVIP_BYTE) {
                  bptr=(byte *)(char *)in->image_ptr[mb]->rptr[i+l1];
                  while(l2<size) {
                     dist[bptr[j+l2]]+=1.0;
		     l2++;
	          }
               } 
               else {
                  sptr=(short *)(char *)in->image_ptr[mb]->rptr[i+l1];
                  while(l2++<size) {
                     dist[sptr[j+l2]]+=1.0;
		     l2++;
	          }
               }
	       l1++;
            } 			/* while l1 */
	 } 			/* if !j */
	 else {	/* j!=0 */
	    while(l1<size) {
	       if(dt==CVIP_BYTE) {
		   dist[((byte *)in->image_ptr[mb]->rptr[i+l1])[j-1]]-=1.0;
                   dist[((byte *)in->image_ptr[mb]->rptr[i+l1])[j+size]]+=1.0;
		   l1++;
	       }
	       else { /* must be CVIP_SHORT */
	          dist[((short *)in->image_ptr[mb]->rptr[i+l1])[j-1]]-=1.0;
                  dist[((short *)in->image_ptr[mb]->rptr[i+l1])[j+size]]+=1.0; 
	       }
	    }
	 }

/*
 * Scale and compute the Cumulative Distribution Function.
 */
         cum[0]=dist[0]*mult;
         for(k=1; k<num; k++) {
	    if(dist[k]>0.0) {
               cum[k]=dist[k]*mult;
               cum[k]+=cum[k-1];
	    }
	    else {
	       cum[k]=cum[k-1];
	    }
         }
/*
 * equalize.
 */
         if(in->bands==1) {
            if(dt==CVIP_BYTE) {
               for(k=0; k<bands; k++)
                  ((float *)(char *)out->image_ptr[k]->rptr[i+off])[j+off]=cum[((byte *)(char *)in->image_ptr[k]->rptr[i+off])[j+off]];
            }
            else {
               for(k=0; k<bands; k++)
                  ((float *)out->image_ptr[k]->rptr[i+off])[j+off]=cum[((short *)(char *)in->image_ptr[k]->rptr[i+off])[j+off]];
            }
         }
         else { /* Color */
            tmp=((byte *)(char *)in->image_ptr[mb]->rptr[i+off])[j+off];
            tmp1=cum[tmp];
            ((float *)out->image_ptr[mb]->rptr[i+off])[j+off]=tmp1; 
	    /* to avoid zero division */
	    if(tmp==0) tmp++;
            tmp1/=(float)tmp;
	    if(!mb) {
               ((float *)out->image_ptr[1]->rptr[i+off])[j+off]=(float)((byte *)in->image_ptr[1]->rptr[i+off])[j+off]*tmp1;
               ((float *)out->image_ptr[2]->rptr[i+off])[j+off]=(float)((byte *)in->image_ptr[2]->rptr[i+off])[j+off]*tmp1;
	    }
	    else if (mb==1) {
               ((float *)out->image_ptr[0]->rptr[i+off])[j+off]=(float)((byte *)in->image_ptr[0]->rptr[i+off])[j+off]*tmp1;
	       ((float *)out->image_ptr[2]->rptr[i+off])[j+off]=(float)((byte *)in->image_ptr[2]->rptr[i+off])[j+off]*tmp1;
	    }
	    else { /* mb=2, so we want to remap band 2 (blue) */
               ((float *)out->image_ptr[0]->rptr[i+off])[j+off]=(float)((byte *)in->image_ptr[0]->rptr[i+off])[j+off]*tmp1;
               ((float *)out->image_ptr[1]->rptr[i+off])[j+off]=(float)((byte *)in->image_ptr[1]->rptr[i+off])[j+off]*tmp1;
	    }
         }
      } 
   }
   fprintf(stdout, "\n");

/*
   for(i=0; i<off; i++) {
      for(j=0; j<in->image_ptr[0]->rows; j++) {
         for(k=0; k<bands; k++) {
            if(dt==CVIP_BYTE)
               ((byte *)(char *)out->image_ptr[k]->rptr[i])[j]=0;
            else
               ((short *)(char *)out->image_ptr[k]->rptr[i])[j]=0;
         }
      }
   }
   for(i=in->image_ptr[0]->rows-off; i<in->image_ptr[0]->rows; i++) {
      for(j=0; j<in->image_ptr[0]->rows; j++) {
         for(k=0; k<bands; k++) {
            if(dt==CVIP_BYTE)
               ((byte *)(char *)out->image_ptr[k]->rptr[i])[j]=0;
            else
               ((short *)(char *)out->image_ptr[k]->rptr[i])[j]=0;
         }
      }
   }
   for(i=0; i<in->image_ptr[0]->rows; i++) {
      for(j=0; j<off; j++) {
         for(k=0; k<bands; k++) {
            if(dt==CVIP_BYTE)
               ((byte *)(char *)out->image_ptr[k]->rptr[i])[j]=0;
            else
               ((short *)(char *)out->image_ptr[k]->rptr[i])[j]=0;
         }
      }
      for(j=(in->image_ptr[0]->cols-off); j<in->image_ptr[0]->cols; j++) {
         for(k=0; k<bands; k++) {
            if(dt==CVIP_BYTE)
               ((byte *)(char *)out->image_ptr[k]->rptr[i])[j]=0;
            else
               ((short *)(char *)out->image_ptr[k]->rptr[i])[j]=0;
         }
      }
   }
*/
   free(dist);
   free(cum);
   delete_Image(in);
   return(out);
}

