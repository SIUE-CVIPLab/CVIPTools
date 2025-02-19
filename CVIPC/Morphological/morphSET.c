/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: morphSET.c
*           Description: contains several routines to be used with the function
*			 morphomod(...).
*         Related Files: morph.c, morph.h, Imakefile
*   Initial Coding Date: Mon May 31 02:36:54 CDT 1993
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
** $Log: morphSET.c,v $
** Revision 1.6  1997/03/08 17:04:11  yawei
** Swaped CVIP_YES and CVIP_NO
**
** Revision 1.5  1997/03/08 00:54:43  yawei
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
** Revision 1.4  1997/01/15 17:14:47  yawei
** Global Change:  IMAGE ==> Image
**
 * Revision 1.3  1996/12/18  03:43:19  yawei
 * Changed Image to Image
 *
 * Revision 1.2  1995/09/23  19:13:03  akjoele
 * Changed argument #2 in call to morphIterMod_Image() to be cast to
 * (const MATRIX **) to be compatible with prototype for
 * morphIterMod_Image().
 *
 * Revision 1.1  1993/06/01  16:46:59  hanceg
 * Initial revision
 *
*
****************************************************************************/
#define DEFAULT 0
 
/* Define Preprocessor statements */
#include <stdio.h>
#include <string.h>
#include "CVIPimage.h"
#include <stdlib.h>
#include <stdarg.h>
#include "CVIPmorph.h"

static void print_surround(const MATRIX *, int);
static void print_bookhex();


/****************************************************************
                   Name: array2MATRIX
          Expanded Name: array to MATRIX
             Parameters: <array> - pointer to a statically allocated 2-D array
			 <atype> - data type of the array
			 <arows> - number of rows in the array
			 <acols> - number of columns in the array
                Returns: pointer to a new instance of a MATRIX structure
			 initialzed to the values of the array
            Description: converts a statically allocated 2-D array to a
			 dynamically allocated MATRIX structure.
	    Diagnostics: none
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

MATRIX *array2MATRIX(array, atype, arows, acols)
const void *array;
CVIP_TYPE atype;
unsigned int arows;
unsigned int acols;
{
   MATRIX *matrix;
   register void *mptr;
   register int i;

   matrix = (MATRIX *) matrix_allocate(arows, acols, atype, REAL);
   mptr = (void *) matrix->rptr[0];
   
   switch(atype) {
      case CVIP_BYTE:    (void) memcpy(mptr, array, arows*acols);
                     for(i = acols; i < acols*arows; i += acols)
                        matrix->rptr[i/acols] = (char *) (((byte *) mptr) + i);
		    break;
      case CVIP_SHORT:   (void) memcpy(mptr, array, sizeof(short)*arows*acols);
                     for(i = acols; i < acols*arows; i += acols)
                        matrix->rptr[i/acols] = (char *) (((short *) mptr) + i);
		    break;
      case CVIP_INTEGER: (void) memcpy(mptr, array, sizeof(int)*arows*acols);
                     for(i = acols; i < acols*arows; i += acols)
                        matrix->rptr[i/acols] = (char *) (((int *) mptr) + i);
		    break;
      case CVIP_FLOAT:   (void) memcpy(mptr, array, sizeof(float)*arows*acols);
                     for(i = acols; i < acols*arows; i += acols)
                        matrix->rptr[i/acols] = (char *) (((float *) mptr) + i);
		    break;
      case CVIP_DOUBLE:  (void) memcpy(mptr, array, sizeof(double)*arows*acols);
                     for(i = acols; i < acols*arows; i += acols)
                        matrix->rptr[i/acols] = (char *) (((double *) mptr) + i);
		    break;
   }
return matrix;
}


/****************************************************************
                   Name: euler_dif
          Expanded Name: euler differential
             Parameters: <surrMATRIX> - pointer to MATRIX structure
			 <connectedness> - connectivity scheme (must be either
			 SIX_NWSE or SIX_NESW)
                Returns: the euler differential.
            Description: determines the euler differential for a hexagonally
			 tessellated structuring element.
	    Diagnostics: none.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/


int euler_dif(surrMATRIX, connectedness)
const MATRIX *surrMATRIX;
int connectedness;
{

   register byte **surr;
   int ed;
   
   surr = (byte **) surrMATRIX->rptr;
   
   switch(connectedness) {
      case SIX_NWSE:
         if( surr[0][0] && !surr[0][1] ) ed++;
         if( surr[1][0] && !surr[0][0] ) ed++;
         if( surr[2][1] && !surr[1][0] ) ed++;
         if( surr[2][2] && !surr[2][1] ) ed++;
	 if( surr[1][2] && !surr[2][2] ) ed++;
	 if( surr[0][1] && !surr[1][2] ) ed++;
         break;
      case SIX_NESW:
         if( surr[0][1] && !surr[0][2] ) ed++;
         if( surr[1][0] && !surr[0][1] ) ed++;
         if( surr[2][0] && !surr[1][0] ) ed++;
         if( surr[2][1] && !surr[2][0] ) ed++;
	 if( surr[1][2] && !surr[2][1] ) ed++;
	 if( surr[0][2] && !surr[1][2] ) ed++;
         break;
   }
return(1-ed);
}



/*
 * print out a 3x3 hexagonal structuring element
 */

