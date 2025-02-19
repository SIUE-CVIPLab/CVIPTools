/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: grey_RLC.h
*           Description: 
*         Related Files: 
*   Initial Coding Date: Tue Dec  3 20:15:02 CST 1996
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Muthukumaran Sankarasubbu
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1996 SIUE - by Scott Umbaugh and Yansheng Wei.
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
** $Log: grey_RLC.h,v $
 * Revision 1.6  1997/03/08  00:49:15  yawei
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
** Revision 1.5  1997/01/15 17:12:09  yawei
** Global Change:  IMAGE ==> Image
**
 * Revision 1.4  1997/01/15  16:22:45  yawei
 * updated changes
 *
 * Revision 1.3  1996/12/04  02:36:28  yawei
 * Added header.
 *
 * Revision 1.3  1996/12/04  02:36:28  yawei
 * Added header.
 *
*
****************************************************************************/
#if !defined( GRAY_LEVEL_RLC_DEFINED)
   #define GRAY_LEVEL_RLC_DEFINED

   #include "CVIPimage.h"
   #include "CVIPdef.h"

#ifdef __cplusplus
extern "C"{
#endif 

   extern int glr_compress(Image *inputImage, char *filename, int win);
   extern Image *glr_decompress(char *filename);

   /* extern Image* glr(Image *srcImage, CVIP_BOOLEAN *remap); 
	   This wrapper function is no longer supported, as with other compress
		functions
	 */

	/* this following function is for backward compatibility, new programs
	 * should always use the newer ones provided above
	 */
   extern Image *glr_decompression(FILE *dec);
#ifdef __cplusplus
}
#endif 

#endif

