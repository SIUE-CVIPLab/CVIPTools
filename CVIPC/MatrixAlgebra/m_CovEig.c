/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: m_CovEig.c
*           Description: contains all of the necessary modules to find the
*			 covariance matrix and eigenvectors of a matrix.
*         Related Files: pct.h, Imakefile
*   Initial Coding Date: Sun May 30 14:48:13 CDT 1993
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
** $Log: m_CovEig.c,v $
** Revision 1.6  1998/04/19 02:41:48  achomai
** Cleaned up :
** 1) vector
**    - Changed the function definition to ANSI-C style.
**    - Made the function return NULL if memory allocation failed.
** 2) matrix :
**    - Changed the function definition to ANSI-C style.
**    - Made the function return NULL if memory allocation failed.
** 3) NICfree_matrix :
**    - Changed the function definition to ANSI-C style.
** 4) jacobi :
**    - Removed "float *vector()" from the variable list to solve
**      confusion whether it is a function pointer or a prototype of
**      the "vector" static function.
** 5) covariance_Matrix :
**    - Made the function check if matrix_allocate returned NULL.
**    - Replaced "vecfree" with "delete_Matrix" to do cleanup correctly.
** 6) eigenSystem_Matrix :
**    - Made the function check if matrix_allocate, vector , and matrix
**      returned NULL.
**    - Removed the function prototype "void eigsrt()" from the function
**      body to fix confusion.
**
** Revision 1.5  1997/07/26 17:51:39  smakam
** nade corrections woith respect to nu,merical recipes
**
** Revision 1.4  1997/06/03 02:24:46  yawei
** combined routines from nrutil.c
**
** Revision 1.3  1997/03/08 00:55:11  yawei
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
** Revision 1.2  1997/01/16 21:12:44  yawei
** updated changes
**
 * Revision 1.1  1994/10/30  17:58:40  hanceg
 * CVIPtools1.0 source file - G. Hance
 *
 * Revision 1.1  1993/05/31  03:23:41  hanceg
 * Initial revision
 *
*
****************************************************************************/
#include "CVIPtoolkit.h"
#include "pct.h"
#include <imaging.h>

/* the function below is to free the vector created before */
static void vector_free(float *v,int nl,int nh)
{
	free((char*) (v+nl));
}

/* the function below is to create a new vector */
static float *vector(int nl,int nh)
{
	float *v;

	v=(float *)malloc((unsigned) (nh-nl+1)*sizeof(float));
	if (!v)
	{
		error_CVIP("vector", "allocation failure in vector()");
		return(NULL);
	}
	return v-nl;
}

/* the function below is to create a new matrix */
static float **matrix(int nrl,int nrh,int ncl,int nch)
{
	int i;
	float **m;

	m=(float **) malloc((unsigned) (nrh-nrl+1)*sizeof(float*));
	if (!m)
	{
		error_CVIP("matrix", "allocation failure 1 in matrix()");
		return(NULL);
	}
	m -= nrl;

	for(i=nrl;i<=nrh;i++) {
		m[i]=(float *) malloc((unsigned) (nch-ncl+1)*sizeof(float));
		if(!m[i])
		{
			error_CVIP("matrix","allocation failure 2 in matrix()");
			break;
		}
		m[i] -= ncl;
	}
	if(i > nrh)
	return(m);

	do{
		i--;
		free(m[i]);
	}while(i >= nrl);
	return(NULL);
}


static void NICfree_matrix(float **m,int nrl,int nrh,int ncl,int nch)
{
	int i;

	for(i=nrh;i>=nrl;i--) free((char*) (m[i]+ncl));
	free((char*) (m+nrl));
}

/*
 * routine to sort a list of eigen-vectors
 */

static void eigsrt(float d[], float **v, int n)
{
	int k,j,i;
	float p;

	for (i=1;i<n;i++) {
		p=d[k=i];
		for (j=i+1;j<=n;j++)
			if (d[j] >= p) p=d[k=j];
		if (k != i) {
			d[k]=d[i];
			d[i]=p;
			for (j=1;j<=n;j++) {
				p=v[j][i];
				v[j][i]=v[j][k];
				v[j][k]=p;
			}
		}
	}
}


#define ROTATE(a,i,j,k,l) g=a[i][j];h=a[k][l];a[i][j]=g-s*(h+g*tau);\
	a[k][l]=h+s*(g-h*tau);

