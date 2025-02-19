/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: splitNmerge.c
*           Description: split and merge segmentation routine based on an
*			 algorithm presented in "Algorithms for Graphics and
*			 Image Processing" by T. Pavlidis.
*         Related Files: splitNmerge.h, Imakefile
*   Initial Coding Date: Tue Jun  1 12:02:19 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Gregory Hance
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1993 SIUE - by Gregory Hance.
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
** $Log: splitnMerge.c,v $
** Revision 1.6  1997/07/18 15:15:37  wzheng
** memory free on quadROI
**
** Revision 1.5  1997/03/08 17:01:16  yawei
** Swaped CVIP_YES and CVIP_NO
**
** Revision 1.4  1997/03/08 00:44:23  yawei
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
** Revision 1.3  1997/01/15 17:08:58  yawei
** Global Change:  IMAGE ==> Image
**
 * Revision 1.2  1996/12/23  00:46:53  yawei
 * Changed header file splitnMerge.h ==> split_merge.h
 *
 * Revision 1.1  1994/10/30  17:58:22  hanceg
 * CVIPtools1.0 source file - G. Hance
 *
 * Revision 1.1  1993/06/02  04:48:34  hanceg
 * Initial revision
 *
*
****************************************************************************/
#include "CVIPtoolkit.h"
#include "CVIPtools.h"
#include "CVIPimage.h"
#include "CVIPdef.h"
#include "CVIPtyp.h"
#include "split_merge.h"

/* 
** private function members 
*/
static CVIP_BOOLEAN ispowerof2(unsigned int value);
static void split(QUAD *parentQUAD, Stack sP);
static void draw(Image *srcImage, QUAD *quadROI);
static QUAD_LIST form_quad_list(unsigned int level, unsigned int width, unsigned int height, unsigned int *no_of_regions);
static void free_Quad( void *objP );

/****************************************************************
                   Name: split_merge_generic
          Expanded Name: split and merge
             Parameters: <srcImage> - pointer to Image structure (where each
			 dimension must be a power of 2).
			 <pt> - pointer to function to perform predicate test
			 <pt_paramP> - pointer to an array of values that will
			 be used as the third argument to pt(....).
			 <level> - level at which to begin split and merge
			 procedure (0 ... 2^n (^ => "power of")) where n is
			 the image dimension.
                Returns: a linked list of quad trees
            Description: performs split and merge segmentation based on an
			 algorithm presented in "Algorithms for Graphics and
			 Image Processing" by T. Pavlidis. The algorithm
			 begins by merging all regions of size 2^(n-q) that
			 satisfy a homogeneity criterion set by the predicate
			 test pt(...). All regions not satisfying the merge
			 criterion will serve as the root node of a quad tree
			 that is formed by recursively splitting each region
			 into adjoint quadrants until all regions satisfy the
			 predicate test. The predicate test pt(...) sets the 
			 criterion for splitting and merging. Two sample
		         predicate test modules are provided (see
			 predicate_test(...) and mean_test(...) for the
			 expected format ). The predicate test is seperate so 
			 that users may define their own homogeneity criteria.  
			 To reconstruct the image from the quad tree 
			 representation, pass the linked list of quad trees 
			 (QUAD_LIST) returned by split_merge_generic(...) to
			 quadtree2ras(...) (see quadtree2ras(...) below. )
	    Diagnostics: returns NULL pointer with corresponding error message
			 if the <srcImage> does not meet the required format
			 (i.e. dimensions are not power of 2, etc.)
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

QUAD_LIST 
split_merge_generic(
	Image *srcImage,
	CVIP_BOOLEAN (*const pt)(Image *, QUAD *, void *),
        void *pt_paramP,
	unsigned int level
)
{
	QUAD_LIST 	rootQUAD, quadROI, mergeQUAD, quadP;
   	QUAD 		*quadNODE;
	Stack		sP;
   	const char 	*fn = "split_merge_generic";
   	unsigned int 	no_of_regions, width, height, merge_no=0, merge_size,
			max_level;
   	double 		log_2;
   	register int 	i, j;

   	width = srcImage->bandP[0]->cols; 
   	height = srcImage->bandP[0]->rows;

   /*	if( !ispowerof2(width) || !ispowerof2(height) ) {
      		fprintf(stderr, "\n%s: width and height of image must be power of 2.\n",fn);
      		fprintf(stderr, "%s: returning to CVIPtools menu...\n\n",fn);
      		return(NULL);
   	}
*/
   	max_level = MIN(LOG2(width),LOG2(height));

   	if(level > max_level) {
 /*    		fprintf(stderr, "\n%s: maximum level of %u has been exceeded.\n",fn,max_level); */
 /*    		fprintf(stderr, "%s: choose a lower level (0 <-> %u).\n",fn,max_level); */
 /*    		fprintf(stderr, "%s: returning to CVIPtools menu...\n\n",fn); */
      		return(NULL);
    	}
