/*
 *
 * convolve_Image()
 *
 * Convolve two images.  Delete whatever was passed.  return
 * a pointer to the result.  Uses convolve_Matrix(), which handles
 * all data types.  If the two images have the same number of bands,
 * they are convolved as you would expect.  If image 1 has several
 * bands and image 2 only 1 band, each band of image 1 is convolved with
 * image 2.  All other cases cause error.
 *
 * Author: Arve Kjoelen, SIUE (akjoele@ee.siue.edu)
 *
 * Initial Coding Date: Thu Dec 12 14:07:37 CST 1996
 *
 */

#include "CVIPimage.h"
Image *conv_Image(Image *im1, Image *im2, int handle, int center) {
   Matrix *cp1, *cp2, *tp;
   Image *resIm;
   FORMAT fm;
   int i;

   fm=im2->bandP[0]->data_format;
   if(im1->bandP[0]->data_format >= im2->bandP[0]->data_format) 
      fm=im1->bandP[0]->data_format;
   if(im1->bands==im2->bands) {
      resIm=duplicate_Image(im1);
      for(i=0; i<im1->bands; i++) {
         cp1=duplicate_Matrix(im1->bandP[i], fm);
         cp2=duplicate_Matrix(im2->bandP[i], fm);
         tp=resIm->bandP[i];
         resIm->bandP[i]=convolve_Matrix(cp1, cp2, handle, center);
         delete_Matrix(tp);
      }
      delete_Image(im1);
      delete_Image(im2);
      return(resIm);
   }
   else if(im1->bands==1 || im2->bands==1) {
      resIm=duplicate_Image((im1->bands==1 ? im2 : im1));
      for(i=0; i<MAX(im1->bands, im2->bands); i++) {
         if(im1->bands==1) {
            cp1=duplicate_Matrix(im1->bandP[0], fm);
            cp2=duplicate_Matrix(im2->bandP[i], fm);
            tp=resIm->bandP[i];
            resIm->bandP[i]=convolve_Matrix(cp1, cp2, handle, center);
         }
         else if(im2->bands==1) {
            cp1=duplicate_Matrix(im1->bandP[i], fm);
            cp2=duplicate_Matrix(im2->bandP[0], fm);
            tp=resIm->bandP[i];
            resIm->bandP[i]=convolve_Matrix(cp1, cp2, handle, center);
	}
        delete_Matrix(tp);
      }
      delete_Image(im1);
      delete_Image(im2);
      return(resIm);
   }
}
