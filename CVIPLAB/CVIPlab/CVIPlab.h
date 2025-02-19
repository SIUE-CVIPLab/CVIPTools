/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: CVIPlab.h
*           Description: contains function prototypes, constants and types
*			            defined in CVIPlab functions.
*         Related Files: *.c
*   Initial Coding Date: Tue Apr 27 21:49:42 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Gregory Hance
*                        Southern Illinois University @ Edwardsville
*
* RCS (Revision Control System) Information
* ...Added automatically by RCS
*
** $Log: CVIPlab.h,v $
** Revision 1.4  1997/01/10 19:45:12  yawei
** threshold_Image ==> threshold_lab
**
* Revision 1.3  1997/01/09  23:05:25  yawei
* 1) Changed header info.
* 2) Added conditional macro to avoid repeated including
* 3) threshold.h ==> CVIPlab.h
*
* Revision 1.2  1996/12/23  17:45:00  yawei
* updated from $CVIPHOME/include
*
* Revision 1.3  1996/11/14  04:29:38  yawei
* Added another parameter to threshold_Image
*
* Revision 1.2  1996/07/22  16:29:39  akjoele
* *** empty log message ***
*
* Revision 1.1  1994/10/30  22:43:06  hanceg
* Initial revision
*
* Revision 1.1  1993/04/29  06:54:22  hanceg
* Initial revision
*
*
****************************************************************************/

#ifndef CVIP_LAB__H
#define CVIP_LAB__H


extern Image *threshold_lab(Image *imageP, unsigned int level);
extern int test_function(int i);
#endif
