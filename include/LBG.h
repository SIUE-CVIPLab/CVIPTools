/************************************************************************
*									*
* ===================================================================== *
*  COMPUTER VISION/Image PROCESSING TOOL - DR. SCOTT E. UMBAUGH, SIUE	*
* ===================================================================== *
*									*
*	FILE NAME: lbg.h						*
*									*
*	DESCRIPTION: header file containing struc type definitions	*
*	and function prototypes for all routines dealing with the	*
*	LBG (Linde, Buzo and Gray) algorithm for Vector Quantization.	*
*									*
*	AUTHOR: Arve Kjoelen, SIUE					*
*									*
*	RELATED FILES: lbg.c						*
*									*
*	INITIAL CODING DATE: 9/28/93					*
*									*
*	LAST MODIFICATIONS MADE: 10/22/93				*
*									*
************************************************************************/
#if !defined( CVIP_LBG_DEFINED)

   #define CVIP_LBG_DEFINED
   #include "CVIPimage.h"
   #include "CVIPdef.h"
   #define LBG_ERROR 0.001

   typedef enum {WAVL, EQUAL_BLOCKS} BLOCK_TYPE;
   typedef struct VQ_info *VQ_INFO;

   typedef struct element *ELEMENT;
   struct element {
      float **codebook;        /* Codebook for this frequency band       */
      float **data;            /* Vectors Created by block_to_vec        */
      int *codebook_index;     /* Nearest codeword for each vector       */
      ELEMENT next;            /* Pointer to info for next color band    */
   };
 
   struct VQ_info {
      BLOCK_TYPE block_type;    /* Blocks of equal size or not.             */
      CVIP_BOOLEAN pct_done;         /* PCT done between fbands or not.	    */
      MATRIX **pcts;		/* Pointer to PCT transform matrices.	    */
      byte scheme;              /* Identifies the compression scheme used.  */
      int bands;                /* Number of frequency bands.               */
      int *hsize;               /* Horizontal sizes of blocks.              */
      int *vsize;               /* Vertical sizes of blocks.                */
      int *codebook_size;       /* Size of codebook in each frequency band. */
      int *nvecs;		/* Number of data vectors in each band	    */
      ELEMENT elements;         /* Pointer to the data for this color band. */
      VQ_INFO next;             /* Pointer to info for next color band      */
   };
   CVIP_BOOLEAN Tumor_image;
   /* Preset schemes for wavelet vector quantization of 512x512 image: */

   /* Scheme 1: 10 frequency bands, ~ 0.7109 bpp (11.25:1) */
   static int WVQ1_blocks[] = {64, 2, 2, 2, 2, 2, 4, 4, 4, 8};
   static int WVQ1_cbsizes[] = {1, 256, 256, 64, 64, 64, 256, 256, 256, 256};
   static int WVQ1_nvecs[] = {1, 1024, 1024, 1024, 4096, 4096, 1024, 4096, 4096, 1024};

   /* Scheme 1 for Tumor Images: 10 fbands, ~ */
   static int TUM1_blocks[] = {56, 2, 2, 2, 2, 2, 4, 4, 4, 8};
   static int TUM1_nvecs[] = {1, 784, 784, 784, 3136, 3136, 1024, 3136, 3136, 786};

   /* Scheme (PCT): 10 frequency bands, ~ 0.338 bpp (12.9074:1) */
   /* WVQ2R also serves as scheme 4 - 0.8394bpp */
   static int WVQ2R_blocks[] = {64, 2, 2, 2, 2, 2, 4, 4, 4, 8};
   static int WVQ2R_cbsizes[] = {1, 512, 512, 256, 128, 128, 512, 512, 512, 512};
   static int WVQ2R_nvecs[] = {1, 1024, 1024, 1024, 4096, 4096, 1024, 4096, 4096, 1024};
   static int WVQ2G_blocks[] = {64, 2, 2, 2, 4, 4, 8, 16, 16, 16};
   static int WVQ2G_cbsizes[] = {1, 256, 256, 64, 64, 64, 64, 0, 0, 0};
   static int WVQ2G_nvecs[] = {1, 1024, 1024, 1024, 1024, 1024, 256, 0, 0, 0};
   /* WVQ2B also serves as scheme 5 - 0.2239 bpp*/
   static int WVQ2B_blocks[] = {64, 2, 2, 2, 4, 4, 8, 16, 16, 16};
   static int WVQ2B_cbsizes[] = {1, 64, 64, 32, 64, 64, 64, 0, 0, 0};
   static int WVQ2B_nvecs[] = {1, 1024, 1024, 1024, 1024, 1024, 256, 0, 0, 0};

   /* Scheme 2: 10 frequency bands ~ 0.2434 bpp (32.87:1) */
   static int WVQ3_blocks[] = {64, 2, 2, 2, 4, 4, 8, 16, 16, 16};
   static int WVQ3_cbsizes[] = {1, 256, 256, 64, 64, 64, 64, 0, 0, 0};
   static int WVQ3_nvecs[] = {1, 1024, 1024, 1024, 1024, 1024, 256, 0, 0, 0};

   /* Scheme 4: 10 frequency bands, 0.7969 bpp */
   static int WVQ4_blocks[] = {64, 2, 2, 2, 2, 2, 4, 4, 4, 8};
   static int WVQ4_cbsizes[] = {1, 512, 512, 256, 128, 128, 512, 512, 512, 512};
   static int WVQ4_nvecs[] = {1, 1024, 1024, 1024, 4096, 4096, 1024, 4096, 4096, 1024};

   /* Scheme 6: 13 frequency bands, 0.7363bpp - 10.86:1 */
   static int WVQ6_blocks[] = {32, 2, 2, 2, 2, 2, 2, 2, 2, 4, 4, 4, 8};
   static int WVQ6_cbsizes[] = {1, 4096, 4096, 1024, 512, 512, 256, 128, 128, 512, 512, 512, 512};
   static int WVQ6_nvecs[] = {1, 256, 256, 256, 1024, 1024, 1024, 4096, 4096, 1024, 4096, 4096, 1024};

   /* Schemes with n in name indicate 'new' schemes designed with the */
   /* primary objective of minimizing total disk space - that is, the */
   /* sum of the data and codebook sizes.			      */
   /* Scheme n1 (6): 9.3267:1  <=>  0.8577 TOTAL bpp */

   static int WVQn1_hblocks[] = {64, 2, 2, 2, 2, 2, 2, 2, 2, 0};
   static int WVQn1_vblocks[] = {64, 2, 2, 2, 2, 2, 2, 4, 4, 0};
   static int WVQn1_cbsizes[] = {1, 256, 256, 64, 32, 32, 32, 32, 32, 0};
   static int WVQn1_nvecs[] = {1, 1024, 1024, 1024, 4096, 4096, 4096, 8192, 8192, 0};

   /* Scheme n2 (7): */
   /* use same blocks and nvecs as scheme n1, only cbsizes differ */
   static int WVQn2_cbsizes[] = {1, 256, 256, 64, 32, 32, 32, 16, 16, 0};

   /* Scheme n3 (8): */
   /* use same blocks as scheme n1, cbsizes and nvecs are different */
   static int WVQn3_cbsizes[] = {1, 256, 256, 64, 32, 32, 16, 0, 0, 0};
   static int WVQn3_nvecs[] = {1, 1024, 1024, 1024, 4096, 4096, 4096, 0, 0, 0};

   /* scheme n4: uses the PCT and downsampling */
   /* band 1 is identical to WVQ1n scheme */
   static int WVQn4G_hblocks[] = {32, 2, 2, 2, 2, 2, 2, 0, 0, 0};
   static int WVQn4G_vblocks[] = {32, 1, 1, 1, 2, 2, 2, 0, 0, 0};
   static int WVQn4G_cbsizes[] = {1, 16, 16, 8, 32, 32, 32, 0, 0, 0};
   static int WVQn4G_nvecs[] = {1, 512, 512, 512, 1024, 1024, 1024, 0, 0, 0}; 

   /* scheme subPCT1: Uses the PCT to decorrelate fbands: 17.36:1 */
   static int WVQsubPCT1_hblocks[] = {64, 2, 2, 2, 2, 2, 2, 0, 0, 0};
   static int WVQsubPCT1_vblocks[] = {64, 2, 2, 4, 2, 4, 4, 0, 0, 0};
   static int WVQsubPCT1_cbsizes[] = {1, 256, 128, 128, 64, 32, 16, 0, 0, 0};
   static int WVQsubPCT1_nvecs[] = {1, 1024, 1024, 512, 4096, 2048, 2048, 0, 0, 0};

   /* scheme subPCT2: Uses the PCT to decorrelate fbands: */
   static int WVQsubPCT2_hblocks[] = {64, 2, 2, 2, 2, 4, 4, 0, 0, 0};
   static int WVQsubPCT2_vblocks[] = {64, 2, 2, 4, 4, 4, 4, 0, 0, 0};
   static int WVQsubPCT2_cbsizes[] = {1, 256, 128, 128, 128, 64, 32, 0, 0, 0};
   static int WVQsubPCT2_nvecs[] = {1, 1024, 1024, 512, 2048, 1024, 1048, 0, 0, 0};

   /* T schemes were designed to analyze the performance of different */
   /* implementations of the same bit rate.  For instance, 1bpp rate  */
   /* may be implemented using 2x2 block size, 16 codebook vectors,   */
   /* or it may be implemented using 2x4 block size, 256 codebook     */
   /* vectors.							      */

   /* Function declarations */
   extern int get_info(Image *image, VQ_INFO info);
   extern void get_lbg_scheme(int scheme, int bands, VQ_INFO info);
   extern void encode_data(float **codebook, float **data, int *index, int size, int dim, int nvecs);
   extern void compute_centroid(ELEMENT struc, int size, int dim, int nvecs);
   extern int LBG_error(int size, int dim, ELEMENT struc, float **codebook, int first, int nvecs);
   extern void block_to_vec(float **rptr, float *p, int rn, int cn, int vs, int hs);
   extern void vec_to_block(float **rptr, float *p, int rn, int cn, int vs, int hs);
   extern void do_decoding(Image *image, VQ_INFO info);
   extern char *save_codebook(Image *image, VQ_INFO info);
   extern char *save_cdbook(Image *image, VQ_INFO info, char *codebook);
   extern CVIP_BOOLEAN load_lbg_book(VQ_INFO info, char *name);
   extern void lbg_save(Image *image, VQ_INFO info, char *name);
   extern Image *lbg_decompress(VQ_INFO info, char *filename);
   extern float findminval_Matrix(unsigned rows, unsigned cols, float **rptr);
   extern float findmaxval_Matrix(unsigned rows, unsigned cols, float **rptr);
   extern void downsample(Image *image);
   extern void reconstruct(Image *image);
   extern void allocate_vectors(Image *image, VQ_INFO info);
   extern void free_info(VQ_INFO info, int bands);
   extern void get_lbg_scheme(int choice, int fbands, VQ_INFO info);



#endif
