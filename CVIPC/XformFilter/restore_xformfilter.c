/*
 * Image Processing / Computer Vision Tool Project - Dr. Umbaugh, SIUE
 * restore_xformfilter.c
 * 
 * Description: Contains routines necessary to perform
 * an inverse filter.  The inverse filter is a Frequency Domain
 * Filter defined as follows:
 *
 *          G(u,v)
 * F(u,v) = ------
 *          H(u,v)
 *
 * Where F(u,v) is the Fourier Transform of the restored image;
 *       G(u,v) is the Fourier Transform of the degraded image; and
 *       H(u,v) is the Fourier Transform of the degradation function.
 *
 * Credits: Arve Kjoelen
 */
#ifndef WIN32
#include <values.h>
#else
#define MAXDOUBLE 1.7976931348623158E+308
#endif

#include "CVIPimage.h"
#include "CVIPtransform.h"
#include "CVIPxformfilter.h"
#include "CVIPdef.h"
#include "CVIParithlogic.h"

/*
 * Routine Name: restor_filter_Setup()
 *
 * Description:
 *	Setup function for all restoration routines.  An equation for these
 *	routines, parameterized in terms of gamma and alpha, is:
 *
 *              _       _ alpha     _                                _ (1-alpha)
 *             | H*(u,v) |         |                  H*(u,v)         |
 * FIL=G(u,v)* | ------- |         | -------------------------------- |
 *             |        2|         |        2                         |
 *             ||H(u,v)| |         ||H(u,v)| + gamma(Pn(u,v)/Pf(u,v)) |
 *              -       -           -                                -
 *
 * Variables passed: 
 *	Image *degraded - pointer to degraded image ( H(u,v) ).
 *	Image *degradation_fn - pointer to degradation function. Ideally, 
 *	we want the inverse of this (G(u,v) )
 *	Image *noise_fn - pointer to the noise function. (Pn(u,v) is the power 
 *	spectrum of this.
 *	float gamma - gamma in the above equation restr. to the interval [0,1].
 *	float alpha - alpha in the above equation. Restr. to the interval [0,1].
 *	int filter - filter to be performed:
 *		0 = Inverse Filter	(obtained by alpha=0 and gamma=0 above)
 *		1 = Simple Wiener Filter (obtained by alpha=0 and substituting
 *		    a constant, k, for [gamma(Pn(u,v)/Pf(u,v)]
 *		    above.  This constant is passed as gamma).
 *		2 = Wiener Filter (obtained by alpha=0 and gamma=1)
 *		3 = Parametric Wiener Filter    (obtained by alpha=0 above).
 *		4 = Power Spectrum Equalization (alpha=0.5 and gamma=1)
 *		5 = Least-squares restoration   (obtained by letting alpha=0 and
 *		    replacing Pn(u,v)/Pf(u,v) with the Fourier Transform
 *	 	    of the highpass mask
 *
 *							 0	-1	 0
 *
 *							-1	 4	-1
 *
 *							 0	-1	 0
 *
 *		    this mask is zero-padded to the size of
 *		    the degraded image.
 *		6 = Geometric Mean Filter (the parameterized equation above)
 *		
 *	int choice - Specifies how to handle denominator=0 
 *	int cutoff - specifies a cutoff frequency for filtering
 *
 *	NOTE: The above images may be passed as either spatial-domain images or
 *	      transformed (w/FFT) images.  history_check() is used to determine
 *	      whether the images are in the transform domain.  the FFT is per-
 *	      formed as needed if the passed images are in the spatial domain.
 *
 */

/*
 * function declarations
 */
static struct history	*p_CreateHistory(PROGRAMS,int,CVIP_TYPE *);
static int		b_Preprocess(int,Image **);
static Image		*geometric_mean_filters(Image *,Image *,Image *,Image *,float,float,int,int);

static struct history	*p_CreateHistory(	PROGRAMS		ftag,
						int		dsize,
						CVIP_TYPE	*dtype)
{
	struct history	*output;
	int		count;

	output = (struct history *)malloc(sizeof(struct history));
	if(output != NULL)
	{
		output->ftag = ftag;
		output->next = NULL;
		output->packetP = (PACKET *)malloc(sizeof(PACKET));
		if(output->packetP != NULL)
		{
			output->packetP->dsize = dsize;
			output->packetP->dtype = (CVIP_TYPE *)malloc((size_t)dsize*sizeof(CVIP_TYPE));
			if(output->packetP->dtype != NULL)
			{
				for(count = 0;count < dsize;count++)
				output->packetP->dtype[count] = dtype[count];

				output->packetP->dptr = (void **)malloc((size_t)dsize*sizeof(void *));
				if(output->packetP->dptr != NULL)
				{
					for(count = 0;count < dsize;count++)
					{
						if(dtype[count] == CVIP_BYTE)
						output->packetP->dptr[count] = malloc(sizeof(unsigned char));
						else
						if(dtype[count] == CVIP_SHORT)
						output->packetP->dptr[count] = malloc(sizeof(short));
						else
						if(dtype[count] == CVIP_INTEGER)
						output->packetP->dptr[count] = malloc(sizeof(int));
						else
						if(dtype[count] == CVIP_FLOAT)
						output->packetP->dptr[count] = malloc(sizeof(float));
						else
						if(dtype[count] == CVIP_DOUBLE)
						output->packetP->dptr[count] = malloc(sizeof(double));
						else
						break;
						if(output->packetP->dptr[count] == NULL)
						break;
					}
					if(count == dsize)
					{
						return(output);
					}
					while(count)
					{
						count--;
						free(output->packetP->dptr[count]);
					}
					free(output->packetP->dptr);
				}
				free(output->packetP->dtype);
			}
			free(output->packetP);
		}
		free(output);
	}
}

