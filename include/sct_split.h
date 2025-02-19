/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: sct_split.h
*           Description: contains function prototypes, type names and constants
*			 for the sctsplit.c
*         Related Files: sct_split.c, Imakefile
*   Initial Coding Date: Sun May 30 14:26:41 CDT 1993
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
** $Log: sct_split.h $
** Revision 1.5  1996/12/30 22:22:50  yawei
** Added A_split, B_split
**
 * Revision 1.4  1996/12/23  16:40:53  yawei
 * 1) Changed file name: SCTsplit.h ==> sct_split.h
 * 2) Changed function prototype:
 *    Image *SCTsplit_Image(Image **imgP,int,int )
 * ==>Image *sct_split_segment(Image *imgP,int,int )
 *
 * Revision 1.3  1996/07/22  16:29:25  akjoele
 * *** empty log message ***
 *
 * Revision 1.2  1996/01/17  02:47:18  kluo
 * change prototype of SCTsplit_Image
 *
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
 * Revision 1.1  1993/05/31  03:23:37  hanceg
 * Initial revision
 *
*
****************************************************************************/
#if !defined(SCTSPLIT_DEFINED)

   	#define SCTSPLIT_DEFINED

#ifdef __cplusplus
extern "C"{
#endif 

	extern Image *sct_split_segment( Image *imgP,int A_split,int B_split);

	/* the setup function is for compatibility with the old menu_driven 
	 * CVIPtools interface, new application are not encouraged to use it.
	 */
	extern Image *sct_split_setup(Image *imgP);

#ifdef __cplusplus
}
#endif 

#endif /* SCTSPLIT_DEFINED */
