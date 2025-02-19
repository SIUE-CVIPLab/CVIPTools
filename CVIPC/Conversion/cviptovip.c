/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*
*             File Name: cviptovip.c
*           Description: save the contents of an Image structure out to a
*                        CVIPtools "VIP - Visualization in Image Processing"
*                        format
*         Related Files: libconverter.a, CVIPvip.h, CVIPmagic.h
*   Initial Coding Date: Wed Apr  7 18:38:57 CDT 1993
*           Portability: Standard (ANSI) C
*             Credit(s): Gregory Hance, Arve Kjoelena, Kun Luo
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1993 SIUE - by Gregory Hance, Arve Kjoelena and Kun Luo.
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
* $Log: cviptovip.c,v $
* Revision 1.20  2001/05/02 14:46:43  zlin
* add transform compression TRCM stuff
*
* Revision 1.19  1999/11/17 00:45:05  ycheng
* added cvip <=> vip convert support to VQ and XVQ.
*
* Revision 1.18  1998/03/10 04:27:23  smakam
* made changes corresponding to including a new compression method fractal
*
* Revision 1.17  1997/05/21 03:27:26  yawei
* added WIN32 binary fopen
*
* Revision 1.16  1997/03/08 00:43:40  yawei
* Name Changes:
* 	BOOLEAN ==> CVIP_BOOLEAN
* 	FALSE ==> CVIP_YES
* 	TRUE ==> CVIP_NO
* 	BYTE ==> CVIP_BYTE
* 	SHORT ==> CVIP_SHORT
* 	INTEGER ==> CVIP_INTEGER
* 	FLOAT ==> CVIP_FLOAT
* 	DOUBLE ==> CVIP_DOUBLE
* 	TYPE ==> CVIP_TYPE
*
* Revision 1.15  1997/01/16 20:48:55  yawei
* Global Change:  Image_FORMAT ==> IMAGE_FORMAT
*
 * Revision 1.14  1997/01/15  17:08:25  yawei
 * Global Change:  IMAGE ==> Image
 *
 * Revision 1.13  1996/12/14  03:36:39  yawei
 * Added cvip <==> vip convert support to ZON and ZON2
 *
 * Revision 1.12  1996/12/05  15:44:44  akjoele
 * Changed LZW to ZVL after changes made by yawei to CVIPimage.h.
 *
 * Revision 1.11  1996/12/04  21:05:31  yawei
 * changed lzw_decompress ==> zvl_decompression
 *
 * Revision 1.10  1996/12/03  23:28:55  yawei
 * changed function name glr_decompress() to the backward compatible version
 * glr_decompresssion()
 *
 * Revision 1.9  1996/11/30  18:00:57  yawei
 * Chnaged DPCM_decompress to  backward compatible version dpc_decompression
 *
 * Revision 1.8  1996/11/30  02:37:18  yawei
 * Changed btc2/3_decompress to btc2/3_decompression (old backward compatiable
 * version)
 *
 * Revision 1.7  1996/11/30  01:14:12  yawei
 * changed btc_decompress to decompression (the outdated version)
 *
 * Revision 1.6  1996/11/30  00:21:43  yawei
 * Changed bit_decompression to the new bit_decompress
 *
 * Revision 1.5  1996/01/16  17:31:58  kluo
 * add extern header
 *
 * Revision 1.4  1995/11/03  22:45:11  kluo
 * add dpcm.
 *
 * Revision 1.3  1995/09/22  17:34:16  kluo
 * history is saved
 *
 * Revision 1.2  1995/09/18  20:50:09  kluo
 * check file in
 *
 * Revision 1.1  1993/05/31  07:10:14  hanceg
 * Initial revision
 *
*
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "CVIPimage.h"
#include "pbmplus.h"
#include "CVIPmagic.h"
#include "CVIPvip.h"
#include "CVIPhistory.h"
#include "grey_RLC.h"

#include <CVIPcompress.h>

extern char *data_format_string[],
				*data_type_string[],
				*color_format_string[];
CVIP_BOOLEAN cviptovip( Image *cvipImage, char *filename, FILE *file, 
			CVIP_BOOLEAN save_history, CVIP_BOOLEAN is_compressed, 
			CVIP_BOOLEAN verbose)
{

	
	 

	XDR xdro;
	const char *fn = "cviptovip";
  
	/* Write basic image parameters to disk */
	if(verbose) {
		msg_CVIP(fn,"listing image attributes ...\n");
		msg_CVIP(fn," color space -- %s.\n",
					color_format_string[getColorSpace_Image(cvipImage)]);
		msg_CVIP(fn,"   data type -- %s.\n",
					data_type_string[getDataType_Image(cvipImage)]);
		msg_CVIP(fn,"      format -- %s.\n",
					data_format_string[getDataFormat_Image(cvipImage)]);
		msg_CVIP(fn,"       bands -- %u.\n", getNoOfBands_Image(cvipImage));
		msg_CVIP(fn,"        rows -- %d.\n", getNoOfRows_Image(cvipImage));
		msg_CVIP(fn,"        cols -- %d.\n", getNoOfCols_Image(cvipImage));
	}




	/* 
	 * write out magic number 'VIP'
	 */
	if( putc(CVIP_MAGIC1, file) == EOF ) {
		error_CVIP(fn, "error writing magic number");
      		return 0;
   	}
	if( putc(CVIP_MAGIC2, file) == EOF ) {
		error_CVIP(fn, "error writing magic number");
      		return 0;
   	}
   	if( putc(CVIP_MAGIC3, file) == EOF ) {
		error_CVIP(fn, "error writing magic number");
      		return 0;
   	}

	xdrstdio_create(&xdro, file, XDR_ENCODE);

	if(!xdr_image(&xdro, cvipImage,file,filename,save_history,is_compressed)) {
		error_CVIP(fn, "XDR I/O failed.");
		error_CVIP(fn, "could not write image to %s.", filename);
		return 0;
	}

return 1;
}