static int	b_Preprocess(	int	total,
				Image	**input)
{
	unsigned	count;
	unsigned	block_size;
	struct history	*stuff;
	CVIP_TYPE	fft_param[1] = {CVIP_INTEGER};
	CVIP_TYPE	datatype;

	block_size = getNoOfRows_Image(input[0]);
	if(block_size < getNoOfCols_Image(input[0]))
	block_size = getNoOfCols_Image(input[0]);
	for(count = 1;count < total;count++)
	{
		if(block_size < getNoOfRows_Image(input[0]))
		block_size = getNoOfRows_Image(input[0]);
		if(block_size < getNoOfCols_Image(input[0]))
		block_size = getNoOfCols_Image(input[0]);
	}
	for(count = 1;count < block_size;count *= 2);
	block_size = count;

	for(count = 0;count < total;count++)
	if(!history_check(FFT,input[count]))
	{
		input[count] = fft_transform(input[count],block_size);
		if(input[count] == NULL)
		break;
		stuff = p_CreateHistory(FFT,1,fft_param);
		if(stuff == NULL)
		break;
		((int *)(stuff->packetP->dptr[0]))[0] = block_size;
		history_add(input[count],stuff);
	}
	if(count != total)
	{
		for(count = 0;count < total;count++)
		if(input[count] != NULL)
		delete_Image(input[count]);

		return(0);
	}

	datatype = getDataType_Image(input[0]);
	for(count = 1;count < total;count++)
	if(datatype < getDataType_Image(input[0]))
	datatype = getDataType_Image(input[0]);
	if(datatype < CVIP_FLOAT)
	datatype = CVIP_FLOAT;

	for(count = 0;count < total;count++)
	{
		if(datatype != getDataType_Image(input[count]))
		cast_Image(input[count],datatype);
		if(datatype != getDataType_Image(input[count]))
		break;
	}
	if(count != total)
	{
		for(count = 0;count < total;count++)
		if(input[count] != NULL)
		delete_Image(input[count]);

		return(0);
	}
	return(1);
}