static void print_surround(surrMATRIX, connectedness)
const MATRIX *surrMATRIX;
int connectedness;
{

   register byte **surr;
      
   surr = (byte **) surrMATRIX->rptr;
   
   switch(connectedness) {
      case SIX_NWSE:
         fprintf(stderr, "\n      %1d\n", surr[0][0]);
         fprintf(stderr, "  %1d       %1d\n", surr[1][0], surr[0][1]);
         fprintf(stderr, "  %1d       %1d\n", surr[2][1], surr[1][2]);
         fprintf(stderr, "      %1d\n", surr[2][2]);
         break;
      case SIX_NESW:
         fprintf(stderr, "\n      %1d\n", surr[0][2]);
         fprintf(stderr, "  %1d       %1d\n", surr[0][1], surr[1][2]);
         fprintf(stderr, "  %1d       %1d\n", surr[1][0], surr[2][1]);
         fprintf(stderr, "      %1d\n", surr[2][0]);
         break;
   }
}


/*
 * print out the 14 unique hexagonal lattices
 */

static void print_bookhex()
{

   fprintf(stderr, "\n      %1d              %1d              %1d              %1d\n", HEXLAT1[0][0], HEXLAT2[0][0], HEXLAT3[0][0], HEXLAT4[0][0]);
   fprintf(stderr, "  %1d       %1d      %1d       %1d      %1d       %1d      %1d       %1d\n",HEXLAT1[1][0],HEXLAT1[0][1],HEXLAT2[1][0],HEXLAT2[0][1],HEXLAT3[1][0],HEXLAT3[0][1],HEXLAT4[1][0],HEXLAT4[0][1]);
   fprintf(stderr, "  %1d       %1d      %1d       %1d      %1d       %1d      %1d       %1d\n",HEXLAT1[2][1],HEXLAT1[1][2],HEXLAT2[2][1],HEXLAT2[1][2],HEXLAT3[2][1],HEXLAT3[1][2],HEXLAT4[2][1],HEXLAT4[1][2]);
   fprintf(stderr, "      %1d              %1d              %1d              %1d\n", HEXLAT1[2][2], HEXLAT2[2][2], HEXLAT3[2][2], HEXLAT4[2][2]);
   fprintf(stderr,"(1) E* = 1     (2) E* = 0      (3) E* = 0    (4) E* = 0\n\n");
   fprintf(stderr, "\n      %1d              %1d              %1d              %1d\n", HEXLAT5[0][0], HEXLAT6[0][0], HEXLAT7[0][0], HEXLAT8[0][0]);
   fprintf(stderr, "  %1d       %1d      %1d       %1d      %1d       %1d      %1d       %1d\n",HEXLAT5[1][0],HEXLAT5[0][1],HEXLAT6[1][0],HEXLAT6[0][1],HEXLAT7[1][0],HEXLAT7[0][1],HEXLAT8[1][0],HEXLAT8[0][1]);
   fprintf(stderr, "  %1d       %1d      %1d       %1d      %1d       %1d      %1d       %1d\n",HEXLAT5[2][1],HEXLAT5[1][2],HEXLAT6[2][1],HEXLAT6[1][2],HEXLAT7[2][1],HEXLAT7[1][2],HEXLAT8[2][1],HEXLAT8[1][2]);
   fprintf(stderr, "      %1d              %1d              %1d              %1d\n", HEXLAT5[2][2], HEXLAT6[2][2], HEXLAT7[2][2], HEXLAT8[2][2]);
   fprintf(stderr,"(5) E* = 0     (6) E* = 0      (7) E* = 1    (8) E* = -2\n\n");
   fprintf(stderr, "\n      %1d              %1d              %1d              %1d\n", HEXLAT9[0][0], HEXLAT10[0][0], HEXLAT11[0][0], HEXLAT12[0][0]);
   fprintf(stderr, "  %1d       %1d      %1d       %1d      %1d       %1d      %1d       %1d\n",HEXLAT9[1][0],HEXLAT9[0][1],HEXLAT10[1][0],HEXLAT10[0][1],HEXLAT11[1][0],HEXLAT11[0][1],HEXLAT12[1][0],HEXLAT12[0][1]);
   fprintf(stderr, "  %1d       %1d      %1d       %1d      %1d       %1d      %1d       %1d\n",HEXLAT9[2][1],HEXLAT9[1][2],HEXLAT10[2][1],HEXLAT10[1][2],HEXLAT11[2][1],HEXLAT11[1][2],HEXLAT12[2][1],HEXLAT12[1][2]);
   fprintf(stderr, "      %1d              %1d              %1d              %1d\n", HEXLAT9[2][2], HEXLAT10[2][2], HEXLAT11[2][2], HEXLAT12[2][2]);
   fprintf(stderr,"(9) E* = -1  (10) E* = -1    (11) E* = -1   (12) E* = -1\n\n");
   fprintf(stderr, "\n      %1d              %1d\n", HEXLAT13[0][0], HEXLAT14[0][0]);
   fprintf(stderr, "  %1d       %1d      %1d       %1d\n",HEXLAT13[1][0],HEXLAT14[0][1],HEXLAT14[1][0],HEXLAT14[0][1]);
   fprintf(stderr, "  %1d       %1d      %1d       %1d\n",HEXLAT13[2][1],HEXLAT13[1][2],HEXLAT14[2][1],HEXLAT14[1][2]);
   fprintf(stderr, "      %1d              %1d\n", HEXLAT13[2][2], HEXLAT14[2][2]);
   fprintf(stderr,"(13) E* = -1      (14) E* = -1\n\n");
}


