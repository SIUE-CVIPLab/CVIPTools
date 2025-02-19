/*****************************************************************************
 * ======================================================================    *
 * Image Processing/Computer Vision Tool Project - Dr. Scott Umbaugh SIUE    *
 * ======================================================================    *
 *                                                                           *
 * ROUTINE/PGM NAME: xform_util.c                                            *
 *                                                                           *
 *              DESCRIPTION: This file contains several functions that are   *
 * needed for performing forward and inverse fft. They are sort of           *
 * transparent to the programmer who use fft_transform() or ifft_transform().*
 *                                                                           *
 * 1996/12/28/: Several utiliy functions in xform_setup.c are moved here, so *
 * this file servers as a general utility file for all transforms.           *
 *                                                                           *
 *                   AUTHOR: Simon Low                                       *
 *                                                                           *
 *            RELATED FILES: fft.c, fourn.c, filter.c.                       *
 *                                                                           *
 *              CODING DATE: 1/15/92                                         *
 *  LAST MODIFICATIONS MADE: 11/16/94                                        *
 *                           revised by Kun Luo in November, 1994 to make    *
 *                           those functions work with the new fft and ifft  *
 *                                                                           *
 *                                                                           *
 *****************************************************************************
RCS (Revision Control System) Information - Added automatically by RCS)

$Author: smakam $
$Date: 1997/07/06 20:06:22 $
$Source: /home/cvip/cvipapps/CVIPtools3.6/TRANSFORMS/RCS/xform_util.c,v $
$Header: /home/cvip/cvipapps/CVIPtools3.6/TRANSFORMS/RCS/xform_util.c,v 1.19 1997/07/06 20:06:22 smakam Exp $

*******************************************************************************/
/* Define Preprocessor statements */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "CVIPimage.h"
#include "CVIPtransform.h"

static void xsform_2_image(Image *in_Image, float data1[], int h, int w, int xx,
	int yy, int which_PLANE, int block_size);
static void fft(float indata[], int nn[], int ndim, int isign);

void manager(Image *in_Image, float data[], FFT_DIRECTION direction,
	int which_PLANE, int block_size)
{
  int a, b, inc;
  int x, y, xx=0, yy=0, i, j;
  int *arr, nofblk, Hnofblk;
  int nn[3], h, w, Hcounter=1;
  float *arrptr;

  h = in_Image->image_ptr[0]->rows;
  w = in_Image->image_ptr[0]->cols;

  nofblk=(w/block_size)*(h/block_size);
  Hnofblk=w/block_size;
  /*consta =w/Hnofblk;*/
  
  /* pointer to blk array */

  arrptr = (float *) calloc(block_size*2*block_size+1, sizeof(float));
  arr = (int *) calloc(block_size*2*block_size+1, sizeof(int));

  nn[1] = block_size; nn[2] = block_size;  /* always == block_size ? */
  a=1; inc = 1;

  for(x=1; x<= nofblk; ){

      i=1;inc=1;
      while(inc <= block_size) { /* inc = nof row per blk read */
        for(y=a; y< (a+block_size*2); y++){
          arrptr[i]= data[y];
          arr[i]= y; i++;    /* memorize the coordinates used in data */        }
        b = a;
        a+=Hnofblk*block_size*2;  /* a = new start value */
        inc++;
      }  /* end while  */

      x++;    /* one block done */

      if (direction == FORWARD)
        fft(arrptr, nn, 2, 1);

      if(direction == INVERSE)
        fft(arrptr, nn, 2, -1);

      Hcounter++;     /* counter to keep track of Hori Blk performed */

      for(j=1; j <= block_size*block_size*2 ;j++){
        data[arr[j]]= arrptr[j]; /* arr stored the correct cordinates r data*/
      }

      if(direction == INVERSE) {
        xsform_2_image(in_Image, arrptr, h, w, xx, yy, which_PLANE,block_size);

        if(Hcounter > Hnofblk){
          xx += block_size; /* consta;*/
          yy  = 0;
        } else
          yy+= block_size;
      }
        if( Hcounter <= Hnofblk)
          a = b-(block_size-1)*(w*2)+block_size*2;
        else {
           a = b + block_size*2;
           Hcounter = 1;  /*  reset Hcounter after Hnofblk has  */
        }
  }
free(arrptr);
free(arr);
 
}

/* routine to copy input array to data[]
   data are shifted to the center first
   by means of the variable si.  The shift
   is (-1)pow(x+y).

  since data[] is calloc'ed, not malloc'ed, it need not ever be
  set to zero here.
*/

