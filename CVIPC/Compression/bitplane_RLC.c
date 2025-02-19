/******************************************************************************
    ======================================================================
    Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
    ======================================================================

                   Name: bitplane
          Expanded Name: Bitplane Runlength Coding
             Parameters: Pointer to original image of type Image
                Returns: Image Pointer
            Description: Decomposes the greylevel image into 8 bitplanes via 
                         highest order(7th order) bitplane to lowest order
                         bitplane(0th order). Then each bitplane is runlength
                         coded and written in a separate file  
            Diagnostics: All filenames should be entered without extensions
    Initial Coding Date: 1/2/94
Last Modifications Made: 
             References: None
              Author(s): Muthu Kumar, Kun Luo
                         Southern Illinois University @ Edwardsville ________________________________________________________________________________
 
 The 'bitplane' main function provides sub menu for Bitplane Runlength coding Algorithm. Three functions are incorporated in the submenu via bit_compress() bit_decompress() and bit_planeadd() . These functions perform compression and decompression and addition of bitplanes respectively. The main function 'bitplane' takes pointer to the input image as the arguments. 
*******************************************************************************/

#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "bitplane_RLC.h"
#include <sys/types.h>
#include <sys/stat.h>

extern char temp_dir[100];
extern char *Cmpr_Name[];
/* moved to hte header file
Image *bitplane_sep(Image *input_Image, char *string);
*/

/*Image*
bitplane(Image *input_Image) {
    char string[50];

    printf("\nSelect bit-plane to retain\n(most significant-7,6,5,4,3,2,1,0-least significant):");
    gets(string);
   
    return bitplane_sep(input_Image, string);
}

Image *bitplane_sep(Image *input_Image, char *string){
    Image *bit_planeadd(char*);
    void bitpre(int,int, byte **);
    byte sect = 0;
	 char filename[30], filenames[30],*returnname;


    char select[6];
    int i, j, count = 0,dum,word;
    byte **image_array;
    Image *decodImage, *errorImage;
    IMAGE_FORMAT image;
    COLOR_FORMAT color;
    CVIP_TYPE data_type;
    FORMAT data_format;
    image = getDataType_Image(input_Image);
    data_format = getDataFormat_Image(input_Image);
    data_type = getFileFormat_Image(input_Image);
    color = getColorSpace_Image(input_Image);
    image_array = (byte**) input_Image->image_ptr[0]->rptr;

	 returnname = (char*)malloc(100);
	 strcpy(returnname,temp_dir);
	 strcat(returnname,"/__"); strcat(returnname, Cmpr_Name[Brc]);
 
    word = '0';
    for(i=0;i<8;i++,word++)
        if(strchr(string,word))
		sect |= (1<<i);
    if (bit_compress(input_Image, returnname, sect) < 0) 
		return (Image *)NULL;
    decodImage=bit_decompress(returnname);
    free(returnname);
    return(decodImage);
}

*/



