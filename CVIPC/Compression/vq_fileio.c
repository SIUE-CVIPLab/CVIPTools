/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: write_vector.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Tue Feb  3 20:12:34 CST 1998
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): 
*                        Southern Illinois University @ Edwardsville
*
* RCS (Revision Control System) Information
* ...Added automatically by RCS 
*
** $Log: vq_fileio.c,v $
** Revision 1.10  2001/04/04 06:20:03  ycheng
** fixed one bug.
**
** Revision 1.9  1999/05/30 22:46:34  lguo
** some print out commented out
**
** Revision 1.8  1999/04/20 22:57:59  lguo
** deleted some useless output printing
**
** Revision 1.7  1999/04/20 22:12:05  lguo
** *** empty log message ***
**
** Revision 1.6  1998/11/25 04:00:20  lguo
**  enough comment before the fuction begins.the version reserves many print out as debugging reference, which will be deleted before freezing.
**
** Revision 1.4  1998/11/14 06:38:42  lguo
** when inout is a color img, the 3 color bands are now treated as different subimg.
**
** Revision 1.3  1998/10/24 09:04:29  lguo
** no changes
**
** Revision 1.2  1998/04/09 01:08:05  wzheng
** compressed file checking(add)
**
** Revision 1.1  1998/04/04 21:22:29  wzheng
** Initial revision
**
** Revision 1.13  1998/04/02 00:10:06  wzheng
** all parameters working
**
** Revision 1.12  1998/03/26 00:31:03  wzheng
** add codebook member "vector_heigth" read and write
++ stoped VECTOR_LST->vector_height after last crash
++ not crash ... all white or black image return.
**
** Revision 1.11  1998/03/07 04:14:04  wzheng
** revise memory allocate error on vq_info->coding_result
**
** Revision 1.10  1998/03/07 03:26:31  wzheng
** change mis_seting on coding_result length
**
** Revision 1.9  1998/03/06 00:41:58  wzheng
** take off signing error and error_threshold to NULL
** it cause crash
**
** Revision 1.8  1998/03/02 00:59:06  wzheng
** revise ReadVectors()
**
** Revision 1.7  1998/03/01 20:40:05  wzheng
** revise function of read and write vectors
** add function getBitsInInt()
**
** Revision 1.6  1998/02/20 00:47:45  wzheng
** VQ_INFO add: fixed_cdbook,cdbook_in_file, cdbook_file
** adjust function returns
**
** Revision 1.5  1998/02/15 22:19:59  wzheng
** add total_row and total_col read write into "VQ_INFO"
**
** Revision 1.4  1998/02/14 05:36:19  wzheng
** add memory allocate to ReadHeader()
** third compile
**
** Revision 1.3  1998/02/14 04:08:54  wzheng
** third compile
**
** Revision 1.2  1998/02/12 03:04:35  wzheng
** second compile
**
** Revision 1.1  1998/02/04 02:13:07  wzheng
** Initial revision
**
*
****************************************************************************/
/***************************************************************************
*
*             File Name: write_vector.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Tue Feb  3 20:10:18 CST 1998
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): 
*                        Southern Illinois University @ Edwardsville
*
****************************************************************************/
/*
** include header files
*/

#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPimage.h"
#include <vector_quant.h>
#define CASE_MAX 3
/**************************************************************
In this file contains these functions :
	WriteHeader (VQ_INFO *vq_info, FILE *file )
	WriteVectors ()
	ReadVectors()
	WriteCodebook ()
	ReadCodebook ()
	GetCodebook ()
	WriteCodebookHeader(FILE *cdbook_file, VQ_INFO *vq_info)
	get_vq_info_from_file(FILE temp_file,VQ_INFO vq_info )
	read_cdbook_info_from_file (FILE *file, VQ_INFO *vq_info)
	get_info_from_codebook_file(coding_info)
	write_to_disk( VQ_INFO *vq_info, VECTOR_LST   **cdbook )    
**************************************************************/


