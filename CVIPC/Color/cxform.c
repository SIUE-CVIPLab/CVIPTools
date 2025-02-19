/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: cxform.c
*           Description: contains functions for computing the color transform
*			 of an image.
*         Related Files: CVIPcolor.h, Imakefile
*   Initial Coding Date: Sun May 30 14:48:01 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Gregory Hance
*                        Southern Illinois University @ Edwardsville
*
*  Global Function List: colorxform - perform a color transform
*			 linxform - perform a linear transform
*
*   Local Function List: rgb2hsl - RGB -> HSL transform
*			 rgb2hsv - RGB -> HSV transform
*			 chrom_xform - RGB -> chromaticity transform
*			 spher_xform - RGB -> spherical transform
*			 spher_inv_xform - spherical transform->RGB
*			 cylin_xform - RGB -> cylindrical transform
*			 cylin_inv_xform - cylindrical transform->RGB
*			 Lab_xform - RGB -> C.I.E. L*a*b* transform
*			 Lab_inv_xform - C.I.E. L*a*b* transform->RGB
*			 Luv_xform - EGB -> C.I.E. L*u*v* transform
*			 Luv_inv_xform - C.I.E. L*u*v* transform->EGB
*                        hsl2rgb - HSL -> RGB transform
*                        hsv2rgb - HSV -> RGB transform
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
** Revision 1.11 Xiaohe Chen 2003/12
** fixed the burst error message addd counter
** $Log: cxform.c,v $
** Revision 1.10  1997/07/17 15:04:46  yawei
** fixed memory access bug
**
** Revision 1.9  1997/03/08 00:58:54  yawei
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
** Revision 1.8  1997/01/15 17:17:18  yawei
** Global Change:  IMAGE ==> Image
**
* Revision 1.7  1996/12/06  01:47:04  wli
* fix a name error
*
* Revision 1.6  1996/12/05  03:37:03  wli
* modify colorxform() to accomodate normalize.
*
* Revision 1.5  1996/12/05  03:11:51  wli
* *** empty log message ***
*
* Revision 1.4  1996/12/05  00:12:00  wli
* add new functions Luv_inv_xform(), Lab_inv_xform(),
* spher_inv_xform() and cylin_inv_xform() into CVIPtools.
*
* Revision 1.3  1996/07/22  16:32:02  akjoele
* *** empty log message ***
*
* Revision 1.2  1996/02/29  14:49:23  akjoele
* Redefined rgb2hsv and hsv2rgb from being static to enable their being
* accessed by other modules.
*
* Revision 1.1  1993/05/31  03:23:39  hanceg
* Initial revision
*
*
****************************************************************************/
#include "CVIPdef.h"
#include "CVIPcomplex.h"
#include "CVIPtoolkit.h"
#include "CVIPcolor.h"

#define MIN2(x,y)       (((x) < (y)) ? (x) : (y))
#define MAX2(x,y)       (((x) > (y)) ? (x) : (y))
#define MIN3(a,b,c)     (MIN2(a,MIN2(b,c)))
#define MAX3(a,b,c)     (MAX2(a,MAX2(b,c)))

static void rgb2hsl(float **cvecP, unsigned long vdim);
static void hsl2rgb(float **cvecP, unsigned long vdim);
static void chrom_xform(float **cvecP, unsigned long vdim);
static void spher_xform(float **cvecP, unsigned long vdim);
static void cylin_xform(float **cvecP, unsigned long vdim);
static void Luv_xform(float **cvecP, unsigned long vdim, float Xo, float Yo, float Zo);
static void Lab_xform(float **cvecP, unsigned long vdim, float Xo, float Yo, float Zo);
static void Luv_inv_xform(float **cvecP, unsigned long vdim, float Xo, float Yo, float Zo);
static void Lab_inv_xform(float **cvecP, unsigned long vdim, float Xo,
	float Yo, float Zo);
static void spher_inv_xform(float **cvecP, unsigned long vdim);
static void cylin_inv_xform(float **cvecP, unsigned long vdim);


