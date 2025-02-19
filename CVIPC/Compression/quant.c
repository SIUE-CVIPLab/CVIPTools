/*****************************************************************************
 * ======================================================================    *
 * Image Processing/Computer Vision Tool Project - Dr. Scott Umbaugh SIUE    *
 * ======================================================================    *
 *                                                                           *
 * ROUTINE/FUNCTION: quantization.c                                          *                    
 *                                                                           *
 *                                                                           *
 *              DESCRIPTION: This program will quantize the image with       *
 *			     user defined quantization table.                *
 *                                                                           *                                                                          
 *                   AUTHOR: Ramesh Reddy                                    *
 *                                                                           *
 *            RELATED FILES: dct.c                                           *   
 *                                                                           *                                                             
 *              CODING DATE: 11/29/92                                        *
 *  LAST MODIFICATIONS MADE: 1/18/93                                         *
 *                                                                           *
 *  VARIABLES PASSED TO YOUR_FUNCTION:					     *
 *        input_Image - An image structure with necessary info. about the    *
 *        image as well as a **ptr to the image data. (see image.h)          *
 *        and a pointer to the quantization table.                           *               
 *                                                                           *
 *  RETURNED VARIABLES:                                                      *
 *      Quantization() -  returns the same image structure that was          *
 *         passed to it but with quantized image data content.               *                                                                       
 *                                                                           *
 *****************************************************************************/
 
#include <stdio.h>
#include <math.h>
#include "CVIPimage.h"

/*   
     quant_setup: This routine takes a poiter to the 8X8 block of integers
     as an input argument and returns the same pointer with quantization 
     table values in it.  User has a choice to select the contents of that
     table.
*/

void quant_setup(int quant[][8])
{
     
    int       rows,cols,x,y,z,color,i,j,k,ent,table;
    const char fn[] = {"Quantization setup"};
    
   /*   these two are supported by jpeg group   */
   
    static int  Luminance[8][8]   = {      16,  11,  10,  16,  24,  40,  51,  61,
    				           12,  12,  14,  19,  26,  58,  60,  55,
				           14,  13,  16,  24,  40,  57,  69,  56,
				           14,  17,  22,  29,  51,  87,  80,  62,
					   18,  22,  37,  56,  68,  109, 103, 77,
					   24,  35,  55,  64,  81,  104, 113, 92,
					   49,  64,  78,  87,  103, 121, 120,101,
					   72,  92,  95,  98,  112, 100, 103, 99      };
					   
    static int  Chrominance[8][8] = {      17,  18,  24,  47,  99,  99,  99,  99,
    					   18,  21,  26,  66,  99,  99,  99,  99,
					   24,  26,  56,  99,  99,  99,  99,  99,
					   47,  66,  99,  99,  99,  99,  99,  99,
					   99,  99,  99,  99,  99,  99,  99,  99,
					   99,  99,  99,  99,  99,  99,  99,  99,
					   99,  99,  99,  99,  99,  99,  99,  99,
					   99,  99,  99,  99,  99,  99,  99,  99      };
	   
     
        
    do{
       fputs("\nChoose the Quantization Table:\n\n",stdout);
       fputs("    1)  Luminance Table         \n",stdout);
       fputs("    2)  Chrominance Table       \n",stdout);
       fputs("    3)  User Defined Table (Your Table)     \n\n",stdout);
       fputs("The First two tables are supported by JPEG's Group\n",stdout);
       fputs("Enter the Table #: ",stdout);
       table = get_uint(10, 1 , 3);
     } while( table <= 0 || table > 3);
     
    if (table == 1) memcpy(quant,Luminance,sizeof(Luminance));
    else if ( table == 2 )memcpy(quant,Chrominance, sizeof(Chrominance)); 
    if ( table == 3 ){
       fputs( "\nStart Entering the Your Quantization Table(0 to 255):\n",stdout);
       for ( x = 0; x < 8; x++){
         for  ( y = 0; y < 8; y++){
	    ent = (unsigned int) get_uint(10, 2, 255 );
	         quant[x][y] = ent;
	 }
       }
    }
}					/*   end of quant setup   */
    
