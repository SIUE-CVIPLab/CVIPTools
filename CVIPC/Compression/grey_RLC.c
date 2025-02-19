/******************************************************************************
    ======================================================================
    Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
    ======================================================================

                   Name: glr
          Expanded Name; Grey Level Runlength Coding
             Parameters: Pointer to original image of type Image
                Returns: Image Pointer
            Description: Performs Grey Level Runlength coding and decoding  
            Diagnostics: All filenames should be entered without extensions
    Initial Coding Date: 1/2/94
Last Modifications Made: 1/2/94
             References: None
              Author(s): Muthu Kumar, Kun Luo
                         Southern Illinois University @ Edwardsville ________________________________________________________________________________
 
 The 'glr' main function provides sub menu for Grey Level Runlength coding Algorithm. Two functions are incorporated in the submenu via glr_compress() and glr_decompress(). These functions perform compression and decompression respectively. The main function 'glr' takes pointer to the input image as the arguments. 
*******************************************************************************/

#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "grey_RLC.h"
#include <sys/types.h>
#include <sys/stat.h>

extern char temp_dir[100];
extern char *Cmpr_Name[];


/*Image *glr_decompress(char *filename);
Image *glr_decompress(FILE *dec); */

static long int encode( long int i1, int pix1[1026],long int comp1, FILE *enc); 

/*Image* glr(Image *input_Image, CVIP_BOOLEAN *remap)
  {
   char select[6], *fname=NULL; 
   int i, j, bands, cols, rows, count = 0, done=0;
   byte **image_array, **red_plane, **green_plane, **blue_plane, **error_array;
   IMAGE_FORMAT image;
   COLOR_FORMAT color;
   CVIP_TYPE data_type;
   FORMAT data_format;
   Image *decodImage;
 
   rows = input_Image->image_ptr[0]->rows;
   cols = input_Image->image_ptr[0]->cols; 
   bands = getNoOfBands_Image(input_Image);
   image_array = (byte**) input_Image->image_ptr[0]->rptr;
   fname=glr_compress(rows,cols,bands,input_Image);
   if(fname == NULL)
	return NULL;
   decodImage=glr_decompress(fname);
   free(fname);
   *remap=CVIP_NO;
   return decodImage ;
} */


/******************************************************************************
                   Name: glr_compress
          Expanded Name: Grey Level Runlength Coding
             Parameters: Image * inputImage : pointer to the input image
								 char *filename: compressed data file
								 int win: window size
                Returns: Image Pointer
            Description: This function is called from the main function glr(..).
                         For more description read the bottom of this header.  
            Diagnostics: All filenames should be entered without extensions
    Initial Coding Date: 1/2/94
Last Modifications Made: 1/2/94
             References: None
              Author(s): Muthu Kumar
                         Southern Illinois University @ Edwardsville ________________________________________________________________________________
This function is called from the main function glr(..). It takes four parameters namely the height, width,no of bands of the input image and pointer to the input image array. When this routine is in execution it asks the user for the file name to which the compressed image is to be stored. The user has to enter the filename with no extension. The routine automatically appends the extension to the file name. A window length is needed for compression and user is requested to enter it. The valid window length is (1-128). The user is suggested to use winow length from 1-75 as this range gives better results. The higher the window range the higher the compression ratio and vice versa. This compression function usues the routine encode(....) for its operation.

       At the end of the compression, this routine automatically writes to the screen the following data: the size of the original image, size of the compressed file, compression ratio. The compressed file is stored in the filename entered by the user. *******************************************************************************/


