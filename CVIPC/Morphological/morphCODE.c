/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: morphOCDE.c
*           Description: This file contains program to implement gray-level
*			 open, close, dilate, erode. Greg first wrote open
*			 and close function in his dermvis application. 
*			 Kun Luo extracted it out and created additional
*			 dilate and erode functions and four setup functions
*			 for these operations.
*         Related Files: 
*   Initial Coding Date: Mon Jul 31 12:48:19 CDT 1995
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Gregory Hance, Kun Luo
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1995 SIUE - by Gregory Hance, Kun Luo.
** 
*  Write functions supporting new kernels: square_SE(), rectangle_SE() and cross_SE()
*  -- Wenxing Li
*
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
** $Log: morphCODE.c,v $
** Revision 1.6  1997/03/08 00:54:40  yawei
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
** Revision 1.5  1997/01/15 17:14:43  yawei
** Global Change:  IMAGE ==> Image
**
 * Revision 1.4  1996/12/18  03:44:30  yawei
 * 1) Changed int MorphXXXX_Image to Image *MorphXXXX_Image
 * 2) Changed MorphXXX_Setup_sep to MorphXXX
 *
 * Revision 1.3  1996/08/21  03:41:44  wli
 * put functions supporting new kernels into CVIPtools
 * modify MorphClose, MorphOpen, MorphErode and MorphDilate so that
 * they can use new kernels
 *
 * Revision 1.2  1996/01/24  00:30:34  zli
 * split the following functions into 2 parts, of which the first part asks for the kernel dimension
 * MorphDilate_Setup()  MorphOpen_Setup()  MorphClose_Setup()  MorphErode_Setup()
 *
 * Revision 1.1  1995/07/31  17:53:57  kluo
 * Initial revision
 *
*
****************************************************************************/
#include "CVIPimage.h"
#include "CVIPtoolkit.h"
#include "CVIPmatrix.h"
#include "CVIPmorph.h"

Image* MorphErode(Image *inputImage, int k_type, int ksize, int height,
	int width)
{
    Matrix	*matP = NULL;
    Image	*tempImage;
    int		 retv;

    if(inputImage->bands != 1){
	fprintf(stderr,"This routine is OK with gray image only\n");
	return NULL;
    }

    if (k_type < 1 || k_type > 4) 
      {fprintf(stderr,"kernel type value should be within 1-4\n");
       return NULL;
      }

    if(inputImage->bandP[0]->data_type != CVIP_BYTE){
	tempImage = remap_Image(inputImage,CVIP_BYTE,0,255);
	fprintf(stderr,"Image is remapped into CVIP_BYTE\n");
	delete_Image(inputImage);
	inputImage = tempImage;
    }

    fflush(stdin);

    switch(k_type)
      { case 1: retv=disk_SE(&matP, CVIP_INTEGER, -1.0, 0.0, ksize);
         	break;
        case 2: retv=square_SE(&matP, CVIP_INTEGER, -1.0, 0.0, ksize, height); 
		break;
        case 3: retv=rectangle_SE(&matP, CVIP_INTEGER, -1.0, 0.0, ksize, height, width); 
		break;
        case 4: retv=cross_SE(&matP, CVIP_INTEGER, -1.0, 0.0, ksize, height, width); 
		break;
        default:fprintf(stderr, "should not happen\n");
      }
 
    if(!retv) {
	fprintf(stderr,"could not form SE");
	return NULL;
    }
    if((inputImage = MorphErode_Image(inputImage, matP, 0, 0, 0)) 
			== (Image *)NULL) {
	fprintf(stderr,"could not perform gray-scale morphological eroding");
	return NULL;
    }
    return inputImage;
}

