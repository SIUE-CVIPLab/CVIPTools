/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: ObjectProperties.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Sat Jul 31 15:56:51 CDT 1993
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
** $Log: ObjectProperties.c,v $
** Revision 1.3  1997/03/08 17:03:17  yawei
** Swaped CVIP_YES and CVIP_NO
**
** Revision 1.2  1997/03/08 00:53:00  yawei
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
** Revision 1.1  1994/10/30 17:58:52  hanceg
** CVIPtools1.0 source file - G. Hance
**
*
****************************************************************************/
#include "CVIPtoolkit.h"
#include "CVIPobject.h"
#include "CVIPdef.h"

void getProp_Object(Object *objP, ROI *roiP)
{

   unsigned rows, cols, obj_label, runlength, dcount;
   long *hprojP, *hP, *vprojP, *vP, *dprojP, *dP;
   double m_00=0, m_01=0, m_10=0, m_11=0, m_20=0, m_02=0, u_11=0, u_20=0,
   u_02=0, h_cog, v_cog, eig_ratio, eig_min, eig_max, eig_1, eig_2, eig_arg,
   theta;
   register int i, j;
   byte trans_flag = 0;
   int *rowP;

   rows = getNoOfRows_ROI(roiP); /* number of rows in object region */
   cols = getNoOfCols_ROI(roiP); /* numbre of cols in object region */

   dcount = cols+rows; /* number of potential diagonal projection elements */

   /* horizontal projection array */
   hP = hprojP = (long *) calloc(rows, sizeof(long));
   /* vertical projection array */
   vP = vprojP = (long *) calloc(cols, sizeof(long));
   /* diagonal projection array */
   dP = dprojP = (long *) calloc(dcount, sizeof(long));

   obj_label = objP->label; /* label of the object of interest */

   /* search ROI for pixels marked with object label */

   for(i=0; i < rows; i++, hP++) {
      rowP = (int *) getRow_ROI(roiP, i, 0); /* get next row in ROI */

      for(j=0, trans_flag = 0; j < cols; j++, rowP++)
         if( (*rowP == obj_label) ^ (trans_flag & 0x01) ) {
            if(trans_flag) {
               *hP += runlength;
               vP[j]--;
	       dP[i+j]--;
	    }
	    else {
	       vP[j]++;
	       dP[i+j]++;
	    }
	    trans_flag = ~trans_flag;
            runlength = 1;
         }
	 else
	    runlength++;

      if(trans_flag) {
         *hP += runlength;
	 dP[i+j]--;
      }

   }

  /*
   * Based on the horizontal projection data calculate:
   * m_00  -- the zero-order spatial moment
   * m_01  -- the first-order column moment
   * v_cog -- the vertical center of gravity (centroid)
   * m_02  -- the second-order column moment of interia
   * u_02  -- the second-order column central moment of intertia
   */

   for(i = 0, hP = hprojP; i < rows; i++, hP++) {
      m_00 += (double) *hP;
      m_01 += i * (*hP);
      m_02 += i * i * (*hP);
   }
   v_cog = m_01/m_00;
   u_02 = m_02 - m_00*v_cog*v_cog;

  /*
   * Based on the vertical projection data calculate:
   * m_10  -- the first-order row moment
   * h_cog -- the horizontal center of gravity (centroid)
   * m_20  -- the second-order row moment of interia
   * u_20  -- the second-order row central moment of intertia
   */

   for(j = 1, vP = &vprojP[1]; j < cols; j++, vP++) {
      *vP += *(vP-1);
      m_10 += j * (*vP);
      m_20 += j * j * (*vP);
   }
   h_cog = m_10/m_00;
   u_20 = m_20 - m_00*h_cog*h_cog;

  /*
   * Based on the diagonal projection data calculate:
   * m_11  -- the row-column cross moment of inertia
   * u_11  -- the row-column cross central moment of inertia
   */

   for(i = 1, dP = &dprojP[1]; i < dcount; i++, dP++) {
      *dP += *(dP-1);
      m_11 += i * i * (*dP);
   }
   m_11 = (m_11-m_20-m_02)/2;
   u_11 = m_11 - m_00*v_cog*h_cog;

  /* Based on the second order central moments we can explicitly calulate:
   * eig_1, eig_2 -- the eigenvalues of the moment of interia covariance matrix
   * theta - the orientation angle of the object
   */

   eig_arg = u_20*u_20 + u_02*u_02 - 2*u_20*u_02 + 4*u_11*u_11;
   eig_1 = ((u_20+u_02) + sqrt(eig_arg))/2.0;
   eig_2 = ((u_20+u_02) - sqrt(eig_arg))/2.0;
   eig_max = MAX(eig_1,eig_2);
   eig_min = MIN(eig_1,eig_2);
   eig_ratio = (eig_max) ? (eig_min/eig_max) : 1.0;
      
   if(u_02 == eig_max)
      theta = PIOVER2;
   else
      theta = atan(u_11/(u_02-eig_max));
   theta *= RTOD;  /* convert radians to degrees */

   objP->prop.area = m_00;
   objP->prop.h_cog = h_cog + getHorOffset_ROI(roiP);
   objP->prop.v_cog = v_cog + getVerOffset_ROI(roiP);
   objP->prop.orientation = theta;
   objP->prop.eig_ratio = eig_ratio;

   free(hprojP);  
   free(vprojP);
   free(dprojP);
}

