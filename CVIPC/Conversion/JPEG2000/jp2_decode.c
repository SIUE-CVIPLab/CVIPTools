/* CVIPtools>> */
#include "CVIPtoolkit.h"
#include "CVIPconvert.h"
#include "CVIPdef.h"
#include "CVIPimage.h"
/* <<CVIPtools */

#include "openjpeg.h"
#include "dirent.h"
#include "getopt.h"

#define J2K_CFMT 0
#define JP2_CFMT 1
#define JPT_CFMT 2

#define PXM_DFMT 10
#define PGX_DFMT 11
#define BMP_DFMT 12
#define YUV_DFMT 13
#define TIF_DFMT 14
#define RAW_DFMT 15
#define TGA_DFMT 16

/* ----------------------------------------------------------------------- */

typedef struct dircnt{
	/** Buffer for holding images read from Directory*/
	char *filename_buf;
	/** Pointer to the buffer*/
	char **filename;
}dircnt_t;


typedef struct img_folder{
	/** The directory path of the folder containing input images*/
	char *imgdirpath;
	/** Output format*/
	char *out_format;
	/** Enable option*/
	char set_imgdir;
	/** Enable Cod Format for output*/
	char set_out_format;

}img_fol_t;

void decode_help_display() {
	fprintf(stdout,"HELP\n----\n\n");
	fprintf(stdout,"- the -h option displays this help information on screen\n\n");

/* UniPG>> */
	fprintf(stdout,"List of parameters for the JPEG 2000 "
#ifdef USE_JPWL
		"+ JPWL "
#endif /* USE_JPWL */
		"decoder:\n");
/* <<UniPG */
	fprintf(stdout,"\n");
	fprintf(stdout,"\n");
	fprintf(stdout,"  -ImgDir \n");
	fprintf(stdout,"	Image file Directory path \n");
	fprintf(stdout,"  -OutFor \n");
	fprintf(stdout,"    REQUIRED only if -ImgDir is used\n");
	fprintf(stdout,"	  Need to specify only format without filename <BMP>  \n");
	fprintf(stdout,"    Currently accepts PGM, PPM, PNM, PGX, BMP, TIF, RAW and TGA formats\n");
	fprintf(stdout,"  -i <compressed file>\n");
	fprintf(stdout,"    REQUIRED only if an Input image directory not specified\n");
	fprintf(stdout,"    Currently accepts J2K-files, JP2-files and JPT-files. The file type\n");
	fprintf(stdout,"    is identified based on its suffix.\n");
	fprintf(stdout,"  -o <decompressed file>\n");
	fprintf(stdout,"    REQUIRED\n");
	fprintf(stdout,"    Currently accepts PGM, PPM, PNM, PGX, BMP, TIF, RAW and TGA files\n");
	fprintf(stdout,"    Binary data is written to the file (not ascii). If a PGX\n");
	fprintf(stdout,"    filename is given, there will be as many output files as there are\n");
	fprintf(stdout,"    components: an indice starting from 0 will then be appended to the\n");
	fprintf(stdout,"    output filename, just before the \"pgx\" extension. If a PGM filename\n");
	fprintf(stdout,"    is given and there are more than one component, only the first component\n");
	fprintf(stdout,"    will be written to the file.\n");
	fprintf(stdout,"  -r <reduce factor>\n");
	fprintf(stdout,"    Set the number of highest resolution levels to be discarded. The\n");
	fprintf(stdout,"    image resolution is effectively divided by 2 to the power of the\n");
	fprintf(stdout,"    number of discarded levels. The reduce factor is limited by the\n");
	fprintf(stdout,"    smallest total number of decomposition levels among tiles.\n");
	fprintf(stdout,"  -l <number of quality layers to decode>\n");
	fprintf(stdout,"    Set the maximum number of quality layers to decode. If there are\n");
	fprintf(stdout,"    less quality layers than the specified number, all the quality layers\n");
	fprintf(stdout,"    are decoded.\n");
	fprintf(stdout,"  -x  \n"); 
	fprintf(stdout,"    Create an index file *.Idx (-x index_name.Idx) \n");
	fprintf(stdout,"\n");
/* UniPG>> */
#ifdef USE_JPWL
	fprintf(stdout,"  -W <options>\n");
	fprintf(stdout,"    Activates the JPWL correction capability, if the codestream complies.\n");
	fprintf(stdout,"    Options can be a comma separated list of <param=val> tokens:\n");
	fprintf(stdout,"    c, c=numcomps\n");
	fprintf(stdout,"       numcomps is the number of expected components in the codestream\n");
	fprintf(stdout,"       (search of first EPB rely upon this, default is %d)\n", JPWL_EXPECTED_COMPONENTS);
#endif /* USE_JPWL */
/* <<UniPG */
	fprintf(stdout,"\n");
}

