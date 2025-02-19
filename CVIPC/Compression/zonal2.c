/******************************************************************************
    ======================================================================
    Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
    ======================================================================
 
                   Name: zonal2.c
          Expanded Name: Zonal coding (DC component is not included into 
				       local remapping)

             Parameters: inputImage -- Pointer to the input image of type
                                       Image.

                         block_size -- kernel size, the kernel will be
                                       block_size*block_size(should be
                                       power of 2).

                         choice -- which transform you want to use.
                                   1:FFT; 2:DCT; 3:Walsh; 4:Hadamard.

                         mask_type -- which kind of kernel you want to use.
                                      1:triangle; 2:square; 3:circle.

                         compress_ratio -- compression ratio.

                Returns: For zon2_compress(), if succeeds, return 1; if errors
                         happen, return 0.

                         For zon2_decompress(), returns pointer to the
                         decompressed image.

            Description: The input image is a real image, it can be
                         multi_band and of any data type: CVIP_BYTE, CVIP_SHORT,
                         CVIP_INTEGER, CVIP_FLOAT and CVIP_DOUBLE.

            Diagnostics: None

    Initial Coding Date: 5/10/96
Last Modifications Made: 10/31/96
             References: None

                 Author: Wenxing Li


          Southern Illinois University @ Edwardsville


*******************************************************************************/




#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "CVIPimage.h"
#include "CVIPtransform.h"
#include "zonal.h"
 
 
extern char temp_dir[100];
extern char *Cmpr_Name[];
 

/*int zon2_compress(Image * inputImage, int block_size, int choice,
               int mask_type, float compress_ratio);

Image * zon2_decompress(char * inputfile);
*/


static int    choosing()       /* return transform choice*/
{
   int  	choice;         /* transform choice */

   printf(" 1.\t\t FFT\n");
   printf(" 2.\t\t DCT\n");
   printf(" 3.\t\t Walsh\n");
   printf(" 4.\t\t Hadamard\n");
   printf("other\t\t Exit.\n");
   printf("===========================\n");
   printf("\t Enter a number(1-4):");
   scanf("%d",&choice);

   return choice;
}


static Image * xform_calling(Image * inputImage, int block_size, int choice)
{
   switch (choice)
	{ case 1:  return((Image *)fft_transform(inputImage, block_size));
	  case 2:  return((Image *)dct_transform(inputImage, block_size));
	  case 3:  return((Image *)walhad_transform(inputImage, 1, block_size));
 	  case 4:  return((Image *)walhad_transform(inputImage, 3, block_size));
	  default: return(NULL);
	}
}


/* form a triangular mask, return its pointer */
static int * tri_mask(int block_size, int choice, float compress_ratio)
{
   int 		*P;    		/* to mask */
   int 		 side_len, i,j, position, start;
   				/* allocate memory for mask*/	
   P = (int *) calloc(block_size*block_size, sizeof(int));

   for (j=0; j<block_size; j++)				 /*initialize */ 
	for (i=0; i<block_size; i++) P[j*block_size+i] = 0;

   if (compress_ratio == 1.0) 
     { if (choice == 1) start = block_size/2; /* for column */
       else 		start = 0;
       for (i=0; i<block_size; i++)	
	 for (j=start; j<block_size; j++) P[i*block_size+j] = 1;
       return P;
     }

   side_len =sqrt(2*block_size*block_size/compress_ratio);  /*S=b*h/2 */

   if (choice != 1) position = 0;                       /* non_FFT */
   else {position = block_size/2; side_len/=2;}  	/* FFT     */
   
   for (i=0; (i<side_len) && (i<block_size); i++) /* rows */
     for (j=0; j<side_len-i; j++)       /* cols */
       { P[(i+position)*block_size + j+position] = 1; /*if not FFT, only one element*/	
  	 if (choice == 1)			/* if FFT, two elements */
             P[(block_size/2 -1 - i)*block_size + j+block_size/2] = 1;	
 /*          P[i*block_size + (block_size -1 - j)] = 1;
	     P[(block_size-1-i)*block_size + (block_size-1-j)] = 1;   */
	   
       }

   return(P);
}	


/* form a square mask, return its pointer */
static int * squ_mask(int block_size, int choice, float compress_ratio)
{
   int 		*P;    		/* to mask */
   int 		side_len, i, j;
   float 	temp;
                                /* allocate memory for mask*/
   P = (int *) calloc(block_size*block_size, sizeof(int));
  
   temp =sqrt(block_size*block_size/compress_ratio);  /*S=L*L */
   if (choice == 1) temp/=2;
   side_len = temp;
   if ( temp - side_len > 0.5 ) side_len++;

   for (j=0; j<block_size; j++)                         /*initialize */
        for (i=0; i<block_size; i++) P[j*block_size+i] = 0;

   if (choice != 1) 			    /* non_FFT */
	 for (i=0; i<side_len; i++)
	     for (j=0; j<side_len; j++)  P[i*block_size +j] =1;
   else  					   /* FFT   */
	 for (i=block_size/2 - side_len; i<block_size/2 + side_len; i++)
             for (j=block_size/2; j<block_size/2 + side_len; j++)
		P[i*block_size + j] =1;

   return(P);
}    


