/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: zvl.c
*           Description: adaptive lemple-ziv coding
*         Related Files: 
*   Initial Coding Date: Tue Sep 24 19:17:54 CDT 1996
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): MArk Heffrom, Kun Luo 
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1996 SIUE - by Scott Umbaugh and Kun Luo.
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
** $Log: zvl.c,v $
** Revision 1.13  2001/04/04 05:39:07  ycheng
** revised errors so that it works under Linux.
**
** Revision 1.12  1997/07/16 21:42:27  wzheng
** bug on linux
**
** Revision 1.11  1997/06/04 17:06:23  wzheng
** memory leak
**
** Revision 1.10  1997/05/16 23:13:04  smakam
** Commented out fsync and added another alternative
**
** Revision 1.9  1997/05/05 18:33:15  yawei
** fixed the compress bug
**
** Revision 1.8  1997/03/08 00:56:20  yawei
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
** Revision 1.7  1997/01/15 17:15:15  yawei
** Global Change:  IMAGE ==> Image
**
 * Revision 1.6  1996/12/04  21:10:21  yawei
 * char *lzw_compression(Image *inputImage)
 *  ==>int zvl_compress(Image *inputImage, char *filename)
 *  Image *lzw_decompression(char *filename)
 *  ==>Image *zvl_decompress(char *filename)
 *
 *  Image *lzw_decompress(FILE *input)
 *  ==>Image *zvl_decompression(FILE *input)
 *
 * Revision 1.5  1996/11/20  15:22:44  yawei
 * Changed hard coded extension name to global array element
 *
 * Revision 1.4  1996/09/25  00:27:58  sumbaug
 * corrected header on file (author)
 *
 * Revision 1.3  1996/09/25  00:18:06  sumbaug
 * added CVIPtools header to the file
 *
*
****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "CVIPdef.h"
#include "CVIPimage.h"
#include "CVIPcompress.h"
/* ------------------------ Global Declarations -----------------------*/

#define INIT_BITS 9
#define MAX_BITS 14
#define HASHING_SHIFT MAX_BITS - 8

#if MAX_BITS == 14     /* Set the table size. Must be a prime number */
#define TABLE_SIZE 18041
#elif MAX_BITS == 13
#define TABLE_SIZE 9029
#else
#define TABLE_SIZE 5021
#endif

#define CLEAR_TABLE 256 /* Code to clear the string table */
#define TERMINATOR  257 /* Marks EOF condition, instead of MAX_VALUE */
#define FIRST_CODE  258 /* First available code for code_vaule table */
#define CHECK_TIME  100 /* Check comp ratio every CHECK_TIME chars input */

#define MAXVAL(n) (( 1 <<(n)) -1)  /* max_value formual macro */


static void output_code(FILE *output, unsigned int code);
static unsigned input_code(FILE *input);
static int find_match(int hash_prefix, unsigned int hash_symbol);
static char *decode_string(unsigned char *buffer, unsigned int code);

int *code_value;       		/* this is the code value array */
unsigned int *prefix_code;	/* this array holds the prefix codes */
unsigned char *append_symbol; /* this array holds the append symbols */
unsigned char decode_stack[4000];  /* this array holds the decoded string */
int num_bits = INIT_BITS;  	/* initializes code word to 9 bits */
unsigned long bytes_in=0, bytes_out_zvl=0;
	/* used to monitor compression ratio */
int max_code; 			/* old MAX_CODE */
unsigned long checkpoint=CHECK_TIME;  /* for compression ration monitoring */
int mess = 0;                   /* message display counter */

extern char temp_dir[100];
extern char *Cmpr_Name[];
static int input_bit_count = 0; /*bit counter for the buffer */
static unsigned long input_bit_buffer = 0L; /* buffer for storing the symbols as they */
						    /* are read */
static int output_bit_count = 0; /* number of 8 bit symbols written */
static unsigned long output_bit_buffer = 0L; /* 32 bit buffer */


/*
Image *zvl(Image *inputImage){
    char *filename;
    Image *decodeImage;

    filename = zvl_compress(inputImage);
    if(filename == NULL)
	return NULL;
    decodeImage = zvl_decompress(filename);
    free(filename);
    
    return decodeImage;
}

*/

/* ----------------------- Function COMPACT ------------------------ */
/* --------------- encodes the file using LZW algorithm ------------ */
/*            the first two 9-bit codes have been reserved for       */
/*            communication between the encoder and decoder          */
/* ----------------------------------------------------------------- */

