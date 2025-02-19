/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: scale_to_max.c
'           Description: scale_to_max function implementation
'         Related Files: CVIPC Directory
'                        Include Directory
'   Initial Coding Date: February 2013
'       Delevoping tool: Visual Studio 2010-C++
'             Credit(s): Patrick Solt
`						 Hari Siva Kumar Reddy Bhogala
'                        Southern Illinois University Edwardsville
'
' Copyright (C) 2013 Scott Umbaugh and SIUE
'
' Permission to use, copy, modify, and distribute this software and its
' documentation for any non-commercial purpose and without fee is hereby
' granted, provided that the above copyright notice appear in all copies
' and that both that copyright notice and this permission notice appear
' in supporting documentation.  This software is provided "as is"
' without express or implied warranty.
'
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''*/

#include "CVIPimage.h"

Image* draw_picture(float** map, int width, int height, int dim)
{  
	byte** data = NULL;
    int band, col, row, bound, limit;
	
	Image* ret = NULL;
    switch (dim)
    {
    case 1:
        ret = new_Image(PGM, GRAY_SCALE, 1, height, width, CVIP_BYTE, REAL);
        break;
    case 3:
        ret = new_Image(PPM, RGB, 3, height * 3, width, CVIP_BYTE, REAL);
        break;
    default:
        fprintf(stderr, "Fatal Error:cannot create a new image\n");
        return NULL;
    }
    
	
	for (band = 0; band < dim; band++)
    {
        data = (byte**)getData_Image(ret, band);
        bound = band * height;
        for (col = 0; col < width; col++)
        {
            limit = height - (map[band][col] * height);
            for (row = bound; row < (height * (band + 1)); row++)
            {
			
                if ((row - bound) >= limit)
                  {
					  data[row][col] = 255;
			
				}
				else
                    data[row][col] = 0;
            }
        }
    }
	
	
    return ret;
}

void scale_to_max(float** vec1, float** vec2, int dim, int len)
{
	int i, j;
    float max = vec1[0][0];
    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < len; j++)
        {
            if (vec1[i][j] > max)
                max = vec1[i][j];
        }
    }
	
    if (vec2 != NULL)
    {
        for (i = 0; i < dim; i++)
        {
            for (j = 0; j < len; j++)
            {
                if (vec2[i][j] > max)
                    max = vec2[i][j];
            }
        }
    }
    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < len; j++)
            vec1[i][j] /= max;
    }
    if (vec2 != NULL)
    {
        for (i = 0; i < dim; i++)
        {
            for (j = 0; j < len; j++)
                vec2[i][j] /= max;
        }
    }

	
}
