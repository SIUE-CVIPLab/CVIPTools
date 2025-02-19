/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: VectorMinMax.c
*           Description: routines to find the minimum or maximum value in
*			 a vector.
*         Related Files: CVIPvector.h, Imakefile
*   Initial Coding Date: Tue Aug 31 14:56:23 CDT 1993
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
** $Log: VectorMinMax.c,v $
** Revision 1.2  1997/03/08 01:02:35  yawei
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
** Revision 1.1  1994/10/30 17:59:04  hanceg
** CVIPtools1.0 source file - G. Hance
**
*
****************************************************************************/
#include "CVIPtoolkit.h"

#define MIN_VECTOR(vec_,length_,min_,type_) { \
	type_ *a_ = (type_ *) vec_; \
	type_ temp_ = a_[0]; \
	register type_ smallest_ = a_[0]; \
	register type_ *ptr_ = &a_[length_]; \
	for(;;) { \
		while( *--ptr_ > smallest_ ); \
		if (ptr_ == &a_[0]) break; \
		a_[0] = smallest_ = *ptr_; \
	} \
	a_[0] = temp_; \
	min_ = smallest_; \
} \

#define MAX_VECTOR(vec_,length_,max_,type_) { \
	type_ *a_ = (type_ *) vec_; \
	type_ temp_ = a_[0]; \
	register type_ greatest_ = a_[0]; \
	register type_ *ptr_ = &a_[length_]; \
	for(;;) { \
		while( *--ptr_ < greatest_ ); \
		if (ptr_ == &a_[0]) break; \
		a_[0] = greatest_ = *ptr_; \
	} \
	a_[0] = temp_; \
	max_ = greatest_; \
} \


/****************************************************************
                   Name: findMinVal_Vector
          Expanded Name: find minimum value vector
             Parameters: <a> - pointer to vector
			 <length> - no of elements in vector
			 <data_type> - valid CVIPtools data type (i.e. one of
			 CVIP_BYTE, CVIP_SHORT, CVIP_INTEGER, CVIP_FLOAT or CVIP_DOUBLE)
                Returns: the minimum value in the span of the vector <a>.
            Description: Finds the minimum value in the span of a vector. The
			 value is returned as a floating point value of type
			 double.
	    Diagnostics: none.
             References: none.
              Author(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

double findMinVal_Vector(void *a, unsigned length, CVIP_TYPE data_type) 
{
   double min;

   switch(data_type) {
      case    CVIP_BYTE: MIN_VECTOR(a,length,min,byte);
		    break;
      case   CVIP_SHORT: MIN_VECTOR(a,length,min,short);
		    break;
      case CVIP_INTEGER: MIN_VECTOR(a,length,min,int);
		    break;
      case   CVIP_FLOAT: MIN_VECTOR(a,length,min,float);
		    break;
      case  CVIP_DOUBLE: MIN_VECTOR(a,length,min,double);
		    break;
           default: fprintf(stderr,"unsupported data type!\n");
    }

return min;
}


/****************************************************************
                   Name: findMaxVal_Vector
          Expanded Name: find maximum value vector
             Parameters: <a> - pointer to vector
			 <length> - no of elements in vector
			 <data_type> - valid CVIPtools data type (i.e. one of
			 CVIP_BYTE, CVIP_SHORT, CVIP_INTEGER, CVIP_FLOAT or CVIP_DOUBLE)
                Returns: the maximum value in the span of the vector <a>.
            Description: Finds the maximum value in the span of a vector. The
			 value is returned as a floating point value of type
			 double.
	    Diagnostics: none.
             References: none.
              Author(s): Gregory Hance
		         Southern Illinois University @ Edwardsville
****************************************************************/

double findMaxVal_Vector(void *a, unsigned length, CVIP_TYPE data_type) 
{
   double max;

   switch(data_type) {
      case    CVIP_BYTE: MAX_VECTOR(a,length,max,byte);
		    break;
      case   CVIP_SHORT: MAX_VECTOR(a,length,max,short);
		    break;
      case CVIP_INTEGER: MAX_VECTOR(a,length,max,int);
		    break;
      case   CVIP_FLOAT: MAX_VECTOR(a,length,max,float);
		    break;
      case  CVIP_DOUBLE: MAX_VECTOR(a,length,max,double);
		    break;
      default: fprintf(stderr,"unsupported data type!\n");
    }

return max;
}

   
	
		
	