static Image	*geometric_mean_filters(	Image	*degr,
						Image	*degr_fn,
						Image	*p_noise,
						Image	*p_orig,
						float	gamma,
						float	alpha,
						int	choice,
						int	cutoff)
{
	unsigned	rowCount,colCount,bandCount;
	double		rR,iR;
	double		rH,iH;
	double		rD,iD;
	double		rSo,iSo;
	double		rSn,iSn;
	double		Rdc,R;
	double		den1,den2;
	double		dr,dc;
	Image		*inputs[4];
	Image		*output;
	CVIP_TYPE	datatype;
	unsigned	rows,cols,bands;

	void		*p_rH,*p_iH;
	void		*p_rD,*p_iD;
	void		*p_rSn,*p_iSn;
	void		*p_rSo,*p_iSo;
	void		*p_rI,*p_iI;

	inputs[0] = degr;
	inputs[1] = degr_fn;
	inputs[2] = p_noise;
	inputs[3] = p_orig;
	if(!b_Preprocess(4,inputs))
	return(NULL);
	degr = inputs[0];
	degr_fn = inputs[1];
	p_noise = inputs[2];
	p_orig = inputs[3];

	output = duplicate_Image(degr);
	if(output == NULL)
	{
		delete_Image(degr);
		delete_Image(degr_fn);
		delete_Image(p_noise);
		delete_Image(p_orig);
		return(NULL);
	}
	rows = getNoOfRows_Image(output);
	cols = getNoOfCols_Image(output);
	bands = getNoOfBands_Image(output);
	datatype = getDataType_Image(output);

	for(bandCount = 0;bandCount < bands;bandCount++)
	{
		if(datatype == CVIP_FLOAT)
		{
			rH = getRealPixel_Image(degr_fn,float,rows/2,cols/2,bandCount);
			iH = getImagPixel_Image(degr_fn,float,rows/2,cols/2,bandCount);

			rSo = getRealPixel_Image(p_orig,float,rows/2,cols/2,bandCount);
			iSo = getImagPixel_Image(p_orig,float,rows/2,cols/2,bandCount);

			rSn = getRealPixel_Image(p_noise,float,rows/2,cols/2,bandCount);
			iSn = getImagPixel_Image(p_noise,float,rows/2,cols/2,bandCount);
		}
		else
		{
			rH = getRealPixel_Image(degr_fn,double,rows/2,cols/2,bandCount);
			iH = getImagPixel_Image(degr_fn,double,rows/2,cols/2,bandCount);

			rSo = getRealPixel_Image(p_orig,double,rows/2,cols/2,bandCount);
			iSo = getImagPixel_Image(p_orig,double,rows/2,cols/2,bandCount);

			rSn = getRealPixel_Image(p_noise,double,rows/2,cols/2,bandCount);
			iSn = getImagPixel_Image(p_noise,double,rows/2,cols/2,bandCount);
		}
		rH /= rows;
		iH /= rows;

		rSo = rSo*rSo+iSo*iSo;
		rSn = rSn*rSn+iSn*iSn;
		if(rSo == 0)
		{
		/*	No signal power.  Set the gain to 0. */
			Rdc = 0;
		}
		else
		{
			rR = rH;
			iR = -iH;
			den1 = rH*rH+iH*iH;
			den2 = den1+gamma*(rSn/rSo);
			den1 = pow(den1,alpha);
			den2 = pow(den2,1.0-alpha);
			den1 *= den2;
			if(den1 != 0)
			{
				rR /= den1;
				iR /= den1;
				Rdc = sqrt(rR*rR+iR*iR);
			}
			else
			{
				Rdc = MAXDOUBLE;
			}
		}
		Rdc *= (double)choice;
		for(rowCount = 0;rowCount < rows;rowCount++)
		{
			p_rI = getRealRow_Image(output,rowCount,bandCount);
			p_rH = getRealRow_Image(degr_fn,rowCount,bandCount);
			p_rD = getRealRow_Image(degr,rowCount,bandCount);
			p_rSn = getRealRow_Image(p_noise,rowCount,bandCount);
			p_rSo = getRealRow_Image(p_orig,rowCount,bandCount);

			p_iI = getImagRow_Image(output,rowCount,bandCount);
			p_iH = getImagRow_Image(degr_fn,rowCount,bandCount);
			p_iD = getImagRow_Image(degr,rowCount,bandCount);
			p_iSn = getImagRow_Image(p_noise,rowCount,bandCount);
			p_iSo = getImagRow_Image(p_orig,rowCount,bandCount);

			for(colCount = 0;colCount < cols;colCount++)
			{
				if(datatype == CVIP_FLOAT)
				{
					rH = *(float *)p_rH;
					iH = *(float *)p_iH;
					rD = *(float *)p_rD;
					iD = *(float *)p_iD;
					rSo = *(float *)p_rSo;
					iSo = *(float *)p_iSo;
					rSn = *(float *)p_rSn;
					iSn = *(float *)p_iSn;
				}
				else
				{
					rH = *(double *)p_rH;
					iH = *(double *)p_iH;
					rD = *(double *)p_rD;
					iD = *(double *)p_iD;
					rSo = *(double *)p_rSo;
					iSo = *(double *)p_iSo;
					rSn = *(double *)p_rSn;
					iSn = *(double *)p_iSn;
				}

				rH /= rows;
				iH /= rows;
				rD /= rows;
				iD /= rows;

				rSo = rSo*rSo+iSo*iSo;
				rSn = rSn*rSn+iSn*iSn;
				if(rSo == 0)
				{
				/*	No signal power.  Set gain to 0. */
					rR = 0;
					iR = 0;
				}
				else
				{
					rR = rH;
					iR = -iH;
					den1 = rH*rH+iH*iH;
					den2 = den1+gamma*(rSn/rSo);
					den1 = pow(den1,alpha);
					den2 = pow(den2,1.0-alpha);
					den1 *= den2;
					if(den1 != 0)
					{
						rR /= den1;
						iR /= den1;
						if(Rdc > 0)
						{
						R = sqrt(rR*rR+iR*iR);
						if(R > Rdc)
						{
							rR /= (Rdc/R);
							iR /= (Rdc/R);
						}
						}
					}
					else
					{
						if(Rdc > 0)
						rR = Rdc;
						else
						rR = MAXDOUBLE;
						iR = 0;
					}
				}
				if(cutoff > 0)
				{
					dr = (double)rowCount;
					dr -= (double)rows/2.0;
					dc = (double)colCount;
					dc -= (double)cols/2.0;
					if(sqrt(dr*dr+dc*dc) > (double)cutoff)
					{
						rR = 0;
						iR = 0;
					}
				}
				if(datatype == CVIP_FLOAT)
				{
					*((float *)p_rI) = (float)((rR*rD-iR*iD)*(double)rows);
					*((float *)p_iI) = (float)((rR*iD+iR*rD)*(double)rows);

					p_rI = (void *)(((float *)p_rI)+1);
					p_rH = (void *)(((float *)p_rH)+1);
					p_rD = (void *)(((float *)p_rD)+1);
					p_rSn = (void *)(((float *)p_rSn)+1);
					p_rSo = (void *)(((float *)p_rSo)+1);

					p_iI = (void *)(((float *)p_iI)+1);
					p_iH = (void *)(((float *)p_iH)+1);
					p_iD = (void *)(((float *)p_iD)+1);
					p_iSn = (void *)(((float *)p_iSn)+1);
					p_iSo = (void *)(((float *)p_iSo)+1);
				}
				else
				{
					*((double *)p_rI) = (double)((rR*rD-iR*iD)*(double)rows);
					*((double *)p_iI) = (double)((rR*iD+iR*rD)*(double)rows);

					p_rI = (void *)(((double *)p_rI)+1);
					p_rH = (void *)(((double *)p_rH)+1);
					p_rD = (void *)(((double *)p_rD)+1);
					p_rSn = (void *)(((double *)p_rSn)+1);
					p_rSo = (void *)(((double *)p_rSo)+1);

					p_iI = (void *)(((double *)p_iI)+1);
					p_iH = (void *)(((double *)p_iH)+1);
					p_iD = (void *)(((double *)p_iD)+1);
					p_iSn = (void *)(((double *)p_iSn)+1);
					p_iSo = (void *)(((double *)p_iSo)+1);
				}
			}
		}
	}
	delete_Image(degr);
	delete_Image(degr_fn);
	delete_Image(p_noise);
	delete_Image(p_orig);
	return(output);
}
/*
 * Routine Name: simple_wiener()
 *
 * Description: 
 * 	Performs the operations needed to perform a simple Wiener Filter
 *	Denoting the degraded image by G(u,v), and using
 *	H(u,v) for the degradation function Image, this function calculates
 *		                    2
 *                          |H(u,v)|
 *        G(u,v)    *    --------------
 *                               2
 *                       |H(u,v)|   + k
 *
 * Variables Passed:
 *	Image *degr - Contains the degraded image.
 *	Image *degr_fn - Contains the degradation function.
 *	float k - constant.
 *
 * Diagnostics:  
 *    	- This function does its own memory management.  if you'd
 *    	like to keep you images intact, make a copy of them before you pass
 * 	them to this function.
 *	- The function tries to determine whether an FFT has been performed
 *	on the passed images.  If not, the function will perform the FFT.
 *	- the function will also extend the sizes of the passed images as best
 *	it can when they are of unequal size.
 *
 * Author: Arve Kjoelen, SIUE
 *
 */