/******************************************************************************
    
                   Name: bit_compress
          Expanded Name: bitplane compression
             Parameters: char *filename : The filename of the compressed data
								 byte sect: bits to retain
                         Image *inputImage: Input image pointer
                Returns: 0 success
								 -1 failure
            Description: This function is called from the main function  
                         bitplane(..). For more description read the bottom of
                         this header.  
            Diagnostics: All filenames should be entered without extensions
    Initial Coding Date: 1/2/94
Last Modifications Made: 1/2/94
             References: None
              Author(s): Muthu Kumar, Kun Luo
                         Southern Illinois University @ Edwardsville ________________________________________________________________________________
 This function is called from the main function bitplane(..). It takes four parameters namely the height, width, no of bands of the input image and pointer to the input image array. When this routine is in execution it asks the user for the file name to which the compressed image is to be stored. The user has to enter the filename with no extension. The input image is decomposed into 8 binary images. Each decomposed image correspond to one of the 8 bitplanes of the grey level image. Each bitplane image is separately runlength coded and the compressed image is stored in the file specified by the user. The routine automatically appends the extension and the number of the bitplane(0-7) to the file name. At the end of the compresssion we would be left with 8 binary files  with appropriate bitplane number appended to it.    
 
*******************************************************************************/
int bit_compress(Image *inputImage, char *filename, byte sect )
  {   
    byte **image_array;
    int x,y,length,win,lower,higher,diff,ref,pixel1,no_band,
		 rows, cols, bands;
    int value,k,f,gvalue,agvalue,j,least,heighest,ll,pixel,count,mask,leng;
    long int comp,dum;
    long int len,i;
    FILE *enc;
    char ch[4];
    int tt;
    struct stat s_buf;
    long counter;

    rows = inputImage->image_ptr[0]->rows;
    cols = inputImage->image_ptr[0]->cols; 
    bands = getNoOfBands_Image(inputImage);


    mask=128;
    ch[0]='.';
    ch[1]= '_';
    ch[2]='8';
    ch[3]='\0';

        if ((enc = fopen(filename, "w+b"))==NULL)
          {
	    if (inputImage) delete_Image(inputImage);
            printf("\nError opening the file"); return -1;
          } 
        putc(98,enc);
        putc(114,enc);
        putc(99,enc);
        fwrite(&rows,sizeof(short int), 2,enc);
        fwrite(&cols,sizeof(short int), 2,enc);  
        fwrite(&bands,sizeof(short int), 2,enc);  
        putc((char)sect,enc);

    for(tt=7; tt>=0; tt--)
      { 
        mask =1 <<tt; 
	if(!(mask & sect)) continue;
    for(no_band=0;no_band<bands;no_band++){
	image_array = getData_Image(inputImage,no_band);
        for(y=0;y<rows;y++)
          {
            x=0;
            pixel=image_array[y][x];
            if((image_array[y][0] & mask)!=0) putc(0,enc);
            count=0; 
            for(x=0;x<cols;x++)
              {
                pixel = image_array[y][x];
                if(pixel & mask)
                  {
                    for(; ;)
                      {
                        pixel = image_array[y][x];
						if (pixel & mask)
						{
							count++;
							x++;
							if (x >= cols)
							{
								putc(count, enc);
								break;
							}
							if (count >= 255)
							{
								putc(255, enc);
								if ((image_array[y][x] & mask))
									putc(0, enc);
								x--; count = 0; break;
							}
						
                          }
                           else {putc(count,enc); count=0;x--;break;}
                      }
                 }    
                  else
                    {
                      for(; ;)
                        {
                          pixel = image_array[y][x];
                          if (!(pixel & mask))
                            {     
                              count++;
                              x++;
                              
                              if( x >=cols)
                                {
                                  putc(count,enc);  
                                  break;
                                }
							  if (count >= 255)
							  {
								  putc(255, enc);
								   if(!(image_array[y][x] & mask))
										putc(0, enc); 
								   x--; count = 0; break;
							  }
                            }        
                             else {putc(count,enc); count=0;x--;break;}
                        }    
                    }
               if(x>=cols) break;
             }
         }
     }
    }
    /*fsync(fileno(enc));*/
	 fflush(enc);
    fclose(enc);
    if(stat(filename,&s_buf)==0){
	counter =(long)s_buf.st_size;
 	printf("\nThe original raw data occupies %ld bytes", rows*cols*bands);
	printf("\nThe compressed data occupies %ld bytes",counter );
	printf("\nCompression ratio 1 : %f\n", (rows*cols*bands)/(float)counter);
    }

    if (inputImage) delete_Image(inputImage);
    return 0;
  }  



/******************************************************************************
                   Name: bit_decompress
          Expanded Name: Bitplane decompression
             Parameters: char *filename : compressed filename
                Returns: Image Pointer
            Description: This function is called from the main function
                         bitplane(..). See bottom of this header for more
                         description.  
            Diagnostics: All filenames should be entered without extensions
    Initial Coding Date: 1/2/94
Last Modifications Made: 1/2/94
             References: None
              Author(s): Muthu Kumar, Kun Luo
                         Southern Illinois University @ Edwardsville ________________________________________________________________________________
This function is called from the main function bitplane(..). It takes single parameter namely the compressed filename without any extension. While on execution this function reads each compressed file corressponding to each bitplane (the extension of the filename specifies the bitplane number) and decompress it. when decompression is completed it displays 8 binary images each corresponding to each bitplane. *******************************************************************************/


Image *bit_decompress(char *filename)
  {
    FILE *dec;
    Image *decodeImage;
   
            if(filename == NULL)
	   return NULL;
       	if((dec = fopen(filename, "rb")) == '\0')
	  {
	    printf("\nError opening the file\n");
	    return NULL;
          }    
    decodeImage = (Image *) bit_decompression(dec);
    fclose(dec);

    return decodeImage;
}

