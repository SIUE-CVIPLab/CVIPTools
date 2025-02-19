/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: fracdec.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Sun Feb 15 22:45:05 CST 1998
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
** $Log: fracdec.c,v $
** Revision 1.7  2001/04/09 14:01:03  ycheng
** fixed bugs so that it works under Linux.
**
** Revision 1.6  1998/04/29 20:28:23  smakam
** *** empty log message ***
**
** Revision 1.5  1998/04/17 19:17:02  smakam
** removed some warnings
**
** Revision 1.4  1998/04/17 18:43:58  smakam
** removed unwanted statements (comments)
**
** Revision 1.3  1998/03/30 19:13:33  smakam
** checked the bombing of the function
**
** Revision 1.2  1998/03/14 02:28:50  smakam
** got the first draft of fractal working
**
** Revision 1.1  1998/02/18 05:45:56  cvip
** Initial revision
**
*
****************************************************************************/
/**************************************************************************/
/* Decode an image encoded with a quadtree partition based fractal scheme */
/*                                                                        */
/*       Copyright 1993,1994 Yuval Fisher. All rights reserved.           */
/*	Modified by Makam Sreenivas	Spring 1998			  */
/*                                                                        */
/* Version 0.04 3/14/94                                                   */
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

/* The following belong in a encdec.h file, but nevermind...              */
/* -----------------------------------------------------------------------*/
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
#include "fractal.h"

static partition_image(int atx, int aty, int hsize,int vsize );

#define DEBUG 0
#define GREY_LEVELS 255

#define IMAGE_TYPE unsigned char /* may be different in some applications */

/* The following #define allocates an hsize x vsize  matrix of type type */
#define matrix_allocate1(matrix, hsize,vsize, TYPE) {\
    TYPE *imptr; \
    int _i; \
    matrix = (TYPE **)malloc(vsize*sizeof(TYPE *));\
    imptr = (TYPE*)malloc((long)hsize*(long)vsize*sizeof(TYPE));\
    if (imptr == NULL) \
        fatal("\nNo memory in matrix allocate."); \
    for (_i = 0; _i<vsize; ++_i, imptr += hsize) \
        matrix[_i] = imptr; \
 }

#define bound(a)   ((a) < 0.0 ? 0 : ((a)>255.0? 255 : a))

/* various function declarations to keep compiler warnings away           */
static void fatal();

/* ---------------------------------------------------------------------- */

IMAGE_TYPE **image,*imptr,**image1; 
                             /* The input image data and a dummy         */ 

static double max_scale = 1.0;      /* maximum allowable grey level scale factor */

static int    s_bits = 5,           /* number of bits used to store scale factor */
       o_bits = 7,           /* number of bits used to store offset       */
       hsize = -1,           /* The horizontal size of the input image    */
       vsize = -1,           /* The vertical size                         */
       scaledhsize,          /* hsize*scalefactor                         */
       scaledvsize,          /* vsize*scalefactor                         */
       bands,band,
       size,                 /* largest square image that fits in image   */
       min_part,         /* min and max _part determine a range of    */
       max_part,         /* Range sizes from hsize>>min to hsize>>max */
       dom_step = 4,         /* Density of domains relative to size       */
       dom_step_type = 0,    /* Flag for dom_step a multiplier or divisor */
       dom_type = 0,         /* Method of generating domain pool 0,1,2..  */
       post_process = 1,     /* Flag for postprocessing.                  */
       num_iterations= 10,   /* Number of decoding iterations used.       */
       *no_h_domains,        /* Number of horizontal domains.             */
       *domain_hstep,        /* Domain density step size.                 */
       *domain_vstep,        /* Domain density step size.                 */
       *bits_needed,         /* Number of bits to encode domain position. */
       zero_ialpha,          /* the const ialpha when alpha = 0           */
       output_partition=0,   /* A flag for outputing the partition        */
       max_exponent;         /* The max power of 2 side of square image   */
                             /* that fits in our input image.             */

struct transformation_node {
       int rx,ry,            /* The range position and size in a trans.   */
              xsize, ysize,  
              rrx,rry,
              dx,dy;         /* The domain position.                      */
       int sym_op;           /* The symmetry operation used in the trans. */
       int depth;            /* The depth in the quadtree partition.      */
       double scale, offset; /* scalling and offset values.               */
       struct transformation_node *next;       /* The next trans. in list */
} *transformations, *trans[3],*trans1; 

FILE *output,*other_input,*input1; 


/* fatal is for when there is a fatal error... print a message and exit */
void fatal(s)
char *s;
{
     printf("\n%s\n",s);
     exit(-1);
}

