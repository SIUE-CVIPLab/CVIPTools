/****************************************************************
*								*
*  ===========================================================  *
*  	 MASTER'S THESIS - ARVE KJOELEN, SIUE			*
*  ===========================================================  *
*								*
*	FILE NAME: wav.c					*
*								*
*	DESCRIPTION: This file contains routines related to 	*
*	performing the wavelet transform of an image.		*
*								*
*	AUTHOR: Arve Kjoelen, SIUE				*
*								*
*	RELATED FILES: wav.h					*
*								*
*	INITIAL CODING DATE: 10/06/93				*
*								*
*	LAST MODIFICATIONS MADE: 10/06/93			*
*								*
*								*
*								*
****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "CVIPimage.h"
#include "CVIPtools.h"
#include "CVIPdef.h"
#include "wavelet.h"
   

/****************************************************************
*								*
*	PGM/ROUTINE NAME: get_wav_filter()			*
*								*
*	DESCRIPTION: This routine, upon being passed a number   *
*	specifying the filter length, returns a pointer to	*
*	a wavelet filter hn.					*
*								*
*	AUTHOR: Arve Kjoelen, SIUE				*
*								*
*	INITIAL CODING DATE: 10/6/93				*
*								*
*	LAST MODIFICATIONS MADE: 10/6/93			*
*								*
****************************************************************/
float *get_wav_filter(int nn) {
   float *hn;
   switch(nn) {
      case 6 : hn = (float *)daub6;
               break;

      case 8 : hn = (float *)daub8;
               break;

      case 10: hn = (float *)daub10;
               break;

      case 12: hn = (float *)daub12;
               break;

      case 14: hn = (float *)daub14;
               break;

      case 16: hn = (float *)daub16;
               break;

      case 18: hn = (float *)daub18;
               break;

      case 20: hn = (float *)daub20;
               break;
   }
   return(hn);
}



/****************************************************************
*								*
*	PGM/ROUTINE NAME: get_bandpass_filter()			*
*								*
*	DESCRIPTION: This routine, upon being passed a pointer  *
*       to a set of filter coefficients for the low-pass	*
*	wavelet filter hn, creates the complementary bandpass	*
*	filter hn from hn.  The	relationship between the two is *
*	hi(n)= (-1)pow(n)*h(N-n), where N is the number of 	*
*	coefficients in hn.					*
*								*
*	AUTHOR: Arve Kjoelen, SIUE				*
*								*
*	INITIAL CODING DATE: 10/6/93				*
*								*
*	LAST MODIFICATIONS MADE: 10/8/93			*
*								*
****************************************************************/
float *get_bandpass_filter(float *hn, int nn) {
   float *hi, isign=1.0;
   int i;

   hi = (float *)malloc(sizeof(float)*nn);

   hi[0]=hn[1];
   hi[1]=-hi[0];
   for(i=2; i<nn; i++) {
      hi[i]=hn[nn-i+1]*isign;
      isign*=-1.0;
   }
   return(hi);
}

/****************************************************************
*								*
*	ROUTINE/PGM NAME: get_transpose_filter()		*
*								*
*	DESCRIPTION: Upon being passed a pointer to a filter, 	*
*	this routine calculates the (frequency-domain) complex	*
*	conjugate transpose filter.  Since we are dealing with	*
*	1-D filters, this corresponds to calculating h(-n) for	*
*	a given h(n) (we're assuming h(n) is periodic).	The	*
*	function returns a pointer to the transpose filter.	*
*								*
*	AUTHOR: Arve Kjoelen					*
*								*
*	INITIAL CODING DATE: 10/8/93				*
*								*
*	LAST MODIFICATIONS MADE: 10/8/93			*
*								*
****************************************************************/
float *get_transpose_filter(float *hn, int nn) {
   float *htrans, isign=-1.0;
   int i;

   htrans = (float *)malloc(sizeof(float)*nn);

   htrans[0]=hn[0];
   for(i=1; i<nn; i++) {
      htrans[i]=hn[nn-i]*isign;
      isign*=-1.0;
   }
   return(htrans);
}



