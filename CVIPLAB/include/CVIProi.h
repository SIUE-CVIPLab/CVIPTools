/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: CVIPROI.h
*           Description: 
*         Related Files: 
*   Initial Coding Date: Tue Jul 20 17:40:10 CDT 1993
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
** $Log: CVIProi.h,v $
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
*
****************************************************************************/
#if !defined( CVIPROI_DEFINED )

   #define CVIPROI_DEFINED

   #include "CVIPimage.h"

   struct ROIType {

      unsigned x;     /* Horizontal offset of ROI from pixel location (0,0) */
      unsigned y;     /* Vertical offset of ROI from pixel location (0,0) */
      unsigned dx;    /* Horizontal size of the ROI */
      unsigned dy;    /* Vertical size of the ROI */

      Image *dataP;
   };

   typedef struct ROIType ROI;

   static int DataSize[5] = {sizeof(byte), sizeof(short), sizeof(int), sizeof(float), sizeof(double)};


   /*
    * ROI stuff
    */

   /* Function Prototypes*/
   extern ROI *new_ROI(void);
   extern void delete_ROI(ROI *roiP);
   extern void asgnImage_ROI(ROI *roiP, Image *imageP, unsigned x, unsigned y,  
   unsigned dx, unsigned dy);
   #define asgnFullImage_ROI(roiP,imageP) \
   asgnImage_ROI(roiP,imageP,0,0,getNoOfCols_Image(imageP),\
   getNoOfRows_Image(imageP))

   /* Macros */

   #define getHorOffset_ROI(roiP) ((roiP)->x)
   #define getVerOffset_ROI(roiP) ((roiP)->y)
   #define getHorSize_ROI(roiP) ((roiP)->dx)
   #define getVerSize_ROI(roiP) ((roiP)->dy)
   #define getNoOfRows_ROI(roiP) getVerSize_ROI(roiP)
   #define getNoOfCols_ROI(roiP) getHorSize_ROI(roiP)
   #define getNoOfBands_ROI(roiP) (((roiP)->dataP)->bands)
   #define getDataFormat_ROI(roiP) ((*((roiP)->dataP)->bandP)->data_format)
   #define getDataType_ROI(roiP) ((*((roiP)->dataP)->bandP)->data_type)

   #define getRealRow_ROI(roiP,y,band_no) \
   ((byte *)getRealRow_Image((roiP)->dataP,(y)+getVerOffset_ROI(roiP), \
    band_no) + DataSize[getDataType_ROI(roiP)] * getHorOffset_ROI(roiP))
   #define getRow_ROI(roiP,y,band_no) getRealRow_ROI(roiP,y,band_no)
   #define getImagRow_ROI(roiP,y,band_no) \
   ((byte *)getImagRow_Image((roiP)->dataP,(y)+getVerOffset_ROI(roiP), \
   band_no) + DataSize[getDataType_ROI(roiP)] * getHorOffset_ROI(roiP))


   #define getRealPixel_ROI(roiP,type,x,y,band_no) \
   (getRealPixel_Image((roiP)->dataP, \
   type,x+getHorOffset_ROI(roiP),y+getVerOffset_ROI(roiP),band_no))
   #define getPixel_ROI(roiP,type,x,y,band_no) \
   getRealPixel_ROI(roiP,type,x,y,band_no)
   #define getImagPixel_ROI(roiP,type,x,y,band_no) \
   (getImagPixel_Image((roiP)->dataP, \
   type,x+getHorOffset_ROI(roiP),y+getVerOffset_ROI(roiP),band_no))

   #define setRealPixel_ROI(roiP,type,x,y,band_no,pixel) \
   (getRealPixel_ROI(roiP,type,x,y,band_no) = (pixel))
   #define setPixel_ROI(roiP,type,x,y,band_no,pixel) \
   setRealPixel_ROI(roiP,type,x,y,band_no,pixel)
   #define setImagPixel_ROI(roiP,type,x,y,band_no,pixel) \
   (getImagPixel_ROI(roiP,type,x,y,band_no) = (pixel))

   #define unloadRow_ROI(roiP,rowP,y,band_no) \
   ((void) memcpy((void*)rowP,(void *)getRow_ROI(roiP,y,band_no), \
   (DataSize[getDataType_ROI(roiP)]*getHorSize_ROI(roiP))))

   #define loadRow_ROI(roiP,rowP,y,band_no) \
   ((void) memcpy((void *)getRow_ROI(roiP,y,band_no),(void *)rowP, \
   (DataSize[getDataType_ROI(roiP)]*getHorSize_ROI(roiP))))

#endif