/* -------------------------------------------------------------------------- */

int get_num_images(char *imgdirpath){
	DIR *dir;
	struct dirent* content;	
	int num_images = 0;

	/*Reading the input images from given input directory*/

	dir= opendir(imgdirpath);
	if(!dir){
		fprintf(stderr,"Could not open Folder %s\n",imgdirpath);
		return 0;
	}
	
	while((content=readdir(dir))!=NULL){
		if(strcmp(".",content->d_name)==0 || strcmp("..",content->d_name)==0 )
			continue;
		num_images++;
	}
	return num_images;
}

int load_images(dircnt_t *dirptr, char *imgdirpath){
	DIR *dir;
	struct dirent* content;	
	int i = 0;

	/*Reading the input images from given input directory*/

	dir= opendir(imgdirpath);
	if(!dir){
		fprintf(stderr,"Could not open Folder %s\n",imgdirpath);
		return 1;
	}else	{
		fprintf(stderr,"Folder opened successfully\n");
	}
	
	while((content=readdir(dir))!=NULL){
		if(strcmp(".",content->d_name)==0 || strcmp("..",content->d_name)==0 )
			continue;

		strcpy(dirptr->filename[i],content->d_name);
		i++;
	}
	return 0;	
}

int get_file_format(char *filename) {
	unsigned int i;
	static const char *extension[] = {"pgx", "pnm", "pgm", "ppm", "bmp","tif", "raw", "tga", "j2k", "jp2", "jpt", "j2c" };
	static const int format[] = { PGX_DFMT, PXM_DFMT, PXM_DFMT, PXM_DFMT, BMP_DFMT, TIF_DFMT, RAW_DFMT, TGA_DFMT, J2K_CFMT, JP2_CFMT, JPT_CFMT, J2K_CFMT };
	char * ext = strrchr(filename, '.');
	if (ext == NULL)
		return -1;
	ext++;
	if(ext) {
		for(i = 0; i < sizeof(format)/sizeof(*format); i++) {
			if(strnicmp(ext, extension[i], 3) == 0) {
				return format[i];
			}
		}
	}

	return -1;
}

char get_next_file(int imageno,dircnt_t *dirptr,img_fol_t *img_fol, opj_dparameters_t *parameters){
	char image_filename[OPJ_PATH_LEN], infilename[OPJ_PATH_LEN],outfilename[OPJ_PATH_LEN],temp_ofname[OPJ_PATH_LEN];
	char *temp_p, temp1[OPJ_PATH_LEN]="";

	strcpy(image_filename,dirptr->filename[imageno]);
	fprintf(stderr,"File Number %d \"%s\"\n",imageno,image_filename);
	parameters->decod_format = get_file_format(image_filename);
	if (parameters->decod_format == -1)
		return 1;
	sprintf(infilename,"%s/%s",img_fol->imgdirpath,image_filename);
	strncpy(parameters->infile, infilename, sizeof(infilename));

	//Set output file
	strcpy(temp_ofname,strtok(image_filename,"."));
	while((temp_p = strtok(NULL,".")) != NULL){
		strcat(temp_ofname,temp1);
		sprintf(temp1,".%s",temp_p);
	}
	if(img_fol->set_out_format==1){
		sprintf(outfilename,"%s/%s.%s",img_fol->imgdirpath,temp_ofname,img_fol->out_format);
		strncpy(parameters->outfile, outfilename, sizeof(outfilename));
	}
	return 0;
}