/****************************************************************
*								*
*	PGM/ROUTINE NAME: wav_setup()				*
*								*
*	DESCRIPTION: Setup routine for the wavelet transform.	*
*	This routine passes each color band of the image along	*
*	with the size of that band to the function wavdaub4_transform.	*
*	If the input image is of type byte, it is recast to	*
*	type float.						*
*								*
*	AUTHOR: Arve Kjoelen, SIUE				*
*								*
*	INITIAL CODING DATE: 10/6/93				*
*								*
*	LAST MODIFICATIONS MADE: 10/6/93			*
*								*
****************************************************************/
Image *wav_setup(Image *in_Image, CVIP_BOOLEAN *remap) {
   Image *image;
   MATRIX **matrix;
   char *answer;
   int i, rows, isign, **hptr;
   int choice, fchoice, lowband;
   float *hn, *hi, *htrans, *hitrans;  /* Filters */
   HISTORY stuff;

   image = in_Image;
   if(image->image_ptr[0]->data_type !=CVIP_FLOAT)
      (void) cast_Image(image, CVIP_FLOAT);

   *remap=CVIP_NO;

   /* answer = (char *)malloc(32);  	comment out since memory leak */
   matrix = (MATRIX **)image->image_ptr;
   rows = image->image_ptr[0]->rows;

   /* Check to see if forward transform has already been performed */
   if((history_check(WAVELET, image)) && (!history_check(I_WAVELET, image))) {
      stuff=history_get(image, WAVELET);
      hptr = (int **)stuff->packetP->dptr;
      choice=hptr[0][0];
      fchoice=hptr[1][0];
      isign=-1;
   }
   else {
      answer = (char *)malloc(32);
      fprintf(stdout, "\n=======================================\n");
      fprintf(stdout, "=          WAVELET TRANSFORM          =\n");
      fprintf(stdout, "=======================================\n");
      fprintf(stdout, "1.   Forward Wavelet Transform\n");
      fprintf(stdout, "2.   Inverse Wavelet Transform\n");
      fprintf(stdout, "     Enter your choice ->");
      (void)gets(answer);
      choice=atoi(answer);
      if(choice==1) isign=1;
      else if (choice==2) isign=-1;
      answer[0]='\0';

      fprintf(stdout, "    \nPlease select a basis wavelet:\n");
      fprintf(stdout, " 1. Haar wavelet\n");
      fprintf(stdout, " 2. daub4 wavelet\n");
/*
      fprintf(stdout, " 3. daub6 wavelet\n");
      fprintf(stdout, " 4. daub8 wavelet\n");
      fprintf(stdout, " 5. daub10 wavelet\n");
      fprintf(stdout, " 6. daub12 wavelet\n");
      fprintf(stdout, " 7. daub14 wavelet\n");
      fprintf(stdout, " 8. daub16 wavelet\n");
      fprintf(stdout, " 9. daub18 wavelet\n");
      fprintf(stdout, "10. daub20 wavelet\n");
*/
      (void)gets(answer);
      choice = atoi(answer);

      answer[0]='\0';
      fprintf(stdout, "\nPlease select the number of decomposition levels:\n");
      fprintf(stdout, "1.  4 frequency bands => Smallest band = %dx%d\n",   (rows/2), (rows/2));
      fprintf(stdout, "2.  7 frequency bands => Smallest band = %dx%d\n", (rows/4), (rows/4));
      fprintf(stdout, "3. 10 frequency bands => Smallest band = %dx%d\n", (rows/8), (rows/8));
      fprintf(stdout, "4. 13 frequency bands => Smallest band = %dx%d\n", (rows/16), (rows/16));
      fprintf(stdout, "5. 16 frequency bands => Smallest band = %dx%d\n", (rows/32), (rows/32));
      fprintf(stdout, "6. 19 frequency bands => Smallest band = %dx%d\n", (rows/64), (rows/64));
      (void)gets(answer);
      fchoice = atoi(answer);
      free(answer);
      lowband = rows/(int)(pow(2,(fchoice-1))+0.5);
      fprintf(stdout, "Performing Wavelet Transform...\n");
	}

   switch(choice) {
      case 1 : lowband = (matrix[0]->rows)/ (int)(pow(2,(fchoice-1))+0.5);
               image = (Image *)wavhaar_transform(image, isign, lowband);
               break;

      case 2 : lowband = (matrix[0]->rows)/ (int)(pow(2,(fchoice-1))+0.5);
               image = (Image *)wavdaub4_transform(image, isign, lowband);
               break; 
   }

   if(choice>10) {
      fprintf(stdout, "choice=%d\n", choice);
      fprintf(stdout, "Invalid selection\n");
   }
   if((choice>2)&&(choice<11)) {
      fprintf(stdout, "Function Not Supported\n");
      return(image);
/*      hn = get_wav_filter(2*choice);
      hi = get_bandpass_filter(hn, 2*choice);
      htrans = get_transpose_filter(hn, 2*choice);
      hitrans = get_transpose_filter(hi, 2*choice);
      for(i=0; i<image->bands; i++) wavtgeneric(matrix[i], matrix[i]->rows, isign, lowband, 2*choice, htrans, hitrans);
*/
   }
   /* Add history information */
   stuff=(HISTORY)NULL;
   stuff=(HISTORY)malloc(sizeof(struct history));
   stuff->packetP = (PACKET *)malloc(sizeof(PACKET));
   stuff->packetP->dsize=2;
   stuff->packetP->dtype=(CVIP_TYPE *)malloc(sizeof(CVIP_TYPE)*2);
   stuff->packetP->dtype[0]=CVIP_INTEGER;
   stuff->packetP->dtype[1]=CVIP_INTEGER;
   hptr=(int **)NULL;
   hptr=(int **)malloc(sizeof(int *)*2);
   hptr[0]=(int *)malloc(sizeof(int));
   hptr[1]=(int *)malloc(sizeof(int));
   hptr[0][0]=(int)choice;
   hptr[1][0]=(int)fchoice;
   stuff->packetP->dptr=(void **)hptr;
   stuff->next=(HISTORY)NULL;
   if(isign==1) stuff->ftag=WAVELET;
   else if(isign==-1) stuff->ftag=I_WAVELET;
   history_add(image, stuff);
   return(image);
}



