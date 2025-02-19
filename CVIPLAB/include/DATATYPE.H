/******************************************************************\
**  Title:   DATATYPE.H                                           **
**  Purpose: Special data types used in source code.              **
**  Version: 1.0.0                                                **
**  Date:    April 1991                                           **
**  Author:  James D. Murray, Anaheim, CA  USA                    **
**                                                                **
**  Data type definitions and directives use to consolidate the   **
**  data types used in the source modules and to ease the job of  **
**  porting code to other systems.                                **
**                                                                **
**  Portions Copyright (C) 1994 by James D. Murray and William vanRyper     **
\******************************************************************/
#if !defined(DATATYPE_H)
#define DATATYPE_H      1           /* Used to prevent recursive 
inclusion */

#include <stddef.h>                 /* Standard ANSI definitions  */
#include <limits.h>

#ifndef FALSE
#define FALSE           0           /* FALSE boolean data value   */
#endif
#ifndef TRUE
#define TRUE            !FALSE      /* TRUE boolean data value    */
#endif

/*
**  Data type definitions.  Used to aid in portability and to make
**  source code generally more readable.
*/
#ifndef VOID
typedef void            VOID;       /* Void data type             */
#endif
#ifndef SHORT
typedef short           SHORT;       /* Boolean data type          */
#endif
#ifndef BOOL
typedef int           BOOL;       /* Boolean data type          */
#endif
#ifndef CHAR
typedef signed char     CHAR;       /*  8-bit signed data type    */
#endif
#ifndef BYTE
typedef unsigned char   BYTE;       /*  8-bit unsigned data type  */
#endif
#ifndef INT
typedef int    INT;        /* 16-bit signed data type    */
#endif
#ifndef WORD
typedef unsigned short  WORD;       /* 16-bit unsigned data type  */
#endif
#ifndef LONG
typedef signed long     LONG;       /* 32-bit signed data type    */
#endif
#ifndef DWORD
typedef unsigned long   DWORD;      /* 32-bit unsigned data type  */
#endif
                
/*
**  A variety of macros used to tear down and build up words of data.
*/
#ifndef TRUE
#define LOBYTE(w)       ((BYTE) (w))
#endif
#ifndef TRUE
#define HIBYTE(w)       ((BYTE) ((0x00FF & (WORD) ((w) >>  8))))
#endif
#ifndef TRUE
#define LOWORD(d)       ((WORD) (d))
#endif
#ifndef TRUE
#define HIWORD(d)       ((WORD) ((0xFFFF & (DWORD)((d) >> 16))))
#endif
#ifndef TRUE
#define MAKEWORD(h,l)   (((WORD)  ((WORD)  (h) <<  8)) | (WORD) ((BYTE)(l)))
#endif
#ifndef TRUE
#define MAKEDWORD(h,l)  (((DWORD) ((DWORD) (h) << 16)) | (DWORD)((WORD)(l)))
#endif

/*
**  A variety of macros used to test/flip bits within words of data.
*/
/* Flip the specified bit to 0 */
#define BITCLEAR(field, bit)  ((field) & ~(bit))
/* Flip the specified bit to 1 */
#define BITSET(field, bit)    ((field) | (bit))
/* Flip the specified bit to its inverse state */
#define BITTOG(field, bit)    ((field) ^ (bit))
/* Create a string of 0 bits from n to m */
#define BITSON(n, m)          (~(~0 << (m) << 0) & (~0 << (n)))
/* Create a string of 1 bits from n to m */
#define BITSOFF(n, m)         (~(~0 << (m) << 1) & (~0 << (n)))


/* Structure copy macro */
#if defined(__STDC__)
#define assignstruct(a, b)  ((a) = (b))
#else
#define assignstruct(a, b)  (memcpy((char*)&(a), (char *)&(b), sizeof(a)))
#endif

#if !defined(offsetof)
#define offsetof(s, m)  ((size_t)&(((s *)0)->m))
#endif

#if !defined(max)
#define max(a,b)        (((a) > (b)) ? (a) : (b))
#endif

#if !defined(min)
#define min(a,b)        (((a) < (b)) ? (a) : (b))
#endif

#endif  /* DATATYPE_H */


