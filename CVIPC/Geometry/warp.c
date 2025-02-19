
/***************************************************************************
* =========================================================================
*
*   Computer Vision and Image Processing Lab - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: CVIPlab.c 
*   Initial Coding Date: 03/23/95
*          Last edition: 05/13/95    
*           Portability: Standard (ANSI) C
*             Credit(s): Jianxin Tan
*                        Southern Illinois University @ Edwardsville
* $Log: warp.c,v $
* Revision 1.14  1997/05/19 21:43:16  yawei
* replaced rint by ROUND
*
* Revision 1.13  1997/04/14 19:15:06  yawei
* turned off error output
*
* Revision 1.12  1997/04/09 22:49:55  yawei
* added boundary check so nor bombing
*
* Revision 1.11  1997/03/08 17:07:06  yawei
* Swaped CVIP_YES and CVIP_NO
*
* Revision 1.10  1997/03/08 01:01:18  yawei
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
* Revision 1.9  1997/01/16 21:31:48  yawei
* Global Change:  Image_FORMAT ==> IMAGE_FORMAT
*
 * Revision 1.8  1997/01/15  17:19:28  yawei
 * Global Change:  IMAGE ==> Image
 *
 * Revision 1.7  1996/12/20  19:22:42  yawei
 * Use "view_Image" to display images.
 *
 * Revision 1.6  1996/12/16  23:09:18  yawei
 * 1) removed function black_pgm1
 * 2) changed function name black_pgm1 ==> create_black
 *
 * Revision 1.5  1996/09/07  00:16:34  yawei
 * changed viewer so image will be written to the temp dir
 * with correct format.
 *
 * Revision 1.4  1996/09/04  22:22:57  yawei
 * added choice to viewer
 *
 * Revision 1.3  1996/03/27  01:58:09  kluo
 * change the type of image viewer
 *
 * Revision 1.2  1996/02/02  21:00:47  akjoele
 * Changed line 1000 so that function get_line, which expects to return
 * a value, returns one instead of just 'return'.
 *
 * Revision 1.1  1995/05/15  20:54:18  luok
 * Initial revision
 *
****************************************************************************/

#include <math.h>
#include "CVIPtoolkit.h"
#include "CVIPdef.h"
#include "CVIPimage.h"
#include "CVIPhisto.h"
#include "CVIPfs.h"
#include "CVIPmesh.h"
#include "CVIPdrawimg.h"
#include "CVIPview.h"

static void cell_map_nearest_ri(byte **in,byte **out,
	struct mesh_node *outtie,float *c, int rows, int cols,
	CVIP_BOOLEAN zero_out); 
static void cell_map_bilinear_ri(byte **in,byte **out,struct mesh_node *outtie,
	float *c, int rows, int cols, CVIP_BOOLEAN zero_out); 
static void cell_map_average_2d_ri(byte **in,byte **out,
	struct mesh_node *outtie,float *c, int rows, int cols,
	CVIP_BOOLEAN zero_out); 

static void cell_map_average_2d(byte **in,byte **out,
	struct mesh_node *outtie,float *c, int rows, int cols); 
static void cell_map_bilinear(byte **in,byte **out,
	struct mesh_node *outtie,float *c, int rows, int cols);
static void cell_map_nearest(byte **in,byte **out,
	struct mesh_node *outtie,float *c); 

static int solve_equation4(struct mesh_node *left,int *right,float *solution);
static double get_delta(float a0[4],float a1[4],float a2[4],float a3[4]); 

static int interpolation_bilinear(float x,float y,byte **in,
	int rows, int cols);
static int interpolation_average_2d(float x,float y,byte **in,
	int rows, int cols);
static int interpolation_linear_1d(float x,float y,int rotation,byte **in,
	int rows, int cols);
static void grid(float x,int *gridpair);
static int in_cell(int x,int y,struct float_pair *lines,int* situation); 
static int get_lines(struct mesh_node *intie,struct float_pair *lines,
	int* situation); 
static void draw_line1(Image* inputImage,int tlx,int tly,int brx, int bry); 

void keyboard_mesh(void){
	char	*inputfile;
	char    image_name[100];
	struct mesh *inmesh;
	Image	*cvipImage;
	inmesh = keyboard_to_mesh();
	print_CVIP("\n\tInput the mesh file name: ");
	inputfile = getString_CVIP();	
	if((mesh_to_file(inmesh,inputfile)) == 0)
		return;
	cvipImage = create_black(512,512);
	display_mesh(cvipImage,inmesh,inputfile);
}


int solve_c(struct mesh_node intie[4],struct mesh_node outtie[4],float *c) { 
	int i,rightx[4],righty[4];
	float tempc[4];
	for(i=0;i<4;i++) {
		rightx[i] = outtie[i].x;
		righty[i] = outtie[i].y;
	}

	if(solve_equation4(intie,rightx,tempc)!=1) {
		/*printf("\nError:(solve_c)delta == 0.\n"); */
		return 0;
	}
	for(i=0;i<4;i++)
		c[i] = tempc[i];
	if(solve_equation4(intie,righty,tempc)!=1) {
		/*printf("\nError:(solve_c)delta == 0.\n");*/
		return 0;
	}
	for(i=0;i<4;i++)
		c[i+4] = tempc[i];
	return 1;
}

void cell_paint(byte **out,struct mesh_node *intie) {
	struct mesh_node win[2];
	struct float_pair lines[4];
	int x,y,situation[4];

	win[0].x = (intie[0].x < intie[2].x) ? 	intie[0].x : intie[2].x;
	win[1].x = (intie[1].x > intie[3].x) ? 	intie[1].x : intie[3].x;
	win[0].y = (intie[0].y < intie[1].y) ? 	intie[0].y : intie[1].y;
	win[1].y = (intie[2].y > intie[3].y) ? 	intie[2].y : intie[3].y;

	get_lines(intie,lines,situation);
/*tiepoints[4] not in order*/
	for(y=win[0].y;y<win[1].y;y++) {
		for(x=win[0].x;x<win[1].x;x++) {
			if(in_cell(x,y,lines,situation)){
				out[y][x] = 255;
			}
		}
	}
}


