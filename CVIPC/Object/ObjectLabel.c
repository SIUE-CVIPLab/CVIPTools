/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: ObjectLabel.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Fri Nov 22 14:54:05 CST 1996
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Greg Hance 
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1996 SIUE - by Scott Umbaugh and Greg Hance.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
****************************************************************************/
#include "CVIPtoolkit.h"
#include "ObjectLabel.h"
#include "CVIPdef.h"

typedef HashTable *ObjectHash;

#define HASH_SIZE 251U

#define hash_Object(label) (((unsigned)(label))%HASH_SIZE)


static void addto_Objects(ObjectHash hashP, int next_label, Color pixel, int y_pos, int x_pos);
static void update_Objects(ObjectHash hashP, int object_label, int y_pos, int x_pos);
static void combine_Objects(ObjectHash hashP, int b, int c, int *xmin, int *xmax, int *ymin, int *ymax);
static ObjectList hash2List_Objects(ObjectHash hashP);

static void makegraymap_Objects(ColorHistogram *chP);
static Matrix *color2index_Image(ColorHistogram *chP, Image *imageP );

/* 
 * label recycling routines 
 */
static void initLabelStack(void);
static int getNextLabel(void);
static void recycleLabel(int label);

/* 
 * global variables used by label recycling routines 
 */
static int label_count;
static Stack label_stackP;

ObjectList 
label_Objects( 
	Image *imageP, 
	Image **labelP,
	unsigned background
)
{
register int x, y=0, i, j;
int A, B, C, D, rows, cols;
byte *pixarray2, *pixarray1; /* pixel arrays */
int *labarray1, *labarray2, *rowP; /* label arrays */
int xmin, xmax, ymin, ymax, next_label;
unsigned *A_LABEL, B_LABEL, C_LABEL, D_LABEL, MAX_LABEL;
ObjectList listP;
ObjectHash hashP;
Object *objP;
ColorHistogram *chP;
ColorHistObject *mapP;
Matrix *matrixP;
ROI *roiP;
const char *fn = "label";

chP = new_ColorHist();

if(getNoOfBands_Image(imageP) > 1) {
   msg_CVIP(fn, "finding color map...\n");
   compute_ColorHist(chP, imageP, 256);
   matrixP = color2index_Image(chP, imageP);
   
}
else {
   msg_CVIP(fn, "finding gray map...\n");
   makegraymap_Objects(chP);
   matrixP = getBand_Image(imageP,0);
}

mapP = chP->histogram;
if(mapP==NULL) return NULL;

rows = getNoOfRows_Image(imageP);
cols = getNoOfCols_Image(imageP);

*labelP = new_Image(PGM, GRAY_SCALE, 1, rows, cols, CVIP_INTEGER, REAL);

msg_CVIP(fn, "building object list...\n");
//msg_CVIP(fn, "found object   0.");

pixarray2 = getRow_Matrix(matrixP, 0);
labarray2 = getRow_Image(*labelP, 0, 0);

initLabelStack();
hashP = new_HT(HASH_SIZE);

/* 
 * handle special case of first row
 */

for(x=0; x < cols; x++)
   if( pixarray2[x] != background ) {
      if( (x==0) || (pixarray2[x-1] != pixarray2[x]) ) {
         next_label = getNextLabel();
         addto_Objects(hashP, next_label, mapP[pixarray2[x]].pixel, y, x);
         labarray2[x] = next_label;
      }
      else {
        update_Objects(hashP, labarray2[x-1], y, x);
        labarray2[x] = labarray2[x-1];
      }
   }

for(y=0; y < rows-1; y++)
{
  
   pixarray1 = pixarray2;
   pixarray2 = getRow_Matrix(matrixP, y+1);

   labarray1 = labarray2;
   labarray2 = getRow_Image(*labelP, y+1, 0);
   
   for(x=0; x < cols-1; x++)
   {
      A = pixarray2[x+1];
      B = pixarray2[x];
      C = pixarray1[x+1];
      D = pixarray1[x];

      A_LABEL = (unsigned *) &labarray2[x+1];
      B_LABEL = labarray2[x];
      C_LABEL = labarray1[x+1];
      D_LABEL = labarray1[x];
      
      if (x == 0)
      {
         if (B != background)
            if(D == B)
            {
               B_LABEL = labarray2[x] = D_LABEL;
               update_Objects(hashP, B_LABEL, y+1, x);
            }
            else
            {
               next_label = getNextLabel();
               addto_Objects(hashP, next_label, mapP[B].pixel,y+1,x);
               B_LABEL = labarray2[x] = next_label;
            }
      }
      if (A != background)
      {
         if(D != A)
         {
            if(B != A)
            {
               if(C != A)
               {
                  next_label = getNextLabel();
                  addto_Objects(hashP, next_label,mapP[A].pixel, y+1, x+1);
                  *A_LABEL = next_label;
               }
               else
               {
                  *A_LABEL = C_LABEL;
                  update_Objects(hashP, *A_LABEL, y+1, x+1);
               }
            }
            else
            {
               if (C == A)
               {
                  if (B_LABEL == C_LABEL)
                  {
                     *A_LABEL = B_LABEL;
                  }
                  else
                  {
                     combine_Objects(hashP, B_LABEL, C_LABEL, &xmin, &xmax,
		     &ymin, &ymax);

		     MAX_LABEL = MAX(B_LABEL,C_LABEL);
                     *A_LABEL =  MIN(B_LABEL,C_LABEL);

                     roiP = new_ROI();
                     asgnImage_ROI(roiP, *labelP, xmin, ymin, xmax-xmin+1,
		     ymax-ymin+1);

                     for(i=0; i < getNoOfRows_ROI(roiP); i++) {
		        rowP = (int *) getRow_ROI(roiP, i, 0);
			for(j=0; j < getNoOfCols_ROI(roiP); j++, rowP++)
			   if(*rowP == MAX_LABEL)
			      *rowP = *A_LABEL;
		     }
		     
                     delete_ROI(roiP);
                  }
               }
               else
                  *A_LABEL = B_LABEL;

               update_Objects(hashP, *A_LABEL, y+1, x+1);
            }
         }
         else
         {
            *A_LABEL = D_LABEL;
            update_Objects(hashP, *A_LABEL, y+1, x+1);
         }
      }
   }
}

listP = hash2List_Objects(hashP);

print_CVIP("\n");

/*
fprintf(stderr, "Displaying Object Statistics...\n\n");
fprintf(stderr, "Number of objects found = %u.\n\n", size_LL(listP));
print_Objects(listP);
fprintf(stderr, "\n\n                 Press the <ENTER> key to continue");
getchar();
*/

delete_Matrix(matrixP);
free(chP);
free(mapP);

return listP;
}