void shift_n_copy(Image *input_Image, float data[], int which_PLANE)
{
  int x=0, y, i=1, rows, cols, compl, si, datasize;

  rows = input_Image->image_ptr[0]->rows;
  cols=input_Image->image_ptr[0]->cols;
  datasize=rows*cols*2;
  compl= (input_Image->image_ptr[0]->data_format==COMPLEX) ? 1 : 0;

  while( i<=datasize) {
      while ( x< rows ){
	 switch(input_Image->image_ptr[0]->data_type) {
            case CVIP_BYTE:
	       for(y=0; y<cols; y++) {
		  si = ((x+y)&0x01) ? -1 : 1;
		  data[i]=(si>0) ? (float)((byte **)input_Image->image_ptr[which_PLANE]->rptr)[x][y] : -(float)((byte **)input_Image->image_ptr[which_PLANE]->rptr)[x][y];
		  if(compl>0) {
		     data[i+1]=(si>0) ? (float)((byte **)input_Image->bandP[which_PLANE]->rptr)[x][y] : -(float)((byte **)input_Image->image_ptr[which_PLANE]->rptr)[x][y];
		  }
		  i+=2;
	       }
	       break;
            case CVIP_SHORT:
               for(y=0; y<cols; y++) {
                  si = ((x+y)&0x01) ? -1 : 1;
                  data[i]=(si>0) ? (float)((short **)input_Image->bandP[which_PLANE]->rptr)[x][y] : (float)-((short **)input_Image->image_ptr[which_PLANE]->rptr)[x][y];
                  if(compl>0) {
                     data[i+1]=(si>0) ? (float)((short **)input_Image->bandP[which_PLANE]->rptr)[x][y] : (float)-((short **)input_Image->image_ptr[which_PLANE]->rptr)[x][y];
                  }
                  i+=2;
               }
               break;
            case CVIP_INTEGER:
               for(y=0; y<cols; y++) {
                  si = ((x+y)&0x01) ? -1 : 1;
                  data[i]=(si>0) ? (float)((int **)input_Image->image_ptr[which_PLANE]->rptr)[x][y] : (float)-((int **)input_Image->image_ptr[which_PLANE]->rptr)[x][y];
                  if(compl>0) {
                     data[i+1]=(si>0) ? (float)((int **)input_Image->bandP[which_PLANE]->rptr)[x][y] : (float)-((int **)input_Image->image_ptr[which_PLANE]->rptr)[x][y];
                  }
                  i+=2;
               }
               break;
            case CVIP_FLOAT:
               for(y=0; y<cols; y++) {
                  si = ((x+y)&0x01) ? -1 : 1;
                  data[i]=(si>0) ? ((float **)input_Image->bandP[which_PLANE]->rptr)[x][y] : -((float **)input_Image->image_ptr[which_PLANE]->rptr)[x][y];
                  if(compl>0) {
                     data[i+1]=(si>0) ? ((float **)input_Image->bandP[which_PLANE]->rptr)[x][y] : -((float **)input_Image->image_ptr[which_PLANE]->rptr)[x][y];
                  }
                  i+=2;
               }
               break;
            case CVIP_DOUBLE:
               for(y=0; y<cols; y++) {
                  si = ((x+y)&0x01) ? -1 : 1;
                  data[i]=(si>0) ? (float)((double **)input_Image->image_ptr[which_PLANE]->rptr)[x][y] : (float)-((double **)input_Image->image_ptr[which_PLANE]->rptr)[x][y];
                  if(compl>0) {
                     data[i+1]=(si>0) ? (float)((double **)input_Image->bandP[which_PLANE]->rptr)[x][y] : (float)-((double **)input_Image->image_ptr[which_PLANE]->rptr)[x][y];
                  }
                  i+=2;
               }
               break;
	 }
        x++;
      }
   }
}

/* routine to convert inverse-transformed data back to image */

static void xsform_2_image(Image *in_Image, float data1[], int h, int w,
	int xx, int yy, int which_PLANE, int block_size)
{
  float n;
  int x, y, i, si;

  n = 1.0/(float)(block_size*block_size);  /* image size*/
  i=1;

   for(x=xx; x< xx+block_size; x++)
    for(y=yy; y< yy+block_size; y++) {

      si = ((x+y)&0x01) ? -1 : 1;
      ((float **)(in_Image->image_ptr[which_PLANE]->rptr))[x][y] = si>0 ? (data1[i]*n) : -(data1[i]*n);
      i+= 2;
    }
}

/* check to make sure that the image is REAL, and the dimension is power of 2,
 * which is required by other transforms, except fft
 */
