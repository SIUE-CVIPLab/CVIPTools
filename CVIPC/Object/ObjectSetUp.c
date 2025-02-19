/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: ObjectSetUp.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Wed Feb  2 12:42:41 CST 1994
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
** $Log: ObjectSetUp.c,v $
** Revision 1.8  1997/03/08 17:03:25  yawei
** Swaped CVIP_YES and CVIP_NO
**
** Revision 1.7  1997/03/08 00:53:09  yawei
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
** Revision 1.6  1996/11/22 21:02:33  sumbaug
** moved form FEATURE back to OBJECT
**
 * Revision 1.5  1996/11/21  23:21:25  wli
 * Moved to FEATURE from OBJECT.
 *
 * Revision 1.4  1995/12/13  19:03:39  kluo
 * get rid of the message
 *
 * Revision 1.3  1995/12/08  01:43:41  kluo
 * get rid of object file
 *
 * Revision 1.2  1995/12/08  01:33:25  kluo
 * check file into RCS
 *
 * Revision 1.1  1994/10/30  17:58:54  hanceg
 * CVIPtools1.0 source file - G. Hance
 *
*
****************************************************************************/
#include "CVIPtoolkit.h"
#include "CVIPobject.h"

static CVIP_BOOLEAN askYorN_CVIP( void );

static CVIP_BOOLEAN
askYorN_CVIP( void )
{
	char 	buf[80];

	(void) fGetLine_CVIP(stdin, buf);

	if( (*buf == 'y') || (*buf == 'Y') )
		return CVIP_YES;
	else
		return CVIP_NO;
}


Image *
setUpLabel_Objects( const Image *imageP )
{
	Image 		*labelP;
	ObjectList	listP;
	char 		buf[80];

	fflush(stdin);

	listP = label_Objects( (Image *) imageP, &labelP, 0);

        
/*as of December 7, 1995 meeting, we decide not to write disk file
						Kun Luo */
	/*printLabel_Objects(listP, buf);*/

   	delete_LL(listP, delete_Object);

	return labelP;
}

void
setUpProp_Objects( const Image *imageP )
{
	CVIP_BOOLEAN 	ans;
	Image 		*labelP;
	ObjectList	listP;
	char 		buf[80];

	print_CVIP("Has the image already been labelled?");
	if(ans = askYorN_CVIP()) {
		print_CVIP("Enter the object label list file name to read: ");
		(void) fGetLine_CVIP(stdin, buf);
		listP = new_LL();
   		readLabel_Objects(listP, buf);
		labelP = (Image *) imageP;
	}
	else
		listP = label_Objects( (Image *) imageP, &labelP, 0);

	print_CVIP("Enter the object property list file name to write: ");

 	(void) fGetLine_CVIP(stdin, buf);
		
	getProp_Objects( listP, labelP );

   	printProp_Objects( listP, buf );

   	delete_LL( listP, delete_Object );

	if(!ans)
		delete_Image(labelP);

	return;
}