Image *bit_decompression(FILE *dec){
    int x,y,run,grey,i,k,l,a,b,high,dummy,pixel,tt,siz,rows,cols,bands,leng;
    long int count =0,no_band;
    double rmse,psnr,mse=0.0;
    char filename[30],ch[4],filenames[30],cha[]="brc",aa,bb,cc;
    byte sect;
    Image *decodeImage;
    byte mask;
    byte **image_array;   

   /*     ch[2]=ch[2]-1;
        strcpy(filenames,filename);
        strcat(filenames,ch);
        strcat(filenames,cha);
*/


        aa=getc(dec);
        bb=getc(dec);
        cc=getc(dec);    
        if(aa != 'b' || bb != 'r' || cc != 'c')
          { printf("\n\n\t\tInvalid File format\n"); exit(0);}
        fread(&rows,sizeof(short int), 2,dec);
        fread(&cols,sizeof(short int), 2,dec);  
        fread(&bands,sizeof(short int), 2,dec); 
   	sect = (byte)getc(dec);
        if(bands == 1)
          decodeImage=new_Image(PGM,GRAY_SCALE,bands,rows,cols,CVIP_BYTE,REAL);
        else
	  decodeImage=new_Image(PPM,RGB,bands,rows,cols,CVIP_BYTE,REAL);
    for(tt=7; tt>=0; tt--)
      { 
 	if(!((mask=1<<tt)&sect))continue;
	
	for(no_band=0;no_band<bands;no_band++){
	    image_array= getData_Image(decodeImage,no_band);
		//for (int t = 0; t < rows; t++)
		//{
		//	for (int r = 0; r < cols; r++)
		//	{
		//		image_array[t][r] = 0;
		//	}
		//}
        x=0; y=0;
        for(; ;)
          {
            if(y>=rows) break;               
            if(feof(dec)) return 0;
            pixel = fgetc(dec);    
            if(pixel==0)
              {
                if(feof(dec)) return(0);
                pixel=fgetc(dec);    
                high = mask;
              }
               else  high=0;    
            for(; ;)
              { 
                for(; ;)
                  {  
                    for(i=0; i<pixel; i++)
                      {
                        image_array[y][x]|=high;
                        x++;
                        if(x>=cols) 
                          { y++; break;}
                      }
                    if(x>=cols) break;
                    if(feof(dec)) return(0);
                    pixel=fgetc(dec); 
                    if(pixel) break;
                      else { if(feof(dec)) return(0);
                             pixel=fgetc(dec); }
 
                  } 
                if(x>=cols) {x=0;break;} 
                if(high==mask) high=0;
                  else if (high==0) high=mask;  
              }
          }         
	}
       }
   decodeImage->image_format = BRC;
return decodeImage;
}