Image	*simple_wiener(	Image	*degr,
			Image	*degr_fn,
			float	k)
{
	unsigned	rowCount,colCount,bandCount;
	double		rR,iR;
	double		rH,iH;
	double		rD,iD;
	double		den1;
	CVIP_TYPE	wiener_params[1] = {CVIP_FLOAT};
	struct history	*stuff;
	Image		*inputs[2];
	Image		*output;
	CVIP_TYPE	datatype;
	unsigned	rows,cols,bands;

	void		*p_rH,*p_iH;
	void		*p_rD,*p_iD;
	void		*p_rI,*p_iI;

	inputs[0] = degr;
	inputs[1] = degr_fn;
	if(!b_Preprocess(2,inputs))
	return(NULL);
	degr = inputs[0];
	degr_fn = inputs[1];

	output = duplicate_Image(degr);
	if(output == NULL)
	{
		delete_Image(degr);
		delete_Image(degr_fn);
		return(NULL);
	}
	rows = getNoOfRows_Image(output);
	cols = getNoOfCols_Image(output);
	bands = getNoOfBands_Image(output);
	datatype = getDataType_Image(output);

	for(bandCount = 0;bandCount < bands;bandCount++)
	{
		for(rowCount = 0;rowCount < rows;rowCount++)
		{
		p_rI = getRealRow_Image(output,rowCount,bandCount);
		p_rH = getRealRow_Image(degr_fn,rowCount,bandCount);
		p_rD = getRealRow_Image(degr,rowCount,bandCount);

		p_iI = getImagRow_Image(output,rowCount,bandCount);
		p_iH = getImagRow_Image(degr_fn,rowCount,bandCount);
		p_iD = getImagRow_Image(degr,rowCount,bandCount);

		for(colCount = 0;colCount < cols;colCount++)
		{
			if(datatype == CVIP_FLOAT)
			{
				rH = *(float *)p_rH;
				iH = *(float *)p_iH;
				rD = *(float *)p_rD;
				iD = *(float *)p_iD;
			}
			else
			{
				rH = *(double *)p_rH;
				iH = *(double *)p_iH;
				rD = *(double *)p_rD;
				iD = *(double *)p_iD;
			}

			rH /= rows;
			iH /= rows;
			rD /= rows;
			iD /= rows;

			rR = rH;
			iR = -iH;
			den1 = rH*rH+iH*iH+k;
			if(den1 != 0)
			{
				rR /= den1;
				iR /= den1;
			}
			else
			{
				rR = MAXDOUBLE;
				iR = 0;
			}
			if(datatype == CVIP_FLOAT)
			{
				*((float *)p_rI) = (float)((rR*rD-iR*iD)*(double)rows);
				*((float *)p_iI) = (float)((rR*iD+iR*rD)*(double)rows);

				p_rI = (void *)(((float *)p_rI)+1);
				p_rH = (void *)(((float *)p_rH)+1);
				p_rD = (void *)(((float *)p_rD)+1);

				p_iI = (void *)(((float *)p_iI)+1);
				p_iH = (void *)(((float *)p_iH)+1);
				p_iD = (void *)(((float *)p_iD)+1);
			}
			else
			{
				*((double *)p_rI) = (double)((rR*rD-iR*iD)*(double)rows);
				*((double *)p_iI) = (double)((rR*iD+iR*rD)*(double)rows);

				p_rI = (void *)(((double *)p_rI)+1);
				p_rH = (void *)(((double *)p_rH)+1);
				p_rD = (void *)(((double *)p_rD)+1);

				p_iI = (void *)(((double *)p_iI)+1);
				p_iH = (void *)(((double *)p_iH)+1);
				p_iD = (void *)(((double *)p_iD)+1);
			}
		}
		}
	}
	delete_Image(degr);
	delete_Image(degr_fn);
/*	Add history information to output. */
	stuff = p_CreateHistory(SIMPLE_WIENER,1,wiener_params);
	if(stuff != NULL)
	{
		((float *)(stuff->packetP->dptr[0]))[0] = k;

		history_add(output,stuff);
		return(output);
	}
	delete_Image(output);
	return(NULL);
}

/*
 * Routine name least_squares()
 *
 * Description: see header.  The least_squares_filter() routine must, because
 * of its potential for zero in the denominator, give the user the option
 * of performing some additional hanky-panky when division blows up.
 * The function takes as its arguments:
 *    Image *degr 	- pointer to the degraded image.
 *    Image *degr_fn 	- pointer to the degradation function.
 *    Image *snr_approx - pointer to image that approximates Pn(u,v)/Pf(u,v).
 *                        In many practical applications, this is the FFT
 *			  of the highpass mask specified at the top of this
 *			  file.  However, any image may be passed.
 *    float gamma	- gamma in equation above.
 *
 * Diagnostics:  
 *    	- This function does its own memory management.  if you'd
 *    	like to keep you images intact, make a copy of them before you pass
 * 	them to this function.
 *	- The function tries to determine whether an FFT has been performed
 *	on the passed images.  If not, the function will perform the FFT.
 *	- the function will also extend the sizes of the passed images as best
 *	it can when they are of unequal size.
 *
 * Returns: Pointer to the restored image (in the frequency domain).
 * 
 * Author: Arve Kjoelen, SIUE
 */
