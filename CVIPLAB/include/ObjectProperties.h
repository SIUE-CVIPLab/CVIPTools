/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: ObjectProperties.h
*           Description: 
*         Related Files: 
*   Initial Coding Date: Sat Jul 31 15:57:58 CDT 1993
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
** $Log: ObjectProperties.h,v $
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
*
****************************************************************************/
#if !defined( OP_DEFINED )

   #define OP_DEFINED

   #include "Object.h"
      
   extern void getProp_Object( Object *objP, ROI *roiP );
   extern void printProp_Object( void *thisP , FILE *fileP);
   extern void getProp_Objects(ObjectList listP, Image *labelP);
   extern void printProp_Objects( ObjectList listP, const char *name );
   extern int readProp_Objects( ObjectList listP, const char *name );

#endif