/****************************************************************************
 	 WriteHeader
 	 this function write the header part of temp_file
 	 	'v'
 	 	'q'
 	 	vq_info->cdbook_in_file
 	 	if (vq_info->cdbook_in_file == 0)
 	 	{file_name_length
 	 	 cdbook file name
 	 	 }
****************************************************************************/
void WriteHeader (VQ_INFO *vq_info, FILE *file )
  {
  int            n_subimg;
  SUB_IMAGE      *img_rang;
  int            file_name_length;

  fputc((int)'v',file);

  fputc((int)'q',file);
  fwrite(&(vq_info->cdbook_in_file), sizeof(int),1,file);
  if (vq_info->cdbook_in_file == 0)
    {
    file_name_length = strlen(vq_info->cdbook_file)+1;
    fwrite(& file_name_length, sizeof(int),1,file);
    fwrite(vq_info->cdbook_file, sizeof(char),file_name_length,file);
    }
  }/*  End of WriteHeader */




/****************************************************************************
 WriteVectors write the coding result from *VectorArray to file
****************************************************************************/
void WriteVectors (
     unsigned int	*VectorArray,
     unsigned int	TotalVectors,
     unsigned int	BitsUsed,
     FILE		*file 
     )
  {
  unsigned char	WriteBuffer =(unsigned char)0;
  unsigned int	BitsInBuffer;
  unsigned int	TestMSB;
  unsigned char ClearLSBMask;
  unsigned int	CurVector;
  int           BitsInInt;
  int 		j,k;

  if (VectorArray==NULL)
  return ;
  
  BitsInInt = get_BitsInInt();
  /* TestMSB is an unsigned integer with only the MSB set.
  It is used to test the MSB of the vector.*/
  TestMSB = (unsigned int)((unsigned int)1 << (BitsInInt-1));
  /* ClearLSBMask is an unsigned integer with all bits
  except the LSB set.  It is use to clear the LSB.*/
  ClearLSBMask = (unsigned char) 1;
  ClearLSBMask = ~ClearLSBMask;

  /* At the beginning, the buffer is empty */
  BitsInBuffer = 0;
  for(j = 0;j< TotalVectors;j++)
    {
    CurVector = VectorArray[j];
    /* Strip off high bits. */
    CurVector = CurVector << (BitsInInt-BitsUsed);
    /* For all used bits in current vector, */
    for(k = 0;k < BitsUsed;k++)
      {
      if(BitsInBuffer == 8)
        {
         /* Buffer is full.  Write it out to disk. */
         fwrite(&WriteBuffer,sizeof(unsigned char),1,file);
         /* Now buffer should be empty. */
         BitsInBuffer = 0;
         }
      /* Reserve space for one bit in write buffer. */
      WriteBuffer = (unsigned char)(WriteBuffer << 1);
      /* If the MSB is 1, set the LSB of the write buffer.*/
      if(CurVector & TestMSB)
      WriteBuffer = WriteBuffer | (unsigned char)1;
      /* Else, clear the LSB of the write buffer. */
      else
      WriteBuffer = WriteBuffer & ClearLSBMask;
      /* We have written one bit, so update the counter. */
      BitsInBuffer++;
      /* Shift off the current MSB and move the next 
      bit to the MSB position.*/
      CurVector = (unsigned int)(CurVector << 1);
      }
    }

    /* Write the remaining bits to disk.*/
      WriteBuffer = (unsigned char)(WriteBuffer << (8-BitsInBuffer));
      fwrite(&WriteBuffer,sizeof(unsigned char),1,file);

  }/*End of WriteVectors*/


/****************************************************************************
 ReadVectors read coding result from file to *VectorArray
****************************************************************************/
int ReadVectors(
     unsigned int	*VectorArray,
     unsigned int	TotalVectors,
     unsigned int	BitsUsed,
     FILE		*file 
     )
  {
  unsigned char	ReadBuffer;
  unsigned int	BitsOutBuffer;
  unsigned char TestMSB;
  unsigned int  ClearLSBMask;
  unsigned int	CurVector=0;
  int           BitsInInt;
  int 		j,k;
  int           vector_cnt;
  


  BitsInInt = get_BitsInInt();
  /* TestMSB is an unsigned integer with only the MSB set.
  It is used to test the MSB of the vector.*/
  TestMSB = (unsigned char)((unsigned char)1 << (8 - 1));
  /* ClearLSBMask is an unsigned integer with all bits
  except the LSB set.  It is use to clear the LSB.*/
  ClearLSBMask = (unsigned int) 1;
  ClearLSBMask = ~ClearLSBMask;

  /* At the beginning, the buffer is empty */
  BitsOutBuffer = 0;
  fread(&ReadBuffer,sizeof(unsigned char),1, file);
  for(j = 0;j< TotalVectors;j++)
    {
    CurVector = CurVector << (BitsInInt-BitsUsed);

    /* For all used bits in current vector, */
    for(k = 0;k < BitsUsed;k++)
      {
      if(BitsOutBuffer == 8)
        {
        fread(&ReadBuffer,sizeof(unsigned char),1, file);
        BitsOutBuffer = 0;
        }
      CurVector = (unsigned int)(CurVector<< 1);
      /* If the MSB is 1, set the LSB of the bit buffer.*/
      if(ReadBuffer & TestMSB)
        CurVector = CurVector | (unsigned int)1;
      /* Else, clear the LSB of the write buffer. */
      else
        CurVector = CurVector & ClearLSBMask;
      /* We have written one bit, so update the counter. */
      BitsOutBuffer++;
      /* Shift off the current MSB and move the next */
      /* bit to the MSB position.*/
      ReadBuffer = (unsigned char)(ReadBuffer << 1);
      }
    VectorArray[j] = CurVector;
    
    }

  return 1;
  }

