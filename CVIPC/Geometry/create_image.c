/***********************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
* Credit: Jianxin Tan
* $Log: create_image.c,v $
* Revision 1.11  1997/03/08 01:01:32  yawei
* Name Changes:
* 	BOOLEAN ==> CVIP_BOOLEAN
* 	FALSE ==> CVIP_NO
* 	TRUE ==> CVIP_YES
* 	BYTE ==> CVIP_BYTE
* 	SHORT ==> CVIP_SHORT
* 	INTEGER ==> CVIP_INTEGER
* 	FLOAT ==> CVIP_FLOAT
* 	DOUBLE ==> CVIP_DOUBLE
* 	TYPE ==> CVIP_TYPE
*
* Revision 1.10  1996/12/16 23:09:04  yawei
* Change function name:
* cosine_wave_sep          ==> create_cosine
*
 * Revision 1.9  1996/12/16  20:54:20  yawei
 * Changed function names:
 *   create_Image_circle ==> create_circle
 *   create_Image_rectangular == > create_rectangle
 *   create_Image_checkboard  == > create_checkboard
 *   create_Image_line        == > create_line
 *
 * Revision 1.8  1996/11/07  22:30:48  yawei
 * changed paint_rectangular so the size of the created square with be
 * widthxheight, instead of (width+1)x(height+1).
 *
 * Revision 1.7  1995/12/06  03:45:27  kluo
 * check it in
 *
 * Revision 1.6  1995/05/14  19:29:50  luok
 * change prompt of x offset
 *
 * Revision 1.5  1995/05/08  18:20:38  luok
 * change the definition of create_circle.
 *
 * Revision 1.4  1995/05/03  05:27:21  luok
 * change the declaration for checkboard setup
 *
 * Revision 1.3  1995/04/28  22:10:34  tanj
 * create_circle_setup is fixed
 * draw_line is improved to provide more flexibility
 * create_checkboard and create_checkboard_setup is added
 * by Jianxin Tan 4/28/95.
 *
 * Revision 1.2  1995/04/22  19:32:11  luok
 * check file into RCS.
 *
***********************************************************************/
#include "CVIPtoolkit.h"
#include "CVIPdrawimg.h"

Image *create_black(int width, int height) {
	Image *outputImage;
	byte **output;
    	outputImage = new_Image(PGM,GRAY_SCALE,1,height,width,CVIP_BYTE,REAL);
	output = getData_Image(outputImage, 0);
	return outputImage;
}

Image *create_rectangle(int width, int height,int tlx,int tly,int sqwidth, int sqheight) {
	Image* outputImage;
	outputImage = create_black(width, height);
	paint_rectangular(outputImage,tlx,tly,sqwidth,sqheight);
	return outputImage;
}

void draw_rectangular(Image* inputImage,int tlx,int tly,int sqwidth,int sqheight) {
	byte **output;
	int no_bands,x,y,xlimit,ylimit,i,rows,cols;
	rows = getNoOfRows_Image(inputImage);
	cols = getNoOfCols_Image(inputImage);	
	no_bands = getNoOfBands_Image(inputImage);
	for (i=0;i<no_bands;i++) {
		output = getData_Image(inputImage, i);
		xlimit = tlx + sqwidth;
		if(xlimit>cols-1)
			xlimit = cols-1;
		ylimit = tly + sqheight;
		if(ylimit>rows-1)
			ylimit = rows-1;
		for(x=tlx;x<=xlimit;x++) {
			output[tly][x] = 255;
			output[ylimit][x] = 255;		
		}
		for(y=tly+1;y<ylimit;y++) {
			output[y][tlx] = 255;
			output[y][xlimit] = 255;		
		}
	}
}

