/***************************************************************************
* =========================================================================
*   Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* =========================================================================
*
*             File Name: laws_texture.h 
*           Description: contains the function prototypes, constants, and
*                        types defined in laws_texture.c
*   Initial Coding Date: September 27, 2012
*           Portability: Standard (ANSI) C
*             Credit(s): Christopher Daigle, Anthony Seganfredo,
*                        Patrick Solt
*                        Southern Illinois University Edwardsville
*
*   Copyright (C) 2013 Scott Umbaugh and SIUE
*
****************************************************************************/

#ifndef _LAWS_TEXTURE
#define _LAWS_TEXTURE

#define LAWS_LEVEL          0
#define LAWS_EDGE           1
#define LAWS_SPOT           2
#define LAWS_RIPPLE         3
#define LAWS_WAVE           4

#define LAWS_SIZE           5
#define LAWS_BOUND          LAWS_SIZE / 2

#define NEIGHBORHOOD_SIZE   15
#define NEIGHBORHOOD_BOUND  NEIGHBORHOOD_SIZE / 2

#ifdef _LAWS_TEXTURE_C
/* laws mask constants */
const int laws_masks[LAWS_SIZE][LAWS_SIZE][LAWS_SIZE][LAWS_SIZE] =
{
   {{{  1,   4,   6,   4,   1}, {  4,  16,  24,  16,   4}, {  6,  24,  36,  24,   6}, {  4,  16,  24,  16,   4}, {  1,   4,   6,   4,   1}},
    {{ -1,  -2,   0,   2,   1}, { -4,  -8,   0,   8,   4}, { -6, -12,   0,  12,   6}, { -4,  -8,   0,   8,   4}, { -1,  -2,   0,   2,   1}},
    {{ -1,   0,   2,   0,  -1}, { -4,   0,   8,   0,  -4}, { -6,   0,  12,   0,  -6}, { -4,   0,   8,   0,  -4}, { -1,   0,   2,   0,  -1}},
    {{  1,  -4,   6,  -4,   1}, {  4, -16,  24, -16,   4}, {  6, -24,  36, -24,   6}, {  4, -16,  24, -16,   4}, {  1,  -4,   6,  -4,   1}},
    {{ -1,   2,   0,  -2,   1}, { -4,   8,   0,  -8,   4}, { -6,  12,   0, -12,   6}, { -4,   8,   0,  -8,   4}, { -1,   2,   0,  -2,   1}}},

   {{{ -1,  -4,  -6,  -4,  -1}, { -2,  -8, -12,  -8,  -2}, {  0,   0,   0,   0,   0}, {  2,   8,  12,   8,   2}, {  1,   4,   6,   4,   1}},
    {{  1,   2,   0,  -2,  -1}, {  2,   4,   0,  -4,  -2}, {  0,   0,   0,   0,   0}, { -2,  -4,   0,   4,   2}, { -1,  -2,   0,   2,   1}},
    {{  1,   0,  -2,   0,   1}, {  2,   0,  -4,   0,   2}, {  0,   0,   0,   0,   0}, { -2,   0,   4,   0,  -2}, { -1,   0,   2,   0,  -1}},
    {{ -1,   4,  -6,   4,  -1}, { -2,   8, -12,   8,  -2}, {  0,   0,   0,   0,   0}, {  2,  -8,  12,  -8,   2}, {  1,  -4,   6,  -4,   1}},
    {{  1,  -2,   0,   2,  -1}, {  2,  -4,   0,   4,  -2}, {  0,   0,   0,   0,   0}, { -2,   4,   0,  -4,   2}, { -1,   2,   0,  -2,   1}}},

   {{{ -1,  -4,  -6,  -4,  -1}, {  0,   0,   0,   0,   0}, {  2,   8,  12,   8,   2}, {  0,   0,   0,   0,   0}, { -1,  -4,  -6,  -4,  -1}},
    {{  1,   2,   0,  -2,  -1}, {  0,   0,   0,   0,   0}, { -2,  -4,   0,   4,   2}, {  0,   0,   0,   0,   0}, {  1,   2,   0,  -2,  -1}},
    {{  1,   0,  -2,   0,   1}, {  0,   0,   0,   0,   0}, { -2,   0,   4,   0,  -2}, {  0,   0,   0,   0,   0}, {  1,   0,  -2,   0,   1}},
    {{ -1,   4,  -6,   4,  -1}, {  0,   0,   0,   0,   0}, {  2,  -8,  12,  -8,   2}, {  0,   0,   0,   0,   0}, { -1,   4,  -6,   4,  -1}},
    {{  1,  -2,   0,   2,  -1}, {  0,   0,   0,   0,   0}, { -2,   4,   0,  -4,   2}, {  0,   0,   0,   0,   0}, {  1,  -2,   0,   2,  -1}}},

   {{{ -1,  -4,  -6,  -4,  -1}, {  2,   8,  12,   8,   2}, {  0,   0,   0,   0,   0}, { -2,  -8, -12,  -8,  -2}, {  1,   4,   6,   4,   1}},
    {{  1,   2,   0,  -2,  -1}, { -2,  -4,   0,   4,   2}, {  0,   0,   0,   0,   0}, {  2,   4,   0,  -4,  -2}, { -1,  -2,   0,   2,   1}},
    {{  1,   0,  -2,   0,   1}, { -2,   0,   4,   0,  -2}, {  0,   0,   0,   0,   0}, {  2,   0,  -4,   0,   2}, { -1,   0,   2,   0,  -1}},
    {{ -1,   4,  -6,   4,  -1}, {  2,  -8,  12,  -8,   2}, {  0,   0,   0,   0,   0}, { -2,   8, -12,   8,  -2}, {  1,  -4,   6,  -4,   1}},
    {{  1,  -2,   0,   2,  -1}, { -2,   4,   0,  -4,   2}, {  0,   0,   0,   0,   0}, {  2,  -4,   0,   4,  -2}, { -1,   2,   0,  -2,   1}}},

   {{{  1,   4,   6,   4,   1}, { -4, -16, -24, -16,  -4}, {  6,  24,  36,  24,   6}, { -4, -16, -24, -16,  -4}, {  1,   4,   6,   4,   1}},
    {{ -1,  -2,   0,   2,   1}, {  4,   8,   0,  -8,  -4}, { -6, -12,   0,  12,   6}, {  4,   8,   0,  -8,  -4}, { -1,  -2,   0,   2,   1}},
    {{ -1,   0,   2,   0,  -1}, {  4,   0,  -8,   0,   4}, { -6,   0,  12,   0,  -6}, {  4,   0,  -8,   0,   4}, { -1,   0,   2,   0,  -1}},
    {{  1,  -4,   6,  -4,   1}, { -4,  16, -24,  16,  -4}, {  6, -24,  36, -24,   6}, { -4,  16, -24,  16,  -4}, {  1,  -4,   6,  -4,   1}},
    {{ -1,   2,   0,  -2,   1}, {  4,  -8,   0,   8,  -4}, { -6,  12,   0, -12,   6}, {  4,  -8,   0,   8,  -4}, { -1,   2,   0,  -2,   1}}}
};
#endif
#endif
