#include "CVIPdef.h"
#include "CVIPimage.h"
#include "CVIPspfltr.h"
#include "CVIPdrawimg.h"
#include "CVIPmatrix.h"
#include "CVIPtoolkit.h"
#include "CVIPconvert.h"



/* PG Macros */
#define PG_MAX(a,b)  (a>b? a: b)
#define PG_MIN(a,b)  (a<b? a: b)
#define SMALL_FLOAT_NUMBER_EPSILON 0.0000001

typedef unsigned char  PGbyte;
typedef          char  PGchar;
typedef unsigned short PGushort;
typedef          short PGshort; 
typedef unsigned int   PGuint;
typedef          int   PGint;
typedef float          PGfloat;
typedef double         PGdouble;
typedef void           PGvoid;

/* Allocates a matrix of doubles with range [nrl..nrh][ncl..nch] */
PGdouble **pgDmatrix(nrl,nrh,ncl,nch)
     int nrl,nrh,ncl,nch;
{
   int j;
   long bufsize,bufptr;
   PGdouble **m;
   
   bufsize = (nrh-nrl+1)*sizeof(PGdouble*)
      + (nrh-nrl+1)*(nch-ncl+1)*sizeof(PGdouble);
   
   m=(PGdouble **) malloc(bufsize);
   if (!m) fprintf(stderr, "allocation failure 1 in pgDmatrix()");
   m -= nrl;
   
   bufptr = ((long) (m+nrl)) + (nrh-nrl+1)*sizeof(PGdouble*);
   for(j=nrl;j<=nrh;j++) {
      m[j] = ((PGdouble *) (bufptr+(j-nrl)*(nch-ncl+1)*sizeof(PGdouble)));
      m[j] -= ncl;
   }
   
   return m;
}

/* Frees a matrix allocated by dmatrix */
PGvoid pgFreeDmatrix(m,nrl,nrh,ncl,nch)
     PGdouble **m;
     int nrl,nrh,ncl,nch;
{
   free((char*) (m+nrl));
   return;
}

typedef struct UV
{
	double **u;
	double **v;
}UV;

