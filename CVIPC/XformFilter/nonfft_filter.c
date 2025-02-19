/*****************************************************************************
 * ======================================================================    *
 * Image Processing/Computer Vision Tool Project - Dr. Scott Umbaugh SIUE    *
 * ======================================================================    *
 *                                                                           *
 * ROUTINE/PGM NAME: nonfft_filter.c                                         *
 *                                                                           *
 *                   Filtering setup program                                 *
 *              DESCRIPTION: This program is setup to handle filtering of    *
 * transforms whose dc is at the top left corner of the frequency spectrum.  *
 * For example: Walsh Hadamard, Sine, Cosine, DCT etc. The actual routines   *
 * that perform the filtering are in filter.c.                               *
 *                                                                           *
 *                   AUTHOR: 	Simon Low                                    *
 *				Greg Hance				     *
 *                                                                           *
 *            RELATED FILES: filter.c                                        *
 *                                                                           *
 *              CODING DATE: 1/15/92                                         *
 *  LAST MODIFICATIONS MADE: 11/18/92                                        *
 *                                                                           *
*****************************************************************************
RCS (Revision Control System) Information - Added automatically by RCS)
$Author: wzheng $
$Date: 1997/06/25 19:25:42 $
$Source: /home/cvip/cvipapps/CVIPtools3.6/XFORMFILTER/RCS/nonfft_filter.c,v $
$Header: /home/cvip/cvipapps/CVIPtools3.6/XFORMFILTER/RCS/nonfft_filter.c,v 1.14 1997/06/25 19:25:42 wzheng Exp $
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "CVIPdef.h"
#include "CVIPimage.h"
#include "CVIPxformfilter.h"

#define getRealData_Image(image,band_no) \
(getRealData_Matrix(getBand_Image(image,band_no)))

#define getImagData_Image(image,band_no) \
(getImagData_Matrix(getBand_Image(image,band_no)))

Image *
nonfft_xformfilter(
	Image 		*imgP, 
   int 		block_size, 
 	int 		dc, 
   FILTER_TYPE 	filtertype, 
   int 		p1, 
   float	p2, 
   int 		order
)
{
  	Image 		*blkP;
  	int 		rows, cols, p, q, mm, nn;
  	int 		pp2,nofblk, horiz_nofblk;
  	int 		x, y, j, k, a=0, b=0, m=0, n=0;
  	int 		horiz_counter=1;
  	float 		alfa=0.0, **rdfP, **idfP, **rbfP, **ibfP;
  	CVIP_BOOLEAN 	komplex=CVIP_YES;

  	cols = getNoOfCols_Image(imgP);
  	rows = getNoOfRows_Image(imgP);

  	if(getDataFormat_Image(imgP)==REAL)
    		komplex=CVIP_NO;

  	nofblk = ( rows/block_size) * (cols/block_size);
  	horiz_nofblk = cols / block_size;
	alfa=p2;
	pp2 = (int)p2;	

 	if(filtertype==HIGH_FREQ_EMPHASIS) { /* for high freq emphasis filter only */
  		if(alfa <0.01 || alfa >3.0) {
			error_CVIP("nonfft_xformfilter", "alpha should be 0.01--3.0");
			delete_Image(imgP);
			return (Image *)NULL;
  		}
 	}

 	blkP = (Image *) new_Image(
				getFileFormat_Image(imgP),
        			getColorSpace_Image(imgP), 
				getNoOfBands_Image(imgP),
				2*block_size, 
        			2*block_size,
				CVIP_FLOAT,
				getDataFormat_Image(imgP)
			); 
	history_copy(imgP,blkP);

   	for(j=0; j < nofblk; j++) {

     		for(k=0; k < getNoOfBands_Image(imgP); k++) {
			rdfP = getRealData_Image(imgP, k);
			rbfP = getRealData_Image(blkP, k);
			if(komplex) {
				idfP = getImagData_Image(imgP, k);
				ibfP = getImagData_Image(blkP, k);
			}
			m = block_size; 
			n = block_size;

     			for(x=b; x < (b+block_size); x++) {
			
       				for(y=a; y < (a+block_size); y++) {
					rbfP[m][n] = rdfP[x][y];        
       					if(komplex)
						ibfP[m][n] = idfP[x][y];
					/* 
					** m&n from block_size to 2*block_size 
					*/
         				n++;           
       				}
				/* 
				** increase as x increase 
				*/
       				m++;
				/* 
				** reinitialize as y restart fr 0 
				*/
       				n = block_size;
     			}
		}

     		if(filtertype != HIGH_FREQ_EMPHASIS)
       			blkP = (Image *) select_filter(blkP,
			2*block_size, dc,filtertype,p1, pp2, order);
		else
       			blkP=(Image *)High_Freq_Emphasis(blkP,
			2*block_size,dc,p1,alfa,order);
                
 			
		for(k=0; k < getNoOfBands_Image(imgP); k++) {
			rdfP = getRealData_Image(imgP, k);
			rbfP = getRealData_Image(blkP, k);
			if(komplex) {
				idfP = getImagData_Image(imgP, k);
				ibfP = getImagData_Image(blkP, k);
			}
			/* 
			** xfer image back to its matrix 
			*/ 
     			mm = block_size; 
			nn = block_size;

     			for( p=(x-block_size); p<x; p++) {
       				for( q=(y-block_size); q<y; q++) {
					rdfP[p][q] = rbfP[mm][nn];
       					if(komplex)
						idfP[p][q] = ibfP[mm][nn];
         	
         				nn++;
       				}
       				mm++;
       				nn = block_size;
     			}
		}

     		horiz_counter++;

     		if(horiz_counter > horiz_nofblk){
       			a = 0;
       			b+=block_size;
       			horiz_counter = 1; 
     		} else {
       			a += block_size;    
     		}

   	} /* loop through blocks */

	return imgP;
  
} 
/* 
** end nonfft_xformfilter(...) 
*/ 


