/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: assemble_bands.c
*           Description: assemble bands from several monochrome images to
*			 produce a multi-spectral image.  Return the
*			 "assembled" image.
*         Related Files: libband.a
*   Initial Coding Date: 8/12/96
*           Portability: Standard (ANSI) C
*             Credit(s): Arve Kjoelen
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
****************************************************************************/

#include "stdlib.h"
#include "stdio.h"
#include "CVIPimage.h"


/****************************************************************
                   Name: assemble_band
          Expanded Name: Assemble Image Bans
             Parameters: <inImgs> - pointer to pointers to image structures.
			 <noimgs> - number of images passed.
			 a monochrome image.
                Returns: pointer to new Image structure containing assembled
			 image.
            Description: assemble a multiband image from the passed monochrome
			 images.
	    Diagnostics: - returns with NULL pointer and error message when
			 assembly cannot be performed.
			 - If n images are passed, the result image will have
			 n bands.
			 - If any of the passed images are not monochrome,
			 the first spectral band of these images will be
			 used for asdsembly.  The other bands will be ignored.
			 - Support for complex images:  If all input images
			   are COMPLEX, the output will also be COMPLEX.  If
			   one or more of the input images are REAL, the output
			   will be REAL.
			 - The input Image structures are not deleted.
              Credit(s): Arve Kjoelen
****************************************************************/

Image *assemble_bands(Image **inImgs, int noimgs) {
	Image		*outIm;
	HISTORY		stuff;
	int		*hptr, cnt;
	FORMAT		fm=COMPLEX;
	const char	fn[] = {"assemble_bands"};
   
	/*
	* Some sanity checks first...
	*/
	if(inImgs == (Image **)NULL) {
		error_CVIP(fn,"No input images.\n");
		return((Image *)NULL);
	}
	for(cnt=0; cnt<noimgs; cnt++) {
	  if(inImgs[cnt] == (Image *)NULL ) {
		error_CVIP(
			fn,
			"Too few input images %d.  %d needed.\n",
			cnt+1,
			noimgs);
		return((Image *)NULL);
	  }
	  if(inImgs[cnt]->image_ptr[0]->data_format==REAL)
	  fm=REAL;
	  if(	(inImgs[cnt]->image_ptr[0]->rows !=
		inImgs[0]->image_ptr[0]->rows) ||
		(inImgs[cnt]->image_ptr[0]->cols !=
		inImgs[0]->image_ptr[0]->cols)) {
		error_CVIP(fn,"Input images must be of identical size.\n");
		error_CVIP(fn,"Try resizing your images.\n");
		return((Image *)NULL);
	  }
	}
   
	/*
	* Allocate memory and set new image parameters.
	*/
	outIm=(Image *)malloc(sizeof(Image));
	if(outIm != NULL)
	{
	  outIm->bands=noimgs; 
	  outIm->story=(HISTORY)NULL;
	  if(noimgs==3) {
	    outIm->image_format=PNG;
	    outIm->color_space=RGB;
	  }
	  else {
	    outIm->image_format=VIP;
	    outIm->color_space=GRAY_SCALE;
	  }
	  /*
	  * Assemble the image.
	  */
	  outIm->image_ptr=(Matrix **)malloc(sizeof(Matrix *)*noimgs);
	  if(outIm->image_ptr != NULL)
	  {
	    for(cnt=0; cnt<noimgs; cnt++) {
	      if(inImgs[cnt]->bands > 1) {
	        error_CVIP(
	          fn,
	          "Input image %d of %d has more than one band.\n",
	          cnt,
	          noimgs);
	        error_CVIP(fn,"Ignoring all but band 0.\n");
	      }
	      outIm->image_ptr[cnt]=duplicate_Matrix(
					inImgs[cnt]->image_ptr[0],
					fm);
	      if(outIm->image_ptr[cnt] == NULL)
	      break;
	    }
	    if(cnt == noimgs)
	    {
	      /*
	      * Add new history information.
	      */
	      stuff=(HISTORY)malloc(sizeof(struct history));
	      if(stuff != NULL)
	      {
	        stuff->packetP = (PACKET *)malloc(sizeof(PACKET));
	        if(stuff->packetP != NULL)
	        {
	          stuff->packetP->dsize=1;
	          stuff->packetP->dtype=(CVIP_TYPE *)malloc(sizeof(CVIP_TYPE));
	          if(stuff->packetP->dtype != NULL)
	          {
	            stuff->packetP->dtype[0]=CVIP_INTEGER;
	            hptr=(int *)malloc(sizeof(int));
	            if(hptr != NULL)
	            {
	              hptr[0]=noimgs;
	              stuff->packetP->dptr=(void **)malloc(sizeof(void *));
	              if(stuff->packetP->dptr != NULL)
	              {
	                stuff->packetP->dptr[0]=(int *)hptr;
	                stuff->next=(HISTORY)NULL;
	                stuff->ftag=ASSEMBLE_BANDS;
	                history_add(outIm, stuff);
	                return(outIm);
	              }
	              free(hptr);
	            }
	            free(stuff->packetP->dtype);
	          }
	          free(stuff->packetP);
	        }
	        free(stuff);
	      }
	    }
	    if(cnt != 0)
	    do{
	      cnt--;
	      delete_Matrix(outIm->image_ptr[cnt]);
	    }while(cnt != 0);
	    free(outIm->image_ptr);
	  }
	  free(outIm);
	}
	return(NULL);
 }