UV* GVFC(int YN, int XN, double *f, double *ou, double *ov, double mu, int ITER)
{
	UV *uv;
   double mag2, temp, tempx, tempy, fmax, fmin;
   int count, x, y, XN_1, XN_2, YN_1, YN_2;
   
   PGdouble **fx, **fy, **u, **v, **Lu, **Lv, **g, **c1, **c2, **b;
   
   /* define constants and create row-major double arrays */
   XN_1 = XN - 1;
   XN_2 = XN - 2;
   YN_1 = YN - 1;
   YN_2 = YN - 2;
   fx = pgDmatrix(0,YN_1,0,XN_1);
   fy = pgDmatrix(0,YN_1,0,XN_1);
   u  = pgDmatrix(0,YN_1,0,XN_1);
   v  = pgDmatrix(0,YN_1,0,XN_1);
   Lu = pgDmatrix(0,YN_1,0,XN_1);
   Lv = pgDmatrix(0,YN_1,0,XN_1);
   g  = pgDmatrix(0,YN_1,0,XN_1);
   c1 = pgDmatrix(0,YN_1,0,XN_1);
   c2 = pgDmatrix(0,YN_1,0,XN_1);
   b  = pgDmatrix(0,YN_1,0,XN_1);

   uv = (UV *)malloc(sizeof(UV));
   uv->u = (double **)malloc(YN*sizeof(double *));
   uv->v = (double **)malloc(YN*sizeof(double *));
   for (x = 0; x < XN; x++)
   {
	   uv->u[x] = (double *)malloc(XN*sizeof(double));
	   uv->v[x] = (double *)malloc(XN*sizeof(double));
   }
   

   /************** I: Normalize the edge map to [0,1] **************/
   fmax = -1e10;
   fmin = 1e10;
   for (x=0; x<=YN*XN-1; x++) {
      fmax = PG_MAX(fmax,f[x]);
      fmin = PG_MIN(fmin,f[x]);
   }

   if (fmax==fmin) 
      fprintf(stderr, "Edge map is a constant image.");      

   for (x=0; x<=YN*XN-1; x++)
      f[x] = (f[x]-fmin)/(fmax-fmin);

   //checked

   /**************** II: Compute edge map gradient *****************/
   /* I.1: Neumann boundary condition: 
    *      zero normal derivative at boundary 
    */
   /* Deal with corners */
   fx[0][0] = fy[0][0] = fx[0][XN_1] = fy[0][XN_1] = 0;
   fx[YN_1][XN_1] = fy[YN_1][XN_1] = fx[YN_1][0] = fy[YN_1][0] = 0;

   /* Deal with left and right column */
   for (y=1; y<=YN_2; y++) {
      fx[y][0] = fx[y][XN_1] = 0;
      fy[y][0] = 0.5 * (f[y+1] - f[y-1]);
      fy[y][XN_1] = 0.5 * (f[y+1 + XN_1*YN] - f[y-1 + XN_1*YN]);
   }

   /* Deal with top and bottom row */
   for (x=1; x<=XN_2; x++) {
      fy[0][x] = fy[YN_1][x] = 0;
      fx[0][x] = 0.5 * (f[(x+1)*YN] - f[(x-1)*YN]);
      fx[YN_1][x] = 0.5 * (f[YN_1 + (x+1)*YN] - f[YN_1 + (x-1)*YN]);
   }
   
   /* I.2: Compute interior derivative using central difference */
   for (y=1; y<=YN_2; y++)
   {
      for (x=1; x<=XN_2; x++) {
	 /* NOTE: f is stored in column major */
	 fx[y][x] = 0.5 * (f[y + (x+1)*YN] - f[y + (x-1)*YN]); 	 
	 fy[y][x] = 0.5 * (f[y+1 + x*YN] - f[y-1 + x*YN]);
      }
   }
   
   /******* III: Compute parameters and initializing arrays **********/
   temp = -1.0/(mu*mu);
   for (y=0; y<=YN_1; y++)
   {
      for (x=0; x<=XN_1; x++) {

	 tempx = fx[y][x];
	 tempy = fy[y][x];
	 /* initial GVF vector */
	 u[y][x] = tempx;
	 v[y][x] = tempy;

	 /* gradient magnitude square */
	 mag2 = tempx*tempx + tempy*tempy;
	 //fprintf(log, "%.1lf ", u[y][x]);
	 
	 g[y][x] = mu;
	 b[y][x] = mag2;

	 c1[y][x] = b[y][x] * tempx;
	 c2[y][x] = b[y][x] * tempy;
      }
	  //fprintf(log, "\n");
   }
      //fclose(log);
   
   /* free memory of fx and fy */
   pgFreeDmatrix(fx,0,YN_1,0,XN_1);
   pgFreeDmatrix(fy,0,YN_1,0,XN_1);

   //checked

   /************* Solve GVF = (u,v) iteratively ***************/
   for (count=1; count<=ITER; count++) {
      /* IV: Compute Laplace operator using Neuman condition */
      /* IV.1: Deal with corners */
      Lu[0][0] = (u[0][1] + u[1][0])*0.5 - u[0][0]; 
      Lv[0][0] = (v[0][1] + v[1][0])*0.5 - v[0][0];
      Lu[0][XN_1] = (u[0][XN_2] + u[1][XN_1])*0.5 - u[0][XN_1];
      Lv[0][XN_1] = (v[0][XN_2] + v[1][XN_1])*0.5 - v[0][XN_1];
      Lu[YN_1][0] = (u[YN_1][1] + u[YN_2][0])*0.5 - u[YN_1][0];
      Lv[YN_1][0] = (v[YN_1][1] + v[YN_2][0])*0.5 - v[YN_1][0];
      Lu[YN_1][XN_1] = (u[YN_1][XN_2] + u[YN_2][XN_1])*0.5 - u[YN_1][XN_1];
      Lv[YN_1][XN_1] = (v[YN_1][XN_2] + v[YN_2][XN_1])*0.5 - v[YN_1][XN_1];
      
      /* IV.2: Deal with left and right columns */
      for (y=1; y<=YN_2; y++) { 
	 Lu[y][0] = (2*u[y][1] + u[y-1][0] + u[y+1][0])*0.25 - u[y][0];
	 Lv[y][0] = (2*v[y][1] + v[y-1][0] + v[y+1][0])*0.25 - v[y][0];
	 Lu[y][XN_1] = (2*u[y][XN_2] + u[y-1][XN_1] 
			+ u[y+1][XN_1])*0.25 - u[y][XN_1];
	 Lv[y][XN_1] = (2*v[y][XN_2] + v[y-1][XN_1] 
			+ v[y+1][XN_1])*0.25 - v[y][XN_1];
      }
      
      /* IV.3: Deal with top and bottom rows */
      for (x=1; x<=XN_2; x++) { 
	 Lu[0][x] = (2*u[1][x] + u[0][x-1] + u[0][x+1])*0.25 - u[0][x];
	 Lv[0][x] = (2*v[1][x] + v[0][x-1] + v[0][x+1])*0.25 - v[0][x];
	 Lu[YN_1][x] = (2*u[YN_2][x] + u[YN_1][x-1] 
			+ u[YN_1][x+1])*0.25 - u[YN_1][x];
	 Lv[YN_1][x] = (2*v[YN_2][x] + v[YN_1][x-1] 
			+ v[YN_1][x+1])*0.25 - v[YN_1][x];
      }
      
      /* IV.4: Compute interior */
      for (y=1; y<=YN_2; y++)
	 for (x=1; x<=XN_2; x++) {
	    Lu[y][x] = (u[y][x-1] + u[y][x+1] 
			+ u[y-1][x] + u[y+1][x])*0.25 - u[y][x];
	    Lv[y][x] = (v[y][x-1] + v[y][x+1]
			+ v[y-1][x] + v[y+1][x])*0.25 - v[y][x];
	 }
      
      /******** V: Update GVF ************/
      for (y=0; y<=YN_1; y++)
	 for (x=0; x<=XN_1; x++) {
		 u[y][x] = (1- b[y][x])*u[y][x] + g[y][x]*Lu[y][x]*4 + c1[y][x];
		 v[y][x] = (1- b[y][x])*v[y][x] + g[y][x]*Lv[y][x]*4 + c2[y][x];
	 }
      
      /* print iteration number */
      printf("%5d",count);
      if (count%15 == 0)
	 printf("\n");
   }
   printf("\n");
   
   /* copy u,v to the output in column major order */
   for (y=0; y<=YN_1; y++)
      for (x=0; x<=XN_1; x++) {
	 uv->u[y][x] = ou[x*YN+y] = u[y][x];
	 uv->v[y][x] = ov[x*YN+y] = v[y][x];
      }

   /* free all the array memory */
   pgFreeDmatrix(u,0,YN_1,0,XN_1);
   pgFreeDmatrix(v,0,YN_1,0,XN_1);
   pgFreeDmatrix(Lu,0,YN_1,0,XN_1);
   pgFreeDmatrix(Lv,0,YN_1,0,XN_1);
   pgFreeDmatrix(g,0,YN_1,0,XN_1);
   pgFreeDmatrix(c1,0,YN_1,0,XN_1);
   pgFreeDmatrix(c2,0,YN_1,0,XN_1);
   pgFreeDmatrix(b,0,YN_1,0,XN_1);

   return uv;
}

