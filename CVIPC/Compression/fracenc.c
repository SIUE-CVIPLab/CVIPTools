/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: fracenc.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Sun Feb 15 18:50:27 CST 1998
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Makam Sreenivas
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1996 SIUE - by Scott Umbaugh and Makam Sreenivas.
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
** $Log: fracenc.c,v $
** Revision 1.6  2001/04/09 14:00:29  ycheng
** fixed bugs so that it works under Linux.
**
** Revision 1.5  1998/04/29 20:28:15  smakam
** *** empty log message ***
**
** Revision 1.4  1998/04/17 18:43:34  smakam
** removed unwanted statements (comments)
**
** Revision 1.3  1998/03/30 19:13:08  smakam
** checked the bombing of the function
**
** Revision 1.1  1998/02/18 05:45:38  cvip
** Initial revision
**
*
****************************************************************************/
/**************************************************************************/
/* Encode a byte image using a fractal scheme with a quadtree partition   */
/*                                                                        */
/*       Copyright 1993,1994 Yuval Fisher. All rights reserved.           */
/*	Modified by Makam Sreenivas Spring 1998				  */
/*                                                                        */
/* Version 0.03 3/14/94                                                   */
/**************************************************************************/

/*
Quadtree Based Fractal Image Compressor.
-----------------------------------------

Written by:
Yuval Fisher
INLS 0402
UCSD
La Jolla, CA 92093
email: yfisher@ucsd.edu

   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

 1. You may copy and distribute verbatim or modified copies of the
Programs' source code as you receive it, in any medium, provided that
you conspicuously and appropriately publish on each copy an appropriate
copyright notice and disclaimer of warranty; keep intact all the notices
that refer to this License and to the absence of any warranty; attribute
the programs to all their authors all authors of the programs; and give
any other recipients of the Programs a copy of this License along
with the Program.

2. You may modify your copy or copies of the Programs or any portion of
it, and copy and distribute such modifications under the terms of Paragraph
1 above, provided that you also do the following:

    a) cause the modified files to carry prominent notices stating that
    you changed the files and the date of any change; and

    b) cause the whole of any work that you distribute or publish, that
    in whole or in part contains the Programs or any part thereof, either
    with or without modifications, to be licensed at no charge to all
    third parties under the terms of this License.

3. You may not copy, modify, sublicense, distribute or transfer the
Program for any commercial purpose without the express agreement of
its principal author.

4. By copying, distributing or modifying the Program (or any work based
on the Program) you indicate your acceptance of this license to do so,
and all its terms and conditions.

5. BECAUSE THE PROGRAMS ARE LICENSED FREE OF CHARGE, THERE IS NO WARRANTY
FOR THE PROGRAMS, TO THE EXTENT PERMITTED BY APPLICABLE LAW.  EXCEPT WHEN
OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES
PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED
OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE ENTIRE RISK AS
TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU.  SHOULD THE
PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING,
REPAIR OR CORRECTION.
*/

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPimage.h"
#include "CVIPtransform.h"
#include "fractal.h"

static partition_image(int atx, int aty, int hsize, int vsize, double tol);

#define DEBUG 0
#define GREY_LEVELS 255

#define bound(a)   ((a) < 0.0 ? 0 : ((a)>255.0? 255 : a))

/* various function declarations to keep compiler warnings away. ANSI     */
/* prototypes can go here, for the hearty.                                */
static void fatal();
static int convert_pow_two(int number);
static void list_free(struct classified_domain *node);
static void pack(int size, long int value,FILE *foutf);
static int compute_sums(int hsize, int vsize,byte **theImage);

/* The following #define allocates an hsize x vsize  matrix of type TYPE */
#define matrix_allocate1(matrix, hsize, vsize, TYPE) {\
    TYPE *imptr; \
    int _i; \
    matrix = (TYPE **)malloc((vsize)*sizeof(TYPE *));\
    imptr = (TYPE*)malloc((long)(hsize)*(long)(vsize)*sizeof(TYPE));\
    if (imptr == NULL) {\
        fatal("\nNo memory in matrix allocate."); return -1;}\
    for (_i = 0; _i<vsize; ++_i, imptr += hsize) \
        matrix[_i] = imptr; \
 }

#define free1(matrix) {\
	for(i=0;i<vsize/2;i++)\
	free(matrix[i]);\
	free((char *)matrix);\
}

#define free2(matrix,i) {\
	for(j=0;j<(domain.no_v_domains[i]);j++)\
	free(matrix[j]);\
	free(matrix);\
}
#define swap(a,b,TYPE)           {TYPE _temp; _temp=b; b=a; a= _temp;}

static byte **image = NULL;
double     **domimage[4];    /* Decimated input image used for domains    */

static double max_scale = 1.0;      /* Maximum allowable grey level scale factor */