/* form a circular mask, return its pointer */
static int * cir_mask(int block_size, int choice, float compress_ratio)
{
   int 		*P;    				/* to mask */
   int 		i, j, position, start;
   float 	radius;
                                /* allocate memory for mask*/
   P = (int *) calloc(block_size*block_size, sizeof(int));

   for (j=0; j<block_size; j++)				 /*initialize */ 
	for (i=0; i<block_size; i++) P[j*block_size+i] = 0;

   if (compress_ratio == 1.0) 
     { if (choice == 1) start = block_size/2; /* for column */
       else 		start = 0;
       for (i=0; i<block_size; i++)	
	 for (j=start; j<block_size; j++) P[i*block_size+j] = 1;
       return P;
     }

   radius =sqrt(4.0*block_size*block_size/compress_ratio/3.1416); 
   if (choice != 1)  position = 0; 
   else { position = block_size/2; radius/=2;} 
  
   for (i=0; i<block_size - position; i++)         /* rows */
     for (j=0; j<block_size - position; j++)       /* cols */
       if (sqrt(i*i + j*j) <= radius)
         { P[(i+position)*block_size + j+position] = 1; /*if not FFT, only one element*/	
  	   if (choice == 1)			/* if FFT, two elements */
              P[(block_size/2 -1 - i)*block_size + j+block_size/2] = 1;	
         }

   return(P);
}


/* forming the spicific zonal mask, return its pointer(that mask)*/
/* when choice = 1, FFT */
static int * z_mask(int block_size, int choice, int mask_type, 
		    float compress_ratio)   
{
   if (mask_type < 1 || mask_type > 3)
     { fprintf(stderr, "kernel_type should be within 1-3\n");
       return NULL;
     } 

   switch (mask_type)
	{ case 1:  return(tri_mask(block_size, choice, compress_ratio));
          case 2:  return(squ_mask(block_size, choice, compress_ratio));
      	  case 3:  return(cir_mask(block_size, choice, compress_ratio));
      	  default: return(NULL);
	}
}


/* compute the number of nonzero elements in the mask */
static long computing(int * P, int block_size)
{
   long 	i,n=0;

   for (i=0; i<block_size*block_size; i++)
     if (P[i] != 0) n++;

   switch (n % 4)
    { case 0:  return n;
      case 1:  for (i=block_size*block_size-1; i>-1; i--)
                  if (P[i] == 1) { P[i]=0; return (n-1);} 
      case 2:  for (i=block_size*block_size-1; i>-1; i--)
                  if (P[i] == 1) 
		    { if ((i+block_size) > (block_size*block_size-1))
              		   { P[i+1]=1; P[i+2]=1; }
		      else { P[i+1]=1; P[i+block_size]=1;}
		      return (n+2);
		    } 
      case 3:  for (i=block_size*block_size-1; i>-1; i--)
                  if (P[i] == 1) 
		    { if ((i+block_size) > (block_size*block_size-1))
		           P[i+1]=1;
	 	      else P[i+block_size] = 1;
		      return (n+1);
		    } 
    } 
} 



