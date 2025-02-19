/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: CVIPhistory.h
*           Description: contains function prototypes, type names, constants,
*			 etc. related to the creation and maintenance of a 
*                        history of operations performed on an image.
*         Related Files: history.c
*   Initial Coding Date: 3/1/93
*Last Modification Date: 9/14/93
*           Portability: Standard (ANSI) C
*             Credit(s): Arve Kjoelen
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1993 SIUE - by Arve Kjoelen.
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
** $Log: CVIPhistory.h,v $
** Revision 1.5  1998/03/30 19:57:39  smakam
** included 2 new defines GET_BOOL_DATA and GET_HIST_DATA1 for operations specific to including history stuff for geometry functions
**
** Revision 1.4  1997/03/08 00:52:17  yawei
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
** Revision 1.3  1996/06/11 12:13:50  kluo
** chck in
**
 * Revision 1.2  1995/09/19  20:54:30  kluo
 * change declaration for dptr
 *
 * Revision 1.1  1994/10/30  22:43:06  hanceg
 * Initial revision
 *
 * Revision 1.1  1993/12/02  19:47:59  kjoelena
 * Initial revision
 *
*
****************************************************************************/

#if !defined ( CVIPHISTORY_DEFINED )

   #define CVIPHISTORY_DEFINED

   #include "CVIPtools.h"
   #include "CVIPdef.h"

   typedef struct packet PACKET;
   struct packet {
      CVIP_TYPE *dtype;
      unsigned int dsize;
      void **dptr; 
   };

   typedef struct history *HISTORY;
   struct history {
      PROGRAMS ftag;
      PACKET *packetP;
      HISTORY next;
   };


#define GET_HIST_DATA(A,b,c) { \
	    switch( A->packetP->dtype[b]) { \
		case CVIP_BYTE:  \
		    c = ((byte *)(A->packetP->dptr[b]))[0]; \
		    break; \
		case CVIP_SHORT:  \
		    c = ((short *)(A->packetP->dptr[b]))[0];  \
		    break; \
		case CVIP_INTEGER:  \
		    c = ((int *)(A->packetP->dptr[b]))[0]; \
		    break; \
		case CVIP_FLOAT:  \
		    c = ((float *)(A->packetP->dptr[b]))[0]; \
		    break; \
		case CVIP_DOUBLE:  \
		    c = ((double *)(A->packetP->dptr[b]))[0]; \
		    break; \
	    } \
} \


#define GET_BOOL_DATA(A,b,c) { \
	    switch( A->packetP->dtype[b]) { \
		case CVIP_YES:  \
		    c = ((CVIP_BOOLEAN *)(A->packetP->dptr[b]))[0]; \
		    break; \
		case CVIP_NO:  \
		    c = ((CVIP_BOOLEAN *)(A->packetP->dptr[b]))[0]; \
		    break; \
		} \
} \

#define GET_HIST_DATA1(A,b,d,c) { \
	    switch( A->packetP->dtype[b]) { \
		case CVIP_BYTE:  \
		    c = ((byte *)(A->packetP->dptr[b]))[d]; \
		    break; \
		case CVIP_SHORT:  \
		    c = ((short *)(A->packetP->dptr[b]))[d];  \
		    break; \
		case CVIP_INTEGER:  \
		    c = ((int *)(A->packetP->dptr[b]))[d]; \
		    break; \
		case CVIP_FLOAT:  \
		    c = ((float *)(A->packetP->dptr[b]))[d]; \
		    break; \
		case CVIP_DOUBLE:  \
		    c = ((double *)(A->packetP->dptr[b]))[d]; \
		    break; \
	    } \
} \


#endif /* CVIPHISTORY_DEFINED */




