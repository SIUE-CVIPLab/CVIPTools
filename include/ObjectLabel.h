/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: ObjectLabel.h
*           Description: 
*         Related Files: 
*   Initial Coding Date: Tue Jul 20 20:36:56 CDT 1993
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
** $Log: ObjectLabel.h,v $
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
*
****************************************************************************/
#if !defined( OBJECT_LABEL_DEFINED )

   #define OBJECT_LABEL_DEFINED

   #include "Object.h"

   struct ObjectVectorType {
      Object *oP;
      unsigned no_of_objects;
   };

   typedef struct ObjectVectorType ObjectVector;

   extern ObjectList label_Objects( Image *imageP, Image **labelP, unsigned background );
   extern  void printLabel_Objects( ObjectList listP, const char *name );
   extern int readLabel_Objects( ObjectList listP, const char *name );
   extern ObjectVector *listToVector_Objects(ObjectList listP);
   extern Image *setUpLabel_Objects(const Image *imageP);
   extern void setUpProp_Objects( const Image *imageP );

#endif

