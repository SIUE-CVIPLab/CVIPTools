/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: morph.c
*           Description: routine to perform morphological iterative
*			 modification.
*         Related Files: morph.h, morphSET.c, Imakefile
*   Initial Coding Date: Mon May 31 02:36:39 CDT 1993
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
** $Log: morph.c,v $
** Revision 1.9  1997/03/08 17:04:05  yawei
** Swaped CVIP_YES and CVIP_NO
**
** Revision 1.8  1997/03/08 00:54:37  yawei
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
** Revision 1.7  1997/01/15 17:14:39  yawei
** Global Change:  IMAGE ==> Image
**
 * Revision 1.6  1996/12/18  03:44:04  yawei
 * Changed Image* to Image*
 *
 * Revision 1.5  1996/11/23  01:50:11  yawei
 * Added morpho function
 *
 * Revision 1.4  1995/07/20  21:09:49  seu
 * change the reverse order
 *
 * Revision 1.3  1995/05/24  21:23:01  luok
 * fix it so that it work with the "right" PBM interpretation
 *
 * Revision 1.2  1995/05/24  20:13:48  luok
 * check file into RCS.
 *
 * Revision 1.1  1993/06/01  16:46:59  hanceg
 * Initial revision
 *
*
****************************************************************************/
#include "CVIPimage.h"
#include "CVIPmorph.h"

static int chk_bin(Image *inputImage);

/****************************************************************
                   Name: morphomod
          Expanded Name: morphological modification
             Parameters: <binImage> - pointer to Image structure (binary image)
			 <surMATS> - pointer to a set (S) of surrounds for which
			 a_ij = 1
			 <boolFUNC> - a pointer to a Boolean function
			 of the form L(a,b) (c_ij = L(a_ij,b_ij)).
                         <no_of_sur> - number of surrounds
			 <connectedness> - the connectivity scheme being used
			 one of... FOUR, EIGHT, SIX_NWSE, SIX_NESW.
			 <no_of_iter> - number of iterations to perform
			 <f> - number of subfields into which the image
			 tesselation will be divided
                Returns: pointer to resultant Image structure.
            Description: Consider a_ij to have value one when the neighborhood
			 of the picture cell at (i, j) is in this set. Next 
			 consider b_ij to denote the value of the picture cell 	
			 itself. At each point of the tessellated image a new 
			 binary value is computed that is the result for that
			 point of the iterative modification algorithm. The new
			 value c_ij is to be computed from a_ij and b_ij. Here 
			 a, b, c are Boolean variables, in that the they can 
			 only take on values of 0 or 1. Computation of c 
			 from a and b can thus be specified by a Boolean
			 function of two variables -- <boolFUNC>. 
			 We can uniquely define the morphological iterative
			 modification algorithm by specifying four things...
			 (1) The set S of surrounds (for which a_ij = 1), 
			 (2) The Boolean function L(a,b) (where c_ij = 
			 L(a_ij,b_ij)), (3) The number of iterations, n. (4) The
			 number of subfields, <f>, into which the image
			 tessellation is divided. There are several Boolean
			 functions provided for the user (see functions zero,
			 not_b, and, or, not_and, or_not_and, xor.) In addition
			 a set of hexagonal lattices are provided and declared
			 as HEXLAT1, HEXLAT2, ..., HEXLAT14. The function
			 array2MATRIX can be used to form a MATRIX structure
			 that can then be passed to morphomod(...).
	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/



/*statement: Because we found that the previous PBM interpretation in CVIP was not
	     correct, after we modify it, we find morph doen't work, so Reverse_Image
	     and Forward_Image are written to save the work*/

static void Reverse_Image(Image *inputImage){
	byte 		**image;
	int		y,x,bands;
	unsigned int 	rows,cols,no_of_bands,threshval;

	no_of_bands = getNoOfBands_Image(inputImage);
	rows =  getNoOfRows_Image(inputImage);
  	cols =  getNoOfCols_Image(inputImage);
	for(bands=0; bands < no_of_bands; bands++) {
  		image = getData_Image(inputImage, bands);
  		for(y=0; y < rows; y++) {
     			for(x=0; x < cols; x++) {
				if(image[y][x] == 0)
            				image[y][x] = 0;
	  			else  
	     				image[y][x] = 1;
         		}
     		}
	}
}

static void Forward_Image(Image *inputImage){
	byte 		**image;
	int		y,x,bands;
	unsigned int 	rows,cols,no_of_bands,threshval;

	no_of_bands = getNoOfBands_Image(inputImage);
	rows =  getNoOfRows_Image(inputImage);
  	cols =  getNoOfCols_Image(inputImage);
	for(bands=0; bands < no_of_bands; bands++) {
  		image = getData_Image(inputImage, bands);
  		for(y=0; y < rows; y++) {
     			for(x=0; x < cols; x++) {
				if(image[y][x] == 0)
            				image[y][x] = 0;
	  			else 
	     				image[y][x] = 255;
         		}
     		}
	}
}


