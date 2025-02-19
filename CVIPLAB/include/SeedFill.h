#if !defined( SEEDFILL_DEFINED )

   #define SEEDFILL_DEFINED

   typedef int Pix;		/* 1-channel frame buffer assumed */

   typedef struct {		/* window: a discrete 2-D rectangle */
      int x0, y0;			/* xmin and ymin */
      int x1, y1;			/* xmax and ymax (inclusive) */
   } Window;

   extern int fill( byte **dP, int x, int y, Window *win, Pix nv);
   extern void fillContour_Border(Border imageP, int nv, int x, int y, 
   int x_min, int y_min, int x_max, int y_max);


#endif
