/*****************************************************************************/
/*                             
    ======================================================================
    Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
    ======================================================================

                  LOSSLESS HUFFMAN CODING ALGORITHM
                  ________ _______ ______ _________                                                                             */
/*                                                                           */
/*                                                                           */
/*          DEVELOPER: Mark Heffron                                          */
/*          PORTED BY: Muthu Kumar                                           */
/*                                                                           */ 
/*          DATE: 28 July 1992 - original                                    */
/*          PORTING DATE   24 January 1994                                   */
/*                                                                           */
/*          FUNCTION:  This program reads the infile as a binary             */
/*          file and builds a probability table for the symbols.             */
/*          From the probability array, a Huffman tree is built.             */
/*          The tree is used to encode the infile.  Decoding is              */
/*          done by building a Huffman tree from the probability             */
/*          array contained in infile.  The tree is used to decode           */
/*          the infile.                                                      */
/*                                                                           */
/*          FILE STRUCTURE:  The output file structure is:                   */
/*                           4 bytes - original file size                    */
/*                           1 byte  - number of leaves                      */
/*                          x5 bytes - probability array                     */
/*                           n bytes - encoded file                          */
/*                                                                           */
/*                      where x is the number of symbols and                 */
/*                            n is the number of encoded words               */
/* ____________________________________________________________________________
The 'huffman' main function provides sub menu for Huffman coding and decoding
Algorithms. Two functions are incorporated in the submenu via huf_compress() and huf_decompress(). These functions perform compression and decompression respectively. The main function 'hufman' takes pointer to the input image as the arguments.*/ 
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "huffman.h"

static char out8;  
static int code_count8=0;
static int in_8bits;  
static int bit_count8=8;   
struct bin_tree *root;


typedef unsigned long int COUNTER;  /* defines variable type for symbol counting */

static float outbit(FILE *output, int bit);
static void buildtree();

/* ------------------------ Global Declarations -----------------------*/
struct bin_tree
{
	unsigned char ch;	/* character value */
	COUNTER cnt;		/* character frequency */
	struct bin_tree *parent;/* pointer to parent node */
	struct bin_tree *right; /* pointer to right child node */
	struct bin_tree *left;  /* pointer to left child node */
};
struct bin_tree b_tree[];       /* binary tree for Huffman encoding */
COUNTER bytes_out = 0;          /* number of bytes written to output file */

extern char temp_dir[100];
extern char *Cmpr_Name[];


/*Image* huffman(Image *input_Image)
{

   char select[6], *filename=NULL, outputfile[]="temp.ppm\0"; 
   int i, j, bands, cols, rows, count = 0;
   byte **image_array, **red_plane, **green_plane, **blue_plane, **error_array;
   IMAGE_FORMAT image;
   COLOR_FORMAT color;
   CVIP_TYPE data_type;
   FORMAT data_format;
   Image *decodImage;

   rows = input_Image->image_ptr[0]->rows;
   cols = input_Image->image_ptr[0]->cols; 
   bands = input_Image->bands;
   image_array = (byte**) input_Image->image_ptr[0]->rptr;	
   filename = huf_compress(rows,cols,bands,input_Image);
   if(filename == NULL)
	return NULL;
   decodImage = huf_decompress(filename);
   free(filename);
   return decodImage;
     
}*/


/******************************************************************************
                   Name: huf_compress
          Expanded Name: Huffman Coding
             Parameters: int rows : height of the input image
                         int cols : width of the input image
                         byte** image_array : pointer to the input image array
                Returns: Image Pointer
            Description: This function is called from the main function 
                         huffman(..). For more description read the bottom of
                         this header.  
            Diagnostics: All filenames should be entered without extensions
    Initial Coding Date: 7/28/92
           Porting Date: 1/24/94
             References: None
              Author(s): Mark Heffron
                         Southern Illinois University @ Edwardsville ________________________________________________________________________________
This function is called from the main function huffman(..). It takes four parameters namely the height, width,no of bands of the input image and pointer to the input image array. When this routine is in execution it asks the user for the file name to which the compressed image is to be stored. The user has to enter the filename with no extension. The routine automatically appends the extension to the file name.
     The routine compacts the input image using huffman encoding. It first reads the input image, build the array table with the symbol and frequency of occurence. Binary tree is built from the array table. Using the binary tree that was built each symbol(greylevel value ) is encoded. The encoded data is written in a binary file. At the end of the compression, this routine automatically writes to the screen the compression ratio. *******************************************************************************/