/****************************************************************
*								*
*	ROUTINE/PGM NAME: wavhaar_transform()			*
*								*
*	DESCRIPTION: setup routine for the Haar wavelet trans-	*
*	form.  Extracts from the image a row or column to be	*
*	transformed, and calls the Haar wavelet transform 	*
*	kernel.							*
*								*
*	AUTHOR: Arve Kjoelen, SIUE				*
*								*
*	INITIAL CODING DATE: 10/11/93				*
*								*
*	LAST MODIFICATIONS MADE: 10/12/93			*
*								*
****************************************************************/
Image *wavhaar_transform(Image *image, int isign, int lowband) {
   unsigned nn, n;
   int i, k,
		rows = getNoOfRows_Image(image),
		cols = getNoOfCols_Image(image);
   float **a, *wksp;
   MATRIX *matrix;

	n = (rows > cols) ? rows : cols;
	if (rows != cols) zero_pad(image, n, n);
  	wksp = (float *) malloc(sizeof(float)*n);

   for(k=0; k<image->bands; k++) {
      matrix=(MATRIX *)image->image_ptr[k];
      a = (float **)matrix->rptr;
      if(n<lowband) return(NULL);
      if(isign>=0) {	 /* Wavelet transform. */
         /* Start at largest hierarchy, and work towards smallest. */
         for(nn=n; nn>=lowband; nn>>=1) {
            for(i=0; i<nn; i++) do_haarwavl(a[i], wksp, nn, isign);
            partial_transpose(matrix, nn);
            for(i=0; i<nn; i++) do_haarwavl(a[i], wksp, nn, isign);
            partial_transpose(matrix, nn);
         } 
      }
      else {          	 /* Inverse Wavelet Transform. */
         /* Start at smallest hierarchy, and work towards largest. */
         for(nn=(unsigned)lowband; nn<=n; nn<<=1) {
            for(i=0; i<nn; i++) do_haarwavl(a[i], wksp, nn,isign);
            partial_transpose(matrix, nn);
            for(i=0; i<nn; i++) do_haarwavl(a[i], wksp, nn,isign);
            partial_transpose(matrix, nn);
         } 
      }
   }
   free(wksp);
   return(image);
}