static int    s_bits = 5,           /* Number of bits used to store scale factor */
       o_bits = 7,           /* Number of bits used to store offset       */
       min_part = 4,         /* Min and max _part determine a range of    */
       max_part = 6,         /* Range sizes from hsize>>min to hsize>>max */
       dom_step = 1,         /* Density of domains relative to size       */
       dom_step_type = 0,    /* Flag for dom_step a multiplier or divisor */
       dom_type = 0,         /* Method of generating domain pool 0,1,2..  */
       only_positive = 0,    /* A flag specifying use of positive scaling */
       subclass_search = 0,  /* A flag specifying classes searched        */
       fullclass_search = 0, /* A flag specifying classes searched        */
       *bits_needed,         /* Number of bits to encode domain position. */
       zero_ialpha,          /* The const ialpha when alpha = 0           */
       max_exponent;         /* The max power of 2 side of square image   */
                             /* that fits in our input image.             */


                             /* The class_transform gives the transforms  */
                             /* between classification numbers for        */
                             /* negative scaling values, when brightest   */
                             /* becomes darkest, etc...                   */
int    class_transform[2][24] = {23,17,21,11,15,9,22,16,19,5,13,3,20,10,18,
                                 4,7,1,14,8,12,2,6,0,
                                 16,22,10,20,8,14,17,23,4,18,2,12,11,21,5,
                                 19,0,6,9,15,3,13,1,7};

                             /* rot_transform gives the rotations for     */
                             /* domains with negative scalings.           */
int    rot_transform[2][8] = {7,4,5,6,1,2,3,0, 2,3,0,1,6,7,4,5};

struct domain_data {
       int *no_h_domains,    /* The number of domains horizontally for    */
           *no_v_domains,    /* each size.                                */
           *domain_hsize,    /* The size of the domain.                   */
           *domain_vsize,    /* The size of the domain.                   */
           *domain_hstep,    /* The density of the domains.               */
           *domain_vstep;    /* The density of the domains.               */
struct domain_pixels {       /* This is a three (sigh) index array that   */
       int dom_x, dom_y;     /* dynamically allocated. The first index is */
       double sum,sum2;      /* the domain size, the other are two its    */
       int sym;              /* position. It contains the sum and sum^2   */
} ***pixel;                  /* of the pixel values in the domains, which */
} domain;                    /* are computed just once.                   */ 
                             

struct classified_domain {             /* This is a list which containes  */
       struct domain_pixels *the;      /* pointers to  the domain data    */
       struct classified_domain *next; /* in the structure above. There   */
} **the_domain[3][24];                 /* are three classes with 24 sub-  */
                                       /* classes. Using this array, only */
                                       /* domains and ranges in the same  */
                                       /* class are compared..            */
                                       /* The first pointer points to the */
                                       /* domain size the the second to   */
                                       /* list of domains.                */

FILE *output;                /* Output FILE containing compressed data    */