bool_t
xdr_image(
	XDR *xdrs,
	Image *imgP,
	FILE  *file,
	char	*file_name,
	CVIP_BOOLEAN save_history,
	CVIP_BOOLEAN is_compressed
)
{
	register int i;
	byte compress,format,color,type,bands,data_format;
	short rows, cols;
	
	if(xdrs->x_op == XDR_ENCODE){
		compress = (byte) is_compressed;
		format = (byte) imgP->image_format;
		color = imgP->color_space;
		bands = (byte)imgP->bands;
		rows =  (short)imgP->bandP[0]->rows;
		cols =  (short)imgP->bandP[0]->cols;
		type = (byte)imgP->bandP[0]->data_type;
		data_format = (byte)imgP->bandP[0]->data_format;
	}
	
	
	if(!(
		xdr_u_char(xdrs, (byte *)&compress) &&
		xdr_u_char(xdrs, (byte *)&format) &&
		xdr_u_char(xdrs, (byte *)&color) &&
		xdr_u_char(xdrs, (byte *)&type) &&
		xdr_u_char(xdrs, (byte *)&bands) &&
		xdr_short(xdrs, (short*)&cols) &&
		xdr_short(xdrs, (short*)&rows) &&
		xdr_u_char(xdrs, (byte *)&data_format))){
		error_CVIP("xdr_image", "XDR I/O failed.");
		return 0;
	}

	if(xdrs->x_op == XDR_DECODE){
		imgP->color_space = (COLOR_FORMAT)color;
		imgP->image_format = (IMAGE_FORMAT)format;
		imgP->bands = bands;
	}

	if(!xdr_info(xdrs,imgP,save_history)){
		error_CVIP("xdr_history", "XDR I/O failed.");
		return 0;
	}

	if(compress){
		return xdr_compress(xdrs,imgP,file,file_name);
	}

	if(!xdr_array(xdrs, (caddr_t *)&imgP->bandP, (unsigned int *)&imgP->bands, MAXBANDS,
		sizeof(Matrix *), xdr_long)){
		error_CVIP("xdr_image", "XDR I/O failed.");
		return 0;
	}

	for(i=0; i < imgP->bands; i++) {

		if(xdrs->x_op == XDR_DECODE) imgP->bandP[i] = NULL;

		if(! xdr_reference(xdrs, (caddr_t *)imgP->bandP+i, sizeof(Matrix),
		     xdr_matrix)
		) {
			error_CVIP("xdr_image", "XDR I/O failed.");
			return 0;
		}

	}

	return 1;
} 

bool_t xdr_compress(
	XDR *xdrs,
	Image *imgP,
	FILE *file,
	char *filename){
	Image *temp_image = NULL;
	FILE *fptr;
	int data;
	
	if(xdrs->x_op == XDR_ENCODE){
		#ifndef WIN32
		fptr = fopen(filename,"r");
		#else
		fptr = fopen(filename,"rb");
		#endif
		if(fptr == NULL) {
			error_CVIP("xdr_compress", "Cannot open compressed image file");
			return 0;
		}
		data = getc(fptr);
		while(data != EOF){
			putc(data,file);
			data = getc(fptr);
		}
		fflush(file);
		fclose(fptr);
	}
	else{
		if(imgP->image_format == BTC)
			temp_image = (Image*)btc_decompression(file);
		else if(imgP->image_format == GLR)
			temp_image = (Image*)glr_decompression(file);
		else if(imgP->image_format == BRC)
			temp_image = (Image*)bit_decompression(file);
		else if(imgP->image_format == HUF)
			temp_image = (Image*)huf_decompression(file);
		else if(imgP->image_format == FRA)
			temp_image = (Image*)frac_decompression(file);
		else if(imgP->image_format == ZVL)
			temp_image = (Image*)zvl_decompression(file);
		else if(imgP->image_format == BTC2)
			temp_image = (Image*)btc2_decompression(file);
		else if(imgP->image_format == BTC3)
			temp_image = (Image*)btc3_decompression(file);
		else if(imgP->image_format == DPC)
			temp_image = (Image*)dpc_decompression(file);
		else if(imgP->image_format == ZON)
			temp_image = (Image*)zon_decompression(file);
		else if(imgP->image_format == ZON2)
			temp_image = (Image*)zon2_decompression(file);
		else if(imgP->image_format == VQ)
			temp_image = (Image*)VQ_read_decompression(file); 
		else if(imgP->image_format == XVQ) 
			temp_image = (Image*)XVQ_read_decompression(file, imgP);
		else if(imgP->image_format == TRCM) 
			temp_image = (Image*)TRCM_read_decompression(file, imgP);
		if(temp_image == NULL)
			return 0;
		imgP->bandP = temp_image->bandP;
		free(temp_image);
	}
	
	return 1;
}	

