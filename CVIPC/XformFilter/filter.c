/*****************************************************************************
 * ======================================================================    *
 * Image Processing/Computer Vision Tool Project - Dr. Scott Umbaugh SIUE    *
 * ======================================================================    *
 *                                                                           *
 * ROUTINE/PGM NAME: filter.c                                                *
 *                                                                           *
 *              DESCRIPTION: This file contains all the filtering routines.  *
 * The filtering functions below can be called idependently with correct     *
 * parameters, they can be called also with the setup programs listed        *
 * below.                                                                    *
 *                                                                           *
 *                   AUTHOR: Simon Low                                       *
 *                                                                           *
 *            RELATED FILES: lpf_setup.c,hpf_setup,bpf_setup.c,brf_setup.c   *
 *                           homf_setup.c,cn_setup.c                         *
 *                                                                           *
 *              CODING DATE: 1/15/92                                         *
 *  LAST MODIFICATIONS MADE: 11/18/92                                        *
 *                                                                           *
 *****************************************************************************
RCS (Revision Control System) Information - Added automatically by RCS)

$Author: yawei $
$Date: 1997/03/08 17:03:29 $
$Source: /export/home_faculty/cvipapps/CVIPtools3.5/XFORMFILTER/RCS/filter.c,v $
$Header: /export/home_faculty/cvipapps/CVIPtools3.5/XFORMFILTER/RCS/filter.c,v 1.7 1997/03/08 17:03:29 yawei Exp $

*******************************************************************************/
/* Define Preprocessor statements */

#include <math.h>
#include <stdio.h>
#include <stdlib.h> 
#include "CVIPdef.h"
#include "CVIPimage.h" 

Image*
Ideal_Low(
	Image* in_Image,
	int	block_size,
	int	dc,
	int	Cutoff
)
{
	int i, ii, jj, x, y = 0;
	int H, W, x1, y1;
	int a = 0, b = 0, nofblk;
	int  Hnofblk, Hcounter = 1;
	double r1;
	CVIP_BOOLEAN komplex = CVIP_YES;

	H = in_Image->image_ptr[0]->cols;
	W = in_Image->image_ptr[0]->rows;

	if (in_Image->image_ptr[0]->data_format == REAL)
		komplex = CVIP_NO;

	nofblk = (H / block_size) * (W / block_size);  /* total number of blocks */
	Hnofblk = W / block_size;   /* total of horizontal blocks */

	/*consta =W/Hnofblk;   a constant. should replace by block_size  */
	/* Hnofblk = horizontal number of block counter eg. for 256= 512/16=32*/

	for (i = 1; i <= nofblk; ) {

		x1 = a + block_size / 2; y1 = b + block_size / 2;
		for (x = a; x < (a + block_size); x++) {
			for (y = b; y < (b + block_size); y++) {

				ii = abs(x - x1);
				jj = abs(y - y1);
				r1 = sqrt((double)(ii * ii) + (double)(jj * jj));

				if (r1 > (double)(Cutoff)) {

					if (!(x == x1 && y == y1)) {

						((float**)(in_Image->image_ptr[0]->rptr))[x][y] = 0;
						if (komplex)
							((float**)(in_Image->image_ptr[0]->iptr))[x][y] = 0;

						if (in_Image->bands == 3) {
							((float**)(in_Image->image_ptr[1]->rptr))[x][y] = 0;
							((float**)(in_Image->image_ptr[2]->rptr))[x][y] = 0;
							if (komplex) {
								((float**)(in_Image->image_ptr[1]->iptr))[x][y] = 0;
								((float**)(in_Image->image_ptr[2]->iptr))[x][y] = 0;
							}
						}
					}
				}
			}
		} /* end x=a... */

		/* if does not want retain dc */

		if (!dc) {
			((float**)(in_Image->image_ptr[0]->rptr))[x1][y1] = 0;
			if (komplex)
				((float**)(in_Image->image_ptr[0]->iptr))[x1][y1] = 0;

			if (in_Image->bands == 3) {
				((float**)(in_Image->image_ptr[1]->rptr))[x1][y1] = 0;
				((float**)(in_Image->image_ptr[2]->rptr))[x1][y1] = 0;
				if (komplex) {
					((float**)(in_Image->image_ptr[1]->iptr))[x1][y1] = 0;
					((float**)(in_Image->image_ptr[2]->iptr))[x1][y1] = 0;
				}
			}
		}
		i++; /* one block done */

		Hcounter++;  /* to keep track of number of Horizontal Blks performed */

		if (Hcounter > Hnofblk) {
			b += block_size;
			a = 0;
			Hcounter = 1;
		}
		else
			a += block_size;

	} /* end (for i=1 ; */

	return in_Image;
}