Image* MorphDilate(Image *inputImage, int k_type, int ksize, int height,
		int width)
{
    Matrix	*matP = NULL;
    Image	*tempImage;
    int		 retv;

    if(inputImage->bands != 1){
		fprintf(stderr,"This routine is OK with gray image only\n");
		return NULL;
    }

    if (k_type < 1 || k_type > 4)
      {fprintf(stderr,"kernel type value should be within 1-4\n");
       return NULL;
      }

    if(inputImage->bandP[0]->data_type != CVIP_BYTE){
	tempImage = remap_Image(inputImage,CVIP_BYTE,0,255);
	fprintf(stderr,"Image is remapped into CVIP_BYTE\n");
	delete_Image(inputImage);
	inputImage = tempImage;
    }

    fflush(stdin);

    switch(k_type)
      { case 1: retv=disk_SE(&matP, CVIP_INTEGER, -1.0, 0.0, ksize);
                break;
        case 2: retv=square_SE(&matP, CVIP_INTEGER, -1.0, 0.0, ksize, height);
                break;
        case 3: retv=rectangle_SE(&matP, CVIP_INTEGER, -1.0, 0.0, ksize, height, width);
                break;
        case 4: retv=cross_SE(&matP, CVIP_INTEGER, -1.0, 0.0, ksize, height, width);
                break;
        default:fprintf(stderr, "should not happen\n");
      }  
 
    if(!retv) {
	fprintf(stderr,"could not form SE");
	return NULL;
    }
    if((inputImage = MorphDilate_Image(inputImage, matP, 0, 0, 0)) ==
			(Image *)NULL) {
	fprintf(stderr,"could not perform gray-scale morphological dilating");
	return NULL;
    }
    return inputImage;
}


Image* MorphOpen(Image *inputImage, int k_type, int ksize, int height,
	int width)
{
    Matrix	*matP = NULL;
    Image	*tempImage;
    int		 retv;

    if(inputImage->bands != 1){
	fprintf(stderr,"This routine is OK with gray image only\n");
	return NULL;
    }

    if (k_type < 1 || k_type > 4)
      {fprintf(stderr,"kernel type value should be within 1-4\n");
       return NULL;
      }

    if(inputImage->bandP[0]->data_type != CVIP_BYTE){
	tempImage = remap_Image(inputImage,CVIP_BYTE,0,255);
	fprintf(stderr,"Image is remapped into CVIP_BYTE\n");
	delete_Image(inputImage);
	inputImage = tempImage;
    }

    fflush(stdin);

    switch(k_type) 
      { case 1: retv=disk_SE(&matP, CVIP_INTEGER, -1.0, 0.0, ksize); 
                break; 
        case 2: retv=square_SE(&matP, CVIP_INTEGER, -1.0, 0.0, ksize, height); 
                break; 
        case 3: retv=rectangle_SE(&matP, CVIP_INTEGER, -1.0, 0.0, ksize, height, width); 
                break; 
        case 4: retv=cross_SE(&matP, CVIP_INTEGER, -1.0, 0.0, ksize, height, width); 
                break; 
        default:fprintf(stderr, "should not happen\n"); 
      }   
 
    if(!retv) {  
        fprintf(stderr,"could not form SE");
        return NULL;
    }

    if((inputImage = MorphOpen_Image(inputImage, matP, 0, 0, 0)) == 
		(Image *)NULL ) {
	fprintf(stderr,"could not perform gray-scale morphological opening");
	return NULL;
    }
    return inputImage;
}

Image* MorphClose(Image *inputImage, int k_type, int ksize, int height,
	int width) {
    Matrix	*matP = NULL;
    Image	*tempImage;
    int		 retv;

    if(inputImage->bands != 1){
	fprintf(stderr,"This routine is OK with gray image only\n");
	return NULL;
    }

    if (k_type < 1 || k_type > 4) 
      {fprintf(stderr,"kernel type value should be within 1-4\n"); 
       return NULL; 
      }

    if(inputImage->bandP[0]->data_type != CVIP_BYTE){
	tempImage = remap_Image(inputImage,CVIP_BYTE,0,255);
	fprintf(stderr,"Image is remapped into CVIP_BYTE\n");
	delete_Image(inputImage);
	inputImage = tempImage;
    }

    fflush(stdin);

    switch(k_type)  
      { case 1: retv=disk_SE(&matP, CVIP_INTEGER, -1.0, 0.0, ksize);  
                break;  
        case 2: retv=square_SE(&matP, CVIP_INTEGER, -1.0, 0.0, ksize, height);  
                break; 
        case 3: retv=rectangle_SE(&matP, CVIP_INTEGER, -1.0, 0.0, ksize, height, width);  
                break;  
        case 4: retv=cross_SE(&matP, CVIP_INTEGER, -1.0, 0.0, ksize, height, width);  
                break;  
        default:fprintf(stderr, "should not happen\n");  
      }    
  
    if(!retv) {   
        fprintf(stderr,"could not form SE"); 
        return NULL; 
    }

    if( (inputImage = MorphClose_Image(inputImage, matP, 0, 0, 0))
			 == (Image *)NULL) {
	fprintf(stderr,"could not perform gray-scale morphological closing");
	return NULL;
    }
    return inputImage;
}


