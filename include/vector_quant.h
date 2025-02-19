#ifndef LBG_STRUCTURE
#define LBG_STRUCTURE

#include<stdio.h>
#include<stdlib.h>
#include<CVIPdef.h>

#define CVIP_MAX_PATH 150 /* max length of the full path in CVIPtools */
/*  SUBIMAGE*/
 
typedef struct{
  int		bands_num;	/* color band number of this subImage*/
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
  int   	vector_heigth;
  int		total_entry;	/* the total number of the entries in the codebook*/
  void  	**vector;	/* the data stored in the vector	*/
}VECTOR_LST;

typedef enum err_method {Single, mean_square} ERR_METHOD;
typedef enum xform_fmt {REGULAR_FORMAT, VQ_15, VQ_PCT_15, VQ_30, VQ_PCT_30, VQ_55, VQ_PCT_55, VQ_80, VQ_PCT_80, VQ_set, VQ_PCT_set} XFORM_FMT;

/*	VQ_INFO contains all the information, except codebook vector data, 
 *	this data structure exists all through the program
*/
typedef struct VQ_info1{
  Image		*inputImage;	/* input image to be compressed*/
  XFORM_FMT	xform;		/* scheme tye, REGULAR, WVQ3 ...*/
  char		*temp_file;	/* the temp file to cotain compreesed image*/
  int		color_processed;/* 1: using different codebook for different bands, 0: one codebook for all 3 bands.*/
  int           cdbook_in_file; /* 0 indicate: cdbook is not in the vq_code file */
  char          *cdbook_file;    /* the file name of cdbook, used only when cdbook_in_file=0 */
  CVIP_TYPE	data_type;	/* indicate the image data type */
  int		color_band;	/* coresponding color band (same as cvip image sequence) */
  int           subimg_nbr;        /* number of subimages */
  SUB_IMAGE	*subimage_range;
  int           total_row;
  int           total_col;
  int           fixed_cdbook;   /* 0 indicate: cdbook is not fixed */
  int		*row_vector;	/* no_of_rows in one vector */
  int		*col_vector;	/* no_of_cols in one vector */
  int		*total_vector;	/* the total number of vectors in each band of the subImage*/
  int           *total_entry;       /* the total number of the entries in the codebook*/
  double	**error;	/* the error between training_set and codebook. error[subimg][vector]*/
  unsigned int  **coding_result; /* the series encoded index number coding_result[subimg][vector]*/
  float         *error_threshold;  /* the limit that error can be tolerated error_threshold[subImg]*/
  ERR_METHOD    error_method;       /* the error method */
}VQ_INFO;
#endif
#ifdef __cplusplus
extern "C"{
#endif 

extern int initial_codebook (
        VECTOR_LST *cdbook,
        VECTOR_LST *training_set,
        CVIP_TYPE data_type
        );

extern int initial_training_set(const Image *inputImage, 
				VECTOR_LST *training_set, 
				int row_vector, int col_vector, 
				SUB_IMAGE img_range, 
				int color_processed);


int compression_result (VQ_INFO *coding_info);

int encode_subimage (
        int        subimg_nbr,
        VECTOR_LST *cdbook,
        const VECTOR_LST *training_set,
        VQ_INFO *coding_info
        );

int allocate_vector_sets (VECTOR_LST **aset,
     int no_of_sets,
     int no_of_entries,
     int length_vector,
		 int vector_heigth,
     CVIP_TYPE data_type
     );

void free_vector_sets(VECTOR_LST **cdbook, int no_of_band);
void free_codebooks (VECTOR_LST **cdbook, int no_of_band , int no_of_subImg);
void free_coding_info(VQ_INFO *coding_info);

int define_codebook(VECTOR_LST *cdbook,
     const VECTOR_LST *training_set,
     VQ_INFO *coding_info,
     int subimg_nbr
     );


int initial_info_coding_result (
        VECTOR_LST *cdbook,
        const VECTOR_LST *training_set,
        VQ_INFO *coding_info,
        int subimg_nbr 
        );



double cbk_training_distance (
				void *cbk_vector,
				void *trn_vector,
				int vector_size,
				CVIP_TYPE data_type);

int single_vector_checking (
		 VQ_INFO *coding_info,
		 double *prev_error,
		 int    subimg_nbr
		 );

int average_mean_square(
		 VQ_INFO *coding_info,
		 double *prev_error,
		 int    subimg_nbr
		 );
/*********************** Write & Read ***********************/

void WriteHeader (
        VQ_INFO     *vq_info,
        FILE        *file
        );

void WriteVectors (
     unsigned int       *VectorArray,
     unsigned int       TotalVectors,
     unsigned int       BitsUsed,
     FILE               *file
     );

int ReadVectors(
     unsigned int       *VectorArray,
     unsigned int       TotalVectors,
     unsigned int       BitsUsed,
     FILE               *file
     );


int GetCodebook (
	FILE          *file,
	VECTOR_LST    *cdbook,
	CVIP_TYPE     datatype
	);

/*******************************************************************
                    DECOMPRESSION
*******************************************************************/

void    **Alloc2DArray( int             Rows,
                        int             Cols,
                        CVIP_TYPE       data_type);

/*****************************************************************
		New function
*********************************************************************/
int get_vq_info (
  	Image         *inputImage,
	char          *temp_file,
	int           cdbook_in_file,
	int           fixed_codebook,   /* 0: indicate the code book is allowed to modified */
	float         in_error_thres,
	char          *cdbook_file,
	int           in_no_of_entries,
	int           in_row_vector,    /* the number of rows within a vector */
	int           in_col_vector,    /* the number of cols within a vector */
	XFORM_FMT     xform,
	VQ_INFO	      *coding_info 
	);
	
int	get_info_from_codebook_file(VQ_INFO *coding_info );
	
void   	print_vq_info(VQ_INFO *coding_info);
extern Image 	*vq_decompress(char *filename);
extern int 	vq_compress (
  	Image         *inputImage,
	char          *temp_file,
	int           cdbook_in_file,
	int           fixed_codebook,   /* 0: indicate the code book is allowed to modified */
	float         in_error_thres,
	char          *cdbook_file,
	int           in_no_of_entries,
	int           in_row_vector,    /* the number of rows within a vector */
	int           in_col_vector,    /* the number of cols within a vector */
	XFORM_FMT     xform
	);
	
extern int 	vq_compression (  VQ_INFO  *vq_info , VECTOR_LST   **cdbook);

int	write_to_disk( VQ_INFO *vq_info, VECTOR_LST   **cdbook );

void 	WriteCodebookHeader(FILE *cdbook_file, VQ_INFO *vq_info);

void 	WriteCodebook (
     	FILE            *file,
     	VECTOR_LST      *cdbook,
     	VQ_INFO         *vq_info,
     	int	     subimg
     	);

int 	get_vq_info_from_file( char *file,VQ_INFO *vq_info );	

int 	read_cdbook_info_from_file(FILE *file, VQ_INFO *vq_info);

extern int	vq_decompression (VQ_INFO *vq_info, FILE *file  , FILE *file_result);

int 	ReadCodebook (	FILE          	*file,
        		VECTOR_LST    	*cdbook,
        		CVIP_TYPE    	datatype
        		);
int 	get_BitsInInt(void);

extern Image *VQ_read_decompression(FILE *fp);

extern Image *xvq(Image *image, int xform, int scheme, char *filename, int file_type, int remap_type, int dc);
extern Image *xvq_compress(Image *image, int xform, int scheme, char *filename, int file_type, int remap_type, int dc);

extern Image *XVQ_read_decompression(FILE *fp, Image *imgP);

extern Image *xvq_decompress(char *filename);

extern Image *trans_compr(char *filename,char *quantfile, Image *image, int color_space, int xform, int WAVELET_basic, 
			 int subimage_size, int quant, int JPEG_Q_Table, int use_vq, int data_type, int remap_type, int keep_DC);

#ifdef __cplusplus
}
#endif 