/*char* huf_compress(int rows, int cols, int bands, Image *input) */
int huf_compress(Image *inputImage, char *filename)
  {
    byte **image_array;
    FILE *file_in, *file_out; 
    int symbol,x,y,
		rows, cols, bands;              
    unsigned char code_out;  
    COUNTER bytectr = 0;     
    int freqctr = 0;          
    time_t start, end;        
    float com_ratio;          
    int temp,dum,leng,no_band;                 
    int mess = 0;             
    float f_out,f_ctr;
    struct stat s_buf;
    long counter;

	 bands = getNoOfBands_Image(inputImage);
	 rows =  getNoOfRows_Image(inputImage);
	 cols =  getNoOfCols_Image(inputImage);

    if ((file_out= fopen(filename, "w+b"))==NULL)
      {
        printf("\n\nError opening the file\n");
	if (inputImage) delete_Image(inputImage);
        return -1;
      } 
     fputc(104,file_out);
     fputc(117,file_out);
     fputc(102,file_out);
     fwrite(&rows,sizeof(rows), 1,file_out);
     fwrite(&cols,sizeof(cols), 1,file_out);
     fwrite(&bands,sizeof(bands), 1,file_out);                
     start = time(NULL);
     for(no_band = 0;no_band < bands; no_band++){
	image_array = getData_Image(inputImage,no_band);
        freqctr=mess=0;bit_count8=8;code_count8=0;
     for (dum=0; dum <512; dum++)
       {
         b_tree[dum].ch = NULL;
         b_tree[dum].cnt =0;
         b_tree[dum].parent=0;
         b_tree[dum].left=0;
         b_tree[dum].right=0;
       }
     for(y=0; y<rows; y++)
       for(x=0;x<cols;x++) 		                  
         { 
           symbol=image_array[y][x];
           symbol &= 255;    
	   if (b_tree[symbol].cnt == 0) 
             {
	       freqctr++;        
	       b_tree[symbol].ch = symbol; 
             }
	   b_tree[symbol].cnt++;  
           bytectr++;    
         }
     bytes_out = sizeof bytectr; 
     fwrite(&bytectr, sizeof bytectr, 1, file_out);
     bytes_out = bytes_out + sizeof freqctr;
     fwrite(&freqctr, sizeof freqctr, 1, file_out);
     for (mess = 0; mess<256; mess++)
       {
	 if(b_tree[mess].cnt > 0)  
	   {
	     fwrite(&b_tree[mess].ch, sizeof(char), 1, file_out);
	     bytes_out = bytes_out + sizeof(char); 
	     fwrite(&b_tree[mess].cnt, sizeof(COUNTER), 1, file_out);
	     bytes_out = bytes_out + sizeof(COUNTER); 
	   }
	} 		
      buildtree();		
      for(y=0; y<rows; y++)
        for(x=0;x<cols;x++) 
	  {
            symbol=image_array[y][x];
	    mark_compress(file_out, b_tree + (symbol & 255), NULL);
          }
  
      outbit(file_out, -1); 
      }   
    /*fsync(fileno(file_out));*/
	fflush(file_out);
	fclose(file_out);
    if(stat(filename,&s_buf)==0){
	counter =(long)s_buf.st_size;
 printf("\nThe original raw data occupies %ld bytes!!", rows*cols*bands);
 printf("\nThe compressed data occupies %ld bytes!!",counter );
 printf("\nCompression ratio 1 : %f\n", (rows*cols*bands)/(float)counter);
    }

    if (inputImage) delete_Image(inputImage);
      return 0;
  }
	