/*char *zvl_compress(Image *inputImage) */
int zvl_compress(Image *inputImage, char *filename) 
{
	byte **image_array;
	short int y,x,rows,cols,bands,no_of_bands;
	long counter;
        FILE *input, *output;
	unsigned int next_code=FIRST_CODE;  /* initializes code word counter to first available location */
	unsigned int symbol;                /* symbol read from input file */
	unsigned int string_code;           /* stores the strings as they are built */
	unsigned int index;                 /* counter for locations of strings */
	int i;                              /* misc variable */
	int ratio_new, ratio_old=100;       /* compaction ratios as percents */
    struct stat s_buf;

	code_value =(int*)calloc(TABLE_SIZE,sizeof(int));
	prefix_code = (unsigned int*)calloc(TABLE_SIZE,sizeof(int));
	append_symbol = (byte*)calloc(TABLE_SIZE,sizeof(byte));
	bytes_in=0; bytes_out_zvl=0;
	num_bits = INIT_BITS;
	checkpoint=CHECK_TIME; 
	mess = 0;
        max_code = MAXVAL(num_bits);
	input_bit_count = 0; 
	input_bit_buffer = 0L; 
	output_bit_count = 0; 
	output_bit_buffer = 0L; 
	for(i=0; i<TABLE_SIZE; i++)
		code_value[i]=-1;  /* initializes table, showing no strings*/
	/* -------------------- encode the input file using LZW algorithm ------------------ */

	if((output = fopen(filename,"w+b"))==NULL){
	    printf("\nError open the file");
	    if (inputImage) delete_Image(inputImage);
	    return -1;
	}
/*  	putc('z',output);
	putc('v',output);
	putc('l',output); */
	fprintf(output, "zvl");
	rows = inputImage->bandP[0]->rows;
	cols = inputImage->bandP[0]->cols;
	no_of_bands = inputImage->bands;
 	fwrite(&rows,sizeof(short int), 1,output);
 	fwrite(&cols,sizeof(short int), 1,output);
 	fwrite(&no_of_bands,sizeof(short int), 1,output);
	for(bands=0;bands<no_of_bands;bands++){
	    image_array = getData_Image(inputImage,bands);
	    for(y=0;y<rows;y++){
		for(x=0;x<cols;x++){			
	if(bands==0&&y==0&&x==0){
	    string_code = image_array[y][x];
	    continue;
	}
	else{ 
   	    symbol = image_array[y][x];
	}
		mess++; /* increments message counter for message display */
		/* ----------------- flashes ENCODING on the display ---------------- */
		++bytes_in;  /* increments number of bytes read */
		index = find_match(string_code,symbol); /* call FIND_MATCH function */
		if (code_value[index] != -1) /* if strings exist, then place the value into the string */
			string_code = code_value[index];
		else
		{
			if (next_code <= max_code) /* violate limit on number of new codes? */
			{
				code_value[index] = next_code++; /* new code for code string and increment */
								 /* to the next code location in the table */
				prefix_code[index] = string_code; /* base code for the new code string */
				append_symbol[index] = symbol;    /* symbol added to base code to form  */
								     /* the new string */
			}

			/* ----------------------- write code words to output file ----------------------- */
			output_code(output,string_code); /* call OUTPUT_CODE function */
			string_code = symbol; /* update string_code */

                        /* --------------------------- is table full? ------------------------------------ */
			/*                if the table is full, increment the code                         */
			/*                word size or clear old strings from the table                    */
			/*                table clearing routine was taken from Dr. Dobb's                 */
			/*                Journal, June 1990.                                              */
			/* ------------------------------------------------------------------------------- */
			if (next_code > max_code)
			{
				if (num_bits < MAX_BITS) /* increment to larger code word if available */
				{
					max_code = MAXVAL(++num_bits);
				}
				else if (bytes_in > checkpoint) /* are we at checkpoint */
				{
					if (num_bits == MAX_BITS > max_code)
					{
						ratio_new = bytes_out_zvl*100/bytes_in; /* new compaction ratio */
						if (ratio_new > ratio_old)   /* has ratio degraded? */
						{
							output_code(output,CLEAR_TABLE); /* YES, flush string table */
							printf("\nCLEARING TABLE");
							printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
							num_bits = INIT_BITS;
							next_code = FIRST_CODE; /* reset to FIRST_CODE */
							/* ----------------- reinitializing variables ------------------ */
							max_code = MAXVAL(num_bits);
							bytes_in = bytes_out_zvl = 0;
							ratio_old = 100;   /* reset compaction ratio */
							for (i=0; i<TABLE_SIZE; i++)  /* clear string table and reinitialize to -1 */
								code_value[i] = -1;
						}
						else     /* NO, then save new compaction ratio */
							ratio_old = ratio_new;
					}
					checkpoint = bytes_in + CHECK_TIME;  /* set new checkpoint */
				}
			}
		}
	}
	}
	}
	/* ----------------------------- house keeping chores ---------------------------------- */
	output_code(output,string_code); /* write the last code word */
	if (next_code == max_code) /* handles special case for bit */
	{
		++num_bits;   /* increments on EOF */
	}

	output_code(output, TERMINATOR);   /* output the end of buffer code */
	output_code(output, 0);  /* flush the output buffer */
	output_code(output, 0);
	output_code(output, 0);
    /*fsync(fileno(output));*/
	fflush(output);
	fclose(output);
    if(stat(filename,&s_buf)==0){
	counter =(long)s_buf.st_size;
 printf("\nThe original raw data occupies %ld bytes", rows*cols*no_of_bands);
 printf("\nThe compressed data occupies %ld bytes",counter );
 printf("\nCompression ratio 1 : %f\n", (rows*cols*no_of_bands)/(float)counter);
    }
    free(code_value);
    free(prefix_code);
    free(append_symbol);
    if (inputImage) delete_Image(inputImage);

	return 0;
}

