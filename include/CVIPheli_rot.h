/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: CVIPheli_rot.h
*           Description: 
*         Related Files: 
*   Initial Coding Date: Tue Apr  1 15:54:51 CST 1997
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Yansheng Wei
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1996 SIUE - by Scott Umbaugh and Yansheng Wei.
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
** $Log: CVIPheli_rot.h,v $
** Revision 1.2  1997/04/01 21:56:52  yawei
** added header
**
*
****************************************************************************/
 
/* project.h */
#include "CVIPtoolkit.h"
#include "CVIPdef.h"

#if !defined(CVIP_HELI_ROT)
#define CVIP_HELI_ROT

#define DEFAULT 0
#define WHITE	255
#define	BLACK	0

#ifdef SQRT_2PI
#undef SQRT_2PI
#endif
#define	SQRT_2PI	2.506628275

#define MAX1        10
#define THRESHOLD   10
#define HASH_SIZE 251U
#define hash_Object(label) (((unsigned)(label))%HASH_SIZE)



static void print_surround(const MATRIX *, int);
static void print_bookhex();

typedef HashTable *ObjectHash;
static  CVIP_BOOLEAN askYorN_CVIP( void );

static CVIP_BOOLEAN
askYorN_CVIP( void )
{
        char    buf[80];

        (void) fGetLine_CVIP(stdin, buf);


        if( (*buf == 'y') || (*buf == 'Y') )
                return CVIP_YES;
        else
                return CVIP_NO;
}

typedef struct {
	int	lower;
	int	peak;
	int	upper;
} PeakObject;

int   array_sp[10][9];
float CB[10][10];
IMAGE *morphIterMod_Image (
   const IMAGE *binIMAGE,
   const MATRIX **surMATS,
   CVIP_BOOLEAN (*const boolFUNC)(CVIP_BOOLEAN a,CVIP_BOOLEAN b),
   int no_of_sur,
   int connectedness,
   int no_of_iter,
   int f
);
int CB_index, CB_index1, CB_index1;
int nx1, ndx1, nyy1, ndyy1, nx2, ndx2, ny2, ndy2;
int Fin_set[5][10] = {{53, 54, 56, 59, 61, 62, 65, 37, 68, 68},
		      {68, 68, 68, 67, 67, 67, 67, 66, 66, 66},
	  	      {30, 30, 32, 34, 37, 37, 43, 43, 43, 43},
  		      {175635, 177230, 181001, 179132, 179599, 
		       180339, 180330, 176626, 177760, 179653}};
int  choice1;
long int heli_area[1000];
long int heli_hcog[1000];
long int heli_vcog[1000];
int  no_heli_obj;
long int fin_heli_area;
long int fin_heli_hcog;
long int fin_heli_vcog;
int  heli_index;
int XulBL, YulBL, XbrBL, YbrBL, XulO, YulO, XbrO, YbrO ;
int norm = 5, norm1 = 10;
static int label_count;
static Stack label_stackP;
#endif