/*read a mesh from a file*/
struct mesh *file_to_mesh(char* mesh_file) {
	struct mesh *outmesh;
	int cols,rows,x,y;
	FILE *fp;
   	if((fp=fopen(mesh_file,"rb"))==NULL){
		perror("Couldn't open file to read: \n");
		return NULL; 
	}
    	if(fread(&cols,sizeof(int),1,fp)!=1){
		perror("Couldn't read cols: \n");
		return NULL;
    	}
    	if(fread(&rows,sizeof(int),1,fp)!=1){
		perror("Couldn't read rows: \n");
		return NULL;
    	}

	outmesh = (struct mesh*)malloc(sizeof(struct mesh));
	outmesh->nodes 
	= (struct mesh_node**)malloc(sizeof(struct mesh_node*)*cols);
	outmesh->width = cols;
	outmesh->height = rows;
	for(x=0;x<cols;x++)
		outmesh->nodes[x]
		= (struct mesh_node*)calloc(rows,sizeof(struct mesh_node));
    	
	for(y=0; y<rows; y++) {
		for(x=0; x<cols; x++) {
			if(fread(&(outmesh->nodes[x][y].x),
			sizeof(int),1,fp)!=1){
				perror("Couldn't read a node: \n");
				return NULL;
    			}
			if(fread(&(outmesh->nodes[x][y].y),
			sizeof(int),1,fp)!=1){
				perror("Couldn't read a node: \n");
				return NULL;
    			}
		}
	}
	fclose(fp);
	return outmesh;
}

struct mesh *keyboard_to_mesh(void) {
	struct mesh *outmesh;
	int cols,rows,x,y;
	printf("\n\tColumns of the mesh matrix please: ");
	cols = getInt_CVIP(10, 1, 512);
	printf("\tRows of the mesh matrix please: ");
	rows = getInt_CVIP(10, 1, 512);
	outmesh = (struct mesh*)malloc(sizeof(struct mesh));
	outmesh->nodes 
	= (struct mesh_node**)malloc(sizeof(struct mesh_node*)*cols);
	outmesh->width = cols;
	outmesh->height = rows;
	for(x=0;x<cols;x++)
		outmesh->nodes[x]
		= (struct mesh_node*)calloc(rows,sizeof(struct mesh_node));
	for(y=0; y<rows; y++) {
		for(x=0; x<cols; x++) {
			printf("\n\tX of the mesh point(%d,%d) please: ",x,y);
			outmesh->nodes[x][y].x = getInt_CVIP(10,0,511);
			printf("\n\tY of the mesh point(%d,%d) please: ",x,y);
			outmesh->nodes[x][y].y = getInt_CVIP(10,0,511);
		}
	}
	return outmesh;
}

int mesh_to_file(struct mesh *inmesh, char* mesh_file) {
	int x,y;
	FILE *fp;
   	if((fp=fopen(mesh_file,"wb"))==NULL){
		perror("Couldn't open file to write: \n");
		return 0; 
	}
    	if(fwrite(&(inmesh->width),sizeof(int),1,fp)!=1){
		perror("Couldn't write cols: \n");
		return 0;
    	}
    	if(fwrite(&(inmesh->height),sizeof(int),1,fp)!=1){
		perror("Couldn't write rows: \n");
		return 0;
    	}

	for(y=0; y<inmesh->height; y++) {
		for(x=0; x<inmesh->width; x++) {
			if(fwrite(&(inmesh->nodes[x][y].x),
			sizeof(int),1,fp)!=1){
				perror("Couldn't write a node: \n");
				return 0;
    			}
			if(fwrite(&(inmesh->nodes[x][y].y),
			sizeof(int),1,fp)!=1){
				perror("Couldn't write a node: \n");
				return 0;
    			}
		}
	}
	fclose(fp);
  	return 1;
}


struct mesh *regular_mesh(struct mesh* inmesh,int cols,int rows) {
	struct mesh *outmesh;
	int x,y;
	float rx,ry;

	outmesh = (struct mesh*)malloc(sizeof(struct mesh));
	outmesh->nodes 
	= (struct mesh_node**)malloc(sizeof(struct mesh_node*)*inmesh->width);
	outmesh->width = inmesh->width;
	outmesh->height = inmesh->height;
	for(x=0;x<inmesh->width;x++)
		outmesh->nodes[x]
		= (struct mesh_node*)calloc(inmesh->height,
		sizeof(struct mesh_node));
	rx = (float)(cols-1)/(inmesh->width-1);
	ry = (float)(rows-1)/(inmesh->height-1);
	for(y=0;y<inmesh->height;y++) { 
		for(x=0;x<inmesh->width;x++) {
			outmesh->nodes[x][y].y = (int)(ry*y);
			outmesh->nodes[x][y].x = (int)(rx*x); 
		}
	}
	return outmesh;
}

