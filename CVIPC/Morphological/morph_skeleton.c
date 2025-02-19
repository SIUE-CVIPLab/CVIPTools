

/***************************************************************************
* =========================================================================
*
*   Computer Vision and Image Processing Lab - Dr. Scott Umbaugh SIUE
* 
* =========================================================================
*
*             File Name: morph_skeleton.c 
*           Description: Performs morphological operation
*   Initial Coding Date: Nov 30th 2009
*           Portability: Standard (ANSI) C
*             Credit(s): Mounika Mamidi
*                        Southern Illinois University at Edwardsville
*
** Copyright (c) 1995, 2004, SIUE - Scott Umbaugh, Mounika Mamidi
****************************************************************************/
/*
** include header files
*/
#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPimage.h"
#include "CVIPtyp.h"
#include "CVIPmorph.h"



	/* 
	** Skeleton transform
	*/
	Image* morph_thinning(Image *inputImage, int dimension, char* thinning);

	
	Image* morph_skeleton(Image *inputImage,int filterdimension,char *SkeletonFilter, int iterations, int four_eight_mask, int method)
	{
		Image *skeleton_Image1,*skeleton_Image2,*skeleton_Image3, *temp;
		float **skeletondata,**outputdata;
		unsigned int rows,cols, bands,no_of_bands;
		unsigned int  b, x,y;
		int midpoint=filterdimension/2, mid=0, a=0, dimension=filterdimension-1;
		int i=0,r,c,shift=midpoint;
		//char skeleton_90[150], skeleton_180[150], skeleton_270[150], shift_45[150];
		//char skeleton_135[150],skeleton_225[150],skeleton_315[150],shift45[150],Skeleton_45[150];
		char *skeleton_90,*skeleton_180, *skeleton_270, *shift_45;
		char *skeleton_135,*skeleton_225,*skeleton_315,*shift45,*Skeleton_45;

		no_of_bands = getNoOfBands_Image(inputImage);
		  skeleton_90 = (char *) malloc(sizeof(char)* (filterdimension*filterdimension));
		  skeleton_180 = (char *) malloc(sizeof(char)* (filterdimension*filterdimension));
		  skeleton_270 = (char *) malloc(sizeof(char)* (filterdimension*filterdimension));
		  shift_45 = (char *) malloc(sizeof(char)* (filterdimension*filterdimension));
		  skeleton_135 = (char *) malloc(sizeof(char)* (filterdimension*filterdimension));
		  skeleton_225 = (char *) malloc(sizeof(char)* (filterdimension*filterdimension));
		  skeleton_315 = (char *) malloc(sizeof(char)* (filterdimension*filterdimension));
		  shift45 = (char *) malloc(sizeof(char)* (filterdimension*filterdimension));
		  Skeleton_45 = (char *) malloc(sizeof(char)* (filterdimension*filterdimension));

		cast_Image(inputImage, CVIP_FLOAT);

		bands = getNoOfBands_Image(inputImage);

		rows =  getNoOfRows_Image(inputImage);

		cols =  getNoOfCols_Image(inputImage);
		

			for(y=0,r=0;y<filterdimension,r<filterdimension;y++,r++)
			{      
				//x-column, y-row
				for(x=filterdimension-1,c=0;x>=0,c<filterdimension;x--,c++)
				{
					skeleton_90[x*filterdimension+y]=SkeletonFilter[r*filterdimension+c];
				}
			}
			for(y=filterdimension-1,r=0;y>=0,r<filterdimension;y--,r++)
			{      
				//x-column, y-row
				for(x=filterdimension-1,c=0;x>=0,c<filterdimension;x--,c++)
				{
					skeleton_180[y*filterdimension+x]=skeleton_90[r*filterdimension+c];
				}
			}
			for(y=filterdimension-1,r=0;y>=0,r<filterdimension;y--,r++)
			{      
				//x-column, y-row
				for(x=0,c=0;x<filterdimension,c<filterdimension;x++,c++)
				{
					skeleton_270[x*filterdimension+y]=skeleton_180[r*filterdimension+c];
				}
			}
			//45 degrees move

					while(mid!=midpoint&&dimension!=midpoint)
					{

						r=mid;
						c=mid;
						a=0;
						while(r>=mid&&c<=dimension)
						{
						shift_45[a]=SkeletonFilter[r*filterdimension+c];
						c++;
						a++;
						}
						if(c>dimension&&r<=dimension)
						{
							c--;
							r++;
						}
						while(c>=dimension&&r<=dimension)
						{
						shift_45[a]=SkeletonFilter[r*filterdimension+c];
						r++;
						a++;
						}
						if(r>dimension)
						{c--;
							r--;
						}
						while(r<=dimension&&c>=mid)
						{
						shift_45[a]=SkeletonFilter[r*filterdimension+c];
						c--;
						a++;
						}
						if(c<mid)
						{
							r--;
							c=mid;
						}
						while(c>=mid&&r>mid)
						{
						shift_45[a]=SkeletonFilter[r*filterdimension+c];
						r--;
						a++;
						}	
						x=shift;
						y=0;
						while(!(y>=a))
						{							
							shift45[x]= shift_45[y];
						x++;
							//a--;
							if(x>=a)
							{
								x=0;
							}
							y++;
						}
						r=mid;
						c=mid;
						a=0;

						//shifting matrix						
						while(r>=mid&&c<=dimension)
						{
						Skeleton_45[r*filterdimension+c]=shift45[a];
						c++;
						a++;
						}
						if(c>dimension&&r<=dimension)
						{
							c--;
							r++;
						}
						while(c>=dimension&&r<=dimension)
						{
						Skeleton_45[r*filterdimension+c]=shift45[a];
						r++;
						a++;
						}
						if(r>dimension)
						{c--;
							r--;
						}
						while(r<=dimension&&c>=mid)
						{
						Skeleton_45[r*filterdimension+c]=shift45[a];
						c--;
						a++;
						}
						if(c<mid)
						{
							r--;
							c=mid;
						}
						while(c>=mid&&r>mid)
						{
						Skeleton_45[r*filterdimension+c]=shift45[a];
						r--;
						a++;
						}	

						mid++;
						dimension=dimension-1;
						shift--;
					}

				Skeleton_45[midpoint*filterdimension+midpoint]=SkeletonFilter[midpoint*filterdimension+midpoint];
			
					//135 degrees shift
			for(y=0,r=0;y<filterdimension,r<filterdimension;y++,r++)
			{      
				//x-column, y-row
				for(x=filterdimension-1,c=0;x>=0,c<filterdimension;x--,c++)
				{
					skeleton_135[x*filterdimension+y]=Skeleton_45[r*filterdimension+c];
				}
			}
			//225 degrees shift
			for(y=filterdimension-1,r=0;y>=0,r<filterdimension;y--,r++)
			{      
				//x-column, y-row
				for(x=filterdimension-1,c=0;x>=0,c<filterdimension;x--,c++)
				{
					skeleton_225[y*filterdimension+x]=skeleton_135[r*filterdimension+c];
				}
			}
			//315 degrees shift
			for(y=filterdimension-1,r=0;y>=0,r<filterdimension;y--,r++)
			{      
				//x-column, y-row
				for(x=0,c=0;x<filterdimension,c<filterdimension;x++,c++)
				{
					skeleton_315[x*filterdimension+y]=skeleton_225[r*filterdimension+c];
				}
			}

			skeleton_Image3=duplicate_Image(inputImage);

			switch(method)
			{

			case 0:

			switch(four_eight_mask)
			{
			case 0:
			skeleton_Image1=duplicate_Image(inputImage);
			skeleton_Image2=duplicate_Image(inputImage);
			for(i=0;i<iterations;i++)
			{
			skeleton_Image1=morph_thinning(skeleton_Image3,filterdimension, SkeletonFilter);
			skeleton_Image2=morph_thinning(skeleton_Image3,filterdimension,skeleton_90);
			skeleton_Image2=and_Image(skeleton_Image2,skeleton_Image1);
			skeleton_Image1=morph_thinning(skeleton_Image3,filterdimension, skeleton_180);
			skeleton_Image2=and_Image(skeleton_Image2,skeleton_Image1);
			skeleton_Image1=morph_thinning(skeleton_Image3,filterdimension, skeleton_270);
			skeleton_Image2=and_Image(skeleton_Image2,skeleton_Image1);
			skeleton_Image3=duplicate_Image(skeleton_Image2);

			}

			delete_Image(skeleton_Image2);
				break;

			//case 1:
			//skeleton_Image1=duplicate_Image(inputImage);
			//skeleton_Image2=duplicate_Image(inputImage);
			//for(i=0;i<iterations;i++)
			//{
			//skeleton_Image1=morph_thinning(skeleton_Image3,filterdimension, SkeletonFilter);
			//skeleton_Image2=morph_thinning(skeleton_Image3,filterdimension,skeleton_90);
			//skeleton_Image2=and_Image(skeleton_Image2,skeleton_Image1);
			//skeleton_Image1=morph_thinning(skeleton_Image3,filterdimension, skeleton_180);
			//skeleton_Image2=and_Image(skeleton_Image2,skeleton_Image1);
			//skeleton_Image1=morph_thinning(skeleton_Image3,filterdimension, skeleton_270);
			//skeleton_Image2=and_Image(skeleton_Image2,skeleton_Image1);
			//skeleton_Image3=duplicate_Image(skeleton_Image2);

			//}

			//delete_Image(skeleton_Image2);
			//	break;

			case 1:
			skeleton_Image1=duplicate_Image(inputImage);
			skeleton_Image2=duplicate_Image(inputImage);

			for(i=0;i<iterations;i++)
			{
			skeleton_Image1=morph_thinning(skeleton_Image3,filterdimension, SkeletonFilter);
			skeleton_Image2=morph_thinning(skeleton_Image3,filterdimension,skeleton_90);
			skeleton_Image2=and_Image(skeleton_Image2,skeleton_Image1);
			skeleton_Image1=morph_thinning(skeleton_Image3,filterdimension, skeleton_180);
			skeleton_Image2=and_Image(skeleton_Image2,skeleton_Image1);
			skeleton_Image1=morph_thinning(skeleton_Image3,filterdimension, skeleton_270);
			skeleton_Image2=and_Image(skeleton_Image2,skeleton_Image1);
			skeleton_Image1=morph_thinning(skeleton_Image3,filterdimension, Skeleton_45);
			skeleton_Image2=and_Image(skeleton_Image2,skeleton_Image1);
			skeleton_Image1=morph_thinning(skeleton_Image3,filterdimension, skeleton_135);
			skeleton_Image2=and_Image(skeleton_Image2,skeleton_Image1);
			skeleton_Image1=morph_thinning(skeleton_Image3,filterdimension, skeleton_225);
			skeleton_Image2=and_Image(skeleton_Image2,skeleton_Image1);
			skeleton_Image1=morph_thinning(skeleton_Image3,filterdimension, skeleton_315);
			skeleton_Image2=and_Image(skeleton_Image2,skeleton_Image1);

			skeleton_Image3=duplicate_Image(skeleton_Image2);

			}
			delete_Image(skeleton_Image2);

				break;
			default:
				print_CVIP("Sorry ! You have Entered a wrong choice Enter 0 or 1 to select mask");
			break;
			}
			break;

			case 1:
			switch(four_eight_mask)
			{
			case 0:
			skeleton_Image2=duplicate_Image(inputImage);
			for(i=0;i<iterations;i++)
			{
			skeleton_Image2=morph_thinning(skeleton_Image3,filterdimension, SkeletonFilter);
			delete_Image(skeleton_Image3);
			skeleton_Image3=morph_thinning(skeleton_Image2,filterdimension,skeleton_90);
			delete_Image(skeleton_Image2);
			skeleton_Image2=morph_thinning(skeleton_Image3,filterdimension, skeleton_180);
			delete_Image(skeleton_Image3);
			skeleton_Image3=morph_thinning(skeleton_Image2,filterdimension, skeleton_270);
			delete_Image(skeleton_Image2);

			}

				break;
			case 1:
			skeleton_Image2=duplicate_Image(inputImage);
			for(i=0;i<iterations;i++)
			{
			skeleton_Image2=morph_thinning(skeleton_Image3,filterdimension, SkeletonFilter);
			delete_Image(skeleton_Image3);
			skeleton_Image3=morph_thinning(skeleton_Image2,filterdimension,skeleton_90);
			delete_Image(skeleton_Image2);
			skeleton_Image2=morph_thinning(skeleton_Image3,filterdimension, skeleton_180);
			delete_Image(skeleton_Image3);
			skeleton_Image3=morph_thinning(skeleton_Image2,filterdimension, skeleton_270);
			delete_Image(skeleton_Image2);
			skeleton_Image2=morph_thinning(skeleton_Image3,filterdimension, Skeleton_45);
			delete_Image(skeleton_Image3);
			skeleton_Image3=morph_thinning(skeleton_Image2,filterdimension,skeleton_135);
			delete_Image(skeleton_Image2);
			skeleton_Image2=morph_thinning(skeleton_Image3,filterdimension, skeleton_225);
			delete_Image(skeleton_Image3);
			skeleton_Image3=morph_thinning(skeleton_Image2,filterdimension, skeleton_315);
			delete_Image(skeleton_Image2);
			}

				break;
			default:
				print_CVIP("Sorry ! You have Entered a wrong choice Enter 0 or 1 to select mask");
			break;			
			}
			break;

			default:
				print_CVIP("Sorry ! You have Entered a wrong choice Enter 0 or 1 to select method");
			break;			
			}
		
			free(skeleton_90);
			free(skeleton_180);
			free(skeleton_270); 
			free(shift_45);
			free(skeleton_135);
			free(skeleton_225);
			free(skeleton_315);
			free(shift45);
			free(Skeleton_45);

		delete_Image(inputImage);
		temp=(Image *)remap_Image((const Image *)skeleton_Image3,CVIP_BYTE,0,255);
		delete_Image(skeleton_Image3);
		skeleton_Image3=temp;

		return skeleton_Image3;	
	}