/************************  End of ReadVectors****************************/


/***********************************************************************
  WriteCodebook. 
  	the *file might point to cdbook_file or the cerain part of tem_file
  	this fuction write to file the data of each subimg:
  	row_vector
  	col_vector
  	total_entry
  	error_threshold
  	vectordata[entry][vector]
***********************************************************************/
void WriteCodebook (
     FILE            *file,
     VECTOR_LST      *cdbook,
     VQ_INFO         *vq_info,
     int	     subimg
     )
  {
  int entries;
  int vectors;
  byte vector_byte;
  short vector_short;
  int vector_int;
  float vector_float;
  double vector_double;
  
  fwrite(&(vq_info->subimage_range[subimg].bands_num), sizeof(int),1,file);
  fwrite(&(vq_info->subimage_range[subimg].start_row), sizeof(int),1,file);
  fwrite(&(vq_info->subimage_range[subimg].start_col), sizeof(int),1,file);
  fwrite(&(vq_info->subimage_range[subimg].end_row), sizeof(int),1,file);
  fwrite(&(vq_info->subimage_range[subimg].end_col), sizeof(int),1,file);
  fwrite(&(vq_info->row_vector[subimg]), sizeof(int),1,file);
  fwrite(&(vq_info->col_vector[subimg]), sizeof(int),1,file);
  fwrite(&(vq_info->total_entry[subimg]), sizeof(int),1,file);
  fwrite(&(vq_info->error_threshold[subimg]), sizeof(float),1,file);

  for (entries=0; entries < cdbook->total_entry; entries++)
    {
    switch (vq_info->data_type)
      {
      case CVIP_BYTE:
        for (vectors=0; vectors < cdbook->vector_size; vectors++)
          {
          vector_byte = ((byte *)(cdbook->vector[entries]))[vectors];
          fwrite(&(vector_byte),sizeof(byte),1,file);
          }
      break;

      case CVIP_SHORT:
        for (vectors=0; vectors < cdbook->vector_size; vectors++)
          {
          vector_short= ((short*)(cdbook->vector[entries]))[vectors];
          fwrite(&(vector_short),sizeof(short),1,file);
          }
      break;

      case CVIP_INTEGER:
        for (vectors=0; vectors < cdbook->vector_size; vectors++)
          {
          vector_int= ((int*)(cdbook->vector[entries]))[vectors];
          fwrite(&(vector_int),sizeof(int),1,file);
          }
      break;

      case CVIP_FLOAT:
        for (vectors=0; vectors < cdbook->vector_size; vectors++)
          {
          vector_float= ((float*)(cdbook->vector[entries]))[vectors];
          fwrite(&(vector_float),sizeof(float),1,file);
          }
      break;

      case CVIP_DOUBLE:
        for (vectors=0; vectors < cdbook->vector_size; vectors++)
          {
          vector_double= ((double*)(cdbook->vector[entries]))[vectors];
          fwrite(&(vector_double),sizeof(double),1,file);
          }
      }
    }

  }/* End of WriteCodebook  **/


