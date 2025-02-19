/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: cxform_setup.c
*           Description: contains set-up modules used with the main CVIPtools
*			 user interface.
*         Related Files: CVIPcolor.h, Imakefile
*   Initial Coding Date: Sun May 30 14:48:03 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Gregory Hance
*                        Southern Illinois University @ Edwardsville
*
*  Global Function List: cxform_dispatch - interface module to CVIPtools CLI.
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
** $Log: cxform_setup.c,v $
** Revision 1.6  1997/03/08 17:06:08  yawei
** Swaped CVIP_YES and CVIP_NO
**
** Revision 1.5  1997/03/08 00:59:01  yawei
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
** Revision 1.4  1997/01/15 17:17:25  yawei
** Global Change:  IMAGE ==> Image
**
 * Revision 1.3  1995/04/22  22:00:38  luok
 * make file conform with new menu
 *
 * Revision 1.2  1995/04/22  21:52:27  luok
 * check file into RCS.
 *
 * Revision 1.1  1993/05/31  03:23:40  hanceg
 * Initial revision
 *
*
****************************************************************************/
#include "CVIPdef.h"
#include "CVIPtoolkit.h"
#include "CVIPcolor.h"

/* local functions */
static Image *HSLsetup(const Image *srcImage, CVIP_BOOLEAN *remapg);
static Image *HSVsetup(const Image *srcImage, CVIP_BOOLEAN *remapg);
static Image *XYZsetup(const Image *srcImage, CVIP_BOOLEAN *remapg);
static Image *SCTsetup(const Image *srcImage, CVIP_BOOLEAN *remapg);
static Image *LUVsetup(const Image *srcImage, CVIP_BOOLEAN *remapg);
static Image *LABsetup(const Image *srcImage, CVIP_BOOLEAN *remapg);
static Image *CCTsetup(const Image *srcImage, CVIP_BOOLEAN *remapg);



