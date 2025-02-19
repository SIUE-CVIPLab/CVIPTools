/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: Stack.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Sun Sep 19 15:32:45 CDT 1993
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
** $Log: Stack.c,v $
** Revision 1.1  1994/10/30 17:59:09  hanceg
** CVIPtools1.0 source file - G. Hance
**
*
****************************************************************************/
#include "CVIPmanager.h"


Stack new_Stack(void)
{
   Stack this = new_LL();
   return this;
}

void push_Stack(Stack sP, void *objectP)
{
   addhead_LL(sP, objectP);
}

void *pop_Stack(Stack sP)
{
   void *objectP;

   objectP = retrieve_LL(sP);
   removehead_LL(sP);

   return objectP;
}

int isempty_Stack(Stack sP)
{
   return isempty_LL(sP);
}


