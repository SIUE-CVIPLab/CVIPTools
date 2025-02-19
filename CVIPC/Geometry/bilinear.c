/*
*	Bilinear Interpolation
*	Arve Kjoelen - akjoele@ee.siue.edu
*	Mon Oct 23 09:26:08 CDT 1995
*
*/
#include <stdio.h>
#include <math.h>
#include <CVIPimage.h>
#include <CVIPdef.h>
#include "bilinear.h"

Image *bilinear_setup(Image *inImg) {
	float sf;
	char *mystr=malloc(32);
	fprintf(stdout, "Please enter a scaling factor;\n");
	fprintf(stdout, "A number greater than 1 will enlarge\n");
	fprintf(stdout, "The image, while a number less than 1 will\n");
	fprintf(stdout, "shrink it.\n");
	sf=(float)atof(fgets(mystr, 31, stdin));

	return(Image *)bilinear_interp(inImg, sf);
}

/*
 * Bilinear Interpolation.  Takes a floating-point
 * number as input.  This scaling factor is used to 
 * enlarge or shrink the image.
 */
Image *bilinear_interp(Image *inImg, float factor) {
	int rows, cols;
	int i,j,k;		/* Counters */
	int *int_map;		/* Map of old coords to new coords */
	float *delta_map;	/* Map of interpolation coordinates */
	Image *outIm;

	rows=inImg->image_ptr[0]->rows;
	cols=inImg->image_ptr[0]->cols;

	i=(int)(float)(0.5+factor*(float)rows);
	j=(int)(float)(0.5+factor*(float)cols);
	int_map=(int *)malloc(sizeof(int)*(1+MAX(i,j)));
	delta_map=(float *)malloc(sizeof(float)*(1+MAX(i,j)));
	outIm=new_Image(inImg->image_format, inImg->color_space, inImg->bands, i, j, inImg->image_ptr[0]->data_type, inImg->image_ptr[0]->data_format);

	/* Calculate mappings */ 
	for(k=0; k<=MAX(i,j); k++) {
	   int_map[k]=(int)(float)((float)k/factor);
	   delta_map[k]=(float)(k/factor - (float)int_map[k]);
	}
	/* adjust limits so we don't overrun bounds */
	i--;j--;

	for(k=0; k<inImg->bands; k++) {
	   for(rows=0; rows<i; rows++) {
	      switch(inImg->image_ptr[0]->data_type) {
		 case CVIP_BYTE:
		    LOOP_BILINEAR(byte,rows,j,int_map,delta_map,(byte **)inImg->image_ptr[k]->rptr,(byte *)outIm->image_ptr[k]->rptr[rows])
	 	 break;
		 case CVIP_SHORT:
                    LOOP_BILINEAR(short,rows,j,int_map,delta_map,(short **)inImg->image_ptr[k]->rptr,(short *)outIm->image_ptr[k]->rptr[rows]);
		 break;
		 case CVIP_INTEGER:
                    LOOP_BILINEAR(int,rows,j,int_map,delta_map,(int **)inImg->image_ptr[k]->rptr,(int *)outIm->image_ptr[k]->rptr[rows]);
		 break;
		 case CVIP_FLOAT:
                    LOOP_BILINEAR(float,rows,j,int_map,delta_map,(float **)inImg->image_ptr[k]->rptr,(float *)outIm->image_ptr[k]->rptr[rows]);
	  	 break;
		 case CVIP_DOUBLE:
                    LOOP_BILINEAR(double,rows,j,int_map,delta_map,(double **)inImg->image_ptr[k]->rptr,(double *)outIm->image_ptr[k]->rptr[rows]);
		 break;
	      } /* switch */
	   } /* for (rows.. */
	} /* k */
	delete_Image(inImg);
	return(outIm);
}

#define SMALL_FLOAT_NUMBER_EPSILON 0.0000001

static float distance(float x1, float y1, float x2, float y2)
{
	float t1, t2;

	t1 = x1 - x2;
	t2 = y1 - y2;

	return (sqrt(t1*t1 + t2*t2));
}

