/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: hough.c
*           Description: This file contains two types of functions:
*			 hough transforms function.
*			 hough_transform takes three arguments:
*			   Image* cvipImage, contains input image data, it 
*				need to be a binary image.
*			   char *interpret,  a string which has the 
*			      corresponding bytes set to 1 to indicate which
*			      angle is of interest and should be included
*			      when hough transform is performed. It is strong
*			      recommended that user use parse_string function
*			      which it will transform a input string into
*			      the format needed by hough transform.
*			      The range is from 0 to 179 in degrees. An example
* 			      to parse string is like "-18 40-60 90 130-", which
* 			      means keep those lines whose slope are in the 
*			      range from 0 to 18, 40 to 60, 90, 130 to 179 
*			      degrees. The result string is returned from
*			      parse_string.
*			   int num, a integer to indicate the length of the 
*			      string. If you use parse_string to parse your
*			      request, this number should be 180.
*			 hough_inverse takes four arguments:
*			   Image *cvipImage, contains input image data, which
*				 should be the image got from hough_transform.
*			   int height,width the height and width of output image
*			     Normally, these two values should be set to 
*			     the size of original image(different from result
*			     image of hough_transform)
*		 	   int threshold, threshold indicating the minimum
*			      number of pixels on a line which will be kept
*			      in the result image.
*		 	 What hough_inverse does is draw lines in the output
*			 image which has pixel numbers greater than threshold.
*			 Those lines are drawn through the scope the input 
*			 image, which may not what you really desired. What you
*			 may do is bitwise AND output image with the original
*			 image to get a desired image.
*			 If you want a easy way, it is best to call hough_filter.
*			 It takes six arguments.
*			    Image *cvipImage, input image data.
*			    char *name, the name of input image.
*			    char *degree_string, string to indicate which degree
*			      is of interest. Its format is the same as the
*			      input string to parse_string function call. 
*			    int threshold, threshold indicating the minimum
*			      number of pixels on a line which will be kept
*			      in the result image.
*			    int connection, number to indicate the maxmum 
*			      distance to be linked on a line which will be
*			      kept after threshold.
*			    int interactive, indicate whether the program
*			      is performed in interactive mode. set it to 
*			      1 will make it interactive, just like in 
*			      CVIPtools, and arguments degree_string, thresold,
*			      and connection will not be used because they
*			      will be read from standard input.
*			      
*         Related Files: 
*   Initial Coding Date: Mon Jul 31 11:36:19 CDT 1995
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Kun Luo
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1995 SIUE - by Kun Luo.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
* RCS (Revision Control System) Information
* ...Added automatically by RCS 
*
* $Log: hough.c,v $
* Revision 1.18  1997/03/08 01:03:02  yawei
* Name Changes:
* 	BOOLEAN ==> CVIP_BOOLEAN
* 	FALSE ==> CVIP_NO
* 	TRUE ==> CVIP_YES
* 	BYTE ==> CVIP_BYTE
* 	SHORT ==> CVIP_SHORT
* 	INTEGER ==> CVIP_INTEGER
* 	FLOAT ==> CVIP_FLOAT
* 	DOUBLE ==> CVIP_DOUBLE
* 	TYPE ==> CVIP_TYPE
*
* Revision 1.17  1997/01/15 17:20:46  yawei
* Global Change:  IMAGE ==> Image
*
 * Revision 1.16  1996/12/24  23:22:39  yawei
 * changed function names.
 *
 * Revision 1.15  1996/12/23  17:24:57  yawei
 * removed "threshold_Image"
 *
 * Revision 1.14  1996/12/20  19:24:17  yawei
 * Use "view_Image" to display images.
 *
 * Revision 1.13  1996/09/07  00:17:04  yawei
 * changed viewer so image will be written to the temp dir
 * with correct format.
 *
 * Revision 1.12  1996/09/04  22:23:15  yawei
 * added choice to viewer
 *
 * Revision 1.11  1996/02/06  21:09:41  kluo
 * change to use display_RAMImage
 *
 * Revision 1.10  1995/07/31  17:31:43  kluo
 * add header.
 *
 * Revision 1.9  1995/07/31  17:20:56  kluo
 * add header
 *
 * Revision 1.8  1995/07/31  17:19:47  kluo
 * add header.
 * .,
 *
 * Revision 1.7  1995/06/30  18:45:12  kluo
 * add link image
 *
 * Revision 1.6  1995/06/30  17:11:51  kluo
 * fix problem of precsion
 *
 * Revision 1.5  1995/06/27  21:56:05  kluo
 * fininsh direction speiification
 *
 * Revision 1.4  1995/06/27  18:32:13  kluo
 * fix problem of overlinking
 *
 * Revision 1.3  1995/06/23  16:36:11  kluo
 * check file in
 *
 * Revision 1.2  1995/06/23  16:21:59  kluo
 * change the way to connect points
 *
 * Revision 1.1  1995/06/23  05:10:25  kluo
 * Initial revision
 *