/* ------------------- Function FIND_MATCH ----------------------- */
/* -------------- searches string tables for a match ------------- */
/*           strings are stored in the string table based          */
/*           on an index calculated from the symbol shifted        */
/*           to the left and exclusive-ORed with hash_prefix       */
/*           return the index number of a free location or         */
/*           the location of a matching string                     */
/* --------------------------------------------------------------- */
static int find_match(int hash_prefix, unsigned int hash_symbol)
{
	int index;        /* counter for the table string */
	int offset;       /* offset variable for table locations */

	/* -------- calculate index counter for string table -------- */
	index = (hash_symbol << HASHING_SHIFT) ^ hash_prefix;
	if (index ==0)
		offset = 1;
	else
		offset = TABLE_SIZE - index;

	while(1)
	{
		if (code_value[index] == -1) /* no match found, new string */
			return(index);
		if (prefix_code[index] == hash_prefix && append_symbol[index] == hash_symbol)
			return(index); /* matching string found */
		index -= offset; /* update index by the offset */

		if (index < 0)
			index += TABLE_SIZE;
	}
}

Image *zvl_decompress(char *filename){
    FILE *input;

    if((input = fopen(filename, "rb")) == NULL)  {
       printf("\nError opening the file\n");
       return NULL;
    }

    return zvl_decompression(input);
}

Image *zvl_decompression(FILE *input)
{
	unsigned int next_code = FIRST_CODE; /* initialize next_code to first available location */
	unsigned int new_code; /* code word read from input file */
	unsigned int old_code; /* previous code word read from the input file */
	int symbol;          /* variable for symbol storage */
	int clear_flag = 1;  /* need to clear the code value array */
	short int rows, cols, no_of_bands,x,y,bands;
	char a,b,c;
	Image *decodeImage;
	byte **image_array;
	unsigned char *string; /* pointer declaration for symbol string */

	code_value =(int*)calloc(TABLE_SIZE,sizeof(int));
	prefix_code = (unsigned int*)calloc(TABLE_SIZE,sizeof(int));
	append_symbol = (byte*)calloc(TABLE_SIZE,sizeof(byte));
	bytes_in=0; bytes_out_zvl=0;
	num_bits = INIT_BITS;
	checkpoint=CHECK_TIME; 
	mess = 0;
	input_bit_count = 0; 
	input_bit_buffer = 0L; 
	output_bit_count = 0; 
	output_bit_buffer = 0L; 
	max_code = MAXVAL(num_bits);
	a = getc(input);
	b = getc(input);
	c = getc(input);
	if(a!='z' || b !='v' || c !='l'){
	    printf("\nInvalid File format\n");
	    free(code_value);
	    free(prefix_code);
	    free(append_symbol);
	    return NULL;
	}
        fread(&rows,sizeof(short int), 1,input);
    	fread(&cols,sizeof(short int), 1,input);
    	fread(&bands,sizeof(short int), 1,input);
    	if(bands == 1)
            decodeImage=new_Image(PGM,GRAY_SCALE,bands,rows,cols,CVIP_BYTE,REAL);
    	else
            decodeImage=new_Image(PPM,RGB,bands,rows,cols,CVIP_BYTE,REAL);
	
	image_array = getData_Image(decodeImage,0);
	x=y=no_of_bands=0;

	/* --------------- decode code words until EOF ------------------- */
	while((new_code = input_code(input)) != TERMINATOR)
	{
		mess++; /* increments message counter for message display */
		/* ----------------- flashes DECODING on the display ---------------- */
		if (clear_flag)  /* initialize or re-initialize */
		{
			clear_flag = 0; /* set clear_flag to zero */
			old_code = new_code; /* update old_code */
			symbol = old_code;  /* clear symbol and update */
			image_array[y][x] = (byte)symbol;
			x++;
			if(x>=cols){
			    x=0; y++;
			}
			if(y>=rows){
			    y=0; no_of_bands++;
			    if(no_of_bands < bands)
			        image_array = getData_Image(decodeImage,no_of_bands);
			}
			
			continue;
		}
		if (new_code == CLEAR_TABLE)  /* Clear string table */
		{
			clear_flag = 1; /* reset clear_flag */
			num_bits = INIT_BITS; /* initialize num_bits */
			next_code = FIRST_CODE; /* initialize next_code to first location */
			max_code = MAXVAL(num_bits); /* initialize max_code */
			continue;
		}

		/* ----------------------- decoding code words ------------------------ */
		if (new_code >= next_code)  /* check for string+symbol+string */
		{
			*decode_stack = symbol;
			string = (byte*)decode_string(decode_stack + 1, old_code);
		}
		else
		{
			string = (byte*)decode_string(decode_stack,new_code);
		}

		
		symbol = *string; /* initialize symbol */
		while (string >= decode_stack)
		{
			image_array[y][x] = *string--;
			x++;
			if(x>=cols){
			    x=0; y++;
			}
			if(y>=rows){
			    y=0; no_of_bands++;
			    if(no_of_bands < bands)
			        image_array = getData_Image(decodeImage,no_of_bands);
			}
		}

		if (next_code <= max_code)   /* add string to table if not full */
		{
			prefix_code[next_code] = old_code; /* base code for string */
			append_symbol[next_code++] = symbol; /* next symbol to be added to the string */

			if (next_code == max_code && num_bits < MAX_BITS)
			{
				max_code = MAXVAL(++num_bits); /* increment max_code if next_code is beyond current limits */
			}
		}
		old_code = new_code; /* update old_code */
	}
	decodeImage->image_format = ZVL;
	free(code_value);
	free(prefix_code);
	free(append_symbol);
	return decodeImage;
}

