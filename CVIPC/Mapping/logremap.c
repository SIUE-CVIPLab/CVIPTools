/*****************************************************************************
 * ======================================================================    *
 * Image Processing/Computer Vision Tool Project - Dr. Scott Umbaugh SIUE    *
 * ======================================================================    *
 *                                                                           *
 * ROUTINE/PGM NAME: logremap.c                                              *
 *                                                                           *
 *              DESCRIPTION: This function perform logarithm transformation  *
 * on fourier spectrum(s), original or filtered.                             *
 *     If band != -1, the specified band will be extracted;                  *
 *     if band == -1, not single band will be extracted;                     *
 *                AUTHOR(s): Simon Low, Arve Kjoelen,Kun Luo, Yansheng Wei   *
 *                                                                           *
 *            RELATED FILES: program_invoke.c                                *
 *                                                                           *
 *              CODING DATE: 2/22/94                                         *
 *  LAST MODIFICATIONS MADE: 2/22/94                                         *
 *                                                                           *
 *****************************************************************************
RCS (Revision Control System) Information - Added automatically by RCS)

$Author: achomai $
$Date: 1998/04/21 23:48:13 $
$Source: /home/cvip/cvipapps/CVIPtools3.7/Mapping/RCS/logremap.c,v $
$Header: /home/cvip/cvipapps/CVIPtools3.7/Mapping/RCS/logremap.c,v 1.24 1998/04/21 23:48:13 achomai Exp $

*******************************************************************************/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CVIPtools.h"
#include "CVIPimage.h"
#include "CVIPdef.h"
#include "CVIPmap.h"
#include "CVIPconvert.h"

/*band is used to tell whether to extract a band spectrum or not
  band = -1  -> no need to extract a band spectrum
	= 0  -> extract red band
	= 1  -> extract green band
	= 2  -> extract blue band
	...
*/
Image *
logMap_Image(
	Image 	*imgP, 
	int	band
)
{
  	Image  		*remP,*remP1;
	IMAGE_FORMAT 	format;
  	HISTORY 	stuff;
  	char 		bsize[6], *assign="spectrum",
			*strP = NULL;
	float		**rdataP, **idataP, N, **odataP;
    	int 		h, w, x, y, color=0, bands, k, m, *hptr, block_size;
  	double 		temp;
	char		*fn = "logMap_Image";

  	if(getDataType_Image(imgP) != CVIP_FLOAT)
     		(void) cast_Image(imgP, CVIP_FLOAT);

  	bands	= getNoOfBands_Image(imgP);
  	h 	= getNoOfRows_Image(imgP);
  	w 	= getNoOfCols_Image(imgP);

	if(band > bands-1) {
		error_CVIP(fn,"The maximum band number is %d\n",bands-1);
		band = bands-1;
	}
	if(band==-1 && bands == 3)  
  		remP = new_Image(PPM,RGB,bands,h,w,CVIP_FLOAT,REAL);
	else
		remP = new_Image(PGM,GRAY_SCALE,1,h,w,CVIP_FLOAT,REAL);

	if(remP == NULL)
	{
		delete_Image(imgP);
		return(NULL);
	}
	(void)history_copy(imgP, remP);

  	if(	(imgP->bandP[0]->data_format == COMPLEX)&&
		(!history_check(FFT, imgP))) { 
		error_CVIP(fn,"No FFT transform detected on COMPLEX image.\n");
    		delete_Image(remP);
		delete_Image(imgP);
    		return (Image *)NULL;
  	}
  	else if(imgP->bandP[0]->data_format == COMPLEX){
     		stuff=history_get(imgP, FFT);
     		GET_HIST_DATA(stuff,0,block_size );
     		N=(float)block_size;
  	} 
	else {	/* Not COMPLEX */
		if(history_check(WALSH, imgP))
		stuff=history_get(imgP, WALSH);
		else if(history_check(HADAMARD, imgP))
		stuff=history_get(imgP, HADAMARD);
		else if(history_check(HAAR, imgP))
		stuff=history_get(imgP, HAAR);
		else if(history_check(DCTXFORM, imgP))
		stuff=history_get(imgP, DCTXFORM);
		else if(history_check(WAVELET, imgP))
		stuff=history_get(imgP, WAVELET);
		else {
			error_CVIP(fn,"No transform detected in image history.\n");
			delete_Image(remP);
			delete_Image(imgP);
			return (Image *)NULL;
		}
		GET_HIST_DATA(stuff,0,block_size);
		N=(float)block_size;
		if(history_check(WAVELET, imgP)) N=2; /* Arbitrary */
		N*=N;
	}
	if(imgP->bandP[0]->data_format == COMPLEX){
		for (k = 0; k < bands; k++) {
			if(band != -1) k = band;
			rdataP = getRealData_Matrix(getBand_Image(imgP, k));
			idataP = getImagData_Matrix(getBand_Image(imgP, k));
			if(band ==-1)
				odataP = getRealData_Matrix(getBand_Image(remP, k));
			else
				odataP = getRealData_Matrix(getBand_Image(remP, 0));

  			for(y = 0; y < h; y++)
    			for(x = 0; x < w; x++) {
      				temp = 	(double)sqrt(pow((double)(rdataP[y][x]), 2)+ \
					pow((double)(idataP[y][x]), 2)) ;
      				odataP[y][x] = log10(1.0+temp);
    			} 
			if(band !=-1)
			break;
		}
	}
	else {		/* Not COMPLEX */
		/* if(history_check(WALSH, imgP)) */
		N=16*LOG2(N);
		for (k = 0; k < bands; k++) {
			if(band != -1) k = band;
			rdataP = getRealData_Matrix(getBand_Image(imgP, k));
			if(band ==-1)
			odataP = getRealData_Matrix(getBand_Image(remP, k));
			else
			odataP = getRealData_Matrix(getBand_Image(remP, 0));

  			for(y = 0; y < h; y++) 
    			for(x = 0; x < w; x++) {
/*
      				temp = 	ABS((double)((128.0*rdataP[y][x])));
*/
				temp = ABS((double)(N*rdataP[y][x]));
      				odataP[y][x] = (float)LOG2(1.0+temp);
    			} 
			if(band !=-1)
			break;
		}
	}

	remP1= (Image *) remap_Image(remP,CVIP_BYTE,0,255);
	if (remP) delete_Image(remP);
	if (imgP) delete_Image(imgP);
	return remP1;
}