int frac_compress(Image *inputImage,char *filename,double tol,int min_part1,int max_part1,int dom_type1,int dom_step1,char c1,char c2,int s_bits1,int o_bits1)
{
    /* Defaults are set initially */
    int            i,j,k,
                   hsize = -1,           /* The horizontal and vertical    */
                   vsize = -1,            /* size of the input image.       */
		   val,
		   bands=0;
    long counter;
    struct stat s_buf;
    int a,b,c,band;
    int hsize_temp,vsize_temp;

    if(min_part1!=-1)
    min_part=min_part1;
    if(max_part1!=-1)
    max_part=max_part1;
    if(dom_type1!=-1)
    dom_type=dom_type1;
    if(dom_step1!=-1)
    dom_step=dom_step1;
    if(s_bits1!=-1)
    s_bits=s_bits1;
    if(o_bits1!=-1)
    o_bits=o_bits1;
    if(c1=='y') 
	fullclass_search=1;
    if(c2=='y') 
	subclass_search=1;
	
    hsize=getNoOfRows_Image(inputImage);
    vsize=getNoOfCols_Image(inputImage);
    bands=getNoOfBands_Image(inputImage);
    hsize_temp=convert_pow_two(hsize);
    vsize_temp=convert_pow_two(vsize);
    if(hsize_temp>vsize_temp) vsize_temp=hsize_temp;
    else hsize_temp=vsize_temp;

    if((!check_pow_two(hsize)) || (!check_pow_two(vsize)) || (hsize!=vsize))
    zero_pad(inputImage,hsize_temp,vsize_temp);
    hsize=hsize_temp;
    vsize=vsize_temp;

    /* allocate memory for domain data and initialize it */
    if ((output = fopen(filename, "wb")) == NULL) {
        printf("Can't open output file.");
	if(inputImage) delete_Image(inputImage);
	return -1;
    }
    /* puts the characters 'fra' in to the file */
    fputc(102,output);
    fputc(114,output);
    fputc(97,output);
    /* output some data into the outputfile. */
    pack(4,(long)min_part,output);
    pack(4,(long)max_part,output);
    pack(4,(long)dom_step,output);
    pack(1,(long)dom_step_type,output);
    pack(2,(long)dom_type,output);
    pack(4,(long)s_bits,output);
    pack(4,(long)o_bits,output);
    pack(12,(long)hsize,output);
    pack(12,(long)vsize,output);
    pack(4,(long)bands,output);


    for( band=0; band< bands; band++) {
    image=getData_Image(inputImage,band);
    /* allocate memory for the input image. Allocating one chunck saves  */
    /* work and time later.                                              */
    matrix_allocate1(domimage[0], hsize/2, vsize/2, double)
    matrix_allocate1(domimage[1], hsize/2, vsize/2, double)
    matrix_allocate1(domimage[2], hsize/2, vsize/2, double)
    matrix_allocate1(domimage[3], hsize/2, vsize/2, double)
    /* max_ & min_ part are variable, so this must be run time allocated */
    bits_needed = (int *)malloc(sizeof(int)*(1+max_part-min_part));
	/* This is the quantized value of zero scaling.. needed later */
    val=compute_sums(hsize,vsize,image);
    if(val<0) {
    	free(bits_needed);
    	free1(domimage[0]);
    	free1(domimage[1]);
    	free1(domimage[2]);
    	free1(domimage[3]);
    	return -1;
    }
    zero_ialpha = 0.5 + (max_scale)/(2.0*max_scale)*(1<<s_bits);

    /* The following routine takes a rectangular image and calls the */
    /* quadtree routine to encode square sum-images in it.           */
    /* the tolerance is a parameter since in some applications different */
    /* regions of the image may need to be compressed to different tol's */
    printf("\nEncoding Image.....");
//    fflush(stdout);
    partition_image(0, 0, hsize,vsize, tol);
    printf("Done.");
//    fflush(stdout);

    /* stuff the last byte if needed */
    
    /* Free allocated memory*/
    free(bits_needed);
    free(domimage[0]);
    free(domimage[1]);
    free(domimage[2]);
    free(domimage[3]);
    free(domain.no_h_domains);
    free(domain.no_v_domains);
    free(domain.domain_hsize);
    free(domain.domain_vsize);
    free(domain.domain_hstep);
    free(domain.domain_vstep);
    /*for (i=0; i <= max_part-min_part; ++i) 
        free2(domain.pixel[i],i);*/
    for (i=0; i <= max_part-min_part; ++i) 
        free(domain.pixel[i]);
    free(domain.pixel);
    /*free(image[0]);*/
    for (i=0; i <= max_part-min_part; ++i) 
    for (k=0; k<3; ++k) 
     for (j=0; j<24; ++j) list_free(the_domain[k][j][i]);
     }
    pack(-1,(long)0,output);
    fflush(output);
    fclose(output);
    if(stat(filename,&s_buf)==0){
	    counter =(long)s_buf.st_size;
     printf("\nThe original raw data occupies %ld bytes", hsize*vsize*bands);
     printf("\nThe compressed data occupies %ld bytes",counter );
     printf("\nCompression ratio 1 : %f\n", (hsize*vsize*bands)/(float)counter);
   }

     if (inputImage) delete_Image(inputImage);
    return 0;
}

/* ************************************************************** */
/* free memory allocated in the list structure the_domain         */
/* ************************************************************** */
void list_free(node)
struct classified_domain *node;
{
     if (node->next != NULL)
       list_free(node->next);
     free(node);
}

/* ************************************************************** */
/* return the average pixel value of a region of the image.       */
/* ************************************************************** */
void average(x,y,xsize,ysize, psum, psum2)
int x,y,xsize,ysize;
double *psum, *psum2;
{
    register int i,j,k;
    register double pixel;
    *psum = *psum2 = 0.0;
    k = ((x%2)<<1) + y%2;
    x >>= 1; y >>= 1;
    xsize >>= 1; ysize >>= 1;
    for (i=x; i<x+xsize; ++i)
    for (j=y; j<y+ysize; ++j) {
	   pixel = domimage[k][j][i];
       *psum += pixel;
       *psum2 += pixel*pixel;
    }
}

/* ************************************************************** */
/* return the average pixel value of a region of the image. This  */
/* routine differs from the previous in one slight way. It does   */
/* not average 2x2 sub-images to pixels. This is needed for clas- */
/* sifying ranges rather than domain where decimation is needed.  */
/* ************************************************************** */
void average1(x,y,xsize,ysize, psum, psum2)
int x,y,xsize,ysize;
double *psum, *psum2;
{
    register int i,j;
    register double pixel;
    *psum = *psum2 = 0.0;

    for (i=x; i<x+xsize; ++i)
    for (j=y; j<y+ysize; ++j) {
	   pixel = (double)image[j][i];
       *psum += pixel;
       *psum2 += pixel*pixel;
    }
}

/* ************************************************************** */
/* Take a region of the image at x,y and classify it.             */
/* The four quadrants of the region are ordered from brightest to */
/* least bright average value, then it is rotated into one of the */
/* three cannonical orientations possible with the brightest quad */
/* in the upper left corner.                                      */
/* The routine returns two indices that are class numbers: pfirst */
/* and psecond; the symmetry operation that bring the square into */
/* cannonical position; and the sum and sum^2 of the pixel values */
/* ************************************************************** */
void classify(x, y, xsize, ysize, pfirst, psecond, psym, psum, psum2, type)
int x,y,xsize,ysize,   /* position, size of subimage to be classified */
    *pfirst, *psecond, /* returned first and second class numbers     */
    *psym;             /* returned symmetry operation that brings the */
                       /* subimage to cannonical position.            */
