/************************************************************************
*									*
* ===================================================================== *
*    COMPUTER VISION/Image PROCESSING TOOL - Dr. Scott Umbaugh, SIUE	*
* =====================================================================	*
*									*
*	FILE NAME: LBG_utils.c						*
*									*
*	Contains utility routines needed to implement the LBG Vector	*
*	Quantization algorithm.						*
*									*
*	LIST OF FUNCTIONS:						*
*	-----------------						*
*	fband_pct()							*
*	downsample()							*
*	reconstruct()							*
*	get_lbg_scheme()						*
*	block_to_vec()							*
*	vec_to_block()							*
*	encode_data()							*
*	compute_centroid()						*
*	LBG_error()							*
*	allocate_vectors()						*
*	do_decoding()							*
*	free_info()							*
*	save_codebook()							*
*	load_lbg_book()							*
*	lbg_save()							*
*	lbg_decompress()						*
*									*
*	AUTHOR: Arve Kjoelen, Southern Illinois University Edwardsville	*
*									*
*	INITIAL CODING DATE: 02/24/94					*
*									*
************************************************************************/
#include <stdio.h>
#include "CVIPimage.h"
#include "LBG.h"

/************************************************************************
*									*
*	ROUTINE/PGM NAME: fband_pct()					*
*									*
*	DESCRIPTION: This routine performs the Principal Components	*
*	transform on groups of three related frequency bands of a	*
*	wavelet-transformed image.					*
*									*
*	VARIABLES PASSED:						*
*		=>Image *image - a pointer to the image.		*
*		=>byte where - a byte value indicating the groups of	*
*	frequency bands on which the PCT is to be performed.  'where'	*
* 	is the logical OR of the following:				*
*			1 if the PCT is to be performed on group 1 of	*
*	frequency bands (fbands 1, 2 and 3).				*
*			2 if the PCT is to be performed on group 2 of	*
*	frequency bands (fbands 4, 5 and 6).				*
*			4 if the PCT is to be performed on group 3 of	*
*	frequency bands (fbands 7, 8 and 9).				*
*	Thus, if one wishes to perform the PCT on group 1 and group 3	*
*	of an image one must call this function with the argument 	*
*	'where' equal to 5 (1|4).					*
*		=>VQ_INFO info - a pointer to a VQ structure which can	*
*	
*									*
*	AUTHOR: Arve Kjoelen, Southern Illinois University at		*
*	Edwardsville.  PCT functions written by Greg Hance, Southern 	*
*	Illinois University at Edwardsville.				*
*									*
*	INITIAL CODING DATE: 04/20/94					*
*									*
*	LAST MODIFICATIONS MADE: 04/21/94				*
*									*
************************************************************************/
void fband_pct(Image *image, byte where, VQ_INFO info) {
   int rows, cols;	/* Number of rows, columns in each spectral band */
   int fbands;		/* Number of frequency bands from wavelet transform */
   int i, k, no_pcts, x, y, z, j; /* Counter variables */
   int t;		/* Number of groups of fbands in wavelet transform */
   int rmin, rmax, cmin, cmax; /* Limits on location of fbands */
   int *xcoord, *ycoord; /* Limits on location of fbands */
   byte mask;		/* mask to determine whether to PCT a certain fgroup */
   float **rptr, *ptr, **frptr, *fptr; /* Pointers to image pixels */
   float **cvecP;	/* Pointer to covariance vectors */
   double **tmat;	/* Pointer to transform matrix */
   MATRIX *matP;	/* Pointer to transform matrix */
   Image *fake_Image;
   HISTORY stuff;
   VQ_INFO infotemp;
   FILE *out;
   const char *fn = "PCT";
   int **temp;		/* temporary pointer to hold history information */
   int *fbandsize, bandsize, number, ttt;
   float tmp;

   /* Check to see if a wavelet transform has been performed */
   if((info->block_type!=WAVL) && (!history_check(WAVELET, image))) {
      fprintf(stderr, "You must perform a wavelet transform on the image\n");
      fprintf(stderr, "Before attempting to perform a PCT on related\n");
      fprintf(stderr, "groups of frequency bands.  Aborting...\n");
      return;
   }

   /* Allocate memory */
   cvecP = (float **)malloc(image->bands*sizeof(float *));


   /* Get number of frequency bands */
   if(history_check(WAVELET, image)) {
      temp=(int **)(history_get(image, WAVELET))->packetP->dptr;
      t=*temp[1];
      fbands=3*t+1;
   }
   else {
      fbands=info->bands;
      t=(fbands-1)/3;
   }
   fprintf(stdout, "found wavelet transform, fbands=%d\n", fbands);
   xcoord=(int *)malloc(sizeof(int)*fbands);
   ycoord=(int *)malloc(sizeof(int)*fbands);
   fbandsize=(int *)malloc(sizeof(int)*fbands);
   /* Begin loop through each image band */
   for(k=0; k<image->bands; k++) {
      rows=(int)image->image_ptr[k]->rows;
      cols=(int)image->image_ptr[k]->cols;
      mask=1;
      no_pcts=0;
      j=0; 		/* j is # of PCTs performed in this spectral band */
      bandsize=(image->image_ptr[k]->rows)/(2<<((fbands-4)/3));
      xcoord[0]=0;
      ycoord[0]=0;
      fbandsize[0]=bandsize;
      for(i=1; i<fbands; i+=3) {
         xcoord[i]=0;
         ycoord[i]=bandsize;
         fbandsize[i]=bandsize;
         xcoord[i+1]=bandsize;
         ycoord[i+1]=0;
         fbandsize[i+1]=bandsize;
         xcoord[i+2]=bandsize;
         ycoord[i+2]=bandsize;
         fbandsize[i+2]=bandsize;
         bandsize<<=1;
      }
      for(i=0; i<fbands; i++) {
         fprintf(stderr, "xcoord[%d]=%d, ycoord[%d]=%d, fbandsize[%d]=%d\n", i, xcoord[i], i, ycoord[i], i, fbandsize[i]);
      }
      fprintf(stderr, "Assigned xcoord, ycoord&fbandsize\n");
      /* Count the number of PCT matrices that need stored in INFO structure */
      for(i=0; i<t; i++) {
         if(mask&where) no_pcts++;
         mask<<=1;
      }
      mask=1;
      infotemp=info;
      if(info->pct_done!=CVIP_YES) {
         for(i=0; i<image->bands; i++) {
            info->pcts=(MATRIX **)malloc(sizeof(MATRIX *)*no_pcts);
            if(info->next!=(VQ_INFO)NULL) info=info->next;
         }
      }
      info=infotemp;
      mask=where;
      fprintf(stderr, "%d groups found\n", no_pcts);
      for(i=0; i<2; i++) {	/* for each PCT group */
         if(1) { 	/* Do the PCT in this fgroup */
            fprintf(stderr, "Found a group, i=%d\n", i);
            number=3*i+1;
            bandsize=fbandsize[number];
            fprintf(stderr, "Allocating image, bandsize=%d\n", bandsize);
            fake_Image=(Image *)new_Image(PPM, RGB, 3, bandsize, bandsize, CVIP_FLOAT, REAL);
            fprintf(stderr, "Allocated fake_Image\n");
            /* Copy fbands into matrix */
            rptr=(float **)image->image_ptr[k]->rptr;
            for(z=number; z<number+3; z++) { /* Copy for each fband in color band */
               frptr=(float **)fake_Image->image_ptr[z-number]->rptr;
               for(x=xcoord[z];  x<xcoord[z] + bandsize; x++) {
                  ptr=(float *)rptr[x];
                  fptr=(float *)frptr[x-xcoord[z]];
                  for(y=ycoord[z]; y<ycoord[z] + bandsize; y++) {
                     fptr[y-ycoord[z]]=ptr[y];
                  } /* end for(y=ycoord...) */
               } /* end for(x=xcorrd...) */
            } /* end for(z=0...) */
            fprintf(stderr, "Done copying fbands into image\n");
            /* Do the PCT */
            if(info->pct_done!=CVIP_YES) { 		/* Perform forward PCT */
               msg_CVIP(fn, "performing (PCT)...\n");
               msg_CVIP(fn, "computing covariance matrix...\n");
               getBandVector_Image(fake_Image, cvecP);
               matP = covariance_Matrix(cvecP, image->bands, bandsize, 0, -1.0);
               msg_CVIP(fn, "computing eigenvectors of covariance matrix\n");
               msg_CVIP(fn, "to compose transformation matrix...\n");
               matP=eigenSystem_Matrix(matP);
               tmat=(double **)getData_Matrix(matP);
               print_Matrix(matP);
               fprintf(stderr, "\n");
               linearTrans_Image(cvecP, image->bands, bandsize, tmat);
               info->pcts[j++]=(MATRIX *)matP;
            } 					/* end if(!(info->...) */
            else {				/* Perform inverse PCT */
               msg_CVIP(fn, "performing Inverse PCT...\n");
               getBandVector_Image(fake_Image, cvecP);
               matP=(MATRIX *)info->pcts[i];
               fprintf(stderr, "assigning matrix to info->pcts[%d]", i);
               matP=invert_Matrix(matP);
               tmat = (double **) getData_Matrix(matP);
               print_Matrix(matP);
               fprintf(stderr, "\n");
               if(k==1&&i==1) {
                  out=fopen("text.txt", "w");
                  ttt=0;
                  while(ttt<12288) {
                     tmp=(float)fake_Image->image_ptr[0]->rptr[0][ttt+1];
                     fprintf(out, "%f\t", tmp);
                     if((tmp>10000.0) || (tmp<-10000.0)) {
                        fprintf(stderr, "Last good one: band 0 ttt=%f\n", ttt);
                     }
                     tmp=(float)fake_Image->image_ptr[1]->rptr[0][ttt+1];
                     fprintf(out, "%f\t", tmp);
                     if((tmp>10000.0) || (tmp<-10000.0)) {
                        fprintf(stderr, "Last good one: band 1 ttt=%f\n", ttt);
                     }
                     tmp=(float)fake_Image->image_ptr[2]->rptr[0][ttt+1];
                     fprintf(out, "%f\n", tmp);
                     if((tmp>10000.0) || (tmp<-10000.0)) {
                        fprintf(stderr, "Last good one: band 2 ttt=%f\n", ttt);
                     }
                     ttt++;
                  }
                  fclose(out);
               } 
               linearTrans_Image(cvecP, image->bands, bandsize, tmat);
            } 					/* end else */
            /* Copy back results */
            for(z=number; z<number+3; z++) { /* Copy for each fband in color band */
               frptr=(float **)fake_Image->image_ptr[z-number]->rptr;
               for(x=xcoord[z];  x<xcoord[z] + bandsize; x++) {
                  ptr=(float *)rptr[x];
                  fptr=(float *)frptr[x-xcoord[z]];
                  for(y=ycoord[number]; y<ycoord[z] + bandsize; y++) {
                     ptr[y]=fptr[y-ycoord[z]];
                  } /* end for(y=ycoord...) */
               } /* end for(x=xcorrd...) */
            } /* end for(z=0...) */
            /* Free image */
            rmin=rmax;
            cmin*=2;
            delete_Image(fake_Image);
         }					/* end if(mask&where) */
         mask*=2;
      }						/* End for(i=0..) */
      info->pct_done=CVIP_YES;
      if(info->next!=(VQ_INFO)NULL) info=info->next;
      no_pcts=0;
   } 						/* end for(k=0; ...) */
} 						/* end function fband_pct() */ 
/************************************************************************
*									*
*	ROUTINE/PGM NAME: downsample()					*
*									*
*	DESCRIPTION: This routine downsamples an image by a factor of	*
*	two in the horizontal and vertical directions, resulting in a	*
*	total data reduction of 4:1 in the second and			*
*									*
*	AUTHOR: Arve Kjoelen, SIUE					*
*									*
*	INITIAL CODING DATE: 02/24/94					*
*									*
************************************************************************/
void downsample(Image *image) {
   int i, j, k, rows, cols;
   float **rptr, **newrptr, *ptr, *newptr;

   if(image->bands<3) {
      fprintf(stdout, "This routine is intended for downsampling of bands\n");
      fprintf(stdout, "2 and three of an RGB-image.  Your image is Gray\n");
      return;
   }

   else if(image->image_ptr[0]->data_type!=CVIP_FLOAT) (void)cast_Image(image, CVIP_FLOAT);

   fprintf(stdout, "Downsampling by 2 in horizontal and vertical direction\n");

   for(k=1; k<image->bands; k++) {
      rows=image->image_ptr[k]->rows;
      cols=image->image_ptr[k]->cols;
      rptr=(float **)image->image_ptr[k]->rptr;
      newrptr=(float **)malloc(sizeof(float *)*rows/2);
      newrptr[0]=(float *)malloc(sizeof(float)*rows*cols/4);
      for(i=0; i<rows/2; i++) {
         newrptr[i]=&newrptr[0][i*cols/2];
         for(j=0; j<cols/2; j++) newrptr[i][j]=rptr[2*i][2*j];
      }

      /* free old image */
      free(image->image_ptr[k]->rptr[0]);
      free(image->image_ptr[k]->rptr);

      /* Allocate new space for image */
      image->image_ptr[k]->rptr=(char **)(void **)(float **)malloc(sizeof(float *)*rows);
      image->image_ptr[k]->rptr[0]=(char *)(void *)(float *)malloc(sizeof(float *)*rows*cols/4);
      rptr=(float **)image->image_ptr[k]->rptr;
      for(i=0; i<rows/2; i++) rptr[i]=&rptr[0][i*cols/2];

      /* copy data into image */
      for(i=0; i<rows/2; i++) {
         ptr=rptr[i];
         newptr=newrptr[i];
         for(j=0; j<cols/2; j++) ptr[j]=newptr[j];
      }

      /* free newrptr so we can reallocate for next band */
      free(newrptr[0]);
      free(newrptr);

      /* update info about #rows and cols */
      image->image_ptr[k]->rows/=2;
      image->image_ptr[k]->cols/=2;

   } /* end for(k=1; */ 
}

