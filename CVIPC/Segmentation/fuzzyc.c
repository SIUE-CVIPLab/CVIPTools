/***************************************************************************
* ======================================================================
* Computer Vision/ImageFuzzy Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: fuzzyc.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Tue Jun  1 12:02:11 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Gregory Hance
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1993 SIUE - by Gregory Hance.
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
** $Log: fuzzyc.c,v $
** 
**Revision1.11  2006/07/29   Wenjun Bian
**  add code: free(in.matrix); in order to avoid memroy leak
**
** Revision 1.10  2001/10/15 02:42:17  ycheng
** Log message of 'Revision 1.9' is not correct because still this C code could only handle
** 3 bands. It can't handle 1 bands image so that you must assemble the 1 band image into
** 3 bands image to use this method.
**
** Revision 1.9  2001/10/15 01:51:31  ycheng
** changed the code in read_ppm & write_ppm so that now the code could handle 1 band image as well nds image.
**
** Revision 1.8  1997/06/16 21:36:37  yawei
** removed bzero/bcopy definition
**
** Revision 1.7  1997/01/15 17:08:42  yawei
** Global Change:  IMAGE ==> Image
**
 * Revision 1.6  1996/12/24  15:40:48  yawei
 * changed include file to "fuzzyc.h"
 *
 * Revision 1.5  1996/12/23  18:32:29  yawei
 * filename changed:
 *   fuzzycMeans.c ==> fuzzyc.c
 *
 * Revision 1.4  1996/12/23  00:39:55  yawei
 * Changed (const Image) to (Image) in the setup function
 *
 * Revision 1.3  1996/12/22  23:12:15  yawei
 * Chnaged so fuzzyc_segment_setup won't duplicate the input image
 * structure
 *
 * Revision 1.2  1996/12/20  22:23:33  yawei
 * Changed
 *   fuzzycMeans_Image ==> fuzzyc_segment
 *
 * Revision 1.1  1994/10/30  17:58:22  hanceg
 * CVIPtools1.0 source file - G. Hance
 *
 * Revision 1.1  1993/06/02  04:48:32  hanceg
 * Initial revision
 *
*
****************************************************************************/
#include "CVIPtoolkit.h"
#include "CVIPdef.h"
#include "fuzzyc.h"
 
/*
** dynamic memory allocation stuff
*/
static ImageFuzzy *create_image(int width, int	height, int colors);
static Pixel **create_matrix(int width, int height);
static int free_image(ImageFuzzy *im);
static int free_matrix(Pixel **m);
static int read_ppm(Image *src, ImageFuzzy *im);
static int write_ppm(ImageFuzzy *im, Image *src);

/*
** math stuff
*/
float 	tore = 5.0;
int   	t_len;	/* 49.0 */

static int convolution(Histogram *ser1, double	*ser2, int len1, int len2);
static double *gausian(float tore, float len);

/*
** histogram stuff
*/
static int count_his(ImageFuzzy *in, Histogram	*his);
static void max_his(Histogram *h, int colors);


/*
** segmentation stuff
*/
int   vn[3];     /* number of valleys in each space */
int   pn[3];     /* number of peaks in each space */
int   max_peak;   /* Total number of peaks */
int   not_count;

double peak[64][3];      	/* at most 64 peaks in one color dimension */
double valley[64][3];
Peak   *pk;
Class  *klass;
float  safe = 0.1;     		/* 10% safety margin */

Pixel  colors[27] = {
	{0,0,0}, {250,0,0}, {0,250,0}, {0,0,250}, 
        {250,250,0}, {250,0,250}, {0,250,250},
	{125,0,0},   {0,125,0},   {0,0,125}, 
	{125,125,0}, {125,0,125}, {0,125,125}, 
	{250,125,0}, {250,0,125}, {125,250,0}, 
	{0,250,125}, {125,0,250}, {0,125,250},
	{250,250,125}, {250,125,250}, {125,250,250}, 
	{250,125,125}, {125,250,125}, {125,125,250}, 
	{250,250,250}, {125,125,125}
};

static byte class_index1(byte c, int k);
static int class_index(Pixel p);
static void coarse_seg(void);
static double member_ship(Pixel p, Class k);
static void fine_seg(void);
static void find_cluster(void);


