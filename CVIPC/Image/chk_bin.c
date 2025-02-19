/*''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
' ======================================================================
' Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
' ======================================================================
'
'             File Name: chk_bin.c
'           Description: chk_bin function implementation
'         Related Files: CVIPC Directory
'                        Include Directory
'   Initial Coding Date: February 2013
'       Delevoping tool: Visual Studio 2010-C++
'             Credit(s): Patrick Solt
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

int chk_bin(Image* image)
{
    unsigned char levels[2];
    unsigned char **pixeldata;
    int i, is_binary, numlevels = 0;
    unsigned int band, bands = (unsigned int)image->bands;
    unsigned int row, rows = image->image_ptr[0]->rows;
    unsigned int col, cols = image->image_ptr[0]->cols;

    if (image->image_ptr[0]->data_type != CVIP_BYTE)
        return 0;

    for (band = 0; band < bands; band++)
    {
        pixeldata = (unsigned char**)getData_Image(image, band);
        for (row = 0; row < rows; row++)
        {
            for (col = 0; col < cols; col++)
            {
                is_binary = 0;
                for (i = 0; i < numlevels; i++)
                {
                    if (pixeldata[row][col] == levels[i])
                    {
                        is_binary = 1;
                        break;
                    }
                }
                if (is_binary == 0)
                {
                    if (numlevels == 2)
                        return 0;

                    levels[numlevels++] = pixeldata[row][col];
                }
            }
        }
    }
    return 1;
}