Image*
Ideal_High(
	Image* in_Image,
	int	block_size,
	int	dc,
	int	Cutoff
)
{
	int i, ii, jj, x, y;
	int H, W, x1, y1;
	int a = 0, b = 0, nofblk;
	int  Hnofblk, Hcounter = 1;
	double r1;
	CVIP_BOOLEAN komplex = CVIP_YES;

	H = in_Image->image_ptr[0]->cols;
	W = in_Image->image_ptr[0]->rows;
	if (in_Image->image_ptr[0]->data_format == REAL)
		komplex = CVIP_NO;

	nofblk = (H / block_size) * (W / block_size);  /* total number of blocks */
	Hnofblk = W / block_size;
	/*consta =W/Hnofblk;*/
	/* Hnofblk = horizontal number of block counter ex for 256= 512/16=32*/

	for (i = 1; i <= nofblk; ) {
		x1 = a + block_size / 2; y1 = b + block_size / 2;
		for (x = a; x < (a + block_size); x++) {
			for (y = b; y < (b + block_size); y++) {

				ii = abs(x - x1);
				jj = abs(y - y1);
				r1 = sqrt((double)(ii * ii) + (double)(jj * jj));

				if (r1 < (double)(Cutoff)) {
					if (!(x == x1 && y == y1)) {

						((float**)(in_Image->image_ptr[0]->rptr))[x][y] = 0;
						if (komplex)
							((float**)(in_Image->image_ptr[0]->iptr))[x][y] = 0;

						if (in_Image->bands == 3) {
							((float**)(in_Image->image_ptr[1]->rptr))[x][y] = 0;
							((float**)(in_Image->image_ptr[2]->rptr))[x][y] = 0;
							if (komplex) {
								((float**)(in_Image->image_ptr[1]->iptr))[x][y] = 0;
								((float**)(in_Image->image_ptr[2]->iptr))[x][y] = 0;
							}
						}
					}
				}
			}
		} /* end x=a... */

		if (!dc) {
			((float**)(in_Image->image_ptr[0]->rptr))[x1][y1] = 0;
			if (komplex)
				((float**)(in_Image->image_ptr[0]->iptr))[x1][y1] = 0;

			if (in_Image->bands == 3) {
				((float**)(in_Image->image_ptr[1]->rptr))[x1][y1] = 0;
				((float**)(in_Image->image_ptr[2]->rptr))[x1][y1] = 0;
				if (komplex) {
					((float**)(in_Image->image_ptr[1]->iptr))[x1][y1] = 0;
					((float**)(in_Image->image_ptr[2]->iptr))[x1][y1] = 0;
				}
			}
		}

		i++; /* one block done */

		Hcounter++;      /*  to keep track of # of Horizontal Blks performed */

		if (Hcounter > Hnofblk) { /* need to reset Hcounter also */
			a = 0;
			b += block_size;
			Hcounter = 1;
		}
		else
			a += block_size;

	} /* end (for i=1 ; */

	return in_Image;
}