/************************************************************************
*									*
*	ROUTINE/PGM NAME: reconstruct()					*
*									*
*	DESCRIPTION: reconstructs an image which has been previously	*
*	downsampled by a factor of 2:1 in the second and third spectral	*
*	bands.  Reconstruction is done using first-order hold (linear	*
*	interpolation).							*
*									*
*	AUTHOR: Arve Kjoelen, SIUE					*
*									*
*	INITIAL CODING DATE: 02/24/94					*
*									*
************************************************************************/
void reconstruct(Image *image) {
   int i, j, k, rows, cols;
   float **rptr, **newrptr, *newptr, *ptr;

   if(image->bands<3) {
      fprintf(stdout, "This routine is intended for reconstruction of bands\n");
      fprintf(stdout, "2 and three of an RGB-image.  Your image is Gray\n");
      return;
   }

   fprintf(stdout, "reconstructing image using 1st order hold (linear interpolation)\n");

   if(image->image_ptr[0]->data_type!=CVIP_FLOAT) (void)cast_Image(image, CVIP_FLOAT);

   for(k=1; k<image->bands; k++) {
      rows=image->image_ptr[k]->rows;
      cols=image->image_ptr[k]->cols;
      rptr=(float **)image->image_ptr[k]->rptr;
      newrptr=(float **)malloc(sizeof(float *)*rows*2);
      newrptr[0]=(float *)malloc(sizeof(float)*rows*cols*4);
      for(i=0; i<2*rows; i++) { 
         newrptr[i]=&newrptr[0][i*cols*2];
      }

      /* copy known data into new matrix */
      for(i=0; i<2*rows; i+=2) {
         newptr=newrptr[i];
         ptr=rptr[i/2];
         for(j=0; j<2*cols; j+=2) newptr[j]=ptr[j/2];
      }

      /* reconstruct even-numbered rows */
      for(i=0; i<2*rows; i+=2) {
         newptr=newrptr[i];
         for(j=1; j<(2*cols-1); j+=2) newptr[j]=(newptr[j-1]+newptr[j+1])*0.5;
         /* reconstruct edge pixel */
         newptr[2*cols-1]=0.9*newptr[2*cols-2]+0.1*newptr[2*cols-3];
      }

      /* reconstruct odd-numbered rows */
      for(i=1; i<(2*rows-1); i+=2) {
         for(j=0; j<2*cols; j+=2) {
            newrptr[i][j]=0.5*(newrptr[i-1][j]+newrptr[i+1][j]);
         }
         for(j=0; j<2*cols; j+=2) {
            newrptr[2*rows-1][j]=0.9*newrptr[2*rows-2][j]+0.1*newrptr[2*rows-3][j];
         }
      }

      /* free old image */
      free(image->image_ptr[k]->rptr[0]);
      free(image->image_ptr[k]->rptr);

      /* Allocate memory for new image */
      image->image_ptr[k]->rptr=(char **)(void **)(float **)malloc(sizeof(float *)*2*rows);
      image->image_ptr[k]->rptr[0]=(char *)(void *)(float *)malloc(sizeof(float)*rows*cols*4);
      rptr=(float **)image->image_ptr[k]->rptr;
      for(i=0; i<2*rows; i++) {
         rptr[i]=&rptr[0][2*cols*i];
      }

      /* copy data into image */
      for(i=0; i<2*rows; i++) {
         ptr=rptr[i];
         newptr=newrptr[i];
         for(j=0; j<2*cols; j++) ptr[j]=newptr[j];
      }

      /* free newrptr so we can use it again for next band */
      free(newrptr[0]);
      free(newrptr);

      /* adjust the number of rows and columns in MATRIX structure */
      image->image_ptr[k]->rows*=2;
      image->image_ptr[k]->cols*=2;
   } /* end for k=1; */
}


