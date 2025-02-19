/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: huffman.h
*           Description: contains function prototypes, constants and types
*			 defined in grey.c
*         Related Files: huffman.c
*   Initial Coding Date: Wed Dec 29 15:30:00 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Muthukumaran Sankarasubbu
*                        Southern Illinois University @ Edwardsville
*
*
*
****************************************************************************/
#if !defined( HUFFMAN_DEFINED)
   #define HUFFMAN_DEFINED

   #include "CVIPimage.h"
#ifdef __cplusplus
extern "C"{
#endif 


	extern int huf_compress(Image *inputImage, char *filename);
	extern Image *huf_decompress(char *filename);

	/* this following function is for backward compatibility, new programs
	 * should always use the newer ones provided above
	 */
   extern Image *huf_decompression(FILE *file_in);
#ifdef __cplusplus
}
#endif 
#endif /* HUFFMAN_DEFINED */
