#include <stdlib.h>
/*
 *$Author: yawei $
 *$Id: ee.c,v 1.2 1997/01/16 21:03:50 yawei Exp $
 *$Log: ee.c,v $
 *Revision 1.2  1997/01/16 21:03:50  yawei
 *updated changes
 *
 * Revision 1.1  1995/10/25  00:46:57  kluo
 * Initial revision
 *
 * Revision 1.2  1995/07/10  17:59:41  dlyons
 * Port to Solaris
 *
 */

#include <math.h>
#include <setjmp.h>
#include <time.h>
#include "ee.h"
#include "eefunc.h"

int   ERROR;                 /* The error number */
char  ERTOK[TOKLEN + 1];     /* The token that generated the error */
int   ERPOS;                 /* The offset from the start of the expression */
char* ERANC;                 /* Used to calculate ERPOS */

/*
   Add any "constants" here...  These are "read-only" values that are
   provided as a convienence to the user.  Their values can not be
   permanently changed.  The first field is the variable name, the second
   is its value.
*/
VARIABLE Consts[] =
	{
	/* name, value */
	{ "pi",      M_PI },
	{ "e",       M_E },
	{ 0 }
	};

VARIABLE        Vars[MAXVARS];       /* Array for user-defined variables */
unsigned char*  expression;          /* Pointer to the user's expression */
unsigned char   token[TOKLEN + 1];   /* Holds the current token */
int             type;                /* Type of the current token */
jmp_buf         jb;                  /* jmp_buf for errors */


FUNCTION Funcs[] =
	{
	{ "sin",     1,    sin },
	{ "cos",     1,    cos },
	{ "tan",     1,    tan },
	{ "asin",    1,    asin },
	{ "acos",    1,    acos },
	{ "atan",    1,    atan },
	{ "sinh",    1,    sinh },
	{ "cosh",    1,    cosh },
	{ "tanh",    1,    tanh },
	{ "exp",     1,    exp },
	{ "log",     1,    log },
	{ "log10",   1,    log10 },
	{ "sqrt",    1,    sqrt },
	{ "floor",   1,    floor },
	{ "ceil",    1,    ceil },
	{ "abs",     1,    fabs },
/*	{ "hypot",   2,    hypot },*/
	{ "deg",     1,    deg },
	{ "rad",     1,    rad },
	{ "p2f",     3,    p2f },
	{ "f2p",     3,    f2p },
	{ "f2a",     3,    f2a },
	{ "p2a",     3,    p2a },
	{ "a2f",     3,    a2f },
	{ "a2p",     3,    a2p },
	{ "imp",     1,    impulse },
	{ "d",       1,    impulse },
	{ "step",    1,    step },
	{ "u",       1,    step },
	{ "ramp",    1,    ramp },
	{ "r",       1,    ramp },
	{ "rand",    2,    randf },
	{ "randi",   2,    randi },
	{ "gauss",   3,	   gauss },
	{ 0 }
	};
	

/*************************************************************************
**                                                                       **
** GetSymbol( char* s )                                                  **
**                                                                       **
** This routine obtains a value from the program's environment.          **
**                                                                       **
 *************************************************************************/

GetSymbol( s, v )
char* s;
double* v;
	{
	char* e;

	e = getenv( s );
	if( !e )
		return( 0 );
	*v = atof( e );
	return( 1 );
	}


/*************************************************************************
**                                                                       **
** strlwr( char* s )   Internal use only                                 **
**                                                                       **
** This routine converts a string to lowercase.  I know many compilers   **
** offer their own routine, but my VMS compiler didn't so...             **
** Again, this one is ASCII specific!                                    **
**                                                                       **
 *************************************************************************/

static strlwr( s )
char * s;
	{
	while( *s )
		{
		if( *s >= 'A' && *s <= 'Z' )
			*s += 32;
		s++;
		}
	}


/*************************************************************************
**                                                                       **
** ClearAllVars()                                                        **
**                                                                       **
** Erases all user-defined variables from memory. Note that constants    **
** can not be erased or modified in any way by the user.                 **
**                                                                       **
** Returns nothing.                                                      **
**                                                                       **
 *************************************************************************/

ClearAllVars()
	{
	int i;

	for( i = 0; i < MAXVARS; i++ )
		{
		*Vars[i].name = 0;
		Vars[i].value = 0;
		}
	}


/*************************************************************************
**                                                                       **
** ClearVar( char* name )                                                **
**                                                                       **
** Erases the user-defined variable that is called NAME from memory.     **
** Note that constants are not affected.                                 **
**                                                                       **
** Returns 1 if the variable was found and erased, or 0 if it didn't     **
** exist.                                                                **
**                                                                       **
 *************************************************************************/

ClearVar( name )
char * name;
	{
	int i;

	for( i = 0; i < MAXVARS; i++ )
		if( *Vars[i].name && ! strcmp( name, Vars[i].name ) )
			{
			*Vars[i].name = 0;
			Vars[i].value = 0;
			return( 1 );
			}
	return( 0 );
	}


