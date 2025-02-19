/***************************************************************************
*
*             File Name: vq_initial.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Sat Apr  4 15:21:40 CST 1998
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): 
*                        Southern Illinois University @ Edwardsville
*
* RCS (Revision Control System) Information
* ...Added automatically by RCS 
*
** $Log: vq_initial.c,v $
** Revision 1.11  1999/11/21 04:53:46  ycheng
** an useless message has be cancled in the function 'initial_codebook'.
**
** Revision 1.10  1999/11/13 23:13:07  ycheng
** some parts of the log meassages messed up. hopefully it is fixed now
**
** Revision 1.9  1998/11/25 04:00:59  lguo
**  enough comment before the fuction begins.the version reserves many print out as debugging reference, which will be deleted before freezing. 
**
** Revision 1.8  1998/11/24 04:26:38  lguo
** this is new version of VQ
**
** Revision 1.5  1998/11/16 22:04:43  lguo
** now, when dealing with color img, diferent color bands are treated as diferent sub img.
**
** Revision 1.4  1998/04/14 22:07:01  wzheng
** initial_cdbook()  handle the case codebook larger than training set
**
** Revision 1.3  1998/04/09 02:48:46  wzheng
** fix bug of encoding on diff datatype.  float image still has bug
**
** Revision 1.2  1998/04/09 01:08:54  wzheng
** using new header
**
** Revision 1.1  1998/04/04 21:21:50  wzheng
** Initial revision
**
* RCS (Revision Control System) Information
* ...Added automatically by RCS 
*
** $Log: vq_initial.c,v $
** Revision 1.11  1999/11/21 04:53:46  ycheng
** an useless message has be cancled in the function 'initial_codebook'.
**
** Revision 1.10  1999/11/13 23:13:07  ycheng
** some parts of the log meassages messed up. hopefully it is fixed now
**
** Revision 1.9  1998/11/25 04:00:59  lguo
**  enough comment before the fuction begins.the version reserves many print out as debugging reference, which will be deleted before freezing. 
**
** Revision 1.8  1998/11/24 04:26:38  lguo
** this is new version of VQ
**
** Revision 1.5  1998/11/16 22:04:43  lguo
** now, when dealing with color img, diferent color bands are treated as diferent sub img.
**
** Revision 1.4  1998/04/14 22:07:01  wzheng
** initial_cdbook()  handle the case codebook larger than training set
**
** Revision 1.3  1998/04/09 02:48:46  wzheng
** fix bug of encoding on diff datatype.  float image still has bug
**
** Revision 1.2  1998/04/09 01:08:54  wzheng
** using new header
**
** Revision 1.1  1998/04/04 21:21:50  wzheng
** Initial revision
**
** Revision 1.13  1998/04/01 00:58:50  wzheng
** add VECTOR_LST->vector_height for initial function
** stoped the last crash
** not crash ... all white or black image return.
**
** Revision 1.12  1998/03/15 19:47:30  wzheng
** change cbk_training_square_distance to cbk_training_distance
**
** Revision 1.11  1998/03/10 03:30:39  wzheng
** seperate single_vector_checking()
**
** Revision 1.10  1998/03/07 03:25:48  wzheng
** set point to NULL after free
**
** Revision 1.9  1998/03/01 20:56:58  wzheng
** one codebook for multiple bands at each subimage
**
** Revision 1.8  1998/02/28 01:01:03  wzheng
** add free_codebooks()
**
** Revision 1.7  1998/02/24 18:10:50  wzheng
**  set_coding_info change to initial_info_coding_result()
** initial_training_set() fix the error for initial each band
** define_codebook() fix the three bugs.
**
** Revision 1.6  1998/02/24 16:06:13  wzheng
** initial_codebook() set based on training_set
**
** Revision 1.5  1998/02/23 17:52:34  wzheng
** row col treversing in initial_training_set()
**
** Revision 1.4  1998/02/19 03:22:56  wzheng
** add error_threshold & cdbook_file for free_coding_info()
**
** Revision 1.3  1998/02/14 04:08:36  wzheng
** third compile
**
** Revision 1.2  1998/02/12 03:05:24  wzheng
** second compile
**
** Revision 1.1  1998/02/04 02:04:47  wzheng
** Initial revision
**
*
*
****************************************************************************/
/***************************************************************************
*
*             File Name: lbg_initial.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Tue Feb  3 20:04:34 CST 1998
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): 
*                        Southern Illinois University @ Edwardsville
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
	allocate_vector_sets ()
	**Alloc2DArray()
	free_vector_sets(VECTOR_LST **aset, int no_of_band)
	free_coding_info(VQ_INFO *coding_info)
	initial_training_set ()
	initial_codebook ()
	initial_info_coding_result ()
	define_codebook ()
**************************************************************/


