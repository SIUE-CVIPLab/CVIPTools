/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: vector_quantization.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Mon Mar 23 18:22:02 CST 1998
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): 
*                        Southern Illinois University @ Edwardsville
*
* RCS (Revision Control System) Information
* ...Added automatically by RCS 
*
** $Log: vector_quantization.c,v $
** Revision 1.29  2001/04/04 06:13:35  ycheng
** fixed one bug.
**
** Revision 1.28  2000/05/09 17:38:19  ycheng
** revised the display message about compression ratio.
**
** Revision 1.27  2000/01/05 23:11:49  ycheng
** revised again the display message of the size of the original raw data.
**
** Revision 1.26  2000/01/04 22:47:36  ycheng
** revised an error about the display message of the size of the original raw data.
**
** Revision 1.25  1999/12/17 18:00:43  ycheng
** corrected the display message about the size of original raw data.
**
** Revision 1.24  1999/12/13 20:17:26  ycheng
** remove a duplicate information in vq_compress().
**
** Revision 1.23  1999/11/23 23:42:24  ycheng
** added the header file for Win32.
**
** Revision 1.22  1999/11/21 04:56:31  ycheng
** when reading vq compressed files from disk, a temporary file had been written and read to/from 'c.cvip_temp' directory. So the path of '.cvip_temp' must be found by the program itself.
**
** Revision 1.21  1999/11/15 19:11:15  ycheng
** rename function VQ_decompression() and XVQ_decompression() to VQ_read_decompression() and XVQ_read_decompression() respectively.
** move function XVQ_read_decompression() to the file xvq.c.
**
** Revision 1.20  1999/11/11 22:32:35  ycheng
** function VQ_decompression() and XVQ_decompression() has been added.
**
** Revision 1.19  1999/05/30 23:27:05  lguo
** some print out commented out
**
** Revision 1.18  1999/05/30 22:46:53  lguo
** some print out commented out
** VQ_set and VQ_PCT_set are added to support customizing xvq set
**
** Revision 1.17  1999/05/13 05:15:20  lguo
** small bugs fixed
**
** Revision 1.16  1999/04/27 22:39:53  lguo
** now vq scheme support different compression schemes: VQ_15...VQ_80, VQ_PCT_15...VQ_PCT_80
**
** Revision 1.14  1999/04/20 22:56:43  lguo
** added printing out the result
** delete some out put printing
**
** Revision 1.13  1999/04/20 22:07:31  lguo
** *** empty log message ***
**
** Revision 1.12  1998/12/01 22:49:08  lguo
** no changes
**
** Revision 1.11  1998/11/25 03:56:39  lguo
**  enough comment before the fuction begins.
** the version reserves many print out as debugging reference, which will be deleted before freezing. 
**
** Revision 1.10  1998/11/20 04:46:15  lguo
** new version. finished the get_vq_info, compression, write_to _disk part, in a word, the compress is finished and tested.
**
** Revision 1.9  1998/11/14 07:16:25  lguo
** *** empty log message ***
**
** Revision 1.8  1998/11/14 05:56:42  lguo
** when a color img is inputed, diferent color bands will be counted as different sub_image. bands_num is added to sub_img_range in .h file. get_image_range() is changed.
**
** Revision 1.7  1998/10/24 09:04:48  lguo
** fix bugs. now it works firmly
**
** Revision 1.6  1998/05/30 01:43:20  wzheng
** subimage works for all functions
**
** Revision 1.5  1998/05/27 23:08:57  wzheng
** *** empty log message ***
**
** Revision 1.4  1998/05/19 01:38:56  wzheng
**  subimg number save into seperate codebook file
**
** Revision 1.3  1998/04/08 02:50:56  wzheng
** add compression ratio calculation routine
**
** Revision 1.2  1998/04/08 01:55:54  wzheng
** *** empty log message ***
**
** Revision 1.1  1998/03/24 00:23:09  wzheng
** Initial revision
**
*
****************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<CVIPtoolkit.h>
#include<CVIPdef.h>
#include <vector_quant.h>
#include <sys/stat.h>
#include <vector_data.h>
#ifndef WIN32
#include <unistd.h>
#include <pwd.h>
#include <dirent.h>
#else
#include <io.h>
#include <direct.h>
#endif

   extern  int VQ_set_vector_height[];
   extern  int VQ_set_vector_width[];
   extern  int VQ_set_vector_entries[];

/****************************************************************************
in this file, here are this functions:
	compression_result(VQ_INFO *coding_info)
	vq_decompress ( char *file )
	vq_compress ()
	get_vq_info ()
****************************************************************************/
/****************************************************************************
	this fuction print out the compress ratio 
****************************************************************************/
 int compression_result(VQ_INFO *coding_info)
  {
	long file_size;
	long image_size;
	long pixel_length;
	struct stat s_buf;        /*structure used to contain file info */
/*	 fprintf(stderr, "begin compression_result(VQ_INFO *coding_info)\n");*/

   switch(coding_info->data_type) {
   case CVIP_BYTE:
			pixel_length = sizeof(byte);
      break;
   case CVIP_SHORT:
			pixel_length = sizeof(short);
      break;
   case CVIP_INTEGER:
			pixel_length = sizeof(int);
      break;
   case CVIP_FLOAT:
			pixel_length = sizeof(float);
      break;
   case CVIP_DOUBLE:
			pixel_length = sizeof(double);
      break;
   default:
      fprintf(stderr,"Unrecognized image data type?\n");
      return 0;
   }
	 image_size = coding_info->total_row*coding_info->total_col*coding_info->color_band*pixel_length;

  if (stat(coding_info->temp_file, &s_buf)==0)
  {
	file_size = (long)s_buf.st_size;
	  
	 /*fprintf(stdout, "\ncoding_info->data_type = %d\n", coding_info->data_type);*/
	 if(coding_info->data_type == CVIP_BYTE) /*display the Compression Ratio when the data type is BYTE*/
	  {
	    printf("\n\tThe original raw data occupies %ld bytes",image_size);
	    printf("\n\tThe compressed data occupies %ld bytes",file_size);
	    printf("\n\tThe Compression ratio : %.2f\n\n",(image_size)/(float)file_size);
	  }
	
  }
}
/***********************************************************************
		 DECOMPRESSION
		 first moduel: get all informarion besides codebook vectors
		 from temp_fiel and codebook file, writing into vq_info
**********************************************************************/

