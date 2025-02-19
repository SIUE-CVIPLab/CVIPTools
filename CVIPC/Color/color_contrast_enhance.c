/***************************************************************************
* =========================================================================
*
*   Computer Vision and Image Processing Lab - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: color_contrast_enhance.c 
*           Description: This function improves the color of the image 
*   Initial Coding Date: March 20, 2010
*           Portability: Standard (ANSI) C
*             Credit(s): Mounika Mamidi
*                        Southern Illinois University at Edwardsville
*
** Copyright (c) 1995, 1996, SIUE - Scott Umbaugh, Mounika Mamidi
****************************************************************************/


/*
** include header files
*/

#include "CVIPdef.h"
#include "CVIPcomplex.h"
#include "CVIPtoolkit.h"
#include "CVIPcolor.h"
#include <math.h>
#include "CVIPconvert.h"
#include "CVIPimage.h"
#include "CVIPtyp.h"
#include "histogram.h"
#include "CVIPhisto.h"
#include <CVIPband.h>
#include "CVIPcolor.h"



Image *color_contrast_enhance(Image *inputImage, int low_limit,int high_limit, float low_clip, float high_clip)
{
	Image *HueBand, *SaturationBand, *LightnessBand, *temp, *midImage;
	Image *Bands[3];
	COLOR_FORMAT newformat=HSL;
	float norm[3]={255.0,255.0,255.0};
	float ref[3]={1.0,1.0,1.0};
	int j;
	
	//remap the image to byte format
	temp=(Image *)remap_Image((const Image *)inputImage,CVIP_BYTE,0,255);
//	delete_Image(inputImage);
	inputImage=temp;

	//transform RGB color space to HSL color space
	inputImage=colorxform(inputImage, HSL,norm,ref ,1);
	midImage = duplicate_Image(inputImage);

	//extracting hue band
	HueBand=extract_band(midImage, 1);
	midImage = duplicate_Image(inputImage);

	//extracting saturation band
	SaturationBand=extract_band(midImage, 2);
	temp=(Image *)remap_Image((const Image *)SaturationBand,CVIP_BYTE,0,255);
//	delete_Image(SaturationBand);
	SaturationBand=temp;

	//apply histogram equalization on saturation band
	SaturationBand= histeq(SaturationBand,0);
	midImage = duplicate_Image(inputImage);

	//extract lightness band
	LightnessBand=extract_band(midImage, 3);	 
	temp=(Image *)remap_Image((const Image *)LightnessBand,CVIP_FLOAT,0,255);
//	delete_Image(LightnessBand);
	LightnessBand=temp;

	//apply histogram stretch on lightness band
	LightnessBand=hist_stretch(LightnessBand, low_limit, high_limit,low_clip, high_clip);
	cast_Image(LightnessBand,CVIP_FLOAT);

	//assemble all three processed bands
	Bands[0]=HueBand;
	Bands[1]=SaturationBand;
	Bands[2]=LightnessBand;
	inputImage = assemble_bands(Bands, 3);

	temp=(Image *)remap_Image((const Image *)inputImage,CVIP_BYTE,0,255);
//	delete_Image(inputImage);
	inputImage=temp;

	//apply inverse transform on the image to convert it to RGB color space
	inputImage=colorxform(inputImage, HSL,norm, ref,-1);

	return inputImage;
	
	}