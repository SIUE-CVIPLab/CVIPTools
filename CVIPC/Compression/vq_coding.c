/****************************************************************
*             File Name: LBG_coding.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Fri Nov 21 15:36:37 CST 1997
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): 
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1996 SIUE - by Scott Umbaugh and .
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
** $Log: vq_coding.c,v $
** Revision 1.17  2001/11/21 01:32:15  ycheng
** fixed the problem of 'datatype double = 0' in function cbk_training_distance
**
** Revision 1.16  2001/04/09 13:08:21  ycheng
** rename 'single' to 'Single' in order not to conflict wiht a C function name.
**
** Revision 1.15  2001/04/04 06:17:27  ycheng
** fixed some bugs.
**
** Revision 1.14  1999/05/30 22:45:57  lguo
** some print out commented out
**
** Revision 1.13  1999/04/20 22:57:29  lguo
** deleted some useless output printing
**
** Revision 1.12  1998/11/25 03:59:55  lguo
**  enough comment before the fuction begins.the version reserves many print out as debugging reference, which will be deleted before freezing. 
**
** Revision 1.10  1998/11/14 07:16:38  lguo
** *** empty log message ***
**
** Revision 1.9  1998/11/14 06:37:59  lguo
** *** empty log message ***
**
** Revision 1.8  1998/11/14 05:59:54  lguo
** when a color img is inputed, diferent color bands will be counted as different sub_image. bands_num is added to sub_img_range in .h file, and some parts of compression, encode_image ReconstructSubima
** are changed
**
** Revision 1.7  1998/10/27 20:51:39  lguo
** *** empty log message ***
**
** Revision 1.6  1998/10/24 09:05:48  lguo
** fix bugs. now it works firmly
**
** Revision 1.5  1998/05/30 01:44:42  wzheng
** subimages work for all functions
** subimage num < codebooks stored in codebook file -- OK
**
** Revision 1.4  1998/05/27 23:12:25  wzheng
** fix the error of pass cdbook pointer while calling ReconstructSubImg
**
** Revision 1.3  1998/05/19 01:37:12  wzheng
** subimg number save into seperate codebook file
**
** Revision 1.2  1998/04/09 01:02:41  wzheng
** saved compressed data bug:  outImage->image_format = VQ;
** image format conversion
**
** Revision 1.1  1998/04/04 21:20:00  wzheng
** Initial revision
**
** Revision 1.23  1998/04/02 00:08:52  wzheng
** all paremeters done
**
** Revision 1.22  1998/04/01 00:55:10  wzheng
** stoped VECTOR_LST->vector_height after last crash
** not crash ... all white or black image return.
**
** Revision 1.20  1998/03/15 19:36:52  wzheng
** simplize the err threshold checking procedures
** fix the bit_used calculation
**
** Revision 1.19  1998/03/13 00:50:20  wzheng
** big prolem on encoding: flow chart mistake
**
** Revision 1.18  1998/03/10 03:30:21  wzheng
** seperate single_vector_checking()
**
** Revision 1.17  1998/03/10 02:28:37  wzheng
** fix "fclose(infile)"
**
** Revision 1.16  1998/03/07 04:13:12  wzheng
** fix free codebook error
**
** Revision 1.15  1998/03/07 03:24:10  wzheng
** fix the mis-seting on length of coding_result, error, error_thershold
**
** Revision 1.14  1998/03/04 04:05:07  wzheng
** decoding bugs fix
**
** Revision 1.13  1998/03/01 20:58:51  wzheng
** one codebook for all mutiple color band in each subimage
**
** Revision 1.11  1998/02/24 18:08:38  wzheng
** change function name from set_coding_info() to initial_info_coding_result()
**
** Revision 1.10  1998/02/24 16:05:06  wzheng
** initial_codebook() prototype change
**
** Revision 1.9  1998/02/23 16:53:42  wzheng
** solve vq_info mis-free right after allocated
**
** Revision 1.8  1998/02/21 04:16:25  wzheng
** temp input setup
** redo no_of_vector calculation
**
** Revision 1.7  1998/02/20 02:58:22  wzheng
** add vq_decompression()
** coding done
**
** Revision 1.6  1998/02/20 00:44:09  wzheng
** seperate setup, compress, compression functions
** VQ_INFO add cdbook_in_file, cdbook_file, fixed_cdbook
**
** Revision 1.5  1998/02/17 00:42:41  wzheng
** seperate LBG_setup() with vq_compress()
**
** Revision 1.4  1998/02/15 22:09:04  wzheng
** add ReconstructSubImg()
**
** Revision 1.3  1998/02/14 04:07:53  wzheng
** third comile
**
** Revision 1.2  1998/02/12 03:04:01  wzheng
** second compile
**
** Revision 1.1  1998/02/04 02:02:56  wzheng
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
#include<vector_quant.h>
/**************************************************************
In this file contains these functions :
	vq_compression (  VQ_INFO  *vq_info, VECTOR_LST   **cdbook)
	encode_subimage()
	single_vector_checking ()
	average_mean_square()
	cbk_training_distance()
  	ReconstructSubImg ()
	vq_decompression (VQ_INFO *vq_info, FILE *file, FILE *file_result )
	get_BitsInInt(void)
**************************************************************/