ObjectVector *
listToVector_Objects(
	ObjectList listP
)
{
   	ObjectVector 	*newP;
   	register int 	i = 0;

   	newP = (ObjectVector *) malloc(sizeof(ObjectVector));

   	newP->no_of_objects = size_LL(listP);
   	newP->oP = (Object *) malloc(newP->no_of_objects*sizeof(Object));
  
   	head_LL(listP);
   
   	for(;;) {
      		newP->oP[i++] = *((Object *) retrieve_LL(listP));
      		if (istail_LL(listP)) break;
      		next_LL(listP);
   	}
   
return newP;
}

static ObjectList hash2List_Objects(ObjectHash hashP)
{
   register int i, first = 0;
   ObjectList listP;

   for(;;) { 
      if(hashP->table[first]) break;
      first++;
   }

   listP = hashP->table[first];

   for(i=first+1; i < size_HT(hashP); i++)
      if(hashP->table[i]) {
        
         *(listP->tailP) = *(hashP->table[i]->headP->nextP);
         listP->tailP = hashP->table[i]->tailP;
         listP->listlength += size_LL(hashP->table[i]);
	 delete_Link(hashP->table[i]->headP->nextP);
         delete_Link(hashP->table[i]->headP);
         /* delete_Link(hashP->table[i]->headP->nextP); */
         free(hashP->table[i]);

       }

    return listP;
}

#if 0
static int areacompare( const void *o1P, const void *o2P )
{
    return ((Object *)o2P)->area - ((Object *)o1P)->area;
}
#endif

void printLabel_Objects( ObjectList listP, const char *name)
{

	FILE *fileP;
   /*
   qsort( thisP->oP, thisP->no_of_objects, sizeof(Object), &areacompare );
   */
	fileP = openWrite_CVIP(name, CVIP_NO);

	fprintf(fileP, "Total Number of Objects : %d\n", size_LL(listP));
	print_LL(listP, print_Object, fileP);

	close_CVIP(fileP);
}


int readLabel_Objects( ObjectList listP, const char *name )
{

	FILE *fileP;
	long no_of_objects;
	Object *objP;
	const char *fn = "readLabel_Objects";
	int status;
  
	fileP = openRead_CVIP(name);

	no_of_objects = fGetInt_CVIP(fileP, &status, 2, ":");
	if(!status) {
		error_CVIP(fn, "problem reading objects from %s\n", name);
		return 0;
	}

	if(!isempty_LL(listP)) {
		error_CVIP(fn, "object list must be empty\n");
		return 0;
	}

	listP->clP = listP->headP;

	for(;;) {
		objP = (Object *) malloc(sizeof(Object));
		if(!read_Object(objP,fileP)) {
			free(objP);
			break;
		}
		addnext_LL(listP, objP);
	}

	if(no_of_objects != size_LL(listP)) {
		error_CVIP(fn, "problem reading objects from %s\n", name);
		return 0;
	}

	close_CVIP(fileP);

	return 1;
}



