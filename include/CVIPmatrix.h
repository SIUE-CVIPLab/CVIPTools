/***************************************************************************
======================================================================
Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
======================================================================
                                                                      
             File Name: matrix.h
           Description: Include file for all functions using data
                        objects of type Matrix. Also contains function
			prototypes for matrix library functions - libmatrix.a
         Related Files: Makefile, CVIPtyp.h, libmatrix.a
   Initial Coding Date: 2/29/92
           Portability: Standard (ANSI) C
             Credit(s): Gregory Hance, E.E. Dept. SIUE 
			
****************************************************************************

** Copyright (C) 1991, 1992, 1993 SIUE - by Scott Umbaugh, Greg Hance.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.

RCS (Revision Control System) Information - Added automatically by RCS) 

$Log: CVIPmatrix.h,v $
Revision 1.13  1997/06/16 21:33:26  yawei
removed bzero definition

Revision 1.12  1997/05/29 20:54:40  yawei
removed nrutil.h, which is no longer used

Revision 1.11  1997/03/08 00:46:28  yawei
Name Changes:
	BOOLEAN ==> CVIP_BOOLEAN
	FALSE ==> CVIP_YES
	TRUE ==> CVIP_NO
	BYTE ==> CVIP_BYTE
	SHORT ==> CVIP_SHORT
	INTEGER ==> CVIP_INTEGER
	FLOAT ==> CVIP_FLOAT
	DOUBLE ==> CVIP_DOUBLE
	TYPE ==> CVIP_TYPE

Revision 1.10  1997/01/15 17:10:40  yawei
Global Change:  IMAGE ==> Image

 * Revision 1.9  1996/12/13  22:32:57  akjoele
 * changed 4th arhument of convolve_Matrix to be const int instead of int.
 *
 * Revision 1.8  1996/12/12  17:43:51  akjoele
 * Added convolve_Matrix
 *
 * Revision 1.7  1996/12/06  18:57:12  akjoele
 * Added prototype for cbrt_Matrix()
 *
 * Revision 1.6  1996/12/05  20:47:27  akjoele
 * Added prototype for sqrt_Matrix()
 *
 * Revision 1.5  1996/11/25  22:32:01  akjoele
 * Changed prototype for square_mag_matrix to take const Matrix *
 * instead of Matrix *
 *
 * Revision 1.4  1996/07/26  17:11:47  akjoele
 * Added square_mag_Matrix() and conj_Matrix()
 *
 * Revision 1.3  1996/03/04  22:01:43  akjoele
 * Added definition for mag_Matrix
 *
 * Revision 1.2  1996/02/01  20:22:23  akjoele
 * Changed definition of bzero to be conditional to avoid annoying
 * compiler warnings about redefining the symbol bzero.
 *
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
 * Revision 1.1  1993/05/04  02:31:01  hanceg
 * Initial revision
 *                                                         

*****************************************************************************/

