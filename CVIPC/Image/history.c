/* ====================================================================== *
* Image Processing/Computer Vision Tool Project - Dr. Scott Umbaugh SIUE  *
* ======================================================================= *
*                                                                         *
* 	  FILE NAME: history.c                                            *
*                                                                         *
*                                                                         *
*         DESCRIPTION:  This files contains modules that manipulate the   *
*  history entry of the image structure.  The history entry is used to    *
*  pass parameters from function to function and to keep track of the     *
*  operations that have been performed on an image.                       * 
*									  *
*                      AUTHOR: Arve Kjoelen                               *
*                                                                         *
*                                                                         *
*                                                                         *
*         INITIAL CODING DATE:  3/22/93                                   *
*                                                                         *
*    LAST MODIFICATIONS MADE :  5/10/95                                   *
*                                                                         *
*                                                                         *
*    MODULES CONTAINED IN THIS FILE:                                      *
*                                                                         *
*         history_add() -  called by functions that manipulate images in  *
*    the queue.  Adds a record of the last operation performed on an      *
*    image to the history list.                                           *  
*									  *
*	  history_check() - determines whether a given operation has been *
*    performed on the image.  Returns a 1 if the operation has been 	  *
*    performed, a 0 otherwise.						  *  
*                                                                         *
*         history_get() - called by functions to find a specific history *
*    entry.  Returns a pointer to the history structure containing the	  *
*    pertinent information.                                               *
*                                                                         *
*	  history_copy() - called by functions in order to copy the	  *
*    history information of one image into another image.	  	  * 
*                                                                         *
*	  getlast_Hist() - takes a list of programs as input, and returns *
*			   a pointer to the one which was performed LAST. *
*									  *
*	  history_delete() - deletes the history information associated   *
*			   with an image.				  *
*                                                                         *
***************************************************************************/
#include "CVIPimage.h"
#include "CVIPtyp.h"
#include "CVIPtools.h"
#include <stdlib.h>


/* ====================================================================== *
* Image Processing/Computer Vision Tool Project - Dr. Scott Umbaugh SIUE  *
* ======================================================================= *
*                                                                         *
* ROUTINE/PGM NAME: history_add()                                         *
*                                                                         *
*                                                                         *
*         DESCRIPTION:  					          *
*         history_add() -  called by functions that manipulate images in  *
*    the queue.  Adds a record of the last operation performed on an      *
*    image to the history list.                                           *    
*    Variables passed:                                                    *
*         Image *image  :  pointer to the image structure that has been   *  
*    modified.                                                            *
*         history* story:  pointer to history structure to be added to    *                                                                 *    the image's history.                                                 *
*    Variables returned :  None                                           *                        *									  *
*                      AUTHOR: Arve Kjoelen                               *
*                                                                         *
*                                                                         *
*               RELATED FILES:  program_invoke.                           *
*                                                                         *
*         INITIAL CODING DATE:  3/22/93                                   *
*                                                                         *
*    LAST MODIFICATIONS MADE :  3/22/93                                   *
*                                                                         *
*                                                                         *
**************************************************************************/

void history_add(	Image	*image,
			HISTORY	newstuff)
{
	struct history	*temp;
	char		*fn = "history_add";

	if(image == NULL)
	{
		error_CVIP(fn,"NULL pointer passed.\n");
		return;
	}
	if(image->story==(HISTORY)NULL)
	{
		image->story = newstuff;
		image->story->next = NULL;
	}
	else
	{
		temp = image->story;
		while(temp->next != (HISTORY)NULL)
		temp = temp->next;
		temp->next = newstuff;
		temp->next->next = NULL;
	}
}


/* ====================================================================== *
* Image Processing/Computer Vision Tool Project - Dr. Scott Umbaugh SIUE  *
* ======================================================================= *
*                                                                         *
* ROUTINE/PGM NAME: history_check()                                       *
*                                                                         *
*                                                                         *
*         DESCRIPTION:                                                    *
*         history_check() - called by functions to find a specific history*
*    entry (To ascertain whether a given operation has been performed on  *
*    the image).                                                          *
*    Variables passed:                                                    *
*         Image *image  :  pointer to the image structure that has been   *  
*    modified.                                                            * 
*         FCN_TAG tag   :  the specific function to be found              *
*    Variables returned :  pointer to the history structure that contains *
*    the parameters for the specified operation.  A null pointer is       *  
*    returned if the operation has not been performed on the image        *
*									  *
*                      AUTHOR: Arve Kjoelen                               *
*                                                                         *
*                                                                         *
*               RELATED FILES:  program_invoke.                           *
*                                                                         *
*         INITIAL CODING DATE:  3/22/93                                   *
*                                                                         *
*    LAST MODIFICATIONS MADE :  3/22/93                                   *
*                                                                         *
*                                                                         *
**************************************************************************/

