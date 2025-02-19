/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: ObjectContour.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Fri Nov 22 14:47:05 CST 1996
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Tim Feldman, Greg Hance 
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1996 SIUE - by Scott Umbaugh and Greg Hance.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
****************************************************************************/
/*****************************************************************************
*
*	contour.c
*
*	Author:	Tim Feldman, original author modified by Greg Hance
*		Island Graphics Corporation
*
*	Vectorizes the outline of an elevation contour in a set of sampled
*	data.  Uses Freeman chain encoding.
*
*****************************************************************************/

/*****************************************************************************
*
*	Include files
*
*****************************************************************************/

#include "ObjectContour.h"

/*****************************************************************************
*
*	Constants
*
*****************************************************************************/

/***	these are the 'dir' values in a Vector:

	0	right
	1	right and up
	2	up
	3	left and up
	4	left
	5	left and down
	6	down
	7	right and down		***/

/*****************************************************************************
*
*	Global data
*
*****************************************************************************/

/***	these are the coordinates of the edges of the
	rectangular array of sample points		***/

static int Y_MIN;
static int Y_MAX;
static int X_MIN;
static int X_MAX;

/***	this points to the first member in the Freeman chain of vectors	***/

static Vector *	chain;

/***	these are the coordinates of the starting point
	of the Freeman chain, in the array of sample points	***/

static int	start_x;
static int	start_y;

/***	this is the elevation of the contour to be outlined
	in the array of sample points				***/

static int	elev;

static int	sample_data[8][8] =
{
	100, 100, 100, 100, 100, 100, 100,   0,
	100, 100, 200, 200, 200, 200, 100, 100,
	100, 200, 200, 250, 255, 200, 100, 100,
	100, 200, 200, 250, 200, 200, 100, 100,
	100, 200, 200, 250, 200, 200, 100, 100,
	100, 200, 100, 200, 100, 200, 200, 100,
	100, 200, 100, 100, 100, 200, 200, 200,
	100, 100, 100, 100, 100, 100, 100, 200
};

static int **	sample;

/*****************************************************************************
*
*	Procedures
*
*****************************************************************************/

/*****************************************************************************
*
*	in_cont(y, x)
*
*	Determines whether the sample point at 'y, x' is within the contour
*	being outlined.  Points outside of the array of samples are not
*	in the contour.
*
*	Returns 0 if the point is not in the contour.
*	Returns 1 if the point is     in the contour.
*
*****************************************************************************/

static short
in_cont(
	int	y,
	int	x
)
{
	if ( (y < Y_MIN) || (y > Y_MAX) || (x < X_MIN) || (x > X_MAX) )
		return(0);

	if (sample[y][x] == elev)
		return(1);
	else
		return(0);
}

/*****************************************************************************
*
*	probe(y, x, dir, new_y, new_x)
*
*	Checks a sample neighboring 'y, x' to see if it is in the contour
*	being outlined.  'dir' specifies which neighboring sample to check.
*	'new_y, new_x' always get the coordinates of the neighbor.
*
*	Returns 0 if the neighbor is not in the contour.
*	Returns 1 if the neighbor is     in the contour.
*
*****************************************************************************/

static short
probe(  
	int	y,
	int	x,
	int	dir,
	int *	new_y,
	int *	new_x
)

{
	/***	figure out coordinates of neighbor	***/

	if ( (dir < 2) || (dir > 6) )
		++x;

	if ( (dir > 2) && (dir < 6) )
		--x;

	if ( (dir > 0) && (dir < 4) )
		--y;

	if (dir > 4)
		++y;

	/***	always return the new coordinates	***/

	*new_y = y;
	*new_x = x;

	/***	determine if the new sample point is in the contour	***/

	return(in_cont(y, x));
}