void paint_rectangular(Image* inputImage,int tlx,int tly,int sqwidth,int sqheight) {
	byte **output;
	int no_bands,x,y,xlimit,ylimit,i,rows,cols;
	rows = getNoOfRows_Image(inputImage);
	cols = getNoOfCols_Image(inputImage);	
	no_bands = getNoOfBands_Image(inputImage);
	for (i=0;i<no_bands;i++) {
		output = getData_Image(inputImage, i);
		xlimit = tlx + sqwidth - 1;
		if(xlimit>cols-1)
			xlimit = cols-1;
		ylimit = tly + sqheight - 1;
		if(ylimit>rows-1)
			ylimit = rows-1;
		for(y=tly;y<=ylimit;y++) 
			for(x=tlx;x<=xlimit;x++)
				output[y][x] = 255;
	}
}


/*	[Description]
	Draws an ellipse using the ellipse equation :
	((x-cx)/a)^2 + ((y-cy)/b)^2 = 1
	cx,cy	= Co-ordinate of center.
	a	= (Horizontal length)/2
	b	= (Vertical length)/2
	[Notes]
	This function does not check if the image passed is valid or not.
*/
void	paint_ellipse(	Image	*InputImage,
			int	centerrow,
			int	centercol,
			int	hor_length,
			int	ver_length)
{
	byte	**BandData;
	int	RowCount,ColCount,BandCount;
	double	d_RowParts,d_ColParts;

/*	Convert horizontal length (hor_length) and vertical length 
	(ver_length) to a and b respectively.
*/
	hor_length /= 2;
	ver_length /= 2;
/*	Make sure a and b are not zero to prevent "Division by zero" error.
*/
	if(hor_length == 0) hor_length = 1;
	if(ver_length == 0) ver_length = 1;
	for(BandCount = 0;BandCount < getNoOfBands_Image(InputImage);BandCount++)
	{
		BandData = getData_Image(InputImage,BandCount);
		for(RowCount = 0;RowCount < getNoOfRows_Image(InputImage);RowCount++)
		{
			d_RowParts = (double)(RowCount-centerrow)/ver_length;
			d_RowParts *= d_RowParts;
			for(ColCount = 0;ColCount < getNoOfCols_Image(InputImage);ColCount++)
			{
				d_ColParts = (double)(ColCount-centercol)/hor_length;
				d_ColParts *= d_ColParts;
				if(d_ColParts+d_RowParts <= 1)
				BandData[RowCount][ColCount] = 255;
			}
		}
	}
}

Image	*create_ellipse(	int	width,
				int	height,
				int	centerrow,
				int	centercol,
				int	hor_length,
				int	ver_length)
{
	Image	*outputImage;

	outputImage = create_black(width,height);
	if(outputImage != NULL)
	paint_ellipse(outputImage,centerrow,centercol,hor_length,ver_length);
	return outputImage;
}

Image *create_circle(int width, int height,int centerx,int centery,int radius) {
	Image *outputImage;
	outputImage = create_black(width, height);
	paint_circle(outputImage,centerx,centery,radius);
	return outputImage;
}

Image *create_degenerate_circle(int width, int height,int centerx,int centery,int radius1, int radius2) {
	Image *outputImage;
	outputImage = create_black(width, height);
	paint_degenerate_circle(outputImage,centerx,centery,radius1, radius2);
	return outputImage;
}

