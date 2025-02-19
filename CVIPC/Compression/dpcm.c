/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: dpcm.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Tue Apr 16 15:47:01 CDT 1996
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Kun Luo
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
$Log: dpcm.c,v $
Revision 1.22  2001/04/09 13:21:32  ycheng
fixed bugs so that it could run under Linux.

Revision 1.21  1997/06/16 20:02:05  yawei
cast for SGI port

Revision 1.20  1997/06/04 14:57:14  wzheng
memory leak

Revision 1.19  1997/05/16 22:58:04  smakam
Commented out fsync and added an alternative

Revision 1.18  1997/03/08 00:57:00  yawei
Name Changes:
	BOOLEAN ==> CVIP_BOOLEAN
	FALSE ==> CVIP_YES
	TRUE ==> CVIP_NO
	BYTE ==> CVIP_BYTE
	SHORT ==> CVIP_SHORT
	INTEGER ==> CVIP_INTEGER
	FLOAT ==> CVIP_FLOAT
	DOUBLE ==> CVIP_DOUBLE
	TYPE ==> CVIP_TYPE

Revision 1.17  1997/01/15 17:15:49  yawei
Global Change:  IMAGE ==> Image

 * Revision 1.16  1996/11/30  18:02:20  yawei
 * Name changes:
 *  DPCM_compression ==> dpc_compress
 *  DPCM_decompression ==> dpc_decompress
 *  DPCM_decompress ==> dpc_decompression
 *
 * Revision 1.15  1996/11/20  15:22:03  yawei
 * Changed hard coded extension name to global array element
 *
 * Revision 1.14  1996/06/12  21:31:20  kluo
 * check in
 *
 * Revision 1.13  1996/04/10  01:33:31  kluo
 * change default file from __DPCM to __dpcm
 *
 * Revision 1.12  1996/03/13  02:00:40  kluo
 * add table
 *
 * Revision 1.11  1996/03/09  21:30:09  kluo
 * add new lloyd_max predictor
 *
 * Revision 1.10  1996/03/08  02:37:24  kluo
 * add in llyod_max compression
 *
 * Revision 1.9  1996/02/20  17:43:47  kluo
 * close file when it is not used
 *
 * Revision 1.8  1996/01/10  00:06:31  kluo
 * add reconstruct option
 *
 * Revision 1.7  1995/11/27  22:29:15  mzuke
 * changed messages in dpc_compression prompts
 *
 * Revision 1.6  1995/11/09  19:31:13  kluo
 * change prompt for compression setup file
 *
 * Revision 1.5  1995/11/07  19:16:39  kluo
 * add clipping direction
 *
 * Revision 1.4  1995/11/07  17:39:35  kluo
 * fix problem with .5 ad decode stage
 *
 * Revision 1.3  1995/11/03  22:43:18  kluo
 * add log message
 *
*/
#include <CVIPimage.h>
#include <CVIPcompress.h>
#include <sys/stat.h>

extern char temp_dir[100];
extern char *Cmpr_Name[];
static int code_vertical;
static int do_clipping;

static float lloyd_max_value2[]  = {.7071};
static float lloyd_max_value4[]  = {.4198,1.8340};
static float lloyd_max_value8[]  = {.2334,.8330,1.6725,3.0868};
static float lloyd_max_value16[] = {.1240,.4049,.7288,1.1111,1.5780,2.1776,3.0171,4.4314};
static float lloyd_max_value32[] = {.0641,.2005,.3463,.5028,.6718,.8555,1.0565,1.2786,1.5266,1.8076,2.1314,2.5138,2.9807,3.5803,4.4199,5.8341};
static float lloyd_max_value64[] = {.0326,.1000,.1695,.2415,.3159,.3930,.4730,.5563,.6467,.7330,.8272,.9257,1.0291,1.1377,1.2522,1.3731,1.5014,1.6379,1.7838,1.9404,2.1094,2.2931,2.4942,2.7163,2.9644,3.2453,3.5692,3.9516,4.4185,5.0181,5.8576,7.2719};
static float lloyd_max_value128[]= {.0166,.0502,.0844,.1191,.1544,.1903,.2269,.2640,.3019,.3404,.3796,.4195,.4602,.5017,.5440,.5871,.6311,.6761,.7220,.7689,.8169,.8659,.9161,.9675,1.0202,1.0741,1.1295,1.1863,1.2447,1.3047,1.3664,1.4299,1.4964,1.5629,1.6327,1.7048,1.7793,1.8566,1.9368,2.0200,2.1067,2.1970,2.2913,2.3899,2.4933,2.6220,2.7165,2.8376,2.9659,3.1024,3.2483,3.4049,3.5740,3.7577,3.9587,4.1809,4.4289,4.7099,5.0338,5.4162,5.6831,6.4227,7.3222,8.7364};

static float *lloyd_max_value[] = {
		lloyd_max_value2,lloyd_max_value4,lloyd_max_value8,
		lloyd_max_value16,lloyd_max_value32,lloyd_max_value64,
		lloyd_max_value128
}; 