/* sampling and rearranging input image */
static remapSTRUCT * sampling(Image * inputImage, int * P, int block_size)
{
   int             x, y, x0, y0;    /* x & x0 row,  y & y0 col */
   unsigned int    hbn, vbn;        /* horizontal and vertical block numbers */
   int             i, j;            /* i vertical, j horizontal */
   float 	** real, **imag;
   int 		   complex=0;
   float        *  rer,  * rei, * tr, * ti; 
   long            len,  position;   /* record col position of rearranged matrix*/
   remapSTRUCT  *  remapp;

   vbn =  getNoOfRows_Image(inputImage) / block_size;
   hbn =  getNoOfCols_Image(inputImage) / block_size;
   len =  computing(P, block_size);

   real = (float **)inputImage->image_ptr[0]->rptr;
   imag = (float **)inputImage->image_ptr[0]->iptr; 
   if (inputImage->image_ptr[0]->data_format == COMPLEX) complex = 1; 

   rer = (float *) calloc(vbn*hbn*(len+1), sizeof(float));
   if (complex) rei = (float *) calloc(vbn*hbn*(len+1), sizeof(float));
 
   for (i=0; i<vbn; i++)
     for (j=0; j<hbn; j++)
/* in one block */
      { if (complex) 
	  { rer[(i*hbn+j)*(len+1)] = 	
		real[i*block_size+block_size/2][j*block_size+block_size/2];
	    rei[(i*hbn+j)*(len+1)] = 
		imag[i*block_size+block_size/2][j*block_size+block_size/2];
	    tr = rer + (i*hbn+j)*(len+1) + 1; ti = rei + (i*hbn+j)*(len+1) + 1;
	  }
	else 
	  { rer[(i*hbn+j)*(len+1)] = real[i*block_size][j*block_size];
	    tr = rer + (i*hbn+j)*(len+1) + 1;
	  }
	position = 0;
        for (x=i*block_size, x0=0; x<(i+1)*block_size, x0<block_size; x++, x0++)
           for (y=j*block_size, y0=0; y<(j+1)*block_size, y0<block_size; y++, y0++)
              if (P[x0*block_size + y0] ==1) 
		{
		  tr[position] = real[x][y]; 
        	  if (complex) ti[position] = imag[x][y];
		  if (complex && x0==block_size/2 && y0==block_size/2)
		    { tr[position]=tr[position-1]; ti[position]=ti[position-1];}
		  position++;
		}
      }

   remapp = (remapSTRUCT *) malloc(sizeof(remapSTRUCT));
   remapp->rows = vbn*hbn;
   remapp->cols = len + 1;
   remapp->rer  = rer;
   if (complex) remapp->rei  = rei;
   else remapp->rei = NULL;

   return remapp;
}


/*find the position of the first non_zero element in a mask*/
static int * finding(int * P, int block_size)
{
  int 		i, j;
  int 	      * ptr;

    /* coordinates of the first non_zero element in a mask*/
  ptr = (int *) malloc(2*sizeof(int));

  for (i=0; i<block_size; i++)
     for (j=0; j<block_size; j++)
        if ( P[i*block_size +j] != 0) 
		{ ptr[0] = i; ptr[1] = j; return ptr;}
}


/* for mask storing */
static MYSTRUCT * mask_compress(int * P, int block_size)
{
  int 		  i, j, maxcol=0;
  int 		  nrow=0, ncol;
  int 		  a[513];
  unsigned char * ptr;
  long          * pl;
  MYSTRUCT      * str;
 
  for (i=0; i<block_size; i++)
   {	  
     ncol = 0;

     for (j=0; j<block_size; j++)
       if (P[i*block_size + j] != 0) ncol++;

     if (ncol != 0) 
        { nrow++;
          a[nrow] = ncol;
        }

     if (ncol > maxcol) maxcol = ncol;
   }
  a[0] = nrow;  

  str  = (MYSTRUCT *)malloc(sizeof(MYSTRUCT));
  if ((nrow+1) < 256 && maxcol < 256)
     { ptr = (unsigned char *)calloc(nrow+1, sizeof(char));
       for (i=0; i<= nrow; i++) ptr[i] = a[i];
       str->c = 'c';
       str->ptr = ptr;
     }
  else 
     { pl = (long *)calloc((nrow+1), sizeof(long));
       for (i=0; i<= nrow; i++) pl[i] = a[i];
       str->c = 'l';
       str->pl = pl;
     }     
  return str;
}


static int band_storing(storeSTRUCT  * storep, FILE * fp, int choice)
{
  long			temp[2];

  temp[0] = storep->rows;
  temp[1] = storep->cols;

  if (fwrite(temp, 4, 2,fp) != 2) 
     { fprintf(stderr,"write rows&cols error\n"); return 0;}

  if (fwrite(storep->storer, 1, temp[0]*temp[1], fp) != temp[0]*temp[1])
     { fprintf(stderr,"write image real data error\n"); return 0;}

  if (choice == 1)
    if (fwrite(storep->storei, 1, temp[0]*temp[1], fp) != temp[0]*temp[1])
     { fprintf(stderr,"write image imaginary data error\n"); return 0;}

  return 1;
}