/*********************************************************************
  	ReadCodebook
  	this function only read the vector information for each subimg.
  	so it skips the SUB_IMAGE part
*********************************************************************/
int ReadCodebook (
        FILE          	*file,
        VECTOR_LST    	*cdbook,
        CVIP_TYPE    	datatype
        )
  {
  int entries;
  int width;
  int vectors;
  byte vector_byte;
  short vector_short;
  int vector_int;
  float vector_float;
  double vector_double;

  if (file ==NULL)
    return 0;
    
  fseek(file,sizeof(SUB_IMAGE) ,1/*SEEK_CUR*/);
  fread(&(cdbook->vector_heigth), sizeof(int),1,file);
  fread(&(width), sizeof(int),1,file);
  cdbook->vector_size = cdbook->vector_heigth * width;
  fread(&(cdbook->total_entry), sizeof(int),1,file);
  fseek(file,sizeof(float) ,1/*SEEK_CUR*/);
  
  if (cdbook->total_entry==0) 
    {cdbook->vector=NULL;
     return 1;
    }
  for (entries=0; entries < cdbook->total_entry; entries++)
    {
    switch (datatype)
      {
      case CVIP_BYTE:
        for (vectors=0; vectors < cdbook->vector_size; vectors++)
          {
          fread(&(vector_byte),sizeof(byte),1,file);
          ((byte *)(cdbook->vector[entries]))[vectors] = vector_byte;
          }
      break;

      case CVIP_SHORT:
        for (vectors=0; vectors < cdbook->vector_size; vectors++)
          {
          fread(&(vector_short),sizeof(short),1,file);
          ((short*)(cdbook->vector[entries]))[vectors] = vector_short;
          }
      break;

      case CVIP_INTEGER:
        for (vectors=0; vectors < cdbook->vector_size; vectors++)
          {
          fread(&(vector_int),sizeof(int),1,file);
          ((int*)(cdbook->vector[entries]))[vectors] = vector_int;
          }
      break;

      case CVIP_FLOAT:
        for (vectors=0; vectors < cdbook->vector_size; vectors++)
          {
          fread(&(vector_float),sizeof(float),1,file);
          ((float*)(cdbook->vector[entries]))[vectors] = vector_float;
          }
      break;

      case CVIP_DOUBLE:
        for (vectors=0; vectors < cdbook->vector_size; vectors++)
          {
          fread(&(vector_double),sizeof(double),1,file);
          ((double*)(cdbook->vector[entries]))[vectors] = vector_double;
          }
      }
    }


  return 1;
  }/*End of ReadCodebook */




/*********************************************************************
  GetCodebook
	should allocate memory along reading
*********************************************************************/
int GetCodebook (
	FILE          *file,
	VECTOR_LST    *cdbook,
	CVIP_TYPE     datatype
	)
  {
  int entries;
  int vectors;
  byte vector_byte;
  short vector_short;
  int vector_int;
  float vector_float;
  double vector_double;

  if (file ==NULL)
    return 0;

  fread(&(cdbook->vector_size), sizeof(int),1,file);
	fread(&(cdbook->vector_heigth), sizeof(int),1,file);
  fread(&(cdbook->total_entry), sizeof(int),1,file);

  cdbook->vector = Alloc2DArray(cdbook->total_entry,
																cdbook->vector_size,
																datatype);
  for (entries=0; entries < cdbook->total_entry; entries++)
    {
    switch (datatype)
      {
      case CVIP_BYTE:
        for (vectors=0; vectors < cdbook->vector_size; vectors++)
          {
          fread(&(vector_byte),sizeof(byte),1,file);
          ((byte *)(cdbook->vector[entries]))[vectors] = vector_byte;
          }
      break;

      case CVIP_SHORT:
        for (vectors=0; vectors < cdbook->vector_size; vectors++)
          {
          fread(&(vector_short),sizeof(short),1,file);
          ((short*)(cdbook->vector[entries]))[vectors] = vector_short;
          }
      break;

      case CVIP_INTEGER:
        for (vectors=0; vectors < cdbook->vector_size; vectors++)
          {
          fread(&(vector_int),sizeof(int),1,file);
          ((int*)(cdbook->vector[entries]))[vectors] = vector_int;
          }
      break;

      case CVIP_FLOAT:
        for (vectors=0; vectors < cdbook->vector_size; vectors++)
          {
          fread(&(vector_float),sizeof(float),1,file);
          ((float*)(cdbook->vector[entries]))[vectors] = vector_float;
          }
      break;

      case CVIP_DOUBLE:
        for (vectors=0; vectors < cdbook->vector_size; vectors++)
          {
          fread(&(vector_double),sizeof(double),1,file);
          ((double*)(cdbook->vector[entries]))[vectors] = vector_double;
          }
      }
    }


  return 1;
  }/*End of ReadCodebook  */


  