/****************************************************************************
 			ALLOCATE AND FREE 

****************************************************************************/


int allocate_vector_sets (VECTOR_LST **aset, 
	int no_of_sets, 
	int no_of_entries, 
	int length_vector, 
	int vector_heigth,
	CVIP_TYPE data_type
    )
  {

  int		i,j,k;		/* loop counter		*/

  *aset = (VECTOR_LST *)calloc(no_of_sets,sizeof(VECTOR_LST));

  for (i=0; i<no_of_sets; i++) {
    (*aset)[i].vector_size = length_vector;
    (*aset)[i].total_entry = no_of_entries;
		(*aset)[i].vector_heigth = vector_heigth;

    /* the data type of the vector is the same as requirement in the function call*/
    (*aset)[i].vector = Alloc2DArray(no_of_entries,length_vector,data_type);
  }
  return 1;
  }

/*************************************************/
void	**Alloc2DArray(	int		Rows,
			int		Cols,
			CVIP_TYPE	data_type)
{
	void	**Output;
	int	Count;

	Output = (void **)calloc(Rows,sizeof(void *));
	if(Output == NULL)
	return(NULL);

	switch(data_type)
	{
		case	CVIP_BYTE:
			for(Count = 0;Count < Rows;Count++)
			{
				Output[Count]=(byte *)calloc(Cols,sizeof(byte));
				if(Output[Count] == NULL)
				break;
			}
			if(Count == Rows)
			return(Output);
			break;
		case	CVIP_SHORT:
			for(Count = 0;Count < Rows;Count++)
			{
				Output[Count]=(short *)calloc(Cols,sizeof(short));
				if(Output[Count] == NULL)
				break;
			}
			if(Count == Rows)
			return(Output);
			break;
		case	CVIP_INTEGER:
			for(Count = 0;Count < Rows;Count++)
			{
				Output[Count]=(int *)calloc(Cols,sizeof(int));
				if(Output[Count] == NULL)
				break;
			}
			if(Count == Rows)
			return(Output);
			break;
		case	CVIP_FLOAT:
			for(Count = 0;Count < Rows;Count++)
			{
				Output[Count]=(float *)calloc(Cols,sizeof(float));
				if(Output[Count] == NULL)
				break;
			}
			if(Count == Rows)
			return(Output);
			break;
		case	CVIP_DOUBLE:
			for(Count = 0;Count < Rows;Count++)
			{
				Output[Count]=(double *)calloc(Cols,sizeof(double));
				if(Output[Count] == NULL)
				break;
			}
			if(Count == Rows)
			return(Output);
			break;
		default:
			free(Output);
			return(NULL);
	}
	do{
		Count--;
		free(Output[Count]);
	}while(Count);
	free(Output);
	return(NULL);
}


/*************************************************/



void free_vector_sets(VECTOR_LST **aset, int no_of_band) {
  int		i,j;
  
  no_of_band=1;
  
  for (i=0; i< no_of_band; i++){
     for(j=0; j<(*aset)[i].total_entry; j++) {
	     free((*aset)[i].vector[j]);
			 (*aset)[i].vector[j] = NULL;
     }
     free((*aset)[i].vector);
		 (*aset)[i].vector = NULL;
  }
  free(*aset);
	*aset = NULL;
}