/* ************************************************************ */
/* unpack value using size bits read from fin.                  */
/* ************************************************************ */
long unpack(size, fin)
int size;
FILE *fin;
{
    int i;
    int value = 0;
    static int ptr = 1; /* how many bits are packed in sum so far */
    static int sum; 


    /* size == -2 means we initialize things */
    if (size == -2) {
        sum = fgetc(fin);
        sum <<= 1;
	ptr=1;
        return((long)0);
    }

    /* size == -1 means we want to peek at the next bit without */
    /* advancing the pointer */
    if (size == -1)
        return((long)((sum&256)>>8));

     for (i=0; i<size; ++i, ++ptr,  sum <<= 1) {
        if (sum & 256) value |= 1<<i;

         if (ptr == 8) {
            sum = fgetc(fin);
            ptr=0;
        }
     }
    return((long)value);
}

Image *frac_decompress(char *filename) {
	FILE *file_in;
	Image *decodeImage;
 	if((file_in = fopen(filename, "rb")) == '\0')
        {
	      printf("\nError opening the file\n");
	      return NULL;
        }
	decodeImage = frac_decompression(file_in);
        fclose(file_in);
	return decodeImage;
}


Image *frac_decompression(FILE *input)
{
    /* Defaults are set initially */
    double         scalefactor = 1.0;           /* Scale factor for output */
    char           inputfilename[200];
    char           outputfilename[200];
    char           other_input_file[200];
    int            i,j, x_exponent, y_exponent;
    int            domain_size, no_domains;
    char  	   aa,bb,cc;
    Image 	   *decodeImage;
    byte 	   **image_arr;
    int a,b,c;

    input1=input; 
    inputfilename[0] = 1;    /* We initially set the input to this and */
    outputfilename[0] = 1;   /* then check if the input/output names   */
    other_input_file[0] = 1; /* have been set below.                   */

	/* checking for the top 3 characters in the file */
    aa=fgetc(input1);
    bb=fgetc(input1);
    cc=fgetc(input1);
    if(aa!='f' || bb!='r' || cc!= 'a') {
	printf("\n\tInvalid file format\n");
	exit(0);
    }

    unpack(-2,input1); /* initialize the unpacking routine */
	/* read the header data from the input file. This should probably */
    /* be put into one read which reads a structure with the info     */
    min_part = (int)unpack(4,input1);
    max_part = (int)unpack(4,input1);
    dom_step = (int)unpack(4,input1);
    dom_step_type = (int)unpack(1,input1);
    dom_type = (int)unpack(2,input1);
    s_bits = (int)unpack(4,input1);
    o_bits = (int)unpack(4,input1);
    hsize=(int)unpack(12,input1);
    vsize=(int)unpack(12,input1);
    bands=(int)unpack(4,input1);
    if(bands==1)
    	decodeImage=(Image *)new_Image(PGM,GRAY_SCALE,bands,hsize,vsize,CVIP_BYTE,REAL);
    else
    	decodeImage=(Image *)new_Image(PPM,RGB,bands,hsize,vsize,CVIP_BYTE,REAL);

    transformations = (struct transformation_node *)
		      malloc(sizeof(struct transformation_node )*bands);
    for(band=0;band<bands;band++) {
    image_arr=getData_Image(decodeImage,band);

    /* we now compute size */
    x_exponent = (int)floor(log((double)hsize)/log(2.0));
    y_exponent = (int)floor(log((double)vsize)/log(2.0));
   
    /* exponent is min of x_ and y_ exponent */
    max_exponent = (x_exponent > y_exponent ? y_exponent : x_exponent);
    /* size is the size of the largest square that fits in the image */
    /* It is used to compute the domain and range sizes.             */
    size =  1<<max_exponent; 

    /* This is the quantized value of zero scaling */
    zero_ialpha = 0.5 + (max_scale)/(2.0*max_scale)*(1<<s_bits);

    /* allocate memory for the output image. Allocating one chunck saves  */
    /* work and time later.                                              */
	scaledhsize = (int)(scalefactor*hsize);
	scaledvsize = (int)(scalefactor*vsize);
    matrix_allocate1(image, scaledhsize,scaledvsize, IMAGE_TYPE);
    matrix_allocate1(image1, scaledhsize, scaledvsize, IMAGE_TYPE);

    if (other_input_file[0] != 1) {
        other_input = fopen(other_input_file, "r");
        i = fread(image[0], sizeof(IMAGE_TYPE), 
				scaledhsize*scaledvsize, other_input);
        if (i < scaledhsize*scaledvsize) 
           fatal("Couldn't read input... not enough data.");
        else
            printf("\n%d pixels read from %s.\n", i,other_input_file);
        fclose(other_input);
    }
          
    /* since max_ and min_ part are variable, these must be allocated */
    i = max_part - min_part + 1;
    bits_needed = (int *)malloc(sizeof(int)*i);
    no_h_domains = (int *)malloc(sizeof(int)*i);
    domain_hstep = (int *)malloc(sizeof(int)*i);
    domain_vstep = (int *)malloc(sizeof(int)*i);
    
    /* compute bits needed to read each domain type */
    for (i=0; i <= max_part-min_part; ++i) {
       /* first compute how many domains there are horizontally */
       domain_size = size >> (min_part+i-1);
       if (dom_type == 2) 
             domain_hstep[i] = dom_step; 
       else if (dom_type == 1)
             if (dom_step_type ==1)
                domain_hstep[i] = (size >> (max_part - i-1))*dom_step;
             else 
                domain_hstep[i] = (size >> (max_part - i-1))/dom_step;
       else 
             if (dom_step_type ==1)
                domain_hstep[i] = domain_size*dom_step;
             else 
                domain_hstep[i] = domain_size/dom_step;

       no_h_domains[i] = 1+(hsize-domain_size)/domain_hstep[i];
       /* bits_needed[i][0] = ceil(log(no_domains)/log(2));  */

       /* now compute how many domains there are vertically */
       if (dom_type == 2) 
             domain_vstep[i] = dom_step; 
       else if (dom_type == 1)
             if (dom_step_type ==1)
             domain_vstep[i] = (size >> (max_part - i-1))*dom_step;
             else 
             domain_vstep[i] = (size >> (max_part - i-1))/dom_step;
       else 
             if (dom_step_type ==1)
                domain_vstep[i] = domain_size*dom_step;
             else 
                domain_vstep[i] = domain_size/dom_step;

       no_domains = 1+(vsize-domain_size)/domain_vstep[i];
       bits_needed[i] = ceil(log((double)no_domains*(double)no_h_domains[i])/
                           log(2.0)); 
     }

    /* Read in the transformation data */
    trans[band]=&(transformations[band]);
    printf("\nReading transformations.....");
//    fflush(stdout);
    partition_image(0, 0, hsize,vsize );
    printf("Done.");
//    fflush(stdout);
   
	if (scalefactor != 1.0) {
		printf("\nScaling image to %d x %d.", scaledhsize,scaledvsize);
		scale_transformations(scalefactor); 
	}
 
    /* when we output the partition, we just read the transformations */
    /* in and write them to the outputfile                            */ 
    if (output_partition) {
          fprintf(output,"\n%d %d\n %d %d\n%d %d\n\n", 
                  0, 0, scaledhsize, 0, scaledhsize, scaledvsize);
          printf("\nOutputed partition data in %s\n",outputfilename);
          fclose(output);
          return;
    }

    for (i=0; i<num_iterations; ++i) 
      apply_transformations();

    if (post_process) 	
      smooth_image();
      for(i=0;i<hsize;i++)
      for(j=0;j<vsize;j++)
	 image_arr[i][j]=image[i][j]; 
	free(image[0]);
	free(image1[0]);
	free(bits_needed);
	free(no_h_domains);
	free(domain_hstep);
	free(domain_vstep);
	}
	/* XXX
	There would be memory leakage here for sure but the functions works so far
	for(band=0;band<bands;band++)
	{
		trans[band]=&(transformations[band]);
		while(trans[band]->next != NULL)
		{
			trans1=trans[band];
			trans[band]=trans[band]->next;
	        free(trans1);
		}
		free(trans[band]);
	 }
	 */

    decodeImage->image_format = FRA;
    return decodeImage;
}

