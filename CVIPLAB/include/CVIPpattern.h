/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: CVIPlab.h
*           Description: contains function prototypes, constants and types
*			            defined in CVIPlab functions.
*         Related Files: *.c
*   Initial Coding Date: Jun. 19, 2005
*           Portability: Standard (ANSI) C
*             Credit(s): Geer Shuang
*                        Southern Illinois University @ Edwardsville
*
*
****************************************************************************/



#ifndef MAX_CASE
#define MAX_CASE 128
#endif

#ifndef CVIP_PATTERN_H
#define CVIP_PATTERN_H

#ifdef __cplusplus
extern "C"{
#endif 

extern float euclidean_distance(float *vector1, float *vector2, int n);
extern float city_block(float *vector1, float *vector2, int n);
extern float maximum_value_metric(float *vector1, float *vector2, int n);
extern float vector_inner_product(float *vector1, float *vector2, int n);
extern float tanimoto_metric(float *vector1, float *vector2, int n, int *err_code);
extern float minkowski_distance(float *vector1, float *vector2, int r, int n, int *err_code);
extern float **range_normalize(float **vector, int i, int j, int option, int *err_code);
extern float **unit_vector_normalization(float **vector, int i, int j, int option, int *err_code);
extern float **standard_normal_density_normalization(float **vector, int i, int j, int option, int *err_code);
extern float **min_max_normalization(float **vector, int i, float s_min, float s_max, int option, int *err_code);
extern float **softmax_scaling(float **vector, int i, int j, float r_softmax, int option, int *err_code);
extern int pattern_euclidean(char *file_tt, char *file_tr, int *err_code);
extern int pattern_city_block(char *file_tt, char *file_tr, int *err_code);
extern int pattern_maximum(char *file_tt, char *file_tr, int *err_code);
extern int pattern_minkowski(char *file_tt, char *file_tr, int r_minkowski, int *err_code);
extern int pattern_vector_inner_product(char *file_tt, char *file_tr, int *err_code);
extern int pattern_tanimoto(char *file_tt, char *file_tr, int *err_code);
extern int *pattern_range_normalize(char *file_tr, char *file_tt, int *err_code);
extern int *pattern_unit_vector_normalization(char *file_tr, char *file_tt, int *err_code);
extern int *pattern_standard_normal_density_normalization(char *file_tr, char *file_tt, int *err_code);
extern int *pattern_min_max_normalization(char *file_tr, char *file_tt, float s_min, float s_max, int *err_code);
extern int *pattern_softmax_scaling_normalization(char *file_tr, char *file_tt, float r_softmax, int *err_code);
extern int *nearest_centroid_set(char *file_tr, int *err_code);
extern int k_nearest_neighbor(char *file_tt, char *file_tr, char *file_out, int option_normalize, int option_distance, int k, float s_min, float s_max, float r_softmax, int r_minkowski);
extern int nearest_neighbor(char *file_tt, char *file_tr, char *file_out, int option_normalize, int option_distance, float s_min, float s_max, float r_softmax, int r_minkowski);
extern int nearest_centroid(char *file_tt, char *file_tr, char *file_out, int option_normalize, int option_distance, float s_min, float s_max, float r_softmax, int r_minkowski);


#ifdef __cplusplus
}
#endif

#endif
