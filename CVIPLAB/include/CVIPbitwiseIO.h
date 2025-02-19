/************************************************************************
*									*
* ===================================================================== *
*     COMPUTER VISION/Image PROCESSING TOOL - DR SCOTT UMBAUGH, SIUE	*
* ===================================================================== *
*									*
*	PGM/FILE NAME: CVIPbitwiseIO.h					*
*									*
*	  DESCRIPTION: Header file for I/O routines which pack and	*
*		       unpack bitfield for maximum compression.		*
*									*
*	       AUTHOR: Arve Kjoelen, Southern Illinois University @	*
*		       Edwardsville.					*
*									*
* INITIAL CODING DATE: 04/28/94						*
*									*
************************************************************************/
#if !defined (CVIPBITWISEIO_DEFINED)
   #define CVIPBITWISEIO_DEFINED

   #include <stdio.h>
   #include "CVIPdef.h"

   /* Function Prototypes */
   extern CVIP_BOOLEAN Write_4bit_wide(int *data, int size, FILE *fname);
   extern CVIP_BOOLEAN Write_5bit_wide(int *data, int size, FILE *fname);
   extern CVIP_BOOLEAN Write_6bit_wide(int *data, int size, FILE *fname);
   extern CVIP_BOOLEAN Write_6bit_wide(int *data, int size, FILE *fname);
   extern CVIP_BOOLEAN Write_7bit_wide(int *data, int size, FILE *fname);
   extern CVIP_BOOLEAN Write_8bit_wide(int *data, int size, FILE *fname);
   extern CVIP_BOOLEAN Write_9bit_wide(int *data, int size, FILE *fname);
   extern CVIP_BOOLEAN Write_10bit_wide(int *data, int size, FILE *fname);
   extern CVIP_BOOLEAN Write_11bit_wide(int *data, int size, FILE *fname);
   extern CVIP_BOOLEAN Write_12bit_wide(int *data, int size, FILE *fname);
   extern CVIP_BOOLEAN Read_5bit_wide(int *data, int size, FILE *fname);
   extern CVIP_BOOLEAN Read_6bit_wide(int *data, int size, FILE *fname);
   extern CVIP_BOOLEAN Read_6bit_wide(int *data, int size, FILE *fname);
   extern CVIP_BOOLEAN Read_7bit_wide(int *data, int size, FILE *fname);
   extern CVIP_BOOLEAN Read_8bit_wide(int *data, int size, FILE *fname);
   CVIP_BOOLEAN Read_9bit_wide(int *data, int size, FILE *fname);
   CVIP_BOOLEAN Read_10bit_wide(int *data, int size, FILE *fname);
   CVIP_BOOLEAN Read_11bit_wide(int *data, int size, FILE *fname);
   CVIP_BOOLEAN Read_12bit_wide(int *data, int size, FILE *fname);


#endif
