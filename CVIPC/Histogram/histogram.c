/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: histogram.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Thu Nov  2 17:04:33 CST 1995
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Dave Lyons
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1996 SIUE - by Scott Umbaugh.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
****************************************************************************/
/*RCS inf
 *$Author: ycheng $
 *$Id: histogram.c,v 1.21 2002/04/15 00:18:52 ycheng Exp $
 *$Log: histogram.c,v $
 *Revision 1.21  2002/04/15 00:18:52  ycheng
 *a typo mistake of 'original_hist' so that this file can't compile under windows.
 *
 *Revision 1.20  2002/02/10 20:48:43  rswamis
 *Changed the ifdef statements once again!!
 *
 *Revision 1.19  2002/02/10 20:06:25  rswamis
 *Once again changed the ifdef satements because the previous changes dint work with gcc complier!.
 *
 *Revision 1.18  2002/02/09 20:04:52  rswamis
 *Changed the hardcoded path of temporary files in hist_spec for windows
 *
 *Revision 1.17  1997/08/06 21:20:26  smakam
 *the rcs entries was updates
 *
 *Revision 1.16  1997/03/08 00:54:13  yawei
 *Name Changes:
 *	BOOLEAN ==> CVIP_BOOLEAN
 *	FALSE ==> CVIP_NO
 *	TRUE ==> CVIP_YES
 *	BYTE ==> CVIP_BYTE
 *	SHORT ==> CVIP_SHORT
 *	INTEGER ==> CVIP_INTEGER
 *	FLOAT ==> CVIP_FLOAT
 *	DOUBLE ==> CVIP_DOUBLE
 *	TYPE ==> CVIP_TYPE
 *
 *Revision 1.15  1997/01/22 15:47:14  yawei
 *Fixed hist_spec bug
 *
 * Revision 1.14  1997/01/16  21:02:17  yawei
 * Global Change:  Image_FORMAT ==> IMAGE_FORMAT
 *
 * Revision 1.13  1997/01/15  17:14:23  yawei
 * Global Change:  IMAGE ==> Image
 *
 * Revision 1.12  1996/12/31  22:19:36  yawei
 * changed function names/prototypes
 *
 * Revision 1.11  1996/12/30  18:59:35  yawei
 * histeq ==> static histeq_special
 *
 * Revision 1.10  1996/12/20  19:23:49  yawei
 * Use "view_Image" to display images.
 *
 * Revision 1.9  1996/09/07  00:15:28  yawei
 * changed viewer so image will be written to the temp dir
 *  with correct format.
 *
 * Revision 1.8  1996/09/04  22:21:27  yawei
 * added choice to viewer.
 *
 * Revision 1.7  1996/06/12  21:29:11  kluo
 * check in
 *
 * Revision 1.6  1996/01/30  21:21:54  kluo
 * check file into RCS
 *
 * Revision 1.5  1995/11/08  19:38:12  mzuke
 * corrected spelling error
 *
 * Revision 1.4  1995/11/02  23:06:42  mzuke
 * added header info
 *
 * Revision 1.3  1995/11/02  21:40:19  seu
 * modified messages so that only functions that work are listed.
 * also modied message to tell; user 'x' is gray level
 *
 * Revision 1.2  1995/10/30  17:44:14  mzuke
 * modified functions to go directly to
 * histogram specification
 *
 * Revision 1.1  1995/10/25  00:47:27  kluo
 * Initial revision
 *
 * Revision 1.4  1995/06/17  15:48:54  dlyons
 * No changes
 *
 * Revision 1.3  1995/06/17  15:11:29  dlyons
 * Redid RCS
 *
 */

#ifndef __HISTOGRAM_C
#define __HISTOGRAM_C

#define debugline(x)	printf("debug point %d\n",x)
#include <stdio.h>
#include "CVIPtoolkit.h"
#include "histogram.h"
#include "ee.h"

static void histeq_special(Image *imageP);
static void expandHistogram_Image(Image **imageP,IMAGE_FORMAT image_format,
	COLOR_FORMAT color_format);

typedef struct
	{
	char *name;
	void (*func)();
	} HISTFUNC;

HISTFUNC HistFunc[]=
	{
	{ "Histogram Equalization", histeq_special },
	{ "Histogram Specification", hist_spec_setup },
	{ "Create image of histogram", make_histogram_setup },
	{ 0 }
	};

extern char temp_dir[100];