/****************************************************************
*								*
*	PGM/ROUTINE NAME: eavdaub4_transform			*
*								*
*	DESCRIPTION: This routine extracts from an image color	*
*	band the right rows and columns to be wavelet-		*
*	transformed by do_daub4.  As such, it goes through the	*
*	entire image band recursively, until the desired	*
*	number of decomposition levels has been computed.	*
*	The routine performs the inverse wavelet transform when	*
*	called with isign=-1 as an argument.  In that case, it 	*
*	works from the lowest level until the image is 		*
*	completely reconstructed.				*
*								*
*	AUTHOR: Arve Kjoelen, SIUE				*
*								*
*	INITIAL CODING DATE: 9/1/93				*
*								*
*	LAST MODIFICATIONS MADE: 10/6/93			*
*								*
*								*
****************************************************************/
Image *wavdaub4_transform(Image *image, int isign, int lowband) {
   unsigned nn, n;
   int i, k,
		rows = getNoOfRows_Image(image),
		cols = getNoOfCols_Image(image);
   float **a, *wksp;
   MATRIX *matrix;

	n = (rows > cols) ? rows : cols;
	if (rows != cols) zero_pad(image, n, n);
  	wksp = (float *) malloc(sizeof(float)*n);

   for(k=0; k<image->bands; k++) {
      matrix=(MATRIX *)image->image_ptr[k];
      a = (float **)matrix->rptr;
      if(n<lowband) return(NULL);
      if(isign>=0) {	 /* Wavelet transform. */
         /* Start at largest hierarchy, and work towards smallest. */
         for(nn=n; nn>=lowband; nn>>=1) {
            for(i=0; i<nn; i++) do_daub4(a[i], wksp, nn, isign);
            partial_transpose(matrix, nn);
            for(i=0; i<nn; i++) do_daub4(a[i], wksp, nn, isign);
            partial_transpose(matrix, nn);
         } 
      }
      else {          	 /* Inverse Wavelet Transform. */
         /* Start at smallest hierarchy, and work towards largest. */
         for(nn=(unsigned)lowband; nn<=n; nn<<=1) {
            for(i=0; i<nn; i++) do_daub4(a[i], wksp, nn,isign);
            partial_transpose(matrix, nn);
            for(i=0; i<nn; i++) do_daub4(a[i], wksp, nn,isign);
            partial_transpose(matrix, nn);
         } 
      }
   }
   free(wksp);
   return(image);
}