CVIP_BOOLEAN image_check(Image *image) {
   CVIP_BOOLEAN dims;
   int rows, cols;

   /* Make sure the data is REAL */
   if(image->image_ptr[0]->data_format == COMPLEX) {
      fprintf(stderr, "Your data is complex, and cannot be processed using this real-valued transform\n");
      return(CVIP_NO);
   }

   rows = image->image_ptr[0]->rows;
   cols = image->image_ptr[0]->cols;

   dims = check_pow_two((int)rows);
   if(dims) {
      dims = check_pow_two((int)cols);
      if(dims) {
         return(CVIP_YES);
      }
   }
   return(CVIP_NO);
}


/* This little handy routine takes any number and */
/* Checks whether the number is an integer power  */
/* of 2.  If it is, it returns CVIP_YES, if not, it   */
/* returns CVIP_NO.				  */
CVIP_BOOLEAN check_pow_two(int number) {
   int count;

   for(count=1; count<15; count++) {
      if(number == pow(2, count)) {
         return(CVIP_YES);
      }
   }
   return(CVIP_NO);
}

/************************************************************************
*									*
*	ROUTINE/PGM NAME: get_block_size()				*
*									*
*	DESCRIPTION:	This routine asks for a block size, and checks	*
*			whether it is a power of two before returning	*
*			the blocksize.  				*
*									*
*	AUTHOR:		Arve Kjoelen, SIUE				*
*									*
*	INITIAL CODING DATE: 02/22/94					*
************************************************************************/
int get_block_size(void) {
   int block_size;
   char *answer;
   CVIP_BOOLEAN check_block;
   
   answer = (char *)malloc(5);
   do {
      fflush(stdin);
      fprintf(stdout, "Please enter desired block size\n");
      fprintf(stdout, "4 = 4x4, 8 = 8x8, etc\n");

      (void)gets(answer);
      block_size = atoi(answer);
//      free(answer); /*duplicate free memory*/
      check_block=check_pow_two(block_size);
   }  while(!check_block);

   free(answer);
   return(block_size);
}

/************************************************************************
*									*
*	ROUTINE/PGM NAME: get_zpad_dims()				*
*									*
*	DESCRIPTION:	This routine determines the dimensions to which *
*	the passed image should be zero-padded.  These dimensions are	*
*	determined from the current image size and the desired 		*
*	blocksize.  If the routine determines that no zero-padding is	*
*	needed, it returns a CVIP_BOOLEAN CVIP_NO.  If zero-padding is needed,	*
*	the CVIP_BOOLEAN CVIP_YES is returned, and the dimensions to which the	*
*	image should be zero-padded are contained in *n_rows and 	*
*	*n_cols.							*
*									*
*	AUTHOR: Arve Kjoelen, SIUE					*
*									*
*	INITIAL CODING DATE: 06/16/94					*
*									*
************************************************************************/
CVIP_BOOLEAN get_zpad_dims(Image *image, int *n_rows, int *n_cols, int block_size) {

   *n_rows=block_size; *n_cols=block_size;
   if((block_size > image->image_ptr[0]->rows) || (block_size > image->image_ptr[0]->cols)) {
	return(CVIP_YES);
      if(image_check(image)) { /* Image has power-of-two dims */
         /*fprintf(stderr, "ERROR: Your blocksize is too large!!\n");
         block_size = get_block_size();*/
      }
      else {
         if((!check_pow_two(image->image_ptr[0]->rows)) && (!check_pow_two (image->image_ptr[0]->cols))) {
            /* Neither rows nor cols has pow-of-two dims   */
            /* so zeropad image to blocksize by blocksize  */
            if(image->image_ptr[0]->rows>block_size)
               *n_rows=2*block_size;
            else 
               *n_rows=block_size;
            if(image->image_ptr[0]->cols>block_size) 
               *n_cols=2*block_size;
            else 
               *n_cols=block_size;
         }
         else if(!check_pow_two(image->image_ptr[0]->rows)) {
            /* no_of_rows is not pow_of_two, so zero-pad */
            /* no_of_rows to blocksize.		     */
            *n_rows=block_size;
            if(image->image_ptr[0]->cols<block_size)
               *n_cols=block_size;
            else
               *n_cols=image->image_ptr[0]->cols;
         }
         else {
            /* no_of_cols is not pow_of_two, so zero-pad */
            /* no_of_cols to blocksize.		     */
            *n_cols=block_size;
            if(image->image_ptr[0]->rows<block_size)
               *n_rows=block_size;
             else
               *n_rows=image->image_ptr[0]->cols;
         }
      }
   }
   /* If we made it here, the blocksize is smaller than both     */
   /* the number of rows and the number of columns in the image. */
   /* At the same time, neither the number of rows nor the       */ 
   /* number of columns in the image is an integer power of 2.   */
   /* Now, the task becomes extending the image so that its      */
   /* dimensions become integer multiples of the blocksize.      */
   else { /* blocksize smaller than rows and smaller than cols */
      *n_rows=(image->image_ptr[0]->rows)%block_size;
      *n_cols=(image->image_ptr[0]->cols)%block_size;
      if(*n_rows || *n_cols) { /* Must extend image dimensions */   
         if(*n_rows) { 
            *n_rows=block_size-(*n_rows);
            *n_rows+=image->image_ptr[0]->rows;
         }
         else 
            *n_rows=image->image_ptr[0]->rows;
         if(*n_cols) {
            *n_cols=block_size-(*n_cols);
            *n_cols+=image->image_ptr[0]->cols;
         }
         else 
            *n_cols=image->image_ptr[0]->cols;
      }
      else {
            *n_rows=image->image_ptr[0]->rows;
            *n_cols=image->image_ptr[0]->cols;
           }

      if(*n_cols==image->image_ptr[0]->cols && *n_rows==image->image_ptr[0]->rows)
         return(CVIP_NO); /* Do not zero-pad */
      else 
         return(CVIP_YES);  /* zero_pad */
   }
   return(CVIP_NO);
}

