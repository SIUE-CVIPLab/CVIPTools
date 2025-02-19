/**************************************************************************
* ======================================================================= *
* Image Processing/Computer Vision Tool Project - Dr. Scott Umbaugh SIUE  *
* ======================================================================= *
*                                                                         *
* ROUTINE/PGM NAME: haar.c                                                *
*                                                                         *
*                                                                         *
*         DESCRIPTION:  This files contains modules that perform a fast   *
* Haar Transform on an image.  The routine works on                       *
* any image with dimensions that are a power of 2.  Optional Zero-        *
* padding may be performed if input image has different dimensions.       *
* The transform is not performed in-place, and a temporary array is       *
* dynamically allocated to hold intermediate results.                     *
*                                                                         *
*                      AUTHOR: Arve Kjoelen                               *
*                                                                         *
*                                                                         *
*               RELATED FILES:  program_invoke.c                          *
*                                                                         *
*         INITIAL CODING DATE:  3/18/93                                    *
*                                                                         *
*    LAST MODIFICATIONS MADE :  9/8/93                                   *
*                                                                         *
*                                                                         *
*    VARIABLES PASSED TO haar2d():                                        *
*                                                                         *
*         input_Image - an Image structure ptr. to either a gray-map      *
*         (8-bit) or an RGB (24-bit) image.                               *
*                                                                         *
*         ibit - a variable indicating whether the forward or             *
*         inverse transform is to be performed.                           *
*         ibit=1 => Forward Haar Xform.  ibit=0=> Inverse Haar Xform      *
*                                                                         *
*  A forward transform is implemented as follows:                         *
*  1.  execute haar()   Division by N also takes place here.              *
*  2.  execute haarnorm()                                                 *
*                                                                         *
*  An inverse transform is implemented as follows:                        *
*  1.  execute haarnorm()                                                 *
*  2.  execute haarin()                                                   *
*                                                                         *
*                                                                         *
**************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "CVIPtools.h"
#include "CVIPimage.h"
#include "CVIPdef.h"
#include "CVIPtransform.h"

/* 
** function prototypes 
*/
static void haar( float *, unsigned int, int );
static void haarin( float *, unsigned int, int );
static void haarnorm( float *, unsigned int, int );

/* 
** Global Temporary array for intermediate results 
*/
static float *sspace;


Image *
haar_transform(
	Image 	*in_Image, 
	int 	ibit, 
	int 	block_size
) 
{
   HISTORY stuff;
   int i, j, bands, *hptr;
   unsigned rows, cols, line;
   MATRIX *desmatrix[3],*temp_Matrix;
   char **desptr;

   bands=in_Image->bands;
   rows=in_Image->image_ptr[0]->rows;
   cols=in_Image->image_ptr[0]->cols;
   if (rows >= cols) line = cols;
   else line = rows;

   /* Allocate space for temporary reordering variables */
   sspace = (float *)malloc(sizeof(float)*MAX(rows, cols));

   /* allocate float image */
   if(in_Image->image_ptr[0]->data_type!=CVIP_FLOAT) {
      for(i=0; i<in_Image->bands; i++) {
         desmatrix[i]=new_Matrix(rows, cols, CVIP_FLOAT, REAL);
         (void)copy_Matrix(in_Image->image_ptr[i], desmatrix[i]);
	 delete_Matrix(in_Image->image_ptr[i]);
         in_Image->image_ptr[i]=desmatrix[i];
      }
   }

   /* start calling HAAR kernel */
   for(i=0; i<bands; i++) {
      //fprintf(stdout, "Calculating the Haar transform for spectral band #%d\n", (i+1));
      desptr=in_Image->image_ptr[i]->rptr;
      for(j=0; j<rows; j++) {
         if(ibit==1) {
            haar((float *)desptr[j], line, block_size);
            haarnorm((float *)desptr[j], line, block_size);
         }
         else {
            haarnorm((float *)desptr[j], line, block_size);
            haarin((float *)desptr[j], line, block_size);
         }
      }
      temp_Matrix=(MATRIX *)transpose_Matrix(in_Image->image_ptr[i]);
      delete_Matrix(in_Image->image_ptr[i]);
      in_Image->image_ptr[i]=temp_Matrix;
      desptr=in_Image->image_ptr[i]->rptr;
      for(j=0; j<cols; j++) {
         if(ibit==1) {
            haar((float *)desptr[j], rows, block_size);
            haarnorm((float *)desptr[j], rows, block_size);
         }
         else {
            haarnorm((float *)desptr[j], rows, block_size);
            haarin((float *)desptr[j], rows, block_size);
         }
      }
      temp_Matrix=(MATRIX *)transpose_Matrix(in_Image->image_ptr[i]);
      delete_Matrix(in_Image->image_ptr[i]);
      in_Image->image_ptr[i]=temp_Matrix;
   }
   free(sspace);
   /* Create entries in history structure */
   stuff = (HISTORY)malloc(sizeof(struct history));
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
   if(ibit==1) { /* Forward HAAR */
      stuff->ftag=HAAR;
   }
   else if(ibit==0) {        /* Inverse HAAR */
      stuff->ftag=I_HAAR;
   }
   history_add(in_Image, stuff);

   return(in_Image);
}


