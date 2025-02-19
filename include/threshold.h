/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: threshold.h
*           Description: contains function prototypes, constants and types
*			 defined in threshold.c
*         Related Files: threshold.c
*   Initial Coding Date: Tue Apr 27 21:49:42 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Gregory Hance
*                        Southern Illinois University @ Edwardsville
*
* RCS (Revision Control System) Information
* ...Added automatically by RCS 
*
** $Log: threshold.h,v $
** Revision 1.6  1997/03/08 00:50:43  yawei
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
** Revision 1.5  1997/01/15 17:12:33  yawei
** Global Change:  IMAGE ==> Image
**
 * Revision 1.4  1996/12/23  18:39:22  yawei
 * Changed function name
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
#if !defined (_CVIP_THRESHOLD_)
#define _CVIP_THRESHOLD_
#ifdef __cplusplus
extern "C"{
#endif 

extern Image *threshold_segment(Image *imageP, unsigned int level, 
					CVIP_BOOLEAN thresh_inbyte);
extern Image *threshold_setup(Image *inputImage);

#ifdef __cplusplus
}
#endif 

#endif 