static int prep_storing(FILE * fp, int block_size, int * P, int choice, 
	   int bands, COLOR_FORMAT color, unsigned int rows, unsigned int cols)
{
  int         		 * ptr;
  unsigned char  	   a[3];
  long           	   block, s[2];
  MYSTRUCT       	 * str;
  unsigned char          * pc;
  long         		 * pl;

  if (fwrite("ZON2", 1, 4, fp) != 4)
     { fprintf(stderr,"write ZON2 error\n"); return 0;}

  a[0] = (unsigned char)color;
  a[1] = (unsigned char)bands;
  if (fwrite(a, 1, 2, fp) != 2)
     { fprintf(stderr,"write color_space&bands error\n"); return 0;}

  block = block_size;
  if (fwrite(&block, 4, 1, fp) != 1 ) 
     { fprintf(stderr,"write block_size error\n"); return 0;}

  s[0] = (long)rows;
  s[1] = (long)cols;
  if (fwrite(s, 4, 2, fp) != 2 ) 
     { fprintf(stderr,"write rows&cols error\n"); return 0;}  

  a[0] = choice; 
   ptr = finding(P, block_size);
  a[1] = ptr[0];
  a[2] = ptr[1];
  if (fwrite(a, 1, 3, fp) != 3) 
     { fprintf(stderr,"write choice&coordinates error\n"); return 0;}

  str = mask_compress(P, block_size);
  if (putc(str->c, fp) == EOF) {fprintf(stderr,"error in putc\n"); return 0;}
  if (str->c == 'c')  
        { if (fwrite(str->ptr, 1,*(str->ptr)+1, fp) != *(str->ptr)+1 ) 
	     { fprintf(stderr,"write mask error\n"); return 0;}   }
  else  { if (fwrite(str->pl, 4,*(str->pl)+1, fp) != *(str->pl)+1 ) 
	     { fprintf(stderr,"write mask error\n"); return 0;}   }

  if (str->c == 'c') free((char *)str->ptr);
  else		     free((char *)str->pl);
  free((char *)str);
  free((char *)ptr);
  return 1;
}


static Image * a_temp(Image * cvipImage)
{
  Image 		* tempImage;

  tempImage = (Image *)malloc(sizeof(Image));
  tempImage->image_format = cvipImage->image_format;
  tempImage->color_space  = GRAY_SCALE; /*cvipImage->color_space; */
  tempImage->bands = 1;
  tempImage->image_ptr = (Matrix **)malloc(sizeof(Matrix *));

  return tempImage;
}


static void dealing_remap(long rows, long cols, float * rp, byte * sp, int scl)
{
  long	   i,    j;
  float	   max,  min,   factor,  temp;

  for (i=0; i < rows; i++)
    { *(rp+1) = *(rp+2);
      max = *(rp+2);
      min = max;
      for (j=1; j < cols; j++)
        { temp = rp[j];
	  if (temp > max) max = temp;
          if (temp < min) min = temp; 
        }
      factor = 255.0/(max - min);
      *((float *)sp) = min;
      *((float *)(sp + sizeof(float))) = factor;
      *((float *)(sp + 2*sizeof(float))) = *rp;
      for (j=1; j<cols; j++)
        sp[3*sizeof(float) + j-1]  = factor * (rp[j] - min) + 0.5;
      sp += scl;
      rp += cols;
    }
}



static storeSTRUCT * newremap(remapSTRUCT * remapp)
{
   storeSTRUCT  *  storep;
   int             i, j;            /* i vertical, j horizontal */

   storep = (storeSTRUCT *)calloc(1, sizeof(storeSTRUCT));
   storep->rows = remapp->rows;
   storep->cols = remapp->cols - 1 + 3*sizeof(float);

   storep->storer = calloc(storep->rows*storep->cols, sizeof(char));
   if (remapp->rei != NULL) 
     storep->storei = calloc(storep->rows*storep->cols, sizeof(char));
   else storep->storei = NULL;

   dealing_remap(remapp->rows, remapp->cols, remapp->rer, storep->storer, (int)storep->cols);
   if (remapp->rei != NULL)
     dealing_remap(remapp->rows, remapp->cols, remapp->rei, storep->storei, (int)storep->cols);

   return storep;
}


/* sample, map and store image to disk, OK 1, otherwise 0 */
static int sam_map_stor(Image * cvipImage, char * inputfile, 
			int block_size, int * P, int choice)
{
  FILE         		 * fp;    
  storeSTRUCT 		 * storep;
  remapSTRUCT 		 * remapp;
  Image       		 * tempImage;
  int			   k;
  unsigned int   	   rows, cols;

  rows =  getNoOfRows_Image(cvipImage);
  cols =  getNoOfCols_Image(cvipImage);

  if ( (fp = fopen(inputfile,"wb")) == NULL)
     { fprintf(stderr,"fopen error\n"); return 0;}
 
  tempImage = a_temp(cvipImage);

  for (k=0; k < cvipImage->bands; k++)
    { tempImage->image_ptr[0] = cvipImage->image_ptr[k];

      remapp = sampling(tempImage, P, block_size);

      storep  =  newremap(remapp);          /*float->byte*/

      if (k == 0)			    /* only once */
        if (!prep_storing(fp, block_size, P, choice, cvipImage->bands,
      			  cvipImage->color_space, rows, cols)) 
	    return 0;

      if (!band_storing(storep, fp, choice)) return 0;

      free((char *)remapp->rer);
      if (remapp->rei) free((char *)remapp->rei);
      free((char *)remapp);
      free((char *)storep->storer);
      if (storep->storei) free((char *)storep->storei);
      free((char *)storep);
    }

  if (fclose(fp) == EOF) {fprintf(stderr,"close error\n"); return 0;}

  free((char *)tempImage->image_ptr);
  free((char *)tempImage);
  return 1;
}


