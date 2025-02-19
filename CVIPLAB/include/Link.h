/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: link.h
*           Description: 
*         Related Files: 
*   Initial Coding Date: Thu Jul 15 15:26:00 CDT 1993
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
** $Log: Link.h,v $
 * Revision 1.2  1997/02/26  21:34:46  yawei
 * link ==> slink for porting to linux
 *
** Revision 1.1  1994/10/30 22:43:06  hanceg
** Initial revision
**
*
****************************************************************************/

#if !defined( LINKTYPE_DEFINED )

   #define LINKTYPE_DEFINED

   struct DoubleLinkType {
      struct DoubleLinkType *nextP;
      struct DoubleLinkType *previousP;
      void *contentsP;
   };

   typedef struct DoubleLinkType dlink;

   struct SingleLinkType {
      struct SingleLinkType *nextP;
      void *contentsP;
   };

   typedef struct SingleLinkType slink;

#endif
