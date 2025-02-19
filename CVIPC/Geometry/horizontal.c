/* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: horizontal.c
*           Description: The file contains function to horizontally flip an image.
*			 This function has two function calls 
*			 HorizontalFlip_setup, HorizontalFlip.
*			 There is one argument for HorizontalFlip function.
*			     Image *inputImage, contain input image data
*         Related Files: 
*   Initial Coding Date: Thu Nov 11 03.10.08 CDT 2000
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Raga
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 2000 SIUE - by Ragavendar Swamisai
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
****************************************************************************/

#include <CVIPimage.h>
#include <CVIPmatrix.h>
#include <CVIPgeometry.h>

Image *HorizontalFlip(Image *inputImage);


Image * HorizontalFlip_setup(Image *inputImage){
    return HorizontalFlip(inputImage);
}

Image *HorizontalFlip(Image *inputImage){
    Image *resultImage;
    byte  **image_array, **newImage_array;
    float **image_arrayF, **newImage_arrayF;
    int no_of_rows, no_of_cols, bands, no_of_bands,r,c;
    int temp,a,b;

    no_of_bands = getNoOfBands_Image(inputImage);   
    no_of_rows =  getNoOfRows_Image(inputImage);   
    no_of_cols =  getNoOfCols_Image(inputImage);
   
    
    a = abs((no_of_cols/2));
    
    if(inputImage->bandP[0]->data_type != CVIP_BYTE){
        resultImage = new_Image(inputImage->image_format,inputImage->color_space,
			no_of_bands,no_of_rows,no_of_cols,CVIP_FLOAT,inputImage->bandP[0]->data_format);
        if(resultImage == NULL){
	    fprintf(stderr,"Error in allocating new image");
	    return NULL;
        }
	if(inputImage->image_ptr[0]->data_type != CVIP_FLOAT) {
	if(!cast_Image(inputImage,CVIP_FLOAT)){
	     fprintf(stderr,"cast_Image failed");
	     return NULL;
	}}
	else{
	     fprintf(stderr,"Image is cast into float");
	}
    	for(bands=0;bands < no_of_bands;bands++){
	    image_arrayF = getData_Image(inputImage,bands);
	    newImage_arrayF = getData_Image(resultImage,bands);
            for(r=0;r <(no_of_rows-1);r++){
                for(c=0;c< a ;c++){
		    temp = image_arrayF[r][a -c];
		    newImage_arrayF[r][c] = image_arrayF[r][no_of_cols-1 - c];
		    newImage_arrayF[r][a+ c] = temp;
		}
	    }
	}
    }
    else{
        resultImage = new_Image(inputImage->image_format,inputImage->color_space,
			no_of_bands,no_of_rows,no_of_cols,CVIP_BYTE,inputImage->bandP[0]->data_format);
        if(resultImage == NULL){
	    fprintf(stderr,"Error in allocating new image");
	    return NULL;
        }
    	for(bands=0;bands < no_of_bands;bands++){
	    image_array = getData_Image(inputImage,bands);
	    newImage_array = getData_Image(resultImage,bands);
            for(r=0;r <(no_of_rows);r++){
                for(c=0;c< a ;c++){
		    temp = image_array[r][a - c];
		    newImage_array[r][c] = image_array[r][no_of_cols-1 - c];
		    newImage_array[r][a+ c] = temp ;
	    	}
	    }
	}
    }
    delete_Image(inputImage);
    return resultImage;
}

Image *VerticalFlip(Image *inputImage){
    Image *resultImage;
    byte  **image_array, **newImage_array;
    float **image_arrayF, **newImage_arrayF;
    int no_of_rows, no_of_cols, bands, no_of_bands,r,c;
    int temp,a,b;

    no_of_bands = getNoOfBands_Image(inputImage);   
    no_of_rows =  getNoOfRows_Image(inputImage);   
    no_of_cols =  getNoOfCols_Image(inputImage);
   
    
    a = abs((no_of_rows/2));
    
    if(inputImage->bandP[0]->data_type != CVIP_BYTE){
        resultImage = new_Image(inputImage->image_format,inputImage->color_space,
			no_of_bands,no_of_rows,no_of_cols,CVIP_FLOAT,inputImage->bandP[0]->data_format);
        if(resultImage == NULL){
	    fprintf(stderr,"Error in allocating new image");
	    return NULL;
        }
	if(inputImage->image_ptr[0]->data_type != CVIP_FLOAT) {
	if(!cast_Image(inputImage,CVIP_FLOAT)){
	     fprintf(stderr,"cast_Image failed");
	     return NULL;
	}}
	else{
	     fprintf(stderr,"Image is cast into float");
	}
    	for(bands=0;bands < no_of_bands;bands++){
	    image_arrayF = getData_Image(inputImage,bands);
	    newImage_arrayF = getData_Image(resultImage,bands);
            for(c=0;c <(no_of_cols-1);c++){
                for(r=0;r< a ;r++){
		    temp = image_arrayF[a-r][c];
		    newImage_arrayF[r][c] = image_arrayF[no_of_rows-1 - r][c];
		    newImage_arrayF[a+r][c] = temp;
		}
	    }
	}
    }
    else{
        resultImage = new_Image(inputImage->image_format,inputImage->color_space,
			no_of_bands,no_of_rows,no_of_cols,CVIP_BYTE,inputImage->bandP[0]->data_format);
        if(resultImage == NULL){
	    fprintf(stderr,"Error in allocating new image");
	    return NULL;
        }
    	for(bands=0;bands < no_of_bands;bands++){
	    image_array = getData_Image(inputImage,bands);
	    newImage_array = getData_Image(resultImage,bands);
            for(c=0;c<(no_of_cols);c++){
                for(r=0;r< a ;r++){
		    temp = image_array[a-r][c];
		    newImage_array[r][c] = image_array[no_of_rows-1 - r][c];
		    newImage_array[a+r][c] = temp ;
	    	}
	    }
	}
    }
    delete_Image(inputImage);
    return resultImage;
}