static int z_size_compute(Image * inputImage, int block_size, 
			  unsigned int * nrows, unsigned int * ncols)
{
 int 		i, j, k=0;
 unsigned int   rows, cols, size;

 rows =  getNoOfRows_Image(inputImage);
 cols =  getNoOfCols_Image(inputImage);

 if ((rows % block_size) != 0) rows = (rows/block_size + 1)*block_size;
 if ((cols % block_size) != 0) cols = (cols/block_size + 1)*block_size; 

 if ((rows == inputImage->image_ptr[0]->rows) && (cols == inputImage->image_ptr[0]->cols))
    return 0;    /* no change */
 else 
    { *nrows = rows; 
      *ncols = cols;
      return 1;  /* has been changed */
    } 
}


static void init_image(Image * returnImage, CVIP_TYPE dtype)
{int		    i, j, k;
 void		 ** newimage;
 unsigned int 	    rows, cols;

 rows = returnImage->image_ptr[0]->rows;
 cols = returnImage->image_ptr[0]->cols;

 for (k=0; k< returnImage->bands; k++)	/* all assign 0 initially */
   { newimage = (void **) returnImage->image_ptr[k]->rptr;
     for (i=0; i < rows; i++)
       for (j=0; j < cols; j++)
	 switch(dtype)
 	       { case CVIP_BYTE:  ((byte **)newimage)[i][j]  =  (byte)0;  break;
  		 case CVIP_SHORT: ((short **)newimage)[i][j] = (short)0;  break;
    		 case CVIP_INTEGER:((int **)newimage)[i][j]  =  (int)0;   break;
    		 case CVIP_FLOAT: ((float **)newimage)[i][j] = (float)0;  break;
    		 case CVIP_DOUBLE:((double **)newimage)[i][j]= (double)0; 
	       }
    }
}



static Image * image_norm(Image * inputImage, unsigned int newrows, unsigned int newcols)
{
 void  		 ** inimage, ** newimage;
 int 	  	    i, j, k, m, n;
 CVIP_TYPE	  	    dtype;
 Image  	 *  returnImage;
 unsigned int       inrows, incols;

 inrows =  getNoOfRows_Image(inputImage);
 incols =  getNoOfCols_Image(inputImage);

 dtype = inputImage->image_ptr[0]->data_type;
 returnImage = new_Image(inputImage->image_format, inputImage->color_space, 
			 inputImage->bands, newrows, newcols, dtype, REAL);

 init_image(returnImage, dtype);

 for (k=0; k< returnImage->bands; k++)
   { newimage = (void **) returnImage->image_ptr[k]->rptr;
     inimage  = (void **)  inputImage->image_ptr[k]->rptr;
     for (i=0; i < inrows; i++)        /*according to the smaller one*/
       for (j=0; j < incols; j++) 
     	 switch(dtype)
 	   { case CVIP_BYTE:   ((byte **)newimage)[i][j] =  ((byte **)inimage)[i][j];  break;
  	     case CVIP_SHORT: ((short **)newimage)[i][j] = ((short **)inimage)[i][j]; break;
    	     case CVIP_INTEGER: ((int **)newimage)[i][j] =   ((int **)inimage)[i][j]; break;
    	     case CVIP_FLOAT: ((float **)newimage)[i][j] = ((float **)inimage)[i][j]; break;
    	     case CVIP_DOUBLE:((double**)newimage)[i][j] = ((double**)inimage)[i][j]; 
	   }
    }

 return (returnImage);
}


 /* succeed 1,otherwise 0 */
 /* multi_band real image of any data type */
int zon2_compress(Image * inputImage, char *filename, int block_size, int choice, 
	       int mask_type, float compress_ratio)  
{
   int		  i, j=2,  k=0, size;
   int          * P;
   Image        * cvipImage;
   unsigned int   newrows=0, newcols=0;

   for (i=0, j=2; i<9 && j<block_size; i++, j*=2) 
       if (block_size % j != 0) k++;
   if (k != 0) 
     {fprintf(stderr, "block size is not power of 2\n"); return -1;}

   if (choice <1 || choice >4) {printf("wrong choice\n"); return -1;}

   if (!z_size_compute(inputImage, block_size, &newrows, &newcols))
        inputImage = duplicate_Image(inputImage);
   else inputImage = image_norm(inputImage, newrows, newcols);

   cvipImage = xform_calling(inputImage, block_size, choice);

   P = z_mask(block_size, choice, mask_type, compress_ratio);
   if (P == NULL) return -1;

   if (!sam_map_stor(cvipImage, filename, block_size, P, choice)) return -1;

   delete_Image((Image *)cvipImage);
   free((char *)P);

   return 0;
}