/****************************************************************
*								*
*	ROUTINE/PGM NAME: wavtgeneric()				*
*								*
*	DESCRIPTION: This routine extracts one row (or column)	*
*	at a time from an image and passes a pointer to the	*
*	first element in this row/column) to a generic wavelet	*
*	transform routine.  This routine can currently support	*
*	all the basis wavelets described in Daubechies: 	*
*	"Orthonormal Bases for Compactly Supported Wavelets".	*
*	This function performs the wavelet decomposition for	*
*	the filter lengths of 6, 8, 10, 12, 14, 16, 18 and 20	*
*	taps.							*
*								*
*	AUTHOR: Arve Kjoelen, SIUE				*
*								*
*	INITIAL CODING DATE: 10/8/93				*
*								*
*	LAST MODIFICATIONS MADE: 10/8/93			*
*								*
****************************************************************/
void wavtgeneric(MATRIX *matrix, unsigned n, int isign,
	int lowband, int filter_size, float *lpf, float *hpf) {
   unsigned nn;
   int i;
   float **a, *wksp;
   int center;

   wksp = (float *)malloc(sizeof(float)*nn);
   center = filter_size/2 - 1;

   if(n<lowband) return;
   if(n<filter_size) {
      fprintf(stdout, "Smallest band cannot be smaller than the filter size\n");
      if(isign<0) n<<=1;
      return;
   }
   

   a = (float **)matrix->rptr;


   if(isign>=0) {	 /* Wavelet transform. */
      /* Start at largest hierarchy, and work towards smallest. */
      for(nn=n; nn>=lowband; nn>>=1) {
         for(i=0; i<nn; i++) do_wavtgeneric(a[i], wksp, nn, isign, filter_size, lpf, hpf, center);
         partial_transpose(matrix, nn);
         for(i=0; i<nn; i++) do_wavtgeneric(a[i], wksp, nn, isign, filter_size, lpf, hpf, center);
         partial_transpose(matrix, nn);
      } 
   }
   else {          	 /* Inverse Wavelet Transform. */
      /* Start at smallest hierarchy, and work towards largest. */
      for(nn=(unsigned)lowband; nn<=n; nn<<=1) {
         for(i=0; i<nn; i++) do_wavtgeneric(a[i], wksp, nn, isign, filter_size, lpf, hpf, center);
         partial_transpose(matrix, nn);
         for(i=0; i<nn; i++) do_wavtgeneric(a[i], wksp, nn, isign, filter_size, lpf, hpf, center);
         partial_transpose(matrix, nn);
      } 
   }
   free(wksp);
}


/****************************************************************
*								*
*	PGM/ROUTINE NAME: do_wavtgeneric()			*
*								*
*	DESCRIPTION: THis routine applies a wavelet filter	*
*	pair,  specified by the two pointers passed to it, to	*
*	one row of the image.  The routine performs the wavelet	*
*	transform in the spatial domain, yielding optimal	*
*	computational complexity for n<14 approx.		*
*								*
*	AUTHOR: Arve Kjoelen					*
*								*
*	INITIAL CODING DATE: 10/8/93				*
*								*
*	LAST MODIFICATIONS MADE: 10/8/93			*
*								*
****************************************************************/
void do_wavtgeneric(float *a, float *wksp, unsigned n, int isign,
	int filter_size, float *lpf, float *hpf, int center) {
   unsigned nh, i, j, k;

   if(n<filter_size) return;

   nh=n>>1;

   if(isign>0) {	/* Filter and decimate in one step */
      for(i=center,j=0; i<nh; j+=2, i++) {
         wksp[i]=0.0;
         wksp[(i%nh)+nh]=0.0;
         for(k=0; k<filter_size; k++) {
            wksp[i%nh]+=lpf[k]*a[(j+k)%n];
            wksp[(i%nh)+nh]+=hpf[k]*a[(j+k)%n];
         }
      }      
   }
   else {		/* Reconstruct - Use transpose filters */
      for(i=center,j=0; i<nh; i++) {
         wksp[j%n]=0.0;
         for(k=0; k<filter_size; k++) {
            wksp[j%n]+=lpf[k]*a[k+i];
         }
         j++;
         wksp[j%n]=0.0;
         for(k=0; k<filter_size; k++) {
            wksp[j%n]+=hpf[k]*a[k+i];
         }
         j++;
      }
   }
   for(i=0; i<n; i++) a[i]=wksp[i];
}