static float lloyd_max_level2[]  = {.0};
static float lloyd_max_level4[]  = {.0,1.1269};
static float lloyd_max_level8[]  = {.0,.5332,1.2528,2.3797};
static float lloyd_max_level16[] = {.0,.2645,.5668,.9200,1.3446,1.8778,2.5974,3.7243};
static float lloyd_max_level32[] = {.0,.1323,.2734,.4245,.5873,.7636,.9560,1.1675,1.4026,1.6671,1.9695,2.3227,2.7473,3.2805,4.0001,5.1270};
static float lloyd_max_level64[] = {.0,.0663,.1348,.2055,.2787,.3545,.4330,.5146,.5995,.6879,.7801,.8764,.9774,1.0834,1.1949,1.3127,1.4373,1.5697,1.7108,1.8621,2.0249,2.2013,2.3936,2.6052,2.8403,3.1048,3.4073,3.7604,4.1850,4.7183,5.4379,6.5647};
static float lloyd_max_level128[]= {.0,0.0334,.0673,.1018,.1368,.1724,.2086,.2455,.2829,.3211,.3600,.3995,.4398,.4809,.5228,.5655,.6091,.6536,.6991,.7455,.7929,.8414,.8910,.9418,.9938,1.0471,1.1018,1.1579,1.2155,1.2747,1.3355,1.3982,1.4627,1.5292,1.5978,1.6687,1.7420,1.8180,1.8967,1.9764,2.0634,2.1518,2.2441,2.3406,2.4416,2.5477,2.6593,2.7771,2.9017,3.0341,3.1753,3.3266,3.4894,3.6658,3.8582,4.0698,4.3049,4.5694,4.8718,5.2250,5.6496,6.1829,6.9024,8.0293};

static float *lloyd_max_level[] = {
		lloyd_max_level2,lloyd_max_level4,lloyd_max_level8,
		lloyd_max_level16,lloyd_max_level32,lloyd_max_level64,
		lloyd_max_level128
};


static short *lloyd_max_value_cal;
static short *lloyd_max_level_cal;

static int getmean_Image(Image *inputImage, int no_of_bands);
static void initialize_struct(int bit_length, float deviation);

static void Record_first_data(FILE *fptr, Image *inputImage);
static void Quantize_Predict(Image *inputImage, Image *duplicate);
static void
store_DPCM(FILE *fptr, Image *inputImage, Image *duplicate, int bit_leng);

static int read_raw_DPCM(Image *decodeImage, Image *sign_Image,int bit_length,
			FILE *fptr);
static void decode_DPCM(Image *decodeImage, Image *signImage,int mean_value,
			float ratio,int bit_length,int no_of_bands, int origin);
static void Predict_DPCM(Image *inputImage,Image *sign_Image,int mean_value,
			float ratio, int origin, int clip[]);
static void
store_DPCM_clipping(FILE *fptr,Image *inputImage,Image *duplicate,
			int bit_length);

/*
Image* dpc_compression(Image *inputImage);
int dpc_compress(Image *inputImage, char *filename,float ratio,int num,int c, int d, int or, float);
Image *DPCM_decompression(char *filename);
Image *DPCM_decompress(FILE *fptr);
*/


Image* dpc_compression(Image *inputImage){
    char  filename[150];
    float ratio;
    int number;
    int direction = 0, clipping = 0;
    int origin = 0;
    float deviation;

    strcpy(filename,temp_dir);
    strcat(filename,"/__"); strcat(filename, Cmpr_Name[Dpcm]);
   
    printf("Enter the normalized correlation factor\n (typically between 0.85 and 0.95):");
    ratio = (float)getFloat_CVIP(0,1);
    fflush(stdin);
    printf("Do you want to scan in vertical direction(y/n)?:");
    if(getchar() == 'y')
	direction = 1;
    fflush(stdin);
    printf("Which method do you want use during encoding?");
    printf("\n\t1) original value");
    printf("\n\t2) reconstructed value");
    printf("\n\t3) reconstructed value using Lloyd-Max Quantizers");
    fflush(stdin);
    printf("\nChoice:");
    origin = getInt_CVIP(10,1,3);
    fflush(stdin);
    if(origin != 3){
    	printf("Do you want to clip to the maximum?(y/n):");
    	if(getchar() == 'y'){
	    clipping = 1;
	    fflush(stdin);
            printf("Enter the number of bits used for each pixel(1-8):");
            number = getInt_CVIP(10,1,8);
    	}
    	else{
	    fflush(stdin);
            printf("Enter the number of bits used for each pixel(2-8):");
            number = getInt_CVIP(10,2,8);
        }
    }
    else{
    	clipping = 1;
	fflush(stdin);
        printf("Enter the number of bits used for each pixel(1-7):");
        number = getInt_CVIP(10,1,7);
	fflush(stdin);
	printf("Enter the value for the standard deviation:");
	scanf("%f",&deviation);
    }
    if(dpc_compress(inputImage,filename,ratio,number,
				clipping,direction,origin,deviation)== -1)
	return NULL;


    return dpc_decompress(filename);
}

Image *dpc_decompress(char *filename){
    FILE *fptr;
    Image *decodeImage;

    fptr = fopen(filename,"rb");
    if(fptr == NULL){
	fprintf(stderr,"DPCM decompression:cannot open file for reading");
	return NULL;
    }

    decodeImage = dpc_decompression(fptr);
    fclose(fptr);

    return decodeImage;
}