/************************************************************************
*									*
*	ROUTINE/PGM NAME: get_lbg_scheme()				*
*									*
*	DESCRIPTION: selects the proper LBG scheme based on		*
*	information passed to it.					*
*									*
*	VARIABLES PASSED:						*
*		int scheme - Indicates which compression scheme has	*
*		been selected, and includes information on whether the	*
*		pct has been performed.					*
*		int bands - the number of color bands in the image.	*
*		VQ_INFO info - Pointer to the structure that contains	*
*		information about the current scheme.			*
*									*
*	AUTHOR: Arve Kjoelen, SIUE.					*
*									*
*	INITIAL CODING DATE: 12/28/93					*
*									*
*	LAST MODIFICATIONS MADE: 12/28/93				*
*									*
************************************************************************/
void get_lbg_scheme(int scheme, int bands, VQ_INFO info) {
   int temp=96;
   int i=0;
   fprintf(stderr, "get_lbg_scheme: bands=%d\n", bands);
   if(scheme<33) { /* No PCT or sub PCT */
      switch(scheme) {
         /* Case 1-15: 10-band schemes */
         case 1:
         if(!Tumor_image) {
         while(i<bands) {
            info->block_type=WAVL;
            info->bands=10;
            info->hsize=&WVQ1_blocks[0];
            info->vsize=&WVQ1_blocks[0];
            info->codebook_size=&WVQ1_cbsizes[0];
            info->nvecs=&WVQ1_nvecs[0];
            info=(VQ_INFO)info->next;
            i++;
         }
         }
         else { /* Tumor_image=1 */
         while(i<bands) {
            info->block_type=WAVL;
            info->bands=10;
            info->hsize=&TUM1_blocks[0];
            info->vsize=&TUM1_blocks[0];
            info->codebook_size=&WVQ1_cbsizes[0];
            info->nvecs=&TUM1_nvecs[0];
            info=(VQ_INFO)info->next;
            i++;
         }
         }
         break;
         case 2:
         if(!Tumor_image) {
         while(i<bands) {
            info->block_type=WAVL;
            info->bands=10;
            info->hsize=&WVQ3_blocks[0];
            info->vsize=&WVQ3_blocks[0];
            info->codebook_size=&WVQ3_cbsizes[0];
            info->nvecs=&WVQ3_nvecs[0];
            info=(VQ_INFO)info->next;
            i++;
         }
         }
         break;
         case 3:
         if(!Tumor_image) {
         while(i<bands) {
            info->block_type=WAVL;
            info->bands=10;
            info->hsize=&WVQ4_blocks[0];
            info->vsize=&WVQ4_blocks[0];
            info->codebook_size=&WVQ4_cbsizes[0];
            info->nvecs=&WVQ4_nvecs[0];
            info=(VQ_INFO)info->next;
            i++;
         }
         }
         break;
         case 4:
         if(!Tumor_image) {   
         while(i<bands) {
            info->block_type=WAVL;
            info->bands=10;
            info->hsize=&WVQ2R_blocks[0];
            info->vsize=&WVQ2R_blocks[0];
            info->codebook_size=&WVQ2R_cbsizes[0];
            info->nvecs=&WVQ2R_nvecs[0];
            info=(VQ_INFO)info->next;
            i++;
         }
         }
         break;
         case 5:
         if(!Tumor_image) {  
         while(i<bands) {
            info->block_type=WAVL;
            info->bands=10;
            info->hsize=&WVQ2B_blocks[0];
            info->vsize=&WVQ2B_blocks[0];
            info->codebook_size=&WVQ2B_cbsizes[0];
            info->nvecs=&WVQ2B_nvecs[0];
            info=(VQ_INFO)info->next;
            i++;
         }
         }
         break;
         case 6: /* This is the n1 scheme in LBG.h */
         while(i<bands) {
            info->block_type=WAVL;
            info->bands=10;
            info->hsize=&WVQn1_hblocks[0];
            info->vsize=&WVQn1_vblocks[0];
            info->codebook_size=&WVQn1_cbsizes[0];
            info->nvecs=&WVQn1_nvecs[0];
            info=(VQ_INFO)info->next;
            i++;
         }
         break;
         case 7: /* n2 scheme in LBG.h */
         while(i<bands) {
            info->block_type=WAVL;
            info->bands=10;
            info->hsize=&WVQn1_hblocks[0];
            info->vsize=&WVQn1_vblocks[0];
            info->codebook_size=&WVQn2_cbsizes[0];
            info->nvecs=&WVQn1_nvecs[0];
            info=(VQ_INFO)info->next;
            i++;
         }
         break;
         case 8: /* n3 scheme in LBG.h */
         while(i<bands) {
            info->block_type=WAVL;
            info->bands=10;
            info->hsize=&WVQn1_hblocks[0];
            info->vsize=&WVQn1_vblocks[0];
            info->codebook_size=&WVQn3_cbsizes[0];
            info->nvecs=&WVQn3_nvecs[0];
            info=(VQ_INFO)info->next;
            i++;
         }
         break;
         /* Case 16: 13-band schemes */
         case 16:
         if(!Tumor_image) {
         while(i<bands) {
            info->block_type=WAVL;
            info->bands=13;
            info->hsize=&WVQ6_blocks[0];
            info->vsize=&WVQ6_blocks[0];
            info->codebook_size=&WVQ2B_cbsizes[0];
            info->nvecs=&WVQ2B_nvecs[0];
            info=(VQ_INFO)info->next;
            i++;
         }
         break;
         } /* End if !Tumor_image */
      }
   }
   else if((scheme>=32)&&(scheme<64)) {	/* PCT performed */
      scheme-=32;
      switch(scheme) {
         case 1:
         info->block_type=WAVL;
         info->bands=10;
         info->hsize=&WVQ2R_blocks[0];
         info->vsize=&WVQ2R_blocks[0];
         info->codebook_size=&WVQ2R_cbsizes[0];
         info->nvecs=&WVQ2R_nvecs[0];
         info=info->next;
         info->block_type=WAVL;
         info->bands=10;
         info->hsize=&WVQ2G_blocks[0];
         info->vsize=&WVQ2G_blocks[0];
         info->codebook_size=&WVQ2G_cbsizes[0];
         info->nvecs=&WVQ2G_nvecs[0];
         info=info->next;
         info->block_type=WAVL;
         info->bands=10;
         info->hsize=&WVQ2B_blocks[0];
         info->vsize=&WVQ2B_blocks[0];
         info->codebook_size=&WVQ2B_cbsizes[0];
         info->nvecs=&WVQ2B_nvecs[0];
         break;

         case 2:
         info->block_type=WAVL;
         info->bands=10;
         info->hsize=&WVQn1_hblocks[0];
         info->vsize=&WVQn1_vblocks[0];
         info->codebook_size=&WVQn1_cbsizes[0];
         info->nvecs=&WVQn1_nvecs[0];
         info=info->next;
         i=1;
         while(i<bands) {
            info->block_type=WAVL;
            info->bands=10;
            info->hsize=&WVQn4G_hblocks[0];
            info->vsize=&WVQn4G_vblocks[0];
            info->codebook_size=&WVQn4G_cbsizes[0];
            info->nvecs=&WVQn4G_nvecs[0];
            info=info->next;
            i++;
         }
         break;
      }
   }
   else if(scheme>=64) {	/* subPCT performed */
      scheme-=64;
      switch(scheme) {
         case 1:
         while(i<bands) {
            info->block_type=WAVL;
            info->bands=10;
            info->hsize=&WVQsubPCT1_hblocks[0];
            info->vsize=&WVQsubPCT1_vblocks[0];
            info->codebook_size=&WVQsubPCT1_cbsizes[0];
            info->nvecs=&WVQsubPCT1_nvecs[0];
            info=info->next;
            i++;
         }
         break;
      }
   }
   else if(temp&scheme==96) {	/* PCT and subPCT performed */
      scheme-=96;
   }
}

/************************************************************************
*									*
*	ROUTINE/PGM NAME: block_to_vec()				*
*									*
*	DESCRIPTION: Converts a block of an image to a vector.		*
*									*
*	VARIABLES PASSED: 						*
*		int rn, cn: Coordinates of start of block.		*
*		int vs, hs: Vertical and horizontal size of block.	*
*	      float **rptr: pointer to matrix structure.		*
*		  float *p: Pointer to be filled with vector.		*
*									*
*	VARIABLES RETURNED:						*
*		The result is returned in p.				*
*									*
*	AUTHOR: Arve Kjoelen, SIUE.					*
*									*
*	INITIAL CODING DATE: 10/22/93.					*
*									*
*	LAST MODIFICATIONS MADE: 10/22/93.				*
*									*
*	DIAGNOSTICS: The input must be of type float.			*
*									*
************************************************************************/
void block_to_vec(float **rptr, float *p, int rn, int cn, int vs, int hs) {
   int i,j, htemp, vtemp, index=0;
   float *row;

   htemp=cn+hs;
   vtemp=rn+vs;

   for(i=rn; i<vtemp; i++) {
      row=rptr[i];
      for(j=cn; j<htemp; j++) {
         (*p++)=row[j];
      }
   }
}


/************************************************************************
*									*
*	ROUTINE/PGM NAME: vec_to_block()				*
*									*
*	DESCRIPTION: Converts a vector to a block and inserts the block	*
*	into its proper place in the image structure.			*
*									*
*	VARIABLES PASSED:						*
*		float **rptr: Pointer to matrix structure.		*
*		    float *p: Pointer to vector to be converted.	*
*		  int rn, cn: Coordinates where first vector element 	*
*			      belongs in matrix.			*
*		  int vs, hs: Vertical and horizontal size of blocks.	*
*									*
*	VARIABLES RETURNED:						*
*		The result is returned in rptr.				*
*									*
*	AUTHOR: Arve Kjoelen, SIUE.					*
*									*
*	INITIAL CODING DATE: 10/22/93.					*
*									*
*	LAST MODIFICATIONS MADE: 10/22/93.				*
*									*
*	DIAGNOSTICS: The inputs must be of type float.			*
*									*
************************************************************************/
void vec_to_block(float **rptr, float *p, int rn, int cn, int vs, int hs) {
   int i,j, htemp, vtemp, index=0;
   float *row;

   htemp=cn+hs;
   vtemp=rn+vs;

   for(i=rn; i<vtemp; i++) {
      row=rptr[i];
      for(j=cn; j<htemp; j++) {
         row[j]=*p++;
      }
   }
}



