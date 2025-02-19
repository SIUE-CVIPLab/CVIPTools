/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: CVIPtools.h
*           Description: This header file define.h is responsible
* 			 for reading in other necessary ansi standard C
*			 libraries as well as for naming macros, enumerated
*			 type declarations, and some functions.
*         Related Files: included in most higher level CVIPtools functions
*			 related to the user interface shell environment
*   Initial Coding Date: Sun May  2 15:53:25 CDT 1993
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
** $Log: CVIPtools.h,v $
** Revision 1.50  1997/05/29 15:33:51  yawei
** rename MAXWORD for WIN32 compatibility
**
** Revision 1.49  1996/12/17 20:11:14  akjoele
** changed names of frequency filters.
**
 * Revision 1.48  1996/08/09  15:44:13  akjoele
 * Added definitions for EXTRACT_BAND and ASSEMBLE_BANDS
 *
 * Revision 1.47  1996/07/22  16:29:17  akjoele
 * *** empty log message ***
 *
 * Revision 1.46  1996/02/29  20:25:21  akjoele
 * Added LOCAL_HISTEQ
 *
 * Revision 1.45  1996/02/15  23:04:02  kluo
 * add wiener filter parameter
 *
 * Revision 1.44  1996/01/18  21:59:59  mzuke
 * added menu case II8_7
 *
 * Revision 1.43  1996/01/06  20:15:38  kluo
 * add cosine wave
 *
 * Revision 1.42  1995/12/07  22:12:39  kluo
 * add unix compression
 *
 * Revision 1.41  1995/12/04  17:23:59  kluo
 * cd ..
 * add single filter
 *
 * Revision 1.40  1995/11/17  18:54:53  kluo
 * add raster scan
 *
 * Revision 1.39  1995/11/15  02:27:29  kluo
 * add helicopter rotor enhancement
 *
 * Revision 1.38  1995/11/02  01:21:46  kluo
 * add DPCM
 *
 * Revision 1.37  1995/10/31  15:20:12  mzuke
 * added enum for menu II2-1-2
 *
 * Revision 1.36  1995/10/26  15:30:17  mzuke
 * revised enums for restoration menu
 * II6
 *
 * Revision 1.35  1995/10/24  22:15:14  kluo
 * add hist specification
 * .o
 *
 * Revision 1.34  1995/10/23  19:34:48  mzuke
 * changed utility and compression menus
 *
 * Revision 1.33  1995/10/17  16:04:36  kluo
 * add the new btc program name
 *
 * Revision 1.32  1995/10/17  14:45:16  akjoele
 * add LUMINANCE
 *
 * Revision 1.31  1995/10/12  18:39:12  kluo
 * add lzw option
 *
 * Revision 1.30  1995/10/10  13:43:48  mzuke
 * modified menu items for utilities
 * and conversion
 *
 * Revision 1.29  1995/09/15  15:45:32  mzuke
 * changes menu listing
 * from II6_1_3 to II6_1_5
 *
 * Revision 1.28  1995/08/30  22:52:59  kluo
 * add new programs
 *
 * Revision 1.27  1995/08/23  21:39:41  kluo
 * add edge prewitt
 *
 * Revision 1.26  1995/08/23  21:37:12  kluo
 * check into RCS
 *
 * Revision 1.25  1995/08/01  20:51:19  kluo
 * add perimeter and euler stuff
 *
 * Revision 1.24  1995/07/31  18:47:20  mzuke
 * added menu item II5_1
 * to menu enum list
 *
 * Revision 1.23  1995/07/26  19:14:59  kluo
 * add unsharp
 *
 * Revision 1.22  1995/07/23  15:57:30  mzuke
 * removed menu case II3_3
 * from enums
 *
 * Revision 1.21  1995/07/18  20:12:48  kluo
 * add new definition
 *
 * Revision 1.20  1995/07/14  20:31:05  kluo
 * add new stuff.
 *
 * Revision 1.19  1995/07/12  02:25:59  kluo
 * add new program
 *
 * Revision 1.18  1995/07/07  00:51:43  kluo
 * add morph stuff
 *
 * Revision 1.17  1995/06/30  18:44:16  kluo
 * add link image
 *
 * Revision 1.16  1995/06/23  16:22:51  kluo
 * add hough
 *
 * Revision 1.15  1995/06/21  20:08:40  kluo
 * add quant
 *
 * Revision 1.14  1995/06/13  18:08:00  zook
 * added menu enums for added Add Noise submenus
 * and added FFT
 *
 * Revision 1.13  1995/06/07  00:04:01  luok
 * add function definition to it(spatial filters and noise utility)
 *
 * Revision 1.12  1995/05/31  00:45:23  luok
 * add spatial filter
 *
 * Revision 1.11  1995/05/15  20:53:28  luok
 *  add warp stuff.
 *
 * Revision 1.10  1995/05/11  17:39:30  kjoelena
 * Added following definitions: WVQ_APP, DEFORM_TEMPLATE.
 *
 * Revision 1.9  1995/05/10  20:49:25  zook
 * Added new program definition: MEDIAN_FILTER
 *
 * Revision 1.8  1995/05/08  20:22:06  luok
 * add binthreshold const.
 *
 * Revision 1.7  1995/04/22  20:34:12  luok
 * add new function constant to it.
 *
 * Revision 1.6  1995/04/18  21:13:01  luok
 * add multiply, divide,add, subtract, and , or, nor definition to it
 *
 * Revision 1.5  1995/04/14  21:50:08  zook
 * major changes made to MENU
 * new CVIPtools version 2.0\
 *
 * Revision 1.3  1995/01/25  19:35:45  luok
 * change compression menu and modify the index to level specification.
 * so that 'whereami' is support everywhere.
 *
 * Revision 1.2  1995/01/22  05:03:51  luok
 * add feature definition
 *
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
 * Revision 1.1  1993/05/02  23:21:00  hanceg
 * Initial revision
 *
