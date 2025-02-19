/******************************************************************************
    ======================================================================
    Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
    ======================================================================

                   Name: hist_feature.c
          Expanded Name: histgram features 

             Parameters: Pointer to the original image of type Image
		 	 Pointer to the labeled image of type Image 
                         coordinates of the point on the labled image to
			 select the object of interest:
			 r -- row coordinate, c -- column coordinate

                Returns: pointer to an array containing histogram features,
			 the sequence is: mean, standard deviation, skew,
			 		  energy and entropy.
			 If the original image is a color image, the first
			 five values are above five histogram features for
			 band 0; the next five data are for band 1, and so on.
 
            Description: The original image can be of any data types: CVIP_BYTE,
			 CVIP_SHORT, CVIP_INTEGER, CVIP_FLOAT and CVIP_DOUBLE.

            Diagnostics: None

    Initial Coding Date: 6/20/96
Last Modifications Made: 7/7/96
             References: None

              Author(s): Wenxing Li


          Southern Illinois University @ Edwardsville

*******************************************************************************/


#include <math.h>
#include "CVIPimage.h"

extern long area();

# define MAXGRAYVALUE   90000//16384		/* 128 * 128 */

struct histstruct
{
 void	      	     * data;
 long	               num;
 int		       bands;
 struct histstruct   * next;
};

typedef struct
{
 long	     	     * P;
 long	               length;
 struct histstruct   * head;
} HISTRET;

/* huge and minus values, linked list; 0--MAXGRAYVALUE, array */
#define HISTPROCESS(type_,image_,i_,j_,P_)\
  {	register struct histstruct	* mid_; \
	register int		          found_=1; \
        register type_		          value_;\
        value_ = ((type_ **)image_)[i_][j_];\
	if ( value_ < MAXGRAYVALUE && value_ >= 0) \
	   P_[k*MAXGRAYVALUE + (long)value_]++;\
	else if (head == NULL) \
	       { head = (struct histstruct *)malloc(sizeof(struct histstruct));\
		 tail = head; \
 		 (type_ *)tail->data = (type_ *)malloc(sizeof(type_)); \
		 *((type_ *)tail->data) = value_;\
		 tail->num = 1;\
		 tail->bands = k;\
		 tail->next = NULL;\
	       }\
	     else { mid_ = head; \
		    while (mid_ && found_) \
		      if ( *((type_ *)(mid_->data)) == value_) \
			 { mid_->num ++; found_ = 0;}\
		      else mid_ = mid_->next;\
		    if (found_) \
		      { tail->next = (struct histstruct *)malloc(sizeof(struct histstruct));\
			tail = tail->next;\
			(type_ *)tail->data = (type_ *)malloc(sizeof(type_)); \
			*((type_ *)tail->data) = value_;\
			tail->num = 1;\
			tail->bands = k;\
			tail->next = NULL;\
		      }\
		  }\
  }


/* for an object in a multiband real image of any data type */
static HISTRET * get_histogram(Image * inputImage, Image * labeledImage,
	int r, int c)
{ int	    	 	i, j, k, label; 
 CVIP_TYPE	    		dtype;
 long	       	      * P, n;
 void	      	     ** image;
 unsigned int    	rows, cols;
 struct histstruct    * head=NULL, * tail=NULL;
 HISTRET       	      * retp;
 int		     ** limage;

 rows = inputImage->image_ptr[0]->rows;
 cols = inputImage->image_ptr[0]->cols;
 limage = (int **)labeledImage->image_ptr[0]->rptr;
 label = limage[r][c];

 dtype = inputImage->image_ptr[0]->data_type;
 if (dtype == CVIP_BYTE) { P = (long *)malloc(256 * sizeof(long) * inputImage->bands);
		      for (n=0; n<256*inputImage->bands; n++) P[n] = (long)0;
		    }
 else		    { P = (long *)malloc(MAXGRAYVALUE * sizeof(long) * inputImage->bands);
		      for (n=0; n<MAXGRAYVALUE*inputImage->bands; n++) P[n] = (long)0;
		    }

 for (k=0; k<inputImage->bands; k++)
   { image = (void **)inputImage->image_ptr[k]->rptr;
     for (i=0; i<rows; i++)
       for (j=0; j<cols; j++)
	 if (limage[i][j] == label)
	   switch(dtype)
 	       { case CVIP_BYTE: P[k*256 + ((byte **)image)[i][j]]++; break;
  		 case CVIP_SHORT:  HISTPROCESS(short,image,i,j,P)  break;
    		 case CVIP_INTEGER:  HISTPROCESS(int,image,i,j,P)  break;
    		 case CVIP_FLOAT:  HISTPROCESS(float,image,i,j,P)  break;
    		 case CVIP_DOUBLE:HISTPROCESS(double,image,i,j,P)
	       }
   }

 retp = (HISTRET *)malloc(sizeof(HISTRET));
 retp->P = P;
 retp->head = head;
 if (dtype == CVIP_BYTE) retp->length = 256;
 else 		    retp->length = MAXGRAYVALUE;
 return (retp);
}