/*
** beginning of general global declarations
*/

const char *fn = "fuzzyc_segment";
FILE  *in_ppm, *out_ppm;
ImageFuzzy in, out, h_p;
char  in_name[64], out_name[64];
Histogram  *his, *his1, *his2;
int   cur_space = 1, new_space;
int  assign_mean = 1;
char  space[][12] = {"BOGUS", "RGB", "IHS", "L,a,b", "I1-I2-I3", "rgb"};


Image	*
fuzzyc_segment_setup ( Image 	*imgP)
{
	Image		*fcsP;
	float		tore;

	fcsP = imgP;

	print_CVIP("Enter a value for the gaussian kernel variance.\n");
	print_CVIP("[0.0 - 20.0]: ");
	tore = (float) getFloat_CVIP(0.0, 20.0);

	fcsP = fuzzyc_segment(fcsP, tore);

	return fcsP;
}

Image *fuzzyc_segment(
	Image 	*srcImage,
	float	variance
)
{
    	int  		i, j, k;
    	double 		*g;
    	static double 	d[2] = {-1.0, 1.0};
    	int  		choice = -1;

    if((his = (Histogram*) calloc (257, sizeof(Histogram))) == NULL)
    {
       fprintf(stderr, "\nOut of memory\n");
		 delete_Image(srcImage);
       return (Image *)NULL;
    }
    if((his1 = (Histogram*) calloc (257, sizeof(Histogram))) == NULL)
    {
       free(his);
       fprintf(stderr, "\nOut of memory\n");
       return (Image *)NULL;
    }
    if((his2 = (Histogram*) calloc (257, sizeof(Histogram))) == NULL)
    {
       free(his);
       free(his1);
       fprintf(stderr, "\nOut of memory\n");
		 delete_Image(srcImage);
       return (Image *)NULL;
    }
    
    read_ppm(srcImage, &in);
   

#if 0
	    case 1 :
		free(his);
		free(his1);
		free(his2);
         	if(cur_space != 0) {
		    free_matrix(in.matrix);
		}
	        msg_CVIP(fn, "Thanks for using this program, Bye.\n");
		msg_CVIP(fn, "NOTE: no change in orignial image.\n");
		srcImage->image_ptr = NULL;
		getchar();
		 delete_Image(srcImage);
	    return (Image *)NULL;		
		break;

	    	get_tau(&tore);	
		t_len = (int) (10 * tore - 1);
		break;
#endif
		
		if(variance)
			tore = variance;
		t_len = (int) (10 * tore - 1);
		
    		msg_CVIP(fn, "\nComputing histogram, please wait.\n");
		count_his(&in, his);
		max_his(his, in.colors);

		msg_CVIP(fn, "computing scale-space filtering, gaussian(%f, %d)\n", tore, t_len);
		g = gausian(tore, t_len);
		convolution(his, g, in.colors+1, t_len);
                msg_CVIP(fn, "finish convolution, save in \"his0.ppm\".\n");
		max_his(his, in.colors);
		
		msg_CVIP(fn, "computing first derivative, please wait.\n");
		bcopy(his, his1, 257*sizeof(Histogram));
		convolution(his1, d, in.colors, 2);
		msg_CVIP(fn, "finish first derivative, save in \"his1.ppm\".\n");
		max_his(his1, in.colors-1);
		
		msg_CVIP(fn, "computing second derivative, please wait.\n");
		bcopy(his1, his2, 257*sizeof(Histogram));
		convolution(his2, d, in.colors, 2);
		msg_CVIP(fn, "finish second derivative, save in \"his2.ppm\".\n");
		max_his(his2, in.colors-2);
		
		msg_CVIP(fn, "\ndetecting clusters, please wait.\n\n");
		find_cluster();
                bcopy(&in, &out, sizeof(ImageFuzzy));
		if((out.matrix = create_matrix(in.width, in.height)) == NULL)
		{
		    msg_CVIP(fn, "No space for out ppm\n");
			 delete_Image(srcImage);
		    return;
		}
		
		msg_CVIP(fn, "peforming coarse segmentation, please wait.\n\n");
		coarse_seg();
		msg_CVIP(fn, "performing fine segmentation, please wait.\n\n");
		fine_seg();
      write_ppm(&out, srcImage);
		free_matrix(out.matrix);
       
		//new code
		free_matrix(in.matrix);
		return srcImage;

}


