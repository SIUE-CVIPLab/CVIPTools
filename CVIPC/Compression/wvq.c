/************************************************************************
*									*
*		===================================			*
*		MASTER'S THESIS - Arve Kjoelen SIUE			*
*		===================================			*
*									*
*	FILE NAME: wvq.c						*
*									*
*	SYNOPSIS: This file contains routines related to the LBG	*
*	(Linde, Buzo, Gray) algorithm for vector quantization.  Among	*
*	the routines are algorithms that remap square blocks of an 	*
*	image to one-dimensional arrays for use as input to the LBG	*
*	algorithm.  Routines that implement the recursive LBG method	*
*	for Vector Quantization are also in this file.			*
*									*
*	AUTHOR: Arve Kjoelen, SIUE					*
*									*
*	RELATED FILES: LBG.h, LBG.c					*
*									*
*	INITIAL CODING DATE: 9/27/93					*
*									*
*	LAST MODIFICATIONS MADE: 12/30/93				*
*									*
* RCS (Revision Control System) Information
* ...Added automatically by RCS 
*
** $Log: wvq.c,v $
** Revision 1.6  1997/11/07 22:00:46  wzheng
** modify to create first "wvq" cviptcl command
**
** Revision 1.3  1997/03/08 17:06:25  yawei
** Swaped CVIP_YES and CVIP_NO
**
** Revision 1.2  1997/03/08 00:59:56  yawei
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
** Revision 1.1  1996/12/29 04:35:15  yawei
** Initial revision
**
*
*									*
************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "CVIPtoolkit.h"
#include "CVIPdef.h"
#include "LBG.h"
#include "wavelet.h"

/************************************************************************
*									*
*	ROUTINE/PGM NAME:	wvq_setup()				*
*									*
*	DESCRIPTION:		This setup routine for wavelet-based	*
*		vector quantization lets the user choose between 	*
*		several 'canned' compression schemes.  These 		*
*		shcemes take care of everything - wavelet transform,	*
*		vector quantization and output to disk.  The input is 	*
*		the image we want to compress.				*
*									*
*	AUTHOR: Arve Kjoelen, SIUE	(akjoele@siue.edu)		*
*									*
*	INITIAL CODING DATE: 5/11/95					*
*									*
*	LAST MODIFICATIONS MADE: Thu May 11 11:56:01 CDT 1995		*
*									*
************************************************************************/
int wvq_compress(Image *input,int choice,char *name) {
	Image *image;
	/*char *name;*/
	int arg1, arg2, **hptr, *tptr, done, lowband, maxsz, size, fbands, j, dim, i=0;
	HISTORY stuff;
	VQ_INFO info, temp;	/* Vector Quantization info structure */
	ELEMENT struc;		/* Structure related to Vecotr Quantization */
	CVIP_BOOLEAN remap;

	/*
	 * get a duplicate copy of the image. so the processing 
	 * will not affect the orignal one
	 */
	image = duplicate_Image(input);
	if(image->image_ptr[0]->rows != image->image_ptr[0]->cols) {
		maxsz=MAX(image->image_ptr[0]->rows, image->image_ptr[0]->cols);
		while(size>1) {
			if(size>maxsz)
				size>>=1;
			else
				(void)zero_pad(image, 2*size, 2*size);
		}
	}
/*
	fprintf(stdout, "\nAVAILABLE COMPRESSION SCHEMES:\n");
	fprintf(stdout, "1.	10.16:1	Compression - slow\n");
	fprintf(stdout, "2.	15:1 	Compression - slow\n");
	fprintf(stdout, "3.	32.87:1	Compression - slow\n");
	fprintf(stdout, "4.	35.73:1 Compression - fair speed\n");
	fprintf(stdout, "Please Enter Your Choice:\n");
	(void)gets(answer);
	choice=atoi(answer);
	free(answer);
*/

	if(image->image_ptr[0]->data_type !=CVIP_FLOAT)
      		(void) cast_Image(image, CVIP_FLOAT);

	/* Initialization stuff for wavelet transform */
	if(choice<5) {
	   fprintf(stdout, "Performing Wavelet Xform:  10 subbands, Wavelet=daub4...\n");
	   lowband=(int)(image->image_ptr[0]->rows)>>2;
	   image=(Image *)wavdaub4_transform(image, 1, lowband);
	}
	/* Add history information for wavelet */
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
   	hptr[0][0]=2; /* 1=haar, 2=daub4 			*/
	if(choice<5)
   		hptr[1][0]=3; /* 1=4 fbands, 2=7fbands, 3=10fbands */
	else
		fprintf(stdout, "Not implemented\n");

   	stuff->packetP->dptr=(void **)hptr;
   	stuff->next=(HISTORY)NULL;
   	stuff->ftag=WAVELET;
   	history_add(image, stuff);


	/* Initialization stuff for Vector Quantization */
	fprintf(stdout, "Performing Vector Quantization...\n");

   /* Allocate main structure for vector quantization */
   info= (VQ_INFO)malloc(sizeof(struct VQ_info));
   info->block_type=WAVL;
   info->pct_done=CVIP_NO;
   info->elements=(ELEMENT)calloc(1, sizeof(struct element));
   temp=(VQ_INFO)info;
   while((++i)<image->bands) {
      temp->next = (VQ_INFO)calloc(1, sizeof(struct VQ_info));
      temp->next->block_type=WAVL;
      temp->next->pct_done=CVIP_NO;
      temp->next->elements=(ELEMENT)calloc(1, sizeof(struct element));
      temp=(VQ_INFO)temp->next;
   }
   temp->next = (VQ_INFO)NULL;
   temp=info;
   switch (choice) {
      case 1:
	 fbands=10;
	 info->scheme=7;
	 break;
      case 2:
	 fbands=10;
	 info->scheme=8;
	 break;
      case 3:
	 fbands=10;
	 info->scheme=2; 
	 break;
      case 4:
         fbands=10;
         info->scheme=5;
         break;	
      default:
	 fprintf(stderr, "Error, invalid scheme specified\n");
	 return -1;
   }

   /* selects the proper LBG scheme based on information passed to it */
   get_lbg_scheme((int)info->scheme, image->bands, info);

   /* llocates the memory needed for the one-dimensional vectors to 	*/
   /* which the image is to be transformed. The memory is stored as 	*/
   /* part of the 'element' structure. 					*/
   allocate_vectors(image, info);

   for(i=0; i<image->bands; i++) {
      if(image->bands>1) fprintf(stdout, "Color band #%d\n", i);
      for(j=0, struc = (ELEMENT)info->elements; j<info->bands; j++, struc=(ELEMENT)struc->next) {
      if(info->codebook_size[j]) {
         dim=(info->hsize[j]*info->vsize[j]);
         fprintf(stderr, "Iterating, frequency band #%d: Rel. Improv.:", j);
	 /* calculates the quantization error between the codebook 	*/
	 /* vectors used and the actual input vectors.			*/
         done=LBG_error(info->codebook_size[j], dim, struc, struc->codebook, 1, info->nvecs[j]);

	 /* assigns a codebook index to the input vectors based on the 	*/
	 /* nearest-neighbor classification criterion.  		*/
         encode_data(struc->codebook, struc->data, struc->codebook_index,
info->codebook_size[j], dim, info->nvecs[j]);

	 /* each codebook entry Ci, computes the centroid of all the 	*/
	 /* vectors encoded into Ci.					*/ 
         compute_centroid(struc, info->codebook_size[j], dim, info->nvecs[j]);

	 /* repeat the above processing					*/
         while(!LBG_error(info->codebook_size[j], dim, struc, struc->codebook, 0, info->nvecs[j])) {
            encode_data(struc->codebook, struc->data, struc->codebook_index, info->codebook_size[j], dim, info->nvecs[j]);
            compute_centroid(struc, info->codebook_size[j], dim, info->nvecs[j]);
            }
         }
      }   
      info=info->next;
   }
   fprintf(stdout, "Encoding complete.\n");
   info=temp;
   strcat(name,".temp");

   /* saves the current codebook to a file		*/
   /* the file name is called temp.lbgwav		*/ 
   name=save_cdbook(image, info, name);

   /* stores an LBG-encoded image to disk		*/
   /* the file is called temp.lbg			*/
   lbg_save(image, info, name);

   /* Free data structures */
   free_info(info, image->bands);
   info=(VQ_INFO)NULL;
   
   /* Allocate main structure for vector quantization */
   /*i=0;
   info= (VQ_INFO)malloc(sizeof(struct VQ_info));
   info->pct_done=CVIP_NO;
   info->block_type=WAVL;
   info->elements=(ELEMENT)calloc(1, sizeof(struct element));
   temp=(VQ_INFO)info;
   while((++i)<image->bands) {
      temp->next = (VQ_INFO)calloc(1, sizeof(struct VQ_info));
      temp->next->block_type=WAVL;
      temp->next->elements=(ELEMENT)calloc(1, sizeof(struct element));
      temp=(VQ_INFO)temp->next;
   }
   temp->next = (VQ_INFO)NULL;*/

   /* ?????????????????? */
   /* if this image pointer is deleted, the hash maybe corrupted. */
   /* The function can not display images. still investigating    */
   /* this problem*/
   /*free_info(info, image->bands);
   info=(VQ_INFO)NULL;*/
   if (stuff) free(stuff);
/*
   delete_Image(image);
   image=(Image *)NULL;
*/
}