/************************************************************************
*									*
*	PGM/ROUTINE NAME: encode_data()					*
*									*
*	DESCRIPTION: This routine assigns a codebook index to the	*
*	input vectors based on the nearest-neighbor classification	*
*	criterion.  This criterion results in the selection of the	*
*	codebook entry which is closest to the input vector in 		*
*	euclidian space.						*
*									*
*	AUTHOR: Arve Kjoelen, SIUE					*
*									*
*	INITIAL CODING DATE: 9/27/93					*
*									*
*	LAST MODIFICATIONS MADE: 9/27/93				*
*									*
************************************************************************/
void encode_data(float **codebook, float **data, int *index, int size, int dim, int nvecs) {
   float  *vec, *code, sum, min;
   int i, j, k;
   for(i=0; i<nvecs; i++) { /* For each vector */
      min=1.0E12;
      for(k=0; k<size; k++) {  /* Find closest codebook entry */
         vec=(float *)data[i];
         sum = 0.0;
         code = (float *)codebook[k];
         for(j=0; j<dim; j++) {
            sum+=(*vec-*code)*(*vec-*code);
            vec++;
            code++;
         }
         if(sum<min) {
            index[i]=k;
            min=sum;
         }
      }
   }
}


/************************************************************************
*									*
*	ROUTINE/PGM NAME: compute_centroid()				*
*									*
*	DESCRIPTION: This routine performs one part of the iterative	*
*	LBG algorithm.  For each codebook entry Ci, this routine 	*
*	computes the centroid of all the vectors encoded into Ci.  This	*
*	centroid is then used as the new codebook entry in the next	*
*	iteration.  The routine assigns the centroid as the new code-	*
*	book entry.							*
*									*
*	AUTHOR: Arve Kjoelen						*
*									*
*	INITIAL CODING DATE: 9/27/93					*
*									*
*	LAST MODIFICATIONS MADE: 9/27/93				*
*									*
************************************************************************/
void compute_centroid(ELEMENT struc, int size, int dim, int nvecs) {
   int i, j, k, count, zcount=0, *index;
   float *temp, **codebook, **data, *dat, *centroid;
   static int offset;

   if(offset==dim) offset++;
   else offset = dim;

   codebook=(float **)struc->codebook;
   data = (float **)struc->data;
   centroid=(float *)malloc(sizeof(float)*dim);
   index=struc->codebook_index;


   for(i=0; i<size; i++) { 	/* For each codeword    */
      for(k=0; k<dim; k++) {
         centroid[k]=0.0;
      }
      count=0;
      for(j=0; j<nvecs; j++) {	/* For each vector 	*/
         if(index[j]==i) { 
            count++;
            dat=(float *)data[j];
            for(k=0; k<dim; k++) {      /* Each vector element */ 
               centroid[k]+=*dat++;
            }
         }
      }
      temp=codebook[i];
      if(count>0) {
         for(k=0; k<dim; k++) {
            temp[k]=centroid[k]/(float)(count);
         }
      }
      else {
         dat=(float *)data[offset%nvecs];
         for(k=0; k<dim; k++) {
            temp[k]=*dat++;
         }
      }
   }
   free(centroid);
}


/************************************************************************
*									*
*	ROUTINE/PGM NAME: LBG_error()					*
*									*
*	DESCRIPTION: This routine calculates the quantization error	*
*	between the codebook vectors used and the actual input vectors.	*
*	This error is then compared with the previous error level.  If	*
*	the decrease in quantization error is not greater than some	*
*	predetermined threshold, a 1 is returned, indicating that the	*
*	iterative algorithm should come to a halt.			*
*									*
*	AUTHOR: Arve Kjoelen						*
*									*
*	INITIAL CODING DATE: 9/27/93					*
*									*
*	LAST MODIFICATIONS MADE: 9/27/93				*
*									*
************************************************************************/
int LBG_error(int size, int dim, ELEMENT struc, float **codebook, int first, int nvecs) {
   static float error;
   float **vecs, *temp, *book, temp_error, comp;
   int i, j, *indeces;
   temp_error=0.0;

   if(first) {
      error=1.0E12;
      return(0);
   }

   vecs = (float **)struc->data;
   indeces=(int *)struc->codebook_index;
   for(i=0; i<nvecs; i++) {		/* For each vector */
      temp=vecs[i];
      book=codebook[indeces[i]];
      for(j=0; j<dim; j++) {
         temp_error+=(*temp-*book)*(*temp-*book);
         temp++;
         book++;
      }
   }
   if(temp_error>0.00000001) {
      comp = 1.0 - (temp_error/error);
      fprintf(stderr, "\b\b\b\b\b\b%6.4f", comp);
   }
   if(temp_error>1.0E10) return(0);
   if((comp<LBG_ERROR)|| temp_error<LBG_ERROR) {
      error=temp_error;
      fprintf(stderr, "\tError=%f\n", error);
      return(1);  /* done */
   }
   error=temp_error;           /* another iteration needed */
   return(0);
}


/************************************************************************
*									*
*	ROUTINE/PGM NAME: allocate_vectors()				*
*									*
*	DESCRIPTION: This function allocates the memory needed for the	*
*	one-dimensional vectors to which the image is to be transformed.*
*	The memory is stored as part of the 'element' structure.	*
*									*
*	AUTHOR: Arve Kjoelen, SIUE					*
*									*
*	INITIAL CODING DATE: 11/02/93					*
*									*
*	LAST MODIFICATIONS MADE: 12/08/93				*
*									*
*									*
************************************************************************/
void allocate_vectors(Image *image, VQ_INFO info) {
   int i=0, j, k, l, t, s, vectors, size, *xcoord, *ycoord, fbands, offset;
   /* Remark: xcoord=row number, ycoord=column number */
   int noblocks, bandsize, *fbandsize, rn, cn, vs, hs, count=0, zcount=0;
   float **data, **rptr;
   ELEMENT stuff;
   
   while(i<image->bands) {
      rptr=(float **)image->image_ptr[i]->rptr;
      /* Find coordinates of each frequency band */
      fbands=info->bands;
      fbandsize=(int *)malloc(sizeof(int)*fbands);
      if(info->block_type==WAVL) {
         stuff=(ELEMENT)info->elements;
         xcoord=(int *)malloc(sizeof(int)*fbands);
         ycoord=(int *)malloc(sizeof(int)*fbands);
         bandsize=(image->image_ptr[i]->rows)/(2<<((fbands-4)/3));
         xcoord[0]=0;
         ycoord[0]=0;
         fbandsize[0]=bandsize;
         for(j=1; j<fbands; j+=3) { 
            xcoord[j]=0;
            ycoord[j]=bandsize;
            fbandsize[j]=bandsize;
            xcoord[j+1]=bandsize;
            ycoord[j+1]=0;
            fbandsize[j+1]=bandsize;
            xcoord[j+2]=bandsize;
            ycoord[j+2]=bandsize;
            fbandsize[j+2]=bandsize;
            bandsize<<=1;
         }
         for(j=0; j<fbands; j++) {
            if(info->codebook_size[j]) {
               size=info->hsize[j]*info->vsize[j];
               vectors=info->nvecs[j];
               offset=(int)info->nvecs[j]/info->codebook_size[j];
               /* Allocate memory for data vectors */
               if(stuff->data==(float **)NULL) {
                  stuff->data=(float **)malloc(sizeof(float *)*vectors);
                  data=stuff->data;
                  *data=(float *) malloc (sizeof(float)*size*vectors);
                  for(k=1; k<vectors; k++) {
                     data[k]=(float *)&(data[0][k*size]);
                  }
               }
               /* Allocate memory for codebook indeces */
               if(stuff->codebook_index==(int *)NULL) {
                  stuff->codebook_index=(int *)malloc(sizeof(int)* info->nvecs[j]);
               }
               /* Allocate memory for codebook vectors */
               if(stuff->codebook==(float **)NULL) {
                  stuff->codebook=(float **)malloc(sizeof(float *)* info->codebook_size[j]);
                  *(stuff->codebook)=(float *) malloc (sizeof(float)*  info->codebook_size[j]*size);
                  for(k=1; k<info->codebook_size[j]; k++) {
                     stuff->codebook[k]=(float *)&(stuff->codebook[0][k*size]);
                  }
               }
               rn=xcoord[j];
               cn=ycoord[j];
               t=0;
               for(k=xcoord[j]; k<xcoord[j]+fbandsize[j]; k+=info->vsize[j]) {
                  for(l=ycoord[j]; l<ycoord[j]+fbandsize[j]; l+=info->hsize[j]) {
                     block_to_vec(rptr, data[t], rn, cn, info->vsize[j], info->hsize[j]);
                     t++;                 
                  cn+=info->hsize[j];
                  }
                  cn=ycoord[j];
                  rn+=info->vsize[j];
               }
               for(t=0; t<info->codebook_size[j]; t++) {
                  for(s=0; s<size; s++) {
                     stuff->codebook[t][s]=data[offset*t][s];
                  }    
               }
            }
            if(stuff->next==(ELEMENT)NULL) {
               stuff->next = (ELEMENT)calloc(1, sizeof(struct element));
            }
            stuff=(ELEMENT)stuff->next;
         }
         free(xcoord);
         free(ycoord);
      }
      info=info->next;
      i++;
   }
   free(fbandsize);
}