/******************************************************************************
                   Name: huf_decompress
          Expanded Name: Huffman Decoding
             Parameters: char *filename : compressed filename
                Returns: Image Pointer
            Description: This function is called from the main function
                         huffman(..). For more description read the bottom of
                         this header.  
            Diagnostics: All filenames should be entered without extensions
    Initial Coding Date: 7/28/92
           Porting Date: 1/24/94
             References: None
              Author(s): Mark Heffron
                         Southern Illinois University @ Edwardsville ________________________________________________________________________________
This function is called from the main function huffman(..). It takes single parameter namely the compressed filename. This routine decode the original image from the encoded file. It reads the original file size, symbol frequency from the encoded file. A binary tree is built from the probability table stored in the encoded file. The original image is recovered by using the binary tree.   when decompression is completed it returns the pointer to the decoded image.
*******************************************************************************/
Image *huf_decompress(char *filename)    
  {
    FILE *file_in; 
    Image *decodeImage;


    if((file_in = fopen(filename, "rb")) == '\0')
      {
        printf("\nError opening the file\n");
        return NULL;
      } 
    decodeImage = huf_decompression(file_in);
    fclose(file_in);

    return decodeImage;
}


Image *huf_decompression(FILE *file_in){
    FILE *file_out; 
    Image *decodeImage;
    byte **image_arra; 
    int symbol,rows=512,cols=512,bands=1,x,y,leng,no_band;               
    unsigned char code_out;   
    COUNTER bytectr = 0;     
    int freqctr = 0;          
    time_t start, end;        
    float com_ratio;          
    int temp,dum;                 
    int mess = 0, freeit=0;  
    long int ncou;           
    float f_out,f_ctr;
    char aa,bb,cc,ccc,ch[]=".huf";      


    aa=fgetc(file_in);
    bb=fgetc(file_in);
    cc=fgetc(file_in);      
    if(aa!= 'h' || bb != 'u' || cc != 'f')
      {
        printf("\n\n\t\tInvalid File format\n");
        exit(0);
      }
    fread(&rows,sizeof(rows), 1,file_in);
    fread(&cols,sizeof(cols), 1,file_in); 
    fread(&bands,sizeof(bands), 1,file_in);
    if(bands==1)
       decodeImage=new_Image(PGM,GRAY_SCALE,bands,rows,cols,CVIP_BYTE,REAL);
    else
       decodeImage=new_Image(PPM,RGB,bands,rows,cols,CVIP_BYTE,REAL);
    start = time(NULL);  
    for(no_band=0;no_band < bands;no_band++){
        bytectr=0;freqctr=0;mess=0;freeit=0;
    image_arra=getData_Image(decodeImage,no_band);
    fread(&bytectr, sizeof bytectr, 1, file_in);
    fread(&freqctr, sizeof freqctr, 1, file_in);
    for (dum=0; dum <512; dum++)
      {
        b_tree[dum].ch = NULL;
        b_tree[dum].cnt =0;
        b_tree[dum].parent=0;
        b_tree[dum].left=0;
        b_tree[dum].right=0;
      }
    while (freqctr--)
      {
        fread(&code_out, sizeof(char), 1, file_in);
	b_tree[code_out].ch = code_out;
	fread(&b_tree[code_out].cnt, sizeof(COUNTER), 1, file_in);
       } 
     code_count8 = 0; bit_count8 = 8;
     buildtree();
     mess = 0;   
     y=0;x=0;ncou=0;              
     for(y=0;y<rows; y++)
       for(x=0;x<cols;x++)
         {               
           symbol = decompress(file_in,root);  
	   image_arra[y][x]=symbol;                                                    
         } 
     root=0;
     }    
     end = time(NULL); 
     decodeImage->image_format = HUF;
     return decodeImage;

}