/***********************************************************************************************
  vq_compression (  VQ_INFO  *vq_info, VECTOR_LST   **cdbook)
  	this function is called by vq_compress. it follow this flow chart:
  	for each subimg:
  	   {	1, calling allocate_vector_sets() to allocate memoryand fill data to 
  		cdbook and traningset
  		2, calling initial_codebook() to use image to fill in training set
  		3, use training set to initialize the cdbook, or read cdbook information from file
  		4, encode_subimage(), the encoding result is saved in vq_info->coding_result
  		5, free the cdbook structure
  	    }
  	if u want to make changes in this part, make sure:
  		1, read from cd_book_file with correft format
  		2, make sure this part deal with those subimg with 0 vector_entries well
***********************************************************************************************/

int vq_compression (  VQ_INFO  *vq_info, VECTOR_LST   **cdbook)
  {
  	
  	VECTOR_LST   *training_set;
  	int          length_vector; 
  	int          bits_used;
  	FILE         *codebook_io=NULL;
  	int          subImg;
	int          temp;


	if (vq_info->fixed_cdbook == 1)
		{
		codebook_io = fopen(vq_info->cdbook_file, "rb");
		fseek(codebook_io,7*sizeof(int) , 0/*SEEK_SET*/);
		}
	
  	for ( subImg = 0; subImg < vq_info->subimg_nbr; subImg++)
    	{
    	 if (vq_info->total_entry[subImg] == 0)/*this frequ band is discarded*/
    	   { vq_info->error[subImg]=NULL;
    	     vq_info->coding_result[subImg]=NULL;
    	     cdbook[subImg] = (VECTOR_LST *)calloc(1, sizeof (VECTOR_LST));
    	     cdbook[subImg]->vector_size=0;
    	     cdbook[subImg]->vector_heigth=0;
    	     cdbook[subImg]->vector=NULL;
    	     cdbook[subImg]->total_entry=0;
		if (vq_info->fixed_cdbook == 1)
		/*in this condition, we should move the pointer in codebook_io with a length of SUB_IMAGE*/
		  {
			fseek(codebook_io,sizeof(SUB_IMAGE)+3*sizeof(int)+sizeof(float) , 1/*SEEK_CUR*/);
		  }
     	     continue;
    	   }
    	 
    	 length_vector = vq_info->row_vector[subImg] * vq_info->col_vector[subImg];
    	  /* allocate space for cdbook, and fill the height&width to each vector */
/*	fprintf(stderr,"begin allocate_vector_sets() for cdbook\n");*/
    	 if (allocate_vector_sets(	&cdbook[subImg],
                              		1, 
                              		(vq_info->total_entry)[subImg],
                              		length_vector,
					(vq_info->row_vector)[subImg],
                              		vq_info->data_type) != 1)
            {	fprintf(stderr, "vq_compresion: allocate_vector_sets for cdbook return error");
      		free_codebooks(cdbook, 1, vq_info->subimg_nbr);
      		return 0;
      	    }
	 /* allocate space for training set  */
/*	fprintf(stderr,"begin allocate_vector_sets() for training set\n");*/
    	switch (vq_info->color_processed)
    	{
    	 case	0: /*using one codebook for all the 3 color bands*/
    	 allocate_vector_sets(	&training_set, 
                              	1,
                              	vq_info->total_vector[subImg]*vq_info->color_band,
                              	length_vector,
			      	(vq_info->row_vector)[subImg],
                              	vq_info->data_type); 
         break;
    	 case	1: /*using one codebook for all the 3 color bands*/
    	 allocate_vector_sets(	&training_set, 
                              	1,
                              	vq_info->total_vector[subImg],
                              	length_vector,
			      	(vq_info->row_vector)[subImg],
                              	vq_info->data_type);
	 break;
	 default:
         { 	fprintf(stderr, "Whether color_processed is not idicated");
      		free_codebooks(cdbook, 1, vq_info->subimg_nbr); free_vector_sets(&training_set, 1);
      		return 0;
         }
        } 
	/* begin to use image data to fill training set*/
/*	fprintf(stderr,"begin initial_training_set\n");*/
     	if (initial_training_set(vq_info->inputImage, training_set, vq_info->row_vector[subImg], vq_info->col_vector[subImg], vq_info->subimage_range[subImg], vq_info->color_processed) != 1)
      	{
      	 free_codebooks(cdbook, 1, vq_info->subimg_nbr);
      	 free_vector_sets(&training_set, 1);
      	 return 0;
      	}

/*	fprintf(stderr,"begin initial_codebook, or ReadCodebook\n");*/
   	if (vq_info->fixed_cdbook == 0)
	{
     	 if (initial_codebook(cdbook[subImg], training_set, vq_info->data_type)!= 1)
       		{ 	fprintf(stderr, "vq_compresion: initial_codebook return error");
       			free_codebooks(cdbook, 1, vq_info->subimg_nbr);
       			free_vector_sets(&training_set, 1);
       			return 0;
       		}
     	}
   	else{	
		 if ((ReadCodebook(codebook_io, cdbook[subImg], vq_info->data_type)) == 0)
		   {	fprintf(stderr, "vq_compression: ReadCodebook return error");
       			free_codebooks(cdbook, 1, vq_info->subimg_nbr);
       			free_vector_sets(&training_set, 1);
       			return 0;
		   }
	    }

/*	fprintf(stderr,"begin encode_subimage(subImg, cdbook[subImg], training_set, vq_info)\n");*/
   	if (encode_subimage(subImg, cdbook[subImg], training_set, vq_info) != 1)
      	 {
      	 fprintf(stderr, "vq_compresion: encode_subimage return error");
      	 free_codebooks(cdbook, 1, vq_info->subimg_nbr);
      	 free_vector_sets(&training_set, 1);
      	 return 0;
      	 }
	
   	/* free memory at end of subImg encoding */
   	free_vector_sets(&training_set, 1);

   	} /* end of subimg loop*/
   	if (codebook_io!=NULL)
   		fclose(codebook_io);
//   	free(codebook_io);
   	return 1;
   }/*end of vq_compression() */
