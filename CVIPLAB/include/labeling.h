#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPimage.h"

/* Global Variant */

Matrix *pMLabel;
byte ** pImageMatrix;
byte **newImageMatrix;
int **pLabel;           /* labeling matrix containing labeling information */
Image * outImage;
int no_of_rows, no_of_cols, no_of_bands;

int counter = 1;        /*objects number in the image*/

int convex = 0;         /*convexities number for each object*/
int concav = 0;         /*concavities number for each object in the image*/