Image *dpc_decompression(FILE *fptr){
    Image *decodeImage,*signImage;
    int rows, cols, bands,y,x,no_of_bands; 
    char header[5];
    float ratio;
    int mean_value;
    int bit_length;
    int direction,clipping,origin;
    float deviation;
    byte **data;

    header[0] = (char)getc(fptr);
    header[1] = (char)getc(fptr);
    header[2] = (char)getc(fptr);
    header[3] = (char)getc(fptr);
    header[4] = '\0';
   
    if(strcmp(header,"dpcm") != 0){
	fprintf(stderr,"Inappropriate image format\n");
	return NULL;
    }
    fread(&rows,sizeof(int),1,fptr);
    fread(&cols,sizeof(int),1,fptr);
    fread(&bands,sizeof(int),1,fptr);
    fread(&bit_length,sizeof(int),1,fptr);
    fread(&direction,sizeof(int),1,fptr);
    fread(&clipping,sizeof(int),1,fptr);
    fread(&origin,sizeof(int),1,fptr);
    fread(&deviation,sizeof(float),1,fptr);
    fread(&ratio,sizeof(float),1,fptr);
    code_vertical = direction;
    do_clipping = clipping;

    if(origin == 3)
	initialize_struct(bit_length, deviation);

    if(bands == 1){
    	decodeImage=new_Image(PGM,GRAY_SCALE,bands,rows,cols,CVIP_BYTE,REAL);
	signImage =new_Image(PGM,GRAY_SCALE,bands,rows,cols,CVIP_BYTE,REAL);
    } 
    else{
        decodeImage=new_Image(PPM,RGB,bands,rows,cols,CVIP_BYTE,REAL);
	signImage =new_Image(PPM,RGB,bands,rows,cols,CVIP_BYTE,REAL);
    }
    if(decodeImage == NULL)
	return NULL;
    
    for(no_of_bands = 0; no_of_bands < bands;no_of_bands++){
    	fread(&mean_value,sizeof(int),1,fptr);
	
    }

    for(no_of_bands = 0; no_of_bands < bands;no_of_bands++){
	data = getData_Image(decodeImage,no_of_bands);
	if(code_vertical == 0){
	  for(y=0;y<rows;y++)
	    fread(data[y],1,1,fptr);   
	}
	else{ 
	  for(x=0;x<cols;x++)
	    fread(data[0]+x,1,1,fptr);   
	}
    }
    if(read_raw_DPCM(decodeImage,signImage,bit_length,fptr)== -1){
	delete_Image(decodeImage);
	return NULL;
    }
    

    for(no_of_bands = 0; no_of_bands < bands;no_of_bands++){
    	decode_DPCM(decodeImage,signImage,mean_value,ratio,
			bit_length,no_of_bands, origin);	
    }

    decodeImage->image_format = DPC; 
    delete_Image(signImage);

    if(origin == 3){
	free(lloyd_max_level_cal);
	free(lloyd_max_value_cal);
    }
   
    return decodeImage;
}

static void decode_DPCM_clipping(Image *decodeImage,int mean_value,float ratio,
			int bit_length,int no_of_bands, int origin){
    int rows, cols, x,y,bands;
    byte ** data;
    int temp, sign_bit;

    rows = decodeImage->bandP[0]->rows;
    cols = decodeImage->bandP[0]->cols;
    data = getData_Image(decodeImage,no_of_bands);
    if(code_vertical == 0){
      for(y=0;y<rows;y++){
     	for(x=1;x<cols;x++){
	    temp = data[y][x];
	    sign_bit = temp & (1<<(bit_length-1));
	    if(sign_bit)
		temp = ~temp + 1;
	    temp &= ((1<<bit_length) - 1);
	    if(origin == 3 && sign_bit)
	         temp--;
	    if(origin == 3)
	        temp = lloyd_max_value_cal[temp];
	    if(sign_bit)
	        temp *= -1;
	    data[y][x] = (byte)(ratio*(float)(data[y][x-1])+
				  (1.0-ratio)*mean_value - temp + 0.5);
	}
      }
    }
    else{
      for(x=0;x<cols;x++){
     	for(y=1;y<rows;y++){
	    temp = data[y][x];
	    sign_bit = temp & (1<<(bit_length-1));
	    if(sign_bit)
		temp = ~temp + 1;
	    temp &= ((1<<bit_length) - 1);
	    if(origin == 3 && sign_bit)
	         temp--;
	    if(origin == 3)
	        temp = lloyd_max_value_cal[temp];
	    if(sign_bit)
	        temp *= -1;
	    data[y][x] = (byte)(ratio*(float)(data[y-1][x])+
				  (1.0-ratio)*mean_value - temp + 0.5);
	}
      }
    }
}

static void decode_DPCM(Image *decodeImage, Image *signImage,int mean_value,
			float ratio,int bit_length,int no_of_bands,
			int origin){
    int rows, cols, x,y,bands;
    byte ** data,**sign_data;
    int temp;

    if(do_clipping){
	decode_DPCM_clipping(decodeImage,mean_value,ratio,bit_length,
		no_of_bands,origin);
        return;
    }
    rows = decodeImage->bandP[0]->rows;
    cols = decodeImage->bandP[0]->cols;
    data = getData_Image(decodeImage,no_of_bands);
    sign_data = getData_Image(signImage,no_of_bands);
    if(code_vertical == 0){
      for(y=0;y<rows;y++){
     	for(x=1;x<cols;x++){
	    temp = data[y][x];
	    if(origin != 3){
	        if(sign_data[y][x] == 1)
		    temp *= -1;
	    }
	    else{
		if(sign_data[y][x] == 1)
		    temp--;
		temp = lloyd_max_value_cal[temp] * ((sign_data[y][x]==0)?1:-1);
	    }		
	    data[y][x] =(byte)((ratio*(float)(data[y][x-1])+
				  (1.0-ratio)*mean_value - temp) + 0.5);
	}
      }
    }
    else{
      for(x=0;x<cols;x++){
     	for(y=1;y<rows;y++){
	    temp = data[y][x];
	    if(origin != 3){
	    	if(sign_data[y][x] == 1)
		    temp *= -1;
	    }
	    else{
		if(sign_data[y][x] == 1)
		    temp--;
		temp = lloyd_max_value_cal[temp] * ((sign_data[y][x]==0)?1:-1);
	    }		
	    data[y][x] =(byte)((ratio*(float)(data[y-1][x])+
				  (1.0-ratio)*mean_value - temp) + 0.5);
	}
      }
    }
}