void draw_circle(Image* inputImage,int centerx,int centery,int radius) {
	byte **output;
	int i,x,y,small_1,big,string,rsquare,rows,cols,no_bands;
	rows = getNoOfRows_Image(inputImage);
	cols = getNoOfCols_Image(inputImage);	
	no_bands = getNoOfBands_Image(inputImage);
	for(i=0;i<no_bands;i++) {
		output = getData_Image(inputImage, i);
		rsquare = pow(radius,2);
		small_1 = centerx - radius*3/4;
		if(small_1<0)
			small_1 = 0;
		big = centerx + radius*3/4;
		if(big>cols-1)
			big = cols-1;		
		for(x=small_1;x<=big;x++) {
			string = (int)sqrt(rsquare-pow(x-centerx,2));
			if(centery+string<=rows-1)
				output[centery+string][x] = 255;
			if(centery-string>=0)
				output[centery-string][x] = 255;
		}
		small_1 = centery - radius*3/4;
		if(small_1<0)
			small_1 = 0;
		big = centery + radius*3/4;
		if(big>rows-1)
			big = rows-1;
		for(y=small_1;y<=big;y++) {
			string = (int)sqrt(rsquare-pow(y-centery,2));
			if(centerx+string<=cols-1)
				output[y][centerx+string] = 255;
			if(centerx-string>=0)
				output[y][centerx-string] = 255;		
		}
	}
}
/*
void draw_circle(Image* inputImage,int centerx,int centery,int radius){
    byte ** output;
    int y, x, rows, cols, no_of_bands,bands;
    double result;

    rows = getNoOfRows_Image(inputImage);
    cols = getNoOfCols_Image(inputImage);
    bands = getNoOfBands_Image(inputImage);
    for(no_of_bands = 0; no_of_bands < bands; no_of_bands++){
	output = getData_Image(inputImage,no_of_bands);
	for(y=0;y<rows;y++){
	    for(x=0;x<cols;x++){
		result = (float)(centerx - x) * (centerx -x) + 
			 (float)(centery - y) * (centery -y);
		result = sqrt(result);
		if((int)result == radius)
		      output[y][x] = 255;
	    }
	}
    }
}
	
void paint_circle(Image* inputImage,int centerx,int centery,int radius) {
    byte ** output;
    int y, x, rows, cols, no_of_bands,bands;
    double result;
fprintf(stderr,"%d",radius);

    rows = getNoOfRows_Image(inputImage);
    cols = getNoOfCols_Image(inputImage);
    bands = getNoOfBands_Image(inputImage);
    for(no_of_bands = 0; no_of_bands < bands; no_of_bands++){
	output = getData_Image(inputImage,no_of_bands);
	for(y=0;y<rows;y++){
	    for(x=0;x<cols;x++){
		result = (float)(centerx - x) * (centerx -x) + 
			 (float)(centery - y) * (centery -y);
		result = sqrt(result);
		if(result <= radius)
		      output[y][x] = 255;
	    }
	}
    }
}



*/

void paint_circle(Image* inputImage,int centerx,int centery,int radius) {
	byte **output;
	int i,x,y,xsmall,xbig,ysmall,ybig,string,rsquare,rows,cols,no_bands;
	rows = getNoOfRows_Image(inputImage);
	cols = getNoOfCols_Image(inputImage);	
	no_bands = getNoOfBands_Image(inputImage);

	rsquare = pow(radius,2);
	xsmall = centerx - radius;
	if(xsmall<0)
		xsmall = 0;
	xbig = centerx + radius;
	if(xbig>cols-1)
		xbig = cols-1;
	ysmall = centery - radius;
	if(ysmall<0)
		ysmall = 0;
	ybig = centery + radius;
	if(ybig>rows-1)
		ybig = rows-1;

	for(i=0;i<no_bands;i++) {
		output = getData_Image(inputImage, i);		
		for(x=xsmall;x<=xbig;x++) {
			for(y=ysmall;y<=ybig;y++) {
				if(pow(x-centerx,2)+pow(y-centery,2)<=rsquare)
					output[y][x]=255;
			}		
		}
	}
}

