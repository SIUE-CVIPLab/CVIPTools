/**************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: object_crop.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Wed Feb 23 07:45:46 CST 2000
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): 
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1996 SIUE - by Scott Umbaugh and .
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
** $Log: object_crop.c,v $
** Revision 1.6  2001/11/10 18:33:54  rswamis
** Removed the printf statements
**
** Revision 1.5  2001/11/10 18:33:10  cvip
** ycheng checked in this file for cpohl according to his request.
**
** Revision 1.4  2000/04/19 21:20:01  cpohl
** Modified cropping function to return border images.
**
** Revision 1.3  2000/03/30 03:40:19  cpohl
** Object cropping working!!!!!
**
** Revision 1.2  2000/02/29 20:46:20  cpohl
** Function compiles and runs but not sure if correct.
**
** Revision 1.1  2000/02/23 13:46:58  cpohl
** Initial revision
**
*
****************************************************************************/
#include <ctype.h>
#include "CVIPdef.h"
#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPimage.h"
#include "CVIPgeometry.h"
#include "DermVis.h"
#include "SeedFill.h"

void MinMax(int *array_ptr, int num_array, int *min, int *max);
int getSeedPoint(Image *imgP, int *ray_x, int *ray_y);
void fillObject( Matrix *mP, int nv, int x, int y, int x_min, int y_min, int x_max, int y_max);

/* This function takes in a pointer to an image, the number of coordinates
 * in the list and a pointer to an array of alternating row then column 
 * coordinates.  This returns a cropped image based on the coordinate list 
 * passed in. 
 */