/**************WriteCodebookHeader(File *cdbook_file, VQ_INFO *vq_info)*******
	this function write the header part of codebookfile, including:
	vq_info->subimg_nr
	vq_info->data_type
	vq_info->color_band
	vq_info->total_row
	vq_info->total_col
	vq_info->color_processed
	vq_info->error_method
************************************************************************************/
void 	WriteCodebookHeader(FILE *cdbook_file, VQ_INFO *vq_info)
      {	
        fwrite(&( vq_info->subimg_nbr ),sizeof(int),1,cdbook_file);
        fwrite(&( vq_info->data_type ),sizeof(int),1,cdbook_file);
        fwrite(&( vq_info->color_band ),sizeof(int),1,cdbook_file);
        fwrite(&( vq_info->total_row ),sizeof(int),1,cdbook_file);
        fwrite(&( vq_info->total_col ),sizeof(int),1,cdbook_file);
        fwrite(&( vq_info->color_processed ),sizeof(int),1,cdbook_file);
        fwrite(&( vq_info->error_method ),sizeof(int),1,cdbook_file);
      }/*end of WriteCodebookHeader()*/
      
 
 
/********get_vq_info_from_file(FILE temp_file,VQ_INFO vq_info )*******
	this function read from temp_file and cdbook_file to fill
	most of vq_info's parts, except these useless parts:
	vq_info->xform
	vq_info->fixedcdbook
	vq_info->color_band
	vq_info->temp_file
	this two will be given value NUll
	vq_info->error
	vq_info->error_threshold
	and the vq_info->inputImage will be filled in later functions
************************************************************************************/
int get_vq_info_from_file( char *temp_file, VQ_INFO *vq_info )	
{
	FILE	*file, *cdbook_file;
	char    vv,qq;
	/* xchen comments this line */
	/* char    *cdbk_name; */
	int	 length, bits_used, subimg;
	
	vq_info->error=NULL;
	vq_info->error_threshold=NULL;
	/*	fprintf(stderr,"begin cdbook_file=calloc(1, sizeof (FILE))\n");*/

	/* xchen comments this line */
  	/* cdbook_file=calloc(1, sizeof (FILE)); */
	/*	fprintf(stderr," cdbook_file=calloc(1, sizeof (FILE)) ok\n");*/
	/* xchen comments this line */
	/* cdbk_name = calloc(150, sizeof (char)); */
	/* xchen update  this two line */
	/*vq_info->temp_file = (char *)calloc(CVIP_MAX_PATH, sizeof (char));*/
	vq_info->cdbook_file= (char *)calloc(CVIP_MAX_PATH, sizeof (char));
	
	if ( !(file = fopen(temp_file, "rb")) )
	{
		fprintf(stderr, "decompress: open temp_file failed\n%s\n", temp_file);
		return 0;
	}

  	vv = (char)getc(file);
	qq = (char)getc(file);
	if (vv != 'v' || qq != 'q') 
	{
		fprintf(stderr, "decompress: it is not QV file\n");
		return 0;
	}
	
	fread(&(vq_info->cdbook_in_file), sizeof(int),1,file);
	if (  vq_info->cdbook_in_file == 0)
	{	
		fread(&(length), sizeof(int),1,file);
		fread(vq_info->cdbook_file, sizeof(char),length,file);
  		if ( !(cdbook_file = fopen(vq_info->cdbook_file, "rb")) )
		{	
			fprintf(stderr,"fopen(vq_info->cdbook_file, ) failed\n");
			return 0;
  	  	}
		/*	fprintf(stderr,"begin read_cdbook_info_from_file(cdbook_file, vq_info)\n");*/
		if (!(read_cdbook_info_from_file(cdbook_file, vq_info)))
		{
			fprintf(stderr, "decompress: read_cdbook_info_from_file failed");
     	 	return 0;
		}
		fclose(cdbook_file);
	}/*end of if*/
	else
	{	
		/*	fprintf(stderr,"begin read_cdbook_info_from_file(file, vq_info)\n");*/
		if (!(read_cdbook_info_from_file(file, vq_info)))
		{
			fprintf(stderr, "decompress: read_cdbook_info_from_file failed");
     	 	return 0;
		}
	}/*end of else*/
     	  
	/* read vq_info->coding_result  */
	for (subimg=0; subimg<vq_info->subimg_nbr; subimg++)
	{
		if (vq_info->total_entry[subimg]==0)
		{
			continue;
		}
     	  	
		bits_used = ceil(log(vq_info->total_entry[subimg])/log(2.0));
		if ((ReadVectors(vq_info->coding_result[subimg],
						(vq_info->total_vector[subimg]),
						bits_used,
						file)) == 0)
		{
			fprintf(stderr, "decompression: ReadVectors returns error");
			free_coding_info(vq_info);
			return 0;
		}
     	  
	}/*end of for loop*/
	fclose(file);
	return 1;
     	

}/*end of et_vq_info_from_file(FILE temp_file,VQ_INFO vq_info )*/

