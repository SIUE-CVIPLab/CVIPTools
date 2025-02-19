/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: spatial_quant.c
*           Description: This file contains function to spatially quantize
*			 input image.
*			 It contains two functions
*			 SpatQuant_Setup and SpatQuant_Image
*			 There are four arguments to SpatQuant_Image.
*			    Image *cvipImage, contains input image data
*			    int row, desired height of output image
*			    int col, desired width of output image
*			    int methods, which method to use.
*				Currently there are three methods available.
*				method = 1, average  , represented by AVERAGE
*  				method = 2, median  ,  represented by MEDIAN
*   				method = 3, decimate, represented by DECIMATE
*			        AVERAGE, MEDIAN, DECIMATE are three constants
*				defined in CVIPquant.h
*			 The col, and row should be smaller than original ones,
*			 otherwise error will occurs.
*			 Whenever there is error, NULL pointer will be returned.
*			
*			 SpatQuant_Setup is a setup function call used in
*			  CVIPtools, it acts interactively.
*				
*         Related Files: CVIPquant.h
*   Initial Coding Date: Thu Jul 27 16:33:17 CDT 1995
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
* RCS (Revision Control System) Information
* ...Added automatically by RCS 
*
* $Log: spatial_quant.c,v $
* Revision 1.11  1997/07/11 20:44:56  smakam
* changed the spatial_quant function so that it works for float images
*
* Revision 1.10  1997/07/11 20:35:47  wzheng
* solve out of loop error
*
* Revision 1.9  1997/03/08 01:01:50  yawei
* Name Changes:
* 	BOOLEAN ==> CVIP_BOOLEAN
* 	FALSE ==> CVIP_NO
* 	TRUE ==> CVIP_YES
* 	BYTE ==> CVIP_BYTE
* 	SHORT ==> CVIP_SHORT
* 	INTEGER ==> CVIP_INTEGER
* 	FLOAT ==> CVIP_FLOAT
* 	DOUBLE ==> CVIP_DOUBLE
* 	TYPE ==> CVIP_TYPE
*
* Revision 1.8  1997/01/15 17:20:02  yawei
* Global Change:  IMAGE ==> Image
*
 * Revision 1.7  1996/12/17  22:07:11  yawei
 * Changed "image_geometry.h" to "CVIPgeometry.h"
 *
 * Revision 1.6  1996/12/17  21:49:22  yawei
 * Changed the header file "CVIPquant" to "image_geometry.h"
 *
 * Revision 1.5  1996/12/17  21:08:20  yawei
 * Changed :
 *   Spatial_QuantImage       ==> spatial_quant
 *
 * Revision 1.4  1995/07/27  21:43:17  kluo
 * add header
 *
 * Revision 1.3  1995/06/21  02:38:26  kluo
 * add more space allocate to array
 *
 * Revision 1.2  1995/06/21  02:27:05  kluo
 * change malloc for median
 *
 * Revision 1.1  1995/06/21  01:19:32  kluo
 * Initial revision
****************************************************************************/
#include <CVIPimage.h>
#include <CVIPmatrix.h>
#include "CVIPgeometry.h"

Image * spatial_quant_sep(Image *cvipImage){
    int rows, cols;
    int method;
    printf("There are three methods for Spatial Quantization");
    printf("\n\t\t1) Average ");
    printf("\n\t\t2) Median  ");
    printf("\n\t\t3) Decimate");
    printf("\n\tEnter the choice:");
    scanf("%d",&method);
    printf("Enter the desired height of the resulting image:");
    scanf("%d",&rows);
    printf("Enter the desired width of the resulting image:");
    scanf("%d",&cols);
    return spatial_quant(cvipImage,rows,cols,method);
}

