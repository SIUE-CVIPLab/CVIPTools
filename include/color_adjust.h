/*	Arve Kjoelen - Thu Oct 12 10:39:10 CDT 1995 */
#if !defined( CVIP_COLOR_ADJUST )
   #define CVIP_COLOR_ADJUST

   extern Image *balance_RGB_Setup(Image *inIm);
   extern float *aver_region(Image *inIm, int xin, int yin, int xfin, int yfin);
   extern void balance_RGB_Image(Image *inIm, float *averages);
#endif
