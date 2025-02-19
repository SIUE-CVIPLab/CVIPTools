/*************************************************************************
* ===================================================================== *
*    COMPUTER VISION/Image PROCESSING TOOL - DR. SCOTT UMBAUGH, SIUE  	*
* ===================================================================== *
*									*
*		Project			:  Deformable Templates		*	*									*
*		File			:  deform_template.h		*	*									*
*		Programmer(s)	:  Lance A. Kendrick    		*       *    									*
*		Origin Date		:  2-Apr-92			*
*									*
*		DESCRIPTION: Header file for deformable template 	*
*		image segmentation algorithm.				*
*									*
*		MODIFIED FOR CVIPTOOLS BY: Arve Kjoelen, SIUE		*
*									*
*		LAST MODIFICATION DATE: 01/31/94			*	*									*	*									*
************************************************************************/
#ifndef	_TEMPLATES_H_
#   define 	_TEMPLATES_H_

 /*  INCLUDES  */

#include 	<stdio.h>
#include 	<sys/types.h>
#include 	<sys/stat.h>
#include 	<fcntl.h>
#ifndef WIN32
#include 	<unistd.h>
#endif
#include 	<math.h>
#include 	"imaging.h"
#include "CVIPimage.h"

typedef struct {
	int snum_itr;
        int sh;
	int sinc;
	int sbilinear;
	float    salpha;
	float    ssigma;
	float    sdt;
	float    sstddev; } sdata;
	
  
 /*  FUNCTION PROTOTYPES  */

   extern int  	GetParametersc( char* );
   extern void 	EchoParameters( void );
   extern void 	set_up_sc( float***, float***, float***, float***, float**,    float**, float**, float**, unsigned );
   extern Image	*sincos(Image *template, Image *seg, Image *data );

#  if defined( SGIArchitecture)
      int  	initialize_grafix( float**, float** );
      void 	update_display( float** );

#  endif /* SGIArchitecture */
   void 	invert( unsigned long* );
   void 	displace( float**, float**, float**, float** );
   void 	bldisplace( float**, float**, float**, float** );
   void 	calc_coeff( float**, float**, float**, float** );
   void 	calc_partials( float**, float**, float** );
   void 	calc_displacement( float**, float**, float**, float** );

   /*  DEFINITIONS  */
#   define STOCHASTIC

   /*
#   define ZOOM
   */

#   define X   						0
#   define Y   						1
#   define NUMCOLOR 					255
#   define GL_OFFSET					600.0
#   define MAX_SPECT     			3

#   define WEST_EDGE    	j==0 && (i!=0 && i!=(vsize-1))
#   define EAST_EDGE    	j==(hsize-1) && (i!=0 && i!=(vsize-1))
#   define NORTH_EDGE   	i==0 && (j!=0 && j!=(hsize-1))
#   define SOUTH_EDGE   	i==(vsize-1) && (j!=0 && j!=(hsize-1))
#   define NWEST_CORNER 	i==0 && j==0
#   define NEAST_CORNER 	i==0 && j==(hsize-1)
#   define SEAST_CORNER 	i==(vsize-1) && j==(hsize-1)
#   define SWEST_CORNER 	i==(vsize-1) && j==0

 /*  MACROS  */

#   define MOOD(a,b)       ( (a) >= 0 ? ((a)%(b)) : ((b)-(abs(a) % (b))) % (b))

 /*  EXTERNAL VARIABLES  */

   extern int		bilinear, h,	vsize, hsize;
   extern int		num_spectra, num_itr, inc;
   extern char		u1_file[50], u2_file[50];
   extern char		temp_files[MAX_SPECT][50], data_files[MAX_SPECT][50];
   extern char		coeffs_1_file[50], coeffs_2_file[50];
   extern float	*x, *y, *xx, *displ_ptr;
   extern float   dt, sqrtdt,	ampnoise; 
   extern float	alpha, alpha_sqrd, sigma;
   extern float   pi, pi_sqrd;
   extern double	stddev;
   extern long		temp_win, data_win;
   extern unsigned long	*g_temp,	*g_data;
   extern unsigned char	*tmp_temp, *tmp_data;

#define DEF_NUM_ITR 120
#define DEF_ALPHA 1.0
#define DEF_SIGMA 0.01
#define DEF_DT 0.000001
#define DEF_h 1
#define DEF_INC 20
#define DEF_STDDEV 20
#define DEF_BILINEAR 1
#endif	/* !_TEMPLATES_H_ */
