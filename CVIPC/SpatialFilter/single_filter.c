/***************************************************************************
* **********************************************************************
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* **********************************************************************
*
*             File Name: single_filter.c
*           Description: 
*         Related Files: 
*   Initial Coding Date: Tue Dec 12 11:03:58 CST 1995
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Mark Zuke
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1996 SIUE - by Scott Umbaugh and Mark Zuke.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
* RCS (Revision Control System) Information
* ...Added automatically by RCS 
*
** $Log: single_filter.c,v $
** Revision 1.6  1996/12/30 20:40:56  yawei
** IMAGE ==> Image
**
 * Revision 1.5  1996/12/30  20:38:24  yawei
 * single_filter ==> single_filter_setup
 * single_filter_sep ==> single_filter
 *
 * Revision 1.4  1996/02/02  02:43:51  kluo
 * modify it to fit with cviptcl
 *
 * Revision 1.3  1995/12/13  20:06:17  kluo
 * get the newest code from joseph, add it in
 *
 * Revision 1.2  1995/12/13  20:02:41  mzuke
 * changed prompts to clarify needed entries
 *
 * Revision 1.1  1995/12/12  17:04:23  mzuke
 * Initial revision
 *
*
****************************************************************************/

#include "CVIPimage.h"
#include "CVIPspfltr.h"

Image *single_filter_setup (Image *orig_image)
{ /* 1 */
float sx, sy, rot, beta;
int xcen, ycen, index;
float *h;
int N, choice;

printf("Enter horizontal sizing factor [typically 1] : ");
scanf("%f",&sx);
fflush(stdin);
printf("Enter vertical sizing factor [typically 1] : ");
scanf("%f",&sy);
fflush(stdin);
printf("Enter x-coordinate for new center [typically 0] : ");
scanf("%d",&xcen);
fflush(stdin);
printf("Enter y-coordinate for new center [typically 0] : ");
scanf("%d",&ycen);
fflush(stdin);
printf("Enter value for angle of rotation [typically 0] : ");
scanf("%f",&rot);
fflush(stdin);
printf("Enter value for beta [typically 0.1 to 0.9] : ");
scanf("%f",&beta);
fflush(stdin);


printf("\nHow big is the kernel for the filter(must be an odd number): ");
scanf("%d",&N);
h = (float*)calloc(N*N, sizeof(float));
if(beta!=0)
	{
	printf("\nEnter %dx%d filter mask:\n",N,N);
	for(index=1;index<=N*N;index++)
		{
		printf("h[%d] = ",index);
		scanf("%f",&h[index]);
		fflush(stdin);
		}
	}
else
	for(index=1;index<=9;index++)
		h[index]=0;

printf("\nYou can choose the operation of the filter:\n");
printf("1 - minus, minus\n");
printf("2 - plus, plus\n");
printf("3 - plus, minus\n");
printf("4 - minus, plus\n");
printf("=> ");
scanf("%d",&choice);

orig_image = single_filter(orig_image,sx,sy,xcen, ycen,rot, beta, N,(float*)h, choice);
free(h);
return orig_image;
}