#define  HISTFEATNUM    5
#define  LOGE2		log(2)

#define  MEECOMPUTE(data_,num_,size_)\
 	  mean   += data_ * num_;\
  	 energy  += ((double)num_ / (double)size_) * ((double)num_ / (double)size_);\
  	 entropy -= (double)num_ * (log(num_) - log(M))/LOGE2;

#define DSCOMPUTE(data_,num_)\
   variance += pow((data_ - ptr[k*HISTFEATNUM]),2) * num_;\
   skew     += pow((data_ - ptr[k*HISTFEATNUM]),3) * num_;  

void mee_hist(HISTRET * retp, long M, double * ptr, int bands, CVIP_TYPE dtype)
{long 		     j, length, num;
 long		   * P;
 int		     k;
 struct histstruct * mid;
 double		     mean, energy, entropy;

 length = retp->length;
 mid  = retp->head;
 P  = retp->P;
 
 for (k=0; k<bands; k++)
   { mean = 0; energy = 0; entropy = 0;

     for (j=0; j<length; j++)
       if (P[k*length + j] != 0) 
	 {   num    = P[k*length + j];
	    mean   += j * num;
	   energy  += ((double)num / (double)M) * ((double)num / (double)M);
	   entropy -= (double)num * (log(num) - log(M))/LOGE2;
	 }
     if (mid) while (mid && mid->bands == k) 
       { switch(dtype)
 	   { case CVIP_SHORT:   MEECOMPUTE(*((short *)mid->data),mid->num,M)  break;
    	     case CVIP_INTEGER:   MEECOMPUTE(*((int *)mid->data),mid->num,M)  break;
    	     case CVIP_FLOAT:   MEECOMPUTE(*((float *)mid->data),mid->num,M)  break;
    	     case CVIP_DOUBLE: MEECOMPUTE(*((double *)mid->data),mid->num,M)
	    }
	 mid = mid->next;
       }
 
     ptr[k*HISTFEATNUM]     = mean / M;
     ptr[k*HISTFEATNUM + 3] = energy;
     ptr[k*HISTFEATNUM + 4] = entropy / M;
   }
}

void ds_hist(HISTRET * retp, long M, double * ptr, int bands, CVIP_TYPE dtype)
{long 		     j, length;
 long		   * P;
 int		     k;
 struct histstruct * mid;
 double		     variance, skew;

 length = retp->length;
 mid  = retp->head;
 P  = retp->P;

 for (k=0; k<bands; k++)
   { variance = 0; skew = 0;

     for (j=0; j<length; j++)
       if (P[k*length + j] != 0) 
	 { variance += pow((j - ptr[k*HISTFEATNUM]),2)*P[k*length + j];
	   skew     += pow((j - ptr[k*HISTFEATNUM]),3)*P[k*length + j];   
	 }
     if (mid) while (mid && mid->bands == k) 
       { switch(dtype)
 	   { case CVIP_SHORT:   DSCOMPUTE(*((short *)mid->data),mid->num)  break;
    	     case CVIP_INTEGER:   DSCOMPUTE(*((int *)mid->data),mid->num)  break;
    	     case CVIP_FLOAT:   DSCOMPUTE(*((float *)mid->data),mid->num)  break;
    	     case CVIP_DOUBLE: DSCOMPUTE(*((double *)mid->data),mid->num)
	    }
	 mid = mid->next;
       }
 
     ptr[k*HISTFEATNUM + 1] = sqrt(variance / M);
     ptr[k*HISTFEATNUM + 2] = (skew / M) / pow(ptr[k*HISTFEATNUM + 1], 3) ;
   }
}

void del_histogram(HISTRET * retp)
{long		   * P;
 struct histstruct * head, * mid;
 char 		   * data;

 P = retp->P;
 head = retp->head;

 free((char *)P);

 while (head) 
   { mid = head;
     head = head->next;
     data = (char *)mid->data;
     free(data);
     free(mid);
   }
 
 free((char *)retp);
}

double * hist_feature(Image * originalImage, Image * labeledImage, int r, int c)
{long		     M;
 double 	   * ptr;
 CVIP_TYPE		     dtype;
 HISTRET 	   * retp;

 ptr = (double *)malloc(originalImage->bands * HISTFEATNUM * sizeof(double));
 
 retp = get_histogram(originalImage, labeledImage, r, c);

 M  = area(labeledImage, r, c); 
 dtype = originalImage->image_ptr[0]->data_type;
 
 mee_hist(retp, M, ptr, originalImage->bands, dtype);
 
 ds_hist(retp, M, ptr, originalImage->bands, dtype);

 del_histogram(retp);

 return (ptr);
}
 