/* ************************************************************ */
/* Read in the transformation data from *input.                 */
/* This is a recursive routine whose recursion tree follows the */
/* recursion done by the encoding program.                      */
/* ************************************************************ */
read_transformations(atx,aty,xsize,ysize,depth)
int atx,aty,xsize,ysize,depth; 
{
    /* Having all these locals in a recursive procedure is hard on the  */
    /* stack.. but it is more readable.                                 */
    int i,j,
        sym_op,                   /* A symmetry operation of the square */
        ialpha,                   /* Intgerized scalling factor         */
	count=0,
        ibeta;                    /* Intgerized offset                  */

    long domain_ref; 

    double alpha, beta;
    /* keep breaking it down until we are small enough */
    if (depth < min_part) {
         read_transformations(atx,aty, xsize/2, ysize/2, depth+1);
         read_transformations(atx+xsize/2,aty, xsize/2, ysize/2, depth+1);
         read_transformations(atx,aty+ysize/2,xsize/2, ysize/2,  depth+1);
         read_transformations(atx+xsize/2,aty+ysize/2,xsize/2,ysize/2,depth+1);
         return;
    }

    if (depth < max_part && unpack(1,input1)) {
         /* A 1 means we subdivided.. so quadtree */
         read_transformations(atx,aty, xsize/2, ysize/2, depth+1);
         read_transformations(atx+xsize/2,aty, xsize/2, ysize/2, depth+1);
         read_transformations(atx,aty+ysize/2, xsize/2, ysize/2, depth+1);
         read_transformations(atx+xsize/2,aty+ysize/2,xsize/2,ysize/2,depth+1);
    } else {  
         /* we have a transformation to read */
         trans[band]->next = (struct transformation_node *)
                  malloc(sizeof(struct transformation_node ));
         trans[band] = trans[band]->next;
	 count++;
         ialpha = (int)unpack(s_bits,  input1);
         ibeta = (int)unpack(o_bits,  input1);
         alpha = (double)ialpha/(double)(1<<s_bits)*(2.0*max_scale)-max_scale;

         beta = (double)ibeta/(double)((1<<o_bits)-1)*
               ((1.0+fabs(alpha))*GREY_LEVELS);
         if (alpha > 0.0) beta -= alpha*GREY_LEVELS;

         trans[band]->scale = alpha;
         trans[band]->offset = beta;
         if (ialpha != zero_ialpha) {
            trans[band]-> sym_op = (int)unpack(3, input1);
            domain_ref = unpack(bits_needed[depth-min_part], input1);
            trans[band]->dx = (double)(domain_ref % no_h_domains[depth-min_part])
                                              * domain_hstep[depth-min_part];
            trans[band]->dy = (double)(domain_ref / no_h_domains[depth-min_part])
                                              * domain_vstep[depth-min_part];
         } else {
            trans[band]-> sym_op = 0;
            trans[band]-> dx  = 0;
            trans[band]-> dy = 0;
         }
         trans[band]->rx = atx;
         trans[band]->ry = aty;
         trans[band]->depth = depth;
        
         trans[band]->rrx = atx + xsize;
         trans[band]->rry = aty + ysize;

         if (output_partition) 
                fprintf(output,"\n%d %d\n %d %d\n%d %d\n\n", 
                  atx,       vsize-aty-ysize, 
                  atx,       vsize-aty, 
                  atx+xsize, vsize-aty);
  
    }
    trans[band]->next= NULL;
}
     
