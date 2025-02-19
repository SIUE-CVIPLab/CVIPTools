/*****************************************************************************
 * ======================================================================    *
 * Image Processing/Computer Vision Tool Project - Dr. Scott Umbaugh SIUE    *
 * ======================================================================    *
 *                                                                           *
 * ROUTINE/FUNCTION: DCT, IDCT, FDCT_1D, IFDCT_1D, bitReverse, creat_sct...  *
 *                                                                           *
 *                                                                           *
 *              DESCRIPTION: This module will perform a discrete cosine      *
 *                           transform of a grayscalc/color image.           *
 *                                                                           * 
 *                   AUTHOR: Jianxin Tan                                     *
 *			     (dct_setup was written by Ramesh Reddy in 92~93 *
 *                           and was modified by Kun Luo in March 95)        *
 *            RELATED FILES: dct.h	                                     *
 *                                                                           *
 *              CODING DATE: 2/14/95                                         *
 *  LAST MODIFICATIONS MADE: 3/15/95                                         *
 *                                                                           *
 *  VARIABLES PASSED TO DCT:					             *
 *        input_Image - An image structure with necessary info. about the    *
 *        image as well as a block size.                                     *
 *                                                                           *
 *  RETURNED VARIABLES:                                                      *
 *        dct_transform() -  returns a new image structure with new transformed        * 
 *                 image data in VIP format.                                 *
 *                                                                           *
 *****************************************************************************/
#include <math.h>
#include "CVIPtools.h"
#include "CVIPtoolkit.h"
#include "CVIPdef.h"
#include "CVIPtransform.h"
/*This group of functions declared here was developed by Jianxin Tan.*/
/*Last modification on 3/15/95*/
/*********************************************************************/
static int* bitReverse(int);
static float* FDCT_1D(int n, float *f, float** sc_table);
static float* IFDCT_1D(int n, float *f, float** sc_table);
static int AnfMatrix(int n, float *f, float** sc_table);
static int IAnfMatrix(int n, float *f, float** sc_table);
static void BN(int n, float *f);
static void TYPE1(int n, float *f, float** sc_table);
static void TYPE2(int n, float *f);
static void TYPE3(int n, int q, float *f, float** sc_table);
static void TYPE4(int n, int p, float *f);
static void ITYPE1(int n, float *f, float** sc_table);
static void ITYPE3(int n, int q, float *f, float** sc_table);
static float mysin(int i, int j);
static float mycos(int i, int j);
static float **creat_sct(int n);

/********************************************************************/

/*------------------------------------------------------------------*/
/*This funciton returns an array of pow(2,bitNumber) integers       */
/*whose elements are the bit-reversal numbers                       */
/*of the elements at the coresponding positions                     */
/*in the array [0,1,...,pow(2,bitNumber)]                           */
/*------------------------------------------------------------------*/
static int* bitReverse(int bitNumber) {
        int* ptr,currentin,currentbit,temp,setbit,mmax;
        int  max = 1<<bitNumber; /*pow(2,bitNumber);*/
        mmax = max - 1;
        /*ptr = (int *)malloc(sizeof(int)*max);
        bzero((char*)ptr,sizeof(int)*max);*/
	ptr = (int *)calloc(max,sizeof(int));
        for(currentin=1;currentin<max;currentin++) {
                if(ptr[currentin]==0) { /*avoid repetition*/
                        setbit = max>>1; /*/2;*/
                        ptr[currentin] = currentin;
                        temp = currentin;
                        for(currentbit=0;currentbit<bitNumber;currentbit++) {
                                if(temp%2 == 1) { /*fetch the right most bit*/
                                        ptr[currentin]=ptr[currentin]|setbit;
                                }  /*put it back on left hand side, left-right*/
                                else
                                ptr[currentin] = ptr[currentin] & (~setbit);
                        setbit = setbit >> 1;   /*update the setbit's position*/
                        temp = temp >> 1; /*shift to get the right most bit*/
                        }
                        /*same pair*/
                        ptr[ptr[currentin]] = currentin;
                        /*symetric pair*/
                        ptr[mmax - currentin] = mmax - ptr[currentin];
                        /*symetric pair's same pair*/
                        ptr[mmax - ptr[currentin]] = mmax - currentin;
                 }
        }
        return ptr;
}

/*------------------------------------------------------------------*/
/*This function returns an array of "float" numbers                 */
/*which is the dct_transform of the input array f
 */