Image	*least_squares(	Image	*degr,
			Image	*degr_fn,
			Image	*snr_approx,
			float	gamma,
			int	choice,
			int	cutoff)
{
	CVIP_TYPE	ls_params[3] = {CVIP_FLOAT,CVIP_INTEGER,CVIP_INTEGER};
	struct history	*stuff;

	unsigned	rowCount,colCount,bandCount;
	double		rR,iR;
	double		rH,iH;
	double		rD,iD;
	double		rSo,iSo;
	double		Rdc,R;
	double		den1;
	double		dr,dc;
	Image		*inputs[3];
	Image		*output;
	CVIP_TYPE	datatype;
	unsigned	rows,cols,bands;

	void		*p_rH,*p_iH;
	void		*p_rD,*p_iD;
	void		*p_rSo,*p_iSo;
	void		*p_rI,*p_iI;

	inputs[0] = degr;
	inputs[1] = degr_fn;
	inputs[2] = snr_approx;
	if(!b_Preprocess(3,inputs))
	return(NULL);
	degr = inputs[0];
	degr_fn = inputs[1];
	snr_approx = inputs[2];

	output = duplicate_Image(degr);
	if(output == NULL)
	{
		delete_Image(degr);
		delete_Image(degr_fn);
		delete_Image(snr_approx);
		return(NULL);
	}
	rows = getNoOfRows_Image(output);
	cols = getNoOfCols_Image(output);
	bands = getNoOfBands_Image(output);
	datatype = getDataType_Image(output);

	for(bandCount = 0;bandCount < bands;bandCount++)
	{
		if(datatype == CVIP_FLOAT)
		{
			rH = getRealPixel_Image(degr_fn,float,rows/2,cols/2,bandCount);
			iH = getImagPixel_Image(degr_fn,float,rows/2,cols/2,bandCount);

			rSo = getRealPixel_Image(snr_approx,float,rows/2,cols/2,bandCount);
			iSo = getImagPixel_Image(snr_approx,float,rows/2,cols/2,bandCount);
		}
		else
		{
			rH = getRealPixel_Image(degr_fn,double,rows/2,cols/2,bandCount);
			iH = getImagPixel_Image(degr_fn,double,rows/2,cols/2,bandCount);

			rSo = getRealPixel_Image(snr_approx,double,rows/2,cols/2,bandCount);
			iSo = getImagPixel_Image(snr_approx,double,rows/2,cols/2,bandCount);
		}
		rH /= rows;
		iH /= rows;
		rSo /= rows;
		iSo /= rows;

		rR = rH;
		iR = -iH;
		den1 = rH*rH+iH*iH+gamma*(rSo*rSo+iSo*iSo);
		if(den1 != 0)
		{
			rR /= den1;
			iR /= den1;
			Rdc = sqrt(rR*rR+iR*iR);
		}
		else
		{
			Rdc = MAXDOUBLE;
		}
		Rdc *= (double)choice;
		for(rowCount = 0;rowCount < rows;rowCount++)
		{
			p_rI = getRealRow_Image(output,rowCount,bandCount);
			p_rH = getRealRow_Image(degr_fn,rowCount,bandCount);
			p_rD = getRealRow_Image(degr,rowCount,bandCount);
			p_rSo = getRealRow_Image(snr_approx,rowCount,bandCount);

			p_iI = getImagRow_Image(output,rowCount,bandCount);
			p_iH = getImagRow_Image(degr_fn,rowCount,bandCount);
			p_iD = getImagRow_Image(degr,rowCount,bandCount);
			p_iSo = getImagRow_Image(snr_approx,rowCount,bandCount);

			for(colCount = 0;colCount < cols;colCount++)
			{
				if(datatype == CVIP_FLOAT)
				{
					rH = *(float *)p_rH;
					iH = *(float *)p_iH;
					rD = *(float *)p_rD;
					iD = *(float *)p_iD;
					rSo = *(float *)p_rSo;
					iSo = *(float *)p_iSo;
				}
				else
				{
					rH = *(double *)p_rH;
					iH = *(double *)p_iH;
					rD = *(double *)p_rD;
					iD = *(double *)p_iD;
					rSo = *(double *)p_rSo;
					iSo = *(double *)p_iSo;
				}

				rH /= rows;
				iH /= rows;
				rD /= rows;
				iD /= rows;
				rSo /= rows;
				iSo /= rows;

				rR = rH;
				iR = -iH;
				den1 = rH*rH+iH*iH+gamma*(rSo*rSo+iSo*iSo);
				if(den1 != 0)
				{
					rR = rH/den1;
					iR = -iH/den1;
					if(Rdc > 0)
					{
					R = sqrt(rR*rR+iR*iR);
					if(R > Rdc)
					{
						rR /= (Rdc/R);
						iR /= (Rdc/R);
					}
					}
				}
				else
				{
					if(Rdc > 0)
					rR = Rdc;
					else
					rR = MAXDOUBLE;
					iR = 0;
				}
				if(cutoff > 0)
				{
					dr = (double)rowCount;
					dr -= (double)rows/2.0;
					dc = (double)colCount;
					dc -= (double)cols/2.0;
					if(sqrt(dr*dr+dc*dc) > (double)cutoff)
					{
						rR = 0;
						iR = 0;
					}
				}
				if(datatype == CVIP_FLOAT)
				{
					*((float *)p_rI) = (float)((rR*rD-iR*iD)*(double)rows);
					*((float *)p_iI) = (float)((rR*iD+iR*rD)*(double)rows);

					p_rI = (void *)(((float *)p_rI)+1);
					p_rH = (void *)(((float *)p_rH)+1);
					p_rD = (void *)(((float *)p_rD)+1);
					p_rSo = (void *)(((float *)p_rSo)+1);

					p_iI = (void *)(((float *)p_iI)+1);
					p_iH = (void *)(((float *)p_iH)+1);
					p_iD = (void *)(((float *)p_iD)+1);
					p_iSo = (void *)(((float *)p_iSo)+1);
				}
				else
				{
					*((double *)p_rI) = (double)((rR*rD-iR*iD)*(double)rows);
					*((double *)p_iI) = (double)((rR*iD+iR*rD)*(double)rows);

					p_rI = (void *)(((double *)p_rI)+1);
					p_rH = (void *)(((double *)p_rH)+1);
					p_rD = (void *)(((double *)p_rD)+1);
					p_rSo = (void *)(((double *)p_rSo)+1);

					p_iI = (void *)(((double *)p_iI)+1);
					p_iH = (void *)(((double *)p_iH)+1);
					p_iD = (void *)(((double *)p_iD)+1);
					p_iSo = (void *)(((double *)p_iSo)+1);
				}
			}
		}
	}
	delete_Image(degr);
	delete_Image(degr_fn);
	delete_Image(snr_approx);
/*	Add history information to output. */
	stuff = p_CreateHistory(LEAST_SQUARES,3,ls_params);
	if(stuff != NULL)
	{
		((float *)(stuff->packetP->dptr[0]))[0] = gamma;
		((int *)(stuff->packetP->dptr[1]))[0] = choice;
		((int *)(stuff->packetP->dptr[2]))[0] = cutoff;

		history_add(output,stuff);
		return(output);
	}
	delete_Image(output);
	return(NULL);
}
/*
 * Routine Name: wiener()
 *
 * Description:
 *	The Wiener Filter is described in the header of this file.
 *	This function implements a wiener filter from the parameters
 * 	passed to it (G,H,Pn,Pf).  This routine may be used to implement
 *	a parametric wiener filter by multiplying Pn by gamma before
 *	calling this function (again, see equation at top of file).
 * Diagnostics:
 *    	- This function does its own memory management.  if you'd
 *    	like to keep you images intact, make a copy of them before you pass
 * 	them to this function.
 *	- The function tries to determine whether an FFT has been performed
 *	on the passed images.  If not, the function will perform the FFT.
 *	- The function will also extend the sizes of the passed images as best
 *	it can when they are of unequal size.
 *      - The input images are assumed to be spatial-domain if no
 *	FFT is detected in the image history.  This is especially
 *	important to note for the power images.
 *	See also comments in the code for other diagnostics.
 *
 * Author: Arve Kjoelen
 *
 * Date: 11/01/96
 *
 */