/************************************************************************
*									*
*	ROUTINE/PGM NAME: do_decoding()					*
*									*
*	DESCRIPTION: This routine reconstructs an image from the	*
*	codebook indeces passed to the routine.	 The codebook vectors	*
*	are copied into the image structure by calls to vec_to_mat(),	*
*	and the result is written into the Image structure passed to	*
*	do_decoding().	If the passed image structure has not been	*
*	allocated, the routine allocates it.				*
*									*
*	AUTHOR: Arve Kjoelen, SIUE					*
*									*
*	INITIAL CODING DATE: 11/09/93					*
*									*
*	LAST MODIFICATIONS MADE: 12/08/93				*
*									*
*	DIAGNOSTICS: The image and codebook vectors must be of type	*
*	float.								*
************************************************************************/
void do_decoding(Image *image, VQ_INFO info) {
   int i=0, j, k, l, t, vectors, size, *xcoord, *ycoord, fbands;
   /* Remark: xcoord=row number, ycoord=column number */
   int noblocks, bandsize, *fbandsize, rn, cn, vs, hs, *index, count;
   float **rptr, **codebook;
   ELEMENT stuff;
  

   if(image==(Image *)NULL) {
      /* Allocate image */
   }

   for(i=0; i<image->bands; i++) {
      rptr=(float **)image->image_ptr[i]->rptr;
      /* Find coordinates of each frequency band */
      fbands=info->bands;
      fbandsize=(int *)malloc(sizeof(int)*fbands);
      if(info->block_type==WAVL) {
         stuff=(ELEMENT)info->elements;
         xcoord=(int *)malloc(sizeof(int)*fbands);
         ycoord=(int *)malloc(sizeof(int)*fbands);
         bandsize=(image->image_ptr[i]->rows)/(2<<((fbands-4)/3));
         xcoord[0]=0;
         ycoord[0]=0;
         fbandsize[0]=bandsize;
         for(j=1; j<fbands; j+=3) { 
            xcoord[j]=0;
            ycoord[j]=bandsize;
            fbandsize[j]=bandsize;
            xcoord[j+1]=bandsize;
            ycoord[j+1]=0;
            fbandsize[j+1]=bandsize;
            xcoord[j+2]=bandsize;
            ycoord[j+2]=bandsize;
            fbandsize[j+2]=bandsize;
            bandsize<<=1;
         }
         for(j=0; j<fbands; j++) {
            if(info->codebook_size[j]) {
               size=info->hsize[j]*info->vsize[j];
               vectors=info->nvecs[j];
               codebook=stuff->codebook;
               rn=xcoord[j];
               cn=ycoord[j];
               index=stuff->codebook_index;
               t=0;
               for(k=xcoord[j]; k<xcoord[j]+fbandsize[j]; k+=info->vsize[j]) {
                  for(l=ycoord[j]; l<ycoord[j]+fbandsize[j]; l+=info->hsize[j]) {
                     vec_to_block(rptr, codebook[*index++], rn, cn, info->vsize[j], info->hsize[j]);
                     cn+=info->hsize[j];
                  }
                  cn=ycoord[j];
                  rn+=info->vsize[j];
               }
            }
            stuff=(ELEMENT)stuff->next;
         }
         free(xcoord);
         free(ycoord);
      }
      info=info->next;
   }
   free(fbandsize);
   fprintf(stdout, "Decoding complete\n");
}

/************************************************************************
*									*
*	ROUTINE/PGM NAME: free_info()					*
*									*
*	DESCRIPTION: This routine will free up the VQ_INFO structures	*
*	and all memory allocated for them.				*
*									*
*	AUTHOR: Arve Kjoelen, SIUE.					*
*									*
*	INITIAL CODING DATE: 11/15/93.					*
*									*
*	LAST MODIFICATIONS MADE: 12/30/93				*
*									*
************************************************************************/
void free_info(VQ_INFO info, int bands) {
   int i, j;
   VQ_INFO temp;
   ELEMENT stuff, temp_stuff;
   for(i=0; i<bands; i++) {
      stuff=info->elements;
      for(j=0; j<info->bands; j++) {
         if(info->codebook_size[j]) {
            free(*stuff->codebook);
            free(stuff->codebook);
            if(stuff->data!=(float **)NULL) {
               free(*stuff->data);
               free(stuff->data);
            }
            if(stuff->codebook_index!=(int *)NULL) {
               free(stuff->codebook_index);
            }
         }
	 temp_stuff=stuff;
         stuff=stuff->next;
	 if(temp_stuff) free(temp_stuff);
      }
      temp=info;
      info=info->next;
      if(temp) free(temp);
   }
}


/************************************************************************
*									*
*	ROUTINE/PGM NAME:save_codebook()				*
*									*
*	DESCRIPTION: This routine saves the current codebook to a file.	*
*	The file name is specified by the user.		 		*
*									*
*	AUTHOR: Arve Kjoelen, SIUE					*
*									*
*	INITIAL CODING DATE: 12/10/93					*
*									*
*	LAST MODIFICATIONS MADE: 12/28/93				*
*									*
*	NOTE: Format of saved codebook:					*
*	===============================					*
*	1. No Magic Number.  Consistency is ensured by comparing byte	*
*	   1 of this file with byte one of the file to be decompressed.	*
*	2. First byte specifies either:					*
*		a) In the case of a wavelet transform:			*
*		bit 7 (MSB) = 1.					*
*		bit 6,5   : Number of color bands in image.		*
*		bit 4,3,2 : Number of frequency bands per color.	*
*		bit 1,0   : Whether the PCT was performed, and where.	*
*		b) In the case of equal-sized blocks:			*
*		bit 7 (MSB) = 0.					*
*		bit 6,5   : Number of color bands in image.		*
*		bit 4,3,2 : Blocksize of transform.			*
*		bit 1,0   : Which Transform: 00=>Walsh, 01=>Haar,	*
*			    10=>DCT.					*
*	3. Each codebook is stored as floating-point values, and the	*
*	   file name has a number which combined with byte 1 of the	*
*	   file is enough to identify the compression scheme, and thus	*
*	   the number of codebook vectors in each frequency band and	*
*	   the dimension of each codebook vector.			*
*									*
************************************************************************/
char *save_cdbook(Image *image, VQ_INFO info, char *codebook) {
   int i, j, k, l, dim, size;
   ELEMENT stuff;
   float **book, min, max;
   FILE *lbgcb_file;
   byte header=0;

   if(info->block_type==WAVL) {
      strcat(codebook, ".lbgwav");
   }
   else {
      strcat(codebook, ".lbgreg");
   }

   lbgcb_file = fopen(codebook, "wb");

   if(image->bands==3) header|=(byte)32;
   if(image->bands==7) {
      header|=(byte)64;
      fprintf(stderr, "bands=7\n");
   }
   if(info->block_type==WAVL) {
      header|=(byte)128;
      if(info->bands==4) header|=(byte)4;
      else if(info->bands==7) header|=(byte)8;
      else if(info->bands==10) header|=(byte)12;
      else if(info->bands==13) header|=(byte)16;
      else if(info->bands==16) header|=(byte)20;
      else if(info->bands==19) header|=(byte)24;
      if(history_check(PCT, image)) header|=(byte)2;
      if(info->pct_done) header|=(byte)1;
   }
   fwrite(&header, sizeof(byte), 1, lbgcb_file);
   header=(byte)info->scheme;
   fwrite(&header, sizeof(byte), 1, lbgcb_file);
   header=(byte)(image->image_ptr[0]->rows)>>3;
   fwrite(&header, sizeof(byte), 1, lbgcb_file);
   header=(byte)(image->image_ptr[0]->cols)>>3;
   fwrite(&header, sizeof(byte), 1, lbgcb_file);
   i=0;
   while(i<image->bands) {
      stuff=info->elements;
      for(j=0; j<info->bands; j++) {
         if((info->codebook_size[j])&&j) {
            dim=info->hsize[j]*info->vsize[j];
            book=stuff->codebook;
            size=info->codebook_size[j];
            min=findminval_Matrix(size, dim, book);
            fwrite(&min, sizeof(float), 1, lbgcb_file);
            max=findmaxval_Matrix(size, dim, book);
            fwrite(&max, sizeof(float), 1, lbgcb_file);
            max=(max-min);
            for(k=0; k<size; k++) {
               for(l=0; l<dim; l++) {
                  header=(byte)((book[k][l]-min)*255/max);
                  fwrite(&header, sizeof(byte), 1, lbgcb_file);
               }
            }
         }
         stuff=stuff->next;
      }
      info=info->next;
      i++;
   }     
   fclose(lbgcb_file);
   return(codebook);
}