/*      	msg_CVIP(fn, "\nforming quad list at level %d ...\n", level); */
   	mergeQUAD = quadROI = rootQUAD = form_quad_list(level, width, height, &no_of_regions);

/*   	if(no_of_regions > 1) {
      		msg_CVIP(fn, "searching list for regions that can be merged\n");
      		msg_CVIP(fn, "out of %d possible regions...\n",no_of_regions);
   	}
*/
 
	if(no_of_regions > 1) {

   		for(i=0; i < no_of_regions; i+=4) {

      			quadROI->q->dx <<= 1;
      			quadROI->q->dy <<= 1;

			if( pt( srcImage, quadROI->q, pt_paramP ) ) {

         			if(i) {
            				mergeQUAD->next = quadROI;
            				mergeQUAD = mergeQUAD->next;
         			}
         			for(j=0; j < 3; j++) {
            				quadROI = quadROI->next;
            				quadP = quadROI->next;
            				free(quadROI->q);
            				/*free(quadROI);*/
         			}
        			quadROI = quadP;
         			merge_no++;
      			}
      			else {
         			quadROI->q->dx >>= 1;
         			quadROI->q->dy >>= 1;

         			if(i) {
            				mergeQUAD->next = quadROI;
            				mergeQUAD = mergeQUAD->next;
         			}

         			quadROI = quadROI->next;

         			for(j=0; j < 3; j++, quadROI=quadROI->next, mergeQUAD=mergeQUAD->next) 
            				mergeQUAD->next = quadROI;
      			}
   		}
	}

	mergeQUAD->next = NULL;
/*	msg_CVIP(fn, "%u regions merged.\n", merge_no<<2);
	msg_CVIP(fn, "proceeding to split remaining %u regions...\n\n", no_of_regions-(merge_no<<2));
*/
   	quadROI = rootQUAD;
       /* Added by arve, 10/13/95: */
	
	mergeQUAD = rootQUAD;
   	sP = new_Stack();

   	merge_size = (width>>level) << 1;

   	while(quadROI != NULL) {

      		if( quadROI->q->dx != merge_size ) {

         		push_Stack(sP, quadROI->q);   
   
         		while(!isempty_Stack(sP)) {

            			quadNODE = pop_Stack(sP);
            
            			if( pt( srcImage, quadNODE, pt_paramP ) 
					|| quadNODE->dx==1 
                                	|| quadNODE->dy==1 ) {
	       					quadNODE -> upper_left = NULL;
      	       					quadNODE -> upper_right = NULL;
	       					quadNODE -> lower_left = NULL;
               					quadNODE -> lower_right = NULL;
            			}
            			else 
					{
              				split( quadNODE, sP );
					}
        	 	}

      		}
   		quadROI = quadROI->next;
   	}

	if(quadROI) free(quadROI);
	delete_Stack(sP, &free_Quad);
/*
return rootQUAD;
Following added by Arve 10/13/95 */
return(mergeQUAD); 
}