/****************************************************************
Name: colorxform
Expanded Name: Color Transform
Parameters: <rgbImage> - pointer to an Image structure (must have
a have data type equal to or less precise than type
CVIP_FLOAT)
<newcspace> - color space to transform to
<norm> - pointer to a normalization vector
<refwhite> - pointer to reference white values (used
only in LUV and LAB transform)
<dir> - direction of transform (1 => (RGB-><newcspace>)
else (<newcspace>->RGB is assumed))
Returns: pointer to Image structure containing the color
transformed image of type float.
Description: transforms an RGB image into a new color space
specified by <newcspace>, one of...
HSL - Hue/Saturation/Lightness,
HSV - Hue/Saturation/Value,
SCT - Spherical Coordinates Transform,
CCT - Cylindrical Coordinates Transform,
LAB - C.I.E. L*a*b* Color Coordinate System,
LUV - C.I.E. L*u*v* Color Coordinate System,
XYZ - Chromaticity Coordinate System. 
Each transform requires that the input image be
normalized between 0 and 1.  A pointer to a
normalization vector <norm> must be passed that
contains a set of values to normalize the image bands
with. (e.g. norm[0] = norm[1] = norm[2] = 255.0). If
<norm> is NULL then it will be assumed that the input
image is already normalized. colorxform is capable of
performing several inverse transforms as well. If <dir>
is passed as any other value except for one then the
inverse transform (<newcspace>->RGB) will be performed.
Currently the only inverse transforms that are
supported are HSL->RGB & HSV->RGB.
If either a L*a*b* or L*u*v* transform is requested
then an additional parameter <refwhite> must be passed
as well. (e.g. refwhite[0] = refwhite[1] = refwhite[2]
= 1.0 ). All transforms will also be normalized to
the range [0.0 ... 1.0] except for L*a*b* and L*u*v*
whose range will vary with different values of
reference white.
Diagnostics: returns NULL pointer with corresponding error message
upon error.
Credit(s): Gregory Hance
Southern Illinois University @ Edwardsville
****************************************************************/

Image *colorxform(const Image *rgbImage, COLOR_FORMAT newcspace, float *norm,float *refwhite, int dir) 
{



	Image *cstImage, *freeImage;
	register float *rP, *gP, *bP, *rnP, *gnP, *bnP;
	float  **cvecP;
	double **tmatrix;
	unsigned long imgsize;
	register int i=0, j;
	const char *fn = "colorxform";
	const char *csn[] = { NULL, NULL, "RGB", "HSL", "HSV", "SCT", "CCT", 
		"L*u*v", "L*a*b", "XYZ" };


	castImage((Image *)rgbImage, CVIP_FLOAT);
	cstImage = (Image *) rgbImage;

	imgsize = rgbImage->image_ptr[0]->cols*rgbImage->image_ptr[0]->rows;

	/* Simplify some variables */
	rP = (float *) cstImage->image_ptr[0]->rptr[0];
	gP = (float *) cstImage->image_ptr[1]->rptr[0];
	bP = (float *) cstImage->image_ptr[2]->rptr[0];

	cvecP = (float **) malloc(3*sizeof(float *));
	cvecP[0] = rP; cvecP[1] = gP; cvecP[2] = bP;

	if(norm != NULL)
	{
		if(*(norm+1) == 1.0 )
		{
			for(i= 0;i<3;i++,refwhite++)
			{
				*refwhite = 1.0;
			}
			for(i= 0;i<3;i++,refwhite--);
		}

	}i=0;

	if(norm != NULL)
	{
		if(*norm == 255.0)
		{
			for(i= 0;i<3;i++,norm++)
			{
				*norm = 255.0;
			}
			for(i= 0;i<3;i++,norm--);
		}

	}
	i=0;






	/* Normalize Image data */
	if(norm) {
		fprintf(stderr, "%s: normalizing color vector...\n", fn);
		(void) vecnorm(cvecP, norm, CVIP_FLOAT, 3, imgsize);
	}

	fprintf(stderr, "%s: converting from %s color coordinate system\n", fn, csn[cstImage->color_space]);
	fprintf(stderr, "%s: to %s color coordinate system...\n", fn, csn[newcspace]);

	if(dir==1) 
		switch(newcspace) {
		case HSL:
			rgb2hsl(cvecP, imgsize);
			break;
		case XYZ:
			chrom_xform(cvecP, imgsize);
			break;
		case SCT:
			spher_xform(cvecP, imgsize);
			break;
		case CCT:
			cylin_xform(cvecP, imgsize);
			break;
		case LUV:
			Luv_xform(cvecP, imgsize, refwhite[0], refwhite[1], refwhite[2]);
			break;
		case LAB:
			Lab_xform(cvecP, imgsize, refwhite[0], refwhite[1], refwhite[2]);
			break;
		case HSV:
			rgb2hsv( cvecP, imgsize);
			break;
		default: fprintf(stderr,"%s: can't happen!\n",fn); break;
	}
	else {
		switch(newcspace) {
		case HSL:
			hsl2rgb(cvecP, imgsize);
			break;
		case HSV:
			hsv2rgb(cvecP, imgsize);
			break;	 
		case SCT:
			spher_inv_xform(cvecP, imgsize);
			break;
		case CCT:
			cylin_inv_xform(cvecP, imgsize);
			break;
		case LUV:
			Luv_inv_xform(cvecP, imgsize, refwhite[0], refwhite[1], refwhite[2]);
			break;
		case LAB:
			Lab_inv_xform(cvecP, imgsize, refwhite[0], refwhite[1], refwhite[2]);
			break;   
		default: fprintf(stderr,"%s: can't happen!\n",fn); break;
		}
	}
	if (norm)
		for(rnP=rP, gnP=gP, bnP=bP; i < imgsize; i++, rnP++, gnP++, bnP++) {
			*rnP *= 255.0; *gnP *= 255.0; *bnP *= 255.0;  }

		//	if (err_counter != 0)
		//		fprintf(stderr,"reverse cxform: bogus hue angle, total %d messages\n", err_counter);


		free(cvecP);
		return cstImage;
}