CVIP_BOOLEAN history_check(PROGRAMS program, Image *image)
{
	struct history	*temp;
	int		fftflag=0;
	int		dctflag=0;
	int		haarflag=0;
	int		hadamardflag=0;
	int		walshflag=0;
	int		waveletflag=0;
	int		pctflag=0;
	char		*fn = "history_check";

	if(image == NULL)
	{
		error_CVIP(fn,"NULL pointer passed.\n");
		return(CVIP_NO);
	}
	if(image->story==(HISTORY)NULL) {
		return(CVIP_NO);
	}

	temp=image->story;
	while(temp!=(HISTORY)NULL)
	{
		if(temp->ftag==program)
		{
			switch(program)
			{
				case FFT:
					fftflag=1;
					break;
				case DCTXFORM:
					dctflag=1;
					break;
				case WALSH:
					walshflag=1;
					break;
				case HAAR:
					haarflag=1;
					break;
				case HADAMARD:
					hadamardflag=1;
					break;
				case WAVELET:
					waveletflag=1;
					break;
				case PCT:
					pctflag=1;
					break;
				default:
					break;
			}
		}
		temp=temp->next;
	}

	if(	(!fftflag)&&(!dctflag)&&(!haarflag)&&
		(!pctflag)&&(!waveletflag)&&(!walshflag)&&(!hadamardflag))
	return(CVIP_NO);

	temp=image->story;
	if(fftflag)
	{
		while(temp != (HISTORY)NULL)
		{
			if(temp->ftag==I_FFT)
			return(CVIP_NO);
			temp=temp->next;
		}
		return(CVIP_YES);
	}
	temp=image->story;
	if(dctflag)
	{
		while(temp != (HISTORY)NULL)
		{
			if(temp->ftag==I_DCTXFORM)
			return(CVIP_NO);
			temp=temp->next;
		}
		return(CVIP_YES);
	}
	temp=image->story;
	if(haarflag)
	{
		while(temp != (HISTORY)NULL)
		{
			if(temp->ftag==I_HAAR)
			return(CVIP_NO);
			temp=temp->next;
		}
		return(CVIP_YES);
	}
	temp=image->story;
	if(hadamardflag)
	{
		while(temp != (HISTORY)NULL)
		{
			if(temp->ftag==I_HADAMARD)
			return(CVIP_NO);
			temp=temp->next;
		}
		return(CVIP_YES);
	}
	temp=image->story;
	if(waveletflag)
	{
		while(temp != (HISTORY)NULL)
		{
			if(temp->ftag==I_WAVELET)
			return(CVIP_NO);
			temp=temp->next;
		}
		return(CVIP_YES);
	}
	temp=image->story;
	if(walshflag)
	{
		while(temp != (HISTORY)NULL)
		{
			if(temp->ftag==I_WALSH)
			return(CVIP_NO);
			temp=temp->next;
		}
		return(CVIP_YES);
	}
	temp=image->story;
	if(pctflag)
	{
		while(temp != (HISTORY)NULL)
		{
			if(temp->ftag==I_PCT)
			return(CVIP_NO);
			temp=temp->next;
		}
		return(CVIP_YES);
	}
}

CVIP_BOOLEAN history_check1(Image *image)
{
	char	*fn = "history_check1";

	if(image == NULL)
	{
		error_CVIP(fn,"NULL pointer passed.\n");
		return(CVIP_NO);
	}
	if(image->story==NULL)
	{
		return(CVIP_NO);
	}
	return(CVIP_YES);
}


