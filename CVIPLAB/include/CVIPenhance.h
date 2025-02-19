/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: CVIPenhance.h
*           Description: contains function prototypes, constants and types
*			 defined in threshold.c
*         Related Files: compliment.c
*   Initial Coding Date: Tue Apr 27 21:49:42 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Srini
*                        Southern Illinois University @ Edwardsville
*
* RCS (Revision Control System) Information
* ...Added automatically by RCS 
*
** $Log: CVIPenhance.h,v $
 * Revision 1.5  1997/01/15  17:12:05  yawei
 * Global Change:  IMAGE ==> Image
 *
 * Revision 1.4  1996/12/24  22:29:25  yawei
 * Changed filename:
 *    image_enhance.h ==> CVIPenhance.h
 *
 * Revision 1.3  1996/12/24  22:27:52  yawei
 * void image_smooth( Image *srcImage ) ==>
 * Image *smooth_filter(Image *inputImage,int kernel)
 *
 * Revision 1.2  1996/12/24  22:12:04  yawei
 * added median_hist
 *
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
 * Revision 1.1  1993/04/29  06:54:22  hanceg
 * Initial revision
 *
*
****************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif 

extern Image *smooth_filter(Image *inputImage,int kernel);
extern Image *median_hist(Image *srcImage);

/* setup function for backward compabibility, new applications shouldn't use
 * them
 */
extern Image *smooth_setup(Image *inputImage);

#ifdef __cplusplus
}
#endif 
