/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: compliment.h
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
** $Log: waves.h,v $
** Revision 1.3  1996/12/16 23:26:27  yawei
** Changed function names:
**   sine_wave_sep            ==> create_sine
**   square_wave_sep          ==> create_squarewave
** added
**   cosine_wave_sep          ==> create_cosine
**
 * Revision 1.2  1995/04/22  19:46:39  luok
 * change the declaration of those two function.
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

extern Image *create_sine(int img_size, int frequency, int choice);
extern Image *create_squarewave(int img_size, int frequency, int choice);
extern Image *create_cosine(int img_size, int frequency, int choice);

/* setup functions for interactive programs, not encouraged to use */
extern Image *create_sine_sep();
extern Image *create_squarewave_sep();
extern Image *create_cosine_sep();
#ifdef __cplusplus
}
#endif 