/*
**	***	dynamic memory allocation stuff	***
*/


/*
**  allocate a memory of an image
*/

static ImageFuzzy *
create_image(
	int	width, 
	int	height, 
	int	colors
) 
{
   ImageFuzzy *im;
   
   im = (ImageFuzzy *) calloc (1, sizeof(ImageFuzzy));
   if (im == NULL)
   {
      fprintf(stderr, "\nCan not allocate memory!\n");
      return NULL;
   }
   
   im->width = width;
   im->height = height;
   im->colors = colors;
   im->size = im->width * im->height;

   im->matrix = (Pixel **) create_matrix(im->width, im->height);
   if (im->matrix == NULL)
   {
      fprintf(stderr, "\nCan not allocate memory!\n");
      free(im);
      return NULL;
   }
  
   return im;
}

/*
** create a 2D Pixel iamge matrix
*/

static Pixel **
create_matrix(
	int	width, 
	int	height
)
{
   Pixel **m;
   int col;
   
   m = (Pixel **) calloc (height, sizeof(Pixel *));
   if (m == NULL)
   {
      fprintf(stderr, "\nCan not allocate memory!\n");
      return NULL;
   }

   m[0] = (Pixel *) calloc (width, height * sizeof(Pixel));
   if (m[0] == NULL)
   {
      free(m);
      fprintf(stderr, "\nCan not allocate memory!\n");
      return NULL;
   }

   for (col = 1; col < height; col++)
      m[col] = &m[0][col*width];
   
   return m;
}

/*
** free the memory of image
*/

static int 
free_image(
	ImageFuzzy 	*im
)
{
    if(im->matrix != NULL)
        free_matrix(im->matrix);
    if(im != NULL)
        free(im);
    return 0;
}

/*
** free the memory of matrix
*/

static int 
free_matrix(
	Pixel 	**m
)
{
    if(m[0] != NULL)
        free(m[0]);
    if(m != NULL)
        free(m);
    return 0;
}

/****************************************************************
* Note: this function has modified from it's original purpose.  *
* It simple converts one ImageFuzzy structure into the format of     *
* another (Image).                                              *
****************************************************************/

static int 
write_ppm(
	ImageFuzzy	*im, 
	Image		*src
)
{
   	int   	i=0;
   	byte 	*pixelP, **bvecP;
	int 	bands;
   
	im->bands = getNoOfBands_Image(src);

  	bvecP = (byte **) malloc((im->bands)*sizeof(byte *));
	getBandVector_Image(src, bvecP);

   	pixelP = (byte *) im->matrix[0];

      	for(; i < im->size; i++) {
		for (bands=0 ; bands < (im->bands) ; bands++)
			*(bvecP[bands])++ = *pixelP++;
   	}

	return 1;
}

/****************************************************************
* Note: this function has modified from it's original purpose.  *
* It simple converts one Image structure into the format of     *
* another (ImageFuzzy).                                              *
****************************************************************/

static int 
read_ppm(
	Image		*src, 
	ImageFuzzy	*im
)
{
   	int   	i;
   	byte 	*pixelP, **bvecP;
	int	bands;

   	im->width  = getNoOfCols_Image(src);
   	im->height = getNoOfRows_Image(src);
	im->bands = getNoOfBands_Image(src);
   	im->colors = 255;

   	im->size = im->width * im->height;
   
   	msg_CVIP(fn, "width = %d,  height = %d, colors = %d\n", im->width, im->height, im->colors);

   	im->matrix = create_matrix(im->width, im->height);

	bvecP = (byte **) malloc((im->bands)*sizeof(byte *));
	getBandVector_Image(src, bvecP);
   
   	pixelP = (byte *) im->matrix[0];
   
   	for(i=0; i < im->size; i++) {
		for (bands=0 ; bands < (im->bands) ; bands++)
         		*pixelP++ = *(bvecP[bands])++;
   	}
	
	return 1;
}


/*
**	***	math stuff	***
*/

/*
** compute the gausion distrubution
*/

