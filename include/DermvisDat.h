/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: DermvisDat.h
*           Description: 
*         Related Files: 
*   Initial Coding Date: Sat Sep 18 17:23:31 CDT 1993
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
** $Log: DermvisDat.h,v $
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
*
****************************************************************************/
#if !defined( DERMVISDAT_DEFINED )

	#define DERMVISDAT_DEFINED

	struct UMR_BorderDataType {
		char border[80]; /* border determined by */
		char date[80]; /* date determined */
		double perimeter; /* perimeter */
		long integer_perimeter; /* integer perimeter */
		long area_upper_bound; /* area upper bound */
		double upper_bound_irr; /* upper bound for irregularity */
		double span_for_irr; /* span for irregularity */
		double assymetry_index; /* assymetry index */
		double avg_tumor_red; /* average tumor red */
		double avg_tumor_grn; /* average tumor green */
		double avg_tumor_blu; /* average tumor blue */
		double avg_skin_red; /* average skin red */
		double avg_skin_grn; /* average skin green */
		double avg_skin_blu; /* average skin blue */
		double var_tumor_red; /* variance of red in tumor */
		double var_tumor_grn; /* variance of green in tumor */
		double var_tumor_blu; /* variance of blue in tumor */
		double var_skin_red; /* variance of red in tumor */
		double var_skin_grn; /* variance of green in skin */
		double var_skin_blu; /* variance of blue in skin */
		long tumor_min_x; /* tumor min x */
		long tumor_max_x; /* tumor max x */
		long tumor_min_y; /* tumor min y */
		long tumor_max_y; /* tumor max y */
		double rel_red_chrom; /* relative red chromaticity */
		double rel_grn_chrom; /* relative green chromaticity */
		double rel_blu_chrom; /* relative blue chromaticity */
		double sph_length; /* spherical co-ordinates length of tumor color */
		double sph_angle_a; /* spherical co-ordinates angle A of tumor color (degrees) */
		double sph_angle_b; /* spherical co-ordinates angle B of tumor color (degrees) */
		double avg_bright; /* average brightness in tumor */
		double avg_hue; /* average hue in tumor (degrees) */
		double avg_chroma; /* average chroma in tumor  */
	};

	typedef struct UMR_BorderDataType UMR_BorderData;

extern int write_UMR_BorderData(UMR_BorderData *bdP, const char *file_name);
extern int read_UMR_BorderData(UMR_BorderData *bdP, const char *file_name);

#endif /* DERMVISDAT_DEFINED */
