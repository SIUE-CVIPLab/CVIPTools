/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: btc.h
*           Description: contains function prototypes, constants and types
*			 defined in threshold.c
*         Related Files: threshold.c
*   Initial Coding Date: Tue Apr 27 21:49:42 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Gregory Hance
*                        Southern Illinois University @ Edwardsville
*
*
*
****************************************************************************/
#if !defined( BTC_COMPRESSION_DEFINED)
   #define BTC_COMPRESSION_DEFINED

   #include "CVIPimage.h"
   #include "CVIPdef.h"
#ifdef __cplusplus
extern "C"{
#endif 


   extern Image *btc(Image *inputImage);
   extern int btc_compress(Image *inputImage, char *filename, int blocksize);
   extern Image *btc_decompress(char *filename);

	/* this following function is for backward compatibility, new programs 
	 * should always use the newer ones provided above
	 */
   extern Image *btc_decompression(FILE *dec);
	
	extern int btc2_compress(Image *inputImage, char *filename, int blocksize);
	extern Image* btc2_decompress(char *filename);
	/* this following function is for backward compatibility, new programs 
	 * should always use the newer ones provided above
	 */
   extern Image *btc2_decompression(FILE *fp);

	extern int btc3_compress(Image *inputImage, char *filename, int blocksize);
	extern Image *btc3_decompress(char *filename);

	/* this following function is for backward compatibility, new programs 
	 * should always use the newer ones provided above
	 */
   extern Image * btc3_decompression(FILE *fp);

#ifdef __cplusplus
}
#endif 

#endif