Image*
Ideal_Band_Pass(
	Image* in_Image,
	int	block_size,
	int	dc,
	int	inner,
	int	outer
)
{
	int i, ii, jj, x, y;
	int H, W, x1, y1;
	int a = 0, b = 0, nofblk;
	int  Hnofblk, Hcounter = 1;
	double r1;
	CVIP_BOOLEAN komplex = CVIP_YES;

	H = in_Image->image_ptr[0]->cols;
	W = in_Image->image_ptr[0]->rows;

	nofblk = (H / block_size) * (W / block_size);  /* total number of blocks */
	Hnofblk = W / block_size;
	/*consta =W/Hnofblk;     a constant */

	if (in_Image->image_ptr[0]->data_format == REAL)
		komplex = CVIP_NO;

	/* Hnofblk = horizontal number of block counter ex for 256= 512/16=32*/

	for (i = 1; i <= nofblk; ) {

		x1 = a + block_size / 2; y1 = b + block_size / 2;
		for (x = a; x < (a + block_size); x++) {
			for (y = b; y < (b + block_size); y++) {

				ii = abs(x - x1);
				jj = abs(y - y1);
				r1 = sqrt((double)(ii * ii) + (double)(jj * jj));

				if (r1 >= (double)(outer) || r1 <= (double)(inner)) {
					if (!(x == x1 && y == y1)) {

						((float**)(in_Image->image_ptr[0]->rptr))[x][y] = 0;
						if (komplex)
							((float**)(in_Image->image_ptr[0]->iptr))[x][y] = 0;

						if (in_Image->bands == 3) {
							((float**)(in_Image->image_ptr[1]->rptr))[x][y] = 0;
							((float**)(in_Image->image_ptr[2]->rptr))[x][y] = 0;
							if (komplex) {
								((float**)(in_Image->image_ptr[1]->iptr))[x][y] = 0;
								((float**)(in_Image->image_ptr[2]->iptr))[x][y] = 0;
							}
						}
					}
				}
			}
		} /* end x=a... */

		/* if does not want retain dc value*/

		if (!dc) {
			((float**)(in_Image->image_ptr[0]->rptr))[x1][y1] = 0;
			if (komplex)
				((float**)(in_Image->image_ptr[0]->iptr))[x1][y1] = 0;

			if (in_Image->bands == 3) {
				((float**)(in_Image->image_ptr[1]->rptr))[x1][y1] = 0;
				((float**)(in_Image->image_ptr[2]->rptr))[x1][y1] = 0;
				if (komplex) {
					((float**)(in_Image->image_ptr[1]->iptr))[x1][y1] = 0;
					((float**)(in_Image->image_ptr[2]->iptr))[x1][y1] = 0;
				}
			}
		}
		i++; /* one block done */

		Hcounter++;    /*to keep track of number of Horizontal Blks performed */

		if (Hcounter > Hnofblk) { /* need to reset Hcounter also */
			a = 0;
			b += block_size;
			Hcounter = 1;
		}
		else
			a += block_size;

	} /* end (for i=1 ; */

	return in_Image;
}


Image*
Ideal_Band_Reject(
	Image* in_Image,
	int	block_size,
	int	dc,
	int	inner,
	int	outer
)
{
	int i, ii, jj, x, y;
	int H, W, x1, y1;
	int a = 0, b = 0, nofblk, aoff, boff;
	int  Hnofblk, Hcounter = 1, bandc;
	double r1;
	CVIP_BOOLEAN komplex = CVIP_YES;
	float** rptr, * ptr, ** irptr, * iptr;

	H = in_Image->image_ptr[0]->cols;
	W = in_Image->image_ptr[0]->rows;

	if (in_Image->image_ptr[0]->data_format == REAL)
		komplex = CVIP_NO;

	nofblk = (H / block_size) * (W / block_size);  /* total number of blocks */
	Hnofblk = W / block_size;
	/*consta =W/Hnofblk;*/

	for (bandc = 0; bandc < in_Image->bands; bandc++) {
		rptr = (float**)in_Image->image_ptr[bandc]->rptr;
		if (komplex) irptr = (float**)in_Image->image_ptr[bandc]->iptr;
		for (i = 1; i <= nofblk; ) {
			x1 = a + block_size / 2; y1 = b + block_size / 2;
			aoff = a + block_size;
			boff = b + block_size;
			for (x = a; x < aoff; x++) {
				ptr = (float*)rptr[x];
				if (komplex) iptr = (float*)irptr[x];
				for (y = b; y < boff; y++) {
					ii = abs(x - x1);
					jj = abs(y - y1);
					r1 = sqrt((double)(ii * ii) + (double)(jj * jj));

					if ((r1 <= (double)(outer)) && (r1 >= (double)(inner))) {
						if (!((x == x1) && (y == y1))) {

							ptr[y] = 0.0;
							if (komplex)
								iptr[y] = 0.0;
						}
					}
				}
			} /* end x=a... */

			/* if does not want retain dc value */

			if (!dc) {
				((float**)(in_Image->image_ptr[0]->rptr))[x1][y1] = 0;
				if (komplex)
					((float**)(in_Image->image_ptr[0]->iptr))[x1][y1] = 0;

				if (in_Image->bands == 3) {
					((float**)(in_Image->image_ptr[1]->rptr))[x1][y1] = 0;
					((float**)(in_Image->image_ptr[2]->rptr))[x1][y1] = 0;
					if (komplex) {
						((float**)(in_Image->image_ptr[1]->iptr))[x1][y1] = 0;
						((float**)(in_Image->image_ptr[2]->iptr))[x1][y1] = 0;
					}
				}
			}
			i++; /* one block done */

			Hcounter++;     /*to keep track of number of Horizontal Blks performed */

			if (Hcounter > Hnofblk) { /* need to reset Hcounter also */
				a = 0;
				b += block_size;
				Hcounter = 1;
			}
			else
				a += block_size;

		} /* end (for i=1 ; */

	} /* end (for banc=0; */
	return in_Image;
}