static double interp(void **image1, int type, int rows, int cols, float r, float c)
{
	Matrix	*Ai, *Bi;
	double	**a, **b;
	double  k[4], temp[4];

	byte   **bimage1;
	short  **simage1;
	int    **iimage1;
	float  **fimage1;
	double **dimage1;

	int i, index;

	int left, right, top, bottom;
	float d[4], minValue;

	left  = (int)c;
	right = left+1;

	top   = (int)r;
	bottom= top+1;

	if (left < 0) left = 0;
	if (right >= cols) right = cols-1;
	if (top < 0) top = 0;
	if (bottom >= rows) bottom = rows-1;

	d[0] = distance(left, top, c, r);
	d[1] = distance(right, top, c, r);
	d[2] = distance(left, bottom, c, r);
	d[3] = distance(right, bottom, c, r);

	switch (type) {
	case CVIP_BYTE: 
		bimage1 = (byte **)(image1);
		temp[0] = bimage1[top][left];
		temp[1] = bimage1[top][right];
		temp[2] = bimage1[bottom][left];
		temp[3] = bimage1[bottom][right];
		break;
	case CVIP_SHORT: 
		simage1 = (short **)(image1);
		temp[0] = simage1[top][left];
		temp[1] = simage1[top][right];
		temp[2] = simage1[bottom][left];
		temp[3] = simage1[bottom][right];
		break;
	case CVIP_INTEGER: 
		iimage1 = (int **)(image1);
		temp[0] = iimage1[top][left];
		temp[1] = iimage1[top][right];
		temp[2] = iimage1[bottom][left];
		temp[3] = iimage1[bottom][right];
		break;
	case CVIP_FLOAT: 
		fimage1 = (float **)(image1);
		temp[0] = fimage1[top][left];
		temp[1] = fimage1[top][right];
		temp[2] = fimage1[bottom][left];
		temp[3] = fimage1[bottom][right];
		break;
	case CVIP_DOUBLE: 
		dimage1 = (double **)(image1);
		temp[0] = dimage1[top][left];
		temp[1] = dimage1[top][right];
		temp[2] = dimage1[bottom][left];
		temp[3] = dimage1[bottom][right];
		break;
	}

	if (d[0] < SMALL_FLOAT_NUMBER_EPSILON) return temp[0];
	if (d[1] < SMALL_FLOAT_NUMBER_EPSILON) return temp[1];
	if (d[2] < SMALL_FLOAT_NUMBER_EPSILON) return temp[2];
	if (d[3] < SMALL_FLOAT_NUMBER_EPSILON) return temp[3];

	Ai = new_Matrix(4,4,CVIP_DOUBLE, REAL);
	if(Ai == NULL)
	return(0);

	a = (double **)Ai->rptr;

	a[0][0] = top;
	a[0][1] = left;
	a[0][2] = top*left;
	a[0][3] = 1;

	a[1][0] = top;
	a[1][1] = right;
	a[1][2] = top*right;
	a[1][3] = 1;

	a[2][0] = bottom;
	a[2][1] = left;
	a[2][2] = bottom*left;
	a[2][3] = 1;

	a[3][0] = bottom;
	a[3][1] = right;
	a[3][2] = bottom*right;
	a[3][3] = 1;

	Bi = invert_Matrix(Ai);
	delete_Matrix(Ai);
	if(Bi == NULL) {
		index = 0;
		minValue = d[0];
		for (i = 1; i < 4; i++) {
			if (minValue > d[i]) {
				index = i;
				minValue = d[i];
			}
		}
		return temp[index]; //Zero order
	}

	b = (double **)Bi->rptr;

	for (i = 0; i < 4; i++) {
		k[i] = b[i][0] * temp[0] + 
			   b[i][1] * temp[1] + 
			   b[i][2] * temp[2] + 
			   b[i][3] * temp[3];
	}

	delete_Matrix(Bi);

	return (k[0]*r + k[1]*c + k[2]*r*c + k[3]);
}

/*
 * Linear Interpolation.
 */