*
****************************************************************************/

#if !defined( CVIPTOOLS_DEFINED )

#define CVIPTOOLS_DEFINED

#if !defined( NO_STD_INCLUDES )
/* Define Preprocessor statements */
	#include <stdio.h>    
	#include <stdlib.h>
	#include <string.h> 
	#include <fcntl.h>
	#include <signal.h>
	#include <sys/types.h>
	#include <math.h>

#endif

#define	MAXARG		30
#define	MAXFNAME	30
#define	CVIP_MAXWORD		80
#define	BADFD		-2
#define TICKS           60

#define LEVEL2 "Analysis", "Restoration", "Enhancement", "Compression", \
               "Conversion", "Geometry", "EnvironmentOptions"
#define LEVEL3 "Segmentation", "ObjectProperties", "EdgeDetection", \
               "Transforms", "ConvolutionMasks", "FeatureSpaceDefinition", \
	       "Lossless", "Lossy"
#define LEVEL4 "Texture", "MorphologicalFunctions", "Filtering", \
               "ColorTransforms","Zonal"  
    
typedef enum {
	T_WORD, 
	T_BAR, 
	T_AMP, 
	T_SEMI, 
	T_GT, 
	T_GTGT, 
	T_LT, 
	T_NL, 
	T_EOF
} TOKEN;

typedef enum {
	INTRO, 
	HELP, 
	I, 
	II1, 
	II2, 
	II3, 
	II4, 
	II5, 
	II6,
	II7,
	II8,
	II9,
	II1_1, 
	II1_2,
	II1_3, 
	II1_4, 
	II1_1_1,
	II1_1_2, 
	II1_1_3, 
	II1_1_4, 
	II1_1_5, 
	II1_3_8,
	II1_4_7, 
        II1_1_5_7,
	II2_1,
	II2_2,
        II2_3,
        II2_4,
	II2_1_2,
	II2_3_8,
	II3_1,
	II3_2,
	II3_4,
	II3_5,
	II4_1,
	II4_2,
	II4_4,
	II4_5,
        II5_1,
	II5_2,
	II5_3,
	II5_4,
	II6_1,
	II6_2,
        II6_3,
	II6_4,
 	II6_5,
        II6_1_4,
        II6_1_5,
	II6_2_1,
	II6_2_2, 
        II6_2_4,
	II6_5_1,
	II6_5_2,
        II8_7,
	II9_7
} MENU;