static int read_raw_DPCM_clipping(Image *decodeImage,int bit_length,FILE *fptr){
    int cur_pos,max_pos,cur_byte,temp_pos, left_bit;
    byte *padding;
    int rows, cols, bands,y,x,no_of_bands; 
    char header[5];
    float ratio;
    byte **data;
    byte temp;

    rows = decodeImage->bandP[0]->rows;
    cols = decodeImage->bandP[0]->cols;
    bands = decodeImage->bands;
    padding = (byte*)malloc(bit_length);
    max_pos = bit_length*8;

    for(no_of_bands = 0; no_of_bands < bands;no_of_bands++){
	data = getData_Image(decodeImage,no_of_bands);
	if(code_vertical==0){
	  for(y=0;y<rows;y++){
	    x=1;
	    while(x<cols){
		cur_pos = 0;
		if(fread(padding,1,bit_length,fptr) == -1){
		    fprintf(stderr,"Error in reading compressed file");
		    return -1;
	 	}
		while(cur_pos < max_pos){
		    temp = 0;
		    cur_byte = cur_pos/8;
		    left_bit = (8-(cur_pos%8));
		    if(left_bit >= bit_length){
			temp = ((padding[cur_byte])>>(left_bit-bit_length))
					&((1<<bit_length) -1);
			data[y][x++] = temp;
			cur_pos +=bit_length;
		    }
		    else{
			temp = ((padding[cur_byte])<<(bit_length - left_bit))
					&((1<<bit_length) -1);
			cur_pos += left_bit;
			cur_byte = cur_pos/8;
			left_bit = bit_length - left_bit;
			temp |=(padding[cur_byte]) >> (8 - left_bit);
			data[y][x++] = temp;
			cur_pos += left_bit;
		    }
		    if(x == cols)
		   	break;
		}
	    }
	  }
	}
	else{
	  for(x=0;x<cols;x++){
	    y=1;
	    while(y<rows){
		cur_pos = 0;
		if(fread(padding,1,bit_length,fptr) == -1){
		    fprintf(stderr,"Error in reading compressed file");
		    return -1;
	 	}
		while(cur_pos < max_pos){
		    temp = 0;
		    cur_byte = cur_pos/8;
		    left_bit = (8-(cur_pos%8));
		    if(left_bit >= bit_length){
			temp = ((padding[cur_byte])>>(left_bit-bit_length))
					&((1<<bit_length) -1);
			data[y++][x] = temp;
			cur_pos +=bit_length;
		    }
		    else{
			temp = ((padding[cur_byte])<<(bit_length - left_bit))
					&((1<<bit_length) -1);
			cur_pos += left_bit;
			cur_byte = cur_pos/8;
			left_bit = bit_length - left_bit;
			temp |=(padding[cur_byte]) >> (8 - left_bit);
			data[y++][x] = temp;
			cur_pos += left_bit;
		    }
		    if(y == rows)
		   	break;
		}
	    }
	  }
	}
    }
    free(padding);

    return 0;
}
   

static int read_raw_DPCM(Image *decodeImage, Image *sign_Image,int bit_length,
			FILE *fptr){
    int cur_pos,max_pos,cur_byte,temp_pos, left_bit;
    byte *padding;
    int rows, cols, bands,y,x,no_of_bands; 
    float ratio;
    byte **data,**sign_data;
    byte temp, max_data,min_data,max_sign, min_sign, mask_in;
    byte sign_bit;

    if(do_clipping == 1){
	return read_raw_DPCM_clipping(decodeImage,bit_length,fptr);
    }

    rows = decodeImage->bandP[0]->rows;
    cols = decodeImage->bandP[0]->cols;
    bands = decodeImage->bands;
    padding = (byte*)malloc(bit_length);
    max_pos = bit_length*8;

    max_data = (1<<(bit_length-1)) - 2;
    max_sign = max_data + 1;
    min_data = (1<<(bit_length-1)) - 1;
    min_sign = min_data + 1;
    mask_in = (1<<bit_length)-1;

    for(no_of_bands = 0; no_of_bands < bands;no_of_bands++){
	data = getData_Image(decodeImage,no_of_bands);
	sign_data = getData_Image(sign_Image,no_of_bands);
	if(code_vertical == 0){
	  for(y=0;y<rows;y++){
	    x=1;
	    while(x<cols){
		cur_pos = 0;
		if(fread(padding,1,bit_length,fptr) == -1){
		    fprintf(stderr,"Error in reading compressed file");
		    return -1;
	 	}
		while(cur_pos < max_pos){
		    temp = 0;
		    cur_byte = cur_pos/8;
		    left_bit = (8-(cur_pos%8));
		    if(left_bit >= bit_length){
			temp = ((padding[cur_byte])>>(left_bit-bit_length))
					&mask_in;
	    		sign_bit = temp & min_sign;
	    		if(sign_bit)
		            temp = ~temp + 1;
	    		temp &= mask_in;
			if(data[y][x]==0){
			    if(sign_bit)
			        sign_data[y][x] = 1;
			    else
				sign_data[y][x] = 0;
			}
			data[y][x] += temp;
			if((temp < max_sign && sign_bit ==0) ||
			   (temp < min_sign && sign_bit)){
			    x++;
			}
			cur_pos +=bit_length;
		    }
		    else{
			temp = ((padding[cur_byte])<<(bit_length - left_bit))
					&mask_in;
			cur_pos += left_bit;
			cur_byte = cur_pos/8;
			left_bit = bit_length - left_bit;
			temp |=(padding[cur_byte]) >> (8 - left_bit);
	    		sign_bit = temp & min_sign;
	    		if(sign_bit)
		            temp = ~temp + 1;
	    		temp &= mask_in;
			if(data[y][x]==0){
			    if(sign_bit)
			        sign_data[y][x] = 1;
			    else
				sign_data[y][x] = 0;
			}
			data[y][x] += temp;
			if((temp < max_sign && sign_bit ==0) || 
			   (temp < min_sign && sign_bit)){
			    x++;
			}
			cur_pos += left_bit;
		    }
		    if(x >= cols)
		   	break;
		}
	    }
	  }
	}
	else{
	  for(x=0;x<cols;x++){
	    y=1;
	    while(y<rows){
		cur_pos = 0;
		if(fread(padding,1,bit_length,fptr) == -1){
		    fprintf(stderr,"Error in reading compressed file");
		    return -1;
	 	}
		while(cur_pos < max_pos){
		    temp = 0;
		    cur_byte = cur_pos/8;
		    left_bit = (8-(cur_pos%8));
		    if(left_bit >= bit_length){
			temp = ((padding[cur_byte])>>(left_bit-bit_length))
					&mask_in;
	    		sign_bit = temp & min_sign;
	    		if(sign_bit)
		            temp = ~temp + 1;
	    		temp &= mask_in;
			if(data[y][x]==0){
			    if(sign_bit)
			        sign_data[y][x] = 1;
			    else
				sign_data[y][x] = 0;
			}
			data[y][x] += temp;
			if((temp < max_sign && sign_bit ==0) ||
			   (temp < min_sign && sign_bit)){
			    y++;
			}
			cur_pos +=bit_length;
		    }
		    else{
			temp = ((padding[cur_byte])<<(bit_length - left_bit))
					&mask_in;
			cur_pos += left_bit;
			cur_byte = cur_pos/8;
			left_bit = bit_length - left_bit;
			temp |=(padding[cur_byte]) >> (8 - left_bit);
	    		sign_bit = temp & min_sign;
	    		if(sign_bit)
		            temp = ~temp + 1;
	    		temp &= mask_in;
			if(data[y][x]==0){
			    if(sign_bit)
			        sign_data[y][x] = 1;
			    else
				sign_data[y][x] = 0;
			}
			data[y][x] += temp;
			if((temp < max_sign && sign_bit ==0) || 
			   (temp < min_sign && sign_bit)){
			    y++;
			}
			cur_pos += left_bit;
		    }
		    if(y >= rows)
		   	break;
		}
	     }
	  }
	}
    }
    free(padding);
    return 0;
}