static double *
gausian(
	float	tore, 
	float	len
)
{
    double *ser, neg_two_tore_sqr, c;
    int i, j;
    
    neg_two_tore_sqr = -2.0 * tore * tore;
    c = 1.0 / SQRT_2PI / tore;
    
    if((ser = (double *) calloc (len, sizeof(double))) == NULL)
    {
        fprintf(stderr, "No space for Gaussian series.\n");
	return NULL;
    }
    
    for (i = 0, j = -len/2; i < len; i++, j++)
    {
        ser[i] = c * exp(j * j / neg_two_tore_sqr);
    }
    
    return ser;
}


/*
** convolution of two series
*/

static int 
convolution(
	Histogram	*ser1, 
	double		*ser2, 
	int		len1, 
	int		len2
)
{
    double  *sum;
    int  i, j, k;
    
       
    if((sum = (double *) calloc (len1+len2-1, sizeof(double))) == NULL)
    {
        fprintf(stderr, "No space error in convolution");
	return -1;
    }
        /* init the sum */
   for (k = 0; k < 3; k++)
   { 	    
	for(i = 0; i < len1+len2-1; i++)
	    sum[i] = 0.0;
	    
	for(i = 0; i < len1; i++)
	    for (j = 0; j < len2; j++)
		sum[i+len2-j-1] += ser2[j] * ser1[i][k];
	    
	j = floor(len2/2);
	for (i = 0; i <len1; i++)
	    ser1[i][k] = (double) sum[i+j];
    }		
    free(sum);
    
    return 0;
}

/*
**	***	histogram stuff	***
*/

/*
** extract the three color component histograms
*/

static int 
count_his(
	ImageFuzzy 	*in, 
	Histogram	*his
)   
{
    int i, j;

    for (i=0; i<in->colors+1; i++)
       his[i][0] = his[i][1] = his[i][2] = 0;
    
    for(i=0; i<in->height; i++)
	for(j=0; j<in->width; j++)
	{
	    his[(int)in->matrix[i][j][0]][0]+= 1.0;
	    his[(int)in->matrix[i][j][1]][1]+= 1.0;
	    his[(int)in->matrix[i][j][2]][2]+= 1.0;
	}
   
    max_his(his, in->colors);
    return 0;
}

/*
** finger the max_value of the histogram
*/

static void 
max_his(
	Histogram	*h, 
	int		colors
)
{
    Histogram t;
    int i;
    
    h[colors+1][0] = 0;
    h[colors+1][1] = 0;
    h[colors+1][2] = 0;

       	/* don't consider background */
    for (i=1; i < colors+1; i++)
    {
        t[0] = ABS(h[i][0]);
        t[1] = ABS(h[i][1]);
        t[2] = ABS(h[i][2]);
        h[colors+1][0] = MAX (t[0],h[colors+1][0]);
        h[colors+1][1] = MAX (t[1],h[colors+1][1]);
        h[colors+1][2] = MAX (t[2],h[colors+1][2]);
    }
 
    return;
}


/*
**	***	segmentation stuff	***
*/


/*
** find the class index in one dimension
** return 255 if it is in safety margin
*/

static byte
class_index1(
	byte	c, 
	int	k
)  
{
    unsigned char  i;
    
    for(i = 0; i < pn[k]; i++) {
        if (c < pk[i][k].low)
	    return 255;
	if (c <= pk[i][k].up)
	    return i;
    }
    return 255;
}

static int 
class_index(Pixel p)
{
    int i;
    
      /*    c2 + pn[2] * (c1 + pn1 * c0) */
      /* or c0 + pn[0] * (c1 + pn1 * c2) */
    i = (p[0]*pn[1] + p[1]) * pn[2] + p[2];
    return i;
}
	       
/*
** first stage, coarse segmentation
*/