void create_mesh_sine(void) {
	Image* outputImage;
	struct mesh *outmesh;
	char* mesh_file,*outputfile;
	IMAGE_FORMAT 	format1;
	int cols,rows,x,y,oldx,newx,oldy,newy,width,height;
	width = 511;
	height = 511;
	printf("\n\tColumns of the mesh matrix please: ");
	cols = getInt_CVIP(10, 1, 512);
	printf("\tRows of the mesh matrix please: ");
	rows = getInt_CVIP(10, 1, 512);
	outmesh = (struct mesh*)malloc(sizeof(struct mesh));
	outmesh->nodes 
	= (struct mesh_node**)malloc(sizeof(struct mesh_node*)*cols);
	outmesh->width = cols;
	outmesh->height = rows;
	for(x=0;x<cols;x++)
		outmesh->nodes[x]
		= (struct mesh_node*)calloc(rows,sizeof(struct mesh_node));
	oldy = 0;
	for(y=0; y<rows; y++) {
		oldx = 0;
		newy = oldy + abs((int)(25*cos(y)+0.5));
		if(newy>=height)
			newy = height;
		for(x=0; x<cols; x++) {
			newx = oldx + abs((int)(25*sin(x)+0.5));
			if(newx >= width)
				newx = width;
			outmesh->nodes[x][y].x = newx;
			oldx = newx;
			outmesh->nodes[x][y].y = newy;
		}
		oldy = newy;
	}
printf("\n\tsine mesh file height=%d, width=%d\n",outmesh->height,outmesh->width);
 	print_CVIP("\n\t\tEnter the file name to save the mesh:  "); 	
        mesh_file = getString_CVIP();
	outputImage = create_black(512, 512);
	display_mesh(outputImage,outmesh,mesh_file);
	mesh_to_file(outmesh,mesh_file);
}

void  display_mesh(Image* inputImage,struct mesh *inmesh, char *file_name) {
	byte **output;
	int i,x,y,move,rows,cols,no_bands;
	int height,width,m,n,tlx,tly,brx,bry;
	float namda;

	height = getNoOfRows_Image(inputImage);
	width = getNoOfCols_Image(inputImage);	
	no_bands = getNoOfBands_Image(inputImage);
	for(i=0;i<no_bands;i++) {
		output = getData_Image(inputImage, i);
		for(m=0; m<inmesh->width; m++) {
			for(n=0; n<inmesh->height-1; n++) {
				tlx = inmesh->nodes[m][n].x;
				tly = inmesh->nodes[m][n].y;
				brx = inmesh->nodes[m][n+1].x;
				bry = inmesh->nodes[m][n+1].y;
				draw_line1(inputImage,tlx,tly,brx,bry);
			}
		}
		for(n=0; n<inmesh->height; n++) {
	 		for(m=0; m<inmesh->width-1; m++){
				tlx = inmesh->nodes[m][n].x;
				tly = inmesh->nodes[m][n].y;
				brx = inmesh->nodes[m+1][n].x;
				bry = inmesh->nodes[m+1][n].y;
				draw_line1(inputImage,tlx,tly,brx,bry);	
			}
		}
	}
//   view_Image(inputImage,file_name);
}

Image *mesh_warping(Image *inputImage,struct mesh *inmesh,int method){
	Image *outputImage,*showImage;
	byte **in,**out;
	int i,j,x,y,rows, cols,bands,no_bands;
	struct mesh *outmesh;
	struct mesh_node intie[4],outtie[4];
	float c[8];

	outputImage = duplicate_Image(inputImage);
	rows = getNoOfRows_Image(inputImage);
	cols = getNoOfCols_Image(inputImage);
	no_bands = getNoOfBands_Image(inputImage);	
	
	outmesh = regular_mesh(inmesh,cols,rows);
	for(bands=0;bands<no_bands;bands++) {
  		in = getData_Image(inputImage, bands);
  		out = getData_Image(outputImage, bands);
		for(y=0;y<inmesh->height-1;y++) {
			for(x=0;x<inmesh->width-1;x++) {
				intie[0]=inmesh->nodes[x][y];
				intie[1]=inmesh->nodes[x][y+1];
				intie[2]=inmesh->nodes[x+1][y];
				intie[3]=inmesh->nodes[x+1][y+1];
				outtie[0]=outmesh->nodes[x][y];
				outtie[1]=outmesh->nodes[x][y+1];
				outtie[2]=outmesh->nodes[x+1][y];
				outtie[3]=outmesh->nodes[x+1][y+1];

				solve_c(outtie,intie,c);
				switch (method) {
				case 1:
					cell_map_nearest(in,out,outtie,c);
					break;
				case 2:  
					cell_map_bilinear(in,out,outtie,c,rows,cols);
					break;
				case 3:  
					cell_map_average_2d(in,out,outtie,c,rows,cols);
					break;
				default:
					printf("\nError:(mesh_warping)Must choose from the methods shown.\n");
				}
			}
		}
	}
	delete_Image(inputImage);
	return outputImage;
}

Image *mesh_warping_ri(Image *inputImage,struct mesh *outmesh,
	int method, CVIP_BOOLEAN zero_out){
	Image *outputImage,*showImage;
	byte **in,**out;
	int i,j,x,y,rows, cols,bands,no_bands;
	struct mesh *inmesh;
	struct mesh_node intie[4],outtie[4];
	float c[8];

	rows = getNoOfRows_Image(inputImage);
	cols = getNoOfCols_Image(inputImage);
	outputImage = (Image *)new_Image(
		inputImage->image_format, getColorSpace_Image(inputImage),
		getNoOfBands_Image(inputImage), rows, cols, getDataType_Image(inputImage),
		getDataFormat_Image(inputImage));;
	no_bands = getNoOfBands_Image(inputImage);	
	
	inmesh = regular_mesh(outmesh,cols,rows);
	for(bands=0;bands<no_bands;bands++) {
  		in = getData_Image(inputImage, bands);
  		out = getData_Image(outputImage, bands);
		for(y=0;y<inmesh->height-1;y++) {
			for(x=0;x<inmesh->width-1;x++) {
				intie[0]=inmesh->nodes[x][y];
				intie[1]=inmesh->nodes[x+1][y];
				intie[2]=inmesh->nodes[x][y+1];
				intie[3]=inmesh->nodes[x+1][y+1];
				outtie[0]=outmesh->nodes[x][y];
				outtie[1]=outmesh->nodes[x+1][y];
				outtie[2]=outmesh->nodes[x][y+1];
				outtie[3]=outmesh->nodes[x+1][y+1];
				solve_c(outtie,intie,c);
				switch (method) {
				case 1:
					cell_map_nearest_ri(in,out,outtie,c, rows, cols,zero_out);
					break;
				case 2:  
					cell_map_bilinear_ri(in,out,outtie,c, rows, cols,zero_out);
					break;
				case 3:  
					cell_map_average_2d_ri(in,out,outtie,c, rows, cols,zero_out); 
					break;
				default:
					printf("\nError:(mesh_warping)Must choose from the methods shown.\n");
				}
			}
		}
	}
	delete_Image(inputImage);
	return outputImage;
}