Image *object_crop(Image *imgP,int no_of_coords,int *rcList, int format, int Rvalue, int Gvalue, int Bvalue) {

  byte **image, **outimage, **tempimage;
  Image *OimgP, *timgP, *oimgP;
  
  unsigned int no_of_bands, no_rows, no_cols;
  Matrix *origP;
  HISTORY stuff;
  CVIP_TYPE img_type;
  IMAGE_FORMAT file_format;	 
  COLOR_FORMAT color_space;
  
  byte color;
  int *rptr, *cptr;
  int rdiff, cdiff, diff, re, arrpos, rdir, cdir,r,c,i,j,rcnt,ccnt;
  int minr, minc, maxr, maxc, ray_x, ray_y;
  int cstart, cend, count, rows, cols, row_offset, col_offset, temp; 
  float rincr, cincr; 
    
  no_rows = getNoOfRows_Image(imgP);
  no_cols = getNoOfCols_Image(imgP);
  
  /* Initialize min and max values*/  
  minr = no_rows;
  minc = no_cols;
  maxr = 0;
  maxc = 0;
  
  rptr = (int *)malloc(sizeof(int)*(no_rows*no_cols));
  cptr = (int *)malloc(sizeof(int)*(no_rows*no_cols));
  
  /* need to interpolate inbetween corrdinates to find missing rows */
  no_of_coords -=2;
  arrpos = 0;
  
  for(i=0; i<no_of_coords; i+=2) {
    /* Save original coordinates into new row and column lists */
    rptr[arrpos] = *(rcList+i);
    cptr[arrpos] = *(rcList+i+1);
    arrpos++;
    
    /* determine if each row coordinate is either increasing, decreasing 
     * or staying the same.  
     */
    
    if(!(
	 (((*(rcList+i)-1) == *(rcList+i+2)) && ((*(rcList+i+1)-1) == *(rcList+i+3))) ||
	 (((*(rcList+i)) == *(rcList+i+2)) && ((*(rcList+i+1)-1) == *(rcList+i+3))) ||
	 (((*(rcList+i)+1) == *(rcList+i+2)) && ((*(rcList+i+1)-1) == *(rcList+i+3))) ||
	 (((*(rcList+i)-1) == *(rcList+i+2)) && ((*(rcList+i+1)) == *(rcList+i+3))) ||
	 (((*(rcList+i)+1) == *(rcList+i+2)) && ((*(rcList+i+1)) == *(rcList+i+3))) ||
	 (((*(rcList+i)-1) == *(rcList+i+2)) && ((*(rcList+i+1)+1) == *(rcList+i+3))) ||
	 (((*(rcList+i)) == *(rcList+i+2)) && ((*(rcList+i+1)+1) == *(rcList+i+3))) ||
	 (((*(rcList+i)+1) == *(rcList+i+2)) && ((*(rcList+i+1)+1) == *(rcList+i+3)))
	 )) {
      
      /* find row and column differences */
      rdiff = *(rcList+i+2) - *(rcList+i);
      cdiff = *(rcList+i+3) - *(rcList+i+1);
      
      /* calculate the increment amount */
      rincr = fabs ((rdiff*1.0)/cdiff);
      cincr = fabs ((cdiff*1.0)/rdiff);
      rdir = 1;
      cdir = 1;
      
      if(abs(rdiff) >= abs(cdiff)) {
	re = abs(rdiff);
	rincr = 1;
      }
      else {
	re = abs(cdiff);
	cincr = 1;
      }
      
      if(rdiff == 0) {
	cincr = 1;
      }
      
      if(cdiff == 0) {
	rincr = 1;
      }
      
      /* Determine the direction of the next pixel */
      if(rdiff < 0) {
	rdir = -1;
	if(cdiff < 0) {
	  cdir = -1;
	}
      } 
      else if(rdiff > 0) {
	rdir = 1;
	if(cdiff < 0) {
	  cdir = -1;
	}	
      }
      else {
	
	rdir = 0;
	
	if(cdiff < 0) {
	  cdir = -1;
	}	
      }
      
      
      for(r=1; r<re; r++) {
	rptr[arrpos] = (int) (*(rcList+i)+(rdir)*((float) rincr*r));
	cptr[arrpos] = (int) (*(rcList+i+1)+ (cdir)*((float) cincr*r));
	arrpos++;
      }
    }
  }
 
	/* Get Min and Max values */
  MinMax(rptr, arrpos, &minr, &maxr);
  MinMax(cptr, arrpos, &minc, &maxc);
    
  /* Get current Image Information */
  file_format = getFileFormat_Image(imgP);
  color_space = getColorSpace_Image(imgP);
  no_of_bands = getNoOfBands_Image(imgP); 
  img_type = getDataType_Image(imgP);
  
  /* Create a new output Image */ 
  OimgP = new_Image(file_format, color_space, no_of_bands, (maxr-minr)+2, (maxc-minc)+2, img_type, REAL);
  timgP = new_Image(file_format, GRAY_SCALE, 1, no_rows, no_cols, CVIP_BYTE, REAL);
    
  	tempimage = getData_Image(timgP, 0);

   	for(r=0; r < no_rows; r++) 
     	for(c=0; c < no_cols; c++) 
	tempimage[r][c] = 0;
    
    /* Draw border of image */ 
    for(j=0; j<arrpos; j++) {
      tempimage[*(rptr+j)][*(cptr+j)] = 255;
    }
    origP = getBand_Image(timgP, 0);
    ray_y = minr + (maxr - minr)/2;
    ray_x = minc + (maxc - minc)/2;
    getSeedPoint(timgP, &ray_x, &ray_y);
    fillObject(origP, 255, ray_x, ray_y, minc, minr, maxc, maxr); 
    
    setBand_Image(timgP,origP,0);
    
    
    if(format == 2) {
     
		delete_Image(OimgP);
		delete_Image(imgP);
  		free(rptr);
  		free(cptr);
  		return(timgP);
    }
    else if(format == 1)  {	
      for(i=0; i < no_of_bands; i++) {
	image = getData_Image(imgP, i);
	outimage = getData_Image(OimgP, i);
	rcnt = 0;
	for(r=minr; r<=maxr; r++) {
	  ccnt=0;
	  for(c=minc; c<=maxc; c++) {
	    outimage[rcnt][ccnt] = tempimage[r][c]&image[r][c];
	    ccnt++;
	  }
	  rcnt++;
	}
	
      } 
//			delete_Matrix(origP);
			delete_Image(timgP);
			delete_Image(imgP);
  free(rptr);
  free(cptr);

  return(OimgP);
	 }
  else {
  oimgP = new_Image(file_format, color_space, no_of_bands, no_rows, no_cols, img_type, REAL);
    for(i=0; i < no_of_bands; i++) {
      image = getData_Image(imgP, i);
      outimage = getData_Image(oimgP, i);
      if(i == 0) 
				color = Rvalue;
      else if(i == 1)
				color = Gvalue;
      else if(i == 2) 
				color = Bvalue;

    	for(r=0; r < no_rows; r++) 
      	for(c=0; c < no_cols; c++) 
	outimage[r][c] = image[r][c];
      for(j=0; j<arrpos; j++) 
	{
		outimage[*(rptr+j)][*(cptr+j)] = color;
        }
    }
//			delete_Matrix(origP);
			delete_Image(OimgP);
			delete_Image(timgP);
			delete_Image(imgP);

  free(rptr);
  free(cptr);

  return(oimgP);
  }

}