Image *single_filter(Image *orig_image, float sx, float sy, int xcen,
	 int ycen,float rot, float beta, int N, float *h, 
	 int choice){
byte **image;
Image *filtered_image;
float angle;
int no_of_bands, rows, cols, bands;
int xnew, ynew;
int total;
int index,x,y, z, r, u[10], v[10];
float xtran[10], ytran[10], udiff, vdiff;
float ax, by, sum, sum1;
float a, b, c, d, e, f;
float a1,b1,c1,d1,e1,f1;
float qv[10], qu[10];
float udiffmin, vdiffmin;
int prompt;


angle=rot*3.14/180;
a1=cos(angle)/sx;
b1=sin(angle)/sx;
c1=xcen;
d1=-sin(angle)/sy;
e1=cos(angle)/sy;
f1=ycen;

a=sx*cos(angle);
b=-1*sy*sin(angle);
c=-1*sx*cos(angle)*xcen+sy*sin(angle)*ycen;
d=sx*sin(angle);
e=sy*cos(angle);
f=-1*sx*sin(angle)*xcen-sy*cos(angle)*ycen;

ax=(N-1)/(2*sx);
by=(N-1)/(2*sy);


filtered_image = duplicate_Image(orig_image);
no_of_bands = getNoOfBands_Image(orig_image);
rows = getNoOfRows_Image(orig_image);
cols = getNoOfCols_Image(orig_image);

/* Blank new image */
for(bands=0;bands<no_of_bands;bands++)
	{ /* 2 */
	for(y=0;y<rows;y++)
		for(x=0;x<cols;x++)
			setPixel_Image(filtered_image,byte,x,y,bands,0);
	} /* 2 */

printf("\nBeginning scan.......\n\n");
for (bands=0;bands<no_of_bands;bands++)
	{ /* 3 */
	image = getData_Image(orig_image,bands);
	for(y=1;y<rows-1;y++)
/*		for(y=178;y<179;y++)*/
		{ /* 4 */
		for(x=1;x<cols-1;x++)
/*			for(x=157;x<161;x++)*/
			{ /* 5 */
			index=1;
			/* Compute u's, v's, xtran's, & ytran's */
			for(z=-1;z<=1;z++)
				{ /* 6 */
				u[index]=u[index+3]=u[index+6]=a1*(x+z)+b1*(y+z)+c1+0.5;
				v[3*index-2]=v[3*index-1]=v[3*index]=d1*(x+z)+e1*(y+z)+f1+0.5;
				xtran[index]=xtran[index+3]=xtran[index+6]=u[index]*a+v[3*index-2]*b+c;
				ytran[3*index-2]=ytran[3*index-1]=ytran[3*index]=u[index]*d+v[3*index-2]*e+f;
				index++;
				} /* 6 */
			for(z=1;z<=9;z++)
				qu[z]=qv[z]=0;
			/* Compute qv' and qu' */
			udiffmin=vdiffmin=100;
			if((u[5]<cols)&&(v[5]<rows)&&(u[5]>0)&&(v[5]>0))	
				r=image[v[5]][u[5]];
			else
				r=0;
			for(z=1;z<=9;z++)
				{
/*				printf("u[z]=%d, v[z]=%d\n",u[z],v[z]);*/
				if((u[z]<cols)&&(v[z]<rows)&&(u[z]>0)&&(v[z]>0))
					{ /* 7 */
					udiff=xtran[z]-x;
					vdiff=ytran[z]-y;
	/*				printf("udiff=%f, vdiff=%f, z=%d\n",udiff,vdiff,z);*/
/*					printf("beta=%f\n",beta);*/
					if(ax<=0.5)
						{ /* 8 */
						if((udiff>=0.5-ax)&&(udiff<=0.5+ax)) qu[z]=h[z]*(ax+0.5-udiff);
							if((udiff<=0.5-ax)&&(udiff>=ax-0.5)) qu[z]=h[z]*2*ax;
								if((udiff<ax-0.5)&&(udiff>=-0.5-ax)) qu[z]=h[z]*(ax+0.5+udiff);
						} /* 8 */
					else
						{ /* 9 */
						if((udiff<=ax+0.5)&&(udiff>=ax-0.5)) qu[z]=h[z]*(ax+0.5-udiff);
							if((udiff<ax-0.5)&&(udiff>=0.5-ax)) {
								qu[z]=h[z];
	/*							printf("went here\n");
								printf("z=%d\n",z);
								printf("qu[z]=%f\n",qu[z]);*/
							}
								if((udiff<0.5-ax)&&(udiff>=-0.5-ax)) qu[z]=h[z]*(ax+0.5+udiff);
						} /* 9 */	
					if(by<=0.5)   
						{ /* 10 */
           	   	if((vdiff>=0.5-by)&&(vdiff<=0.5+by)) qv[z]=(by+0.5-vdiff);
							if((vdiff<=0.5-by)&&(vdiff>=by-0.5)) qv[z]=2*by; 
                    		if((vdiff<by-0.5)&&(vdiff>=-0.5-by)) qv[z]=(by+0.5+vdiff);
               	} /* 10 */
            	else 
              		{ /* 11 */ 
               	if((vdiff<=by+0.5)&&(vdiff>=by-0.5)) qv[z]=(by+0.5-vdiff); 
                  	if((vdiff<by-0.5)&&(vdiff>=0.5-by)) qv[z]=1; 
                     	if((vdiff<0.5-by)&&(vdiff>=-0.5-by)) qv[z]=(by+0.5+vdiff);
						} /* 11 */
					if(udiff<0) udiff=-1*udiff;
					if(vdiff<0) vdiff=-1*vdiff;
             if((udiff<=0.5)&&(vdiff<=0.5)&&(udiff<udiffmin)&&(vdiff<vdiffmin)&&(image[v[z]][u[z]]!=0))
						{	
						r=image[v[z]][u[z]];
						udiffmin=udiff;
						vdiffmin=vdiff;
						} /* 12 */
					} /* 7 */
				else
					{ /* 13 */ 
					if((u[z]>cols)||(u[z]<0)) qu[z]=0;
					if((v[z]>rows)||(v[z]<0)) qu[z]=0;
					} /* 13 */
/*				printf("ax=%f, by=%f\n",ax,by);*/
				}

	/*		printf("beta=%f\n",beta);*/	
			/* Find matches and eliminate them */
/*			for(z=1;z<=9;z++)
				for(index=z+1;index<=9;index++)
					{ 
					if(qu[z]==qu[index]) qu[index]=0;
					if(qv[z]==qv[index]) qv[index]=0;
					} */

			/* Calculate sum and set pixel */
			sum=0;
			for(z=1;z<=9;z++)
				{
/*				printf("u[z]=%d, v[z]=%d, h[z]=%f, qu[z]=%f, qv[z]=%f, image=%d\n",u[z],v[z],h[z],qu[z],qv[z],(int)image[v[z]][u[z]]);*/
/*				scanf("%d",&prompt);
				fflush(stdin);*/
				if((u[z]<cols)&&(v[z]<rows)&&(u[z]>0)&&(v[z]>0))
					{
					sum=sum+(qu[z])*(qv[z])*(image[v[z]][u[z]]);
			/*		scanf("%d",&prompt);
					fflush(stdin);
					printf("sum=%f\n",sum);*/
					}
				}
/*			printf("x=%d\n",x);*/
/*				printf("sum=%f\n",sum);*/
/*			printf("Finished sum and set pixel!!!!\n");*/
/*			printf("beta=%f, sum=%f, r=%d\n",beta,sum,r);*/
/*			scanf("%d",&prompt);
			fflush(stdin);*/
			sum1=sum;
/*			printf("sum1=%f, r=%d\n",sum1,r);*/
			if (choice==1) sum=-1*(beta*sum1)+((1-beta)*r);
			if (choice==2) sum=(beta*sum1)+((1+beta)*r);
			if (choice==3) sum=(beta*sum1)+((1-beta)*r);
			if (choice==4) sum=-1*(beta*sum1)+((1+beta)*r);
			total=sum;
/*			printf("sum1=%f, beta=%f, sum=%f, total=%d\n",sum1,beta,sum,total);*/
	/*		printf("beta=%f, x=%d, sum=%f\n",beta,x,sum);*/
			if(total>255)
				setPixel_Image(filtered_image,byte,x,y,bands,255);
			else
				if(total<0)
					setPixel_Image(filtered_image,byte,x,y,bands,0);
				else
			    	setPixel_Image(filtered_image,byte,x,y,bands,(byte)total);
			} /* 5 */
		}
	}
fflush(stdin);
free(orig_image);
return filtered_image;
} /* 1 */
	
