/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: CVIPimage.h
*           Description: contains function prototypes, type names, constants,
*			 etc. related to libdataserv (Data Services Toolkit.)
*         Related Files: Imakefile, image.c
*   Initial Coding Date: 2/29/92
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
** $Log: CVIPimage.h,v $
** Revision 1.40  2001/06/14 00:28:22  ycheng
** PS IMAGE_FORMAT should be added at the end.
**
** Revision 1.39  2001/05/22 20:13:31  rswamis
** Added PostScript Format to the existing image Formats
**
** Revision 1.38  2001/05/02 14:55:33  zlin
** change Trans_compr to Trcm and add TRCM to IMAGE_FORMAT
**
** Revision 1.37  2001/02/26 00:05:11  ycheng
** add CMPR_FORMAT type Trans_compr
**
** Revision 1.36  1999/11/20 23:51:43  ycheng
** In the 'type enum{} CMPR_FORMAT', Xvq should be added in front of the TOP.
**
** Revision 1.35  1998/12/02 04:56:28  lguo
** WVQ added to IMAGE_FORMAT
**
** Revision 1.34  1998/12/02 03:30:44  lguo
** added Wvq to CMPR_FORMAT
**
** Revision 1.33  1998/03/24 03:16:11  wzheng
** modify the sequency of VQ Vq
**
** Revision 1.32  1998/03/13 01:30:01  wzheng
** add VQ in IMAGE_FORMAT
**
** Revision 1.31  1998/03/12 03:12:47  wzheng
** add CMPR_FORMAT "Vq"
**
** Revision 1.30  1998/03/10 04:37:11  smakam
** made changes corresponding to including new compression method fractal
**
** Revision 1.29  1997/10/31 00:08:10  wzheng
** add Wvq as a new compression method
**
** Revision 1.28  1997/05/02 22:46:36  yawei
** added getDataRange_Image
**
** Revision 1.27  1997/04/29 00:11:08  yawei
** added jpg
**
** Revision 1.26  1997/04/15 00:20:54  yawei
** added JPG
**
** Revision 1.25  1997/03/08 02:04:55  yawei
** update TYPE update
**
** Revision 1.24  1997/03/08 00:47:55  yawei
** Name Changes:
** 	BOOLEAN ==> CVIP_BOOLEAN
** 	FALSE ==> CVIP_YES
** 	TRUE ==> CVIP_NO
** 	BYTE ==> CVIP_BYTE
** 	SHORT ==> CVIP_SHORT
** 	INTEGER ==> CVIP_INTEGER
** 	FLOAT ==> CVIP_FLOAT
** 	DOUBLE ==> CVIP_DOUBLE
** 	TYPE ==> CVIP_TYPE
**
** Revision 1.23  1997/01/16 20:57:14  yawei
** Global Change:  Image_FORMAT ==> IMAGE_FORMAT
**
 * Revision 1.22  1997/01/15  17:24:08  yawei
 * Image ==> IMAGE in one place
 *
 * Revision 1.21  1997/01/15  17:12:46  yawei
 * Global Change:  IMAGE ==> Image
 *
 * Revision 1.20  1997/01/05  20:23:09  yawei
 * moved setDisplay_Image, getDisplay_Image, and display_Image to CVIPview.h
 *
 * Revision 1.19  1996/12/20  21:22:12  yawei
 * Put "CVIPview.h" to the end
 *
 * Revision 1.18  1996/12/20  19:19:43  yawei
 * included "CVIPview.h"
 *
 * Revision 1.17  1996/12/14  03:38:17  yawei
 * added iamge type definition ZON2.
 *
 * Revision 1.16  1996/12/13  16:30:03  yawei
 * removed data_format and data_type, defined somewhere else already.
 *
 * Revision 1.15  1996/12/13  16:17:00  yawei
 * Added DATA_TYPE and DATA_FORMAT type definitions.
 *
 * Revision 1.14  1996/12/09  20:27:12  akjoele
 * removed snr() and rms_error(), since these have moved to
 * libcompress
 *
 * Revision 1.13  1996/12/05  15:45:33  akjoele
 * Added prototypes for getSize_Hist() and getAllSize_Hist().
 *
 * Revision 1.12  1996/12/04  20:34:33  yawei
 * Changed LZW to ZVL
 *
 * Revision 1.11  1996/11/27  19:37:24  yawei
 * Changed COMR_FORMAT to CMPR_FORMAT
 *
 * Revision 1.10  1996/11/26  19:33:07  akjoele
 * Added prototype defifnitions for
 * snr() and rms_error()
 *
 * Revision 1.9  1996/11/20  14:38:31  yawei
 * Added CMPR_FORMAT enumeration type.
 *
 * Revision 1.8  1996/09/06  05:23:53  wli
 * add ZON into IMAGE_FORMAT
 *
 * Revision 1.7  1996/08/12  16:18:33  akjoele
 * Added prototype declarations for
 * assemble_bands() and
 * extract_band()
 *
 * Revision 1.6  1996/07/22  16:29:45  akjoele
 * *** empty log message ***
 *
 * Revision 1.5  1996/02/02  17:10:38  akjoele
 * Added SAFVR to the IMAGE_FORMAT list, so we can load up these images.
 *
 * Revision 1.4  1995/11/02  01:30:31  kluo
 * change DPCM to DPC
 *
 * Revision 1.3  1995/11/02  01:22:21  kluo
 * add DPCM
 *
 * Revision 1.2  1995/10/17  16:05:41  kluo
 * add BTC header.
 *
 * Revision 1.1  1995/06/16  02:58:51  luok
 * Initial revision
 *
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
*
****************************************************************************/

