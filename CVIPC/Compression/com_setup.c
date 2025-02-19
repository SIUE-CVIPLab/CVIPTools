/*****************************************************************************
 * ======================================================================    *
 * Image Processing/Computer Vision Tool Project - Dr. Scott Umbaugh SIUE    *
 * ======================================================================    *
 *                                                                           *
 * ROUTINE/FUNCTION: Compress_setup, Decompress_setup                        *                    
 *                                                                           *
 *                                                                           *
 *              DESCRIPTION: This module will calculate the dc difference    *
 *                            of the between blocks   			     *
 *                                                                           *                                                                          
 *                   AUTHOR: Ramesh Reddy                                    *
 *                                                                           *
 *            RELATED FILES: huffcompress.c huffdecompress.c                 *   
 *                                                                           *                                                             
 *              CODING DATE: 1/10/93                                         *
 *  LAST MODIFICATIONS MADE: 1/18/93                                         *
 *                                                                           *
 *  VARIABLES PASSED TO YOUR_FUNCTION:					     *
 *        input_Image - An image structure with necessary info. about the    *
 *        image as well as a **ptr to the image data. (see image.h)          *
 *                                                                           *
 *  RETURNED VARIABLES:                                                      *
 *        dcpred() -  returns the same image structure that was              *
 *         passed to it but with new image data content.                     *                                                                       
 *                                                                           *
 *****************************************************************************/
#include <stdio.h>
#include <math.h>
#include "CVIPimage.h"
#include <string.h>

/*  
	Compress_setup : This is setup routine for the compress routine. it takes the 
	image pointer and filename pointer and quanttization table pointer as inputs.
	it up dates the filename pointer to under which name the compressed image should
	be saved. and also most importtent thing is it saves the quantization contents
	image structure properties in a 80 bytes header so that it can be used by the 
	de compression program at later time for these details.
*/

void Compress_setup( inImage,filename, inputfile,quant )
Image *inImage;
char  *inputfile,*filename;
int *quant;
{
   char *pc;
   FILE *outfile;
   unsigned char packet[80];
   int i;
   
   strcpy( filename, inputfile);   /*  file name manipulation  */
   pc = filename;
   while( *pc != '.')
      pc++;
   *pc = '\0';
   strcat(filename, ".JPEG");     /* attach .JPEG subscript  */
   
    packet[0]  = (char)inImage->image_format;     /*  pack the data   */
   packet[1]  = (char)inImage->color_space;
   packet[2]  = (char)inImage->bands;
   packet[3]  = (char)(inImage->image_ptr[0])->data_type;
   packet[4]  = (char)(inImage->image_ptr[0])->data_format;
   packet[5]  = (char) (   (inImage->image_ptr[0])->rows >> 24 );   /*  pack rows #  */
   packet[6]  = (char) ( ( (inImage->image_ptr[0])->rows << 8 ) >> 24 );
   packet[7]  = (char) ( ( (inImage->image_ptr[0])->rows << 16 ) >> 24 );
   packet[8]  = (char) ( ( (inImage->image_ptr[0])->rows << 24 ) >> 24 );
   packet[9]  = (char) (   (inImage->image_ptr[0])->cols >> 24 );      /* pack cols #  */
   packet[10] = (char) ( ( (inImage->image_ptr[0])->cols << 8 ) >> 24 );
   packet[11] = (char) ( ( (inImage->image_ptr[0])->cols << 16 ) >> 24 );
   packet[12] = (char) ( ( (inImage->image_ptr[0])->cols << 24 ) >> 24 );
   
   for ( i = 13; i < 77 ; i++ )   /* pack quantization table  */
      packet[i] = (char) *quant++;
   
   packet[77] = 'E';   /*  for security pupose only  */
   packet[78] = 'N';
   packet[79] = 'D';
   
	#ifndef WIN32
   outfile = fopen( filename, "w" );
	#else
   outfile = fopen( filename, "wb" );
	#endif
   if ( outfile  == NULL )
       printf("Couldn't open %s for writing header.\n", filename);
       
   fwrite ( packet, sizeof(char), 80, outfile);   /*  write header to the file */
   
 fclose(outfile);    /* close the file  */
 
}  /*  end compress setup   */

/*
	De_Compress_setup:  This takes a pointer to a char array and a pointer to a 8x8 int
	array as input arguments.  What this routine basically does is it opens the file which 
	supplied to it. and unpackes the header information of that file whiach contains image
	properties and quantization table. and updates the quantization pointer with header 
	contents of quantization table, and also allocates memory for the output image with
	image properties which it got from the header of the file. finally it returns a pointer
	to that created image.
*/

Image *De_Compress_setup( filename,quant )
char *filename;
int *quant;
{
   Image *output_Image;
   FILE *infile;
   unsigned char packet[80];
   IMAGE_FORMAT format;
   COLOR_FORMAT color;
   CVIP_TYPE  data_type;
   FORMAT data_format;
   unsigned int rows, cols, bands,i,p5,p6,p7,p8,p9,p12,p10,p11;
   
	#ifndef WIN32
   infile = fopen( filename, "r" );   /* open the file  */
	#else
   infile = fopen( filename, "rb" );   /* open the file  */
	#endif
   if ( infile  == NULL )
       printf("Couldn't open %s for writing header.\n", filename);
       
   fread(packet, sizeof(char), 80, infile);  /*  read the header packet  */
   
   format      =    (IMAGE_FORMAT)packet[0];  /* unpack info about iamge  */
   color       =    (COLOR_FORMAT)packet[1];
   bands       =    (int) packet[2];
   data_type   =    (CVIP_TYPE)packet[3];
   data_format =    (FORMAT)packet[4];
   p5       =       (int)packet[5];  /* unpack rows */
   p6          =    (int)packet[6]; 
   p7          =    (int)packet[7]; 
   p8          =    (int)packet[8]; 
   p5 = (p5 << 8 )| p6 ;   
   p5 = (p5 << 8) | p7 ;   
   p5 = (p5 << 8) | p8;   
   rows = p5;
   cols =    (int)packet[9];    /* unpack cols  */
   p10         = (int)packet[10];
   p11         = (int)packet[11];
   p12         = (int)packet[12];
   cols = (cols << 8 )| p10;
   cols = (cols << 8) | p11;
   cols = (cols << 8) | p12;
      
   for ( i = 13; i < 77; i++)    /*  unpack quantization table   */
     (*(quant + (i - 13) )) = (int)packet[i];
    
   if ( packet[77] != 'E' && packet[78] != 'N' && packet[79] != 'D' )  /* security  */
      printf("Ooops Packet got messed up\n");
   
   fclose(infile);
   fflush(stdout);
   output_Image = (Image *)image_allocate(format,color, bands,rows,cols, data_type, data_format); /*create image*/
   return (output_Image); /* return the created image  */
 }   /*  end of de compress setup    */
 
 /*  end of comsetup file  */

 