static void initialize_struct(int bit_length, float deviation){
	int pos = 1<<(bit_length-1);

	lloyd_max_level_cal = (short*)malloc(sizeof(short)*pos);
	lloyd_max_value_cal = (short*)malloc(sizeof(short)*pos);
	pos--;
	lloyd_max_level_cal[pos] = 255;
	lloyd_max_value_cal[pos] = lloyd_max_value[bit_length-1][pos]
				    * deviation + 0.5;
	do{
	    pos --;
	    if(pos < 0)
		break;
	    lloyd_max_value_cal[pos] = lloyd_max_value[bit_length-1][pos]
				    	* deviation + 0.5;
	    lloyd_max_level_cal[pos] = lloyd_max_level[bit_length-1][pos+1] 
				    	* deviation + 0.5;
	}while(1);
}

int dpc_compress(Image *inputImage, char *filename,float ratio, 
			int bit_length,int clipping, int direction, 
			int origin, float deviation){
    FILE *fptr;
    int mean_value;    
    int rows, cols, bands,no_of_bands; 
    Image *duplicate;
    struct stat s_buf;
    long counter;
    int clip[2];

    fptr = fopen(filename,"wb");
    if(fptr == NULL){
	fprintf(stderr,"cannot open file: %s for writing\n",filename);
	if(inputImage) delete_Image(inputImage);
	if(duplicate) delete_Image(duplicate);
	return -1;
    }

    /*write header "dpcm" into file*/
    putc((int)'d',fptr);
    putc((int)'p',fptr);
    putc((int)'c',fptr);
    putc((int)'m',fptr);

    /*record rows, cols, bands*/
    rows = inputImage->bandP[0]->rows;
    cols = inputImage->bandP[0]->cols;
    bands = inputImage->bands;
    
    if(origin == 3)
    	clipping = 1;

    fwrite(&rows,sizeof(int),1,fptr);
    fwrite(&cols,sizeof(int),1,fptr);
    fwrite(&bands,sizeof(int),1,fptr);    
    fwrite(&bit_length,sizeof(int),1,fptr);
    fwrite(&direction,sizeof(int),1,fptr);
    fwrite(&clipping,sizeof(int),1,fptr);
    fwrite(&origin,sizeof(int),1,fptr);
    fwrite(&deviation,sizeof(float),1,fptr);

    code_vertical = direction;
    do_clipping = clipping;
   
     
    /*record mean and normalization factor*/
    fwrite(&ratio,sizeof(float),1,fptr);

    for(no_of_bands = 0; no_of_bands < bands;no_of_bands++){
    	mean_value = getmean_Image(inputImage, no_of_bands);
    	fwrite(&mean_value,sizeof(int),1,fptr);
    }


    /*write down image data of first row*/
    Record_first_data(fptr,inputImage);

    duplicate = duplicate_Image(inputImage);
    if(clipping == 0){
	clip[0] = -255;
	clip[1] = 255;
    }
    else{
	clip[0] = -1 * (1<<(bit_length-1));
	clip[1] = (1<<(bit_length-1))-1;
    }
    if(origin == 3){
	initialize_struct(bit_length, deviation);
    }

    Predict_DPCM(inputImage,duplicate,mean_value,ratio,origin,clip);
   
    if(origin != 3)
    	Quantize_Predict(inputImage,duplicate);

    store_DPCM(fptr,inputImage, duplicate,bit_length);

    /*fsync(fileno(fptr));*/
	fflush(fptr);
	fclose(fptr);
    if(stat(filename,&s_buf)==0){
	counter = (long)s_buf.st_size;
 	printf("\nThe original raw data occupies %ld bytes", rows*cols*bands);
 	printf("\nThe compressed data occupies %ld bytes",counter );
 	printf("\nCompression ratio 1 : %f\n", 
				(rows*cols*bands)/(float)counter);
    }
    if(duplicate) delete_Image(duplicate);
    if(inputImage) delete_Image(inputImage);

    if(origin == 3){
	free(lloyd_max_level_cal);
	free(lloyd_max_value_cal);
    }

    return 0;
}

