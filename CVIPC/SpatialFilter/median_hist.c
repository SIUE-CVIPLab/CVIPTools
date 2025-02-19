/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: median_hist.c
*	    Description: This file contains the functions necessary to
*			 perform a fast median filter based on the histogram
*			 method.
*         Related Files: program_invoke.c
*   Initial Coding Date: Wed May 10 16:33:31 CDT 1995
*           Portability: Standard (ANSI) C
*             Credit(s): Frank Smith, Mark Zuke, Arve Kjoelen
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1995 SIUE - by Scott Umbaugh
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
*************************************************************************/
#include <CVIPspfltr.h>
#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPimage.h"
#include "CVIPxformfilter.h"
#include "CVIPtransform.h"
#include <math.h>


void swap2(float x[], int i,int j);

Image *median_hist(Image *inputImage)
{	int 	size;
               
	printf("This program performs a fast median filter\n");
        printf("using an NxN mask.\n");
        printf("Please enter an odd integer for N, 3 or greater.\n");
	printf("Your choice for N : ");
        scanf("%d", &size);
	if(size<3 || !(size%2) || (size>(int)inputImage->image_ptr[0]->rows) || (size>(int)inputImage->image_ptr[0]->cols)) {
		fprintf(stderr, "Invalid parameter, returning...\n");
		return((Image *)NULL);
	}
	return median_filter(inputImage, size); 
} 


static int median_sort(int a[], int n)
{
	int i,j;
	int temp;

	for (i=0;i<n-1;i++)
		for (j=n+1;j<n;j++)
			if (a[i]>a[j])
			{
			   temp = a[i];
			   a[i] = a[j];
			   a[j] = temp;
			}
	return NULL; 
}

Image *median_filter(Image *inputImage, int size)  
{
 	Image		*outputImage;  
	MATRIX		*p_matrix;   
	HISTORY		h_story;
    	byte 		**image, *bP,  **out;/* 2-d matrix data pointer */
	int 		y,		/* row index */
			x, 		/* column index */
			bands,		/* band index */
                        choice,
                        i,j,k,g,t,th,q,w,
                        temp,pixel,**pix,
			**p,
			*mhist;
          unsigned int  mdn, z, var,ltmdn;
          int  		*curwin;
          int           done=CVIP_NO;
			
	unsigned int 	rows, 		/* number of rows in image */
			cols,		/* number of columns in image */
			no_of_bands;	/* number of image bands */

	int margins;

        th=((size*size)-1)/2;
	curwin=(int *)malloc(sizeof(int)*size*size);
	mhist=(int *)calloc(256, sizeof(int));
	if(inputImage->image_ptr[0]->data_type>CVIP_INTEGER) {
		fprintf(stdout, "Warning:you will lose precision with this operation, as your\n");
		fprintf(stdout, "data is being cast from CVIP_FLOAT or CVIP_DOUBLE to CVIP_INTEGER\n");
		cast_Image(inputImage, CVIP_INTEGER);
	}
	outputImage=(Image *)clone_Image(inputImage, inputImage->image_ptr[0]->data_type);
	history_copy(inputImage, outputImage);

	no_of_bands = getNoOfBands_Image(inputImage);
	rows =  getNoOfRows_Image(inputImage);
	cols =  getNoOfCols_Image(inputImage);  

	p_matrix=new_Matrix(rows, cols,  CVIP_INTEGER, REAL);
	p=(int **)p_matrix->rptr;    
                          
	for(bands=0; bands < no_of_bands; bands++)
	{
          	/*
		** reference each band of image data in 2-d matrix form;
		** which is used for reading and writing the pixel values
		*/
  		image = getData_Image(inputImage, bands);
                out = getData_Image(outputImage, bands);
                 
	copy_Matrix(inputImage->image_ptr[bands], p_matrix);

 /******************************************************************/
	for(y=0; y<rows-size; y++)
        {
	   for(x=0; x<cols-size; x++)
              {
	         if (x==0)                    /* Reset histogram, mdn*/
                                              /* and ltmdn*/
                 {
                    for (var=0;var<=255;var++)
		    {
                       mhist[var]=0;
                    }
         	    mdn=0;
              	    ltmdn=0;

                    for(t=y;t<=((y+size)-1); t++)     /* create window*/ 
                       for(z=x;z<=((x+size)-1);z++)
		       {
	                  mhist[(p[t][z])]++;
                          curwin[size*(t-y)+(z-x)]=p[t][z];
                       }
                       median_sort(curwin,(size*size));

                       mdn=curwin[((size*size)/2)-1];
                      
                       for(g=0;g<(size*size);g++)
                          if(curwin[g]<mdn) ltmdn++;
                }
                else
		{

                    /* loop that moves histogram that delete leftmost column*/
                    /* and rightmost column*/
                    for(t=y;t<=y+size-1;t++)
		    {
                       if(image[t][x-1]<mdn) ltmdn--;
                       if(image[t][x+size-1]<mdn)ltmdn++;
                       mhist[image[t][x+size-1]]++;
                       mhist[image[t][x-1]]--;
                    }
                    if (ltmdn>th)
                    {
                       do
                       {
                          mdn--;
                          ltmdn=ltmdn-mhist[mdn];

                          
                       }
                       while (ltmdn>th);
		    }
		    else 
	            {
                       while (ltmdn+mhist[mdn]<=th)
		       {
                          ltmdn=ltmdn+mhist[mdn];
                          mdn++;
                       }
                    }
		out[y+(size-1)/2][x+(size-1)/2]=mdn;         
     		  }
	     }         
	}
    }

	margins = (size - 1)/2;

	//handle borders (use original pixel values)
	for (bands = 0; bands < no_of_bands; bands ++)
	{
		image = getData_Image(inputImage, bands);
        out = getData_Image(outputImage, bands);

		//top margin
		for (x = 0; x < margins + 1; x++)
			for (y = 0; y < cols; y++)
				out[x][y] = image[x][y];

		//bottom margin
		for (x = rows - margins - 1; x < rows; x++)
			for (y = 0; y < cols; y++)
				out[x][y] = image[x][y];
		
		//left margin
		for (x = 0; x < rows; x++)
			for (y = 0; y < margins + 1; y++)
				out[x][y] = image[x][y]; 
		
		//right margin
		for (x = 0; x < rows; x++)
			for (y = cols - margins - 1; y < cols; y++)
				out[x][y] = image[x][y];
	}

    /* Add history information */
    h_story=(HISTORY)malloc(sizeof(struct history));
    h_story->next=(HISTORY)NULL;
    h_story->packetP=(PACKET *)malloc(sizeof(PACKET));
    h_story->packetP->dtype=(CVIP_TYPE *)malloc(sizeof(CVIP_TYPE));
    *(h_story->packetP->dtype)=CVIP_INTEGER;
    h_story->packetP->dsize=1;
    h_story->packetP->dptr = (void**)malloc(sizeof(void*));
    h_story->packetP->dptr[0]=(int *)malloc(sizeof(int));
    memcpy((void *)h_story->packetP->dptr[0], (void *)&size, sizeof(int));
    h_story->ftag=MEDIAN_FILTER;
    history_add(outputImage, h_story);
    delete_Image(inputImage);
    delete_Matrix(p_matrix);
    free(curwin);
    free(mhist);
    return (outputImage);
} 