/*****************************************************************************
*
*	neighbor(y, x, last_dir, new_y, new_x)
*
*	Finds a neighbor of the sample at 'y, x' that is in the same
*	contour.  Always follows the contour in a clockwise direction.
*	'last_dir' is the direction that was used to get to 'y, x'
*	when it was found.  'new_y, new_x' always get the coordinates
*	of the neighbor.
*
*	This procedure should only be called for a sample that has at
*	least one neighbor in the same contour.
*
*	Returns the direction to the neighbor.
*
*****************************************************************************/

static int
neighbor(    
	int y, 
	int x, 
	int last_dir, 
	int *new_y, 
	int *new_x 
)
{
int	n;
int	new_dir;

	/***	figure out where to start looking for a neighbor --
		always look ahead and to the left of the last direction

		if the last vector was 0
		then start looking at  1

		if the last vector was 1
		then start looking at  3

		if the last vector was 2
		then start looking at  3

		if the last vector was 3
		then start looking at  5

		if the last vector was 4
		then start looking at  5

		if the last vector was 5
		then start looking at  7

		if the last vector was 6
		then start looking at  7

		if the last vector was 7
		then start looking at  1	***/

	if (last_dir & 0x01)
	{
		/***	last dir is odd --
			add 2 to it		***/

		new_dir = last_dir + 2;
	}
	else
	{
		/***	last dir is even --
			add 1 to it		***/

		new_dir = last_dir + 1;
	}

	/***	keep new_dir in the range 0 through 7	***/

	if (new_dir > 7)
		new_dir -= 8;

	/***	probe the neighbors, looking for one on the edge	***/

	for (n = 0; n < 8; n++)
	{
		if (probe(y, x, new_dir, new_y, new_x))
		{
			/***	found the next clockwise edge neighbor --
				its coordinates have already been
				stuffed into new_y, new_x		***/

			return(new_dir);
		}
		else
		{
			/***	check the next clockwise neighbor	***/

			if (--new_dir < 0)
				new_dir += 8;
		}
	}
}

/*****************************************************************************
*
*	build()
*
*	Builds a Freeman chain of vectors describing the edge of the
*	contour with elevation 'elev'.  Always follows the contour
*	in a clockwise direction.  Uses 'start_y, start_x' as tentative
*	starting point; modifies them to hold coordinates of first point
*	in chain.
*
*	Returns 0 if unsuccessful.
*	Returns 1 if   successful.
*
*****************************************************************************/

