/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: HT.h
*           Description: 
*         Related Files: 
*   Initial Coding Date: Wed Aug 25 12:43:44 CDT 1993
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
** $Log: HT.h,v $
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
*
****************************************************************************/
/*
 * Hash Table Class Stuff
 */

#if !defined( HASH_TABLE_DEFINED )

   #define HASH_TABLE_DEFINED

   #include "LL.h"

   #define setKey_HT(h,k) ((h)->key = (k))
   #define size_HT(h) ((h)->size)

   struct HashTableType {
      linked_list **table;
      unsigned key;

      unsigned size;
   };

   typedef struct HashTableType HashTable;

   extern HashTable *new_HT(size_t size);
   extern void delete_HT(HashTable *htP, void (*objfree)(void *objectP));
   extern void addObject_HT(HashTable *htP, void *objectP);
   extern int findObject_HT(HashTable *htP, int (*match)(void *objectP, void *lookforP), void *lookforP);
   extern int findNextObject_HT(HashTable *htP, int (*match)(void *objectP, void *lookforP), void *lookforP);
   extern void *getNextObject_HT(HashTable *htP);
   extern void *getObject_HT(HashTable *htP);
   extern void removeNextObject_HT(HashTable *htP);

#endif