/****************************************************************
                   Name: hexrotate
          Expanded Name: hexagonal rotate
             Parameters: <surMATRIX> - pointer to MATRIX structure
			 <connnectedness> - must specify either SIX_NWSE or 
			 SIX_NESW connectivity.
			 <degrees> - number of degrees to rotate (must be a
			 multiple of 60)
                Returns: pointer to rotated surrround.
            Description: rotate a (3x3) hexagonal structuring element (surround)
			 by <degrees> degrees.
	    Diagnostics: nada.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

MATRIX *hexrotate(surMATRIX, connectedness, degrees)
const MATRIX *surMATRIX;
int connectedness;
int degrees;
{
   MATRIX *rotMATRIX;
   register byte **surr;
   int temp, i;
   
   rotMATRIX = (MATRIX *) matrix_dup(surMATRIX, REAL);
   surr = (byte **) rotMATRIX->rptr;

   for(i=1; i <= (degrees/60); i++)
      switch(connectedness) {
         case SIX_NWSE:
            temp = surr[0][1];
            surr[0][1] = surr[0][0];
            surr[0][0] = surr[1][0];
            surr[1][0] = surr[2][1];
            surr[2][1] = surr[2][2];
	    surr[2][2] = surr[1][2];
	    surr[1][2] = temp;
            break;
         case SIX_NESW:
            temp = surr[0][2];
            surr[0][2] = surr[0][1];
            surr[0][1] = surr[1][0];
            surr[1][0] = surr[2][0];
            surr[2][0] = surr[2][1];
	    surr[2][1] = surr[1][2];
	    surr[1][2] = temp;
            break;
      }
return rotMATRIX;
}


/****************************************************************
                   Name: parse2ints
          Expanded Name: parse to integers
             Parameters: <strptr> - pointer to character string
			 <sepchars> - an array of seperating characters that
			 will distinguish between values.
                Returns: pointer to an integer array
            Description: parses a string of characters into seperate tokens and
			 stores the result in an array. ( e.g. the string 
			 "5 10 15" would be returned as a 3 element integer
			 array where a[0]=5, a[1]=10 and a[2]=15 )
	    Diagnostics: returns with NULL pointer and respective error msg.
			 when a bogus value is encountered.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

int *parse2ints(const char *strptr, const char *sepchars, int *n)
{
   unsigned int no_of_tokens=0, len;
   char *word, *str, *endcp;
   int *intarray, *outarray;
   
   len = strlen(strptr);
   
   intarray = (int *) malloc(sizeof(int)*((len/2)+1));
   outarray = intarray;
   str = (char *) malloc(len+1);

   (void) strcpy(str, strptr);
   word = strtok(str,sepchars);
   while(word != NULL) {
      *intarray = (int) strtol(word, &endcp, 10);
      if( !(word == endcp) && !(*endcp != '\0')) {
         intarray++;
         no_of_tokens++;
      }
      word = strtok(NULL,sepchars);
   }
   free(str);
   if(*n=no_of_tokens)
      return((int *) realloc(outarray, sizeof(int)*no_of_tokens));
   else
      return NULL;
}   


/****************************************************************
                   Name: zero
          Expanded Name:  "
             Parameters: <a> - Boolean variable
			 <b> - Boolean variable
                Returns: 0
            Description: resets all cells to 0.
	    Diagnostics: none.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

CVIP_BOOLEAN zero(CVIP_BOOLEAN a, CVIP_BOOLEAN b)
{ return((CVIP_BOOLEAN) 0); }


/****************************************************************
                   Name: not_b
          Expanded Name: not b
             Parameters: <a> - Boolean variable
			 <b> - Boolean variable
                Returns: !b
            Description: performs a logical "not" operation on b.
			 complements all pixel cells.
	    Diagnostics: none.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

CVIP_BOOLEAN not_b(CVIP_BOOLEAN a, CVIP_BOOLEAN b)
{ return((CVIP_BOOLEAN) !b); }


/****************************************************************
                   Name: not_a
          Expanded Name: not a
             Parameters: <a> - Boolean variable
			 <b> - Boolean variable
                Returns: !a
            Description: performs a logical "not" operation on a.
	    Diagnostics: none.
              Credit(s): Charles Stacey
		         Southern Illinois University @ Edwardsville
****************************************************************/

