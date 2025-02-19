/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: noise.c
*           Description: adds noise to images 
*         Related Files: 
*   Initial Coding Date: Mon Dec  2 20:13:49 CST 1996
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Kun Luo, John Crieghton 
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1996 SIUE - by Scott Umbaugh and Kun Luo.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
****************************************************************************/
/*****************************************************************************
Author: Kun Luo, John Creight
$log:$
*****************************************************************************/
#include "CVIPtoolkit.h"
#include "CVIPdef.h"
#include "CVIPimage.h"
#include "CVIPnoise.h"
#include <math.h>
#include <float.h>

/*we need to declare drand48 by ourselves when -Xc option is used*/
#ifndef WIN32
extern double drand48(void);
#endif
/*#ifdef WIN32
double drand481(void);
#endif

#ifdef WIN32
double drand481(void)
{
	double rand1;
	rand1=((double)rand())/32767.0;
	return rand1;
}
#endif*/

Image *gamma_noise_setup(Image *imageP)
	{
	float var;
	int alpha;
 
	printf("Enter variance [typically 100 to 400] : ");
	scanf("%f",&var);
	printf("\nEnter alpha [typically 1 to 6; values > 1.3 are very slow] : ");
	scanf("%d",&alpha);
	printf("\n");
	return gamma_noise(imageP,&var,&alpha);
	}

Image *gamma_noise(Image *imageP,float *var,int *alpha)
	{
	byte *bP;
	int a,pix,x,y,z;
	unsigned bands,rows,cols;
	float theta,noise,pixf,Rx,Ry,A;
	float *fP;
	float fpix;

	bands=getNoOfBands_Image(imageP);
	rows=getNoOfRows_Image(imageP);
	cols=getNoOfCols_Image(imageP);

	A=sqrt((double)*var/(double)*alpha)/2;

/*  if(imageP->bandP[0]->data_type != CVIP_BYTE ){ */
	   if(imageP->bandP[0]->data_type != CVIP_FLOAT && cast_Image(imageP,CVIP_FLOAT)){
		fprintf(stderr,"Image is cast into float \n");
	   } else if(imageP->bandP[0]->data_type != CVIP_FLOAT ){
		fprintf(stderr,"cast_Image failed..\n");
		if (imageP) delete_Image(imageP);
		return (Image *)NULL;
	   }
	   for(z=0;z<bands;z++)
		for(y=0;y<rows;y++)
			{
			fP=(float*)getRow_Image(imageP,y,z);
			for(x=0;x<cols;x++,fP++)
				{
				pixf=0.0;
				for(a=0;a<*alpha;a++)
					{
					noise=sqrt(-2*A*log(1.0-(float)drand48()));
					theta=(float)(drand48() * 6.28318530718 - 3.14159265359);
					Rx=noise*cos(theta);
					Ry=noise*sin(theta);
					noise=Rx*Rx+Ry*Ry;
					pixf=pixf+noise;
					}
				 fpix=*fP+pixf+0.5;
				*fP = fpix;

			       
				}
			}
/*      } else{
	for(z=0;z<bands;z++)
		for(y=0;y<rows;y++)
			{
			bP=(byte*)getRow_Image(imageP,y,z);
			for(x=0;x<cols;x++,bP++)
				{
				pixf=0.0;
				for(a=0;a<*alpha;a++)
					{
					noise=sqrt(-2*A*log(1.0-(float)drand48()));
					theta=(float)(drand48() * 6.28318530718 - 3.14159265359);
					Rx=noise*cos(theta);
					Ry=noise*sin(theta);
					noise=Rx*Rx+Ry*Ry;
					pixf=pixf+noise;
					}
				 pix=(int)*bP+pixf+0.5;
				*bP=(byte)trunc(pix);

			       
				}
			}
		} */
	return imageP;
}


Image *gaussian_noise_setup(Image *imageP)
	{
	float var,mean;

	printf("\n");
	printf("Enter variance [typically 100 to 400] : ");
	scanf("%f",&var);
	printf("\nEnter mean [mean > 0 will brighten, mean < 0 will darken image] : ");
	scanf("%f",&mean);
	printf("\n");
	return gaussian_noise(imageP,&var,&mean);
	}

