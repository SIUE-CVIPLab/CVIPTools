/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: image.c 
*           Description: This is a series of modules primarily used
*			 for the creation, manipulation, etc. of image
*			 structures. 
*         Related Files: Imakefile, libdataserv.a, libband.a, libmatrix.a,
*			 libcli.a
*   Initial Coding Date: 1/15/92
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
** $Log: image.c,v $
** Revision 1.41  2001/05/02 14:52:06  zlin
** change trans_compr to trcm
**
** Revision 1.40  2001/02/26 00:21:48  zlin
** add "trans_compr" to Cmpr_Name[]
**
** Revision 1.39  2000/03/14 23:39:16  ycheng
** in the 'char * image_format_string[] ', the compressed format of 'VQ' and 'XVQ'
** has been changed to 'VIP/VQ' and 'VIP/XVQ' respectively.
**
** Revision 1.38  1999/11/20 23:56:50  ycheng
** In the 'char *Cmpr_Name[] = {}', "xvq" should be added in the front of "top".
**
** Revision 1.37  1999/10/04 02:22:46  lguo
** compressed format of VQ and XVQ added
**
** Revision 1.36  1998/04/22 00:04:17  achomai
** 1.  Made all functions check for memory allocation failure or NULL
**     pointers returned from the Matrix library functions.
** 2.  Made all functions use error_CVIP to print error messages.
** 3.  If an error occured in any function, memory blocks or matrices
**     allocated before that point will be freed.
**
** Revision 1.35  1998/04/09 00:27:34  wzheng
** add vq compression format
**
** Revision 1.34  1998/03/10 04:25:01  smakam
** made changes corresponding to including a new compression method fractal compression
**
** Revision 1.33  1998/02/12 20:25:20  smakam
** changed DPCM - DPC
**
** Revision 1.32  1997/11/07 22:39:05  wzheng
** add "wvq" as one of Cmpr_Name[]
**
** Revision 1.31  1997/06/16 18:58:38  yawei
** fixed data format mismatch for datarange.
**
** Revision 1.30  1997/05/19 00:50:16  yawei
** added temp_dir here, which is used in DIsPLAY and COMPRESSION
**
** Revision 1.29  1997/05/03 00:21:32  yawei
** added getDataRange_Image
**
** Revision 1.28  1997/04/29 00:32:56  yawei
** added jpeg
**
** Revision 1.27  1997/04/29 00:10:20  yawei
** added jpgs
**
** Revision 1.26  1997/03/08 17:06:31  yawei
** Swaped CVIP_YES and CVIP_NO
**
** Revision 1.25  1997/03/08 01:00:02  yawei
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
** Revision 1.24  1997/01/16 21:29:15  yawei
** Global Change:  Image_FORMAT ==> IMAGE_FORMAT
**
 * Revision 1.23  1997/01/15  17:18:07  yawei
 * Global Change:  IMAGE ==> Image
 *
 * Revision 1.22  1997/01/05  20:19:48  yawei
 * moved setDisplay_Image, setDisplay_Image, display_Image to libgui.
 *
 * Revision 1.21  1996/12/17  17:20:07  yawei
 * *** empty log message ***
 *
 * Revision 1.20  1996/12/13  16:21:08  yawei
 * added data_format_string and data_type_string
 *
 * Revision 1.19  1996/12/04  20:36:10  yawei
 * changed lzw to zvl
 *
 * Revision 1.18  1996/11/30  18:00:17  yawei
 * changed appendix btc1-> btc; dpcm->dpc
 *
 * Revision 1.17  1996/11/20  15:24:58  yawei
 * Added global array to hold the extension of compressed files.
 *
 * Revision 1.16  1996/11/04  19:09:19  akjoele
 * included CVIPdef.h so that CVIP_BOOLEAN is defined.
 * removed unused code (nopt reached)
 *
 * Revision 1.15  1996/10/15  15:52:28  akjoele
 * no change
 *
 * Revision 1.14  1996/10/13  22:27:01  yawei
 * Changed the image_format_string back to the Abreviated form.
 *
 * Revision 1.13  1996/10/13  20:45:35  yawei
 * Changed the image_format_string
 * 1) The image name gives more detailed information about the Image format;
 * 2) Keep the image format information in the GUI and viewer consistent.
 *
 * Revision 1.12  1996/10/10  21:16:39  yawei
 * added ZON image format to image_format_string.
 *
 * Revision 1.11  1996/08/19  12:26:15  akjoele
 * *** empty log message ***
 *
 * Revision 1.10  1996/01/30  17:01:57  kluo
 * add NULL pointer to image_format_string array
 *
 * Revision 1.9  1996/01/30  16:59:30  kluo
 * add new extension definition
 *
 * Revision 1.8  1995/10/11  14:10:55  kluo
 * change for history and added compression menu
 *
 * Revision 1.7  1995/09/19  22:02:14  kluo
 * change history dptr
 *
 * Revision 1.6  1995/09/19  21:38:32  kluo
 * check file in
 *
 * Revision 1.5  1995/04/14  18:04:56  zook
 * Fixed the copying of image history information in duplicate_image()
 *
 * Revision 1.4  1995/02/03  00:54:39  luok
 *  fix the bug on duplication of history stuff. Originally, the new
 *  history copy shares the resource memory on dtype and dptr with the
 *   old history copy. When the old history is deleted, the new history
 *  copy cannot have the information about dtype and dptr, which will
 * cause problem with further routines
 *
 * Revision 1.3  1995/01/14  00:54:20  luok
 * fix a bug in delete_Image function, change the condition for loop
 * from "i = 0" to "i >=0". The previous condition will make loop
 * not executed at all.
 *
 * Revision 1.2  1995/01/14  00:03:25  luok
 * check image.c back into RCS
 *
 * Revision 1.1  1993/05/11  00:36:55  hanceg
 * Initial revision
 *