Image *
MorphErode_Image(
	Image *imageP,
	Matrix *kernelP,
	CVIP_BOOLEAN user_org,
	int x,
	int y
)
{
	byte 	**workP, **bP, **wP;
	int 	x_ctr, y_ctr, x_org, y_org, **kP;
	int 	nc,        /* number of columns of image */ 
		nr,        /*   "    "  rows    "  "    */
		starti,    /* x upper left corner position of kernel */
		startj,    /* y   "    "    "        "     "   "     */
		kernc,     /* number of columns of kernel */
		kernr;     /* number of rows of kernel */
	const char 	*fn = "MorphErode_Image";
	int 		i, j, ii, jj, iii, jjj;
	register int 	minpix, maxpix, imagepix,  kernpix;

	msg_CVIP("MorphErode_Image","performing morphological eroding.\n");

    	/* Check type,... of image */
    
    	nc = getNoOfCols_Image(imageP); /* number of columns */
    	nr = getNoOfRows_Image(imageP); /* number of rows    */

    	bP = (byte **) getData_Matrix(getBand_Image(imageP,0)); 

    	/* Check type,... of kernel */
    
	/* number of columns of the kernel */
	kernc = getNoOfCols_Matrix(kernelP);
	/* number of rows of the kernel    */
	kernr = getNoOfRows_Matrix(kernelP); 

  	x_ctr = kernc/2; 
  	y_ctr = kernr/2;

 	/* 
	 * set the SE origin:  either center it,  or accept user
  	 * values 
	 */
  	if (!user_org) {
     		x_org = x_ctr;
     		y_org = y_ctr;
  	}
  	else {
     		x_org = x;
     		y_org = y;
  	}

	starti = -x_org; /* position of upper left hand */ 
	startj = -y_org; /* corner of the kernel (x,y)  */

	kP = (int **) getData_Matrix(kernelP); /* pointer on kernel values */

	/* 
	 * Checks if the position of the kernel relative to the 
         * dimension of the image will give a significant result image
	 */
    	if (starti > nr/2 || startj > nc/2) {
        	error_CVIP(fn,"the size of the kernel is too big compared");
        	error_CVIP(fn,"to the image size. The visible result may be");
        	error_CVIP(fn,"out of the result image dimension...");
        }

    	/* 
	 * dynamic memory allocation for temporary result stockage 
	 */
    	workP = allocMatrix_CVIP(nr, nc, sizeof(byte));
    	if (!workP) {
        	error_CVIP(fn, "insufficient space avaliable");
        	return (Image *)NULL;
    	}

    	wP = workP; /* pointer on the result image data */

	msg_CVIP("MorphErode","eroding scanline   0.\n");
    	for (i=0;i < nr; i++) {
//		print_CVIP("\b\b\b\b%3d.", i);
      		for (j=0; j < nc; j++) {
              		minpix = 255; 
              		for (ii=0;  ii < kernr;  ii++) {
                 		iii = i + ii + starti;
                 		if (iii < 0 || iii >= nr) continue;
                    		for (jj = 0;  jj < kernc; jj++) {
                       			jjj = j + jj + startj;
                       			if (jjj >= 0 && jjj < nc) {
                          			imagepix = bP[iii][jjj];
                          			kernpix = kP[ii][jj];
                          			if (kernpix >= 0)
                             				minpix = MIN(minpix, (imagepix - kernpix));
                        		}
                    		}
              		 }
           	minpix = MAX(minpix, 0);
           	wP[i][j] = (byte) minpix;
        
           	}
         }
    	for (i=0;i < nr; i++) {
      		for (j=0; j < nc; j++) {
			bP[i][j]=wP[i][j];
		}
	}
   	/* 
	 * free memory location of temporary result storage
	 */ 
    
	freeMatrix_CVIP(workP);

	return imageP;	
}