/****************************************************************
Name: rgb2hsl
Expanded Name: rgb to hsl
Parameters: <cvecP> - pointer to an array of normalized
band vectors
<vdim> - dimension of each vector (number of pixels)
Returns: nada
Description: Performs RGB to HSL color transformation. The resulting
transform will also be normalized to [0.0 ... 1.0]. 
Diagnostics: none
Credit(s): Gregory Hance
Southern Illinois University @ Edwardsville
****************************************************************/

static void rgb2hsl(float **cvecP, unsigned long vdim)
{
	float min, max, rc, gc, bc, dmm;
	float r, g, b, *h, *s, *l;
	register unsigned long i=0;

	h = cvecP[0]; r = *h;
	s = cvecP[1]; g = *s;
	l = cvecP[2]; b = *l;

	for(; i < vdim; i++) {

		r=*h; g=*s; b=*l;
		max = MAX3(r,g,b);
		min = MIN3(r,g,b);

		/* calculate lightness */
		*l = (max + min)/2;

		/* calculate saturation */

		if (max == min) *s = *h = 0; /* achromatic case */
		else
		{
			*s = (dmm = (max-min))/( (*l <= 0.5) ? (max+min): (2-max-min) );

			/* calculate hue */
			rc = (max-r)/dmm;
			gc = (max-g)/dmm;
			bc = (max-b)/dmm;

			/***********************************************
			* (r == max) => between yellow & magenta      *
			* (g == max) => between cyan & yellow         *
			* (b == max) => between magenta & cyan        *
			***********************************************/               

			*h = (r == max) ? (bc-gc) : (g == max) ? (2+rc-bc) : (4+gc-rc);

			/* divide into sextants */      
			*h /= 6;  
			if (*h < 0.0) *h += 1.0;
		}
		h++;s++;l++;
	}
}


/****************************************************************
Name: rgb2hsv
Expanded Name: rgb to hsv
Parameters: <cvecP> - pointer to an array of normalized
band vectors
<vdim> - dimension of each vector (number of pixels)
Returns: nada
Description: Performs RGB to HSV color transformation. The resulting
transform will also be normalized to [0.0 ... 1.0]. 
Diagnostics: none
Credit(s): Gregory Hance
Southern Illinois University @ Edwardsville
****************************************************************/

void rgb2hsv(float **cvecP, unsigned long vdim)
{
	float min, max, rc, gc, bc, dmm;
	float r, g, b, *h, *s, *v;
	register unsigned long i=0;

	h = cvecP[0]; r = *h;
	s = cvecP[1]; g = *s;
	v = cvecP[2]; b = *v;

	for(; i < vdim; i++, r=*++h, g=*++s, b=*++v) {

		*v = max = MAX3(r,g,b);
		min = MIN3(r,g,b);

		/* calculate saturation */

		dmm = max-min;

		*s = (max == 0.0) ? 0.0 : dmm/max;

		if (*s == 0.0) *h = 0;
		else
		{

			/* calculate hue */
			rc = (max-r)/dmm;
			gc = (max-g)/dmm;
			bc = (max-b)/dmm;

			/***********************************************
			* (r == max) => between yellow & magenta      *
			* (g == max) => between cyan & yellow         *
			* (b == max) => between magenta & cyan        *
			***********************************************/               

			*h = (r == max) ? (bc-gc) : (g == max) ? (2+rc-bc) : (4+gc-rc);

			/* divide into sextants */      
			*h /= 6;  
			if (*h < 0.0) *h += 1.0;
		}
	}
}


