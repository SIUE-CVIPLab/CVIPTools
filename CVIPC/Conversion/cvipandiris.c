/********************************************************************************Author: Kun Luo
*
*This iris conversion mostly is taken from xv software by John Bradly
*I modified it so it can be incorporated into CVIPtools
*
* Copyright @1995 SIUE - by Kun Luo
* 
* Copyright @1991, 1994 by John Bradly and Paul Haeberli
*
* $Log: cvipandiris.c,v $
* Revision 1.6  1997/03/08 00:43:34  yawei
* Name Changes:
* 	BOOLEAN ==> CVIP_BOOLEAN
* 	FALSE ==> CVIP_NO
* 	TRUE ==> CVIP_YES
* 	BYTE ==> CVIP_BYTE
* 	SHORT ==> CVIP_SHORT
* 	INTEGER ==> CVIP_INTEGER
* 	FLOAT ==> CVIP_FLOAT
* 	DOUBLE ==> CVIP_DOUBLE
* 	TYPE ==> CVIP_TYPE
*
* Revision 1.5  1997/01/15 17:08:09  yawei
* Global Change:  IMAGE ==> Image
*
 * Revision 1.4  1995/08/01  02:30:47  kluo
 * change new_Image argument from ppm to iris
 *
 * Revision 1.3  1995/07/24  17:24:18  kluo
 * fix mix of row and col
 *
 * Revision 1.2  1995/06/19  20:59:15  kluo
 * add a return to iris write
 * output
 *
 * Revision 1.1  1995/06/16  05:04:58  luok
 * Initial revision
 *
******************************************************************************/
#include <CVIPtoolkit.h>
#include <CVIPimage.h>
#include <string.h>



#define IMAGIC 	0732
#define BPPMASK			0x00ff
#define ITYPE_VERBATIM		0x0000
#define ITYPE_RLE		0x0100
#define ISRLE(type)		(((type) & 0xff00) == ITYPE_RLE)
#define ISVERBATIM(type)	(((type) & 0xff00) == ITYPE_VERBATIM)
#define BPP(type)		((type) & BPPMASK)
#define RLE(bpp)		(ITYPE_RLE | (bpp))
#define VERBATIM(bpp)		(ITYPE_VERBATIM | (bpp))


typedef struct {
    u_short	imagic;		/* stuff saved on disk . . */
    u_short 	type;
    u_short 	dim;
    u_short 	xsize;
    u_short 	ysize;
    u_short 	zsize;
    u_long 	min;
    u_long 	max;
    u_long	wastebytes;	
    char 	name[80];
    u_long	colormap;

    long 	file;		/* stuff used in core only */
    u_short 	flags;
    short	dorev;
    short	x;
    short	y;
    short	z;
    short	cnt;
    u_short	*ptr;
    u_short	*base;
    u_short	*tmpbuf;
    u_long	offset;
    u_long	rleend;		/* for rle images */
    u_long	*rowstart;	/* for rle images */
    long	*rowsize;	/* for rle images */
} IRISImage;


#define TAGLEN	(5)
#define FatalError(string)  (fprintf(stderr,string))
#define RINTLUM (79)
#define GINTLUM (156)
#define BINTLUM (21)

#define OFFSET_R	3	/* this is byte order dependent */
#define OFFSET_G	2
#define OFFSET_B	1
#define OFFSET_A	0

#define ILUM(r,g,b)     ((int)(RINTLUM*(r)+GINTLUM*(g)+BINTLUM*(b))>>8)
#define CHANOFFSET(z)	(3-(z))	/* this is byte order dependent */


static int      irisError    (char *, char *);
static byte    *getimagedata (FILE *, IRISImage *);
static void     interleaverow(byte *, byte *, int, int);
static void     expandrow    (byte *, byte *, int);
static void     readtab      (FILE *, u_long *, int);
static void     addimgtag    (byte *, int, int);

static void     lumrow       (byte *, byte *, int);
static int      compressrow  (byte *, byte *, int, int);

static u_short  getshort     (FILE *);
static u_long   getlong      (FILE *);
static void     putshort     (FILE *, int);
static void     putlong      (FILE *, u_long);
static char *BaseName(char*);

