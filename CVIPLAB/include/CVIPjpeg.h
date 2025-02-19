#ifndef CVIPJPEG_H
#define CVIPJPEG_H

#include "CVIPtyp.h"
#include "CVIPimage.h"
#ifdef __cplusplus
extern "C"{
#endif 


extern int cviptojpg(Image *cvipImage, char *filename, int quality, 
	CVIP_BOOLEAN grayscale, CVIP_BOOLEAN optimize, int smooth, 
	CVIP_BOOLEAN verbose, char *qtablesFile);

extern Image *jpgtocvip(char *filename, int colors, CVIP_BOOLEAN blocksmooth, 
	CVIP_BOOLEAN grayscale, CVIP_BOOLEAN nodither, CVIP_BOOLEAN verbose);
#ifdef __cplusplus
}
#endif 

#endif