static void store_DPCM_clipping(FILE *fptr,Image *inputImage,Image *duplicate,
			int bit_length){
    int rows, cols, x,y,bands,no_of_bands;
    byte ** image_data,**new_data;
    byte temp;
    int cur_pos,max_pos,cur_byte,temp_pos, want_bit, left_bit;
    byte *padding;
    int max_data, min_data;



    rows = inputImage->bandP[0]->rows;
    cols = inputImage->bandP[0]->cols;
    bands = inputImage->bands;
    padding = (byte*)malloc(bit_length);
    max_pos = bit_length*8;

    max_data = (1<<(bit_length-1)) - 1;
    min_data = 1<<(bit_length-1);

    for(no_of_bands=0;no_of_bands<bands;no_of_bands++){
	image_data = getData_Image(inputImage,no_of_bands);
	new_data = getData_Image(duplicate,no_of_bands);
	if(code_vertical == 0){
	  for(y=0;y<rows;y++){
	    x=0;
	    while(x<cols-1){
		cur_pos = 0;
		memset(padding,0,bit_length);
		while(cur_pos < max_pos){
		    if(x == cols-1)
			break;
		    temp = image_data[y][x];
		    /*clipping the extreme value*/
		    if(temp > (byte)max_data && new_data[y][x] == 0)
			temp = max_data;
		    else if(temp > (byte)min_data && new_data[y][x] == 1)
			temp = min_data;

		    if(new_data[y][x] == 1)
			temp = ~temp + 1;
		    else{
			if(temp > (byte)(max_data))
			   temp >>= 1;
		    }
		    temp &= (max_data + min_data);
		    x++;
		    cur_byte = cur_pos/8;
		    want_bit = (8-(cur_pos%8));
		    if(want_bit >= bit_length){
		        padding[cur_byte] |= temp<<(want_bit-bit_length);
			cur_pos += bit_length;
		    }
		    else{
			padding[cur_byte] |= temp >>(bit_length-want_bit);
			cur_pos += want_bit;	
			cur_byte = cur_pos/8;
			want_bit = bit_length - want_bit;
			padding[cur_byte] |= temp<<(8-want_bit);
			cur_pos += want_bit;
		    }
		}
		fwrite(padding,sizeof(byte),bit_length,fptr);
	    }
	  }
	}
	else{
	  for(x=0;x<cols;x++){
	    y=0;
	    while(y<rows-1){
		cur_pos = 0;
		memset(padding,0,bit_length);
		while(cur_pos < max_pos){
		    if(y == rows-1)
			break;
		    temp = image_data[y][x];
		    /*clipping the extreme value*/
		    if(temp > (byte)max_data && new_data[y][x] == 0)
			temp = max_data;
		    else if(temp > (byte)min_data && new_data[y][x] == 1)
			temp = min_data;

		    if(new_data[y][x] == 1)
			temp = ~temp + 1;
		    else{
			if(temp > (byte)(max_data))
			   temp >>= 1;
		    }
		    temp &= (max_data + min_data);
		    y++;
		    cur_byte = cur_pos/8;
		    want_bit = (8-(cur_pos%8));
		    if(want_bit >= bit_length){
		        padding[cur_byte] |= temp<<(want_bit-bit_length);
			cur_pos += bit_length;
		    }
		    else{
			padding[cur_byte] |= temp >>(bit_length-want_bit);
			cur_pos += want_bit;	
			cur_byte = cur_pos/8;
			want_bit = bit_length - want_bit;
			padding[cur_byte] |= temp<<(8-want_bit);
			cur_pos += want_bit;
		    }
		}
		fwrite(padding,sizeof(byte),bit_length,fptr);
	    }
	  }
	}
    }
    free(padding);
}	
    