/* ----------------------- Function INBIT ----------------------- */
/* ------------- read a bit at a time from a file --------------- */
/*               reads a symbol from the input file and           */
/*               masks the most significant bit.  returns         */
/*               the masked bit and shifts the symbol to          */
/*               the left.  after all 8 bits have been returned   */
/*               read the next symbol                             */
/* -------------------------------------------------------------- */

static int inbit(FILE *input)
{
	int symbol_bit;  

	if (bit_count8 == 8)  
	{
		in_8bits = fgetc(input);  
		bit_count8 = 0;  
	}
	symbol_bit = in_8bits & 0x80; 
	bit_count8++;            
	in_8bits <<= 1;          
	return(symbol_bit);      
}


/* ------------------- Function DECOMPRESS ----------------------- */
/* ------------- decompress file bits into characters ------------ */
/*               starts at the root node and traces back           */
/*               to a leaf.  the symbol at leaf is returned        */
/* --------------------------------------------------------------- */
static int decompress(FILE *input, struct bin_tree *h)
{      
	while (h->right != NULL)
		if (inbit(input)) 
			h = h->left; 
		else
			h = h->right; 
	return h->ch;   
}


/* --------------------- Function COMPRESS --------------------------- */
/* ---------- mark_compress a character value into a bit stream ----------- */
/*            starts at the leaf and works to the root node            */
/*            preceeding right equals 0 preceeding left equals         */
/*            1                                                        */
/* ------------------------------------------------------------------- */
static mark_compress(FILE *output, struct bin_tree *h, struct bin_tree *child)
{
	if (h -> parent != NULL) 
		mark_compress(output, h -> parent, h);
	if (child)
	{
		if (child == h -> right)
		{
			outbit(output,0); /* preceeding right */
		}
		else if (child == h -> left)
		{
			outbit(output,1); /* preceeding left */
		}
	}
	return;
}



/* --------------------- Function OUTBIT ---------------------------- */
/* ----------- collect and write bits to the  output file ----------- */
/*             shift out8 to the left by one.  OR this with           */
/*             the bit passed from MAIN.  once 8 bits have            */
/*             passed, write out8 to the output file.  if             */
/*             bit = -1, clear out8 to the output file                */
/* ------------------------------------------------------------------ */
static float outbit(FILE *output, int bit)
{
	int j;   

	
	if (bit == -1 && code_count8 != 0)
	{
		for (j=code_count8; j<8; j++)
		{
			out8 = (out8<<1) | 0;
		}
		fputc(out8,output);
		bytes_out++; 
		return(bytes_out);
	}

	if (code_count8 == 8)  
	{
		fputc(out8, output);  
		code_count8 = 0;      
		bytes_out++;          
	}
	out8 = (out8 << 1) | bit;
	code_count8++;  
	return(bytes_out);

}

struct bin_tree b_tree[512];

static void buildtree(void)
{
	int treect = 256;
	int i;
	while (1)
	{
		struct bin_tree *h1 = NULL, *h2 = NULL;
		
		for (i=0; i < treect; i++)
		{
			if(b_tree+i != h1)
			{
				if (b_tree[i].cnt > 0 && b_tree[i].parent == NULL)
				{
					if (h1 == NULL || b_tree[i].cnt < h1 -> cnt)
					{
						if (h2 == NULL || h1 -> cnt < h2 -> cnt)
							h2 = h1;
						h1 = b_tree + i;
					}
					else if (h2 == NULL || b_tree[i].cnt < h2 -> cnt)
						h2 = b_tree + i;
				}
			}
		}
		if(h2 == NULL)
			{
				root = h1;
				break;
			}
		h1 -> parent = b_tree + treect;
		h2 -> parent = b_tree + treect;
		b_tree[treect].cnt = h1 -> cnt + h2 -> cnt;
		b_tree[treect].right = h1;
		b_tree[treect].left = h2;
		treect++;
	}
}

