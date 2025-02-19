/******************************************************************************
    ======================================================================
    Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
    ======================================================================

                   Name: RST_feature.c
          Expanded Name: RST invariant features

             Parameters: Pointer to the labeled image of type IMAGE 
                         coordinates of the point on the labled image to
                         select the object of interest:
                         r -- row coordinate, c -- column coordinate

                Returns: pointer to an array containing seven RST invariant features.

            Description: Moments are extracted features that are derived from the raw
			 measurements and that, in 2-D, may be used to achieve rotation(R),
			 scale(S), translation (T) (or position) invariant.

            Diagnostics: None

    Initial Coding Date: 6/21/96
Last Modifications Made: 7/12/96
             References: None

              Author(s): Jihong Zhou


          Southern Illinois University @ Edwardsville

*******************************************************************************/

#include <math.h>
#include "CVIPimage.h"

double * rst_invariant( Image *label_image, int r, int c)   
{
        int            **image;        /* 2-d matrix data pointer */
         
        int             y,              /* row index */
                        x,              /* column index */
                        p, 
                        q,
                        i, j, label;

        double        * ptr;   
        double          moment[2][2],	  /* zeroth moment and first moment */
                        moment1[4][4],    /* central moment */
                        moment2[4][4];    /*normalization of central moment*/

        unsigned int    rows,           /* number of rows in image */
                        cols;           /* number of columns in image */
        
        rows =  getNoOfRows_Image(label_image);
        cols =  getNoOfCols_Image(label_image);

        ptr = (double *)malloc(7 * sizeof(double));
	for (i=0; i<7; i++) ptr[i] = 0.0;

	for (i=0; i<2; i++) 
	  for (j=0; j<2; j++) moment[i][j] = 0.0;

        for (i=0; i<4; i++) 
          for (j=0; j<4; j++) {moment1[i][j] = 0.0; moment2[i][j] = 0.0;}
 
         /*
        ** compares the pixel value at the location (y,x)
        ** with the threshold value. If it is greater than
        ** the threshold value it writes 255 at the location
        ** else 0
        */
        image = (int **)getData_Image(label_image, 0);
	label = image[r][c];

        for(p=0; p <= 1; p++){   
          for(q = 0; q <= 1; q++){
            for(y = 1; y < rows; y++) {
              for(x = 1; x < cols; x++) {
                       
        if(image[y][x] == label){
                                       
        moment[p][q] = moment[p][q] + pow(x, p) * pow(y, q)*1;   /* for binary image, cosider binary patterns. where f(x, y)= 1 or 0, here 1 is white, 0 is black */
                                                        
                          }                   
                        }
                      }
                    }
		  }
                                  
        for(p=0; p <= 3; p++){   
          for(q = 0; q <= 3; q++){
            for(y = 1; y < rows; y++) {
              for(x = 1; x < cols; x++) {
 
        if(image[y][x] == label){
                                             
         moment1[p][q] =
 moment1[p][q] + pow((x-(moment[1][0]/moment[0][0])), p)*pow( (y-(moment[0][1]/moment[0][0])), q) *1 ;  /* for binary image, cosider binary patterns. where f(x, y)= 1 or 0, here 1 is white, 0 is black */

                         }
                       }
                     }
                   }
                 }

        for(p=0; p < 4; p++){   
          for(q = 0; q < 4; q++){
              if((p+q) == 2 || (p+q) == 3){
                 moment2[p][q]=moment1[p][q]/pow(moment1[0][0],((p+q)*0.5)+1);                                      
                     }             
                   }
                 }
                                
                
        ptr[0] = moment2[2][0] + moment2[0][2];

        ptr[1] = (moment2[2][0]-moment2[0][2])*(moment2[2][0]-moment2[0][2])+4*(moment2[1][1])*(moment2[1][1]);

        ptr[2] = 
(moment2[3][0]-3*moment2[1][2])*(moment2[3][0]-3*moment2[1][2]) + (3*moment2[2][1]-moment2[0][3])* (3*moment2[2][1]-moment2[0][3]) ;

        ptr[3] = 
(moment2[3][0]+moment2[1][2])*(moment2[3][0]+moment2[1][2])+(moment2[2][1]+moment2[0][3])*(moment2[2][1]+moment2[0][3]);

        ptr[4] =
(moment2[3][0] - 3*moment2[1][2])*(moment2[3][0] + moment2[1][2])*((moment2[3][0] + moment2[1][2])*(moment2[3][0] + moment2[1][2])- 3*(moment2[2][1]+moment2[0][3])*(moment2[2][1]+moment2[0][3])) + (3*moment2[2][1] - moment2[0][3])*(moment2[2][1] + moment2[0][3])*(3*(moment2[3][0] + moment2[1][2])*(moment2[3][0] + moment2[1][2]) - (moment2[2][1]+moment2[0][3])*(moment2[2][1]+moment2[0][3]));
  
        ptr[5] = 
(moment2[2][0] - moment2[0][2])*((moment2[3][0] + moment2[1][2])*(moment2[3][0] + moment2[1][2])- (moment2[2][1]+moment2[0][3])*(moment2[2][1]+moment2[0][3])) + 4*(moment2[1][1]) * (moment2[3][0] + moment2[1][2])*(moment2[2][1] + moment2[0][3]);

        ptr[6] = 
(3*moment2[2][1] - moment2[0][3])*(moment2[3][0] + moment2[1][2])* ((moment2[3][0] + moment2[1][2])* (moment2[3][0] + moment2[1][2])- 3*(moment2[2][1] +moment2[0][3])*(moment2[2][1] +moment2[0][3])) - (moment2[3][0] - 3*moment2[1][2])*(moment2[2][1] + moment2[0][3])*(3*(moment2[3][0] + moment2[1][2])*(moment2[3][0] + moment2[1][2]) - (moment2[2][1] + moment2[0][3])*(moment2[2][1] + moment2[0][3])); 
        
                                      
        return ptr;
}    
/*
** end of rst_features function
*/