/*The function "float **creat_sct(int n)" must be called first      */
/*to create the sine_cosine_table needed by this function           */
/*------------------------------------------------------------------*/


static float* FDCT_1D(int n, float *f, float** sc_table) {
	/*reorder and 2/N(n,f) */
	int *reorder,i;
	float *result;
	if(n==1) {
		printf("\nError: n must be larger than 1.\n");
		exit(0);
	}
	result = (float *)malloc(sizeof(float)*n);
	i = (int)ROUND(log(n)/log(2));

	reorder = bitReverse((int)ROUND(log(n)/log(2)));
	
	AnfMatrix(n, f, sc_table);

	for(i=0;i<n;i++) {
		result[i] = f[reorder[i]]*2/n;
	} 
	free(f);	
	free(reorder);		
	return result;
}

/*------------------------------------------------------------------*/
/*This funtion performs all the matrix calculations                 */
/*needed by 1D_DCT calculation except the final                     */
/*reallocation from bit-reversal order to normal order              */
/*------------------------------------------------------------------*/
static int AnfMatrix(int n, float *f, float** sc_table) {
	int i,halfn;
	float *lowhalf,*highhalf,swap;
	if(n != 2) 
		BN(n,f);
	else {
		swap = f[0];
		f[0] = (f[0]+f[1])*sqrt(2.)/2.;
		f[1] = (swap -f[1])*sqrt(2.)/2.;
		return 1;
	}
	halfn = n>>1; /*/2;*/
	lowhalf = f;
	highhalf = f + halfn;

	AnfMatrix(halfn, lowhalf, sc_table);

	if(n>4) {
		TYPE2(halfn, highhalf);

		for(i=(int)(2*ROUND(log(n)/log(2))-4);i>1;i--) {
			if(i%2==1)
				TYPE3(halfn, i, highhalf, sc_table);
			else
				TYPE4(halfn, i, highhalf);
		}
	}
	TYPE1(halfn, highhalf, sc_table);
	return 1;
}

/*------------------------------------------------------------------*/
/*Normal butterfly operation in 1D_FDCT                             */
/*------------------------------------------------------------------*/
static void BN(int n, float *f){
	int i;
	float *swap;
	swap = (float *)malloc(sizeof(float)*n/2);
	for(i=0;i<(n>>1);i++) {
		swap[i] = f[i]; 
		f[i] = f[i] + f[n-i-1];
	}
	for(i=(n>>1);i<n;i++) 
		f[i] = swap[n-i-1] - f[i];

	free(swap);	
}

/*------------------------------------------------------------------*/
/*Maxtrix calculation type 1 in 1D_FDCT                             */
/*------------------------------------------------------------------*/
static void TYPE1(int n, float *f, float** sc_table) {
	int *bitr,i,tn;
	float *swap;
	swap = (float *)malloc(sizeof(float)*(n>>1));
	i = (int)ROUND((log(n)/log(2.0))+1);
	tn = i - 2;          /*4*n bit number -1*/
	bitr = bitReverse(i);
	for(i=0;i<(n>>1);i++) {
		swap[i] = f[i];
		f[i] = f[i]*sc_table[tn][bitr[n+i]] 
	               + f[n-i-1]*sc_table[tn][bitr[n+i]-1];
	}
	for(i=(n>>1);i<n;i++) {
		f[i] = f[i]*sc_table[tn][bitr[n+i]-1]
  	               - swap[n-i-1]*sc_table[tn][bitr[n+i]];
	}

	free(swap);
	free(bitr);	
}

/*------------------------------------------------------------------*/
/*Maxtrix calculation type 2 1D_FDCT                                */
/*------------------------------------------------------------------*/
static void TYPE2(int n, float *f) {
	int order,i;
	float *swap;

	swap = (float *)malloc(sizeof(float)*(n>>1));
	order = n>>2;	
	for(i=order;i<(order<<1);i++) {
		swap[i] = f[i]; 
		f[i] = (f[n-i-1] - f[i])*mycos(1,4); 
	}
	for(i=(order<<1);i<3*order;i++) 
		f[i] = (swap[n-i-1] + f[i])*mycos(1,4);

	free(swap);	
}

