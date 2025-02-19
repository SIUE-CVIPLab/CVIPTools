/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: getvalue.c
*           Description: provide standard, more robust ways of accepting
*			 user input
*         Related Files: Imakefile, CVIPget.h, libcli.a
*   Initial Coding Date: Sat Apr 10 16:38:02 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Gregory Hance
*                        Southern Illinois University @ Edwardsville
*
*  Global Function List: getString_CVIP - get string from user
*			 getInt_CVIP - get integer value from user
*			 get_unit - get unsigned integer value from user
*			 getFloat_CVIP - get floating point value from user
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
* $Log: getvalue.c,v $
* Revision 1.2  1997/01/16 21:24:20  yawei
* updated changes
*
 * Revision 1.1  1993/05/03  22:37:20  hanceg
 * Initial revision
 *
*
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "CVIPget.h"

#define LINELENGTH 80
#define BUFLENGTH 30

/****************************************************************
                   Name: get string
          Expanded Name: get string
             Parameters: (void)
                Returns: pointer to string of input text LINELENGTH characters
			 long.
            Description: obtain a string of characters from stdin up
			 to the first newline character. If more than
			 LINELENGTH characters are read the rest of the input
			 is dicarded up to and including the newline char.
	    Diagnostics: returns NULL pointer w/ appropriate error message upon
			 (1) memory allocation failure, (2) error reading
			 from standard input.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

char *getString_CVIP(void)
{
    char *string, *newline, bitbucket[LINELENGTH];   /* result string pointer */
    const char *fn = "getString_CVIP";

    string = (char *) malloc(LINELENGTH);
    if(!string) {
        error_CVIP(fn, "\nString allocation error in getString_CVIP.");
        return NULL;
    }
    if( fgets(string, LINELENGTH, stdin) == NULL ) {
       error_CVIP(fn, "\nerror occured while reading from \"stdin\".");
       return NULL;
    }
    
    if( (newline = strchr(string, '\n')) == NULL ) {
       string[79] = '\0';
       do {
          if( fgets(bitbucket, LINELENGTH, stdin) == NULL ) {
             error_CVIP(fn, "\nerror occured while reading from \"stdin\".");
             return NULL;
          }
       } while(strchr(bitbucket, '\n') == NULL);
     }
     else *newline = '\0';

    return(string);
}
/****************************************************************
                   Name: getInt_CVIP
          Expanded Name: get integer
             Parameters: <base> - base/radix of number (2 to 36 inclusive)
			 <low_limit> - lower limit of acceptable input
			 <up_limit> - upper limit of acceptable input
                Returns: an integer value
            Description: obtain value of type int from standard input
			 within a specified range <low_limit>...<up_limit>.
			 This function uses the C library function-- strtol(..)
			 and expects the number to consist of... (1) an optional
			 plus or minus sign. (2) a sequence of decimal digits
			 which may be preceeded by 0x or 0X for hexadecimal 
			 values.
	    Diagnostics: prompts user for another value when the value entered
			 is... (1) - a candidate for overflow, (2) bogus, (4) 
			 not within the specified range <low_limit>...
			 <up_limit>. Returns with value of 0 w/ appropriate
			 error message when a call is made to getUInt_CVIP(...)
			 and <low_limit> < <up_limit> or base is not between
			 2 and 36.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

long getInt_CVIP(int base, long low_limit, long up_limit)
{
    int error_flag;
    long i;
    char *cp,*endcp;                /* char pointer */
    const char *fn = "getInt_CVIP";

/* check for limit error, low may equal high but not greater */
    if(low_limit > up_limit) {
        error_CVIP(fn, "\nLimit error, lower > upper");
        return 0;
    }

/* check to make sure that base is between 2 and 36 inclusive */
    if( base < 2 || base > 36) {
       error_CVIP(fn, "\nbase must be between 2 and 36 inclusive.");
       return 0;
    }