CVIP_BOOLEAN not_a(CVIP_BOOLEAN a, CVIP_BOOLEAN b)
{ return((CVIP_BOOLEAN) !a); }


/****************************************************************
                   Name: and
          Expanded Name:  "
             Parameters: <a> - Boolean variable
			 <b> - Boolean variable
                Returns: a&b
            Description: performs a logical "and" operation on a and b.
	    Diagnostics: none.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

CVIP_BOOLEAN and(CVIP_BOOLEAN a, CVIP_BOOLEAN b)
{ return((CVIP_BOOLEAN) a&b); }


/****************************************************************
                   Name:  or
          Expanded Name:   "
             Parameters: <a> - Boolean variable
			 <b> - Boolean variable
                Returns: a|b.
            Description: performs a logical "or" operation on a and b.
			 Tends to 
	    Diagnostics: none.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

CVIP_BOOLEAN or(CVIP_BOOLEAN a, CVIP_BOOLEAN b)
{ return((CVIP_BOOLEAN) a|b); }


/****************************************************************
                   Name:  not_and
          Expanded Name:  not and
             Parameters: <a> - Boolean variable
			 <b> - Boolean variable
                Returns: (!a)&b.
            Description: performs a logical operation on a and b.
	    Diagnostics: none.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

CVIP_BOOLEAN not_and(CVIP_BOOLEAN a, CVIP_BOOLEAN b)
{ return((CVIP_BOOLEAN) (!a)&b); }


/****************************************************************
                   Name: or_not_and
          Expanded Name: or not and
             Parameters: <a> - Boolean variable
			 <b> - Boolean variable
                Returns: a|((!a)&b)).
            Description: performs a logical operation on a and b.
	    Diagnostics: none.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

CVIP_BOOLEAN or_not_and(CVIP_BOOLEAN a, CVIP_BOOLEAN b)
{ return((CVIP_BOOLEAN) a|((!a)&b)); }


/****************************************************************
                   Name: xor
          Expanded Name:  "
             Parameters: <a> - Boolean variable
			 <b> - Boolean variable
                Returns: a^b.
            Description: performs a logical "xor" on a and b.
	    Diagnostics: none.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

CVIP_BOOLEAN xor(CVIP_BOOLEAN a, CVIP_BOOLEAN b)
{ return((CVIP_BOOLEAN) a^b); }


/****************************************************************
                   Name: morph_setup
          Expanded Name: morphological set-up
             Parameters: <srcImage> - pointer to original Image structure
			 <imgname> - character string containing the image name
                Returns: pointer to resultant 
            Description: set-up routine for morphological iterative scheme.
	    Diagnostics: returns NULL pointer with respective error msg. upon
			 strange happenings.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

Image *morph_setup(const Image *srcImage, const char *imgname)
{

   const char fn[] = {"morph"};
   char selection[LINELENGTH];
   int *surrchoice, n=0, no_of_iter=-1, subf=0, i, j, k, *sP, boolf, add_sur=0;
   CVIP_BOOLEAN (*bF)(CVIP_BOOLEAN a,CVIP_BOOLEAN b), finished = CVIP_NO;
   MATRIX **surrounds;
   byte *surrP[] =   {(byte*)HEXLAT1, (byte*)HEXLAT2, (byte*)HEXLAT3, 
                      (byte*)HEXLAT4, (byte*)HEXLAT5, (byte*)HEXLAT6, 
		      (byte*)HEXLAT7, (byte*)HEXLAT8, (byte*)HEXLAT9, 
		      (byte*)HEXLAT10,(byte*)HEXLAT11,(byte*)HEXLAT12,
		      (byte*)HEXLAT13,(byte*)HEXLAT14};
   char *func[] = {"0", "!b", "ab", "a+b","a^b","(!a)b","a + (!a)b"};

   fprintf(stderr,"\n%s: To uniquely perform an iterative modification scheme\n",fn);
   fprintf(stderr,"%s: please specify the following information when prompted.\n\n",fn);

   print_bookhex();

   fprintf(stderr,"%s: Select a set S of surrounds (for which a_ij = 1).\n",fn);
   fprintf(stderr,"%s: (seperate entries by a space, comma or semicolon.)\n",fn);
   fprintf(stderr,"%s: S{...} = ", fn);
   (void) fgets(selection,LINELENGTH,stdin);
   surrchoice = (int *) parse2ints(selection, " ,;:\n",&n);

   fprintf(stderr,"\n%s: Consider rotations(n)?", fn);
   (void) gets(selection);

   if(*selection=='y' || *selection=='Y') {
      for(i=0; i < n; i++) 
	 if(surrchoice[i]>1 && surrchoice[i]<7) add_sur+=5;
	 else if(surrchoice[i]>8 && surrchoice[i]<13) add_sur+=5;
	 else if(surrchoice[i] == 8) add_sur++;
	 else if(surrchoice[i]==13 || surrchoice[i]==14) add_sur+=2;
	 else {/*Change Nothing*/}
   }

   k = n;

   surrounds = (MATRIX **) calloc(n+add_sur,sizeof(MATRIX *));
   for(i=0, sP=surrchoice; i < n; i++, sP++)
      surrounds[i] = array2MATRIX(surrP[*sP-1], CVIP_BYTE, 3, 3);
      
   if(*selection=='y' || *selection=='Y') {
      fprintf(stderr, "\n%s: rotating surrounds...\n",fn);
      for(i=0; i < n; i++) 
	 if( (surrchoice[i]>1 && surrchoice[i]<7) || (surrchoice[i]>8 && surrchoice[i]<13) ) 
	    for(j=0; j < 5; j++, k++)
	       surrounds[k] = hexrotate(surrounds[i], SIX_NWSE, (j+1)*60);
	 else if(surrchoice[i] == 8) 
	    surrounds[k++] = hexrotate(surrounds[i], SIX_NWSE, 60);
	 else if(surrchoice[i]==13 || surrchoice[i]==14)
	    for(j=0; j < 2; j++, k++)
	       surrounds[k] = hexrotate(surrounds[i], SIX_NWSE, (j+1)*60);
	 else {/*Change Nothing*/}
   }
               
