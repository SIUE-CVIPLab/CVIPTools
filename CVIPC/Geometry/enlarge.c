/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: enlarge.c
*           Description: The file contains function to enlarge a image.
*			 The function call is enlarge.
*			 There are two function calls.
*			 enlarge_setup, enlarge.
*			 There are three arguments to enlarge.
*			     Image *cvipImage, contain input image data
*			     int row, the desired height of output image
*			     int col, the desired width of outptu image
*			 Arguments row and col must be greater than original
*			 ones, otherwise error will occur. 
*			 When error occurs, NULL pointer will be returned.
*
*			 enlarge_setup is a setup function as used in CVIPtools,
*			 it will asked the desired row and col, then it will
*			 call enlarge
*
*         Related Files: 
*   Initial Coding Date: Thu Jul 27 16:21:09 CDT 1995
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
 $Log: enlarge.c,v $
 Revision 1.6  1997/07/16 14:25:24  wzheng
 make it work for float data type imge.

 Revision 1.5  1997/03/08 01:01:47  yawei
 Name Changes:
 	BOOLEAN ==> CVIP_BOOLEAN
 	FALSE ==> CVIP_NO
 	TRUE ==> CVIP_YES
 	BYTE ==> CVIP_BYTE
 	SHORT ==> CVIP_SHORT
 	INTEGER ==> CVIP_INTEGER
 	FLOAT ==> CVIP_FLOAT
 	DOUBLE ==> CVIP_DOUBLE
 	TYPE ==> CVIP_TYPE

 Revision 1.4  1997/01/15 17:19:59  yawei
 Global Change:  IMAGE ==> Image

 * Revision 1.3  1996/12/31  00:40:00  yawei
 * Enlarge_Image ==> enlarge
 *
 * Revision 1.2  1995/07/27  21:30:51  kluo
 * add header
 *
 * Revision 1.1  1995/07/12  02:07:57  kluo
 * Initial revision
 *
****************************************************************************/

#include <CVIPimage.h>
#include <CVIPmatrix.h>
#include <CVIPgeometry.h>


Image * enlarge_setup(Image *cvipImage){
    int rows, cols;
    int method;
    printf("Enter the desired height of the resulting image:");
    scanf("%d",&rows);
    printf("Enter the desired width of the resulting image:");
    scanf("%d",&cols);
    return enlarge(cvipImage,rows,cols);
}

Image *enlarge(Image *cvipImage, int row, int col){
    Image *resultImage;
    int rows, cols, bands, no_of_bands,y,x;
    byte **imaget,**images;
    float **imageft,**imagefs;
    float ratio_x, ratio_y;
    int i,j;

    bands = getNoOfBands_Image(cvipImage);   
    rows =  getNoOfRows_Image(cvipImage);   
    cols =  getNoOfCols_Image(cvipImage);
    if(cols > col || rows > row){
	fprintf(stderr,"Incorrect Specification about Image size");
	return NULL;
    }
    ratio_x = (float)cols/col;
    ratio_y = (float)rows/row;

    if(cvipImage->bandP[0]->data_type != CVIP_BYTE){
        resultImage = new_Image(cvipImage->image_format,cvipImage->color_space,
			bands,row,col,CVIP_FLOAT,cvipImage->bandP[0]->data_format);
        if(resultImage == NULL){
	    fprintf(stderr,"Error in allocating new image");
	    return NULL;
        }
	if(cvipImage->image_ptr[0]->data_type != CVIP_FLOAT) {
	if(!cast_Image(cvipImage,CVIP_FLOAT)){
	     fprintf(stderr,"cast_Image failed");
	     return NULL;
	}}
	else{
	     fprintf(stderr,"Image is cast into float");
	}
    	for(no_of_bands=0;no_of_bands < bands;no_of_bands++){
	    imagefs = getData_Image(cvipImage,no_of_bands);
	    imageft = getData_Image(resultImage,no_of_bands);
            for(y=0;y<row;y++){
                for(x=0;x<col;x++){
		    imageft[y][x] = imagefs[(int)(y*ratio_y)][(int)(x*ratio_x)];
		}
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
            for(y=0;y<row;y++){
                for(x=0;x<col;x++){
		    imaget[y][x] = images[(int)(y*ratio_y)][(int)(x*ratio_x)];
		}
	    }
	}
    }
    delete_Image(cvipImage);
    return resultImage;
}

