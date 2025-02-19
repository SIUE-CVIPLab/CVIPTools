/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: lee_filer.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Tue Oct  7 17:52:54 CDT 1997
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Sun Lingwei
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1996 SIUE - by Scott Umbaugh and Sun Lingwei.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
****************************************************************************/
/** Porject adaptive median filter
** This program is to implement median filter and adaptive median filter.
** When there are lot of impulse noise in the image, median filter fails to
** eliminate the noise. Adaptive median filter is to test for the presence of 
** residual impulses in the median filter output, and also test whether the 
** center pixel is corrupted by an impulse or not.
*/

#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPimage.h"
#include "CVIPxformfilter.h"
#include "CVIPtransform.h"
#include <CVIPspfltr.h>
#include <math.h>

 
/* new lee's algorithm equation:
** the old name: new_lee	new_name:exp_ace_filter
** fbar[r][c] = m*(A[r][c]/m)**beta + (f[r][c]/A[r][c])**alpha */ 
Image *exp_ace_filter(Image *inputIMAGE,int wsize,float alpha, float beta)
{
	float **image,**imaget,
			f,fbar,t1,t2,m=256.0,
			lfbar,f1bar,lf1bar,labar,fw,fwbar,lfwbar;
	int r,c,bands,i,j,wmin=3,w=0,k=0,r1,c1,z,w1;
        unsigned int 	no_of_rows,	/* number of rows in image */
			no_of_cols,	/* number of columns in image */
			no_of_bands,	/* number of image bands */
			data_type,
			data_format,
			file_format,
			color_space;
	Image *resultImage;

/*        if(alpha<0 ||alpha>1 || beta<0 || beta >1) return NULL;*/

	cast_Image(inputIMAGE,CVIP_FLOAT);
        no_of_bands = getNoOfBands_Image(inputIMAGE);
        no_of_rows =  getNoOfRows_Image(inputIMAGE);
        no_of_cols =  getNoOfCols_Image(inputIMAGE);
	data_type=getDataType_Image(inputIMAGE);
	data_format=getDataFormat_Image(inputIMAGE);
	file_format=getFileFormat_Image(inputIMAGE);
	color_space=getColorSpace_Image(inputIMAGE);

/*	resultImage = new_Image(file_format,color_space,no_of_bands,no_of_rows,
				no_of_cols,data_type,data_format);*/
      resultImage = new_Image(file_format,color_space,no_of_bands,no_of_rows,
                                no_of_cols,CVIP_FLOAT,data_format);
	w=wsize/2;
    	for(bands=0; bands < no_of_bands; bands++) {
  	  image = getData_Image(inputIMAGE, bands);
	  imaget = getData_Image(resultImage,bands);
  	    for(r=w; r < no_of_rows-w; r++) 
     	      for(c=w; c < no_of_cols-w; c++){
		f=image[r][c];
		labar=0;
		for (r1=r-w;r1<=r+w;r1++)
		   for (c1=c-w; c1<=c+w; c1++) {
			fw=image[r1][c1];
			labar+=fw;
		   }
		labar=labar/wsize/wsize;
		if(w==0) labar=image[r][c];
		t1=image[r][c]/m;t1=m*(float)pow((double)t1,(double)(beta));
/*		t1=labar/m;t1=m*(float)pow((double)t1,(double)(beta));*/
		if(w==0) t2=image[r][c]; else t2=((float)image[r][c])/labar;
		t2=pow((double)t2,(double)alpha);		
		imaget[r][c]=(float)(t1+t2);
	      }
	}		
    	delete_Image(inputIMAGE);
	return remap_Image(resultImage,data_type,0,255);
}
/*Lee's Algorithm apples equation : 
old name: lee		newname: ace2_filter
**fbar[r][c]=alpha*A[r][c]+beta*(f[r][c]-A[r][c])*/
Image *ace2_filter(Image *inputIMAGE,int wsize,float alpha, float beta)
{
	float **image,**imaget,
			f,fbar,
			f1bar,abar,fw;
	int r,c,bands,i,j,wmin=3,w=0,k=0,r1,c1,z,w1,m=256;
        unsigned int 	no_of_rows,	/* number of rows in image */
			no_of_cols,	/* number of columns in image */
			no_of_bands,	/* number of image bands */
			data_type,
			data_format,
			file_format,
			color_space;
	Image *resultImage;

/*        if(alpha<0 ||alpha>1 || beta<0 || beta >1) return NULL;*/

	cast_Image(inputIMAGE,CVIP_FLOAT);
        no_of_bands = getNoOfBands_Image(inputIMAGE);
        no_of_rows =  getNoOfRows_Image(inputIMAGE);
        no_of_cols =  getNoOfCols_Image(inputIMAGE);
	data_type=getDataType_Image(inputIMAGE);
	data_format=getDataFormat_Image(inputIMAGE);
	file_format=getFileFormat_Image(inputIMAGE);
	color_space=getColorSpace_Image(inputIMAGE);

	resultImage = new_Image(file_format,color_space,no_of_bands,no_of_rows,
				no_of_cols,data_type,data_format);
	w=wsize/2;
    	for(bands=0; bands < no_of_bands; bands++) {
  	  image = getData_Image(inputIMAGE, bands);
	  imaget = getData_Image(resultImage,bands);
  	    for(r=w; r < no_of_rows-w; r++) 
     	      for(c=w; c < no_of_cols-w; c++){
		f=image[r][c];
		abar=0;
		for (r1=r-w;r1<=r+w;r1++)
		   for (c1=c-w; c1<=c+w; c1++) {
			fw=image[r1][c1];
			abar+=fw;
		   }
		abar=abar/wsize/wsize;
		f1bar=abar*alpha+beta*(f-abar);
		imaget[r][c]=(float)f1bar;
	      }
	}		
	resultImage=remap_Image(resultImage,CVIP_BYTE,0,255);
    	delete_Image(inputIMAGE);
	return resultImage;
}
/* new lee algorithm 1 applies equation:
** old name: new_lee1		new name: log_ace_filter
** log(fbar[r][c])= alpha*log(A[r][c])+beta*(log(1-f[r][c]/m)-log(A[r][c]));
** fbar[r][c]= m*(1-exp(log(fbar[r][c])))
*/ 
Image *log_ace_filter(Image *inputIMAGE,int wsize,float alpha, float beta)
{
	float **image,**imaget,
			f,fbar,
			lfbar,f1bar,lf1bar,labar,fw,fwbar,lfwbar;
	int r,c,bands,i,j,wmin=3,w=0,k=0,r1,c1,z,w1,m=256;
        unsigned int 	no_of_rows,	/* number of rows in image */
			no_of_cols,	/* number of columns in image */
			no_of_bands,	/* number of image bands */
			data_type,
			data_format,
			file_format,
			color_space;
	Image *resultImage;

/*	if(alpha<0 ||alpha>1 || beta<0 || beta >1) return NULL;*/

	cast_Image(inputIMAGE,CVIP_FLOAT);
        no_of_bands = getNoOfBands_Image(inputIMAGE);
        no_of_rows =  getNoOfRows_Image(inputIMAGE);
        no_of_cols =  getNoOfCols_Image(inputIMAGE);
	data_type=getDataType_Image(inputIMAGE);
	data_format=getDataFormat_Image(inputIMAGE);
	file_format=getFileFormat_Image(inputIMAGE);
	color_space=getColorSpace_Image(inputIMAGE);


	resultImage = new_Image(file_format,color_space,no_of_bands,no_of_rows,
				no_of_cols,data_type,data_format);
	w=wsize/2;
    	for(bands=0; bands < no_of_bands; bands++) {
  	  image = getData_Image(inputIMAGE, bands);
	  imaget = getData_Image(resultImage,bands);
  	    for(r=w; r < no_of_rows-w; r++) 
     	      for(c=w; c < no_of_cols-w; c++){
		f=image[r][c]; fbar=1-f/m; lfbar=log(fbar);
		labar=0;
		for (r1=r-w;r1<=r+w;r1++)
		   for (c1=c-w; c1<=c+w; c1++) {
			fw=image[r1][c1]; fwbar=1-fw/m; lfwbar=log(fwbar);
			labar+=lfwbar;
		   }
		labar=labar/wsize/wsize;
		lf1bar=labar*alpha+beta*(lfbar-labar);
		f1bar=m*(1-exp(lf1bar));
		imaget[r][c]=(float)f1bar;
	      }
	}		
	resultImage=remap_Image(resultImage,CVIP_BYTE,0,255);
    	delete_Image(inputIMAGE);
	return resultImage;
}