****************************************************************************/
#include "CVIPtoolkit.h"
#include "CVIPdef.h"
#include "CVIPview.h"
#include "CVIPfs.h"

extern display_temp(char *name);

/*only pixels of 255 will be scanned, here I mean binary image is composed of
  255 and 0, not other definition*/

Image * hough_transform(Image* cvipImage,char *interpret,int num, int delta_length){
    Image *outImage,*tempImage,*out1Image;

    byte  **image_i, **image_t;
    short **image_o;
    double angle;
    int x, y,i,j, bands, rows, cols, no_of_bands,arm_length;
    float arm;

    bands = getNoOfBands_Image(cvipImage);   
    rows =  getNoOfRows_Image(cvipImage);   
    cols =  getNoOfCols_Image(cvipImage);
    if(cvipImage->bandP[0]->data_type != NULL){
	tempImage = remap_Image(cvipImage,CVIP_BYTE,0,255);
	delete_Image(cvipImage);
	cvipImage = tempImage;
    	fprintf(stderr,"Input is remapped into CVIP_BYTE");
    }
    arm = sqrt((double)rows*rows+cols*cols);
    arm_length = arm;
    outImage = new_Image(PPM,cvipImage->color_space,bands,
		  ((arm_length / delta_length) + 1),180,CVIP_SHORT,REAL);
    if(outImage == NULL){
	fprintf(stderr,"Error in allocating new image");
	return NULL;
    }
    out1Image = new_Image(PPM,cvipImage->color_space,bands,
		  ((arm_length / delta_length) + 1),180,CVIP_BYTE,REAL);
    if(out1Image == NULL){
	fprintf(stderr,"Error in allocating new image");
	return NULL;
    }
    for(no_of_bands=0;no_of_bands<bands;no_of_bands++){
	image_i = getData_Image(cvipImage,no_of_bands);
        image_o = getData_Image(outImage,no_of_bands);
    	for(y=0;y<rows;y++){
	    for(x=0;x<cols;x++){
	    	if(image_i[y][x] == 255){
		    for(i=0;i<180;i++){
			if(i<num && interpret[i] == 0)
			    continue;
			angle = (double)i*PI/180;
			j = x*cos(angle) + y*sin(angle)  ;
			if(j>=0 && j < arm_length){
			    image_o[j/delta_length][i]++;
			}
		    }
		}
	    }
	}
    }
    for(no_of_bands=0;no_of_bands<bands;no_of_bands++){
        image_o = getData_Image(outImage,no_of_bands);
	image_t = getData_Image(out1Image,no_of_bands);
    	for(y=0;y<arm_length;y++){
	    for(x=0;x<180;x++){
		if(image_o[y/delta_length][x] > 255)
		    image_t[y/delta_length][x] = 255;
		else
		    image_t[y/delta_length][x] = image_o[y/delta_length][x];
	    }
	}
    }
    delete_Image(cvipImage);
    delete_Image(outImage);
    return out1Image;
}

