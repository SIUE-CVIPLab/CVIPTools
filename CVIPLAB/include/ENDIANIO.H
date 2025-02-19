/******************************************************************\
**  Title:   ENDIANIO.H                                           **
**  Purpose: Endianio Header file                                 **
**  Version: 1.0.0                                                **
**  Date:    May 1991                                             **
**  Author:  James D. Murray, Anaheim, CA, USA                    **
**                                                                **
**  Header file for ENDIANIO.C.  Must be included in any source   **
**  modules calling any of the endian I/O functions found in      **
**  ENDIANOI.C.                                                   **
**                                                                **
**  Portions Copyright (C) 1994 by James D. Murray and William vanRyper     **
\******************************************************************/
#ifndef ENDIANIO_H
#define ENDIANIO_H   1

#include "datatype.h"        /* Include the data type definitions */

#define ENDIAN_LSB      0    /* Machine is little-endian */
#define ENDIAN_MSB      1    /* Machine is big-endian    */

#define GetByte(fp)             ((BYTE) fgetc(fp))
#define PutByte(b, fp)          fputc((BYTE) b, fp)

/*
** Function prototypes
*/
WORD    TestByteOrder(VOID);             /* Test byte-order of the 
machine  */
WORD    GetBigWord(FILE *);              /* Get a big-endian    16-bit 
word */
WORD    GetLittleWord(FILE *);           /* Get a little-endian 16-bit 
word */
VOID    PutBigWord(WORD, FILE *);        /* Put a big-endian    16-bit 
word */
VOID    PutLittleWord(WORD, FILE *);     /* Put a little-endian 16-bit 
word */
DWORD   GetBigDword(FILE *);             /* Get a big-endian    32-bit 
word */
DWORD   GetLittleDword(FILE *);          /* Get a little-endian 32-bit 
word */
VOID    PutBigDword(DWORD, FILE *);      /* Put a big-endian    32-bit 
word */
VOID    PutLittleDword(DWORD, FILE *);   /* Put a little-endian 32-bit 
word */
BYTE   *GetString(BYTE *, WORD, FILE *);
BYTE   *PutString(BYTE *, WORD, FILE *);

#endif  /* ENDIANIO_H */