/* get the string and make sure i is in range and valid */
    do {
        cp = getString_CVIP();
        i = strtol(cp,&endcp,base);
        error_flag = (cp == endcp) || (*endcp != '\0'); /* detect errors */
        if( error_flag ) {
           perror_CVIP(fn, "the following problem has occurred");
           msg_CVIP(fn, "please enter another value: ");
        }
        else if(i < low_limit || i > up_limit) {
           error_CVIP(fn, "value must be in the range %ld...%ld.", low_limit, up_limit);
           msg_CVIP(fn, "please enter another value: ");
        }
        free(cp);
    } while(i < low_limit || i > up_limit || error_flag);

    return(i);
}


/****************************************************************
                   Name: getUInt_CVIP
          Expanded Name: get unsigned int
             Parameters: <base> - base/radix of number (2 to 36 inclusive)
			 <low_limit> - lower limit of acceptable input
			 <up_limit> - upper limit of acceptable input
                Returns: unsigned integer value
            Description: obtain value of type unsigned int from standard input
			 within a specified range <low_limit>...<up_limit>.
			 This function uses the C library function-- strtoul(..)
			 and expects the number to consist of... (1) an optional
			 plus or minus sign. (2) a sequence of decimal digits
			 which may be preceeded by 0x or 0X for hexadecimal 
			 values.
	    Diagnostics: prompts user for another value when the value entered
			 is... (1) - a candidate for overflow, (2) bogus, (4) 
			 not within the specified range <low_limit>...
			 <up_limit>. Returns with value of 0 w/ appropriate
			 error message when a call is made to getUInt_CVIP(...)
			 and <low_limit> < <up_limit> or base is not between
			 2 and 36.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

unsigned long getUInt_CVIP(int base, unsigned long low_limit, unsigned long up_limit)
{
    int error_flag;
    unsigned long i;
    char *cp,*endcp;                /* char pointer */
    const char *fn = "getUInt_CVIP";

/* check for limit error, low may equal high but not greater */
    if(low_limit > up_limit) {
        error_CVIP(fn, "\nLimit error, lower > upper");
        return 0;
    }

/* check to make sure that base is between 2 and 36 inclusive */
    if( base < 2 || base > 36) {
       error_CVIP(fn, "\nbase must be between 2 and 36 inclusive.");
       return 0;
    }

/* get the string and make sure i is in range and valid */
    do {
        cp = getString_CVIP();
        i = strtoul(cp,&endcp,base);
        error_flag = (cp == endcp) || (*endcp != '\0'); /* detect errors */
        if( error_flag ) {
           perror_CVIP(fn, "the following problem has occurred");
           msg_CVIP(fn, "please enter another value: ");
        }
        else if(i < low_limit || i > up_limit) {
           error_CVIP(fn, "value must be in the range %u...%u.", low_limit, up_limit);
           msg_CVIP(fn, "please enter another value: ");
        }
        free(cp);
    } while(i < low_limit || i > up_limit || error_flag);

    return(i);
}

/****************************************************************
                   Name: getFloat_CVIP
          Expanded Name: Get Float
             Parameters: <low_limit> - lower limit of acceptable input
			 <up_limit> - upper limit of acceptable input
                Returns: double precison floating point value
            Description: obtain value of type double from standard input
			 within a specified range <low_limit>...<up_limit>.
			 This function uses the C library function -- strtod(..)
			 and expects the number to consist of... (1) an optional
			 plus or minus sign. (2) a sequence of decimal digits
			 possibly containing a single decimal point, and
			 (3) an optional exponent part, consisting of the letter
			 e or E. an optional sign, and a sequence of decimal
			 digits.
	    Diagnostics: prompts user for another value when the value entered
			 is... (1) - a candidate for overflow, (2) a candidate
			 for overflow, (3) bogus, (4) not within the specified
			 range <low_limit>...<up_limit>. Returns with value of
			 0 w/ appropriate error message when a call is made 
			 to getFloat_CVIP(...) and <low_limit> < <up_limit>.
              Credit(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

double getFloat_CVIP(double low_limit, double up_limit)
{
    double x;
    int error_flag;
    char *cp,*endcp;                /* char pointer */
    const char *fn = "getFloat_CVIP";