/****************************************************************
Name: chrom_xform
Expanded Name: chromaticity transform
Parameters: <cvecP> - pointer to an array of normalized
band vectors
<vdim> - dimension of each vector (number of pixels)
Returns: nada
Description: Performs RGB to XYZ color transformation. The resulting
transform will also be normalized to [0.0 ... 1.0]. 
Diagnostics: none
Credit(s): Gregory Hance
Southern Illinois University @ Edwardsville
****************************************************************/

static void chrom_xform(float **cvecP, unsigned long vdim)
{
	float sum;
	float r, g, b, *x, *y, *z;
	register unsigned long i=0;

	x = cvecP[0]; r = *x;
	y = cvecP[1]; g = *y;
	z = cvecP[2]; b = *z;

	for(; i < vdim; i++, r=*++x, g=*++y, b=*++z) {
		sum = r + g + b;
		if(sum==0.0) (*x = *y = *z = 0.0);
		else (*x = r/sum, *y = g/sum, *z = b/sum);
	}
}

#ifndef PI
#define PI 3.141592654
#endif


/****************************************************************
Name: spher_xform
Expanded Name: spherical transform
Parameters: <cvecP> - pointer to an array of normalized
band vectors
<vdim> - dimension of each vector (number of pixels)
Returns: nada
Description: Performs RGB to SCT color transformation. The resulting
transform will also be normalized to [0.0 ... 1.0]. 
Diagnostics: none
Credit(s): Gregory Hance
Southern Illinois University @ Edwardsville
****************************************************************/

static void spher_xform(float **cvecP, unsigned long vdim) 
{ 
	double arg_acos;
	float r, g, b, *rho, *phi, *theta;
	register unsigned long i=0;

	rho   = cvecP[0]; r = *rho;
	phi   = cvecP[1]; g = *phi;
	theta = cvecP[2]; b = *theta;

	for(; i < vdim; i++, r=*++rho, g=*++phi, b=*++theta) {

		*rho = (float) sqrt((double)(r*r + g*g + b*b));

		if (*rho == 0.0) *phi = *theta = 0.0;
		else {
			arg_acos = ((double) b)/(*rho);
			*phi = (arg_acos > 1.0) ? (float) acos(1.0) : (float) acos(arg_acos);

			arg_acos = ((double) r)/ ( (*rho)*sin((double)*phi) );
			*theta = (arg_acos > 1.0) ? (float) acos(1.0) : (float) acos(arg_acos);

		}
	}
}


/****************************************************************
Name: spher_inv_xform
Expanded Name: spherical inverse transform
Parameters: <cvecP> - pointer to an array of normalized
band vectors
<vdim> - dimension of each vector (number of pixels)
Returns: nada
Description: Performs SCT to RGB color transformation.
Diagnostics: none
Author: Wenxing Li
Southern Illinois University @ Edwardsville
****************************************************************/

void spher_inv_xform(float **cvecP, unsigned long vdim)
{
	double         rho_sin_phi;
	float        * r, * g, * b, rho, phi, theta;
	unsigned long  i;

	r   = cvecP[0];  rho   = *r;
	g   = cvecP[1];  phi   = *g;
	b   = cvecP[2];  theta = *b;

	for(i=0; i < vdim; i++, rho=*++r, phi=*++g, theta=*++b)
	{   
		rho_sin_phi = (double)rho * sin((double)phi);
		*r = (float)(rho_sin_phi * cos((double)theta));
		*g = (float)(rho_sin_phi * sin((double)theta));
		*b = (float)((double)rho * cos((double)phi));
	}   
}


/****************************************************************
Name: cylin_xform
Expanded Name: cylindrical transform
Parameters: <cvecP> - pointer to an array of normalized
band vectors
<vdim> - dimension of each vector (number of pixels)
Returns: nada
Description: Performs RGB to HSL color transformation. The resulting
transform will also be normalized to [0.0 ... 1.0]. 
Diagnostics: none
Credit(s): Gregory Hance
Southern Illinois University @ Edwardsville
****************************************************************/

