#if !defined(CVIPCOMPRESS_DEFINED)

 #define CVIPCOMPRESS_DEFINED


 #include "block_trunc_coding.h"
 #include "huffman.h"
 #include "fractal.h"
 #include "grey_RLC.h"
 #include "bitplane_RLC.h"
 #include "zonal.h"
 #include "vector_quant.h"

#ifdef __cplusplus
extern "C"{
#endif 

/*----------------------- jpeg & jpeg2000-----------------------*/
extern int jpg_compress(Image *cvipImage, char *filename, int quality, CVIP_BOOLEAN grayscale, CVIP_BOOLEAN optimize, int smooth, CVIP_BOOLEAN verbose, char *qtablesFile);

extern Image *jpg_decompress(char *filename, int colors, CVIP_BOOLEAN blocksmooth, CVIP_BOOLEAN grayscale, CVIP_BOOLEAN nodither, CVIP_BOOLEAN verbose);

extern Image *jpg_decompression(FILE *fp, int colors, CVIP_BOOLEAN blocksmooth, CVIP_BOOLEAN grayscale, CVIP_BOOLEAN nodither, CVIP_BOOLEAN verbose);

extern Image *jp2_decoder(char *filename);

extern int jp2_encoder(Image *cvipImage, char *outputFileName, int rate, int quality, int numberoflayers, int block_size);

/*----------------------- dpc ----------------------------------*/
 extern int dpc_compress(Image *inputImage, char *filename,float ratio,
	 int bit_length,int clipping, int direction, int origin, float deviation);
 extern Image *dpc_decompress(char *filename);

 /* This function is an interactive driver for dpc_compress to get the 
  * parameters. Applications oriented to cviptcl/wish shouldn't use it.
  */
 extern Image* dpc_compression(Image *inputImage);
 /* this following function is for backward compatibility, new programs
  * should always use the newer ones provided above
  */
 extern Image *dpc_decompression(FILE *fptr);

/*----------------------- zvl ----------------------------------*/
 extern int zvl_compress(Image *inputImage, char *filename);
 extern Image *zvl_decompress(char *filename);

 /* this following function is for backward compatibility, new programs
  * should always use the newer ones provided above
  */
 extern Image *zvl_decompression(FILE *input);
 extern float *rms_error(Image *, Image *);
 extern float *snr(Image *, Image *);
#ifdef __cplusplus
}
#endif 

#endif /* CVIPCOMPRESS_DEFINED */