/* Butterworh Low Pass Filter */

Image*
Butterworth_Low(
	Image* in_Image,
	int	block_size,
	int	dc,
	int	Cutoff,
	int	order
)
{
	int i, ii, jj, x, y, x1, y1;
	int a = 0, b = 0, nofblk, Hnofblk, Hcounter = 1;
	float C = 0.414;
	double H, temp, r1;
	int h, w;
	CVIP_BOOLEAN komplex = CVIP_YES;

	h = in_Image->image_ptr[0]->cols;
	w = in_Image->image_ptr[0]->rows;


	nofblk = (h / block_size) * (w / block_size);  /* total number of blocks */
	Hnofblk = w / block_size;
	/*consta =w/Hnofblk;*/
   /* Cutoff =(int) (Cutoff/Hnofblk);   Do  */

	order *= 2;

	if (in_Image->image_ptr[0]->data_format == REAL)
		komplex = CVIP_NO;

	for (i = 1; i <= nofblk; ) {

		x1 = a + block_size / 2; y1 = b + block_size / 2;
		for (x = a; x < (a + block_size); x++) {
			for (y = b; y < (b + block_size); y++) {

				ii = abs(x - x1);
				jj = abs(y - y1);
				r1 = sqrt((double)(ii * ii) + (double)(jj * jj)); /* D(u, v) */

				temp = r1 / Cutoff;

				H = (1 / (1 + C * (pow(temp, (double)(order)))));

				if (!(x == x1 && y == y1)) {

					((float**)(in_Image->image_ptr[0]->rptr))[x][y] *= H;
					if (komplex)
						((float**)(in_Image->image_ptr[0]->iptr))[x][y] *= H;

					if (in_Image->bands == 3) {
						((float**)(in_Image->image_ptr[1]->rptr))[x][y] *= H;
						((float**)(in_Image->image_ptr[2]->rptr))[x][y] *= H;
						if (komplex) {
							((float**)(in_Image->image_ptr[1]->iptr))[x][y] *= H;
							((float**)(in_Image->image_ptr[2]->iptr))[x][y] *= H;
						}
					}
				}
			} /* end y=a..*/
		} /* end x=a... */

		if (!dc) {
			((float**)(in_Image->image_ptr[0]->rptr))[x1][y1] = 0;
			if (komplex)
				((float**)(in_Image->image_ptr[0]->iptr))[x1][y1] = 0;

			if (in_Image->bands == 3) {
				((float**)(in_Image->image_ptr[1]->rptr))[x1][y1] = 0;
				((float**)(in_Image->image_ptr[2]->rptr))[x1][y1] = 0;
				if (komplex) {
					((float**)(in_Image->image_ptr[1]->iptr))[x1][y1] = 0;
					((float**)(in_Image->image_ptr[2]->iptr))[x1][y1] = 0;
				}
			}
		}
		i++; /* one block done */

		Hcounter++;      /* counter to keep track of Hori Blk performed */

		if (Hcounter > Hnofblk) { /* reset Hcounter  */
			a = 0;
			b += block_size;
			Hcounter = 1;
		}
		else
			a += block_size;

	} /* end (for i=1 ; */

	return in_Image;
}


/* Butterworh High  Pass Filter */