Image *bilinear_interp1(Image *inImg, float xfactor, float yfactor) {
	int rows, cols, newrows, newcols;
	int i,j,k;		/* Counters */
	Image *outIm;
	byte   **bimage1, **bimage2;
	short  **simage1, **simage2;
	int    **iimage1, **iimage2;
	float  **fimage1, **fimage2;
	double **dimage1, **dimage2;
	int edger, edgec;

	if (xfactor <= 0.0 || yfactor <= 0.0) return inImg;

	rows=inImg->image_ptr[0]->rows;
	cols=inImg->image_ptr[0]->cols;

	newrows=(int)(float)(0.5+yfactor*(float)rows);
	newcols=(int)(float)(0.5+xfactor*(float)cols);
	yfactor= (float)newrows/rows;
	xfactor= (float)newcols/cols;
	edger = (int)(ceil((double)yfactor));
	edgec = (int)(ceil((double)xfactor));

	outIm=new_Image(inImg->image_format, inImg->color_space, inImg->bands, newrows, newcols, inImg->image_ptr[0]->data_type, inImg->image_ptr[0]->data_format);

	switch(inImg->image_ptr[0]->data_type) {
		 case CVIP_BYTE:
			for(k=0; k<inImg->bands; k++) {
	  			bimage1 = getData_Image(inImg, k);
  				bimage2 = getData_Image(outIm, k);
			   for(i=0; i<newrows-edger; i++) {
				   for(j=0; j<newcols-edgec; j++) {
					   bimage2[i][j] = (byte)interp(bimage1, CVIP_BYTE, rows, cols, (float)(i)/yfactor, (float)(j)/xfactor);
				   }
				   for(j=newcols-edgec; j<newcols; j++)
					   bimage2[i][j] = (byte)bimage2[i][j-1];
			   }
			   for(i=newrows-edger; i<newrows; i++)
				   for(j=0; j<newcols; j++)
					   bimage2[i][j] = (byte)bimage2[i-1][j];
			}
		 break;
		 case CVIP_SHORT:
			for(k=0; k<inImg->bands; k++) {
	  			simage1 = getData_Image(inImg, k);
  				simage2 = getData_Image(outIm, k);
			   for(i=0; i<newrows-edger; i++) {
				   for(j=0; j<newcols-edgec; j++) {
					   simage2[i][j] = (short)interp(simage1, CVIP_SHORT, rows, cols, (float)(i)/yfactor, (float)(j)/xfactor);
				   }
				   for(j=newcols-edgec; j<newcols; j++)
					   simage2[i][j] = (short)simage2[i][j-1];
			   }
			   for(i=newrows-edger; i<newrows; i++)
				   for(j=0; j<newcols; j++)
					   simage2[i][j] = (short)simage2[i-1][j];
			}
		 break;
		 case CVIP_INTEGER:
			for(k=0; k<inImg->bands; k++) {
	  			iimage1 = getData_Image(inImg, k);
  				iimage2 = getData_Image(outIm, k);
			   for(i=0; i<newrows-edger; i++) {
				   for(j=0; j<newcols-edgec; j++) {
					   iimage2[i][j] = (int)interp(iimage1, CVIP_INTEGER, rows, cols, (float)(i)/yfactor, (float)(j)/xfactor);
				   }
				   for(j=newcols-edgec; j<newcols; j++)
					   iimage2[i][j] = (int)iimage2[i][j-1];
			   }
			   for(i=newrows-edger; i<newrows; i++)
				   for(j=0; j<newcols; j++)
					   iimage2[i][j] = (int)iimage2[i-1][j];
			}
		 break;
		 case CVIP_FLOAT:
			for(k=0; k<inImg->bands; k++) {
	  			fimage1 = getData_Image(inImg, k);
  				fimage2 = getData_Image(outIm, k);
			   for(i=0; i<newrows-edger; i++) {
				   for(j=0; j<newcols-edgec; j++) {
					   fimage2[i][j] = (float)interp(fimage1, CVIP_FLOAT, rows, cols, (float)(i)/yfactor, (float)(j)/xfactor);
				   }
				   for(j=newcols-edgec; j<newcols; j++)
					   fimage2[i][j] = (float)fimage2[i][j-1];
			   }
			   for(i=newrows-edger; i<newrows; i++)
				   for(j=0; j<newcols; j++)
					   fimage2[i][j] = (float)fimage2[i-1][j];
			}
	  	 break;
		 case CVIP_DOUBLE:
			for(k=0; k<inImg->bands; k++) {
	  			dimage1 = getData_Image(inImg, k);
  				dimage2 = getData_Image(outIm, k);
			   for(i=0; i<newrows-edger; i++) {
				   for(j=0; j<newcols-edgec; j++) {
					   dimage2[i][j] = (double)interp(dimage1, CVIP_DOUBLE, rows, cols, (float)(i)/yfactor, (float)(j)/xfactor);
				   }
				   for(j=newcols-edgec; j<newcols; j++)
					   dimage2[i][j] = (double)dimage2[i][j-1];
			   }
			   for(i=newrows-edger; i<newrows; i++)
				   for(j=0; j<newcols; j++)
					   dimage2[i][j] = (double)dimage2[i-1][j];
			}
		 break;
    } /* switch */
	return(outIm);
}
