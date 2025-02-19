/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: fractal.h
*           Description: 
*         Related Files: 
*   Initial Coding Date: Tue Feb 17 23:28:31 CST 1998
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Sreenivas Makam
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1996 SIUE - by Scott Umbaugh and Sreenivas Makam.
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
** $Log: fractal.h,v $
** Revision 1.2  1998/03/30 19:29:44  smakam
** changed the prototype to include 11 parameters
**
** Revision 1.1  1998/02/18 05:31:50  cvip
** Initial revision
**
**
****************************************************************************/
#if !defined( FRACTAL_DEFINED)
   #define FRACTAL_DEFINED

   #include "CVIPimage.h"
/* xchen update here */
#ifdef __cplusplus
extern "C"{
#endif 
	extern int frac_compress(Image *inputImage, char *filename,double,int,int,int,int,char,char,int,int);
	extern Image *frac_decompress(char *filename);
/* and xchen update here */
#ifdef __cplusplus
}
#endif 
	
	
	/* this following function is for backward compatibility, new programs
	* should always use the newer ones provided above
	*/
	extern Image *frac_decompression(FILE *file_in);

#endif /* FRACTAL_DEFINED */

