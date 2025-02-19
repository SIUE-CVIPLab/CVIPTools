/****************************************************************
*								*
*  ===========================================================  *
*  	 MASTER'S THESIS - ARVE KJOELEN, SIUE			*
*  ===========================================================  *
*								*
*	FILE NAME: wavelet.h					*
*								*
*	DESCRIPTION: Header file containing filter coefficients *
*	for several wavelets, as well as function prototypes	*
*								*
*	AUTHOR: Arve Kjoelen, SIUE				*
*								*
*	RELATED FILES: wavelet.c				*
*								*
*	INITIAL CODING DATE: 10/06/93				*
*								*
*	LAST MODIFICATIONS MADE: 10/06/93			*
*								*
*	REFERENCES:  The daubechies filter coefficients are	*
*	from the paper "Orthogonal bases for compactly 		*
*	supported wavelets", by Ingrid Daubechies.		*	
*								*
*								*
*								*
****************************************************************/

#if !defined( CVIPWAVELETS_DEFINED)
   #define CVIPWAVELETS_DEFINED

   #include "CVIPimage.h"
   #define C0 0.4829629131445341
   #define C1 0.8365163037378079
   #define C2 0.2241438680420134
   #define C3 -0.1294095225512604


   static float daub6[] = {0.332670552950, 0.806891509311, 0.459877502118, -0.135011020010, -0.085441273882, 0.035226291882};

   static float daub8[] = {0.230377813309, 0.714846570553, 0.630880767930, -0.027983769417, -0.187034811719, 0.030841381836, 0.032883011667, -0.010597401785};

   static float daub10[] = {0.160102397974, 0.603829269797, 0.724308528438, 0.138428145901, -0.242294887066, -0.032244869585, 0.077571493840, -0.006241490213, -0.012580751999};

   static float daub12[] = {0.111540743350, 0.494623890398, 0.751133908021, 0.315250351709, -0.226264693965, -0.129766867567, 0.097501605587, 0.027522865530, -0.031582039318, 0.000553842201, 0.004777257511, -0.001077301085};

   static float daub14[] = {0.077852054085, 0.396539319482, 0.729132090846, 0.469782287405, -0.143906003929, -0.224036184994, 0.071309219267, 0.080612609151, -0.038029936935, -0.016574541631, 0.012550998556, 0.000429577973, -0.001801640704, 0.000353713800};

   static float daub16[] = {0.054415842243, 0.312871590914, 0.675630736297, 0.585354683654, -0.015829105256, -0.2840155542962, 0.000472484574, 0.128747426620, -0.017369301002, -0.044088253931, 0.013981027917, 0.008746094047, -0.004870352993, -0.000391740373, 0.000675449406, -0.000117476784};

   static float daub18[] = {0.038077947364, 0.243834674613, 0.604823123690, 0.657288078051, 0.133197385825, -0.293273783279, -0.96840783223, 0.148540749338, 0.030725681479, -0.067632829061, 0.0002509471115, 0.022361662124, -0.004723204758, -0.004281503682, 0.001847646883, 0.000230385764, -0.000251963189, 0.000039347320};

   static float daub20[] = {0.026670057901, 0.188176800078, 0.527201188932, 0.688459039454, 0.281172343661, -0.249846424327, -0.195946274377, 0.127369340336, 0.093057364604, -0.071394147166, -0.029457536822, 0.033212674059, 0.003606553567, -0.010733175483, 0.001395351747, 0.001992405295, -0.000685856695, -0.000116466855, 0.000093588670, -0.000013264203};

   /* Function Prototypes */
   extern float *get_wav_filter(int nn);
   extern float *get_bandpass_filter(float *hn, int nn);
   extern float *get_transpose_filter(float *h, int nn);
   extern void do_haarwavl(float *a, float *wksp, unsigned n, int isign);
   extern void do_wavtgeneric(float *a, float *wksp, unsigned n, int isign, int    filter_size, float *lpf, float *hpf, int center);
   extern void wavtgeneric(MATRIX *matrix, unsigned n, int isign, int lowband,    int filter_size, float *lpf, float *hpf);
   extern void partial_transpose(MATRIX *matrix, int nn);
   extern void do_daub4(float *a, float *wksp, unsigned n, int isign);

   extern Image *wavdaub4_transform(Image *image, int isign, int lowband);
   extern Image *wavhaar_transform(Image *image, int isign, int lowband);

   extern Image *wav_setup(Image *image, CVIP_BOOLEAN *remap);
   extern int wvq_compress(Image *image, int choice,char *name);
   extern Image *wvq_decompress(Image *image,char *name);
#endif