int WriteIRIS(FILE *fp,Image *cvipImage);
int LoadIRIS(FILE *fp, Image** input_Image);

static char *loaderr;


void cviptoiris(Image *cvipImage,char *f_name,FILE *fp,int prt_type,int verb){
    char *prog_name[1] = {"cviptoiris"},*fn = "cviptoiris";
    int rows, cols,is_color;

    pnm_init(&verb,prog_name);
    msg_CVIP(fn,"opening IRIS file %s for output.\n", f_name);

    rows = cvipImage->bandP[0]->rows;
    cols = cvipImage->bandP[0]->cols;
    is_color = (cvipImage->bands == 3)?1:0;

    if(!is_color){
	  msg_CVIP(fn,"writing %dx%d Gray Scale Image - %s.\n",rows, cols, f_name);
	  msg_CVIP(fn,"8 bits per sample.\n");
	  msg_CVIP(fn,"1 sample per pixel.\n");
    }
    else{
	  msg_CVIP(fn,"writing %dx%d Color Image - %s.\n",rows, cols, f_name);
	  msg_CVIP(fn,"8 bits per sample.\n");
	  msg_CVIP(fn,"3 samples per pixel.\n");
    }
    WriteIRIS(fp,cvipImage);
}

Image * iristocvip(char *f_name,FILE *fp, int format, int verb){
    char *prog_name[1] = {"iristocvip"},*fn = "iristocvip";
    int rows, cols,is_color;
    Image* cvipImage;
    
    if(!LoadIRIS(fp,&cvipImage))
	return NULL;
   
    pnm_init(&verb,prog_name);
    
    rows = cvipImage->bandP[0]->rows;
    cols = cvipImage->bandP[0]->cols;
    is_color = (cvipImage->bands == 3)?1:0;

    if(is_color){
	      msg_CVIP(fn,"loading %dx%d Color IRIS file - %s.\n",rows, cols, f_name);
	      msg_CVIP(fn,"8 bits per sample.\n");
	      msg_CVIP(fn,"3 samples per pixel.\n");
    }
    else{
	      msg_CVIP(fn,"loading %dx%d Gray Scale IRIS file - %s.\n",rows, cols, f_name);
	      msg_CVIP(fn,"8 bits per sample.\n");
	      msg_CVIP(fn,"1 sample per pixel.\n");
    }
    return cvipImage;
}




char *BaseName(fname)
     char *fname;
{
  char *basname;

  /* given a complete path name ('/foo/bar/weenie.gif'), returns just the 
     'simple' name ('weenie.gif').  Note that it does not make a copy of
     the name, so don't be modifying it... */

  basname = strrchr(fname, '/');
  if (!basname) basname = fname;
  else basname++;

  return basname;
}



