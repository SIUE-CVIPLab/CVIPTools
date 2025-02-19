/*filename mesh.h*/
/*Jianxin Tan, 3/23/95*/
/* $Log: CVIPmesh.h,v $
 * Revision 1.7  1997/04/09 22:49:35  yawei
 * cleaned up functions
 *
 * Revision 1.6  1997/04/09 17:03:57  yawei
 * added two parms to cell_map_bilinear_ri
 *
 * Revision 1.5  1997/01/15 17:12:57  yawei
 * Global Change:  IMAGE ==> Image
 *
 * Revision 1.4  1996/12/06  15:44:34  akjoele
 * Made function prototypes ANSI C-ish
 *
 * Revision 1.3  1995/05/15  20:53:40  luok
 * *** empty log message ***
 *
 * Revision 1.2  1995/05/15  20:28:41  luok
 * change the declaration for mesh warping setup.
 *
*/

#ifndef _CVIP_MESH
#define _CVIP_MESH


#include <stdlib.h>
#include <math.h>

struct mesh_node {
	int x;
	int y;
};

struct mesh {
	int width;
	int height;
	struct mesh_node** nodes;
};

struct float_pair {
	float x;
	float y;
};

#ifdef __cplusplus
extern "C"{
#endif 

Image *mesh_warping(Image *inputImage,struct mesh *inmesh,int method);
Image *mesh_warping_ri(Image *inputImage,struct mesh *inmesh,int method,
	CVIP_BOOLEAN zero_out);
Image * mesh_warping_setup(Image *cvipImage);

struct mesh *file_to_mesh(char* mesh_file);	/*read a mesh from a file*/
struct mesh *keyboard_to_mesh(void);	/*input the mesh from the keyboard*/
int mesh_to_file(struct mesh *mesh_matrix,char* mesh_file);
	/*save the mesh to a file*/
int print_mesh(struct mesh *inmesh);	
	/*print the mesh to screen*/
void  display_mesh(Image* inputImage,struct mesh *inmesh, char *filename);
	/*display the mesh to screen*/
struct mesh *regular_mesh(struct mesh* inmesh,int width,int height);

int solve_c(struct mesh_node *intie,struct mesh_node *outtie,float *c);
void cell_paint(byte **out,struct mesh_node *intie);
void create_mesh_sine(void);

#ifdef __cplusplus
}
#endif 

/*void cell_map_nearest_ri(byte **in,byte **out,struct mesh_node *outtie,
	float *c, int rows, int cols);
void cell_map_bilinear_ri(byte **in,byte **out,struct mesh_node *outtie,float *c);
void cell_map_average_2d_ri(byte **in,byte **out,struct mesh_node *outtie,float
 *c); 

void cell_map(byte **in,byte **out,byte **reg,struct mesh_node *intie,struct
 mesh_node *outtie,float *c);
void cell_map_nearest(byte **in,byte **out,struct mesh_node *outtie,float *c);
void cell_map_bilinear(byte **in,byte **out,struct mesh_node *outtie,float *c);
void cell_map_average_2d(byte **in,byte **out,struct mesh_node *outtie,float
 *c);
int solve_equation4(struct mesh_node *left,int* right,float *c);
double get_delta(float c0[4],float c1[4],float c2[4],float c3[4]);

int interpolation_bilinear(float x,float y,byte **in);
int interpolation_average_2d(float x,float y,byte **in);
int interpolation_linear_1d(float x,float y,int rotation,byte **in);
void grid(float x,int *gridpair);
int in_cell(int x,int y,struct float_pair *lines,int* situation);
int get_lines(struct mesh_node *intie,struct float_pair *lines,int* situation);

void draw_line1(Image* inputImage,int tlx,int tly,int brx, int bry);
Image *black_pgm1(int width, int height);
 Make them static */

#endif
