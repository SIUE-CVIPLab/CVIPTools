/*
 * Warning, this file was automatically created by the TIFF configure script
 * VERSION:	 v3.4033
 * DATE:	 Wed May 21 22:06:38 CDT 1997
 * TARGET:	 sparc-sun-solaris2.5.1
 * CCOMPILER:	 /opt/apps/bin/cc
 */
#ifndef _PORT_
#define _PORT_ 1
#ifdef __cplusplus
extern "C" {
#endif
#include <sys/types.h>
#define HOST_FILLORDER FILLORDER_MSB2LSB
#define HOST_BIGENDIAN	1
#define HAVE_MMAP 1
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
typedef double dblparam_t;
#define	INLINE
#define GLOBALDATA(TYPE,NAME)	extern TYPE NAME
#ifdef __cplusplus
}
#endif
#endif