Image *
select_filter ( 
	Image 	*filter_Image, 
	int 	blk_size, 
	int 	dc, 
	FILTER_TYPE 	filtertype, 
	int 	p1, 
	int 	p2, 
	int 	order
)
{
 Image *imgP;

 switch (filtertype) { 
                      
   case IDEAL_LOW: /* ilpf: ideal low pass filter */
      imgP = (Image *) Ideal_Low(filter_Image, blk_size, dc, p1); 
      return (imgP);
   case BUTTER_LOW:  /* blpf: butterworth low pass */
      imgP = (Image *) Butterworth_Low(filter_Image, blk_size, dc,p1,order);
      return(imgP);
   case IDEAL_HIGH:
      imgP =(Image *) Ideal_High(filter_Image, blk_size, dc,p1);
      return(imgP);
   case BUTTER_HIGH: 
      imgP = (Image *) Butterworth_High(filter_Image, blk_size, dc,p1,order);
      return(imgP);
   case IDEAL_BAND: /* ibpf */
      imgP = (Image *)Ideal_Band_Pass(filter_Image,blk_size,dc,p1,p2);  
      return(imgP);
   case BUTTER_BAND: /* bbpf */
      imgP=(Image *)Butterworth_Band_Pass(filter_Image,blk_size,dc,p1,p2,order);
      return(imgP);
   case IDEAL_REJECT: /* ibrf */
      imgP=(Image *)Ideal_Band_Reject(filter_Image,blk_size,dc,p1,p2);
      return(imgP);
   case BUTTER_REJECT:
      imgP=(Image *)Butterworth_Band_Reject(filter_Image,blk_size,dc,p1,p2,order);
     return(imgP);
   default:
      printf("\nError: Filter type not properly setup.\n"); 
      break; 
 }      
 return(NULL);
} /* End select_filter() */
