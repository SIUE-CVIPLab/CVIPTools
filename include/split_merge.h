/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: split_merge.h
*           Description: header file defining function prototypes, type names,
*			 and constants for split_merge.c
*         Related Files: split_merge.c, Imakefile
*   Initial Coding Date: Tue Jun  1 12:02:33 CDT 1993
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
** $Log: split_merge.h,v $
** Revision 1.6  1997/03/08 00:52:39  yawei
** Name Changes:
** 	BOOLEAN ==> CVIP_BOOLEAN
** 	FALSE ==> CVIP_YES
** 	TRUE ==> CVIP_NO
** 	BYTE ==> CVIP_BYTE
** 	SHORT ==> CVIP_SHORT
** 	INTEGER ==> CVIP_INTEGER
** 	FLOAT ==> CVIP_FLOAT
** 	DOUBLE ==> CVIP_DOUBLE
** 	TYPE ==> CVIP_TYPE
**
** Revision 1.5  1997/01/15 17:13:33  yawei
** Global Change:  IMAGE ==> Image
**
 * Revision 1.4  1996/12/23  16:42:23  yawei
 * Changed function prototypes.
 *
 * Revision 1.3  1996/12/23  00:16:13  yawei
 * changed function names
 *
 * Revision 1.2  1996/01/30  23:08:13  kluo
 * remove declaration of predicate_test
 *
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
 * Revision 1.1  1993/06/02  04:48:36  hanceg
 * Initial revision
 *
*
****************************************************************************/
#if !defined( SPLIT_N_MERGE_DEFINED )

   #define SPLIT_N_MERGE_DEFINED

   typedef struct quad QUAD;
   struct quad {
   
      byte data[3];
      unsigned int x;
      unsigned int y;
      unsigned int dx;
      unsigned int dy;
      QUAD *lower_right;
      QUAD *lower_left;
      QUAD *upper_right;
      QUAD *upper_left;

   };


/*
 * Structure type of stack to be used
 * in split and merge routine for temporary
 * storage of pointer addresses
 */

   typedef struct stack STACK;
   struct stack {
      QUAD *key;
      STACK *next;
   } ;

   typedef struct quad_list_item* QUAD_LIST;
   struct quad_list_item {
      QUAD *q;
      QUAD_LIST next;
   };

#ifdef __cplusplus
extern "C"{
#endif 

   extern Image *split_merge_setup(Image *imgP);
	extern Image *split_merge_segment(Image  *imgP,   /* <srcImage> */
		unsigned int level, unsigned int choice, void *parameters,
		CVIP_BOOLEAN Run_PCT); 
	extern Image *multi_resolution_segment(Image *imgP,   /* <srcImage> */
		unsigned int choice, void *parameters, CVIP_BOOLEAN Run_PCT);

   extern QUAD_LIST split_merge_generic(Image *srcImage,
		CVIP_BOOLEAN (*const pt)(Image *, QUAD *, void *),
		void *pt_paramP, unsigned int level);
   extern Image *quadtree2ras(Image *srcImage, QUAD *treeQUAD);
#ifdef __cplusplus
}
#endif 

#endif /* SPLIT_N_MERGE_DEFINED */