/*
  	QUANTIZATION:  this routine takes a pointer to the input image structure and 
        pointer to the 8x8 block whre quantization table is stored. This returns a 
        quantized image pointer.
*/
   
Image *QUANTIZATION( input_Image, quant )
Image *input_Image;
int *quant;
 {
    int       rows,cols,x,y,z,color,i,j,k,ent,table,diff;
    const char fn[] = {"Quantization"};
    float     offset,total;
     
    rows  = (int) input_Image->image_ptr[0]->rows;  /*  # of rows in an image */
    cols  = (int) input_Image->image_ptr[0]->cols;  /* # of cols in an image  */
    if (input_Image->bands == 3) color = 3; else color = 1; /* is it color image ?  */
    
    puts("Forward quantization in Progress");
  
    for ( k = 0; k < color; k++){   /* quantizing the image   */
      x = 0; y = 0; 
      while( x < rows ){
        y = 0;
        while( y < cols){
	  for ( i = 0; i < 8; i++){
	    for ( j = 0; j < 8; j++){
	          if ( (((short**)input_Image->image_ptr[k]->rptr)[(x+i)][(y+j)]) != 0 ){
	            total  = (((short**)input_Image->image_ptr[k]->rptr)[(x+i)][(y+j)]) / (*(quant + (i*8)+j)) ;
                    diff   = (short)total;
		    offset = total - diff ;
		    if ( offset >= 0.5 ) 
		       ((short **)input_Image->image_ptr[k]->rptr)[(x+i)][(y+j)] = diff + 1;
		    else
		       ((short **)input_Image->image_ptr[k]->rptr)[(x+i)][(y+j)]  = diff;
		  }
	    } 
	  }
       y+=8;		 
       }
      x+=8; 
     }          /*   end of while   */
   }            /*   end of for      */
    return input_Image;
 }   /* end of quantization    */

/*   
        INV QUANTIZATION:  this routine takes a pointer to the quantizedinput image 
        structure and pointer to the 8x8 block whre quantization table is stored. This 
	returns a dequantized image pointer.
	
*/

   
Image *INV_QUANTIZATION( input_Image, quant )
Image *input_Image;
int *quant;
 {
    int       rows,cols,x,y,z,color,i,j,k,ent,table,diff;
    const char fn[] = {"Inverse Quantization"};
    float      quant1[8][8],offset,total;
           
    rows  = (int) input_Image->image_ptr[0]->rows;    /* # of rows in the image  */
    cols  = (int) input_Image->image_ptr[0]->cols;    /* # of cols in the image  */
    if (input_Image->bands == 3) color = 3; else color = 1;  /* is it color ? */
    puts("Inverse quantization in Progress");
  
    for ( k = 0; k < color; k++){  /* de quantizing taking place  */
      x = 0; y = 0;
      while( x < rows ){
        y = 0;
        while( y < cols){
	  for ( i = 0; i < 8; i++){
	    for ( j = 0; j < 8; j++){
	          if ( (((short**)input_Image->image_ptr[k]->rptr)[(x+i)][(y+j)]) != 0 ){
	  	    total  = (((short**)input_Image->image_ptr[k]->rptr)[(x+i)][(y+j)]) * (*(quant + (i*8)+j));
                    diff   = (short)total;
		    offset = total - diff ;
		    if ( offset >= 0.5 ) 
		       ((short **)input_Image->image_ptr[k]->rptr)[(x+i)][(y+j)] = diff + 1;
		    else
		       ((short **)input_Image->image_ptr[k]->rptr)[(x+i)][(y+j)]  = diff;
		 }
	    } 
	  }
       y+=8;		 
       }
      x+=8; 
     }       				   /*   end of while   */
   }          				  /*   end of for      */
    return input_Image;
 }					  /*   end of Inverse Quantization   */