/* check for limit error, low may equal high but not greater */
    if(low_limit > up_limit) {
        printf("\nLimit error, lower > upper\n");
        return 0.0;
    }
    
/* get the string and make sure x is in range */
    do {
        cp = getString_CVIP();
        x = strtod(cp,&endcp);
        error_flag = (cp == endcp) || (*endcp != '\0'); /* detect errors */
        if( error_flag ) {
           perror_CVIP(fn, "the following problem has occurred");
           msg_CVIP(fn, "please enter another value: ");
        }
        else if(x < low_limit || x > up_limit) {
           error_CVIP(fn, "value must be in the range %1.2g...%1.2g.", low_limit, up_limit);
           msg_CVIP(fn, "please enter another value: ");
        }
        free(cp);
    } while(x < low_limit || x > up_limit || error_flag);

/* return result */
    return(x);
}


#if 0
int *get_larray( const char *sepchars, int base, long low_limit,
                 long up_limit, int minn, int maxn, int *n )
{
   unsigned int no_of_tokens=0, error_flag, count;
   char *strP, *endcp, *word, bitbucket[80];
   const char *fn = "get_larray";
   int *larray, *lP;

   larray = (long *) malloc(sizeof(long)*maxn);
   if(!larray) {
          error_CVIP(fn, "\nInteger array allocation error.");
          return NULL;
   }

   while( no_of_tokens < minn ) {

      if( no_of_tokens )
         msg_CVIP(fn, "you need atleast %ld more values...\n", low_limit-no_of_tokens);

      strP = (char *) calloc(80, 1);
      if(!strP) {
          error_CVIP(fn, "\nString allocation error.");
          return NULL;
      }

      if( fgets(strP, LINELENGTH-BUFLENGTH, stdin) == NULL ) {
         error_CVIP(fn, "\nerror occured while reading from \"stdin\".");
         return NULL;
      }

      count = 0;
      if( strP[LINELENGTH-BUFLENGTH-1] != '\0' ) {
         while( count < 30 &&   ) count++;
         if( count < 0 ) {
            error_CVIP(fn, "buffer is full! can not parse input....\n");
            return NULL;
         }
         else {
            count = (LINELENGTH-1)-count;
            strncpy( buf, strP, count );
            strP[LINELENGTH-1] = '\0';
         }
      }

      word = strtok(strP,sepchars);
      while(word != NULL) {
         *lP = strtol(word, &endcp, base);
         error_flag = (word == endcp) || (*endcp != '\0'); /* detect errors */
         if( error_flag ) {
            perror_CVIP(fn, "the following problem has occurred");
            msg_CVIP(fn, "please enter another value instead of %s to replace it...\n", word);
         }
         else if(*lP < low_limit || *lP > up_limit) {
            error_CVIP(fn, "value %ld is not in the range %ld...%ld.", *lP, low_limit, up_limit);
            msg_CVIP(stderr, "%s: please enter another value to replace it...\n");
         }
         else {
            lP++;
            no_of_tokens++;
         }

         if( no_of_tokens == maxn ) {
            if( strchr(word + strlen(word) + 2, '\n') == NULL )
               do {
                  if( fgets(bitbucket, 80, stdin) == NULL ) {
                     error_CVIP(fn, "\nerror occured while reading from \"stdin\".");
                     return NULL;
                  } 
               } while( strchr(bitbucket, '\n') == NULL );
         }

      word = strtok(NULL,sepchars);
      }
   }

return((long *) realloc(larray, sizeof(long)*no_of_tokens));
}

#endif


char *
getEnv_CVIP(
	const char	*name
)
{
	char		*strP, *valP;

	if((strP = getenv(name)) == NULL)
		return NULL;
	else {
		valP = malloc(strlen(strP)+1);
		(void) strcpy(valP, strP);
	}

	return valP;
}