Image *
MorphDilate_Image(
	Image *imageP,
	Matrix *kernelP,
	CVIP_BOOLEAN user_org,
	int x,
	int y
)
{
	byte 	**workP, **bP, **wP;
	int 	x_ctr, y_ctr, x_org, y_org, **kP;
	int 	nc,        /* number of columns of image */ 
		nr,        /*   "    "  rows    "  "    */
		starti,    /* x upper left corner position of kernel */
		startj,    /* y   "    "    "        "     "   "     */
		kernc,     /* number of columns of kernel */
		kernr;     /* number of rows of kernel */
	const char 	*fn = "MorphDilate_Image";
	int 		i, j, ii, jj, iii, jjj;
	register int 	minpix, maxpix, imagepix,  kernpix;

	msg_CVIP("MorphDilate","performing morphological dilating.\n");

    	/* Check type,... of image */
    
    	nc = getNoOfCols_Image(imageP); /* number of columns */
    	nr = getNoOfRows_Image(imageP); /* number of rows    */

    	bP = (byte **) getData_Matrix(getBand_Image(imageP,0)); 

    	/* Check type,... of kernel */
    
	/* number of columns of the kernel */
	kernc = getNoOfCols_Matrix(kernelP);
	/* number of rows of the kernel    */
	kernr = getNoOfRows_Matrix(kernelP); 

  	x_ctr = kernc/2; 
  	y_ctr = kernr/2;

 	/* 
	 * set the SE origin:  either center it,  or accept user
  	 * values 
	 */
  	if (!user_org) {
     		x_org = x_ctr;
     		y_org = y_ctr;
  	}
  	else {
     		x_org = x;
     		y_org = y;
  	}

	starti = -x_org; /* position of upper left hand */ 
	startj = -y_org; /* corner of the kernel (x,y)  */

	kP = (int **) getData_Matrix(kernelP); /* pointer on kernel values */
	/* 
	 * Checks if the position of the kernel relative to the 
         * dimension of the image will give a significant result image
	 */
    	if (starti > nr/2 || startj > nc/2) {
        	error_CVIP(fn,"the size of the kernel is too big compared");
        	error_CVIP(fn,"to the image size. The visible result may be");
        	error_CVIP(fn,"out of the result image dimension...");
        }

    	/* 
	 * dynamic memory allocation for temporary result stockage 
	 */
    	workP = allocMatrix_CVIP(nr, nc, sizeof(byte));
    	if (!workP) {
        	error_CVIP(fn, "insufficient space avaliable");
        	return (Image *)NULL;
    	}

    	wP = workP; /* pointer on the result image data */

	msg_CVIP("MorphDilate","dilating scanline   0.\n");
    	for (i=0;i < nr; i++) {
//		print_CVIP("\b\b\b\b%3d.", i);
      		for (j=0; j < nc; j++) {
              		maxpix = 0; 
              		for (ii=0;  ii < kernr;  ii++) {
                 		iii = i + ii + starti;
                 		if (iii < 0 || iii >= nr) continue;
                    		for (jj = 0;  jj < kernc; jj++) {
                       			jjj = j + jj + startj;
                       			if (jjj >= 0 && jjj < nc) {
                          			imagepix = bP[iii][jjj];
                          			kernpix = kP[ii][jj];
                          			if (kernpix >= 0)
                             				maxpix = MAX(maxpix, (imagepix + kernpix));
                        		}
                    		}
              		 }
           	maxpix = MIN(maxpix, 255);
           	wP[i][j] = (byte) maxpix;
        
           	}
         }

    	for (i=0;i < nr; i++) {
      		for (j=0; j < nc; j++) {
			bP[i][j]=wP[i][j];
		}
	}
    
	freeMatrix_CVIP(workP);

	return imageP;
}