Image *morphIterMod_Image (
   const Image *binImage,
   const MATRIX **surMATS,
   CVIP_BOOLEAN (*const boolFUNC)(CVIP_BOOLEAN a,CVIP_BOOLEAN b),
   int no_of_sur,
   int connectedness,
   int no_of_iter,
   int f
)
{
   Image *modImage;
   CVIP_BOOLEAN a, b, c;
   int cnt = no_of_iter*f, emptyset=1, y, x, nr, nc, s_ct, d_nr, d_nc;
   int surnc=0, surnr=0, ys, xs, fstart, newsubf=0, n=0;
   byte *bdata, *surr, *mdata;
   const char fn[] = {"morph"};

   nr = binImage->image_ptr[0]->rows;
   nc = binImage->image_ptr[0]->cols;
   
   if(surMATS) {
      surnc = surMATS[0]->cols;
      surnr = surMATS[0]->rows;
   }
   
   d_nr = surnr/2;
   d_nc = surnc/2;
   
   if(!cnt) cnt=f;
   
   modImage = (Image *) image_allocate(binImage->image_format, BINARY, 1, nr, nc, CVIP_BYTE, REAL);
   mdata = (byte*) modImage->image_ptr[0]->rptr[0];
   (void) memcpy((void*)mdata,(void*)binImage->image_ptr[0]->rptr[0],nr*nc);
   
   Reverse_Image(modImage);      

   bdata = (byte *) malloc(nr*nc);
   
   fprintf(stderr,"%s: iteration  1, subfield  1.",fn);
   
   while( emptyset && (cnt > 0) ) {

      (void) memcpy((void*)bdata,(void*) mdata, nr*nc);
      for(y=0, fstart=newsubf, emptyset=0; y < nr-surnr+1; y++) {
         for(x=fstart; x < nc-surnc+1; x+=f) {
            
	    for(s_ct=0,a=CVIP_NO; (s_ct<no_of_sur) && (a==CVIP_NO); s_ct++) {
               surr = (byte*) surMATS[s_ct]->rptr[0];

	       for(ys=0,a=CVIP_YES;(ys < surnr) && (a==CVIP_YES); ys++) 
	          for(xs=0; xs < surnc; xs++) 
                     switch(connectedness) {
                        case FOUR:
		           if( ((xs==d_nr) || (ys==d_nc)) && !((xs==d_nc)&&(ys==d_nr)) )
			      if ( *(surr+ys*surnc+xs) != *(bdata+(y+ys)*nc+(x+xs)) ) a=CVIP_NO;
			   break;
			case SIX_NWSE:
			   if( ((xs!=(surnc-1))||(ys!=0)) && ((ys!=(surnr-1))||(xs!=0)) && !((xs==d_nc)&&(ys==d_nr)) )
			      if ( *(surr+ys*surnc+xs) != *(bdata+(y+ys)*nc+(x+xs)) ) a=CVIP_NO;
			   break;
			case SIX_NESW:
			   if( ((ys != 0)||(xs != 0)) && ((ys!=(surnr-1))||(xs!=(surnc-1))) && !((xs==d_nc)&&(ys==d_nr)) )
			      if ( *(surr+ys*surnc+xs) != *(bdata+(y+ys)*nc+(x+xs)) ) a=CVIP_NO;
			   break;
			case EIGHT:
			   if( !((xs==d_nc)&&(ys==d_nr)) )
			      if ( *(surr+ys*surnc+xs) != *(bdata+(y+ys)*nc+(x+xs)) ) a=CVIP_NO;
			   break;
		     }

	    }
	    b = *(bdata+(y+d_nr)*nc+(x+d_nc));
	    c = boolFUNC(a,b);
	    *(mdata+(y+d_nr)*nc+(x+d_nc)) = c;
	    if(c!=b) emptyset++;
	 }
	 if(f>1) fstart = (!fstart) ? f-1 : fstart-1;
      }
      if (no_of_iter) cnt--; else cnt++;
      if(f>1) newsubf = (!(cnt%f)) ? 0 : (++emptyset, ++newsubf);
      n++;
//      fprintf(stderr,"\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b%3d, subfield %1d.",n/f+1,newsubf+1);
   }
      fprintf(stderr," ... iteration %3d, subfield %1d.",n/f+1,newsubf+1);
   Forward_Image(modImage);
return modImage;
}