#if !defined( CVIPImage_DEFINED )

   #define CVIPImage_DEFINED


   #if !defined( CVIPMATRIX_DEFINED )
      #include "CVIPmatrix.h"
   #endif

   #if !defined( CVIPBAND_DEFINED )
      #include "CVIPband.h"
   #endif

   #if !defined( CVIPHISTORY_DEFINED )
      #include "CVIPhistory.h"
   #endif

#ifdef __cplusplus
extern "C"{
#endif 

   typedef enum {BINARY, GRAY_SCALE, RGB, HSL, HSV, SCT, CCT, LUV, LAB, XYZ} COLOR_FORMAT;


   typedef enum {PBM, PGM, PPM, EPS, TIF, GIF, RAS, ITX,IRIS, CCC, BIN, VIP, GLR, BTC, BRC, HUF, ZVL, ARITH, BTC2, BTC3, DPC, ZON, ZON2, SAFVR, JPG, WVQ, FRA, VQ, XVQ, TRCM, PS, BMP, JP2, PNG} IMAGE_FORMAT;

	typedef enum {Btc, Btc2, Btc3, Dpcm, Zvl, Glr, Brc, Huf, Zon, Zon2, Jpg, Wvq, Fra, Vq, Xvq, Trcm, TOP} \
				CMPR_FORMAT;

typedef struct {
      IMAGE_FORMAT image_format;
      COLOR_FORMAT color_space;
      int bands;
      MATRIX **image_ptr;
      HISTORY story;
   } IMAGE;

   #define bandP image_ptr

   typedef IMAGE Image;

   /* macros used to extract information from the Image structure */
   #define getNoOfRows_Image(image) ((image)->bandP[0]->rows)
   #define getNoOfCols_Image(image) ((image)->bandP[0]->cols)
   #define getDataType_Image(image) ((image)->bandP[0]->data_type)

	float * getDataRange_Image( Image *imageP);

   #define getDataFormat_Image(image) ((image)->bandP[0]->data_format)
   #define getFileFormat_Image(image) ((image)->image_format)
   #define getColorSpace_Image(image) ((image)->color_space)
   #define getNoOfBands_Image(image) ((image)->bands)
   #define setNoOfBands_Image(image,bands) \
   (getNoOfBands_Image(image) = (bands))
   #define setFileFormat_Image(image,format) \
   (getFileFormat_Image(image) = (format))
   #define setColorSpace_Image(image,space) \
   (getColorSpace_Image(image) = (space))

   #define getBand_Image(image,band_no) ((image)->bandP[band_no])
   #define setBand_Image(image,band,band_no) ((image)->bandP[band_no]=(band)) 

   #define getRealData_Image(image,band_no) \
   (getRealData_Matrix(getBand_Image(image,band_no)))
   #define getData_Image(image,band_no) getRealData_Image(image,band_no)
   #define getImagData_Image(image,band_no) \
   (getImagData_Matrix(getBand_Image(image,band_no)))

   #define getRealRow_Image(image,row,band_no) \
   (getRealRow_Matrix(getBand_Image(image,band_no),row))
   #define getRow_Image(image,row,band_no) getRealRow_Image(image,row,band_no)
   #define getImagRow_Image(image,row,band_no) \
   (getImagRow_Matrix(getBand_Image(image,band_no),row))

   #define getRealPixel_Image(image,type,x,y,band_no) \
   (getRealVal_Matrix(getBand_Image(image,band_no),type,x,y))
   #define getPixel_Image(image,type,x,y,band_no) \
   getRealPixel_Image(image,type,x,y,band_no)
   #define setRealPixel_Image(image,type,x,y,band_no,pixel) \
   (getPixel_Image(image,type,x,y,band_no) = (pixel))
   #define setPixel_Image(image,type,x,y,band_no,pixel) \
   setRealPixel_Image(image,type,x,y,band_no,pixel)
   #define getImagPixel_Image(image,type,x,y,band_no) \
   (getImagVal_Matrix(getBand_Image(image,band_no),type,x,y))
   #define setImagPixel_Image(image,type,x,y,band_no,pixel) \
   (getImagPixel_Image(image,type,x,y,band_no) = (pixel))


   #define DEFAULT 0

  /* 
   * macros for backwards compatibity with old function names
   */
   #define image_allocate(a,b,c,d,e,f,g) new_Image(a,b,c,d,e,f,g)
   #define cvip_display(a,b) display_Image(a,b)
   #define image_free(a) delete_Image(a)
   #define image_duplicate(a) duplicate_Image(a)
   #define castImage(a,b) cast_Image(a,b)
   #define unloadImage(a,b,c,d,e,f) unload_Image(a,b,c,d,e,f)
   #define uploadImage(a,b,c,d,e,f,g) upload_Image(a,b,c,d,e,f,g)
   #define Imagedump(a) dump_Image(a)
   #define makecomplexImage(a) makeComplex_Image(a)
   #define makerealImage(a)  makeReal_Image(a)

  /*
   * New function names with class extension added
   */
   extern Image *new_Image(IMAGE_FORMAT image_format, COLOR_FORMAT color_space, int bands, int heigth, int width, CVIP_TYPE data_type,FORMAT data_format);
   extern void delete_Image(Image *A);
   extern Image *duplicate_Image(const Image *inImage);
   extern int cast_Image(Image *srcImage, CVIP_TYPE dtype);
   extern void *unload_Image(Image *srcImage, DATAFORM df, CVIP_TYPE type, unsigned int *bands, unsigned int *rows, unsigned int *cols);
   extern void upload_Image(Image *srcImage, void *dataP, DATAFORM df,
	CVIP_TYPE type, unsigned int bands, unsigned int rows, unsigned int cols);
   extern CVIP_BOOLEAN dump_Image(Image *srcImage);
   extern void makeComplex_Image(Image *srcImage);
   extern void makeReal_Image(Image *srcImage);
   extern void getBandVector_Image(Image *imageP, void *vecP);
   extern void selectCopy_Image(Image *image_aP, Image *image_bP, void *selectP, unsigned no_of_sel);
   extern int copy_Image(const Image *srcP, Image *desP);
   extern Image *clone_Image(const Image *imgP, CVIP_TYPE dt);
   extern int findMaxVal_Image(const Image *imgP, double *maxvec);
   extern int findMinVal_Image(const Image *imgP, double *minvec);
   extern int abs_Image(Image *imgP);
   extern int cropBands_Image( Image *imgP, int crop_bands );
   extern Image *extract_band(Image *inImg, int bandno);
   extern Image *assemble_bands(Image **inImgs, int noimgs);
   extern int chk_bin(Image* image);

   /* old functions that i'm trying to widdle out */
   extern void *refBAND( Image *srcImage, DATAFORM df, int band_no );


	/*
	** History Stuff
	*/

	extern void history_add(Image *image, HISTORY);
	extern void history_delete_program(Image *image, PROGRAMS program);
   	extern CVIP_BOOLEAN history_check(PROGRAMS program, Image *image);
   	extern CVIP_BOOLEAN history_check1(Image *image);
   	extern HISTORY history_get(Image *image, PROGRAMS program);
   	extern HISTORY history_get1(Image *image);
        extern void history_show(Image *image);
	extern void history_copy(Image *from, Image *to);
	extern PROGRAMS getlast_Hist(Image *in, PROGRAMS *progs, unsigned n);
        extern int getSize_Hist(HISTORY stuff);
        extern int getAllSize_Hist(Image *image);

   #include "CVIPview.h"
#ifdef __cplusplus
}
#endif 

#endif
