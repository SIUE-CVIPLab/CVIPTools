/******************************************************************************
    ======================================================================
    Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
    ======================================================================
 
                   Name: fft_phase.c
          Expanded Name: extract phase of fft
 
             Parameters: <fftImage> - Pointer to a complex image structure
			 <remap_norm> - 
			   0 = remaps the phase data and returns a CVIP_BYTE image
	                   1 = normalizes the magnitude, using value of k, 
			       returns a complex image
			 <k> - constant to normalize the magnitude
 
                Returns: a complex or CVIP_BYTE image
 
            Description: None
 
            Diagnostics: None
 
    Initial Coding Date: 12/1/96
Last Modifications Made: 12/5/96
             References: None
 
                 Author: Wenxing Li
 
 
          Southern Illinois University @ Edwardsville
 
*******************************************************************************/ 

#include <math.h>
#include "CVIPimage.h"


Image * remap_Image(const Image *, CVIP_TYPE, long, long);

#ifndef M_PI
#define M_PI            3.14159265358979323846
#endif

#ifndef M_PI_4
#define M_PI_4          0.78539816339744830962
#endif

/* return a complex image */
static Image * norm_magnitude(Image * fftImage, float f)
{ Image 	*  returnImage;
  float		   theta;
  int		   i, j, k;
  float 	** rp,  ** ip;
  unsigned int	   rows, cols;

  returnImage = duplicate_Image(fftImage);
  rows = returnImage->image_ptr[0]->rows;
  cols = returnImage->image_ptr[0]->cols;

  for (k=0; k<returnImage->bands; k++)
    { rp = (float **)returnImage->image_ptr[k]->rptr;
      ip = (float **)returnImage->image_ptr[k]->iptr;
      for (i=0; i<rows; i++)
        for (j=0; j<cols; j++)
	  { theta = atan2(ip[i][j], rp[i][j]);
	    rp[i][j] = f * cos(theta);
	    ip[i][j] = f * sin(theta);
	  }
    }

  return returnImage;
}

static void prep_phase(Image * fftImage, Image ** dImage, Image ** iImage,
			int rows, int cols)
{ float		dconst = -(M_PI + M_PI_4);
  float		iconst = M_PI_4 - M_PI; 
  int		i, j, k;
  float	     ** dimage,  ** iimage;	

  *dImage = new_Image(fftImage->image_format, fftImage->color_space, 
			 fftImage->bands, rows, cols, CVIP_FLOAT, REAL);

  *iImage = new_Image(fftImage->image_format, fftImage->color_space, 
			 fftImage->bands, rows, cols, CVIP_FLOAT, REAL);

  for (k=0; k<fftImage->bands; k++)
    { dimage = (float **)(*dImage)->image_ptr[k]->rptr;
      iimage = (float **)(*iImage)->image_ptr[k]->rptr;
      for (i=0; i<rows; i++)
        for (j=0; j<cols; j++)
	  { dimage[i][j] = dconst;
	    iimage[i][j] = iconst;
	  }
    }
}

static Image * combine_phase(Image * decImage, Image * incImage)
{ Image		 * rdecImage,  * rincImage;
  int		   i, j, k;
  byte		** dimage,  ** iimage;
  unsigned int	   rows, cols;

  rows = incImage->image_ptr[0]->rows;
  cols = incImage->image_ptr[0]->cols;

  rdecImage = remap_Image(decImage, CVIP_BYTE, 0, 255);
  rincImage = remap_Image(incImage, CVIP_BYTE, 0, 255);

  for (k=0; k < incImage->bands; k++)
    { dimage = (byte **)rdecImage->image_ptr[k]->rptr;
      iimage = (byte **)rincImage->image_ptr[k]->rptr;
      for (i=0; i<rows; i++)
        for (j=0; j<cols; j++)
  	  if (dimage[i][j] > iimage[i][j])
	    iimage[i][j] = dimage[i][j];
    }

  delete_Image(decImage);
  delete_Image(incImage);
  delete_Image(rdecImage);

  return (rincImage);
}

/* return a CVIP_BYTE image */
static Image * remap_phase(Image * fftImage)
{ 
	Image 	 * decImage,  * incImage;
  float		   theta;
  float		   conrad = M_PI_4 - M_PI;
  int		   i, j, k;
  float 	** rp,  ** ip;
  float	        ** dimage,  ** iimage;
  unsigned int	   rows, cols;

  rows = fftImage->image_ptr[0]->rows;
  cols = fftImage->image_ptr[0]->cols;
 
  prep_phase(fftImage, &decImage, &incImage, (int)rows, (int)cols);

 for (k=0; k < fftImage->bands; k++)
    { rp = (float **)fftImage->image_ptr[k]->rptr;
      ip = (float **)fftImage->image_ptr[k]->iptr;
      dimage = (float **)decImage->image_ptr[k]->rptr;
      iimage = (float **)incImage->image_ptr[k]->rptr;

      for (i=0; i<rows; i++)
        for (j=0; j<cols; j++)
	  { theta = atan2(ip[i][j], rp[i][j]);
	    if (theta < conrad) theta += 2*M_PI;
	    if (theta < M_PI_4) iimage[i][j] = theta;
	    else		dimage[i][j] = 0 - theta;
	  }
    }

  return (combine_phase(decImage, incImage));
}

Image * fft_phase(Image * fftImage, int remap_norm, float k)
{
   if (fftImage->image_ptr[0]->data_format != COMPLEX)
     { fprintf(stderr, "Input image should be a complex image\n");
       return NULL;
     }

   if (remap_norm) return (norm_magnitude(fftImage, k));
   else return (remap_phase(fftImage));
}
