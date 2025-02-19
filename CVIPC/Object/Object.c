/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: Object.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Sat Jul 31 17:04:54 CDT 1993
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
** $Log: Object.c,v $
** Revision 1.3  1996/11/22 21:01:36  sumbaug
** moved form FEATURE back to OBJECT
**
 * Revision 1.2  1996/11/21  23:06:51  wli
 * Moved to FEATURE from OBJECT.
 *
 * Revision 1.1  1994/10/30  17:58:51  hanceg
 * CVIPtools1.0 source file - G. Hance
 *
*
****************************************************************************/
#include "CVIPtoolkit.h"
#include "CVIPdef.h"
#include "Object.h"

/****************************************************************
                   Name: new_Object
          Expanded Name: new object
             Parameters: <label_count> - object label
			 <pixel> - color of the object
			 <y_pos> - vertical position of upper left corner
			 <x_pos> - horizontal position of upper left corner
                Returns: pointer to new initialized object
            Description: constructor for object class
	    Diagnostics: none
             References: none
              Author(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

Object *new_Object(int label_count, Color pixel, int y_pos, int x_pos)
{  

   Object *newobjP = (Object *) malloc(sizeof(Object));
   newobjP->pixel = pixel;
   newobjP->label = label_count;

   newobjP->x_min = x_pos;
   newobjP->x_max = x_pos;

   newobjP->y_min = y_pos;
   newobjP->y_max = y_pos;

   return newobjP;

}


/****************************************************************
                   Name: print_Object
          Expanded Name: print object
             Parameters: <thisP> -pointer to object
			 <fileP> - file pointer
                Returns: nothing
            Description: prints the contents of an object structure
	    Diagnostics: none
             References: none
              Author(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

void print_Object( void *thisP, FILE *fileP)
{
   Object *objectP = thisP;

   fprintf(fileP,"*** label *** :\t%3d\n", objectP->label);
   fprintf(fileP,"red component :\t%3d\n", objectP->pixel.r);
   fprintf(fileP,"grn component :\t%3d\n", objectP->pixel.g);
   fprintf(fileP,"blu component :\t%3d\n", objectP->pixel.b);
   fprintf(fileP,"object min x  :\t%3ld\n", objectP->x_min);
   fprintf(fileP,"object max x  :\t%3ld\n",  objectP->x_max);
   fprintf(fileP,"object min y  :\t%3ld\n",  objectP->y_min);
   fprintf(fileP,"object max y  :\t%3ld\n",  objectP->y_max);

}


/****************************************************************
                   Name: read_Object
          Expanded Name: read object
             Parameters: <thisP> - pointer to object
			 <fileP> - file pointer
                Returns: integer error status (0 or 1)
            Description: reads an object description from a file
	    Diagnostics: returns 0 upon failure to read
             References: none
              Author(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

int read_Object( void *thisP, FILE *fileP)
{
	Object *objP = thisP;
	int status;

	objP->label = fGetInt_CVIP(fileP, &status, 2, ":");
		if(!status) return 0;

	objP->pixel.r = fGetInt_CVIP(fileP, &status, 2, ":");
		if(!status) return 0;

	objP->pixel.g = fGetInt_CVIP(fileP, &status, 2, ":");
		if(!status) return 0;

	objP->pixel.b = fGetInt_CVIP(fileP, &status, 2, ":");
		if(!status) return 0;

	objP->x_min = fGetInt_CVIP(fileP, &status, 2, ":");
		if(!status) return 0;

	objP->x_max = fGetInt_CVIP(fileP, &status, 2, ":");
		if(!status) return 0;

	objP->y_min = fGetInt_CVIP(fileP, &status, 2, ":");
		if(!status) return 0;

	objP->y_max = fGetInt_CVIP(fileP, &status, 2, ":");
		if(!status) return 0;

	return 1;
}



/****************************************************************
                   Name: delete_Object
          Expanded Name: delete object
             Parameters: <objectP> - pointer to Object structure
                Returns: nothing
            Description: detroys an instance of an object structure
	    Diagnostics: none
             References: none
              Author(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

void delete_Object(void *objectP)
{
   free(objectP);
}


/****************************************************************
                   Name: match_Object
          Expanded Name: match object
             Parameters: <objectP> - pointer to object structure
			 <labelP> - pointer to label to match (int)
                Returns: 0 or 1
            Description: returns 1 for a match and 0 otherwise
	    Diagnostics: none
             References: none
              Author(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

int match_Object(void *objectP, void *labelP)
{ 
   return ((Object *) objectP)->label == *((int *) labelP);
}


/****************************************************************
                   Name: drawBB_Objects
          Expanded Name: draw bounding box objects
             Parameters: <imageP> - pointer to Image structure
			 <listP> - pointer to object list
                Returns: nothing
            Description: draws a bounding box around each box corresponding
			 to each object in the list
	    Diagnostics: none
             References: none
              Author(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

void drawBB_Objects(Image *imageP, ObjectList listP)
{
   ROI *roiP;
   Object *objP;

   head_LL(listP);
   
   for(;;) {
      roiP = new_ROI();
      objP = (Object *) retrieve_LL(listP);
      asgnImage_ROI(roiP, imageP, objP->x_min, objP->y_min,
      objP->x_max - objP->x_min + 1, objP->y_max - objP->y_min + 1);
      drawBox_GP(roiP);
      delete_ROI(roiP);
      if (istail_LL(listP)) break;
      next_LL(listP);
   }
}




/****************************************************************
                   Name: 
          Expanded Name:
             Parameters:
                Returns:
            Description:
	    Diagnostics:
             References:
              Author(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

int
shootRay( 
	Image *imageP,
	int elev,
	int *ray_x, 
	int *ray_y,
	int x1, 
	int y1, 
	int x2, 
	int y2
)
{
    int d, x, y, ax, ay, sx, sy, dx, dy;
    register int i;

    dx = x2-x1;  ax = ABS(dx)<<1;  sx = SGN(dx);
    dy = y2-y1;  ay = ABS(dy)<<1;  sy = SGN(dy);

    x = x1;
    y = y1;
    if (ax>ay) {		/* x dominant */
	d = ay-(ax>>1);
	for (;;) {
	    if(getPixel_Image(imageP,int,x,y,0) == elev) {
	       *ray_x = x;
	       *ray_y = y;
	       return 1;
	    }
	    if (x==x2) return 0;
	    if (d>=0) {
		y += sy;
		d -= ax;
	    }
	    x += sx;
	    d += ay;
	}
    }
    else {			/* y dominant */
	d = ax-(ay>>1);
	for (;;) {
	    if(getPixel_Image(imageP,int,x,y,0) == elev) {
	       *ray_x = x;
	       *ray_y = y;
	       return 1;
	    }
	    if (y==y2) return 0;
	    if (d>=0) {
		x += sx;
		d -= ay;
	    }
	    y += sy;
	    d += ax;
	}
    }
}
