/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: CVIPxel.h
           Description: include file containing some macros for
			converting from the PBMPLUS data structure
			"pixel" to the CVIPtools data structure "Image";
         Related Files: libconverter.a, Makefile
   Initial Coding Date: 1/24/92
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE
			
****************************************************************************

** Copyright (C) 1991, 1992, 1993 SIUE - by Scott Umbaugh, Greg Hance.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.

RCS (Revision Control System) Information - Added automatically by RCS) 

$Author: yawei $                                                         
$Date: 1997/01/15 17:11:10 $                                                        
$Source: /opt/cvipapps/CVIPtools3.5/include/RCS/CVIPxel.h,v $                                                         
$Header: /opt/cvipapps/CVIPtools3.5/include/RCS/CVIPxel.h,v 1.2 1997/01/15 17:11:10 yawei Exp $

*****************************************************************************/


/****************************************************************
                  Name: PNM_TO_CVIP
         Expanded Name: PNM to CVIP
            Parameters: ppm_pixel_array - array of pointers to
					  pixel structures
			     red_matrix - array of pointers to
					  elements in Image red plane
			   green_matrix - array of pointers to
					  elements in Image green plane
			    blue_matrix - array of pointers to
					  elements in Image blue plane
				   rows - number of rows in image
				   cols - number of columns in image
				   type - legal C type describing the type of data
					  elements being passed.
               Returns: (Nada)
           Description: This macro was written to be used with the PBMPLUS conversion
			library (specifically libpnm.a) The macro will convert
			a matrix of pixel structures (each structure contains a red,
			green and blue component) into three seperate planes which
			can then be incorporated into the CVIPtools Image structure.
			If green_matrix is passed as a NULL pointer then only
			the blue component of the pixel structure will be extracted
			and copied into blue_matrix.
           Diagnostics: (Nada)
             Credit(s): Greg Hance
			
			
****************************************************************/
#define PNM_TO_CVIP(ppm_pixel_array,red_matrix,green_matrix,blue_matrix,rows,cols,type) {  \
                 type **_RMX = (type **)red_matrix; \
		 type **_GMX = (type **)green_matrix; \
		 type **_BMX = (type **)blue_matrix; \
		 type *_PTR; \
		 type *_PTG; \
		 type *_PTB; \
		 pixel *_PIXEL; \
                 int _IX,_JX; \
		 for(_IX = 0 ; _IX < rows ; _IX++) { \
		    _PTB = _BMX[_IX]; \
		    if(_GMX) { \
		       _PTG = _GMX[_IX]; \
		       _PTR = _RMX[_IX]; \
		    } \
		    _PIXEL = (pixel *)ppm_pixel_array[_IX]; \
		    for(_JX = 0 ; _JX < cols ; _JX++) { \
		       if(_GMX) { \
		          *_PTR++ = _PIXEL->r; \
		          *_PTG++ = _PIXEL->g; \
		       } \
		       *_PTB++ = _PIXEL->b; \
		       _PIXEL++; \
		    } \
	         } \
}


/****************************************************************
                  Name: CVIP_TO_PNM
         Expanded Name: CVIP to PNM
            Parameters: ppm_pixel_array - array of pointers to
					  pixel structures
			     red_matrix - array of pointers to
					  elements in Image red plane
			   green_matrix - array of pointers to
					  elements in Image green plane
			    blue_matrix - array of pointers to
					  elements in Image blue plane
				   rows - number of rows in image
				   cols - number of columns in image
				   type - legal C type describing the type of data
					  elements being passed.
               Returns: (Nada)
           Description: This macro was written to be used with the PBMPLUS conversion
			library (specifically libpnm.a) The macro will copy
			the RGB planes of a CVIP Image structure into a matrix of
			PBMPLUS pixel structures.
			If green_matrix is passed as a NULL pointer then only
			the blue component of the pixel structure will be copied
			into blue_matrix.
           Diagnostics: (Nada)
             Credit(s): Greg Hance
			
			
****************************************************************/

#define CVIP_TO_PNM(ppm_pixel_array,red_matrix,green_matrix,blue_matrix,rows,cols,type) {  \
                 type **_RMX = (type **)red_matrix; \
		 type **_GMX = (type **)green_matrix; \
		 type **_BMX = (type **)blue_matrix; \
		 type *_PTR; \
		 type *_PTG; \
		 type *_PTB; \
		 pixel *_PIXEL; \
                 int _IX,_JX; \
		 for(_IX = 0 ; _IX < rows ; _IX++) { \
		    _PTB = _BMX[_IX]; \
		    if(_GMX) { \
		       _PTG = _GMX[_IX]; \
		       _PTR = _RMX[_IX]; \
		    } \
		    _PIXEL = (pixel *)ppm_pixel_array[_IX]; \
		    for(_JX = 0 ; _JX < cols ; _JX++) { \
		       if(_GMX) { \
		          _PIXEL->r = *_PTR++; \
		          _PIXEL->g = *_PTG++; \
		       } \
		       _PIXEL->b = *_PTB++; \
		       _PIXEL++; \
		    } \
	         } \
}

