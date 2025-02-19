/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: rotate.c
*           Description: new rotate function replacing the old one
*         Related Files: 
*   Initial Coding Date: Tue Apr  8 17:22:02 CDT 1997
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Sreenivas Makam
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1996 SIUE - by Scott Umbaugh and Sreenivas Makam.
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
** $Log: rotate.c,v $
** Revision 1.14  1998/03/30 19:53:38  smakam
** included history stuff in the image
**
** Revision 1.13  1997/07/02 22:38:28  smakam
** made copypoint and setpoint functions extern so that they can be accessed by functions from outside like dct.c
**
** Revision 1.12  1997/04/10 23:13:38  smakam
** Copied the history information
**
** Revision 1.11  1997/04/08 23:51:28  smakam
** Removed unwanted lines
**
** Revision 1.10  1997/04/08 22:26:32  smakam
** changed function name
**
** Revision 1.9  1997/04/08 22:23:58  smakam
** replace the old none
**
*
****************************************************************************/

#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPimage.h"
#define pi 3.14159265358979323846

extern void copypoint(Image *,unsigned int ,unsigned int ,unsigned int ,Image *,unsigned int,unsigned int );

/* Function prototype for copying data values from the old image                 to the new image */
extern void setpoint(Image *,unsigned int, unsigned int ,unsigned int,double,double);
/* Function prototype for setting the  values of new image not present in the old image */


Image *rotate(Image *inputIMAGE,float degrees)
{
	
	float rads;/* Radians of rotation */
	Image *newIMAGE;/* Contains the rotated image */
	unsigned int  no_of_rows,     /* number of rows in image */
                      no_of_cols,     /* number of columns in image */
                      no_of_bands;    /* number of image bands */
	unsigned int  rows,/* row index */
		      cols,/* column index */
		      bands;/* band index */
	float rcorners[4],/* Four corners of the image */
	      ccorners[4];
	float new_row_min,
	      new_row_max,
	      new_col_min,
	      new_col_max;
	IMAGE_FORMAT image_format;
    	COLOR_FORMAT color_space;
    	CVIP_TYPE  data_type;
    	FORMAT data_format;
	unsigned int newimgrows,
	             newimgcols;/* Number of rows and columns in the new image */
	float inter,/* To store the intermediate values*/
	      inter1;
	float oldrowcos,
	      oldrowsin,
	      oldcolcos,
	      oldcolsin,
	      old_row,
	      old_col;
	int count;
	HISTORY stuff;
	float *hptr;

     
rads=degrees*pi/180;
rcorners[0]=0;
rcorners[1]=0;
ccorners[0]=0;
ccorners[2]=0;
rcorners[2]=(getNoOfRows_Image(inputIMAGE))-1;
rcorners[3]=(getNoOfRows_Image(inputIMAGE))-1;
ccorners[1]=(getNoOfCols_Image(inputIMAGE))-1;
ccorners[3]=(getNoOfCols_Image(inputIMAGE))-1;
new_row_min=0;
new_col_min=0;
new_row_max=0;
new_col_max=0;
newimgrows=0;
newimgcols=0;
for(count=0;count<4;count++)
	{
	 
	 inter=rcorners[count]*cos(rads)+ccorners[count]*sin(rads);
	 if(inter<new_row_min)
		new_row_min=inter;
	 if(inter>new_row_max)
		new_row_max=inter;
	 inter1=-rcorners[count]*sin(rads)+ccorners[count]*cos(rads);
	 if(inter1<new_col_min)
		new_col_min=inter1;	
	 if(inter1>new_col_max)
		new_col_max=inter1;
	}	
newimgrows=(unsigned)ceil((double)new_row_max-new_row_min);
newimgcols=(unsigned)ceil((double)new_col_max-new_col_min);
data_type=getDataType_Image(inputIMAGE);
data_format=getDataFormat_Image(inputIMAGE);
image_format=getFileFormat_Image(inputIMAGE);
color_space=getColorSpace_Image(inputIMAGE);
no_of_bands = getNoOfBands_Image(inputIMAGE);
no_of_rows = getNoOfRows_Image(inputIMAGE);
no_of_cols = getNoOfCols_Image(inputIMAGE);
newIMAGE=image_allocate(image_format,color_space,no_of_bands,newimgrows,newimgcols,data_type,data_format);
/* The following command is to copy the history information*/
history_copy(inputIMAGE,newIMAGE);
for(bands=0;bands<no_of_bands;bands++)
{
   for(rows=0;rows<newimgrows;rows++)
   {
	for(cols=0;cols<newimgcols;cols++)
	{
	   oldrowcos=((float)rows+new_row_min)*cos(-rads);
	   oldrowsin=((float)rows+new_row_min)*sin(-rads);
	   oldcolcos=((float)cols+new_col_min)*cos(-rads);
	   oldcolsin=((float)cols+new_col_min)*sin(-rads);
	   old_row=oldrowcos+oldcolsin;
	   old_col=-oldrowsin+oldcolcos;
	   old_row=ceil((double)old_row);
	   old_col=ceil((double)old_col);
	   if((old_row>=0)&&(old_row<no_of_rows)&&
	      (old_col>=0)&&(old_col<no_of_cols))
	   {
              copypoint(newIMAGE,bands,rows,cols,inputIMAGE,(unsigned)old_row,(unsigned)old_col);
	   }
	   else
	     setpoint(newIMAGE,bands,rows,cols,0,0);
	}
    }
}
stuff=(HISTORY)malloc(sizeof(struct history));
stuff->packetP = (PACKET *)malloc(sizeof(PACKET));
stuff->packetP->dsize=1;
stuff->packetP->dtype=(CVIP_TYPE *)malloc(sizeof(CVIP_TYPE));
stuff->packetP->dtype[0]=CVIP_FLOAT;
hptr=(float *)malloc(sizeof(float));
hptr[0]=degrees;
stuff->packetP->dptr = (void**)malloc(sizeof(void*));
stuff->packetP->dptr[0]=(void *)hptr;
stuff->next=(HISTORY)NULL;
stuff->ftag=ROTATE;
history_add(newIMAGE, stuff);
stuff=NULL;
return newIMAGE;
}