/******read_cdbook_info_from_file(FIEL *file, VQ_INFO *vq_info)****************
	this function read the codebook part of temp_file, or from cdbook_file
****************************************************************************/	
int read_cdbook_info_from_file (FILE *file, VQ_INFO *vq_info)
   {	int	n_subimg, move;
   
	fread(&(vq_info->subimg_nbr), sizeof(int),1,file);
  	fread(&(vq_info->data_type), sizeof(int),1,file);
  	fread(&(vq_info->color_band), sizeof(int),1,file);
  	fread(&(vq_info->total_row), sizeof(int),1,file);
   	fread(&(vq_info->total_col), sizeof(int),1,file);
  	fread(&(vq_info->color_processed), sizeof(int),1,file);
 	fread(&(vq_info->error_method), sizeof(int),1,file);
 	
	vq_info->subimage_range = (SUB_IMAGE *)calloc(vq_info->subimg_nbr, sizeof(SUB_IMAGE));
      	vq_info->row_vector = (int *)calloc(vq_info->subimg_nbr, sizeof(int));
      	vq_info->col_vector = (int *)calloc(vq_info->subimg_nbr, sizeof(int));
      	vq_info->total_vector = (int *)calloc(vq_info->subimg_nbr, sizeof(int));
      	vq_info->total_entry = (int *)calloc(vq_info->subimg_nbr, sizeof(int));
      	vq_info->coding_result = (int **)calloc(vq_info->subimg_nbr, sizeof(int*));
	
	for(n_subimg=0;n_subimg<vq_info->subimg_nbr;n_subimg++)
    	  {
    		fread(&(vq_info->subimage_range[n_subimg].bands_num),sizeof(int),1,file);
    		fread(&(vq_info->subimage_range[n_subimg].start_row),sizeof(int),1,file);
    		fread(&(vq_info->subimage_range[n_subimg].start_col),sizeof(int),1,file);
    		fread(&(vq_info->subimage_range[n_subimg].end_row),sizeof(int),1,file);
    		fread(&(vq_info->subimage_range[n_subimg].end_col),sizeof(int),1,file);


    		fread(&(vq_info->row_vector[n_subimg]), sizeof(int),1,file);
    		fread(&(vq_info->col_vector[n_subimg]), sizeof(int),1,file);
		fread(&(vq_info->total_entry[n_subimg]), sizeof(int),1,file);   
		 
	   	vq_info->total_vector[n_subimg] = ceil(((float)(vq_info->subimage_range[n_subimg].end_row - vq_info->subimage_range[n_subimg].start_row+1)/(float)vq_info->row_vector[n_subimg]));
     		vq_info->total_vector[n_subimg] *= ceil((float)(vq_info->subimage_range[n_subimg].end_col - vq_info->subimage_range[n_subimg].start_col+1)/(float)vq_info->col_vector[n_subimg]);
     		
     		if (!vq_info->color_processed)
     		   {	vq_info->coding_result[n_subimg] = (int *)calloc(vq_info->total_vector[n_subimg]*vq_info->color_band, sizeof(int));
     		   }
     		else
     		   {	vq_info->coding_result[n_subimg] = (int *)calloc(vq_info->total_vector[n_subimg], sizeof(int));
     		   }
		
		move = vq_info->total_entry[n_subimg]*vq_info->row_vector[n_subimg]*vq_info->col_vector[n_subimg];
      		switch (vq_info->data_type)
      		{
      		case CVIP_BYTE:
      			move *= sizeof (byte); break;
      		case CVIP_SHORT:
      			move *= sizeof (short); break;
      		case CVIP_INTEGER:
      			move *= sizeof (int); break;
      		case CVIP_FLOAT:
      			move *= sizeof (float); break;
      		case CVIP_DOUBLE:
      			move *= sizeof (double); break;
      		}
      		move +=sizeof(float);
		fseek(file, move, 1/*SEEK_CUR*/	);/*skip error_threshopld and vectordata*/
    	  }/*end of for loop*/
	return 1;
   }/*end of read_cdbook_info_from_file */