static void addto_Objects(ObjectHash hashP, int next_label, Color pixel, int y_pos, int x_pos)
{
 //  print_CVIP("\b\b\b\b\b\b%5d.", next_label);
   fflush(stderr);

   setKey_HT(hashP, hash_Object(next_label));
   addObject_HT( hashP, new_Object(next_label, pixel, y_pos, x_pos) );
}

static void update_Objects( ObjectHash hashP, int object_label, int y_pos, int x_pos)
{
   Object *obj;
   const char *fn = "update_Objects";

   setKey_HT(hashP,hash_Object(object_label));
  
   if(findObject_HT(hashP, match_Object, &object_label)) {
      obj = getObject_HT(hashP);

      obj -> x_min = MIN(obj -> x_min, x_pos);
      obj -> x_max = MAX(obj -> x_max, x_pos);
      obj -> y_min = MIN(obj -> y_min, y_pos);
      obj -> y_max = MAX(obj -> y_max, y_pos);
   }
   else
      error_CVIP(fn,"could not update hash with new object!");

}


static void combine_Objects(ObjectHash hashP, int b, int c, int *xmin, int *xmax, int *ymin, int *ymax)
{
   dlink *linkP;
   Object *bP, *cP;

   if (b < c) SWAP(b,c);

   setKey_HT(hashP,hash_Object(b));
   findNextObject_HT(hashP, match_Object, &b);
   bP = getNextObject_HT(hashP);
   removeNextObject_HT(hashP);

   setKey_HT(hashP,hash_Object(c));
   findObject_HT(hashP, match_Object, &c);
   cP = getObject_HT(hashP);

   *xmin = bP->x_min;
   *xmax = bP->x_max;
   *ymin = bP->y_min;
   *ymax = bP->y_max;

   cP -> x_min = MIN(cP -> x_min, bP->x_min);
   cP -> x_max = MAX(cP -> x_max, bP->x_max);
   cP -> y_min = MIN(cP -> y_min, bP->y_min);
   cP -> y_max = MAX(cP -> y_max, bP->y_max);

   delete_Object(bP);

   recycleLabel(b);
}


static void makegraymap_Objects( ColorHistogram *chP )
{
   register int i;

   chP->histogram = (ColorHistObject *) malloc(256*sizeof(ColorHistObject));

   for(i=0; i < 256; i++)
	assign_Color(chP->histogram[i].pixel, i, i, i);
}


static Matrix *color2index_Image(ColorHistogram *chP, Image *imageP )
{
   Matrix *matrixP;
   Color pixel;
   ColorHashTable *chtP;
   unsigned rows, cols;
   register int i;
   byte *mP, *rP, *gP, *bP;

   if(chP->no_of_colors > 256) {
      msg_CVIP("color2index", "too many colors!\n");
      return NULL;
   }

   rows = getNoOfRows_Image(imageP);
   cols = getNoOfCols_Image(imageP);
   rP = getRow_Image(imageP, 0, RED);
   gP = getRow_Image(imageP, 0, GRN);
   bP = getRow_Image(imageP, 0, BLU);

   matrixP = new_Matrix(rows, cols, CVIP_BYTE, REAL);
   mP = getRow_Matrix(matrixP,0);

   chtP = hist2Hash_ColorHT(chP);

   for(i=0; i < rows*cols; i++, mP++, rP++, gP++, bP++) {

      assign_Color(pixel, *rP, *gP, *bP);

      if( (*mP = lookUpColor_ColorHT( chtP, pixel )) == -1 )
         return NULL;
   }
   delete_ColorHT(chtP);

   return matrixP;
}


static void initLabelStack(void)
{
	label_stackP = new_Stack();
	label_count=1;
}

static int getNextLabel(void)
{
	int next_label, *labelP;

	if(isempty_Stack(label_stackP))
		next_label = label_count++;
	else {
		labelP = pop_Stack(label_stackP);
		next_label = *labelP;
		free(labelP);
	}
	
	return next_label;
}

static void recycleLabel(int label)
{
	int *labelP = (int *) malloc(sizeof(int));
	*labelP = label;
	push_Stack(label_stackP, labelP); 
}