int glr_compress(Image *inputImage, char *filename, int win) {
   long  int encode(long int i, int pix[512],long int comp, FILE *enc); 
   int x,y,length,lower,higher,diff,ref,pixe,no_band,
		rows, cols, bands;
   byte **image_array;
   int value,k,f,gvalue,agvalue,j,least,heighest,ll,leng;
   long int comp,dum;
   long int len,i;
   FILE *enc;
   int *pix, grpix[55],l,flag,test,pixel[1025];
   float ratio;
    struct stat s_buf;
    long counter;

   rows = inputImage->image_ptr[0]->rows;
   cols = inputImage->image_ptr[0]->cols; 
   bands = getNoOfBands_Image(inputImage);

    pix = (int*)malloc(sizeof(int)*100025);

   if ((enc = fopen(filename, "w+b"))!=NULL)
    {
     putc(103,enc);
     putc(108,enc);
     putc(114,enc);
     fwrite(&rows,sizeof(short int), 2,enc);
     fwrite(&cols,sizeof(short int), 2,enc);
     fwrite(&bands,sizeof(short int), 2,enc);
     for(no_band = 0; no_band < bands;no_band++){
     image_array = getData_Image(inputImage,no_band);
     for (y=0; y<rows; y++)
      for(x=0; x<cols; x++)
       { 
        pixe = image_array[y][x];
	if(pixe < 16) pixe = 16;
        if(pixe > 239) pixe = 239;
	image_array[y][x] = pixe;          
       } 
     x=0; len =0; comp =0;
     y=0;
     for (x =0; x< cols ; x++)
       pixel[x] = image_array[y][x];          
     x=0;     
     for (; ;)
      {        
       i=0;
       j=0;
       if(y>=rows) {x=0;break;}
       ref = pixel[x];    
       x++;
       if(x>=cols) 
        {
         y++; 
         if(y>= rows) 
          {
           pix[i]=ref; 
           comp = encode(i,pix,comp,enc);
           len =len+i+1;x=0;
           break;
          }
         for (x =0; x< cols ; x++) 
           pixel[x] = image_array[y][x];
         x=0;
        } 
     if((ref-(win-1)) <0)
      {
       diff=win-1-ref;
       lower = 0;
      }
       else
        {
         diff=0;
         lower = ref -(win-1);
        }
     higher = ref + (win-1);
     pix[i] =pixel[x];
     least =ref;
     heighest = ref;
     for (; ;)
      {
       flag = 0;     
       pix[i] = pixel[x]; 
       if((pix[i] > higher) || (pix[i] < lower))
        { 
         pix[i]=ref;
         comp = encode(i,pix,comp,enc);
         len=len+i+1;
         break;
        }
     k = ref - pix[i];
     if (k > 0) value = 1;
     if (k < 0) value = 2;
     if (k == 0) value = 3;
     switch (value)
      {
       case 1: if(pix[i] >= least) break;
        	else
	         {
		  higher = higher-(least-pix[i]);
		  least = pix[i];
		 }
       case 2: if(pix[i] <= heighest) break;
	        else
		 { 
		  ll=heighest;
		  heighest = pix[i];
	          if(pix[i] > (ref + diff))
	          lower = lower + (pix[i]-ll-diff);
		 }
       case 3:  break;
       default : break;
      }
     i++;
     x++; 
     if(x>=cols) 
      { 
       x=0;
       y++;
       if(y>=rows)
        {
         pix[i]=ref;
         comp = encode(i,pix,comp,enc);
         len=len+i+1;
	 x=0;
         break; 
        }
       for (x =0; x< cols ; x++) 
        pixel[x] = image_array[y][x];
       x=0;
      }
    } 
  }
 }
    /*fsync(fileno(enc));*/
	putc(216,enc);
	fflush(enc);
	fclose(enc);
    if(stat(filename,&s_buf)==0){
	counter =(long)s_buf.st_size;
 printf("\nThe original raw data occupies %ld bytes", rows*cols*bands);
 printf("\nThe compressed data occupies %ld bytes",counter );
 printf("\nCompression ratio 1 : %f\n", (rows*cols*bands)/(float)counter);
    }
   

}   
  else {
    printf("error opening the file");
    free(pix);
    if (inputImage) delete_Image(inputImage);
    return (-1);
  }

free(pix);
if (inputImage) delete_Image(inputImage);
return 0;
}

static long int
encode( long int i1, int pix1[1026],long int comp1, FILE *enc) {
  int j,b,greylevel,t,m,comp,dum,flag=0;
  long int total,k;
  total=0;
  for(t=0; t<=i1; t++){
    total = total+pix1[t];
   }
  greylevel = total/(i1+1);	  
  k=i1+1;
  while (k>=512)
    { 
      if(flag==0)
        {
          putc(greylevel, enc);
          flag = 1;
          putc(1,enc);
          comp1 = comp1+2;
        }
        else {putc(1,enc); comp1++;}
          k=k-512;                                     
    }     
  if(k>=256)
    {
      k=k-256;
      if(flag==0)
        { 
          putc(greylevel,enc);
          putc(0,enc);
          comp1 = comp1+2;
          flag=1;
        }
         else {putc(0,enc); comp1++;}		 
    }  
  if(k>=128)
    {
      k=k-128;
      if(flag==0)
        {
          putc(greylevel,enc); 
          putc(255,enc);
          comp1 = comp1+2;
          flag=1;
        }
         else {putc(255,enc); comp1++;}
     }
  if(k>=64)
    {
      k=k-64;
      if(flag==0)
        {
          putc(greylevel, enc);
          putc(254,enc);
          comp1 = comp1+2; 
          flag=1;
        }
         else  {putc(254,enc); comp1++;}    
    }
  if(k>=32) 
    {
      k= k-32;
      if(flag==0)
        {
          putc(greylevel, enc);
          putc(253,enc);
          comp1 = comp1+2;
          flag=1; 
        }
         else {putc(253,enc);comp1++;}
    }
  if((k>=28)&&(k<32))
    {
      k=k-28;
      if(flag==0)
        {
          putc(greylevel,enc);
          putc(252,enc);
          comp1 = comp1+2; 
          flag=1;
        }
         else {putc(252,enc);comp1++;}
    }
  if((k>=16)&&(k<=27))
    { 
      k=k+224;
      if(flag==0)
        {
          putc(greylevel,enc);           
          putc(k,enc);
	  comp1 = comp1+2;
          flag=1;
        }
         else {putc(k,enc);comp1++;} 
      k=0;
    }
  if((k>=2)&&(k<=15)) 
    {
      if (flag==0)
        {
          putc(greylevel,enc);  
          putc(k,enc);
          comp1 = comp1+2;
          flag=1;
        }
         else {putc(k,enc);comp1++;} 
      k=0;
    }
  if(k==1)
    {
      putc(greylevel,enc);
      comp1++;  
      k=0;
    }	  
  return comp1;
}