Image *adapt_median_filter(Image *inputIMAGE,int wmax)
{
	float m[122];
	float **image,**imaget,xmed,xmin,xmax,t1,t2,u1,u2;
	int r,c,bands,i,j,wmin=3,ws=0,w=0,k=0,r1,c1,z,w1;
        unsigned int 	no_of_rows,	/* number of rows in image */
			no_of_cols,	/* number of columns in image */
			no_of_bands,	/* number of image bands */
			data_type,
			data_format,
			file_format,
			color_space;
	Image *resultImage;
	int margins, x, y, rows, cols;

	cast_Image(inputIMAGE,CVIP_FLOAT);
        no_of_bands = getNoOfBands_Image(inputIMAGE);
        rows = no_of_rows =  getNoOfRows_Image(inputIMAGE);
        cols = no_of_cols =  getNoOfCols_Image(inputIMAGE);
	data_type=getDataType_Image(inputIMAGE);
	data_format=getDataFormat_Image(inputIMAGE);
	file_format=getFileFormat_Image(inputIMAGE);
	color_space=getColorSpace_Image(inputIMAGE);

	resultImage = new_Image(file_format,color_space,no_of_bands,no_of_rows, no_of_cols,data_type,data_format);
	ws=(int)(wmax*.5);
	m[0]=0;

    	for(bands=0; bands < no_of_bands; bands++) {
  	  image = getData_Image(inputIMAGE, bands);
	  imaget = getData_Image(resultImage,bands);
  	    for(r=ws; r < no_of_rows-ws; r++) 
     	      for(c=ws; c < no_of_cols-ws; c++){
		   w1=wmin;
		   w=(int)(wmin*.5);
		   while (w1<=wmax) { /*window loop */
			k=1;		/*prepare data for sorting */
			for (r1=r-w;r1<=r+w;r1++)
		   	   for (c1=c-w; c1<=c+w; c1++) {
				m[k]=image[r1][c1]; k++;
		   	   }
			for (i=1;i<=w1*w1+1;i++)	/*sorting */
		   	   for (j=2;j<=w1*w1+1-i;j++)
				if (m[j-1]>m[j]) swap2(m,j-1,j);
			z=(w1*w1+1)/2;
			xmed=m[z];xmin=m[1];xmax=m[w1*w1];
	      		t2=xmed-xmax;t1=xmed-xmin;
	      		if (t1>0 && t2<0) { /*no impulse */
		   	   u1=image[r][c]-xmin; u2=image[r][c]-xmax;
		   	   if (u1>0 && u2<0){ /*uncorrupted */
			 	imaget[r][c]=image[r][c];
			   } 
		   	   else {imaget[r][c]=xmed;} /*corrupted */
			   w1=wmax+1;/*exit while loop */
	      		}
			else { /*has impulse */
			   imaget[r][c]=xmed;
		           w++;w1=w1+2;  /*increase window */
		   	}
	      	  } /*end of while loop */
	    } /* end of for c loop */
    	} /* end of for bands loop */

	margins = (wmax - 1)/2;

	//handle borders (use original pixel values)
	for (bands = 0; bands < no_of_bands; bands ++)
	{
		image = getData_Image(inputIMAGE, bands);
        imaget = getData_Image(resultImage, bands);

		//top margin
		for (x = 0; x < margins + 1; x++)
			for (y = 0; y < cols; y++)
				imaget[x][y] = image[x][y];

		//bottom margin
		for (x = rows - margins - 1; x < rows; x++)
			for (y = 0; y < cols; y++)
				imaget[x][y] = image[x][y];
		
		//left margin
		for (x = 0; x < rows; x++)
			for (y = 0; y < margins + 1; y++)
				imaget[x][y] = image[x][y]; 
		
		//right margin
		for (x = 0; x < rows; x++)
			for (y = cols - margins - 1; y < cols; y++)
				imaget[x][y] = image[x][y];
	}
	resultImage=remap_Image(resultImage,CVIP_BYTE,0,255);
    	delete_Image(inputIMAGE);
	return resultImage;
}
/* end of adapt_median_filter function */


void swap2(float x[], int i,int j)
{
        float t;
        t=x[i];
        x[i]=x[j];
        x[j]=t;
}  