typedef enum {

	HISTEQ,
	HISTSPEC,
	LOCAL_HISTEQ,
	SMOOTH,
	SHARP,
	EDGE_LAPLACIAN, 
	EDGE_ROBERTS, 
	EDGE_SOBEL, 
	EDGE_PREWITT,
	EDGE_KIRSCH, 
	EDGE_ROBINSON,
	EDGE_PYRAMID,
	EDGE_FREI, 
	EDGE_LINK,
	HOUGH,
	CONVERT,  
	MORPHO,
/*
** Arithmetic Logic 
*/
	ADD,
	SUBTRACT,
	MULTIPLY,
	DIVIDE,
	AND,
	NOT,
	OR,
	XOR,

/*
** Band Utilities
*/
	EXTRACT_BAND,
	ASSEMBLE_BANDS,

/*
** Segmentation
*/
	MULTIRES,
	SPLITNMERGE,
	FUZZYC,
	SCTSPLIT,
	HIST_THRESH,
	MEDIANCUT,
/*
** Color
*/
	COLORXFORM, 
	LUMINANCE,
	subPCT, 
	I_subPCT, 
	PCT, 
	I_PCT,
/*
** Transforms
*/
	DCTXFORM, 
	I_DCTXFORM, 
	FFT, 
	I_FFT, 
	WALSH, 
	I_WALSH, 
	HADAMARD, 
	I_HADAMARD, 
	HAAR, 
	I_HAAR, 
	WAVELET, 
	I_WAVELET,
/*
** Noise Utilities
*/
	GAMMA_NOISE,
	GAUSSIAN_NOISE,
	NEGATIVE_NOISE,
	RAYLEIGH_NOISE,
	SALT_NOISE,
	UNIFORM_NOISE,
/*
** Histogram Modification
*/
	HIST_SHRINK,
	HIST_SLIDE,
	HIST_SPEC,
	HIST_STRETCH,
	GRAY_LIN_MOD,
	GRAY_NOLIN_MOD,
/*
** Compression
*/
	Block_Trunc_Coding, 
	GRAY_RLC, 
	BITPLANE_RLC, 
	HUFFMAN,
	JPEG_COMPRESS,
	ARITHMETIC_CODE,
	LZW_COMPRESS,
	BTC_ALG2,
	BTC_ALG3,
	DPCM,
	UNIX_PACK,
	UNIX_COMPRESS,
	UNIX_GZIP,
/*
** MORPHO
*/
	MORPH_OPEN,
	MORPH_CLOSE,
	MORPH_DILATE,
	MORPH_ERODE,
/*
** Geometry
*/
	SCALE,
	ROTATE,
	ZOOM,
	ENLARGE,
	TRANSLATE,
	CUT_PASTE,
	CROP,
	GRAY_QUANT,
	SPATIAL_QUANT,
/*
** Utility Image Creation
*/
	CHECKBOARD,
	CIRCLE,
	LINE,
	SQUARE,
	SINE_WAVE,
	COSINE_WAVE,
	SQUARE_WAVE,
/*
** Object Properties
*/
	LABEL,
	PROPS,
	BINTHRESH,
	EULER,
	PERIMETER,
	THINNESS,
	IRREGULARITY,
/*
** Warping
*/
	BILINEAR,
	CREATE_MESH,
	DISPLAY_MESH,
	WARPING,
	KEYBOARD_MESH,
	AREA_POINTS,
/*
** Linear Filters
*/
	BLUR_SPATIAL,
	LOWPASS_SPATIAL,
	LAPLACIAN_SPATIAL,
	HIGHPASS_SPATIAL,
 	DIFFERENCE_SPATIAL,
	SPECIFY_SPATIAL,
	UNSHARP_SPATIAL,
	RASTER_SCAN,
	SINGLE_FILTER,
/*
** Transform-Domain Filtering
*/
	XFORMFILTER,
	INVERSEFILTER,
	LEAST_SQUARES,
	SIMPLE_WIENER,
	WIENER_FILTER,
	PARAMETRIC_WIENER,
	GEOMETRIC_MEAN,
	POWER_SPECT_EQUALIZE,
	HOMOMORFILTER,
	NOTCHFILTER,
	

/*
** Spatial-Domain Filtering
*/
	MINIMUM_FILTER,
	MEAN_FILTER,
	ALPHA_FILTER,
	CONTRA_FILTER,
	GEOMETRIC_FILTER,
	HARMONIC_FILTER,
	YP_MEAN_FILTER,
	MEDIAN_FILTER,
	MIDPOINT_FILTER,
	MAXIMUM_FILTER,
/*
** Environment Options
*/
	CVIP_IMGPATH,
	CVIP_DISPLAY,
/*
** Other
*/
	ZERO_PAD,
	DATA_REMAP,
	MOUSE_COORDS,
/*
** Applications
*/
	DERMVIS,
	FEATURE,
	WVQ_APP,
	DEFORM_TEMPLATE,
	NIGHTVISION,
	COPTER_APP1

} PROGRAMS;

#endif /* CVIPTOOLS_DEFINED */