float **get_histogram(Image *imageP)
	{
   	register byte *bP;
   	register int i,j,k;
   	unsigned bands,rows,cols;
		unsigned levels=0;
	float **histogram;
   
   	bands = getNoOfBands_Image(imageP);
   	rows =  getNoOfRows_Image(imageP);
   	cols =  getNoOfCols_Image(imageP);
	
	histogram=(float**)calloc((bands+1),sizeof(float*));
	if(!histogram)
		{
		printf("memory allocation error for float **histogram\n");
		return (float **)NULL;
		}
	for(i=0;i<bands;i++)
		{
		histogram[i]=(float*)calloc(256,sizeof(float));
		if(!histogram[i])
			{
			printf("Insufficient memory for histogram[%d]\n",i);
		return (float **)NULL;
			}
		}
	for(i=0;i<bands;i++)
		for(k=0;k<256;k++)
			histogram[i][k]=0.0;
   	for(i=0; i < bands; i++)
      		for(j=0; j < rows; j++)
			{
         		bP=(byte *)getRow_Image(imageP, j, i);
         		for(k=0; k < cols; k++, bP++)
				histogram[i][*bP]++;
      			}
	for(i=0;i<bands;i++)
		for(k=0;k<256;k++)
			histogram[i][k]/=(float)(rows*cols);
#ifdef DEBUG
	printf("  r  histogram \n");			
	printf("---------------\n");			
	for(i=0;i<256;i++)				
		printf("%4d %8d\n",i,histogram[0][i]);
#endif	
	return histogram;
}

/* Perform histogram equalization on image pointed to by imageP */
/************************************************************************/
static void histeq_special(Image *imageP)
	{
   	register byte 	*bP;
   	register int 	z, y, x;
   	unsigned bands, rows, cols;
	float **histogram,**T;

	if ( (histogram=get_histogram(imageP)) == (float **)NULL)
		return; /* do nothing */
   	bands = getNoOfBands_Image(imageP);
   	rows =  getNoOfRows_Image(imageP);
   	cols =  getNoOfCols_Image(imageP);

	/* Create cummulutive distribution function T[] */
	/****************************************************************/
	T=(float**)calloc(bands+1,sizeof(float*));
	for(z=0;z<bands;z++)
		{
		T[z]=(float*)calloc(256,sizeof(float));
		if(T[z])
			{
			T[z][0]=histogram[z][0];
			for(x=1;x<256;x++)
				T[z][x]=T[z][x-1]+histogram[z][x];
			}
		else
			{
			printf("Memory allocation failure\n");
			return; 
			}
		}
	T[bands]=NULL;
	/*****************************************************************/


	/* Equalize the histogram if the image pointer */
	/*****************************************************************/
	for(z=0;z<bands;z++)
      		for(y=0;y<rows;y++)
			{
         		bP=(byte *)getRow_Image(imageP,y,z);
         		for(x=0;x<cols;x++,bP++)
				*bP=(byte)(T[z][*bP]*255+0.5);
			}
	/*******************************************************************/

	/* Cleanup */
	/*******************************************************************/
	z=0;
	while(T[z])
		free(T[z++]);
	free(T);
	z=0;
	while(histogram[z])
		free(histogram[z++]);
	free(histogram);
	/********************************************************************/
	}

