/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: raster_deblur.c
*           Description: 
*
*         Related Files: 
*   Initial Coding Date: November 17, CDT 1995
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Kun Luo
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1995 SIUE - by Kun Luo.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
** $Log: raster_deblur.c,v $
** Revision 1.5  1997/03/08 01:03:06  yawei
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
** Revision 1.4  1996/12/27 03:47:56  yawei
** IMAGE => Image
**
 * Revision 1.3  1996/12/25  00:01:34  yawei
 * filename change: raster_scan.c ==> raster_deblur.c
 *
 * Revision 1.2  1996/12/24  23:55:30  yawei
 * Function name change:
 *   Rasterfilter_Image ==> raster_deblur_filter
 *
 * Revision 1.1  1996/07/18  19:53:15  akjoele
 * Initial revision
 *
*
****************************************************************************/
#include <CVIPtoolkit.h>
#include <CVIPspfltr.h>

Image *raster_deblur_filter(Image *cvip_image){
    byte **image,**image_f;
    int x,y,i,bands,sum;
    unsigned int rows,cols,no_of_bands;

    no_of_bands = getNoOfBands_Image(cvip_image);
    rows = getNoOfRows_Image(cvip_image);
    cols = getNoOfCols_Image(cvip_image);

    if(cvip_image->bandP[0]->data_type != CVIP_BYTE ){
	if(cvip_image->bandP[0]->data_type != CVIP_FLOAT && 
				cast_Image(cvip_image,CVIP_FLOAT)){
	    fprintf(stderr,"Image is cast into float \n");
	}
	else if(cvip_image->bandP[0]->data_type != CVIP_FLOAT ){
	    fprintf(stderr,"cast_Image failed..\n");
	    return NULL;
	}
        for (bands=0;bands<no_of_bands;bands++){
	    image_f = getData_Image(cvip_image,bands);
	    for(y=0;y<rows-2;y+=2){	
		for (x=0;x<cols;x++){	
		    sum = image[y][x];
		    sum += image[y+2][x];
		    sum /= 2;
		    image_f[y+1][x] = sum;
		}
	    }		
	    for(x=0;x<cols-2;x+=2){	
		for (y=0;y<rows;y++){	
		    sum = image[y][x];
		    sum += image[y][x+2];
		    sum /= 2;
		    image_f[y][x+1] = sum;
		}
	    }		
	}
    }
    else{
        for (bands=0;bands<no_of_bands;bands++){
	    image = getData_Image(cvip_image,bands);
	    for(y=0;y<rows-2;y+=2){	
		for (x=0;x<cols;x++){	
		    sum = image[y][x];
		    sum += image[y+2][x];
		    sum /= 2;
		    image[y+1][x] = sum;
		}
	    }		
	    for(x=0;x<cols-2;x+=2){	
		for (y=0;y<rows;y++){	
		    sum = image[y][x];
		    sum += image[y][x+2];
		    sum /= 2;
		    image[y][x+1] = sum;
		}
	    }		
	}
    }

    return cvip_image;
}
