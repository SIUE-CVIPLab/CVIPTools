/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: Stack.h
*           Description: 
*         Related Files: 
*   Initial Coding Date: Sun Sep 19 15:32:54 CDT 1993
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
** $Log: Stack.h,v $
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
*
****************************************************************************/
#if !defined( STACK_DEFINED )

	#define STACK_DEFINED

	typedef linked_list *Stack;

	extern Stack new_Stack(void);
	extern void push_Stack(Stack sP, void *objectP);
	extern void *pop_Stack(Stack sP);
	extern int isempty_Stack(Stack sP);

	#define delete_Stack(stackP,objfreeP) delete_LL(stackP,objfreeP)

#endif /* STACK_DEFINED */