/*****************encode_subimage*************
	this function encode the image and fill the vq_info->coding_result
***************************************************/	
int encode_subimage (
        int        subimg_nbr,
       	VECTOR_LST *cdbook,
	const VECTOR_LST *training_set, 
      	VQ_INFO *coding_info  
        ) 
{
  int		trn_entry,
  		item;		/* indicate each item within a vector */
  double	current_square_error=0;/* the error for each current working index vector */
  double        current_error;
  double        total_pre_error=0;
  double        total_cur_error=0;
  unsigned int  cbk_entry,
                encode_as;      /* the codebook entry corespond with a training set */
  double        *error;
  double        *saved_error;
  unsigned int  *coding_result;
  int           redo_coding;    /* the error cant pass threshold, redo_coding is needed= 1*/
  int           fixed_codebook; 
  int           pass_code_generate;


  pass_code_generate = 0;
  fixed_codebook = coding_info->fixed_cdbook;
	saved_error = (double *)calloc(training_set->total_entry, sizeof(double));

  /* for coding */
  error = coding_info->error[subimg_nbr];
  coding_result = coding_info->coding_result[subimg_nbr];

  /* perform the simple match checking on codebook and training_set */
  if (training_set->vector_size != cdbook->vector_size)
    {	
	fprintf(stderr,"training_set->vector_size != cdbook->vector_size \nsubimg_nbr=%d  training_set->vector_size=%d    cdbook->vector_size=%d\n", 
 		subimg_nbr, training_set->vector_size, cdbook->vector_size);
 	return 0;
    }

      
     /*find the codebook_entry for each training_set_vector*/
       
      initial_info_coding_result(cdbook, training_set, coding_info, subimg_nbr);
      for (trn_entry=0; trn_entry < (training_set->total_entry); trn_entry++) 
          {
	        for (cbk_entry=0; cbk_entry<(cdbook->total_entry); cbk_entry++) 
	          {
	          current_error = cbk_training_distance(cdbook->vector[cbk_entry],
	                                                training_set->vector[trn_entry],
							cdbook->vector_size,
	                                                coding_info->data_type);
	           if (current_error < error[trn_entry])
               	    {
	             	coding_result[trn_entry] = cbk_entry;
               		error[trn_entry] = current_error;
                    }
	          }
	   }

       if (fixed_codebook == 1)
          pass_code_generate = 1;


  error = coding_info->error[subimg_nbr];
  while (pass_code_generate == 0)
    {

      pass_code_generate = 1;

      if (define_codebook(cdbook, training_set, coding_info, subimg_nbr) != 1)
        {
         fprintf(stderr,"encode_subimage: define_codebook return error");
         return 0;
        }

      /*
       * find the codebook_entry for each training_set_vector
       */
      for (trn_entry=0; trn_entry < (training_set->total_entry); trn_entry++) 
				 saved_error[trn_entry] = error[trn_entry];
      initial_info_coding_result(cdbook, training_set, coding_info, subimg_nbr);
      for (trn_entry=0; trn_entry < (training_set->total_entry); trn_entry++) 
          {
	        for (cbk_entry=1; cbk_entry<(cdbook->total_entry); cbk_entry++) 
	          {
	           current_error = cbk_training_distance(cdbook->vector[cbk_entry],
	                                                 training_set->vector[trn_entry],
							 cdbook->vector_size,
	                                                 coding_info->data_type);
	           if (current_error < error[trn_entry])
               		{
	             	 coding_result[trn_entry] = cbk_entry;
               		 error[trn_entry] = current_error;
               		}
	          }
	   }

        /*
         * caculate coding error for each training_set_vector
         * if any one of them cant pass the error_threshold,
         * setup to redefine codebook
         */
	  switch (coding_info->error_method)
	  {
		case (Single):
 		pass_code_generate = single_vector_checking( 	coding_info,
								saved_error,
								subimg_nbr);
           	break;

           case (mean_square):
 		pass_code_generate = average_mean_square( coding_info,
							  saved_error,
							  subimg_nbr);
           	break;
          }
    }
  free(saved_error);

  return 1;
} /*end of encode_subimage() */ 