short 
build_ChainCode(
	ChainCode *ccP,
	Image *imageP,
	int x_min,
	int y_min,
	int x_max,
	int y_max
)
{
const char 	*fn = "build";
int		y;
int		x;
int		new_y;
int		new_x;
int		dir;
int		last_dir;
Vector *	new;
Vector *	prev;

	Y_MIN = y_min;
	Y_MAX = y_max;
	X_MIN = x_min;
	X_MAX = x_max;

	elev = ccP->elev;

	sample = (int **) getData_Matrix(getBand_Image(imageP,0));

	/***	go left in the starting row until out of the contour	***/

	while (in_cont(ccP->start_y, ccP->start_x))
		--(ccP->start_x);

	/***	move back right one point, to the leftmost edge
		in the contour, in that row			***/

	(ccP->start_x)++;

        if(!in_cont(ccP->start_y, ccP->start_x))
		return(0);

	start_x = ccP->start_x;
	start_y = ccP->start_y;

	/***	create the head of the chain	***/

	chain = (Vector *)NULL;
	prev = (Vector *)NULL;

	/***	check if the starting point
		has no neighbors in the contour --
		the starting direction to check is arbitrary	***/

	y = start_y;
	x = start_x;

	dir = 0;

	for ( ; ; )
	{
		if (probe(y, x, dir, &new_y, &new_x))
		{
			/***	found a neighbor in that direction
				(its coordinates are in new_y, new_x
				but we don't use them here)		***/

			break;
		}

		/***	try next direction	***/

		if (++dir == 8)
		{
			/***	starting point has no neighbors --
				make the chain one vector long	***/
			
			/***	allocate storage for the vector	***/

			if ( (chain = (Vector *)malloc(sizeof(Vector))) == NULL)
			{
				printf("Insufficient memory available.\n");
				return(0);
			}

			/***	fill in the vector --
				the direction is arbitrary,
				since the point is isolated	***/

			chain->dir = 0;
			chain->next = (Vector *)NULL;
 			
			ccP->chain = chain;
			ccP->no_of_vectors++;

			return(1);
		}
	}

	/***	get ready to follow the edge --
		since we are at the left edge,
		force initial probe to be to upper left
		by initializing last_dir to 1		***/

	last_dir = 1;

	/***	follow the edge clockwise, building a Freeman chain	***/

	msg_CVIP(fn, "building Freeman chain... \n");
/*	msg_CVIP(fn, "forming vector    0."); 	*/

	for ( ; ; )
	{
		/***	get the next point on the edge
			and the vector to it		***/

		dir = neighbor(y, x, last_dir, &new_y, &new_x);

		/***	allocate storage for the new vector	***/

		if ( (new = (Vector *)malloc(sizeof(Vector))) == NULL)
		{
			printf("Insufficient memory available.\n");
			return(0);
		}

		/***	fill in the new vector	***/

		new->dir = dir;
		new->next = (Vector *)NULL;

		ccP->no_of_vectors++;

		if (prev)
		{
			/***	add it to the existing chain	***/

			prev->next = new;
		}
		else
		{
			/***	it is the first vector in the chain	***/

			ccP->chain = chain = new;
		}

		/***	maybe done with contour	***/

		if ( (new_y == start_y) && (new_x == start_x) ) {
			print_CVIP("\n");
			return(1);
		}

		/***	else get ready to continue following the edge	***/

		prev = new;
		y = new_y;
		x = new_x;
		last_dir = dir;
	}
}

/*****************************************************************************
*
*	report()
*
*	Follows the Freeman chain of vectors describing the edge of the
*	contour with elevation 'elev'.  Reports the elevation, start point,
*	direction vectors, and the number of vectors in the chain.
*
*****************************************************************************/

void
report_ChainCode(ChainCode *ccP)

{
Vector *	p;

	printf("Elevation = %d\n", ccP->elev);
	printf("Start point (y, x) = %d, %d\n", ccP->start_y, ccP->start_x);

	p = ccP->chain;

	while (p)
	{
		printf("%d\n", p->dir);
		p = p->next;
	}

	if (ccP->no_of_vectors > 1)
		printf("%d vectors in the chain.\n", ccP->no_of_vectors);
	else
		printf("1 vector in the chain.\n");
}

/*****************************************************************************
*
*	main()
*
*	Describes the outline of an elevation contour in the sampled data.
*
*	Returns  0 if   successful.
*	Returns -1 if unsuccessful.
*
*****************************************************************************/

int
test_contour()

{
	ChainCode *ccP;
	/***	get the elevation of the contour to follow
		and get a starting point within the contour --

		they are given explicitly in this example, but
		in a real application the user would provide them,
		or they would be found algorithmically			***/

	ccP = new_ChainCode(3,2,200);

	/***	follow the edge of the contour,
		building a Freeman chain of vectors		***/
#if 0
	if (build_ChainCode(ccP))
	{
		/***	report the results	***/

		report_ChainCode(ccP);
		return(0);
	}
	else
	{
		/***	failed	***/

		return(-1);
	}
#endif
}



ChainCode *new_ChainCode( int start_y, int start_x, int elev )
{
	ChainCode *ccP;

	if ( (ccP = (ChainCode *)calloc(1,sizeof(ChainCode))) == NULL)
	{
			error_CVIP("new_ChainCode", "Insufficient memory available.\n");
			return(0);
	}
	ccP->start_y = start_y;
	ccP->start_x = start_x;
	ccP->elev = elev;
	
	return ccP;
}


