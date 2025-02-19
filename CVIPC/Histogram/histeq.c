/***************************************************************************
*
*             File Name: histeq.c
*           Description: Contains routines necessary to perform histogram
*                        equalization on an image.
*         Related Files: 
*   Initial Coding Date: 3/1/96
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Arve Kjoelen
*                        Southern Illinois University @ Edwardsville
*
* RCS (Revision Control System) Information
* ...Added automatically by RCS 
*
** $Log: histeq.c,v $
** Revision 1.6  1997/03/08 00:54:10  yawei
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
** Revision 1.5  1996/12/30 18:59:15  yawei
** histeq_Image ==> histeq
**
 * Revision 1.4  1996/12/30  18:11:46  yawei
 * added RCS log
 *
*
****************************************************************************/
#include <stdio.h>
#include "CVIPimage.h"
#include "CVIPdef.h"
#include "CVIPcolor.h"
#include "CVIPhisto.h"

/*
 * Function Name: histeq_setup.
 *
 * Description: Setup function for histeq.  Remaps image to
 * type CVIP_SHORT if not already CVIP_SHORT or CVIP_BYTE.
 */
Image *histeq_setup(Image *in) {
   int mb=0;

   if(in->bands>1) {
      fprintf(stdout, "This function will preserve relative colors.  Please\n");
      fprintf(stdout, "select the band on which you wish to calculate the\n");
      fprintf(stdout, "histogram (0=Red, 1=Green, 2=Blue)\n");
      mb=getInt_CVIP(10,0,2);
   }

   if(in->image_ptr[0]->data_type > CVIP_SHORT)
      in=condRemap_Image(in, CVIP_SHORT, 0, 32767);

   in=histeq(in, mb);
   return(in);
}

Image *histeq(Image *in, int mb) {
   
	 
	int i,j,k; /* Counter Variables */
   int rows, cols; 
   int num; /* number of image intensity levels */
   float *dist, mult, tmp, tmp1;
   CVIP_TYPE dt;
   Image *out;

   dt=in->image_ptr[0]->data_type;
   rows=in->image_ptr[0]->rows;
   cols=in->image_ptr[0]->cols;
   mult=1.0/(rows*cols);
    
	 
   if(dt>CVIP_SHORT) {
      fprintf(stderr, "local_heq: Image not of type CVIP_BYTE or CVIP_SHORT\n");
      return(in);
   }
   else if(dt==CVIP_SHORT) {
      dist=(float *)calloc(32768,sizeof(float));
      num=32768;
   }
   else { /* must be byte at this point */
      dist=(float *)calloc(256,sizeof(float));
      num=256;
   }

   out=clone_Image(in, CVIP_FLOAT);
   history_copy(in, out);
/*
 * Calculate the Probability Density Function of each block.
 */
   for(i=0; i<rows; i++) {
      for(j=0; j<cols; j++) {
         if(dt==CVIP_BYTE)
            dist[((byte *)in->image_ptr[mb]->rptr[i])[j]]+=1.0;
         else
            dist[((short *)in->image_ptr[mb]->rptr[i])[j]]+=1.0;
      }
   }

/*
 * Scale and calculate the Cumulative Distribution Function.
 */
   mult*=(float)(num-1);
   dist[0]*=mult;
   for(i=1; i<num; i++) {
      dist[i]*=mult;
      dist[i]+=dist[i-1];
   }

/*
 * equalize.
 */
   for(i=0; i<rows; i++) {
      for(j=0; j<cols; j++) {
         if(dt==CVIP_BYTE)
            ((float *)out->image_ptr[mb]->rptr[i])[j]=dist[((byte *)in->image_ptr[mb]->rptr[i])[j]];
         else
            ((float *)out->image_ptr[mb]->rptr[i])[j]=dist[((short *)in->image_ptr[mb]->rptr[i])[j]];
      }
   }
   if(in->bands>1) {
      for(i=0; i<rows; i++) {
         for(j=0; j<cols; j++) {
            if(dt==CVIP_BYTE) {
               tmp=(float)((byte *)in->image_ptr[mb]->rptr[i])[j];
               tmp1=dist[(int)tmp];
	       if(tmp>0.5)
                  tmp1/=tmp;
               if(!mb) {
                  ((float *)out->image_ptr[1]->rptr[i])[j]=(float)((byte *)in->image_ptr[1]->rptr[i])[j]*tmp1;
                  ((float *)out->image_ptr[2]->rptr[i])[j]=(float)((byte *)in->image_ptr[2]->rptr[i])[j]*tmp1;
               }
               else if(mb==1) {
                  ((float *)out->image_ptr[0]->rptr[i])[j]=(float)((byte *)in->image_ptr[0]->rptr[i])[j]*tmp1;
                  ((float *)out->image_ptr[2]->rptr[i])[j]=(float)((byte *)in->image_ptr[2]->rptr[i])[j]*tmp1; 
               } 
               else { /* mb=2, so we want to remap band 2 (blue) */
                  ((float *)out->image_ptr[0]->rptr[i])[j]=(float)((byte *)in->image_ptr[0]->rptr[i])[j]*tmp1;
                  ((float *)out->image_ptr[1]->rptr[i])[j]=(float)((byte *)in->image_ptr[1]->rptr[i])[j]*tmp1; 
               } 
            }
            else { /* dt=CVIP_SHORT */
               tmp=(float)((short *)in->image_ptr[mb]->rptr[i])[j];
               tmp1=dist[(int)tmp];
               tmp1/=tmp;
               if(!mb) {
                  ((float *)out->image_ptr[1]->rptr[i])[j]=(float)((short *)in->image_ptr[1]->rptr[i])[j]*tmp1;
                  ((float *)out->image_ptr[2]->rptr[i])[j]=(float)((short *)in->image_ptr[2]->rptr[i])[j]*tmp1; 
               } 
               else if(mb==1) { 
                  ((float *)out->image_ptr[0]->rptr[i])[j]=(float)((short *)in->image_ptr[0]->rptr[i])[j]*tmp1; 
                  ((float *)out->image_ptr[2]->rptr[i])[j]=(float)((short *)in->image_ptr[2]->rptr[i])[j]*tmp1;  
               }  
               else { /* mb=2, so we want to remap band 2 (blue) */ 
                  ((float *)out->image_ptr[0]->rptr[i])[j]=(float)((short *)in->image_ptr[0]->rptr[i])[j]*tmp1; 
                  ((float *)out->image_ptr[1]->rptr[i])[j]=(float)((short *)in->image_ptr[1]->rptr[i])[j]*tmp1;  
               }  
            } 
         }
      }
   }
    
   free(dist);
   delete_Image(in);
   return(out);
}