static int * mask_restore(long block_size, unsigned char * a,
			  void * ptr, char choice)
{
  int  		 * P;
  unsigned char  * pc;
  long 		 * pl;
  long  	   i, j, k, rows, cols, position;

  if (a[1] != 0 && a[1] != block_size/2) 
	{ printf("mask_restore error\n"); return NULL; }

  P  = (int *) calloc(block_size*block_size, sizeof(int));

  for (i=0; i<block_size*block_size; i++) P[i] = 0;

  if (a[2] == 'c') pc = (unsigned char *) ptr;
  if (a[2] == 'l') pl = (long          *) ptr;
  
  k = 1;
  if (a[2] == 'c') rows = a[0] + pc[0];
  else             rows = a[0] + pl[0];

  if (choice == 1 && a[1]==0) position = 256;
  else 			      position = a[1];

  for (i=a[0]; i< rows; i++)
    { if (a[2] == 'c') cols = position + pc[k];
      else             cols = position + pl[k];
      for (j=position; j< cols; j++) P[i*block_size + j] = 1;
      k++;
    }

  return P;
}


/* byte -> float */
static float * inv_remap(unsigned char * data, long * temp)
{
  float        * newdata, * returndata;
  float          factor, minP;
  long           i,  j,	cols;
 
  cols = temp[1] - 3*sizeof(float);
  newdata = (float *)calloc(temp[0]*cols, sizeof(float));
  returndata = newdata;

  for (i=0; i<temp[0]; i++)
   { minP    = *((float *)(data + i*temp[1]));
     factor  = *((float *)(data + i*temp[1] + sizeof(float)));
     for (j=0; j<cols; j++)
       { 
         *newdata = (float)(minP + ((float)data[i*temp[1] + 3*sizeof(float) + j] - 0.5)/factor);
         newdata++;
        }
   }

  return returndata;
}



static Image * imag_restore(float * newdata, int * P, int rows, int cols, 
			    long block_size, char choice, char * rdata, long rcol)
{
  unsigned int     hbn, vbn;
  int              x, y, x0, y0;
  int              i, j;
  int 		   check;
  Image          * restoreImage;
  float         ** image;
  long		   len, position=0;     /* record the position of newdata[n] */

  if (choice != 1) check = 0;    /* non_FFT 0, FFT 1 */
  else 		 check = 1;

  hbn = cols/block_size;
  vbn = rows/block_size;
  restoreImage = new_Image(PGM, GRAY_SCALE, 1, rows, cols, CVIP_FLOAT, REAL);
  image  = (float **) restoreImage->image_ptr[0]->rptr; 
  len = computing(P, block_size);

  for (i=0; i<rows; i++)
    for (j=0; j<cols; j++)
      image[i][j] = (float)0;

  for (i=0; i<vbn; i++)
    for (j=0; j<hbn; j++)
/* in one block */
     { position = 0;
       for (x=i*block_size, x0=0; x<(i+1)*block_size, x0<block_size; x++, x0++)
         for (y=j*block_size, y0=0; y<(j+1)*block_size, y0<block_size; y++, y0++)
           if (P[x0*block_size + y0] == 1) 
	     { image[x][y] = newdata[(i*hbn+j)*len+position];
	       if (check && (y0 % (block_size/2) != 0) && (x0 != 0)) 
		 image[(i+1)*block_size-x0][(j+1)*block_size-y0] = image[x][y];
	       position++;
	     }
       if (check) 
	  image[i*block_size+block_size/2][j*block_size+block_size/2] = 
		((float *)((char *)rdata+(i*hbn+j)*rcol))[2];
       else image[i*block_size][j*block_size] = ((float *)((char *)rdata+(i*hbn+j)*rcol))[2];
     }

  return restoreImage;
}


/* for complex image data only, multi_band */
static void conjugate(Image * inputImage, long block_size)
{
  int            i,  j, k, a, band;
  int            rows, vbn;
  float       ** image;

  rows = inputImage->image_ptr[0]->rows;
  vbn  = inputImage->image_ptr[0]->cols / block_size;

  for (band=0; band < inputImage->bands; band++)
    { image = (float **) inputImage->image_ptr[band]->iptr;
      for (i=0; i<rows; i++)
        { a = 0;
          for ( k=0; k<vbn; k++)
            { for (j=a; j<a + block_size/2; j++) image[i][j] = -image[i][j];
	      a += block_size;
            }
        }
    }
} 