void
delete_ChainCode(
	ChainCode *ccP
)
{
	Vector *p, *t;
	
	p = ccP->chain;

	while (p)
	{
		t = p;
		p = p->next;
		free(t);
	}

	free(ccP);
}


void getXY_ChainCode(ChainCode *ccP, int **xP, int **yP)
{

Vector *	p;
int x, y;
int dir;
register int i;

	p = ccP->chain;
	x = ccP->start_x;
	y = ccP->start_y;

	i = 0;

	if(!(*xP))
		*xP = (int *) malloc(ccP->no_of_vectors*sizeof(int));
	if(!(*yP))
   		*yP = (int *) malloc(ccP->no_of_vectors*sizeof(int));

	while (p)
	{
		dir =  p->dir;

		if ( (dir < 2) || (dir > 6) )
			++x;

		if ( (dir > 2) && (dir < 6) )
			--x;

		if ( (dir > 0) && (dir < 4) )
			--y;

		if (dir > 4)
			++y;

		(*xP)[i] = x;
		(*yP)[i] = y;

		i++;

		p = p->next;
	}

}


void draw_ChainCode(
	ChainCode *ccP,
	Image *imageP
)
{
   int *xP = NULL, *yP = NULL;
   register int i;

   getXY_ChainCode(ccP,&xP,&yP);
   
   for(i=0; i < ccP->no_of_vectors; i++)
      setPixel_Image(imageP,byte,xP[i],yP[i],0,1);

   free(xP);
   free(yP);
}

int print_ChainCode(
	ChainCode *ccP,
	const char *name
	
)
{
	Vector *	p;
	FILE *fileP;

	if(!(fileP = openWrite_CVIP(name, CVIP_NO)))
		return 0;

	fprintf(fileP, "elevation : %d\n", ccP->elev);
	fprintf(fileP, "start point x : %d\n", ccP->start_x);
	fprintf(fileP, "start point y : %d\n", ccP->start_y);
	fprintf(fileP, "vectors in the chain : %d\n", ccP->no_of_vectors);

	p = ccP->chain;

	while (p)
	{
		fprintf(fileP, "%1hd\n", p->dir);
		p = p->next;
	}

	close_CVIP(fileP);
}



ChainCode *read_ChainCode(
	const char *name
	
)
{
	ChainCode *ccP;
	Vector *p, *prev;
	FILE *fileP;
	long elev, start_x, start_y, no_of_vectors;
	int check_fp, status;

	if(!(fileP = openRead_CVIP(name)))
		return NULL;

	elev = fGetInt_CVIP(fileP, &status, 2, ":");
		if(!status) return 0;

	start_x = fGetInt_CVIP(fileP, &status, 2, ":");
		if(!status) return 0;

	start_y = fGetInt_CVIP(fileP, &status, 2, ":");
		if(!status) return 0;

	no_of_vectors = fGetInt_CVIP(fileP, &status, 2, ":");
		if(!status) return 0;

	ccP = new_ChainCode(start_y, start_x, elev);

	p = ccP->chain = (Vector *) malloc(sizeof(Vector));

	do {
		if(ccP->no_of_vectors) {
			prev = p;
			p->next = (Vector *) malloc(sizeof(Vector));
			p = p->next;
		}
		check_fp = fscanf(fileP, "%1hd", &p->dir);
		ccP->no_of_vectors++;

	} while( check_fp != EOF );

	free(p);
	prev->next = NULL;
        ccP->no_of_vectors--;

	if(ccP->no_of_vectors != no_of_vectors) {
		error_CVIP("read_ChainCode", "found %d vectors, expected %d.",
		ccP->no_of_vectors, no_of_vectors);
		delete_ChainCode(ccP);
		return NULL;
	}

	close_CVIP(fileP);

	return(ccP);
}

