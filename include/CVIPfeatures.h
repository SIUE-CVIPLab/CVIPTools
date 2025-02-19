/**************************************************************************** 
*  ====================================================================== 
*  Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE 
*  ======================================================================
*             File Name: CVIPfeatures.h
*           Description: contains function prototypes, constants and types
*			 defined in centroid.c
*         Related Files: and.c, ht_wd.c, skew.c, centroid.c, mean.c, thresh.c*
*                        euler.c, moments.c, variance.c, feature.c,  
*                        no_white_black.c, feature_mod.c, perimeter.c
*
*   Initial Coding Date: 6/6/94
*           Portability: Standard (ANSI) C
*             Credit(s): Kun Luo
*         
*                        This head file is established to replace the original
*                        multiple head files.
*                       
*                        Southern Illinois University @ Edwardsville
*
*
*                         $Log: CVIPfeatures.h,v $
 * Revision 1.3  1997/01/15  17:13:16  yawei
 * Global Change:  IMAGE ==> Image
 *
 * Revision 1.2  1995/08/07  21:04:25  kluo
 * change to gray_level for thiness and irregular
 *
 * Revision 1.1  1995/08/07  18:07:03  kluo
 * Initial revision
 *
 * Revision 1.2  1994/11/24  00:15:57  luok
 * second revision
 *
 * Revision 1.1  1994/11/23  23:33:46  luok
 * Initial revision
 *
*
****************************************************************************/

#ifndef  _CVIPFEATURE
#define  _CVIPFEATURE

#include "newfeature.h"

#ifdef __cplusplus
extern "C"{
#endif 

extern long area(Image* labeled, int r, int c);
extern double aspect(Image* labeled, int r, int c);
extern Image* an_d(Image* srcImage, Image* threshImage);
extern int* centroid(Image* labeled, int r, int c);
extern int euler(Image* labeled, int r, int c);
extern int Euler_Setup(Image* cvipImage);
extern int Find_euler(Image* cvipImage, int gray_level);
extern float Find_irregular(Image* inputImage, int gray_level);
extern long Find_perimeter(Image* input_Image, int gray_level);
extern float Find_thinness(Image* inputImage, int gray_level);
extern long GrayPerimeter_Setup(Image* cvipImage);
extern double* hist_feature(Image* image, Image* labeled, int r, int c);
extern int* ht_wd(Image* srcImage);
extern double irregular(Image* labeled, int r, int c);
extern float Irregular_Setup(Image* inputImage);
extern Image* label(const Image* image);
extern double* laws_texture(Image* image, Image* labeled_image, int r, int c, int windowsize, int vector1, int vector2);
extern float* mean(Image* image);
extern double* moments(Image* image);
extern long int* no_white_black(Image* image);
extern Image* object_feature(Image* image, Image* original, char* name);
extern double orientation(Image* labeled_image, int r, int c);
extern int perimeter(Image* labeled, int r, int c);
extern int* projection(Image* labeled, int r, int c, int height, int width);
extern double* rst_invariant(Image* labeled, int r, int c);
extern float* skew(Image* image);
extern double thinness(Image* labeled, int r, int c);
extern float Thinness_Setup(Image* image);
extern Image* thresh(int a, int b, Image* labeled);
extern float* variance(Image* image);


#ifdef __cplusplus
}
#endif 

#endif