*
****************************************************************************/

#include <math.h>         /* header files */ 
#include <stdlib.h>
#include <stdio.h>
#include "CVIPparse.h"
#include "CVIPimage.h"
char temp_dir[100];

   char *color_format_string[] = {"BINARY", "GRAY_SCALE", "RGB", "HSL", "HSV",\
			"SCT", "CCT", "LUV", "LAB", "XYZ",NULL};

   char * image_format_string[] = {"PBM", "PGM", "PPM", "EPS", "TIF", "GIF",\
			"RAS", "ITX","IRIS", "CCC", "BIN", "VIP", "VIP/GLR", "VIP/BTC",\
			"VIP/BRC", "VIP/HUF", "VIP/ZVL","ARITH","VIP/BTC2",\
			"VIP/BTC3", "VIP/DPC", "VIP/ZON", "VIP/ZON2", "SAFVR", "JPEG", "VIP/WVQ", "VIP/FRA", "VIP/VQ","VIP/XVQ", "VIP/TRCM", "JPEG2000", "PNG",  NULL};

   char *Cmpr_Name[] = {"btc", "btc2", "btc3", "dpc", "zvl", "glr", "brc",\
			"huf", "zon", "zon2", "jpg", "wvq", "fra", "vq", "xvq", "trcm", "top", "jp2"}; 

	char *data_format_string[] = {"REAL", "COMPEX"};
	char *data_type_string[] = {"CVIP_BYTE", "CVIP_SHORT", "CVIP_INTEGER", "CVIP_FLOAT"};

/****************************************************************
                   Name: new_image
          Expanded Name: new image
             Parameters: <image_format> - original file format of image
			 <color_space> - current color space of image
			 <bands> - number of spectral bands
			 <height> - height of image (no. of rows)
			 <width> - width of image (no. of cols)
			 <data_type> - current data type of image
			 <data_format> - specifies real or complex data
                Returns: pointer to Image structure
            Description: creates a new instance of a CVIPtools Image structure.
			 The Image structure is the primary means of data
			 transport in CVIPtools.  Ordinarily the developer
			 does not have to worry about allocating an Image
			 structure in the sense that the function
			 CVIPreadimage(...) returns a pointer to an Image
			 structure that has been initialized to the
			 specifications of a particular image.
	    Diagnostics  returns a NULL pointer w/ respective error message
			 when a memory allocation request can not be satisfied.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

Image *
new_Image(IMAGE_FORMAT image_format, COLOR_FORMAT color_space,
               int bands, int heigth, int width, CVIP_TYPE data_type,
               FORMAT data_format)
{
	int	i;
	Image	*A;
	char	*module_name = "new_Image";

/* allocate the image structure */
	A = (Image *) calloc(1,sizeof(Image));
	if(!A) {
		error_CVIP(module_name,"Unable to allocate memory.\n");
		return(NULL);
	}

/* set up the size as requested */
	A->image_format = image_format;
	A->color_space = color_space;
	A->bands = bands;
	A->story = NULL;

/* try to allocate the request */
	A->image_ptr = (MATRIX **) calloc(bands,sizeof(MATRIX *));
	if(A->image_ptr == NULL)
	{
		error_CVIP(module_name,"Unable to allocate memory.\n");
		free(A);
		return(NULL);
	}

	for(i = 0 ; i < bands ; i++)
	{
		A->image_ptr[i] = (MATRIX *)new_Matrix(	heigth, width,
							data_type, data_format);
		if(!A->image_ptr[i])
		break;
	}
	if(i == bands)
	return(A);
	error_CVIP(module_name,"Error making frequency band #%d\n",i);
	while(i > 0)
	{
		i--;
		delete_Matrix(A->image_ptr[i]);
	}
	free(A->image_ptr);
	free(A);
	return(NULL);
}


/****************************************************************
                   Name: delete_Image
          Expanded Name: delete image
             Parameters: <A> - pointer to Image structure
                Returns: nada
            Description: free all elements of an Image structure
	    Diagnostics  complains if the structure passed is not valid
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

/****************************************************************
 *
 * Edit: November 2009
 *
 * It seems that the check for valid structure is not strict
 * enough, letting some invalid structures through. This usually
 * corrupts the stack and operations afterwards have problems
 * until program finally crashes.
 *
 * Adding MAX_BANDS value to narrow the filter for what is
 * considered a valid structure. Currently, 1024 seems like a
 * very generous value. This value may be increased in the future
 * if needed.
 *
 * Pat Solt
 */
#define MAX_BANDS	1024