static void cylin_xform(float **cvecP, unsigned long vdim)
{ 
	float r, g, b, *rr, *theta, *z;
	register unsigned long i=0;

	rr = cvecP[0]; r = *rr;
	theta = cvecP[1]; g = *theta;
	z = cvecP[2]; b = *z;

	for(; i < vdim; i++, r=*++rr, g=*++theta, b=*++z) {

		REC2POL(float, *rr, *theta, r, g);

	}
}


/****************************************************************
Name: cylin_inv_xform
Expanded Name: cylindrical inverse transform
Parameters: <cvecP> - pointer to an array of normalized
band vectors
<vdim> - dimension of each vector (number of pixels)
Returns: nada
Description: Performs cylindrical to RGB color transformation.
Diagnostics: none
Author: Wenxing Li
Southern Illinois University @ Edwardsville
****************************************************************/

void cylin_inv_xform(float **cvecP, unsigned long vdim)
{
	float         * r, * g, rr, theta;
	unsigned long   i;

	r = cvecP[0];    rr = *r;
	g = cvecP[1]; theta = *g;

	for(i=0; i < vdim; i++, rr=*++r, theta=*++g)
	{
		*r = (float)((double)rr * cos((double)theta));
		*g = (float)((double)rr * sin((double)theta));
	}
}


/****************************************************************
Name: Luv_xform
Expanded Name: L*u*v* transform
Parameters: <cvecP> - pointer to an array of normalized
band vectors
<vdim> - dimension of each vector (number of pixels)
<Xo> - reference white for red
<Yo> - reference white for green
<Zo> - reference white for blue
Returns: nada
Description: Performs RGB to LUV color transformation. 
Diagnostics: none
Credit(s): Gregory Hance
Southern Illinois University @ Edwardsville
****************************************************************/

static void Luv_xform(float **cvecP, unsigned long vdim, float Xo, float Yo, float Zo) 
{ 



	float Y_Yo, uo_prime, vo_prime, uv_den, u_prime, v_prime;
	double one_third_power;
	float X, Y, Z, *L, *u, *v;
	register unsigned long i=0;

	L   = cvecP[0]; X = *L;
	u   = cvecP[1]; Y = *u;
	v   = cvecP[2]; Z = *v;

	/* Using the NTSC RGB Receiver Primaries R = 1, G = 1, B = 1, This by
	the following transformation matrix Xo, Yo, and Zo are obtained:
	Xo = R{ 0.607,  0.174,  0.201} = 0.982, 
	Yo = G{ 0.299,  0.587,  0.114} = 1.0, 
	Zo = B{0.000,  0.066,  1.117}  = 1.183 

	*/




	uo_prime = (4 * Xo) / (Xo + (15 * Yo) + (3 * Zo));
	vo_prime = (9 * Yo) / (Xo + (15 * Yo) + (3 * Zo));

	one_third_power = (1.0/3.0);

	for(; i < vdim; i++, X=*++L, Y=*++u, Z=*++v) {

		uv_den = X + (15 * Y) + (3 * Z);

		if(uv_den == 0.0) *L = *u = *v = 0.0;
		else {
			u_prime = (4 * X) / uv_den;
			v_prime = (9 * Y) / uv_den;

			Y_Yo = Y / Yo;

			*L = (Y_Yo <= 0.008856) ? (903.3 * Y_Yo) : (float) 116*pow ((double)Y_Yo, one_third_power) - 16;
			*u = 13 * (*L) * (u_prime - uo_prime);
			*v = 13 * (*L) * (v_prime - vo_prime);       
		}
	}

}


/****************************************************************
Name: Luv_inv_xform
Expanded Name: L*u*v* inverse transform
Parameters: <cvecP> - pointer to an array of normalized
band vectors
<vdim> - dimension of each vector (number of pixels)
<Xo> - reference white for red
<Yo> - reference white for green
<Zo> - reference white for blue
Returns: nada
Description: Performs LUV to RGB color transformation.
Diagnostics: none
Author: Wenxing Li
Southern Illinois University @ Edwardsville
****************************************************************/

/* When (x+15Y+3Z)==0 or L==0, L, u, v will all be 0; When L==0(L=u=v=0 actually), let
X=Y=Z=0; the left will all satisfy (X+15Y+3Z)!=0 and L!=0:
For Y, when L > 8.0, it will use L = 116*pow((Y/Yn), 1/3) - 16;
when L <= 8.0, it will use Lm = 903.3 * (Y/Yn).
For X and Z:  X = (Y*(9*u'))/(4*v')
Z = (3*Y)/v' - X/3 - 5*Y
*/