/**************************************************************************
* ======================================================================  *
* Image Processing/Computer Vision Tool Project - Dr. Scott Umbaugh SIUE  *
* ======================================================================= *
*									  *
*	ROUTINE/PGM NAME: history_get()					  *
*									  *
*	DESCRIPTION: This function finds and returns information about	  *
*	the program passed to it.  First, it checks to see whether the	  *
*	program/function has ever been performed on the image.  If not,	  *
*	the program prints an error message and return the NULL pointer.  *
*	If the program has been performed on the image, a pointer to      *
*	the pertinent history structure is returned.	                  *
*									  *
*	AUTHOR: Arve Kjoelen, SIUE					  *
*									  *
*	INITIAL CODING DATE: 11/11/93					  *
*									  *
*	LAST MODIFICATIONS MADE: 11/11/93				  *
*									  *
**************************************************************************/
HISTORY history_get(	Image		*image,
			PROGRAMS	program)
{
	CVIP_BOOLEAN	is_it_here;
	HISTORY		temp;
	char		*fn = "history_get";

	if(image == NULL)
	{
		error_CVIP(fn,"NULL pointer passed.\n");
		return((HISTORY)NULL);
	}
	is_it_here=history_check(program, image);
	if(!is_it_here)
	{
		return((HISTORY)NULL);
	}
	temp=image->story;
	while(temp!=(HISTORY)NULL)
	{
		if(temp->ftag==program)
		{
			return(temp);
		}
		temp=temp->next;
	}
	return((HISTORY)NULL);  
}


HISTORY	history_get1(Image *image)
{
	CVIP_BOOLEAN	is_it_here;
	HISTORY		temp;
	char		*fn = "history_get1";

	if(image == NULL)
	{
		error_CVIP(fn,"NULL pointer passed.\n");
		return((HISTORY)NULL);
	}

	is_it_here=history_check1(image);
	if(!is_it_here)
	{
		return((HISTORY)NULL);
	}
	return(image->story);
}



/* ====================================================================== *
* Image Processing/Computer Vision Tool Project - Dr. Scott Umbaugh SIUE  *
* ======================================================================= *
*									  *
*	ROUTINE/PGM NAME: history_show()				  *
*									  *
*	DESCRIPTION: This routine is a setup routine for the printing  of *
*	the image history to stdout.  It checks whether there is any	  *
*	record of programs being performed on the image, and sends those  *
*	records to history_print for output.				  *
*									  *
*	AUTHOR: Arve Kjoelen, SIUE					  *
*									  *
*	INITIAL CODING DATE: 11/23/93					  *
*									  *
*	LAST MODIFICATIONS MADE: 11/23/93				  *
*									  *
**************************************************************************/
void	history_print(HISTORY);

void	history_show(Image *image)
{
	HISTORY	stuff;
	char	*fn = "history_show";

	if(image == NULL)
	{
		error_CVIP(fn,"NULL pointer passed.\n");
		return;
	}
   
	print_CVIP("\n");

	if(image->story==(HISTORY)NULL)
	{
		print_CVIP( "No Processing history for the image\n");
		return;
	}
	stuff=image->story;
	while(stuff->next!=(HISTORY)NULL)
	{
		history_print(stuff);
		stuff=stuff->next;
	}
	history_print(stuff);
	print_CVIP( "End of processing history.\n");
}

/************************************************************************
* ===================================================================== *
*    Image Processing/Computer Vision Tool - Dr. Scott Umbaugh, SIUE    *
* ===================================================================== *
*									*
*	ROUTINE/PGM NAME: history_print()				*
*									*
*	DESCRIPTION: This routine performs the actual output of the	*
*	information associated with the history structure passed to it.	*
*									*
*	AUTHOR: Arve Kjoelen, SIUE.					*
*									*
*	INITIAL CODING DATE: 11/23/93					*
*									*
*	LAST MODIFICATIONS MADE: 11/23/93				*
*									*
************************************************************************/
char	*get_wav_base(int);