void delete_Image(Image *A)
{
	register int	i;
	const char	*fn = "delete_Image";
	HISTORY		head, previous;

	/* check for valid structure */
	if(!A)
	{
		error_CVIP(fn,"NULL pointer passed.\n");
		return;
	}
	if((A->bands < 1) || (A->bands > MAX_BANDS) || !(A->image_ptr))
	{
		error_CVIP(fn,"Invalid structure passed.\n");
		return;
	}
	if(A->story!=NULL){
		head=A->story;
		while(head!=NULL){
			previous=head;
			head=head->next;
			i = previous->packetP->dsize;
			while(i>0){
				i--;
				free(previous->packetP->dptr[i]);
			}
			free(previous->packetP->dptr);
			free(previous->packetP->dtype);
			free(previous->packetP);
			free(previous);
		} 
	}
	/* xchen update here */
	A->story = NULL;
	/* free each band/matrix of the image */
	for(i=A->bands-1; i >= 0; i--){
		if(A->image_ptr[i]!=0)
			delete_Matrix(A->image_ptr[i]);
		/* xchen update here */
		A->image_ptr[i] = NULL;
	}

	/* free band pointer */
	free( A->image_ptr );
	/* xchen update here */
	A->image_ptr = NULL;

	/* free image structure */
	free((IMAGE *)A);
	/* xchen update here */
	A = NULL;
}


/****************************************************************
                   Name: duplicate_Image
          Expanded Name: duplicate image
             Parameters: <inImage> - pointer to Image structure
                Returns: pointer to new Image structure
            Description: creates a new instance of the Image structure pointed
			 to by <inImage>. This function is useful if one
			 wants to pass an Image structure to a function to be
			 processed while maintaining the integrity of the
			 original image.
	    Diagnostics: complains and returns NULL pointer upon memory
			 allocation failure.
              Credit(s): Gregory Hance, Arve Kjoelen
		         Southern Illinois University @ Edwardsville
****************************************************************/

Image *duplicate_Image(const Image *inImage)
{
	Image	*dupImage;

	dupImage = (Image *)new_Image(	inImage->image_format,
					inImage->color_space,
					inImage->bands,
					(inImage->image_ptr[0])->rows,
					(inImage->image_ptr[0])->cols,
					(inImage->image_ptr[0])->data_type,
					(inImage->image_ptr[0])->data_format); 
	if(dupImage == NULL)
	return(NULL);

	bandcopy(inImage->image_ptr, dupImage->image_ptr, inImage->bands);

	/* Copy all history stuff */
	history_copy((Image *)inImage, dupImage);
	return(dupImage);
}

