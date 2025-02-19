/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: masks.h
*           Description: This is header file containing info. pertinent
*                        to edge_detect.c
*         Related Files: edge_detect.c, Imakefile
*   Initial Coding Date: Wed Jun  2 01:06:35 CDT 1993
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
** $Log: masks.h,v $
** Revision 1.4  1997/05/18 04:58:23  yawei
** changed mask values to float number, remove WIN32 warnings and for
** numer safety.
**
** Revision 1.3  1996/11/05 21:43:42  yawei
** changed function name from "mask_img" to "h_image"
**
 * Revision 1.2  1996/11/03  23:34:51  yawei
 * Added function mask_img
 *
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
 * Revision 1.1  1993/06/02  07:54:17  hanceg
 * Initial revision
 *
*
****************************************************************************/
#if !defined( MASKS_DEFINED )

   #define MASKS_DEFINED

   typedef enum {GAUSSIAN, LOW1, LOW2, NEIGHBORHOOD, LAP1, LAP2, LAPB1, LAPB2,
SOB_V, SOB_H, W1, W2, W3, W4, W5, W6, W7, W8, W9} MASK_TYPE;  

   typedef struct {
      short int n;
      short int **vertical;
      short int **horizontal;
      short int **diag1;
      short int **diag2;
    } KIRSCH_MASK;

   #define LAPLACIAN_MASK 19

   #define MASKS1  (MASK_TYPE)0,       1.0,2.0,1.0,     2.0,4.0,2.0,     1.0,2.0,1.0, \
(MASK_TYPE)1, 0.1,0.1,0.1,      0.1,0.2,0.1,       0.1,0.1,0.1, \
(MASK_TYPE)2, 1.0/16,1.0/8.0,1.0/16.0, 1.0/8.0,1.0/4.0,1.0/8.0, 1.0/16,1.0/8,1.0/16, \
(MASK_TYPE)3, 1.0/9.0,1.0/9.0,1.0/9.0, 1.0/9.0,1.0/9.0,1.0/9.0, 1.0/9.0,1.0/9.0,1.0/9.0, \
(MASK_TYPE)4,    0.0,-1.0,0.0,         -1.0,4.0,-1.0,     0.0,-1.0,0.0, \
(MASK_TYPE)5,    1.0,-2.0,1.0,         -2.0,4.0,-2.0,     1.0,-2.0,1.0, \
(MASK_TYPE)6,    -1.0,-1.0,-1.0,       -1.0,9.0,-1.0,     -1.0,-1.0,-1.0, \
(MASK_TYPE)7,    1.0,-2.0,1.0,         -2.0,5.0,-2.0,     1.0,-2.0,1.0, \
(MASK_TYPE)8,    1.0,0.0,-1.0,         2.0,0.0,-2.0,      1.0,0.0,-1.0, \
(MASK_TYPE)9,    1.0,2.0,1.0,          0.0,0.0,0.0,       -1.0,-2.0,-1.0, \
(MASK_TYPE)10,   1.0,1.4142136,1.0,    0.0,0.0,0.0,       -1.0,-1.4142136,-1.0,  \
(MASK_TYPE)11,   1.0,0.0,-1.0,         1.4142136,0.0,-1.4142136,   1.0,0.0,-1.0,  \
(MASK_TYPE)12,   0.0,-1.0,1.4142136,   1.0,0.0,-1.0,            -1.4142136,1.0,0.0, \
(MASK_TYPE)13,   1.4142136,-1.0,0.0,   -1.0,0.0,1.0,            0.0,1.0,-1.4142136, \
(MASK_TYPE)14,   0.0,1.0,0.0,          -1.0,0.0,-1.0,           0.0,1.0,0.0, \
(MASK_TYPE)15,   -1.0,0.0,1.0,         0.0,0.0,0.0,             1.0,0.0,-1.0, \
(MASK_TYPE)16,   1.0,-2.0,1.0,         -2.0,4.0,-2.0,           1.0,-2.0,1.0, \
(MASK_TYPE)17,   -2.0,1.0,-2.0,        1.0,4.0,1.0,            -2.0,1.0,-2.0, \
(MASK_TYPE)18,   1.0,1.0,1.0,             1.0,1.0,1.0,             1.0,1.0,1.0, \
(MASK_TYPE)19,   0.0,-1.0,0.0,            -1.0,4.0,-1.0,             0.0,-1.0,0.0, \
(MASK_TYPE)20,   0.0,-1.0,0.0,            -1.0,5.0,-1.0,             0.0,-1.0,0.0, \
(MASK_TYPE)21,    -1.0,-1.0,-1.0,       -1.0,8.0,-1.0,     -1.0,-1.0,-1.0, \
(MASK_TYPE)22,    -1.0,-1.0,-1.0,       -1.0,9.0,-1.0,     -1.0,-1.0,-1.0, \
(MASK_TYPE)23,   -2.0,1.0,-2.0,             1.0,4.0,1.0,             -2.0,1.0,-2.0, \
(MASK_TYPE)24,   -2.0,1.0,-2.0,             1.0,5.0,1.0,             -2.0,1.0,-2.0 

   #define MASKS2 (MASK_TYPE)0,   1.0/25,1.0/25,1.0/25,1.0/25,1.0/25, \
     1.0/25,1.0/25,1.0/25,1.0/25,1.0/25, \
     1.0/25,1.0/25,1.0/25,1.0/25,1.0/25, \
     1.0/25,1.0/25,1.0/25,1.0/25,1.0/25, \
     1.0/25,1.0/25,1.0/25,1.0/25,1.0/25
     
   static struct mask3x3 {
      MASK_TYPE choice;
      float kernel[9];
   } MASK3x3[] = {MASKS1}; 

   static struct mask5x5 {
      MASK_TYPE choice;
      float kernel[25];
   } MASK5x5[] = {MASKS2}; 

#ifdef __cplusplus
extern "C"{
#endif 
	extern Image * h_image(int type, unsigned int height, unsigned int width);
#ifdef __cplusplus
}
#endif 

#endif /* MASKS_DEFINED */