Image * hough_inverse(Image *cvipImage,int height, int width, int threshold, int delta_length){
    Image *outImage,*tempImage;
    byte **image_i, **image_o;
    double  angle,arm,r_cos,r_sin,test_c,test_s;
    int x, y, bands, rows,cols,no_of_bands,i,j;
 
    bands = getNoOfBands_Image(cvipImage);   
    rows =  getNoOfRows_Image(cvipImage);   
    cols =  getNoOfCols_Image(cvipImage);
    if(cvipImage->bandP[0]->data_type != NULL){
	tempImage = remap_Image(cvipImage,CVIP_BYTE,0,255);
	delete_Image(cvipImage);
	cvipImage = tempImage;
    	fprintf(stderr,"Input is remapped into CVIP_BYTE");
    }
    if(cvipImage->bands == 1)
         outImage = new_Image(PGM,cvipImage->color_space,1,
		   height,width,CVIP_BYTE,REAL);
    else
         outImage = new_Image(PPM,cvipImage->color_space,3,
		   height,width,CVIP_BYTE,REAL);
    if(outImage == NULL){
	fprintf(stderr,"Error in allocating new image");
	return NULL;
    }
    for(no_of_bands=0;no_of_bands<bands;no_of_bands++){
	image_i = getData_Image(cvipImage,no_of_bands);
        image_o = getData_Image(outImage,no_of_bands);
    	for(y=0;y<rows*delta_length;y++){
	    for(x=0;x<cols;x++){
		if(image_i[y/delta_length][x] >=(byte) threshold){
		    angle = (double)x*PI/180;
		    arm = y+0.5;
		    r_cos = cos(angle);
		    r_sin = sin(angle);
		    test_c = (r_cos > 0)? r_cos : -1*r_cos;
		    test_s = (r_sin > 0)? r_sin : -1*r_sin;
		    if(test_c < test_s){
		        for(i=0;i<width;i++){
			    j = (arm - i*r_cos)/r_sin - 0.5;
			    if(j>=0 && j < height)
			        image_o[j][i] = 255;
			    j = (arm - i*r_cos)/r_sin + 0.5;
			    if(j>=0 && j < height)
			        image_o[j][i] = 255;
		        }
		    }
		    else{
		        for(j=0;j<height;j++){
			    i = (arm - j*r_sin)/r_cos - 0.5;
			    if(i>=0 && i < width)
			        image_o[j][i] = 255;
			    i = (arm - j*r_sin)/r_cos + 0.5;
			    if(i>=0 && i < width)
			        image_o[j][i] = 255;
		        }
		    }
		}
	    }
	}
    }
    delete_Image(cvipImage);
    return outImage;
}

char* parse_string(char *input){
    int count,before,decision = 0,lower,upper;
    char *output, tempChar;
    char *ptr,temp[10],original[180];

    output = (char*)calloc(180,sizeof(char));
    memset(original,0,sizeof(original));
    ptr = input;
    while(*ptr ==' ' || *ptr == '\t')ptr++;
    if(*ptr == '\n' || *ptr == NULL){
	memset(output,1,180*sizeof(char));
	return output;
    }
    while(*ptr != NULL){
	before = -1;
	if(*ptr == '-'){
	    before = decision;
	    ptr++;
	}
	while(*ptr ==' ' || *ptr == '\t')ptr++;
	count = 0;
	while(isdigit(*ptr))
	    temp[count++] = *ptr++;
	temp[count] = NULL;
  	if(count != 0){
	    sscanf(temp,"%d",&decision);
	    if(decision <= 179){
		if(before == -1)
		    original[decision] = 1;
		else{
		    lower = (before < decision)?before:decision;
		    upper = (before > decision)?before:decision;
		    memset(&original[lower],1,(upper-lower+1) 
				*sizeof(char));
		    before = -1;
		}
	    }
	    else{
		 decision = 179;
		 original[decision] = 1;
	    }
	}
        while(*ptr ==' ' || *ptr == '\t')ptr++;
	if(*ptr == NULL)
	    break;
    }
    if(before != -1)
	memset(&original[before],1,(180 - before)*sizeof(char));
    memcpy(output,&original[90],90*sizeof(char));
    memcpy(&output[90],original,90*sizeof(char));
	for (count = 1; count <= 89; count++) {
		tempChar = output[90 - count];
		output[90 - count] = output[90 + count];
		output[90 + count] = tempChar;
	}
    return output;
}
	
	    