Image *gaussian_noise(Image *imageP,float *var,float *mean)
	{
	byte *bP;
	int pix,x,y,z;
	unsigned bands,rows,cols;
	float noise,theta;
	float *fP;
	float fpix;

	bands=getNoOfBands_Image(imageP);
	rows=getNoOfRows_Image(imageP);
	cols=getNoOfCols_Image(imageP);

/*       if(imageP->bandP[0]->data_type != CVIP_BYTE ){ */
	   if(imageP->bandP[0]->data_type != CVIP_FLOAT && cast_Image(imageP,CVIP_FLOAT)){
		fprintf(stderr,"Image is cast into float \n");
	   } else if(imageP->bandP[0]->data_type != CVIP_FLOAT ){
		fprintf(stderr,"cast_Image failed..\n");
		if (imageP) delete_Image(imageP);
		return (Image *)NULL;
	   }
	   for(z=0;z<bands;z++)
		for(y=0;y<rows;y++)
			{
			fP=(float*)getRow_Image(imageP,y,z);
			for(x=0;x<cols;x++,fP++)
				{
				noise=sqrt(-2*(*var)*log(1.0-(float)drand48()));
				theta=(float)(drand48() * 6.28318530718 - 3.14159265359);
				noise=noise*cos(theta);
				noise=noise+(*mean);
				fpix=*fP+noise+0.5;
				*fP=fpix;
				}
			}

/*      }
	else{
	   for(z=0;z<bands;z++)
		for(y=0;y<rows;y++)
			{
			bP=(byte*)getRow_Image(imageP,y,z);
			for(x=0;x<cols;x++,bP++)
				{
				noise=sqrt(-2*(*var)*log(1.0-(float)drand48()));
				theta=(float)(drand48() * 6.28318530718 - 3.14159265359);
				noise=noise*cos(theta);
				noise=noise+(*mean);
				pix=(int)*bP+noise+0.5;
				*bP=(byte)trunc(pix);
				}
			}
		} */
	return imageP;
}


Image *neg_exp_noise_setup(Image *imageP)
	{
	float var;
	printf("Enter variance [typically 100 to 400] : ");
	scanf("%f",&var);
	printf("\n");
	return neg_exp_noise(imageP,&var);
	}

Image *neg_exp_noise(Image *imageP,float *var)
	{
	byte *bP;
	int pix,x,y,z;
	unsigned bands,rows,cols;
	float theta,noise,Rx,Ry,A;
	float *fP;
	float fpix;

bands=getNoOfBands_Image(imageP);
	rows=getNoOfRows_Image(imageP);
	cols=getNoOfCols_Image(imageP);

	A=(float)sqrt(*var)/2;

/*    if(imageP->bandP[0]->data_type != CVIP_BYTE ){ */
	   if(imageP->bandP[0]->data_type != CVIP_FLOAT && cast_Image(imageP,CVIP_FLOAT)){
		fprintf(stderr,"Image is cast into float \n");
	   }
	   else if(imageP->bandP[0]->data_type != CVIP_FLOAT ){
		fprintf(stderr,"cast_Image failed..\n");
		if (imageP) delete_Image(imageP);
		return (Image *)NULL;
	   }
	    for(z=0;z<bands;z++)
		for(y=0;y<rows;y++)
			{
			fP=(float*)getRow_Image(imageP,y,z);
			for(x=0;x<cols;x++,fP++)
				{
				noise=sqrt(-2*A*log(1.0-(float)drand48()));
				theta=(float)(drand48()*6.28318530718-3.14159365359);
				Rx=noise*cos(theta);
				Ry=noise*sin(theta);
				noise=Rx*Rx+Ry*Ry;
				fpix=*fP+noise+0.5;
				*fP=fpix;
				}
			}
/*      }
	else{
	    for(z=0;z<bands;z++)
		for(y=0;y<rows;y++)
			{
			bP=(byte*)getRow_Image(imageP,y,z);
			for(x=0;x<cols;x++,bP++)
				{
				noise=sqrt(-2*A*log(1.0-(float)drand48()));
				theta=(float)(drand48()*6.28318530718-3.14159365359);
				Rx=noise*cos(theta);
				Ry=noise*sin(theta);
				noise=Rx*Rx+Ry*Ry;
				pix=(int)*bP+noise+0.5;
				*bP=(byte)trunc(pix);
				}
			}
		} */
	return imageP;
}