/*************************************************************************
**                                                                       **
** GetValue( char* name, double* value )                                   **
**                                                                       **
** Looks up the specified variable (or constant) known as NAME and       **
** returns its contents in VALUE.                                        **
**                                                                       **
** First the user-defined variables are searched, then the constants are **
** searched.                                                             **
**                                                                       **
** Returns 1 if the value was found, or 0 if it wasn't.                  **
**                                                                       **
 *************************************************************************/

GetValue( name, value )
char * name;
double * value;
	{
	int i;

	/* First check for an environment variable reference... */
	if( *name == '_' )
		return( GetSymbol( name + 1, value ) );
	/* Now check the user-defined variables. */
	for( i = 0; i < MAXVARS; i++ )
		if( *Vars[i].name && ! strcmp( name, Vars[i].name ) )
			{
			*value = Vars[i].value;
			return( 1 );
			}
	/* Now check the programmer-defined constants. */
	for( i = 0; *Consts[i].name; i++ )
		if( *Consts[i].name && ! strcmp( name, Consts[i].name ) )
			{
			*value = Consts[i].value;
			return( 1 );
			}
	return( 0 );
	}


/*************************************************************************
**                                                                       **
** SetValue( char* name, double* value )                                   **
**                                                                       **
** First, it erases any user-defined variable that is called NAME.  Then **
** it creates a new variable called NAME and gives it the value VALUE.   **
**                                                                       **
** Returns 1 if the value was added, or 0 if there was no more room.     **
**                                                                       **
 *************************************************************************/

SetValue( name, value )
char * name;
double * value;
	{
	char b[30];
	int  i;

	ClearVar( name );
	for( i = 0; i < MAXVARS; i++ )
		if( ! *Vars[i].name )
			{
			strcpy( Vars[i].name, name );
			Vars[i].name[VARLEN] = 0;
			Vars[i].value = *value;
			return( 1 );
			}
	return( 0 );
	}


/*************************************************************************
**                                                                       **
** Parse()   Internal use only                                           **
**                                                                       **
** This function is used to grab the next token from the expression that **
** is being evaluated.                                                   **
**                                                                       **
 *************************************************************************/

static Parse()
	{
	char* t;

	type = 0;
	t = (char*)token;
	while( iswhite( *expression ) )
		expression++;
	if( isdelim( *expression ) )
		{
		type = DEL;
		*t++ = *expression++;
		}
	else	if( isnumer( *expression ) )
			{
			type = NUM;
			while( isnumer( *expression ) )
				*t++ = *expression++;
			}
		else	if( isalpha( *expression ) )
				{
				type = VAR;
				while( isalpha( *expression ) )
					*t++ = *expression++;
				token[VARLEN] = 0;
				}
			else	if( *expression )
					{
					*t++ = *expression++;
					*t = 0;
					ERR( E_SYNTAX );
					}
	*t = 0;
	while( iswhite( *expression ) )
	expression++;
	}


/*************************************************************************
**                                                                       **
** Level1( double* r )   Internal use only                                 **
**                                                                       **
** This function handles any variable assignment operations.             **
** It returns a value of 1 if it is a top-level assignment operation,    **
** otherwise it returns 0                                                **
**                                                                       **
 *************************************************************************/

static Level1( r )
double *r;
	{
	char t[VARLEN + 1];

	if( type == VAR )
		if( *expression == '=' )
			{
			strcpy( t, token );
			Parse();
			Parse();
			if( !*token )
				{
				ClearVar( t );
				return(1);
				}
			Level2( r );
			if( ! SetValue( t, r ) )
				ERR( E_MAXVARS );
			return( 1 );
			}
	Level2( r );
	return( 0 );
	}


/*************************************************************************
**                                                                       **
** Level2( double* r )   Internal use only                                 **
**                                                                       **
** This function handles any addition and subtraction operations.        **
**                                                                       **
 *************************************************************************/

static Level2( r )
double *r;
	{
	double t = 0;
	char o;

	Level3( r );
	while( (o = *token) == '+' || o == '-' )
		{
		Parse();
		Level3( &t );
		if( o == '+' )
			*r = *r + t;
		else	if( o == '-' )
				*r = *r - t;
		}
	}


/*************************************************************************
**                                                                       **
** Level3( double* r )   Internal use only                                 **
**                                                                       **
** This function handles any multiplication, division, or modulo.        **
**                                                                       **
 *************************************************************************/

static Level3( r )
double *r;
	{
	double t;
	char o;

	Level4( r );
	while( (o = *token) == '*' || o == '/' || o == '%' )
		{
		Parse();
		Level4( &t );
		if( o == '*' )
			*r = *r * t;
		else	if( o == '/' )
				{
				if( t == 0 )
					ERR( E_DIVZERO );
				*r = *r / t;
				}
			else	if( o == '%' )
					{
					if( t == 0 )
						ERR( E_DIVZERO );
					*r = fmod( *r, t );
					}
		}
	}


