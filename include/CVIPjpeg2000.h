#ifndef CVIPJPEG2000_H
#define CVIPJPEG2000_H

#include "CVIPtyp.h"
#include "CVIPimage.h"
#ifdef __cplusplus
extern "C"{
#endif 


extern Image *jp2tocvip(char *filename);
extern int cviptojp2(Image *inputImage, char *filename, int rate, int quality, int numberoflayers, int block_size);
#ifdef __cplusplus
}
#endif 

#endif