Image *
MorphOpen_Image(
	Image *imageP,
	Matrix *kernelP,
	CVIP_BOOLEAN user_org,
	int x,
	int y
)
{
	msg_CVIP("MorphOpen_Image","performing morphological opening.\n");

  if((imageP = MorphErode_Image(imageP,kernelP,user_org,x,y)) 
				== (Image *)NULL ){
		fprintf(stderr,
		"could not perform gray-scale morphological eroding");
		return (Image *)NULL;
	}
        if((imageP=MorphDilate_Image(imageP,kernelP,user_org,x,y))
		 		 == (Image *)NULL){
		fprintf(stderr,
		"could not perform gray-scale morphological dilating");
		return (Image *)NULL;
	}
  
	return imageP;
}


Image *
MorphClose_Image(
	Image *imageP,
	Matrix *kernelP,
	CVIP_BOOLEAN user_org,
	int x,
	int y
)
{
	msg_CVIP("MorphClose","performing morphological closing.\n");

        if((imageP = MorphDilate_Image(imageP,kernelP,user_org,x,y)) ==
				(Image *) NULL){
		fprintf(stderr,
		"could not perform gray-scale morphological dilating");
		return (Image *)NULL;
	}
   if((imageP = MorphErode_Image(imageP,kernelP,user_org,x,y)) 
				== (Image *)NULL){
		fprintf(stderr,
		"could not perform gray-scale morphological eroding");
		return (Image *)NULL;
	}
	return imageP;
}

int
disk_SE(
	Matrix 	**stru_elemP, 
	CVIP_TYPE 	type, 
	float 	bgnd, 
	float 	fgnd,  
	float 	d
)
{
	Matrix 	*seP;
  	int 	x_ctr, y_ctr, rows, cols, *iP;
	register int 	i, j;
 	float 	r;
	byte 	*bP;

  	rows = d;
  	cols = d;

	if(!(*stru_elemP))
		*stru_elemP = new_Matrix(rows, cols, type, REAL);


  	if (*stru_elemP == NULL) {
     		error_CVIP("Disk_SE","unable to allocate structuring element!\n");
      		*stru_elemP = NULL;
      		return(0);
    	}

  	seP = *stru_elemP;

  	r = d/2.0;
  	r = r*r;

  	x_ctr = (int)d/2.0; 
  	y_ctr = (int)d/2.0;

	switch(type) {
      		case CVIP_BYTE :
        	for (i=0; i < rows; i++) {
			bP = getRow_Matrix(seP, i);
          		for (j=0; j < cols; j++, bP++)
            		if ((i-y_ctr)*(i-y_ctr)+(j-x_ctr)*(j-x_ctr) <= r)
				*bP = fgnd;
            		else 
				*bP = bgnd;
		}
        	break;
      		case CVIP_INTEGER :
        	for (i=0; i < rows; i++) {
			iP = getRow_Matrix(seP, i);
          		for (j=0; j < cols; j++, iP++)
            		if ((i-y_ctr)*(i-y_ctr)+(j-x_ctr)*(j-x_ctr) <= r)
				*iP = fgnd;
            		else 
				*iP = bgnd;
		}
        	break;
      		default:
        		error_CVIP("Disk_SE","invalid data type");
        		error_CVIP("Disk_SE","types supported - CVIP_BYTE, CVIP_INTEGER");
        		return(0);
    	}

return(1);
}


#define CALCULATE_SE(type_)\
    for (i=0; i < block_size; i++) \
       { ptr = (void *)getRow_Matrix(seP, i); \
         for (j=0; j < block_size; j++, ((type_ *)ptr)++) \
            if (i>=x_ul && i<x_br && j>=y_ul && j<y_br) \
                  *((type_ *)ptr) = fgnd; \
            else  *((type_ *)ptr) = bgnd; \
       }


static Matrix * prep_SE(Matrix  **stru_elemP, CVIP_TYPE    type,
	int   block_size, const char *fn)
{
 if(!(*stru_elemP))
     *stru_elemP = new_Matrix(block_size, block_size, type, REAL);

 if (*stru_elemP == NULL)
      error_CVIP(fn,"unable to allocate structuring element!\n");

 return (*stru_elemP);
}