Image *hist_spec(Image *imageP, int mode, char **input){
	Image *ORIGHIST;
	Image *SPECHIST;
	Image *NEWHIST;
	char select;
	char filename[50];
	char *extension;
	char original_hist[150];
	char specified_hist[150];
	char result_hist[150];
	unsigned bands,z;
	float **histogram, **show_hist;
	IMAGE_FORMAT image_format;
	COLOR_FORMAT color_format;
	char buffer[100];


	#ifdef WIN32
	strcpy(original_hist,temp_dir);
	strcat(original_hist,"\ORIGINAL.HISTOGRAM.");
	strcpy(specified_hist,temp_dir);
	strcat(specified_hist,"\SPECIFIED.HISTOGRAM.");
	strcpy(result_hist,temp_dir);
	strcat(result_hist,"\RESULT.HISTOGRAM.");
	#else 
	strcpy(original_hist,temp_dir);
	strcat(original_hist,"/ORIGINAL.HISTOGRAM.");
	strcpy(specified_hist,temp_dir);
	strcat(specified_hist,"/SPECIFIED.HISTOGRAM.");
	strcpy(result_hist,temp_dir);
	strcat(result_hist,"/RESULT.HISTOGRAM.");
	#endif
	if(mode == 1)
	    histogram=define_histogram(getNoOfBands_Image(imageP), 1,
			(char**)&buffer);
	else 
	    histogram=define_histogram(getNoOfBands_Image(imageP), 0,input);



	image_format=getFileFormat_Image(imageP);
	color_format=getColorSpace_Image(imageP);
	if ( (ORIGHIST=get_histogram_Image(imageP)) == (Image *)NULL) {
		delete_Image(imageP);
		return (Image *)NULL;
	}
	extension=(char*)calloc(sizeof(char),4);
	switch(image_format)
		{
		case PBM:
			strcpy(extension,"pbm");
			break;
		case PGM:
			strcpy(extension,"pgm");
			break;
		case PPM:
			strcpy(extension,"ppm");
			break;
		case EPS:
			strcpy(extension,"eps");
			break;
		case TIF:
			strcpy(extension,"tif");
			break;
		case GIF:
			strcpy(extension,"gif");
			break;
		case RAS:
			strcpy(extension,"ras");
			break;
		case ITX:
			strcpy(extension,"itx");
			break;
		case CCC:
			strcpy(extension,"ccc");
			break;
		case BIN:
			strcpy(extension,"bin");
			break;
		case VIP:
			strcpy(extension,"vip");
			break;
		}
	strcat(original_hist,extension);
	strcat(specified_hist,extension);
	strcat(result_hist,extension);


//	view_Image(ORIGHIST,original_hist); 
	/*delete_Image(ORIGHIST);*/

	if ( (show_hist = get_histogram(imageP)) != (float **)NULL)
		showMax_histogram(show_hist,"Original");

	if ( (imageP = histogram_spec(imageP,histogram)) == (Image *)NULL)
		return (Image *)NULL;

	if (SPECHIST=make_histogram(histogram,image_format,color_format)) {
//		view_Image(SPECHIST,specified_hist);
		/*delete_Image(SPECHIST);*/
	}

	if ((NEWHIST=get_histogram_Image(imageP)) == (Image *)NULL) {
		delete_Image (imageP);
		/*return (Image *)NULL;*/
	} else {
//		view_Image(NEWHIST,result_hist);
		delete_Image(NEWHIST);
	}

	if ( (show_hist = get_histogram(imageP)) != (float **)NULL)
		showMax_histogram(show_hist,"Result");


	z=0;
	while(histogram[z]) free(histogram[z++]);
	free(histogram);
	return imageP; 
}
/**************************************************************************
**************************************************************************/
Image *spec_hist_images(Image *imageP, char **input)
{
	Image *SPECHIST;
	unsigned z;
	float **histogram;
	IMAGE_FORMAT image_format;
	COLOR_FORMAT color_format;

    histogram=define_histogram(getNoOfBands_Image(imageP), 0,input);

	image_format=getFileFormat_Image(imageP);
	color_format=getColorSpace_Image(imageP);

	SPECHIST=make_histogram(histogram,image_format,color_format);

	z = 0;
	while (histogram[z])
		free(histogram[z++]);
	free(histogram);
	return SPECHIST;
}
/**************************************************************************
**************************************************************************/
Image *histogram_spec(Image *imageP,float **SPEC)
{
	register byte *bP,pixel;
	int x,y,i,j,k,minval,minj;
	unsigned bands,rows,cols;
	float **G,**InvG;

   	bands = getNoOfBands_Image(imageP);
   	rows =  getNoOfRows_Image(imageP);
   	cols =  getNoOfCols_Image(imageP);

	G=(float**)malloc(sizeof(float*) * bands);
	InvG=(float**)malloc(sizeof(float*) * bands);
	for(i=0;i<bands;i++)
		{
		G[i]=(float*)malloc(sizeof(float) * 256);
		InvG[i]=(float*)malloc(sizeof(float) * 256);
		}

	histeq_special(imageP);
	for(k=0;k<bands;k++)
		{
		G[k][0]=SPEC[k][0]*255;
		for(i=1;i<256;i++)
			G[k][i]=G[k][i-1]+SPEC[k][i]*255;
		for(i=0;i<256;i++)
			{
			minval=abs(i-G[k][0]);
			minj=0;
			for(j=0;j<256;j++)
				{
				if(abs(i-G[k][j])<minval)
					{
					minval=abs(i-G[k][j]);
					minj=j;
					}
				InvG[k][i]=minj;
/*				printf("%d ", InvG[k][i]); */
				}
			}
		}
	for(i=0;i<bands;i++)
		for(y=0;y<rows;y++)
			{
         		bP = (byte *) getRow_Image(imageP, y, i);
			for(x=0;x<cols;x++,bP++)
				{
				pixel=(byte)(InvG[i][*bP]+0.5);
				*bP=pixel > 255 ? 255 : pixel;
				}
			}
	for(i=0;i<bands;i++)
		free(G[i]);
	free(G);
	for(i=0;i<bands;i++)
		free(InvG[i]);
	free(InvG);
	return imageP;
}