static void Luv_inv_xform(float **cvecP, unsigned long vdim, float Xo, float Yo, float Zo)
{
	float           uo_prime, vo_prime, u_prime, v_prime;
	float         * X, * Y, * Z, L, u, v;
	unsigned long   i;

	X   = cvecP[0]; L = *X;
	Y   = cvecP[1]; u = *Y;
	Z   = cvecP[2]; v = *Z;

	uo_prime = (4 * Xo) / (Xo + (15 * Yo) + (3 * Zo));
	vo_prime = (9 * Yo) / (Xo + (15 * Yo) + (3 * Zo));

	for(i=0; i < vdim; i++, L=*++X, u=*++Y, v=*++Z)
	{ if(L == 0.0) *X = *Y = *Z = 0.0;
	else
	{ if (L > 8.0) *Y = Yo*pow(((L+16)/116), 3);
	else         *Y = (Yo*L)/903.3;

	u_prime = u/(13*L) + uo_prime;
	v_prime = v/(13*L) + vo_prime;

	*X = (9*u_prime*(*Y))/(4*v_prime);

	*Z = (3*(*Y))/v_prime - *X/3 - 5*(*Y);
	}
	}    
}


/****************************************************************
Name: Lab_xform
Expanded Name: L*a*b* transform
Parameters: <cvecP> - pointer to an array of normalized
band vectors
<vdim> - dimension of each vector (number of pixels)
<Xo> - reference white for red
<Yo> - reference white for green
<Zo> - reference white for blue
Returns: nada
Description: Performs RGB to LAB color transformation. 
Diagnostics: none
Credit(s): Gregory Hance
Southern Illinois University @ Edwardsville
****************************************************************/

static void Lab_xform(float **cvecP, unsigned long vdim, float Xo, 
	float Yo, float Zo) 
{ 
	float X_Xo, Y_Yo, Z_Zo;
	double one_third_power;
	float X, Y, Z, *L, *a, *b;
	register unsigned long i=0;

	L   = cvecP[0]; X = *L;
	a   = cvecP[1]; Y = *a;
	b   = cvecP[2]; Z = *b;


	/* Using the NTSC RGB Receiver Primaries R = 1, G = 1, B = 1, This by
	the following transformation matrix Xo, Yo, and Zo are obtained:
	Xo = R{ 0.607,  0.174,  0.201} = 0.982, 
	Yo = G{ 0.299,  0.587,  0.114} = 1.0, 
	Zo = B{0.000,  0.066,  1.117}  = 1.183 
	*/

	one_third_power = (1.0/3.0);

	for(; i < vdim; i++, X=*++L, Y=*++a, Z=*++b) {

		X_Xo = X / Xo; 
		Y_Yo = Y / Yo;
		Z_Zo = Z / Zo;

		*L = (float) 116*pow ((double)Y_Yo, one_third_power) - 16;
		*a = (float) 500*( pow((double)X_Xo, one_third_power) - pow((double)Y_Yo, one_third_power) );
		*b = (float) 200*( pow((double)Y_Yo, one_third_power) - pow((double)Z_Zo, one_third_power) );
	}

}


/****************************************************************
Name: Lab_inv_xform
Expanded Name: L*a*b* inverse transform
Parameters: <cvecP> - pointer to an array of normalized
band vectors
<vdim> - dimension of each vector (number of pixels)
<Xo> - reference white for red
<Yo> - reference white for green
<Zo> - reference white for blue
Returns: nada
Description: Performs LAB to RGB color transformation.
Diagnostics: none
Author: Wenxing Li
Southern Illinois University @ Edwardsville
****************************************************************/

static void Lab_inv_xform(float **cvecP, unsigned long vdim, float Xo,
	float Yo, float Zo)
{
	float            X_Xo, Y_Yo, Z_Zo;
	float          * X, * Y, * Z, L, a, b;
	unsigned long    i;

	X   = cvecP[0]; L = *X;
	Y   = cvecP[1]; a = *Y;
	Z   = cvecP[2]; b = *Z;

	for(i=0; i < vdim; i++, L=*++X, a=*++Y, b=*++Z)
	{
		Y_Yo = (L + 16)/116;
		X_Xo = (a / 500) + Y_Yo;
		Z_Zo = Y_Yo - (b / 200);

		*X = pow(X_Xo, 3) * Xo;
		*Y = pow(Y_Yo, 3) * Yo;
		*Z = pow(Z_Zo, 3) * Zo;
	}

}


