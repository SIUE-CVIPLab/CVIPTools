
/***************************************************************************
* =========================================================================
*
*   Computer Vision and Image Processing Lab - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: Cooccurrence_matrix.c 
*           Description: it contains the function to calculate Co-occurrence matrix of an image 
*   Initial Coding Date: November 17, 2008
*           Portability: Standard (ANSI) C
*             Credit(s): Jhansi Lakshmi Akkineni
*                        Southern Illinois University at Edwardsville
*
** Copyright (c) 1995, 1996, SIUE - Scott Umbaugh, Kun Luo, Yansheng Wei
****************************************************************************/

/*
** include header files
*/

#include "CVIPconvert.h"
#include "CVIPimage.h"

Matrix *Cooccurrence_matrix(Image *inputImage, int direction, int bands, int distance, int row1, int col1, int row2, int col2, int zerorowcol){

	byte 		**image; 	/* 2-d matrix data pointer */
    int 		r,r1,		/* row index */
			c,c1; 		/* column index */
			
    int 	no_of_rows,	/* number of rows in image */
			no_of_cols;	/* number of columns in image */

    int matrix_row = 256, matrix_col = 256;
	int count = 0;

	int i, j;
	Matrix *Co_Var;

	
    /* 
    ** Gets the number of rows in the input image  
    */
    no_of_rows =  getNoOfRows_Image(inputImage);
	

    /* 
    ** Gets the number of columns in the input image  
    */
    no_of_cols =  getNoOfCols_Image(inputImage);
	

	image = getData_Image(inputImage, bands);
	

	Co_Var = new_Matrix(matrix_row, matrix_col, CVIP_FLOAT, REAL);

	// Calculating the Co-occurrence matrix for each band 

	for(i=0; i< matrix_row; i++)
	{
		for(j=0; j< matrix_col; j++)
		{
			((float**)(Co_Var->rptr))[i][j] = 0.0;
		}
	}
			switch (direction){

			case 0: 
				// horizontal
				for(r=row1; r<=row2; r++)
				{
					for(c=col1; c<=(col2-distance); c++)
					{
						i = image[r][c];
						j = image[r][c+distance];
						((float**)(Co_Var->rptr))[i][j] = ((float**)(Co_Var->rptr))[i][j] + 1;
					}
					for(c=col2; c>=(col1+distance); c--)
					{
						i = image[r][c];
						j = image[r][c-distance];
						((float**)(Co_Var->rptr))[i][j] = ((float**)(Co_Var->rptr))[i][j] + 1;
					}
				}
				
			break;

			case 1:
				// in right diagonal 45 degrees
				for(r=(row1+distance); r<=row2; r++)
				{
					for(c=col1; c<=(col2-distance); c++)
					{
						i = image[r][c];
						j = image[r-distance][c+distance];
						((float**)(Co_Var->rptr))[i][j] = ((float**)(Co_Var->rptr))[i][j] + 1;
					}
				}
					
				//in right diagonal 225 degrees
				for(r=row1; r<=(row2-distance); r++)
				{
					for(c=col2; c>=(col1+distance); c--)
					{
						i = image[r][c];
						j = image[r+distance][c-distance];
						((float**)(Co_Var->rptr))[i][j] = ((float**)(Co_Var->rptr))[i][j] + 1;
					}
				}
			break;

			case 2:
				//vertical 
				for(c=col1; c<=col2; c++)
				{
					for(r=row1; r<=(row2-distance); r++)
					{
						i = image[r][c];
						j = image[r+distance][c];
						((float**)(Co_Var->rptr))[i][j] = ((float**)(Co_Var->rptr))[i][j] + 1;
					}
					for(r=row2; r>=(row1+distance); r--)
					{
						i = image[r][c];
						j = image[r-distance][c];
						((float**)(Co_Var->rptr))[i][j] = ((float**)(Co_Var->rptr))[i][j] + 1;
					}
				}
			break;

			case 3: 
				// in left diagonal 315 degrees
				for(r=row1; r<=(row2-distance); r++)
				{
					for(c=col1; c<=(col2-distance); c++)
					{
						i = image[r][c];
						j = image[r+distance][c+distance];
						((float**)(Co_Var->rptr))[i][j] = ((float**)(Co_Var->rptr))[i][j] + 1;
					}
				}
					
				//in left diagonal 135 degrees
				for(r=row2; r>=(row1+distance); r--)
				{
					for(c=col2; c>=(col1+distance); c--)
					{
						i = image[r][c];
						j = image[r-distance][c-distance];
						((float**)(Co_Var->rptr))[i][j] = ((float**)(Co_Var->rptr))[i][j] + 1;
					}
				}
			break;
				
			}

	if(zerorowcol ==0)
	{
		r1=1;
		c1=1;
	}
	else if(zerorowcol ==1)
	{
		r1=0;
		c1=0;
	}

	for(r=r1; r<matrix_row; r++)
	{
		for(c=c1; c<matrix_col; c++)
		{
			count = count + ((float**)(Co_Var->rptr))[r][c];
		}
	}

	for(r=r1; r<matrix_row; r++)
	{
		for(c=c1; c<matrix_col; c++)
		{
			((float**)(Co_Var->rptr))[r][c] = (((float**)(Co_Var->rptr))[r][c] / (float)count);
		}
	}
	return Co_Var;
}