double *psum, *psum2;  /* returned sum and sum^2 of pixel values      */
int type;              /* flag for decimating (for domains) or not    */ 
{

    int order[4], i,j; 
    double a[4],a2[4];
    void (*average_func)();
    
    if (type == 2) average_func = average; else average_func = average1;

    /* get the average values of each quadrant                         */


    (*average_func)(x,y,                 xsize/2,ysize/2,   &a[0], &a2[0]);
    (*average_func)(x,y+ysize/2,         xsize/2,ysize/2,   &a[1], &a2[1]);
    (*average_func)(x+xsize/2,y+ysize/2, xsize/2,ysize/2,   &a[2], &a2[2]);
    (*average_func)(x+xsize/2,y,         xsize/2,ysize/2,   &a[3], &a2[3]);

    *psum = a[0] + a[1] + a[2] + a[3];
    *psum2 =  a2[0] + a2[1] + a2[2] + a2[3];

    for (i=0; i<4; ++i) {
         /* after the sorting below order[i] is the i-th brightest   */
         /* quadrant.                                                */
         order[i] = i; 
         /* convert a2[] to store the variance of each quadrant      */
         a2[i] -= (double)(1<<(2*type))*a[i]*a[i]/(double)(xsize*ysize);
    }

    /* Now order the average value and also in order[],   which will */
    /* then tell us the indices (in a[]) of the brightest to darkest */
    for (i=2; i>=0; --i)
    for (j=0; j<=i; ++j)
        if (a[j]<a[j+1]) {
            swap(order[j], order[j+1],int)
            swap(a[j], a[j+1],double)
    }

    /* because of the way we ordered the a[] the rotation can be */
    /* read right off of order[]. That will make the brightest   */
    /* quadrant be in the upper left corner. But we must still   */ 
    /* decide which cannonical class the image portion belogs    */
    /* to and whether to do a flip or just a rotation. This is   */
    /* the following table summarizes the horrid lines below     */
    /* order      class            do a rotation                 */
    /* 0,2,1,3      0                   0                        */
    /* 0,2,3,1      0                   1                        */
    /* 0,1,2,3      1                   0                        */
    /* 0,3,2,1      1                   1                        */
    /* 0,1,3,2      2                   0                        */
    /* 0,3,1,2      2                   1                        */

    *psym = order[0]; 
    /* rotate the values */
    for (i=0; i<4; ++i)
        order[i] = (order[i] - (*psym) + 4)%4; 

    for (i=0; order[i] != 2; ++i); 
    *pfirst = i-1;
    if (order[3] == 1 || (*pfirst == 2 && order[2] == 1)) *psym += 4;

    /* Now further classify the sub-image by the variance of its    */
    /* quadrants. This give 24 subclasses for each of the 3 classes */
    for (i=0; i<4; ++i) order[i] = i; 

    for (i=2; i>=0; --i)
    for (j=0; j<=i; ++j)
        if (a2[j]<a2[j+1]) {
            swap(order[j], order[j+1],int)
            swap(a2[j], a2[j+1],double)
    }

    /* Now do the symmetry operation */
    for (i=0; i<4; ++i)
        order[i] = (order[i] - (*psym%4) + 4)%4; 
    if (*psym > 3) 
        for (i=0; i<4; ++i)
           if (order[i]%2) order[i] = (2 + order[i])%4;

    /* We want to return a class number from 0 to 23 depending on */
    /* the ordering of the quadrants according to their variance  */
    *psecond = 0;
    for (i=2; i>=0; --i)
    for (j=0; j<=i; ++j)
        if (order[j] > order[j+1]) {
            swap(order[j],order[j+1], int);
            if (order[j] == 0 || order [j+1] == 0) 
                 *psecond += 6;
            else if (order[j] == 1 || order [j+1] == 1) 
                 *psecond += 2;
            else if (order[j] == 2 || order [j+1] == 2) 
                 *psecond += 1;
        }
}

