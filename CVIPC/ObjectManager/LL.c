/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: ll.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Fri Jul 16 12:31:20 CDT 1993
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
** $Log: LL.c,v $
** Revision 1.4  1997/03/08 02:14:20  yawei
** link ==> slink
**
** Revision 1.3  1997/02/26 21:25:47  yawei
** link ==> slink for porting to Linux.
**
** Revision 1.2  1997/01/16 21:35:16  yawei
** updated changes
**
 * Revision 1.1  1994/10/30  17:59:08  hanceg
 * CVIPtools1.0 source file - G. Hance
 *
*
****************************************************************************/
#include <stdio.h>
#include "LL.h"

/*
 * constructor/allocator for the link class
 */

slink *new_Link( void *newcontentsP )
{
   slink *lP;
   lP = (slink *) malloc(sizeof(slink));
   lP->contentsP = newcontentsP;
   return lP;
}

/*
 * destructor/deallocator for the link class
 */

void delete_Link( slink *linkP )
{
   free(linkP);
}

/*
 * return the size of the list (number of links)
 */

int size_LL( linked_list *llP )
{
   return llP->listlength;
}

/*
 * assign the current link pointer to the head of the list
 */

void head_LL( linked_list *llP )
{
   llP->clP = llP->headP->nextP;
}

/*
 * assign the current link pointer to the tail of the list
 */

void tail_LL( linked_list *llP )
{
   llP->clP = llP->tailP;
   previous_LL(llP);
}

/*
 * returns 1 if the current link pointer is the tail and 0 otherwise
 */

int istail_LL( linked_list *llP )
{
   return (llP->clP->nextP == llP->tailP);
}


/*
 * returns 1 if the current link pointer is the head and 0 otherwise
 */

int ishead_LL( linked_list *llP )
{
   return (llP->clP == llP->headP->nextP);
}

/*
 * point the current link to the next link in the list
 */

void next_LL( linked_list *llP )
{
   llP->clP = llP->clP->nextP;
}


/*
 * returns a pointer to the object contained in the current link
 */

void *retrieve_LL( linked_list *llP )
{
   return llP->clP->contentsP;
}

void *retrieveNext_LL( linked_list *llP )
{
   return llP->clP->nextP->contentsP;
}


/*
 * add a new link to the head of the list
 */

void addhead_LL(  linked_list *llP,  void *newobjectP )
{
 
   slink *newlinkP;

  /*
   * set up new link
   */

   newlinkP = new_Link(newobjectP);

  /*
   * add new link to the head of the list
   */

   newlinkP->nextP = llP->headP->nextP;
   llP->clP = llP->headP->nextP = newlinkP;

   llP->listlength++;
}


void addnext_LL(  linked_list *llP,  void *newobjectP )
{
 
   slink *newlinkP;

  /*
   * set up new link
   */

   newlinkP = new_Link(newobjectP);

 
  /*
   * add new link to the head of the list
   */

   newlinkP->nextP = llP->clP->nextP;
   llP->clP = llP->clP->nextP = newlinkP;

   llP->listlength++;
}


/*
 * promotes the current link to the head of the list
 */

void promote_LL( linked_list *llP )
{
   slink *currentP;

  /*
   * special case: current link is head, then nothing to do
   */

   if( ishead_LL(llP) ) return;

  /*
   * promote current to head
   */

   currentP = llP->clP;
   previous_LL(llP);

   llP->clP->nextP = currentP->nextP;
   currentP->nextP = llP->headP->nextP;
   llP->headP->nextP = llP->clP = currentP;
}

/*
 * delete the current link from the list
 */

void removenext_LL( linked_list *llP )
{
   slink *currentP = llP->clP->nextP;

   
  /*
   * delete current link
   */

   if( !isempty_LL(llP) ) {
 	llP->clP->nextP = currentP->nextP;
        delete_Link(currentP);
        llP->listlength--;
   }

}


/*
 * delete the current link from the list
 */

void removehead_LL( linked_list *llP )
{
   slink *currentP = llP->headP->nextP;
 
  /*
   * delete current link
   */

   llP->clP = llP->headP->nextP = currentP->nextP;

   if( !isempty_LL(llP) ) {
      delete_Link(currentP);
      llP->listlength--;
   }
}


/*
 * replace the object contained in the current link with a new one
 */

void replace_LL(linked_list *llP, void *newobjectP )
{
   llP->clP->contentsP = newobjectP;
}


int find_LL( linked_list *llP, int (*match)(void *objectP, void *lookforP), void *lookforP )
{
   head_LL(llP);

   for (;;) {
      if ((*match)(llP->clP->contentsP, lookforP)) return 1;
      if (istail_LL(llP)) return 0;
      next_LL(llP);
   }
}


int findNext_LL( linked_list *llP, int (*match)(void *objectP, void *lookforP), void *lookforP )
{
   llP->clP = llP->headP;

   for (;;) {
      if ((*match)(llP->clP->nextP->contentsP, lookforP)) return 1;
      next_LL(llP);
      if (istail_LL(llP)) return 0;
   }
}


void previous_LL( linked_list *llP )
{
   slink *currentP = llP->clP;

   llP->clP = llP->headP;
   
   while ( (llP->clP->nextP != currentP) && !(istail_LL(llP)) ) {
      next_LL(llP);
   }

}



/*
 * prints the contents of the linked list
 */

void
print_LL(
	linked_list *llP,
	void (*print)(void *objectP, FILE *fileP),
	FILE *fileP
)
{
   slink *refP = llP->clP;
   register int i = 1;

   head_LL(llP);

   if( !isempty_LL(llP) ) {
      for (;;) {
         (*print)(retrieve_LL(llP),fileP);
         if (istail_LL(llP)) break;
         next_LL(llP);
      }
   }

   llP->clP = refP;
}



linked_list *new_LL(void)
{
   linked_list *this;
   this = (linked_list *) malloc(sizeof(linked_list));

   this->headP = this->clP = new_Link(NULL);
   this->tailP = this->headP->nextP = new_Link(NULL);
   this->tailP->nextP = this->tailP;
   this->listlength = 0;

   return this;
}


void delete_LL( linked_list *llP, void (*objfree)(void *objectP) )
{
   slink *currentP;

   head_LL(llP);

   if( !isempty_LL(llP) ) {
      while ( llP->clP != llP->tailP ) {
         if (objfree)
	    (*objfree)(retrieve_LL(llP));
         currentP = llP->clP;
         next_LL(llP);
         delete_Link(currentP);
      }
   }

   delete_Link(llP->headP);
   delete_Link(llP->tailP);
   free(llP);
}

int isempty_LL( linked_list *llP )
{
   return llP->headP->nextP == llP->tailP;
}