/****************************************************************************
 single_vector_checking 

****************************************************************************/
/*
* caculate coding error for each training_set_vector
* if any one of them cant pass the error_threshold,
* setup to redefine codebook
*/
int single_vector_checking (
		 VQ_INFO      *coding_info,
		 double       *prev_error,
		 int          subimg_nbr
		 )
  {
	int 	trn_entry;
	double  *current_error;
	float   error_threshold;
	int     pass_code_generate;
	int     total_training_entry;

  	pass_code_generate = 1;
	total_training_entry = coding_info->total_vector[subimg_nbr];
	current_error = coding_info->error[subimg_nbr];
	error_threshold = coding_info->error_threshold[subimg_nbr];
	for(trn_entry=0; trn_entry < total_training_entry; trn_entry++)
	if (fabs(current_error[trn_entry] - prev_error[trn_entry]) > error_threshold)
			{
			pass_code_generate = 0;
			break;
			}

  	return pass_code_generate;
  }/*end of single_vector_checking*/

/****************************************************************************
 average_mean_square 

****************************************************************************/
int average_mean_square(
		 VQ_INFO      *coding_info,
		 double       *prev_error,
		 int          subimg_nbr
			)
    {
	int          trn_entry;
	double       *current_error;
	double       sum_error;
	double       sum_previous_error;
	double       mean_square_error;
	double       prev_mean_square_error;
	float        error_threshold;
	int          pass_code_generate;
	int          total_training_entry;

	pass_code_generate = 1;
	sum_error = sum_previous_error = 0;
	total_training_entry = coding_info->total_vector[subimg_nbr];
	current_error = coding_info->error[subimg_nbr];
	error_threshold = coding_info->error_threshold[subimg_nbr];
	for(trn_entry=0; trn_entry < total_training_entry; trn_entry++)
		{
		sum_error += current_error[trn_entry];
		sum_previous_error += prev_error[trn_entry];
		}

  	mean_square_error = sum_error/total_training_entry;
	prev_mean_square_error = sum_previous_error/total_training_entry;

	if (fabs(mean_square_error - prev_mean_square_error) > error_threshold)
		pass_code_generate = 0;

  	return pass_code_generate;
    }/*end of average_mean_square() */

/****************************************************************************
  cbk_training_distance

****************************************************************************/
double cbk_training_distance (
        void *cbk_vector,
        void *trn_vector,
        int vector_size,
        CVIP_TYPE data_type)
{
   int          item;
   double       distance = 0.0;

   switch(data_type) {
   case CVIP_BYTE:
      for(item=0; item<vector_size; item++) {
        distance += pow((double)(((byte*)trn_vector)[item] - ((byte*)cbk_vector)[item]),2);
      }
      break;
   case CVIP_SHORT:
      for(item=0; item<vector_size; item++) {
        distance += pow((double)(((short*)trn_vector)[item]-((short*)cbk_vector)[item]),2);
      }
      break;
   case CVIP_INTEGER:
      for(item=0; item<vector_size; item++) {
        distance += pow((double)(((int*)trn_vector)[item] - ((int*)cbk_vector)[item]),2);
      }
      break;
   case CVIP_FLOAT:
      for(item=0; item<vector_size; item++) {
        distance += pow((double)(((float*)trn_vector)[item]-((float*)cbk_vector)[item]),2);
      }
      break;
   case CVIP_DOUBLE:
      for(item=0; item<vector_size; item++) {
        distance += pow((((double*)trn_vector)[item] - ((double*)cbk_vector)[item]),2);
      }
      break;
   default:
      fprintf(stderr,"Unrecognized image data type?\n");
      return 0;
   }
   if (distance<0)
   {
     fprintf(stderr,"During caculating cbk_training_distance, distance is found negative.\n");
     distance = 0.0;
   }
   return sqrt(distance);
} /* end of cbk_training_distance() */

