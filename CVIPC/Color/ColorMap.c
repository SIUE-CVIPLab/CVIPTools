/* libppm3.c - ppm utility library part 3
**
** Colormap routines.
**
** Copyright (C) 1989, 1991 by Jef Poskanzer.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
*/
#include "CVIPtoolkit.h"
#include "ColorMap.h"

#define HASH_SIZE 20023U

#define hash_Color(p) ( ( ( (long) ((p).r) * 33023 + (long) ((p).g) * 30013 + (long) ((p).b) * 27011 ) & 0x7fffffff ) % HASH_SIZE )

static int match_Color(void *objP, void *pixelP);

static void delete_ColorHistObject(void *objectP);
static ColorHistObject *new_ColorHistObject(void);

static ColorHashTable *computeHash_ColorHist(Image *imageP, unsigned maxval);
static void hash2Hist_ColorHist(ColorHistogram *chP, ColorHashTable *chtP);

/*
 * Color Histogram/Mapping Class Stuff
 */

ColorHistogram *new_ColorHist(void)
{
   return( (ColorHistogram *) calloc(1,sizeof(ColorHistogram)) );
}

void delete_ColorHist(ColorHistogram *chP)
{
   free(chP->histogram);
   free(chP);
}

void compute_ColorHist( ColorHistogram *chP, Image *imageP, unsigned maxval)
{
	ColorHashTable *chtP;

   	chtP = computeHash_ColorHist( imageP, maxval);
   	if(!chtP) {
		chP->histogram = NULL;
		return;
	}

   	hash2Hist_ColorHist( chP, chtP );

   	delete_HT(chtP, delete_ColorHistObject);
}

int
dropColor_ColorHist(
	ColorHistogram 	*chP,
	Color 		pixel,
	unsigned	*no_pixels
)
{
	ColorHistObject *newHistP;
	register int 	i, j;

	*no_pixels = 0;
	
   	newHistP = 	(ColorHistObject *) malloc( (chP->no_of_colors - 1) *
			sizeof(ColorHistObject) );

   	if (!newHistP) {
      		error_CVIP("trim_ColorHist",
		"can not allocate memory for color histogram");
      		return 0;
   	}

	for(i=0, j=0; i < chP->no_of_colors; i++)
			if(!(equal_Color(chP->histogram[i].pixel, pixel))) {
				newHistP[j].pixel.r = (chP->histogram)[i].pixel.r;
				newHistP[j].pixel.g = (chP->histogram)[i].pixel.g;
				newHistP[j].pixel.b = (chP->histogram)[i].pixel.b;
				newHistP[j++].value= (chP->histogram)[i].value; 
			} else
				*no_pixels = chP->histogram[i].value; 

	if(j == i) {
		free(newHistP);  
		return 0;
	}
	else {
		free(chP->histogram);
		chP->histogram = newHistP;
		chP->no_of_colors--;
		return 1;
	}
}
	


static int valueCompare( const void *cho1P, const void *cho2P )
{
    return ((ColorHistObject *)cho2P)->value - ((ColorHistObject *)cho1P)->value;
}

void print_ColorHist( ColorHistogram *chP )
{
   register int i;
   const char *fn = "print";

   if(!chP->histogram) return;

  /* Sort by count. */
   qsort( chP->histogram, chP->no_of_colors, sizeof(ColorHistObject), valueCompare );
   msg_CVIP(fn, "\nTOTAL NUMBER OF UNIQUE COLORS = %u.\n\n",chP->no_of_colors);
   msg_CVIP(fn, "RED GRN BLU\tCOUNT\n" );
   msg_CVIP(fn, "--- --- ---\t-----\n" );
   for ( i = 0; i < chP->no_of_colors; i++ )
      msg_CVIP(fn, "%3d %3d %3d\t%d\n", getRed_Color(chP->histogram[i].pixel), getGrn_Color(chP->histogram[i].pixel), getBlu_Color(chP->histogram[i].pixel), chP->histogram[i].value );
   msg_CVIP(fn,"\n" );

}

