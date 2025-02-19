/*
 * m_magnitude() - calculate the magnitude or squared magnitude of a matrix.
 *
 * Returns the resulting real matrix.  Does not affect the passed matrix.
 * The returned matrix is of type CVIP_DOUBLE if the input was.  Otherwise, it
 * is of type CVIP_FLOAT.
 *
 * Function list:
 *	mag_matrix(Matrix *in)
 *	square_mag_Matrix(Matrix *in)
 *
 * Author: Arve Kjoelen, SIUE
 *
 * Initial Coding Date: 3/4/96
 *
 */
#include <math.h>
#include "CVIPmatrix.h"
#include "CVIPdef.h"

Matrix *square_mag_Matrix(const Matrix *in) {
	int	i,j,cols;
	Matrix	*out;
	char	*FuncName = "square_mag_Matrix";

	if(!in) return(NULL);
	if(in->data_format!=COMPLEX) return(multPWise_Matrix(in, in));

	cols=in->cols;
	if(in->data_type<CVIP_DOUBLE) 
		out=new_Matrix(in->rows, in->cols, CVIP_FLOAT, REAL);
	else
		out=new_Matrix(in->rows, in->cols, CVIP_DOUBLE, REAL);
	if(out == NULL)
	return(NULL);


	for(i=0; i<out->rows; i++) {
		if(out->data_type==CVIP_FLOAT) {
			for(j=0; j<cols; j++) {
			((float *)out->rptr[i])[j]=
			SQR(((float *)in->rptr[i])[j])+
			SQR(((float *)in->iptr[i])[j]);
			}
		}
		else { /* data_type is double */
			for(j=0; j<cols; j++) {
			((double *)out->rptr[i])[j]=
			SQR(((double *)in->rptr[i])[j])+
			SQR(((double *)in->iptr[i])[j]);
			}
		}
	}
	return(out);
}

Matrix *mag_Matrix(Matrix *in) {
	int	i,j,cols;
	Matrix	*out;
	char	*FuncName = "mag_Matrix";

	if(!in) return(NULL);
	cols=in->cols;

	out=square_mag_Matrix(in);
	if(out == NULL)
	return(NULL);

	for(i=0; i<out->rows; i++) {
		if(out->data_type==CVIP_FLOAT) {
			for(j=0; j<cols; j++) {
			((float *)out->rptr[i])[j]=
			(float)sqrt((double)((float *)out->rptr[i])[j]);
			}
		}   
		else { /* data_type is double */
			for(j=0; j<cols; j++) {
			((double *)out->rptr[i])[j]=
			sqrt(((double *)out->rptr[i])[j]);
			}
		}
	}
	return(out);  
}