#define _MAX_HISTORY          (1 << 24)

bool_t xdr_info(
	XDR *xdrs,
	Image *imgP,
	CVIP_BOOLEAN save_history){
	struct history *temp, *temp_pos;
	int history_size = 0;
	
	if(xdrs->x_op == XDR_ENCODE){
		if(imgP->story == NULL){
			return xdr_int(xdrs,(int*)&history_size);
		}
		else{
			history_size = getAllSize_Hist(imgP);
		}
	}
 	if(!xdr_int(xdrs,(int*)&history_size)){
		return 0;
	}
	if(xdrs->x_op == XDR_DECODE && history_size == 0){
		imgP->story = NULL;	
		return 1;
	}

	if(xdrs->x_op == XDR_ENCODE){
		temp = imgP->story;
	}
	else{
		temp = NULL;
	}

	while(1){
		if(!xdr_reference(xdrs,(caddr_t *)&temp, sizeof(struct history),xdr_history)){
			error_CVIP("xdr_history", "XDR I/O failed.");
			return 0;
		}
		if(xdrs->x_op == XDR_ENCODE){
			temp = temp->next;
			if(temp == NULL)
				break;
		}
		else{
			if(imgP->story == NULL){
				temp_pos = imgP->story = temp;
			}
			else{
				temp_pos->next = temp;
				temp_pos = temp_pos->next;
			}
			history_size -= getSize_Hist(temp);
			if(history_size == 0)
				break;
			temp = NULL;
		}
	}
	
	return 1;
}	 
			

bool_t xdr_history(
	XDR *xdrs,			
	HISTORY  story){

	if(!xdr_enum(xdrs,(enum_t *)&story->ftag)){
		error_CVIP("xdr_packet", "XDR I/O failed.");
		return 0;
	}
	return xdr_reference(xdrs,(caddr_t *)&story->packetP, sizeof(PACKET),xdr_packet);

}

bool_t xdr_packet(
	XDR *xdrs,
	PACKET * packet){
	unsigned size;
	int i;
	int mem_size =0;
		
	if(!xdr_u_int(xdrs,(unsigned*)&packet->dsize)){
		error_CVIP("xdr_packet", "XDR I/O failed.");
		return 0;
	}
	size = packet->dsize;
	if(xdrs->x_op == XDR_DECODE){
		packet->dtype = NULL;
		packet->dptr = NULL;
	}
	if(!(xdr_array(xdrs,(caddr_t *)&packet->dtype,&size,_MAX_HISTORY,sizeof(CVIP_TYPE),xdr_enum))){
		error_CVIP("xdr_packet", "XDR I/O failed.");
		return 0;
	}
	if(!(xdr_array(xdrs,(caddr_t *)&packet->dptr,&size,_MAX_HISTORY,sizeof(void *),xdr_long))){
		error_CVIP("xdr_packet", "XDR I/O failed.");
		return 0;
	}

	for(i=0;i < size;i++){
		if(xdrs->x_op == XDR_DECODE){
			packet->dptr[i] = NULL;
		}
		switch(packet->dtype[i]){
			case CVIP_BYTE:
				if(!xdr_reference(xdrs,(caddr_t *)(packet->dptr+i),sizeof(byte),
							xdr_u_char)){
					error_CVIP("xdr_packet", "XDR I/O failed.");
					return 0;
				}
				break;
			case CVIP_SHORT:
				if(!xdr_reference(xdrs,(caddr_t *)(packet->dptr+i),sizeof(short),
							xdr_short)){
					error_CVIP("xdr_packet", "XDR I/O failed.");
					return 0;
				}
				break;
			case CVIP_INTEGER:
				if(!xdr_reference(xdrs,(caddr_t *)(packet->dptr+i),sizeof(int),
							xdr_int)){
					error_CVIP("xdr_packet", "XDR I/O failed.");
					return 0;
				}
			case CVIP_FLOAT:
				if(!xdr_reference(xdrs,(caddr_t *)(packet->dptr+i),sizeof(float),
							xdr_float)){
					error_CVIP("xdr_packet", "XDR I/O failed.");
					return 0;
				}
				break;
			case CVIP_DOUBLE:
				if(!xdr_reference(xdrs,(caddr_t *)(packet->dptr+i),sizeof(short),
							xdr_short)){
					error_CVIP("xdr_packet", "XDR I/O failed.");
					return 0;
				}
				break;
			default:
				return 0;
		}			
	}
	
	return 1;	
}
	