void	history_print(HISTORY stuff)
{
	const char	fn[]="history_print";
	int		*ptr;
	char		*wavbase;

	print_CVIP( "\n");

	switch(stuff->ftag)
	{
		case PCT:
			print_CVIP(
		"** Principal Components Transform.  Transform matrix:\n");
			print_Matrix(stuff->packetP->dptr[0]);
			break;
		case I_PCT:
			print_CVIP(
				"** Inverse Principal Components Transform\n");
			break;
		case WALSH:
			ptr=(int *)stuff->packetP->dptr[0];
			print_CVIP(
				"** Walsh Transform. Blocksize: %d\n",
				ptr[0]);
			break;
		case I_WALSH:
			ptr=(int *)stuff->packetP->dptr[0];
			print_CVIP(
				"** Inverse Walsh Transform. Blocksize: %d\n",
					ptr[0]);
			break;
		case HADAMARD:
			ptr=(int *)stuff->packetP->dptr[0];
			print_CVIP("** Hadamard Transform. Blocksize: %d\n",
					ptr[0]);
			break;
		case I_HADAMARD:
			ptr=(int *)stuff->packetP->dptr[0];
			print_CVIP(
			"** Inverse Hadamard Transform. Blocksize: %d\n",
					ptr[0]);
			break;
		case HAAR:
			ptr=(int *)stuff->packetP->dptr[0];
			print_CVIP(	"** Haar Transform. Blocksize: %d\n",
					ptr[0]);
			break;
		case I_HAAR:
			ptr=(int *)stuff->packetP->dptr[0];
			print_CVIP(
				"** Inverse Haar Transform. Blocksize: %d\n",
					ptr[0]);
			break;
		case FFT:
			ptr=(int *)stuff->packetP->dptr[0];
			print_CVIP(
				"** Fast Fourier Transform. Blocksize: %d\n",
					ptr[0]);
			break;
		case I_FFT:
			ptr=(int *)stuff->packetP->dptr[0];
			print_CVIP(
			"** Inverse Fast Fourier Transform. Blocksize: %d\n",
					ptr[0]);
			break;
		case DCTXFORM:
			ptr=(int *)stuff->packetP->dptr[0];
			print_CVIP(
				"** Discrete Cosine Transform. Blocksize: %d\n",
					ptr[0]);
			break;
		case I_DCTXFORM:
			ptr=(int *)stuff->packetP->dptr[0];
			print_CVIP(
			"** Inverse Discrete Cosine Transform. Blocksize: %d\n",
					ptr[0]);
			break;
		case WAVELET:
			ptr=(int *)stuff->packetP->dptr[0];
			print_CVIP("** Wavelet Transform:\n");
			wavbase = (char *)get_wav_base(ptr[0]);
			ptr=(int *)stuff->packetP->dptr[1];
			print_CVIP("     - Basis: %s\n", wavbase);
			print_CVIP("     - # of frequency bands: %d\n",
				3*ptr[0]+1);
			break;
		case I_WAVELET:
			ptr=(int *)stuff->packetP->dptr[0];
			print_CVIP( "** Inverse Wavelet Transform:\n");
			wavbase = (char *)get_wav_base(ptr[0]);
			ptr=(int *)stuff->packetP->dptr[1];
			print_CVIP("     - Basis: %s\n", wavbase);
			print_CVIP("     - # of frequency bands: %d\n",
				3*ptr[0]+1);
			break;
		case XFORMFILTER:
			print_CVIP( "** Transform-domain filter\n");
			break;
		case INVERSEFILTER:
			if(stuff->ftag==INVERSEFILTER)
			print_CVIP( "** Inverse Filter\n");
			else
			print_CVIP( "** Wiener Filter\n");
			ptr=(int *)stuff->packetP->dptr[0];
			if(*ptr==1)
			print_CVIP( "When H(u,v)=0: F(u,v)=G(u,v)\n");
			else if(*ptr==2)
			print_CVIP( "When H(u,v)=0: F(u,v)=0\n");
			else
			error_CVIP(fn,"Unexpected history parameter.\n");
			ptr=(int *)stuff->packetP->dptr[1];
			if(*ptr>0)
			print_CVIP( "Filter Cutoff: %d\n", *ptr);
			else if(*ptr==0)
			print_CVIP( "No Filter Cutoff\n");
			else
			error_CVIP(fn,"Unexpected history parameter\n");
			break;
		case ZERO_PAD:
			ptr=(int *)stuff->packetP->dptr[0];
			print_CVIP(
	"** Zero-padding: %d by %d image extended to %d rows by %d cols\n",
			ptr[0], ptr[1], ptr[2], ptr[3]);
			break;
		case MEDIAN_FILTER:
			ptr=(int *)stuff->packetP->dptr[0];
			print_CVIP(
				"Median Filter.  Filter Window Size: %d\n",
					ptr[0]);
			break;
		default:
			error_CVIP(fn,
		"** Unidentified Operation Performed: Program identity: %d\n",
					stuff->ftag);
	}
}