static void  
coarse_seg(void)
{
    int i, j, k, n, m;
    int d[3];
    Class *kl;
        
	/* allocate & initiate all necessary class structs */
    if((klass = (Class *) calloc (pn[0]*pn[1]*pn[2], sizeof(Class))) == NULL) {
        msg_CVIP(fn, "Too many peaks, try bigger tau.\n\n");
	return;
    }
        /* initate class to be {0, {0,0,0}, {0,0,0}, {0,0,0}} */
    kl = klass;
    for(i = 0; i < pn[0]; i ++)
      for(j = 0; j < pn[1]; j ++) 
        for(k = 0; k < pn[2]; k++) {
	    kl->mean[0] = kl->mean[1] = kl->mean[2] = 0.0;
	    kl->std[0] = kl->std[1] = kl->std[2] = 0.0;
	    kl->count = 0;
	    kl->peak[0] = pk[i][0].peak;
	    kl->peak[1] = pk[j][1].peak;
	    kl->peak[2] = pk[k][2].peak;
	    kl++;
	}
	
    not_count = 0;   /* the counter of unclassified pixels */
        /* first run to count the class.count and class.mean */
    for(i = 0; i < out.height; i ++)
      for(j = 0; j < out.width; j ++) {
        for(k = 0; k < 3; k++)
            if(((out.matrix[i][j][k] = class_index1(in.matrix[i][j][k], k))>=pn[k])
	      && (out.matrix[i][j][k] != 255))
	    {
	        msg_CVIP(fn, "error return from index1(): too many peaks in \n\n");
	        getchar();
	    }
	if( (out.matrix[i][j][0] == 255) || (out.matrix[i][j][1] == 255) ||
	                                    (out.matrix[i][j][2] == 255) ) {
	    out.matrix[i][j][0] = 255;
	    out.matrix[i][j][1] = 255;
	    out.matrix[i][j][2] = 255;
	    not_count ++;
	} else {
	    n = class_index(out.matrix[i][j]);
	    for(k = 0; k < 3; k++)
	        klass[n].mean[k] += (double) in.matrix[i][j][k];
	    klass[n].count ++;
	}
      }
        /* eliminate minor classes, an important coefficient !!!!!!!!! */
    m = in.size * 0.005;
    
    max_peak = 0;
    for(i = 0; i < pn[0]*pn[1]*pn[2]; i++) {
        if(klass[i].count <= m) {
	    klass[i].count = 0;
	} else {
	    max_peak ++;
	        /* normalize the mean */
	    for(k = 0; k < 3; k++)
	        klass[i].mean[k] /= (double) klass[i].count;
	}
    }

    msg_CVIP(fn, "all the klasses = %d\n\n", pn[0]*pn[1]*pn[2] );
/*    for(i= 0; i < pn[0]*pn[1]*pn[2]; i ++)
    {
        msg_CVIP(fn, "%d : count=%d, mean{%5.2f,%5.2f,%5.2f}\n\n", i, klass[i].count,
	        klass[i].mean[0],klass[i].mean[1],klass[i].mean[2]);
    }
*/ 
	msg_CVIP(fn, "Total number of unclassified pixels: %d (%5.2f%% of Total %d)\n\n", 
           not_count, 100.0 * not_count / out.size, out.size);
 
 
        /* decided the represent colors */
    if(max_peak > 27) { 
         msg_CVIP(fn, " Too many classes, Assigning color will cause problem, use"
	        "mean value for result colors\n\n");
	 assign_mean = 1;
    } 
    
    if (assign_mean == 0)
    n = 0;
    kl = klass;
        /* assign the predefined colors */
    for(i = 0; i < pn[0]; i ++)
      for(j = 0; j < pn[1]; j ++) 
        for(k = 0; k < pn[2]; k++) {
            if((kl->count != 0) && (n < max_peak)) {
	        kl->color[0] = colors[n][0];
		kl->color[1] = colors[n][1];
		kl->color[2] = colors[n][2];
		n ++;
	    }
	    kl++;
	}
    
        /* second run to compute std */
    for(i = 0; i < out.height; i ++)
      for(j = 0; j < out.width; j ++) {
        if( (out.matrix[i][j][0] != 255) && (out.matrix[i][j][1] != 255) &&
	                                    (out.matrix[i][j][2] != 255) ) {
	    
	    n = class_index(out.matrix[i][j]);
	        /* re-assign the pixels belongs to minor classes */	        
	    if (klass[n].count == 0) { /* invalid class */
	        out.matrix[i][j][0] = 255;
	        out.matrix[i][j][1] = 255;
	        out.matrix[i][j][2] = 255;
		not_count ++;
	    } else {   /* classify all pixels belongs to valid classes */
	        for(k = 0; k < 3; k++) {
	            klass[n].std[k] += (in.matrix[i][j][k] - klass[n].mean[k]) 
	                             * (in.matrix[i][j][k] - klass[n].mean[k]);
                    if(assign_mean == 1)
		        out.matrix[i][j][k] = klass[n].mean[k];
		    else 
		        out.matrix[i][j][k] = klass[n].color[k];

		}
	    }
	}
      }

    max_peak = 0;
        /* normalize the class.std */
    for(i = 0; i < pn[0]*pn[1]*pn[2]; i++) {
        if(klass[i].count != 0) {
	/* definition of std ?????? */
	    for(k = 0; k < 3; k++) {
	        klass[i].std[k] /= (double) klass[i].count;
	        klass[i].std[k] = sqrt(klass[i].std[k]);
	    }
	    bcopy(&(klass[i]), &(klass[max_peak++]), sizeof(Class));
	}
    }
    
    msg_CVIP(fn, "\nTotal Number of Peaks (max_peak)= %d\n\n", max_peak);
/*    for(i= 0; i < max_peak; i ++)
    {
        msg_CVIP(fn, "%d : count=%d, mean{%5.2f,%5.2f,%5.2f}, std = " 
	       "{%5.2g,%5.2g,%5.2g}\n\n", i, klass[i].count,
	        klass[i].mean[0],klass[i].mean[1],klass[i].mean[2],
		klass[i].std[0], klass[i].std[1], klass[i].std[2]);
    }
*/
    msg_CVIP(fn, "Total Number of unclassified Pixels: %d (%5.2f%% of Total %d)\n\n",
           not_count, 100.0 * not_count / out.size, out.size);
         
    return;
}	   

