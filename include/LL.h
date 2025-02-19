/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: ll.h
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
** $Log: LL.h,v $
 * Revision 1.2  1997/02/26  21:22:58  yawei
 * link == slink. for porting to Linux
 *
** Revision 1.1  1994/10/30 22:43:06  hanceg
** Initial revision
**
*
****************************************************************************/
#if !defined( LINKED_LIST_DEFINED )

   #define LINKED_LIST_DEFINED

   #include "Link.h"

   struct SinglyLinkedListType {
      slink *clP;
      slink *headP;
      slink *tailP;
      int listlength;
   };

   typedef struct SinglyLinkedListType linked_list;

   extern linked_list *new_LL(void);
   extern void removenext_LL(linked_list *llP);
   extern void removehead_LL(linked_list *llP);
   extern int size_LL(linked_list *llP);
   extern void head_LL(linked_list *llP);
   extern void tail_LL(linked_list *llP);
   extern int istail_LL(linked_list *llP);
   extern int ishead_LL(linked_list *llP);
   extern void next_LL(linked_list *llP);
   extern void previous_LL(linked_list *llP);
   extern void *retrieve_LL(linked_list *llP);
   extern void *retrieveNext_LL( linked_list *llP );
   extern void addhead_LL(linked_list *llP, void *newobjectP);
   extern void addnext_LL(linked_list *llP, void *newobjectP);
   extern void promote_LL(linked_list *llP);
   extern void print_LL(linked_list *llP, void (*print)(void *objectP,FILE *fileP), FILE *fileP);
   extern void delete_LL(linked_list *llP, void (*objfree)(void *objectP) );
   extern void replace_LL(linked_list *llP, void *newobjectP);
   extern int find_LL(linked_list *llP, int (*match)(void *objectP, void *lookforP), void *lookforP);
   extern int findNext_LL( linked_list *llP, int (*match)(void *objectP, void *lookforP), void *lookforP );
   extern int isempty_LL( linked_list *llP );

   extern slink *new_Link( void *newcontentsP );
   extern void delete_Link( slink *linkP );

#endif




















