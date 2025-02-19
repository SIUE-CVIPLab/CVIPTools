/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: watershed.h
*           Description: 
*         Related Files: 
*   Initial Coding Date: 
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Xiaohe Chen
****************************************************************************/

#ifndef __WATERSHED
#define __WATERSHED
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CVIPtools.h"
#include "CVIPimage.h"
#include "CVIPdef.h"
#include "stdio.h"
#include "CVIPtyp.h"
#define WATERSHED_PLATEAU 256

#ifdef __cplusplus
extern "C"{
#endif 
extern Image *luminance_Image(Image *inputImage);
extern Image * labeling_Image(Image *inputImage);
extern Image *watershed_segment(Image *inputImage, float threshold, CVIP_BOOLEAN choice);
//Image * watershed2(Image *inputImage);
#ifdef __cplusplus
}
#endif 
#endif
