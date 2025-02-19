/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: bandcopy.c
*           Description: copy one image band into another
*         Related Files: Imakefile, libband.a, libmatrix.a
*   Initial Coding Date: Sun May  2 23:21:33 CDT 1993
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
* $Log: bandcopy.c,v $
* Revision 1.3  1998/03/31 03:58:44  achomai
* Cleaned bandcopy :
* 1.  Changed the function definition to ANSI-C style.
* 2.  Changed the structure name from MATRIX to Matrix.
* 3.  Removed the unused local variable, fn.
* 4.  Changed from matrix_fcopy to fastCopy_Matrix.
*
* Revision 1.2  1997/01/16 21:25:54  yawei
* updated changes
*
 * Revision 1.1  1993/05/03  05:53:15  hanceg
 * Initial revision
 *
*
*
****************************************************************************/

#include "stdlib.h"
#include "stdio.h"
#include "CVIPmatrix.h"

/****************************************************************
                   Name: bandcopy
          Expanded Name: Band Copy
             Parameters: <srcBANDS> - pointer to an array of MATRIX pointers
			 <desBANDS> - pointer to an array of MATRIX pointers
			 <no_of_bands> - number of spectral data bands
                Returns: nada
            Description: copy the data pointed to be srcBANDS into that of
			 desBANDS.
	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

void bandcopy(	Matrix	**srcBANDS,
		Matrix	**desBANDS,
		int	no_of_bands)
{
	int		i;

	for(i = 0; i < no_of_bands; i++)
	if(srcBANDS[0]->data_type == desBANDS[0]->data_type)
		(void) fastCopy_Matrix(srcBANDS[i], desBANDS[i]);
	else
		(void) copy_Matrix(srcBANDS[i], desBANDS[i]);
}