extern  void copypoint(Image *newIMAGE,unsigned int bands,unsigned int rows,unsigned int cols,Image *inputIMAGE,unsigned int old_row,unsigned int old_col)
{
     CVIP_TYPE data_type;
     FORMAT data_format;

     data_type=getDataType_Image(inputIMAGE);
     data_format=getDataFormat_Image(inputIMAGE);
     switch(data_type)
     {
	case CVIP_BYTE:
		  ((byte **)(newIMAGE->image_ptr[bands]->rptr))[rows][cols]=((byte **)(inputIMAGE->image_ptr[bands]->rptr))[old_row][old_col];
		  if(data_format==COMPLEX)
		  ((byte **)(newIMAGE->image_ptr[bands]->iptr))[rows][cols]= ((byte **)(inputIMAGE->image_ptr[bands]->iptr))[old_row][old_col];
		  break;

	case CVIP_SHORT:
		  ((short **)(newIMAGE->image_ptr[bands]->rptr))[rows][cols]= ((short **)(inputIMAGE->image_ptr[bands]->rptr))[old_row][old_col];           
		  if(data_format==COMPLEX)
		  ((short **)(newIMAGE->image_ptr[bands]->iptr))[rows][cols]= ((short **)(inputIMAGE->image_ptr[bands]->iptr))[old_row][old_col];           
		  break;

	case CVIP_INTEGER:
		  ((int **)(newIMAGE->image_ptr[bands]->rptr))[rows][cols]=((int **)(inputIMAGE->image_ptr[bands]->rptr))[old_row][old_col];
		  if(data_format==COMPLEX)
		  ((int **)(newIMAGE->image_ptr[bands]->iptr))[rows][cols]=((int **)(inputIMAGE->image_ptr[bands]->iptr))[old_row][old_col];
		  break;

	case CVIP_FLOAT:
		  ((float **)(newIMAGE->image_ptr[bands]->rptr))[rows][cols]=((float **)(inputIMAGE->image_ptr[bands]->rptr))[old_row][old_col];
		  if(data_format==COMPLEX)
((float **)(newIMAGE->image_ptr[bands]->iptr))[rows][cols]=((float **)(inputIMAGE->image_ptr[bands]->iptr))[old_row][old_col];
		  break;

	case CVIP_DOUBLE:
		  ((double **)(newIMAGE->image_ptr[bands]->rptr))[rows][cols]=((double **)(inputIMAGE->image_ptr[bands]->rptr))[old_row][old_col];
		  if(data_format==COMPLEX)
		  ((double **)(newIMAGE->image_ptr[bands]->iptr))[rows][cols]=((double **)(inputIMAGE->image_ptr[bands]->iptr))[old_row][old_col];
		  break;
      }
	
}



extern  void setpoint(Image *newIMAGE,unsigned int bands, unsigned int rows,unsigned int cols,double rdata,double idata)
{
	CVIP_TYPE data_type;

	data_type=getDataType_Image(newIMAGE);
	switch(data_type)
	{
	     case CVIP_BYTE:
		       ((byte **)(newIMAGE->image_ptr[bands]->rptr))[rows][cols]=(byte)rdata;
		       if(data_type==COMPLEX)
			  ((byte **)(newIMAGE->image_ptr[bands]->iptr))[rows][cols]=(byte)idata;
		       break;
		 
	     case CVIP_SHORT:
		       ((short **)(newIMAGE->image_ptr[bands]->rptr))[rows][cols]=(short)rdata;
		       if(data_type==COMPLEX)
		       ((short **)(newIMAGE->image_ptr[bands]->iptr))[rows][cols]=(short)idata;
		       break;
		 

	     case CVIP_INTEGER:
		       ((int **)(newIMAGE->image_ptr[bands]->rptr))[rows][cols]=(int)rdata;
		       if(data_type==COMPLEX)

		       ((int **)(newIMAGE->image_ptr[bands]->iptr))[rows][cols]=(int)idata;
			break;
		 

	     case CVIP_FLOAT:
		        ((float **)(newIMAGE->image_ptr[bands]->rptr))[rows][cols]=(int)rdata;
		       if(data_type==COMPLEX)
((float **)(newIMAGE->image_ptr[bands]->iptr))[rows][cols]=(int)idata;         
		       break;
		 

	     case CVIP_DOUBLE:
		       ((double **)(newIMAGE->image_ptr[bands]->rptr))[rows][cols]=(double)rdata;
		       if(data_type==COMPLEX)
		       ((double **)(newIMAGE->image_ptr[bands]->iptr))[rows][cols]=(double)idata;
		       break;
	}
}
		 




