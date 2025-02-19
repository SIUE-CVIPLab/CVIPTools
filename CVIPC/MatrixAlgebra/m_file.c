/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: m_file.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Mon Sep 20 20:49:25 CDT 1993
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Gregory Hance
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
** $Log: m_file.c,v $
** Revision 1.4  1997/03/08 17:04:26  yawei
** Swaped CVIP_YES and CVIP_NO
**
** Revision 1.3  1997/03/08 00:55:14  yawei
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
** Revision 1.2  1997/01/16 21:13:44  yawei
** updated changes
**
 * Revision 1.1  1994/10/30  17:58:41  hanceg
 * CVIPtools1.0 source file - G. Hance
 *
*
****************************************************************************/
#include "CVIPmatrix.h"
#include <rpc/rpc.h> /* xdr is a sub-library of rpc */

bool_t
xdr_matrix(
	XDR *xdrs,
	Matrix *mP
)
{
	unsigned prows, img_size, maxrows, maxelements;
	bool_t alloc_ok;
	register int row;
	size_t elem_size;

	maxrows = MAXROWS;
	maxelements = MAXELEMENTS;

	if(xdrs->x_op == XDR_ENCODE) {
		prows = mP->rows << mP->data_format;
		img_size = (mP->rows * mP->cols) << mP->data_format;
	}

	if(!(
		xdr_enum(xdrs, (enum_t *)&mP->data_type) &&
		xdr_enum(xdrs, (enum_t *)&mP->data_format) &&	
		xdr_u_int(xdrs, &mP->rows) &&
		xdr_u_int(xdrs, &mP->cols)
	)) {
		error_CVIP("xdr_matrix", "XDR I/O failed.");
		return 0;
	}

	maxrows <<= mP->data_format;
	maxelements <<= mP->data_format;

	if(!(
		xdr_array(xdrs, (caddr_t *)&mP->rptr, &prows, maxrows, sizeof(void *),
		xdr_long)
	)) {
		error_CVIP("xdr_matrix", "XDR I/O failed.");
		return 0;
	}

	if(xdrs->x_op == XDR_DECODE) *(mP->rptr) = NULL;

	switch(mP->data_type) {

	case CVIP_BYTE :
		elem_size = 1;
		alloc_ok = xdr_bytes(xdrs, mP->rptr, &img_size, maxelements);
		break;
	case CVIP_SHORT :
		elem_size = sizeof(short);
		alloc_ok = xdr_array(xdrs, (caddr_t *)mP->rptr, &img_size, maxelements,
		elem_size, xdr_short);
		break;
	case CVIP_INTEGER :
		elem_size = sizeof(int);
		alloc_ok = xdr_array(xdrs, (caddr_t *)mP->rptr, &img_size, maxelements,
		elem_size, xdr_int);
		break;
	case CVIP_FLOAT :
		elem_size = sizeof(float);
		alloc_ok = xdr_array(xdrs, (caddr_t *)mP->rptr, &img_size, maxelements,
		elem_size, xdr_float);
		break;
	case CVIP_DOUBLE :
		elem_size = sizeof(double);
		alloc_ok = xdr_array(xdrs, (caddr_t *)mP->rptr, &img_size, maxelements,
		elem_size, xdr_double);
		break;

	}
	if(!alloc_ok) {
		error_CVIP("xdr_matrix", "XDR I/O failed.");
		return 0;
	}

	if(xdrs->x_op == XDR_DECODE) {

		if( ( prows != (mP->rows << mP->data_format ) ) ||
		( img_size != ((mP->rows * mP->cols) << mP->data_format) ) ) {
			error_CVIP("xdr_matrix", "XDR I/O failed.");
			return 0;
		}

		/* 
		 * if read from disk was successful then fulfill the
		 * indirect memory requirements by mapping the row vectors 
		 */

		for(row = 0; row < prows; row++)
			mP->rptr[row] = (char *) *(mP->rptr) + 
			row*mP->cols*elem_size;

		if(mP->data_format == COMPLEX)
			mP->iptr = (char **) mP->rptr + mP->rows;
		else
			mP->iptr = NULL;
	}

	return 1;
} 
	

int read_Matrix(
	Matrix *matP,
	const char *name
)
{
	XDR xdri;
	FILE *fileP;
	register int i;
	unsigned prows;
	size_t ds[5] = { sizeof(byte), sizeof(short), sizeof(int),
	sizeof(float), sizeof(double) }, elem_size;

	if(!(fileP = openRead_CVIP(name)))
		return( (int) fileP);

	matP->rptr = NULL;

	xdrstdio_create(&xdri, fileP, XDR_DECODE);
	if(!xdr_matrix(&xdri, matP)) {
		error_CVIP("read_Matrix","could not read matrix from %s.",name);
		return 0;
	}

	close_CVIP(fileP);
	return 1;
}


int write_Matrix(
	Matrix *matP,
	const char *name
)
{
	XDR xdro;
	FILE *fileP;

	if(!(fileP = openWrite_CVIP(name, CVIP_NO)))
		return( (int) fileP);

	xdrstdio_create(&xdro, fileP, XDR_ENCODE);
	if(!xdr_matrix(&xdro, matP)) {
		error_CVIP("write_Matrix","could not write matrix to %s.",name);
		return 0;
	}

	close_CVIP(fileP);
	return 1;
}