static int post_SE(Matrix * seP,  CVIP_TYPE type,  int  bgnd,  int  fgnd,
	int  block_size, int  x_ul,  int  y_ul,   int  x_br,  int  y_br, 
	const char *fn)
{
 register int    i, j;
 void          * ptr;

 switch(type) 
   { case    CVIP_BYTE :     CALCULATE_SE(byte)     break;
     case    CVIP_INTEGER :  CALCULATE_SE(int)      break;
     default:
             error_CVIP(fn,"invalid data type");
             error_CVIP(fn,"types supported - CVIP_BYTE, CVIP_INTEGER");
             return(0);
   }
 
return(1);
}

int square_SE(Matrix  **stru_elemP, CVIP_TYPE    type, int   bgnd, int   fgnd,
	      int   block_size,     int   side_len)
{
 Matrix        * seP;
 int     	 x_ul, y_ul, x_br, y_br;

 if (side_len > block_size) 
   {printf("square_SE: side length larger than block size\n");
    return (0);
   }			

 seP = prep_SE(stru_elemP, type, block_size, "square_SE");
 if (seP == NULL)   return (0); 

 x_ul = block_size/2 - side_len/2;
 y_ul = x_ul;
 x_br = x_ul + side_len;
 y_br = x_br;

 return (post_SE(seP, type, bgnd, fgnd, block_size, x_ul, y_ul, x_br, y_br, "square_SE"));

}


int rectangle_SE(Matrix  **stru_elemP, CVIP_TYPE    type, int   bgnd,
	int   fgnd, int   block_size,   int  height,  int  width)
{
 Matrix        * seP;
 int     	 x_ul, y_ul, x_br, y_br;

 if (height > block_size || width > block_size)
   { printf("rectangle_SE: height or width larger than block size\n");
     return (0);
   }

 seP = prep_SE(stru_elemP, type, block_size, "rectangle_SE");
 if (seP == NULL)   return (0);

 x_ul = block_size/2 - height/2;
 y_ul = block_size/2 - width/2;
 x_br = x_ul + height;
 y_br = y_ul + width;

return (post_SE(seP, type, bgnd, fgnd, block_size, x_ul, y_ul, x_br, y_br, "rectangle_SE"));

}

/* combine two */
#define CROSS_COMBINE(type_) \
   for (i=0; i < block_size; i++) \
      { ptrh = (void *)getRow_Matrix(seP, i); \
        ptrv = (void *)getRow_Matrix(matP, i); \
        for (j=0; j < block_size; j++) \
           { if (*((type_ *)ptrv) == fgnd )  *((type_ *)ptrh) = fgnd; \
             ((type_ *)ptrh)++; \
             ((type_ *)ptrv)++; \
           } \
      }   


int  cross_SE(Matrix  **stru_elemP, CVIP_TYPE    type, int   bgnd, int   fgnd,
	      int   block_size,   int  thickness,  int  width)
{
 int		reth, retv;
 Matrix	      * matP = NULL, * seP;
 int		i,   j;
 void	      * ptrh, * ptrv;

 if (thickness > block_size || width > block_size)
   { printf("cross_SE: thickness or width larger than block size\n");
     return (0);
   }

 reth = rectangle_SE(stru_elemP, type, bgnd, fgnd, block_size, thickness, width);
 if (reth == 0)   return (0);

 retv = rectangle_SE(&matP, type, bgnd, fgnd, block_size, width, thickness);
 if (retv == 0)   return (0);

 seP = *stru_elemP;

 switch(type)
   { case    CVIP_BYTE :     CROSS_COMBINE(byte)     break;
     case    CVIP_INTEGER :  CROSS_COMBINE(int)      break;
     default:
             error_CVIP("cross_SE", "invalid data type");
             error_CVIP("cross_SE", "types supported - CVIP_BYTE, CVIP_INTEGER");
             return(0);
   }
 
 delete_Matrix(matP);

 return (1);
}

