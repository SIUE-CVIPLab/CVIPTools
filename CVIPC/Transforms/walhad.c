/**************************************************************************
* ======================================================================= *
* Image Processing/Computer Vision Tool Project - Dr. Scott Umbaugh SIUE  *
* ======================================================================= *
*                                                                         *
* ROUTINE/PGM NAME: walhad.c                                              *
*                                                                         *
*                                                                         *
*         DESCRIPTION:  This files contains modules that perform a fast   *
* Hadamard-ordered Walsh-Hadamard Transform on an image.  The result is   *
* then reordered for display in sequency order.  The routine works on     *
* any image with dimensions that are a power of 2.  Optional Zero-        *
* padding may be performed if input image has different dimensions.       *
*                                                                         *
*                      AUTHOR: Arve Kjoelen                               *
*                                                                         *
*                                                                         *
*               RELATED FILES:  program_invoke.c, xform_setup.c		  	  *
*                                                                         *
*         INITIAL CODING DATE:  2/12/93                                   *
*                                                                         *
*    LAST MODIFICATIONS MADE :  3/25/93                                   *
*                                                                         *
*                                                                         *
*    VARIABLES PASSED TO walhad_transform():                              *
*                                                                         *
*         input_Image - an Image structure ptr. to either a gray-map      *
*         (8-bit) or an RGB (24-bit) image.                               *
*                                                                         *
*         ibit - a variable indicating whether the forward or             *
*         inverse transform is to be performed.  This variable also       *
*         determines whether a Walsh-ordered or a Hadamard-ordered        *
*         transform will result:                                          *
*         ibit=0 => Inverse Walsh Transform.  ibit=1 => Walsh Transform   *
*         ibit=2 => Inverse Hadamard Xform. ibit=3 => Hadamard Xform      *
*                                                                         *
* RCS (Revision Control System) Information
* ...Added automatically by RCS 
*
** $Log: walhad.c,v $
** Revision 1.10  1997/03/08 00:57:55  yawei
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
** Revision 1.9  1997/01/15 17:16:46  yawei
** Global Change:  IMAGE ==> Image
**
 * Revision 1.8  1997/01/02  17:41:36  akjoele
 * lint fixes.
 *
 * Revision 1.7  1996/12/29  05:13:53  yawei
 * wht2d.c ==> walhad.c (filename)
 *
 * Revision 1.6  1996/12/29  05:11:05  yawei
 * changed function name wht2d ==> walhad_transform
 *
 * Revision 1.5  1996/12/29  04:59:16  yawei
 * added RCS info
 *
*
*                                                                         *
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "CVIPtools.h"
#include "CVIPimage.h"
#include "CVIPdef.h"
#include "CVIPtransform.h"

/* local function prototypes */
static void do_fwht( float *, unsigned int, int );
static void reorder( float *, unsigned int );
static void scale_it( MATRIX *, unsigned long int );

/* global variables for reordering */
static float *space;
static int *indexx;