void free_codebooks (VECTOR_LST **cdbook, int no_of_band , int no_of_subImg)
  {
  int i;

  if (cdbook != NULL)
    for ( i = 0; i < no_of_subImg; i++)
      {
      if (cdbook[i] != NULL) free_vector_sets(&cdbook[i], no_of_band);
			cdbook[i] = NULL;
      }
    free(cdbook);
		cdbook = NULL;
  }


/*********************************************************************************************
** xchen modified this function for further research
** The structure of VQ_INFO is and only pointers need to be freed
  Image		*inputImage;
  XFORM_FMT	xform;		
  char		*temp_file;	
  int		color_processed;
  int           cdbook_in_file;
  char          *cdbook_file;  
  CVIP_TYPE	data_type;
  int		color_band;
  int           subimg_nbr;
  SUB_IMAGE	*subimage_range;
  int           total_row;
  int           total_col;
  int           fixed_cdbook;
  int		*row_vector;
  int		*col_vector;
  int		*total_vector;
  int           *total_entry;
  double	**error;
  unsigned int  **coding_result;
  float         *error_threshold;
  ERR_METHOD    error_method;
}VQ_INFO;
**
*********************************************************************************************/
void free_coding_info(VQ_INFO *coding_info)
{
	int		band,img;

	/* xchen add code here */
	/* mandotarily release the image pointer NOT FREE*/
	coding_info->inputImage = NULL;

	if (coding_info->subimage_range) 
	{
		free(coding_info->subimage_range);
		coding_info->subimage_range = NULL;
	}
	if (coding_info->row_vector)
	{
		free(coding_info->row_vector);
		coding_info->row_vector = NULL;
	}
	if (coding_info->col_vector)
	{
		free(coding_info->col_vector);
		coding_info->col_vector = NULL;
	}
	if (coding_info->total_vector)
	{
		free(coding_info->total_vector);
		coding_info->total_vector = NULL;
	}
	if (coding_info->total_entry)
	{
		free(coding_info->total_entry);
		coding_info->total_entry = NULL;
	}
	if (coding_info->error_threshold)
	{
		free(coding_info->error_threshold);
		coding_info->error_threshold = NULL;
	}
	/* xchen add this */
	if (coding_info->temp_file)
	{
		free(coding_info->temp_file);
		coding_info->temp_file = NULL;
	}
	if (coding_info->cdbook_file)
	{
		/* xchen updated here shouldn't free cdbook_file 'cause its the parameter passed to the vq_compress */
		/* will cause error if forcely freed */
		/* later recover this structure too complicated one modifed all crashed. really shoot */
		free(coding_info->cdbook_file);
		coding_info->cdbook_file = NULL;
	}

	for (img = 0; (img < coding_info->subimg_nbr)&&(coding_info->error); img++)
	{
		if (*(coding_info->error))
		{
			free(*(coding_info->error));
			*(coding_info->error) = NULL;
		}
		if (*(coding_info->coding_result))
		{
			free (*(coding_info->coding_result));
			*(coding_info->coding_result) = NULL;
		}
	}
	if (coding_info->error)
	{
		free(coding_info->error);
		coding_info->error = NULL;
	}
	if (coding_info->coding_result)
	{
		free (*(coding_info->coding_result));
		coding_info->coding_result = NULL;
	}
}