Image*
Butterworth_High(
	Image* in_Image,
	int	block_size,
	int	dc,
	int	Cutoff,
	int	order
)
{
	int i, ii, jj, x, y, x1, y1;
	int a = 0, b = 0, nofblk, Hnofblk, Hcounter = 1;
	float C = 0.414;
	double H, temp, r1;
	int h, w;
	CVIP_BOOLEAN komplex = CVIP_YES;

	h = in_Image->image_ptr[0]->cols;
	w = in_Image->image_ptr[0]->rows;

	if (in_Image->image_ptr[0]->data_format == REAL)
		komplex = CVIP_NO;

	nofblk = (h / block_size) * (w / block_size);  /* total number of blocks */
	Hnofblk = w / block_size;
	/*consta =w/Hnofblk;*/
	/*Cutoff =(int) (Cutoff/Hnofblk);   Do  */

	order *= 2;

	for (i = 1; i <= nofblk; ) {

		x1 = a + block_size / 2; y1 = b + block_size / 2;
		for (x = a; x < (a + block_size); x++) {
			for (y = b; y < (b + block_size); y++) {

				ii = abs(x - x1);
				jj = abs(y - y1);
				r1 = sqrt((double)(ii * ii) + (double)(jj * jj)); /* D(u, v) */

				if (r1 != 0) {
					temp = (double)(Cutoff / r1);
					H = (1 / (1 + C * (pow(temp, (double)(order)))));
				}

				if (!(x == x1 && y == y1)) {
					((float**)(in_Image->image_ptr[0]->rptr))[x][y] *= H;
					if (komplex)
						((float**)(in_Image->image_ptr[0]->iptr))[x][y] *= H;

					if (in_Image->bands == 3) {
						((float**)(in_Image->image_ptr[1]->rptr))[x][y] *= H;
						((float**)(in_Image->image_ptr[2]->rptr))[x][y] *= H;
						if (komplex) {
							((float**)(in_Image->image_ptr[1]->iptr))[x][y] *= H;
							((float**)(in_Image->image_ptr[2]->iptr))[x][y] *= H;
						}
					}
				}
			} /* end y=a..*/
		} /* end x=a... */

		if (!dc) {
			((float**)(in_Image->image_ptr[0]->rptr))[x1][y1] = 0;
			if (komplex)
				((float**)(in_Image->image_ptr[0]->iptr))[x1][y1] = 0;

			if (in_Image->bands == 3) {
				((float**)(in_Image->image_ptr[1]->rptr))[x1][y1] = 0;
				((float**)(in_Image->image_ptr[2]->rptr))[x1][y1] = 0;
				if (komplex) {
					((float**)(in_Image->image_ptr[1]->iptr))[x1][y1] = 0;
					((float**)(in_Image->image_ptr[2]->iptr))[x1][y1] = 0;
				}
			}
		}
		i++; /* one block done */

		Hcounter++;      /* counter to keep track of Hori Blk performed */

		if (Hcounter > Hnofblk) { /* reset Hcounter  */
			a = 0;
			b += block_size;
			Hcounter = 1;
		}
		else
			a += block_size;

	} /* end (for i=1 ; */

	return in_Image;
}