/****************************************************************
                   Name: form_quad_list
          Expanded Name: form quad list
             Parameters: <level> - level at which to form list
			 <width> - width of image
			 <height> - height of image
			 <no_of_regions> - holds value of the number of regions
			 contained in the list
                Returns: pointer to a linked list of QUAD nodes.
            Description: forms a quad list that will be used for merging.
	    Diagnostics: nada.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

static QUAD_LIST 
form_quad_list(
	unsigned int 	level,
	unsigned int 	width, 
	unsigned int 	height, 
	unsigned int 	*no_of_regions)
{
   	unsigned int dx, dy, jinc, iinc;
   	QUAD_LIST listQUAD, quadP;
   	register int i, j, k, l;

   	dx = width >> level;
   	dy = height >> level;

   	*no_of_regions = (level) ? (2<<(2*level - 1)) : 1;

   	jinc = dy<<1;
   	iinc = dx<<1;

   	listQUAD = (QUAD_LIST) malloc(sizeof(struct quad_list_item));
   	quadP = listQUAD;

   	if(level) {
      	for(j=0; j < height ; j+=jinc)
         	for(i=0; i < width; i+=iinc)
            		for(k=0; k < 2; k++)
               			for(l=0; l < 2; l++, quadP=quadP->next) {
                  		quadP->q = (QUAD *) malloc(sizeof(QUAD));

                  		quadP->q->dx = dx;
                  		quadP->q->dy = dy;
                  		quadP->q->x  = i + l*dx;
                  		quadP->q->y  = j + k*dy;

                  		quadP->q->upper_left = quadP->q->upper_right = NULL;
                  		quadP->q->lower_left = quadP->q->lower_right = NULL;
 
                  		quadP->next = (QUAD_LIST) malloc(sizeof(struct quad_list_item));
               			}

      	free(quadP);
   	}
   	else {
      		quadP->q = (QUAD *) malloc(sizeof(QUAD));
      		quadP->q->dx = dx;
      		quadP->q->dy = dy;
      		quadP->q->x  = quadP->q->y  = 0;
      		quadP->q->upper_left = quadP->q->upper_right = NULL;
      		quadP->q->lower_left = quadP->q->lower_right = NULL;
   	}

   	return listQUAD;
}
   
/****************************************************************
                   Name: split
          Expanded Name:  "
             Parameters: <parentQUAD> - pointer to quad tree node
                Returns: nada.
            Description: assigns 4 children to the node of a quad tree and
			 initializes each new node with the proper size.
	    Diagnostics: none.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

static void 
split(
	QUAD 	*parentQUAD,
	Stack	sP
)
{
   	QUAD 		*childQUAD;        /* Break region up into quadrants */
   	int 		region_number;
   	unsigned int 	dx, dy;
   	char 		*fn = "split";

   	dx = (unsigned int) parentQUAD->dx >> 1;
   	dy = (unsigned int) parentQUAD->dy >> 1;

   	for(region_number=1; region_number<=4; region_number++) {                                
         	childQUAD = (QUAD *) malloc (sizeof(QUAD));
         	childQUAD->dx = dx;
         	childQUAD->dy = dy;
	 	if( (childQUAD->dx==0) || (childQUAD->dy==0) ) {
/*	    		fprintf(stderr, "parentQUAD->dx = %d\n", parentQUAD->dx);
	    		fprintf(stderr, "parentQUAD->dy = %d\n", parentQUAD->dy);
	    		fprintf(stderr, "parentQUAD->y = %d\n", parentQUAD->y);
	    		fprintf(stderr, "parentQUAD->x = %d\n", parentQUAD->x);
*/ ;
	 	}
	   
	 	switch(region_number) {
            		case 1 : /* NW quadrant */
 
               			childQUAD->x = parentQUAD->x;                  
               			childQUAD->y = parentQUAD->y;
	       			parentQUAD -> upper_left  = (QUAD *) childQUAD;

	       		break;         
            		case 2 : /* NE quadrant */

               			childQUAD->x = childQUAD->dx + parentQUAD->x; 
               			childQUAD->y = parentQUAD->y;
	       			parentQUAD -> upper_right = (QUAD *) childQUAD;

               		break;
            		case 3 : /* SW quadrant */

               			childQUAD->x = parentQUAD->x;                 
               			childQUAD->y = childQUAD->dy + parentQUAD->y;
	       			parentQUAD -> lower_left  = (QUAD *) childQUAD;
               		break;
   
            		case 4 : /* SE quadrant */

               			childQUAD->x = childQUAD->dx + parentQUAD->x;  
               			childQUAD->y = childQUAD->dy + parentQUAD->y;
	       			parentQUAD -> lower_right = (QUAD *) childQUAD;
	       		break;

	    		default :
	       			fprintf(stderr, "%s: shouldn't happen!\n", fn);
				break;
         	}

   		push_Stack(sP, childQUAD);
	}

}