/****************************************************************
                   Name: HSLsetup
          Expanded Name: HSL set-up routine
             Parameters: <srcImage> - pointer to source image
			 <remapg> - holds the value of the global mapping scheme
                Returns: pointer to an Image structure.
            Description: asks the user a few questions.
	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/
   
static Image *HSLsetup(const Image *srcImage, CVIP_BOOLEAN *remapg)
{
const char *fn = "hsl";
char *uinput;
int choice, dir;
float *normvec;
CVIP_BOOLEAN remapl = 0;
Image *xformImage;

uinput = (char *) malloc(30);
normvec = (float *) malloc(3*sizeof(float));

fprintf(stderr, "%s: (1) RGB -> HSL\n", fn);
fprintf(stderr, "%s: (2) HSL -> RGB\n", fn);
fprintf(stderr, "%s: Choose (1 or 2)?", fn);
choice = atoi(gets(uinput));

if(choice == 1) {
   dir = 1;
   fprintf(stderr, "%s: This operation requires an image normalized between [0 ... 1].\n", fn);
   fprintf(stderr, "%s: is the image normalized?", fn);
   (void) gets(uinput);
   if(*uinput == 'y' || *uinput == 'Y')
      normvec = NULL;
   else
      normvec[0] = normvec[1] = normvec[2] = 255.0;
   fprintf(stderr, "%s: Do you wish to 1) re-map the image for display only or 2) retain the\n", fn);
   fprintf(stderr, "%s: re-mapped image within the queue.\n", fn);
   fprintf(stderr, "%s: Choose (1 or 2)?", fn);
   choice = atoi(gets(uinput));
   if(choice == 1) *remapg = CVIP_YES;
   else *remapg = CVIP_NO;
   xformImage = colorxform(srcImage, HSL, normvec, NULL, 1);
}
else {
   fprintf(stderr, "%s: This operation requires an HSL image normalized between [0 ... 1].\n", fn);
   fprintf(stderr, "%s: proceed... (y) or (n)?", fn);
   (void) gets(uinput);
   if(*uinput == 'n' || *uinput == 'N')
      return NULL;
   else
      xformImage = colorxform(srcImage, HSL, NULL, NULL, -1);
}
   free(uinput);
   free(normvec);

return xformImage;
}


/****************************************************************
                   Name: HSVsetup
          Expanded Name: HSV set-up routine
             Parameters: <srcImage> - pointer to source image
			 <remapg> - holds the value of the global mapping scheme
                Returns: pointer to an Image structure.
            Description: asks the user a few questions.
	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

static Image *HSVsetup(const Image *srcImage, CVIP_BOOLEAN *remapg)
{
const char *fn = "hsv";
char *uinput;
int choice, dir;
float *normvec;
CVIP_BOOLEAN remapl = 0;
Image *xformImage;

uinput = (char *) malloc(30);
normvec = (float *) malloc(3*sizeof(float));

fprintf(stderr, "%s: (1) RGB -> HSV\n", fn);
fprintf(stderr, "%s: (2) HSV -> RGB\n", fn);
fprintf(stderr, "%s: Choose (1 or 2)?", fn);
choice = atoi(gets(uinput));

if(choice == 1) {
   dir = 1;
   fprintf(stderr, "%s: This operation requires an image normalized between [0 ... 1].\n", fn);
   fprintf(stderr, "%s: is the image normalized?", fn);
   (void) gets(uinput);
   if(*uinput == 'y' || *uinput == 'Y')
      normvec = NULL;
   else
      normvec[0] = normvec[1] = normvec[2] = 255.0;
   fprintf(stderr, "%s: Do you wish to 1) re-map the image for display only or 2) retain the\n", fn);
   fprintf(stderr, "%s: re-mapped image within the queue.\n", fn);
   fprintf(stderr, "%s: Choose (1 or 2)?", fn);
   choice = atoi(gets(uinput));
   if(choice == 1) *remapg = CVIP_YES;
   else  *remapg = CVIP_NO;
   xformImage = colorxform(srcImage, HSV, normvec, NULL, 1);
}
else {
   fprintf(stderr, "%s: This operation requires an HSV image normalized between [0 ... 1].\n", fn);
   fprintf(stderr, "%s: proceed... (y) or (n)?", fn);
   (void) gets(uinput);
   if(*uinput == 'n' || *uinput == 'N')
      return NULL;
   else
      xformImage = colorxform(srcImage, HSV, NULL, NULL, -1);
}

   free(uinput);
   free(normvec);

return xformImage;
}


/****************************************************************
                   Name: XYZsetup
          Expanded Name: XYZ set-up routine
             Parameters: <srcImage> - pointer to source image
			 <remapg> - holds the value of the global mapping scheme
                Returns: pointer to an Image structure.
            Description: asks the user a few questions.
	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

static Image *XYZsetup(const Image *srcImage, CVIP_BOOLEAN *remapg)
{
const char *fn = "XYZ";
char *uinput;
int choice;
CVIP_BOOLEAN remapl = 0;
Image *xformImage;

uinput = (char *) malloc(30);

   fprintf(stderr, "%s: Do you wish to 1) re-map the image for display only or 2) retain the\n", fn);
   fprintf(stderr, "%s: re-mapped image within the queue.\n", fn);
   fprintf(stderr, "%s: Choose (1 or 2)?", fn);
   choice = atoi(gets(uinput));
   if(choice == 1) *remapg = CVIP_YES;
   else  *remapg = CVIP_NO;
   xformImage = colorxform(srcImage, XYZ, NULL, NULL, 1);

   free(uinput);

return xformImage;
}


/****************************************************************
                   Name: SCTsetup
          Expanded Name: SCT set-up routine
             Parameters: <srcImage> - pointer to source image
			 <remapg> - holds the value of the global mapping scheme
                Returns: pointer to an Image structure.
            Description: asks the user a few questions.
	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

static Image *SCTsetup(const Image *srcImage, CVIP_BOOLEAN *remapg)
{
const char *fn = "sct";
char *uinput;
int choice, dir, i = 0;
float *normvec, **normout;
CVIP_BOOLEAN remapl = 0;
Image *xformImage;
unsigned int imgsize;

uinput = (char *) malloc(30);
normvec = (float *) malloc(3*sizeof(float));


   fprintf(stderr, "%s: This operation requires an image normalized between [0 ... 1].\n", fn);
   fprintf(stderr, "%s: is the image normalized?", fn);
   (void) gets(uinput);
   if(*uinput == 'y' || *uinput == 'Y')
      normvec = NULL;
   else
      normvec[0] = normvec[1] = normvec[2] = 255.0;
   fprintf(stderr, "%s: Do you wish to 1) re-map the image for display only or 2) retain the\n", fn);
   fprintf(stderr, "%s: re-mapped image within the queue.\n", fn);
   fprintf(stderr, "%s: Choose (1 or 2)?", fn);
   choice = atoi(gets(uinput));
   if(choice == 1) *remapg = CVIP_YES;
   else *remapg = CVIP_NO;
   xformImage = colorxform(srcImage, SCT, normvec, NULL, 1);

   fprintf(stderr, "%s: normalizing resultant image...\n", fn); 
   normout = (float **) malloc(3*sizeof(float *));
   for(; i < xformImage->bands; i++)
      normout[i] = (float *) xformImage->bandP[i]->rptr[0];
   normvec[0] = 1.7320508; /* normalize between 0 and 1 */
   normvec[1] = (PI/2.0);
   normvec[2] = (PI/2.0);
   imgsize = (xformImage->bandP[0]->rows)*(xformImage->bandP[0]->cols);
   (void) vecnorm(normout, normvec, CVIP_FLOAT, 3, imgsize);

   free(uinput);
   free(normvec);
   free(normout);