char	*get_wav_base(int no)
{
	char	*name;

	switch(no)
	{
		case 1:
			name = "haar wavelet\0";
			break;
		case 2:
			name = "daub4 wavelet\0";
			break;
		case 3:
			name = "daub6 wavelet\0";
			break;
		case 4:
			name = "daub8 wavelet\0";
			break;
		case 5:
			name = "daub10 wavelet\0";
			break;
		case 6:
			name = "daub12 wavelet\0";
			break;
		case 7:
			name = "daub14 wavelet\0";
			break;
		case 8:
			name = "daub16 wavelet\0";
			break;
		case 9:
			name = "daub18 wavelet\0";
			break;
		case 10:
			name = "daub20 wavelet\0";
			break;
	}
	return(name);
}
      
/************************************************************************
* ===================================================================== * 
*    Image Processing/Computer Vision Tool - Dr. Scott Umbaugh, SIUE    *
* ===================================================================== *
*                                                                       *
*       ROUTINE/PGM NAME: history_copy()                                *
*                                                                       *
*	DESCRIPTION: This function copies information from the HISTORY	*
*		structure old_story to the HISTORY structure h_story.	*
*		It is intended for use as a freestanding function to be	*
*		called from any function.				*
*                                                                       *
*       AUTHOR: Arve Kjoelen, SIUE.                                     *
*                                                                       *
*       INITIAL CODING DATE: 5/10/95                                    *
*                                                                       *
*       LAST MODIFICATIONS MADE: 5/11/95                                *
*                                                                       *
************************************************************************/
void	history_copy(	Image	*from,
			Image	*to)
{
	HISTORY		old_story, h_story, temp;
	PACKET		*oldpacket;
	int		i=0;
	unsigned int	limit;
	size_t		size;
	int		w;
	char		*fn = "history_copy";

	if((from == NULL) || (to == NULL))
	{
		error_CVIP(fn,"NULL pointer passed.\n");
		return;
	}
	if(from->story==(HISTORY)NULL)
	return;

	old_story=from->story;

	to->story=(HISTORY)malloc(sizeof(struct history));
	if(to->story == (HISTORY)NULL)
	{
		error_CVIP(fn,"Unable to allocate memory.\n");
		return;
	}

	h_story=to->story;
	h_story->next=(HISTORY)NULL;

	while(old_story != (HISTORY)NULL)
	{
		oldpacket = old_story->packetP;
		h_story->ftag = (PROGRAMS)old_story->ftag;
		limit = old_story->packetP->dsize;

		h_story->packetP = (PACKET *)malloc(sizeof(PACKET));
		if(h_story->packetP == NULL)
		break;

		h_story->packetP->dsize = limit;
		h_story->packetP->dtype =
			(CVIP_TYPE*)malloc(sizeof(CVIP_TYPE)*limit);
		if(h_story->packetP->dtype == NULL)
		{
			free(h_story->packetP);
			h_story->packetP = NULL;
			break;
		}
		memcpy(	h_story->packetP->dtype,
			oldpacket->dtype,
			sizeof(CVIP_TYPE)*limit);
		h_story->packetP->dptr = (void**)malloc(sizeof(void*)*limit);
		if(h_story->packetP->dptr == NULL)
		{
			free(h_story->packetP->dtype);
			free(h_story->packetP);
			h_story->packetP = NULL;
			break;
		}
		for(w = 0; w < limit; w++)
		{
			switch (oldpacket->dtype[w]){
			case CVIP_BYTE:
				h_story->packetP->dptr[w] =
					(byte *)malloc(sizeof(byte));
				if(h_story->packetP->dptr[w] == NULL)
				break;
				((byte*)(h_story->packetP->dptr[w]))[0] = 
					((byte*)(oldpacket->dptr[w]))[0];
				break;
			case CVIP_SHORT:
				h_story->packetP->dptr[w] =
					(short *)malloc(sizeof(short));
				if(h_story->packetP->dptr[w] == NULL)
				break;
				((short*)(h_story->packetP->dptr[w]))[0] = 
					((short*)(oldpacket->dptr[w]))[0];
				break;
			case CVIP_INTEGER:
				h_story->packetP->dptr[w] =
					(int *)malloc(sizeof(int));
				if(h_story->packetP->dptr[w] == NULL)
				break;
				((int*)(h_story->packetP->dptr[w]))[0] = 
					((int*)(oldpacket->dptr[w]))[0];
				break;
			case CVIP_FLOAT:
				h_story->packetP->dptr[w] =
					(float *)malloc(sizeof(float));
				if(h_story->packetP->dptr[w] == NULL)
				break;
				((float*)(h_story->packetP->dptr[w]))[0] = 
					((float*)(oldpacket->dptr[w]))[0];
				break;
			case CVIP_DOUBLE:
				h_story->packetP->dptr[w] =
					(double *)malloc(sizeof(double));
				if(h_story->packetP->dptr[w] == NULL)
				break;
				((double*)(h_story->packetP->dptr[w]))[0] = 
					((double*)(oldpacket->dptr[w]))[0];
				break;
			}
		}
		if(w != limit)
		{
			while(w > 0)
			{
				w--;
				free(h_story->packetP->dptr[w]);
			}
			free(h_story->packetP->dptr);
			free(h_story->packetP->dtype);
			free(h_story->packetP);
			h_story->packetP = NULL;
			break;
		}
		if(old_story->next==(HISTORY)NULL) break;
		old_story=old_story->next;

		h_story->next=(HISTORY)malloc(sizeof(struct history));
		if(h_story->next == NULL)
		break;

		h_story=h_story->next;
	}  /* end while (old_story!- */
	if(old_story->next != NULL)
	{
		error_CVIP(fn,"Unable to allocate memory.\n");
		h_story = to->story;
		while(h_story != NULL)
		{
			if(h_story->packetP != NULL)
			{
				free(h_story->packetP->dtype);
				for(w = 0;w < h_story->packetP->dsize;w++)
				free(h_story->packetP->dptr[w]);
				free(h_story->packetP);
			}
			temp = h_story;
			h_story = h_story->next;
			free(temp);
		}
		to->story = NULL;
	}
	else
	h_story->next=(HISTORY)NULL;
}