Image *get_histogram_Image(Image *imageP)
	{
	int i=0;
	float **histogram;
	Image *HI;

	histogram=get_histogram(imageP);
	if(!histogram)
		{
		printf("Insuffficient memory for float **histogram\n");
		return (Image *)NULL;
		}
	HI=make_histogram(histogram,getFileFormat_Image(imageP),getColorSpace_Image(imageP));
	while(histogram[i])
		free(histogram[i++]);
	free(histogram);
	return HI;
	}

Image *make_histogram(float **histogram,IMAGE_FORMAT image_format,
	COLOR_FORMAT color_format)
{
	register byte *bP;
	register int i,j,k;
	int bands=0;
	const int cols=512,rows=256;
	int *x;
	float histmax,*y;
	Image *HistIm;

	i=0;
	while(histogram[i++]) bands++;


	HistIm=new_Image(image_format,color_format,bands,256,512,CVIP_BYTE,REAL);
	if (HistIm == (Image *) NULL) return (Image *)NULL;

	x=(int *)calloc(cols,sizeof(int));
	if(!x)
		{
		printf("Insuffficient memory ");
		printf("for int *x");
		delete_Image(HistIm);
		return (Image *)NULL;
		}

	y=(float*)calloc(256,sizeof(float));
	if(!y)
		{
		printf("Insufficient memory ");
		printf("for float *y\n");
		delete_Image(HistIm);
		free(x);
		return (Image *)NULL;
		}


	for(i=0;i<cols;i++) x[i]=(int)(i*255/(cols-1))+0.5;

	for(i=0; i < bands; i++)
		{
		histmax=0.0;
		for(j=0;j<256;j++)
			if(histogram[i][j] > histmax)
				histmax=histogram[i][j];
	 	for(j=0;j<rows;j++)
			y[j]=(float)((rows-j)*histmax/rows);
		for(j=0; j<256; j++)
			{
         		bP=(byte*)getRow_Image(HistIm,j,i);
			for(k=0; k < cols; k++,bP++)
				if(y[j]<=histogram[i][x[k]])
					*bP=255;
				else
					*bP=0;	
      			}
		}
	if(bands==3)
		expandHistogram_Image(&HistIm,image_format,color_format);
	return HistIm;
	}

void showMax_histogram(float **histogram,char *title)
	{
	register int i,j;
	byte grey;
	float max;
	printf("**********************************************\n");
	printf("%s: Most Frequent Gray Level\n\n",title);
	i=0;
	while(histogram[i])
		{
		max=0;
		for(j=0;j<256;j++)
			if(histogram[i][j]>max)
				{
				max=histogram[i][j];
				grey=j;
				}
		printf("Band %d\n",i);
		printf("gray level = %d\n# most frequent/total # of pixels = %f\n",grey,max);
		printf("*********************************************\n");
		i++;
		}
	}

void histogram_show(float **histogram)
	{
	register int i,j,k,x;
	unsigned int bands=0;
	float y=0.0;

	while(histogram[bands++]);
	bands--;
	for(i=0;i<bands;i++)
		for(j=0;j<256;j++)
			y=histogram[i][j]>y ? histogram[i][j]:y;

	for(i=0;i<bands;i++)
		for(j=0;j<256;j++)
			{
			printf("%3d",j);
			x=(int)75*histogram[i][j]/y+0.5;
			for(k=0;k<x;k++)
				printf("*");
			printf("\n");
			}
	for(i=0;i<78;i++)
		printf("-");
	printf("\n");
	printf("  0");
	for(i=0;i<75/2-4;i++)
		printf(" ");
	printf("%8.6f",y/2);
	for(i=0;i<75/2-11;i++)
		printf(" ");
	printf("%8.6f\n",y);
	}