static Image * inv_xform_calling(Image * inputImage, int block_size, int choice)
{
   switch (choice)
	{ case 1:  return((Image *)ifft_transform(inputImage, block_size));
	  case 2:  return((Image *)idct_transform(inputImage, block_size));
	  case 3:  return((Image *)walhad_transform(inputImage, 0, block_size));
 	  case 4:  return((Image *)walhad_transform(inputImage, 2, block_size));
	  default: return(NULL);
	}
}


static Image * band_decom(FILE * fp, char choice, long block_size, int * P, 
			  unsigned int rows, unsigned int cols)
{
  long           temp[2];
  char         * rdata,	   * idata=NULL;
  float        * rnewdata, * inewdata=NULL;
  Image        * cvipImage,* imagImage;

   if (fread(temp, sizeof(long), 2, fp) != 2) 
      { fprintf(stderr, "read 6 data error\n"); 
	return NULL;
      }

   rdata = calloc(temp[0]*temp[1], sizeof(char)); 
   if (fread(rdata, sizeof(char), temp[0]*temp[1], fp) != temp[0]*temp[1])
      { fprintf(stderr, "read remapped image error\n"); 
	return NULL;
      }

   if (choice == 1)
    { idata = calloc(temp[0]*temp[1], sizeof(char));
      if (fread(idata, sizeof(char), temp[0]*temp[1], fp) != temp[0]*temp[1])
         { fprintf(stderr, "read remapped image error\n"); 
	   return NULL;
	 }
    }

   rnewdata = inv_remap((unsigned char *)rdata, temp);
   if (choice == 1) inewdata = inv_remap((unsigned char *)idata, temp);

   cvipImage = imag_restore(rnewdata, P, rows, cols, block_size, choice, rdata, temp[1]);
   if (choice == 1) 
     { imagImage = imag_restore(inewdata, P, rows, cols, block_size, choice, idata, temp[1]);  
       cvipImage->image_ptr[0]->iptr = imagImage->image_ptr[0]->rptr;
       cvipImage->image_ptr[0]->data_format = COMPLEX;
       free((char *)imagImage->image_ptr[0]);
       free((char *)imagImage->image_ptr);
       free((char *)imagImage);
     } 

   free(rdata);
   if (idata != NULL) free(idata);
   free((char *)rnewdata);
   if (inewdata != NULL) free((char *)inewdata);
   return cvipImage;
}



/* error, return NULL */
static int * mask_decom(FILE * fp, char choice, long block_size)
{
  char           a[3];
  unsigned  char nc,       * pc=NULL;
  long 		 nl,       * pl=NULL;
  void         * ptr;
  int          * P;         		/* restored mask */

  if (fread(a, 1, 3, fp) != 3) 
     { fprintf(stderr, "read 3 error\n"); 
       return NULL;
     }

  if (a[2] == 'c') 
    { if (fread(&nc, 1, 1, fp) != 1) 
        { fprintf(stderr, "read 4 error\n"); 
	  return NULL;
        }
      pc = (unsigned char *)calloc((nc+1), sizeof(char));
      *pc = nc;  ptr = (void *) pc;
      if (fread(pc+1, 1, nc, fp) != nc) 
	{ fprintf(stderr, "read 5 error\n"); 
	  return NULL;
	}
    }
   else 
     if (a[2] == 'l') 
       { if (fread(&nl, 4, 1, fp) != 1) 
	   { fprintf(stderr, "read 4 error\n"); 
	     return NULL;
	   }
	 pl = (long *)calloc((nl+1), sizeof(long));
         *pl = nl;  ptr = (void *) pl;
         if (fread(pl+1, sizeof(long), nl, fp) != nl) 
	   { fprintf(stderr, "read 5 error\n"); 
	     return NULL;
	   }
       }
     else 
       { fprintf(stderr, "mask type error\n"); 
	 return NULL;
       }

   P = mask_restore(block_size, (unsigned char *)a, ptr, choice);

   free((char *)ptr);
   return  P;
}


static Image * z_combine(int bands)
{
 Image  * A;

 A = (Image *) malloc(sizeof(Image));
 if (!A) 
   { fprintf(stderr, "\nERROR in image structure allocate\n");
     exit(1);
   }

 A->bands = bands;
 A->story = NULL;
 A->image_ptr = (MATRIX **) calloc(bands, sizeof(MATRIX *));
 
 return A;
}