void paint_degenerate_circle(Image* inputImage,int centerx,int centery,int radius1, int radius2) {
	byte **output;
	int i,x,y,xsmall,xbig,ysmall,ybig,string,rsquare1,rows,cols,no_bands;
	int temp, rsquare2;

	rows = getNoOfRows_Image(inputImage);
	cols = getNoOfCols_Image(inputImage);	
	no_bands = getNoOfBands_Image(inputImage);

	rsquare1 = pow(radius1,2);
	if (radius2 <= radius1) radius2 = radius1+1;
	rsquare2 = pow(radius2,2);

	xsmall = centerx - radius2;
	if(xsmall<0)
		xsmall = 0;
	xbig = centerx + radius2;
	if(xbig>cols-1)
		xbig = cols-1;
	ysmall = centery - radius2;
	if(ysmall<0)
		ysmall = 0;
	ybig = centery + radius2;
	if(ybig>rows-1)
		ybig = rows-1;

	for(i=0;i<no_bands;i++) {
		output = getData_Image(inputImage, i);		
		for(x=xsmall;x<=xbig;x++) {
			for(y=ysmall;y<=ybig;y++) {
				temp = pow(x-centerx,2)+pow(y-centery,2);
				if(temp<=rsquare1)
					output[y][x]=255;
				else if (temp <= rsquare2)
					output[y][x] = (BYTE)(255.0 * (radius2 - sqrt(temp)) / (radius2 - radius1));
			}		
		}
	}
}

Image *create_line(int width, int height,int tlx,int tly,int brx, int bry){
	Image *outputImage;
	outputImage = create_black(width, height);
	draw_line(outputImage,tlx,tly,brx,bry);
	return outputImage;
}

void draw_line(Image* inputImage,int tlx,int tly,int brx, int bry) {
	byte **output;
	int i,x,y,move,rows,cols,no_bands,difx,dify;
	float namda;
	rows = getNoOfRows_Image(inputImage);
	cols = getNoOfCols_Image(inputImage);	
	no_bands = getNoOfBands_Image(inputImage);
	for(i=0;i<no_bands;i++) {
		output = getData_Image(inputImage, 0);
		difx = brx-tlx;
		dify = bry-tly;
		if(difx==0){
			if(bry>=tly) {
				if(tly<0)
					tly = 0;
				if(bry>=rows)
					bry = rows-1; 
				for(y=tly;y<=bry;y++)
					output[y][tlx] = 255;
			}
			else {
				if(bry<0)
					bry = 0;
				if(tly>=rows)
					tly = rows-1;
				for(y=bry;y<=tly;y++)
					output[y][tlx] = 255;
			}
		}
		else if(dify == 0) {
			if(brx>=tlx) {
				if(tlx<0)
					tlx = 0;
				if(brx>=cols)
					brx = cols-1;
				for(x=tlx;x<=brx;x++)
					output[tly][x] = 255;
			}
			else {
				if(brx<0)
					brx = 0;
				if(tlx>=cols)
					tlx = cols-1;
				for(x=brx;x<=tlx;x++)
					output[tly][x] = 255;
			}
		}

		else if(dify>difx){
			namda = (float)difx/(float)dify;
			if(bry>=tly) {
				for(y=tly;y<bry;y++) {
				if(y>=0 && y<rows) {
					move = (int)(namda*(y-tly))+tlx;
					if(move>=0 && move<cols)
						output[y][move] = 255;
					}
				}
			}
			else {
			for(y=bry;y<tly;y++) {
				if(y>=0 && y<rows) {
					move = (int)(namda*(y-tly))+tlx;
					if(move>=0 && move<cols)
						output[y][move] = 255;
					}
				}
			}

		}
		else {
			namda = (float)dify/(float)difx;
			if(brx>=tlx) {
			for(x=tlx;x<brx;x++) {
				if(x>=0 && x<cols) {
					move = (int)(namda*(x-tlx))+tly;
					if(move>=0 && move<rows)
						output[move][x] = 255;
					}
				}
			}
			else {
			for(x=brx;x<tlx;x++) {
				if(x>=0 && x<cols) {
					move = (int)(namda*(x-tlx))+tly;
					if(move>=0 && move<rows)
						output[move][x] = 255;
					}
				}
			}
		}
	}
}