int LoadIRIS(FILE *fp, Image** input_Image)
{
  /* returns '1' on success, '0' on failure */

  IRISImage   img;

  byte  **read_data[3];
  byte   *rawdata, *rptr;
  byte   *pic824,  *bptr;
  int     trunc, i, j;
  long    filesize;
  char   *bname;

  trunc = 0;
  memset((char*)&img,0,sizeof(IRISImage));
  bname = BaseName("iristocvip");


  /* figure out the file size */
  fseek(fp, 0L, 2);
  filesize = ftell(fp);
  fseek(fp, 0L, 0);

  /* read header information from file */
  img.imagic = getshort(fp);
  img.type   = getshort(fp);
  img.dim    = getshort(fp);
  img.xsize  = getshort(fp);
  img.ysize  = getshort(fp);
  img.zsize  = getshort(fp);

  if (ferror(fp)) {
    fclose(fp);
    return irisError(bname, "error in header info");
  }

  if (img.imagic != IMAGIC) {
    fclose(fp);
    return irisError(bname, "bad magic number");
  }

  rawdata = getimagedata(fp, &img);
  if (!rawdata) {   
    fclose(fp);
    if (loaderr) irisError(bname, loaderr);
    return 0;
  }

  if (ferror(fp)) trunc = 1;   /* probably truncated file */

  fclose(fp);


  /* got the raw image data.  Convert to an CVIP Image (1,3 bytes / pix) */

  if(img.zsize == 1)
      *input_Image = new_Image(IRIS,GRAY_SCALE,img.zsize,img.ysize, 	
			img.xsize,CVIP_BYTE,REAL);
  else
      *input_Image = new_Image(IRIS,RGB,img.zsize,img.ysize, 	
			img.xsize,CVIP_BYTE,REAL);

  
    


  if (img.zsize < 3) {  /* grayscale */
    read_data[0] = getData_Image(*input_Image,0);

    /* copy plane 3 from rawdata into pic824, inverting pic vertically */
    for (i=0; i<(int)img.ysize; i++) {
      rptr = rawdata + 3 + ((img.ysize - 1) - i) * (img.xsize * 4);
      for (j=0; j<(int)img.xsize; j++,rptr+=4){
	 read_data[0][i][j] = *rptr;
      }
    }

  }

  else {  /* truecolor */
    for(i=0;i<3;i++)
	read_data[i] = getData_Image(*input_Image,i);
    
    /* copy plane 3 from rawdata into pic824, inverting pic vertically */
    for (i=0; i<(int)img.ysize; i++) {
      rptr = rawdata + ((img.ysize - 1) - i) * (img.xsize * 4);
      for (j=0; j<(int)img.xsize; j++, rptr+=4) {
	read_data[0][i][j] = rptr[3];
	read_data[1][i][j] = rptr[2];
	read_data[2][i][j] = rptr[1];
      }
    }

  }

  free(rawdata);

  if (trunc) irisError(bname, "File appears to be truncated.");

  return 1;
}     


/*******************************************/
static int irisError(name, st)
  char *name, *st;
{
  fprintf(stderr,"%s: %s", name, st);
  return 0;
}


/****************************************************/
static byte *getimagedata(fp, img)
     FILE  *fp;
     IRISImage *img;
{
  /* read in a B/W RGB or RGBA iris image file and return a 
     pointer to an array of 4-byte pixels, arranged ABGR, NULL on error */

  byte   *base, *lptr;
  byte   *verdat;
  int     y, z, pos, len, tablen;
  int     xsize, ysize, zsize;
  int     bpp, rle, cur, badorder;
  int     rlebuflen;


  rle     = ISRLE(img->type);
  bpp     = BPP(img->type);
  loaderr = (char *) NULL;

  if (bpp != 1) {
    loaderr = "image must have 1 byte per pix chan";
    return (byte *) NULL;
  }

  xsize = img->xsize;
  ysize = img->ysize;
  zsize = img->zsize;

  if (rle) {
    byte *rledat;
    long *starttab, *lengthtab;

    rlebuflen = 2 * xsize + 10;
    tablen    = ysize * zsize * sizeof(long);
    starttab  = (long *) malloc(tablen);
    lengthtab = (long *) malloc(tablen);
    rledat    = (byte *) malloc(rlebuflen);

    if (!starttab || !lengthtab || !rledat) {
      fprintf(stderr,"out of memory in Load IRIS image");
      exit(1);
    }

    fseek(fp,512,0);
    readtab(fp, (ulong*)starttab,  tablen);
    readtab(fp, (ulong*)lengthtab, tablen);

    if (ferror(fp)) {
      loaderr = "error reading scanline tables";
      free(starttab);  free(lengthtab);  free(rledat);
      return (byte *) NULL;
    }


    /* check data order */
    cur = 0;
    badorder = 0;
    for (y=0; y<ysize && !badorder; y++) {
      for (z=0; z<zsize && !badorder; z++) {
	if (starttab[y+z*ysize] < cur) badorder = 1;
	else cur = starttab[y+z*ysize];
      }
    }

    fseek(fp, 512 + 2*tablen, 0);
    cur = 512 + 2*tablen;

    base = (byte *) malloc((xsize*ysize+TAGLEN) * 4);
    if (!base) FatalError("out of memory in LoadIRIS()");

    addimgtag(base,xsize,ysize);

    if (badorder) {
      for (z=0; z<zsize; z++) {
	lptr = base;
	for (y=0; y<ysize; y++) {
	  if (cur != starttab[y+z*ysize]) {
	    fseek(fp,starttab[y+z*ysize],0);
	    cur = starttab[y+z*ysize];
	  }

	  if (lengthtab[y+z*ysize]>rlebuflen) {
	    FatalError("LoadIRIS() - rlebuf too small");
	  }

	  fread(rledat,lengthtab[y+z*ysize],1,fp);
	  cur += lengthtab[y+z*ysize];
	  expandrow(lptr,rledat,3-z);
	  lptr += (xsize * 4);
	}
      }
    }
    else {
      lptr = base;
      for (y=0; y<ysize; y++) {
	for (z=0; z<zsize; z++) {
	  if (cur != starttab[y+z*ysize]) {
	    fseek(fp,starttab[y+z*ysize],0);
	    cur = starttab[y+z*ysize];
	  }

	  fread(rledat,lengthtab[y+z*ysize],1,fp);
	  cur += lengthtab[y+z*ysize];
	  expandrow(lptr,rledat,3-z);
	}
	lptr += (xsize * 4);
      }
    }

    free(starttab);
    free(lengthtab);
    free(rledat);
    return base;
  }      /* end of RLE case */

  else {  /* not RLE */
    verdat = (byte *) malloc(xsize);
    base   = (byte *) malloc((xsize*ysize+TAGLEN) * 4);
    if (!base || !verdat) FatalError("out of memory in LoadIRIS()");

    addimgtag(base,xsize,ysize);
    
    fseek(fp,512,0);

    for (z=0; z<zsize; z++) {
      lptr = base;
      for (y=0; y<ysize; y++) {
	fread(verdat,xsize,1,fp);
	interleaverow(lptr,verdat,3-z,xsize);
	lptr += (xsize * 4);
      }
    }

    free(verdat);
    return base;
  }
}