/****************************************************************
                   Name: cast_Image
          Expanded Name: cast Image
             Parameters: <srcImage> - pointer to Image structure
			 <type> - new data type
                Returns: 0 or -1.
            Description: casts an Image structure into a more precise data type.
	    Diagnostics: returns 0 if the cast can be performed (i.e. the
			 type specified by <type> is more precise than that of
			 <srcImage> and -1 if the type of <srcImage> is more
			 precise than that of <type>. If the types are the same
			 or -1 is returned then <srcImage> is left untouched.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

int 
cast_Image(
	Image 		*srcP, 
	CVIP_TYPE 	dtype
)
{
	Matrix		*newP, *oriP;
	Matrix		**Temp;
	const char 	*fn = "cast_Image";
	register int	i;
	unsigned	bands;

	bands	= getNoOfBands_Image(srcP);

	if( getDataType_Image(srcP) < dtype )
	{
		Temp = calloc(bands,sizeof(Matrix *));
		if(Temp != NULL)
		{
			for(i = 0;i < bands;i++)
			{
				oriP = getBand_Image(srcP,i);
				Temp[i] = clone_Matrix(oriP,dtype);
				if(Temp[i] == NULL)
				break;
				copy_Matrix(oriP,Temp[i]);
			}
			if(i == bands)
			{
				for(i = 0;i < bands;i++)
				{
					oriP = getBand_Image(srcP,i);
					setBand_Image(srcP,Temp[i],i);
					delete_Matrix(oriP);
				}
				free(Temp);
				return(1);
			}
			while(i > 0)
			{
				i--;
				delete_Matrix(Temp[i]);
			}
		}
	}
	return(0);
}


/****************************************************************
                   Name: unloadvec
          Expanded Name: unload vector
             Parameters: <srcImage> - pointer to Image structure
			 <vectype> - type of vector
			 <bands> - pointer to variable to hold no. of bands
			 <rows> - pointer to variable to hold no. of rows
			 <cols> - pointer to variable to hold no. of cols
                Returns: pointer to array of vectors
            Description: unload data from an Image structure in vector
			 format.
	    Diagnostics: returns NULL pointer w/ corresponding error message
			 upon memory allocation failure, etc.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

static void	*unloadvec(	Image		*srcImage,
				DATAFORM	vectype,
				CVIP_TYPE	type,
				unsigned int	bands, 
				unsigned int	rows,
				unsigned int	cols )
{
	CVIP_TYPE	dtype;
	unsigned int	bandsize, no_of_vecs, vecdim;
	register int	i,j;
	void		*vecP;
	const char	*fn = "unloadvec";

	dtype = getDataType_Image(srcImage);
	bandsize = rows*cols;

	no_of_vecs = (vectype==PIXVECFORM) ? bandsize : bands;
	vecdim = (vectype==PIXVECFORM) ? bands : bandsize;

	vecP = (void **) malloc(no_of_vecs*sizeof(void *));
	if(vecP == NULL)
	{
		error_CVIP(fn,"Unable to allocate memory.\n");
		return(NULL);
	}

	switch(type) {
	case CVIP_BYTE: {
		byte	**bvecP, *bP;
		bvecP = (byte **) vecP;
		for(i = 0;i < no_of_vecs;i++) {
			bP = bvecP[i] = (byte *) malloc(vecdim*sizeof(byte));
			if(bP == NULL)
			{
				while(i > 0)
				{
					i--;
					free(bvecP[i]);
				}
				break;
			}
			if(vectype==PIXVECFORM) {
				for(j=0; j < vecdim; j++, bP++)
				*bP = *(srcImage->bandP[j]->rptr[0] + i);
			}
			else
			(void) copyvec(	srcImage->bandP[i]->rptr[0],
					bP,
					(size_t)vecdim,
					dtype,
					type);
		}
		break;
	}
	case CVIP_SHORT: {
		short	**svecP, *sP;
		svecP = (short **) vecP;
		for(i = 0;i < no_of_vecs; i++) {
			sP = svecP[i] = (short *) malloc(vecdim*sizeof(short));
			if(sP == NULL)
			{
				while(i > 0)
				{
					i--;
					free(svecP[i]);
				}
				break;
			}
			if(vectype==PIXVECFORM) {
				for(j=0; j < vecdim; j++, sP++)
				*sP = *(srcImage->bandP[j]->rptr[0] + i);
			}
			else
			(void) copyvec(	srcImage->bandP[i]->rptr[0],
					sP,
					(size_t)vecdim,
					dtype,
					type);
		}
		break;
	}
	case CVIP_INTEGER: {
		int	**ivecP, *iP;
		ivecP = (int **) vecP;
		for(i = 0; i < no_of_vecs; i++) {
			iP = ivecP[i] = (int *) malloc(vecdim*sizeof(int));
			if(iP == NULL)
			{
				while(i > 0)
				{
					i--;
					free(ivecP[i]);
				}
				break;
			}
			if(vectype==PIXVECFORM) {
				for(j=0; j < vecdim; j++, iP++)
				*iP = *(srcImage->bandP[j]->rptr[0] + i);
			}
			else
			(void) copyvec(	srcImage->bandP[i]->rptr[0],
					iP,
					(size_t)vecdim,
					dtype,
					type);
		}
		break;
	}
	case CVIP_FLOAT: {
		float	**fvecP, *fP;
		fvecP = (float **) vecP;
		for(i = 0; i < no_of_vecs; i++) {
			fP = fvecP[i] =(float *) malloc(vecdim*sizeof(float));
			if(fP == NULL)
			{
				while(i > 0)
				{
					i--;
					free(fvecP[i]);
				}
				break;
			}
			if(vectype==PIXVECFORM) {
				for(j=0; j < vecdim; j++, fP++)
				*fP = *(srcImage->bandP[j]->rptr[0] + i);
			}
			else
			(void) copyvec(	srcImage->bandP[i]->rptr[0],
					fP,
					(size_t) vecdim,
					dtype,
					type);
		}
		break;
	}
	case CVIP_DOUBLE: {
		double	**dvecP, *dP;
		dvecP = (double **) vecP;
		for(i = 0; i < no_of_vecs; i++) {
			dP = dvecP[i] = (double *)malloc(vecdim*sizeof(double));
			if(dP == NULL)
			{
				while(i > 0)
				{
					i--;
					free(dvecP[i]);
				}
				break;
			}
			if(vectype==PIXVECFORM) {
				for(j=0; j < vecdim; j++, dP++)
				*dP = *(srcImage->bandP[j]->rptr[0] + i);
			}
			else
			(void) copyvec(	srcImage->bandP[i]->rptr[0],
					dP,
					(size_t) vecdim,
					dtype,
					type);
		}
		break;
	}
	default:
		error_CVIP(fn,"shouldn't happen");
		return(NULL);
	}
	if(i == no_of_vecs)
	return(vecP);
	error_CVIP(fn,"Unable to allocate memory.\n");
	free(vecP);
	return(NULL);
} /* End of function unloadvec(...) */


