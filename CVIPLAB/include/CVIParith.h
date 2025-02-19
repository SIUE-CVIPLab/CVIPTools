
#include <stdio.h>
#include "CVIPdef.h"
#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPimage.h"

typedef struct {
    unsigned short int low_count;
    unsigned short int high_count;
    unsigned short int scale;
} SYMBOL;


/* 
  A symbol is defined as a range between 0 and 1. Instead of using 0 and 1
  as end points, an integer scale is used (low_count and high_count) as 
  structure members.
*/

typedef struct bit_file {
    FILE *file;
    unsigned char mask;
    int rack;
    int pacifier_counter;
} BIT_FILE;


BIT_FILE      *OpenInputBitFile( char *name );
BIT_FILE      *OpenOutputBitFile( char *name );
void          OutputBit( BIT_FILE *bit_file, int bit );
void          OutputBits( BIT_FILE *bit_file, unsigned long code, int count );
int           InputBit( BIT_FILE *bit_file );
unsigned long InputBits( BIT_FILE *bit_file, int bit_count );
void          CloseInputBitFile( BIT_FILE *bit_file );
void          CloseOutputBitFile( BIT_FILE *bit_file );
void          FilePrintBinary( FILE *file, unsigned int code, int bits );

byte         **image_array;
int          rows, cols; 
Image        *in_Image, *input_Image;
IMAGE_FORMAT format;
 
#define MAXSIZE       50
#define END_OF_STREAM 256
#define TOTAL_CHARS   257     /* total number of bytes */

short int totals[258];        /* cumulative total */
char  *CompressionName = "Fixed order 0 model with arithmetic coding";
char  *Usage           = "in-file out-file\n\n";


/* end of arith.h */




