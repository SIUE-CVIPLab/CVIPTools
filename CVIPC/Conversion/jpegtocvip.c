#include "CVIPjpeg.h"
#include "CVIPcompress.h"
#include "CVIPtyp.h"
#include "CVIPimage.h"


Image *jpgtocvip(char *filename, int colors, CVIP_BOOLEAN blocksmooth, CVIP_BOOLEAN grayscale, 
                 CVIP_BOOLEAN nodither, CVIP_BOOLEAN verbose) {
    
    Image *cvipImage;
    cvipImage = jpg_decompress(filename, -1, CVIP_NO, CVIP_NO, CVIP_NO,
		 CVIP_NO);
    return cvipImage;

}
