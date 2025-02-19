/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: label.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Fri Nov 22 14:16:07 CST 1996
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Scott Umbaugh
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1996 SIUE - by Scott Umbaugh, Kun Luo, Greg Hance
**                           and Wenxing  Li 
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
****************************************************************************/
/*

   This is a copy of function:

     Image * setUpLabel_Objects( const Image * imageP );

   which is in OBJECT/ObjectSetUp.c


-- wli
*/ 


#include "CVIPtoolkit.h"
#include "CVIPobject.h"


extern ObjectList label_Objects( Image *, Image **, unsigned);


Image *
label( const Image *imageP )
{
        Image           *labelP;
        ObjectList      listP;
        //char            buf[80];

        fflush(stdin);

        listP = label_Objects( (Image *) imageP, &labelP, 0);
	if(listP == NULL ) {
		printf("Too many objects on labeling\n");
		return NULL;
	}


/*as of December 7, 1995 meeting, we decide not to write disk file
                                                Kun Luo */
        /*printLabel_Objects(listP, buf);*/

        delete_LL(listP, delete_Object);
	//free(listP);

        return labelP;
}