/****************************************************************
                   Name: quadtree2ras
          Expanded Name: quad tree to raster
             Parameters: <srcImage> - pointer to Image structure
			 <treeQUAD> - pointer to quad tree list
                Returns: pointer to Image structure.
            Description: this function will fill the contents of an Image
			 structure with the information contained in a 
			 quad tree. The Image structure passed <srcImage> 
			 should have the same basic attributes as the original
			 Image used to form the quad tree; such as, dimension,
			 data type (CVIP_BYTE), etc. Most likely <srcImage> will
			 be the original image used to form the quad tree unless
			 for some reason the contents of the original need be
			 preserved.
	    Diagnostics: none.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

Image *
quadtree2ras(
	Image *srcImage,
	QUAD *treeQUAD
)
{
   	QUAD 	*quadROI;
	Stack	sP;
   	char 	*fn = "quadtree2ras";
         
   	sP = new_Stack();

   	push_Stack(sP, treeQUAD);   

   	while(!isempty_Stack(sP)) {

      		quadROI = pop_Stack(sP);
                  
      		if(quadROI->upper_left) {
         		push_Stack(sP, quadROI->upper_left);
         		push_Stack(sP, quadROI->upper_right);
         		push_Stack(sP, quadROI->lower_left);
         		push_Stack(sP, quadROI->lower_right);
      		}
      		else
         		draw(srcImage, quadROI);

      		free(quadROI);
   	}

	delete_Stack(sP, free_Quad);

   	return srcImage;	 
}


/****************************************************************
                   Name: draw
          Expanded Name:  "
             Parameters: <srcImage> - pointer to Image structure
			 <quadROI> - pointer to QUAD structure
                Returns: nada.
            Description: draws a region as specified in the QUAD structure 
			 <quadROI> into the image pointed to by <srcImage>.
	    Diagnostics: none.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

static void 
draw(
	Image *srcImage,
	QUAD *quadROI
)
{      
   	byte 		*bP;
   	register int 	i, j, k;
   	unsigned int 	yoffset, bands;
   	char 		*fn = "draw";
                  
   	yoffset = quadROI->y + quadROI->dy;
   	bands = srcImage->bands;

   	for(k=0; k < bands; k++) 
      		for(j = quadROI->y; j < yoffset; j++) {
         		bP  = (byte *) srcImage->bandP[k]->rptr[j] + quadROI->x;
         		for(i= 0; i < quadROI->dx; i++) 
            			*bP++ = quadROI->data[k];
      		}
}


/****************************************************************
                   Name: ispowerof2
          Expanded Name: is power of 2
             Parameters: <value> - postive integer value
                Returns: CVIP_YES or CVIP_NO.
            Description: returns CVIP_YES if the number contained in <value>
			 is a power of 2 and CVIP_NO otherwise.
	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

static CVIP_BOOLEAN 
ispowerof2(
	unsigned int value
)
{
   double log_2;

   log_2 = log((double) value)/log(2.0);
   return ( log_2 == ((unsigned int) log_2) ) ? CVIP_YES : CVIP_NO;
}


static void
free_Quad(
	void	*objP
)
{
	free(objP);
}