/*******************************************************************************
  ReconstructSubImg  in this fuction, if color_preprocessed is treated differently
*******************************************************************************/
static int ReconstructSubImg (
     VQ_INFO     *info,
     VECTOR_LST  *cdbook,
     Image       *cvipImg,
     int         subimg_nbr
     )
  {
  VECTOR_LST   *result_lst;
  unsigned int *vq_code;
  unsigned int cur_vq_code;
  int          row, col, band,
               n_row,
               n_col,
               n_band;
  int          img_start_row,
               img_start_col,
               img_end_row,
               img_end_col;
  int          vector_index;       /* the vector counter when traversing */
  int          coding_index;        /* the coding_result counter when traversing */
  int          vector_col;
  int          vector_row;
  int          img_row;
  int          img_col;
  int          vector_length;
  byte         **image_byte;
  int          **image_int;
  short        **image_short;
  float        **image_float;
  double       **image_double;
/*        fprintf(stderr,"in ReconstructSubImg  subimg_nbr=%d\n", subimg_nbr);*/
 
  /* brief image match checking */
  n_row = getNoOfRows_Image(cvipImg);
  n_col = getNoOfCols_Image(cvipImg);
  n_band = getNoOfBands_Image(cvipImg);
/*        fprintf(stderr,"got n_row ...%d %d %d\n", n_row,n_col, n_band );*/
  if ((info->subimage_range[subimg_nbr]).start_row < 0 ||
      (info->subimage_range[subimg_nbr]).start_col < 0 ||
      (info->subimage_range[subimg_nbr]).end_row >= n_row ||
      (info->subimage_range[subimg_nbr]).end_col >= n_col ||
      info->total_row != n_row ||
      info->total_col != n_col ||
      info->color_band != n_band
     )
    return 0;

  vq_code = info->coding_result[subimg_nbr];
  img_start_row = (info->subimage_range[subimg_nbr]).start_row;
  img_start_col = (info->subimage_range[subimg_nbr]).start_col;
  img_end_row = (info->subimage_range[subimg_nbr]).end_row + 1;
  img_end_col = (info->subimage_range[subimg_nbr]).end_col + 1;
  vector_length = info->row_vector[subimg_nbr] * info->col_vector[subimg_nbr];
  vector_index = 0;
  coding_index = 0;
  cur_vq_code = vq_code[coding_index];
 /*        fprintf(stderr,"in ReconstructSubImg begin to switch\n");*/

  if (info->color_processed==1)
  {
  switch (info->data_type)
    {
    case CVIP_BYTE:
    image_byte = getData_Image(cvipImg, (info->subimage_range[subimg_nbr]).bands_num);
      for(row = img_start_row; row < img_end_row; row += info->row_vector[subimg_nbr])
        for(col = img_start_col; col < img_end_col; col += info->col_vector[subimg_nbr])
          {
          for (vector_row=0; vector_row < info->row_vector[subimg_nbr]; vector_row++)
            {
            img_row = row + vector_row;
            for (vector_col=0; vector_col < info->col_vector[subimg_nbr]; vector_col++)
              {
              img_col = col + vector_col;
              if (img_row < img_end_row && img_col < img_end_col)
                image_byte[img_row][img_col] = ((byte*)(cdbook->vector[cur_vq_code]))[vector_index];
              vector_index++;
              if (vector_index >= vector_length)
                {
                vector_index = 0;
                coding_index++;
                if (coding_index < 
                  ((info->total_vector[subimg_nbr])*(info->color_band)))
                  cur_vq_code = vq_code[coding_index];
                }
              }
            }
          }
    break;

    case CVIP_SHORT:
    image_short = getData_Image(cvipImg, (info->subimage_range[subimg_nbr]).bands_num);
      for(row = img_start_row; row < img_end_row; row += info->row_vector[subimg_nbr])
        for(col = img_start_col; col < img_end_col; col += info->col_vector[subimg_nbr])
          {
          for (vector_row=0; vector_row < info->row_vector[subimg_nbr]; vector_row++)
            {
            img_row = row + vector_row;
            for (vector_col=0; vector_col < info->col_vector[subimg_nbr]; vector_col++)
              {
              img_col = col + vector_col;
              if (img_row < img_end_row && img_col < img_end_col)
                image_short[img_row][img_col] = ((short*)(cdbook->vector[cur_vq_code]))[vector_index];
              vector_index++;
              if (vector_index >= vector_length)
                {
                coding_index++;
                vector_index = 0;
                if (coding_index < 
                  ((info->total_vector[subimg_nbr])*(info->color_band)))
                  cur_vq_code = vq_code[coding_index];
                }
              }
            }
          }
    break;

    case CVIP_INTEGER:
    image_int = getData_Image(cvipImg, (info->subimage_range[subimg_nbr]).bands_num);
      for(row = img_start_row; row < img_end_row; row += info->row_vector[subimg_nbr])
        for(col = img_start_col; col < img_end_col; col += info->col_vector[subimg_nbr])
          {
          for (vector_row=0; vector_row < info->row_vector[subimg_nbr]; vector_row++)
            {
            img_row = row + vector_row;
            for (vector_col=0; vector_col < info->col_vector[subimg_nbr]; vector_col++)
              {
              img_col = col + vector_col;
              if (img_row < img_end_row && img_col < img_end_col)
                image_int[img_row][img_col] = ((int*)(cdbook->vector[cur_vq_code]))[vector_index];
              vector_index++;
              if (vector_index >= vector_length)
                {
                coding_index++;
                vector_index = 0;
                if (coding_index < 
                  ((info->total_vector[subimg_nbr])*(info->color_band)))
                  cur_vq_code = vq_code[coding_index];
                }
              }
            }
          }
    break;

    
    case CVIP_FLOAT:
    image_float = getData_Image(cvipImg, (info->subimage_range[subimg_nbr]).bands_num);
      for(row = img_start_row; row < img_end_row; row += info->row_vector[subimg_nbr])
        for(col = img_start_col; col < img_end_col; col += info->col_vector[subimg_nbr])
          {
          for (vector_row=0; vector_row < info->row_vector[subimg_nbr]; vector_row++)
            {
            img_row = row + vector_row;
            for (vector_col=0; vector_col < info->col_vector[subimg_nbr]; vector_col++)
              {
              img_col = col + vector_col;
              if (img_row < img_end_row && img_col < img_end_col)
                image_float[img_row][img_col] = ((float*)(cdbook->vector[cur_vq_code]))[vector_index];
              vector_index++;
              if (vector_index >= vector_length)
                {
                coding_index++;
                vector_index = 0;
                if (coding_index < 
                  ((info->total_vector[subimg_nbr])*(info->color_band)))
                  cur_vq_code = vq_code[coding_index];
                }
              }
            }
          }
    break;

    case CVIP_DOUBLE:
    image_double = getData_Image(cvipImg, (info->subimage_range[subimg_nbr]).bands_num);
      for(row = img_start_row; row < img_end_row; row += info->row_vector[subimg_nbr])
        for(col = img_start_col; col < img_end_col; col += info->col_vector[subimg_nbr])
          {
          for (vector_row=0; vector_row < info->row_vector[subimg_nbr]; vector_row++)
            {
            img_row = row + vector_row;
            for (vector_col=0; vector_col < info->col_vector[subimg_nbr]; vector_col++)
              {
              img_col = col + vector_col;
              if (img_row < img_end_row && img_col < img_end_col)
                image_double[img_row][img_col] = ((double*)(cdbook->vector[cur_vq_code]))[vector_index];
              vector_index++;
              if (vector_index >= vector_length)
                {
                coding_index++;
                vector_index = 0;
                if (coding_index < 
                  ((info->total_vector[subimg_nbr])*(info->color_band)))
                  cur_vq_code = vq_code[coding_index];
                }
              }
            }
          }
    break;

    default:
      fprintf(stderr,"Unrecognized image data type?\n");
      return 0;
    }/*end of switch*/
   }/*end of if*/
   else/*color_processed ==0*/
   {
  switch (info->data_type)
    {
    case CVIP_BYTE:
    for (band = 0; band < n_band; band++)
      {
      image_byte = getData_Image(cvipImg, band);
      for(row = img_start_row; row < img_end_row; row += info->row_vector[subimg_nbr])
        for(col = img_start_col; col < img_end_col; col += info->col_vector[subimg_nbr])
          {
          for (vector_row=0; vector_row < info->row_vector[subimg_nbr]; vector_row++)
            {
            img_row = row + vector_row;
            for (vector_col=0; vector_col < info->col_vector[subimg_nbr]; vector_col++)
              {
              img_col = col + vector_col;
              if (img_row < img_end_row && img_col < img_end_col)
                image_byte[img_row][img_col] = ((byte*)(cdbook->vector[cur_vq_code]))[vector_index];
              vector_index++;
              if (vector_index >= vector_length)
                {
                vector_index = 0;
                coding_index++;
                if (coding_index < 
                  ((info->total_vector[subimg_nbr])*(info->color_band)))
                  cur_vq_code = vq_code[coding_index];
                }
              }
            }
          }
      }
    break;

    case CVIP_SHORT:
    for (band = 0; band < n_band; band++)
      {
      image_short = getData_Image(cvipImg, band);
      for(row = img_start_row; row < img_end_row; row += info->row_vector[subimg_nbr])
        for(col = img_start_col; col < img_end_col; col += info->col_vector[subimg_nbr])
          {
          for (vector_row=0; vector_row < info->row_vector[subimg_nbr]; vector_row++)
            {
            img_row = row + vector_row;
            for (vector_col=0; vector_col < info->col_vector[subimg_nbr]; vector_col++)
              {
              img_col = col + vector_col;
              if (img_row < img_end_row && img_col < img_end_col)
                image_short[img_row][img_col] = ((short*)(cdbook->vector[cur_vq_code]))[vector_index];
              vector_index++;
              if (vector_index >= vector_length)
                {
                coding_index++;
                vector_index = 0;
                if (coding_index < 
                  ((info->total_vector[subimg_nbr])*(info->color_band)))
                  cur_vq_code = vq_code[coding_index];
                }
              }
            }
          }
      }
    break;

    case CVIP_INTEGER:
    for (band = 0; band < n_band; band++)
      {
      image_int = getData_Image(cvipImg, band);
      for(row = img_start_row; row < img_end_row; row += info->row_vector[subimg_nbr])
        for(col = img_start_col; col < img_end_col; col += info->col_vector[subimg_nbr])
          {
          for (vector_row=0; vector_row < info->row_vector[subimg_nbr]; vector_row++)
            {
            img_row = row + vector_row;
            for (vector_col=0; vector_col < info->col_vector[subimg_nbr]; vector_col++)
              {
              img_col = col + vector_col;
              if (img_row < img_end_row && img_col < img_end_col)
                image_int[img_row][img_col] = ((int*)(cdbook->vector[cur_vq_code]))[vector_index];
              vector_index++;
              if (vector_index >= vector_length)
                {
                coding_index++;
                vector_index = 0;
                if (coding_index < 
                  ((info->total_vector[subimg_nbr])*(info->color_band)))
                  cur_vq_code = vq_code[coding_index];
                }
              }
            }
          }
      }
    break;

    
    case CVIP_FLOAT:
    for (band = 0; band < n_band; band++)
      {
      image_float = getData_Image(cvipImg, band);
      for(row = img_start_row; row < img_end_row; row += info->row_vector[subimg_nbr])
        for(col = img_start_col; col < img_end_col; col += info->col_vector[subimg_nbr])
          {
          for (vector_row=0; vector_row < info->row_vector[subimg_nbr]; vector_row++)
            {
            img_row = row + vector_row;
            for (vector_col=0; vector_col < info->col_vector[subimg_nbr]; vector_col++)
              {
              img_col = col + vector_col;
              if (img_row < img_end_row && img_col < img_end_col)
                image_float[img_row][img_col] = ((float*)(cdbook->vector[cur_vq_code]))[vector_index];
              vector_index++;
              if (vector_index >= vector_length)
                {
                coding_index++;
                vector_index = 0;
                if (coding_index < 
                  ((info->total_vector[subimg_nbr])*(info->color_band)))
                  cur_vq_code = vq_code[coding_index];
                }
              }
            }
          }
      }
    break;

    case CVIP_DOUBLE:
    for (band = 0; band < n_band; band++)
      {
      image_double= getData_Image(cvipImg, band);
      for(row = img_start_row; row < img_end_row; row += info->row_vector[subimg_nbr])
        for(col = img_start_col; col < img_end_col; col += info->col_vector[subimg_nbr])
          {
          for (vector_row=0; vector_row < info->row_vector[subimg_nbr]; vector_row++)
            {
            img_row = row + vector_row;
            for (vector_col=0; vector_col < info->col_vector[subimg_nbr]; vector_col++)
              {
              img_col = col + vector_col;
              if (img_row < img_end_row && img_col < img_end_col)
                image_double[img_row][img_col] = ((double*)(cdbook->vector[cur_vq_code]))[vector_index];
              vector_index++;
              if (vector_index >= vector_length)
                {
                coding_index++;
                vector_index = 0;
                if (coding_index < 
                  ((info->total_vector[subimg_nbr])*(info->color_band)))
                  cur_vq_code = vq_code[coding_index];
                }
              }
            }
          }
      }
    break;

    default:
      fprintf(stderr,"Unrecognized image data type?\n");
      return 0;
    }/*end of switch*/
   
   }/*end of else*/
  return 1;
  } /* end of ReconstructSubImg() */