void getProp_Objects(ObjectList listP, Image *labelP)
{
   ROI *roiP;
   Object *objP;
   const char *fn = "getProp";

   head_LL(listP);

   msg_CVIP(fn, "calculating object properties...\n");
   msg_CVIP(fn, "examining object   1.");

   for(;;) {
      roiP = new_ROI();
      objP = (Object *) retrieve_LL(listP);
      print_CVIP("\b\b\b\b%3d.", objP->label);
      asgnImage_ROI(roiP, labelP, objP->x_min, objP->y_min,
      objP->x_max - objP->x_min + 1, objP->y_max - objP->y_min + 1);
      getProp_Object(objP, roiP);
      delete_ROI(roiP);
      if (istail_LL(listP)) break;
      next_LL(listP);
   }

print_CVIP("\n");
}


void printProp_Object( void *thisP, FILE *fileP)
{
   Object *objectP = thisP;


   fprintf(fileP,"### label ### :\t%3d\n", objectP->label);
   fprintf(fileP,"red component :\t%3d\n", objectP->pixel.r);
   fprintf(fileP,"grn component :\t%3d\n", objectP->pixel.g);
   fprintf(fileP,"blu component :\t%3d\n", objectP->pixel.b);
   fprintf(fileP,"object min x :\t%3ld\n", objectP->x_min);
   fprintf(fileP,"object max x :\t%3ld\n",  objectP->x_max);
   fprintf(fileP,"object min y :\t%3ld\n",  objectP->y_min);
   fprintf(fileP,"object max y :\t%3ld\n",  objectP->y_max);
   fprintf(fileP,"zero-order moment (area) : %.6f\n",objectP->prop.area);
   fprintf(fileP,"horizontal center of gravity : %.6f\n",objectP->prop.h_cog);
   fprintf(fileP,"vertical center of gravity : %.6f\n",objectP->prop.v_cog);
   fprintf(fileP,"orientation angle (degrees) : %.6f\n",objectP->prop.orientation);
   fprintf(fileP,"eigenvalue ratio : %.6f\n",objectP->prop.eig_ratio);

}

void printProp_Objects(ObjectList listP, const char *name)
{

	FILE *fileP;
   
	fileP = openWrite_CVIP(name, CVIP_NO);

	fprintf(fileP, "Total Number of Objects : %d\n", size_LL(listP));
	print_LL(listP, printProp_Object, fileP);

	close_CVIP(fileP);
}


static int readProp_Object( void *thisP, FILE *fileP)
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

	objP->prop.area = fGetFloat_CVIP(fileP, &status, 2, ":");
		if(!status) return 0;

	objP->prop.h_cog = fGetFloat_CVIP(fileP, &status, 2, ":");
		if(!status) return 0;

	objP->prop.v_cog = fGetFloat_CVIP(fileP, &status, 2, ":");
		if(!status) return 0;

	objP->prop.orientation = fGetFloat_CVIP(fileP, &status, 2, ":");
		if(!status) return 0;

	objP->prop.eig_ratio = fGetFloat_CVIP(fileP, &status,  2, ":");
		if(!status) return 0;

	return 1;
}



int readProp_Objects( ObjectList listP, const char *name )
{

	FILE *fileP;
	long no_of_objects;
	Object *objP;
	const char *fn = "readProp_Objects";
	int status;
  
	fileP = openRead_CVIP(name);

	no_of_objects = fGetInt_CVIP(fileP, &status, 2, ":");
	if(!status) {
		error_CVIP(fn, "problem reading objects from %s\n", name);
		return 0;
	}

	if(!isempty_LL(listP)) {
		error_CVIP(fn, "object list must be empty\n");
		return 0;
	}

	listP->clP = listP->headP;

	for(;;) {
		objP = (Object *) malloc(sizeof(Object));
		if(!readProp_Object(objP,fileP)) {
			free(objP);
			break;
		}
		addnext_LL(listP, objP);
	}

	if(no_of_objects != size_LL(listP)) {
		error_CVIP(fn, "problem reading objects from %s\n", name);
		return 0;
	}

	close_CVIP(fileP);
	return 1;
}
