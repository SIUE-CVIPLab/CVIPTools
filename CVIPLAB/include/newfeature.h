/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: newfeature.h
*
*           Description: defines struture POWER for spectral_feature.c
*                        
*         Related Files: spectral_feature.c
*
*   Initial Coding Date: 6/16/96
*
*             Author(s): Wenxing Li
*
*
*         Southern Illinois University @ Edwardsville
*
*
****************************************************************************/


typedef struct
{
 int		no_of_sectors;
 int		no_of_bands;
 int		imagebands;
 double	      *	dc;
 double	      * sector;
 double	      * band;
} POWER;
#ifdef __cplusplus
extern "C"{
#endif 

POWER * spectral_feature(Image * originalImage, Image * labeledImage, int no_of_bands,
              int no_of_sectors, int r, int c);
#ifdef __cplusplus
}
#endif 