return xformImage;
}



/****************************************************************
                   Name: CCTsetup
          Expanded Name: CCT set-up routine
             Parameters: <srcImage> - pointer to source image
			 <remapg> - holds the value of the global mapping scheme
                Returns: pointer to an Image structure.
            Description: asks the user a few questions.
	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

static Image *CCTsetup(const Image *srcImage, CVIP_BOOLEAN *remapg)
{
const char *fn = "cct";
char *uinput;
int choice, dir, i = 0;
float *normvec, **normout;
CVIP_BOOLEAN remapl = 0;
Image *xformImage;
unsigned int imgsize;

uinput = (char *) malloc(30);
normvec = (float *) malloc(3*sizeof(float));


   fprintf(stderr, "%s: This operation requires an image normalized between [0 ... 1].\n", fn);
   fprintf(stderr, "%s: is the image normalized?", fn);
   (void) gets(uinput);
   if(*uinput == 'y' || *uinput == 'Y')
      normvec = NULL;
   else
      normvec[0] = normvec[1] = normvec[2] = 255.0;
   fprintf(stderr, "%s: Do you wish to 1) re-map the image for display only or 2) retain the\n", fn);
   fprintf(stderr, "%s: re-mapped image within the queue.\n", fn);
   fprintf(stderr, "%s: Choose (1 or 2)?", fn);
   choice = atoi(gets(uinput));
   if(choice == 1) *remapg = CVIP_YES;
   else *remapg = CVIP_NO;
   xformImage = colorxform(srcImage, CCT, normvec, NULL, 1);

   fprintf(stderr, "%s: normalizing resultant image...\n", fn); 
   normout = (float **) malloc(2*sizeof(float *));
   for(; i < 2; i++)
      normout[i] = (float *) xformImage->bandP[i]->rptr[0];
   normvec[0] = 1.4142136; /* normalize between 0 and 1 */
   normvec[1] = (PI/2.0);
   imgsize = (xformImage->bandP[0]->rows)*(xformImage->bandP[0]->cols);
   (void) vecnorm(normout, normvec, CVIP_FLOAT, 2, imgsize);

   free(uinput);
   free(normvec);
   free(normout);

return xformImage;
}
                

