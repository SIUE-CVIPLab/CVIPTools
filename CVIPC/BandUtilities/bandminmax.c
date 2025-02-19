/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: bandminmax.c
*           Description: find the minimum and maximum values of each band
*			 of an image.
*         Related Files: Imakefile, CVIPband.h
*   Initial Coding Date: Mon Apr 12 11:17:39 CDT 1993
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
* $Log: bandminmax.c,v $
* Revision 1.4  1998/03/31 05:29:34  achomai
* Cleaned band_minmax :
* 1.  Changed MATRIX to Matrix.
* 2.  Used error_CVIP instead of fprintf for printing error messages.
* 3.  Corrected "deafult" to "default" in the switch statement.
* 4.  Fixed error in memory allocation.  Output must be an array of
*     length bdif*2 elements, not bdif elements, because both the
*     minimum and maximum values are stored for each band.
* 5.  If the data type is invalid, NULL will be returned instead of
*     some undefined value.
*
* Revision 1.3  1997/03/08 00:58:33  yawei
* Name Changes:
* 	BOOLEAN ==> CVIP_BOOLEAN
* 	FALSE ==> CVIP_NO
* 	TRUE ==> CVIP_YES
* 	BYTE ==> CVIP_BYTE
* 	SHORT ==> CVIP_SHORT
* 	INTEGER ==> CVIP_INTEGER
* 	FLOAT ==> CVIP_FLOAT
* 	DOUBLE ==> CVIP_DOUBLE
* 	TYPE ==> CVIP_TYPE
*
* Revision 1.2  1996/02/02 21:03:55  akjoele
* Changed function band_minmax so that it returns (void *)NULL
* instead of something undefined when errors are encountered.
*
 * Revision 1.1  1993/05/03  05:53:16  hanceg
 * Initial revision
 *
*
*
****************************************************************************/
#include "CVIPtoolkit.h"
#include "CVIPdef.h"


/****************************************************************
                   Name: band_minmax
          Expanded Name: Band Minimum and Maximum
             Parameters: <bands> - pointer to array of MATRIX pointers
			 containing image data
			 <no_of_bands> - number of spectral bands
			 <data_type> - type of image data
			 <bstart> - starting band
			 <bstop> - stopping band
                Returns: Pointer to array containing pairs of min. and
			 and max. values. Array will have same data type
			 as image data.
            Description: find the maximum and minimum values of each
			 band of an image from <bstart> to <bstop>.
	    Diagnostics: returns NULL pointer w/ error message if
			 bstop < bstart, etc.
              Credit(s): Gregory Hance
			 Southern Illinois University @ Edwardsville
****************************************************************/

void	*band_minmax(	Matrix * const		*bands,
			unsigned int		no_of_bands,
			CVIP_TYPE		data_type,
			int			bstart,
			int			bstop)
{
	register int	i,j,k;
	unsigned int	imgsize, bdif;
	const char	*fn = "band_minmax";
	void		*mmarray;

	if(bstart<0 || bstop<0) {
		bstart = 0;
		bstop = no_of_bands - 1;
	}
	if((bstart>=no_of_bands) || (bstop >= no_of_bands)) {
		error_CVIP(	fn,
		"bstart and bstop must be less than the number of bands.\n");
		return(void *)NULL;
	}
	if(bstop < bstart) {
		error_CVIP(fn,"bstop must be greater than bstart.\n");
		return(void *)NULL;
	}

	imgsize = bands[0]->cols*bands[0]->rows;
	bdif = bstop - bstart + 1;

	k = 0;
	switch(data_type) {
	case CVIP_BYTE: {
		byte	*mm, *byteP;
		mm = (byte *)calloc(bdif*2,sizeof(byte));
		if(mm != NULL)
		for(i=bstart; i<=bstop; i++, k+=2) {
			byteP = (byte *) bands[i]->rptr[0];
			for(	j=0, mm[k]=255, mm[k+1]=0;
				j < imgsize;
				j++, byteP++) {
				mm[k]   = MIN(mm[k],*byteP);
				mm[k+1] = MAX(mm[k+1],*byteP);
			}
		}
		mmarray = (void *) mm;
		break;
	}
	case CVIP_SHORT: {
		short	*mm, *shortP;
		mm = (short *)calloc(bdif*2,sizeof(short));
		if(mm != NULL)
		for(i=bstart; i<=bstop; i++, k+=2) {
			shortP = (short *) bands[i]->rptr[0];
			for(	j=0, mm[k]=255, mm[k+1]=0;
				j < imgsize;
				j++, shortP++) {
				mm[k]   = MIN(mm[k],*shortP);
				mm[k+1] = MAX(mm[k+1],*shortP);
			}
		}
		mmarray = (void *) mm;
		break;
	}
	case CVIP_INTEGER: {
		int	*mm, *intP;
		mm = (int *)calloc(bdif*2,sizeof(int));
		if(mm != NULL)
		for(i=bstart; i<=bstop; i++, k+=2) {
			intP = (int *) bands[i]->rptr[0];
			for(	j=0, mm[k]=255, mm[k+1]=0;
				j < imgsize;
				j++, intP++) {
				mm[k]   = MIN(mm[k],*intP);
				mm[k+1] = MAX(mm[k+1],*intP);
			}
		}
		mmarray = (void *) mm;
		break;
	}
	case CVIP_FLOAT: {
		float	*mm, *floatP;
		mm = (float *)calloc(bdif*2,sizeof(float));
		if(mm != NULL)
		for(i=bstart; i<=bstop; i++, k+=2) {
			floatP = (float *) bands[i]->rptr[0];
			for(	j=0, mm[k]=255, mm[k+1]=0;
				j < imgsize;
				j++, floatP++) {
				mm[k]   = MIN(mm[k],*floatP);
				mm[k+1] = MAX(mm[k+1],*floatP);
			}
		}
		mmarray = (void *) mm;
		break;
	}
	case CVIP_DOUBLE: {
		double	*mm, *doubleP;
		mm = (double *)calloc(bdif*2,sizeof(double));
		if(mm != NULL)
		for(i=bstart; i<=bstop; i++, k+=2) {
			doubleP = (double *) bands[i]->rptr[0];
			for(	j=0, mm[k]=255, mm[k+1]=0;
				j < imgsize;
				j++, doubleP++) {
				mm[k]   = MIN(mm[k],*doubleP);
				mm[k+1] = MAX(mm[k+1],*doubleP);
			}
		}
		mmarray = (void *) mm;
		break;
	}
	default:
		error_CVIP(fn,"Invalid data type.\n");
		mmarray = NULL;
		break;
	}
	return(mmarray);
}