static Image * decompress(FILE * fp, char choice, long block_size, 
			  int bands, unsigned int rows, unsigned int cols)
{
  int		* P;
  Image        ** arrayImage,  * returnImage;
  int		  k;

  if (!(P = mask_decom(fp, choice, block_size)))
     { fprintf(stderr,"mask_decom error\n"); 
       return NULL;
     }

  arrayImage = (Image **)calloc(bands, sizeof(Image *));

  for (k=0; k < bands; k++)
    if (!(arrayImage[k] = band_decom(fp, choice, block_size, P, rows, cols)))
	return NULL;

  returnImage = z_combine(bands);

  for (k=0; k < bands; k++)
    { returnImage->image_ptr[k] = arrayImage[k]->image_ptr[0];
      free((char *)(arrayImage[k]->image_ptr));
      free((char *)arrayImage[k]);
    }

/*  if (fclose(fp) == EOF) 
    { fprintf(stderr,"close error\n"); 
      return 0;
    } */

  free((char *)arrayImage);
  free((char *)P);
  return returnImage;
}


/* no error happens, return 1; otherwise return 0 */
static int prep_decompress(FILE * fp, char * a, IMAGE_FORMAT * f, 
			   COLOR_FORMAT * co, unsigned char * ba, long * bl, 
	   		   long * rows, long * cols, char * ch)
{
  int fmt_size = 4;

  if (fread(a, sizeof(char), fmt_size, fp) != fmt_size)
     { fprintf(stderr,"read format error\n"); 
       return 0;
     }

  a[4]=0;
  if (!strcmp(a, "ZON2")) *f = ZON2;
  else { fprintf(stderr,"erroneous format\n"); 
         return 0;
       }

  if (fread(a, 1, 1, fp) != 1)
     { fprintf(stderr,"read color_space error\n"); 
       return 0;
     }
  *co = (COLOR_FORMAT)a[0];

  if (fread(ba, 1, 1, fp) != 1)
     { fprintf(stderr,"read bands error\n"); 
       return 0;
     }

  if (fread(bl, 4, 1, fp) != 1) 
     { fprintf(stderr,"read block_size error\n"); 
       return 0;
     }

  if (fread(rows, 4, 1, fp) != 1) 
     { fprintf(stderr,"read rows error\n"); 
       return 0;
     }

  if (fread(cols, 4, 1, fp) != 1) 
     { fprintf(stderr,"read cols error\n"); 
       return 0;
     }  

  if (fread(ch, 1, 1, fp) != 1) 
     { fprintf(stderr,"read choice error\n"); 
       return 0;
     }

  return 1;
} 

Image * zon2_decompress(char * inputfile)
{ FILE           * fp;
  Image          * finalImage;

  if ( (fp = fopen(inputfile, "rb")) == NULL ) 
     { fprintf(stderr,"fopen error\n"); 
       return NULL;
     } 
	
	finalImage = zon2_decompression(fp);	
	fclose(fp);	
	return finalImage;
}

Image * zon2_decompression(FILE * fp)
{
  struct stat	   st; 
  Image          * finalImage;
  char             choice, ***iptr, a[5];
  long             block_size;
  IMAGE_FORMAT     format;
  unsigned char    bands;
  COLOR_FORMAT	   color;
  long		   rows, cols;
  int		   k;


  if (!prep_decompress(fp, a, &format, &color, &bands, &block_size, 
		       &rows, &cols, &choice))
     return NULL;

  if (!(finalImage = decompress(fp, choice, block_size, (int)bands, 
				(unsigned int)rows, (unsigned int)cols)))
    return NULL;

  if (choice == 1) conjugate(finalImage, block_size);

  finalImage->color_space  = color;
  finalImage->image_format = format;

  iptr = calloc(bands, sizeof(char **));
  for (k=0; k < (int)bands; k++)
    iptr[k] = finalImage->image_ptr[k]->iptr;

  finalImage = inv_xform_calling(finalImage, block_size, choice);

  finalImage->story = (HISTORY)NULL;

/*
  if (choice == 1) 
     { for (k=0; k < (int)bands; k++)
	 { free(*(iptr+k));  free((char *)iptr[k]); }
       free((char *)iptr);
     }
*/
   if (choice == 1) free(iptr);
  
  if (!fstat(fileno(fp), &st))
     { printf("The original raw data occupies %ld bytes\n", bands*rows*cols);
       printf("The compressed data occupies %ld bytes\n", st.st_size);
       printf("Compression ratio is 1 : %f\n", ((float)bands*rows*cols)/st.st_size);
     }

  return finalImage;
}	  

/*
Image * zonal(Image * inputImage, int  block_size,  int choice, 
	      int     mask_type,  float compress_ratio)	   
{
  if (!zon2_compress(inputImage, block_size, choice, mask_type, compress_ratio)) 
     return NULL;

  return (zon2_decompress(temp_dir));
}*/