/* ************************************************************ */
/* Compute sum and sum^2 of pixel values in domains for use in  */
/* the rms computation later. Since a domain is compared with   */
/* many ranges, doing this just once saves a lot of computation */
/* This routine also fills a list structure with the domains    */
/* as they are classified and creates the memory for the domain */
/* data in a matrix.                                            */
/* ************************************************************ */
int compute_sums(int hsize, int vsize,byte **theImage)
{
    int i,j,k,l,
         domain_x, 
         domain_y, 
         first_class, 
         second_class,
         domain_size, 
         domain_step_size, 
         size,  
         x_exponent, 
         y_exponent;

    struct classified_domain *node;

    printf("\nComputing domain sums... ");
//    fflush(stdout); 

    /* pre-decimate the image into domimage to avoid having to      */
    /* do repeated averaging of 2x2 pixel groups.                   */
    /* There are 4 ways to decimate the image, depending on the     */
    /* location of the domain, odd or even address.                 */
    for (i=0; i<2; ++i)
    for (j=0; j<2; ++j)
    for (k=i; k<hsize-i; k += 2)
    for (l=j; l<vsize-j; l += 2) 
        domimage[(i<<1)+j][l>>1][k>>1] = 
                     ((double)(theImage[l][k]) + (double)(theImage[l+1][k+1]) +
                     (double)(theImage[l][k+1]) + (double)(theImage[l+1][k]))*0.25;


    /* Allocate memory for the sum and sum^2 of domain pixels        */
    /* We first compute the size of the largest square that fits in  */
    /* the image.                                                    */
    x_exponent = (int)floor(log((double)hsize)/log(2.0));
    y_exponent = (int)floor(log((double)vsize)/log(2.0));
   
    /* exponent is min of x_ and y_ exponent */
    max_exponent = (x_exponent > y_exponent ? y_exponent : x_exponent);

    /* size is the size of the largest square that fits in the image */
    /* It is used to compute the domain and range sizes.             */
    size =  1<<max_exponent; 

    if (max_exponent < max_part) {
      fatal("Reduce maximum number of quadtree partitions.");
      return -1;
      }
    if (max_exponent-2 < max_part) {
      printf("\nWarning: so many quadtree partitions yield absurd ranges.");
      return -1;
      }

    i = max_part - min_part + 1;
    domain.no_h_domains = (int *)malloc(sizeof(int)*i);
    domain.no_v_domains = (int *)malloc(sizeof(int)*i);
    domain.domain_hsize = (int *)malloc(sizeof(int)*i);
    domain.domain_vsize = (int *)malloc(sizeof(int)*i);
    domain.domain_hstep = (int *)malloc(sizeof(int)*i);
    domain.domain_vstep = (int *)malloc(sizeof(int)*i);

    domain.pixel= (struct domain_pixels ***)
              malloc(i*sizeof(struct domain_pixels **));
    if (domain.pixel == NULL) {
    fatal("No memory for domain pixel sums.");
    return -1;
    }

    for (i=0; i <= max_part-min_part; ++i) {
       /* first compute how many domains there are horizontally */
       domain.domain_hsize[i] = size >> (min_part+i-1);
       if (dom_type == 2) 
             domain.domain_hstep[i] = dom_step; 
       else if (dom_type == 1)
             if (dom_step_type == 1) 
               domain.domain_hstep[i] = (size >> (max_part - i-1))*dom_step;
             else 
               domain.domain_hstep[i] = (size >> (max_part - i-1))/dom_step;
       else 
             if (dom_step_type == 1) 
               domain.domain_hstep[i] = domain.domain_hsize[i]*dom_step;
             else 
               domain.domain_hstep[i] = domain.domain_hsize[i]/dom_step;

       domain.no_h_domains[i] = 1+(hsize-domain.domain_hsize[i])/
                                                  domain.domain_hstep[i];
       /* bits_needed[i][0] = ceil(log(domain.no_h_domains[i])/log(2.0));  */

       /* now compute how many domains there are vertically. The sizes  */
       /* are the same for square domains, but not for rectangular ones */
       domain.domain_vsize[i] = size >> (min_part+i-1);
       if (dom_type == 2) 
             domain.domain_vstep[i] = dom_step; 
       else if (dom_type == 1)
             if (dom_step_type == 1) 
               domain.domain_vstep[i] = (size >> (max_part - i-1))*dom_step;
             else
               domain.domain_vstep[i] = (size >> (max_part - i-1))/dom_step;
       else 
             if (dom_step_type == 1) 
               domain.domain_vstep[i] = domain.domain_vsize[i]*dom_step;
             else
               domain.domain_vstep[i] = domain.domain_vsize[i]/dom_step;

       domain.no_v_domains[i] = 1+(vsize-domain.domain_vsize[i])/
                                                  domain.domain_vstep[i];

       /* Now compute the number of bits needed to store the domain data */
       bits_needed[i] = ceil(log((double)domain.no_h_domains[i]*
                                 (double)domain.no_v_domains[i])/log(2.0)); 

       matrix_allocate1(domain.pixel[i], domain.no_h_domains[i],
                     domain.no_v_domains[i], struct domain_pixels) 

    }

    /* allocate and zero the list containing the classified domain data */
    i = max_part - min_part + 1;
    for (first_class = 0; first_class < 3; ++first_class)
    for (second_class = 0; second_class < 24; ++second_class) {
       the_domain[first_class][second_class] = 
                           (struct classified_domain **) 
                           malloc(i*sizeof(struct classified_domain *));
       for (j=0; j<i; ++j)
                    the_domain[first_class][second_class][j] = NULL;
    }

    /* Precompute sum and sum of squares for domains                 */
    /* This part can get faster for overlapping domains if repeated  */
    /* sums are avoided                                              */
    for (i=0; i <= max_part-min_part; ++i) {
      for (j=0,domain_x=0; j<domain.no_h_domains[i]; ++j,
             domain_x+=domain.domain_hstep[i]) 
      for (k=0,domain_y=0; k<domain.no_v_domains[i]; ++k,
             domain_y+=domain.domain_vstep[i]) {
		classify(domain_x, domain_y, 
                 domain.domain_hsize[i], 
                 domain.domain_vsize[i], 
					 &first_class, &second_class,
					 &domain.pixel[i][k][j].sym, 
                     &domain.pixel[i][k][j].sum, 
                     &domain.pixel[i][k][j].sum2, 2);

        /* When the domain data is referenced from the list, we need to */
        /* know where the domain is.. so we have to store the position  */
        domain.pixel[i][k][j].dom_x = j;
        domain.pixel[i][k][j].dom_y = k;
        node = (struct classified_domain *)
                                malloc(sizeof(struct classified_domain));
        
        /* put this domain in the classified list structure */
        node->the = &domain.pixel[i][k][j];
        node->next = the_domain[first_class][second_class][i];
        the_domain[first_class][second_class][i] = node;
	  }
    }

    /* Now we make sure no domain class is actually empty.  */
    for (i=0; i <= max_part-min_part; ++i) 
    for (first_class = 0; first_class < 3; ++first_class)
    for (second_class = 0; second_class < 24; ++second_class) 
       if (the_domain[first_class][second_class][i] == NULL) {
           node = (struct classified_domain *)
                                malloc(sizeof(struct classified_domain));
           node->the = &domain.pixel[i][0][0];
           node->next = NULL;
           the_domain[first_class][second_class][i] = node;
       }

    printf("Done.");
//    fflush(stdout);
    return 0;

}

