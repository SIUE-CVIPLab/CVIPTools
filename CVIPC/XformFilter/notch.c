/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: notch.c
*           Description: This file contain function calls that implement
*			 notch filter. The name of the function is
*			 notch. 
*			 There are five arguments to this function call.
*			    Image *cvipImage, input image data, must be
*				  output of some tranform function.
*			    char  *name	, the name of the image.
*			    NOTCH_ZONE *zone, a data structure containing
*				  information about which part of image
*				   be removed.  The declaration is as follows:
*				typedef struct {
*					int x;
*					int y;
*					int radius;
*				} NOTCH_ZONE;
*			    int number, how many of NOTCH_ZONE.
*			    CVIP_BOOLEAN interactive, whether the function is 
*				    executed in interactive mode or not.
*				    interactive = CVIP_YES will make function
*				    interactively.
*				if the program is executed in interactive
*				mode, you will be asked for which area be
*				removed, as in CVIPtools, and in this case,
*				the content of argument zone, number will 
*				be ignored.
*			 
*         Related Files: CVIPxforfilter.h
*   Initial Coding Date: Thu Jul 27 15:54:47 CDT 1995
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
** $Log: notch.c,v $
** Revision 1.14  1997/03/08 17:03:32  yawei
** Swaped CVIP_YES and CVIP_NO
**
** Revision 1.13  1997/03/08 00:53:29  yawei
** Name Changes:
** 	BOOLEAN ==> CVIP_BOOLEAN
** 	FALSE ==> CVIP_YES
** 	TRUE ==> CVIP_NO
** 	BYTE ==> CVIP_BYTE
** 	SHORT ==> CVIP_SHORT
** 	INTEGER ==> CVIP_INTEGER
** 	FLOAT ==> CVIP_FLOAT
** 	DOUBLE ==> CVIP_DOUBLE
** 	TYPE ==> CVIP_TYPE
**
** Revision 1.12  1997/01/15 17:14:04  yawei
** Global Change:  IMAGE ==> Image
**
 * Revision 1.11  1997/01/02  17:00:05  akjoele
 * lint fixes.
 *
 * Revision 1.10  1996/12/31  22:21:56  yawei
 * Notch_Image ==> notch
 *
 * Revision 1.9  1996/12/28  06:53:15  yawei
 * *** empty log message ***
 *
 * Revision 1.8  1995/10/30  17:01:11  kluo
 * change the way to check data format
 *
 * Revision 1.7  1995/10/30  16:52:35  kluo
 * check file into RCS.
 * I don't know the difference who added CVIPmap.h
 *
 * Revision 1.6  1995/07/27  23:10:06  kluo
 * modify header
 *
 * Revision 1.5  1995/07/27  21:10:49  kluo
 * add header
 *
*
****************************************************************************/
#include <CVIPmatrix.h>
#include <CVIPmap.h>
#include <CVIPxformfilter.h>
#include <string.h>


Image* notch(Image *cvipImage, char *name, NOTCH_ZONE *zone,int number,
		 CVIP_BOOLEAN interactive){
    float **image_r, **image_i;
    int rows, cols, bands, no_of_bands,x,y,result,temp;
    int count,temp_x,temp_y,temp_xd,temp_yd;
    int have_imag = 0;

    rows = getNoOfRows_Image(cvipImage);
    cols = getNoOfCols_Image(cvipImage);
    no_of_bands = getNoOfBands_Image(cvipImage);
    temp = (rows>cols)?rows:cols;
    result = 2;
    while(result<temp) 
      	result*=2;

    if(interactive == CVIP_YES){
	fprintf(stderr,"Computing log-map image\n");
	cvipImage = logMap_Image(cvipImage, -1);
     	number = get_notch_input(&zone,result);
    }
    if(cvipImage->bandP[0]->data_format == COMPLEX)
	have_imag = 1;

    for(bands = 0; bands < no_of_bands; bands++){
	image_r = getData_Image(cvipImage,bands);
	if (have_imag) 
	    image_i = getImagData_Image(cvipImage,bands);
	for(count = 0; count < number; count++){
	    temp = zone[count].radius;
	    temp_x = zone[count].x + temp;
	    temp_y = zone[count].y + temp;
	    temp_xd = zone[count].x - temp;
	    temp_yd = zone[count].y - temp;
	    if(temp_x >= result) temp_x = result-1;
	    if(temp_y >= result) temp_y = result-1;
	    if(temp_xd < 0) temp_xd = 0;
	    if(temp_yd < 0) temp_yd = 0;
	    for(y = temp_yd;y<=temp_y;y++){
		for(x = temp_xd;x<=temp_x;x++){
		    image_r[y][x] = 0;
		    if(have_imag)
		        image_i[y][x] = 0;
		}
	    }
	}
    }
    free(zone);
    return cvipImage;

}

    
int get_notch_input(NOTCH_ZONE **zone,int size){
    struct link_zone  *head,*next_one;
    int number = 0,count;
    int x,y,diameter;
    
    head =(struct link_zone *)malloc(sizeof(struct link_zone));
    head->next = NULL;
    next_one = head;
    printf("\nEnter the position for those areas you want to get rid of from the spectrum.");
    printf("\nWhen you are asked for the size, you need to enter the block size of the area centered at the x,y coordinate you want to remove.\n");
    while(1){
	printf("Enter the x coordinate:");
	scanf("%d",&x);
	printf("Enter the y coordinate:");
	scanf("%d",&y);
	printf("Enter the size:");
	scanf("%d",&diameter);
	next_one->area.x = x;
	next_one->area.y = y;
	next_one->area.radius = diameter/2;
	number++;
	fflush(stdin);
 	printf("Do you want to enter another set of data?(y/n)");
	if(getchar()== 'n')
	    break;
	next_one->next = (struct link_zone*)malloc(sizeof(struct link_zone));
	next_one = next_one->next;
	next_one->next = NULL;
    }
    *zone = (NOTCH_ZONE *)malloc(sizeof(NOTCH_ZONE)*number);
    next_one = head;
    for(count = 0; count < number; count++){
	((NOTCH_ZONE*)(*zone))[count] = next_one->area;
	next_one = next_one->next;
    }
    while(head != NULL){
	next_one = head->next;
	free(head);
	head = next_one;
    }
 
    return number;
}
 
	

   