/****************************************************************
Name: hsl2rgb
Expanded Name: hsl to rgb
Parameters: <cvecP> - pointer to an array of normalized
band vectors
<vdim> - dimension of each vector (number of pixels)
Returns: nada
Description: Performs HSL to RGB color transformation. The resulting
transform will also be normalized to [0.0 ... 1.0]. 
Diagnostics: none
Credit(s): Gregory Hance
Southern Illinois University @ Edwardsville
****************************************************************/

static void hsl2rgb(float **cvecP, unsigned long vdim)
{
	float h, s, l, *r, *g, *b, v;
	register unsigned long i=0;
	int err_counter = 0;

	r = cvecP[0]; h = *r;
	g = cvecP[1]; s = *g;
	b = cvecP[2]; l = *b;

	for(; i < vdim; i++ ) {

		h=*r; s=*g; l=*b;
		v = (l <= 0.5) ? (l * (1.0 + s)) : (l + s - l * s);

		if (s == 0) *r = *g = *b = l; /* achromatic case */
		else {
			float m;
			float sv;
			int sextant;
			float fract, vsf, mid1, mid2;

			m = l*2 - v;
			sv = (v - m ) / v;
			if (h < 0.0) h += 1.0;
			h *= 6.0;
			sextant = (int) h;	
			fract = h - sextant;
			vsf = v * sv * fract;
			mid1 = m + vsf;
			mid2 = v - vsf;
			switch (sextant) {
			case 0: *r = v; *g = mid1; *b = m; break;
			case 1: *r = mid2; *g = v; *b = m; break;
			case 2: *r = m; *g = v; *b = mid1; break;
			case 3: *r = m; *g = mid2; *b = v; break;
			case 4: *r = mid1; *g = m; *b = v; break;
			case 5: *r = v; *g = m; *b = mid2; break;
			default: err_counter ++; break;
			}
		}
		++r; ++g; ++b;
	}
	if (err_counter != 0)
		fprintf(stderr,"hsl2rgb: bogus hue angle, total %d messages\n", err_counter);
}


/****************************************************************
Name: hsv2rgb
Expanded Name: hsv to rgb
Parameters: <cvecP> - pointer to an array of normalized
band vectors
<vdim> - dimension of each vector (number of pixels)
Returns: nada
Description: Performs HSV to RGB color transformation. The resulting
transform will also be normalized to [0.0 ... 1.0]. 
Diagnostics: none
Credit(s): Gregory Hance
Southern Illinois University @ Edwardsville
****************************************************************/

void hsv2rgb(float **cvecP, unsigned long vdim)
{
	int sextant;
	float fract, new1, new2, new3;
	float h, s, v, *r, *g, *b;
	register unsigned long i=0;
	int err_counter = 0;

	r = cvecP[0]; h = *r;
	g = cvecP[1]; s = *g;
	b = cvecP[2]; v = *b;

	for(; i < vdim; i++, h=*++r, s=*++g, v=*++b)
	{
		/* if saturation is zero then assume the hue is zero *
		* otherwise an error would occur that we would not *
		* be able to handle */

		if (s == 0.0 )
			*r = *g = *b = v;
		else
		{
			if (h < 0.0)
				h += 1.0;
			h *= 6.0;
			sextant = (int) h;
			fract = h - sextant;

			new1 = v * (1 - s);
			new2 = v * (1 - (s * fract));
			new3 = v * (1 - (s * (1 - fract)));

			switch (sextant)
			{
			case 0: *r = v; *g = new3; *b = new1;
				break;
			case 1: *r = new2; *g = v; *b = new1;
				break;
			case 2: *r = new1; *g = v; *b = new3;
				break;
			case 3: *r = new1; *g = new2; *b = v;
				break;
			case 4: *r = new3; *g = new1; *b = v;
				break;
			case 5: *r = v; *g = new1; *b = new2;
				break;
			default:
				err_counter ++;
				break;
			}
		}
	}
	if (err_counter != 0)
		fprintf(stderr,"hsv2rgb: bogus hue angle, total %d messages\n", err_counter);

}