/****************************************************************************
  initial_training_set
****************************************************************************/
int initial_training_set (
	const Image 	*inputImage, 
	VECTOR_LST 	*training_set,
        int 		row_vector, 
	int 		col_vector, 
	SUB_IMAGE 	img_range,
	int 		color_processed )
{
   int 			band,
			horizontal,	/* num of vectors counte from upper to bottom */
			vertical,	/* num of vectors counte from left to right */
			count,index=0;
   int			flag_row,	/* '1'indicate having remainder on row/vector*/
			flag_col;	/* '1' indicate having remainder on col/vector */
   int			row_range,	/* total number of rows in a subImage */
			col_range;	/* total number of cols in a subImage */
   int			row,
			col;
   unsigned int 	no_of_band,
			no_of_row,
			no_of_col,
			vector_in_row,	/* the number of vector can be arranged in one row */
			vector_in_col;
   byte			**image_byte;
	 short    **image_short;
	 int      **image_int;
	 float    **image_float;
	 double   **image_double;


   no_of_band = getNoOfBands_Image(inputImage);
   no_of_row =  getNoOfRows_Image(inputImage);
   no_of_col =  getNoOfCols_Image(inputImage);
   row_range = img_range.end_row- img_range.start_row+1;
   col_range = img_range.end_col- img_range.start_col+1;

   if (img_range.start_row >= no_of_row ||
	img_range.start_col >= no_of_col ||
	img_range.end_row >= no_of_row ||
	img_range.end_col >= no_of_col ||
	img_range.start_row < 0 ||
	img_range.start_col < 0 ||
	img_range.end_row < 0 ||
	img_range.end_col < 0 ) {
	print_CVIP("\n The subimage range is not correct.");
	return 0;
   }
   flag_row = row_range%row_vector? 1: 0;
   vector_in_row= row_range/row_vector;
   flag_col = col_range%col_vector? 1: 0;
   vector_in_col= col_range/col_vector;

   switch (getDataType_Image(inputImage)) {

   case CVIP_BYTE:
   	switch (color_processed)
   	{
   	case	1:
	image_byte = getData_Image( inputImage, img_range.bands_num);
	for(horizontal=0; horizontal<(vector_in_row+flag_row); horizontal++) {
	   for(vertical=0; vertical<(vector_in_col + flag_col); vertical++) {
		for(count=0; count< training_set->vector_size; count++) {
                  if (index >= training_set->total_entry)
                    return 0;
		   row = (horizontal*row_vector+count/col_vector)%row_range
			+img_range.start_row;
		   col = (vertical*col_vector+count%col_vector)%col_range+img_range.start_col;
		   ((byte*)(training_set->vector[index]))[count]=image_byte[row][col];
		}
		index++;
	   }	   	   	   	   	   	   	   
	}
	break;
   	case	0:
   	for(band = 0; band < no_of_band; band++) {
		image_byte = getData_Image(inputImage, band);	
		for(horizontal=0; horizontal<(vector_in_row+flag_row); horizontal++) {
	   	for(vertical=0; vertical<(vector_in_col + flag_col); vertical++) {
			for(count=0; count< training_set->vector_size; count++) {
                  	if (index >= training_set->total_entry)
                    	return 0;
		   	row = (horizontal*row_vector+count/col_vector)%row_range
			+img_range.start_row;
		   	col = (vertical*col_vector+count%col_vector)%col_range+img_range.start_col;
		   	((byte*)(training_set->vector[index]))[count]=image_byte[row][col];
			}
			index++;
	  	 }	   	   	   	   	   	   	   
		}
   	}
   	break;
   	}
   
   break;

   case CVIP_SHORT:
   	switch (color_processed)
   	{
	case	1:
	image_short = getData_Image( inputImage, img_range.bands_num);
	for(horizontal=0; horizontal<(vector_in_row+flag_row); horizontal++) {
	   for(vertical=0; vertical<(vector_in_col + flag_col); vertical++) {
		for(count=0; count< training_set->vector_size; count++) {
                  if (index >= training_set->total_entry)
                    return 0;
		   row = (horizontal*row_vector+count/col_vector)%row_range
			+img_range.start_row;
		   col = (vertical*col_vector+count%col_vector)%col_range+img_range.start_col;
		   ((short*)(training_set->vector[index]))[count]=image_short[row][col];
		}
		index++;
	   }	   	   	   	   	   	   	   
	}
	break;
	case	0:
	for(band = 0; band < no_of_band; band++) {
		image_short = getData_Image(inputImage, band);	
		for(horizontal=0; horizontal<(vector_in_row+flag_row); horizontal++) {
		   for(vertical=0; vertical<(vector_in_col + flag_col); vertical++) {
			for(count=0; count< training_set->vector_size; count++) {
                  	if (index >= training_set->total_entry)
                    	return 0;
		   	row = (horizontal*row_vector+count/col_vector)%row_range
			+img_range.start_row;
		   	col = (vertical*col_vector+count%col_vector)%col_range+img_range.start_col;
		   	((short*)(training_set->vector[index]))[count]=image_short[row][col];
			}
			index++;
		   }	   	   	   	   	   	   	   
		}
   	}
   	break;
   	}

   break;

   case CVIP_INTEGER:
   	switch (color_processed)
   	{
   	case	1:
	image_int = getData_Image( inputImage, img_range.bands_num);
	for(horizontal=0; horizontal<(vector_in_row+flag_row); horizontal++) {
	   for(vertical=0; vertical<(vector_in_col + flag_col); vertical++) {
		for(count=0; count< training_set->vector_size; count++) {
                   if (index >= training_set->total_entry)
                    return 0;
		   row = (horizontal*row_vector+count/col_vector)%row_range
			+img_range.start_row;
		   col = (vertical*col_vector+count%col_vector)%col_range+img_range.start_col;
		   ((int*)(training_set->vector[index]))[count]=image_int[row][col];
		}
		index++;
	   }	   	   	   	   	   	   	   
	}
	break;
	case	0:
   	for(band = 0; band < no_of_band; band++) {
		image_int = getData_Image(inputImage, band);	
		for(horizontal=0; horizontal<(vector_in_row+flag_row); horizontal++) {
	   	for(vertical=0; vertical<(vector_in_col + flag_col); vertical++) {
			for(count=0; count< training_set->vector_size; count++) {
                   	if (index >= training_set->total_entry)
                    	return 0;
		   	row = (horizontal*row_vector+count/col_vector)%row_range
			+img_range.start_row;
		   	col = (vertical*col_vector+count%col_vector)%col_range+img_range.start_col;
		   	((int*)(training_set->vector[index]))[count]=image_int[row][col];
			}
			index++;
	   	}	   	   	   	   	   	   	   
		}
   	}
   	break;
   	}
   break;

   case CVIP_FLOAT:
   	switch (color_processed)
   	{
   	case	1:
	image_float = getData_Image( inputImage, img_range.bands_num);
	for(horizontal=0; horizontal<(vector_in_row+flag_row); horizontal++) {
	   for(vertical=0; vertical<(vector_in_col + flag_col); vertical++) {
		for(count=0; count< training_set->vector_size; count++) {
                   if (index >= training_set->total_entry)
                    return 0;
		   row = (horizontal*row_vector+count/col_vector)%row_range
			+img_range.start_row;
		   col = (vertical*col_vector+count%col_vector)%col_range+img_range.start_col;
		   ((float*)(training_set->vector[index]))[count]=image_float[row][col];

		}
		index++;
	   }	   	   	   	   	   	   	   
	}
	break;
	case	0:
   	for(band = 0; band < no_of_band; band++) {
		image_float = getData_Image(inputImage, band);	
		for(horizontal=0; horizontal<(vector_in_row+flag_row); horizontal++) {
	   	for(vertical=0; vertical<(vector_in_col + flag_col); vertical++) {
			for(count=0; count< training_set->vector_size; count++) {
                   	if (index >= training_set->total_entry)
                    	return 0;
		   	row = (horizontal*row_vector+count/col_vector)%row_range
			+img_range.start_row;
		   	col = (vertical*col_vector+count%col_vector)%col_range+img_range.start_col;
		   	((float*)(training_set->vector[index]))[count]=image_float[row][col];
			}
			index++;
	   	}	   	   	   	   	   	   	   
		}
   	}
   	break;
   	}
   	
   break;

   case CVIP_DOUBLE:
   	switch (color_processed)
   	{
   	case	1:
	image_double = getData_Image( inputImage, img_range.bands_num);
	for(horizontal=0; horizontal<(vector_in_row+flag_row); horizontal++) {
	   for(vertical=0; vertical<(vector_in_col + flag_col); vertical++) {
		for(count=0; count< training_set->vector_size; count++) {
                   if (index >= training_set->total_entry)
                    return 0;
		   row = (horizontal*row_vector+count/col_vector)%row_range
			+img_range.start_row;
		   col = (vertical*col_vector+count%col_vector)%col_range+img_range.start_col;
		   ((double*)(training_set->vector[index]))[count]=image_double[row][col];
		}
		index++;
	   }	   	   	   	   	   	   	   
	}
	break;
	case	0:
   	for(band = 0; band < no_of_band; band++) {
		image_double = getData_Image(inputImage, band);	
		for(horizontal=0; horizontal<(vector_in_row+flag_row); horizontal++) {
	   	for(vertical=0; vertical<(vector_in_col + flag_col); vertical++) {
			for(count=0; count< training_set->vector_size; count++) {
                  	 if (index >= training_set->total_entry)
                   	 return 0;
		  	 row = (horizontal*row_vector+count/col_vector)%row_range
			+img_range.start_row;
		   	col = (vertical*col_vector+count%col_vector)%col_range+img_range.start_col;
		   	((double*)(training_set->vector[index]))[count]=image_double[row][col];
			}
			index++;
	   	}	   	   	   	   	   	   	   
		}
  	 }
  	 break;
  	 }
		
   break;

   default:
        fprintf(stderr,"Unrecognized image data type?\n");
        return 0;
   }
   return 1;
}
/************** End Of  initial_training_set  **********************************/