/******************************************/
static void interleaverow(lptr,cptr,z,n)
     byte *lptr, *cptr;
     int z, n;
{
  lptr += z;
  while(n--) {
    *lptr = *cptr++;
    lptr += 4;
  }
}


/******************************************/
static void expandrow(optr,iptr,z)
     byte *optr, *iptr;
     int z;
{
  byte pixel, count;

  optr += z;
  while (1) {
    pixel = *iptr++;
    if ( !(count = (pixel & 0x7f)) ) return;
    if (pixel & 0x80) {
      while (count>=8) {
	optr[0*4] = iptr[0];
	optr[1*4] = iptr[1];
	optr[2*4] = iptr[2];
	optr[3*4] = iptr[3];
	optr[4*4] = iptr[4];
	optr[5*4] = iptr[5];
	optr[6*4] = iptr[6];
	optr[7*4] = iptr[7];
	optr += 8*4;
	iptr += 8;
	count -= 8;
      }
      while(count--) {
	*optr = *iptr++;
	optr+=4;
      }
    }
    else {
      pixel = *iptr++;
      while(count>=8) {
	optr[0*4] = pixel;
	optr[1*4] = pixel;
	optr[2*4] = pixel;
	optr[3*4] = pixel;
	optr[4*4] = pixel;
	optr[5*4] = pixel;
	optr[6*4] = pixel;
	optr[7*4] = pixel;
	optr += 8*4;
	count -= 8;
      }
      while(count--) {
	*optr = pixel;
	optr+=4;
      }
    }
  }
}



/****************************************************/
static void readtab(fp, tab, len)
     FILE   *fp;
     u_long *tab;
     int     len;
{
  while(len) {
    *tab++ = getlong(fp);
    len -= 4;
  }
}


