
/***************************************************************************
* =========================================================================
*
*   Computer Vision and Image Processing Lab - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: marr_hilbert_edge.c 
*           Description: Marr Hilbert's Edge Detector
*   Initial Coding Date: Feb 10th 2009
*           Portability: Standard (ANSI) C
*             Credit(s): Mounika Mamidi
*                        Southern Illinois University at Edwardsville
*
** Copyright (c) 1995, 2004, SIUE - Scott Umbaugh, Kun Luo, Yansheng Wei
****************************************************************************/


// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#include <list>
using namespace std;

/*
** corner structure - sortable based on corner strength, or 'q' value
*/
struct corner
{
	int row, col;
	float q;

	corner(int r, int c, float mag)
	{
		row = r;
		col = c;
		q = mag;
	}
	corner(const corner &copy)
	{
		row = copy.row;
		col = copy.col;
		q = copy.q;
	}
	int operator<(const corner &rhs) const
	{
		if(q < rhs.q) return 1;
		return 0;
	}
	double dist2(corner &c2)
	{
		//returns the squared distance between this corner and corner c2
		int dx = row - c2.row;
		int dy = col - c2.col;
		return (dx*dx)+(dy*dy);	
	}
};

bool isLocalMax(float **pixImg, int row, int col)
{
	float cp = pixImg[row][col];
	return
		(cp>=pixImg[row-1][col-1]) && (cp>=pixImg[row-1][col]) && (cp>=pixImg[row-1][col+1]) &&
		(cp>=pixImg[row][col-1])                               && (cp>=pixImg[row][col+1]) &&
		(cp>=pixImg[row+1][col-1]) && (cp>=pixImg[row+1][col]) && (cp>=pixImg[row+1][col+1]);
}


// Declare nonmaxima_mask function using extern "C":
extern "C" void nonmaxima_mask(float **pixImg, unsigned char **pixMask, int rows, int cols, int border, float dmin, int threshold);

// Define nonmaxima_mask function
void nonmaxima_mask(float **pixImg, unsigned char **pixMask, int rows, int cols, int border, float dmin, int threshold)
{
	float q;
	double dmin2 = dmin*dmin;
	list<corner> corners;
	list<corner>::iterator itr;

	for(int r=border; r<rows-border; r++)
	{
		for(int c=border; c<cols-border; c++)
		{
			q = pixImg[r][c];
			if((q > threshold) && isLocalMax(pixImg, r, c))
			{
				corners.push_back(corner(r, c, q));
			}
		}
	}

	corners.sort();
	corners.reverse();

	while(!corners.empty())
	{
		corner c = corners.front();
		corners.pop_front();
		pixMask[c.row][c.col] = 255;

		// delete all remaining corners close to c
		for(itr=corners.begin(); itr!=corners.end(); )
		{
			if(c.dist2(*itr) < dmin2)
				itr = corners.erase(itr);
			else
				itr++;
		}
	}
}