void fillObject( Matrix *mP, int nv, int x, int y, int x_min, int y_min, int x_max, int y_max)
{

	Window *regionP;
	byte **dP;

        regionP = (Window *) malloc(sizeof(Window));

        regionP->x0 = x_min;
        regionP->x1 = x_max;
        regionP->y0 = y_min;
        regionP->y1 = y_max;
	dP = (byte **) getData_Matrix(mP);
        fill( dP, x, y, regionP, nv);
	free(regionP);
}



int getSeedPoint(Image *imP, int *ray_x, int *ray_y)
{

	byte		**bP;
	register int	y, x, w, e, n, s;
	unsigned	rows, cols;
	CVIP_BOOLEAN		firstpoint = CVIP_YES;
	CVIP_BOOLEAN west = CVIP_NO;
	CVIP_BOOLEAN east = CVIP_NO;
	CVIP_BOOLEAN north = CVIP_NO;
	CVIP_BOOLEAN south = CVIP_NO;
	int startx, starty;	

	startx = *ray_x;
	starty = *ray_y;

	rows = getNoOfRows_Image(imP);
	cols = getNoOfCols_Image(imP);

  bP = getData_Image(imP, 0);

	for(y=starty; y < rows; y++) {
		for(x=startx; x < cols; x++) {
			west = CVIP_NO;
			east = CVIP_NO;
			north = CVIP_NO;
			south = CVIP_NO;
		
			if(bP[y][x] != 255) {
			  for(w=x; w > 0; w--) {
					if(bP[y][w] == 255) 
						west = CVIP_YES;
				}
			  for(e=x; e < cols; e++) {
					if(bP[y][e] == 255) 
						east = CVIP_YES;
				}
			  for(n=y; n > 0; n--) {
					if(bP[n][x] == 255) 
						north = CVIP_YES;
				}
			  for(s=y; s < rows; s++) {
					if(bP[s][x] == 255) 
						south = CVIP_YES;
				}

				if((west & east & north & south)&&
						(bP[y-1][x-1] == 0) &&
						(bP[y][x-1] == 0) &&
						(bP[y+1][x-1] == 0) &&
						(bP[y-1][x] == 0) &&
						(bP[y+1][x] == 0)&&
						(bP[y-1][x+1] == 0) &&
						(bP[y][x+1] == 0) &&
						(bP[y+1][x+1] == 0)) {
					*ray_y = y;
					*ray_x = x;
					return 1;
				}
			}
		}	
	}	

	return 0;
	
}
 
void MinMax(int *array_ptr, int num_array, int *min, int *max) {

  int i;
  /* Find min and max row positions */
  for(i=0; i<num_array; i++) {
    if(array_ptr[i] < *min) {
      *min = array_ptr[i];
    }
    if(array_ptr[i] > *max) {
      *max = array_ptr[i];
    }
  }
  return;
}