static void expandHistogram_Image(Image **imageP,IMAGE_FORMAT image_format,
	COLOR_FORMAT color_format)
{
	Image *NewImage;
	register byte *bPorig,*bPnew;
	register int x,y;


	NewImage=new_Image(image_format,color_format,3,3*256,512,CVIP_BYTE,REAL);

	for(y=0;y<256;y++)
		{
		bPorig=getRow_Image(*imageP,y,0);
		bPnew=getRow_Image(NewImage,y,0);
		for(x=0;x<512;x++,bPorig++,bPnew++) 
			*bPnew=*bPorig;
		}
	for(y=0;y<256;y++)
		{
		bPorig=getRow_Image(*imageP,y,1);
		bPnew=getRow_Image(NewImage,y+256,1);
		for(x=0;x<512;x++,bPorig++,bPnew++)
			*bPnew=*bPorig;
		}
	for(y=0;y<256;y++)
		{
		bPorig=getRow_Image(*imageP,y,2);
		bPnew=getRow_Image(NewImage,y+512,2);
		for(x=0;x<512;x++,bPorig++,bPnew++) 
			*bPnew=*bPorig;
		}
	delete_Image(*imageP);
	*imageP=duplicate_Image(NewImage);
	delete_Image(NewImage);
	}

/*interactive function */
float **define_histogram(int bands, int mode, char**eq)
	{
	register int z,x;
	float **histogram,y,ymin;

	histogram=(float**)calloc((bands+1),sizeof(float*));
	if(!histogram) return (float **)NULL;
	if(mode){
	printf("\nYou will specify the histogram modification equation for each band in the \nimage separately. The equation can include algebraic operators (+,-,*,/,^),\nand any of the following functions:\n\n");
   	printf("sin(arg)\tsinh(arg)\timp(arg)\tsqrt(arg)\n");
	printf("cos(arg)\tcosh(arg)\tfloor(arg)\tabs(arg)\n");  
	printf("tan(arg)\ttanh(arg)\tstep(arg)\tceil(arg)\n");
	printf("asin(arg)\texp(arg)\tu(arg)\t\tdeg(arg)\n");
	printf("acos(arg)\tramp(arg)\trad(arg)\n");
	printf("atan(arg)\tr(arg)\t\tlog(arg)\n\n");
	printf("For example, to specify a sine wave, at prompt enter: sin(0.025*x).\n");
	printf("To brighten the image, enter: x+25.\n\n");
	}
	for(z=0;z<bands;z++)
		{
		histogram[z]=(float*)calloc(256,sizeof(float));
		if(histogram[z])
			{
			fflush(stdin);
			if(mode){
			printf("Enter histogram equation for Band %d in terms of the gray level, 'x':\n",z+1);
			gets(*eq);
			}
			ymin=0;
			if(mode)
			    histogram[z]=eemain(256,*eq);
			else
			    histogram[z]=eemain(256,eq[z]);
			for(x=0;x<256;x++)
				{
				if(histogram[z][x]<ymin) ymin=histogram[z][x];
				}
			if(ymin<0)
				for(x=0;x<256;x++)
					histogram[z][x]-=ymin;
			y=0;
			for(x=0;x<256;x++)
				y+=histogram[z][x];
			for(x=0;x<256;x++)
				histogram[z][x]/=y;
			}
		}
	return histogram;
	}

void make_histogram_setup(Image *imageP)
	{
	Image *tempImage;
	tempImage=get_histogram_Image(imageP);
	delete_Image(imageP);
	imageP=duplicate_Image(tempImage);
	delete_Image(tempImage);
	}

/* Histogram Specification setup routine */
/************************************************************************/
void hist_spec_setup(Image *imageP)
	{
	hist_spec(imageP,1,NULL);
}

void histogram_setup(Image *imageP)
	{
	int quit=0;
	int choice;
	int i;

	while(!quit)
		{
		i=0;
		printf("\t\tHistogram Operations\n");
		printf("\t\t---------------------------\n\n");
		while(HistFunc[i].name)
			{
			printf("\t\t%2d. %s\n",i,HistFunc[i].name);
			++i;
			}
		printf("\t\t%2d. Return\n\n",i);
		printf("\t\t>> ");
		scanf("%d",&choice);
		printf("\n");
		if(choice >= 0 && choice < i)
			HistFunc[choice].func(imageP);
		else
			quit++;
		}
	}

#endif