static ColorHashTable *computeHash_ColorHist( Image *imageP, unsigned maxval)
{
   ColorHashTable *chtP;
   ColorHistObject *objP;
   Color pixel;
   unsigned rows, cols, key;
   unsigned no_of_colors = 0;
   register int i, j;
   register byte *rP,*gP,*bP;
   const char *fn = "computeHash_ColorHist";
   CVIP_BOOLEAN found_color;

   rows = getNoOfRows_Image(imageP);
   cols = getNoOfCols_Image(imageP);

   chtP = new_HT(HASH_SIZE);
   if(!chtP) {
      error_CVIP(fn,"out of memory allocating color hash table!");
      return NULL;
   }
      
   /* Go through the entire image, building a hash table of colors. */
   for (i = 0; i < rows; i++) {

      rP = getRow_Image(imageP, i, RED);
      gP = getRow_Image(imageP, i, GRN);
      bP = getRow_Image(imageP, i, BLU);

      for (j = 0; j < cols; j++, rP++, gP++, bP++ ) {

         assign_Color(pixel, *rP, *gP, *bP);

         key = hash_Color(pixel);

         setKey_HT(chtP, key);
         if(found_color = findObject_HT(chtP, &match_Color, &pixel))
	    objP = getObject_HT(chtP);

         if( !found_color ) {
            objP = new_ColorHistObject();
	    if(!objP) {
	       error_CVIP(fn,"out of memory allocating color hist. object!");
	       return NULL;
	    }
            objP->value = 1;
            objP->pixel = pixel;
	    addObject_HT(chtP, objP);
            if(++no_of_colors > maxval) {
               delete_HT(chtP, delete_ColorHistObject);
	       return NULL;
	    }
	 }
	 else (objP->value)++;
      }
   }         
    
   return chtP;
}

static void hash2Hist_ColorHist( ColorHistogram *chP, ColorHashTable *chtP )
{
   register int i, j;
   linked_list **table = chtP->table;

   /* Form a simple contiguous color histogram array from the hash chains. */

   for (i = 0; i < HASH_SIZE; i++)
      if(table[i]) chP->no_of_colors += size_LL(table[i]);

   chP->histogram = (ColorHistObject *) malloc(chP->no_of_colors * sizeof(ColorHistObject));
   if (!chP->histogram) {
      fprintf(stderr, "can not allocate memory for color histogram" );
      return;
   }

   /* Loop through the hash table. */
   j = 0;
   for (i = 0; i < HASH_SIZE; i++)
      if(table[i]) {
         head_LL(table[i]);
         for(;;) {
	    chP->histogram[j++] = *((ColorHistObject *) retrieve_LL(table[i]));
            if (istail_LL(table[i])) break;
            next_LL(table[i]);
 	 }
      }
}


static void delete_ColorHistObject( void *objectP )
{
   free(objectP);
}

static ColorHistObject *new_ColorHistObject(void)
{
   return( (ColorHistObject *) malloc(sizeof(ColorHistObject)) );
}

/*
 * Color Hash Table Stuff
 */

void addObject_ColorHT(
	HashTable *chtP,
	Color pixel,
	int index
)
{
	unsigned key;
	ColorHistObject *objP;

        key = hash_Color(pixel);
        setKey_HT(chtP, key);

        objP = new_ColorHistObject();
        if(!objP) {
        	error_CVIP("addObject_ColorHT", "out of memory allocating color hist. object!");
         	return;
      	}
      	objP->pixel = pixel;
      	objP->value = index;

      	addObject_HT(chtP, objP);
}


void delete_ColorHT(ColorHashTable *chtP)
{
   delete_HT(chtP, delete_ColorHistObject);
}

ColorHashTable *hist2Hash_ColorHT( ColorHistogram *chP )
{
   ColorHashTable *chtP;
   ColorHistObject *objP;
   register int i;
   Color pixel;
   const char *fn = "hist2Hash_ColorHT";

   chtP = new_HT(HASH_SIZE);
   if(!chtP) {
      error_CVIP(fn, "out of memory allocating color hash table!");
      return NULL;
   }

   for ( i = 0; i < chP->no_of_colors; i++ ) {

      pixel = chP->histogram[i].pixel;

      chtP->key = hash_Color(pixel);
	
      objP = new_ColorHistObject();
      if(!objP) {
         error_CVIP(fn, "out of memory allocating color hist. object!");
         return NULL;
      }
      objP->pixel = pixel;
      objP->value = i;

      addObject_HT(chtP, objP);
   }

   return chtP;
}

int lookUpColor_ColorHT( ColorHashTable *chtP, Color pixel )
{
   ColorHistObject *objP = NULL;

   chtP->key = hash_Color(pixel);
   if(findObject_HT(chtP, &match_Color, &pixel))
      objP = getObject_HT(chtP);

   if(objP)
      return objP->value;
   else 
      return -1;
}


/*
 * RGB Color Class Stuff
 */

static int match_Color(void *objP, void *pixelP)
{
   return equal_Color( ((ColorHistObject *) objP)->pixel, *((Color *) pixelP) );
}
