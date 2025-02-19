/******************************************************************************
    ======================================================================
    Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
    ======================================================================

                   Name: zonal.h
          Expanded Name: zonal coding head file

	    Description: some type definitions used in zonal coding.

     	  Related files: zonal.c 	

            Diagnostics: None

    Initial Coding Date: 5/10/96
Last Modifications Made: 10/3/96
             References: None

              Author(s): Wenxing Li


          Southern Illinois University @ Edwardsville

*******************************************************************************/

#if !defined(CVIPCOMPRESS_ZON)

 #define CVIPCOMPRESS_ZON


#ifdef __cplusplus
extern "C"{
#endif 


typedef struct 
{
 char 		 c;
 unsigned char * ptr;
 long          * pl; 
} MYSTRUCT;


typedef struct 
{
 long 		rows;
 long 		cols;
 float 	     *  rer;
 float       *  rei;
} remapSTRUCT;

typedef struct
{
 long           rows;
 long		cols;
 byte	     *  storer;
 byte	     *  storei;
} storeSTRUCT;

extern int zon_compress(Image * inputImage, char *filename, int block_size,
		int choice, int mask_type, float compress_ratio);
extern Image * zon_decompress(char * filename);

/* This function is reserved for backward compatibility, particular, for
 * compatibility with the cvip<->vip. New applications shouldn't use it.
 */
extern Image * zon_decompression(FILE * fp);

extern int zon2_compress(Image * inputImage, char *filename, int block_size,
			int choice, int mask_type, float compress_ratio);
extern Image * zon2_decompress(char * filename);

/* This function is reserved for backward compatibility, particular, for
 * compatibility with the cvip<->vip. New applications shouldn't use it.
 */
extern Image * zon2_decompression(FILE * fp);
#ifdef __cplusplus
}
#endif 

#endif