/* method = 1, average   AVERAGE
   method = 2, median    MEDIAN
   method = 3, decimate  DECIMATE
*/
Image * spatial_quant(Image *cvipImage,int row,int col,int method){
    Image *resultImage;
    int rows, cols, bands, no_of_bands,y,x;
    byte **imaget,**images;
    float **imageft,**imagefs;
    float sum,*array;
    int total;
    float ratio_x, ratio_y;
    int i,j;

    if(method <1 || method > 3){
 	fprintf(stderr,"Wrong method selection");
	return NULL;
    }

    bands = getNoOfBands_Image(cvipImage);   
    rows =  getNoOfRows_Image(cvipImage);   
    cols =  getNoOfCols_Image(cvipImage);
    if(cols < col || rows < row){
	fprintf(stderr,"Incorrect Specification about Image size");
	return NULL;
    }
    ratio_x = (float)cols/col;
    ratio_y = (float)rows/row;
    array = (float *)malloc((int)4*(ratio_x+1)*(ratio_y+1)*sizeof(float));
    if(cvipImage->bandP[0]->data_type != CVIP_BYTE){
        resultImage = new_Image(cvipImage->image_format,cvipImage->color_space,
			bands,row,col,CVIP_FLOAT,cvipImage->bandP[0]->data_format);
        if(resultImage == NULL){
	    fprintf(stderr,"Error in allocating new image");
	    return NULL;
        }
    	if(cvipImage->bandP[0]->data_type != CVIP_FLOAT){
		if(!cast_Image(cvipImage,CVIP_FLOAT)){
	     	fprintf(stderr,"cast_Image failed");
	     	return NULL;
		}
		else{
	     	fprintf(stderr,"Image is cast into float");
		}
	}
    	for(no_of_bands=0;no_of_bands < bands;no_of_bands++){
	    imagefs = getData_Image(cvipImage,no_of_bands);
	    imageft = getData_Image(resultImage,no_of_bands);
	    switch(method){
		case 1: /*average*/
	            for(y=0;y<row;y++){
	                for(x=0;x<col;x++){
			    sum = 0.0;
			    total = 0;
			    for(i=y*ratio_y;i<(y+1)*ratio_y && i<rows;i++){
				for(j=x*ratio_x;j<(x+1)*ratio_x && j<cols;j++){
				    sum = sum + imagefs[i][j];
				    total++;
				}
			    }
			    imageft[y][x] = sum /total;
			}
		    }
		    break;
		case 2:/*median*/    
	            for(y=0;y<row;y++){
	                for(x=0;x<col;x++){
			    total = 0;
			    for(i=y*ratio_y;i<(y+1)*ratio_y && i<rows;i++){
				for(j=x*ratio_x;j<(x+1)*ratio_x && j<cols;j++){
				    array[total++]= imagefs[i][j];
				}
			    }
			    for(i=0;i<total;i++){
				for(j=i;j<total;j++){
				    if(array[j] < array[i]){
					sum = array[j];
					array[j] = array[i];
					array[i] = sum;
				    }
				}
			    }
			    imageft[y][x] = array[(int)total/2];
			}
		    }
		    break;
		case 3:/*decimate*/
	            for(y=0;y<row;y++){
	                for(x=0;x<col;x++){
			    i = y * ratio_y;
			    j = x * ratio_x;
			    imageft[y][x] = imagefs[i][j];
			}
		    }
		    break;
		default:;
	    }
	}
    }
    else{
        resultImage = new_Image(cvipImage->image_format,cvipImage->color_space,
			bands,row,col,CVIP_BYTE,cvipImage->bandP[0]->data_format);
        if(resultImage == NULL){
	    fprintf(stderr,"Error in allocating new image");
	    return NULL;
        }
    	for(no_of_bands=0;no_of_bands < bands;no_of_bands++){
	    images = getData_Image(cvipImage,no_of_bands);
	    imaget = getData_Image(resultImage,no_of_bands);
	    switch(method){
		case 1: /*average*/
	            for(y=0;y<row;y++){
	                for(x=0;x<col;x++){
			    sum = 0.0;
			    total = 0;
			    for(i=y*ratio_y;i<(y+1)*ratio_y && i<rows;i++){
				for(j=x*ratio_x;j<(x+1)*ratio_x && j < cols;j++){
				    sum += images[i][j];
				    total++;
				}
			    }
			    imaget[y][x] = sum /total;
			}
		    }
		    break;
		case 2:/*median*/    
	            for(y=0;y<row;y++){
	                for(x=0;x<col;x++){
			    total = 0;
			    for(i=y*ratio_y;i<(y+1)*ratio_y;i++){
				for(j=x*ratio_x;j<(x+1)*ratio_x;j++){
				    array[total++]= images[i][j];
				}
			    }
			    for(i=0;i<total;i++){
				for(j=i;j<total;j++){
				    if(array[j] < array[i]){
					sum = array[j];
					array[j] = array[i];
					array[i] = sum;
				    }
				}
			    }
			    imaget[y][x] = array[(int)total/2];
			}
		    }
		    break;
		case 3:/*decimate*/
	            for(y=0;y<row;y++){
	                for(x=0;x<col;x++){
			    i = y * ratio_y;
			    j = x * ratio_x;
			    imaget[y][x] = images[i][j];
			}
		    }
		    break;
		default:;
	    }
	}
    }
    free(array);
    delete_Image(cvipImage);
    return resultImage;
}