Image *vq_decompress ( char *file )
{
	VQ_INFO	*vq_info;
	FILE	*temp_file, *cdbook, *file_result;
	Image	*output;
	int	length, subimg ;
	
	/*	 fprintf(stderr, "begin Image *vq_decompress ( char *file )\n");*/
	
	vq_info = (VQ_INFO *)calloc(1, sizeof(VQ_INFO));
	
	/* first module: get info from disk files to fill vq_inf*/
	/* fprintf(stderr, "begin get_vq_info_from_file (file, vq_info )\n");*/
  	if ( get_vq_info_from_file (file, vq_info )!=1 )
	{
		fprintf(stderr, "decompress: get_vq_info_from_file() failed\n");
	   	return 0;
	}

	/*	print_vq_info(vq_info);*/
  	if( vq_info->color_band == 3)
    		output = (Image *)new_Image(	PPM, RGB, 3,vq_info->total_row,
                                  		vq_info->total_col,
                                  		vq_info->data_type, REAL);
  	else if ( vq_info->color_band == 1)
    		 output = (Image *)new_Image(	PGM, GRAY_SCALE, 1,vq_info->total_row,
                                  		vq_info->total_col,
                                  		vq_info->data_type, REAL);
  	else
  	  {	fprintf(stderr, "decompress: vq_info->color_band is not 1 or 3\n");
	   	return 0;
  	  }
  	vq_info->inputImage = output;
	/* second module*/
	 /*decide where to read the vector data, stored  in temp_file*/
	if (vq_info->cdbook_in_file==1)
	   {	temp_file = fopen(file, "rb");
	   	fseek(temp_file, 2*sizeof(char)+8*sizeof(int),0/*SEEK_SET*/);
	   }/*end of if*/
	  else
	   {	temp_file = fopen(vq_info->cdbook_file, "rb");
	   	fseek(temp_file, 7*sizeof(int),0/*SEEK_SET*/);
	    }/*end of else*/
	    
	 /*decide where is coding_result, in  file_result */
	 if (!(file_result = fopen(file, "rb")))
	  {	fprintf(stderr, "open temp_file failed\n");
	  	return 0;
	  }
	 if ( vq_info->cdbook_in_file==0)
	  { 	fseek(file_result, 2*sizeof(char)+sizeof(int), 0/*SEEK_SET*/);
	  	fread(&(length), sizeof(int),1,file_result);
	  	fseek(file_result, 2*sizeof(char)+2*sizeof(int)+length*sizeof(char), 0/*SEEK_SET*/);
	  } /*end of if*/
	 else
	  {	length=2*sizeof(char)+8*sizeof(int);
	  	for (subimg=0; subimg<vq_info->subimg_nbr; subimg++)
	  	  {length= length+3*sizeof(int)+sizeof(float)+sizeof(SUB_IMAGE);
	  	   switch(vq_info->data_type)
	  	   {
	  	    case CVIP_BYTE:
	  	   	length=length+sizeof(byte)*vq_info->row_vector[subimg]*
	  	   		vq_info->col_vector[subimg]*vq_info->total_entry[subimg];
	  	   	break;
	  	    case CVIP_SHORT:
	  	   	length=length+sizeof(short)*vq_info->row_vector[subimg]*
	  	   		vq_info->col_vector[subimg]*vq_info->total_entry[subimg];
	  	   	break;
	  	    case CVIP_INTEGER:
	  	   	length=length+sizeof(int)*vq_info->row_vector[subimg]*
	  	   		vq_info->col_vector[subimg]*vq_info->total_entry[subimg];
	  	   	break;
	  	    case CVIP_FLOAT:
	  	   	length=length+sizeof(float)*vq_info->row_vector[subimg]*
	  	   		vq_info->col_vector[subimg]*vq_info->total_entry[subimg];
	  	   	break;
	  	    case CVIP_DOUBLE:
	  	   	length=length+sizeof(double)*vq_info->row_vector[subimg]*
	  	   		vq_info->col_vector[subimg]*vq_info->total_entry[subimg];
	  	   	break;
	  	   }
	  	  fseek(file_result, length, 0/*SEEK_SET*/); 
	  	  }
	  }/*end of else*/
	  
	  
/*	 fprintf(stderr, "begin vq_decompression(vq_info, temp_file , file_result )\n");*/
  	if (  vq_decompression(vq_info, temp_file , file_result )!=1 )
	 {	fprintf(stderr, "decompress: vq_compression() failed\n");
	   	return 0;
	 }
	 fclose(temp_file);
	 fclose(file_result);
/*	 fprintf(stderr, "begin to free memory\n");*/
	 free_coding_info(vq_info );
	 free(vq_info);

	 return output;  
   }/*end of vq_decompress*/



/*******************************************************************
	In this vq_compress (), there are 3 modules:
		1, get_vq_info(), taking charge of constructing and filling
		coding_info-> when u want to add new function or data
		for pre-process, rectify this part.
		2, compression(), taking charge of encoding. if u want to 
		improve new compression algorithsm, change this part.
		3, writing to disk, taking charge of writing temp_file &
		codebook_file to disk. if u want to change fomat of codebook,
		change this part.
*******************************************************************/
int vq_compress (
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
	)
{

	VQ_INFO       	*coding_info;
	VECTOR_LST   	**cdbook;
      	
	coding_info =(VQ_INFO *)calloc( 1, sizeof(VQ_INFO));
	/*call the first module*/
	/* fprintf(stderr,"begin get_vq_info() \n");*/ 
	if ( get_vq_info(	inputImage,
				temp_file,
				cdbook_in_file,
				fixed_codebook,
				in_error_thres,
				cdbook_file,
				in_no_of_entries,
				in_row_vector,
				in_col_vector,
				xform, 
				coding_info) !=1) 
	{
		fprintf(stderr,"get_vq_info() failed\n");
		return 0;
	}
	/*	fprintf(stderr,"begin print_vq_info \n");*/
	/*	print_vq_info(coding_info);*/
	
  	cdbook = (VECTOR_LST **)calloc(coding_info->subimg_nbr, sizeof(VECTOR_LST*));

	/* 	fprintf(stderr,"begin vq_compression\n");*/
	if ( vq_compression( coding_info ,cdbook)!=1)
	{
		fprintf(stderr,"compression(  ) failed\n");
		return 0;
	}
	else
	/* {fprintf(stderr,"compression(  ) passed\n"); }*/
	/*	fprintf(stderr,"begin write_to_disk\n");*/
	if ( write_to_disk( coding_info ,cdbook)!=1)
	{
		fprintf(stderr,"write_to_disk(  ) failed\n");
		return 0;
	}
	else
	{/*fprintf(stderr,"write_to_disk(  ) passed\n"); */}
	
	compression_result(coding_info);
	
	/*	 fprintf(stderr, "begin to free memory\n");*/
	free_coding_info(coding_info );
	free(coding_info);
	/* compression_result (coding_info);*/
	return 1;
	
}
/******************************************************************************************/
/******end of vq_compress() ************/
/******************************************************************************************/
	
