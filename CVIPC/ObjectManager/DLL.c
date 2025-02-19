/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: DLL.c
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
** $Log: DLL.c,v $
** Revision 1.2  1995/10/23 19:22:34  mzuke
** modified print_DLL to print number on
** same line as list item
**
 * Revision 1.1  1994/10/30  17:59:08  hanceg
 * CVIPtools1.0 source file - G. Hance
 *
*
****************************************************************************/
#include <stdio.h>
#include "DLL.h"

/* private methods for the dlink class */
static dlink *new_DLink(void *newcontentsP);
static void delete_DLink(dlink *linkP);

/*
 * constructor/allocator for the dlink class
 */

static dlink *new_DLink( void *newcontentsP )
{
   dlink *lP;
   lP = (dlink *) malloc(sizeof(dlink));
   lP->contentsP = newcontentsP;
   return lP;
}

/*
 * destructor/deallocator for the dlink class
 */

static void delete_DLink( dlink *linkP )
{
   free(linkP);
}

/*
 * return the size of the list (number of links)
 */

int size_DLL( dlinked_list *llP )
{
   return llP->listlength;
}

/*
 * assign the current link pointer to the head of the list
 */

void head_DLL( dlinked_list *llP )
{
   llP->clP = llP->headP->nextP;
}

/*
 * assign the current link pointer to the tail of the list
 */

void tail_DLL( dlinked_list *llP )
{
   llP->clP = llP->tailP->previousP;
}

/*
 * returns 1 if the current link pointer is the tail and 0 otherwise
 */

int istail_DLL( dlinked_list *llP )
{
   return (llP->clP->nextP == llP->tailP);
}


/*
 * returns 1 if the current link pointer is the head and 0 otherwise
 */

int ishead_DLL( dlinked_list *llP )
{
   return (llP->clP->previousP == llP->headP);
}

/*
 * point the current link to the next link in the list
 */

void next_DLL( dlinked_list *llP )
{
   llP->clP = llP->clP->nextP;
}



/*
 * point the current link to the previous link in the list
 */

void previous_DLL( dlinked_list *llP )
{
   llP->clP = llP->clP->previousP;
}

/*
 * returns a pointer to the object contained in the current link
 */

void *retrieve_DLL( dlinked_list *llP )
{
   return llP->clP->contentsP;
}

/*
 * add a new link to the head of the list
 */

void addhead_DLL(  dlinked_list *llP,  void *newobjectP )
{
 
   dlink *newlinkP;

  /*
   * set up new link
   */

   newlinkP = new_DLink(newobjectP);

  /*
   * handle general case
   */

   llP->headP->nextP->previousP = newlinkP;
   newlinkP->nextP = llP->headP->nextP;
   newlinkP->previousP = llP->headP;
   llP->headP->nextP = llP->clP = newlinkP;

   llP->listlength++;

}


void addnext_DLL(  dlinked_list *llP,  void *newobjectP )
{
 
   dlink *newlinkP;

  /*
   * set up new link
   */

   newlinkP = new_DLink(newobjectP);

  /*
   * handle general case
   */

   llP->clP->nextP->previousP = newlinkP;
   newlinkP->nextP = llP->clP->nextP;
   newlinkP->previousP = llP->clP;
   llP->clP = llP->clP->nextP = newlinkP;

   llP->listlength++;

}


void addtail_DLL(  dlinked_list *llP,  void *newobjectP )
{
 
   dlink *newlinkP;

  /*
   * set up new link
   */

   newlinkP = new_DLink(newobjectP);

  /*
   * handle general case
   */

   llP->tailP->previousP->nextP = newlinkP;
   newlinkP->nextP = llP->tailP;
   newlinkP->previousP = llP->tailP->previousP;
   llP->tailP->previousP = llP->clP = newlinkP;

   llP->listlength++;
}


/*
 * promotes the current link to the head of the list
 */

void promote_DLL( dlinked_list *llP )
{
  /*
   * special case: current link is head, then nothing to do
   */

   if( ishead_DLL(llP) ) return;

 
  /*
   * promote current to head
   */

   llP->clP->previousP->nextP = llP->clP->nextP;
   llP->clP->nextP->previousP = llP->clP->previousP;
   llP->clP->nextP = llP->headP->nextP;
   llP->clP->previousP = llP->headP;
   llP->headP->nextP->previousP = llP->clP;
   llP->headP->nextP = llP->clP;
}

/*
 * delete the current link from the list
 */