void arrayMultiplication(double *A, double *B, double *C, int length)
{
	int i;

	for (i = 0; i < length; i ++)
		C[i] = A[i] * B[i];
}

void arrayMultiplication2(double **A, double **B, double **C, int r, int c)
{
	int i, j;

	for (i = 0; i < r; i ++)
		for (j = 0; j < c; j ++)
			C[i][j] = A[i][j] * B[i][j];
}

void arrayDivision(double *A, double *B, double *C, int length)
{
	int i;

	for (i = 0; i < length; i ++)
		C[i] = B[i] / A[i];
}

void arrayDivision2(double **A, double **B, double **C, int r, int c)
{
	int i, j;

	for (i = 0; i < r; i ++)
		for (j = 0; j < c; j ++)
			C[i][j] = A[i][j] / B[i][j];
}

void arrayAddition(double *A, double *B, double *C, int length)
{
	int i;

	for (i = 0; i < length; i ++)
		C[i] = A[i] + B[i];
}

void arrayAddition2(double **A, double **B, double **C, int r, int c)
{
	int i, j;

	for (i = 0; i < r; i ++)
		for (j = 0; j < c; j ++)
			C[i][j] = A[i][j] + B[i][j];
}

void array2DAddition(double **A, double **B, double **C, int length)
{
	int i, j;

	for (i = 0; i < length; i ++)
		for (j = 0; j < length; j ++)
			C[i][j] = A[i][j] + B[i][j];
}
void array2DMultiplication(double *A, double **B, double *C, int size)
{
	int i, j;
	double tempSum = 0;

	for (i = 0; i < size; i ++)
	{
		for (j = 0; j < size; j ++)
		{
			tempSum += A[i]*B[j][i];
		}
		C[i] = tempSum;
	}
}