/************************************************************************
*									*
*	ROUTINE/PGM NAME: load_lbg_book()				*
*									*
*	DESCRIPTION: This routine loads up an lbg codebook from disk	*
*	and stores it in the VQ_INFO structure.  Normally, this will be	*
*	followed by encoding of the image using the codebook.		*
*									*
*	AUTHOR: Arve Kjoelen, SIUE					*
*									*
*	INITIAL CODING DATE: 12/17/93					*
*									*
*	LAST MODIFICATIONS MADE: 12/28/93				*
*									*
************************************************************************/
CVIP_BOOLEAN load_lbg_book(VQ_INFO info, char *answer) {
   int i=0, j, k, l, dim, size, scheme, bands;
   ELEMENT stuff;
   float **book, min, max;
   FILE *lbgcb_file;
   byte header, temp, rows, cols;
   size_t element_size=sizeof(float);

   if(answer==(char *)NULL) {
      answer = (char *)calloc(80, 1);
      fprintf(stdout, "\nRetrieval of LBG codebook from disk\n");
      fprintf(stdout, "===================================\n");
      fprintf(stdout, "Please enter the name of the codebook file, including extension\n");
      (void)gets(answer);
   }
   lbgcb_file = fopen(answer, "rb");
   if(lbgcb_file == (FILE *)NULL) {
      fprintf(stdout, "The file does not exist\n");
      return(0);
   }
   fread(&header, sizeof(byte), 1, lbgcb_file);
   if(header&128) {
      info->block_type=WAVL;
   }
   temp=(header&28);
   if(temp==4) info->bands=4;
   else if(temp==8) info->bands=7;
   else if(temp==12) info->bands=10;
   else if(temp==16) info->bands=13;
   else if(temp==20) info->bands=16;
   else if(temp==24) info->bands=19;
   fread(&temp, sizeof(byte), 1, lbgcb_file);
   info->scheme=(byte)temp;
/*
   if(header&1) scheme|=64;
   if(header&2) scheme|=32;
*/
   if(header&1) info->scheme|=64;
   if(header&2) info->scheme|=32;
   
   header=header&96;
   if(header==64) bands=1;
   else if(header==32)bands=3;
   else bands=1;
   fprintf(stderr, "calling get_lbg_scheme: bands=%d\n", (int)bands);
   get_lbg_scheme((int)info->scheme, bands, info);
   
   fread(&rows, sizeof(byte), 1, lbgcb_file);
   fread(&cols, sizeof(byte), 1, lbgcb_file);

   fprintf(stderr, "Reading codebook...");
   while(i<bands) {
      stuff=(ELEMENT)info->elements;
      for(j=0; j<info->bands; j++) {
         if((info->codebook_size[j])&&j) {
            dim=info->hsize[j]*info->vsize[j];
            size=info->codebook_size[j];
            if(stuff->codebook==(float **)NULL) {
               stuff->codebook=(float **)malloc(sizeof(float *)*size);
               stuff->codebook[0]=(float *)malloc(sizeof(float)*size*dim);
               book=(float **)stuff->codebook;
               for(k=0; k<size; k++) {
                  book[k]=(float *)&book[0][k*dim];
               }
            }
            fread(&min, sizeof(float), 1, lbgcb_file);
            fread(&max, sizeof(float), 1, lbgcb_file);
            max=max-min;
            for(k=0; k<size; k++) {
               for(l=0; l<dim; l++) {
                  fread(&header, sizeof(byte), 1, lbgcb_file);
	          book[k][l]=(float)(min+((float)header*max)/255.0);
                  if((book[k][l]>(float)(max+min+1.0)) || (book[k][l]<(float)(min-1.0))) {
                     fprintf(stderr, "load_lbg_book: Value out of range: book=%f, min=%f, max=%f\n", book[k][l], min, max);
                  }
               }
            }
/*
            fread(*book, element_size, (size_t)dim*size, lbgcb_file);
*/
         }
         if(stuff->next==(ELEMENT)NULL) {
            stuff->next=(ELEMENT)calloc(1, sizeof(struct element));
         }
         stuff=stuff->next;
      }
      info=info->next;
      i++;
   }     
   /*close(lbgcb_file); date 4/20/98*/
   fclose(lbgcb_file);
   fprintf(stderr, "Done.\n");
   return(1);
}


/************************************************************************
*									*
*	ROUTINE/PGM NAME: lbg_save()					*
*									*
*	DESCRIPTION: This routine stores an LBG-encoded image to disk. 	*
*	The file name is specified by the user, and the information 	*
*	needed to decode the image is specified by a unique byte        *
*	sequence at the	beginning of the file.  This sequence		*
*	incorporates information about the original image size and the	*
*	operations that have been performed on the image.  Also stored	*
*	is the transform matrix if a PCT has been performed on the	*
*	image.								*
*									*
*	AUTHOR: Arve Kjoelen, SIUE					*
*									*
*	INITIAL CODING DATE: 12/10/93					*
*									*
*	LAST MODIFICATIONS MADE: 12/30/93				*
*									*
*	NOTE: Format of saved image:					*
*	===============================					*
*	1. No Magic Number.  The check for consistency is done by	*
*	   comparing byte 1 of the file with byte 1 of the file which	*
*	   contains the codebook vectors.				*
*	2. First byte specifies either:					*
*		a) In the case of a wavelet transform:			*
*		bit 7 (MSB) = 1.					*
*		bit 6,5   : Number of color bands in image.		*
*		bit 4,3,2 : Number of frequency bands per color.	*
*		bit 1,0   : Whether the PCT was performed, and where.	*
*		b) In the case of equal-sized blocks:			*
*		bit 7 (MSB) = 0.					*
*		bit 6,5   : Number of color bands in image.		*
*		bit 4,3,2 : Blocksize of transform.			*
*		bit 1,0   : Which Transform: 00=>Walsh, 01=>Haar,	*
*			    10=>DCT.					*
*	3. 	In the case of equal-sized blocks (no wavelet 		*
*		transform), this completes the image format.)		*
*									*
*		In the case of wavelet transform, if the PCT was 	*
*		on a frequency-band to frequency-band basis (bit 0 of 	*
*		byte 1 equals 1), there will be a 96-bit field between	*
*		the data for each group of 3 frequency bands, excluding *
*		band 0, which will never be involved in the PCT.  This	*
*		96-bit field indicates the magnitude of the elements of *
*		the PCT transform matrix.				*
*									*
*	4.	The next 2 bytes specify the number of rows and columns	*
*		in the image.						*
*									*
*	5.	In the case of wavelet transform, the next byte 	*
*		indicates which wavelet transform was performed.	*
*									*
*									*
************************************************************************/
void lbg_save(Image *image, VQ_INFO info, char *name) {
   int i=0, j, k, l, **h_ptr, no_bits, count, *index, size, pcts;
   HISTORY h_stuff;
   MATRIX *matrix;
   ELEMENT stuff;
   char *answer=calloc(80, 1);
   float **book, *vec, max, min;
   FILE *lbgcomp_file;
   byte header=0, *data;
   size_t element_size=sizeof(float);

/*
   if(name==(char *)NULL) {
      fprintf(stdout, "\nStorage of LBG data to disk\n");
      fprintf(stdout, "===============================\n");
      fprintf(stdout, "Please enter a name for the data. The\n");
      fprintf(stdout, "extension .lbg will be added automatically\n");
      (void)gets(answer);
      strcat(answer, ".lbg");
*   }
*   else 
*/
      strncpy(answer, name, (size_t)(strlen(name)-3));

   lbgcomp_file = fopen(answer, "wb");


   if(image->bands==3) header|=(byte)32;
   if(image->bands==7) header|=(byte)64;
   if(info->block_type==WAVL) {
      header|=(byte)128;
      if(info->bands==4) header|=(byte)4;
      else if(info->bands==7) header|=(byte)8;
      else if(info->bands==10) header|=(byte)12;
      else if(info->bands==13) header|=(byte)16;
      else if(info->bands==16) header|=(byte)20;
      else if(info->bands==19) header|=(byte)24;
      if(history_check(PCT, image)) header|=(byte)2;
      if(info->pct_done) header|=(byte)1;
   }
   fwrite(&header, sizeof(byte), 1, lbgcomp_file);
   header=(byte)(image->image_ptr[0]->rows>>3);
   fwrite(&header, sizeof(byte), 1, lbgcomp_file);
   header=(byte)(image->image_ptr[0]->cols>>3);
   fwrite(&header, sizeof(byte), 1, lbgcomp_file);
   if(info->block_type==WAVL) {
      h_stuff=(HISTORY)history_get(image, WAVELET);
      h_ptr=(int **)h_stuff->packetP->dptr;
      header=(byte)h_ptr[0][0];
      fwrite(&header, sizeof(byte), 1, lbgcomp_file);
   }
   /* WRITE PCT INFO */
   if(history_check(PCT, image)) {
      h_stuff=history_get(image, PCT);
      matrix=(MATRIX *)h_stuff->packetP->dptr;
      fwrite(matrix->rptr[0], sizeof(double), 9, lbgcomp_file);
   }
   while(i<image->bands) {
      /* WRITE SUBPCT INFO */
      if(info->pct_done==CVIP_YES) {
         for(k=0; k<2; k++) {
            matrix=(MATRIX *)info->pcts[k];
            fwrite(matrix->rptr[0], sizeof(double), 9, lbgcomp_file);
         }
      }
      stuff=info->elements;
      for(j=0; j<info->bands; j++) {
         if(info->codebook_size[j]) {
            for(header=0; header<=16; header++) {
               if(pow(2,header)==info->codebook_size[j]) {
                  no_bits=(int)header;
               }
            }
         }
         else no_bits=32; /* just for the heck of it */
         size=(int)info->nvecs[j];
         data = (byte *)malloc((size_t)no_bits);
         index=(int *)stuff->codebook_index;
         count=0;
         switch(no_bits) {
            case 0: /* This case occurs only for frequency band #0 */
            vec=*stuff->data;
            size=info->hsize[0]*info->vsize[0];
            min=(float)findMinVal_Vector((void *)vec, (unsigned)size, CVIP_FLOAT);
            fwrite(&min, sizeof(float), 1, lbgcomp_file);
            max=(float)findMaxVal_Vector((void *)vec, (unsigned)size, CVIP_FLOAT);
            fwrite(&max, sizeof(float), 1, lbgcomp_file);
            max=(max-min);
            while(count<size) {
               header=(byte)((vec[count++]-min)*255/max);
               fwrite(&header, sizeof(byte), 1, lbgcomp_file);
            }
            break;

            case 4:
            while(count<size) {
               data[0]=(byte)(index[count++]<<4);
               data[0]|=(byte)index[count++];
               fwrite(data, sizeof(byte), 1, lbgcomp_file);
            }
            break;

            case 5:
            while(count<size) {
               data[0]=(byte)(index[count++]<<3);
               data[0]|=(byte)(index[count]>>2);
               data[1]=(byte)(index[count++]<<6);
               data[1]|=(byte)(index[count++]<<1);
               data[1]|=(byte)(index[count]>>4);
               data[2]=(byte)(index[count++]<<4);
               data[2]|=(byte)(index[count]>>1);
               data[3]=(byte)(index[count++]<<7);
               data[3]|=(byte)(index[count++]<<2);
               data[3]|=(byte)(index[count]>>3);
               data[4]=(byte)(index[count++]<<5);
               data[4]|=(byte)(index[count++]);
               fwrite(data, sizeof(byte), 5, lbgcomp_file);
            }
            break;

            case 6:
            while(count<size) {
               data[0]=(byte)(index[count++]<<2);
               data[0]|=(byte)(index[count]>>4);
               data[1]=(byte)((index[count++]&15)<<4);
               data[1]|=(byte)(index[count]>>2);
               data[2]=(byte)((index[count++]&3)<<6);
               data[2]|=(byte)(index[count++]);
               fwrite(data, sizeof(byte), 3, lbgcomp_file);
            }
            break;

            case 7:
            while(count<size) {
               data[0]=(byte)(index[count++]<<1);
               data[0]|=(byte)(index[count]>>6);
               data[1]=(byte)((index[count++]&63)<<2);
               data[1]|=(byte)(index[count]>>5);
               data[2]=(byte)((index[count++]&31)<<3);
               data[2]|=(byte)(index[count]>>4);
               data[3]=(byte)((index[count++]&15)<<4);
               data[3]|=(byte)(index[count]>>3);
               data[4]=(byte)((index[count++]&7)<<5);
               data[4]|=(byte)(index[count]>>2);
               data[5]=(byte)((index[count++]&3)<<6);
               data[5]|=(byte)(index[count]>>1);
               data[6]=(byte)((index[count++]&1)<<7);
               data[6]|=(byte)(index[count++]);
               fwrite(data, sizeof(byte), 7, lbgcomp_file);
            }
            break;

            case 8:
            while(count<size) {
               data[0]=(byte)index[count++];
               fwrite(data, sizeof(byte), 1, lbgcomp_file);
            }
            break;

            case 9:
            while(count<size) {
               data[0]=(byte)(index[count]>>1);
               data[1]=(byte)((index[count++]&1)<<7);
               data[1]|=(byte)(index[count]>>2);
               data[2]=(byte)((index[count++]&3)<<6);
               data[2]|=(byte)(index[count]>>3);
               data[3]=(byte)((index[count++]&7)<<5);
               data[3]|=(byte)(index[count]>>4);
               data[4]=(byte)((index[count++]&15)<<4);
               data[4]|=(byte)(index[count]>>5);
               data[5]=(byte)((index[count++]&31)<<3);
               data[5]|=(byte)(index[count]>>6);
               data[6]=(byte)((index[count++]&63)<<2);
               data[6]|=(byte)(index[count]>>7);
               data[7]=(byte)((index[count++]&127)<<1);
               data[7]|=(byte)(index[count]>>8);
               data[8]=(byte)(index[count++]&255);
               fwrite(data, sizeof(byte), 9, lbgcomp_file);
            }
            break;

            case 10:
            while(count<size) {
               data[0]=(byte)(index[count]>>2);
               data[1]=(byte)((index[count++]&3)<<6);
               data[1]|=(byte)(index[count]>>4);
               data[2]=(byte)((index[count++]&15)<<4);
               data[2]|=(byte)(index[count]>>6);
               data[3]=(byte)((index[count++]&63)<<2);
               data[3]|=(byte)(index[count]>>8);
               data[4]=(byte)(index[count++]&255);
               fwrite(data, sizeof(byte), 5, lbgcomp_file);
            }
            break;

            case 11:
            while(count<size) {
               data[0]=(byte)(index[count]>>3);
               data[1]=(byte)((index[count++]&7)<<5);
               data[1]|=(byte)(index[count]>>6);
               data[2]=(byte)((index[count++]&63)<<2);
               data[2]|=(byte)(index[count]>>9);
               data[3]=(byte)((index[count]&511)>>1);
               data[4]=(byte)((index[count++]&1)<<7);
               data[4]|=(byte)(index[count]>>4);
               data[5]=(byte)((index[count++]&15)<<4);
               data[5]|=(byte)(index[count]>>7);
               data[6]=(byte)((index[count++]&127)<<1);
               data[6]|=(byte)(index[count]>>10);
               data[7]=(byte)((index[count]&1023)>>2);
               data[8]=(byte)((index[count++]&3)<<6);
               data[8]|=(byte)(index[count]>>5);
               data[9]=(byte)((index[count++]&31)<<3);
               data[9]|=(byte)(index[count]>>8);
               data[10]=(byte)(index[count++]&255);
               fwrite(data, sizeof(byte), 11, lbgcomp_file);
            }
            break;

            case 12:
            while(count<size) {
               data[0]=(byte)(index[count]>>4);
               data[1]=(byte)((index[count++]&15)<<4);
               data[1]|=(byte)(index[count]>>8);
               data[2]=(byte)(index[count++]&255);
               fwrite(data, sizeof(byte), 3, lbgcomp_file);
            }
            break;
      }
      free(data);
      stuff=stuff->next;   
      }
   info=info->next;
   i++;
   }     
   if(answer) free(answer);
   fclose(lbgcomp_file);
}