/****************************************************************************
 initial_codebook 

****************************************************************************/
int initial_codebook (
	VECTOR_LST *cdbook, 
        VECTOR_LST *training_set,
	CVIP_TYPE data_type) 
{
   int entry;
   int vect;
   float pick_pace;
   int training_entry;

   if (training_set->total_entry < cdbook->total_entry)
     {
     /*fprintf(stderr,"\n\ninitial_codebook: Not good example, cocebook larger than training set");*/
     }


   pick_pace = ((float)training_set->total_entry)/ (float)cdbook->total_entry;
   training_entry = 0;

   switch (data_type)
     {
     case CVIP_BYTE:
	for(entry=0;entry < cdbook->total_entry; entry++) {
     training_entry = pick_pace * entry;
	   for(vect=0; vect < cdbook->vector_size; vect++){
	      ((byte*)(cdbook->vector[entry]))[vect]
			 = ((byte*)(training_set->vector[training_entry]))[vect];
	   }
	 }
    break;

    case CVIP_SHORT:
	for(entry=0;entry < cdbook->total_entry; entry++) {
     training_entry = pick_pace * entry;
	   for(vect=0; vect < cdbook->vector_size; vect++){
	      ((short*)(cdbook->vector[entry]))[vect]
			 = ((short*)(training_set->vector[training_entry]))[vect];
	   }
	 }
    break;

   case CVIP_INTEGER:
	for(entry=0;entry < cdbook->total_entry; entry++) {
     training_entry = pick_pace * entry;
	   for(vect=0; vect < cdbook->vector_size; vect++){
	      ((int*)(cdbook->vector[entry]))[vect]
			 = ((int*)(training_set->vector[training_entry]))[vect];
	   }
	 }
   break;

   case CVIP_FLOAT:
	for(entry=0;entry < cdbook->total_entry; entry++) {
     training_entry = pick_pace * entry;
	   for(vect=0; vect < cdbook->vector_size; vect++){
	      ((float*)(cdbook->vector[entry]))[vect]
			 = ((float*)(training_set->vector[training_entry]))[vect];
	   }
	 }
   break;

   case CVIP_DOUBLE:
	for(entry=0;entry < cdbook->total_entry; entry++) {
     training_entry = pick_pace * entry;
	   for(vect=0; vect < cdbook->vector_size; vect++){
	      ((double*)(cdbook->vector[entry]))[vect]
			 = ((double*)(training_set->vector[training_entry]))[vect];
	   }
	 }
   break;

   default:
        fprintf(stderr,"Unrecognized image data type?\n");
        return 0;
     }
   return 1;
}
/************ End Of  initial_codebook  *****************************************/ 