int	getSize_Hist(HISTORY stuff)
{
	int	size, i, num;

	size = sizeof(struct history);
	size += sizeof(struct packet);
	num = stuff->packetP->dsize;
	size += num * sizeof(void *);
	size += num * sizeof(CVIP_TYPE);
	for(i = 0; i < num; i++)
	{
		switch(stuff->packetP->dtype[i])
		{
			case CVIP_BYTE:  size += sizeof(byte); break;
			case CVIP_SHORT: size += sizeof(short); break;
			case CVIP_INTEGER: size += sizeof(int); break;
			case CVIP_FLOAT: size += sizeof(float); break;
			case CVIP_DOUBLE: size += sizeof(double); break;
		}
	}
	return size;
}

int	getAllSize_Hist(Image *imgP)
{
	HISTORY	stuff;
	int	size = 0;
	char	*fn = "getAllSize_Hist";


	if(imgP == NULL)
	{
		error_CVIP(fn,"NULL pointer passed.\n");
		return(0);
	}
   
	stuff = imgP->story;
	if(stuff == NULL)
	return 0;
	while(stuff != NULL)
	{
		size += getSize_Hist(stuff);
		stuff = stuff->next;
	}
	return size;
}

/*
 * ROUTINE NAME: getlast_Hist()
 *
 * DESCRIPTION: takes an image pointer and a list of PROGRAMS.  Returns
 * returns the name of the program which was performed LAST of the listed
 * programs.  This is useful, for instance, when the user does an FFT,
 * then IFFT, then DCT, then attempt transform filtering.  filtering
 * would assume incorrect periodicity (FFT) unless it retrieved the LAST
 * transform that was performed on the image.
 *
 * The function works as follows: It associates each element in a CVIP_BOOLEAN
 * array with the corresponding element in the array of PROGRAMS passed.
 * It then initializes each element of this array to history_check().
 * This eliminates the PROGRAMS which have not been performed.  The remaining
 * list of PROGRAMS is eliminated by checking which routine was performed
 * last.
 *
 * IMPORTANT NOTE TO DEVELOPERS:
 * The enumeration constants for the various transforms in CVIPtools.h
 * are defined to be contiguous.  Keep them that way - it makes a lot
 * of history routines easier to code.  Also, if you are defining
 * forward and inverse operation, make them contiguous.
 *
 * AUTHOR: Arve Kjoelen
 *
 * INITIAL CODING DATE: 6/30/96
 *
 * DIAGNOSTICS: 
 *	- if none of the programs were performed, the number
 * 0 is returned.  This is a kludge, but oh well....
 *	- the passed PROGRAMS array is not checked for validity.
 */