Image	*create_ellipse_setup(void)
{
	Image	*outputImage;
	int	width,height,centerx,centery,hor_length,ver_length;

	print_CVIP("\n\tWidth of the image  : ");
	width = getInt_CVIP(10,1,1024);
	print_CVIP("\n\tHeight of the image : ");
	height = getInt_CVIP(10,1,1024);
	print_CVIP("\n\tCenter X            : ");
	centerx = getInt_CVIP(10,-1024,1024);
	print_CVIP("\n\tCenter Y            : ");
	centery = getInt_CVIP(10,-1024,1024);
	print_CVIP("\n\tHorizontal length   : ");
	hor_length = getInt_CVIP(10,1,1024);
	print_CVIP("\n\tVertical length   : ");
	ver_length = getInt_CVIP(10,1,1024);
	outputImage = create_ellipse(width,height,centerx,centery,hor_length,ver_length);
	if(outputImage == NULL)
	error_CVIP("create_ellipse_setup()","Unable to create image\n");
	return outputImage;
}

Image* create_circle_setup(void){
	Image* outputImage;
	char* outputfile;
	int width,height,centerx,centery,radius,rsquare,max,min,distance;
	print_CVIP("\n\tWidth of the image:  ");
	width = getInt_CVIP(10, 1, 1024);
	print_CVIP("\n\tHeight of the image:  ");
	height = getInt_CVIP(10, 1, 1024);
	print_CVIP("\n\tX of the circle's center:  ");
	centerx = getInt_CVIP(10, -1024, 1024);
	print_CVIP("\n\tY of the circle's center:  ");
	centery = getInt_CVIP(10, -1024, 1024);
	print_CVIP("\n\tRadius of the circle:  ");
	radius = getInt_CVIP(10, 1, 2048);
	rsquare = pow(radius,2);
	distance = pow(centerx-0,2) + pow(centery-0,2);
	min = distance; 
	max = distance;
	distance = pow(centerx-0,2) + pow(centery-height,2);
	if(distance < min)
		min = distance; 
	if(distance > max)
		max = distance;
	distance = pow(centerx-width,2) + pow(centery-0,2);
	if(distance < min)
		min = distance; 
	if(distance > max)
		max = distance;
	distance = pow(centerx-0,2) + pow(centery-height,2);
	if(distance < min)
		min = distance; 
	if(distance > max)
		max = distance;
	/*if the center is out of the image frame*/
	if(centerx<0 || centerx > width || centery<0 || centery > height) {  
		if(rsquare > max) { 
		printf("\n\tError:(create_circle_setup)radius too large.\n");
		printf("\tThe image will be all white.\n");
		return 0;
		}
		else if(rsquare < min) { 
		printf("\n\tError:(create_circle_setup)radius too small.\n");
		printf("\tThe circle will be out of the image frame.\n");
		return 0;
		}
		else {
		outputImage = 
		create_circle(width,height,centerx,centery,radius); 
		return outputImage;
		}
	}
	/*if the center is inside the image frame*/
	else if(rsquare > max){   
		printf("\n\tError:(create_circle_setup)radius too large.\n");
		printf("\tThe image will be all white.\n");
		return (Image*)NULL;
	}
	else {
		outputImage = 
		create_circle(width,height,centerx,centery,radius); 
		return outputImage;
	}
}

Image* create_rectangular_setup(void) {
	Image* outputImage;
	char* outputfile;
	int width,height,tlx,tly,rectwidth,rectheight;
	print_CVIP("\n\tWidth of the image:  ");
	width = getInt_CVIP(10, 1, 1024);
	print_CVIP("\n\tHeight of the image:  ");
	height = getInt_CVIP(10, 1, 1024);
	print_CVIP("\n\tX of the rectangular's top-left corner:  ");
	tlx = getInt_CVIP(10, 0, width-1);
	print_CVIP("\n\tY of the rectangular's top-left corner:  ");
	tly = getInt_CVIP(10, 0, height-1);
	print_CVIP("\n\tWidth of the rectangular:  ");
	rectwidth = getInt_CVIP(10, 1, width-1-tlx);
	print_CVIP("\n\tHeight of the rectangular:  ");
	rectheight= getInt_CVIP(10, 1, height-1-tly);  
	outputImage =
 	create_rectangle(width,height,tlx,tly,rectwidth,rectheight); 
	return outputImage;
}