Image*
Butterworth_Band_Reject(
	Image* in_Image,
	int	block_size,
	int	dc,
	int	inner,
	int	outer,
	int	order
)
{
	int i, ii, jj, x, y, x1, y1;
	int a = 0, b = 0, nofblk, Hnofblk, Hcounter = 1;
	double H, temp, r1, r2;
	int h, w, Wid, center;
	CVIP_BOOLEAN komplex = CVIP_YES;

	h = in_Image->image_ptr[0]->cols;
	w = in_Image->image_ptr[0]->rows;

	if (in_Image->image_ptr[0]->data_format == REAL)
		komplex = CVIP_NO;

	nofblk = (h / block_size) * (w / block_size);  /* total number of blocks */
	Hnofblk = w / block_size;
	/*consta =w/Hnofblk;*/

	Wid = outer - inner; /* W is the width of the band */
	center = inner + (int)(Wid / 2);  /* Do: its radial center */
	center = (int)(center * center);
	order *= 2;

	for (i = 1; i <= nofblk; ) {

		x1 = a + block_size / 2; y1 = b + block_size / 2;
		for (x = a; x < (a + block_size); x++) {
			for (y = b; y < (b + block_size); y++) {

				ii = abs(x - x1);
				jj = abs(y - y1);

				r1 = sqrt((double)(ii * ii) + (double)(jj * jj)); /* D(u, v) */
				r2 = r1 * r1; /* D square */

				if ((r2 - center) != 0)
					temp = (double)(r1 * Wid / (r2 - center));

				if ((r2 - center) == 0)
					H = 0.0;
				else
					H = 1.0 / (1.0 + pow(temp, (double)(order)));

				if (!(x == x1 && y == y1)) {

					((float**)(in_Image->image_ptr[0]->rptr))[x][y] *= H;
					if (komplex)
						((float**)(in_Image->image_ptr[0]->iptr))[x][y] *= H;

					if (in_Image->bands == 3) {
						((float**)(in_Image->image_ptr[1]->rptr))[x][y] *= H;
						((float**)(in_Image->image_ptr[2]->rptr))[x][y] *= H;
						if (komplex) {
							((float**)(in_Image->image_ptr[1]->iptr))[x][y] *= H;
							((float**)(in_Image->image_ptr[2]->iptr))[x][y] *= H;
						}
					}
				}
			} /* end y=a..*/
		} /* end x=a... */

		if (!dc) { /* assign center of each block 0 */
			((float**)(in_Image->image_ptr[0]->rptr))[x1][y1] = 0.0;
			if (komplex)
				((float**)(in_Image->image_ptr[0]->iptr))[x1][y1] = 0.0;

			if (in_Image->bands == 3) {
				((float**)(in_Image->image_ptr[1]->rptr))[x1][y1] = 0.0;
				((float**)(in_Image->image_ptr[2]->rptr))[x1][y1] = 0.0;
				if (komplex) {
					((float**)(in_Image->image_ptr[1]->iptr))[x1][y1] = 0.0;
					((float**)(in_Image->image_ptr[2]->iptr))[x1][y1] = 0.0;
				}
			}
		}
		i++; /* one block done */
		Hcounter++;      /* counter to keep track of Hori Blk performed */

		if (Hcounter > Hnofblk) { /* reset Hcounter  */
			a = 0;
			b += block_size;
			Hcounter = 1;
		}
		else
			a += block_size;

	} /* end (for i=1 ; */
	return in_Image;
}

Image*
Butterworth_Band_Pass(
	Image* in_Image,
	int	block_size,
	int	dc,
	int	inner,
	int	outer,
	int	order
)
{
	int i, ii, jj, x, y, x1, y1;
	int a = 0, b = 0, nofblk, Hnofblk, Hcounter = 1;
	double H, temp, r1, r2;
	int h, w, W, center;
	CVIP_BOOLEAN komplex = CVIP_YES;

	h = in_Image->image_ptr[0]->cols;
	w = in_Image->image_ptr[0]->rows;

	if (in_Image->image_ptr[0]->data_format == REAL)
		komplex = CVIP_NO;

	nofblk = (h / block_size) * (w / block_size);  /* total number of blocks */
	Hnofblk = w / block_size; /* it was H */
	/*consta =w/Hnofblk;*/

	W = outer - inner;   /* W is the width of the band */
	center = inner + (int)(W / 2);  /* Do: its radial center */
	center = center * center;
	order *= 2;

	for (i = 1; i <= nofblk; ) {

		x1 = a + block_size / 2; y1 = b + block_size / 2;
		for (x = a; x < (a + block_size); x++) {
			for (y = b; y < (b + block_size); y++) {

				ii = abs(x - x1);
				jj = abs(y - y1);
				r1 = sqrt((double)(ii * ii) + (double)(jj * jj)); /* D(u, v) */
				r2 = r1 * r1;
				if ((r2 - center) != 0)
					temp = (double)((r1 * W) / (r2 - center));

				if ((r2 - center) == 0)  /* need to recheck this part 9/27 */
					H = 0;
				else
					H = 1.0 / (1 + pow(temp, (double)(order)));

				H = -1.0 * (H - 1);

				if (!(x == x1 && y == y1)) {
					((float**)(in_Image->image_ptr[0]->rptr))[x][y] *= H;
					if (komplex)
						((float**)(in_Image->image_ptr[0]->iptr))[x][y] *= H;

					if (in_Image->bands == 3) {
						((float**)(in_Image->image_ptr[1]->rptr))[x][y] *= H;
						((float**)(in_Image->image_ptr[2]->rptr))[x][y] *= H;
						if (komplex) {
							((float**)(in_Image->image_ptr[1]->iptr))[x][y] *= H;
							((float**)(in_Image->image_ptr[2]->iptr))[x][y] *= H;
						}
					}
				}
			} /* end y=a..*/
		} /* end x=a... */

		if (!dc) {
			((float**)(in_Image->image_ptr[0]->rptr))[x1][y1] = 0;
			if (komplex)
				((float**)(in_Image->image_ptr[0]->iptr))[x1][y1] = 0;

			if (in_Image->bands == 3) {
				((float**)(in_Image->image_ptr[1]->rptr))[x1][y1] = 0;
				((float**)(in_Image->image_ptr[2]->rptr))[x1][y1] = 0;
				if (komplex) {
					((float**)(in_Image->image_ptr[1]->iptr))[x1][y1] = 0;
					((float**)(in_Image->image_ptr[2]->iptr))[x1][y1] = 0;
				}
			}
		}
		i++; /* one block done */

		Hcounter++;      /* counter to keep track of Hori Blk performed */

		if (Hcounter > Hnofblk) { /* reset Hcounter  */
			a = 0;
			b += block_size;
			Hcounter = 1;
		}
		else
			a += block_size;

	} /* end (for i=1 ; */

	return in_Image;
}


