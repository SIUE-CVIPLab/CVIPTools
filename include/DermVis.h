/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: CVIPdermvis.h
*           Description: 
*         Related Files: 
*   Initial Coding Date: Wed Sep 15 19:41:57 CDT 1993
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Gregory Hance
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
** $Log: DermVis.h,v $
 * Revision 1.4  1997/03/08  00:50:16  yawei
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
** Revision 1.3  1996/12/18 03:47:19  yawei
** Changed header file to CVIPmorph.h
**
 * Revision 1.2  1996/12/13  19:24:58  akjoele
 * removed crop_Image()
 *
 * Revision 1.1  1996/12/13  19:03:18  akjoele
 * Initial revision
 *
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
*
****************************************************************************/
#if !defined( CVIPDERMVIS_DEFINED )

	#define CVIPDERMVIS_DEFINED

	typedef Image *Border;

	#include "CVIPobject.h"
	#include "CVIPsegment.h"
        #include "Spline.h"
	#include "SeedFill.h"
	#include "findNonSkin.h"
	#include "CVIPmorph.h"


	#define SKIP_ROWS 32

	#define CENTER_X	256
	#define CENTER_Y	256

	typedef struct {
		int	number;
		float	h_cog;
		float	v_cog;
	} CentroidObjectType;

	typedef CentroidObjectType *CentroidObject;



	extern Border new_Border(unsigned width, unsigned height);
	extern int makeImage_Matrix(Matrix *matrixP, Image **imageP);
	extern void BinToGray_Image(Image *imageP);
	extern Image *mask_Image(Image *imgP, Image *maskP);
	extern Image *cloneNoData_Image(Image *inP);
	extern double correlate_Border(Border manP, Border autP);
	extern long getArea_Border(Border borP);
	extern Border col2Bin_Border(Image *origP, Image *cborP);
	extern Border xor_Border( Border bor1P, Border bor2P );
	extern  Image *color2index_Image( Image *imageP );
	extern int getBest_Objects(ObjectList olP);
	extern int getLocDat_Image(Image *imgP, int value, int *ray_x, int *ray_y);
	extern int getInsidePoint_Contour(Image *imgP, int value, int *ray_x, int *ray_y);
int PMedian_Image( Image *imgP );
	extern int findNoColors_Image( Image *img );
	extern CVIP_BOOLEAN stdDevTest(Image *imgP, QUAD *quadP, void *paramP);
	extern CVIP_BOOLEAN varianceTest(Image *imgP, QUAD *quadP, void *paramP);
	extern ObjectList dupList_Objects(ObjectList listP);
	extern int readCentroidFile(const char *fname, CentroidObject *objP, int n);
	extern CentroidObject findCentroidObject(CentroidObject objP, int n, int number);
	extern int drawTumorBorder_Image(Image *imgP, Border borP, byte *color);
	extern int vectorMoment(float *data, int n, float *ave, float *sdev);

	extern Image *dermVisApp_SetUp(const Image *imgP);
	
#endif /* CVIPDERMVIS_DEFINED */
