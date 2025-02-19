/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: pct.c
*           Description: contains all of the necessary modules to perform
*			 a principal components transform.
*         Related Files: pct.h, Imakefile
*   Initial Coding Date: Sun May 30 14:48:13 CDT 1993
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
** $Log: pct.c,v $
** Revision 1.16  2000/01/23 01:55:04  rswamis
** this is actually revision 1.13; it is 1.14 with the includes
** header files:   m_CovEig.h
**
** Revision 1.13  1997/07/24 18:40:26  smakam
** made the pct inverse transform work
**
** Revision 1.12  1997/03/08 17:05:59  yawei
** Swaped CVIP_YES and CVIP_NO
**
** Revision 1.11  1997/03/08 00:58:48  yawei
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
** Revision 1.10  1997/01/15 17:17:14  yawei
** Global Change:  IMAGE ==> Image
**
 * Revision 1.9  1996/12/23  21:28:48  yawei
 * Changed function names and prototypes
 *
 * Revision 1.8  1996/04/20  22:40:53  kluo
 * fix problem with history information
 *
 * Revision 1.7  1996/03/12  21:06:43  kluo
 * change to fit with cviptcl
 *
 * Revision 1.6  1995/09/21  16:53:06  kluo
 * change history dptr
 *
 * Revision 1.5  1995/03/01  03:26:28  luok
 * get rid of one extra delete_Matrix
 *
 * Revision 1.4  1995/02/10  19:22:58  luok
 * fix a memory leak in pct_Image
 *
 * Revision 1.3  1995/02/10  18:18:05  luok
 * check file into RCS
 *
 * Revision 1.2  1995/02/10  16:50:18  luok
 * check file into RCS
 *
 * Revision 1.1  1993/05/31  03:23:41  hanceg
 * Initial revision
 *
*
****************************************************************************/
#include "CVIPtoolkit.h"
#include "pct.h"


/****************************************************************
                   Name: pct
          Expanded Name: principal components transform
             Parameters: <srcImage> - pointer to source Image structure
                Returns: pointer to transformed image of type float
            Description: performs the prinicipal components transform (PCT) on
			 <srcImage>.  The resultant image contains a set of
			 decorrelated data bands in which the first band
			 is the most discriminant, then the second band
			 , and so on.
	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

Image *pct_setup(
	Image 	*imgP,
	CVIP_BOOLEAN is_mask,
	float 	*maskP
) 
{
   int 	i, j=0, choice;
   char 	*answer;

        /* 
	** check for correct number of bands 
	*/
	if(imgP->bands>3) {
           printf("PCT for > three color bands is not supported\n");
			  delete_Image(imgP);
			  return (Image *)NULL;
        }
        else if(imgP->bands!=3) {
           printf("The PCT is not defined on a monochrome image\n");
			  delete_Image(imgP);
			  return (Image *)NULL;
        }

        /* 
	** check for type CVIP_FLOAT image 
	*/
        for(i=0; i<imgP->bands; i++) {
           if(imgP->image_ptr[i]->data_type!=CVIP_FLOAT) {
              j=0;
           }
        }
        /* 
	** if image type is not CVIP_FLOAT, convert to type  CVIP_FLOAT  
	*/
        if(!j) (void)cast_Image(imgP, CVIP_FLOAT);

        printf("1. PCT\n");
        printf("2. Inverse PCT\n");
	printf("Your Choice: ");
        answer=(char *)malloc(32);
        (void)gets(answer);
        choice=atoi(answer);
        free(answer);

	return pct_color(imgP,is_mask,maskP,choice);
}

Image *pct_color(
	Image 	*imgP,
	CVIP_BOOLEAN is_mask,
	float 	*maskP,
	int	choice
){ 
        if(choice<1||choice>2) {
           printf("Invalid choice\n");
			  delete_Image(imgP);
           return (Image *)NULL;
        }
        if(choice==1) {
           imgP = pct(imgP, is_mask, maskP);
           return  imgP;
        }
        else { /* choice == 2 */
           if(!history_check(PCT, imgP)) {
              printf("The PCT must be performed before you can\n");
              printf("Perform the inverse PCT!!\n");
			  		delete_Image(imgP);
           		return (Image *)NULL;
           }
           else {
              imgP=ipct(imgP, is_mask, maskP);
              return imgP;
           }
        }
}