/*
 * routine for finding the eigen-vectors of a matrix.
 */

static void jacobi(float **a,int n, float *d, float **v, int *nrot)
{
	int j,iq,ip,i;
	float tresh,theta,tau,t,sm,s,h,g,c,*b,*z;

	b=vector(1,n);
	z=vector(1,n);
	for (ip=1;ip<=n;ip++) {
		for (iq=1;iq<=n;iq++) v[ip][iq]=0.0;
		v[ip][ip]=1.0;
	}
	for (ip=1;ip<=n;ip++) {
		b[ip]=d[ip]=a[ip][ip];
		z[ip]=0.0;
	}
	*nrot=0;
	for (i=1;i<=50;i++) {
		sm=0.0;
		for (ip=1;ip<=n-1;ip++) {
			for (iq=ip+1;iq<=n;iq++)
				sm += fabs(a[ip][iq]);
		}
		if (sm == 0.0) {
			vector_free(z,1,n);
			vector_free(b,1,n);
			return;
		}
		if (i < 4)
			tresh=0.2*sm/(n*n);
		else
			tresh=0.0;
		for (ip=1;ip<=n-1;ip++) {
			for (iq=ip+1;iq<=n;iq++) {
				g=100.0*fabs(a[ip][iq]);
				if (i > 4 && fabs(d[ip])+g == fabs(d[ip])
					&& fabs(d[iq])+g == fabs(d[iq]))
					a[ip][iq]=0.0;
				else if (fabs(a[ip][iq]) > tresh) {
					h=d[iq]-d[ip];
					if (fabs(h)+g == fabs(h))
						t=(a[ip][iq])/h;
					else {
						theta=0.5*h/(a[ip][iq]);
						t=1.0/(fabs(theta)+sqrt(1.0+theta*theta));
						if (theta < 0.0) t = -t;
					}
					c=1.0/sqrt(1+t*t);
					s=t*c;
					tau=s/(1.0+c);
					h=t*a[ip][iq];
					z[ip] -= h;
					z[iq] += h;
					d[ip] -= h;
					d[iq] += h;
					a[ip][iq]=0.0;
					for (j=1;j<=ip-1;j++) {
						ROTATE(a,j,ip,j,iq)
					}
					for (j=ip+1;j<=iq-1;j++) {
						ROTATE(a,ip,j,j,iq)
					}
					for (j=iq+1;j<=n;j++) {
						ROTATE(a,ip,j,iq,j)
					}
					for (j=1;j<=n;j++) {
						ROTATE(v,j,ip,j,iq)
					}
					++(*nrot);
				}
			}
		}
		for (ip=1;ip<=n;ip++) {
			b[ip] += z[ip];
			d[ip]=b[ip];
			z[ip]=0.0;
		}
	}
	error_CVIP("jacobi", "Too many iterations in routine JACOBI");
}

#undef ROTATE