/*******************************************************************************************
  	vq_decompression is called by vq_decompress
  		file point to where is codebook vector data
  		file_result point to the vq_info->coding_result part in file
*******************************************************************************************/
int	vq_decompression (VQ_INFO *vq_info, FILE *file, FILE *file_result )
  {
  	VECTOR_LST   *cdbook;
  	int          subImg;
  	int          bits_used;
  	int          length_vector;
  	/*FILE         *codebook_in;*/
  	int          temp;

  	cdbook = (VECTOR_LST   *)calloc(vq_info->subimg_nbr, sizeof(VECTOR_LST *));
  	
      for (subImg = 0; subImg < vq_info->subimg_nbr; subImg++)
       {
    		length_vector = ((vq_info->row_vector)[subImg]) * ((vq_info->col_vector)[subImg]);
/*	fprintf(stderr,"begin allocate_vector_sets()\n");*/
    		if ((allocate_vector_sets(&cdbook,
                              			1, 
                              			(vq_info->total_entry)[subImg],
                              			length_vector,
						(vq_info->row_vector)[subImg],
                              			vq_info->data_type)) != 1) 
                 {
      			fprintf(stderr, "vq_compresion: allocate_vector_sets for cdbook return error");
      			free_vector_sets(&cdbook, 1);
      			free_coding_info(vq_info);
      			return 0;
      		 }

/*	fprintf(stderr,"begin ReadCodebook(file, cdbook, vq_info->data_type)\n");*/
	if ((ReadCodebook(file, cdbook, vq_info->data_type)) == 0)
  	  {
		fprintf(stderr, "decompression: ReadCodebook return error - decompress");
         	free_vector_sets(&cdbook, 1);
          	free_coding_info(vq_info);
          	return 0;
	  }


    	if (vq_info->total_entry[subImg]==0 )
    	 {
    	 	continue;
    	 }
    	bits_used = ceil(log(vq_info->total_entry[subImg])/log(2.0));
/*	fprintf(stderr,"begin ReadVectors()\n");*/
    	if (vq_info->color_processed==0)
    	  { if ((ReadVectors(vq_info->coding_result[subImg],
    			 vq_info->total_vector[subImg]*vq_info->color_band,
                     	 bits_used,
                     	 file_result)) == 0)
         	{
        	fprintf(stderr, "decompression: ReadVectors returns error");
        	free_vector_sets(&cdbook, 1);
        	free_coding_info(vq_info);
        	return 0;
         	}	
           }
        else
    	  { if ((ReadVectors(vq_info->coding_result[subImg],
    			 vq_info->total_vector[subImg],
                     	 bits_used,
                     	 file_result)) == 0)
         	{
        	fprintf(stderr, "decompression: ReadVectors returns error");
        	free_vector_sets(&cdbook, 1);
        	free_coding_info(vq_info);
        	return 0;
         	}	
           }
/*	fprintf(stderr, "begin to ReconstructSubImg\n ");*/
    	if ((ReconstructSubImg(vq_info, cdbook, vq_info->inputImage, subImg)) == 0)
      	 {
      		fprintf(stderr, "decompression: ReconstructSubImg return error");
      		free_vector_sets(&cdbook, 1);
      		free_coding_info(vq_info);
      		return 0;
      	 }
      	 
      }/*end of for loop*/
 	vq_info->inputImage->image_format = VQ;
	return 1;
  }/*end of vq_compression*/

int get_BitsInInt(void)
  {
  int BitsInInt;
  unsigned int  ClearLSBMask;
  unsigned int  BitsInBuffer;

  /* set the LSB of unsigned int buffer.*/
  BitsInBuffer = 0;
  BitsInBuffer = BitsInBuffer| (unsigned int)1;

  ClearLSBMask = 1;
  ClearLSBMask = ~ClearLSBMask;

  BitsInInt = 0;
  while(BitsInBuffer != 0)
    {
    BitsInInt++;
    BitsInBuffer = BitsInBuffer << 1;
    BitsInBuffer = BitsInBuffer & ClearLSBMask;
    }
    
  return BitsInInt;
  }