Image* create_line_setup(void) {
	Image* outputImage;
	char* outputfile;
	int width,height,startx,starty,endx,endy;
	print_CVIP("\n\tWidth of the image:  ");
	width = getInt_CVIP(10, 1, 1024);
	print_CVIP("\n\tHeight of the image:  ");
	height = getInt_CVIP(10, 1, 1024);
	print_CVIP("\n\tX of the line's starting point:  ");
	startx = getInt_CVIP(10, -1024, 1024);
	print_CVIP("\n\tY of the line's starting point:  ");
	starty = getInt_CVIP(10, -1024, 1024);
	print_CVIP("\n\tX of the line's ending point:  ");
	endx = getInt_CVIP(10, -1024, 1024);
	print_CVIP("\n\tY of the line's ending point:  ");
	endy = getInt_CVIP(10, -1024, 1024);
	if(startx<0&&endx<0||startx>width&&endx>width
	||starty<0&&endy<0||starty>height&&endy>height) {
		printf
	("\n\tError:(create_line_setup)The line will not be in the image.\n");
		return 0;
	}
	outputImage = create_line(width,height,startx,starty,endx,endy); 
	return outputImage;
}

Image *create_checkboard(int width, int height,int firstx,int firsty,int blockx,int blocky) {
	Image* outputImage;
	byte **output;
	int no_bands,x,y,xlimit,ylimit,i,j,dx,dy;
	outputImage = create_black(width, height);
	output = getData_Image(outputImage, 0);
	dx = blockx << 1;
	dy = blocky << 1;
	for(i=0;i<firsty;i++)
		for(j=0;j<firstx;j++)
			output[i][j] = 255;
	for(y=0;y<firsty;y++)
		for(x=firstx+blockx;x<width;x+=dx) 
			for(j=0;j<blockx;j++) 
				if(y+i<height && x+j<width)
					output[y][x+j] = 255;	

	for(y=firsty+blocky;y<height;y+=dy)
		for(x=0;x<firstx;x++) 
			for(i=0;i<blocky;i++)
				if(y+i<height && x+j<width)
					output[y+i][x] = 255;	
	
	for(y=firsty;y<height;y+=dy)
		for(x=firstx;x<width;x+=dx) 
			for(i=0;i<blocky;i++)
				for(j=0;j<blockx;j++)
					if(y+i<height && x+j<width)
						output[y+i][x+j] = 255;	
						
	
	for(y=firsty+blocky;y<height;y+=dy)
		for(x=firstx+blockx;x<width;x+=dx) 
			for(i=0;i<blocky;i++)
				for(j=0;j<blockx;j++) 
					if(y+i<height && x+j<width)
						output[y+i][x+j] = 255;	

	return outputImage;
}

Image* create_checkboard_setup(void) {
	Image* outputImage;
	char* outputfile;
	int width,height,firstx,firsty,blockx,blocky;
	print_CVIP("\n\tWidth of the image:  ");
	width = getInt_CVIP(10, 1, 1024);
	print_CVIP("\n\tHeight of the image:  ");
	height = getInt_CVIP(10, 1, 1024);
	print_CVIP("\n\tX offset:  ");
	firstx = getInt_CVIP(10, 0, width-1);
	print_CVIP("\n\tY offset:  ");
	firsty = getInt_CVIP(10, 0, height-1);
	print_CVIP("\n\tWidth of each cell:  ");
	blockx = getInt_CVIP(10, firstx, width);
	print_CVIP("\n\tHeight of each cell:  ");
	blocky = getInt_CVIP(10, firsty, height);  
	outputImage =
 	create_checkboard(width,height,firstx,firsty,blockx,blocky); 
	return outputImage;
}