Image *wvq_decompress(Image *input,char *name) {
	Image *image;
	VQ_INFO info, temp;
	HISTORY stuff;
	CVIP_BOOLEAN remap;
	int arg1, arg2, **hptr, *tptr, done, lowband, maxsz, size, fbands, j, dim, i=0;
	ELEMENT struc;		/* Structure related to Vecotr Quantization */
	image = duplicate_Image(input);
   info= (VQ_INFO)malloc(sizeof(struct VQ_info));
   info->block_type=WAVL;
   info->pct_done=CVIP_NO;
   info->elements=(ELEMENT)calloc(1, sizeof(struct element));
   temp=(VQ_INFO)info;
   while((++i)<image->bands) {
      temp->next = (VQ_INFO)calloc(1, sizeof(struct VQ_info));
      temp->next->block_type=WAVL;
      temp->next->pct_done=CVIP_NO;
      temp->next->elements=(ELEMENT)calloc(1, sizeof(struct element));
      temp=(VQ_INFO)temp->next;
   }
   temp->next = (VQ_INFO)NULL;
   fprintf(stderr, "Loading codebook: %s\n", name);
   if(!(load_lbg_book(info, name))) {
      fprintf(stderr, "Error reading codebook\n");
      return(Image *)NULL;
   }

   /* loading up the stored codebook indeces and converting them  */
   /* to a floating point image.  The processing history of the   */
   /* image is added to its image structure, and the necessary    */
   /* image transforms are automatically performed to reconstruct */
   /* an approximation to the original image.			  */
   image=lbg_decompress(info, name);

   /* reconstructs an image from the codebook indeces passed to   */
   /* the routine */
   do_decoding(image, info);

   /* Setup routine for the wavelet transform.                    */
   /* the routine passes each color band of the image along  with */
   /* the size of that band to the function wavdaub4_transform.   */
   image=wav_setup(image, &remap);

   /* Free data structures */
   free_info(info, image->bands);
   info=(VQ_INFO)NULL;
   
/*********************************
   free_info(info, image->bands);
   stuff=history_get(image, WAVELET);
   hptr=(int **)stuff->packetP->dptr;
   arg1=hptr[0][0];
   arg2=hptr[1][0];
   switch(hptr[0][0]) {
      case 1: image=(Image *)wavhaar_transform(image, -1, hptr[1][0]);
              break;
      case 2: image=(Image *)wavdaub4_transform(image, -1, hptr[1][0]);
              break;
      default: fprintf(stderr, "wvq_setup(): Warning: Error detected in history structure\n");
	      break;
   }
********************************/

   /*if (hptr[0]) free(hptr[0]);
   if (hptr[1]) free(hptr[1]);
   if (hptr) free(hptr);
   if (stuff) free(stuff);*/
   image->image_format = WVQ;
   return(image);
}
