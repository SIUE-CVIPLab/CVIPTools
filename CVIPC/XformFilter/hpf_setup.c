/*****************************************************************************
 * ======================================================================    *
 * Image Processing/Computer Vision Tool Project - Dr. Scott Umbaugh SIUE    *
 * ======================================================================    *
 *                                                                           *
 * ROUTINE/PGM NAME: hpf_setup.c                                             *
 *                                                                           *
 *                    High pass filters setup                                *
 *              DESCRIPTION: This function is designed to setup both the     *
 * Ideal High Pass and Butterworth High Pass filter. It prompt the user to   *
 * see if DC value is to be retained, for cut off frequency, and for filter  *
 * order if butterworth filter is requested. It also determines (By the type *
 * of transform) whether to call the filtering function directly or to call  *
 * another setup function call cn_setup().                                   *
 * These high pass filters can also be called independently without using    *
 * this setup program.                                                       *
 *                                                                           *
 * Note: Any newly created transform need to be added to the                 *
 *       switch(transform) statement with dcpos=1 if the dc value is         *
 *       center of the spectrum or dcpos=2 if the dc value is at the top     *
 *       left corner of the spectrum.                                        *
 *                                                                           *
 *                   AUTHOR: Simon Low                                       *
 *                                                                           *
 *            RELATED FILES: filter.c, cn_setup.c                            *
 *                                                                           *
 *              CODING DATE: 1/15/92                                         *
 *  LAST MODIFICATIONS MADE: 11/18/92                                        *
 *                                                                           *
 *****************************************************************************
Revision: Xchen Feb 2003
xchen update this file and add hpf_filter function to it

  RCS (Revision Control System) Information - Added automatically by RCS)

$Author: yawei $
$Date: 1997/01/15 17:13:53 $
$Source: /export/home_faculty/cvipapps/CVIPtools3.5/XFORMFILTER/RCS/hpf_setup.c,v $
$Header: /export/home_faculty/cvipapps/CVIPtools3.5/XFORMFILTER/RCS/hpf_setup.c,v 1.8 1997/01/15 17:13:53 yawei Exp $

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "CVIPtools.h"
#include "CVIPimage.h"
#include "CVIPxformfilter.h"
/*******************************************************************************
********************************************************************************/
Image * hpf_setup( Image *in_Image, PROGRAMS transform )
{
	int dc, dcpos;
	int block_size, choice, filtertype=0;
	char DC[2];
	HISTORY stuff;
	int cut, order, maxi;

	printf("\nRetain DC Value (Y/N) ?: ");
	scanf("%s", &DC);
	getchar();
	if (DC[0] == 'Y' || DC[0] == 'y')
		dc = 1;
	else
		dc = 0;

	switch(transform)
	{
		case WALSH:
			stuff=history_get(in_Image, WALSH);
			GET_HIST_DATA(stuff,0,block_size);
			dcpos = 2; /* corner */
			break;
		case HADAMARD:
			stuff=history_get(in_Image, HADAMARD);
			GET_HIST_DATA(stuff,0,block_size);
			dcpos = 2; 
			break;
		case FFT:
			stuff=history_get(in_Image, FFT);
			GET_HIST_DATA(stuff,0,block_size);
			dcpos = 1;
			break;  
		case DCTXFORM:
			stuff=history_get(in_Image, DCTXFORM);
			GET_HIST_DATA(stuff,0,block_size);
			dcpos=2;
			break;
		case WAVELET:
			dcpos=2;
			block_size=in_Image->image_ptr[0]->rows;
			break;
		default: /* used for unsetup transform, assuming dc at center */ 
			dcpos=1;
			fprintf(stdout, "Was your previous transform an FFT ? (y/n)\n");
			(void)gets(DC);
			if((DC[0]!='y') && (DC[0]!='Y')) dcpos=2;
			printf("\nEnter block size used for previous forward transform: ");
			scanf("%d", &block_size);
			getchar();
			/* xchen add break here */
			break;
	}

	while(choice !=3)
	{
		printf("\n High Pass Filters\n");
		printf("===================\n");
		printf("\n 1. Ideal High Pass Filter\n");
		printf("\n 2. Butterworth High Pass Filter\n");
		printf("\n 3. Go back to Previous menu\n");
		printf("\n Please enter your choice: ");
		scanf("%d", &choice);
		getchar();
		cut = 0;

		if(dcpos==1)
			maxi = block_size/2;
		else
			maxi= block_size; 

		while ( cut < 1 || cut > maxi)
		{
			printf("\nMin: 1   Max: %d \n",maxi);
			printf("\nPlease Enter CutOff Frequency: ");
			scanf("%d", &cut);
			getchar(); 
		}

		switch(choice)
		{
			case 1:  /* Ideal High Pass */ 
				filtertype = 3;
				if ( dcpos == 1) /* dc in center */
				{ 
					in_Image =(Image *) Ideal_High (in_Image, block_size, dc,cut);
					return in_Image;
				}
				else /* 0 for filter order since this is not Butterworth */
				{
					in_Image=(Image *)nonfft_xformfilter(in_Image,block_size,dc,filtertype,cut,0,0);
					return in_Image;
				}
			case 2: /* Butterworth High Pass */
				order = 0; 
				while ( order < 1 || order > 8)
				{
					printf("\nEnter filter order (1-8) : ");
					scanf("%d", &order);
					getchar();
				}
				filtertype = 4; /* Butterworth High Pass */
				if ( dcpos == 1)
				{
					in_Image=(Image *)Butterworth_High(in_Image,block_size,dc,cut,order);
					return in_Image;
				}
				else
				{
					in_Image =(Image *)nonfft_xformfilter(in_Image,block_size,dc,filtertype,cut, 0,order);
					return in_Image;
				}
			case 3:
				printf("\nreturning unprocessed image.\n");
				return in_Image;
			default:
				printf("\nTry again !\n");
				break;
		}
	}
	return(NULL);
}
/**************************************************************************
*
*             File Name: hpf_filter
*           Description: 
*         Related Files: 
*   Initial Coding Date: Feb 2003
*           Portability: Standard (ANSI) C
*            References:
*             Author(s): Xiaohe Chen
*                        Southern Illinois University @ Edwardsville
*
****************************************************************************/
Image * hpf_filter( Image *in_Image, int transform, int Blocksize, int HP_Filter, int FilterOrder, int Cutoff, int KeepDC )
{
	int dcpos; /* DC Position */
	int filtertype=0;
	int maxi;

	switch (transform)
	{
		case 0: /* FFT */
			dcpos = 1;
			break;  
		case 1: /* DCT */
			dcpos=2;
			break;
		case 3: /* Walsh */
			dcpos = 2; /* corner */
			break;
		case 4: /* Hadamard */
			dcpos = 2; 
			break;
		/*
s		case WAVELET:
			dcpos=2;
			block_size=in_Image->image_ptr[0]->rows;
			break;
		*/
		default: /* used for unsetup transform, assuming dc at center */ 
			dcpos = 2; /* corner */
			break;
	}

	if(dcpos==1)
		maxi = Blocksize/2;
	else
		maxi= Blocksize; 

	switch(HP_Filter)
	{
		case 0:  /* Ideal High Pass */ 
			filtertype = 3;
			if ( dcpos == 1) /* dc in center */
				in_Image =(Image *) Ideal_High (in_Image, Blocksize, KeepDC,Cutoff);
			else /* 0 for filter order since this is not Butterworth */
				in_Image=(Image *)nonfft_xformfilter(in_Image,Blocksize,KeepDC,filtertype,Cutoff,0,0);
			break;
		case 1: /* Butterworth High Pass */
			filtertype = 4; /* Butterworth High Pass */
			if ( dcpos == 1)
				in_Image=(Image *)Butterworth_High(in_Image, Blocksize, KeepDC, Cutoff, FilterOrder);
			else
				in_Image =(Image *)nonfft_xformfilter(in_Image, Blocksize, KeepDC, filtertype, Cutoff, 0, FilterOrder);
			break;
		case 2:
			break;
		default:
			filtertype = 3;
			if ( dcpos == 1) /* dc in center */
				in_Image =(Image *) Ideal_High (in_Image, Blocksize, KeepDC,Cutoff);
			else /* 0 for filter order since this is not Butterworth */
				in_Image=(Image *)nonfft_xformfilter(in_Image, Blocksize, KeepDC, filtertype,Cutoff,0,0);
			break;
	} /* END OF CASE */

	return in_Image;
}