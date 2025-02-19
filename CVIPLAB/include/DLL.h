/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: dll.h
*           Description: 
*         Related Files: 
*   Initial Coding Date: Thu Jul 15 15:35:14 CDT 1993
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
** $Log: DLL.h,v $
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
*
****************************************************************************/
#if !defined( DLINKED_LIST_DEFINED )

   #define DLINKED_LIST_DEFINED

   #include "Link.h"

   struct DoublyLinkedListType {
      dlink *clP;
      dlink *headP;
      dlink *tailP;
      int listlength;
   };

   typedef struct DoublyLinkedListType dlinked_list;

   extern dlinked_list *new_DLL(void);
   extern void removecurr_DLL(dlinked_list *llP);
   extern void removehead_DLL(dlinked_list *llP);
   extern void removetail_DLL(dlinked_list *llP);
   extern int size_DLL(dlinked_list *llP);
   extern void head_DLL(dlinked_list *llP);
   extern void tail_DLL(dlinked_list *llP);
   extern int istail_DLL(dlinked_list *llP);
   extern int ishead_DLL(dlinked_list *llP);
   extern void next_DLL(dlinked_list *llP);
   extern void previous_DLL(dlinked_list *llP);
   extern void *retrieve_DLL(dlinked_list *llP);
   extern void addhead_DLL(dlinked_list *llP, void *newobjectP);
   extern void addtail_DLL(dlinked_list *llP, void *newobjectP);
   extern void addnext_DLL(dlinked_list *llP, void *newobjectP);
   extern void promote_DLL(dlinked_list *llP);
   extern void print_DLL(dlinked_list *llP, void (*print)(void *objectP, FILE *fileP) , FILE *fileP);
   extern void delete_DLL(dlinked_list *llP, void (*objfree)(void *objectP) );
   extern void replace_DLL(dlinked_list *llP, void *newobjectP);
   extern int find_DLL(dlinked_list *llP, int (*match)(void *objectP, void *lookforP), void *lookforP);
   extern void print_reverse_DLL(dlinked_list *llP, void (*print)(void *objectP, FILE *fileP), FILE *fileP );
   extern int isempty_DLL( dlinked_list *llP );



#endif




















