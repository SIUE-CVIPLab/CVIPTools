/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: bitplane.h
*           Description: contains function prototypes, constants and types
*			 defined in bitplane.c
*         Related Files: bitplane.c
*   Initial Coding Date: Wed Dec 29 15:32:00 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Muthukumaran Sankarasubbu
*                        Southern Illinois University @ Edwardsville
*
*
*
****************************************************************************/
#if !defined( BITPLANE_RLC_DEFINED)
   #define BITPLANE_RLC_DEFINED
   #include "CVIPimage.h"
#ifdef __cplusplus
extern "C"{
#endif 

   extern int bit_compress(Image *inputImage, char *filename, byte sect);
   extern Image *bit_decompress(char *);

   /*extern Image *bitplane_sep(Image *input_Image, char *string);*/
   extern Image *bit_decompression(FILE *);
	/* This function is for backward compatibility, new programs shouldn't
	 * use it
	 */
#ifdef __cplusplus
}
#endif 

#endif