Image	*wiener(	Image	*degr,
			Image	*degr_fn,
			Image	*p_noise,
			Image	*p_orig,
			int	choice,
			int	cutoff)
{
	CVIP_TYPE	wiener_params[2] = {CVIP_INTEGER,CVIP_INTEGER};
	struct history	*stuff;
	Image		*output;

	output = geometric_mean_filters(degr,degr_fn,p_noise,p_orig,1,0,choice,cutoff);
	if(output == NULL)
	return(NULL);

/*	Add history information to output. */
	stuff = p_CreateHistory(WIENER_FILTER,2,wiener_params);
	if(stuff != NULL)
	{
		((int *)(stuff->packetP->dptr[0]))[0] = choice;
		((int *)(stuff->packetP->dptr[1]))[0] = cutoff;

		history_add(output,stuff);
		return(output);
	}
	delete_Image(output);
	return(NULL);
}
/*
 * Routine name: parametric_wiener()
 * Description: Short and sweet setup routine which uses 
 * 		wiener() to do all the work.
 *		parametric_wiener takes the same arguments as
 *		does wiener(), and also takes a floating-
 *		point value for 'gamma'.  It then multiplies
 *		p_noise by gamma before calling wiener().
 *		The only trick here is to scale by the square root
 *		of gamma if our noise power is not in the frequency
 *		domain, since we will later square p_noise.
 *
 * Author: Arve Kjoelen, Wed Nov 20 15:36:06 CST 1996
 */
Image	*parametric_wiener(	Image	*degr,
				Image	*degr_fn,
				Image	*p_noise,
				Image	*p_orig,
				float	gamma,
				int	choice,
				int	cutoff)
{
	CVIP_TYPE	wiener_params[3] = {CVIP_FLOAT,CVIP_INTEGER,CVIP_INTEGER};
	struct history	*stuff;
	Image		*output;

	output = geometric_mean_filters(degr,degr_fn,p_noise,p_orig,gamma,0,choice,cutoff);
	if(output == NULL)
	return(NULL);

/*	Add history information to output. */
	stuff = p_CreateHistory(PARAMETRIC_WIENER,3,wiener_params);
	if(stuff != NULL)
	{
		((float *)(stuff->packetP->dptr[0]))[0] = gamma;
		((int *)(stuff->packetP->dptr[1]))[0] = choice;
		((int *)(stuff->packetP->dptr[2]))[0] = cutoff;

		history_add(output,stuff);
		return(output);
	}
	delete_Image(output);
	return(NULL);
}
/*
 * Routine name: power_spect_eq()
 * Description: Setup routine which calls pse_n_gm_filter().
 * 		passes a 1 to pse_n_gm_filter, indicating that
 *		an alpha=0.5 should be assumed.
 *
 * Author: Arve Kjoelen, Wed Nov 27 10:41:00 CST 1996
 */