/****************************************************************
                   Name: unloadmat
          Expanded Name: unload matrix
             Parameters: <srcImage> - pointer to Image structure
			 <bands> - pointer to variable to hold no. of bands
			 <rows> - pointer to variable to hold no. of rows
			 <cols> - pointer to variable to hold no. of cols
                Returns: pointer to array of matrices
            Description: unload data from an Image structure into matrix
			 format.
	    Diagnostics: returns NULL pointer w/ corresponding error message
			 upon memory allocation failure, etc.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

static void *unloadmat( Image *srcImage, CVIP_TYPE type, unsigned int bands, 
               unsigned int rows, unsigned int cols )
{
	CVIP_TYPE	dtype;
	unsigned int	bandsize;
	register int	i = 0, j;
	void		*vecP;
	const char	*fn = "unloadmat";

	dtype = getDataType_Image(srcImage);
	bandsize = rows*cols;

	vecP = (void ***) malloc(bands*sizeof(void **));
	if(vecP == NULL)
	{
		error_CVIP(fn,"Unable to allocate memory.\n");
		return(NULL);
	}
	for(j=0;j<bands;j++)
	{
		((void ***) vecP)[j] = (void **) malloc(rows*sizeof(void *));
		if(((void ***)vecP)[j] == NULL)
		break;
	}
	if(j != bands)
	{
		while(j > 0)
		{
			j--;
			free(((void ***)vecP)[j]);
		}
		free(vecP);
	}

	switch(type) {
	case CVIP_BYTE: {
		byte	***bvecP, *bP;
		bvecP = (byte ***) vecP;
		for(i = 0; i < bands; i++) {
			*bvecP[i] = (byte *)malloc(bandsize*sizeof(byte));
			if(*bvecP[i] == NULL)
			{
				while(i > 0)
				{
					i--;
					free(*bvecP[i]);
				}
				break;
			}
			for(j=1; j < rows; j++)
			bvecP[i][j] = (byte *) *bvecP[i] + j*cols;
			(void)copymat(	srcImage->bandP[i]->rptr,
					bvecP[i],
					rows,cols,
					dtype,
					type);
		}
		break;
	}
	case CVIP_SHORT: {
		short	***svecP, *sP;
		svecP = (short ***) vecP;
		for(i = 0; i < bands; i++) {
			*svecP[i] = (short *) malloc(bandsize*sizeof(short));
			if(*svecP[i] == NULL)
			{
				while(i > 0)
				{
					i--;
					free(*svecP[i]);
				}
				break;
			}
			for(j=1; j < rows; j++)
			svecP[i][j] = (short *) *svecP[i] + j*cols;
			(void)copymat(	srcImage->bandP[i]->rptr,
					svecP[i],
					rows,cols,
					dtype,
					type);
		}
		break;
	}
	case CVIP_INTEGER: {
		int	***ivecP, *iP;
		ivecP = (int ***) vecP;
		for(i = 0; i < bands; i++) {
			*ivecP[i] = (int *) malloc(bandsize*sizeof(int));
			if(*ivecP[i] == NULL)
			{
				while(i > 0)
				{
					i--;
					free(*ivecP[i]);
				}
				break;
			}
			for(j=1; j < rows; j++, iP++)
			ivecP[i][j] = (int *) *ivecP[i] + j*cols;
			(void)copymat(	srcImage->bandP[i]->rptr,
					ivecP[i],
					rows,cols,
					dtype,
					type);
		}
		break;
	}
	case CVIP_FLOAT: {
		float	***fvecP, *fP;
		fvecP = (float ***) vecP;
		for(i = 0; i < bands; i++) {
			*fvecP[i] =(float *) malloc(bandsize*sizeof(float));
			if(*fvecP[i] == NULL)
			{
				while(i > 0)
				{
					i--;
					free(*fvecP[i]);
				}
				break;
			}
			for(j=1; j < rows; j++)
			fvecP[i][j] = (float *) *fvecP[i] + j*cols;
			(void)copymat(	srcImage->bandP[i]->rptr,
					fvecP[i],
					rows,cols,
					dtype,
					type);
		}
		break;
	}
	case CVIP_DOUBLE: {
		double	***dvecP, *dP;
		dvecP = (double ***) vecP;
		for(i = 0; i < bands; i++) {
			*dvecP[i] = (double *) malloc(bandsize*sizeof(double));
			if(*dvecP[i] == NULL)
			{
				while(i > 0)
				{
					i--;
					free(*dvecP[i]);
				}
				break;
			}
			for(j=1; j < rows; j++)
			dvecP[i][j] = (double *) *dvecP[i] + j*cols;
			(void)copymat(	srcImage->bandP[i]->rptr,
					dvecP[i],
					rows,cols,
					dtype,
					type);
		}
		break;
	}
	default:
		error_CVIP(fn,"shouldn't happen");
		return NULL;
	}
	if(i == bands)
	return(vecP);
	error_CVIP(fn,"Unable to allocate memory.\n");

	for(j = 0;j < bands;j++)
	free(((void ***)vecP)[j]);
	free(vecP);
	return(NULL);
} /* End of function lvector(...) */


/****************************************************************
                   Name: unload_Image
          Expanded Name: unload image
             Parameters: <srcImage> - pointer to Image structure
			 <df> - data format (BANVECFORM, PIXVECFORM, MATRIXFORM)
			 <type> - type of data
			 <bands> - variable to hold number of data bands
			 <rows> - variable to hold number of rows
			 <cols> - variable to hold number of cols
                Returns: pointer to image data which can take on one of two
			 forms -- (1) an array of vectors/double pointer **, 
			 (2) an array of matrices/triple pointer ***.
            Description: returns a new instance of the image data that can be
			 processed in one of three forms... (1) BANVECFORM -
			 an array of <bands> vectors are returned where each
			 vector points to a different band of the image. (2)
			 PIXVECFORM - an array of <rows*cols> pixel vectors
			 are returned where each vector represents a different
			 pixel of the image. (3) MATRIXFORM - an array of
			 matrices where each matrix represents a different
			 band of the image. <type> specifies the type of the
			 data to be unloaded; which can be a different more
			 precise type if the user so wishes. If the type 
			 specified by <type> is less precise than the data type
			 of the image then a NULL pointer is returned.
			 NOTE: this function returns a new instance of the image
			 data and must be uploaded to the Image structure or 
			 freed with either vecfree(...) or matfree(...).
	    Diagnostics: returns NULL pointer w/ corresponding error upon
			 memory allocation failure or if an invalid Image
			 structure is passed.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

void	*unload_Image(	Image		*srcImage,
			DATAFORM	df,
			CVIP_TYPE	type,
			unsigned int	*bands,
			unsigned int	*rows,
			unsigned int	*cols)
{
	unsigned int	prows; /* pseudo rows */

	if( getDataType_Image(srcImage) > type )
	return(NULL);

	/* simplify some variables */
	*bands = getNoOfBands_Image(srcImage);
	prows = *rows = getNoOfCols_Image(srcImage);
	*cols = getNoOfCols_Image(srcImage);

	if( getDataFormat_Image(srcImage) == COMPLEX )
	prows <<= 1;

	if(df==MATRIXFORM)
	return(unloadmat(srcImage, type, *bands, prows, *cols));
	else
	return(unloadvec(srcImage, df, type, *bands, prows, *cols));
} /* End of function - unloadImage(...) */


