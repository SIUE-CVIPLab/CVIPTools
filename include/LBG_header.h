/***************************************************************************
*
*             File Name: LBG_header.h
*           Description: 
*         Related Files: 
*   Initial Coding Date: Fri Feb 27 19:02:55 CST 1998
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): 
*                        Southern Illinois University @ Edwardsville
*
* RCS (Revision Control System) Information
* ...Added automatically by RCS 
*
** $Log: LBG_header.h,v $
** Revision 1.6  1998/04/02 00:11:53  wzheng
** all parameters working
**
** Revision 1.5  1998/03/10 02:27:34  wzheng
** add ERR_METHOD    error_method
**
** Revision 1.4  1998/03/01 21:01:25  wzheng
** one codebook for mutiple color band at each subimage
**
** Revision 1.3  1998/02/28 01:03:29  wzheng
** *** empty log message ***
**
*
****************************************************************************/
/***************************************************************************
*
*             File Name: LBG_header.h
*           Description: 
*         Related Files: 
*   Initial Coding Date: Tue Feb  3 19:58:10 CST 1998
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): 
*                        Southern Illinois University @ Edwardsville
*
* RCS (Revision Control System) Information
* ...Added automatically by RCS 
*
** $Log: LBG_header.h,v $
** Revision 1.6  1998/04/02 00:11:53  wzheng
** all parameters working
**
** Revision 1.5  1998/03/10 02:27:34  wzheng
** add ERR_METHOD    error_method
**
** Revision 1.4  1998/03/01 21:01:25  wzheng
** one codebook for mutiple color band at each subimage
**
** Revision 1.3  1998/02/28 01:03:29  wzheng
** *** empty log message ***
**
** Revision 1.2  1998/02/07 04:48:52  wzheng
** add VQ_info:subimg_nbr, total_entry
**
** Revision 1.1  1998/02/04 01:58:29  wzheng
** Initial revision
**
*
****************************************************************************/
#ifndef LBG_STRUCTURE
#define LBG_STRUCTURE
#include<stdio.h>
#include<stdlib.h>
#include<CVIPdef.h>

/*
 * SUBIMAGE
 */
typedef struct{
  int		start_row;	/* x-coordinate of the subImage start pixel*/
  int		start_col;	/* y-coordinate of the subIamge start pixel*/
  int		end_row;	/* x_coordiante of the subImage end pixel */
  int		end_col;	/* y_coordiante of the subImage end pixel */
} SUB_IMAGE;
/*
 * the VECTOR_LST stores all the information for a list of vectors.
 * It can be used to allocate codebooks and image training sets.
 * 1. vector_size is result of converting 2-D vector into
 *    1-D vector.  vector_size = vector_height * vector_length
 * 2. total_entry is the total number of the entries in the 
 *    codebook.
 * 3. vector is a two dimetional array. It stalls the data of the vector
 *    the first indices correspend with the indices of the vectors.
 *    for example, vector[6] correpond the fifth vector in the vector list. 
 *    the sequence of the data in the vector is get from left to right, 
 *    upper to bottom converting from corresponding 2-D vector.
 *    the data type of the vector depends on the data type of the image.
 */
typedef struct{
  int		vector_size;	/* the length of the vector,height*length*/
	int   vector_heigth;
  int		total_entry;	/* the total number of the entries in the codebook*/
  void          **vector;	/* the data stored in the vector	*/
}VECTOR_LST;

typedef enum err_method {single, mean_square} ERR_METHOD;

/*
 *
*/
typedef struct VQ_info{
  int           cdbook_in_file; /* 0 indicate: cdbook is not in the vq_code file */
  char          *cdbook_file;    /* the file name of cdbook, used only when cdbook_in_file=0 */
  CVIP_TYPE	    data_type;	/* indicate the image data type */
  int		        color_band;	/* coresponding color band (same as cvip image sequence) */
  int           subimg_nbr;        /* number of subimages */
  SUB_IMAGE	    *subimage_range;
  int           total_row;
  int           total_col;
  int           fixed_cdbook;   /* 0 indicate: cdbook is not fixed */
  int		        *row_vector;	/* no_of_rows in one vector */
  int		        *col_vector;	/* no_of_cols in one vector */
  int		        *total_vector;	/* the total number of vectors in each band of the subImage*/
  int           *total_entry;       /* the total number of the entries in the codebook*/
  double	      **error;	/* the error between training_set and codebook*/
                                /* [subimg][vector] */
  unsigned int  **coding_result; /* the series encoded index number */
                                  /* [subimg][vector] */
  float         *error_threshold;  /* the limit that error can be tolerated */
                                    /* [subImg] */
  ERR_METHOD    error_method;       /* the error method */
}VQ_INFO;

#endif