/****************************************************************
Name: linxform
Expanded Name: linear transform
Parameters: <cvecP> - pointer to an array of band vectors
<no_of_vecs> - number of vectors
<vdim> - dimension of each vector (number of pixels)
<transmatrix> - transformation matrix
Returns: nada
Description: linearly transforms a set of band vectors <cvecP>
through a transformation matrix <transmatrix>. The
transformation matrix must be have a dimension of
<no_of_vecs> by <no_of_vecs>.
Diagnostics: none
Credit(s): Gregory Hance
Southern Illinois University @ Edwardsville
****************************************************************/

void linxform(float **cvecP, unsigned int no_of_vecs, unsigned int vdim,
	double **transmatrix)
{
	register int i=0, j, k;
	float *tP;
	double *dP;
	const char *fn = "linxform";

	fprintf(stderr, "%s: performing linear color transform...\n", fn);
	/*
	if( ... ) {
	fprintf(stderr, "%s-ERROR: transformation matrix must be %dx%d.\n", fn, no_of_vecs, no_of_vecs);
	return;
	}
	*/
	fprintf(stderr, "%s: transformation vectors being used:\n",fn);
	for ( j=0; j < no_of_vecs; j++ ) {
		fprintf(stderr, "%s: [t%d] = ",fn, j);
		dP = transmatrix[j];
		for( k=0; k < no_of_vecs; k++, dP++)
			fprintf(stderr, " %f(x%d) ", *dP, k);
		fprintf(stderr,"\n");
	}

	tP = (float *) malloc(no_of_vecs*sizeof(float));

	for(; i < vdim; i++) {
		(void) memset((char *)tP, 0, (size_t) no_of_vecs*sizeof(float));
		for (j=0; j < no_of_vecs; j++) {
			dP = transmatrix[j];
			for(k=0; k < no_of_vecs; k++, dP++)
				tP[j] += (float) (*dP * (*(cvecP[k] + i)));
		}
		for(k=0; k < no_of_vecs; k++)
			*(cvecP[k] + i) = tP[k];
	}

	free(tP);
}

/*
* rgb2yiq() 
*
* Description: Performs the RGB to YIQ transformation according to
* the following transformation matrix:
*  _     _                   _    _
* |Y|   |0.299   0.587   0.114|  |R|
* |I| = |0.596  -0.274  -0.322|  |G|
* |Q|   |0.211  -0.523   0.312|  |B|
*  -     -                   -    -
*
* When the parameter inv is not 0, the routine 
* performs the RGB to YIQ transformation according to
* the following transformation matrix:
*  _     _                   _    _
* |R|   |1.000   0.956   0.621|  |Y|
* |G| = |1.000  -0.273  -0.647|  |I|    
* |B|   |1.000  -1.104   1.701|  |Q|    
*  -     -                   -    -    
*
* Author: Arve Kjoelen 
* Initial Coding Date: 2/29/96 
*/

void rgb2yiq(Image *in, int inv) {
	register double **xfm=(double **)malloc(sizeof(double*)*3);
	register float **cvecP=(float **)malloc(sizeof(float *)*3); 
	xfm[0]=(double *)malloc(sizeof(double)*3);
	xfm[1]=(double *)malloc(sizeof(double)*3); 
	xfm[2]=(double *)malloc(sizeof(double)*3); 
	if(in->image_ptr[0]->data_type!=CVIP_FLOAT)
		(void)cast_Image(in, CVIP_FLOAT);

	cvecP[0]=(float *)in->image_ptr[0]->rptr[0];
	cvecP[1]=(float *)in->image_ptr[1]->rptr[0]; 
	cvecP[2]=(float *)in->image_ptr[2]->rptr[0]; 

	if(!inv) {
		xfm[0][0]=0.299; xfm[0][1]=0.587; xfm[0][2]=0.114; 
		xfm[1][0]=0.596; xfm[1][1]=-0.274; xfm[1][2]=-0.322;
		xfm[2][0]=0.211; xfm[2][1]=-0.523; xfm[2][2]=0.312;
	}
	else {
		xfm[0][0]=1.000; xfm[0][1]=0.956; xfm[0][2]=0.621;
		xfm[1][0]=1.000; xfm[1][1]=-0.273; xfm[1][2]=-0.647; 
		xfm[2][0]=1.000; xfm[2][1]=-1.104; xfm[2][2]=1.701; 
	}
	linearTrans_Image(cvecP, 3, in->image_ptr[0]->rows*in->image_ptr[0]->cols, xfm);

	free(xfm[0]);    
	free(xfm[1]);
	free(xfm[2]);
	free(xfm);
	free(cvecP);
}
