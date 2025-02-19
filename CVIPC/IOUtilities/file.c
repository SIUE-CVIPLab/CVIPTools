/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: file.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Fri Sep 17 14:34:18 CDT 1993
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Gregory Hance
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
** $Log: file.c,v $
** Revision 1.7  1997/05/21 04:05:57  yawei
** added fopen() binary mode
**
** Revision 1.6  1997/05/21 03:33:55  yawei
** added WIN32 binary fopen
**
** Revision 1.5  1997/03/08 00:58:15  yawei
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
** Revision 1.4  1997/02/27 17:06:19  yawei
** changed for porting to Linux
**
** Revision 1.3  1996/02/02 20:57:05  akjoele
** Changed functions so that all functions that expect to return a
** vakue actually return one instead of "return;"
**
 * Revision 1.2  1995/04/19  18:41:32  kjoelena
 * Changed line 186 to include a type cast.  This is required for ANSI C compliance.
 *
 * Revision 1.1  1994/10/30  17:59:00  hanceg
 * CVIPtools1.0 source file - G. Hance
 *
*
****************************************************************************/
#include "CVIPparse.h"

#define LINELENGTH 80
#define  MAXTOKENS 39

int
replaceFileExt_CVIP( 
	char *bufP,
	const char *extP
)
{

	char	*locP;

	locP = strrchr(bufP, '.');

	if(locP == NULL)
		(void) strcat(bufP, extP);
}
	

/* File open/close that handles "-" as stdin and checks errors. */

FILE *
openRead_CVIP( 
	const char *name 
)
{
	FILE* f;
	const char *fn = "openREAD_CVIP";
	errno = 0;

	if ( strcmp( name, "-" ) == 0 )
		f = stdin;
	else {
		#ifndef WIN32
		f = fopen( name, "r" );
		#else
		f = fopen( name, "rb" );
		#endif
		if ( f == NULL )
			perror_CVIP( fn, name );
	}

return f;
}