/* -------------------------------------------------------------------------- */
int parse_cmdline_decoder(int argc, char **argv, opj_dparameters_t *parameters,img_fol_t *img_fol, char *indexfilename) {
	/* parse the command line */
	int totlen;
	option_t long_option[]={
		{"ImgDir",REQ_ARG, NULL ,'y'},
		{"OutFor",REQ_ARG, NULL ,'O'},
	};

	const char optlist[] = "i:o:r:l:hx:"

/* UniPG>> */
#ifdef USE_JPWL
					"W:"
#endif /* USE_JPWL */
/* <<UniPG */
					;
	totlen=sizeof(long_option);
	img_fol->set_out_format = 0;
	while (1) {
		int c = getopt_long(argc, argv,optlist,long_option,totlen);
		if (c == -1)
			break;
		switch (c) {
			case 'i':			/* input file */
			{
				char *infile = optarg;
				parameters->decod_format = get_file_format(infile);
				switch(parameters->decod_format) {
					case J2K_CFMT:
					case JP2_CFMT:
					case JPT_CFMT:
						break;
					default:
						fprintf(stderr, 
							"!! Unrecognized format for infile : %s [accept only *.j2k, *.jp2, *.jpc or *.jpt] !!\n\n", 
							infile);
						return 1;
				}
				strncpy(parameters->infile, infile, sizeof(parameters->infile)-1);
			}
			break;
				
				/* ----------------------------------------------------- */

			case 'o':			/* output file */
			{
				char *outfile = optarg;
				parameters->cod_format = get_file_format(outfile);
				switch(parameters->cod_format) {
					case PGX_DFMT:
					case PXM_DFMT:
					case BMP_DFMT:
					case TIF_DFMT:
					case RAW_DFMT:
					case TGA_DFMT:
						break;
					default:
						fprintf(stderr, "Unknown output format image %s [only *.pnm, *.pgm, *.ppm, *.pgx, *.bmp, *.tif, *.raw or *.tga]!! \n", outfile);
						return 1;
				}
				strncpy(parameters->outfile, outfile, sizeof(parameters->outfile)-1);
			}
			break;
			
				/* ----------------------------------------------------- */

			case 'O':			/* output format */
			{
				char outformat[50];
				char *of = optarg;
				sprintf(outformat,".%s",of);
				img_fol->set_out_format = 1;
				parameters->cod_format = get_file_format(outformat);
				switch(parameters->cod_format) {
					case PGX_DFMT:
						img_fol->out_format = "pgx";
						break;
					case PXM_DFMT:
						img_fol->out_format = "ppm";
						break;
					case BMP_DFMT:
						img_fol->out_format = "bmp";
						break;
					case TIF_DFMT:
						img_fol->out_format = "tif";
						break;
					case RAW_DFMT:
						img_fol->out_format = "raw";
						break;
					case TGA_DFMT:
						img_fol->out_format = "raw";
						break;
					default:
						fprintf(stderr, "Unknown output format image %s [only *.pnm, *.pgm, *.ppm, *.pgx, *.bmp, *.tif, *.raw or *.tga]!! \n", outformat);
						return 1;
						break;
				}
			}
			break;

				/* ----------------------------------------------------- */


			case 'r':		/* reduce option */
			{
				sscanf(optarg, "%d", &parameters->cp_reduce);
			}
			break;
			
				/* ----------------------------------------------------- */
      

			case 'l':		/* layering option */
			{
				sscanf(optarg, "%d", &parameters->cp_layer);
			}
			break;
			
				/* ----------------------------------------------------- */

			case 'h': 			/* display an help description */
				decode_help_display();
				return 1;				

				/* ------------------------------------------------------ */

			case 'y':			/* Image Directory path */
				{
					img_fol->imgdirpath = (char*)malloc(strlen(optarg) + 1);
					strcpy(img_fol->imgdirpath,optarg);
					img_fol->set_imgdir=1;
				}
				break;
				/* ----------------------------------------------------- */								
			case 'x':			/* Creation of index file */
				{
					char *index = optarg;
					strncpy(indexfilename, index, OPJ_PATH_LEN);
				}
				break;
				/* ----------------------------------------------------- */
				/* UniPG>> */
#ifdef USE_JPWL
			
			case 'W': 			/* activate JPWL correction */
			{
				char *token = NULL;

				token = strtok(optarg, ",");
				while(token != NULL) {

					/* search expected number of components */
					if (*token == 'c') {

						static int compno;

						compno = JPWL_EXPECTED_COMPONENTS; /* predefined no. of components */

						if(sscanf(token, "c=%d", &compno) == 1) {
							/* Specified */
							if ((compno < 1) || (compno > 256)) {
								fprintf(stderr, "ERROR -> invalid number of components c = %d\n", compno);
								return 1;
							}
							parameters->jpwl_exp_comps = compno;

						} else if (!strcmp(token, "c")) {
							/* default */
							parameters->jpwl_exp_comps = compno; /* auto for default size */

						} else {
							fprintf(stderr, "ERROR -> invalid components specified = %s\n", token);
							return 1;
						};
					}

					/* search maximum number of tiles */
					if (*token == 't') {

						static int tileno;

						tileno = JPWL_MAXIMUM_TILES; /* maximum no. of tiles */

						if(sscanf(token, "t=%d", &tileno) == 1) {
							/* Specified */
							if ((tileno < 1) || (tileno > JPWL_MAXIMUM_TILES)) {
								fprintf(stderr, "ERROR -> invalid number of tiles t = %d\n", tileno);
								return 1;
							}
							parameters->jpwl_max_tiles = tileno;

						} else if (!strcmp(token, "t")) {
							/* default */
							parameters->jpwl_max_tiles = tileno; /* auto for default size */

						} else {
							fprintf(stderr, "ERROR -> invalid tiles specified = %s\n", token);
							return 1;
						};
					}

					/* next token or bust */
					token = strtok(NULL, ",");
				};
				parameters->jpwl_correct = true;
				fprintf(stdout, "JPWL correction capability activated\n");
				fprintf(stdout, "- expecting %d components\n", parameters->jpwl_exp_comps);
			}
			break;	
#endif /* USE_JPWL */
/* <<UniPG */            

				/* ----------------------------------------------------- */
			
			default:
				fprintf(stderr,"WARNING -> this option is not valid \"-%c %s\"\n",c, optarg);
				break;
		}
	}

	/* check for possible errors */
	if(img_fol->set_imgdir==1){
		if(!(parameters->infile[0]==0)){
			fprintf(stderr, "Error: options -ImgDir and -i cannot be used together !!\n");
			return 1;
		}
		if(img_fol->set_out_format == 0){
			fprintf(stderr, "Error: When -ImgDir is used, -OutFor <FORMAT> must be used !!\n");
			fprintf(stderr, "Only one format allowed! Valid format PGM, PPM, PNM, PGX, BMP, TIF, RAW and TGA!!\n");
			return 1;
		}
		if(!((parameters->outfile[0] == 0))){
			fprintf(stderr, "Error: options -ImgDir and -o cannot be used together !!\n");
			return 1;
		}
	}else{
		if((parameters->infile[0] == 0) || (parameters->outfile[0] == 0)) {
			fprintf(stderr, "Error: One of the options -i or -ImgDir must be specified\n");
			fprintf(stderr, "Error: When using -i, -o must be used\n");
			fprintf(stderr, "usage: image_to_j2k -i *.j2k/jp2/j2c -o *.pgm/ppm/pnm/pgx/bmp/tif/raw/tga(+ options)\n");
			return 1;
		}
	}

	return 0;
}