static void cell_map_nearest(byte **in,byte **out,
	struct mesh_node *outtie,float *c) {
	int x,y;
	for(y=outtie[0].y;y<outtie[3].y;y++) {
		for(x=outtie[0].x;x<outtie[3].x;x++) {
				/*get the gray value*/
				out[y][x] = 
				in[(int)(c[4]*x+c[5]*y+c[6]*x*y+c[7]+0.5)]
				[(int)(c[0]*x+c[1]*y+c[2]*x*y+c[3]+0.5)];
		}
	}
}

static int solve_equation4(struct mesh_node *left,int *right,float *solution){
	float a0[4],a1[4],a2[4],a3[4],d,b[4];
	double delta[4];
	int i;
	for(i=0;i<4;i++) {
		a0[i] = (float)left[i].x;
		a1[i] = (float)left[i].y;
		a2[i] = (float)left[i].x*left[i].y;
		a3[i] = 1.0;
		b[i] = right[i];
	}

	d = get_delta(a0,a1,a2,a3);
	if(d == 0.) {
		/*printf("\nError:(solve_equation4)delta == 0.\n"); */
		return 0;
	}
	delta[0] = get_delta(b,a1,a2,a3);
	delta[1] = get_delta(a0,b,a2,a3);
	delta[2] = get_delta(a0,a1,b,a3);
	delta[3] = get_delta(a0,a1,a2,b);

	for (i=0;i<4;i++) {
		solution[i] = delta[i]/d;
	}
	return 1;
}


static void cell_map_bilinear(byte **in,byte **out,
	struct mesh_node *outtie,float *c, int rows, int cols) {
	int x,y,intx,inty;
	float tempx,tempy,roundx,roundy;
	for(y=outtie[0].y;y<outtie[3].y;y++) {
		for(x=outtie[0].x;x<outtie[3].x;x++) {
			/*get the gray value*/
			tempx = c[0]*x+c[1]*y+c[2]*x*y+c[3];
			roundx = ROUND(tempx);
			intx = (int)roundx;
			tempy = c[4]*x+c[5]*y+c[6]*x*y+c[7];
			roundy = ROUND(tempy);
			inty = (int)roundy;
			if((tempx-roundx != 0.0)&&(tempy-roundy != 0.0))
				out[y][x]
				= interpolation_bilinear(tempx,tempy,in,rows,cols);
			else if(tempy-roundy == 0.0&&tempx-roundx != 0.0)
				out[y][x]
				= interpolation_linear_1d(tempx,tempy,0,in, rows,cols);
			else if(tempx-roundx == 0.0&&tempy-roundy != 0.0)
				out[y][x]
				= interpolation_linear_1d(tempx,tempy,1,in, rows,cols);
			else {
				out[y][x] = in[inty][intx];
			}
		}
	}
}

static void cell_map_average_2d(byte **in,byte **out,
	struct mesh_node *outtie,float *c, int rows, int cols) {
	int x,y,intx,inty;
	float tempx,tempy,roundx,roundy;
	for(y=outtie[0].y;y<outtie[3].y;y++) {
		for(x=outtie[0].x;x<outtie[3].x;x++) {
			/*get the gray value*/
			tempx = c[0]*x+c[1]*y+c[2]*x*y+c[3];
			roundx = ROUND(tempx);
			intx = (int)roundx;
			tempy = c[4]*x+c[5]*y+c[6]*x*y+c[7];
			roundy = ROUND(tempy);
			inty = (int)roundy;
			if((tempx-roundx != 0.0)&&(tempy-roundy != 0.0))
				out[y][x]
				= interpolation_average_2d(tempx,tempy,in, rows, cols);
			else if(tempy-roundy == 0.0&&tempx-roundx != 0.0)
				out[y][x]
				= interpolation_linear_1d(tempx,tempy,0,in, rows,cols);
			else if(tempx-roundx == 0.0&&tempy-roundy != 0.0)
				out[y][x]
				= interpolation_linear_1d(tempx,tempy,1,in, rows,cols);
			else {
				out[y][x] = in[inty][intx];
			}
		}
	}
}

static int interpolation_bilinear(float x,float y,byte **in,
	int rows, int cols){
	struct mesh_node neighbor[4];
	float c[4];
	int i,guess,gridpair[2],grayvalue[4];

	grid(x,gridpair);
	neighbor[0].x = gridpair[0];
	if (neighbor[0].x<0) neighbor[0].x = 0;
	if (neighbor[0].x>=cols) neighbor[0].x = cols-1;
	neighbor[2].x = neighbor[0].x;
	neighbor[1].x = gridpair[1];
	if (neighbor[1].x<0) neighbor[1].x = 0;
	if (neighbor[1].x>=cols) neighbor[1].x = cols-1;
	neighbor[3].x = neighbor[1].x;
	grid(y,gridpair);
	neighbor[0].y = gridpair[0];
	if (neighbor[0].y < 0) neighbor[0].y = 0;
	if (neighbor[0].y >= rows) neighbor[0].y = rows-1;
	neighbor[1].y = neighbor[0].y;
	neighbor[2].y = gridpair[1];
	if (neighbor[2].y < 0) neighbor[2].y = 0;
	if (neighbor[2].y >= rows) neighbor[2].y = rows-1;
	neighbor[3].y = neighbor[2].y;
	for(i=0;i<4;i++) 
		grayvalue[i] = in[neighbor[i].y][neighbor[i].x];
	if(solve_equation4(neighbor,grayvalue,c)!=1) {
		/*printf("\nError:(interpolation_bilinear)can't guess.\n");*/
		return c[0];
	} else
		guess = (int)(c[0]*x + c[1]*y + c[2]*x*y + c[3] + 0.5);
	return guess;
}