/* author: Numerical Recipe in C                                             */
/* date written: Feb 11, 1991                                                */
/* moved here from fourn.c */


#define FFTSWAP(a,b) tempr=(a);(a)=(b);(b)=tempr

static void fft(float indata[], int nn[], int ndim, int isign)
/*int nn[3],ndim,isign;
 float indata[]; */
/*float indata[nn[1]*nn[2]*2]; */
{
  int i1,i2,i3,i2rev,i3rev,ip1,ip2,ip3,ifp1,ifp2;
  int ibit,idim,k1,k2,n,nprev,nrem,ntot;
  float tempi,tempr;
  double theta,wi,wpi,wpr,wr,wtemp;


  ntot=1;

  for (idim=1;idim<=ndim;idim++)
    ntot *= nn[idim];
    nprev=1;
    for (idim=ndim;idim>=1;idim--) {
      n=nn[idim];
      nrem=ntot/(n*nprev);
      ip1=nprev << 1;
      ip2=ip1*n;
      ip3=ip2*nrem;
      i2rev=1;
      for (i2=1;i2<=ip2;i2+=ip1) {
        if (i2 < i2rev) {
          for (i1=i2;i1<=i2+ip1-2;i1+=2) {
            for (i3=i1;i3<=ip3;i3+=ip2) {
              i3rev=i2rev+i3-i2;
                FFTSWAP(indata[i3],indata[i3rev]);
                FFTSWAP(indata[i3+1],indata[i3rev+1]);
            }
          }
        }
        ibit=ip2 >> 1;
        while (ibit >= ip1 && i2rev > ibit) {
          i2rev -= ibit;
          ibit >>= 1;
        }
        i2rev += ibit;
      }
      ifp1=ip1;
      while (ifp1 < ip2) {
        ifp2=ifp1 << 1;
        theta=isign*6.28318530717959/(ifp2/ip1);
        wtemp=sin(0.5*theta);
        wpr = -2.0*wtemp*wtemp;
        wpi=sin(theta);
        wr=1.0;
        wi=0.0;
        for (i3=1;i3<=ifp1;i3+=ip1) {
          for (i1=i3;i1<=i3+ip1-2;i1+=2) {
            for (i2=i1;i2<=ip3;i2+=ifp2) {
              k1=i2;
              k2=k1+ifp1;
              tempr=wr*indata[k2]-wi*indata[k2+1];
              tempi=wr*indata[k2+1]+wi*indata[k2];
              indata[k2]=indata[k1]-tempr;
              indata[k2+1]=indata[k1+1]-tempi;
              indata[k1] += tempr;
              indata[k1+1] += tempi;
             }
            }
            wr=(wtemp=wr)*wpr-wi*wpi+wr;
            wi=wi*wpr+wtemp*wpi+wi;
          }
          ifp1=ifp2;
      }
      nprev *= n;
   }
/*printf("\nin fft indata[%d] = %f, indata[%d]= %f\n",131072,
indata[131072],131073, 
indata[131073]); */

}

#undef FFTSWAP