/*------------------------------------------------------------------*/
/*Maxtrix calculation type 3 1D_FDCT                                */
/*This is the most complicated, be careful about the indices.       */
/*------------------------------------------------------------------*/
static void TYPE3(int n, int q, float *f, float** sc_table) {
	int order,i,j,k,iorder,*bitr,bitNumber;
	float *swap;
	swap = (float *)malloc(sizeof(float)*n/2);
	order = (int)ROUND(log(n)/log(2))-((q-1)>>1)-2;/*pow(2,(q-1)/2);*/
	iorder = 1<<((q-3)>>1);
	bitNumber = order + 2;
	bitr = bitReverse(bitNumber);  /*bitReverse(q-1);*/
	i = iorder;
	k = n/(1<<((q+1)>>1));

	while (i < (n>>1)-iorder) {
		for(j=i;j<i+iorder;j++) {
			swap[j] = f[j];
			f[j] = f[n-j-1]*sc_table[order][bitr[k]]
 			       - f[j]*sc_table[order][bitr[k]-1];
		}
		i += iorder;
		for(j=i;j<i+iorder;j++) {
			swap[j] = f[j];
			f[j] = -1*f[n-j-1]*sc_table[order][bitr[k]-1]
                               - f[j]*sc_table[order][bitr[k]];
		}
		i += iorder*3;
		k ++;
	}
	i = (n>>1) + iorder;
	while (i < n-iorder) {
		for(j=i;j<i+iorder;j++) {
			f[j] = f[j]*sc_table[order][bitr[k]-1]
                               - swap[n-j-1]*sc_table[order][bitr[k]];
		} 
		i += iorder;
		for(j=i;j<i+iorder;j++) {
			f[j] = swap[n-j-1]*sc_table[order][bitr[k]-1] 
                               + f[j]*sc_table[order][bitr[k]];
		}
		i += iorder*3;
		k ++;
	}

	free(swap);
	free(bitr);
}

/*------------------------------------------------------------------*/
/*Maxtrix calculation type 4 1D_FDCT                                */
/*------------------------------------------------------------------*/
static void TYPE4(int n, int p, float *f) {
	int i,j,k,l;
	float *swap;

	l = 1<<(p>>1); /*pow(2,p/2);*/
	k = l>>1;
	swap = (float *)malloc(sizeof(float)*k);
	l = l - 1; /*biggest index*/
	i = 0;
	while(i<n) {
		for(j=0;j< k;j++) {
			swap[j] = f[i+j];
			f[i+j] = f[i+j] + f[i+l-j];		
		}
		i += k;

		for(j=0;j< k;j++) {
			f[i+j] = swap[k-j-1] - f[i+j];		
		}
		i += k;

		for(j=0;j< k;j++) {
			swap[j] = f[i+j];
			f[i+j] = f[i+l-j] - f[i+j];		
		}
		i += k;

		for(j=0;j< k;j++) {
			f[i+j] = f[i+j] + swap[k-j-1];		
		}
		i += k;
	}

	free(swap);
}

/*------------------------------------------------------------------*/
/*This function returns sin(i*PI/j).                                */
/*------------------------------------------------------------------*/
static float mysin(int i, int j) {
	float angle;
	angle = i * PI / j;	
	return (sin(angle));
}

/*------------------------------------------------------------------*/
/*This function returns cos(i*PI/j).                                */
/*------------------------------------------------------------------*/
static float mycos(int i, int j) {
	float angle;
	angle = i * PI / j;
	return (cos(angle));
}

/*-----------------------------------------------------------------------*/
/*This function creates the sine_cosine-table needed by 1D_FDCT function.*/
/*This table provides all the results of sine_cosine calculations        */
/*needed in the whole 1D_DCT calculation of n points                     */
/*The table sc_table is a 2-Dimensional table.                           */
/*The element sct(i,j)=sin(i/2*PI/pow(2,j+3)) if i is even.              */
/*The element sct(i,j)=cos((i+1)/2*PI/pow(2,j+3)) if i is odd.           */
/*-----------------------------------------------------------------------*/
static float **creat_sct(int n) {
	float **sc_table;
	int i,j,rows;
	rows = (int)ROUND(log(n)/log(2)) -1;
	sc_table = (float **)malloc(sizeof(float*)*rows);
	
	for(i=0;i<rows;i++) {
		/*cols*/
		sc_table[i] = (float *)malloc(sizeof(float)*(1<<(i+2)));
		 
		for(j=1;j<(1<<(i+2));j+=2) {
			sc_table[i][j] = mysin(j,1<<(i+3));
			sc_table[i][j-1] = mycos(j,1<<(i+3));
		}
	}	
	return sc_table; 
}