static void grid(float x,int *gridpair) {
	gridpair[0] = (int)x;
	gridpair[1] = gridpair[0]+1;
}

static int interpolation_average_2d(float x,float y,byte **in,
	int rows, int cols){
	struct mesh_node neighbor[4];
	float c[4];
	int i,guess,gridpair[2],gray;
	grid(x,gridpair);
	neighbor[0].x = gridpair[0];
	if (neighbor[0].x<0) neighbor[0].x = 0;
	if (neighbor[0].x>=cols) neighbor[0].x = cols-1;
	neighbor[2].x = neighbor[0].x;
	neighbor[1].x = gridpair[1];
	if (neighbor[1].x<0) neighbor[1].x = 0;
	if (neighbor[1].x>=cols) neighbor[1].x = cols-1;
	neighbor[3].x = neighbor[1].x;
	grid(y,gridpair);
	neighbor[0].y = gridpair[0];
	if (neighbor[0].y < 0) neighbor[0].y = 0;
	if (neighbor[0].y >= rows) neighbor[0].y = rows-1;
	neighbor[1].y = neighbor[0].y;
	neighbor[2].y = gridpair[1];
	if (neighbor[2].y < 0) neighbor[2].y = 0;
	if (neighbor[2].y >= rows) neighbor[2].y = rows-1;
	neighbor[3].y = neighbor[2].y;
	gray = 0;
	for(i=0;i<4;i++) 
		gray += in[neighbor[i].y][neighbor[i].x];	
	guess = gray/4;
	return guess;
}

