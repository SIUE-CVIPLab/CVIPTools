
#ifndef _tri2tri_
#define _tri2tri_

#define TRANS1(t1,t2,t3,matrix) (matrix[0][0]*(t1) + matrix[0][1]*(t2) + matrix[0][2]*(t3))
#define TRANS2(t1,t2,t3,matrix) (matrix[1][0]*(t1) + matrix[1][1]*(t2) + matrix[1][2]*(t3))
#define TRANS3(t1,t2,t3,matrix) (matrix[2][0]*(t1) + matrix[2][1]*(t2) + matrix[2][2]*(t3))

typedef double trans_matrix[3][3];

static trans_matrix RGBtoYIQ = { { 0.299,  0.587,  0.114},
				 { 0.596, -0.274, -0.322},
				 { 0.211, -0.523,  0.312} };

static trans_matrix RGBtoXYZ = { { 0.607,  0.174,  0.201},
				 { 0.299,  0.587,  0.114},
				 { 0.000,  0.066,  1.117} };
 
static trans_matrix RGBtoUVW = { { 0.405,  0.116,  0.133},
				 { 0.299,  0.587,  0.114},
				 { 0.145,  0.827,  0.627} };

static trans_matrix YIQtoRGB = { { 1.000,  0.956,  0.621},
				 { 1.000, -0.272, -0.647},
				 { 1.000, -1.106,  1.703} };

static trans_matrix YIQtoXYZ = { { 0.967,  0.318,  0.594},
				 { 1.000,  0.000,  0.000},
				 { 1.173, -1.238,  1.870} };

static trans_matrix YIQtoUVW = { { 0.653,  0.208,  0.403},
				 { 1.000,  0.000,  0.000},
				 { 1.599, -0.780,  0.623} };

static trans_matrix XYZtoRGB = { { 1.910, -0.533, -0.288},
				 {-0.985,  2.000, -0.028},
				 { 0.058, -0.118,  0.896} };

static trans_matrix XYZtoYIQ = { { 0.000,  1.000,  0.000},
				 { 1.407, -0.842, -0.451},
				 { 0.932,  1.189,  0.233} };

static trans_matrix XYZtoUVW = { { 0.667,  0.000,  0.000},
				 { 0.000,  1.000,  0.000},
				 {-0.500,  1.500,  0.500} };

static trans_matrix UVWtoRGB = { { 2.432,  0.332, -0.576},
				 {-1.519,  2.083, -0.057},
				 { 1.440, -2.823,  1.803} };

static trans_matrix UVWtoYIQ = { { 0.000,  1.000,  0.000},
				 { 1.403,  0.534, -0.907},
				 { 1.757, -1.898,  0.470} };

static trans_matrix UVWtoXYZ = { { 1.500,  0.000,  0.000},
				 { 0.000,  1.000,  0.000},
				 { 1.500, -3.000,  2.000} };

#endif
/* Don't add after the endif */
