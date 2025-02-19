/***************************************************************************
* =========================================================================
*
*   Computer Vision and Image Processing Lab - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: local_adaptive_zoom.c
*           Description: Zoom using Locally Adaptive method
*   Initial Coding Date: Jan 20, 2005
*           Portability: Standard (ANSI) C
*                        
*				Name   : Pradnya Deokar
*						 Southern Illinois University at Edwardsville
*               Date   : Feb 3, 2006
*
** Copyright (c) 2006, SIUE - Scott Umbaugh, Pradnya Deokar
****************************************************************************/

/*
** include header files
*/

#include <math.h>
#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPimage.h"
#include "ObjectContour.h"
#include "CVIPfeatures.h"
#include "CVIPmatrix.h"

#define CASE_MAX 255
#define T1  200
#define T2  45





Image *local_adaptive_zoom(Image *inputImage){
    float 		**image; 
	float		**image1; /* 2-d matrix data pointer */
    Image       *outputimage;
	char        *outputfile;
	CVIP_TYPE	inputDataType;
	
	
	signed int 		r,rx,cx,i,c,bands;	
			
    signed int 	no_of_rows,	/* number of rows in image */
			    no_of_cols,	/* number of columns in image */
			    no_of_bands; /* number of image bands */
			
	signed int  w2,h2;
				 
	
	int a, b, c1,d ,h1, h, v1, v2;
	

		

    /*
    ** Gets the number of image bands (planes)
    */
    no_of_bands = getNoOfBands_Image(inputImage);

    /* 
    ** Gets the number of rows in the input image  
    */
    no_of_rows =  getNoOfRows_Image(inputImage);

    /* 
    ** Gets the number of columns in the input image  
    */
    no_of_cols =  getNoOfCols_Image(inputImage);



   	
	
// output image size, rows and columns

	w2 = 2 * no_of_rows;
	h2 = 2 * no_of_cols;  
    

	inputDataType = getDataType_Image(inputImage);
	if(inputDataType!=CVIP_FLOAT)
		cast_Image(inputImage, CVIP_FLOAT);

//  constucting Output image structure	

  outputimage =  new_Image(PPM,RGB,no_of_bands,w2,h2,CVIP_FLOAT,REAL);

 
  
//--------------------------------------------------------------------------------------
//                          First Stage
//           First double image by interpolating zeroes 
//--------------------------------------------------------------------------------------
  
  for(bands=0; bands < no_of_bands; bands++) {
	     image1 = getData_Image(outputimage, bands);
	       for ( r=0; r< (w2); r++)
		     for (c=0; c< (h2); c++)
		 	   image1[r][c] =  0;
  }

  
  for(bands=0; bands < no_of_bands; bands++) {
	image = getData_Image(inputImage, bands);
	image1 = getData_Image(outputimage, bands);
	 for ( r=0,rx=0; r< (w2),rx < no_of_rows; r=r+2, rx++)
		 for (c=0,cx = 0; c< (h2),cx < no_of_cols; c=c+2, cx++)
		 	 
		   image1[r][c] = image[rx][cx];
		   
     for ( c=0,r=1;r < w2-1 ; r= r+2)
		  image1[r][c] = image1[r-1][c];

	 for ( r=0,c=1;c < h2-1 ; c= c+2)
		  image1[r][c] = image1[r][c-1];



  }

//---------------------------------------------------------------------------------------
//                         Second Stage
//   
//---------------------------------------------------------------------------------------		



for (i=0;i< 20 ; i++)
{	
  for(bands=0; bands < no_of_bands; bands++) {
	     image1 = getData_Image(outputimage, bands);
	       for ( r=1; r< (w2-1); r=r+1)
		     for (c=1; c< (h2-1); c=c+1)
			 {
				a = image1[r-1][c-1];
				b = image1[r-1][c+1];
				c1 = image1[r+1][c-1]; 
				d = image1[r+1][c+1];
			    h = image1[r-1][c] ;
				h1 = image1[r+1][c];
				v1 = image1[r][c-1];
				v2 = image1[r][c+1];
				
			if (image1[r][c] == 0)
			{
				if (h == 0   &&   h1 ==0  &&   v1 == 0   &&   v2 == 0) 
				{
					   // If a,b,c1,d are uniform then

				 if( abs(a-b)<T1 && abs(b-c1)<T1 && abs(c1-d)<T1 && abs(d-a)<T1 && abs(a-c1)<T1 && abs(b-d)<T1 )
							
					     image1[r][c] = (a+b+c1+d) / 4 ;
			//----------------------------------------------------------------------------------------
				
                else //  If there is edge SW-NE
			 	  if( (abs(a-d) > T2)   &&   (abs(a-d) > ( abs(b-c1) + 80 )))
				     
					  image1[r][c]  = ( b + c1 ) / 2 ;
				   
			//----------------------------------------------------------------------------------------
				  
				  
				  else //  If there is edge NW-SE
			 	   if( (abs(b-c1 ) > T2)   &&   (abs(a-d) <= ( abs(b-c1) + 80 )))
										
				       image1[r][c]  = ( a + d) / 2 ;
					   
					
			//--------------------------------------------------------------------------------------
					 
				   else // If there is edge NS
			 			if( (abs(a-d) > T1) && (abs(b-c1) > T1) && ((b-c1) * (a-d)) > 0 )
						{
							image1[r-1][c]  = (a + b) / 2 ;
							image1[r+1][c] = (c1 + d)/2;
						}

			//-----------------------------------------------------------------------------------		 
						
						else // If there is edge  EW
			 			if( (abs(a-d) > T1) && (abs(b-c1) > T1) && ((b-c1) * (a-d)) < 0 )
						{
							image1[r][c-1]  = (a+ c1) / 2 ;
							image1[r][c+1] = (b + d)/2;
						}
				  				  
				}
			}
		
		
				 
			 }
	  
		 }
  
}
//-----------------------------------------------------------------------------------------
//                                Third stage
//            
//---------------------------------------------------------------------------------------

    for (i=0;i< 10  ; i++)
	{
       for(bands=0; bands < no_of_bands; bands++) {
	     image1 = getData_Image(outputimage, bands);
	       for ( r=1; r< (w2-1); r=r+1)
		     for (c=1; c< (h2-1); c=c+1)
			 {
				a = image1[r-1][c-1];
				b = image1[r-1][c+1];
				c1 = image1[r+1][c-1]; 
				d = image1[r+1][c+1];
			    h = image1[r-1][c] ;
				h1 = image1[r+1][c];
				v1 = image1[r][c-1];
				v2 = image1[r][c+1];
				
			if (image1[r][c] == 0)
				{
				  if (a == 0 && b ==0 && c1 == 0 && d == 0) 
					if( h != 0 && h1 != 0  && v1 != 0 && v2 != 0 )

						
					  if( (abs(h-h1) >  T2) && (abs(h-h1) > (abs(v1-v2) + 50) ))
						  						
				    	  image1[r][c] = (v1 + v2 ) / 2 ;
				 
                      else
						   if ( (abs(v1-v2) >  T2) && (abs(v1-v2) > (abs(h-h1) + 50) ))
							   image1[r][c] = (h + h1 ) / 2 ;
    					   else 
							   image1[r][c] = 0;

                    else 
					
						if ( v1==0 || v2==0)
							if ( abs(h-h1) < T1 )
								image1[r][c] = (h + h1 ) / 2 ;
							else 
								image1[r][c] = 0;
						else
							if ( h==0 || h1==0)
								 if ( abs(v1 - v2) < T1 )
								image1[r][c] = (v1 + v2 ) / 2 ;
							  else 
								image1[r][c] = 0;
						    else 
							image1[r][c] = 0;


			}

		}

  } 

  
} 

//--------------------------------------------------------------------------------------------------
//                         Fourth stage
//   Fixing the pixels which left out through previous stages
//--------------------------------------------------------------------------------------------------
			 	  
				  	
//							
	for(bands=0; bands < no_of_bands; bands++) {
	     image1 = getData_Image(outputimage, bands);
	       for ( r=1; r< (w2-1); r=r+1)
		     for (c=1; c< (h2-1); c=c+1)
			 {
				a = image1[r-1][c-1];
				b = image1[r-1][c+1];
				c1 = image1[r+1][c-1]; 
				d = image1[r+1][c+1];
			    h = image1[r-1][c] ;
				h1 = image1[r+1][c];
				v1 = image1[r][c-1];
				v2 = image1[r][c+1];
				
			if (image1[r][c] == 0)
				{
	  if ((h == 0   &&   h1 ==0)  ||  ( v1 == 0   &&   v2 == 0) )
		  image1[r][c] = ( a + b+ c1 + d) / 4;
	  else
		  image1[r][c] = ( h1 + h + v1 + v2) / 4;
					  

			}

		}

  }
 
  
//---------------------------------------------------------------------------------------
//                       Remapping output image to BYTE
//---------------------------------------------------------------------------------------
   
	if(inputDataType == CVIP_BYTE)
		return remap_Image(outputimage, CVIP_BYTE, 0, 255);
	else
		return outputimage;
		

}

//---------------------------------------------------------------------------------------