Image *rayleigh_noise_setup(Image *imageP)
	{
	float var;
	printf("Enter variance [typically 100 to 400] : ");
	scanf("%f",&var);
	printf("\n");
	return rayleigh_noise(imageP,&var);
	}

Image *rayleigh_noise(Image *imageP,float *var)
	{
	byte *bP;
	int pix,x,y,z;
	unsigned bands,rows,cols;
	float noise,pixf,A;
	float *fP;
	float fpix;

	bands=getNoOfBands_Image(imageP);
	rows=getNoOfRows_Image(imageP);
	cols=getNoOfCols_Image(imageP);

	A=2.3299*(*var);

/*       if(imageP->bandP[0]->data_type != CVIP_BYTE ){ */
	   if(imageP->bandP[0]->data_type != CVIP_FLOAT && cast_Image(imageP,CVIP_FLOAT)){
		fprintf(stderr,"Image is cast into float \n");
	   }
	   else if(imageP->bandP[0]->data_type != CVIP_FLOAT ){
		fprintf(stderr,"cast_Image failed..\n");
		if (imageP) delete_Image(imageP);
		return (Image *)NULL;
	   }
	    for(z=0;z<bands;z++)
		for(y=0;y<rows;y++)
			{
			fP=(float*)getRow_Image(imageP,y,z);
			for(x=0;x<cols;x++,fP++)
				{
				pixf=0.0;
				noise=sqrt(-2*A*log(1.0-(float)drand48()));
				pixf=pixf+noise;
				fpix=*fP+pixf+0.5;
				*fP=fpix;
				}
			}
/*      }
	else{
	    for(z=0;z<bands;z++)
		for(y=0;y<rows;y++)
			{
			bP=(byte*)getRow_Image(imageP,y,z);
			for(x=0;x<cols;x++,bP++)
				{
				pixf=0.0;
				noise=sqrt(-2*A*log(1.0-(float)drand48()));
				pixf=pixf+noise;
				pix=(int)*bP+pixf+0.5;
				*bP=(byte)trunc(pix);
				}
			}
		} */
	return imageP;
}

Image *speckle_noise_setup(Image *imageP)
	{
	float ps,pp;
	printf("Enter probabililty of high grey levels [typically .01 to .05] : ");
	scanf("%f",&ps);
	printf("\nEnter probability of low grey levels [typically .01 to .05] : ");
	scanf("%f",&pp);
	printf("\n");
	return speckle_noise(imageP,&ps,&pp);
	}