/******************************************************************************
                   Name: bit_planeadd
          Expanded Name: Bitplane addition
             Parameters: char *filename : compressed filename
                Returns: Image Pointer
            Description: This function is called from the main function
                         bitplane(..). See bottom of this header for more
                         description.  
            Diagnostics: All filenames should be entered without extensions
    Initial Coding Date: 1/2/94
Last Modifications Made: 1/2/94
             References: None
              Author(s): Muthu Kumar
                         Southern Illinois University @ Edwardsville ________________________________________________________________________________
This function is called from the main function bitplane(..). It takes single parameter namely the compressed filename without any extension. The user could add different combinations of bitplane to analyze the result. The user is interactively asked  to enter the bitplane number to be added. Once the user enters the valid number the corressponding bitplane is added. The user is repeatedly asked to enter the bitplane number after each addition. The user has to press the number '8' when he or she wishes to end addition. Once addition is stopped this function returns the image pointer of the resultant(added) image.  *******************************************************************************/
Image *bit_planeadd(char *filename)
 {
   Image *bit_postprocessing(Image*);
   int x,y,run,grey,i,k,l,a,b,high,dummy,pixel,tt,plane,divisor,bands,rows,cols;
   int leng;
   long int count =0;
   double rmse,psnr,mse=0.0;
   char ch[7],filenames[30],aa,bb,cc;
   Image *decodeImage; 
   byte **image_array; 
   FILE *dec;
/* this is not needed
   printf(" \n\t\t\tWelcome to Adding Bit Planes Algorithm \n\n");
   printf("\nEnter the encoded file name(Don't give extensions, the programme automatically appends the extensions):");
   scanf("%s", filename); */

   leng=strlen(filename);
   if(filename[leng-4]=='.') filename[leng-4]='\0';
   if(filename[leng-6]=='.') filename[leng-6]='\0';
   ch[0]= '.';
   ch[1]= '_';
   ch[2]= '7';
   ch[3]= 'b';
   ch[4]= 'r';
   ch[5]= 'c';       
   ch[6]='\0';    
   strcpy(filenames,filename);
   strcat(filenames,ch);
   if((dec = fopen(filenames, "rb")) == '\0')
     {
       printf("\nError opening the file\n");
       exit(1);
     }
   aa=getc(dec);
   bb=getc(dec);
   cc=getc(dec);    
   if(aa != 'b' || bb != 'r' || cc != 'c')
     { printf("\n\n\t\tInvalid File format\n"); exit(0);}
   fread(&rows,sizeof(short int), 2,dec);
   fread(&cols,sizeof(short int), 2,dec);
   fread(&bands,sizeof(short int), 2,dec);
   fclose(dec);  
   decodeImage=new_Image(PGM,GRAY_SCALE,bands,rows,cols,CVIP_BYTE,REAL);
   image_array=(byte**)decodeImage->image_ptr[0]->rptr; 
   for(y=0; y<rows; y++)
     for(x=0; x<cols; x++)
       image_array[y][x]=0;
   for(; ;)
     {  
       for(; ;)
         {
           printf("\n\nEnter the bitplane to add(0-7), Enter '8' to stop adding: ");
           printf("\nDon't add the same bitplane twice --------------------------> ");
           scanf("%d", &plane);
           if(plane<0 || plane >8) 
           printf("\nInvalid Bit Plane number");
             else break;
         } 
       if(plane==8)
         {
           printf("\nConverting greycoded image into greylevel image....");
           decodeImage=bit_postprocessing(decodeImage);      
           return decodeImage;
         }       
       if (plane==0) divisor=256;
       if (plane==1) divisor=128;
       if (plane==2) divisor=64;
       if (plane==3) divisor=32;
       if (plane==4) divisor=16;
       if (plane==5) divisor=8;
       if (plane==6) divisor=4;
       if (plane==7) divisor=2;
       ch[2]=48+plane;    
       strcpy(filenames,filename);
       strcat(filenames,ch);
       if((dec = fopen(filenames, "rb")) == '\0')
         {
	   printf("\nError opening the file\n");
           exit(1);
         }
       aa=getc(dec);
       bb=getc(dec);
       cc=getc(dec);    
       if(aa != 'b' || bb != 'r' || cc != 'c')
         { printf("\n\n\t\tInvalid File format\n"); exit(0);}
       fread(&rows,sizeof(short int), 2,dec);
       fread(&cols,sizeof(short int), 2,dec); 
       fread(&bands,sizeof(short int), 2,dec);
       printf("\nDecoding Image size: rows-> %d, cols-> %d\n",rows,cols);
       x=0; y=0;
       for(; ;)
         {
           if(y>=rows) break;               
           if(feof(dec)) return 0;
           pixel = fgetc(dec);    
           if(pixel==0)
             {
              if(feof(dec)) return(0);
              pixel=fgetc(dec);          
              high = 255;
             }
             else  high=0;    
           for(; ;)
             { 
               for(; ;)
                 {  
                   for(i=0; i<pixel; i++)
                     {
                       image_array[y][x]+=(high+1)/divisor;
                       x++;
                       if(x>=cols) 
                         { y++; break;}
                     }
                   if(x>=cols) break;
                   if(feof(dec)) return(0);
                   pixel=fgetc(dec); 
                   if(pixel) break;
                     else { if(feof(dec)) return(0);
                            pixel=fgetc(dec); }
                 }    
               if(x>=cols) {x=0;break;} 
               if(high==255) high=0;
                 else if (high==0) high=255;  
             } 
         }         
     }    
 }   

               
Image *bit_postprocessing(Image* decoImage)
  { 
    int x,y,pixel,pixel1,mask,i,count,rows,cols;
    byte **image_aray;
    rows = decoImage->image_ptr[0]->rows;
    cols = decoImage->image_ptr[0]->cols;
    image_aray = (byte**) decoImage->image_ptr[0]->rptr;
    for (y=0; y<rows; y++)
      {
        for(x=0; x<cols; x++)
          { 
            pixel = image_aray[y][x];
            pixel1=pixel;
            mask=128;
            count=0;
            for(i=1; i<9; i++)
              {
                if (count%2 !=0)
                  if((pixel&mask) >0) pixel1=pixel1&(mask^255);
                      else pixel1=pixel1|mask;
                if((pixel&mask) >0) count++;
                mask = mask >>1;
               }         
             image_aray[y][x]=pixel1;               
          }
      }
   return decoImage;
  }






