Image* computeEdgeMap(Image *inputImage)
{
	Image *edgeImage;
	float **image;

	int no_of_rows, no_of_cols;
	int r, c;

	no_of_rows =  getNoOfRows_Image(inputImage);
	no_of_cols =  getNoOfCols_Image(inputImage);

	edgeImage = inputImage;

	if(edgeImage->bandP[0]->data_type != CVIP_FLOAT && cast_Image(edgeImage,CVIP_FLOAT))
	{
		fprintf(stderr,"Image is cast into float \n");
	}
	else if(edgeImage->bandP[0]->data_type != CVIP_FLOAT )
	{
		fprintf(stderr,"cast_Image failed..\n");
		delete_Image(edgeImage);
		return NULL;
	}

	image = (float **)getData_Image(edgeImage, 0);
	for(r=0; r < no_of_rows; r++) 
		for(c=0; c < no_of_cols; c++) 
		{
			image[r][c] = 1.0 - (double)(image[r][c]+1)/255.0;
     	}
	return edgeImage;
}

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

void snakeDeform(double *x, double *y, int size, double alpha, double beta, double gamma, double kappa, double **px, double **py, int iter)
{
	int i, j, k;
	double **A;
	double **diagGamma;
	double a, b, c, d, e;
	double tempA;
	double *vfx;
	double *vfy;
	double *tempx, *tempy;
	Matrix *temp;

	temp = new_Matrix(size, size, CVIP_DOUBLE, REAL);

	A = (double **)malloc(size*sizeof(double *));
	diagGamma = (double **)malloc(size*sizeof(double *));
	for (i = 0; i < size; i ++)
	{
		A[i] = (double *)malloc(size*sizeof(double));
		diagGamma[i] = (double *)malloc(size*sizeof(double));
	}
	vfx = (double *)malloc(size*sizeof(double));
	vfy = (double *)malloc(size*sizeof(double));
	tempx = (double *)malloc(size*sizeof(double));
	tempy = (double *)malloc(size*sizeof(double));

	a = e = beta;
	b = d = -alpha - 2*beta - 2*beta;
	c = alpha + alpha + beta + 4*beta + beta;


	for (i = 0; i < size; i ++)
		for (j = 0; j < size; j ++)
		{
			if (i == j)
			{
				A[i][j] = c;
				diagGamma[i][j] = gamma;
			}
			else if (i == (j - 1) || (i - 1) == j)
				A[i][j] = b;
			else if (i == (j - 2) || (i - 2) == j)
				A[i][j] = a;
			else
			{
				A[i][j] = 0;
				diagGamma[i][j] = 0;
			}
		}

	array2DAddition(A, diagGamma, A, size);

	for (i = 0; i < size; i ++)
	{
		for (j = 0; j < size; j ++)
		{
			tempA = A[i][j];
			(double)setRealVal_Matrix(temp, double, j, i, tempA);
		}
	}

	temp = invert_Matrix(temp);

	for (i = 0; i < size; i ++)
		for (j = 0; j < size; j ++)
			A[i][j] = (double)getRealVal_Matrix(temp, double, j, i);

	for (i = 0; i < iter; i ++)
	{
		//interpolation
		for (j = 0; j < size; j ++)
		{
			vfx[i] = interp(px, CVIP_DOUBLE, size/2 + 1, size/2 + 1, y[i], x[i]);
			vfy[i] = interp(py, CVIP_DOUBLE, size/2 + 1, size/2 + 1, y[i], x[i]);
		}

		for (j = 0; j < size; j ++)
		{
			x[j] = gamma*x[j] + kappa*vfx[j];
			//vfx[j] = kappa*vfx[j];
			y[j] = gamma*y[j] + kappa*vfy[j];
			//vfy[j] = kappa*vfy[j];
		}
		//arrayAddition(x, vfx, tempx, size);
		//arrayAddition(y, vfy, tempy, size);
		//deform snake
		//array2DMultiplication(tempx, A, x, size);
		//array2DMultiplication(tempy, A, y, size);
	}
	return;
}

