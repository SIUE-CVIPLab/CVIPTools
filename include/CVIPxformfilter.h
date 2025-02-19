/***************************************************************************
*									   *
* ======================================================================== *
*  COMPUTER VISION/Image PROCESSING TOOL PROJECT - Dr. Scott Umbaugh, SIUE *
* ======================================================================== *
*									   *
*	FILE NAME: Xform_filtering.h					   *
*									   *
*	DESCRIPTION: Header file for transform_domain filtering functions. *
*									   *
*	AUTHOR : Arve Kjoelen, SIUE					   *
*									   *
*	INITIAL CODING DATE: 01/11/94					   *
*									   *
*	RELATED FILES: filter.c lpf_setup.c hpf_setup.c bpf_setup.c        *
*		       brf_setup.c hfe_setup.c cn_setup.c		   *
*		       xformfilter_setup.c				   *
*									   *
* RCS (Revision Control System) Information
* ...Added automatically by RCS 
*
** $Log: CVIPxformfilter.h,v $
** Revision 1.31  1997/06/25 19:23:00  wzheng
** *** empty log message ***
**
** Revision 1.30  1997/03/15 00:54:09  yawei
** corrected error.
**
** Revision 1.29  1997/03/15 00:39:04  yawei
** defined FILTER_TYPE
**
** Revision 1.28  1997/03/08 00:47:21  yawei
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
** Revision 1.27  1997/01/15 17:11:14  yawei
** Global Change:  IMAGE ==> Image
**
 * Revision 1.26  1996/12/31  22:22:53  yawei
 * Notch_Image ==> notch
 *
 * Revision 1.25  1996/12/30  20:49:24  yawei
 * power_spect_equal ==> power_spect_eq.
 *
 * Revision 1.24  1996/12/30  19:40:26  yawei
 * power_spect_equalize ==> power_spect_equal
 *
 * Revision 1.23  1996/12/30  17:51:33  yawei
 * wiener_filter ==> wiener
 *
 * Revision 1.22  1996/12/30  15:34:35  yawei
 * corner_setup ==> nonfft_xformfilter
 *
*
***************************************************************************/
#if !defined ( XFORM_FILTERING_DEFINED)
   #define XFORM_FILTERING_DEFINED
   #include "CVIPimage.h"
   #include "CVIPtools.h"

	typedef enum {
		IDEAL_LOW = 1,
		BUTTER_LOW = 2,
		IDEAL_HIGH =3 ,
		BUTTER_HIGH = 4,
		IDEAL_BAND = 5,
		BUTTER_BAND = 6,
		IDEAL_REJECT = 7,
		BUTTER_REJECT = 8,
		HIGH_FREQ_EMPHASIS = 9
	} FILTER_TYPE;

#ifdef __cplusplus
extern "C"{
#endif 

   extern Image *nonfft_xformfilter(Image *input_Image, int block_size, int dc,
		FILTER_TYPE filtertype, int p1, float p2, int order);
   extern Image *select_filter(Image *input_Image, int blk_size, int dc,
		FILTER_TYPE filtertype, int p1, int p2, int order);


   extern Image *Ideal_Low(Image *in_Image, int block_size, int dc, int cutoff);
   extern Image *Ideal_High(Image *in_Image, int block_size, int dc, int cutoff);
   extern Image *Ideal_Band_Pass(Image *in_Image, int block_size, int dc,
		int inner, int outer);
   extern Image *Ideal_Band_Reject(Image *in_Image, int block_size, int dc,
		int inner, int outer);
   extern Image *Butterworth_Low(Image *in_Image, int block_size, int dc,
		int Cutoff, int order);
   extern Image *Butterworth_High(Image *in_Image, int block_size, int dc,
		int Cutoff, int order);
   extern Image *Butterworth_Band_Pass(Image *in_Image, int block_size, int dc,
		int inner, int outer, int order);
   extern Image *Butterworth_Band_Reject(Image *in_Image, int block_size,
		int dc, int inner, int outer, int order);
   extern Image *High_Freq_Emphasis(Image *in_Image, int block_size, int dc,
		int Cutoff, float alfa, int order);
   extern Image *inverse_xformfilter(Image *numP, Image *denP, int choice,
		float cutoff);
   extern Image *simple_wiener(Image *degr, Image *degr_fn, float k);
   extern Image *least_squares(Image *degr, Image *degr_fn, Image *snr_approx,
		float gamma, int choice, int cutoff);
   extern Image *wiener(Image *degr, Image *degr_fn, Image *p_noise,
		Image *p_orig, int choice, int cutoff);
   extern Image *parametric_wiener(Image *degr, Image *degr_fn, Image *p_noise,
		Image *p_orig, float gamma, int choice, int cutoff);
   extern Image *power_spect_eq(Image *degr, Image *degr_fn,
		Image *p_noise, Image *p_orig, int choice, int cutoff);
   extern Image *geometric_mean(Image *degr, Image *degr_fn, Image *p_noise,
		Image *p_orig, float gamma, float alpha, int choice, int cutoff);
   extern Image * homomorphic(Image *cvipImage1,float upper, float lower,
		int cutoff);
   extern Image* hpf_filter(Image* in_Image, int xform, int Blocksize, int HP_Filter, int filter_order, int cutoff, int keepdc);
   extern Image* lpf_filter(Image* in_Image, int xform, int Blocksize, int HP_Filter, int filter_order, int cutoff, int keepdc);

typedef struct {
	int x;
	int y;
	int radius;
} NOTCH_ZONE;

struct link_zone{
	NOTCH_ZONE area;
	struct link_zone *next;
};

extern int get_notch_input(NOTCH_ZONE **zone,int size);
extern Image *notch(Image *cvipImage, char *name, NOTCH_ZONE *zone,int number,
		 CVIP_BOOLEAN interactive);

/* interactive functions kept for backward compatibility and for usage in CVIPlab, not
 * encouraged to be used in CVIPtools.
 */
extern Image *xformfilter_setup(Image *input_Image, CVIP_BOOLEAN *remap,
	unsigned filter);
extern Image *lpf_setup(Image *input_Image, PROGRAMS transform);
extern Image *hpf_setup(Image *input_Image, PROGRAMS transform);
extern Image *bpf_setup(Image *input_Image, PROGRAMS transform);
extern Image *brf_setup(Image *input_Image, PROGRAMS transform);
extern Image *hfe_setup(Image *in_Image, PROGRAMS transform);
#ifdef __cplusplus
}
#endif 

#endif