/* ************************************************************ */
/* pack value using size bits and output into foutf */
/* ************************************************************ */
void pack(size, value, foutf)
int size; long int value;
FILE *foutf;
{
     int i;
     static int ptr = 1, /* how many bits are packed in sum so far */
                sum = 0, /* packed bits */ 
                num_of_packed_bytes = 0; /* total bytes written out */

    /* size == -1 means we are at the end, so write out what is left */
    if (size == -1 && ptr != 1) {
        fputc(sum<<(8-ptr), foutf);
        ++num_of_packed_bytes;
	ptr=1;
	sum=0;
        return;
    }
    
    /* size == -2 means we want to know how many bytes we have written */
    /*if (size == -2) 
            return(num_of_packed_bytes);*/
    
    for (i=0; i<size; ++i, ++ptr, value = value>>1, sum = sum<<1) {
        if (value & 1) sum |= 1;

         if (ptr == 8) {
            fputc(sum,foutf);
            ++num_of_packed_bytes;
            sum=0;
            ptr=0;
        }
     }
}

/* ************************************************************ */
/* Compare a range to a domain and return rms and the quantized */
/* scaling and offset values (pialhpa, pibeta).                 */
/* ************************************************************ */
double compare(atx,aty, xsize, ysize, depth, rsum, rsum2, dom_x,dom_y, 
                                  sym_op, pialpha,pibeta)