/****************************************************************
                   Name: refBAND
          Expanded Name: reference BAND
             Parameters: <srcImage> - pointer to Image structure
			 <df> - data form/arrangement
			 <band_no> - number of band to be referenced
                Returns: pointer to data band in either band vector or matrix
			 format.
            Description: references a band of data from the Image structure in
			 either matrix (MATRIXFORM) or band vector (BANVECFORM)
			 format.  It is not possible to reference the data in
			 PIXVECFORM and doing so will simply default to
			 BANVECFORM.
	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

void *refBAND( Image *srcImage, DATAFORM df, int band_no )
{

	return((df == MATRIXFORM) ? (void *) srcImage->bandP[band_no]->rptr :
				(void *) srcImage->bandP[band_no]->rptr[0]);

} /* End of function - refBAND(...) */


/****************************************************************
                   Name: upload_Image
          Expanded Name: upload image
             Parameters: <srcImage> - pointer to Image structure
		         <dataP> - pointer to an array of matrices or vectors
			 allocated by vecalloc(...), matalloc(...) or returned
			 by unloadImage(...).
			 <df> - data format (BANVECFORM, PIXVECFORM, MATRIXFORM)
			 <type> - CVIPtools data type
			 <bands> - number of data bands
			 <rows> - number of rows
			 <cols> - number of cols
                Returns: nada
            Description: loads image data in one of three forms... (1)
			 BANVECFORM - an array of <bands> vectors where each
			 vector points to a different band of the image. (2)
			 PIXVECFORM - an array of <rows*cols> pixel vectors
			 where each vector represents a different pixel of the
			 image. (3) MATRIXFORM - an array of matrices where each
			 matrix represents a different band of the image. <type>
			 specifies the type of the data to be loaded. <type>,
			 <rows> and <cols> may be different from the values
			 specified in <srcImage> but <bands> must be the same.
			 If the number of <bands> differ an diagnostic message
			 is issued and the data is not loaded. NOTE: once the
			 data has been loaded the data once pointed to by
			 <dataP> should now only be referenced through the Image
			 structure and <dataP> should be considered invalid.
	    Diagnostics: returns and issuses a relative error message upon
			 memory allocation failure or if an invalid Image
			 structure is passed.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

void	upload_Image(	Image		*srcImage,
			void		*dataP,
			DATAFORM	df,
			CVIP_TYPE	type,
			unsigned int	bands,
			unsigned int	rows,
			unsigned int	cols)
{
	register int	i,j;
	void		***dP, *refP;
	short		size[5] = {	sizeof(byte),
					sizeof(short),
					sizeof(int),
					sizeof(float),
					sizeof(double)};
	const char	*fn = "uploadImage";

	if( rows != getNoOfRows_Image(srcImage) )
	for(i=0;i<bands;i++)
	srcImage->bandP[i]->rows = rows;
	if( cols != getNoOfCols_Image(srcImage) )
	for(i=0;i<bands;i++)
	srcImage->bandP[i]->cols = cols;
	if( type != getDataType_Image(srcImage) )
		for(i=0;i<bands;i++)
		srcImage->bandP[i]->data_type = type;

	if( getNoOfBands_Image(srcImage) != bands )
	{
		error_CVIP(fn,"Number of bands must equal that of source Image");
		return;
	}
	if( getDataFormat_Image(srcImage) == COMPLEX )
	rows <<= 1;

	if(df == PIXVECFORM)
	{
		refP = dataP;
		dataP = pixvec2banvec(refP, bands, rows*cols);
		vecfree(refP,rows*cols);
	}

	if(df != MATRIXFORM) {
		dP = (void ***) malloc(bands*sizeof(void **));
		for(i=0;i<bands;i++) {
			dP[i] = (void **) malloc(rows*sizeof(void *));
			for(j=0;j<rows;j++)
			dP[i][j] = ((byte **)dataP)[i] + j*cols*size[type];
		}
		free(dataP);
		dataP = dP;
	}
	if( getDataFormat_Image(srcImage) == COMPLEX )
	rows >>= 1;

	for(i=0;i<bands;i++) {

		free(srcImage->bandP[i]->rptr[0]);
		free(srcImage->bandP[i]->rptr);

		srcImage->bandP[i]->rptr = (char **) ((void***)dataP)[i];
		if( getDataFormat_Image(srcImage) == COMPLEX )
		srcImage->bandP[i]->iptr = (char **)(((void***)dataP)[i]+rows);
	}
	free(dataP);
} /* End of function - uploadImage(...) */


