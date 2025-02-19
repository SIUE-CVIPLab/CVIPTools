/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: extract_band.c
*           Description: extract an image band from a specified image and return
*			 the resulting monochrome image.
*         Related Files: libband.a
*   Initial Coding Date: 8/9/96
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
                   Name: extract_band
          Expanded Name: Extract Image Band
             Parameters: <inImg> - pointer to an Image structure
			 <bandno> - number of the spectral data band to be extracted as
			 a monochrome image.
                Returns: pointer to new Image structure containing the extracted band.
            Description: Extract a spectral band from a multiband image and return
			 the band in an Image structure.
	    Diagnostics: - returns with NULL pointer and error message when
			 cast cannot be performed.
			 - For the purposes of this function, bands are numbered such that
			 a color band has bands 1,2 and 3, not 0,1,2.  this is done to
			 make band extraction more intuitive.
			 - The input Image structure is deleted by this function.
              Credit(s): Arve Kjoelen
****************************************************************/

Image *extract_band(Image *inImg, int bandno) {
	Image		*outIm;
	HISTORY		stuff;
	int		*hptr;
	const char	fn[] = {"extract_band"};
   
	/*
	* Some sanity checks first...
	*/
	if(inImg == (Image *)NULL) {
		error_CVIP(fn,"Input image is NULL.\n");
		delete_Image(inImg);
		return((Image *)NULL);
	}
	if(bandno<1) {
		error_CVIP(fn,"The lowest band number you may extract is 1.\n");
		delete_Image(inImg);
		return(NULL);
	}
	if(inImg->bands < (bandno-1) ) {
		error_CVIP(fn,
			"Input image has too few bands to extract band %d\n",
			bandno);
		delete_Image(inImg);
		return((Image *)NULL);
	}
	/*
	* Allocate memory and set new image parameters.
	* Copy the image history.
	*/
	outIm=(Image *)malloc(sizeof(Image));
	if(outIm != NULL)
	{
	  outIm->bands=1; 
	  outIm->image_format=inImg->image_format;
	  outIm->color_space=GRAY_SCALE;
	 
	  outIm->story=(HISTORY)NULL;
	  history_copy(inImg, outIm);
	  /*
	  * Extract the band.
	  */
	  outIm->image_ptr=(Matrix **)malloc(sizeof(Matrix *));
	  if(outIm->image_ptr != NULL)
	  {
	    outIm->image_ptr[0]=(Matrix *)duplicate_Matrix(
				inImg->bandP[bandno-1],
				inImg->bandP[bandno-1]->data_format);
	    if(outIm->image_ptr[0] != NULL)
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
	              hptr[0]=bandno;
	              stuff->packetP->dptr=(void **)malloc(sizeof(void *));
	              if(stuff->packetP->dptr != NULL)
	              {
	                stuff->packetP->dptr[0]=(int *)hptr;
	                stuff->next=(HISTORY)NULL;
	                stuff->ftag=EXTRACT_BAND;
	                history_add(outIm, stuff);
	                delete_Image(inImg);
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
	      delete_Matrix(outIm->image_ptr[0]);
	    }
	    free(outIm->image_ptr);
	  }
	  free(outIm);
	}
	delete_Image(inImg);
	return(NULL);
}