Image *
walhad_transform(
	Image 	*in_Image, 
	int 	ibit, 
	int 	block_size
)
{

HISTORY stuff;
int i, j, bands, *hptr, blockno, nohblocks, novblocks;
unsigned rows, cols;
unsigned long pixels;
MATRIX *desmatrix[3],*temp_Matrix;
char **desptr;
float *temp;

bands=in_Image->bands;
rows=in_Image->image_ptr[0]->rows;
cols=in_Image->image_ptr[0]->cols;
pixels=(unsigned long)block_size*block_size;

/* Allocate space for temporary reordering variables */
space = (float *)malloc(sizeof(float)*MAX(rows, cols));
indexx = (int *)malloc(sizeof(int)*MAX(rows, cols));
novblocks=rows/block_size;
nohblocks=cols/block_size;

/* allocate float image */
   if(in_Image->image_ptr[0]->data_type!=CVIP_FLOAT) {
      for(i=0; i<in_Image->bands; i++) {
         desmatrix[i]=new_Matrix(rows, cols, CVIP_FLOAT, REAL);
         (void)copy_Matrix(in_Image->image_ptr[i], desmatrix[i]);
         delete_Matrix(in_Image->image_ptr[i]);
         in_Image->image_ptr[i]=desmatrix[i];
      }
   }

/* start calling FWHT kernel */
for(i=0; i<bands; i++) {
    fprintf(stdout, "Calculating the WHT for spectral band #%d\n", (i+1));
    rows=in_Image->image_ptr[i]->rows;
    cols=in_Image->image_ptr[i]->cols;
    desptr=in_Image->image_ptr[i]->rptr;
    for(j=0; j<rows; j++) {
       do_fwht((float *)desptr[j], cols, block_size);
       if(ibit<2) { /* Reorder only if Walsh-order is desired */ 
          temp=(float *)desptr[j];
          for(blockno=0; blockno<nohblocks; blockno++) {    
            reorder((float *)temp, block_size);
            temp+=block_size;
          } 
       }
    }
    temp_Matrix=(MATRIX *)transpose_Matrix(in_Image->image_ptr[i]);
    delete_Matrix(in_Image->image_ptr[i]);
    in_Image->image_ptr[i]=temp_Matrix;
    desptr=in_Image->image_ptr[i]->rptr;
    for(j=0; j<cols; j++) {
       do_fwht((float *)desptr[j], rows, block_size);
       if(ibit<2) { /* Reorder only if Walsh-order is desired */ 
          temp=(float *)desptr[j];
          for(blockno=0; blockno<novblocks; blockno++) {
             reorder((float *)temp, block_size);
             temp+=block_size;
          }   
       }
    }
    temp_Matrix=transpose_Matrix(in_Image->image_ptr[i]);
    delete_Matrix(in_Image->image_ptr[i]);
    in_Image->image_ptr[i]=temp_Matrix;
    /* Divide by N if forward transform */
    if((ibit==1) || (ibit==3)) {
       scale_it(in_Image->image_ptr[i], pixels);  
       } 

   }
free(space);
free(indexx);


/* Create entries in history structure */
stuff = (HISTORY)malloc(sizeof(struct history));
if(stuff==NULL) fprintf(stderr, "Error allocating history structure\n");
stuff->packetP = (PACKET *)malloc(sizeof(PACKET));
stuff->packetP->dsize=1;
stuff->packetP->dtype=(CVIP_TYPE *)malloc(sizeof(CVIP_TYPE));
stuff->packetP->dtype[0]=CVIP_INTEGER;
hptr=(int *)malloc(sizeof(int));
hptr[0]=block_size;
stuff->packetP->dptr = (void**)malloc(sizeof(void*));
stuff->packetP->dptr[0]=(int *)hptr;
stuff->packetP->dsize = 1;
stuff->next=(HISTORY)NULL;
if(ibit==0) { /* Inverse Walsh transform */
   stuff->ftag=I_WALSH;
}
else if(ibit==1) { /* Walsh transform */
   stuff->ftag=WALSH;
}
else if(ibit==2) { /* Inverse Hadamard transform */
   stuff->ftag=I_HADAMARD;
}
else { /* Hadamard Transform, ibit==3 */
   stuff->ftag=HADAMARD;
}
history_add(in_Image, stuff);
return(in_Image);
}


static void do_fwht(
	float		*ptr, 
	unsigned int	N, 
	int		block_size
) /* FWHT kernel */
{
   register int j, i, m, offset, mmax, istep;
   int noblocks, blockno;
   float temp;

   noblocks=N/block_size;

   for(blockno=0; blockno<noblocks; blockno++) {
      offset=blockno*block_size;
      mmax=1;
      while(block_size>mmax) {
         istep=2*mmax;
         for(m=0; m<mmax; m++) {
            for(i=m; i<block_size; i+=istep) {
               j=i+mmax;
               temp=ptr[j+offset];
               ptr[j+offset]=ptr[i+offset]-temp;
               ptr[i+offset]+=temp;
            }
         }
      mmax=istep;
      }
   }
}


/* Reorder coefficients: Hadamard-ordered => Walsh-ordered */
static void 
reorder(
	float		*ptr, 
	unsigned int	N
)
{  
   int mmax, mmin, i, j;

   j=1;
   space[0]=ptr[0];
   indexx[0]=0;
   mmin=(int)N/2;
   mmax=1;
   while(mmin>0) {
      for(i=(mmax-1); i>=0; i--) {
         indexx[j]=mmin+(indexx[i]);
         space[j]=ptr[indexx[j]];
         j++;
      }
      mmin=mmin/2;
      mmax=2*mmax;
   }
   for(i=0; i<N; i++) {
      ptr[i]=space[i];
   }
}


static void 
scale_it(
	Matrix		*matrix, 
	unsigned long	nn
)
{
   unsigned int j, k;
   unsigned int rows, cols;
   float min, max, N, *temp;
   char **rptr;
   N=(float)(nn);
   rows=matrix->rows;
   cols=matrix->cols;
   rptr=matrix->rptr;
   min=rptr[0][0];
   max=min; 
   for(j=0; j<rows; j++) {
      temp=(float *)rptr[j];
      for(k=0; k<cols; k++) {
         if(max<temp[k]) {
            max=temp[k];
         }
         if(min>temp[k]) {
            min=temp[k];
         }
         temp[k]/=N;            
      }
   }
}