/****************************************************************
                   Name: LUVsetup
          Expanded Name: LUV se-up routine
             Parameters: <srcImage> - pointer to source image
			 <remapg> - holds the value of the global mapping scheme
                Returns: pointer to an Image structure.
            Description: asks the user a few questions.
	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

static Image *LUVsetup(const Image *srcImage, CVIP_BOOLEAN *remapg)
{
const char *fn = "Luv";
char *uinput;
int choice, dir, i = 0;
float *normvec, *refwhite;
CVIP_BOOLEAN remapl = 0;
Image *xformImage;
unsigned int imgsize;

uinput = (char *) malloc(30);
normvec = (float *) malloc(3*sizeof(float));
refwhite = (float *) malloc(3*sizeof(float));


   fprintf(stderr, "%s: This operation requires an image normalized between [0 ... 1].\n", fn);
   fprintf(stderr, "%s: is the image normalized?", fn);
   (void) gets(uinput);
   if(*uinput == 'y' || *uinput == 'Y')
      normvec = NULL;
   else
      normvec[0] = normvec[1] = normvec[2] = 255.0;
   fprintf(stderr, "%s: Do you wish to 1) re-map the image for display only or 2) retain the\n", fn);
   fprintf(stderr, "%s: re-mapped image within the queue.\n", fn);
   fprintf(stderr, "%s: Choose (1 or 2)?", fn);
   choice = atoi(gets(uinput));
   if(choice == 1) *remapg = CVIP_YES;
   else *remapg = CVIP_NO;
   refwhite[0] = refwhite[1] = refwhite[2] = 1.0;
   xformImage = colorxform(srcImage, LUV, normvec, refwhite, 1);

   free(uinput);
   free(normvec);
   free(refwhite);

return xformImage;
}


/****************************************************************
                   Name: LABsetup
          Expanded Name: LAB se-up routine
             Parameters: <srcImage> - pointer to source image
			 <remapg> - holds the value of the global mapping scheme
                Returns: pointer to an Image structure.
            Description: asks the user a few questions.
	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

static Image *LABsetup(const Image *srcImage, CVIP_BOOLEAN *remapg)
{
const char *fn = "Lab";
char *uinput;
int choice, dir, i = 0;
float *normvec, *refwhite;
CVIP_BOOLEAN remapl = 0;
Image *xformImage;
unsigned int imgsize;

uinput = (char *) malloc(30);
normvec = (float *) malloc(3*sizeof(float));
refwhite = (float *) malloc(3*sizeof(float));


   fprintf(stderr, "%s: This operation requires an image normalized between [0 ... 1].\n", fn);
   fprintf(stderr, "%s: is the image normalized?", fn);
   (void) gets(uinput);
   if(*uinput == 'y' || *uinput == 'Y')
      normvec = NULL;
   else
      normvec[0] = normvec[1] = normvec[2] = 255.0;
   fprintf(stderr, "%s: Do you wish to 1) re-map the image for display only or 2) retain the\n", fn);
   fprintf(stderr, "%s: re-mapped image within the queue.\n", fn);
   fprintf(stderr, "%s: Choose (1 or 2)?", fn);
   choice = atoi(gets(uinput));
   if(choice == 1) *remapg = CVIP_YES;
   else *remapg = CVIP_NO;
   refwhite[0] = refwhite[1] = refwhite[2] = 1.0;
   xformImage = colorxform(srcImage, LAB, normvec, refwhite, 1);

   free(uinput);
   free(normvec);
   free(refwhite);

return xformImage;
}


/****************************************************************
                   Name: cxform_dispatch
          Expanded Name: color transform dispatch
             Parameters: <srcImage> - pointer to source image
			 <choice> - number of color transform to perform
			 <remapg> - holds the value of the global mapping scheme
                Returns: pointer to an Image structure.
            Description: interface module to CVIPtools user interface.
	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

Image *cxform_dispatch(Image *srcImage, unsigned int choice, CVIP_BOOLEAN *remapg)
{
   Image *(* csetup[])(const Image *, CVIP_BOOLEAN *) = { NULL, NULL, NULL, HSLsetup, HSVsetup, SCTsetup,
                                               CCTsetup, LUVsetup, LABsetup, XYZsetup };
   char *fn = "cxform";
   Image *cxformImage, *freeImage;

   fprintf(stderr, "\n");
   if( choice > 9 || choice < 1 ) {
      *remapg = CVIP_NO;
      fprintf(stderr, "%s-ERROR: %d is an invalid selection.\n", fn, choice);
      return NULL;
   }
   else {
      if(choice==1) {
         *remapg = CVIP_NO;
         fprintf(stderr, "%s: only HSL and HSV support transforms back into RGB space.\n", fn);
         return NULL;
      }
      else 
         cxformImage = (csetup[choice])(srcImage, remapg);
   }

   if(!(*remapg)) {
      freeImage = cxformImage;
      cxformImage = (Image *) remapp(cxformImage, CVIP_BYTE, 255);
      image_free(freeImage);
   }
   fprintf(stderr, "\n");

return cxformImage;
}