PROGRAMS	getlast_Hist(	Image		*imgP,
				PROGRAMS	*programs,
				unsigned	nprogs)
{
	HISTORY		temp; 
	CVIP_BOOLEAN	*performed;
	PROGRAMS	res;
	int		i, j, cnt, any, done;
	char		*fn = "getlast_Hist";

	if(imgP == NULL)
	{
		error_CVIP(fn,"NULL pointer passed.\n");
		return((PROGRAMS)0);
	}
	performed = (CVIP_BOOLEAN *)malloc(sizeof(CVIP_BOOLEAN)*nprogs);
	if(performed == NULL)
	{
		error_CVIP(fn,"Unable to allocate memory.\n");
		return((PROGRAMS)0);
	}
	any = 9999;
	for(i=0; i<nprogs; i++)
	{
		performed[i] = history_check(programs[i], imgP);
		if(performed[i]==CVIP_YES)
		any = 0;
	}
	if(any==9999)
	return((PROGRAMS)0);
	while(1)
	{
		cnt=0;
		for(i=0; i<nprogs; i++)
		{
			if(performed[i]==CVIP_YES)
			{
				res=programs[i];
				cnt++;
			}
		}
		if(cnt==1)
		{
			free(performed);
			return(res);
		}
		/*
		* For each PROGRAM which has a corresponding
		* inverse operation, make the entry inactive if
		* the inverse was performed after the forward.
		*/
		for(i=0; i<nprogs; i++)
		{
			if(performed[i]==CVIP_YES)
			{
				res=programs[i];
				if(res>=PCT && res<I_WAVELET)
				{
					temp=history_get(imgP, res);
					while(temp->next!=(HISTORY)NULL)
					{
						if(temp->next->ftag==res+1)
						performed[i]=CVIP_NO;
						temp=temp->next;
					} 
				}
			}
		} 
		/* 
		* At this point, we will have removed all routines which have
		* had their inverses performed.  Now it's time to find out which
		* routines are left and last.  First though, we'll make sure
		* there's a need to perform this step by counting the number
		* of remaining "active" history entries.
		*/
		cnt=0;
		for(i=0; i<nprogs; i++)
		{
			if(performed[i]==CVIP_YES)
			{
				res=programs[i];
				cnt++;
			}
		}
		if(cnt==1)
		{
			free(performed);
			return(res);
		}
		/*
		* find the first "active" entry.
		*/ 
		i=0;
		do{
			if(performed[i]==CVIP_YES)
			{
				i=nprogs;
				res=programs[i];
			}
			i++;
		}while(i<nprogs);
		/*
		* find any active entry performed AFTER this one,
		* and make this one inactive.  If none are found,
		* this is the one we're looking for.
		*/
		temp=history_get(imgP, res);
		while(temp->next!=(struct history *)NULL)
		{
			for(j=i; j<nprogs; j++)
			{
				if(temp->next->ftag==programs[j])
				{
					performed[i]=CVIP_NO;
					res=programs[j];
				}
			}
			temp=temp->next; 
		}  
	}
}

void history_delete_program(Image		*image,
			PROGRAMS	program)
{
	CVIP_BOOLEAN	is_it_here;
	HISTORY		*ppHistory, temp;
	char		*fn = "history_get";

	if(image == NULL)
	{
		error_CVIP(fn,"NULL pointer passed.\n");
		return;
	}
	is_it_here=history_check(program, image);
	if(!is_it_here)
	{
		return;
	}
	ppHistory=&(image->story);
	while((*ppHistory)!=(HISTORY)NULL)
	{
		if((*ppHistory)->ftag==program)
		{
			temp = (HISTORY)(*ppHistory);
			/* XXX Todo: need to free the memory of temp */

			*ppHistory = temp->next;
			ppHistory = &(temp->next);
		} else 
		{
			ppHistory = &((*ppHistory)->next);
		}
	}
	return;  
}

