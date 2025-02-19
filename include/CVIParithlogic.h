#ifndef _CVIP_ARITHLOGIC
#define _CVIP_ARITHLOGIC 
#ifdef __cplusplus
extern "C"{
#endif 

Image *multiply_Image(Image *inputImage1,Image *inputImage2);
Image *add_Image(Image *inputImage1,Image *inputImage2);
Image *subtract_Image(Image *inputImage1,Image *inputImage2);
Image *divide_Image(Image *inputImage1,Image *inputImage2,
	CVIP_BOOLEAN zero_zero);

Image *and_Image(Image *inputImage1,Image *inputImage2);
Image *or_Image(Image *inputImage1,Image *inputImage2);
Image *xor_Image(Image *inputImage1,Image *inputImage2);
Image *not_Image(Image *inputImage);

#ifdef __cplusplus
}
#endif 

#endif