/****************************************************************
                   Name: covariance_Matrix
          Expanded Name:     "
             Parameters: <bvecP> - pointer to an array of band vectors
			 <no_of_bands> - number of data bands
			 <vdim> - vector dimension (no. of pixels)
                Returns: pointer to covariance matrix
            Description: returns the covariance matrix of the band vector.
	                 The dimensions of the matrix are equal to the number
			 of data bands. (e.g.) for an RGB image with 3 data
			 bands the covariance  matrix is...
	                          _                  _
	                         |                    |
			         |  Crr   Cgr    Cbr  |
			         |                    |
			         |  Crg   Cgg    Cbg  |
			         |                    |
			         |  Crb   Cgb    Cbb  |
			         |                    |
			         |_                  _| 3x3
	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

MATRIX *
covariance_Matrix(
	float **bvecP, 
	unsigned int no_of_bands, 
	unsigned int vdim,
	CVIP_BOOLEAN is_mask,
	float mask_val
)
{    
/* Compute the covariance matrix for the set of band vectors */

    register int i,j,k;
    double *mean,**covmatrix;
    float *dataP;
    const char *fn = "covariance_Matrix";
    unsigned ndb=no_of_bands, count = 0;
    MATRIX *covMATRIX;

	covMATRIX = (MATRIX *) matrix_allocate(ndb, ndb, CVIP_DOUBLE, REAL);
	if(covMATRIX == NULL)
	return(NULL);
	covmatrix = (double **) covMATRIX->rptr;

	/* Get space for the mean vector */
	mean = (double *)calloc(ndb, sizeof(double));
	if (mean == NULL) {
		delete_Matrix(covMATRIX);
		error_CVIP(fn,"Unable to allocate space for mean vector.\n");
		return(NULL);
	}

    	for(i=0; i < ndb; i++) {
		count = 0;

       		for(j=0, dataP=bvecP[i]; j < vdim; j++, dataP++) {
	  		if(is_mask && (*dataP == mask_val))
	     			count++;
	  		else
             			mean[i] +=  (double) *dataP;
       		}
       		mean[i] /= (vdim - count);
	}

    	/* 
	** Process each pixel vector in turn, forming the sample covariance
       	** matrix and adding it to the covariance matrix estimate 
	*/

    for(i=0; i < vdim; i++)
       for(j=0; j<ndb; j++) 
          for(k=j; k<ndb; k++) {
	     if(is_mask && (bvecP[j][i] == mask_val))
	        continue;           
             covmatrix[j][k] += bvecP[j][i]*bvecP[k][i];
             covmatrix[k][j] = covmatrix[j][k];
          }
		
    for(i=0; i < ndb; i++)
       for(j=0; j < ndb; j++) { 
          covmatrix[i][j] /=  (vdim - count);
	  covmatrix[i][j] -= mean[i]*mean[j];
       }

    free(mean);

    return covMATRIX;
}

/****************************************************************
                   Name: eigenSystem_Matrix
          Expanded Name:     "
             Parameters: <a_MATRIX> - pointer to MATRIX structure
                Returns: pointer to MATRIX structure containing rows of
			 eigenvectors.
            Description: This function computes the eigenvalues and 
			 corresponding eigenvectors of a real symmetric matrix.
			 The eigen matrix is returned in terms of row vectors.  
			 The routine also sorts the eigenvalues in descending
			 order, and rearranges the rows correspondingly.   
	       
	                           En = {E1, E2, E3, ..., En}
	       	                  _                         _
	                         |                           |
			         |  E11   E12    E13 . . E1n |
			         |                           |
			         |  E21   E22    E23 . . E2n |
			         |                           |
			         |  E31   E32    E33 . . E3n |
			         |   .     .      .          |
			         |   .     .      .          |
			         |  En1   En2    En3 . . Enn |
			         |_                         _| nxn

	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/


 MATRIX *eigenSystem_Matrix(MATRIX *a_MATRIX)
 {
	MATRIX	*v_MATRIX;
	float	**a, **v, *d;
	double	**a_matrix, **v_matrix;
	int	n, n_rot, i, j;
	char	*module_name = "eigensystem";
 
	n = a_MATRIX->rows;
 
	v_MATRIX = (MATRIX *) matrix_allocate(n, n, CVIP_DOUBLE, REAL);
	if(v_MATRIX == NULL)
	return(NULL);

	a_matrix = (double **) a_MATRIX->rptr;
	v_matrix = (double **) v_MATRIX->rptr;
  
	a =  matrix(1, n, 1, n);
	v =  matrix(1, n, 1, n);
 
	d = vector(1, n);
	if((a == NULL) || (v == NULL) || (d == NULL))
	{
		if(a != NULL)
		NICfree_matrix(a,1,n,1,n);
		if(v != NULL)
		NICfree_matrix(v,1,n,1,n);
		if(d != NULL)
		vector_free(d, 1, n);    
		delete_Matrix(v_MATRIX);
		return(NULL);
	}
 
	for(i=1; i <= n; i++)
		for(j=1; j <= n; j++) 
			a[i][j] = (float) a_matrix[i-1][j-1]; 
 
	jacobi(a, n, d, v, &n_rot);
	eigsrt(d, v, n);
 
	for(i=1; i <= n; i++)
	msg_CVIP(module_name, "eigen value %d -> %f\n", i, d[i]);
  
	for(i=1; i <= n; i++)
	for(j=1; j <= n; j++) 
	v_matrix[i-1][j-1] = (double) v[j][i];        

	NICfree_matrix(a,1,n,1,n);
	NICfree_matrix(v,1,n,1,n);

	vector_free(d, 1, n);    
 
	return v_MATRIX; 
}