/*************************************************************************
	get_vq_info() fills the coding_info
*************************************************************************/	
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
	)
{
	int	c_end, r_end, i, j, subImg;

	coding_info->inputImage = inputImage;
	coding_info->xform = xform;

	/* xchen update */
	coding_info->temp_file = (char *)calloc(CVIP_MAX_PATH, sizeof(char));
	if (coding_info->temp_file == NULL)
		return -1;
	strcpy(coding_info->temp_file, temp_file);

	coding_info->data_type = getDataType_Image(inputImage);
	coding_info->color_band = getNoOfBands_Image(inputImage);

	coding_info->total_row = getNoOfRows_Image(inputImage);
	coding_info->total_col = getNoOfCols_Image(inputImage);
	coding_info->fixed_cdbook = fixed_codebook;

	coding_info->cdbook_file = (char *)calloc(CVIP_MAX_PATH, sizeof(char));
	if (coding_info->cdbook_file == NULL)
		return -1;
	strcpy(coding_info->cdbook_file, cdbook_file);

	/* coding_info->cdbook_file = cdbook_file; */
	coding_info->cdbook_in_file = cdbook_in_file;
	
	/*** using switch(xform) to get: 
		coding_info->color_processed
		coding_info->subimg_nbr
		coding_info->row_vector
		coding_info->col_vector
		coding_info->subimage_range
		coding_info->total_entry
	********************************/
	if ( coding_info->fixed_cdbook )
	{	
/*	fprintf(stderr,"begin get_info_from_codebook_file(coding_info)\n");*/
		return get_info_from_codebook_file(coding_info);}
	
/*	fprintf(stderr,"begin switch in get_vq_info ()\n");*/
	switch(xform)
	{ case 	REGULAR_FORMAT:
		coding_info->color_processed = 0;
		coding_info->subimg_nbr = 1;
		coding_info->row_vector = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		coding_info->row_vector[0] = in_row_vector;
		coding_info->col_vector = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		coding_info->col_vector[0] = in_col_vector;
		coding_info->total_entry = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		coding_info->total_entry[0] = in_no_of_entries;
		
		coding_info->subimage_range = (SUB_IMAGE *)calloc( coding_info->subimg_nbr, sizeof(SUB_IMAGE));
		coding_info->subimage_range[0].start_row = 0;
		coding_info->subimage_range[0].start_col = 0;
		coding_info->subimage_range[0].end_row = coding_info->total_row-1;
		coding_info->subimage_range[0].end_col = coding_info->total_col-1;
		coding_info->subimage_range[0].bands_num = -1; /*no difference between color bands*/
		break;

	  case 	VQ_15:
		coding_info->color_processed = 0;
		coding_info->subimg_nbr = 10;
		coding_info->row_vector = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		coding_info->col_vector = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		coding_info->total_entry = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		for(i=0; i<coding_info->subimg_nbr; i++) {
			coding_info->row_vector[i] = VQ_15_vector_height[i];
			coding_info->col_vector[i] = VQ_15_vector_width[i];
	  		coding_info->total_entry[i] = VQ_15_vector_entries[i];
		}

		coding_info->subimage_range = (SUB_IMAGE *)calloc( coding_info->subimg_nbr, sizeof(SUB_IMAGE));
		r_end =coding_info->total_row-1;
		c_end =coding_info->total_col-1;
		for ( i=coding_info->subimg_nbr-1; i>=1; i=i-3)
		 {	coding_info->subimage_range[i].start_row = (r_end+1)/2;
		 	coding_info->subimage_range[i].start_col = (c_end+1)/2;
		 	coding_info->subimage_range[i].end_row = r_end;
		 	coding_info->subimage_range[i].end_col = c_end;
			coding_info->subimage_range[i].bands_num = -1; /*no difference between color bands*/
		 	
		 	coding_info->subimage_range[i-1].start_row = (r_end+1)/2;
		 	coding_info->subimage_range[i-1].start_col = 0;
		 	coding_info->subimage_range[i-1].end_row = r_end;
		 	coding_info->subimage_range[i-1].end_col = (c_end+1)/2-1;
			coding_info->subimage_range[i-1].bands_num = -1; /*no difference between color bands*/
		 	
		 	coding_info->subimage_range[i-2].start_row = 0;
		 	coding_info->subimage_range[i-2].start_col = (c_end+1)/2;
		 	coding_info->subimage_range[i-2].end_row = (r_end+1)/2-1;
		 	coding_info->subimage_range[i-2].end_col = c_end;
			coding_info->subimage_range[i-2].bands_num = -1; /*no difference between color bands*/
		 	
		 	r_end = (r_end+1)/2-1;
		 	c_end = (c_end+1)/2-1;
		 }
		coding_info->subimage_range[0].start_row = 0;
		coding_info->subimage_range[0].start_col = 0;
		coding_info->subimage_range[0].end_row = coding_info->subimage_range[2].start_row-1;
		coding_info->subimage_range[0].end_col = coding_info->subimage_range[1].start_col-1;
		coding_info->subimage_range[0].bands_num = -1; /*no difference between color bands*/
		break;
		
	  case	VQ_PCT_15:
		coding_info->color_processed = 1;
		coding_info->subimg_nbr = 30;
		coding_info->row_vector = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		coding_info->col_vector = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		coding_info->total_entry = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		for(i=0; i<coding_info->subimg_nbr; i++) {
			coding_info->row_vector[i] = VQ_PCT_15_vector_height[i];
			coding_info->col_vector[i] = VQ_PCT_15_vector_width[i];
	  		coding_info->total_entry[i] = VQ_PCT_15_vector_entries[i];
		}

		coding_info->subimage_range = (SUB_IMAGE *)calloc( coding_info->subimg_nbr, sizeof(SUB_IMAGE));
		for ( j=0; j<=20; j=j+10)
		{
		 r_end =coding_info->total_row-1;
		 c_end =coding_info->total_col-1;
		 for ( i=coding_info->subimg_nbr/coding_info->color_band-1; i>=1; i=i-3)
		 {	coding_info->subimage_range[i+j].start_row = (r_end+1)/2;
		 	coding_info->subimage_range[i+j].start_col = (c_end+1)/2;
		 	coding_info->subimage_range[i+j].end_row = r_end;
		 	coding_info->subimage_range[i+j].end_col = c_end;
			coding_info->subimage_range[i+j].bands_num = j/10;
		 	
		 	coding_info->subimage_range[i-1+j].start_row = (r_end+1)/2;
		 	coding_info->subimage_range[i-1+j].start_col = 0;
		 	coding_info->subimage_range[i-1+j].end_row = r_end;
		 	coding_info->subimage_range[i-1+j].end_col = (c_end+1)/2-1;
			coding_info->subimage_range[i-1+j].bands_num = j/10;
		 	
		 	coding_info->subimage_range[i-2+j].start_row = 0;
		 	coding_info->subimage_range[i-2+j].start_col = (c_end+1)/2;
		 	coding_info->subimage_range[i-2+j].end_row = (r_end+1)/2-1;
		 	coding_info->subimage_range[i-2+j].end_col = c_end;
		 	coding_info->subimage_range[i-2+j].bands_num = j/10;
		 	
		 	r_end = (r_end+1)/2-1;
		 	c_end = (c_end+1)/2-1;
		 }
		 coding_info->subimage_range[0+j].start_row = 0;
		 coding_info->subimage_range[0+j].start_col = 0;
		 coding_info->subimage_range[0+j].end_row = coding_info->subimage_range[2+j].start_row-1;
		 coding_info->subimage_range[0+j].end_col = coding_info->subimage_range[1+j].start_col-1;
	  	 coding_info->subimage_range[0+j].bands_num = j/10;
	  	}
/*	fprintf(stderr,"xform=VQ_PCT_15\n");*/
		break;

	  case 	VQ_30:
		coding_info->color_processed = 0;
		coding_info->subimg_nbr = 10;
		coding_info->row_vector = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		coding_info->total_entry = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		coding_info->col_vector = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		for(i=0; i<coding_info->subimg_nbr; i++) {
			coding_info->row_vector[i] = VQ_30_vector_height[i];
			coding_info->col_vector[i] = VQ_30_vector_width[i];
	  		coding_info->total_entry[i]= VQ_30_vector_entries[i];
		}

		coding_info->subimage_range = (SUB_IMAGE *)calloc( coding_info->subimg_nbr, sizeof(SUB_IMAGE));
		r_end =coding_info->total_row-1;
		c_end =coding_info->total_col-1;
		for ( i=coding_info->subimg_nbr-1; i>=1; i=i-3)
		 {	coding_info->subimage_range[i].start_row = (r_end+1)/2;
		 	coding_info->subimage_range[i].start_col = (c_end+1)/2;
		 	coding_info->subimage_range[i].end_row = r_end;
		 	coding_info->subimage_range[i].end_col = c_end;
			coding_info->subimage_range[i].bands_num = -1; /*no difference between color bands*/
		 	
		 	coding_info->subimage_range[i-1].start_row = (r_end+1)/2;
		 	coding_info->subimage_range[i-1].start_col = 0;
		 	coding_info->subimage_range[i-1].end_row = r_end;
		 	coding_info->subimage_range[i-1].end_col = (c_end+1)/2-1;
			coding_info->subimage_range[i-1].bands_num = -1; /*no difference between color bands*/
		 	
		 	coding_info->subimage_range[i-2].start_row = 0;
		 	coding_info->subimage_range[i-2].start_col = (c_end+1)/2;
		 	coding_info->subimage_range[i-2].end_row = (r_end+1)/2-1;
		 	coding_info->subimage_range[i-2].end_col = c_end;
			coding_info->subimage_range[i-2].bands_num = -1; /*no difference between color bands*/
		 	
		 	r_end = (r_end+1)/2-1;
		 	c_end = (c_end+1)/2-1;
		 }
		coding_info->subimage_range[0].start_row = 0;
		coding_info->subimage_range[0].start_col = 0;
		coding_info->subimage_range[0].end_row = coding_info->subimage_range[2].start_row-1;
		coding_info->subimage_range[0].end_col = coding_info->subimage_range[1].start_col-1;
		coding_info->subimage_range[0].bands_num = -1; /*no difference between color bands*/
/*	fprintf(stderr,"xform=VQ_30 \n");*/
		break;
		
	  case	VQ_PCT_30:
		coding_info->color_processed = 1;
		coding_info->subimg_nbr = 30;
		coding_info->row_vector = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		coding_info->col_vector = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		coding_info->total_entry = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		for(i=0; i<coding_info->subimg_nbr; i++) {
			coding_info->row_vector[i] = VQ_PCT_30_vector_height[i];
			coding_info->col_vector[i] = VQ_PCT_30_vector_width[i];
	  		coding_info->total_entry[i] = VQ_PCT_30_vector_entries[i];
		}

		coding_info->subimage_range = (SUB_IMAGE *)calloc( coding_info->subimg_nbr, sizeof(SUB_IMAGE));
		for ( j=0; j<=20; j=j+10)
		{
		 r_end =coding_info->total_row-1;
		 c_end =coding_info->total_col-1;
		 for ( i=coding_info->subimg_nbr/coding_info->color_band-1; i>=1; i=i-3)
		 {	coding_info->subimage_range[i+j].start_row = (r_end+1)/2;
		 	coding_info->subimage_range[i+j].start_col = (c_end+1)/2;
		 	coding_info->subimage_range[i+j].end_row = r_end;
		 	coding_info->subimage_range[i+j].end_col = c_end;
			coding_info->subimage_range[i+j].bands_num = j/10;
		 	
		 	coding_info->subimage_range[i-1+j].start_row = (r_end+1)/2;
		 	coding_info->subimage_range[i-1+j].start_col = 0;
		 	coding_info->subimage_range[i-1+j].end_row = r_end;
		 	coding_info->subimage_range[i-1+j].end_col = (c_end+1)/2-1;
			coding_info->subimage_range[i-1+j].bands_num = j/10;
		 	
		 	coding_info->subimage_range[i-2+j].start_row = 0;
		 	coding_info->subimage_range[i-2+j].start_col = (c_end+1)/2;
		 	coding_info->subimage_range[i-2+j].end_row = (r_end+1)/2-1;
		 	coding_info->subimage_range[i-2+j].end_col = c_end;
		 	coding_info->subimage_range[i-2+j].bands_num = j/10;
		 	
		 	r_end = (r_end+1)/2-1;
		 	c_end = (c_end+1)/2-1;
		 }
		 coding_info->subimage_range[0+j].start_row = 0;
		 coding_info->subimage_range[0+j].start_col = 0;
		 coding_info->subimage_range[0+j].end_row = coding_info->subimage_range[2+j].start_row-1;
		 coding_info->subimage_range[0+j].end_col = coding_info->subimage_range[1+j].start_col-1;
	  	 coding_info->subimage_range[0+j].bands_num = j/10;
	  	}
/*	fprintf(stderr,"xform=%dVQ_PCT_30:\n", xform);*/
		break;

	  case 	VQ_55:
		coding_info->color_processed = 0;
		coding_info->subimg_nbr = 10;
		coding_info->row_vector = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		coding_info->col_vector = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		coding_info->total_entry = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		for(i=0; i<coding_info->subimg_nbr; i++) {
			coding_info->row_vector[i] = VQ_55_vector_height[i];
			coding_info->col_vector[i] = VQ_55_vector_width[i];
	  		coding_info->total_entry[i] = VQ_55_vector_entries[i];
		}

		coding_info->subimage_range = (SUB_IMAGE *)calloc( coding_info->subimg_nbr, sizeof(SUB_IMAGE));
		r_end =coding_info->total_row-1;
		c_end =coding_info->total_col-1;
		for ( i=coding_info->subimg_nbr-1; i>=1; i=i-3)
		 {	coding_info->subimage_range[i].start_row = (r_end+1)/2;
		 	coding_info->subimage_range[i].start_col = (c_end+1)/2;
		 	coding_info->subimage_range[i].end_row = r_end;
		 	coding_info->subimage_range[i].end_col = c_end;
			coding_info->subimage_range[i].bands_num = -1; /*no difference between color bands*/
		 	
		 	coding_info->subimage_range[i-1].start_row = (r_end+1)/2;
		 	coding_info->subimage_range[i-1].start_col = 0;
		 	coding_info->subimage_range[i-1].end_row = r_end;
		 	coding_info->subimage_range[i-1].end_col = (c_end+1)/2-1;
			coding_info->subimage_range[i-1].bands_num = -1; /*no difference between color bands*/
		 	
		 	coding_info->subimage_range[i-2].start_row = 0;
		 	coding_info->subimage_range[i-2].start_col = (c_end+1)/2;
		 	coding_info->subimage_range[i-2].end_row = (r_end+1)/2-1;
		 	coding_info->subimage_range[i-2].end_col = c_end;
			coding_info->subimage_range[i-2].bands_num = -1; /*no difference between color bands*/
		 	
		 	r_end = (r_end+1)/2-1;
		 	c_end = (c_end+1)/2-1;
		 }
		coding_info->subimage_range[0].start_row = 0;
		coding_info->subimage_range[0].start_col = 0;
		coding_info->subimage_range[0].end_row = coding_info->subimage_range[2].start_row-1;
		coding_info->subimage_range[0].end_col = coding_info->subimage_range[1].start_col-1;
		coding_info->subimage_range[0].bands_num = -1; /*no difference between color bands*/
/*	fprintf(stderr,"xform=%dVQ_55:\n", xform);*/
		break;
		
	  case	VQ_PCT_55:
		coding_info->color_processed = 1;
		coding_info->subimg_nbr = 30;
		coding_info->row_vector = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		coding_info->col_vector = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		coding_info->total_entry = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		for(i=0; i<coding_info->subimg_nbr; i++) {
			coding_info->row_vector[i] = VQ_PCT_55_vector_height[i];
			coding_info->col_vector[i] = VQ_PCT_55_vector_width[i];
	  		coding_info->total_entry[i] = VQ_PCT_55_vector_entries[i];
		}

		coding_info->subimage_range = (SUB_IMAGE *)calloc( coding_info->subimg_nbr, sizeof(SUB_IMAGE));
		for ( j=0; j<=20; j=j+10)
		{
		 r_end =coding_info->total_row-1;
		 c_end =coding_info->total_col-1;
		 for ( i=coding_info->subimg_nbr/coding_info->color_band-1; i>=1; i=i-3)
		 {	coding_info->subimage_range[i+j].start_row = (r_end+1)/2;
		 	coding_info->subimage_range[i+j].start_col = (c_end+1)/2;
		 	coding_info->subimage_range[i+j].end_row = r_end;
		 	coding_info->subimage_range[i+j].end_col = c_end;
			coding_info->subimage_range[i+j].bands_num = j/10;
		 	
		 	coding_info->subimage_range[i-1+j].start_row = (r_end+1)/2;
		 	coding_info->subimage_range[i-1+j].start_col = 0;
		 	coding_info->subimage_range[i-1+j].end_row = r_end;
		 	coding_info->subimage_range[i-1+j].end_col = (c_end+1)/2-1;
			coding_info->subimage_range[i-1+j].bands_num = j/10;
		 	
		 	coding_info->subimage_range[i-2+j].start_row = 0;
		 	coding_info->subimage_range[i-2+j].start_col = (c_end+1)/2;
		 	coding_info->subimage_range[i-2+j].end_row = (r_end+1)/2-1;
		 	coding_info->subimage_range[i-2+j].end_col = c_end;
		 	coding_info->subimage_range[i-2+j].bands_num = j/10;
		 	
		 	r_end = (r_end+1)/2-1;
		 	c_end = (c_end+1)/2-1;
		 }
		 coding_info->subimage_range[0+j].start_row = 0;
		 coding_info->subimage_range[0+j].start_col = 0;
		 coding_info->subimage_range[0+j].end_row = coding_info->subimage_range[2+j].start_row-1;
		 coding_info->subimage_range[0+j].end_col = coding_info->subimage_range[1+j].start_col-1;
	  	 coding_info->subimage_range[0+j].bands_num = j/10;
	  	}
/*	fprintf(stderr,"xform=%dVQ_PCT_55:\n", xform);*/
		break;

	  case 	VQ_80:
		coding_info->color_processed = 0;
		coding_info->subimg_nbr = 10;
		coding_info->row_vector = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		coding_info->col_vector = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		coding_info->total_entry = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		for(i=0; i<coding_info->subimg_nbr; i++) {
			coding_info->row_vector[i] = VQ_80_vector_height[i];
			coding_info->col_vector[i] = VQ_80_vector_width[i];
	  		coding_info->total_entry[i] = VQ_80_vector_entries[i];
		}

		coding_info->subimage_range = (SUB_IMAGE *)calloc( coding_info->subimg_nbr, sizeof(SUB_IMAGE));
		r_end =coding_info->total_row-1;
		c_end =coding_info->total_col-1;
		for ( i=coding_info->subimg_nbr-1; i>=1; i=i-3)
		 {	coding_info->subimage_range[i].start_row = (r_end+1)/2;
		 	coding_info->subimage_range[i].start_col = (c_end+1)/2;
		 	coding_info->subimage_range[i].end_row = r_end;
		 	coding_info->subimage_range[i].end_col = c_end;
			coding_info->subimage_range[i].bands_num = -1; /*no difference between color bands*/
		 	
		 	coding_info->subimage_range[i-1].start_row = (r_end+1)/2;
		 	coding_info->subimage_range[i-1].start_col = 0;
		 	coding_info->subimage_range[i-1].end_row = r_end;
		 	coding_info->subimage_range[i-1].end_col = (c_end+1)/2-1;
			coding_info->subimage_range[i-1].bands_num = -1; /*no difference between color bands*/
		 	
		 	coding_info->subimage_range[i-2].start_row = 0;
		 	coding_info->subimage_range[i-2].start_col = (c_end+1)/2;
		 	coding_info->subimage_range[i-2].end_row = (r_end+1)/2-1;
		 	coding_info->subimage_range[i-2].end_col = c_end;
			coding_info->subimage_range[i-2].bands_num = -1; /*no difference between color bands*/
		 	
		 	r_end = (r_end+1)/2-1;
		 	c_end = (c_end+1)/2-1;
		 }
		coding_info->subimage_range[0].start_row = 0;
		coding_info->subimage_range[0].start_col = 0;
		coding_info->subimage_range[0].end_row = coding_info->subimage_range[2].start_row-1;
		coding_info->subimage_range[0].end_col = coding_info->subimage_range[1].start_col-1;
		coding_info->subimage_range[0].bands_num = -1; /*no difference between color bands*/
/*	fprintf(stderr,"xform=%dVQ_80:\n", xform);*/
		break;
		
	  case	VQ_PCT_80:
		coding_info->color_processed = 1;
		coding_info->subimg_nbr = 30;
		coding_info->row_vector = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		coding_info->col_vector = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		coding_info->total_entry = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		for(i=0; i<coding_info->subimg_nbr; i++) {
			coding_info->row_vector[i] = VQ_PCT_80_vector_height[i];
			coding_info->col_vector[i] = VQ_PCT_80_vector_width[i];
	  		coding_info->total_entry[i] = VQ_PCT_80_vector_entries[i];
		}

		coding_info->subimage_range = (SUB_IMAGE *)calloc( coding_info->subimg_nbr, sizeof(SUB_IMAGE));
		for ( j=0; j<=20; j=j+10)
		{
		 r_end =coding_info->total_row-1;
		 c_end =coding_info->total_col-1;
		 for ( i=coding_info->subimg_nbr/coding_info->color_band-1; i>=1; i=i-3)
		 {	coding_info->subimage_range[i+j].start_row = (r_end+1)/2;
		 	coding_info->subimage_range[i+j].start_col = (c_end+1)/2;
		 	coding_info->subimage_range[i+j].end_row = r_end;
		 	coding_info->subimage_range[i+j].end_col = c_end;
			coding_info->subimage_range[i+j].bands_num = j/10;
		 	
		 	coding_info->subimage_range[i-1+j].start_row = (r_end+1)/2;
		 	coding_info->subimage_range[i-1+j].start_col = 0;
		 	coding_info->subimage_range[i-1+j].end_row = r_end;
		 	coding_info->subimage_range[i-1+j].end_col = (c_end+1)/2-1;
			coding_info->subimage_range[i-1+j].bands_num = j/10;
		 	
		 	coding_info->subimage_range[i-2+j].start_row = 0;
		 	coding_info->subimage_range[i-2+j].start_col = (c_end+1)/2;
		 	coding_info->subimage_range[i-2+j].end_row = (r_end+1)/2-1;
		 	coding_info->subimage_range[i-2+j].end_col = c_end;
		 	coding_info->subimage_range[i-2+j].bands_num = j/10;
		 	
		 	r_end = (r_end+1)/2-1;
		 	c_end = (c_end+1)/2-1;
		 }
		 coding_info->subimage_range[0+j].start_row = 0;
		 coding_info->subimage_range[0+j].start_col = 0;
		 coding_info->subimage_range[0+j].end_row = coding_info->subimage_range[2+j].start_row-1;
		 coding_info->subimage_range[0+j].end_col = coding_info->subimage_range[1+j].start_col-1;
	  	 coding_info->subimage_range[0+j].bands_num = j/10;
	  	}
/*	fprintf(stderr,"xform=%dVQ_PCT_80:\n", xform);*/
	  	break;

	  case 	VQ_set:
	  
	{ /* begin reading from file*/
	FILE *file;
	int 	i;
	char	read_in[5];
	file = fopen("xvq_set", "rb");	
		for (i=0; i<=9; i++)
		{
		fscanf(file, "%s", read_in);
		VQ_set_vector_height[i] =atoi(read_in);
		fscanf(file, "%s", read_in);
		VQ_set_vector_width[i] =atoi(read_in);
		fscanf(file, "%s", read_in);
		VQ_set_vector_entries[i] =atoi(read_in);
/**/		fprintf(stdout, "height=%d\t width=%d\tentry=%d\n",VQ_set_vector_height[i], VQ_set_vector_width[i],VQ_set_vector_entries[i]);
		}
	fclose(file);
	}/*end of read from file*/
		coding_info->color_processed = 0;
		coding_info->subimg_nbr = 10;
		coding_info->row_vector = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		coding_info->col_vector = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		coding_info->total_entry = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		for(i=0; i<coding_info->subimg_nbr; i++) {
			coding_info->row_vector[i] = VQ_set_vector_height[i];
			coding_info->col_vector[i] = VQ_set_vector_width[i];
	  		coding_info->total_entry[i] = VQ_set_vector_entries[i];
		}

		coding_info->subimage_range = (SUB_IMAGE *)calloc( coding_info->subimg_nbr, sizeof(SUB_IMAGE));
		r_end =coding_info->total_row-1;
		c_end =coding_info->total_col-1;
		for ( i=coding_info->subimg_nbr-1; i>=1; i=i-3)
		 {	coding_info->subimage_range[i].start_row = (r_end+1)/2;
		 	coding_info->subimage_range[i].start_col = (c_end+1)/2;
		 	coding_info->subimage_range[i].end_row = r_end;
		 	coding_info->subimage_range[i].end_col = c_end;
			coding_info->subimage_range[i].bands_num = -1; /*no difference between color bands*/
		 	
		 	coding_info->subimage_range[i-1].start_row = (r_end+1)/2;
		 	coding_info->subimage_range[i-1].start_col = 0;
		 	coding_info->subimage_range[i-1].end_row = r_end;
		 	coding_info->subimage_range[i-1].end_col = (c_end+1)/2-1;
			coding_info->subimage_range[i-1].bands_num = -1; /*no difference between color bands*/
		 	
		 	coding_info->subimage_range[i-2].start_row = 0;
		 	coding_info->subimage_range[i-2].start_col = (c_end+1)/2;
		 	coding_info->subimage_range[i-2].end_row = (r_end+1)/2-1;
		 	coding_info->subimage_range[i-2].end_col = c_end;
			coding_info->subimage_range[i-2].bands_num = -1; /*no difference between color bands*/
		 	
		 	r_end = (r_end+1)/2-1;
		 	c_end = (c_end+1)/2-1;
		 }
		coding_info->subimage_range[0].start_row = 0;
		coding_info->subimage_range[0].start_col = 0;
		coding_info->subimage_range[0].end_row = coding_info->subimage_range[2].start_row-1;
		coding_info->subimage_range[0].end_col = coding_info->subimage_range[1].start_col-1;
		coding_info->subimage_range[0].bands_num = -1; /*no difference between color bands*/
/*	fprintf(stderr,"xform=VQ_set \n");*/
		break;
		
	  case	VQ_PCT_set:
	  
	{ /*begin reading file */
	FILE *file;
	int 	i;
	char	read_in[5];
	file = fopen("xvq_set", "rb");	
		for (i=0; i<=9; i++)
		{
		fscanf(file, "%s", read_in);
		VQ_PCT_set_vector_height[i] =atoi(read_in);
		fscanf(file, "%s", read_in);
		VQ_PCT_set_vector_height[10+i] =atoi(read_in);
		fscanf(file, "%s", read_in);
		VQ_PCT_set_vector_height[20+i] =atoi(read_in);
		fscanf(file, "%s", read_in);
		VQ_PCT_set_vector_width[i] =atoi(read_in);
		fscanf(file, "%s", read_in);
		VQ_PCT_set_vector_width[10+i] =atoi(read_in);
		fscanf(file, "%s", read_in);
		VQ_PCT_set_vector_width[20+i] =atoi(read_in);
		fscanf(file, "%s", read_in);
		VQ_PCT_set_vector_entries[i] =atoi(read_in);
		fscanf(file, "%s", read_in);
		VQ_PCT_set_vector_entries[10+i] =atoi(read_in);
		fscanf(file, "%s", read_in);
		VQ_PCT_set_vector_entries[20+i] =atoi(read_in);
/**/		fprintf(stdout, "height= R:%d G:%d B:%d\t width= R:%d G:%d B:%d\tentry=R:%d G:%d B:%d\n",
			VQ_PCT_set_vector_height[i], 
			VQ_PCT_set_vector_height[10+i], 
			VQ_PCT_set_vector_height[20+i], 
			VQ_PCT_set_vector_width[i],
			VQ_PCT_set_vector_width[10+i],
			VQ_PCT_set_vector_width[20+i],
			VQ_PCT_set_vector_entries[i],
			VQ_PCT_set_vector_entries[10+i],
			VQ_PCT_set_vector_entries[20+i]
			);
		
		}
	fclose(file);
	}/*end of reading file*/
		coding_info->color_processed = 1;
		coding_info->subimg_nbr = 30;
		coding_info->row_vector = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		coding_info->col_vector = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		coding_info->total_entry = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
		for(i=0; i<coding_info->subimg_nbr; i++) {
			coding_info->row_vector[i] = VQ_PCT_set_vector_height[i];
			coding_info->col_vector[i] = VQ_PCT_set_vector_width[i];
	  		coding_info->total_entry[i] = VQ_PCT_set_vector_entries[i];
		}

		coding_info->subimage_range = (SUB_IMAGE *)calloc( coding_info->subimg_nbr, sizeof(SUB_IMAGE));
		for ( j=0; j<=20; j=j+10)
		{
		 r_end =coding_info->total_row-1;
		 c_end =coding_info->total_col-1;
		 for ( i=coding_info->subimg_nbr/coding_info->color_band-1; i>=1; i=i-3)
		 {	coding_info->subimage_range[i+j].start_row = (r_end+1)/2;
		 	coding_info->subimage_range[i+j].start_col = (c_end+1)/2;
		 	coding_info->subimage_range[i+j].end_row = r_end;
		 	coding_info->subimage_range[i+j].end_col = c_end;
			coding_info->subimage_range[i+j].bands_num = j/10;
		 	
		 	coding_info->subimage_range[i-1+j].start_row = (r_end+1)/2;
		 	coding_info->subimage_range[i-1+j].start_col = 0;
		 	coding_info->subimage_range[i-1+j].end_row = r_end;
		 	coding_info->subimage_range[i-1+j].end_col = (c_end+1)/2-1;
			coding_info->subimage_range[i-1+j].bands_num = j/10;
		 	
		 	coding_info->subimage_range[i-2+j].start_row = 0;
		 	coding_info->subimage_range[i-2+j].start_col = (c_end+1)/2;
		 	coding_info->subimage_range[i-2+j].end_row = (r_end+1)/2-1;
		 	coding_info->subimage_range[i-2+j].end_col = c_end;
		 	coding_info->subimage_range[i-2+j].bands_num = j/10;
		 	
		 	r_end = (r_end+1)/2-1;
		 	c_end = (c_end+1)/2-1;
		 }
		 coding_info->subimage_range[0+j].start_row = 0;
		 coding_info->subimage_range[0+j].start_col = 0;
		 coding_info->subimage_range[0+j].end_row = coding_info->subimage_range[2+j].start_row-1;
		 coding_info->subimage_range[0+j].end_col = coding_info->subimage_range[1+j].start_col-1;
	  	 coding_info->subimage_range[0+j].bands_num = j/10;
	  	}
/*	fprintf(stderr,"xform=%dVQ_PCT_30:\n", xform);*/
		break;

	  default:
		fprintf(stderr,"Unrecognized image data type?\n");
		return 0;
	}/********end of switch*******/
	/******* counting and allocating:
		coding_info->total_vector
		coding_info->error
		coding_info->coding_result
		coding_info->method
		coding_info->error_threshold
	*****************************************/
	coding_info->error_method = mean_square;
	coding_info->error = (double **)calloc(coding_info->subimg_nbr, sizeof(double*));
	coding_info->coding_result = (int **)calloc(coding_info->subimg_nbr, sizeof(int*));
	coding_info->error_threshold = (float *)calloc(coding_info->subimg_nbr, sizeof(float));
	coding_info->total_vector = (int *)calloc(coding_info->subimg_nbr, sizeof(int));
	
	for(subImg = 0; subImg < coding_info->subimg_nbr; subImg++) 
	       {coding_info->error_threshold[subImg] = in_error_thres;
	   	coding_info->total_vector[subImg] = ceil(((float)(coding_info->subimage_range[subImg].end_row - coding_info->subimage_range[subImg].start_row+1)/(float)coding_info->row_vector[subImg]));
     		coding_info->total_vector[subImg] *= ceil((float)(coding_info->subimage_range[subImg].end_col - coding_info->subimage_range[subImg].start_col+1)/(float)coding_info->col_vector[subImg]);
/*	fprintf(stderr,"begin  count  coding_info->error[subImg]\n");*/
     		if (!coding_info->color_processed)

     		   {	coding_info->error[subImg] = (double *)calloc(coding_info->total_vector[subImg]*coding_info->color_band, sizeof(double));
     			coding_info->coding_result[subImg] = (int *)calloc(coding_info->total_vector[subImg]*coding_info->color_band, sizeof(int));
     		   }
     		else
     		   {	coding_info->error[subImg] = (double *)calloc(coding_info->total_vector[subImg], sizeof(double));
     			coding_info->coding_result[subImg] = (int *)calloc(coding_info->total_vector[subImg], sizeof(int));
     		   }
	       }	
	       
	return 1;
	
     }/******end of get_vq_info() ************/  
