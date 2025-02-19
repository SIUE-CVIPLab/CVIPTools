/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: ROI.c
*           Description: Region of interest routines for the CVIPtools
*			 toolkit library -- libroi.a.
*         Related Files: Imakefile, ROI.h, CVIProi.h
*   Initial Coding Date: Tue Jul 20 17:39:24 CDT 1993
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
** $Log: ROI.c,v $
** Revision 1.1  1994/10/30 17:58:54  hanceg
** CVIPtools1.0 source file - G. Hance
**
*
****************************************************************************/
#include "CVIPtoolkit.h"
#include "CVIProi.h"

ROI *new_ROI(void) 
{ 
   return((ROI *) malloc(sizeof(ROI)));
}


void delete_ROI(ROI *roiP) 
{ 
   free(roiP);
}


void asgnImage_ROI(
	ROI *roiP,
	Image *imageP,
	unsigned x, 
	unsigned y, 
	unsigned dx, 
	unsigned dy)
{
   roiP->x = x;
   roiP->y = y;
   roiP->dx = dx;
   roiP->dy = dy;

   roiP->dataP = imageP;

}


         
