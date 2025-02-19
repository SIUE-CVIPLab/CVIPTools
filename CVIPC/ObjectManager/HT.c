/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: ht.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Wed Aug 25 12:43:26 CDT 1993
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Gregory Hance
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
** $Log: HT.c,v $
** Revision 1.1  1994/10/30 17:59:08  hanceg
** CVIPtools1.0 source file - G. Hance
**
*
****************************************************************************/
#include "CVIPtoolkit.h"
#include "HT.h"

/*
 * Hash Table Class Stuff
 */

HashTable *new_HT(size_t size)
   {
   HashTable *newP = (HashTable *) malloc(sizeof(HashTable));

   newP->table = (linked_list **) calloc( size, sizeof(linked_list *));
   newP->size = size;
   newP->key = 0;

   if(!newP->table || !newP) { 
      fprintf(stderr, "can not allocate memory for hash table.\n");
      return NULL;
   }

   return newP;
}

void delete_HT(HashTable *htP, void (*objfree)(void *objectP))
{
   register int i;

   for ( i = 0; i < htP->size; i++ )
      if(htP->table[i]) delete_LL(htP->table[i],objfree);

   free(htP->table);
   free(htP);
}

void addObject_HT(HashTable *htP, void *objectP)
{
   unsigned key = htP->key;

   if(!(htP->table[key]))
      htP->table[key] = new_LL();

   addhead_LL( htP->table[key], objectP);
}

int findObject_HT(HashTable *htP, int (*match)(void *objectP, void *lookforP), void *lookforP)
{
   unsigned key = htP->key;

   if( htP->table[key] )
      return( find_LL( htP->table[key], match, lookforP) );
   else
      return 0;
}


int findNextObject_HT(HashTable *htP, int (*match)(void *objectP, void *lookforP), void *lookforP)
{
   unsigned key = htP->key;

   if( htP->table[key] )
      return( findNext_LL( htP->table[key], match, lookforP) );
   else
      return 0;
}

void *getObject_HT(HashTable *htP)
{
   return(retrieve_LL(htP->table[htP->key]));
}

void *getNextObject_HT(HashTable *htP)
{
   return(retrieveNext_LL(htP->table[htP->key]));
}

void removeNextObject_HT(HashTable *htP)
{
   unsigned key = htP->key;
   removenext_LL(htP->table[key]);
  
   if(isempty_LL(htP->table[key])) {
      delete_Link(htP->table[key]->headP);
      delete_Link(htP->table[key]->tailP);
      free(htP->table[key]);
      htP->table[key] = NULL;
   }
}
