/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: TrimList.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Sun Sep 19 18:48:04 CDT 1993
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
** $Log: TrimList.c,v $
** Revision 1.3  1997/03/08 17:03:23  yawei
** Swaped CVIP_YES and CVIP_NO
**
** Revision 1.2  1997/03/08 00:53:06  yawei
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
** Revision 1.1  1994/10/30 17:58:53  hanceg
** CVIPtools1.0 source file - G. Hance
**
*
****************************************************************************/
#include "CVIPtoolkit.h"
#include "CVIPobject.h"
#include "CVIPdef.h"

int
trimList_Objects(
	ObjectList listP,
	unsigned width,
	unsigned height,
	float p_area_min,
	float p_area_max,
	float eig_r_min,
	float eig_r_max,
	float angle_min,
	float angle_max,
	float p_width,
	float p_height,
	CVIP_BOOLEAN no_edge
)
{
	const char *fn = "trimList_Objects";
	float area_min, area_max;
	Object *objP;
	CVIP_BOOLEAN mark_for_del;

	if(isempty_LL(listP)) {
		error_CVIP(fn, "can not trim empty list");
		return 0;
	}

	area_min = ROUND(p_area_min*width*height);
	area_max = ROUND(p_area_max*width*height);
	
	head_LL(listP);
	previous_LL(listP);

	for (;;) {
		mark_for_del = CVIP_NO;
        	objP = retrieveNext_LL(listP);

		if((objP->prop.area < area_min) || (objP->prop.area > area_max))
			mark_for_del = CVIP_YES;
		else if((objP->prop.eig_ratio < eig_r_min) || 
		(objP->prop.eig_ratio > eig_r_max) )
			mark_for_del = CVIP_YES;
		else if((objP->prop.orientation < angle_min) || 
		(objP->prop.orientation > angle_max) )
			mark_for_del = CVIP_YES;
		else if(no_edge)
			if(	(objP->x_min == 0) ||
				(objP->y_min == 0) ||
				(objP->x_max == (width-1)) ||
				(objP->y_max == (height-1))
			)
				mark_for_del = CVIP_YES;

		if(mark_for_del)
			removenext_LL(listP);
		else
			next_LL(listP);

		if (istail_LL(listP)) break;
	}

	return 1;
}

