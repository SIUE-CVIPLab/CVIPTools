/*********************************************************************
*                                                                    *
*  ===============================================================   *
*  Computer Vision/Image Processing Tool - Dr. Scott Umbaugh, SIUE   *
*  ===============================================================   *
*                                                                    *
*                                                                    *
*                                                                    *
*  Routine/pgm name:                                                 *
*         xform_setup.c                                              *
*                                                                    *
*  Description: This is a setup function for the following           *
*         transforms: Walsh, Hadamard, Haar and Slant.               *
*                                                                    *
*  Variables Passed: image - an Image pointer                        *
*                                                                    *
*  Variables Returned: image - pointer to the transformed image      *
*                                                                    *
*         Author: Arve Kjoelen                                       *
*                                                                    *
*  Initial Coding date: 3/29/93                                      *
*                                                                    *
*  Last Revisions made: 9/15/93                                      *
*                                                                    *
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include "CVIPimage.h"
#include "CVIPtools.h"
#include "CVIPdef.h"
#include "CVIPtransform.h"


Image *xform_setup(Image *image, CVIP_BOOLEAN *remap, PROGRAMS transform)
{
   char *answer;
   HISTORY stuff;
   int choice, block_size, n_rows, n_cols;
   answer = (char *)malloc(25);
   *remap = CVIP_YES;

   switch(transform) {
      case WALSH:
         while(1) {
            fprintf(stdout, "\n1. Walsh Transform\n");
            fprintf(stdout, "2. Inverse Walsh Transform\n");
            (void)gets(answer);
            choice = atoi(answer);
            free(answer);
            if(choice == 1) { /* Forward WALSH */
               block_size = get_block_size();
               if(get_zpad_dims(image, &n_rows, &n_cols, block_size)==CVIP_YES)
                  zero_pad(image, n_rows, n_cols);
               image = (Image *)walhad_transform(image, 1, block_size);
               return(image);
            }
            else if(choice == 2) { /* Inverse WALSH */
               if(!history_check(WALSH, image)) {
                  fprintf(stdout, "Enter blocksize used for forward WALSH:\n");
                  (void)gets(answer);
                  block_size=atoi(answer);
                  free(answer);
               }
               else {
                  stuff=history_get(image, WALSH);
		  GET_HIST_DATA(stuff,0,block_size);
               }
               image = (Image *)walhad_transform(image, 0, block_size);
               return(image);
            }
            else {
               fprintf(stderr, "Invalid choice!\n");
            }
         }
      break;
      case HADAMARD:
         while(1) {
            fprintf(stdout, "\n1. Hadamard Transform\n");
            fprintf(stdout, "2. Inverse Hadamard Transform\n");
            (void)gets(answer);
            choice = atoi(answer);
            free(answer);
            if(choice == 1) { /* Forward HADAMARD */
               block_size = get_block_size();
               if(get_zpad_dims(image, &n_rows, &n_cols, block_size)==CVIP_YES)
                  zero_pad(image, n_rows, n_cols);
               image = (Image *)walhad_transform(image, 3, block_size);
               return(image);
            }
            else if(choice == 2) { /* Inverse HADAMARD */
               if(!history_check(HADAMARD, image)) {
                  fprintf(stdout, "Enter blocksize used for forward HADAMARD:\n");
                  (void)gets(answer);
                  block_size=atoi(answer);
                  free(answer);
               }
               else {
                  stuff=history_get(image, HADAMARD);
		  GET_HIST_DATA(stuff,0,block_size);
               }
               image = (Image *)walhad_transform(image, 2, block_size);
               return(image);
            }
            else {
               fprintf(stderr, "Invalid choice!\n");
            }
         }
      break;
      case HAAR:
         while(1) {
            fprintf(stdout, "\n1. Haar Transform\n");
            fprintf(stdout, "2. Inverse Haar Transform\n");
            (void)gets(answer);
            choice = atoi(answer);
            free(answer);
            if(choice == 1) { /* Forward HAAR */
               block_size = get_block_size();
               if(get_zpad_dims(image, &n_rows, &n_cols, block_size)==CVIP_YES)
                  zero_pad(image, n_rows, n_cols);
               image = (Image *)haar_transform(image, 1, block_size);
               return(image);
            }
            else if(choice == 2) { /* Inverse HAAR */
               if(!history_check(HAAR, image)) {
                  fprintf(stdout, "Enter blocksize used for forward HAAR:\n");
                  (void)gets(answer);
                  block_size=atoi(answer);
                  free(answer);
               }
               else {
                  stuff=history_get(image, HAAR);
		  GET_HIST_DATA(stuff,0,block_size);
               }
               image = (Image *)haar_transform(image, 0, block_size);
               return(image);
            }
            else {
               fprintf(stderr, "Invalid choice!\n");
            }
         }
      break;
      default: {
         fprintf(stderr, "Invalid selection\n");
         *remap=CVIP_NO;
         return(image);
      }
   }
   return(NULL);
}