/************************************************************************
*									*
*	ROUTINE/PGM NAME: pct()					*
*									*
*	DESCRIPTION: Performs the Principal Components Transform by	*
*	estimating the covariance coefficients between the spectral	*
*	bands, forming a 3x3 matrix consisting of these coefficients,	*
*	computing the normalized eigenvectors of this matrix, then	*
*	applying a 3x3 matrix consisting of these eigenvectors to the	*
*	pixels of the image on a pixel-by-pixel basis.  That is, the	*
*	image is treated as a Nx3 matrix, where N is the number of	*
*	pixels in the image.  This Nx3 matrix is left-multiplied by	*
*	the eigenvector matrix described above.  The result is the	*
*	Principal Components Transform of the image.			*
*									*
*	AUTHOR: Greg Hance, SIUE.					*
*									*
*	INITIAL CODING DATE: 05/31/93					*
*									*
*	LAST MODIFICATIONS MADE: 11/24/93				*
*									*
************************************************************************/
Image *pct(
	Image 	*imgP,	/* pointer to input image (also stores result) */
	CVIP_BOOLEAN is_mask,/* whether to ignore a background color */
	float 	*maskP
)
{
	HISTORY 	stuff;
	Matrix 		*matP,*matP1;
	CVIP_BOOLEAN 	is_match = CVIP_YES;
	float 		**cvecP;
	double 		**tmat;
	unsigned int 	bands, imgsize;
	register int 	i, j;
	const char 	*fn = "PCT";
	double  		*hptr;

   	/* 
	** simplify some variables
	*/
   	bands = getNoOfBands_Image(imgP);
   	imgsize = getNoOfRows_Image(imgP)*getNoOfCols_Image(imgP);

   	(void) cast_Image(imgP, CVIP_FLOAT);

   	cvecP = (float **) malloc(bands*sizeof(float *));
	getBandVector_Image(imgP, cvecP);
   
   	msg_CVIP(fn, "performing (PCT) - Principal Components Transform\n");

   	msg_CVIP(fn, "computing covariance matrix...\n");

	if(is_mask && maskP) {
		for(i = 0; i < imgsize; i++) {
			for(j=0; j < bands; j++)
				if(cvecP[j][i] != maskP[j]) {
					is_match = CVIP_NO;
					break;
				}
			if(is_match == CVIP_YES)
				for(j=0; j < bands; j++)
					cvecP[j][i] = -1.0;
			is_match = CVIP_YES;
		}
	}
		
   	matP = covariance_Matrix(cvecP, bands, imgsize, is_mask, -1.0);
   	print_Matrix(matP);
   	msg_CVIP(fn, "\n");

   	msg_CVIP(fn, "computing eigenvectors of covariance matrix\n");
   	msg_CVIP(fn, "to compose transformation matrix...\n");

   	matP1 = eigenSystem_Matrix(matP);
	delete_Matrix(matP);
        matP=matP1;
   	tmat = (double **) getData_Matrix(matP);
   	print_Matrix(matP);
   	msg_CVIP(fn, "\n");

   	linearTrans_Image(cvecP, bands, imgsize, tmat);
	msg_CVIP(fn, "where [x0 x1 x2] = [R G B].\n");

 	/* 
	** Add xform Matrix to image history along with 'PCT' identifier 
	*/
        stuff = (HISTORY) malloc(sizeof(struct history));
        stuff->packetP = (PACKET *) malloc(sizeof(PACKET));
        stuff->packetP->dsize = matP->rows * matP->cols;
        stuff->packetP->dtype=(CVIP_TYPE *)malloc(sizeof(CVIP_TYPE)*
						stuff->packetP->dsize);

	stuff->packetP->dptr = (void**)malloc(sizeof(void*)*
						stuff->packetP->dsize);
	tmat = getRealData_Matrix(matP);
	for(i = 0; i < stuff->packetP->dsize; i++){
	      hptr = (double*)malloc(sizeof(double));
	      *hptr = tmat[i/matP->rows][i%matP->rows];
	      stuff->packetP->dptr[i] = hptr;
              stuff->packetP->dtype[i]=CVIP_DOUBLE;
	}
        stuff->next=(HISTORY) NULL;
        stuff->ftag=PCT;
        history_add(imgP, stuff);
        free(cvecP);
	free(matP);

   	return imgP;
}


/************************************************************************
*									*
*	ROUTINE/PGM NAME: Ipct()					*
*									*
*	DESCRIPTION: performs the inverse PCT by extracting the		*
*	forward PCT transform matrix from the image HISTORY, inverting	*
*	the matrix, and applying the inverted matrix to the image.	*
*									*
*	INITIAL CODING DATE: 11/24/93					*
*									*
*	LAST MODIFICATIONS MADE: 02/10/94				*
*									*
*	CREDIT(S): Arve Kjoelen, SIUE					*
*		   Greg Hance,   SIUE					*
*									*
************************************************************************/
Image *ipct(
	Image 	*imgP, 
	CVIP_BOOLEAN is_mask, 
	float 	*maskP
) 
{
	HISTORY stuff;
	Matrix 	*matP;
        double 	**tmat;
        int 	bands, imgsize;
        float 	**cvecP;
	int     length,i;

        bands=imgP->bands;
   	imgsize = getNoOfRows_Image(imgP)*getNoOfCols_Image(imgP);
   	cvecP = (float **) malloc(bands*sizeof(float *));
	getBandVector_Image(imgP, cvecP);

        printf("Performing inverse PCT\n");

        /* 
	** Get forward transform MATRIX from history structure 
	*/
        stuff=history_get(imgP, PCT);
	length = stuff->packetP->dsize;
	length = sqrt(length);
        matP= new_Matrix(length, length, CVIP_DOUBLE, REAL);
	tmat = getRealData_Matrix(matP);
	for(i = 0; i < stuff->packetP->dsize; i++){
	      tmat[i/matP->rows][i%matP->rows] =
	      				*((double*)(stuff->packetP->dptr[i]));
	}
        /* 
	** Invert PCT matrix - PCT matrix will ALWAYS be invertible 
	*/
        matP=invert_Matrix(matP);
        tmat = (double **) getData_Matrix(matP);
        print_Matrix(matP);
        printf("\n");
        linearTrans_Image(cvecP, bands, imgsize, tmat);

        return imgP;
}