Image *
morpho(const  Image   *binImage, 
	const char * surround_str, CVIP_BOOLEAN rotate,
	int boolFUNC, int connectedness, 
	unsigned no_of_iter, int fields) {

	int *surrchoice, n=0, subf=0, i, j, k, *sP, add_sur=0;
	Matrix **surrounds;
	CVIP_BOOLEAN (*bF)(CVIP_BOOLEAN a,CVIP_BOOLEAN b);

	byte *surrP[] =   {(byte*)HEXLAT1, (byte*)HEXLAT2, (byte*)HEXLAT3, 
							 (byte*)HEXLAT4, (byte*)HEXLAT5, (byte*)HEXLAT6, 
							 (byte*)HEXLAT7, (byte*)HEXLAT8, (byte*)HEXLAT9, 
							 (byte*)HEXLAT10,(byte*)HEXLAT11,(byte*)HEXLAT12,
							 (byte*)HEXLAT13,(byte*)HEXLAT14};


	if(chk_bin((Image *)binImage) == 0){
		perror_CVIP("morpho", "Input image MUST be two-level only, a two level image can be created from a gray level image by thresholding.");
		return (Image *)NULL;
	}

	surrchoice = (int*)parse2ints(surround_str, " ,;:\n",&n);

	if( rotate == CVIP_YES ) {
		for(i=0; i < n; i++) 
			if(surrchoice[i]>1 && surrchoice[i]<7) add_sur+=5;
	 	else if(surrchoice[i]>8 && surrchoice[i]<13) add_sur+=5;
	 	else if(surrchoice[i] == 8) add_sur++;
	 	else if(surrchoice[i]==13 || surrchoice[i]==14) add_sur+=2;
	 	else {/*Change Nothing*/}
	}

	k = n;
	surrounds = (MATRIX **) calloc(n+add_sur,sizeof(MATRIX *));
	for(i=0, sP=surrchoice; i < n; i++, sP++)
		surrounds[i] = array2MATRIX(surrP[*sP-1], CVIP_BYTE, 3, 3);
	if(rotate == CVIP_YES ) {
		for(i=0; i < n; i++) 
			if( (surrchoice[i]>1 && surrchoice[i]<7) ||\
				(surrchoice[i]>8 && surrchoice[i]<13) ) 
				for(j=0; j < 5; j++, k++)
					surrounds[k] = hexrotate(surrounds[i], SIX_NWSE, (j+1)*60);
			else if(surrchoice[i] == 8) 
				surrounds[k++] = hexrotate(surrounds[i], SIX_NWSE, 60);
			else if(surrchoice[i]==13 || surrchoice[i]==14)
				for(j=0; j < 2; j++, k++)
					surrounds[k] = hexrotate(surrounds[i], SIX_NWSE, (j+1)*60);
			else {/*Change Nothing*/}
	}

	switch(boolFUNC){
		case 1: bF = &zero; break;
		case 2: bF = &not_a; break;
		case 3: bF = &and; break;
		case 4: bF = &or; break;
		case 5: bF = &xor; break;
		case 6: bF = &not_and; break;
		default: bF = &or_not_and; break;
	}

	binImage = (Image*) morphIterMod_Image((const Image *) binImage, 
				(const MATRIX **)surrounds, bF, n+add_sur, connectedness, 
				(int)no_of_iter, fields);

	return (Image *)binImage;
}


static int 
chk_bin(Image *inputImage)
{
	byte 		**image; 	/* 2-d matrix data pointer */
	int 		y,		/* row index */
			x, 		/* column index */
			bands;		/* band index */
			
	unsigned int 	rows, 		/* number of rows in image */
			cols,		/* number of columns in image */
			no_of_bands,	/* number of image bands */
			level[2];	/* gray levels */


	/*
	** Gets the number of image bands (planes)
	*/
	no_of_bands = getNoOfBands_Image(inputImage);

	/* 
	** Gets the number of rows in the input image  
	*/
	rows =  getNoOfRows_Image(inputImage);

	/* 
	** Gets the number of columns in the input image  
	*/
  	cols =  getNoOfCols_Image(inputImage);
	
	level[1]=256;
	
	/* 
	** compares the pixel value at the location (y,x)
	** with the threshold value. If it is greater than 
 	** the threshold value it writes 255 at the location
	** else 0
	*/
	for(bands=0; bands < no_of_bands; bands++) {
		/*
		** reference each band of image data in 2-d matrix form
		*/
  		image = getData_Image(inputImage, bands);
		if(bands == 0)
		    level[0]=image[0][0];
  		for(y=0; y < rows; y++) {
     			for(x=0; x < cols; x++) {
				if((image[y][x] != image[0][0])&&(level[1]==256)) 
            				level[1] = image[y][x];
				if((image[y][x]!=level[0])&&(image[y][x]!=level[1]))
	     				return 0;
         		}
     		}
	}
	return 1;
}
