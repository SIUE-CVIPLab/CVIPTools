/***************************************************************************
* =========================================================================
*
*   Computer Vision and Image Processing Lab - Dr. Scott Umbaugh SIUE 
* 
* =========================================================================
*
*             File Name: adaptive_anisotropic_diffusion.c 
*            Name: Serkan Kefel  
*            Portability: Standard (ANSI) C*                         
**      Copyright (c) 2009, SIUE - Scott Umbaugh
****************************************************************************/

/****************************************************************************/

/*
** include header files
*/

#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPimage.h"

#include <math.h>

Image *param_ad_filter(Image *inputImage, int iteration_num, int speed, int edge_height, int blk_size);

Image* adaptive_ad_setup(Image *cvipImage){ 
   int iteration_num, speed, edge_height, blk_size; 
   printf(" **********  THE ADAPTIVE ANISOTROPIC DIFFUSION FILTER  **********\n");          
   do{ 
	printf("\nType in an integer value between 1 and 1000 for number of iterations"); 
	scanf("%d",&iteration_num);  
	if(iteration_num > 0 && iteration_num < 1000) break; 
	else printf("\nInvalid Selection !!!!!  Try Again !!!!!\n");  
   }while(1); 
 
   do{ 
	printf("\nType in an integer value for smoothing per iteration:"); 
	scanf("%d",&speed); 
	if(speed > 0) break; 
	else printf("\nInvalid Selection !!!!!  Try Again !!!!!\n"); 
   }while(1);

   do{ 
	printf("\nType in an integer value for edge thresholding:"); 
	scanf("%d",&edge_height); 
	if(edge_height > 0 && edge_height < 50) break; 
	else printf("\nInvalid Selection !!!!!  Try Again !!!!!\n"); 
   }while(1);

   do{ 
	printf("\nType in an integer value (must be a power of 2) for block size:"); 
	scanf("%d",&blk_size); 
	if(blk_size == 8) break;
	if(blk_size == 16) break;
	if(blk_size == 32) break;
	if(blk_size == 64) break;
	if(blk_size == 128) break;
	else printf("\nInvalid Selection !!!!!  Try Again !!!!!\n"); 
   }while(1);

   return param_ad_filter(cvipImage, iteration_num, speed, edge_height, blk_size); 
}

typedef struct block
{
	int col_id, row_id;
	float pix_min, pix_max;
	float contrast_measure;
	float average;
	float stddev;
}BLOCK;

void sortBlocks (BLOCK *b, int block_num)
{
	int i, j;
	BLOCK temp;
	for (i = 0; i < block_num; i++)
	{
		for (j = 0; j < block_num; j++)
		{
			if (b[i].stddev > b[j].stddev)
			{
				temp = b[i];
				b[i] = b[j];
				b[j] = temp;
			}
		}
	}
}