/******************get_info_from_codebook_file(coding_info)****************
	this function get vq_info from codebookfile.
	From the cdbook_file we get these:
		coding_info->color_processed
		coding_info->subimg_nbr
		coding_info->row_vector
		coding_info->col_vector
		coding_info->subimage_range
		coding_info->total_entry
		coding_info->error_threshold
		coding_info->error_method
		coding_info->total_vector
		coding_info->subimage_range
		coding_info->error
		coding_info->coding_result
	verify these:
		coding_info->data_type
		coding_info->color_band
		coding_info->total_row
		coding_info->total_col
**************************************************************************/
int	get_info_from_codebook_file(VQ_INFO *coding_info )	
{
	FILE	*cdbkfile;
	int	i, data_type, color_band ,total_col, total_row, move;
      	
	if ( !( cdbkfile = fopen(coding_info->cdbook_file, "rb"))) 
	{
		fprintf(stderr, "Read code file error\n");
		return 0;
	}
      		 
	/* verify coding_info->data_type, coding_info->color_band */
	fread(& (coding_info->subimg_nbr),sizeof(int),1,cdbkfile);
	fread(& (data_type),sizeof(int),1,cdbkfile);
	fread(& (color_band),sizeof(int),1,cdbkfile);
	fread(& (total_row),sizeof(int),1,cdbkfile);
	fread(& (total_col),sizeof(int),1,cdbkfile);
      	
      	if ( 	(data_type != coding_info->data_type) || 
      		(color_band != coding_info->color_band) ||
      		(total_col !=  coding_info->total_col) ||
      		(total_row != coding_info->total_row)   )
      		{fprintf(stderr, "This code does not match input Image\n");
		return 0;
		}
  		 
      	/* reading data */
      	coding_info->xform=0;
      	coding_info->error_method = mean_square;
      	fread(& (coding_info->color_processed),sizeof(int),1,cdbkfile);
      	fread(& (coding_info->error_method),sizeof(int),1,cdbkfile);
      	
      	coding_info->row_vector = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
      	coding_info->col_vector = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
      	coding_info->total_entry = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
      	coding_info->error_threshold = (float *)calloc( coding_info->subimg_nbr, sizeof(float));
      	coding_info->total_vector = (int *)calloc( coding_info->subimg_nbr, sizeof(int));
      	coding_info->subimage_range = (SUB_IMAGE *)calloc( coding_info->subimg_nbr, sizeof(SUB_IMAGE));
	coding_info->error = (double **)calloc(coding_info->subimg_nbr, sizeof(double*));
	coding_info->coding_result = (int **)calloc(coding_info->subimg_nbr, sizeof(int*));
      	
      	for (i=0; i<coding_info->subimg_nbr; i++)
      	 {	
       		fread(& (coding_info->subimage_range[i].bands_num),sizeof(int),1,cdbkfile);
       		fread(& (coding_info->subimage_range[i].start_row),sizeof(int),1,cdbkfile);
       		fread(& (coding_info->subimage_range[i].start_col),sizeof(int),1,cdbkfile);
       		fread(& (coding_info->subimage_range[i].end_row),sizeof(int),1,cdbkfile);
       		fread(& (coding_info->subimage_range[i].end_col),sizeof(int),1,cdbkfile);

     		fread(& (coding_info->row_vector[i]),sizeof(int),1,cdbkfile);
      		fread(& (coding_info->col_vector[i]),sizeof(int),1,cdbkfile);
 		fread(& (coding_info->total_entry[i]),sizeof(int),1,cdbkfile);
      		fread(& (coding_info->error_threshold[i]),sizeof(float),1,cdbkfile);
      		
	   	coding_info->total_vector[i] = ceil(((float)(coding_info->subimage_range[i].end_row - coding_info->subimage_range[i].start_row+1)/(float)coding_info->row_vector[i]));
     		coding_info->total_vector[i] *= ceil((float)(coding_info->subimage_range[i].end_col - coding_info->subimage_range[i].start_col+1)/(float)coding_info->col_vector[i]);
     		if (!coding_info->color_processed)
     		   {	coding_info->error[i] = (double *)calloc(coding_info->total_vector[i]*coding_info->color_band, sizeof(double));
     			coding_info->coding_result[i] = (int *)calloc(coding_info->total_vector[i]*coding_info->color_band, sizeof(int));
     		   }
     		else
     		   {	coding_info->error[i] = (double *)calloc(coding_info->total_vector[i], sizeof(double));
     			coding_info->coding_result[i] = (int *)calloc(coding_info->total_vector[i], sizeof(int));
     		   }
      		
      		move = coding_info->total_entry[i] * coding_info->row_vector[i] * coding_info->col_vector[i];
      		switch (coding_info->data_type)
      		{
      		case CVIP_BYTE:
      			move *= sizeof (byte); break;
      		case CVIP_SHORT:
      			move *= sizeof (short); break;
      		case CVIP_INTEGER:
      			move *= sizeof (int); break;
      		case CVIP_FLOAT:
      			move *= sizeof (float); break;
      		case CVIP_DOUBLE:
      			move *= sizeof (double); break;
      		}
      			
      		fseek(cdbkfile, move, 1 /*SEEK_CUR*/) ;

      	 }/* end of for loop*/
	fclose(cdbkfile);
//	free(cdbkfile);
	return 1;      
      }/*end of get_info_from_codebook_file()*/
      