while(!finished) {
   fprintf(stderr, "\n%s: Select a Boolean function L(a,b):\n",fn);
   fprintf(stderr, "%s: ( where c_ij = L(a_ij,b_ij) for all i and j )\n", fn);
   fprintf(stderr, "%s: (1) L(a,b) = 0\n", fn);
   fprintf(stderr, "%s: (2) L(a,b) = !b\n", fn);
   fprintf(stderr, "%s: (3) L(a,b) = ab\n", fn);
   fprintf(stderr, "%s: (4) L(a,b) = a+b\n", fn);
   fprintf(stderr, "%s: (5) L(a,b) = a^b\n", fn);
   fprintf(stderr, "%s: (6) L(a,b) = (!a)b\n", fn);
   fprintf(stderr, "%s: (7) L(a,b) = a + (!a)b\n\n", fn);
   fprintf(stderr, "%s:  L(a,b) = ",fn);
   boolf =  atoi(gets(selection));
   
   finished = CVIP_YES;
   switch( boolf )
   {
      case 1: bF = &zero; break;
      case 2: bF = &not_a; break;
      case 3: bF = &and; break;
      case 4: bF = &or; break;
      case 5: bF = &xor; break;
      case 6: bF = &not_and; break;
      case 7: bF = &or_not_and; break;
      default: finished = CVIP_NO; break;
   }
}