/*------------------------------------------------------------------*/
/*This is the 2D_FDCT function taking a rows_then_columns approach. */
/*------------------------------------------------------------------*/
Image* dct_transform(Image* inputImage, int blocksize) {	
	int i,bx,by,gridx,gridy,bands,rows,cols,currentl,num;
	float *line, **sc_table, **input;
  	Image *tempimage;
	int  ww,w, h, old_w, old_h;
  	int  cc, x, y, zeropad = 0;
	unsigned int count,count1,band;

  	tempimage=inputImage;
	/* not necessary to include the zero padding function inside the dct_transform */
  	/*if ( zeropad ) {
      		printf("\nZero padding... \n");
      		tempimage=image_allocate(inputImage->image_format,inputImage->color_space,inputImage->bands,h,w,inputImage->image_ptr[0]->data_type,inputImage->image_ptr[0]->data_format);
	for(band=0;band<inputImage->bands;band++)
	for(count=0;count<old_h;count++)
	for(count1=0;count1<old_w;count1++)
		copypoint(inputImage,band,count,count1,tempimage,count,count1);
	for(band=0;band<inputImage->bands;band++)
	for(count=old_h;count<h;count++)
	for(count1=old_w;count1<w;count1++)
		setpoint(tempimage,band,count,count1,0,0);
      	delete_Image(inputImage);
  }
  	tempimage=inputImage;*/


	line = (float *)malloc(sizeof(float)*blocksize);
	rows = (int)tempimage->image_ptr[0]->rows;
	cols = (int)tempimage->image_ptr[0]->cols;
	bands = (int)tempimage->bands;

	sc_table = creat_sct(blocksize);
	
	cast_Image(tempimage, CVIP_FLOAT);

	for(i=0;i<bands;i++) {
		input = getData_Image(tempimage, i);
		for(gridy=0;gridy<rows;gridy+=blocksize) {
			for(gridx=0;gridx<cols;gridx+=blocksize) {
				for(by=0;by<blocksize;by++) {

					currentl=gridy+by;

					for(bx=0;bx<blocksize;bx++) {
						line[bx]
						=input[currentl][gridx+bx];
					}
					line 
					= FDCT_1D(blocksize, line, sc_table);
					for(bx=0;bx<blocksize;bx++) {
						input[currentl][gridx+bx]
						= line[bx];
					}
				}
				
				for(bx=0;bx<blocksize;bx++) {
					currentl=gridx+bx;
					for(by=0;by<blocksize;by++) {
						line[by]
						=input[gridy+by][currentl];
					}
					line 
					= FDCT_1D(blocksize, line, sc_table);
					for(by=0;by<blocksize;by++) {
						input[gridy+by][currentl]
						= line[by];
					}
				}		
			}
		}
	}
	free(line);
	num = (int)ROUND(log(blocksize)/log(2)) -1;
	for(i=0;i<num;i++) free((char *)sc_table[i]);
	free(sc_table);	
	return tempimage;
}

/*------------------------------------------------------------------*/
/*This is the inverse 1D_DCT function.                              */
/*The function "float **creat_sct(int n)" must be called first      */
/*to create the sine_cosine_table needed by this function.          */
/*------------------------------------------------------------------*/
static float* IFDCT_1D(int n, float *f, float** sc_table) {
	int *reorder,i;
	float *result;
	if(n==1) {
		printf("\nError: n must be larger than 1.\n");
		exit(0);
	}
	result = (float *)malloc(sizeof(float)*n);
	i = (int)ROUND(log(n)/log(2));

	reorder = bitReverse((int)ROUND(log(n)/log(2)));
	
	for(i=0;i<n;i++) {
		result[i] = f[reorder[i]];
	}

	IAnfMatrix(n, result, sc_table);
 
	free(f);	
	free(reorder);		
	return result;	
}