/****************************************************************
*								*
*	PGM/ROUTINE NAME: do_daub4				*
*								*
*	DESCRIPTION: This routine applies the daub4 filter to	*
*	the input data vector when isign=1, and applies its	*
*	transpose when isign is -1.  It is called 		*
*	hierarchically by wavdaub4_transform.  Note that the routine	*
*	performs the wavelet transform in the spatial domain.	*
*	This is faster than performing the transform in the	*
*	Fourier domain when the filter length is small.		*
*								*
*	AUTHOR: Arve Kjoelen, SIUE				*
*								*
*	INITIAL CODING DATE: 9/1/93				*
*								*
*	LAST MODIFICATIONS MADE: 10/6/93			*
*								*
*								*
****************************************************************/
void do_daub4(float *a, float *wksp, unsigned n, int isign)
{
   unsigned nh, i, j;

   if(n<4) return;

   nh=n>>1;
   if(isign>0) {	/* Filter and decimate in one step */
      for(i=1,j=0; i<nh; j+=2, i++) {
         wksp[i] = C0*a[j] + C1*a[j+1] + C2*a[j+2] + C3*a[j+3];
         wksp[i+nh] = C3*a[j] - C2*a[j+1] + C1*a[j+2] - C0*a[j+3];
      }
      /* Take care of edges */
      wksp[0] = C0*a[n-2] + C1*a[n-1] + C2*a[0] + C3*a[1];
      wksp[nh] = C3*a[n-2] - C2*a[n-1] + C1*a[0] - C0*a[1];      
   }
   else {		/* Reconstruct - Use transpose filters */
      for(i=1,j=0; i<nh; i++) {
         wksp[j++] = C2*a[i-1] + C1*a[i+nh-1] + C0*a[i] + C3*a[i+nh];
         wksp[j++] = C3*a[i-1] - C0*a[i+nh-1] + C1*a[i] - C2*a[i+nh];
      }
      wksp[n-2] = C2*a[nh-1] + C1*a[n-1] + C0*a[0] + C3*a[nh];
      wksp[n-1] = C3*a[nh-1] - C0*a[n-1] + C1*a[0] - C2*a[nh];
   }
   for(i=0; i<n; i++) a[i]=wksp[i];
}


void do_haarwavl(float *a, float *wksp, unsigned n, int isign) {
   unsigned nh, i, j;

   if(n<2) return;

   nh=n>>1;

   if(isign>0) {	/* Filter and decimate in one step */
      for(i=0,j=0; i<nh; j+=2, i++) {
         wksp[i] = SQRT2OVER2*(a[j] + a[j+1]);
         wksp[i+nh] = SQRT2OVER2*(a[j] - a[j+1]);
      }   
   }
   else {		/* Reconstruct - Use transpose filters */
      for(i=0,j=0; i<nh; i++) {
         wksp[j++] = SQRT2OVER2*(a[i] + a[i+nh]);
         wksp[j++] = SQRT2OVER2*(a[i] - a[i+nh]);
      }
   }
   for(i=0; i<n; i++) a[i]=wksp[i];
}



/************************************************************************
*									*
*	ROUTINE/PGM NAME: partial_transpose()				*
*									*
*	DESCRIPTION: performs a partial transpose of a matrix.  Only	*
*	the part ranging from i=0 to N, where N is a number passed to	*
*	partial_transpose.  The routine works for floating-point 	*
*	images only.							*
*									*
*	AUTHOR: Arve Kjoelen, SIUE					*
*									*
*	INITIAL CODING DATE: 10/6/93					*
*									*
*	LAST MODIFICATIONS MADE:					*
*									*
************************************************************************/
void partial_transpose(MATRIX *matrix, int nn) {
   int i,j;
   float **rptr, temp;

   if(nn>(int)matrix->rows) {
      fprintf(stderr, "Error: attempt to do partial transpose of matrix\n");
      fprintf(stderr, "failed due to argument bigger than the matrix size.\n");
      return;
   }

   rptr = (float **)matrix->rptr;
   for(i=0; i<nn; i++) {
      for(j=0; j<i; j++) {
         temp=rptr[i][j];
         rptr[i][j]=rptr[j][i];
         rptr[j][i]=temp;
      }
   }
}
