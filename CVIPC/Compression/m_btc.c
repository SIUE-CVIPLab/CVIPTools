/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: m_btc.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Fri Aug 30 19:16:20 CDT 1996
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Hong Niu and Zhen Li and Kun Luo 
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1996 SIUE - by Scott Umbaugh, Kun Luo, H. Niu, Z. Li.
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
** $Log: m_btc.c,v $
** Revision 1.17  1997/07/25 20:47:25  wzheng
** rewrite the declaration of grayarray
**
** Revision 1.16  1997/06/06 17:42:46  wzheng
** memory leak
**
** Revision 1.15  1997/06/03 18:53:44  wzheng
** memory leak
**
** Revision 1.14  1997/06/02 16:10:13  wzheng
** avoid memory leak
**
** Revision 1.13  1997/05/21 14:08:52  yawei
** added binary fopen for WIN32
**
** Revision 1.12  1997/05/19 00:06:26  yawei
** *** empty log message ***
**
** Revision 1.11  1997/05/18 23:52:09  yawei
** removed fsync
**
** Revision 1.10  1997/03/08 00:57:03  yawei
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
** Revision 1.9  1997/01/16 21:19:32  yawei
** Global Change:  Image_FORMAT ==> IMAGE_FORMAT
**
 * Revision 1.8  1997/01/15  17:15:53  yawei
 * Global Change:  IMAGE ==> Image
 *
 * Revision 1.7  1996/11/30  02:35:51  yawei
 * modified functions and function prototyes.
 *
 * Revision 1.6  1996/11/20  15:22:51  yawei
 * Changed hard coded extension name to global array element
 *
 * Revision 1.5  1996/09/03  22:07:55  sumbaug
 * added CVIPtools header to file
 *
*
****************************************************************************/
/*
** include header files
** (function prototypes, new data types, etc.)
*/
#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPimage.h"
#include "CVIPhisto.h"
#include <sys/types.h>
#include <sys/stat.h>
#include "CVIPcompress.h"
/*
** declaration of function prototypes
*/
static char* BTC_Image(Image *inputImage);
static char* BTC_Image_pred(Image *inputImage);

static int quant_level(Image *inputImage, int blocksize, int blockx,\
	 int blocky,int level[4], int bands);

static int predi(int* level, int lut[][5], int* pred_err, int* prelev);
static int save_to_file(Image* input, int blocksize, char* output);
static void code_block(Image* input, int* level, int l, int j,
			int size, FILE *fp,int bands);
static void pred_code_block(Image* input, int* level, int l, int j,
			int size, FILE *fp, int* err, int index, int bands);

/*  no need now
int btc2_compress(Image *inputImage, int blocksize);
Image* btc2_decompression(char *input) ;
Image* btc2_decompress(FILE *fp); 

char *btc3_compress(Image *inputImage, int blocksize);
Image* btc3_decompression(char *input) ;
Image* btc3_decompress(FILE *fp); 
*/

extern char temp_dir[100];
extern char *Cmpr_Name[];

Image * btc2(Image *cvipImage)
{
	Image *decodeImage;
	char		*outputfile;	/* output file name */	

	outputfile = BTC_Image(cvipImage); /*call the BTC function */
	if(outputfile == NULL)
	    return NULL;
	decodeImage = btc2_decompress(outputfile);
   	free(outputfile);

	if (cvipImage) delete_Image(cvipImage);	
	return decodeImage;
}

Image *btc3(Image *cvipImage)
{
	Image *decodeImage;
	char		*outputfile;	/* output file name */	
	outputfile = (char*)malloc(150);
	strcpy(outputfile,temp_dir);
	strcat(outputfile,"/__"); strcat(outputfile,Cmpr_Name[Btc2]);


	outputfile = BTC_Image_pred(cvipImage); /*call the BTC function */
	if(outputfile == NULL)
	    return NULL;
	decodeImage = btc3_decompress(outputfile);
        free(outputfile);
	
	if (cvipImage) delete_Image(cvipImage);
	return decodeImage;
}




static char * BTC_Image(Image *inputImage){
    int blocksize;
	char		*outputfile;	/* output file name */	

	print_CVIP("\n\t\tEnter the block size:  ");
	blocksize = getInt_CVIP(10, 0, 64);

	outputfile = (char*)malloc(150);
	strcpy(outputfile,temp_dir);
	strcat(outputfile,"/__"); strcat(outputfile,Cmpr_Name[Btc2]);

   if (btc2_compress(inputImage, outputfile, blocksize) < 0) {
		free(outputfile);
		return (char *)NULL;
	} else return outputfile;
}