Image	*power_spect_eq(	Image	*degr,
				Image	*degr_fn,
				Image	*p_noise,
				Image	*p_orig,
				int	choice,
				int	cutoff)
{
	CVIP_TYPE	pse_params[2] = {CVIP_INTEGER,CVIP_INTEGER};
	struct history	*stuff;
	Image		*output;

	output = geometric_mean_filters(degr,degr_fn,p_noise,p_orig,1,0.5,choice,cutoff);
	if(output == NULL)
	return(NULL);

/*	Add history information to output. */
	stuff = p_CreateHistory(POWER_SPECT_EQUALIZE,2,pse_params);
	if(stuff != NULL)
	{
		((int *)(stuff->packetP->dptr[0]))[0] = choice;
		((int *)(stuff->packetP->dptr[1]))[0] = cutoff;

		history_add(output,stuff);
		return(output);
	}
	delete_Image(output);
	return(NULL);
}
/*
 * Routine name: pse_n_gm_filter()
 * Description: Setup routine which uses 
 * 		wiener() to do most work.
 *		pse_n_gm_filter() takes the same arguments as
 *		does wiener().  The difference between the two
 *		is that pse_n_gm_filter uses alpha!=1, and so
 *		needs to do some extra work to compute a root
 *		of what is returned by wiener().  pse_n_gm_filter()
 *		is passed a number which indicates which root to calculate.
 *		when this number is :
 *		1 -> calculates square root, so equivalent to alpha=0.5.
 *		2 -> calculates cube root, so equivalent to alpha=1/3.
 *		3 -> equivalent to alpha=2/3.
 *		4 -> equivalent to alpha=1/9.
 *		5 -> equivalent to alpha=1/4.
 *		6 -> equivalent to alpha=1/8.
 *		7 -> equivalent to alpha=1/6.
 *		8 -> equivalent to alpha=5/6.
 *
 *	Note: pse_n_gm_filter represents Power_Spectrum_Equalization and
 *	      Geometric_Mean_Filter, since it may be used to implement both.
 *
 *
 * Author: Arve Kjoelen, Wed Nov 27 10:41:00 CST 1996
 */


/*
 * Routine name: geometric_mean()
 * Description: Setup routine which uses 
 * 		wiener() to do most work.
 *		geometric_mean takes the same arguments as
 *		does wiener(), and also takes a floating-
 *		point value for 'gamma'.  It then multiplies
 *		p_noise by gamma before calling wiener().
 *		The only trick here is to scale by the square root
 *		of gamma if our noise power is not in the frequency
 *		domain, since we will later square p_noise.
 *		Also note that power_spect_eq() assumes alpha=0.5,
 *		and needs to do some extra work to compute the square root
 *		of what is returned by wiener().  For now, the
 *		value of alpha is fixed at 0.5, since it will take some time
 *		to code a routine that computes an arbitrary root of
 *		a complex number.
 *
 * Author: Arve Kjoelen, Wed Nov 27 10:41:00 CST 1996
 */
Image	*geometric_mean(	Image	*degr,
				Image	*degr_fn,
				Image	*p_noise,
				Image	*p_orig,
				float	gamma,
				float	alpha,
				int	choice,
				int	cutoff)
{
	CVIP_TYPE	geo_params[4] = {CVIP_FLOAT,CVIP_FLOAT,CVIP_INTEGER,CVIP_INTEGER};
	struct history	*stuff;
	Image		*output;

	output = geometric_mean_filters(degr,degr_fn,p_noise,p_orig,gamma,alpha,choice,cutoff);
	if(output == NULL)
	return(NULL);

/*	Add history information to output. */
	stuff = p_CreateHistory(GEOMETRIC_MEAN,4,geo_params);
	if(stuff != NULL)
	{
		((float *)(stuff->packetP->dptr[0]))[0] = gamma;
		((float *)(stuff->packetP->dptr[1]))[0] = alpha;
		((int *)(stuff->packetP->dptr[2]))[0] = choice;
		((int *)(stuff->packetP->dptr[3]))[0] = cutoff;

		history_add(output,stuff);
		return(output);
	}
	delete_Image(output);
	return(NULL);
}

/*
 * Routine name: idealFilter_Matrix.
 *
 * Description: Creates a "filter matrix" - a matrix of selectable
 * size consisting of 1s and 0s - the zeros are all located outside
 * a user-selectable radius.
 *
 * Credits: Greg Hance, Arve Kjoelen
 */
/*
 * Routine Name: inverse_xformfilter
 * 
 * Description: Setup function for Inverse Filter.  Checks
 * input images and performs FFT on them if necessary, automatically
 * extending their sizes (zero-padding). Asks the user how to treat
 * occurences of 0 in the denominator.  Also asks whether optional
 * 'filtering' should be done, wherein F(u,v) is set to 0 when
 * sqrt(u*u + v*v) is outside a certain radius. 
 *
 * The function is also a setup function for a simplified Wiener
 * filter, in which the ratio of the noise power to the original
 * image power is approximated by a constant K.  If the Wiener filter
 * is desired, the function is passed a 1 for the parameter xform.
 *
 * Parameters passed: 	imgP, which will hold the result.
 *			numP, the numerator.
 *			denP, the denominator.
 *
 * History information for inverse filter:
 * parameter #1 = filter cutoff.
 * parameter #2 = method (1: F(u,v)=G(u,v) when H(u,v)=0
 *			  2: F(u,v)=0      when H(u,v)=0)
 */