Image *speckle_noise(Image *imageP,float *psalt,float *ppepper)
	{
	byte *bP;
	int x,y,z;
	unsigned bands,rows,cols;
	float p,ps,pp;
	float *fP;
	double      *minP = NULL, *maxP = NULL, min = -1, max = -1;
	void     **imgvecP = NULL;
	CVIP_TYPE dt = getDataType_Image(imageP);


	if(((*psalt + *ppepper) - 1.0) > 0.000001){
		printf("Invalid probability values\n");
		if (imageP) delete_Image(imageP);
		return (Image *)NULL;
	}
	else
		{
		bands=getNoOfBands_Image(imageP);
		rows=getNoOfRows_Image(imageP);
		cols=getNoOfCols_Image(imageP);
		ps = 1 - *psalt;
		pp = *ppepper;
	if (dt == CVIP_BYTE) { min = 0; max = 255; }
/*       if(imageP->bandP[0]->data_type != CVIP_BYTE ){ */
	   if(imageP->bandP[0]->data_type != CVIP_FLOAT && cast_Image(imageP,CVIP_FLOAT)){
		fprintf(stderr,"Image is cast into float \n");
	   }
	   else if(imageP->bandP[0]->data_type != CVIP_FLOAT ){
		fprintf(stderr,"cast_Image failed..\n");
		if (imageP) delete_Image(imageP);
		return (Image *)NULL;
	   }
		if (max < 0) {
			minP  = (double *) malloc(sizeof(double)*bands);
			maxP  = (double *) malloc(sizeof(double)*bands);
			imgvecP = (void **) malloc(sizeof(void *)*bands);
			getBandVector_Image((Image *)imageP, imgvecP);
			for(z=0; z < bands; z++) {
			   minP[z] = findMinVal_Vector(imgvecP[z], (rows*cols), CVIP_FLOAT);
			   maxP[z] = findMaxVal_Vector(imgvecP[z], (rows*cols), CVIP_FLOAT);
			   if (z == 0) {
				min = minP[0]; max = maxP[0];
			   } else {
				min = (min < minP[z]) ? min : minP[z];
				max = (max > maxP[z]) ? max : maxP[z];
			   }
			}
			free(minP); free(maxP);
			free(imgvecP);
		}
		for(z=0;z<bands;z++)
			for(y=0;y<rows;y++)
				{
				fP=(float*)getRow_Image(imageP,y,z);
				for(x=0;x<cols;x++,fP++)
					{
					p=drand48();
					if(p>=ps) {*fP=max;}
					else{
						if(p<pp) *fP=min;
					}
				}
			}
/*      }
	else{
		for(z=0;z<bands;z++)
			for(y=0;y<rows;y++)
				{
				bP=(byte*)getRow_Image(imageP,y,z);
				for(x=0;x<cols;x++,bP++)
					{
					p=drand48();
					if(p>=ps) {*bP=255;}
					else{
						if(p<pp) *bP=0;}
					}
				}
			} */
		}
	return imageP;
}




Image *uniform_noise_setup(Image *imageP)
	{
	float var,mean; 
	printf("Enter variance [typically 100 to 400] : ");
	scanf("%f",&var);
	printf("\nEnter mean [mean > 0 will brighten, mean < 0 will darken image] : ");
	scanf("%f",&mean);
	printf("\n");
	return uniform_noise(imageP,&var,&mean);
	}


Image *uniform_noise(Image *imageP,float *var,float *mean)
	{
	byte *bP;
	int pix,x,y,z;
	unsigned bands,rows,cols;
	float noise;
	float *fP;
	float fpix;
	double temp;
	temp = RAND_MAX;

	bands=getNoOfBands_Image(imageP);
	rows=getNoOfRows_Image(imageP);
	cols=getNoOfCols_Image(imageP);

/*       if(imageP->bandP[0]->data_type != CVIP_BYTE ){ */
	   if(imageP->bandP[0]->data_type != CVIP_FLOAT && cast_Image(imageP,CVIP_FLOAT)){
		fprintf(stderr,"Image is cast into float \n");
	   }
	   else if(imageP->bandP[0]->data_type != CVIP_FLOAT ){
		fprintf(stderr,"cast_Image failed..\n");
		if (imageP) delete_Image(imageP);
		return (Image *)NULL;
	   }
	    for(z=0;z<bands;z++)
		for(y=0;y<rows;y++)
			{
			fP=(float*)getRow_Image(imageP,y,z);
			for(x=0;x<cols;x++,fP++)
				{
				noise=sqrt((double)(*var))*(1.057192E-4*(float)(rand()/temp*32000.0)-1.7320508)+(*mean);

				 fpix=*fP+noise+0.5;
				 *fP=fpix;

				}
			}
/*      }
	else{
	    for(z=0;z<bands;z++)
		for(y=0;y<rows;y++)
			{
			bP=(byte*)getRow_Image(imageP,y,z);
			for(x=0;x<cols;x++,bP++)
				{
				noise=sqrt((double)(*var))*(1.057192E-4*(float)rand()-1.7320508)+(*mean);

				 pix=(int)*bP+noise+0.5;
				*bP=(byte)trunc(pix);

				}
			}
		} */
	return imageP;
}



 