/************************************************************************
	write_to_disk( VQ_INFO *vq_info )
	this function uses the vq_info, which contains the compressed result and
	all the infornation, to save into temp_file, cdbook_file.
	if u want to change the temp_file format or cdbook_format, change this part.
	these sub functions are called:
		WriteHeader
		WriteCodebookHeader
		WriteCodebook
		WriteVectors()
************************************************************************/	
int	write_to_disk( VQ_INFO *vq_info, VECTOR_LST   **cdbook )
{
	FILE	*temp_file=NULL, *cdbookfile=NULL;
    unsigned int	bits_used;
    int	subImg;
    if (!(temp_file = fopen(vq_info->temp_file, "wb")))
    {	
		fprintf(stderr,"\nopen temp_file failed");
     	return 0;
    }
     	 
    /*write the header part of temp_file*/  
	/*	fprintf(stderr,"begin to WriteHeader\n"); */    	
    WriteHeader(vq_info, temp_file);
     	
     	
	/*write the header part of codebook*/  
	if  (vq_info->cdbook_in_file)
	{	
		/*	fprintf(stderr,"begin to WriteCodebookHeader(temp_file, vq_info)\n"); */    	
	 	WriteCodebookHeader(temp_file, vq_info);}
	else
	{ 
		/*	fprintf(stderr,"begin to WriteCodebookHeader(cdbookfile, vq_info)\n"); */    	
     	if (!( cdbookfile = fopen(vq_info->cdbook_file, "wb")))
     	{
			fprintf(stderr,"\nopen cdbook_file failed");
     		return 0;
     	 }
     	 WriteCodebookHeader(cdbookfile, vq_info);
    }
     
	for (subImg=0; subImg<vq_info->subimg_nbr; subImg++)
	{
		if  (vq_info->cdbook_in_file)
	 	{
			WriteCodebook (temp_file, cdbook[subImg], vq_info, subImg);
	 	    /*free_codebooks(cdbook, 1, vq_info->subimg_nbr);*/
		}
		else
	 	{
	 	    WriteCodebook (cdbookfile, cdbook[subImg], vq_info, subImg);
			/*	fprintf(stderr,"WriteCodebook ok\n");  */   	
	 	}
    }

	if  (cdbookfile)
	{
		fclose(cdbookfile);
	}
     	 
	/*	fprintf(stderr,"begin to WriteVectors()\n");*/     	
	for (subImg=0; subImg<vq_info->subimg_nbr; subImg++)
	{
		bits_used = ceil(log(vq_info->total_entry[subImg])/log(2.0));
	 	
	    switch (vq_info->color_processed)
	    {
	 	case	1:
	 		WriteVectors(	vq_info->coding_result[subImg], (vq_info->total_vector[subImg]), bits_used, temp_file);
      		break;
	 	case	0:
	 		WriteVectors(	vq_info->coding_result[subImg],
      				(vq_info->total_vector[subImg])*(vq_info->color_band),
      				bits_used, temp_file);
      		break;
		}
	}
	fclose(temp_file);
	/* xchen comments out those two moron lines */
	/* free(temp_file); */
	/* free(cdbookfile); */
	return 	1;     
}/*end of write_to_disk( )*/
/*****************************************************************************************************************/     
/*****************************************************************************************************************/
     

      