Image	*inverse_xformfilter(	Image	*numP,
				Image	*denP,
				int	choice,
				float	cutoff)
{
	CVIP_TYPE	ls_params[2] = {CVIP_INTEGER,CVIP_FLOAT};
	struct history	*stuff;

	register unsigned	rowCount,colCount,bandCount;
	double		rH,iH;
	double		rD,iD;
	double		rR,iR;
	double		Rdc,R;
	double		den1;
	double		dr,dc;
	Image		*inputs[2];
	Image		*output;
	CVIP_TYPE	datatype;
	register unsigned	rows,cols,bands;

	void		*p_rH,*p_iH;
	void		*p_rD,*p_iD;
	void		*p_rI,*p_iI;

	inputs[0] = numP;
	inputs[1] = denP;
	if(!b_Preprocess(2,inputs))
	return(NULL);
	numP = inputs[0];
	denP = inputs[1];

	output = duplicate_Image(numP);
	if(output == NULL)
	{
		delete_Image(numP);
		delete_Image(denP);
		return(NULL);
	}
	rows = getNoOfRows_Image(output);
	cols = getNoOfCols_Image(output);
	bands = getNoOfBands_Image(output);
	datatype = getDataType_Image(output);

	for(bandCount = 0;bandCount < bands;bandCount++)
	{
		if(datatype == CVIP_FLOAT)
		{
			rH = getRealPixel_Image(denP,float,rows/2,cols/2,bandCount);
			iH = getImagPixel_Image(denP,float,rows/2,cols/2,bandCount);

		}
		else
		{
			rH = getRealPixel_Image(denP,double,rows/2,cols/2,bandCount);
			iH = getImagPixel_Image(denP,double,rows/2,cols/2,bandCount);

		}
		rH /= rows;
		iH /= rows;

		den1 = rH*rH+iH*iH;
		if(den1 != 0)
		{
			rR = rH/den1;
			iR = -iH/den1;
			Rdc = sqrt(rR*rR+iR*iR);
		}
		else
		{
		/*	H(0,0) is 0+0j.
			R(0,0) = 1/0+0j = 1/0, a huge REAL number.  */
			Rdc = MAXDOUBLE;
		}

		Rdc *= (double)choice;

		for(rowCount = 0;rowCount < rows;rowCount++)
		{
			p_rI = getRealRow_Image(output,rowCount,bandCount);
			p_rH = getRealRow_Image(denP,rowCount,bandCount);
			p_rD = getRealRow_Image(numP,rowCount,bandCount);

			p_iI = getImagRow_Image(output,rowCount,bandCount);
			p_iH = getImagRow_Image(denP,rowCount,bandCount);
			p_iD = getImagRow_Image(numP,rowCount,bandCount);
			for(colCount = 0;colCount < cols;colCount++)
			{
				if(datatype == CVIP_FLOAT)
				{
					rH = *(float *)p_rH;
					iH = *(float *)p_iH;
					rD = *(float *)p_rD;
					iD = *(float *)p_iD;
				}
				else
				{
					rH = *(double *)p_rH;
					iH = *(double *)p_iH;
					rD = *(double *)p_rD;
					iD = *(double *)p_iD;
				}

				rH /= rows;
				iH /= rows;
				rD /= rows;
				iD /= rows;

				rR = rH;
				iR = -iH;
				den1 = rH*rH+iH*iH;
				if(den1 != 0)
				{
					rR /= den1;
					iR /= den1;
					if(Rdc > 0)
					{
						R = sqrt(rR*rR+iR*iR);
						if(R > Rdc)
						{
							rR /= (Rdc/R);
							iR /= (Rdc/R);
						}
					}
				}
				else
				{
				/*	H(u,v) is 0+0j.
					R(u,v) = 1/(0+0j) = 1/0, a huge REAL number.
					Limit it to the threshold. */
					if(Rdc > 0)
					rR = Rdc;
					else
					rR = MAXDOUBLE;
					iR = 0;
				}

				if(cutoff > 0)
				{
					dr = (double)rowCount;
					dr -= (double)rows/2.0;
					dc = (double)colCount;
					dc -= (double)cols/2.0;
					if(sqrt(dr*dr+dc*dc) > (double)cutoff)
					{
						rR = 0;
						iR = 0;
					}
				}
				if(datatype == CVIP_FLOAT)
				{
					*((float *)p_rI) = (float)((rR*rD-iR*iD)*(double)rows);
					*((float *)p_iI) = (float)((rR*iD+iR*rD)*(double)rows);

					p_rI = (void *)(((float *)p_rI)+1);
					p_rH = (void *)(((float *)p_rH)+1);
					p_rD = (void *)(((float *)p_rD)+1);

					p_iI = (void *)(((float *)p_iI)+1);
					p_iH = (void *)(((float *)p_iH)+1);
					p_iD = (void *)(((float *)p_iD)+1);
				}
				else
				{
					*((double *)p_rI) = (double)((rR*rD-iR*iD)*(double)rows);
					*((double *)p_iI) = (double)((rR*iD+iR*rD)*(double)rows);

					p_rI = (void *)(((double *)p_rI)+1);
					p_rH = (void *)(((double *)p_rH)+1);
					p_rD = (void *)(((double *)p_rD)+1);

					p_iI = (void *)(((double *)p_iI)+1);
					p_iH = (void *)(((double *)p_iH)+1);
					p_iD = (void *)(((double *)p_iD)+1);
				}
			}
		}
	}
	delete_Image(numP);
	delete_Image(denP);
	stuff = p_CreateHistory(INVERSEFILTER,2,ls_params);
	if(stuff != NULL)
	{
		((int *)(stuff->packetP->dptr[0]))[0] = choice;
		((float *)(stuff->packetP->dptr[1]))[0] = cutoff;

		history_add(output,stuff);
		return(output);
	}
	delete_Image(output);
	return(NULL);
}

/*
 * Routine Name: inverseFilter_Image
 *
 * Description: Performs the inverse filter.  Does not explicitly
 * return the result, but places it inside the image passed.
 * 
 */ 