/* ************************************************************ */
/* Apply the transformations once to an initially black image.  */
/* ************************************************************ */
int apply_transformations()
{
    IMAGE_TYPE **tempimage;
	int	i,j,i1,j1,count=0;
    double pixel;

    /*trans = trans2;*/
    trans[band]=&(transformations[band]);
    while (trans[band]->next != NULL) {
        trans[band] = trans[band]->next;
		++count;
/* Since the inner loop is the same in each case of the switch below */
/* we just define it once for easy modification.                     */
#define COMPUTE_LOOP              {                                  \
        pixel = (image[j1][i1]+image[j1][i1+1]+image[j1+1][i1]+      \
                image[j1+1][i1+1])/4.0;                              \
        image1[j][i] = bound(0.5 + trans[band]->scale*pixel+trans[band]->offset);\
        }

        switch(trans[band]->sym_op) {
           case 0: for (i=trans[band]->rx, i1 = trans[band]->dx; 
                         i<trans[band]->rrx; ++i, i1 += 2)
                   for (j=trans[band]->ry, j1 = trans[band]->dy; 
                         j<trans[band]->rry; ++j, j1 += 2)
                       COMPUTE_LOOP
                   break;
           case 1: for (j=trans[band]->ry, i1 = trans[band]->dx;
                           j<trans[band]->rry; ++j, i1 += 2)
                   for (i=trans[band]->rrx-1,
                           j1 = trans[band]->dy; i>=(int)trans[band]->rx; --i, j1 += 2) 
                       COMPUTE_LOOP
                   break;
           case 2: for (i=trans[band]->rrx-1, 
                          i1 = trans[band]->dx; i>=(int)trans[band]->rx; --i, i1 += 2)
                   for (j=trans[band]->rry-1,
                           j1 = trans[band]->dy; j>=(int)trans[band]->ry; --j, j1 += 2) 
                       COMPUTE_LOOP
                   break;
           case 3: for (j=trans[band]->rry-1,
                           i1 = trans[band]->dx; j>=(int)trans[band]->ry; --j, i1 += 2)
                   for (i=trans[band]->rx, j1 = trans[band]->dy;
                           i<trans[band]->rrx; ++i, j1 += 2) 
                       COMPUTE_LOOP
                   break;
           case 4: for (j=trans[band]->ry, i1 = trans[band]->dx;
                           j<trans[band]->rry; ++j, i1 += 2)
                   for (i=trans[band]->rx, j1 = trans[band]->dy;
                           i<trans[band]->rrx; ++i, j1 += 2) 
                       COMPUTE_LOOP
                   break;
           case 5: for (i=trans[band]->rx, i1 = trans[band]->dx;
                           i<trans[band]->rrx; ++i, i1 += 2)
                   for (j=trans[band]->rry-1,
                           j1 = trans[band]->dy; j>=(int)trans[band]->ry; --j, j1 += 2) 
                       COMPUTE_LOOP
                   break;
           case 6: for (j=trans[band]->rry-1,
                           i1 = trans[band]->dx; j>=(int)trans[band]->ry; --j, i1 += 2)
                   for (i=trans[band]->rrx-1,
                           j1 = trans[band]->dy; i>=(int)trans[band]->rx; --i, j1 += 2) 
                       COMPUTE_LOOP
                   break;
           case 7: for (i=trans[band]->rrx-1, 
                          i1 = trans[band]->dx; i>=(int)trans[band]->rx; --i, i1 += 2)
                   for (j=trans[band]->ry, j1 = trans[band]->dy; 
                          j<trans[band]->rry; ++j, j1 += 2) 
                       COMPUTE_LOOP
                   break;
        }  
  
    }
    tempimage = image;
    image = image1;
    image1 = tempimage;
    printf("\n%d transformations applied.",count);
    return 0;

}