int btc2_compress(Image *inputImage, char *filename, int blocksize){

	FILE 		*fp;
	struct stat	s_buf;
	long		counter;
	byte 		**image; 	/* 2-d matrix data pointer */

	int 		y,		/* row index */
			x, 		/* column index */
			bands,		/* band index */
			level[4]={0,0,0,0},	/* quantization levels */
			blockx,blocky,xnum,ynum,	/* block number */
			l=0,j;
			
	unsigned int 	rows, 		/* number of rows in image */
			cols,		/* number of columns in image */
			no_of_bands;	/* number of image bands */


	/*
	** Gets the number of image bands (planes)
	*/
	no_of_bands = getNoOfBands_Image(inputImage);

	/* 
	** Gets the number of rows in the input image  
	*/
	rows =  getNoOfRows_Image(inputImage);

	/* 
	** Gets the number of columns in the input image  
	*/
  	cols =  getNoOfCols_Image(inputImage);

	/*
	** reference each band of image data in 2-d matrix form;
	** which is used for reading and writing the pixel values
	*/

    if((fp=fopen(filename,"wb"))==NULL){
	printf("cannot open file to write\n");
 	if (inputImage) delete_Image(inputImage);
	return -1;
    }
    putc((int)'b',fp);
    putc((int)'2',fp);
    putc((int)'t',fp);
    putc((int)'c',fp);
    fclose(fp);
	save_to_file(inputImage, blocksize, filename);
	 #ifndef WIN32
    if((fp=fopen(filename,"a"))==NULL){
	 #else
    if((fp=fopen(filename,"ab"))==NULL){
	 #endif
	printf("cannot open file to write\n");
 	if (inputImage) delete_Image(inputImage);
	return -1;
    }
    

	for(bands=0; bands < no_of_bands; bands++) {
 	  image = getData_Image(inputImage, bands);
	  xnum=cols/blocksize;
	  ynum=rows/blocksize;
	  for (blocky=0; blocky<ynum; blocky++) 
	     for (blockx=0; blockx<xnum; blockx++) {
		quant_level(inputImage, blocksize, blockx, blocky,level, bands);
	code_block(inputImage, level, blockx, blocky, blocksize, fp,bands);             
	   }
 	}
    /*fsync(fileno(fp));*/
	 fflush(fp);
    fclose(fp);
    if(stat(filename,&s_buf)==0){
	counter =(long)s_buf.st_size;
 printf("\nThe original raw data occupies %ld bytes", rows*cols*no_of_bands);
 printf("\nThe compressed data occupies %ld bytes",counter );
 printf("\nCompression ratio 1 : %f\n", (rows*cols*bands)/(float)counter);
    }
 if (inputImage) delete_Image(inputImage);

return 0;
}
/*
** end of function BTC_Image
*/


static char *
BTC_Image_pred(Image *inputImage){
   int blocksize;
	char		*outputfile;	/* output file name */	
	outputfile = (char*)malloc(150);
	strcpy(outputfile,temp_dir);
	strcat(outputfile,"/__"); strcat(outputfile,Cmpr_Name[Btc3]);


	print_CVIP("\n\t\tEnter the block size:  ");
	blocksize = getInt_CVIP(10, 0, 256);
   if (btc3_compress(inputImage, outputfile, blocksize) < 0) {
		free(outputfile);
		return NULL;
	} else return outputfile;
}

int btc3_compress(Image *inputImage, char *filename, int blocksize)
{
	FILE 	*fp;
	struct stat	s_buf;
	long		counter;
	byte 		**image; 	/* 2-d matrix data pointer */

	int 		y,		/* row index */
			x, 		/* column index */
			bands,		/* band index */
			level[4]={0,0,0,0},	/* quantization levels */
			pred_err[4]={0,0,0,0},	/* predictor pred_errs */
			blockx,blocky,xnum,ynum,	/* block number */
			l=0,j,i,
			lut[][5]={{2,3,3,2,10},	{2,4,3,3,12}, {1,2,8,1,12},
				  {3,3,4,2,12}, {3,4,4,3,14}, {2,5,4,3,14},
				  {3,5,4,4,16}, {4,4,5,3,16}, {3,6,5,4,18},
				  {4,4,5,5,18}, {4,6,5,5,20}, {5,6,6,5,22},
				  {3,5,5,9,22}, {5,7,6,6,24}, {9,7,5,3,24},
 				  {9,9,9,9,36}},
					/* bit allocation LUT */
				index,	/* the index of optimal vector in lut */ 
			prelev[2]={0,0}; 	/* previous block levels */
	unsigned int 	rows,		/* number of rows in image */
			cols,		/* number of columns in image */
			no_of_bands;	/* number of image bands */


	/*
	** Gets the number of image bands (planes)
	*/
	no_of_bands = getNoOfBands_Image(inputImage);

	/* 
	** Gets the number of rows in the input image  
	*/
	rows =  getNoOfRows_Image(inputImage);

	/* 
	** Gets the number of columns in the input image  
	*/
  	cols =  getNoOfCols_Image(inputImage);

	/*
	** reference each band of image data in 2-d matrix form;
	** which is used for reading and writing the pixel values
	*/


    if((fp=fopen(filename,"wb"))==NULL){
	printf("cannot open file to write\n");
        if (inputImage) delete_Image(inputImage);
	return -1;
    }
    putc('b',fp);
    putc('3',fp);
    putc('t',fp);
    putc('c',fp);
    fclose(fp);
	save_to_file(inputImage, blocksize, filename);
	 #ifndef WIN32
    if((fp=fopen(filename,"a"))==NULL){
	 #else
    if((fp=fopen(filename,"ab"))==NULL){
	 #endif
	printf("cannot open file to write\n");
        if (inputImage) delete_Image(inputImage);
	return -1;
    }

	for(bands=0; bands < no_of_bands; bands++) {
 	  image = getData_Image(inputImage, bands);
	  level[0]=level[1]=level[2]=level[3]=0;
	  prelev[0]=prelev[1]=0; 	
	  xnum=cols/blocksize;
  	  ynum=rows/blocksize;
	  for (blocky=0; blocky<ynum; blocky++) 
	    for (blockx=0; blockx<xnum; blockx++) {
		quant_level(inputImage, blocksize, blockx, blocky,level, bands); 
		index=predi(level, lut, pred_err, prelev);

	
		prelev[0] = level[1];
		prelev[1] = level[2];
	        pred_code_block(inputImage, level, blockx, blocky, blocksize, \
                                fp,pred_err,index,bands);
               	
	    }
	}

    /*fsync(fileno(fp)); */
	 fflush(fp);
    fclose(fp);
    if(stat(filename,&s_buf)==0){
	counter =(long)s_buf.st_size;
 printf("\nThe original raw data occupies %ld bytes", rows*cols*no_of_bands);
 printf("\nThe compressed data occupies %ld bytes",counter );
 printf("\nCompression ratio 1 : %f\n", (rows*cols*bands)/(float)counter);
    }

if (inputImage) delete_Image(inputImage);
return 0;
}
/*
** end of function BTC_Image_pred
*/


/* Calculat quantization levels */
static int 
quant_level(Image *inputImage, int blocksize, int blockx,\
	 int blocky,int level[4], int bands)
{
	byte 		**image; 	/* 2-d matrix data pointer */

	int 		y,		    	/* row index */
			x, 		    	/* column index */
			i,j,		    	/* index */
			min=255,		/* the min gray level of the image */
			max=0,			/* the max gray level of the image */ 
			thre[3][3]={0,0,0},	/* the threshold value 
						** thre[i][1] is left shift of thre[i][0]
						** thre[i][2] is right shift of thre[i][0]
						*/
			*hist,			/* number of pixels of gray level r*/	
			y0, y1, x0, x1;

	const int 	L=256;	

 	image = getData_Image(inputImage, bands);

	hist=(int*)malloc(L*sizeof(int));
	 		
	for(i=0; i<L; i++)  hist[i]=0;             

 	/*calculat hist[i] */
	y0 = blocksize*blocky;
	y1 = blocksize*(blocky+1);
	x0 = blocksize*blockx;
	x1 = blocksize*(blockx+1);
  	for(y=y0; y<y1; y++) 
     		for(x=x0; x<x1; x++) {
		i=image[y][x];
		hist[i]++;   
		if (i>max) max=i;
		if (i<min) min=i;
        	}

	thre[1][0]=(min+max)/2;
	thre[0][0]=(thre[1][0]+min)/2;
	thre[2][0]=(max+thre[1][0])/2;

	/* dilate thre[0] */
	if (hist[thre[0][0]] == 0) {
		thre[0][1]=thre[0][0];
		thre[0][2]=thre[0][0];
		thre[0][0]=0;
		do {
			thre[0][1]--;
		} while ( hist[thre[0][1]] == 0 );
		do {
			thre[0][2]++;
		} while ( hist[thre[0][2]] == 0 );
		thre[1][0]=(max-thre[0][2])/3+thre[0][2];
		thre[2][0]=(max-thre[0][2])*2/3+thre[0][2];

	}

	/* dilate thre[1] */
	if (hist[thre[1][0]] == 0) {
		thre[1][1]=thre[1][0];
		thre[1][2]=thre[1][0];
		thre[1][0]=0;
		do {
			thre[1][1]--;
		} while ( hist[thre[1][1]] == 0 );
		do {
			thre[1][2]++;
		} while ( hist[thre[1][2]] == 0 );
		thre[2][0]=(max+thre[1][2])/2;
	}

	/* dilate thre[2] */
	if (hist[thre[2][0]] == 0) {
		thre[2][1]=thre[2][0];
		thre[2][2]=thre[2][0];
		thre[2][0]=0;
		do {
			thre[2][1]--;
		} while ( hist[thre[2][1]] == 0 );
		do {
		thre[2][2]++;
		} while ( hist[thre[2][2]] == 0);

	}
	
	for (i=0; i<3; i++)
		if (thre[i][0] != 0) {
			thre[i][1] = thre[i][0];
			thre[i][2] = thre[i][0];
		}

	level[0] = (min + thre[0][1])/2;
	level[1] = (thre[0][2]+thre[1][1])/2;
	level[2] = (thre[1][2]+thre[2][1])/2;
	level[3] = (max + thre[2][2])/2;
		
free(hist);
return 1;

}
/*
** end of quant_level() function
*/

/*
** Calculates predict errors, finds optimal bits allocation vector
*/
static int 
predi(int* level, int lut[][5], int* pred_err, int* prelev) {

	int 	b[4],		/* bit of predictor pred_errs */
		totalb,		/* total bit of four predictor pred_errs */
		i, j,
		index=0;	/* the index of optimal vector which covers */
				/* pred_errs */

	const double 	LOG2=log10(2);
	float 	bit;		/* bit of predictor pred_err */

	/* calculates predictor errors */
	pred_err[1] = level[1]-prelev[0];
	pred_err[2] = level[2]-prelev[1];
	pred_err[0] = 2*level[1]-level[0]-level[2];
	pred_err[3] = level[3]-2*level[2]+level[1];

	/* calculates the bit of each error */
	for (i=0; i<4; i++) {
		if (pred_err[i]==0) 
			bit=1;
		else
			bit = log10(abs(pred_err[i]))/LOG2;
		b[i] = bit+2;
	}
	totalb = b[0]+b[1]+b[2]+b[3]; 

	/*
	** search the optimal bit allocation, 
	** the index of vector which covers the predictor errors in LUT 
	*/
	while (lut[index][4]<totalb) { index++;	}

	i=0;
	do {
	 	if (lut[index][i]<b[i]) {
			i=0;
			index++;
		}
		else
			i++;
	} while (i<4);

	return index;		

}
/* end of predict error function */

/* compress the image to a data file */
static int save_to_file(Image* input, int blocksize, char* output) {
    CVIP_TYPE           image_type;
    IMAGE_FORMAT   image_format;
    int            rows,cols,bands;
    FORMAT         data;
    COLOR_FORMAT   color;
    FILE           *fp;

    image_format =  getFileFormat_Image(input);
    color = getColorSpace_Image(input);
    bands = getNoOfBands_Image(input);
    rows =  getNoOfRows_Image(input);
    cols =  getNoOfCols_Image(input);
    image_type = getDataType_Image(input);
    data = getDataFormat_Image(input);

    /* save Image format data */ 
	 #ifndef WIN32
    if((fp=fopen(output,"a"))==NULL){
	 #else
    if((fp=fopen(output,"ab"))==NULL){
	 #endif
	printf("cannot open file to write\n");
	exit(0); 
    }
    if(fwrite(&image_format,sizeof(image_format),1,fp)!=1){
	printf("cannot write1\n");
	exit(0);
    }
    if(fwrite(&color,sizeof(color),1,fp)!=1){
	printf("cannot write2\n");
	exit(0);
    }
    if(fwrite(&bands,sizeof(bands),1,fp)!=1){
	printf("cannot write3\n");
	exit(0);
    }
    if(fwrite(&rows,sizeof(rows),1,fp)!=1){
	printf("cannot write4\n");
	exit(0);
    }
    if(fwrite(&cols,sizeof(cols),1,fp)!=1){
	printf("cannot write5\n");
	exit(0);
    }
    if(fwrite(&image_type,sizeof(image_type),1,fp)!=1){
	printf("cannot write6\n");
	exit(0);
    }
    if(fwrite(&data,sizeof(data),1,fp)!=1){
	printf("cannot write7\n");
	exit(0);
    }
    if(fwrite(&blocksize,sizeof(blocksize),1,fp)!=1){
	printf("cannot write8\n");
	exit(0);
    }
    fclose(fp); 
    return 1;

}
/* end of save_to_file */
 

/* quantize block[i][j], encoding it and write them to the data file */

static void 
code_block(Image* input, int* level, int l, int j, int size, FILE *fp,int bands){
    byte 	   **image; 	    /* 2-d matrix data pointer */

    int            bitptr=2,
                   num,             /* the number of the gray level which is closest */
                   k,               /* to the pixel */
                   diff,            /* the difference between image[y][x] and level[k]*/
                   min=0,           /* the least difference */  
                   y,		    /* row index */
		   x; 	            /* column index */
                                    			
    unsigned int   rows, 	    /* number of rows in image */
		   cols;	    /* number of columns in image */

    byte           b,buff;	
		
    /* add block data to the file*/ 
    rows =  getNoOfRows_Image(input);
    cols =  getNoOfCols_Image(input);



    /*
    **write the level[4] into the compression file.
    */

    for(k=0; k<4; k++) {
        b=(byte)(level[k]);

        if(fwrite(&b,sizeof(byte),1,fp)!=1){
	    perror("cannot write level\n");
	    exit(0);
        }
    }

    buff=0;

    
  	image = getData_Image(input, bands);
  	for(y=0+j*size; y<(j+1)*size; y++) {
     	    for(x=0+l*size; x<(l+1)*size; x++) {
                min=abs(image[y][x]-level[0]);       /* quantitize the block */
                num=0;
                for(k=1; k<4; k++) {
                    diff=abs(image[y][x]-level[k]);
                    if (diff<min) {
                        min=diff;
                        num=k; 
                    }
                }                                    /* end of quantitize */
 		image[y][x]=level[num];

                buff=buff+num;
                
                if(bitptr==8) {
		    if(fwrite(&buff,sizeof(byte),1,fp)!=1){
			printf("cannot write buff\n");
			exit(0);
    		    }
		    buff=0; bitptr=0;
                }
                buff=buff<<2; bitptr=bitptr+2; 
            }                                                   
        }
    
    /*last pixel with information*/
    for(k=bitptr-2;k<8;k++) {
	buff=buff<<1;
	buff=buff+0;	    
    }
    if(fwrite(&buff,sizeof(buff),1,fp)!=1){
	printf("cannot write last\n");
	exit(0);
    }
      
}                                          /* end of code_block() */


Image* btc2_decompress(char *filename) {
    FILE               *fp;
    Image *		decodeImage;

    if((fp=fopen(filename,"rb"))==NULL){
	printf("cannot open file to read\n");
	return NULL; 
    }
    decodeImage = btc2_decompression(fp);
    fclose(fp);

    return decodeImage;
}

Image *btc2_decompression(FILE *fp){

    Image              *output;
    /*int                grayarray[262144],blocksize,x,y,i,j,k,u,num;*/
    int                *grayarray,blocksize,x,y,i,j,k,u,num;
    byte               level[4],gray,**out;
    CVIP_TYPE               image_type;
    IMAGE_FORMAT       image_format;
    int                bands;
    FORMAT             data;
    COLOR_FORMAT       color;
    char b,t,c,n;
    unsigned int       rows, cols,v,w,no_of_bands;           
    
    u=0; v=0;


    /*read Image Format Data*/
    
    b = (char)getc(fp);
    n = (char)getc(fp);
    t = (char)getc(fp);
    c = (char)getc(fp);
    if(b != 'b' || n != '2' || t != 't' || c != 'c'){
	fprintf(stderr,"Wrong image format\n");
	return NULL;
    }
    if(fread(&image_format,sizeof(image_format),1,fp)!=1){
	printf("cannot read\n");
	return NULL;
    }
    if(fread(&color,sizeof(color),1,fp)!=1){
	printf("cannot read\n");
	return NULL;
    }
    if(fread(&no_of_bands,sizeof(no_of_bands),1,fp)!=1){
	printf("cannot read\n");
	return NULL;
    }

    if(fread(&rows,sizeof(rows),1,fp)!=1){
	printf("cannot read\n");
	return NULL;
    }

    if(fread(&cols,sizeof(cols),1,fp)!=1){
	printf("cannot read\n");
	return NULL;
    }

    if(fread(&image_type,sizeof(image_type),1,fp)!=1){
	printf("cannot read\n");
	return NULL;
    }
    if(fread(&data,sizeof(data),1,fp)!=1){
	printf("cannot read\n");
	return NULL;
    }
    if(fread(&blocksize,sizeof(blocksize),1,fp)!=1){
	printf("cannot read\n");
	return NULL;
    }
               
    grayarray = calloc(blocksize*blocksize+4, sizeof(int)); 
    if(grayarray == NULL) {
	printf("blocksize is too big.\n");
	return NULL;
    }
    output=new_Image(image_format,color,no_of_bands,rows,cols,image_type,data);
    for(bands=0; bands < no_of_bands; bands++) {
        out = getData_Image(output, bands);
        for(i=0; i<rows/blocksize; i++) {
            for(j=0; j<cols/blocksize; j++){   
                for(k=0; k<4; k++) {
                    if(fread(&level[k],sizeof(level[k]),1,fp)!=1){
	                printf("cannot read\n");
			free(grayarray);
	                return NULL;
                    }                    
                }                 

                num=blocksize*blocksize/4;
		for(v=0;v<=num;v++) {
		    if(fread(&gray,sizeof(gray),1,fp)!=1){

         		perror("can't read gray");
	                free(grayarray);
			return NULL;
		    }
	   	    for(u=3; u>=0; u--) {
                        grayarray[u+4*v]=(int)(gray)%4; 
                        gray=gray>>2;
		    }
		}

                w=0;        
                for(y=0+i*blocksize; y<(i+1)*blocksize; y++) {
     	            for(x=0+j*blocksize; x<(j+1)*blocksize; x++) {

                        out[y][x]=level[grayarray[w]];
			w++;                        
                    }
                }
                
            }
        }
    }     
   
    output->image_format = BTC2;
    free(grayarray);


    return output;
}    /* end of decode_file() */
/* quantize block[i][j], encoding it and write them to the data file */

void 
pred_code_block(Image* input, int* level, int l, int j, int size, \
                FILE *fp, int* err, int index, int bands){
    byte 	   **image; 	    /* 2-d matrix data pointer */

    int            bitptr,
                   num,             /* the number of the gray level which is closest */
                   k,               /* to the pixel */
                   diff,            /* the difference between image[y][x] and level[k]*/
                   min=0,           /* the least difference */  
                   y,		    /* row index */
		   x, 	            /* column index */
                   q,               /* the quotient of error and 2 */
                   num_bit;         /* # of bit needed for the error */
                                    			
    unsigned int   rows, 	    /* number of rows in image */
		   cols;	    /* number of columns in image */

    byte           buff;	
    int		   table[][5]={{2,3,3,2,10},{2,4,3,3,12}, {1,2,8,1,12},
			       {3,3,4,2,12}, {3,4,4,3,14}, {2,5,4,3,14},
			       {3,5,4,4,16}, {4,4,5,3,16}, {3,6,5,4,18},
			       {4,4,5,5,18}, {4,6,5,5,20}, {5,6,6,5,22},
			       {3,5,5,9,22}, {5,7,6,6,24}, {9,7,5,3,24},
 			       {9,9,9,9,36}};
					/* bit allocation LUT */
		
    /* add block data to the file*/ 
    
    rows =  getNoOfRows_Image(input);
    cols =  getNoOfCols_Image(input);


    
    /* 
    ** write the index into the compression file
    */
    
    buff=(byte)(index);

    buff=buff<<1; bitptr=5;
         
    /*
    ** write the err[4] into the compression file.
    */
    for(k=0; k<4; k++) {
        num_bit=0;
        q=abs(err[k]);
        while(q!=0) {

	    buff=buff+q%2;
 	    q=q/2;
            num_bit++; 

            if(bitptr==8) {
		if(fwrite(&buff,sizeof(byte),1,fp)!=1){
		    printf("cannot write error\n");
		    exit(0);
    		}
		buff=0; bitptr=0;
            }
            buff=buff<<1; bitptr++; 
        }
        if(num_bit<table[index][k]-1) {
            y=table[index][k]-num_bit-1;
	    for(x=0;x<y;x++) {   		
                if(bitptr==8) {
		    if(fwrite(&buff,sizeof(byte),1,fp)!=1){
		       printf("cannot write the rest 0\n");
		       exit(0);
    		    }
		    buff=0; bitptr=0;
                }
                buff=buff<<1; bitptr++;
             }
        }

        /* write the sign bit */
        if(err[k]<0)
            buff=buff+1;
        if(bitptr==8) {
	    if(fwrite(&buff,sizeof(byte),1,fp)!=1){
		printf("cannot write sign\n");
		exit(0);
    	    }
	    buff=0; bitptr=0;
        }
        buff=buff<<1; bitptr++;  
        
    }

    /* the last buff with information */
    if(bitptr!=1) {
        for(x=bitptr;x<8;x++) 
            buff=buff<<1;
        if(fwrite(&buff,sizeof(buff),1,fp)!=1){
            printf("cannot write last error\n");
	    exit(0);
        }
    } 

    bitptr=2;
    buff=0;


  	image = getData_Image(input, bands);
  	for(y=0+j*size; y<(j+1)*size; y++) {
     	    for(x=0+l*size; x<(l+1)*size; x++) {
                min=abs(image[y][x]-level[0]);           /* quantitize the block */
                num=0;
                for(k=0; k<4; k++) {
                    diff=abs(image[y][x]-level[k]);
                    if (diff<min) {
                        min=diff;
                        num=k; 
                    }
 
                }
                image[y][x]=level[k];                    /* end of quantitize */
                buff=buff+num;
                
                if(bitptr==8) {
		    if(fwrite(&buff,sizeof(byte),1,fp)!=1){
			printf("cannot write buff\n");
			exit(0);
    		    }
		    buff=0; bitptr=0;
                }
                buff=buff<<2; bitptr=bitptr+2; 
            }                                                   
        }
    

    /*last pixel with information*/
    for(k=bitptr-2;k<8;k++) 
	buff=buff<<1;
		    
    if(fwrite(&buff,sizeof(buff),1,fp)!=1){
	printf("cannot write last\n");
	exit(0);
    }
      
}           

Image *btc3_decompress(char *filename){
     FILE *fp;
     Image *decodeImage;

    if((fp=fopen(filename,"rb"))==NULL){
	printf("cannot open file to read\n");
	return NULL; }
    decodeImage = btc3_decompression(fp);
    fclose(fp);

    return decodeImage;
}
     

Image * btc3_decompression(FILE *fp) {
    Image              *output;
    char               *input; 
    int                *grayarray,blocksize,x,y,i,j,k,u,num,index,bitptr;
    /*int                grayarray[262144],blocksize,x,y,i,j,k,u,num,index,bitptr;*/
    byte               buff,**out,gray;
    CVIP_TYPE               image_type;
    IMAGE_FORMAT       image_format;
    int                bands;
    char		b,t,c,n;
    FORMAT             data;
    COLOR_FORMAT       color;
    unsigned int       rows, cols,v,w,no_of_bands;
    int                sign,err[4],level[4],prelev[2];
    int 	      table[][5]={{2,3,3,2,10},	{2,4,3,3,12}, {1,2,8,1,12},
				  {3,3,4,2,12}, {3,4,4,3,14}, {2,5,4,3,14},
				  {3,5,4,4,16}, {4,4,5,3,16}, {3,6,5,4,18},
				  {4,4,5,5,18}, {4,6,5,5,20}, {5,6,6,5,22},
				  {3,5,5,9,22}, {5,7,6,6,24}, {9,7,5,3,24},
 				  {9,9,9,9,36}};
					/* bit allocation table */           
    

     
    b = (char)getc(fp);
    n = (char)getc(fp);
    t = (char)getc(fp);
    c = (char)getc(fp);
    if(b != 'b' || n != '3' || t != 't' || c != 'c'){
	fprintf(stderr,"Wrong image format\n");
	return NULL;
    }
   
    if(fread(&image_format,sizeof(image_format),1,fp)!=1){
	printf("cannot read\n");
	exit(0);
    }
    if(fread(&color,sizeof(color),1,fp)!=1){
	printf("cannot read\n");
	exit(0);
    }
    if(fread(&no_of_bands,sizeof(no_of_bands),1,fp)!=1){
	printf("cannot read\n");
	exit(0);
    }

    if(fread(&rows,sizeof(rows),1,fp)!=1){
	printf("cannot read\n");
	exit(0);
    }

    if(fread(&cols,sizeof(cols),1,fp)!=1){
	printf("cannot read\n");
	exit(0);
    }

    if(fread(&image_type,sizeof(image_type),1,fp)!=1){
	printf("cannot read\n");
	exit(0);
    }
    if(fread(&data,sizeof(data),1,fp)!=1){
	printf("cannot read\n");
	exit(0);
    }
    if(fread(&blocksize,sizeof(blocksize),1,fp)!=1){
	printf("cannot read\n");
	exit(0);
    }
               
    grayarray = calloc(blocksize*blocksize+4, sizeof(int));
    if(grayarray == NULL) {
        printf("blocksize is too big.\n");
        return NULL;
    }


    output=new_Image(image_format,color,no_of_bands,rows,cols,image_type,data);
    for(bands=0; bands < no_of_bands; bands++) {
        out = getData_Image(output, bands);
        for(i=0; i<rows/blocksize; i++) {
            for(j=0; j<cols/blocksize; j++){
                if(fread(&buff,sizeof(buff),1,fp)!=1){
	            printf("cannot read index\n");
	            exit(0);
                }
/*printf("\nbuff=%d",(int)buff);*/

                index=0;
                num=pow(2,7);
                for(k=0; k<4; k++) {
		    if((int)buff>=num)
                        index=index+pow(2,(3-(double)k));
                    buff=buff<<1;
                }
/*printf("\nindex=%d",index);*/

                bitptr=4;

                err[0]=err[1]=err[2]=err[3]=0;

                for(k=0; k<4; k++){                    
                    for(u=0; u<table[index][k]-1; u++) {
                        if(bitptr==8) {
		            if(fread(&buff,sizeof(buff),1,fp)!=1){
			        printf("cannot read error\n");
			        exit(0);
    		            }
/*printf("\nbuff=%d",(int)buff);*/
		            bitptr=0;
                        }
		        if((int)buff>=num)
                            err[k]=err[k]+pow(2,(double)u);
                        buff=buff<<1; bitptr++;                
                            
                    }


                    if(bitptr==8) {
		        if(fread(&buff,sizeof(buff),1,fp)!=1){
			    printf("cannot read error\n");
			    exit(0);
    		        }
/*printf("\nbuff=%d",(int)buff);*/
		        bitptr=0;
                    }
		    sign=1;
		    if((int)buff>=num){
                        sign=-1;                                
                    } 
                    err[k]=err[k]*sign;
                    buff=buff<<1; bitptr++;
                }                  /* end of read error */
/* printf("\nerrors: %d,%d,%d,%d",err[0],err[1],err[2],err[3]);*/

      
                if(i==0&&j==0) 
                    prelev[0]=prelev[1]=0;
                level[1]=err[1]+prelev[0];
                level[2]=err[2]+prelev[1];
                level[0]=2*level[1]-level[2]-err[0];                      
                level[3]=2*level[2]-level[1]+err[3];
                prelev[0]=level[1];
                prelev[1]=level[2];                 
                      
/*printf("\nlevels=%d,%d,%d,%d",level[0],level[1],level[2],level[3]);*/
                num=blocksize*blocksize/4;
		for(v=0;v<=num;v++) {
		    if(fread(&gray,sizeof(gray),1,fp)!=1){
         		perror("can't read gray");
	                exit(0);
		    }
	   	    for(u=3; u>=0; u--) {
                        grayarray[u+4*v]=(int)(gray)%4; 
                        gray=gray>>2;
		    }
		}

                w=0;        
                for(y=0+i*blocksize; y<(i+1)*blocksize; y++) {
     	            for(x=0+j*blocksize; x<(j+1)*blocksize; x++) {

                        out[y][x]=level[grayarray[w]];
			w++;                        
                    }
                }
                
            }
        }
    }     
   
    output->image_format = BTC3;
    free (grayarray);
    return output;
}    /* end of pred_decode_file() */