#if !defined ( CVIPMATRIX_DEFINED )

   #define CVIPMATRIX_DEFINED

   #include "CVIPdef.h"
   #include "CVIPvector.h"
   #include "CVIPcomplex.h"

   typedef enum {REAL, COMPLEX} FORMAT;

   typedef struct {
      CVIP_TYPE data_type;
      FORMAT data_format;
      unsigned int rows;
      unsigned int cols;
      char **rptr;
      char **iptr;
   } MATRIX;

   typedef MATRIX Matrix;

   #include "m_CovEig.h"
   #include "m_file.h"

   /* macros used to extract information from the Image structure */
   #define getNoOfRows_Matrix(matrix) ((matrix)->rows)
   #define getNoOfCols_Matrix(matrix) ((matrix)->cols)
   #define getDataType_Matrix(matrix) ((matrix)->data_type)
   #define getDataFormat_Matrix(matrix) ((matrix)->data_format)

   #define getRealData_Matrix(matrix) ((void *)((matrix)->rptr))
   #define getData_Matrix(matrix) getRealData_Matrix(matrix)
   #define getImagData_Matrix(matrix) ((void *)((matrix)->iptr))


   #define getRealRow_Matrix(matrix,row) ((void *)((matrix)->rptr[row]))
   #define getRow_Matrix(matrix,row) getRealRow_Matrix(matrix,row)
   #define getImagRow_Matrix(matrix,row) ((void *)((matrix)->iptr[row]))

   #define getDataVector_Matrix(matrix,vec) (*(vec) = getRow_Matrix(matrix,0))

   #define getRealVal_Matrix(matrix,type,x,y) \
   (((type **)((matrix)->rptr))[y][x])
   #define getVal_Matrix(matrix,type,x,y) getRealVal_Matrix(matrix,type,x,y)
   #define getImagVal_Matrix(matrix,type,x,y) \
   (((type **)((matrix)->iptr))[y][x])


   #define setRealVal_Matrix(matrix,type,x,y,val) \
   (getRealVal_Matrix(matrix,type,x,y) = (val))
   #define setVal_Matrix(matrix,type,x,y,val) \
   setRealVal_Matrix(matrix,type,x,y,val)
   #define setImagVal_Matrix(matrix,type,x,y,val) \
   (getImagVal_Matrix(matrix,type,x,y) = (val))


   /* Type Declarations for functions contained in CVIPtools matrix
      library - libmatrix.a ( Prototype form ) */
      
   #define matrix_allocate(a,b,c,d) new_Matrix(a,b,c,d) 
   #define matrix_makecomplex(a,b) makeComplex_Matrix(a,b)
   #define matrix_makereal(a,b) makeReal_Matrix(a,b)
   #define matrix_free(a)  delete_Matrix(a)
   #define matrix_print(a) print_Matrix(a)
   #define matrix_scale(a,b) scale_Matrix(a,b)
   #define matrix_crop(a,b,c,d,e) crop_Matrix(a,b,c,d,e)
   #define matrix_add(a,b) add_Matrix(a,b)
   #define matrix_sub(a,b)  sub_Matrix(a,b)
   #define matrix_mult_pwise(a,b) multPWise_Matrix(a,b)
   #define matrix_mult(a,b) mult_Matrix(a,b)
   #define matrix_transpose(a)  transpose_Matrix(a)
   #define matrix_invert(a) invert_Matrix(a)
   #define rect2pol(a,b)  rect2pol_Matrix(a,b)
   #define matrix_det(a) det_Matrix(a)
   #define matrix_copy(a,b,c) copy_Matrix(a,b,c)
   #define matrix_fcopy(a,b) fastCopy_Matrix(a,b)
   #define matrix_dup(a,b) duplicate_Matrix(a,b)

   /* not necessary, defined in CVIPdef.h
	#ifndef bzero
   #define bzero(a,b) (void) memset(a,0x00,b)
   #endif
	*/
#ifdef __cplusplus
extern "C"{
#endif 


   extern Matrix *new_Matrix(unsigned int rows, unsigned int cols, CVIP_TYPE data_type, FORMAT data_format);
   extern CVIP_BOOLEAN makeComplex_Matrix(Matrix *real_Matrix, CVIP_BOOLEAN verbose);
   extern CVIP_BOOLEAN makeReal_Matrix(Matrix *complex_Matrix, CVIP_BOOLEAN verbose);
   extern void delete_Matrix(Matrix *A);
   extern void print_Matrix(const Matrix *A);
   extern Matrix *scale_Matrix(const Matrix *a, double s);
   extern Matrix *crop_Matrix(const Matrix *a, unsigned int, unsigned int, unsigned int, unsigned int);
   extern Matrix *add_Matrix(const Matrix *A,const Matrix *B);
   extern Matrix *sub_Matrix(const Matrix *A,const Matrix *B);
   extern Matrix *multPWise_Matrix(const Matrix *A, const Matrix *B);
   extern Matrix *mult_Matrix(const Matrix *A,const Matrix *B);
   extern Matrix *transpose_Matrix(const Matrix *A);
   extern Matrix *invert_Matrix(const Matrix *A);
   extern Matrix *rect2pol_Matrix(Matrix *A, int dir);
   extern double det_Matrix(const Matrix *A);
   extern CVIP_BOOLEAN copy_Matrix(const Matrix *A, Matrix *B);
   extern CVIP_BOOLEAN fastCopy_Matrix(const Matrix *A, Matrix *B);
   extern Matrix *duplicate_Matrix(const Matrix *A, FORMAT df);
   extern Matrix *and_Matrix( const Matrix *A, const Matrix *B);
   extern int recip_Matrix(Matrix **rP, const Matrix *aP, const Matrix *bP);
   extern int divide_Matrix(Matrix **dP, const Matrix *aP, const Matrix	*bP, const Matrix *cP);
   extern int abs_Matrix(Matrix	*matP);
   extern Matrix *clone_Matrix(const Matrix *matP, CVIP_TYPE dt);
   extern Matrix *mag_Matrix(Matrix *in);
   extern Matrix *square_mag_Matrix(const Matrix *in);
   extern CVIP_BOOLEAN conj_Matrix(Matrix *in);
   extern Matrix *sqrt_Matrix(Matrix *in);
   extern Matrix *cbrt_Matrix(Matrix *in);
   extern Matrix *convolve_Matrix(Matrix *, Matrix *, int handle, const int center);
#ifdef __cplusplus
}
#endif 
    
#endif

/* End Of File */