/*        This should really be done when they are read in.     */
/* ************************************************************ */
int scale_transformations(scalefactor)
double scalefactor;
{
    /*trans = trans2;*/
    trans[band]=&(transformations[band]);
    while (trans[band] ->next != NULL) {
        trans[band]  = trans[band]->next;

		trans[band] ->rrx *= scalefactor;
		trans[band] ->rry *= scalefactor;
		trans[band] ->rx *= scalefactor;
		trans[band] ->ry *= scalefactor;
		trans[band] ->dx *= scalefactor;
		trans[band] ->dy *= scalefactor;
    }
    return 0;
}

/* ************************************************************* */
/* Recursively partition an image, finding the largest contained */
/* square and call read_transformations .                        */
/* ************************************************************* */
static partition_image(atx, aty, hsize,vsize )
int atx, aty, hsize,vsize;
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

   read_transformations(atx,aty,size,size,depth);

   if (size != hsize) 
      partition_image(atx+size, aty, hsize-size,vsize );

   if (size != vsize) 
      partition_image(atx, aty+size, size,vsize-size );
}        
  
/* ************************************************************* */
/* Scan the image and average the transformation boundaries.     */
/* ************************************************************* */
smooth_image()
{
    IMAGE_TYPE pixel1, pixel2;
	int i,j;
	int w1,w2;

	printf("\nPostprocessing Image.\n");
    /*trans = trans2;*/
    trans[band]=&(transformations[band]);
    while (trans[band]->next != NULL) {
        trans[band] = trans[band]->next;
		if (trans[band]->rx == 0 || trans[band]->ry == 0) 
            continue;
		
		if (trans[band]->depth == max_part) {
			w1 = 5;
			w2 = 1;
		} else {
			w1 = 2;
			w2 = 1;
		}

        for (i=trans[band]->rx; i<trans[band]->rrx; ++i) {
             pixel1 = image[(int)trans[band]->ry][i];
             pixel2 = image[(int)trans[band]->ry-1][i];
             image[(int)trans[band]->ry][i] = (w1*pixel1 + w2*pixel2)/(w1+w2);
             image[(int)trans[band]->ry-1][i] = (w2*pixel1 + w1*pixel2)/(w1+w2);
        }

        for (j=trans[band]->ry; j<trans[band]->rry; ++j) {
             pixel1 = image[j][(int)trans[band]->rx];
             pixel2 = image[j][(int)trans[band]->rx-1];
             image[j][(int)trans[band]->rx] = (w1*pixel1 + w2*pixel2)/(w1+w2);
             image[j][(int)trans[band]->rx-1] = (w2*pixel1 + w1*pixel2)/(w1+w2);
        }
    }
}