/* ----------------------- Function *DECODE_STRING ------------------------- */
/* ------------------ decode the strings in the string table --------------- */
/*             decode a code string from the string table, storing           */
/*             the decoded string to a buffer.  the buffer can then          */
/*             be output in reverse order by the expansiom function.         */
/*             UNCHANGED from original program.                              */
/* ------------------------------------------------------------------------- */

static char *decode_string(unsigned char *buffer, unsigned int code)
{
	int i=0;  /* variable for error checking */

	while(code >255)
	{
		*buffer++ = append_symbol[code];
		code = prefix_code[code];
		if (i++ >= 4000)
		{
			printf("\n ERROR DURING CODE EXPANSION\n");
			exit(1);
		}
	}
	*buffer = code;
	return( (char*)buffer);
}

/* ----------------------- Function INPUT_CODE -------------------------- */
/* ------------- reads the symbols from the input file ------------------ */
/*               reads symbols from the input file and stores             */
/*               the symbols into a 4 byte buffer and then                */
/*               decodes the code words from the buffer                   */
/* ---------------------------------------------------------------------- */

static unsigned input_code(FILE *input)
{
	unsigned int return_value; /* decoded code word from the buffer that is returned */

	while (input_bit_count <= 24) /* read symbols until buffer is full */
	{
		input_bit_buffer |= (unsigned long) getc(input) << (24 - input_bit_count);
		input_bit_count += 8; /* increment bit counter after each symbol is read */
		/* read a symbol and shift it into the buffer, then OR present buffer with the */
		/* previous buffer */
	}
	return_value = input_bit_buffer >> (32-num_bits); /* shift buffer to obtain the code word */
	input_bit_buffer <<= num_bits; /* shift the buffer to get ready for the next symbol */
	input_bit_count -= num_bits; /* decrement the bit counter by length of the code word */
	return(return_value); /* return the code word */
}

/* ----------------------- Function OUTPUT_CODE --------------------------- */
/* ----------------- writes the code words to output file ----------------- */
/*             function takes a code word (length 9 to 14 bits)             */
/*             and codes them into 8 bit symbols for writing to             */
/*             the output file                                              */
/* ------------------------------------------------------------------------ */

static void output_code(FILE *output, unsigned int code)
{

	output_bit_buffer |= (unsigned long) code << (32 - num_bits - output_bit_count);
	output_bit_count += num_bits;
	while (output_bit_count >= 8) /* write symbols until buffer is empty */
	{
		putc(output_bit_buffer >> 24, output); /* shift right 24 times and write the symbol */
		output_bit_buffer <<= 8; /* shift left by 8 for next symbol */
		output_bit_count -= 8; /* decrement bit counter by 8 */
		bytes_out_zvl++;    /* compaction monitoring */
	}
	return;
}