/* -------------------------------------------------------------------------- */

/**
sample error callback expecting a FILE* client object
*/
void error_callback(const char *msg, void *client_data) {
	FILE *stream = (FILE*)client_data;
	fprintf(stream, "[ERROR] %s", msg);
}
/**
sample warning callback expecting a FILE* client object
*/
void warning_callback(const char *msg, void *client_data) {
	FILE *stream = (FILE*)client_data;
	fprintf(stream, "[WARNING] %s", msg);
}
/**
sample debug callback expecting no client object
*/
void info_callback(const char *msg, void *client_data) {
	(void)client_data;
//	fprintf(stdout, "[INFO] %s", msg);
}

/* -------------------------------------------------------------------------- */

Image* jp2_decoder(char iImage[])
{
	Image* inputImage;
	int argc = 5;
	char *argv[] ={{"C:\Documents and Settings\Serkan Kefel\Desktop\CVIPlab-NET with JPEG2000\CVIPlab\Debug\CVIPlab_Project.exe"}, {"-i"}, {"cam.jp2"}, {"-o"}, {"cam2.pgm"}};
	char *iExt, *oExt;

	opj_dparameters_t parameters;	/* decompression parameters */
	img_fol_t img_fol;
	opj_event_mgr_t event_mgr;		/* event manager */
	opj_image_t *image = NULL;
	FILE *fsrc = NULL;
	unsigned char *src = NULL;
	int file_length;
	int num_images;
	int i,imageno;
	dircnt_t *dirptr;
	opj_dinfo_t* dinfo = NULL;	/* handle to a decompressor */
	opj_cio_t *cio = NULL;
	opj_codestream_info_t cstr_info;  /* Codestream information structure */
	char indexfilename[OPJ_PATH_LEN];	/* index file name */

	/* configure the event callbacks (not required) */
	memset(&event_mgr, 0, sizeof(opj_event_mgr_t));
	event_mgr.error_handler = error_callback;
	event_mgr.warning_handler = warning_callback;
	event_mgr.info_handler = info_callback;

	/* set decoding parameters to default values */
	opj_set_default_decoder_parameters(&parameters);

	/* Initialize indexfilename and img_fol */
	*indexfilename = 0;
	memset(&img_fol,0,sizeof(img_fol_t));

	/* parse input and get user encoding parameters */
//	if(parse_cmdline_decoder(argc, argv, &parameters,&img_fol, indexfilename) == 1) {
//		return 1;
//	}

	strcpy(parameters.infile, iImage);
	for(i = 0; i < 1000; i++)
	{
		if(iImage[i] == '.')
			if(iImage[i+1] == 'j' || iImage[i+1] == 'J' || iImage[i+1] == 't' || iImage[i+1] == 'T')
				if(iImage[i+2] == 'p' || iImage[i+2] == 'P' || iImage[i+2] == 'm' || iImage[i+2] == 'M')
				{
					if(iImage[i+3] == '2' || iImage[i+3] == 'p' || iImage[i+3] == 'P')
					{
						parameters.decod_format = 1;
						break;
					}
				}
				else if(iImage[i+2] == '2')
				{
					if(iImage[i+3] == 'k' || iImage[i+3] == 'K')
					{
						parameters.decod_format = 0;
						break;
					}
				}
	}

	parameters.cod_format = 10;


	num_images = 1;

	/*Encoding image one by one*/
	for(imageno = 0; imageno < num_images ; imageno++)
	{
		image = NULL;
//		fprintf(stderr,"\n");

		/* read the input file and put it in memory */
		/* ---------------------------------------- */
		fsrc = fopen(parameters.infile, "rb");
		if (!fsrc) 
		{
			fprintf(stderr, "ERROR -> failed to open %s for reading\n", parameters.infile);
			return 1;
		}
		fseek(fsrc, 0, SEEK_END);
		file_length = ftell(fsrc);
		fseek(fsrc, 0, SEEK_SET);
		src = (unsigned char *) malloc(file_length);
		fread(src, 1, file_length, fsrc);
		fclose(fsrc);

		/* decode the code-stream */
		/* ---------------------- */

		switch(parameters.decod_format) 
		{
			case J2K_CFMT:
			{
				/* JPEG-2000 codestream */

				/* get a decoder handle */
				dinfo = opj_create_decompress(CODEC_J2K);

				/* catch events using our callbacks and give a local context */
				opj_set_event_mgr((opj_common_ptr)dinfo, &event_mgr, stderr);

				/* setup the decoder decoding parameters using user parameters */
				opj_setup_decoder(dinfo, &parameters);

				/* open a byte stream */
				cio = opj_cio_open((opj_common_ptr)dinfo, src, file_length);

				/* decode the stream and fill the image structure */
				if (*indexfilename)				// If need to extract codestream information
					image = opj_decode_with_info(dinfo, cio, &cstr_info);
				else
					image = opj_decode(dinfo, cio);
				if(!image) 
				{
					fprintf(stderr, "ERROR -> j2k_to_image: failed to decode image!\n");
					opj_destroy_decompress(dinfo);
					opj_cio_close(cio);
					return 1;
				}

				/* close the byte stream */
				opj_cio_close(cio);

				/* Write the index to disk */
				if (*indexfilename) 
				{
					char bSuccess;
					bSuccess = write_index_file(&cstr_info, indexfilename);
					if (bSuccess) 
					{
						fprintf(stderr, "Failed to output index file\n");
					}
				}
			}
			break;

			case JP2_CFMT:
			{
				/* JPEG 2000 compressed image data */

				/* get a decoder handle */
				dinfo = opj_create_decompress(CODEC_JP2);

				/* catch events using our callbacks and give a local context */
				opj_set_event_mgr((opj_common_ptr)dinfo, &event_mgr, stderr);

				/* setup the decoder decoding parameters using the current image and user parameters */
				opj_setup_decoder(dinfo, &parameters);

				/* open a byte stream */
				cio = opj_cio_open((opj_common_ptr)dinfo, src, file_length);

				/* decode the stream and fill the image structure */
				if (*indexfilename)				// If need to extract codestream information
					image = opj_decode_with_info(dinfo, cio, &cstr_info);
				else
					image = opj_decode(dinfo, cio);			
				if(!image) 
				{
					fprintf(stderr, "ERROR -> j2k_to_image: failed to decode image!\n");
					opj_destroy_decompress(dinfo);
					opj_cio_close(cio);
					return 1;
				}

				/* close the byte stream */
				opj_cio_close(cio);

				/* Write the index to disk */
				if (*indexfilename) 
				{
					char bSuccess;
					bSuccess = write_index_file(&cstr_info, indexfilename);
					if (bSuccess) 
					{
						fprintf(stderr, "Failed to output index file\n");
					}
				}
			}
			break;

			//case JPT_CFMT:
			//{
			//	/* JPEG 2000, JPIP */

			//	/* get a decoder handle */
			//	dinfo = opj_create_decompress(CODEC_JPT);

			//	/* catch events using our callbacks and give a local context */
			//	opj_set_event_mgr((opj_common_ptr)dinfo, &event_mgr, stderr);

			//	/* setup the decoder decoding parameters using user parameters */
			//	opj_setup_decoder(dinfo, &parameters);

			//	/* open a byte stream */
			//	cio = opj_cio_open((opj_common_ptr)dinfo, src, file_length);

			//	/* decode the stream and fill the image structure */
			//	if (*indexfilename)				// If need to extract codestream information
			//		image = opj_decode_with_info(dinfo, cio, &cstr_info);
			//	else
			//		image = opj_decode(dinfo, cio);
			//	if(!image) {
			//		fprintf(stderr, "ERROR -> j2k_to_image: failed to decode image!\n");
			//		opj_destroy_decompress(dinfo);
			//		opj_cio_close(cio);
			//		return 1;
			//	}

			//	/* close the byte stream */
			//	opj_cio_close(cio);

			//	/* Write the index to disk */
			//	if (*indexfilename) {
			//		char bSuccess;
			//		bSuccess = write_index_file(&cstr_info, indexfilename);
			//		if (bSuccess) {
			//			fprintf(stderr, "Failed to output index file\n");
			//		}
			//	}
			//}
			//break;

			default:
				fprintf(stderr, "skipping file..\n");
			continue;
		}

		/* free the memory containing the code-stream */
		free(src);
		src = NULL;
		
		/*  CONVERT IMAGE TO VIP  */
		inputImage = opjtocvip(image);

		///* create output image */
		///* ------------------- */
		//switch (parameters.cod_format) {
		//case PXM_DFMT:			/* PNM PGM PPM */
		//	if (imagetopnm(image, parameters.outfile)) {
		//		fprintf(stdout,"Outfile %s not generated\n",parameters.outfile);
		//	}
		//	else {
		//		fprintf(stdout,"Generated Outfile %s\n",parameters.outfile);
		//	}
		//	break;

		//case PGX_DFMT:			/* PGX */
		//	if(imagetopgx(image, parameters.outfile)){
		//		fprintf(stdout,"Outfile %s not generated\n",parameters.outfile);
		//	}
		//	else {
		//		fprintf(stdout,"Generated Outfile %s\n",parameters.outfile);
		//	}
		//	break;

		//case BMP_DFMT:			/* BMP */
		//	if(imagetobmp(image, parameters.outfile)){
		//		fprintf(stdout,"Outfile %s not generated\n",parameters.outfile);
		//	}
		//	else {
		//		fprintf(stdout,"Generated Outfile %s\n",parameters.outfile);
		//	}
		//	break;

		//case TIF_DFMT:			/* TIFF */
		//	if(imagetotif(image, parameters.outfile)){
		//		fprintf(stdout,"Outfile %s not generated\n",parameters.outfile);
		//	}
		//	else {
		//		fprintf(stdout,"Generated Outfile %s\n",parameters.outfile);
		//	}
		//	break;

		//case RAW_DFMT:			/* RAW */
		//	if(imagetoraw(image, parameters.outfile)){
		//		fprintf(stdout,"Error generating raw file. Outfile %s not generated\n",parameters.outfile);
		//	}
		//	else {
		//		fprintf(stdout,"Successfully generated Outfile %s\n",parameters.outfile);
		//	}
		//	break;

		//case TGA_DFMT:			/* TGA */
		//	if(imagetotga(image, parameters.outfile)){
		//		fprintf(stdout,"Error generating tga file. Outfile %s not generated\n",parameters.outfile);
		//	}
		//	else {
		//		fprintf(stdout,"Successfully generated Outfile %s\n",parameters.outfile);
		//	}
		//	break;
		//}

		///* free remaining structures */
		//if(dinfo) 
		//{
		//	opj_destroy_decompress(dinfo);
		//}
		///* free codestream information structure */
		//if (*indexfilename)	
		//	opj_destroy_cstr_info(&cstr_info);
		///* free image data structure */
		opj_image_destroy(image);
	}
	return inputImage;
}