FILE*
openWrite_CVIP(
	const char *name,
	CVIP_BOOLEAN nice
)
{
	FILE* f;
	char *ansP, c;
	const char* fn = "openWrite_CVIP";
	errno = 0;

	if ( strcmp( name, "-" ) == 0 )
		f = stdout;
	else if ( strcmp( name, "+" ) == 0 )
		f = stderr;
	else {
		if(nice) {
			#ifndef WIN32
			if((f = fopen(name, "r"))!=NULL) {
			#else
			if((f = fopen(name, "rb"))!=NULL) {
			#endif
				fprintf(stderr,"warning: file %s exists, overwrite?", name);
				ansP = getString_CVIP();
				while(isspace(*ansP++));
				c = *ansP;
				free(ansP);
				if(c == 'n' || c == 'N') {
					close_CVIP(f);
					return NULL;
				}
			}
		}
		#ifndef WIN32
		f = fopen( name, "w" );
		#else
		f = fopen( name, "wb" );
		#endif
		if ( f == NULL )
			perror_CVIP( fn, name );
	}

return f;
}

void
close_CVIP(
	FILE* f
 )
{
	const char *fn = "close_CVIP";

	if(f == NULL) return; /* ignore this case  */

	errno = 0;

	if ( f != stdin && f != stdout && f != stderr )
		if ( fclose( f ) != 0 )
	    		perror_CVIP( fn, "fclose" );
}

int fGetLine_CVIP(
	FILE *fileP,
	char *strP
)
{
	char buf[LINELENGTH], *begP;
	size_t len;

	begP = fgets(buf, LINELENGTH, fileP);
	if(!begP) {
		if(feof(fileP))
			return -1;
		else
			return 0;
	}

	while(isspace(*begP)) begP++;
	if( (len = strlen(begP)) < (LINELENGTH - 1) ) {
		strncpy(strP, begP, len);
		strP[len-1] = '\0';
	}
	else
		strncpy(strP, begP, LINELENGTH);

	return 1;
}

int fSkipLines_CVIP(
	FILE *fileP,
	unsigned no_of_lines
)
{
	char buf[LINELENGTH], *goodP;

	while(no_of_lines--) {
		goodP = fgets(buf, LINELENGTH, fileP);
		if(!goodP) {
			if(feof(fileP))
				return -1;
			else
				return 0;
		}
	}

	return 1;
}
	
int strToken_CVIP(
        const char  *strP,
        const char  *setP,
        char   **tokP,
        int    no_of_tokens
)
{
        char *word, *bufP;
        register int count;

        bufP = (char *)strP;

        count = 0;
        /*
        ** find first word
        */
        word = strtok(bufP, setP);

        while( (count < no_of_tokens)) {
                tokP[count++] = word;
                if (word == NULL)
                        break;
                /*
                ** find the next word
                */
                word = strtok(NULL, setP);
        }

        return count;
}


int fGetString_CVIP(
	FILE *fileP,
	char *strP,
	int field_no,
	const char *sep

)
{
	char feature[80], **tokP, *begP;
	const char *fn = "fGetString_CVIP";

	if(fGetLine_CVIP(fileP, feature) != 1)
		return 0;

	tokP = (char **) malloc(field_no*sizeof(char *));
	if(!tokP) {
		error_CVIP(fn, "could not allocate token array");
		return 0;
	}

	if(strToken_CVIP(feature, sep, tokP, field_no) != field_no) {
		free(tokP);
		return 0;
	}

	begP = tokP[field_no-1];
	while(isspace(*begP)) begP++;
	strcpy(strP, begP);
	free(tokP);
	return 1;
}


long fGetInt_CVIP(
	FILE *fileP,
	int *status,
	int field_no,
	const char *sep

)
{
	char feature[80], **tokP, *endcp, *str;
	const char *fn = "fGetInt_CVIP";
	long value;

	errno = 0;

	if(fGetLine_CVIP(fileP, feature) != 1) {
		*status = 0;
		return(-1);
	}

	tokP = (char **) malloc(field_no*sizeof(char *));
	if(!tokP) {
		*status = 0;
		error_CVIP(fn, "could not allocate token array");
		return(-1);
	}

	if(strToken_CVIP(feature, sep, tokP, field_no) != field_no) {
		free(tokP);
		*status = 0;
		return(-1);
	}

	str = tokP[field_no-1];
        value = strtol(str, &endcp, 10);
        if( ( str == endcp) || (*endcp != '\0') ) {
        	perror_CVIP(fn, "the following problem has occurred");
		free(tokP);
		*status = 0;
		return(-1);
        }

	free(tokP);
	*status = 1;
	return value;
}


long strGetInt_CVIP(
	const char *strP,
	int *status,
	int field_no,
	const char *sep

)
{
	char feature[80], **tokP, *endcp, *str;
	const char *fn = "strGetInt_CVIP";
	long value;

	errno = 0;

	(void) strncpy(feature, strP, 80);

	tokP = (char **) malloc(field_no*sizeof(char *));
	if(!tokP) {
		*status = 0;
		error_CVIP(fn, "could not allocate token array");
		return(-1);
	}

	if(strToken_CVIP(feature, sep, tokP, field_no) != field_no) {
		free(tokP);
		*status = 0;
		return(-1);
	}

	str = tokP[field_no-1];
        value = strtol(str, &endcp, 10);

        if( ( str == endcp) || (*endcp != '\0') ) {
        	perror_CVIP(fn, "the following problem has occurred");
		free(tokP);
		*status = 0;
		return(-1);
        }

	free(tokP);
	*status = 1;
	return value;
}



double fGetFloat_CVIP(
	FILE *fileP,
	int *status,
	int field_no,
	const char *sep
)
{
	char feature[80], **tokP, *endcp, *str;
	const char *fn = "fGetFloat_CVIP";
	double value;

	errno = 0;

	if(fGetLine_CVIP(fileP, feature) != 1) {
		*status = 0;
		return(-1);
	}

	tokP = (char **) malloc(field_no*sizeof(char *));
	if(!tokP) {
		*status = 0;
		error_CVIP(fn, "could not allocate token array");
		return(-1);
	}

	if(strToken_CVIP(feature, sep, tokP, field_no) != field_no) {
		free(tokP);
		*status = 0;
		return(-1);
	}

	str = tokP[field_no-1];
        value = strtod(str, &endcp);
        if( ( str == endcp) || (*endcp != '\0') ) {
        	perror_CVIP(fn, "the following problem has occurred");
		free(tokP);
		*status = 0;
		return(-1);
        }

	free(tokP);
	*status = 1;
	return value;
}


double strGetFloat_CVIP(
	const char *strP,
	int *status,
	int field_no,
	const char *sep
)
{
	char feature[80], **tokP, *endcp, *str;
	const char *fn = "fGetFloat_CVIP";
	double value;

	errno = 0;

	(void) strncpy(feature, strP, 80);

	tokP = (char **) malloc(field_no*sizeof(char *));
	if(!tokP) {
		*status = 0;
		error_CVIP(fn, "could not allocate token array");
		return(-1);
	}

	if(strToken_CVIP(feature, sep, tokP, field_no) != field_no) {
		free(tokP);
		*status = 0;
		return(-1);
	}

	str = tokP[field_no-1];
        value = strtod(str, &endcp);
        if( ( str == endcp) || (*endcp != '\0') ) {
        	perror_CVIP(fn, "the following problem has occurred");
		free(tokP);
		*status = 0;
		return(-1);
        }

	free(tokP);
	*status = 1;
	return value;
}


int 
getPathFileName(
	const char	*strP,
	char		*pnP,
	char		*fnP
)
{
	char	buf[80];
	char	*refP;

	if(strlen(strP) >= 80)
		return 0;

	strcpy(buf, strP);

	if((refP = strrchr(buf, '/')) == NULL)
		return 0;

	*refP = '\0';

	strcpy(pnP, buf);
	strcpy(fnP, refP+1);

	return 1;
}


static int
howMany(
	const char	*s,
	int		c
)
{
	int 	n = 0;
	while(s) {
		s = strchr(s,c);
		if (s) n++, s++;
	}

	return n;
}

char **
seperateStrings_CVIP(
	const char 	*strP, 
	int 		c,
	int 		*n
)
{
	char	*word, **sP, sepchar[2];
	int	no = (1); 
	sepchar[0]= (char)c;
	sepchar[1]= '\0';

	if(strP == NULL) {
		*n = 0;
		return NULL;
	}
	else
		*n = howMany(strP, ':') + 1;

	sP = (char **) malloc(sizeof(char *)*(*n));
	*sP = malloc(strlen(strP)+1);
   	(void) strcpy(*sP, strP);

   	word = strtok(*sP, sepchar);
   	while( (word = strtok(NULL, sepchar)) != NULL)
        	sP[no++] = word;

	return sP;
}
