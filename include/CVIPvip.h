/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: CVIPvip.h
*           Description: function prototypes for conversion modules
*                        to and from the CVIPtool image format "VIP"
*         Related Files: libconverter.a, cviptovip.c, viptocvip.c
*   Initial Coding Date: Wed Apr  7 18:39:17 CDT 1993
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
* $Log: CVIPvip.h,v $
* Revision 1.4  1997/03/08 00:47:07  yawei
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
* Revision 1.3  1997/01/15 17:11:06  yawei
* Global Change:  IMAGE ==> Image
*
 * Revision 1.2  1996/06/11  12:14:29  kluo
 * \check in
 *
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
 * Revision 1.1  1993/05/31  07:10:21  hanceg
 * Initial revision
 *
*
****************************************************************************/

#if !defined( CVIPVIP_DEFINED )

   #define CVIPVIP_DEFINED

   #include <rpc/rpc.h> /* xdr is a sub-library of rpc */

   #define MAXBANDS 30
#ifdef __cplusplus
extern "C"{
#endif 


extern Image *viptocvip( char *filename, FILE *file, CVIP_BOOLEAN verbose);
extern bool_t xdr_packet(XDR *xdrs,PACKET * packet);

extern bool_t xdr_compress(XDR *xdrs,Image *imgP,FILE *file,char *filename);

extern bool_t xdr_history(XDR *xdrs,HISTORY  story);

extern bool_t xdr_info(XDR *xdrs,Image *imgP,CVIP_BOOLEAN save_history);

extern CVIP_BOOLEAN cviptovip( Image *cvipImage, char *filename, FILE *file, 
			CVIP_BOOLEAN save_history, CVIP_BOOLEAN is_compressed, 
			CVIP_BOOLEAN verbose);
extern bool_t xdr_image(XDR *xdrs,Image *imgP,FILE  *file,char *file_name,
			CVIP_BOOLEAN save_history,CVIP_BOOLEAN is_compressed);

#ifdef __cplusplus
}
#endif 
#endif
