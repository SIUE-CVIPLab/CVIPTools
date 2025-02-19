/****************************************************************************
*
*Author: Kun Luo
* $Log: gray_quant.c,v $
* Revision 1.6  1997/03/08 00:44:52  yawei
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
* Revision 1.5  1997/01/15 17:09:15  yawei
* Global Change:  IMAGE ==> Image
*
 * Revision 1.4  1996/12/20  22:49:33  yawei
 * Changed function name:
 *   Gray_QuantImage ==> gray_quant_segment
 *
 * Revision 1.3  1996/12/17  21:47:44  yawei
 * Changed the header file "CVIPquant" to "image_geometry.h"
 *
 * Revision 1.2  1995/09/20  00:07:32  kluo
 * change so that error message will not come up infinitely
 *
 * Revision 1.1  1995/07/06  23:08:43  kluo
 * Initial revision
 *
 * Revision 1.2  1995/06/26  14:42:47  kluo
 * change the prompt.
 *
 * Revision 1.1  1995/06/21  01:19:56  kluo
 * Initial revision
 *
*****************************************************************************/
#include <CVIPimage.h>
#include "CVIPtoolkit.h"
#include <CVIPmatrix.h>
#include "CVIPsegment.h" 
#include "CVIPmap.h"

Image* gray_quant_setup(Image *cvipImage){
    int num_bit;
    while(1){
	fflush(stdin);
	printf("Enter the maximum number of gray level(2,4,8,16,32,64,128):");
    	scanf("%d",&num_bit);
	if(num_bit == 2 ||num_bit == 4 || num_bit == 8|| num_bit == 16
		|| num_bit == 32|| num_bit == 64|| num_bit == 128)
	    break;
	else
	    printf("Wrong Selection\n");
    }
    return gray_quant_segment(cvipImage,num_bit);
}

Image * gray_quant_segment(Image *cvipImage, int num_bits){
    int mask;
    int rows, cols, bands, no_of_bands,y,x;
    byte **image;

    bands = getNoOfBands_Image(cvipImage);   
    rows =  getNoOfRows_Image(cvipImage);   
    cols =  getNoOfCols_Image(cvipImage);
    
    if(num_bits != 2 && num_bits != 4 && num_bits != 8 && num_bits != 16
	    && num_bits != 32 && num_bits != 64 && num_bits != 128){
	fprintf(stderr,"Wrong number of gray level");
	return NULL;
    }
    
    if(cvipImage->bandP[0]->data_type != CVIP_BYTE){
	Image *temp;
	temp = (Image*)remap_Image(cvipImage,CVIP_BYTE,0,255);
	if(!temp){
	     fprintf(stderr,"remap_Image failed");
	     return NULL;
	}
	else{
	     delete_Image(cvipImage);
	     cvipImage = temp;
	     fprintf(stderr,"Image is remap into byte");
	}
    } 
    mask = 256;
    mask /= num_bits;
    mask -= 1;
    mask ^= 0xff;
 
    for(no_of_bands=0;no_of_bands < bands;no_of_bands++){
	image = getData_Image(cvipImage,no_of_bands);
	for(y=0;y<rows;y++){
	    for(x=0;x<cols;x++){
		image[y][x] &= mask;
	    }
	}
    }
    return cvipImage;
}
