
/** parameterize.h --> header file**/
#include <stdlib.h>
#include <stdio.h>

#define COLOR 0
#define PERIMETER	1 

#define NUM_OF_SLICES	1
#define VSIZE	480
#define HSIZE	512

#define num_objects_found 1
#define soc_per_slice	1

char slice[NUM_OF_SLICES+1][VSIZE][HSIZE];


int SOC_per_slice[NUM_OF_SLICES+1][num_objects_found];
int SOC_data[NUM_OF_SLICES+1][num_objects_found][soc_per_slice][2];
/* 1 0 0 1 */
char ***precision_slice;
float *****SOC_param_boundary;

/* 1 0 0 point# 0 or 1 */

extern void parameterize(Image *imageP);