/*****************************************************/
static void addimgtag(dptr,xsize,ysize)
     byte *dptr;
     int   xsize, ysize;
{
  /* this is used to extract image data from core dumps. 
     I doubt this is necessary...  --jhb */

  dptr    = dptr + (xsize * ysize * 4);
  dptr[0] = 0x12;  dptr[1] = 0x34;  dptr[2] = 0x56;  dptr[3] = 0x78;
  dptr += 4;

  dptr[0] = 0x59;  dptr[1] = 0x49;  dptr[2] = 0x33;  dptr[3] = 0x33;
  dptr += 4;

  dptr[0] = 0x69;  dptr[1] = 0x43;  dptr[2] = 0x42;  dptr[3] = 0x22;
  dptr += 4;

  dptr[0] = (xsize>>24)&0xff;
  dptr[1] = (xsize>>16)&0xff;
  dptr[2] = (xsize>> 8)&0xff;
  dptr[3] = (xsize    )&0xff;
  dptr += 4;

  dptr[0] = (ysize>>24)&0xff;
  dptr[1] = (ysize>>16)&0xff;
  dptr[2] = (ysize>> 8)&0xff;
  dptr[3] = (ysize    )&0xff;
}










/****************************************************/
static void writetab(FILE *outf,u_long *tab,int n)
{
  while(n) {
    putlong(outf,*tab++);
    n --;
  }
}

/*************************************/
static void lumrow(byte *rgbptr, byte *lumptr,int n) 
{
  lumptr += CHANOFFSET(0);
  while (n--) {
    *lumptr = ILUM(rgbptr[OFFSET_R],rgbptr[OFFSET_G],rgbptr[OFFSET_B]);
    lumptr += 4;
    rgbptr += 4;
  }
}


/*************************************/
static int compressrow(byte *lbuf,byte *rlebuf,int z,int cnt)
{
  byte *iptr, *ibufend, *sptr, *optr;
  short todo, cc;							
  long  count;

  lbuf    += z;
  iptr    = lbuf;
  ibufend = iptr+cnt*4;
  optr    = rlebuf;

  while (iptr<ibufend) {
    sptr = iptr;
    iptr += 8;
    while ((iptr<ibufend) && ((iptr[-8]!=iptr[-4])||(iptr[-4]!=iptr[0])))
      iptr += 4;
    iptr -= 8;

    count = (iptr-sptr)/4;

    while (count) {
      todo = count>126 ? 126 : count;
      count -= todo;
      *optr++ = 0x80|todo;
      while (todo>8) {
	optr[0] = sptr[0*4];
	optr[1] = sptr[1*4];
	optr[2] = sptr[2*4];
	optr[3] = sptr[3*4];
	optr[4] = sptr[4*4];
	optr[5] = sptr[5*4];
	optr[6] = sptr[6*4];
	optr[7] = sptr[7*4];
	optr += 8;
	sptr += 8*4;
	todo -= 8;
      }

      while (todo--) {
	*optr++ = *sptr;
	sptr += 4;
      }
    }

    sptr = iptr;
    cc = *iptr;
    iptr += 4;
    while ((iptr<ibufend) && (*iptr == cc))  iptr += 4;
    
    count = (iptr-sptr)/4;
    while (count) {
      todo = count>126 ? 126:count;
      count -= todo;
      *optr++ = todo;
      *optr++ = cc;
    }
  }
  
  *optr++ = 0;
  return (optr - rlebuf);
}





/* byte order independent read/write of shorts and longs. */

static u_short getshort(FILE *inf)
{
  byte buf[2];
  fread(buf, (size_t) 2, (size_t) 1,inf);
  return (buf[0]<<8)+(buf[1]<<0);
}


static u_long getlong(FILE *inf)
{
  byte buf[4];
  fread(buf, (size_t) 4, (size_t) 1,inf);
  return (((u_long) buf[0])<<24) + (((u_long) buf[1])<<16)
       + (((u_long) buf[2])<<8) + buf[3];
}


static void putshort(FILE *outf, int val)
{
  byte buf[2];
  buf[0] = (val>>8);
  buf[1] = (val>>0);
  fwrite(buf,(size_t) 2,(size_t) 1,outf);
}


static void putlong(FILE *outf,u_long val)
{
  byte buf[4];
  buf[0] = (val>>24);
  buf[1] = (val>>16);
  buf[2] = (val>>8);
  buf[3] = (val>>0);
  fwrite(buf,(size_t) 4,(size_t) 1,outf);
}



