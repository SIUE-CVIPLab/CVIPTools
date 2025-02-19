/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: morph.h
*           Description: function prototypes, constants and type names for
*			 functions related to the morphological iterative
*			 function scheme.
*         Related Files: morph.c, morphSET.c, Imakefile
*   Initial Coding Date: Mon May 31 02:36:15 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Gregory Hance
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1993 SIUE - by Gregory Hance.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
* RCS (Revision Control System) Information
* ...Added automatically by RCS 
*
** $Log: CVIPmorph.h,v $
 * Revision 1.5  1997/03/08  00:46:17  yawei
 * Name Changes:
 * 	BOOLEAN ==> CVIP_BOOLEAN
 * 	FALSE ==> CVIP_YES
 * 	TRUE ==> CVIP_NO
 * 	BYTE ==> CVIP_BYTE
 * 	SHORT ==> CVIP_SHORT
 * 	INTEGER ==> CVIP_INTEGER
 * 	FLOAT ==> CVIP_FLOAT
 * 	DOUBLE ==> CVIP_DOUBLE
 * 	TYPE ==> CVIP_TYPE
 *
** Revision 1.4  1997/01/15 17:10:45  yawei
** Global Change:  IMAGE ==> Image
**
 * Revision 1.3  1996/12/18  03:49:14  yawei
 * Addd all morph function prototypes.
 *
 * Revision 1.2  1996/11/23  01:49:52  yawei
 * Added morpho function
 *
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
 * Revision 1.1  1993/06/01  16:47:00  hanceg
 * Initial revision
 *
*
****************************************************************************/
#if !defined( CVIPMORPH_DEFINED )

   #define CVIPMORPH_DEFINED
#ifdef __cplusplus
extern "C"{
#endif 


   #ifndef LINELENGTH
      #define LINELENGTH 80
   #endif

   #define FOUR 4
   #define EIGHT 8
   #define SIX_NWSE 6
   #define SIX_NESW 7

   typedef byte surround[3][3];

   static surround HEXLAT1 = {{0,0,0},
                              {0,0,0},
			      {0,0,0}};
   static surround HEXLAT2 = {{0,1,0},
                              {0,0,0},
			      {0,0,0}};
   static surround HEXLAT3 = {{1,1,0},
                              {0,0,0},
			      {0,0,0}};
   static surround HEXLAT4 = {{1,1,0},
                              {1,0,0},
			      {0,0,0}};
   static surround HEXLAT5 = {{1,1,0},
                              {1,0,0},
			      {0,1,0}};
   static surround HEXLAT6 = {{1,1,0},
                              {1,0,0},
         		      {0,1,1}};
   static surround HEXLAT7 = {{1,1,0},
                              {1,0,1},
         		      {0,1,1}};
   static surround HEXLAT8 = {{0,1,0},
                              {1,0,0},
         		      {0,0,1}};
   static surround HEXLAT9 = {{1,1,0},
                              {0,0,0},
	     		      {0,1,0}};
   static surround HEXLAT10 = {{1,1,0},
                               {0,0,0},
			       {0,0,1}};
   static surround HEXLAT11 = {{1,1,0},
                               {1,0,0},
			       {0,0,1}};
   static surround HEXLAT12 = {{0,1,0},
                               {1,0,0},
			       {0,0,0}};
   static surround HEXLAT13 = {{0,1,0},
                               {0,0,0},
			       {0,1,0}};
   static surround HEXLAT14 = {{1,1,0},
                               {0,0,0},
			       {0,1,1}};
			    
	/* utility functions */
   extern CVIP_BOOLEAN zero(CVIP_BOOLEAN a,CVIP_BOOLEAN b);
   extern CVIP_BOOLEAN not_b(CVIP_BOOLEAN a,CVIP_BOOLEAN b);
   extern CVIP_BOOLEAN and(CVIP_BOOLEAN a,CVIP_BOOLEAN b);
   extern CVIP_BOOLEAN or(CVIP_BOOLEAN a, CVIP_BOOLEAN b);
   extern CVIP_BOOLEAN not_and(CVIP_BOOLEAN a, CVIP_BOOLEAN b);
   extern CVIP_BOOLEAN or_not_and(CVIP_BOOLEAN a, CVIP_BOOLEAN b);
   extern CVIP_BOOLEAN xor(CVIP_BOOLEAN a, CVIP_BOOLEAN b);
   extern int *parse2ints(const char *strptr, const char *sepchars, int *n);
   extern MATRIX *array2MATRIX(const void *array, CVIP_TYPE atype,
			unsigned int arows, unsigned int acols);
   extern int euler_dif(const MATRIX *surrMATRIX, int connectedness);
	extern int disk_SE(Matrix **stru_elemP, CVIP_TYPE type, float bgnd,
		float fgnd, float d);
	extern int square_SE(Matrix  **stru_elemP, CVIP_TYPE type, int bgnd, int fgnd,
		int   block_size,     int   side_len);
	extern int rectangle_SE(Matrix  **stru_elemP, CVIP_TYPE    type, int   bgnd,
		int   fgnd, int   block_size,   int  height,  int  width);
	extern int cross_SE(Matrix  **stru_elemP, CVIP_TYPE    type, int bgnd, int fgnd,
	      int   block_size,   int  thickness,  int  width);

	extern Image * morpho(const  Image   *binImage, const char * surround_str,
			CVIP_BOOLEAN rotate, int boolFUNC, int connectedness, unsigned no_of_iter,
			int fields);
   extern Image *morphIterMod_Image(const Image *binImage,
			const MATRIX **surMATS, CVIP_BOOLEAN (*const boolFUNC)(CVIP_BOOLEAN a,CVIP_BOOLEAN b),
			int no_of_sur, int connectedness, int no_of_iter, int f);

   extern MATRIX *hexrotate(const MATRIX *surMATRIX, int connectedness,
			int degrees);

	extern Image *MorphClose_Image( Image *imageP, Matrix *kernelP,
			CVIP_BOOLEAN user_org, int x, int y);
	extern Image *MorphClose(Image *inputImage, int k_type, int ksize,
			int height, int width);

	extern Image *MorphOpen_Image( Image *imageP, Matrix *kernelP,
			CVIP_BOOLEAN user_org, int x, int y);
	extern Image *MorphOpen(Image *inputImage, int k_type, int ksize,
			int height, int width);

	extern Image *MorphDilate_Image( Image *imageP, Matrix *kernelP,
			CVIP_BOOLEAN user_org, int x, int y);
	extern Image* MorphDilate(Image *inputImage, int k_type, int ksize,
			int height, int width);

	extern Image *MorphErode_Image( Image *imageP, Matrix *kernelP,
			CVIP_BOOLEAN user_org, int x, int y);

	extern Image* MorphErode(Image *inputImage, int k_type, int ksize,
			int height, int width);

	/* setup function, not encouraged to use */
   extern Image *morph_setup(const Image *srcImage, const char *imgname);
   	extern Image *watershed(Image * inputImage); /* added by xchen */
	extern Image * watershed2(Image *inputImage, float threshold);
	extern Image * watershed3(Image *inputImage, float threshold);

#ifdef __cplusplus
}
#endif 
#endif /* CVIPMORPH_DEFINED */