int atx, aty, xsize, ysize, depth, dom_x, dom_y, sym_op, *pialpha, *pibeta;
double rsum, rsum2;
{
    int i, j, i1, j1, k,
        domain_x, 
        domain_y;        /* The domain position                */

    double pixel,
           det,          /* determinant of solution */
           dsum,         /* sum of domain values */
           rdsum = 0,    /* sum of range*domain values   */
           dsum2,        /* sum of domain^2 values   */
           w2 = 0,       /* total number of values tested */
           rms = 0,      /* root means square difference */
           alpha,        /* the scale factor */
           beta;         /* The offset */


	
    /* xsize = hsize >> depth; */
    /* ysize = vsize >> depth; */
    w2 = xsize * ysize;

    dsum = domain.pixel[depth-min_part][dom_y][dom_x].sum;
    dsum2 = domain.pixel[depth-min_part][dom_y][dom_x].sum2;
    domain_x = (dom_x * domain.domain_hstep[depth-min_part]);
    domain_y = (dom_y * domain.domain_vstep[depth-min_part]);
    k = ((domain_x%2)<<1) + domain_y%2;
    domain_x >>= 1;
    domain_y >>= 1;

    /* The main statement in this routine is a switch statement which */
    /* scans through the domain and range to compare them. The loop   */
    /* center is the same so we #define it for easy modification      */
#define COMPUTE_LOOP              {                                 \
        pixel = domimage[k][j1][i1];                                \
        rdsum += image[j][i]*pixel;                                 \
        }
    
     switch(sym_op) {
         case 0: for (i=atx, i1 = domain_x; i<atx+xsize; ++i, ++i1)
                 for (j=aty, j1 = domain_y; j<aty+ysize; ++j, ++j1) 
                     COMPUTE_LOOP
                 break;
         case 1: for (j=aty, i1 = domain_x; j<aty+ysize; ++j, ++i1)
                 for (i=atx+xsize-1, j1 = domain_y; i>=atx; --i, ++j1) 
                     COMPUTE_LOOP
                 break;
         case 2: for (i=atx+xsize-1, i1 = domain_x; i>=atx; --i, ++i1)
                 for (j=aty+ysize-1, j1 = domain_y; j>=aty; --j, ++j1) 
                     COMPUTE_LOOP
                 break;
         case 3: for (j=aty+ysize-1, i1 = domain_x; j>=aty; --j, ++i1)
                 for (i=atx, j1 = domain_y; i<atx+xsize; ++i, ++j1) 
                     COMPUTE_LOOP
                 break;
         case 4: for (j=aty, i1 = domain_x; j<aty+ysize; ++j, ++i1)
                 for (i=atx, j1 = domain_y; i<atx+xsize; ++i, ++j1) 
                     COMPUTE_LOOP
                 break;
         case 5: for (i=atx, i1 = domain_x; i<atx+xsize; ++i, ++i1)
                 for (j=aty+ysize-1, j1 = domain_y; j>=aty; --j, ++j1) 
                     COMPUTE_LOOP
                 break;
         case 6: for (j=aty+ysize-1, i1 = domain_x; j>=aty; --j, ++i1)
                 for (i=atx+xsize-1, j1 = domain_y; i>=atx; --i, ++j1) 
                     COMPUTE_LOOP
                 break;
         case 7: for (i=atx+xsize-1, i1 = domain_x; i>=atx; --i, ++i1)
                 for (j=aty, j1 = domain_y; j<aty+ysize; ++j, ++j1) 
                     COMPUTE_LOOP
                 break;
     }
    
     det = (xsize*ysize)*dsum2 - dsum*dsum;
    
     if (det == 0.0) 
         alpha = 0.0; 
      else 
         alpha = (w2*rdsum - rsum*dsum)/det;
        
     if  (only_positive && alpha < 0.0) alpha = 0.0;
     *pialpha = 0.5 + (alpha + max_scale)/(2.0*max_scale)*(1<<s_bits);
     if (*pialpha < 0) *pialpha = 0;
     if (*pialpha >= 1<<s_bits) *pialpha = (1<<s_bits)-1;

     /* Now recompute alpha back */
     alpha = (double)*pialpha/(double)(1<<s_bits)*(2.0*max_scale)-max_scale;
        
     /* compute the offset */
     beta = (rsum - alpha*dsum)/w2;

     /* Convert beta to an integer */
     /* we use the sign information of alpha to pack efficiently */
     if (alpha > 0.0)  beta += alpha*GREY_LEVELS;
     *pibeta = 0.5 + beta/
             ((1.0+fabs(alpha))*GREY_LEVELS)*((1<<o_bits)-1);
     if (*pibeta< 0) *pibeta = 0;
     if (*pibeta>= 1<<o_bits) *pibeta = (1<<o_bits)-1;

     /* Recompute beta from the integer */
     beta = (double)*pibeta/(double)((1<<o_bits)-1)*
               ((1.0+fabs(alpha))*GREY_LEVELS);
     if (alpha > 0.0) beta  -= alpha*GREY_LEVELS;

     /* Compute the rms based on the quantized alpha and beta! */
     rms= sqrt((rsum2 + alpha*(alpha*dsum2 - 2.0*rdsum + 2.0*beta*dsum) +
                 beta*(beta*w2 - 2.0*rsum))/w2);
    
     return(rms);
}