static void draw_line1(Image* inputImage,int tlx,int tly,int brx, int bry) {
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


/*rotation 0: horizantal average*/
/*rotation 1: vertical average*/
static int interpolation_linear_1d(float x,float y,int rotation,byte **in,
	int rows, int cols){
	struct mesh_node neighbor[2];
	float c[2];
	int guess,gridpair[2],gray[2];
	if (rotation==0) {
		grid(x,gridpair);
		neighbor[0].x = gridpair[0];
			if (neighbor[0].x < 0) neighbor[0].x = 0;
			if (neighbor[0].x >= cols) neighbor[0].x = cols -1;
		neighbor[1].x = gridpair[1];
			if (neighbor[1].x < 0) neighbor[1].x = 0;
			if (neighbor[1].x >= cols) neighbor[1].x = cols -1;
		neighbor[0].y = y;
			if (neighbor[0].y < 0) neighbor[0].y = 0;
			if (neighbor[0].y >= rows) neighbor[0].y = rows - 1;
		neighbor[1].y = neighbor[0].y;
 		gray[0] = in[neighbor[0].y][neighbor[0].x];
 		gray[1] = in[neighbor[1].y][neighbor[1].x];
		guess = gray[0]+(gray[1]-gray[0])*(x-neighbor[0].x);
	}
	else if (rotation==1) {
		grid(y,gridpair);
		neighbor[0].y = gridpair[0];
			if (neighbor[0].y < 0) neighbor[0].y = 0;
			if (neighbor[0].y >= rows) neighbor[0].y = rows -1;
		neighbor[1].y = gridpair[1];
			if (neighbor[1].y < 0) neighbor[1].y = 0;
			if (neighbor[1].y >= rows) neighbor[1].y = rows - 1;
		neighbor[0].x = x;
			if (neighbor[0].x < 0) neighbor[0].x = 0;
			if (neighbor[0].x >= cols) neighbor[0].x = cols -1;
		neighbor[1].x = x;
 		gray[0] = in[neighbor[0].y][neighbor[0].x];
 		gray[1] = in[neighbor[1].y][neighbor[1].x];
		guess = gray[0]+(gray[1]-gray[0])*(y-neighbor[0].y);
	}
	return guess;
}

Image * mesh_warping_setup(Image *inputImage) {
	Image *outputImage;
	IMAGE_FORMAT format;
	int method,source,direction;
	char *mesh_file,*outputfile;
	struct mesh *inmesh;
	print_CVIP("\t\tDirection \n");
	print_CVIP("\t\t0.\tBack to main menu \n");
  	print_CVIP("\t\t1.\tFrom a irregular mesh to a regular mesh \n");
  	print_CVIP("\t\t2.\tFrom a regular mesh to an irregular mesh \n");
  	print_CVIP("\n\n\tChoice:"); 

 	direction = getInt_CVIP(10, 0, 2);
	print_CVIP("\t\tGray value interpolation method: \n");	
	print_CVIP("\t\t0.\tBack to main menu \n");
  	print_CVIP("\t\t1.\tNearest neighbor \n");
  	print_CVIP("\t\t2.\tBilinear interpolation\n");
  	print_CVIP("\t\t3.\tNeighbor average\n");
  	print_CVIP("\n\n\tChoice:");
	method = getInt_CVIP(10, 0, 3);
	if(method == 0) {
		printf("\n\tUser interrupt\n");
		return 0;
	}
	print_CVIP("\t\tInput the mesh structure: \n");
	print_CVIP("\t\t0.\tBack to main menu \n");
  	print_CVIP("\t\t1.\tFrom the keyboard \n");
  	print_CVIP("\t\t2.\tFrom a file \n");
  	print_CVIP("\n\n\tChoice:"); 

 	source = getInt_CVIP(10, 0, 2);

 	switch(source) {
	case 0:	printf("\n\tUser interrupt\n");
		return 0;

	case 1: inmesh = keyboard_to_mesh();
		break;

	case 2: print_CVIP("\t\tThe mesh file name, please: ");
		mesh_file = getString_CVIP();
		inmesh = file_to_mesh(mesh_file);
		break;
	
   	default:print_CVIP("Sorry ! You Entered a wrong choice ");
		break;
	}

 	switch(direction) {
	case 0:	printf("\n\tUser interrupt\n");
		return 0;

	case 1: outputImage = mesh_warping(inputImage,inmesh,method);;
		break;

	case 2: outputImage = mesh_warping_ri(inputImage,inmesh,method,CVIP_NO);
		break;
	
   	default:print_CVIP("Sorry ! You Entered a wrong choice ");
		break;
	}
	
	return outputImage;
}


static int in_cell(int x,int y,struct float_pair *lines,int* situation) {

	if((situation[0] == 1)&&(y < lines[0].y)) {
/*line 0 is horizontal,and (x,y) is above line 0*/	
/*printf("\nsituation 0\n");*/
			return 0;
	}
	else if((situation[1] == 1)&&(y >= lines[1].y)) {	
/*line 1 is horizontal,and (x,y) is below line 1*/
/*printf("\nsituation 1\n");*/
			return 0;
	}
	else if((situation[2] == 1)&&(x < lines[2].x)) {	
/*line 2 is vertical,and (x,y) is to the left of line 2*/
/*printf("\nsituation 2\n");*/
			return 0;
	}
	else if((situation[3] == 1)&&(x >= lines[3].x)) {	
/*line 3 is vertical,and (x,y) is to the right of line 3*/
/*printf("\nsituation 3\n");*/
			return 0;
	} 
	else if((lines[0].x>=0)&&(x + y*lines[0].x + lines[0].y) < 0
        &&situation[0] == 0) {
/*printf("\nsituation 4\n");*/	/*above line 0*/
		return 0;
}
	else if((lines[0].x<0)&&(x + y*lines[0].x + lines[0].y) > 0
        &&situation[0] == 0) {
/*printf("\nsituation 4\n");*/	/*above line 0*/
		return 0;
}

	else if((lines[1].x>=0)&&(x + y*lines[1].x + lines[1].y) >= 0
        &&situation[1] == 0) {
/*printf("\nsituation 5\n");*/	/*below line 1*/
		return 0;
}
	else if((lines[1].x<0)&&(x + y*lines[1].x + lines[1].y) <= 0
        &&situation[1] == 0) {
/*printf("\nsituation 5\n");*/	/*below line 1*/
		return 0;
}

	else if((lines[2].x>=0)&&(x*lines[2].x + y + lines[2].y) < 0
        &&situation[2] == 0) {
/*printf("\nsituation 6\n");*/	/*to the left of line 2*/
		return 0;
}
	else if((lines[2].x<0)&&(x*lines[2].x + y + lines[2].y) > 0
        &&situation[2] == 0) {
/*printf("\nsituation 6\n");*/	/*to the left of line 2*/
		return 0;
}
	else if((lines[3].x>=0)&&(x*lines[3].x + y + lines[3].y) >= 0
        &&situation[3] == 0) {
/*printf("\nsituation 7\n");*/	/*to the right of line 3*/
		return 0;
}
	else if((lines[3].x<0)&&(x*lines[3].x + y + lines[3].y) <= 0
        &&situation[3] == 0) {
/*printf("\nsituation 7\n");*/	/*to the right of line 3*/
		return 0;
}
	else {
/*printf("\nsituation 8\n");*/
		return 1;
}
}

static int get_lines(struct mesh_node *intie,struct float_pair *lines,
	int* situation) {
	/*line[].x is the k, line[].y is the c for the line x + ky + c = 0*/
	if(intie[1].y == intie[0].y) { 	/*line 0 is horizontal*/
		situation[0] = 1;
		lines[0].y = intie[0].y;
	}
	else {
		situation[0] = 0;
		lines[0].x
		=(float)(intie[0].x-intie[1].x)/(intie[1].y-intie[0].y);
		lines[0].y = -intie[0].x - intie[0].y * lines[0].x;
	}
	if(intie[3].y == intie[2].y) {	/*line 1 is horizontal*/
		situation[1] = 1;
		lines[1].y = intie[2].y;
	}
	else {
		situation[1] = 0;	
		lines[1].x 
		= (float)(intie[2].x - intie[3].x)/(intie[3].y - intie[2].y);
		lines[1].y = -intie[2].x - intie[2].y * lines[1].x;
	}

	/*line[].x is the k, line[].y is the c for the line kx + y + c = 0*/
	if(intie[2].x == intie[0].x) {	/*line 2 is vertical*/
		situation[2] = 1;
		lines[2].x = intie[0].x; 
	}
	else {
		situation[2] = 0;
		lines[2].x 
		= (float)(intie[2].y - intie[0].y)/(intie[0].x - intie[2].x);
		lines[2].y = -intie[0].y - intie[0].x * lines[2].x;
	}
	if(intie[1].x == intie[3].x) {	/*line 3 is vertical*/
		situation[3] = 1;
		lines[3].x = intie[1].x; 
	}
	else {
		situation[3] = 0;
		lines[3].x 
		= (float)(intie[3].y - intie[1].y)/(intie[1].x - intie[3].x);
		lines[3].y = -intie[1].y - intie[1].x * lines[3].x;
	}
	return(1);
}

static void cell_map_nearest_ri(byte **in,byte **out,
	struct mesh_node *outtie,float *c, int rows, int cols,
	CVIP_BOOLEAN zero_out) {
	struct mesh_node win[2];
	struct float_pair lines[4];
	int x,y,situation[4],tempx,tempy;

	win[0].x = (outtie[0].x < outtie[2].x) ? outtie[0].x : outtie[2].x;
	win[1].x = (outtie[1].x > outtie[3].x) ? outtie[1].x : outtie[3].x;
	win[0].y = (outtie[0].y < outtie[1].y) ? outtie[0].y : outtie[1].y;
	win[1].y = (outtie[2].y > outtie[3].y) ? outtie[2].y : outtie[3].y;
	get_lines(outtie,lines,situation);
/*tiepoints[4] not in order*/
	for(y=win[0].y;y<win[1].y;y++) {
		for(x=win[0].x;x<win[1].x;x++) {
			if(in_cell(x,y,lines,situation)){
				/*get the gray value*/
				tempx = (int)(c[0]*x+c[1]*y+c[2]*x*y+c[3]+0.5);
				tempy = (int)(c[4]*x+c[5]*y+c[6]*x*y+c[7]+0.5);
				if(tempx<0) tempx = 0;
				if(tempy<0) tempy = 0;
				if(tempx >= cols) tempx = cols-1;
				if(tempy >= rows) tempy = rows-1;
				out[y][x] = in[tempy][tempx];
			} else if (zero_out == CVIP_NO) out[y][x] = in[y][x];
		}
	}
}

static void cell_map_average_2d_ri(byte **in,byte **out,
	struct mesh_node *outtie,float *c, int rows, int cols,
	CVIP_BOOLEAN zero_out) {
	int x,y,intx,inty,situation[4];
	struct mesh_node win[2];
	struct float_pair lines[4];
	float tempx,tempy,roundx,roundy;
	win[0].x = (outtie[0].x < outtie[2].x) ? outtie[0].x : outtie[2].x;
	win[1].x = (outtie[1].x > outtie[3].x) ? outtie[1].x : outtie[3].x;
	win[0].y = (outtie[0].y < outtie[1].y) ? outtie[0].y : outtie[1].y;
	win[1].y = (outtie[2].y > outtie[3].y) ? outtie[2].y : outtie[3].y;
	get_lines(outtie,lines,situation);
/*tiepoints[4] not in order*/
	for(y=win[0].y;y<win[1].y;y++) {
		for(x=win[0].x;x<win[1].x;x++) {
			if(in_cell(x,y,lines,situation)){

			/*get the gray value*/
			tempx = c[0]*x+c[1]*y+c[2]*x*y+c[3];
			tempy = c[4]*x+c[5]*y+c[6]*x*y+c[7];
			if(tempx<0)
				tempx = 0;
			if(tempy<0)
				tempy = 0;
			if(tempx>=cols)
				tempx = cols-1;
			if(tempy>=rows)
				tempy = rows-1;			
			roundx = ROUND(tempx);
			intx = (int)roundx;
			roundy = ROUND(tempy);
			inty = (int)roundy;
			if((tempx-roundx != 0.0)&&(tempy-roundy != 0.0))
				out[y][x]
				= interpolation_average_2d(tempx,tempy,in,rows,cols);
			else if(tempy-roundy == 0.0&&tempx-roundx != 0.0)
				out[y][x]
				= interpolation_linear_1d(tempx,tempy,0,in,rows,cols);
			else if(tempx-roundx == 0.0&&tempy-roundy != 0.0)
				out[y][x]
				= interpolation_linear_1d(tempx,tempy,1,in,rows,cols);
			else {
				out[y][x] = in[inty][intx];
			}

			} else if (zero_out == CVIP_NO) out[y][x] = in[y][x];
		}
	}
}

static void cell_map_bilinear_ri(byte **in,byte **out,struct mesh_node *outtie,
	float *c, int rows, int cols, CVIP_BOOLEAN zero_out) {
	int x,y,intx,inty,situation[4];
	struct mesh_node win[2];
	struct float_pair lines[4];
	float tempx,tempy,roundx,roundy;
	win[0].x = (outtie[0].x < outtie[2].x) ? outtie[0].x : outtie[2].x;
	win[1].x = (outtie[1].x > outtie[3].x) ? outtie[1].x : outtie[3].x;
	win[0].y = (outtie[0].y < outtie[1].y) ? outtie[0].y : outtie[1].y;
	win[1].y = (outtie[2].y > outtie[3].y) ? outtie[2].y : outtie[3].y;
	get_lines(outtie,lines,situation);
/*tiepoints[4] not in order*/
	for(y=win[0].y;y<win[1].y;y++) {
		for(x=win[0].x;x<win[1].x;x++) {
			if(in_cell(x,y,lines,situation)){

			/*get the gray value*/
			tempx = c[0]*x+c[1]*y+c[2]*x*y+c[3];
			tempy = c[4]*x+c[5]*y+c[6]*x*y+c[7];
			if(tempx<0)
				tempx = 0;
			if(tempy<0)
				tempy = 0;
			if(tempx>=cols)
				tempx = cols -1;
			if(tempy>=rows)
				tempy = rows -1;			
			roundx = ROUND(tempx);
			intx = (int)roundx;
			roundy = ROUND(tempy);
			inty = (int)roundy;
			if((tempx-roundx != 0.0)&&(tempy-roundy != 0.0))
				out[y][x]
				= interpolation_bilinear(tempx,tempy,in,rows,cols);
			else if(tempy-roundy == 0.0&&tempx-roundx != 0.0)
				out[y][x]
				= interpolation_linear_1d(tempx,tempy,0,in,rows,cols);
			else if(tempx-roundx == 0.0&&tempy-roundy != 0.0)
				out[y][x]
				= interpolation_linear_1d(tempx,tempy,1,in,rows,cols);
			else {
				out[y][x] = in[inty][intx];
			}

			} else if (zero_out == CVIP_NO) out[y][x] = in[y][x];
		}
	}
}

static double get_delta(float a0[4],float a1[4],float a2[4],float a3[4]) {
	double delta,rate,temp;
	double c[4][4];
	int i,j,m,n;

	for (i=0;i<4;i++) {
		c[0][i]=a0[i];
		c[1][i]=a1[i];
		c[2][i]=a2[i];
		c[3][i]=a3[i];
	}
	m = 5;
	for(i=0;i<4;i++) {
		if(c[i][0]!=0){
			m = i;
			break;
		}
	}
/*printf("\nm=%d\n",m);*/
	if(m==5) {
/*		printf("m==5\n");*/
		return 0.;
	}
	if(m!=0) {
		for(i=0;i<4;i++){
			temp = c[m][i];
			for(j=m;j>0;j--)
				c[j][i] = c[j-1][i];
			c[0][i] = temp;
		}
	}
/*for(i=0;i<4;i++) {
	for(j=0;j<4;j++)
		printf("%f,",c[j][i]);
	printf("\n");
}
printf("\n");*/
	for(i=1;i<4;i++) {
		if(c[i][0] != 0.) {
			rate = c[i][0]/c[0][0];
			for(j=1;j<4;j++) {
				c[i][j] -= c[0][j]*rate;
			}
		}
	}
/*for(i=0;i<4;i++) {
	for(j=0;j<4;j++)
		printf("%f,",c[j][i]);
	printf("\n");
}
printf("\n");*/
	n = 5;
	for(i=1;i<4;i++) {
		if(c[i][1]!=0){
			n = i;
			break;
		}
	}
/*printf("\nn=%d\n",n);*/
	if(n==5) {
/*		printf("n==5\n");*/
		return 0.;
	}
	if(n!=1) {
		for(i=1;i<4;i++){
			temp = c[n][i];
			for(j=n;j>1;j--) 
				c[j][i] = c[j-1][i];
			c[1][i] = temp;
		}
	}
/*for(i=0;i<4;i++) {
	for(j=0;j<4;j++)
		printf("%f,",c[j][i]);
	printf("\n");
}
printf("\n");*/
	for(i=2;i<4;i++) {
		if(c[i][1] != 0.) {
			rate = c[i][1]/c[1][1];
			for(j=2;j<4;j++) {
				c[i][j] -= c[1][j]*rate;
			}
		}
	}
/*for(i=0;i<4;i++) {
	for(j=0;j<4;j++)
		printf("%f,",c[j][i]);
	printf("\n");
}
printf("\n");*/
	delta = c[0][0]*c[1][1]*(c[2][2]*c[3][3]-c[2][3]*c[3][2]);
	if(m==1||m==3)
		delta = -delta;
	if(n==2)
		delta = -delta;
	
	return delta;	
}


Image * area_points(Image *cvipImage){
	struct mesh *inmesh;
	char *inputfile, *outputfile;
	int i, j;
	byte **out;
	struct mesh_node intie[4];
	out = getData_Image(cvipImage, 0);
	print_CVIP("\n\tInput the mesh file name: ");
	inputfile = getString_CVIP(); 
	inmesh = file_to_mesh(inputfile);
	printf("\n\ti: ");
	i = getInt_CVIP(10, 0, inmesh->width-2);
	printf("\n\tj: ");
	j = getInt_CVIP(10, 0, inmesh->height-2);
	intie[0]=inmesh->nodes[i][j];
	intie[1]=inmesh->nodes[i+1][j];
	intie[2]=inmesh->nodes[i][j+1];
	intie[3]=inmesh->nodes[i+1][j+1];
	cell_paint(out,intie);
	return cvipImage;
} 

void solve_bilinear(void){
	float c[8];
	struct mesh_node intie[4],outtie[4];
	int i, j;
	printf("\nThe following equations are used to define the mapping, one x and one y equation for each tie point, 4 tie points, a total of 8 equations:\n\n");
	printf("====================================================\n");
	printf("c[0]X_in + c[1]Y_in + (c[2]X_in Y_in) + c[3] = X_out\n\n");
	printf("c[4]X_in + c[5]Y_in + (c[6]X_in Y_in) + c[7] = Y_out\n");
	printf("====================================================\n\n");
	printf("(X_in,Y_in) and (X_out,Y_out) are the coordinates of each tie point\n");
 	for(i=0;i<4;i++) {
		printf("\nInput X_in[%d]: ",i);
		intie[i].x = getInt_CVIP(10,0,512);
		printf("Input Y_in[%d]: ",i);
		intie[i].y = getInt_CVIP(10,0,512);
	}
	for(i=0;i<4;i++) {
		printf("\nInput X_out[%d]: ",i);
		outtie[i].x = getInt_CVIP(10,0,512);
		printf("Input Y_out[%d]: ",i);
		outtie[i].y = getInt_CVIP(10,0,512);
	}
	printf("\n");
	solve_c(intie,outtie,c);
	printf("\n");
	for(i=0;i<8;i++) {
		printf("c[%d] = %f\n",i,c[i]);
	}
	printf("\n\n");
}

void display_regular(void){
	char	*inputfile;
	char    image_name[100];
	struct mesh *inmesh;
	Image	*cvipImage;
	print_CVIP("\n\tInput the mesh file name: ");
	inputfile = getString_CVIP(); 
	inmesh = file_to_mesh(inputfile);
	if(inmesh == NULL){
		fprintf(stderr,"\nError in reading the mesh file\n");
		return;
	}
	cvipImage = create_black(512,512);
	print_CVIP("\n\tDisplaying original mesh...");
 	strcpy(image_name,inputfile);
	strcat(image_name,"-ORIGINAL");
	display_mesh(cvipImage,inmesh,image_name);	
	inmesh = regular_mesh(inmesh,512,512);
 	strcpy(image_name,inputfile);
	strcat(image_name,"-REGULAR");
	cvipImage = create_black(512,512);
	print_CVIP("\n\tDisplaying regular mesh...");
	display_mesh(cvipImage,inmesh,image_name);
	free(inputfile);
}