/*
** membership : 3D gausian distrubution
*/

static double 
member_ship(
	Pixel	p, 
	Class	k
)
{
    int i;
    double d[3];
    
    for(i = 0; i < 3; i++) { 
    	d[i] = (p[i] - k.mean[i]) * (p[i] - k.mean[i]);
        d[i] = -0.5 * d[i] / (k.std[i] * k.std[i]);
	d[i] = exp(d[i]) / k.std[i];
    } 

    return (d[0]*d[1]*d[2]);
}

/*
** second stage : fine segmentation
*/

static void  
fine_seg(void)
{
    	int 	i, j, k, n, member;
    	double  mp1, mp2;
    	int 	nc[64], ncsum=0;
    
        /* exclude those class which std = 0.0 */
    i = 0;      /* the last class with non-zero std */
        /* compack the valid classes */
    for(n = 0; n < max_peak; n++) {
        nc[n] = 0;
        if((klass[n].std[0] != 0.0) && (klass[n].std[1] != 0.0)
	                            && (klass[n].std[2] != 0.0)){
	    if (i != n)
	        bcopy(&klass[n], &klass[i], sizeof(Class));
	    i ++;
	}
    }   
        
	/* no valid peak exists */
    if((max_peak = i) == 0)
        return;
    
    msg_CVIP(fn, "Total Number of Peaks (max_peak) = %d\n\n", max_peak);
/*    for(i= 0; i < max_peak; i ++)
    {
        msg_CVIP(fn, "%d : count=%d, mean{%5.2f,%5.2f,%5.2f}, std = "
	       "{%5.2g,%5.2g,%5.2g}\n\n", i, klass[i].count,
	        klass[i].mean[0],klass[i].mean[1],klass[i].mean[2],
		klass[i].std[0], klass[i].std[1], klass[i].std[2]);
    }
*/
	
	/* last run to assign the unclassfied pixels */
    for(i = 0; i < out.height; i ++)
      for(j = 0; j < out.width; j ++) {
        if( (out.matrix[i][j][0] == 255) || (out.matrix[i][j][1] == 255) ||
	                                    (out.matrix[i][j][2] == 255) ) {
	        /* find the min membership */
	    mp1 = member_ship(in.matrix[i][j], klass[0]);
	    member = 0;
	    for(n = 1; n < max_peak; n++) {
	        mp2 = member_ship(in.matrix[i][j], klass[n]);
	        if (mp2 > mp1) {
		    member = n;
		    mp1 = mp2;
		}
            }
	    nc[member]++;
	    for(k = 0; k < 3; k++) {
		if(assign_mean == 1)
		    out.matrix[i][j][k] = klass[member].mean[k];
		else 
		    out.matrix[i][j][k] = klass[member].color[k];

	    }
	}
      }
      
        /* all the memory allocated in seg.c should be freed hers */
    free(pk);
    free(klass);
    
    for(n = 0; n < max_peak; n++) {
        msg_CVIP(fn, "%d pixels classified to class %d\n", nc[n], n);
	ncsum += nc[n];
    }
    
    msg_CVIP(fn, "Total Pixels classifies in fine segmentation : %d\n", ncsum);

    return;
}
    
