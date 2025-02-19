#ifndef _CVIPDRAWIMG
#define _CVIPDRAWIMG

#include "waves.h"

#ifdef __cplusplus
extern "C"{
#endif
/* primary functions */
Image *create_rectangle(int width, int height,int tlx,int tly,int sqwidth,int sqheigth);
Image *create_circle(int width, int height,int centerx,int centery,int radius);
Image *create_degenerate_circle(int width, int height,int centerx,int centery,int radius1,int radius2);
Image *create_ellipse(int width,int height,int centerrow,int centercol,int majoraxis,int minoraxis);
Image *create_line(int width, int height,int startx,int starty,int endx, int endy);
Image *create_checkboard(int width, int height,int firstx,int firsty,int blockx,int blocky);
Image *create_black(int width, int height);

/* setup functions */
Image *create_line_setup(void) ;
Image *create_rectangular_setup(void);
Image *create_circle_setup(void);
Image * create_checkboard_setup(void);

/* utility functions */
void draw_circle(Image* inputImage,int centerx,int centery,int radius);
void paint_circle(Image* inputImage,int centerx,int centery,int radius);
void paint_degenerate_circle(Image* inputImage,int centerx,int centery,int radius1, int radius2);
void draw_rectangular(Image* inputImage,int tlx,int tly,int sqwidth,int sqheigth);
void paint_rectangular(Image* inputImage,int tlx,int tly,int sqwidth,int sqheight);
void draw_line(Image* inputImage,int startx,int starty,int endx, int endy);
#ifdef __cplusplus
}
#endif 
#endif