/****************************************************************************
 initial_info_coding_result 

****************************************************************************/
int initial_info_coding_result (
	VECTOR_LST *cdbook, 
	const VECTOR_LST *training_set, 
	VQ_INFO *coding_info,
        int subimg_nbr
	) 
{

   int		       trn_entry;
   double        *error;
   unsigned int  *coding_result;

   error = coding_info->error[subimg_nbr];
   coding_result = coding_info->coding_result[subimg_nbr];


      for(trn_entry=0; trn_entry < (training_set->total_entry); trn_entry++) {
	coding_result[trn_entry] = (unsigned int) 0;

	error[trn_entry] = cbk_training_distance((cdbook->vector)[0],
	                                         (training_set->vector)[trn_entry],
																					 cdbook->vector_size,
																					 coding_info->data_type);
      }

   return 1;
}
/************ End Of  set_coding_info *****************************************/ 





/****************************************************************************
  define_codebook 
****************************************************************************/
int define_codebook (
	VECTOR_LST *cdbook, 
	const VECTOR_LST *training_set, 
	VQ_INFO    *coding_info,
        int        subimg_nbr
	) 
{
   int		trn_entry,
		item;
   int		*count;		/* number of vectors relating on each codebook entry */
   double	**temp_cbk;	/* temp structure accumulat training set vectors */
   byte		*dt_byte;
   short	*dt_short;
   int		*dt_int;
   float	*dt_float;
   double	*dt_double;
   unsigned int cbk_entry;


   if((count = (int *)calloc(cdbook->total_entry, sizeof(int))) == NULL) {
      fprintf(stderr,"define_codebook: can't allocate memory!");
      return 0;
   }
   /*
    * allocate temp_cbk
    * temp_cbk accumulate vectors which relate to each codebook entry
    */
   if((temp_cbk = (double **)calloc(cdbook->total_entry, sizeof(double*))) == NULL) {
      fprintf(stderr,"define_codebook: can't allocate memory!");
      return 0;
   }
   for(cbk_entry=0; cbk_entry<cdbook->total_entry; cbk_entry++)
     {
     if((temp_cbk[cbk_entry] = (double *)calloc(cdbook->vector_size, sizeof(double))) == NULL)
       {
       fprintf(stderr,"define_codebook: can't allocate memory!");
       return 0;
       }
     }


   switch(coding_info->data_type) {
   case CVIP_BYTE:
      /*
       * accumulate all the training_set_vectors grouped on the codebook_entrys 
       * that they are encoded. 
       * the 'count' record the number of training_set_vectors which is encode
       * as certain codebook entries.
       */
      for(trn_entry=0; trn_entry<training_set->total_entry; trn_entry++) {
	cbk_entry = coding_info->coding_result[subimg_nbr][trn_entry];
	dt_byte = ((byte*)(training_set->vector[trn_entry]));
	for(item=0; item<cdbook->vector_size; item++) {
	   temp_cbk[cbk_entry][item] += ((double)(dt_byte[item]));
	}
	count[cbk_entry]++;
      }

      /*
       * get the average value of the training_set_vectors which relates each
       * codebook_entry.  redefine the codebook
       */
      for(cbk_entry=0; cbk_entry<cdbook->total_entry; cbk_entry++) {
	for(item=0; item<cdbook->vector_size; item++) {
	   temp_cbk[cbk_entry][item] /= count[cbk_entry];
	   ((byte*)(cdbook->vector[cbk_entry]))[item] = ((byte)(temp_cbk[cbk_entry][item]));
	}
      }
      break;

   case CVIP_SHORT:
      /*
       * accumulate all the training_set_vectors grouped on the codebook_entrys 
       * that they are encoded. 
       * the 'count' record the number of training_set_vectors which is encode
       * as certain codebook entries.
       */
      for(trn_entry=0; trn_entry<training_set->total_entry; trn_entry++) {
	cbk_entry = coding_info->coding_result[subimg_nbr][trn_entry];
	dt_short = ((short*)(training_set->vector[trn_entry]));
	for(item=0; item<cdbook->vector_size; item++) {
	   temp_cbk[cbk_entry][item] += ((double)(dt_short[item]));
	}
	count[cbk_entry]++;
      }

      /*
       * get the average value of the training_set_vectors which relates each
       * codebook_entry.  redefine the codebook
       */
      for(cbk_entry=0; cbk_entry<cdbook->total_entry; cbk_entry++) {
	for(item=0; item<cdbook->vector_size; item++) {
	   temp_cbk[cbk_entry][item] /= count[cbk_entry];
	   ((short*)(cdbook->vector[cbk_entry]))[item] = (short)(temp_cbk[cbk_entry][item]);
	}
      }
      break;

   case CVIP_INTEGER:
      /*
       * accumulate all the training_set_vectors grouped on the codebook_entrys 
       * that they are encoded. 
       * the 'count' record the number of training_set_vectors which is encode
       * as certain codebook entries.
       */
      for(trn_entry=0; trn_entry<training_set->total_entry; trn_entry++) {
	cbk_entry = coding_info->coding_result[subimg_nbr][trn_entry];
	dt_int = ((int*)(training_set->vector[trn_entry]));
	for(item=0; item<cdbook->vector_size; item++) {
	   temp_cbk[cbk_entry][item] += ((double)(dt_int[item]));
	}
	count[cbk_entry]++;
      }

      /*
       * get the average value of the training_set_vectors which relates each
       * codebook_entry.  redefine the codebook
       */
      for(cbk_entry=0; cbk_entry<cdbook->total_entry; cbk_entry++) {
	for(item=0; item<cdbook->vector_size; item++) {
	   temp_cbk[cbk_entry][item] /= count[cbk_entry];
	   ((int*)(cdbook->vector[cbk_entry]))[item] = (int)(temp_cbk[cbk_entry][item]);
	}
      }
      break;

   case CVIP_FLOAT:
      /*
       * accumulate all the training_set_vectors grouped on the codebook_entrys 
       * that they are encoded. 
       * the 'count' record the number of training_set_vectors which is encode
       * as certain codebook entries.
       */
      for(trn_entry=0; trn_entry<training_set->total_entry; trn_entry++) {
	cbk_entry = coding_info->coding_result[subimg_nbr][trn_entry];
	dt_float = ((float*)(training_set->vector[trn_entry]));
	for(item=0; item<cdbook->vector_size; item++) {
	   temp_cbk[cbk_entry][item] += ((double)(dt_float[item]));
	}
	count[cbk_entry]++;
      }

      /*
       * get the average value of the training_set_vectors which relates each
       * codebook_entry.  redefine the codebook
       */
      for(cbk_entry=0; cbk_entry<cdbook->total_entry; cbk_entry++) {
	for(item=0; item<cdbook->vector_size; item++) {
	   temp_cbk[cbk_entry][item] /= count[cbk_entry];
	   ((float*)(cdbook->vector[cbk_entry]))[item] = (float)(temp_cbk[cbk_entry][item]);
	}
      }
      break;

   case CVIP_DOUBLE:
      /*
       * accumulate all the training_set_vectors grouped on the codebook_entrys 
       * that they are encoded. 
       * the 'count' record the number of training_set_vectors which is encode
       * as certain codebook entries.
       */
      for(trn_entry=0; trn_entry<training_set->total_entry; trn_entry++) {
	cbk_entry = coding_info->coding_result[subimg_nbr][trn_entry];
	dt_double = ((double*)(training_set->vector[trn_entry]));
	for(item=0; item<cdbook->vector_size; item++) {
	   temp_cbk[cbk_entry][item] += ((double)(dt_double[item]));
	}
	count[cbk_entry]++;
      }

      /*
       * get the average value of the training_set_vectors which relates each
       * codebook_entry.  redefine the codebook
       */
      for(cbk_entry=0; cbk_entry<cdbook->total_entry; cbk_entry++) {
	for(item=0; item<cdbook->vector_size; item++) {
	   temp_cbk[cbk_entry][item] /= count[cbk_entry];
	   ((double*)(cdbook->vector[cbk_entry]))[item] = (double)(temp_cbk[cbk_entry][item]);
	}
      }
      break;

   default:
     fprintf(stderr,"Unrecognized image data type?\n");
     return 0;
   }

      
   free(count);
   free(temp_cbk);
   return 1;
}
/************ End Of  define_codebook  *****************************************/ 
