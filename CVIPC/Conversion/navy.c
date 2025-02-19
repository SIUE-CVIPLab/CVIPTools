/*									*
* ===================================================================== *
* = Computer Vision / Image Processing Tool - Dr. Scott Umbaugh, SIUE = *
* ===================================================================== *
*									*
* File Name:	navy.c							*
*									*
* Description:	Contains routine to convert an image in SAFVR format to *
*		a CVIPtools native structure.				*
*									*
* Credits:	Lance Kendrick, Arve Kjoelen				*
*									*
* Diagnostics:  The image returned by safvrtocvip() is of type PPM.	*
*		Thus, we are presently (2/2/96) not supporting the	*
*		writing of images in the SAFVR format.			*
*		In addition, the current routine (2/2/96) only supports *
*		Gray-scale SAFVR images.				*
*									*
************************************************************************/
#include	"CVIPimage.h"
#include	"CVIPconutils.h"
#include        <stdio.h>
#include 	<string.h>


Image *safvrtocvip(char *filename, FILE* in, int showmessages )
{
    Image *outIm;
    COLOR_FORMAT format;
    int     i_num, iscolor, dig_band;
    int     xsize, ysize;
    char *data;

    i_num = getw( in     );
    iscolor = getw( in     );
    dig_band = getw( in     );
    xsize = getw( in     );
    ysize = getw( in     );

    if (showmessages) {
        fprintf( stdout, "Loading SAFVR Image file %s:\n", filename );
        fprintf( stdout, "\tPhysicalImageNumber:  %d\n", i_num );
        fprintf( stdout, "\t            IsColor:  %d\n", iscolor );
        fprintf( stdout, "\t       DigitizeBand:  %d\n", dig_band );
        fprintf( stdout, "\t              XSize:  %d\n", xsize );
        fprintf( stdout, "\t              YSize:  %d\n", ysize );
    }
        if(iscolor) format=RGB;
	else format=GRAY_SCALE; 
	outIm=(Image *)new_Image(PGM,format,(1+2*iscolor),ysize,xsize,CVIP_BYTE,REAL);
        data = (char *)malloc( (1+2*iscolor) * (xsize*ysize*sizeof(char)) );
        fread( data, sizeof(char), (1+2*iscolor) * (xsize*ysize), in );
	   memcpy((void *)outIm->image_ptr[0]->rptr[0],(const void *)(data),sizeof(char)*ysize*xsize);

        free(data);
        return(outIm);
}