/*------------------------------------------------------------------*/
/*This is the inverse 2D_DCT function                               */
/*taking a rows_then_columns approach.                              */
/*------------------------------------------------------------------*/
Image* idct_transform(Image* inputImage, int blocksize) {	
	int i,bx,by,gridx,gridy,bands,rows,cols,currentl,num;
	float *line, **sc_table, **input;
	line = (float *)malloc(sizeof(float)*blocksize);
	rows = (int)inputImage->image_ptr[0]->rows;
	cols = (int)inputImage->image_ptr[0]->cols;
	bands = (int)inputImage->bands;

	sc_table = creat_sct(blocksize);

	for(i=0;i<bands;i++) {
		input = getData_Image(inputImage, i);
		for(gridy=0;gridy<rows;gridy+=blocksize) {
			for(gridx=0;gridx<cols;gridx+=blocksize) {
				for(by=0;by<blocksize;by++) {
					currentl=gridy+by;
					for(bx=0;bx<blocksize;bx++) {
						line[bx]
						=input[currentl][gridx+bx];
					}
					line 
					= IFDCT_1D(blocksize, line, sc_table);
					for(bx=0;bx<blocksize;bx++) {
						input[currentl][gridx+bx]
						= line[bx];
					}
				}
				
				for(bx=0;bx<blocksize;bx++) {
					currentl=gridx+bx;
					for(by=0;by<blocksize;by++) {
						line[by]
						=input[gridy+by][currentl];
					}
					line 
					= IFDCT_1D(blocksize, line, sc_table);
					for(by=0;by<blocksize;by++) {
						input[gridy+by][currentl]
						= line[by];
					}
				}		
			}
		}
	}
	free(line);
        num = (int)ROUND(log(blocksize)/log(2)) -1;
        for(i=0;i<num;i++) free((char *)sc_table[i]);
	free(sc_table);

	return inputImage;
}

/*------------------------------------------------------------------*/
/*This function performances all the matrix calculation needed by   */
/*the inverse 1D_DCT function.                                      */
/*------------------------------------------------------------------*/
static int IAnfMatrix(int n, float *f, float** sc_table) {
	int i,halfn;
	float *lowhalf,*highhalf,swap;

	if(n == 2) {
		swap = f[0];
		f[0] = (f[0]+f[1])*sqrt(2.)/2.;
		f[1] = (swap -f[1])*sqrt(2.)/2.;

		return 1;
	}

	halfn = n>>1; /*/2;*/
	lowhalf = f;
	highhalf = f + halfn;

	IAnfMatrix(halfn, lowhalf, sc_table);

	ITYPE1(halfn, highhalf, sc_table);
 
	if(n>4) {
		for(i=2;i<=(int)(2*ROUND(log(n)/log(2))-4);i++) {
			if(i%2==1) 
				ITYPE3(halfn, i, highhalf, sc_table);
			else 
				TYPE4(halfn, i, highhalf); 

		}
		TYPE2(halfn, highhalf);
	}

	BN(n,f);

	return 1;
}

/*------------------------------------------------------------------*/
/*Matrix calculation type 1 in inverse 1D_FDCT                      */
/*------------------------------------------------------------------*/
static void ITYPE1(int n, float *f, float** sc_table) {
	int *bitr,i,tn,tm;
	float *swap;
	swap = (float *)malloc(sizeof(float)*(n>>1));
	i = (int)ROUND(log(n)/log(2))+1;
	bitr = bitReverse(i);
	tn = i - 2;          /*4*n bit number -1*/

	tm = n << 1;

	for(i=0;i<(n>>1);i++) {
		swap[i] = f[i];

		f[i] = f[i]*sc_table[tn][bitr[n+i]] 
	               - f[n-i-1]*sc_table[tn][tm - bitr[n+i]];

	}
	for(i=(n>>1);i<n;i++) {

		f[i] = f[i]*sc_table[tn][bitr[n+i]-1]
  	               + swap[n-i-1]*sc_table[tn][tm - bitr[n+i] - 1];

	}

	free(swap);
	free(bitr);	
}

/*------------------------------------------------------------------*/
/*Matrix calculation type 3 in inverse 1D_FDCT                      */
/*------------------------------------------------------------------*/
static void ITYPE3(int n, int q, float *f, float** sc_table) {
	int order,i,j,k,iorder,*bitr,bitNumber,orderh;
	float *swap;
	swap = (float *)malloc(sizeof(float)*n/2);
	order = (int)ROUND(log(n)/log(2))-((q-1)>>1)-2;/*pow(2,(q-1)/2);*/
	
	iorder = 1<<((q-3)>>1);
	bitNumber = order + 2;
	bitr = bitReverse(bitNumber);  /*bitReverse(q-1);*/
	i = iorder;
	k = n/(1<<((q+1)>>1));
	orderh = k << 1;

	while (i < (n>>1)-iorder) {
		for(j=i;j<i+iorder;j++) {
			swap[j] = f[j];

			f[j] = f[n-j-1]*sc_table[order][orderh - bitr[k]-1]
 			       - f[j]*sc_table[order][bitr[k]-1];
		}
		i += iorder;
		for(j=i;j<i+iorder;j++) {
			swap[j] = f[j];

			f[j] = -1*f[n-j-1]*sc_table[order][orderh - bitr[k]]
                               - f[j]*sc_table[order][bitr[k]];
		}
		i += iorder*3;
		k ++;
	}
	i = (n>>1) + iorder;
	while (i < n-iorder) {
		for(j=i;j<i+iorder;j++) {

			f[j] = f[j]*sc_table[order][bitr[k]-1]
                               - swap[n-j-1]*sc_table[order][orderh-bitr[k]-1];
		} 
		i += iorder;
		for(j=i;j<i+iorder;j++) {

			f[j] = swap[n-j-1]*sc_table[order][orderh - bitr[k]] 
                               + f[j]*sc_table[order][bitr[k]];
		}
		i += iorder*3;
		k ++;
	}

	free(swap);
	free(bitr);
}