Image *hough_filter(Image *cvipImage, char *name, char *degree_string, 
	int threshold, int connection, int interactive, 
	int delta_length, int SegmentLength, int intermediate_result){
    Image *outImage, *tempImage,*tempImage1,*houghImage;
    char temp_name[100], direct[150],specification[300], *interpret;
    byte **image_i, **image_o,**image_t;
    int x, y, bands, rows,cols,no_of_bands,i,j,arm_length,flag;
    float  r_cos,r_sin, test_c, test_s,angle,arm;
    int u_x, u_y, d_x, d_y,r_i,r_j;
	int startRow, endRow, tempRow, startCol, endCol, tempCol;

	if (intermediate_result <= 0) {
		intermediate_result = 100; //Return the final image by default
	}
	if (delta_length <= 0) {
		delta_length = 1; //Prevent 'devision by 0' fatal error
	}

    bands = getNoOfBands_Image(cvipImage);   
    rows =  getNoOfRows_Image(cvipImage);   
    cols =  getNoOfCols_Image(cvipImage);
    if(cvipImage->bandP[0]->data_type != NULL){
	tempImage = remap_Image(cvipImage,CVIP_BYTE,0,255);
	delete_Image(cvipImage);
	cvipImage = tempImage;
    	fprintf(stderr,"Input Image is remapped into CVIP_BYTE\n");
    }
    if(interactive){
	fflush(stdin);
	fprintf(stderr,"\n\nNow please specify the orientation which you are interested in x-y coordinates( the same as that of your input image).");
	fprintf(stderr,"The range is from 0 to 179 in degrees\n");
	fprintf(stderr,"\tAn example like \"-18 40-60 90 130-\", which means keep  those lines whose slope are in the range from 0 to 18, 40 to 60, 90, 130 to 179 degrees\n");
        gets(specification);
        interpret = parse_string(specification);
    }
    else{
	interpret = parse_string(degree_string);
    }
    tempImage = (Image*)duplicate_Image(cvipImage);
    cvipImage = hough_transform(cvipImage,interpret,180, delta_length);
    if(*name != NULL)
	strcpy(temp_name,name);
    else
        strcpy(temp_name,"UNKNOWN");
    strcat(temp_name,"-HOUGH");
    fprintf(stderr,"Displaying  Hough transform image...\n");

	if (intermediate_result <= 1) {
		return cvipImage; //1st intermediate result, "Hough transformed image"
	}
	
    if(interactive){
	fflush(stdin);
	fprintf(stderr,"Enter the value for minimum number of pixels per line:");
	scanf("%d",&threshold);
	fprintf(stderr,"Enter the maximum connection distance(in pixels):");
	scanf("%d",&connection);
    }
    houghImage = duplicate_Image(cvipImage);
    cvipImage = hough_inverse(cvipImage,rows,cols,threshold, delta_length);

	if (intermediate_result <= 2) {
		return cvipImage; //2nd intermediate result, "Inverse Hough image"
	}

    tempImage1 = duplicate_Image(cvipImage); 
    for(no_of_bands=0;no_of_bands<bands;no_of_bands++){
	image_i = getData_Image(cvipImage,no_of_bands);
        image_o = getData_Image(tempImage,no_of_bands);
	image_t = getData_Image(tempImage1,no_of_bands);
    	for(y=0;y<rows;y++){
	    for(x=0;x<cols;x++){
		image_t[y][x] = image_i[y][x] & image_o[y][x];
	    }
	}
    }

	if (intermediate_result <= 3) {
		return tempImage1; //3rd intermediate result, "after_and"
	}
	
    delete_Image(cvipImage);
    delete_Image(tempImage);
    tempImage = duplicate_Image(tempImage1);
    arm_length = houghImage->bandP[0]->rows;
    for(no_of_bands=0;no_of_bands<bands;no_of_bands++){
	image_i = getData_Image(houghImage,no_of_bands);
	image_o = getData_Image(tempImage1,no_of_bands);
	image_t = getData_Image(tempImage,no_of_bands);
	for(y=0;y<rows;y++){
	    for(x=0;x<cols;x++){
		if(image_o[y][x] == 255){
		    int high_degree = houghImage->bandP[0]->cols;
		    u_x = x - connection;
		    u_y = y - connection;
		    d_x = x + connection;
		    d_y = y + connection;
		    u_x =   (u_x >= 0) ? u_x : 0;
		    u_y =   (u_y >= 0) ? u_y : 0;
		    d_x = (d_x < cols) ? d_x : cols-1;
		    d_y = (d_y < rows) ? d_y : rows-1;
		    for(i=0;i<high_degree;i++){
			angle = (double)i*PI/180;
			j = (x*cos(angle) + y*sin(angle)) ;
			if(j>=0&&j<arm_length&&image_i[j/delta_length][i]>=(byte)threshold){
			    r_cos = cos(angle);
			    r_sin = sin(angle);
			    arm = x*r_cos + y*r_sin;
			    test_c = (r_cos > 0)? r_cos : -1*r_cos;
			    test_s = (r_sin > 0)? r_sin : -1*r_sin;
			    flag = 0;
			    if(test_c < test_s){
			        for(r_i=u_x;r_i<= x;r_i++){
				    r_j = (arm - r_i*r_cos)/r_sin ;
				    if(r_j>=u_y && r_j<=d_y ){
					if(flag == 1){
						if (image_t[r_j][r_i] == 0)
					    image_t[r_j][r_i] = 255;
					}
//					else if(image_t[r_j][r_i] == 255 ||	image_o[r_j][r_i] == 255)
					else if(image_o[r_j][r_i] == 255){
					    flag = 1;
					}
				    }
			        }
				flag = 0;
			        for(r_i=d_x;r_i>=x;r_i--){
				    r_j = (arm - r_i*r_cos)/r_sin ;
				    if(r_j>=u_y && r_j<=d_y ){
					if(flag == 1){
						if (image_t[r_j][r_i] == 0)
					    image_t[r_j][r_i] = 255;
					}
//					else if(image_t[r_j][r_i] == 255 ||	image_o[r_j][r_i] == 255)
					else if(image_o[r_j][r_i] == 255){
					    flag = 1;
					}
				    } 
			        }
			    }
			    else{
			        for(r_j=u_y;r_j<= y;r_j++){
				    r_i = (arm - r_j*r_sin)/r_cos ;
				    if(r_i>=u_x && r_i<=d_x ){
					if(flag == 1){
						if (image_t[r_j][r_i] == 0)
					    image_t[r_j][r_i] = 255;
					}
//					else if(image_t[r_j][r_i] == 255 ||	image_o[r_j][r_i] == 255)
					else if(image_o[r_j][r_i] == 255){
					    flag = 1;
					}
				    } 
			        }
				flag = 0;
			        for(r_j=d_y;r_j>=y;r_j--){
				    r_i = (arm - r_j*r_sin)/r_cos ;
				    if(r_i>=u_x && r_i<=d_x ){
					if(flag == 1){
						if (image_t[r_j][r_i] == 0)
					    image_t[r_j][r_i] = 255;
					}
//					else if(image_t[r_j][r_i] == 255 ||	image_o[r_j][r_i] == 255)
					else if(image_o[r_j][r_i] == 255){
					    flag = 1;
					}
				    } 
			        }
			    }
			}
		    }

		}
	    }
	}
    }
    
	if (intermediate_result <= 4) {
		return tempImage; //4th intermediate result, "after connection"
	}
	
	/* copy image_t to image_0 and set image_t[y][x]  to 0 */
    for(no_of_bands=0;no_of_bands<bands;no_of_bands++){
		image_o = getData_Image(tempImage1,no_of_bands);
		image_t = getData_Image(tempImage,no_of_bands);
		for(y=0;y<rows;y++){
			for(x=0;x<cols;x++){
				image_o[y][x] = image_t[y][x];
				image_t[y][x] = 0;
			}
		}
	}

    for(no_of_bands=0;no_of_bands<bands;no_of_bands++){
	image_o = getData_Image(tempImage1,no_of_bands);
	image_t = getData_Image(tempImage,no_of_bands);
	for(y=0;y<rows;y++){
	    for(x=0;x<cols;x++){
		if(image_o[y][x] == 255){
		    int high_degree = houghImage->bandP[0]->cols;
		    for(i=0;i<high_degree;i++){
				if(interpret[i] == 0) {
					continue;
				}
				
				j = i > 90 ? 270 - i : 90 - i;

				angle = (double)j*PI/180;
				r_cos = cos(angle);
				r_sin = sin(angle);
				arm = y*r_cos + x*r_sin;

				if (j >= 45 && j < 135) {
					startRow = y;
					startCol = (arm - startRow * r_cos) / r_sin ;
					tempRow = startRow;
					tempCol = startCol;

					do {
						endRow = tempRow;
						endCol = tempCol;
						tempRow ++;
						tempCol = (arm - tempRow * r_cos) / r_sin ;
					} while (tempRow >= 0 && tempRow < rows && tempCol >= 0 && tempCol < cols && (image_o[tempRow][tempCol] == 255));

					if ((abs(startRow - endRow) + 1) > SegmentLength || (abs(startCol - endCol) + 1) > SegmentLength) {
						for(r_j=startRow;r_j<= endRow;r_j++){
							r_i = (arm - r_j*r_cos)/r_sin ;
							image_t[r_j][r_i] = 255;
						}
					}
				} else {
					startCol = x;
					startRow = (arm - startCol * r_sin) / r_cos ;
					tempRow = startRow;
					tempCol = startCol;

					do {
						endRow = tempRow;
						endCol = tempCol;
						tempCol ++;
						tempRow = (arm - tempCol * r_sin) / r_cos ;
					} while (tempRow >= 0 && tempRow < rows && tempCol >= 0 && tempCol < cols && (image_o[tempRow][tempCol] == 255));

					if ((abs(startRow - endRow) + 1) > SegmentLength || (abs(startCol - endCol) + 1) > SegmentLength) {
						for(r_i=startCol;r_i<= endCol;r_i++){
							r_j = (arm - r_i*r_sin)/r_cos ;
							image_t[r_j][r_i] = 255;
						}
					}
				}
		    }

		}
	    }
	}
    }
    free(interpret);
	delete_Image(houghImage);
    delete_Image(tempImage1);
    
    return tempImage; // Final result "after extinct"
}	    
      
			
Image* edge_link_filter(Image *cvipImage, int connection){
    Image *outImage;
    byte  **image_i, **image_o;
    int x,y,rows,cols,no_of_bands,bands,i,j,u_x,u_y,d_x,d_y;
    int y_inc,x_inc,x_abs,y_abs,r_i,r_j,direction;
    float slope;

    bands = getNoOfBands_Image(cvipImage);   
    rows =  getNoOfRows_Image(cvipImage);   
    cols =  getNoOfCols_Image(cvipImage);
    if(cvipImage->bandP[0]->data_type != CVIP_BYTE){
	fprintf(stderr,"Image will be remapped into CVIP_BYTE\n");
	outImage = remap_Image(cvipImage,CVIP_BYTE,0,255);
	delete_Image(cvipImage);
	cvipImage = duplicate_Image(outImage);
    }
    else
    	outImage = duplicate_Image(cvipImage);
    for(no_of_bands=0;no_of_bands<bands;no_of_bands++){
	image_i = getData_Image(cvipImage,no_of_bands);
	image_o = getData_Image(outImage,no_of_bands);
	for(y=0;y<rows;y++){
	    for(x=0;x<cols;x++){
		if(image_i[y][x] == 255){
		    u_x = x - connection;
		    u_y = y - connection;
		    d_x = x + connection;
		    d_y = y + connection;
		    u_x =   (u_x >= 0) ? u_x : 0;
		    u_y =   (u_y >= 0) ? u_y : 0;
		    d_x = (d_x < cols) ? d_x : cols-1;
		    d_y = (d_y < rows) ? d_y : rows-1;
		    for(j=u_y;j<=d_y;j++){
			for(i=u_x;i<=d_x;i++){
			    if(image_i[j][i] == 255 && !(i==x && j==y)){
				x_inc = x - i;
				y_inc = y - j;
				x_abs = abs(x_inc);
				y_abs = abs(y_inc);
				if(x_abs > y_abs){
				    direction = (x_inc > 0)? 1 : -1;
				    slope = (float)y_inc/x_inc;
				    for(r_i=i;r_i!=x;r_i+=direction){
					r_j=slope*(r_i-i)+j;
					image_o[r_j][r_i] = 255;
				    }
				}
				else{
				    direction = (y_inc > 0)? 1 : -1;
				    slope = (float)x_inc/y_inc;
				    for(r_j=j;r_j!=y;r_j+=direction){
					r_i=slope*(r_j-j)+i;
					image_o[r_j][r_i] = 255;
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    delete_Image(cvipImage);
    return outImage;
}
			
Image* link_Setup(Image *cvipImage){
    int length;
    fflush(stdin);
    printf("Enter the maximum linking distance:");
    scanf("%d",&length);
    return edge_link_filter(cvipImage, length);
}