while( no_of_iter<0 ) {
   fprintf(stderr, "\n%s: Enter the number of iterations (0 => oo).\n", fn);
   fprintf(stderr, "%s: n = ", fn);
   no_of_iter = (int) atoi(gets(selection));
}

while(!(subf>0 && subf<4)) {
   fprintf(stderr, "\n%s: Enter the number of subfields f, into which\n", fn);
   fprintf(stderr, "%s: the image tessellation is divided.\n", fn);
   fprintf(stderr, "%s: f = ", fn);
   subf = (int) atoi(gets(selection));
}


fprintf(stderr, "\n%s: Performing morphological modification of image - %s:\n",fn, imgname);
fprintf(stderr, "%s: ==============================================\n", fn);
fprintf(stderr, "%s: S = {",fn);
if(n) {
   fprintf(stderr," %d", surrchoice[0]);
   for(i=1;i<n; i++) fprintf(stderr,", %d", surrchoice[i]);
}
fprintf(stderr," }.\n");
fprintf(stderr, "%s: L(a,b) = %s.\n", fn, func[--boolf]);
if(!no_of_iter)
   fprintf(stderr, "%s: n = oo.\n", fn);
else
   fprintf(stderr, "%s: n = %d.\n", fn, no_of_iter);
fprintf(stderr, "%s: f = %d.\n\n", fn, subf);

if(!n) surrounds = NULL;

return( morphIterMod_Image(srcImage, (const MATRIX **)surrounds, bF, n+add_sur, SIX_NWSE, no_of_iter, subf) );
}
   