Image *param_ad_filter(Image *inputImage, int iteration_num, int speed, int edge_height, int blk_size)
{
	//input parameters
	int nb_iter       = iteration_num; //200;    // Number of iterations
	int nb_smoothings = speed; //1;     // Number of smoothings per iteration
	double dt         = 20.0;  // Adapting time step
	float a1          = 0.5f;  // Diffusion limiter along minimal variations
	float a2          = 0.9f;  // Diffusion limiter along maximal variations
	int save          = 20;    // Iteration saving step
	float edgeheight  = edge_height; //5;     // edge threshold
	int BLOCK_SIZE = blk_size; //Block Size

	float 		**imagef; 	/* 2-d matrix data pointer */
	byte 		**imageb; 	/* 2-d matrix data pointer */
    unsigned int r,		/* row index */
				col, 		/* column index */
				bands;		/* band index */
	unsigned int no_of_rows,	/* number of rows in image */
				no_of_cols,	/* number of columns in image */
				no_of_bands;	/* number of image bands */

	const float c1 = (float)(0.25*(2-sqrt(2.0)));
	const float c2 = (float)(0.5f*(sqrt(2.0)-1));

	float pix_max, pix_min, cur_pix;
	double average, stddev, drange, drange0, drange2;
	int iteration, sit;
	int i, j, k, x, y;

	int px, nx, py, ny;
	float ixx, ixy, iyy;
	float Ipp,Icp,Inp=0,Ipc,Icc,Inc=0,Ipn,Icn,Inn=0;
	float IppInn, IpnInp;
	float fx, fy;
	double a, b, c, d, e, f, l1, l2;
	float val1, val2, vec1, vec2, vec11, vec12, vec22;
	float f1, f2;
	double u, v, n;
	float max, min;
	double ipfnew;
	double xdt;

	float ***ipf;
	float ****grad;
	float ***G;
	float ***T;
	float ***veloc;

	int no_of_blocks;
	int block_row;
	int block_col;
	int row_counter;
	int col_counter;
	BLOCK *im_blocks;
	int block_id[3]; // to find the 3 blocks with having lowest stddev
	float stddevmin1, stddevmin2, stddevmin3;

	/*
    ** Gets the number of image bands (planes)
    */
    no_of_bands = getNoOfBands_Image(inputImage);

    /* 
    ** Gets the number of rows in the input image  
    */
    no_of_rows =  getNoOfRows_Image(inputImage);

    /* 
    ** Gets the number of columns in the input image  
    */
    no_of_cols =  getNoOfCols_Image(inputImage);

	ipf = (float *)malloc(no_of_rows * sizeof(*ipf));
	for(i = 0; i < no_of_rows; i++)
	{
		ipf[i] = (float *)malloc(no_of_cols * sizeof(**ipf));
		for(j = 0; j < no_of_cols; j++)
			ipf[i][j] = (float *)malloc(no_of_bands * sizeof(***ipf));
	}
	grad = (float *)malloc(2 * sizeof(*grad));
	for(i = 0; i < 2; i++)
	{
		grad[i] = (float *)malloc(no_of_rows * sizeof(**grad));
		for(j = 0; j < no_of_rows; j++)
		{
			grad[i][j] = (float *)malloc(no_of_cols * sizeof(***grad));
			for(k = 0; k < no_of_cols; k++)
				grad[i][j][k] = (float *)malloc(no_of_bands * sizeof(****grad));
		}
	}
	T = (float *)malloc(no_of_rows * sizeof(*T));
	for(i = 0; i < no_of_rows; i++)
	{
		T[i] = (float *)malloc(no_of_cols * sizeof(**T));
		for(j = 0; j < no_of_cols; j++)
			T[i][j] = (float *)malloc(3 * sizeof(***T));
	}
	veloc = (float *)malloc(no_of_rows * sizeof(*veloc));
	for(i = 0; i < no_of_rows; i++)
	{
		veloc[i] = (float *)malloc(no_of_cols * sizeof(**veloc));
		for(j = 0; j < no_of_cols; j++)
			veloc[i][j] = (float *)malloc(no_of_bands * sizeof(***veloc));
	}
	G = (float ***)malloc(no_of_rows * sizeof(float***));
	for(i = 0; i < no_of_rows; i++)
	{
		G[i] = (float **)malloc(no_of_cols * sizeof(float**));
		for(j = 0; j < no_of_cols; j++)
			G[i][j] = (float *)malloc(3 * sizeof(float*));
	}

	/* BLOCK INITIALIZATION */
	if (no_of_cols % BLOCK_SIZE == 0)
	{
		if (no_of_rows % BLOCK_SIZE == 0)
		{
			block_col = no_of_cols / BLOCK_SIZE;
			block_row = no_of_rows / BLOCK_SIZE;
			no_of_blocks = (no_of_cols / BLOCK_SIZE)*(no_of_rows / BLOCK_SIZE);
		}
		else
		{
			block_col = no_of_cols / BLOCK_SIZE;
			block_row = no_of_rows / BLOCK_SIZE + 1;
			no_of_blocks = (no_of_cols / BLOCK_SIZE)*(no_of_rows / BLOCK_SIZE + 1);
		}
	}
	else
	{
		if (no_of_rows % BLOCK_SIZE == 0)
		{
			block_col = no_of_cols / BLOCK_SIZE + 1;
			block_row = no_of_rows / BLOCK_SIZE;
			no_of_blocks = (no_of_cols / BLOCK_SIZE + 1)*(no_of_rows / BLOCK_SIZE);
		}
		else
		{
			block_col = no_of_cols / BLOCK_SIZE + 1;
			block_row = no_of_rows / BLOCK_SIZE + 1;
			no_of_blocks = (no_of_cols / BLOCK_SIZE + 1)*(no_of_rows / BLOCK_SIZE + 1);
		}
	}
	im_blocks = (BLOCK *)malloc(no_of_bands * no_of_blocks * sizeof(BLOCK));

	row_counter = 0;
	col_counter = 0;
	for (i = 0; i < no_of_blocks; i++)
	{
		im_blocks[i].average = im_blocks[i].stddev = im_blocks[i].contrast_measure = 0;
		im_blocks[i].pix_max = -1;
		im_blocks[i].pix_min = 256;
		im_blocks[i].col_id = col_counter * BLOCK_SIZE;
		im_blocks[i].row_id = row_counter * BLOCK_SIZE;
		col_counter++;
		if (col_counter % block_col == 0)
		{
			col_counter = 0;
			row_counter++;
		}
	}
	/************************/

	if(inputImage->bandP[0]->data_type != CVIP_BYTE )
	{
		if(inputImage->bandP[0]->data_type != CVIP_FLOAT && cast_Image(inputImage,CVIP_FLOAT))
		{
			fprintf(stderr,"Image is cast into float \n");
		}
		else if(inputImage->bandP[0]->data_type != CVIP_FLOAT )
		{
			fprintf(stderr,"cast_Image failed..\n");
			delete_Image(inputImage);
			return NULL;
		}

		//get image data
		for(bands=0; bands < no_of_bands; bands++)
		{
			imagef = (float **)getData_Image(inputImage, bands);
			for(r = 0; r < no_of_rows; r++)
				for(col = 0; col < no_of_cols; col++)
					ipf[r][col][bands] = imagef[r][col];
		}

		//iteration loop
		for(iteration = 0; iteration < nb_iter; iteration ++)
		{
			//gets initial stats for later normalizing
			/* BLOCK OPERATIONS */
			col_counter = 0;
			row_counter = 0;
			pix_max = pix_min = ipf[0][0][0];
			for (i = 0; i < no_of_blocks; i++)
			{
				im_blocks[i].average = im_blocks[i].stddev = im_blocks[i].contrast_measure = 0;
				im_blocks[i].pix_max = -1;
				im_blocks[i].pix_min = 256;
				im_blocks[i].col_id = col_counter * BLOCK_SIZE;
				im_blocks[i].row_id = row_counter * BLOCK_SIZE;
				col_counter++;
				if (col_counter % block_col == 0)
				{
					col_counter = 0;
					row_counter++;
				}
			}

			for (i = 0; i < no_of_blocks; i++)
			{
				for (bands = 0; bands < no_of_bands; bands++)
				{
					for (r = im_blocks[i].row_id; r < im_blocks[i].row_id + BLOCK_SIZE && r < no_of_rows; r++)
					{
						for (col = im_blocks[i].col_id; col < im_blocks[i].col_id + BLOCK_SIZE && col < no_of_cols; col++)
						{
							cur_pix = ipf[r][col][bands];
							if (cur_pix > im_blocks[i].pix_max) //local calculation
								im_blocks[i].pix_max = cur_pix;
							if (cur_pix < im_blocks[i].pix_min) //local calculation
								im_blocks[i].pix_min = cur_pix;
							if (cur_pix > pix_max) //global calculation 
								pix_max = cur_pix;
							if (cur_pix < pix_min) //global calculation
								pix_min = cur_pix;
							im_blocks[i].average += cur_pix;
						}
					}
				}
				im_blocks[i].average /= BLOCK_SIZE * BLOCK_SIZE * no_of_bands;
			}

			for (i = 0; i < no_of_blocks; i++)
			{
				for (bands = 0; bands < no_of_bands; bands++)
				{
					for (r = im_blocks[i].row_id; r < im_blocks[i].row_id + BLOCK_SIZE && r < no_of_rows; r++)
					{
						for (col = im_blocks[i].col_id; col < im_blocks[i].col_id + BLOCK_SIZE && col < no_of_cols; col++)
						{
							cur_pix = ipf[r][col][bands];
							im_blocks[i].stddev += (cur_pix - im_blocks[i].average)*(cur_pix - im_blocks[i].average);
						}
					}
				}
				im_blocks[i].stddev = sqrt(im_blocks[i].stddev / (BLOCK_SIZE * BLOCK_SIZE * no_of_bands));
			}

			sortBlocks(im_blocks, no_of_blocks);
			stddev = (im_blocks[0].stddev + im_blocks[1].stddev + im_blocks[2].stddev) / 3;
			/********************/

			//normalization
			drange = (edgeheight * stddev) / 256.0;
			drange0 = (6*stddev) / 256.0;
			drange2 = drange * drange;

			//compute gradients
			for(x = no_of_rows; x-- > 0;) 
			{
				px = x-1; 
				if(px < 0) 
					px = 0;
				nx = x+1; 
				if(nx == no_of_rows) 
					nx--;
				for(y = no_of_cols; y-- > 0;) 
				{
					py = y-1; 
					if(py < 0) 
						py = 0;
					ny = y+1; 
					if(ny == no_of_cols) 
						ny--;
					for(k = no_of_bands; k-- > 0;) 
					{
						Ipp = ipf[px][py][k];
						Ipc = ipf[px][y] [k];
						Ipn = ipf[px][ny][k];
						Icp = ipf[x] [py][k];
						Icn = ipf[x] [ny][k];
						Inp = ipf[nx][py][k];
						Inc = ipf[nx][y] [k];
						Inn = ipf[nx][ny][k];
						IppInn = c1 * (Inn - Ipp);
						IpnInp = c1 * (Ipn - Inp);
						grad[0][x][y][k] = (float)(IppInn - IpnInp - c2 * Ipc + c2 * Inc);
						grad[1][x][y][k] = (float)(IppInn + IpnInp - c2 * Icp + c2 * Icn);
					}
				}
			}

			//compute structure tensor field G
			for(x = no_of_rows; x-- > 0;)
			{
				for(y = no_of_cols; y-- > 0;) 
				{
					G[x][y][0] = 0.0f;
					G[x][y][1] = 0.0f;
					G[x][y][2] = 0.0f;
					for(k = no_of_bands; k-- > 0;) 
					{
					//normalization
						fx = grad[0][x][y][k];
						fy = grad[1][x][y][k];
						G[x][y][0] += fx * fx;
						G[x][y][1] += fx * fy;
						G[x][y][2] += fy * fy;
					}
				}
			}
			//compute the tensor field T, used to drive the diffusion
			for(x = no_of_rows; x-- > 0;)
			{
				for(y = no_of_cols; y-- > 0;) 
				{
					//eigenvalues:
					a = G[x][y][0];
					b = G[x][y][1]; 
					c = G[x][y][1]; 
					d = G[x][y][2];
					e = a + d;
					f = sqrt(e * e - 4 * (a * d - b * c));
					l1 = 0.5 * (e - f);
					l2 = 0.5 * ( e + f );
					//more precise computing of quadratic equation
					if(e > 0) 
					{ 
						if(l1 != 0) 
							l2 = (a * d - b * c) / l1; 
					}
					else     
					{ 
						if(l2 != 0) 
							l1 = (a * d - b * c) / l2; 
					}


					val1 = (float)(l2 / drange2);
					val2 = (float)(l1 / drange2);
					// slight cheat speedup for default a1 value
					f1 = (a1 == 0.5) ? (float)(1 / sqrt(1.0f + val1 + val2)) : (float)(pow(1.0f + val1 + val2, -a1));
					f2 = (float)(pow(1.0f + val1 + val2, -a2));

					// eigenvectors:
					if(abs(b) > abs(a - l1)) 
					{ 
						u = 1; 
						v = (l1 - a) / b; 
					}
					else 
					{ 
						if(a - l1 != 0) 
						{ 
							u = -b / (a - l1);
							v = 1;
						} 
						else 
						{ 
							u = 1;
							v = 0;
						} 
					}
					n = sqrt(u * u + v * v);
					u /= n;
					v /= n; 
					vec1 = (float)u;
					vec2 = (float)v;
					vec11 = vec1 * vec1;
					vec12 = vec1 * vec2;
					vec22 = vec2 * vec2;
					T[x][y][0] = f1 * vec11 + f2 * vec22;
					T[x][y][1] = (f1 - f2) * vec12;
					T[x][y][2] = f1 * vec22 + f2 * vec11;
				}
			}

			xdt= 0.0;

			//multiple smoothings per iteration
			for(sit=0; sit < nb_smoothings; sit++)
			{
				//compute the PDE velocity and update the iterated image
				Inp=Inc=Inn=0;
				for(x = no_of_rows; x-- > 0;) 
				{
					px = x - 1; 
					if(px < 0) 
						px = 0;
					nx = x + 1;
					if(nx == no_of_rows)
						nx--;
					for(y = no_of_cols; y-- > 0;) 
					{
						py = y - 1; 
						if(py < 0)
							py = 0;
						ny = y + 1; 
						if(ny == no_of_cols)
							ny--;
						for(k = no_of_bands; k-- > 0;) 
						{
							Ipp=ipf[px][py][k];
							Ipc=ipf[px][y] [k];
							Ipn=ipf[px][ny][k];
							Icp=ipf[x] [py][k];
							Icc=ipf[x] [y] [k];
							Icn=ipf[x] [ny][k];
							Inp=ipf[nx][py][k];
							Inc=ipf[nx][y] [k];
							Inn=ipf[nx][ny][k];
							ixx = Inc + Ipc - 2 * Icc;
							iyy = Icn + Icp - 2 * Icc;
							ixy = 0.5f * (Ipp + Inn - Ipn - Inp);
							veloc[x][y][k] = T[x][y][0] * ixx + T[x][y][1] * ixy + T[x][y][2] * iyy; 
						}
					}
				}

				//find xdt coefficient
				if (dt > 0) 
				{
					max = veloc[0][0][0];
					min = veloc[0][0][0];
					for(x = no_of_rows; x-- > 0;)
						for(y = no_of_cols; y-- > 0;)
							for(k = no_of_bands; k-- > 0;) 
							{
								if(veloc[x][y][k] > max)
									max=veloc[x][y][k];
								if (veloc[x][y][k] < min)
									min=veloc[x][y][k];
							}
					//normalization
					xdt = dt / max(abs(max), abs(min)) * drange0;
				} 
				else 
					xdt = -dt;

				//update image
				for(x = no_of_rows; x-- > 0;)
					for(y = no_of_cols; y-- > 0;)
						for(k = no_of_bands; k-- > 0;) 
						{
							ipfnew = ipf[x][y][k] + veloc[x][y][k] * xdt;
							ipf[x][y][k] = (float)ipfnew;
							// normalize image to the original range
							if (ipf[x][y][k] < pix_min) 
								ipf[x][y][k] = pix_min;
							if (ipf[x][y][k] > pix_max) 
								ipf[x][y][k] = pix_max;
						}
			}

			
			//set image data
			for(bands=0; bands < no_of_bands; bands++)
			{
				imagef = (float **)getData_Image(inputImage, bands);
				for(r = 0; r < no_of_rows; r++)
					for(col = 0; col < no_of_cols; col++)
						imagef[r][col] = (float)ipf[r][col][bands];
			}
		}
	}
	else
	{
		//get image data
		for(bands=0; bands < no_of_bands; bands++)
		{
			imageb = (byte **)getData_Image(inputImage, bands);
			for(r = 0; r < no_of_rows; r++)
				for(col = 0; col < no_of_cols; col++)
					ipf[r][col][bands] = imageb[r][col];
		}

		//iteration loop
		for(iteration = 0; iteration < nb_iter; iteration ++)
		{
			//gets initial stats for later normalizing
			/* BLOCK OPERATIONS */
			col_counter = 0;
			row_counter = 0;
			pix_max = pix_min = ipf[0][0][0];
			for (i = 0; i < no_of_blocks; i++)
			{
				im_blocks[i].average = im_blocks[i].stddev = im_blocks[i].contrast_measure = 0;
				im_blocks[i].pix_max = -1;
				im_blocks[i].pix_min = 256;
				im_blocks[i].col_id = col_counter * BLOCK_SIZE;
				im_blocks[i].row_id = row_counter * BLOCK_SIZE;
				col_counter++;
				if (col_counter % block_col == 0)
				{
					col_counter = 0;
					row_counter++;
				}
			}

			for (i = 0; i < no_of_blocks; i++)
			{
				for (bands = 0; bands < no_of_bands; bands++)
				{
					for (r = im_blocks[i].row_id; r < im_blocks[i].row_id + BLOCK_SIZE && r < no_of_rows; r++)
					{
						for (col = im_blocks[i].col_id; col < im_blocks[i].col_id + BLOCK_SIZE && col < no_of_cols; col++)
						{
							cur_pix = ipf[r][col][bands];
							if (cur_pix > im_blocks[i].pix_max) //local calculation
								im_blocks[i].pix_max = cur_pix;
							if (cur_pix < im_blocks[i].pix_min) //local calculation
								im_blocks[i].pix_min = cur_pix;
							if (cur_pix > pix_max) //global calculation 
								pix_max = cur_pix;
							if (cur_pix < pix_min) //global calculation
								pix_min = cur_pix;
							im_blocks[i].average += cur_pix;
						}
					}
				}
				im_blocks[i].average /= BLOCK_SIZE * BLOCK_SIZE * no_of_bands;
			}

			for (i = 0; i < no_of_blocks; i++)
			{
				for (bands = 0; bands < no_of_bands; bands++)
				{
					for (r = im_blocks[i].row_id; r < im_blocks[i].row_id + BLOCK_SIZE && r < no_of_rows; r++)
					{
						for (col = im_blocks[i].col_id; col < im_blocks[i].col_id + BLOCK_SIZE && col < no_of_cols; col++)
						{
							cur_pix = ipf[r][col][bands];
							im_blocks[i].stddev += (cur_pix - im_blocks[i].average)*(cur_pix - im_blocks[i].average);
						}
					}
				}
				im_blocks[i].stddev = sqrt(im_blocks[i].stddev / (BLOCK_SIZE * BLOCK_SIZE * no_of_bands));
			}

			sortBlocks(im_blocks, no_of_blocks);
			stddev = (im_blocks[0].stddev + im_blocks[1].stddev + im_blocks[2].stddev) / 3;
			/********************/

			//normalization
			drange = (edgeheight * stddev) / 256.0;
			drange0 = (6*stddev) / 256.0;
			drange2 = drange * drange;

			//compute gradients
			for(x = no_of_rows; x-- > 0;) 
			{
				px = x-1; 
				if(px < 0) 
					px = 0;
				nx = x+1; 
				if(nx == no_of_rows) 
					nx--;
				for(y = no_of_cols; y-- > 0;) 
				{
					py = y-1; 
					if(py < 0) 
						py = 0;
					ny = y+1; 
					if(ny == no_of_cols) 
						ny--;
					for(k = no_of_bands; k-- > 0;) 
					{
						Ipp = ipf[px][py][k];
						Ipc = ipf[px][y] [k];
						Ipn = ipf[px][ny][k];
						Icp = ipf[x] [py][k];
						Icn = ipf[x] [ny][k];
						Inp = ipf[nx][py][k];
						Inc = ipf[nx][y] [k];
						Inn = ipf[nx][ny][k];
						IppInn = c1 * (Inn - Ipp);
						IpnInp = c1 * (Ipn - Inp);
						grad[0][x][y][k] = (float)(IppInn - IpnInp - c2 * Ipc + c2 * Inc);
						grad[1][x][y][k] = (float)(IppInn + IpnInp - c2 * Icp + c2 * Icn);
					}
				}
			}

			//compute structure tensor field G
			for(x = no_of_rows; x-- > 0;)
			{
				for(y = no_of_cols; y-- > 0;) 
				{
					G[x][y][0] = 0.0f;
					G[x][y][1] = 0.0f;
					G[x][y][2] = 0.0f;
					for(k = no_of_bands; k-- > 0;) 
					{
					//normalization
						fx = grad[0][x][y][k];
						fy = grad[1][x][y][k];
						G[x][y][0] += fx * fx;
						G[x][y][1] += fx * fy;
						G[x][y][2] += fy * fy;
					}
				}
			}
			//compute the tensor field T, used to drive the diffusion
			for(x = no_of_rows; x-- > 0;)
			{
				for(y = no_of_cols; y-- > 0;) 
				{
					//eigenvalues:
					a = G[x][y][0];
					b = G[x][y][1]; 
					c = G[x][y][1]; 
					d = G[x][y][2];
					e = a + d;
					f = sqrt(e * e - 4 * (a * d - b * c));
					l1 = 0.5 * (e - f);
					l2 = 0.5 * ( e + f );
					//more precise computing of quadratic equation
					if(e > 0) 
					{ 
						if(l1 != 0) 
							l2 = (a * d - b * c) / l1; 
					}
					else     
					{ 
						if(l2 != 0) 
							l1 = (a * d - b * c) / l2; 
					}


					val1 = (float)(l2 / drange2);
					val2 = (float)(l1 / drange2);
					// slight cheat speedup for default a1 value
					f1 = (a1 == 0.5) ? (float)(1 / sqrt(1.0f + val1 + val2)) : (float)(pow(1.0f + val1 + val2, -a1));
					f2 = (float)(pow(1.0f + val1 + val2, -a2));

					// eigenvectors:
					if(abs(b) > abs(a - l1)) 
					{ 
						u = 1; 
						v = (l1 - a) / b; 
					}
					else 
					{ 
						if(a - l1 != 0) 
						{ 
							u = -b / (a - l1);
							v = 1;
						} 
						else 
						{ 
							u = 1;
							v = 0;
						} 
					}
					n = sqrt(u * u + v * v);
					u /= n;
					v /= n; 
					vec1 = (float)u;
					vec2 = (float)v;
					vec11 = vec1 * vec1;
					vec12 = vec1 * vec2;
					vec22 = vec2 * vec2;
					T[x][y][0] = f1 * vec11 + f2 * vec22;
					T[x][y][1] = (f1 - f2) * vec12;
					T[x][y][2] = f1 * vec22 + f2 * vec11;
				}
			}

			xdt= 0.0;

			//multiple smoothings per iteration
			for(sit=0; sit < nb_smoothings; sit++)
			{
				//compute the PDE velocity and update the iterated image
				Inp=Inc=Inn=0;
				for(x = no_of_rows; x-- > 0;) 
				{
					px = x - 1; 
					if(px < 0) 
						px = 0;
					nx = x + 1;
					if(nx == no_of_rows)
						nx--;
					for(y = no_of_cols; y-- > 0;) 
					{
						py = y - 1; 
						if(py < 0)
							py = 0;
						ny = y + 1; 
						if(ny == no_of_cols)
							ny--;
						for(k = no_of_bands; k-- > 0;) 
						{
							Ipp=ipf[px][py][k];
							Ipc=ipf[px][y] [k];
							Ipn=ipf[px][ny][k];
							Icp=ipf[x] [py][k];
							Icc=ipf[x] [y] [k];
							Icn=ipf[x] [ny][k];
							Inp=ipf[nx][py][k];
							Inc=ipf[nx][y] [k];
							Inn=ipf[nx][ny][k];
							ixx = Inc + Ipc - 2 * Icc;
							iyy = Icn + Icp - 2 * Icc;
							ixy = 0.5f * (Ipp + Inn - Ipn - Inp);
							veloc[x][y][k] = T[x][y][0] * ixx + T[x][y][1] * ixy + T[x][y][2] * iyy; 
						}
					}
				}

				//find xdt coefficient
				if (dt > 0) 
				{
					max = veloc[0][0][0];
					min = veloc[0][0][0];
					for(x = no_of_rows; x-- > 0;)
						for(y = no_of_cols; y-- > 0;)
							for(k = no_of_bands; k-- > 0;) 
							{
								if(veloc[x][y][k] > max)
									max=veloc[x][y][k];
								if (veloc[x][y][k] < min)
									min=veloc[x][y][k];
							}
					//normalization
					xdt = dt / max(abs(max), abs(min)) * drange0;
				} 
				else 
					xdt = -dt;

				//update image
				for(x = no_of_rows; x-- > 0;)
					for(y = no_of_cols; y-- > 0;)
						for(k = no_of_bands; k-- > 0;) 
						{
							ipfnew = ipf[x][y][k] + veloc[x][y][k] * xdt;
							ipf[x][y][k] = (float)ipfnew;
							// normalize image to the original range
							if (ipf[x][y][k] < pix_min) 
								ipf[x][y][k] = pix_min;
							if (ipf[x][y][k] > pix_max) 
								ipf[x][y][k] = pix_max;
						}
			}

			
			//set image data
			for(bands=0; bands < no_of_bands; bands++)
			{
				imageb = (byte **)getData_Image(inputImage, bands);
				for(r = 0; r < no_of_rows; r++)
					for(col = 0; col < no_of_cols; col++)
						imageb[r][col] = (byte)ipf[r][col][bands];
			}
		}
	}
	for(i = no_of_rows - 1; i > 0; i--)
	{
		for(j = no_of_cols - 1; j > 0; j--)
			free(G[i][j]);
		free(G[i]);
	}
	free(G);
	for(i = no_of_rows - 1; i > 0; i--)
	{
		for(j = no_of_cols - 1; j > 0; j--)
			free(ipf[i][j]);
		free(ipf[i]);
	}
	free(ipf);
	for(i = no_of_rows - 1; i > 0; i--)
	{
		for(j = no_of_cols - 1; j > 0; j--)
			free(T[i][j]);
		free(T[i]);
	}
	free(T);
	for(i = no_of_rows - 1; i > 0; i--)
	{
		for(j = no_of_cols - 1; j > 0; j--)
			free(veloc[i][j]);
		free(veloc[i]);
	}
	free(veloc);
	for(k = 0; k < 2; k++)
	{
		for(i = no_of_rows - 1; i > 0; i--)
		{
			for(j = no_of_cols - 1; j > 0; j--)
				free(grad[k][i][j]);
			free(grad[k][i]);
		}
		free(grad[k]);
	}
	free(grad);
	free(im_blocks);
	return inputImage;
}