/*************************************************************************
**                                                                       **
** Level4( double* r )   Internal use only                                 **
**                                                                       **
** This function handles any "to the power of" operations.               **
**                                                                       **
 *************************************************************************/

static Level4( r )
double *r;
	{
	double t;

	Level5( r );
	if( *token == '^' )
		{
		Parse();
		Level5( &t );
		*r = pow( *r, t );
		}
	}


/*************************************************************************
**                                                                       **
** Level5( double* r )   Internal use only                                 **
**                                                                       **
** This function handles any unary + or - signs.                         **
**                                                                       **
 *************************************************************************/

static Level5( r )
double *r;
	{
	char o = 0;

	if( *token == '+' || *token == '-' )
		{
		o = *token;
		Parse();
		}
	Level6( r );
	if( o == '-' )
	*r = -*r;
	}


/*************************************************************************
**                                                                       **
** Level6( double* r )   Internal use only                                 **
**                                                                       **
** This function handles any literal numbers, variables, or functions.   **
**                                                                       **
 *************************************************************************/

static Level6( r )
double *r;
	{
	int  i;
	int  n;
	double a[3];

	if( *token == '(' )
		{
		Parse();
		if( *token == ')' )
			ERR( E_NOARG );
		Level1( r );
		if( *token != ')' )
			ERR( E_UNBALAN );
		Parse();
		}
	else
		{
		if( type == NUM )
			{
			*r = (double) atof( (const char*)token );
			Parse();
			}
		else	if( type == VAR )
				{
				if( *expression == '(' )
					{
					for( i = 0; *Funcs[i].name; i++ )
						if( ! strcmp( token, Funcs[i].name ) )
							{
							Parse();
							n = 0;
							do
								{
								Parse();
								if( *token == ')' || *token == ',' )
									ERR( E_NOARG );
								a[n] = 0;
								Level1( &a[n] );
								n++;
								}
							while( n < 4 && *token == ',' );
							Parse();
							if( n != Funcs[i].args )
								{
								strcpy( token, Funcs[i].name );
								ERR( E_NUMARGS );
								}
							*r = Funcs[i].func( a[0], a[1], a[2] );
							return;
							}
					if( ! *Funcs[i].name )
						ERR( E_BADFUNC );
					}
				else	if( ! GetValue( token, r ) )
						ERR( E_UNKNOWN );
				Parse();
				}
			else
				ERR( E_SYNTAX );
			}
	}


/*************************************************************************
**                                                                       **
** Evaluate( char* e, double* result, int* a )                             **
**                                                                       **
** This function is called to evaluate the expression E and return the   **
** answer in RESULT.  If the expression was a top-level assignment, a    **
** value of 1 will be returned in A, otherwise it will contain 0.        **
**                                                                       **
** Returns E_OK if the expression is valid, or an error code.            **
**                                                                       **
 *************************************************************************/

Evaluate( e, result, a )
char* e;
double* result;
int* a;
	{
	if( setjmp( jb ) )
		return( ERROR );
	expression = (unsigned char*)e;
	ERANC = e;
	strlwr( expression );
	*result = 0;
	Parse();
	if( ! *token )
		ERR( E_EMPTY );
	*a = Level1( result );
	return( E_OK );
	}


/*************************************************************************
**                                                                       **
** What follows is a main() routine that evaluates the command line      **
** arguments one at a time, and displays the results of each expression. **
** Without arguments, it becomes an interactive calculator.              **
**                                                                       **
 *************************************************************************/

#include <stdio.h>

char* ErrMsgs[] =
	{
	"Syntax error",
	"Unbalanced parenthesis",
	"Division by zero",
	"Unknown variable",
	"Maximum variables exceeded",
	"Unrecognized funtion",
	"Wrong number of arguments to funtion",
	"Missing an argument",
	"Empty expression"
	};

float *eemain(int argc,char *argv)
	{
	double  result;
	float * ee;
	int   i;
	int   ec;
	int   a;
	char  line[1024];
	char* v;
	char xstring[32];

	srand(time(NULL));
	/* Clear all variables */
	ClearAllVars();
	/* Copy the expression into the string "line" */
	strcpy(line,argv);
	ee=(float*)calloc(argc,sizeof(float));
	if(!ee)
		{
		fprintf(stderr,"Expression Evaluator: Could not calloc\n");
		exit(1);
		}
	for(i=0;i<argc;i++)
		{
		sprintf(xstring,"x=%d",i);
		ec=Evaluate(xstring,&result,&a);
		if((ec=Evaluate(line,&result,&a))==E_OK)
			{
			ee[i]=(float)result;
			}
		else
			if(ec!=E_EMPTY)
				{
				printf( "ERROR: %s - %s", ErrMsgs[ERROR - 1], ERTOK );
				printf( "\n%s", ERANC );
				printf( "\n%*s^\n", ERPOS, "" );
				exit(1);
				}
		}
	return ee;
	}