Image* snakeSetup(Image *inputImage, int no_of_coords, int *rcList, int iteration_num, double alpha, double beta, double kappa)
{
	Image *originalImage;
	Image *magImage, *dirImage;
	byte **orImage;
	UV *uv;
	double *imageData;
	double *u, *v, *mag, *px, *py, *u2, *v2, *upv, *x, *y;
	float 	**image; 	/* 2-d matrix data pointer */
    int 		r,		/* row index */
			c,
			bands,
			pix_counter; 		/* column index */
			
    unsigned int 	no_of_rows,	/* number of rows in image */
			no_of_cols,	/* number of columns in image */
			no_of_bands;	/* number of image bands */

	double **mag2d;
	double **uu, **vv, **uu2, **vv2, **uu2pvv2, **px2d, **py2d;

	int *rptr, *cptr;
	int rdiff, cdiff, diff, re, arrpos, rdir, cdir, i, j, rcnt, ccnt;
	int minr, minc, maxr, maxc, ray_x, ray_y;
	int cstart, cend, count, rows, cols, row_offset, col_offset, temp; 
	float rincr, cincr;
	float high, low, var;
	int lRow, rRow, uRow, dRow, lCol, rCol, uCol, dCol;

    /*
    ** Gets the number of image bands (planes)
    */
    no_of_bands = getNoOfBands_Image(inputImage);

    /* 
    ** Gets the number of rows in the input image  
    */
    no_of_rows =  getNoOfRows_Image(inputImage);

    /* 
    ** Gets the number of columns in the input image  
    */
    no_of_cols =  getNoOfCols_Image(inputImage);

	//clone inputImage
	originalImage = duplicate_Image(inputImage);
	magImage = create_black(no_of_cols, no_of_rows);
	dirImage = create_black(no_of_cols, no_of_rows);

	//initial snake
	minr = no_of_rows;
	minc = no_of_cols;
	maxr = 0;
	maxc = 0;

	rptr = (int *)malloc(sizeof(int)*(no_of_rows*no_of_cols));
	cptr = (int *)malloc(sizeof(int)*(no_of_rows*no_of_cols));

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
	
	imageData = (double *)malloc(no_of_rows*no_of_cols*sizeof(double));
	u = (double *)malloc(no_of_rows*no_of_cols*sizeof(double));
	v = (double *)malloc(no_of_rows*no_of_cols*sizeof(double));
	u2 = (double *)malloc(no_of_rows*no_of_cols*sizeof(double));
	v2 = (double *)malloc(no_of_rows*no_of_cols*sizeof(double));
	upv = (double *)malloc(no_of_rows*no_of_cols*sizeof(double));
	mag = (double *)malloc(no_of_rows*no_of_cols*sizeof(double));
	px = (double *)malloc(no_of_rows*no_of_cols*sizeof(double));
	py = (double *)malloc(no_of_rows*no_of_cols*sizeof(double));
	x = (double *)malloc((no_of_coords/2)*sizeof(double));
	y = (double *)malloc((no_of_coords/2)*sizeof(double));
	mag2d = (double **)malloc(no_of_rows*sizeof(double *));
	uu = (double **)malloc(no_of_rows*sizeof(double *));
	vv = (double **)malloc(no_of_rows*sizeof(double *));
	uu2 = (double **)malloc(no_of_rows*sizeof(double *));
	vv2 = (double **)malloc(no_of_rows*sizeof(double *));
	uu2pvv2 = (double **)malloc(no_of_rows*sizeof(double *));
	px2d = (double **)malloc(no_of_rows*sizeof(double *));
	py2d = (double **)malloc(no_of_rows*sizeof(double *));
	for (r = 0; r < no_of_rows; r ++)
	{
		mag2d[r] = (double *)malloc(no_of_cols*sizeof(double));
		uu[r] = (double *)malloc(no_of_cols*sizeof(double));
		uu2[r] = (double *)malloc(no_of_cols*sizeof(double));
		vv[r] = (double *)malloc(no_of_cols*sizeof(double));
		vv2[r] = (double *)malloc(no_of_cols*sizeof(double));
		uu2pvv2[r] = (double *)malloc(no_of_cols*sizeof(double));
		px2d[r] = (double *)malloc(no_of_cols*sizeof(double));
		py2d[r] = (double *)malloc(no_of_cols*sizeof(double));
	}

	uv = (UV *)malloc(sizeof(UV));
	uv->u = (double **)malloc(no_of_cols*sizeof(double *));
	uv->v = (double **)malloc(no_of_cols*sizeof(double *));
	for (r = 0; r < no_of_rows; r++)
	{
		uv->u[r] = (double *)malloc(no_of_rows*sizeof(double));
		uv->v[r] = (double *)malloc(no_of_rows*sizeof(double));
	}


	for ( r = 0; r < no_of_rows*no_of_cols; r ++)
	{
		u[r] = 0.0;
		v[r] = 0.0;
	}

	// convert color image to gray-scale
	if (no_of_bands > 1)
		inputImage = lum_average(inputImage);

	//compute edge-map
	//inputImage = computeEdgeMap(inputImage);
	low = 1.0;
	high = 1.0;
	var = 0.5;
	inputImage = canny_filter (low, high, var, inputImage, magImage, dirImage);

	if(inputImage->bandP[0]->data_type != CVIP_FLOAT && cast_Image(inputImage,CVIP_FLOAT))
	{
		fprintf(stderr,"Image is cast into float \n");
	}
	else if(inputImage->bandP[0]->data_type != CVIP_FLOAT )
	{
		fprintf(stderr,"cast_Image failed..\n");
		delete_Image(inputImage);
		return NULL;
	}

	image = (float **)getData_Image(inputImage, 0);

	pix_counter = 0;
	for (c = 0; c < no_of_cols; c ++)
		for (r = 0; r < no_of_rows; r ++)
		{
			//store image in column-major
			imageData[pix_counter] = image[r][c];
			pix_counter ++;
		}

	uv = GVFC(no_of_rows, no_of_cols, imageData, u, v, 0.2, 4);	

	//arrayMultiplication(u, u, u2, no_of_cols*no_of_rows);
	//arrayMultiplication(v, v, v2, no_of_cols*no_of_rows);
	//arrayAddition(u2, v2, upv, no_of_cols*no_of_rows);

	//arrayMultiplication2(uu, uu, uu2, no_of_rows, no_of_cols);
	//arrayMultiplication2(vv, vv, vv2, no_of_rows, no_of_cols);
	//arrayAddition2(uu2, vv2, uu2pvv2, no_of_rows, no_of_cols);

	for (r = 0; r < no_of_rows; r ++)
		for (c = 0; c < no_of_cols; c ++)
		{
			mag2d[r][c] = sqrt(pow(uv->u[r][c], 2) + pow(uv->v[r][c], 2));
			px2d[r][c] = uv->u[r][c] / (mag2d[r][c] + 1e-5);
		}

	//arrayDivision2(uu, mag2d, px2d, no_of_rows, no_of_cols);
	//arrayDivision2(vv, mag2d, py2d, no_of_rows, no_of_cols);

	//initial snake
	r = 0;
	for(i = 0; i < no_of_coords; i+=2) 
	{
		x[r] = *(rcList+i);
		y[r] = *(rcList+i+1);
		r++;
	}

	uRow = no_of_rows - 1;
	lCol = no_of_cols - 1;
	dRow = 0;
	rCol = 0;
	for (r = 0; r < no_of_coords/2; r ++)
	{
		if (x[r] < uRow)
		{
			uRow = x[r];
			uCol = y[r];
		}
		if (y[r] < lCol)
		{
			lCol = y[r];
			lRow = x[r];
		}
		if (x[r] > dRow)
		{
			dRow = x[r];
			dCol = y[r];
		}
		if (y[r] > rCol)
		{
			rCol = y[r];
			rRow = x[r];
		}
	}

	for (bands = 0; bands < no_of_bands; bands ++)
	{
		orImage = getData_Image(originalImage, bands);
		for (r = 0; r < no_of_rows; r ++)
			for (c = 0; c < no_of_cols; c ++)
			{
				if ( r > uRow && r < dRow && c > lCol && c < rCol)
					if (image[r][c] == 255)
						orImage[r][c] = 255;

			}
	}

	//iteratively deform the snake
	// gamma is constant = 1
	for (r = 0; r < iteration_num; r ++)
		snakeDeform(x, y, no_of_coords/2, alpha, beta, 1, kappa, px2d, py2d, 5);

	/***********/
	//minr = no_of_rows;
	//minc = no_of_cols;
	//maxr = 0;
	//maxc = 0;

	//rptr = (int *)malloc(sizeof(int)*(no_of_rows*no_of_cols)); 
	//cptr = (int *)malloc(sizeof(int)*(no_of_rows*no_of_cols));

	///* need to interpolate inbetween corrdinates to find missing rows */
	//no_of_coords -=2;
	//arrpos = 0;

	//  for(i=0; i<no_of_coords; i+=2) {
 //   /* Save original coordinates into new row and column lists */
 //   rptr[arrpos] = *(rcList+i);
 //   cptr[arrpos] = *(rcList+i+1);
 //   arrpos++;
 //   
 //   /* determine if each row coordinate is either increasing, decreasing 
 //    * or staying the same.  
 //    */
 //   
 //   if(!(
	// (((*(rcList+i)-1) == *(rcList+i+2)) && ((*(rcList+i+1)-1) == *(rcList+i+3))) ||
	// (((*(rcList+i)) == *(rcList+i+2)) && ((*(rcList+i+1)-1) == *(rcList+i+3))) ||
	// (((*(rcList+i)+1) == *(rcList+i+2)) && ((*(rcList+i+1)-1) == *(rcList+i+3))) ||
	// (((*(rcList+i)-1) == *(rcList+i+2)) && ((*(rcList+i+1)) == *(rcList+i+3))) ||
	// (((*(rcList+i)+1) == *(rcList+i+2)) && ((*(rcList+i+1)) == *(rcList+i+3))) ||
	// (((*(rcList+i)-1) == *(rcList+i+2)) && ((*(rcList+i+1)+1) == *(rcList+i+3))) ||
	// (((*(rcList+i)) == *(rcList+i+2)) && ((*(rcList+i+1)+1) == *(rcList+i+3))) ||
	// (((*(rcList+i)+1) == *(rcList+i+2)) && ((*(rcList+i+1)+1) == *(rcList+i+3)))
	// )) {
 //     
 //     /* find row and column differences */
 //     rdiff = *(rcList+i+2) - *(rcList+i);
 //     cdiff = *(rcList+i+3) - *(rcList+i+1);
 //     
 //     /* calculate the increment amount */
 //     rincr = fabs ((rdiff*1.0)/cdiff);
 //     cincr = fabs ((cdiff*1.0)/rdiff);
 //     rdir = 1;
 //     cdir = 1;
 //     
 //     if(abs(rdiff) >= abs(cdiff)) {
	//re = abs(rdiff);
	//rincr = 1;
 //     }
 //     else {
	//re = abs(cdiff);
	//cincr = 1;
 //     }
 //     
 //     if(rdiff == 0) {
	//cincr = 1;
 //     }
 //     
 //     if(cdiff == 0) {
	//rincr = 1;
 //     }
 //     
 //     /* Determine the direction of the next pixel */
 //     if(rdiff < 0) {
	//rdir = -1;
	//if(cdiff < 0) {
	//  cdir = -1;
	//}
 //     } 
 //     else if(rdiff > 0) {
	//rdir = 1;
	//if(cdiff < 0) {
	//  cdir = -1;
	//}	
 //     }
 //     else {
	//
	//rdir = 0;
	//
	//if(cdiff < 0) {
	//  cdir = -1;
	//}	
 //     }
 //     
 //     
 //     for(r=1; r<re; r++) {
	//rptr[arrpos] = (int) (*(rcList+i)+(rdir)*((float) rincr*r));
	//cptr[arrpos] = (int) (*(rcList+i+1)+ (cdir)*((float) cincr*r));
	//arrpos++;
 //     }
 //   }
 // }
	/***********/

	/* Draw border of image */
	//if (no_of_bands != 1)
	//{
	//	for (bands = 0; bands < no_of_bands; bands ++)
	//		orImage = getData_Image(originalImage, bands);
	//		for(j=0; j<arrpos; j++)
	//		{
	//			if (bands == 0)
	//				orImage[*(rptr+j)][*(cptr+j)] = 0;
	//			else if (bands == 1)
	//				orImage[*(rptr+j)][*(cptr+j)] = 0;
	//			else
	//				orImage[*(rptr+j)][*(cptr+j)] = 0;
	//		}
	//}
	//else
	//{
	//	orImage = getData_Image(originalImage, 0);
	//	for(j=0; j<arrpos; j++)
	//		orImage[*(rptr+j)][*(cptr+j)] = 0;
	//}

	//remap_Image(inputImage, CVIP_BYTE, 0, 255);
	return originalImage;
}