Image *dct_setup(Image *input_Image, CVIP_BOOLEAN *remap)
{
   int c, block_size, *hptr,n_rows,n_cols;
   Image *resultP;
   HISTORY stuff;
   char *answer;

   n_rows=input_Image->image_ptr[0]->rows;
   n_cols=input_Image->image_ptr[0]->cols;
   fprintf(stdout, "\n Discrete Cosine Transform\n");
   fprintf(stdout, "\t1 - dct_transform\n");
   fprintf(stdout, "\t2 - Inverse dct_transform\n\n");
   fprintf(stdout, "Your Choice ->");

   while( (c = getchar()) != '1' && (c != '2') )
      if( c != '\n' )
         fprintf(stderr, "Your Choice ->");


   switch( c ) {
      case '1': *remap = CVIP_NO;
		getchar();
                block_size = get_block_size();
                fprintf(stdout, "Working ...\n");
                if(get_zpad_dims(input_Image, &n_rows, &n_cols, block_size)==CVIP_NO)
                   zero_pad(input_Image, n_rows, n_cols);
		resultP = dct_transform(input_Image, block_size );
                /* Add history Information */
                stuff=(HISTORY)malloc(sizeof(struct history));
                stuff->packetP = (PACKET *)malloc(sizeof(PACKET));
                stuff->packetP->dsize=1;
                stuff->packetP->dtype=(CVIP_TYPE *)malloc(sizeof(CVIP_TYPE));
                stuff->packetP->dtype[0]=CVIP_INTEGER;
                hptr=(int *)malloc(sizeof(int));
                hptr[0]=block_size;
		stuff->packetP->dptr = (void **)malloc(sizeof(void*));
                stuff->packetP->dptr[0]=(int *)hptr;
        	stuff->packetP->dsize = 1;
                stuff->next=(HISTORY)NULL;
                stuff->ftag=DCTXFORM;
                history_add(resultP, stuff);
   		fprintf(stderr, "returning dct_transform image\n");
                break;

      case '2': *remap = CVIP_NO;
               if(!history_check(DCTXFORM, input_Image)) {
		  answer = (char*)malloc(sizeof(char)*10);
                  fprintf(stdout, "Enter blocksize used for forward DCT:\n");
                  (void)gets(answer);
                  block_size=atoi(answer);
                  free(answer);
               }
               else {
                  stuff=history_get(input_Image, DCTXFORM);
		  GET_HIST_DATA(stuff,0,block_size);
               }
                fprintf(stderr, "Working...\n");
		resultP = idct_transform( input_Image, block_size );

                /* Add history Information */
                stuff=(HISTORY)malloc(sizeof(struct history));
                stuff->packetP = (PACKET *)malloc(sizeof(PACKET));
                stuff->packetP->dsize=1;
                stuff->packetP->dtype=(CVIP_TYPE *)malloc(sizeof(CVIP_TYPE));
                stuff->packetP->dtype[0]=CVIP_FLOAT;
                hptr=(int *)malloc(sizeof(int));
                hptr[0]=block_size;
		stuff->packetP->dptr = (void **)malloc(sizeof(void*));
	        stuff->packetP->dsize = 1;
                stuff->packetP->dptr[0]=(int *)hptr;
                stuff->next=(HISTORY)NULL;
                stuff->ftag=I_DCTXFORM;
                history_add(resultP, stuff);
   		fprintf(stderr, "returning idct_transform image\n");
                break;

      default : fprintf(stderr, "Shouldn't Happen!\n"); break;
   }
   return( resultP );
}