void removecurr_DLL( dlinked_list *llP )
{
   dlink *currentP = llP->clP;

  /*
   * delete current link
   */

   llP->clP = currentP->previousP->nextP = currentP->nextP;
   currentP->nextP->previousP = currentP->previousP;

   if( !isempty_LL(llP) ) {
      delete_DLink(currentP);
      llP->listlength--;
   }
}


/*
 * delete the head from the list
 */

void removehead_DLL( dlinked_list *llP )
{
   dlink *currentP = llP->headP->nextP;

  /*
   * delete current link
   */

   llP->clP = llP->headP->nextP = currentP->nextP;
   currentP->nextP->previousP = llP->headP;

   if( !isempty_LL(llP) ) {
      delete_DLink(currentP);
      llP->listlength--;
   }
}


/*
 * delete the tail from the list
 */

void removetail_DLL( dlinked_list *llP )
{
   dlink *currentP = llP->tailP->previousP;

  /*
   * delete current link
   */

   currentP->previousP->nextP = llP->tailP;
   llP->clP = llP->tailP->previousP = currentP->previousP;

   if( !isempty_LL(llP) ) {
      delete_DLink(currentP);
      llP->listlength--;
   }
}




/*
 * replace the object contained in the current link with a new one
 */

void replace_DLL(dlinked_list *llP, void *newobjectP )
{
   llP->clP->contentsP = newobjectP;
}


int find_DLL( dlinked_list *llP, int (*match)(void *objectP, void *lookforP), void *lookforP )
{
   head_DLL(llP);
   
   for (;;) {
      if ((*match)(llP->clP->contentsP, lookforP)) return 1;
      if (istail_DLL(llP)) return 0;
      next_DLL(llP);
   }
}

/*
 * prints the contents of the linked list
 */

void print_DLL(dlinked_list *llP, void (*print)(void *objectP, FILE *fileP) , FILE *fileP)
{
   dlink *refP = llP->clP;
   register unsigned count = 1;

   head_DLL(llP);

   for (;;) {
      fprintf(stderr,"(%u)  ",count++);
      (*print)(retrieve_DLL(llP), fileP);
      if (istail_DLL(llP)) break;
      next_DLL(llP);
   }
   
   fprintf(stderr,"\n");   
   llP->clP = refP;
}


/*
 * prints the contents of the linked list
 */

void print_reverse_DLL(dlinked_list *llP, void (*print)(void *objectP, FILE *fileP), FILE *fileP )
{
   dlink *refP = llP->clP;

   tail_DLL(llP);

   for (;;) {
      (*print)(retrieve_DLL(llP) ,fileP);
      if (ishead_DLL(llP)) break;
      previous_DLL(llP);
   }

   llP->clP = refP;
}




dlinked_list *new_DLL(void)
{
   dlinked_list *this;
   this = (dlinked_list *) malloc(sizeof(dlinked_list));

   this->headP = this->clP = new_DLink(NULL);
   this->tailP = this->headP->nextP = new_DLink(NULL);
   this->tailP->nextP = this->tailP;
   this->headP->previousP = this->tailP->previousP = this->headP;
   this->listlength = 0;

   return this;
}


void delete_DLL( dlinked_list *llP, void (*objfree)(void *objectP) )
{
   dlink *currentP;

   head_DLL(llP);

   if( !isempty_LL(llP) ) {
      while ( llP->clP != llP->tailP ) {
         (*objfree)(retrieve_DLL(llP));
         currentP = llP->clP;
         next_DLL(llP);
         delete_DLink(currentP);
      }
   }

   delete_DLink(llP->headP);
   delete_DLink(llP->tailP);
   free(llP);
}


int isempty_DLL( dlinked_list *llP )
{
   return llP->headP->nextP == llP->tailP;
}

#if 0

void sort_DLL( dlinked_list *llP, int (*compar)(void *object1P, void *object2P))
{
   dlink *currentP;
   void *objectP;

   head_DLL(llP);
   next_DLL(llP);

   for(;;) {
      currentP = llP->clP;
      objectP = retrieve_DLL(currentP);

      head_DLL(llP);
      while(llP->clP->nextP != currentP) {
         if( (*compar)(objectP, retrieve_DLL(llP-clP)) >= 0 ) {
            currentP->nextP->previousP = llP->clP->nextP;
            lcurrentP;




      if( istail_DLL(llP) break;
      next_DLL(llP);
   }

#endif
