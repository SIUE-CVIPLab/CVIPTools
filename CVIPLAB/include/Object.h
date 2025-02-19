/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: Object.h
*           Description: 
*         Related Files: 
*   Initial Coding Date: Sat Jul 31 17:05:07 CDT 1993
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
** $Log: Object.h,v $
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
*
****************************************************************************/
#if !defined( OBJECT_DEFINED )

   #define OBJECT_DEFINED

   #include "ColorMap.h"

   struct ObjPropType {
      float eig_ratio;
      float orientation;
      float h_cog;
      float v_cog;
      float area;
   };

   typedef struct ObjPropType ObjProp;

   struct ObjectType
   {
      int label;
      Color pixel;
      long x_min;
      long y_min;
      long x_max;
      long y_max;
      ObjProp prop;
   };

   typedef struct ObjectType Object;
   typedef linked_list *ObjectList;

   extern void print_Object( void *thisP, FILE *fileP);
   extern int read_Object( void *thisP, FILE *fileP);
   extern Object *new_Object(int label_count, Color pixel, int y_pos, int x_pos);
   extern void delete_Object(void *objectP);
   extern int match_Object(void *objectP, void *labelP);

   extern void drawBB_Objects(Image *imageP, ObjectList listP);
   extern int shootRay( Image *imageP, int elev, int *ray_x, int *ray_y, int x1, int y1, int x2, int y2);

#endif