/********************************************************************************************
********************************************************************************************/
      
/**************print_vq_info(coding_info)**************/
void   print_vq_info(VQ_INFO *coding_info)     
      {	int	i;
        fprintf(stderr,"\nxfom:%d   color_processed:%d  codebookinfile:%d  CVIP_TYPE:%d  color_band:%d", 
      		coding_info->xform, /*coding_info->temp_file,*/ coding_info->color_processed, coding_info->cdbook_in_file,
      		coding_info->data_type, coding_info->color_band);
      	fprintf(stderr,"\nsubimg_nbr:%d  tatal_row:%d  total_col:%d  fixedbook:%d  erro_method:%d",
      		coding_info->subimg_nbr, coding_info->total_row, coding_info->total_col, coding_info->fixed_cdbook, coding_info->error_method);
      	for ( i =0; i< coding_info->subimg_nbr; i++)
      	{	fprintf(stderr,"\nsunimg_nbr:%d\nstar_r:%d  start_c:%d  end_r:%d  end_c:%d  bands:%d", 
      			i, coding_info->subimage_range[i].start_row, coding_info->subimage_range[i].start_col,
      			coding_info->subimage_range[i].end_row,coding_info->subimage_range[i].end_col, coding_info->subimage_range[i].bands_num);
      		fprintf(stderr,"\nrow_vector:%d  col_vector:%d  ", 
      			coding_info->row_vector[i], coding_info->col_vector[i]/*, coding_info->error_threshold[i]*/);
      		fprintf(stderr,"\n");	
      	}/*end of loop*/
      }/*end of print_vq_info(coding_info)*/
      
      

