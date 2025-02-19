/******************************************************************************
    ======================================================================
    Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
    ======================================================================

                   Name: crop_image
          Expanded Name: crop_image
             Parameters: Pointer to original image of type Image
                Returns: Image Pointer
            Description: Crops off specified rows or columns in an image.
            Diagnostics: None as of yet
             References: None
              Author(s): Arve Kjoelen
                         Southern Illinois University @ Edwardsville
    Initial Coding Date: 9/26/95

			 This file contains the functions necessary to let
	the user crop off any row(s) or column(s) from the image.  The 
	resulting image after cropping will be smaller than the original, 
	i.e. the specified row(s) and column(s) are deleted.


 



*******************************************************************************/
/*
 * crop - crop an image, specifying starting and ending points,
 * and the size of the result.  This module moved from SEGMENTATION/
 * DermVis.c.  Deletes the input image, and replaces it with the
 * cropped image.  Works on all data types.  Cupports COMPLEX images.
 *
 * Credits - Greg Hance, Arve Kjoelen
 *
 * initial inclusion date: 12/13/96
 */
#include "CVIPimage.h"
#include "CVIPgeometry.h"

Image *crop(
        Image *imgP,
        unsigned row_offset,
        unsigned col_offset,
        unsigned rows,
        unsigned cols
)
{
        unsigned no_of_bands;
        register int i;
        Matrix *origP, *cropP;
	HISTORY stuff;

         no_of_bands = getNoOfBands_Image(imgP); 

        for(i=0; i < no_of_bands; i++) {
                origP = getBand_Image(imgP, i);
                cropP = crop_Matrix(origP, row_offset, col_offset, rows, cols);
                if(!cropP) return 0;
                setBand_Image(imgP,cropP,i);
        	delete_Matrix(origP);
        }

	stuff=(HISTORY)malloc(sizeof(struct history));
	stuff->packetP = (PACKET *)malloc(sizeof(PACKET));
	stuff->packetP->dsize=4;
	stuff->packetP->dtype=(CVIP_TYPE *)malloc(4*sizeof(CVIP_TYPE));
	stuff->packetP->dtype[0]=CVIP_INTEGER;
	stuff->packetP->dtype[1]=CVIP_INTEGER;
	stuff->packetP->dtype[2]=CVIP_INTEGER;
	stuff->packetP->dtype[3]=CVIP_INTEGER;
	stuff->packetP->dptr = (void**)malloc(sizeof(void*)*stuff->packetP->dsize);
	stuff->packetP->dptr[0]=(void *)malloc(sizeof(int));
	stuff->packetP->dptr[1]=(void *)malloc(sizeof(int));
	stuff->packetP->dptr[2]=(void *)malloc(sizeof(int));
	stuff->packetP->dptr[3]=(void *)malloc(sizeof(int));
	/*stuff->packetP->dptr[0] = (int*)malloc(4*sizeof(int));*/
	memcpy((void *)stuff->packetP->dptr[0], (const void *)&row_offset, sizeof(int));
	memcpy((void *)stuff->packetP->dptr[1], (const void *)&col_offset, sizeof(int));
	memcpy((void *)stuff->packetP->dptr[2], (const void *)&rows, sizeof(int));
	memcpy((void *)stuff->packetP->dptr[3], (const void *)&cols, sizeof(int));
	stuff->next=(HISTORY)NULL;
	stuff->ftag=CROP;
	history_add(imgP, stuff);
	stuff=NULL;
	return(imgP);
}

