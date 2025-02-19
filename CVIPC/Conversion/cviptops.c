/***************************************************************************
* =========================================================================
*
*   Computer Vision and Image Processing Lab - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: cviptops.c
*           Description: Converts a Image to a PostScript format  
*   Initial Coding Date: Feb 22, 2001
*           Portability: Standard (ANSI) C
*             Credit(s): Ragavendar Swamisai 
*                        Southern Illinois University at Edwardsville
*
****************************************************************************/

/*
** include header files
*/

#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPimage.h"

int PureFlag = FALSE;
int ZoomFlag = FALSE;



#define   USABLEHEIGHT   756
#define   USABLEWIDTH   576
#define   PAGEHEIGHT   792
#define   PAGEWIDTH   612
#define   ONEINCH      72

void cviptops(Image *inputImage,char *outputfile_name){

    Image *outputImage;
    IMAGE_FORMAT format1;
    COLOR_FORMAT color;
    CVIP_TYPE  type;
    FORMAT form;
    
    char function_name[] = {"cviptops"};

    int index;
    float xscale, yscale, scale = 1.0;
    int x1, x2, y1, y2;

    int 		r,		/* row index */
    c,  	        /* column index */
    bands;		/* band index */

    int                 Min,Max;
    int                 Scale;
    unsigned int        no_of_rows,no_of_cols,no_of_bands;
    FILE                *fd;
    byte		**image,**image1,**Red,**Green,**Blue;



    /*
    ** Gets the number of rows in the input image 
    */

    no_of_rows =  getNoOfRows_Image(inputImage);

    /*
    ** Gets the number of columns in the input image 
    */

    no_of_cols =  getNoOfCols_Image(inputImage);

    format1 = getFileFormat_Image(inputImage);

    type= getDataType_Image(inputImage);
    color=getColorSpace_Image(inputImage);
    form= getDataFormat_Image(inputImage);
    no_of_bands = getNoOfBands_Image(inputImage);
    outputImage=new_Image(format1,color,no_of_bands,no_of_rows,no_of_cols,type,form);
    if(no_of_bands >1)
    {
        Red = getData_Image(inputImage,0);
        Green = getData_Image(inputImage,1);
        Blue = getData_Image(inputImage,2);
    }
    for(bands=0; bands < no_of_bands; bands++) {
        image = getData_Image(inputImage,bands);
        image1= getData_Image(outputImage,bands);



        /* Scale input image to 0..255 if needed */
        Min = Max = image[0][0];
        for (r = 0; r < no_of_rows; r++)
            for (c = 0; c < no_of_cols; c++)
                if (Min > image[r][c])
                    Min = image[r][c];
                else if (Max < image[r][c])
                    Max = image[r][c];
    }

    if (Max > Min)
        Scale = (float) (255.0 / (Max - Min));
    else
        Scale = 1.0;


    for(bands=0; bands < no_of_bands; bands++) {
        for (r = 0; r < no_of_rows; r++){
            for (c = 0; c < no_of_cols; c++)
            {
                image[r][c] = (byte) ROUND((image[r][c] - Min) * Scale);

            }
        }
    }

    fd = fopen(outputfile_name,"w");

    /* Calculate bounding box */
    x1 = (int) ((PAGEWIDTH - no_of_cols * scale) / 2),
         y1 = (int) ((PAGEHEIGHT - no_of_rows * scale) / 2);
    x2 = x1 + no_of_cols;
    y2 = y1 + no_of_rows;

   printf("cviptops:opening PostScript(PS) output file - %s.\n",outputfile_name) ;
   printf("cviptops:writing %dx%d gray scale image data.\n",no_of_rows,no_of_cols);
   printf("cviptops:8 bits per sample.\n");
   printf("cviptops:1 sample per pixel.\n");


    
    /* Write out introductory comments */
    fprintf(fd, "%%%!PS-Adobe-2.0 EPSF-2.0\n");
    fprintf(fd, "%%%%Creator IMPS version 2.0\n");
    fprintf(fd, "%%%%BoundingBox: %d %d %d %d\n", x1, y1, x2, y2);
    fprintf(fd, "%%%%Pages: 1\n");
    fprintf(fd, "%%%%EndComments:\n");
    fprintf(fd, "%%%%EndProlog:\n");
    fprintf(fd, "%%%%Page: 1 1:\n");
    fprintf(fd, "/origstate save def\n");
    fprintf(fd, "20 dict begin\n");

    /* Write out image title */
    if (PureFlag == FALSE)
    {
        fprintf(fd, "\n");
        fprintf(fd, "/Helvetica findfont 12 scalefont setfont\n");
        fprintf(fd, "%d 0 sub\n", PAGEWIDTH);
        fprintf(fd, "2 div\n");
        fprintf(fd, "%d moveto\n", y1 - ONEINCH / 4);
        fprintf(fd, "0 setgray\n");

    }

    /* Write out image display program */

    fprintf(fd, "\n");
    fprintf(fd, "/pix %d string def\n", no_of_cols);
    fprintf(fd, "%d %d translate\n", x1, y1);
    fprintf(fd, "%d %d scale\n", (int) (no_of_cols * scale), (int) (no_of_rows *
            scale));
    fprintf(fd, "%d %d 8\n", no_of_cols, no_of_rows);
    fprintf(fd, "[%d 0 0 -%d 0 %d]\n", no_of_cols, no_of_rows,no_of_rows);
    fprintf(fd, "   {currentfile pix readhexstring pop   }\n");
    if(no_of_bands>1)
    {
        fprintf(fd, "false 3\n");
        fprintf(fd, "colorimage\n\n");
    }
    else
    {
        fprintf(fd, "image\n\n");
    }


    /* Write out pixel information */


    for(r=0;r<no_of_rows;r++){
        for(c=0;c<no_of_cols;c++){
            if(no_of_bands > 1)
            {
                fprintf(fd,"%02x", (byte) Red[r][c]);
                fprintf(fd,"%02x", (byte) Green[r][c]);
                fprintf(fd,"%02x", (byte) Blue[r][c]);
            }
            else
            {
                fprintf(fd,"%02x", (byte) image[r][c]);
            }
        }
        fprintf(fd, "\n");
    }


    /* Print postscript footer information */
    fprintf(fd, "\n");
    fprintf(fd, "showpage\n");
    fprintf(fd, "end\n");
    fprintf(fd, "origstate restore\n");
    fprintf(fd, "%%%%Trailer\n");
}