/*********************************************************************************
**  	Function VQ_read_decompression() is called by  function xdr_compress()       **
**      in file "cviptovip.c". 						        **
**      This function is used for reading VQ_compressed image files with 	**
**	VIP structure from disk.  						**
**      Because VQ_compressed image files is saved as VIP structure, now 	**
**	the pointer 'fp' points to the raw data in VIP structure. in fact,	**
** 	The raw data in VIP structure is the original VQ_compressed image	**
**	files.									**
********************************************************************************/
Image *VQ_read_decompression(FILE *fp) 
{
   HISTORY stuff;
   Image *temp_image;
   int data;
   int block_size;
   
   FILE *fptr;
   char	*filename;
   
   #ifndef WIN32
     struct passwd *pwentry;
   #endif
   
   filename = (char *)malloc(sizeof(char) * 150);
   
   #ifndef WIN32
     pwentry = getpwuid(getuid()); /*get home directory of the user*/
     strcpy(filename, pwentry->pw_dir);
     strcat(filename, "/vq.cvip_temp/"); 
     //strcat(filename, "temp_file");
   #else
     if(getenv("temp"))
     {
       strcpy(filename, getenv("temp"));
       strcat(filename, "\\vq.cvip_temp");
       //strcat(filename, "\\temp_file");
     }
     else
     {
       strcpy(filename, "\\temp\\vq.cvip_temp");
       //strcat(filename, "\\temp_file");
     }
   #endif
   
   /*error_CVIP("filename = %s", filename);*/ 
 	#ifndef WIN32
		fptr = fopen(filename, "w" );
	#else
		fptr = fopen(filename, "wb" );
	#endif
    
   if(fptr == NULL)
   {
     error_CVIP("VQ_read_decompression", "cannot open new file");
   }

   data = getc(fp);
   while(data != EOF)
   {
     /*error_CVIP("xdr_compress", "putc");*/
     fputc(data, fptr);
     data = getc(fp);
   }
   fclose(fptr);
   if ( (temp_image = (Image *)vq_decompress(filename)) == (Image *) NULL) 
	   {	
	     error_CVIP("VQ decompression fail", " return NULL");
	     return NULL;
	   }
   	
 //  temp_image = remap_Image( temp_image, CVIP_BYTE,0,255);
   /*error_CVIP("VQ decompression", " return temp_image");*/
   return temp_image; 
}

