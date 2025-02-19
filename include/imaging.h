#ifdef SGI
#endif
/*
*/

/*=============================================================*
*                                                             	*
*					Stealth Technologies, Inc.								*
*              101 East Alton												*
*              Marine, IL  62061-0427									*
*                                                              *
*              (c) Copyright 1993 (STI)                        *
*                                                              *
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*
*                                                              * 
*		Project			:  Deformable Templates							*
*		File				:  imaging.h										*
*		Function(s)		:  prototypes and macros for imaging.c		*
*		Programmer(s)	:  Lance A. Kendrick                    	*
*		Date				:  15-Jun-91										*	
*		Revision Date	:  27-Jan-93                          		*
*                                                              * 
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*
*                                                              * 
*		Description:                                            	*
*                                                              *
*			This header file was adapted from a more general 		*
*			purpose file compiled by the same programmer.  The 	*
*			adaptations were mainly	to take advantage of the 		*
*			forms library and to interface robustly to the 			*
*       	ASE routines.														*
*                                                              *
*		Argument(s):															*
*                                                              *
*		Return(s):																*		
*                                                              *
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*
*                                                              *
*		Notes:                                                  	*
*                                                              *
*top                                                           *
*==============================================================*/

#include <math.h>
#include <stdio.h>


/*
 *  DEFINITIONS
 */

#define large	0x7fffffff       /* 2.147484e9 */
#ifndef VERT
#define VERT 	0
#endif
#ifndef HORIZ
#define HORIZ 	1
#endif
#ifndef MAXCVIP_FLOAT
#define	MAXCVIP_FLOAT 	((float)1.7e+38)
#endif
#define  log2(x) 		log(x)/log(2.0)
#define  epsilon		0.001


/*
 *  FUNCTION PROTOTYPES
 */

/****  MATRIX READ AND WRITE  ****/

extern int 	dmat_read( char[], double*, short[] );
extern int 	dmat_write( char[], double*, short[] );
extern int 	fmat_read( char[], float*, short[] );
extern int 	fmat_write( char[], float*, short[] );

/****  Image READ AND WRITE  ****/

extern int 	image_read( char[], unsigned char**, short[] );
extern int 	image_write( char[], unsigned char**, short[] );

/****  MAP GRAY VALUES INTO COLOR MAP  ****/

#ifdef	GRAPHICS
extern int 	gray_map( short, short );
#endif


/****  DYNAMIC ALLOCATION OF VECTORS  ****/

extern int 	*ivector( int, int );
extern float 	*fvector( int, int );
extern double 	*dvector( int, int );
extern unsigned int 		*uvector( int, int );
extern unsigned char 		*ucvector( int, int );
extern unsigned long int 	*ulvector( int, int );
extern unsigned short int 	*usvector( int, int );

/****  DYNAMIC ALLOCATION OF 2D ARRAYS  ****/

extern int 	**imatrix( int, int, int, int );
extern char 	**cmatrix( int, int, int, int );
extern float 	**fmatrix( int, int, int, int );
extern double 	**dmatrix( int, int, int, int );
extern unsigned int 	**umatrix( int, int, int, int );
extern unsigned long 	**ulmatrix( int, int, int, int );
extern unsigned char 	**ucmatrix( int, int, int, int );
extern unsigned short 	**usmatrix( int, int, int, int );
	
/****  DEALLOCATION OF VECTORS  ****/

extern void	free_fvector( float*, int, int );
extern void	free_dvector( double*, int, int );
extern void	free_ivector( int*, int, int );
extern void	free_uvector( unsigned*, int, int );
extern void free_ulvector( unsigned long*, int, int );
extern void free_ucvector( unsigned char*, int, int );
extern void free_usvector( unsigned short*, int, int );

/****  DEALLOCATION OF 2D ARRAYS  ****/

extern void	free_dmatrix( double**, int, int, int, int );
extern void	free_imatrix( int**, int, int, int, int );
extern void	free_fmatrix( float**, int, int, int, int );
extern void	free_umatrix( unsigned int**, int, int, int, int );
extern void	free_ulmatrix( unsigned long**, int, int, int, int );
extern void	free_ucmatrix( unsigned char**, int, int, int, int );
extern void	free_usmatrix( unsigned short**, int, int, int, int );

/****  DYNAMIC ALLOCATION OF 3D ARRAYS  ****/

extern float 		***fvolume( int, int, int );
extern unsigned char 	***ucvolume( int, int, int );

/****  OTHER ROUTINES  ****/

extern int	mod( int, int );
extern void nrerror( char[] );
extern void	fdump_array( float*, int, int, int );
extern void gauran( double, double[] );