Image* High_Freq_Emphasis(
	Image* in_Image,
	int	 	block_size,
	int		dc,
	int		Cutoff,
	float		alfa,
	int		order
)
{
	int i, ii, jj, x, y, x1, y1;
	int a = 0, b = 0, nofblk, Hnofblk, Hcounter = 1;
	float C = 0.414;
	double H, temp, r1;
	int h, w;
	CVIP_BOOLEAN komplex = CVIP_YES;

	h = in_Image->image_ptr[0]->cols;
	w = in_Image->image_ptr[0]->rows;

	if (in_Image->image_ptr[0]->data_format == REAL)
		komplex = CVIP_NO;

	nofblk = (h / block_size) * (w / block_size);  /* total number of blocks */
	Hnofblk = w / block_size;
	order *= 2;

	for (i = 1; i <= nofblk; ) {

		x1 = a + block_size / 2; y1 = b + block_size / 2;
		for (x = a; x < (a + block_size); x++) {
			for (y = b; y < (b + block_size); y++) {

				ii = abs(x - x1);
				jj = abs(y - y1);
				r1 = sqrt((double)(ii * ii) + (double)(jj * jj)); /* D(u, v) */

				if (r1 != 0) {
					temp = (double)(Cutoff / r1);
					H = (1 / (1 + C * (pow(temp, (double)(order)))));
					H += alfa;
				}
				if (!(x == x1 && y == y1)) {
					((float**)(in_Image->image_ptr[0]->rptr))[x][y] *= H;
					if (komplex)
						((float**)(in_Image->image_ptr[0]->iptr))[x][y] *= H;

					if (in_Image->bands == 3) {
						((float**)(in_Image->image_ptr[1]->rptr))[x][y] *= H;
						((float**)(in_Image->image_ptr[2]->rptr))[x][y] *= H;
						if (komplex) {
							((float**)(in_Image->image_ptr[1]->iptr))[x][y] *= H;
							((float**)(in_Image->image_ptr[2]->iptr))[x][y] *= H;
						}
					}
				}
			} /* end y=a..*/
		} /* end x=a... */

		if (!dc) {
			((float**)(in_Image->image_ptr[0]->rptr))[x1][y1] = 0;
			if (komplex)
				((float**)(in_Image->image_ptr[0]->iptr))[x1][y1] = 0;

			if (in_Image->bands == 3) {
				((float**)(in_Image->image_ptr[1]->rptr))[x1][y1] = 0;
				((float**)(in_Image->image_ptr[2]->rptr))[x1][y1] = 0;
				if (komplex) {
					((float**)(in_Image->image_ptr[1]->iptr))[x1][y1] = 0;
					((float**)(in_Image->image_ptr[2]->iptr))[x1][y1] = 0;
				}
			}
		}
		i++; /* one block done */

		Hcounter++;      /* counter to keep track of Hori Blk performed */

		if (Hcounter > Hnofblk) { /* reset Hcounter  */
			a = 0;
			b += block_size;
			Hcounter = 1;
		}
		else
			a += block_size;

	} /* end (for i=1 ; */

	return in_Image;
}
