#ifndef CVIPPNG_H
#define CVIPPNG_H

#include "CVIPtyp.h"
#include "CVIPimage.h"
#ifdef __cplusplus
extern "C"{
#endif 

extern Image* pngtocvip(char *filename);
extern int cviptopng(Image *cvipImage, char *filename);

#ifdef __cplusplus
}
#endif 

#endif