/*
** find the valid cluster
*/

static void
find_cluster(void)
{
    int i, j, k;
    int v_or_p = 1;  /* a flag, if a peak reached clu = 1, else clu = 0*/
    
    vn[0] = vn[1] = vn[2] = 0;
    pn[0] = pn[1] = pn[2] = 0;
    peak[0][0] = 0.0;
    peak[0][1] = 0.0;
    peak[0][2] = 0.0;
    valley[0][0] = 0.0;
    valley[0][1] = 0.0;
    valley[0][2] = 0.0;
    
    for(k = 0; k < 3; k++)
    {   
        v_or_p = 1;
        for(j = 1; j < in.colors-2; j++)
        {
	    if((his1[j][k] == 0.0) || (his1[j-1][k]*his1[j+1][k] < 0.0))
	    {
	        if((v_or_p == 1) && (his2[j][k] > 0.0))
		{   /* it's a valley */
		  /* msg_CVIP(fn, "a valley is reached, color=%d, v=%d\n", k, j);*/
		   v_or_p = 0;  /* turn the flag */
		   valley[vn[k]][k] = (double) j;
		   vn[k]++;
		   if (pn[k] == 0)
		      pn[k] ++; 
		} else { 
		    if((v_or_p == 0) && (his2[j][k] < 0.0))
		    {  /* it's a peak */
		        v_or_p = 1;     /* set the flag */
			peak[pn[k]][k] = (double) j;
			pn[k]++;
			
		    }
		}                      
      	    }
	}
	if((v_or_p == 0) || (pn[k] == vn[k])) {
	    /* the last one is a valley, so assume a peak at 255 */
	    peak[pn[k]][k] = 255.0;
	    pn[k]++;
	}

	/* to mark the end */
	peak[pn[k]][k] = valley[vn[k]][k] = 0.0;
/*	msg_CVIP(fn, "pn = %d, peaks in color %d : ", pn[k], k);
	for (i= 0; i <= pn[k]; i++)
	     msg_CVIP(fn, " %5.2f ", peak[i][k]);

	msg_CVIP(fn, "\n");
	msg_CVIP(fn, "vn = %d, valleys in color %d : ", vn[k], k);
	for (i= 0; i <= vn[k]; i++)
	     msg_CVIP(fn, " %5.2f ", valley[i][k]);
	
	msg_CVIP(fn, "\n");	
*/    
	}

    /* try to fill in the struct peak */
    max_peak = 0;
    for (k = 0; k < 3; k++) {
       max_peak = MAX(max_peak, pn[k]);
       max_peak = MAX(max_peak, vn[k]);
    }
    pk = (Peak *) calloc(max_peak, sizeof(Peak));
    for (k = 0; k < 3; k++) {
        for(i = 0; i < pn[k]; i++) {
	    if(peak[i][k] == 0.0)
	        pk[i][k].low = 0.0;
	    else
	        pk[i][k].low = safe*peak[i][k] + (1-safe)*valley[i-1][k];
	    pk[i][k].peak = peak[i][k];
	    if(valley[i][k] == 0.0)
	        pk[i][k].up = safe*peak[i][k] + (1-safe)*255.0;
	    else
	        pk[i][k].up = safe*peak[i][k] + (1-safe)*valley[i][k];
	    
	}
/*	msg_CVIP(fn, "pn = %d, peaks in color %d : ", pn[k], k);
	for (i= 0; i < pn[k]; i++)
	    msg_CVIP(fn, " {%5.2f,%5.2f,%5.2f}", pk[i][k].low, pk[i][k].peak, 
	            pk[i][k].up);
	msg_CVIP(fn, "\n\n");
*/	
    }
  
	return;
}	   