static void 
haar(
	float		*datain, 
	unsigned	nn, 
	int		block_size
)
{
   int i, j, nmax, nhalf, noblocks, blockno, offset;

   noblocks=nn/block_size;

   for(blockno=0; blockno<noblocks; blockno++) {
      offset=blockno*block_size;
      nmax = block_size;
      while(nmax>=2) {
         nhalf=nmax/2;
         for(i=0; i<nhalf; i++) {
            j=2*i;
            sspace[i+offset]=datain[j+offset]+datain[j+1+offset];
         }
         for(i=nhalf; i<nmax; i++) {
            j=2*(i-nhalf);
            sspace[i+offset]=datain[j+offset]-datain[j+1+offset];
         }
         for(i=0; i<nmax; i++) {
            datain[i+offset]=sspace[i+offset];
         }
         nmax/=2;
      }
   }

   /* Divide input space sequence by # of samples */
   for(i=0; i<nn; i++) {
      datain[i]/=(float)block_size;
   }
}

static void 
haarin(
	float		*datain, 
	unsigned	nn, 
	int		block_size
)
{
   int i, mmax, mhalf, noblocks, blockno, offset;

   noblocks=nn/block_size;

   for(blockno=0; blockno<noblocks; blockno++) {
      offset=blockno*block_size;   
      mmax=2;
      while(mmax<=block_size) {
         mhalf=mmax/2;
         for(i=0; i<mmax; i+=2) {
            sspace[i+offset]=datain[i/2+offset]+datain[i/2+mhalf+offset];
         }
         for(i=1; i<mmax; i+=2) {
            sspace[i+offset]=datain[i/2+offset]-datain[i/2+mhalf+offset];
         }
         for(i=0; i<mmax; i++) {
            datain[i+offset]=sspace[i+offset];
         }
         mmax*=2;
      }
   }
   /* Still hasn't been scaled!! */
}


static void 
haarnorm(
	float		*datain, 
	unsigned	nn, 
	int		block_size
)
{
   int i, istep, istart, inext, blockno, noblocks, offset;
   float factor;

   noblocks=nn/block_size;

   for(blockno=0; blockno<noblocks; blockno++) {
      offset=blockno*block_size;
      factor=1;
      istep=2;
      istart=2;
      inext=4;
      while(inext<=block_size) {
         factor*=SQRT2;
         for(i=istart; i<inext; i++) {
            datain[i+offset]*=factor;
         }
         istart+=istep;
         istep*=2;
         inext=istart+istep;
      }
   } 
}


