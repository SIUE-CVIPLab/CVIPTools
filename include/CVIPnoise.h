#ifndef _CVIPNOISE
#define _CVIPNOISE

#include "CVIPtoolkit.h"
#include "CVIPimage.h"
#include <limits.h>

#ifndef Pi
#define Pi 3.1415926
#endif

#define FS 8000
#define NOISE 100*cos(2*Pi*T*1000/FS)
#define trunc(x) (((x) > 255) ? 255:(((x) < 0) ? 0:(x)))

#ifdef __cplusplus
extern "C"{
#endif 

Image *gamma_noise(Image *imageP,float *var,int *alpha);
Image *gaussian_noise(Image *imageP,float *var,float *mean);
Image *neg_exp_noise(Image *imageP,float *var);
Image *rayleigh_noise(Image *imageP,float *var);
Image *speckle_noise(Image *imageP,float *psalt,float *ppepper);
Image *uniform_noise(Image *imageP,float *var,float *mean);

/* setup functions for backward compatibility, not encouraged to be used in
 * new programs 
 */
Image *gamma_noise_setup(Image *imageP);
Image *gaussian_noise_setup(Image *imageP);
Image *neg_exp_noise_setup(Image *imageP);
Image *rayleigh_noise_setup(Image *imageP);
Image *speckle_noise_setup(Image *imageP);
Image *uniform_noise_setup(Image *imageP);
#ifdef __cplusplus
}
#endif 

#endif