/* ************************************************************ */
/* Recursively partition an image, computing the best transfoms */
/* ************************************************************ */
void quadtree(atx,aty,xsize,ysize,tol,depth)
int atx, aty, xsize, ysize, depth; 
double tol;  /* the tolerance fit  */
{
    int i,
        sym_op,                   /* A symmetry operation of the square */
        ialpha,                   /* Intgerized scalling factor         */
        ibeta,                    /* Intgerized offset                  */
        best_ialpha,              /* best ialpha found                  */
        best_ibeta,
        best_sym_op,
        best_domain_x,
        best_domain_y, 
        first_class, 
        the_first_class, 
        first_class_start,        /* loop beginning and ending values   */
        first_class_end, 
        second_class[2],
        the_second_class, 
        second_class_start,       /* loop beginning and ending values   */
        second_class_end, 
        range_sym_op[2],          /* the operations to bring square to  */
        domain_sym_op;            /* cannonical position.               */

    struct classified_domain *node;  /* var for domains we scan through */

    double rms, best_rms,          /* rms value and min rms found so far */
           sum=0, sum2=0;          /* sum and sum^2 of range pixels      */


    /* keep breaking it down until we are small enough */
    if (depth < min_part) {
         quadtree(atx,aty, xsize/2, ysize/2, tol,depth+1);
         quadtree(atx+xsize/2,aty, xsize/2, ysize/2,tol,depth+1);
         quadtree(atx,aty+ysize/2, xsize/2, ysize/2,tol,depth+1);
         quadtree(atx+xsize/2,aty+ysize/2, xsize/2, ysize/2,tol,depth+1);
         return;
    }

    /* now search for the best domain-range match and write it out */
    best_rms = 10000000000.0;      /* just a big number */

    classify(atx, aty, xsize,ysize, 
              &the_first_class, &the_second_class, 
              &range_sym_op[0], &sum, &sum2, 1);


    /* sort out how much to search based on -f and -F input flags */
    if (fullclass_search) {
         first_class_start = 0; 
         first_class_end = 3;
    } else {
         first_class_start = the_first_class; 
         first_class_end = the_first_class+1;
    } 

    if (subclass_search) {
         second_class_start = 0; 
         second_class_end = 24;
    } else {
         second_class_start = the_second_class; 
         second_class_end = the_second_class+1;
    } 

    /* these for loops vary according to the optimization flags we set */
    /* for subclass_search and fullclass_search==1, we search all the  */
    /* domains (except not all rotations).                             */
    for (first_class = first_class_start; 
         first_class < first_class_end; ++first_class)
    for (second_class[0] = second_class_start; 
         second_class[0] < second_class_end; ++second_class[0]) {

       /* We must check each domain twice. Once for positive scaling,  */
       /* once for negative scaling. Each has its own class and sym_op */
       if (!only_positive) {
          second_class[1] = 
	         class_transform[(first_class == 2 ? 1 : 0)][second_class[0]];
          range_sym_op[1] = 
             rot_transform[(the_first_class == 2 ? 1 : 0)][range_sym_op[0]];
       } 

       /* only_positive is 0 or 1, so we may or not scan                */
       for (i=0; i<(2-only_positive); ++i) 
       for (node = the_domain[first_class][second_class[i]][depth-min_part]; 
           node != NULL; 
           node = node->next) {
           domain_sym_op = node->the->sym;
           /* The following if statement figures out how to transform  */
           /* the domain onto the range, given that we know how to get */
           /* each into cannonical position.                           */
           if (((domain_sym_op>3 ? 4: 0) + (range_sym_op[i]>3 ? 4: 0))%8 == 0)
             sym_op = (4 + domain_sym_op%4 - range_sym_op[i]%4)%4;
           else 
             sym_op = (4 + (domain_sym_op%4 + 3*(4-range_sym_op[i]%4))%4)%8;
            
           rms = compare(atx,aty, xsize, ysize,  depth, sum,sum2, 
                                  node->the->dom_x, 
                                  node->the->dom_y, 
                                  sym_op, &ialpha,&ibeta); 
    
           if (rms < best_rms) {
                   best_ialpha = ialpha;
                   best_ibeta = ibeta;
                   best_rms = rms;
                   best_sym_op = sym_op;
                   best_domain_x = node->the->dom_x;
                   best_domain_y = node->the->dom_y;
           }
       }
    }
        
    if (best_rms > tol && depth < max_part) {
       /* We didn't find a good enough fit so quadtree down */
       pack(1,(long)1,output);  /* This bit means we quadtree'd down */
       quadtree(atx,aty, xsize/2, ysize/2, tol,depth+1);
       quadtree(atx+xsize/2,aty, xsize/2, ysize/2, tol,depth+1);
       quadtree(atx,aty+ysize/2, xsize/2, ysize/2, tol,depth+1);
       quadtree(atx+xsize/2,aty+ysize/2, xsize/2, ysize/2, tol,depth+1);
    } else {
       /* The fit was good enough or we just can't get smaller ranges */
       /* So write out the data */
       if (depth < max_part)          /* if we are not at the smallest range */
               pack(1,(long)0,output);/* then we must tell the decoder we    */
                                      /* stopped quadtreeing                 */
       pack(s_bits, (long)best_ialpha, output);
       pack(o_bits, (long)best_ibeta, output);
       /* When the scaling is zero, there is no need to store the domain */
       if (best_ialpha != zero_ialpha) {
          pack(3, (long)best_sym_op, output);
          pack(bits_needed[depth-min_part], (long)(best_domain_y*
            domain.no_h_domains[depth-min_part]+best_domain_x), output);
      }
     }
}

/* ************************************************************* */
/* Recursively partition an image, finding the largest contained */
/* square and call the quadtree routine the encode that square.  */
/* This enables us to encode rectangular image easily.           */
/* ************************************************************* */
static partition_image(atx, aty, hsize,vsize, tol)
int atx, aty, hsize,vsize;
double tol;
{
   int x_exponent,    /* the largest power of 2 image size that fits */
       y_exponent,    /* horizontally or vertically the rectangle.   */
       exponent,      /* The actual size of image that's encoded.    */
       size, 
       depth; 
   
   x_exponent = (int)floor(log((double)hsize)/log(2.0));
   y_exponent = (int)floor(log((double)vsize)/log(2.0));
   
   /* exponent is min of x_ and y_ exponent */
   exponent = (x_exponent > y_exponent ? y_exponent : x_exponent);
   size = 1<<exponent; 
   depth = max_exponent - exponent;
   quadtree(atx,aty,size,size,tol,depth);
   if (size != hsize) 
      partition_image(atx+size, aty, hsize-size,vsize, tol);

   if (size != vsize) 
      partition_image(atx, aty+size, size,vsize-size, tol);
}        
  
/* fatal is for when there is a fatal error... print a message and exit */
void fatal(s)
char *s;
{
     printf("%s\n",s);
}

int convert_pow_two(int number) {
   int count,temp;

      for(count=1; count<15; count++) {
	    temp=pow(2,count);
	    if(number <= temp) {
	    return temp;
	    }
      }
	return (1<<16);
}