static void
store_DPCM(FILE *fptr,Image *inputImage,Image *duplicate,int bit_length){
    int rows, cols, x,y,bands,no_of_bands;
    byte ** image_data,**new_data;
    byte temp;
    int cur_pos,max_pos,cur_byte,temp_pos, want_bit, left_bit;
    byte *padding;
    byte max_data, min_data, max_sign, min_sign;
    byte mask_in;

    if(do_clipping == 1){
	store_DPCM_clipping(fptr,inputImage,duplicate,bit_length);
        return;
    }

    rows = inputImage->bandP[0]->rows;
    cols = inputImage->bandP[0]->cols;
    bands = inputImage->bands;
    padding = (byte*)malloc(bit_length);
    max_pos = bit_length*8;

    max_data = (1<<(bit_length-1)) - 2;
    max_sign = max_data + 1;
    min_data = (1<<(bit_length-1)) - 1;
    min_sign = min_data + 1;

    mask_in = (1<<bit_length) - 1;

    for(no_of_bands=0;no_of_bands<bands;no_of_bands++){
	image_data = getData_Image(inputImage,no_of_bands);
	new_data = getData_Image(duplicate,no_of_bands);
	if(code_vertical == 0){
	  for(y=0;y<rows;y++){
	    x=0;
	    do{
		cur_pos = 0;
		memset(padding,0,bit_length);
		while(cur_pos < max_pos){
		    if(x == cols-1)
			break;
		    temp = image_data[y][x];
		    if(temp > (byte)max_data && new_data[y][x] == 0){
			while(temp > (byte)max_data){
			    temp -= max_sign;
			    cur_byte = cur_pos/8;
			    want_bit = (8-(cur_pos%8));
			    if(want_bit >= bit_length){
			       padding[cur_byte] |= max_sign<<
						(want_bit-bit_length);
				cur_pos += bit_length;
			    }
			    else{
				padding[cur_byte] |= max_sign >>
							(bit_length-want_bit);
				cur_pos += want_bit;	
				cur_byte = cur_pos/8;
				want_bit = bit_length - want_bit;
				padding[cur_byte] |= max_sign<<(8-want_bit);
				cur_pos += want_bit;
			    }
			    if(cur_pos == max_pos ){
				fwrite(padding,1,bit_length,fptr);
				memset(padding,0,bit_length);
				cur_pos = 0;
			    }
			}
		    }	
		    else if(temp > (byte)min_data && new_data[y][x] == 1){
			while(temp > (byte)min_data){
			    temp -= min_sign;
			    cur_byte = cur_pos/8;
			    want_bit = (8-(cur_pos%8));
			    if(want_bit >= bit_length){
			        padding[cur_byte] |= ((~min_sign+1)&mask_in)<<
						(want_bit-bit_length);
				cur_pos += bit_length;
			    }
			    else{
				padding[cur_byte]|=(int)((~min_sign+1)&mask_in)
						>>(bit_length-want_bit);
				cur_pos += want_bit;	
				cur_byte = cur_pos/8;
				want_bit = bit_length - want_bit;
				padding[cur_byte] |= ((~min_sign+1)&mask_in)<<
							      (8-want_bit);
				cur_pos += want_bit;
			    }
			    if(cur_pos == max_pos){
				fwrite(padding,1,bit_length,fptr);
				memset(padding,0,bit_length);
				cur_pos = 0;
			    }
			}
		    }
		    if(new_data[y][x] == 1)
			temp = ~temp + 1;
		    temp &= mask_in;
		    x++;
		    cur_byte = cur_pos/8;
		    want_bit = (8-(cur_pos%8));
		    if(want_bit >= bit_length){
		        padding[cur_byte] |= temp<<(want_bit-bit_length);
			cur_pos += bit_length;
		    }
		    else{
			padding[cur_byte] |= temp >>(bit_length-want_bit);
			cur_pos += want_bit;	
			cur_byte = cur_pos/8;
			want_bit = bit_length - want_bit;
			padding[cur_byte] |= temp<<(8-want_bit);
			cur_pos += want_bit;
		    }
		}
		fwrite(padding,1,bit_length,fptr);
	    }while(x<cols-1);
	  }
	}
        else{
	  for(x=0;x<cols;x++){
	    y=0;
	    do{
		cur_pos = 0;
		memset(padding,0,bit_length);
		while(cur_pos < max_pos){
		    if(y == rows-1)
			break;
		    temp = image_data[y][x];
		    if(temp > (byte)max_data && new_data[y][x] == 0){
			while(temp > (byte)max_data){
			    temp -= max_sign;
			    cur_byte = cur_pos/8;
			    want_bit = (8-(cur_pos%8));
			    if(want_bit >= bit_length){
			       padding[cur_byte] |= max_sign<<
						(want_bit-bit_length);
				cur_pos += bit_length;
			    }
			    else{
				padding[cur_byte] |= max_sign >>
							(bit_length-want_bit);
				cur_pos += want_bit;	
				cur_byte = cur_pos/8;
				want_bit = bit_length - want_bit;
				padding[cur_byte] |= max_sign<<(8-want_bit);
				cur_pos += want_bit;
			    }
			    if(cur_pos == max_pos ){
				fwrite(padding,1,bit_length,fptr);
				memset(padding,0,bit_length);
				cur_pos = 0;
			    }
			}
		    }	
		    else if(temp > (byte)min_data && new_data[y][x] == 1){
			while(temp > (byte)min_data){
			    temp -= min_sign;
			    cur_byte = cur_pos/8;
			    want_bit = (8-(cur_pos%8));
			    if(want_bit >= bit_length){
			        padding[cur_byte] |= ((~min_sign+1)&mask_in)<<
						(want_bit-bit_length);
				cur_pos += bit_length;
			    }
			    else{
				padding[cur_byte]|=(int)((~min_sign+1)&mask_in)
						>>(bit_length-want_bit);
				cur_pos += want_bit;	
				cur_byte = cur_pos/8;
				want_bit = bit_length - want_bit;
				padding[cur_byte] |= ((~min_sign+1)&mask_in)<<
							      (8-want_bit);
				cur_pos += want_bit;
			    }
			    if(cur_pos == max_pos){
				fwrite(padding,1,bit_length,fptr);
				memset(padding,0,bit_length);
				cur_pos = 0;
			    }
			}
		    }
		    if(new_data[y][x] == 1)
			temp = ~temp + 1;
		    temp &= mask_in;
		    y++;
		    cur_byte = cur_pos/8;
		    want_bit = (8-(cur_pos%8));
		    if(want_bit >= bit_length){
		        padding[cur_byte] |= temp<<(want_bit-bit_length);
			cur_pos += bit_length;
		    }
		    else{
			padding[cur_byte] |= temp >>(bit_length-want_bit);
			cur_pos += want_bit;	
			cur_byte = cur_pos/8;
			want_bit = bit_length - want_bit;
			padding[cur_byte] |= temp<<(8-want_bit);
			cur_pos += want_bit;
		    }
		}
		fwrite(padding,1,bit_length,fptr);
	    }while(y<rows-1);
	  }
	}
    }
    free(padding);
}	
  