int WriteIRIS(FILE *fp,Image *cvipImage){
  IRISImage img;
  int     i, j, pos, len, tablen, rlebuflen,w,h;
  u_long *starttab, *lengthtab;
  byte   *rlebuf;
  byte   *lumbuf, *lptr, *longpic;
  byte   ** r_image, **g_image, **b_image;

  /* write header information */
  fwrite(&img, sizeof(Image), (size_t) 1, fp);
  fseek(fp, 0L, 0);

  img.imagic = IMAGIC;
  img.type   = ITYPE_RLE | (1 & BPPMASK);   /* RLE, 1 byteperpix */
  img.dim    = (cvipImage->bands == 3) ? 3 : 2;
  img.xsize  = cvipImage->bandP[0]->cols;
  img.ysize  = cvipImage->bandP[0]->rows;
  img.zsize  = (cvipImage->bands == 3) ? 3 : 1;
  img.min    = 0;
  img.max    = 255;

  putshort(fp, img.imagic);
  putshort(fp, img.type);
  putshort(fp, img.dim);
  putshort(fp, img.xsize);
  putshort(fp, img.ysize);
  putshort(fp, img.zsize);
  putlong (fp, img.min);
  putlong (fp, img.max);
  putlong (fp, 0L);
  fwrite  ("no name", (size_t) 8, (size_t) 1,fp);

  w = cvipImage->bandP[0]->cols;
  h = cvipImage->bandP[0]->rows;

  if (ferror(fp)) { fclose(fp); return -1; }

  /* allocate RLE compression tables & stuff */
  rlebuflen = 2*w + 10;
  tablen    = h * cvipImage->bands;

  starttab  = (u_long *) malloc((size_t) tablen * sizeof(long));
  lengthtab = (u_long *) malloc((size_t) tablen * sizeof(long));
  rlebuf    = (byte *)   malloc((size_t) rlebuflen);
  lumbuf    = (byte *)   malloc((size_t) w * 4);

  if (!starttab || !lengthtab || !rlebuf || !lumbuf){ 
    fprintf(stderr,"write_Image:out of memory in WriteIRIS()");
    exit(1);
  }

  pos = 512 + 2 * (tablen * 4);
  fseek(fp, (long) pos, 0);

  /* convert image into 4-byte per pix image that the compress routines want */
  longpic = (byte *) malloc((size_t) w * h * 4);
  if (!longpic){
    fprintf(stderr,"write_Image:out of memory in WriteIRIS()");
    return -1;
  }
  if(cvipImage->bands == 3){
     r_image = getData_Image(cvipImage,0);
     g_image = getData_Image(cvipImage,1);
     b_image = getData_Image(cvipImage,2);
  }
  else{
     r_image = g_image = b_image = getData_Image(cvipImage,0);
  }

  for (i=0; i<h; i++) {
    lptr = longpic + ((h-1) - i) * (w * 4);    /* vertical flip */
    for (j=0; j<w; j++) {
	*lptr++ = 0xff;
	*lptr++ = b_image[i][j];
	*lptr++ = g_image[i][j];
	*lptr++ = r_image[i][j];
    }
  }
      


  /* compress and write the data */
  lptr = longpic;
  for (i=0; i<h; i++) {
    for (j=0; j<cvipImage->bands; j++) {
      if (cvipImage->bands == 1) {
	lumrow(lptr, lumbuf, w);
	len = compressrow(lumbuf, rlebuf, CHANOFFSET(j), w);
      } 
      else {
	len = compressrow(lptr, rlebuf, CHANOFFSET(j), w);
      }

      if (len > rlebuflen) {
	fprintf(stderr,"WriteIRIS: rlebuf is too small");
	return -1;
      }

      fwrite(rlebuf, (size_t) len, (size_t) 1, fp);
      starttab [i + j*h] = pos;
      lengthtab[i + j*h] = len;
      pos += len;
    }
    lptr += (w*4);
  }


  /* write out line start and length tables */
  fseek   (fp, 512L, 0);
  writetab(fp, starttab, tablen);
  writetab(fp, lengthtab,tablen);

  free(starttab);
  free(lengthtab);
  free(rlebuf);
  free(lumbuf);
  free(longpic);

  if (ferror(fp)){ return -1;}

  return 0;
}
  
