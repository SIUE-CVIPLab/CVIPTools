/***************************************************************************
* =========================================================================
*
*   Computer Vision and Image Processing Lab - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: Texture_Features.c 
*           Description: it contains the functions to calculate texture features of an image 
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
#include "CVIPtexture.h"
#include <math.h>

extern Matrix *Cooccurrence_matrix(Image *inputImage, int direction, int bands, int distance, int row1, int col1, int row2, int col2, int zerorowcol);


TEXTURE2* texture2(Image *inputImage, Image *labeledImage, int band, int row, int col, int distance, int energy, int inertia, int correlation, int invDiff, int entropy, int zerorowcol){

	float meanx =0, meany=0, sigmax=0, sigmay=0; 
	int i, gray_value=0, row1, row2=0, col1, col2=0;
	int r, r1, c, c1; 		
    int 	no_of_rows,	no_of_cols;	
    Matrix *Co_Var;
	float tmp =0, temp = 0, max, min;
	byte 	**label_image;
	Image *tmpImage1, *tmpImage2, *tmpImage3, *maskImage, *dup_Image;
	TEXTURE2* tf;
	tf = (TEXTURE2 *) calloc(1,sizeof(TEXTURE2));
    if(!tf) {
        printf("\nERROR in TEXTURE structure allocate\n");
        exit(1);
    }

    no_of_rows =  getNoOfRows_Image(inputImage);
    no_of_cols =  getNoOfCols_Image(inputImage);
	row1 = no_of_rows; col1 = no_of_cols; 
	dup_Image = duplicate_Image(labeledImage);
	gray_value = getPixel_Image(labeledImage, int, col, row, 0);
	tmpImage1 = (Image *)threshold_segment(dup_Image,gray_value+1, CVIP_NO);
	dup_Image = duplicate_Image(labeledImage);
	tmpImage2 = (Image *)threshold_segment(dup_Image,gray_value-1, CVIP_NO);
	tmpImage3 = xor_Image(tmpImage1, tmpImage2);
	maskImage  =   and_Image(inputImage, tmpImage3);
	//view_Image(maskImage,"objectImage");
	for(r=0; r<no_of_rows; r++)
	{
		for(c=0; c<no_of_cols; c++)
		{
			temp = getPixel_Image(labeledImage, int, c, r, 0);
			if(temp == gray_value)
			{
				if(r < row1) row1 = r;
				if(c < col1) col1 = c;
				if(r > row2) row2 = r;
				if(c > col2) col2 = c;
			}
		}
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
	for(i=0; i<4; i++)
	{
		Co_Var = Cooccurrence_matrix(maskImage, i, band, distance, row1, col1, row2, col2, zerorowcol);
		if(energy==1)
		{
			tmp=0;
			for(r=r1; r<256; r++)
			{
				for(c=c1; c<256; c++)
				{
					temp = ((float**)(Co_Var->rptr))[r][c];
					tmp = tmp + (temp * temp);
				}
			}
			tf->energy[i] = tmp; 
		}
		/*else{ tf->energy[i] = "NaN"; }*/
		if(inertia==1)
		{
			tmp=0;
			for(r=r1; r<256; r++)
			{
				for(c=c1; c<256; c++)
				{
					temp = ((float**)(Co_Var->rptr))[r][c];
					tmp = tmp + ((r-c) * (r-c) * temp);
				}
			}
			tf->inertia[i] = tmp; 
		}
		/*else{ tf->inertia[i] = "NaN"; }*/
		if(invDiff==1)
		{
			tmp=0;
			for(r=r1; r<256; r++)
			{
				for(c=c1; c<256; c++)
				{
					temp = ((float**)(Co_Var->rptr))[r][c];
					if(r!=c)
						tmp = tmp + (temp/abs(r-c));
				}
			}
			tf->IDM[i] = tmp; 
		}
		/*else{ tf->IDM[i] = "NaN"; }*/
		if(entropy==1)
		{
			tmp=0;
			for(r=r1; r<256; r++)
			{
				for(c=c1; c<256; c++)
				{
					temp = ((float**)(Co_Var->rptr))[r][c];
					if(temp!=0)
						tmp = tmp + (temp * (log(temp)/log(2.0)));
				}
			}
			tf->entropy[i] = 0-tmp; 
		}
		/*else{ tf->entropy[i] = "NaN"; }*/
        if(correlation ==1)
		{
			tmp=0; temp=0;
			for(r=r1; r<256; r++)
			{
				for(c=r1; c<256; c++)
				{
					temp = temp + ((float**)(Co_Var->rptr))[r][c];
				}
				tmp = tmp + (r * temp);
				temp =0;
			}
			meanx = tmp;
			tmp = 0;
			// finding meany
			for(c=c1; c<256; c++)
			{
				for(r=r1; r<256; r++)
				{
					temp = temp + ((float**)(Co_Var->rptr))[r][c];
				}
				tmp = tmp + (c * temp);
				temp =0;
			}
			meany = tmp;
			tmp = 0;
			//finding sigmax
			for(r=r1; r<256; r++)
			{
				for(c=c1; c<256; c++)
				{
					temp = temp + ((float**)(Co_Var->rptr))[r][c];
				}
				tmp = tmp + ((r-meanx) *(r-meanx) * temp);
				temp =0;
			}
			sigmax = tmp;
			sigmax = (float)sqrt(sigmax);
			tmp=0;
			//finding sigmay
			for(c=c1; c<256; c++)
			{
				for(r=r1; r<256; r++)
				{
					temp = temp + ((float**)(Co_Var->rptr))[r][c];
				}
				tmp = tmp + ((c-meany) *(c-meany) * temp);
				temp =0;
			}
			sigmay = tmp;
			sigmay = (float)sqrt(sigmay);
			tmp = 0;
			//finding correlation
			for(r=r1; r<256; r++)
			{
				for(c=c1; c<256; c++)
				{
					tmp = tmp + ((r-meanx)*(c-meany)*((float**)(Co_Var->rptr))[r][c]);
				}
			}
			if(sigmax!=0 && sigmay!=0)
				tmp = (float)(tmp / (sigmax*sigmay));
			else
				tmp = 0;
			tf->correlation[i] = tmp;
			tmp = 0; temp=0;
		}
		//else{ tf->correlation = "NaN"; }
	}
	if(energy==1)
	{
		max = tf->energy[0];
		min = tf->energy[0];
		for (i = 0; i < 4; i++)
		{	
			if (tf->energy[i] <= min)
			min = tf->energy[i];
			if (tf->energy[i] > max)
			max = tf->energy[i];
		}
		tf->energy[4] = (tf->energy[0] + tf->energy[1] + tf->energy[2] + tf->energy[3]) / 4;
		tf->energy[5] = max - min;
	}
	if(inertia==1)
	{
		max = tf->inertia[0];
		min = tf->inertia[0];
		for (i = 0; i < 4; i++)
		{	
			if (tf->inertia[i] <= min)
			min = tf->inertia[i];
			if (tf->inertia[i] > max)
			max = tf->inertia[i];
		}
		tf->inertia[4] = (tf->inertia[0] + tf->inertia[1] + tf->inertia[2] + tf->inertia[3]) / 4;
		tf->inertia[5] = max - min;
	}
	if(invDiff==1)
	{
		max = tf->IDM[0];
		min = tf->IDM[0];
		for (i = 0; i < 4; i++)
		{	
			if (tf->IDM[i] <= min)
			min = tf->IDM[i];
			if (tf->IDM[i] > max)
			max = tf->IDM[i];
		}
		tf->IDM[4] = (tf->IDM[0] + tf->IDM[1] + tf->IDM[2] + tf->IDM[3]) / 4;
		tf->IDM[5] = max - min;
	}
	if(entropy==1)
	{
		max = tf->entropy[0];
		min = tf->entropy[0];
		for (i = 0; i < 4; i++)
		{	
			if (tf->entropy[i] <= min)
			min = tf->entropy[i];
			if (tf->entropy[i] > max)
			max = tf->entropy[i];
		}
		tf->entropy[4] = (tf->entropy[0] + tf->entropy[1] + tf->entropy[2] + tf->entropy[3]) / 4;
		tf->entropy[5] = max - min;
	}
	if(correlation==1)
	{
		float max, min;
		max = tf->correlation[0];
		min = tf->correlation[0];
		for (i = 0; i < 4; i++)
		{	
			if (tf->correlation[i] <= min)
			min = tf->correlation[i];
			if (tf->correlation[i] > max)
			max = tf->correlation[i];
		}
		tf->correlation[4] = (tf->correlation[0] + tf->correlation[1] + tf->correlation[2] + tf->correlation[3]) / 4;
		tf->correlation[5] = max - min;
	}
	return tf;
}