/******************************************************************************
                   Name: glr_decompress
          Expanded Name: Grey Level Runlength deCoding
             Parameters: char *filename : compressed filename
                Returns: Image Pointer
            Description: This function is called from the main function glr(..).
                         For more description read the bottom of this header.  
            Diagnostics: All filenames should be entered without extensions
    Initial Coding Date: 1/2/94
Last Modifications Made: 1/2/94
             References: None
              Author(s): Muthu Kumar
                         Southern Illinois University @ Edwardsville ________________________________________________________________________________
This function is called from the main function glr_decompress(..). It takes single parameter namely the compressed filename. While on execution this function reads the compressed file and decompress it. when decompression is completed it returns the pointer to the decoded image.
*******************************************************************************/
Image *glr_decompress(char *filename)
 {
    int k1,y,x,aa,bb,byte1,byte2,l,m,test1,test2,d,e,rows,cols,bands,leng;
    char a,b,c,dd;
    Image *decodeImage; 
    byte **image_array;
    FILE *dec;
    char ch[]=".btc";

    if((dec = fopen(filename, "rb")) == NULL)  {
       printf("\nError opening the file\n");
       return NULL;
    }

    decodeImage = glr_decompression(dec);
    fclose(dec);
 
    return decodeImage;
}

Image *glr_decompression(FILE *dec)
  {
    int x,y,run,grey,i,k,l,a,b,dummy,bands,rows,cols,leng,no_band;
    long int count =0;
    double rmse,psnr,mse=0.0;
    char aa,bb,cc,ch[]=".glr";
    /* extension: .glr */
    Image *decodeImage;
    byte **image_array;
    x=0; y=0;
  
    aa=getc(dec);
    bb=getc(dec);
    cc=getc(dec);      
    if(aa!= 'g' || bb != 'l' || cc != 'r')
      { printf("\n\n\t\tInvalid File format\n"); return NULL;}
    fread(&rows,sizeof(short int), 2,dec);
    fread(&cols,sizeof(short int), 2,dec); 
    fread(&bands,sizeof(short int), 2,dec);
    if(bands == 1)
        decodeImage=new_Image(PGM,GRAY_SCALE,bands,rows,cols,CVIP_BYTE,REAL);
    else
	decodeImage=new_Image(PPM,RGB,bands,rows,cols,CVIP_BYTE,REAL);
    for(no_band = 0; no_band < bands;no_band++){
        image_array = getData_Image(decodeImage,no_band);    
	y=x=0;
	mse=0.0;  
	count = 0;          
    while(!feof(dec))
      {
	if(no_band == 0) grey = fgetc(dec);
	while((grey>15)&&(grey<240))
          {
            if(feof(dec)!=0) break;
	    run = fgetc(dec);
            if((run<16)||(run>239))
	      while((run<16)||(run>239))
		{ 
		  if(run==1) i= 512;
		  else if(run==0) i= 256;
		  else if(run==255) i= 128;
		  else if(run==254) i=64;
		  else if(run==253) i=32;
		  else if((run>=240)&&(run<=252)) i = run -224;
		  else if((run>=2)&&(run<=15)) i =run;
		  for(k=0; k<i; k++)
	            { 
                      image_array[y][x] = grey;
                      count++;
                      x++;
		      if(x >= cols) 
			{
			  x=0;
			  y++;
		        }
		      if(y>=rows){x=0; break;}
		    }
                  if(feof(dec) != 0) break;
	          run=fgetc(dec);                        
	        }
	      else
	        {
	          image_array[y][x] = grey;     
                  count++;                 
	          x++;
		  if(x>=cols) 
	            {
		      x=0;
		      y++;
	            }
			  
		 }
             grey=run;
             if(y>=rows){x=0; break; }
	   }
	 if(y>=rows) 
           { x=0;
	     break;
           }

       }
   }
/*     printf("\nDecoding completed successfully\n");*/
     decodeImage->image_format = GLR;
     return decodeImage;       
   }