/************************************************************************
*									*
*	ROUTINE/PGM NAME: lbg_decompress()				*
*									*
*	DESCRIPTION: This routine decompresses an LBG_encoded image	*
*	stored on disk by loading up the stored codebook indeces and	*
*	converting them to a floating point image.  The processing	*
*	history of the image is added to its image structure, and the	*
*	necessary image transforms are automatically performed to	*
*	reconstruct an approximation to the original image.		*
*									*
*	AUTHOR: Arve Kjoelen, SIUE					*
*									*
*	INITIAL CODING DATE: 12/10/93					*
*									*
*	LAST MODIFICATIONS MADE: 12/10/93				*
*									*
************************************************************************/
Image *lbg_decompress(VQ_INFO info, char *answer1) {
   Image *image;
   char *answer=calloc(80, 1);
   HISTORY h_stuff, h_story;
   MATRIX *matrix;
   FILE *lbgcomp_file;
   ELEMENT stuff;
   float min, max, *vec;
   byte header, *data, temp, rows, cols, scheme;
   int bands, i, *index, j, no_bits, size, count, k, l, **h_ptr;

   fprintf(stdout, "Decoding of LBG data\n");
   fprintf(stdout, "====================\n");
   if(answer1==(char *)NULL) {
      fprintf(stdout, "Please enter the name of the data file, including extension\n");
      (void)gets(answer);
   }
   else {
      /* copy filename, except for last 3 characters */
      strncpy(answer, answer1, (size_t)(strlen(answer1)-3));
   }
   lbgcomp_file = fopen(answer, "rb");
   if(lbgcomp_file == (FILE *)NULL) {
      fprintf(stdout, "The file does not exist\n");
      return(0);
   }
   fread(&header, sizeof(byte), 1, lbgcomp_file);
   if(header>=128) info->block_type=WAVL;
   else info->block_type=EQUAL_BLOCKS;
   temp=(header&28);
   if(temp==4) info->bands=4;
   else if(temp==8) info->bands=7;
   else if(temp==12) info->bands=10;
   else if(temp==16) info->bands=13;
   else if(temp==20) info->bands=16;
   else if(temp==24) info->bands=19;
   if(header&1) scheme|=64;
   if(header&2) scheme|=32;
   temp=header; /* save header value so we can determine if PCT's been done */
   header=header&96;
   if(header==64) bands=7;
   else if(header==32) bands=3;
   else bands=1;
   fread(&rows, sizeof(byte), 1, lbgcomp_file);
   fread(&cols, sizeof(byte), 1, lbgcomp_file);
   fprintf(stderr, "bands=%d, rows=%d, cols=%d\n", (int)bands, (int)cols, (int)rows);
   if(temp&2) {
      image = (Image *)calloc(1, sizeof(Image));
      image->bands=bands;
      image->color_space=RGB;
      image->image_format=PPM;
      image->image_ptr=(MATRIX **)calloc(bands, sizeof(MATRIX *));
      image->image_ptr[0]=(MATRIX *)new_Matrix((unsigned)(rows<<3), (unsigned)(cols<<3), CVIP_FLOAT, REAL);
      image->image_ptr[1]=(MATRIX *)new_Matrix((unsigned)(rows<<2), (unsigned)(cols<<2), CVIP_FLOAT, REAL);
      image->image_ptr[2]=(MATRIX *)new_Matrix((unsigned)(rows<<2), (unsigned)(cols<<2), CVIP_FLOAT, REAL);
   }
   else {
      image=(Image *)new_Image(PPM, RGB, bands, (unsigned)(rows<<3), (unsigned)(cols<<3), CVIP_FLOAT, REAL);
   }
   /* Add history information so inv. xform can be performed */
   if(info->block_type==WAVL) {
      h_stuff=(HISTORY)malloc(sizeof(struct history));
      h_stuff->packetP=(PACKET *)malloc(sizeof(PACKET));
      h_stuff->packetP->dsize=2;
      h_stuff->packetP->dtype=(CVIP_TYPE *)malloc(sizeof(CVIP_TYPE)*2);
      h_stuff->packetP->dtype[0]=CVIP_INTEGER;
      h_stuff->packetP->dtype[1]=CVIP_INTEGER;
      h_ptr=(int **)malloc(sizeof(int *)*2);
      h_ptr[0]=(int *)malloc(sizeof(int));
      h_ptr[1]=(int *)malloc(sizeof(int));
      /* Read which wavelet basis was used into 'rows' */
      fread(&rows, sizeof(byte), 1, lbgcomp_file);
      h_ptr[0][0]=(int)rows;
      h_ptr[1][0]=(int)(info->bands-1)/3;
      h_stuff->packetP->dptr=(void **)h_ptr;
      h_stuff->next=(HISTORY)NULL;
      h_stuff->ftag=WAVELET;
      history_add(image, h_stuff);
   }
   /* READ PCT INFO IF THERE */
   if(temp&2) { /* Standard PCT performed */
      fprintf(stderr, "Reading PCT transform matrix...\n");
      matrix=new_Matrix(3, 3, CVIP_DOUBLE, REAL);
      fread(matrix->rptr[0], sizeof(double), 9, lbgcomp_file);
      fprintf(stderr, "PCT matrix read:\n");
      print_Matrix(matrix);
      /* Add matrix & PCT info to history structure */
      h_story=(HISTORY)malloc(sizeof(struct history));
      h_story->packetP=(PACKET *)malloc(sizeof(PACKET));
      h_story->ftag=PCT;
      h_story->packetP->dptr=(void **)(MATRIX *)matrix;
      history_add(image, h_story);
   }
   i=0;
   fprintf(stderr, "Working...");
   while(i<image->bands) {
      if(0) { /* took out if(temp&1) */
         fprintf(stdout, "The PCT has been performed do decorrelate the\n");
         fprintf(stdout, "frequency subbands of this spectral band;\n");
         fprintf(stdout, "Reading PCT matrix...\n");
         
         info->pcts=(MATRIX **)malloc(sizeof(MATRIX *)*2);
         info->pct_done=CVIP_YES;
         for(k=0; k<2; k++) {
            info->pcts[k]=new_Matrix(3, 3, CVIP_DOUBLE, REAL);
            fread(info->pcts[k]->rptr[0], sizeof(double), 9, lbgcomp_file);
            fprintf(stdout, "PCT matrix read:\n");
            print_Matrix(info->pcts[k]);
         }
      }
      stuff=info->elements;
      for(j=0; j<info->bands; j++) {
         stuff->data=(float **)malloc(sizeof(float *)*info->nvecs[j]);
         size=info->hsize[j]*info->vsize[j];
         stuff->data[0]=(float *)malloc(sizeof(float)*info->nvecs[j]*size);
         for(k=0; k<info->nvecs[j]; k++) {
            stuff->data[k]=(float *)&stuff->data[0][k*size];
         }
         stuff->codebook_index =(int *)malloc(sizeof(int)*info->nvecs[j]);
         if(info->codebook_size[j]) {
            for(header=0; header<16; header++) {
               if(pow(2, header)==info->codebook_size[j]) {
                  no_bits=(int)header;
               }
            }
         }
         else no_bits=32; /* just for the heck of it */
         size=(int)info->nvecs[j];
         data = (byte *)malloc((size_t)no_bits);
         index=(int *)stuff->codebook_index;
         count=0;
         switch(no_bits) {
            case 0: /* This case occurs only for frequency band #0 */
            stuff->codebook=(float **)malloc(sizeof(float *));
            size=info->hsize[0]*info->vsize[0];
            stuff->codebook[0]=(float *)malloc(sizeof(float)*size);
            vec=stuff->codebook[0];
            fread(&min, sizeof(float), 1, lbgcomp_file);
            fread(&max, sizeof(float), 1, lbgcomp_file);
            max=(max-min);
            while(count<size) {
               fread(&header, sizeof(byte), 1, lbgcomp_file);
               vec[count++]=(float)(min+((float)header*max)/255.0);
               if((vec[count-1]<(min-1.0)) || (vec[count-1]>(max+min+1.0))) {
                  fprintf(stderr, "Value out of range: vec=%f, min=%f, max=%f\n", vec[count-1], min, max);
               }
            }
            index[0]=0;
            break;

            case 4:
            while(count<size) {
               fread(data, sizeof(byte), 1, lbgcomp_file);
               index[count++]=(int)(data[0]>>4);
               index[count++]=(int)(data[0]&15);
            }
            break;

            case 5:
            while(count<size) {
               fread(data, sizeof(byte), 5, lbgcomp_file);
               index[count++]=(int)(data[0])>>3;
               index[count]=(int)(data[0]&7)<<2;
               index[count++]|=(int)data[1]>>6;
               index[count++]=(int)(data[1]&63)>>1;
               index[count]=(int)(data[1]&1)<<4;
               index[count++]|=(int)data[2]>>4;
               index[count]=(int)(data[2]&15)<<1;
               index[count++]|=(int)data[3]>>7;
               index[count++]=(int)(data[3]&127)>>2;
               index[count]=(int)(data[3]&3)<<3;
               index[count++]|=(int)data[4]>>5;
               index[count++]=(int)(data[4]&31);
            }
            break;

            case 6:
            while(count<size) {
               fread(data, sizeof(byte), 3, lbgcomp_file);
               index[count++]=(int)(data[0])>>2;
               index[count]=(int)(data[0]&3)<<4;
               index[count++]|=(int)data[1]>>4;
               index[count]=(int)(data[1]&15)<<2;
               index[count++]|=(int)data[2]>>6;
               index[count++]=(int)(data[2]&63);
            }
            break;

            case 7:
            while(count<size) {
               fread(data, sizeof(byte), 7, lbgcomp_file);
               index[count++]=(int)(data[0])>>1;
               index[count]=(int)(data[0]&1)<<6;
               index[count++]|=(int)data[1]>>2;
               index[count]=(int)(data[1]&3)<<5;
               index[count++]|=(int)data[2]>>3; 
               index[count]=(int)(data[2]&7)<<4;
               index[count++]|=(int)data[3]>>4;
               index[count]=(int)(data[3]&15)<<3;
               index[count++]|=(int)data[4]>>5;
               index[count]=(int)(data[4]&31)<<2;
               index[count++]|=(int)data[5]>>6;
               index[count]=(int)(data[5]&63)<<1;
               index[count++]|=(int)data[6]>>7;
               index[count++]=(int)(data[6]&127);
            }
            break;

            case 8:
            while(count<size) {
               fread(data, sizeof(byte), 1, lbgcomp_file);
               index[count++]=(int)data[0];
            }
            break;

            case 9:
            while(count<size) {
               fread(data, sizeof(byte), 9, lbgcomp_file);
               index[count]=(int)(data[0])<<1;
               index[count++]|=(int)data[1]>>7;
               index[count]=(int)(data[1]&127)<<2;
               index[count++]|=(int)data[2]>>6; /* */
               index[count]=(int)(data[2]&63)<<3;
               index[count++]|=(int)data[3]>>5;
               index[count]=(int)(data[3]&31)<<4;
               index[count++]|=(int)data[4]>>4;
               index[count]=(int)(data[4]&15)<<5;
               index[count++]|=(int)data[5]>>3;
               index[count]=(int)(data[5]&7)<<6;
               index[count++]|=(int)data[6]>>2;
               index[count]=(int)(data[6]&3)<<7;
               index[count++]|=(int)data[6]>>1;
               index[count]=(int)(data[6]&1)<<8;
               index[count++]|=(int)data[7];
            }
            break;

            case 10:
            while(count<size) {
               fread(data, sizeof(byte), 5, lbgcomp_file);
               index[count]=(int)(data[0])<<2;
               index[count++]|=(int)(data[1])>>6;
               index[count]=(int)(data[1]&63)<<4;
               index[count++]|=(int)data[2]>>4;
               index[count]=(int)(data[2]&15)<<6;
               index[count++]|=(int)data[3]>>2;
               index[count]=(int)(data[3]&3)<<8;
               index[count++]|=(int)data[4];
            }
            break;

            case 11:
            while(count<size) {
               fread(data, sizeof(byte), 11, lbgcomp_file);
               index[count]=(int)(data[0])<<3;
               index[count++]|=(int)(data[1])>>5;
               index[count]=(int)(data[1]&31)<<6;
               index[count++]|=(int)data[2]>>2;
               index[count]=(int)(data[2]&3)<<9;
               index[count]|=(int)data[3]<<1;
               index[count++]|=(int)data[4]>>7;
               index[count]=(int)(data[4]&127)<<4;
               index[count++]|=(int)data[5]>>4;
               index[count]=(int)(data[5]&15)<<7;
               index[count++]=(int)data[6]>>1;
               index[count]=(int)(data[6]&1)<<10;
               index[count]|=(int)data[7]<<2;
               index[count++]|=(int)data[8]>>6;
               index[count]=(int)(data[8]&63)<<5;
               index[count++]|=(int)(data[9])>>3;
               index[count]=(int)(data[9]&7)<<8;
               index[count++]|=(int)data[10];
            }
            break;

            case 12:
            while(count<size) {
               fread(data, sizeof(byte), 3, lbgcomp_file);
               index[count]=(int)(data[0])<<4;
               index[count++]|=(int)(data[1])>>4;
               index[count]=(int)(data[1]&15)<<8;
               index[count++]|=(int)data[2];
            }
            break;
         }
         free(data);
         stuff=stuff->next;
      }
      info=info->next;
      i++;
   }
   if(answer) free(answer);
   /*close(lbgcomp_file); date 3/20/98 */
   fclose(lbgcomp_file);
   return(image);
}

float findminval_Matrix(unsigned rows, unsigned cols, float **rptr) {
   int i, j;
   float min;

   min=rptr[0][0];

   for(i=0; i<rows; i++) {
     for(j=0; j<cols; j++) {
        if(rptr[i][j]<min) min=rptr[i][j];
     }
   }
   return(min);
}

float findmaxval_Matrix(unsigned rows, unsigned cols, float **rptr) {
   int i, j;
   float max;

   max=rptr[0][0];

   for(i=0; i<rows; i++) {
      for(j=0; j<cols; j++) {
         if(rptr[i][j]>max) max=rptr[i][j];
      }
   }
   return(max);
}