/****************************************************************
                   Name: dump_IMage
          Expanded Name: dump image
             Parameters: <srcImage> - pointer to Image structure
                Returns: 1 upon success; 0 upon failure.
            Description: print the contents of an Image structure
	    Diagnostics: returns 0 if the pointer to the Image structure
			 is not valid.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

CVIP_BOOLEAN	dump_Image(Image	*srcImage)
{
	char		*fn = "Imagedump";
	char		*cfn[] = {	"BINARY","GRAY_SCALE","RGB",
					"HSL","HSV","SCT","CCT","LUV",
					"LAB", "XYZ"};
	char		*dtn[] = {	"CVIP_BYTE","CVIP_SHORT","CVIP_INTEGER",
					"CVIP_FLOAT","CVIP_DOUBLE"};
	char		*dfn[] = {	"REAL", "COMPLEX"};
	register int	i;

	error_CVIP(fn,"displaying Image structure content...\n");
	error_CVIP(fn,"=====================================\n");
	error_CVIP(fn,"Image File Format - %s\n",
		image_format_string[srcImage->image_format]);
	error_CVIP(fn,"Current Color Space - %s\n",
		cfn[srcImage->color_space]);
	error_CVIP(fn,"No. of data bands - %d\n",srcImage->bands);
	error_CVIP(fn,"Examining individual data bands...\n");
	if(srcImage->image_ptr==NULL) {
		error_CVIP(fn,"NULL pointer found for Matrix **image_ptr\n");
		return(CVIP_NO);
	}
	for(i = 0; i < srcImage->bands; i++) {
		error_CVIP(fn,"(Band %d)\n",i);
		if(srcImage->bandP[i]==NULL) {
			error_CVIP(fn,
			"NULL pointer found for Matrix *image_ptr[%d]\n",i);
			return(CVIP_NO);
		}
		error_CVIP(fn,
			"Data Type - %s\n",
			dtn[srcImage->bandP[i]->data_type]);
		error_CVIP(fn,
			"Data Format - %s\n",
			dfn[srcImage->bandP[i]->data_format]);
		error_CVIP(fn,"Rows - %d\n",  srcImage->bandP[i]->rows);
		error_CVIP(fn,"Cols - %d\n",  srcImage->bandP[i]->cols);
	}
	return(CVIP_YES);
}


/****************************************************************
                   Name: makeComplex_Image
          Expanded Name: make complex image
             Parameters: <srcImage> - pointer to "real" Image structure
                Returns: nada
            Description: create a "complex" Image structure by reallocating
			 the storage the associated with the Image -- <srcImage>
	    Diagnostics: complains when an invalid Image structure is passed
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

void makeComplex_Image(Image *srcImage)
{
	unsigned int	bands = getNoOfBands_Image(srcImage);
	register int	i;

	for(i = 0; i < bands; i++)
	(void)makeComplex_Matrix(srcImage->bandP[i],CVIP_NO);
}


/****************************************************************
                   Name: makeReal_Image
          Expanded Name: make real image
             Parameters: <srcImage> - pointer to "complex" Image structure
                Returns: nada
            Description: create a "real" Image structure by reallocating
			 the storage the associated with the Image -- <srcImage>
	    Diagnostics: complains when an invalid Image structure is passed
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

void makeReal_Image(Image *srcImage)
{
	unsigned int	bands = getNoOfBands_Image(srcImage);
	register int	i;

	for(i = 0; i < bands; i++)
	(void) matrix_makereal(srcImage->bandP[i], CVIP_NO);
}

void getBandVector_Image(Image *imageP, void *vecP)
{
   register int i;

   for(i=0; i < getNoOfBands_Image(imageP); i++)
      ((void **) vecP)[i] = getRow_Image(imageP, 0, i);
}

void 
selectCopy_Image(
	Image		*image_aP,
	Image		*image_bP, 
	void		*selectP, 
	unsigned	no_of_sel
)
{
	unsigned	img_size, bands;
	int		**bvecP, **avecP;
	register int	i, j, k, *aP, *bP, *sP;

	img_size = getNoOfRows_Image(image_aP)*getNoOfCols_Image(image_aP);
	bands = getNoOfBands_Image(image_aP);

	avecP = (int **) malloc(sizeof(int *)*bands);
	bvecP = (int **) malloc(sizeof(int *)*bands);

	if((avecP == NULL) || (bvecP == NULL))
	{
		error_CVIP("selectCopy_Image","Unable to allocate memory.\n");
		if(avecP != NULL)
		free(avecP);

		if(bvecP != NULL)
		free(bvecP);

		return;
	}

	getBandVector_Image(image_aP, avecP);
	getBandVector_Image(image_bP, bvecP);

	for(i=0; i < bands; i++)
	{
		aP = avecP[i];
		bP = bvecP[i];
		for(j=0; j < img_size; j++, aP++, bP++)
		for(k=0, sP = selectP; k < no_of_sel; k++, sP++)
		if(*aP == *sP)
		{
			*bP = *aP;
			break;
		}
	}
	free(avecP);
	free(bvecP);
}

int
findMinVal_Image(
	const Image	*imgP,
	double		*minvec
)
{
	register int	i;
	unsigned	bands, imgsize;
	void		**vecP;

	bands 	= getNoOfBands_Image(imgP);
	imgsize	= getNoOfRows_Image(imgP)*getNoOfCols_Image(imgP);
	vecP	= (void **) malloc(bands*sizeof(void *));
	if(vecP == NULL)
	{
		error_CVIP("findMinVal_Image","Unable to allocate memory.\n");
		return(0);
	}
	getBandVector_Image((Image *)imgP, vecP);

	for(i=0; i < bands; i++)
	minvec[i]= findMinVal_Vector(vecP[i], imgsize, getDataType_Image(imgP));

	free(vecP);
	return(1);
}


int
findMaxVal_Image(
	const Image	*imgP,
	double		*maxvec
)
{
	register int	i;
	unsigned	bands, imgsize;
	void		**vecP;

	bands 	= getNoOfBands_Image(imgP);
	imgsize	= getNoOfRows_Image(imgP)*getNoOfCols_Image(imgP);
	vecP	= (void **) malloc(bands*sizeof(void *));
	if(vecP == NULL)
	{
		error_CVIP("findMaxVal_Image","Unable to allocate memory.\n");
		return(0);
	}
	getBandVector_Image((Image *)imgP, vecP);

	for(i=0; i < bands; i++)
	maxvec[i]= findMaxVal_Vector(vecP[i], imgsize, getDataType_Image(imgP));

	free(vecP);
	return(1);
}

Image *
clone_Image(
	const Image	*imgP,
	CVIP_TYPE		dt
)
{
	return 	new_Image(
		getFileFormat_Image(imgP),
		getColorSpace_Image(imgP),
		getNoOfBands_Image(imgP),
		getNoOfRows_Image(imgP),
		getNoOfCols_Image(imgP),
		dt,
		getDataFormat_Image(imgP)
	);
}
	
int
copy_Image(
	const Image 	*srcP,
	Image 		*desP
)
{
	register int	i;
	unsigned	src_bands;

	src_bands = getNoOfBands_Image(srcP);

	if(src_bands > getNoOfBands_Image(desP)) {
		error_CVIP("copy_Image",
		"bands in destination image must be >= that of source");
		return(0);
	}

	for(i=0; i < src_bands; i++)
	if(!copy_Matrix(getBand_Image(srcP,i),getBand_Image(desP,i)))
	return(0);

	history_copy((Image*)srcP,desP);
	return(1);
}

int
abs_Image(
	Image		*imgP
)
{
	unsigned	n_b;

	n_b	= getNoOfBands_Image(imgP);

	while(n_b--)
	if(!abs_Matrix(getBand_Image(imgP, n_b)))
	return(0);

	return(1);
}

int
cropBands_Image(
	Image	*imgP,
	int	crop_bands
)
{
	unsigned	bands, new_bands;
	register int	i;

	bands = getNoOfBands_Image(imgP);
	if(bands < crop_bands)
	{
	error_CVIP(	"cropBands_Image",
			"Can not crop % bands from an image with % bands\n",
			crop_bands,bands);
	return(0);
	}
	new_bands = bands - crop_bands;

	setNoOfBands_Image(imgP, new_bands);
	if(new_bands == 1) {
		setFileFormat_Image(imgP, PGM);
		setColorSpace_Image(imgP, GRAY_SCALE);
	}

	for(i=new_bands; i < bands; i++)
	delete_Matrix(getBand_Image(imgP, i));

}

float *
getDataRange_Image(
	Image *imageP
)
{
	CVIP_TYPE	dt;
	int		i, count;
	unsigned	no_of_bands, imgsize, rows, cols;
	float		*min_maxP, min, max;
	void		**imgvecP = NULL, **imgvecPi = NULL;
	FORMAT		format;

	dt = getDataType_Image(imageP);
	format = getDataFormat_Image(imageP);
	no_of_bands = getNoOfBands_Image(imageP);
	rows = getNoOfRows_Image(imageP);
	cols = getNoOfCols_Image(imageP);
	imgsize = rows*cols;

	imgvecP = (void **)malloc(sizeof(void *)*no_of_bands);
	if(imgvecP == NULL)
	{
		error_CVIP(	"getDataRange_Image",
				"Unable to allocate memory.\n");
		return(NULL);
	}
	getBandVector_Image((Image *)imageP, imgvecP);

	if(format == COMPLEX) {
		int count = 0;
		imgvecPi = (void **) malloc(sizeof(void *)*no_of_bands);
		if(imgvecPi == NULL)
		{
			free(imgvecP);
			error_CVIP(	"getDataRange_Image",
					"Unable to allocate memory.\n");
			return(NULL);
		}
		for (count = 0; count < no_of_bands; count ++) 
		imgvecPi[count] = getImagRow_Image(imageP, 0, count);
		min_maxP = (float *)malloc(sizeof(float)*(no_of_bands*4+2));
		if(min_maxP == NULL)
		{
			free(imgvecP);
			free(imgvecPi);
			error_CVIP(	"getDataRange_Image",
					"Unable to allocate memory.\n");
			return(NULL);
		}
	}
	else
	min_maxP = (float *) malloc(sizeof(float)*(no_of_bands*2+2));

	count = 0;
	for(i=0; i < no_of_bands; i++) {
		min_maxP[count++] = findMinVal_Vector(imgvecP[i], imgsize, dt);

		if(i)
		min = (min < min_maxP[count-1]) ? min : min_maxP[count-1];
		else
		min =  min_maxP[count-1];

		min_maxP[count++] = findMaxVal_Vector(imgvecP[i], imgsize, dt);

		if(i)
		max = (max > min_maxP[count-1]) ? max : min_maxP[count-1];
		else
		max =  min_maxP[count-1];

		if(format == COMPLEX) {
			min_maxP[count++] = findMinVal_Vector(
						imgvecPi[i], imgsize, dt);
			min=(min < min_maxP[count-1]) ? min : min_maxP[count-1];
			min_maxP[count++] = findMaxVal_Vector(	imgvecPi[i],
								imgsize, dt);
			max=(max > min_maxP[count-1]) ? max : min_maxP[count-1];
		}
	}  
	min_maxP[count++] = min;
	min_maxP[count] = max;
	free(imgvecP); 
	if(format == COMPLEX) {
		free(imgvecPi);
	}
/*	while (count>=0) {
	printf("max = %f, min = %f\n", min_maxP[count--], min_maxP[count--]);
	}*/
	return((float *)min_maxP);
}