void Quantize_Predict(Image *inputImage, Image *duplicate){
    int rows, cols, x,y,bands,no_of_bands;
    byte ** image_data,**new_data;
    int temp;
 
    rows = inputImage->bandP[0]->rows;
    cols = inputImage->bandP[0]->cols;
    bands = inputImage->bands;
    for(no_of_bands=0;no_of_bands<bands;no_of_bands++){
	image_data = getData_Image(inputImage,no_of_bands);
	new_data = getData_Image(duplicate,no_of_bands);
	if(code_vertical == 0){
	    for(y=0;y<rows;y++){
	        for(x=0;x<cols-1;x++){
		   new_data[y][x] = (image_data[y][x] >= new_data[y][x+1])? 0:1;
   		   temp =(image_data[y][x]) - (new_data[y][x+1]);
		   image_data[y][x] = abs(temp);
		}
	    }
	}
	else{
	    for(x=0;x<cols;x++){
	        for(y=0;y<rows-1;y++){
		   new_data[y][x] = (image_data[y][x] >= new_data[y+1][x])? 0:1;
   		   temp =(image_data[y][x]) - (new_data[y+1][x]);
		   image_data[y][x] = abs(temp);
		}
	    }
	}
    }
}
	    

    
static void Predict_DPCM(Image *inputImage,Image *sign_Image,int mean_value,
			float ratio, int origin,int clipping[]){
    int rows, cols, x,y,bands,no_of_bands;
    long summation = 0;
    byte ** image_data,**new_data;
    short reconstruct,diff, level,i,sign;

    rows = inputImage->bandP[0]->rows;
    cols = inputImage->bandP[0]->cols;
    bands = inputImage->bands;

    for(no_of_bands=0;no_of_bands<bands;no_of_bands++){
	image_data = getData_Image(inputImage,no_of_bands);
	new_data = getData_Image(sign_Image,no_of_bands);
	if(code_vertical == 0){
	    for(y=0;y<rows;y++){
	    	for(x=0;x<cols;x++){
		    if(origin == 1)
		        image_data[y][x] =(byte)(ratio*(float)(image_data[y][x])
					+(1.0-ratio)*mean_value + 0.5);
		    else if(origin == 2){
			reconstruct = x==0?image_data[y][0]:
				(reconstruct*ratio+(1.0-ratio)*mean_value+0.5);
			diff = reconstruct - image_data[y][x];
			if(diff < clipping[0]) 
			diff = clipping[0];
			else if(diff > clipping[1]) 
			    diff = clipping[1];
			reconstruct -=diff;
			image_data[y][x] = (byte)(ratio*(float)reconstruct
					+(1.0-ratio)*mean_value + 0.5);
		    }
		    else if(origin == 3){
			i = 0;
			reconstruct = x==0?image_data[y][0]:
				(reconstruct*ratio+(1.0-ratio)*mean_value+0.5);
			if(x != 0){
			    diff = reconstruct - image_data[y][x];
			    sign = diff < 0 ? -1: 1;
			    diff = abs(diff);
			    while(diff > lloyd_max_level_cal[i]) i++;
			    diff = lloyd_max_value_cal[i]*sign;
			    reconstruct -=diff;
			    new_data[y][x-1] = sign>0?0:1;
			    image_data[y][x-1] = sign>0?i:i+1;
			}
		    }
	        }
	    }
	}
	else{
	    for(x=0;x<cols;x++){
	    	for(y=0;y<rows;y++){
		    if(origin == 1)
		        image_data[y][x] =(byte)(ratio*(float)(image_data[y][x])
					+(1.0-ratio)*mean_value + 0.5);
		    else if(origin == 2){
			reconstruct = y==0?image_data[0][x]:
				(reconstruct*ratio+(1.0-ratio)*mean_value+0.5);
			diff = reconstruct - image_data[y][x];
			if(diff < clipping[0]) 
			    diff = clipping[0];
			else if(diff > clipping[1]) 
			    diff = clipping[1];
			reconstruct -=diff;
			image_data[y][x] = (byte)(ratio*(float)reconstruct
					+(1.0-ratio)*mean_value + 0.5);
		    }
		    else if(origin == 3){
			i = 0;
			new_data[y][x] = 0;
			reconstruct = y==0?image_data[0][x]:
				(reconstruct*ratio+(1.0-ratio)*mean_value+0.5);
			if(y != 0){
			    diff = reconstruct - image_data[y][x];
			    sign = diff < 0 ? -1: 1;
			    diff = abs(diff);
			    while(diff > lloyd_max_level_cal[i]) i++;
			    diff = lloyd_max_value_cal[i]*sign;
			    reconstruct -=diff;
			    new_data[y-1][x] = sign>0?0:1;
			    image_data[y-1][x] = sign>0?i:i+1;
			}
		    }
	        }
	    }
	}
    }
}
    



static void Record_first_data(FILE *fptr, Image *inputImage){
    int rows,y,bands,no_of_bands,x,cols;
    byte ** data;

    rows = inputImage->bandP[0]->rows;
    cols = inputImage->bandP[0]->cols;
    bands = inputImage->bands;
    
    for(no_of_bands=0;no_of_bands<bands;no_of_bands++){
	data = getData_Image(inputImage,no_of_bands);
	if(code_vertical == 0){
	    for(y=0;y<rows;y++)
	    	fwrite(data[y],1,1,fptr);    
	}
	else{
	    for(x=0;x<cols;x++)
		fwrite(data[0]+x,1,1,fptr);
	}
    }
}


static int getmean_Image(Image *inputImage, int no_of_bands){
    int rows, cols, x,y;
    long summation = 0;
    byte ** data;

    rows = inputImage->bandP[0]->rows;
    cols = inputImage->bandP[0]->cols;
    data = getData_Image(inputImage,no_of_bands);
    for(y=0;y<rows;y++)
        for(x=0;x<cols;x++)
	summation += data[y][x];
    summation = ((float)summation)/(rows*cols);

    return summation;
}
		

    
