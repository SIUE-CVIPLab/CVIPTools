/***************************************************************************
* ======================================================================
* Computer Vision/Image Processing Tool Project - Dr. Scott Umbaugh SIUE
* ======================================================================
*    
*             File Name: spatial_filter.c
*           Description:  contain spatial filters
*         Related Files: 
*   Initial Coding Date: Sun April 17, 15:54:12 CDT 1995
*           Portability: Standard (ANSI) C
*             Credit(s): Kun Luo, John  Creighton
*                        Southern Illinois University @ Edwardsville
*
** Copyright (C) 1995 SIUE - by  Kun Luo, John Creighton
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
**
** $Log: spatial_filter.c,v $
** Revision 1.11  1997/07/26 17:48:27  smakam
** corrected the code for midpoint filter
**
** Revision 1.10  1997/03/08 01:03:20  yawei
** Name Changes:
** 	BOOLEAN ==> CVIP_BOOLEAN
** 	FALSE ==> CVIP_YES
** 	TRUE ==> CVIP_NO
** 	BYTE ==> CVIP_BYTE
** 	SHORT ==> CVIP_SHORT
** 	INTEGER ==> CVIP_INTEGER
** 	FLOAT ==> CVIP_FLOAT
** 	DOUBLE ==> CVIP_DOUBLE
** 	TYPE ==> CVIP_TYPE
**
** Revision 1.9  1997/01/15 17:21:08  yawei
** Global Change:  IMAGE ==> Image
**
 * Revision 1.8  1996/12/24  18:42:15  yawei
 * chaged function name:
 *   alfa_filter ==> alpha_filter
 *
 * Revision 1.7  1996/01/23  18:26:11  kluo
 * check in
 *
 * Revision 1.6  1995/07/31  17:33:54  kluo
 * add header
 *
 * Revision 1.5  1995/06/16  05:28:52  luok
 * get rid of abs function in YP mean
 *
 * Revision 1.4  1995/06/12  19:18:26  luok
 * modify the left over =
 *
 * Revision 1.3  1995/06/12  14:00:52  luok
 * fix a bug in new-added filters, not use = in the outer loop.
 *
 * Revision 1.2  1995/06/09  02:56:35  luok
 * rewrite alapha-trim, harmonic, YPmean, contra-harmonic filters
 * completely
 *
 * Revision 1.1  1995/06/06  23:55:38  luok
 * Initial revision
 *
 * Revision 1.1  1995/04/17  21:23:27  luok
 * Initial revision
 *
****************************************************************************/
#include <CVIPspfltr.h>
#include <float.h>

Image* ad_filter(Image *, int, int, int);


Image* minimum_setup(Image *cvipImage)      
  {      
     int mask_size;      
printf(" ***************   THE MINIMUM FILTER   ***********\n");             
      
do{      
	printf("\nType in an integer value [3,5,7,9 or 11] for mask size:");      
	scanf("%d",&mask_size);      
      
if(mask_size == 3) break;      
if(mask_size == 5) break;      
if(mask_size == 7) break;      
if(mask_size == 9) break;      
if(mask_size == 11) break;      
else printf("\nInvalid Selection !!!!!  Try Again !!!!!\n");      
}while(1);      
      
return minimum_filter(cvipImage,mask_size);      
}      
      
Image* minimum_filter(Image *imageP, int mask_size)      
       {      
	Image  *imageW;
        int NN;  
	register int    i, j, k, JJ, II,x;      
	unsigned bands, rows, cols;      
      
	bands = getNoOfBands_Image(imageP);      
	rows =  getNoOfRows_Image(imageP);      
	cols =  getNoOfCols_Image(imageP);      
             
	NN=mask_size;      
 	imageW = duplicate_Image(imageP);
	switch(imageP->bandP[0]->data_type){
	   case CVIP_BYTE:{
        	register byte   *bP, *bP1;      
	        int minimum[121];    
		register int smin;
		for(i=0; i < bands; i++)      
 	        {      
  	         for(j=NN/2; j < (rows-NN/2); j++,bP++)      
   	         {      						      				         
    	         bP=(byte*)getRow_Image(imageW,j,i); 

     	        for(k=NN/2; k < (cols-NN/2); k++,bP1++)
	     	 {	      
       	          x=0, smin=255; 

        	        for(JJ = -NN/2; JJ <= NN/2 ; JJ++)
         	          {	
	                     bP1=(byte*)getRow_Image(imageP,j+JJ,i);
							          
  	                     for(II=-NN/2;II<=NN/2;II++,x++)
   	                       { 
    	                        minimum[x] = *(bP1+k+II);
     	                      }
      	             }                 
			
   	               for(JJ=0;JJ<NN*NN;JJ++)
    	               {
     	              if(minimum[JJ] < smin)
      	              smin = minimum[JJ];
	      	       } 
                                 					                                       
		*(bP + k)=(byte)(smin);

		}      
     	   	 }      
		} 
	  }
	  break;     
	  case CVIP_SHORT:{  
        	register short   *bP, *bP1;      
	        int minimum[121];    
		register int smin;
		for(i=0; i < bands; i++)      
 	        {      
  	         for(j=NN/2; j < (rows-NN/2); j++,bP++)      
   	         {      						      				         
    	         bP=getRow_Image(imageW,j,i); 

     	        for(k=NN/2; k < (cols-NN/2); k++,bP1++)
	     	 {	      
       	          x=0, smin=SHRT_MAX; 

        	        for(JJ = -NN/2; JJ <= NN/2 ; JJ++)
         	          {	
	                     bP1=getRow_Image(imageP,j+JJ,i);
							          
  	                     for(II=-NN/2;II<=NN/2;II++,x++)
   	                       { 
    	                        minimum[x] = *(bP1+k+II);
     	                      }
      	             }                 
			
   	               for(JJ=0;JJ<NN*NN;JJ++)
    	               {
     	              if(minimum[JJ] < smin)
      	              smin = minimum[JJ];
	      	       } 
                                 					                                       
		*(bP + k)=(smin);

		}      
     	   	 }      
		} 
	  }
	  break;     	
	case CVIP_INTEGER:{
        	register long   *bP, *bP1;      
	        long minimum[121];    
		register long smin;
		for(i=0; i < bands; i++)      
 	        {      
  	         for(j=NN/2; j < (rows-NN/2); j++,bP++)      
   	         {      						      				         
    	         bP=getRow_Image(imageW,j,i); 

     	        for(k=NN/2; k < (cols-NN/2); k++,bP1++)
	     	 {	      
       	          x=0, smin=LONG_MAX; 

        	        for(JJ = -NN/2; JJ <= NN/2 ; JJ++)
         	          {	
	                     bP1=getRow_Image(imageP,j+JJ,i);
							          
  	                     for(II=-NN/2;II<=NN/2;II++,x++)
   	                       { 
    	                        minimum[x] = *(bP1+k+II);
     	                      }
      	             }                 
			
   	               for(JJ=0;JJ<NN*NN;JJ++)
    	               {
     	              if(minimum[JJ] < smin)
      	              smin = minimum[JJ];
	      	       } 
                                 					                                       
		*(bP + k)=(smin);

		}      
     	   	 }      
		} 
	  }
	  break;  
	case CVIP_FLOAT:{
        	register float   *bP, *bP1;      
	        float minimum[121];    
		register float smin;
		for(i=0; i < bands; i++)      
 	        {      
  	         for(j=NN/2; j < (rows-NN/2); j++,bP++)      
   	         {      						      				         
    	         bP=getRow_Image(imageW,j,i); 

     	        for(k=NN/2; k < (cols-NN/2); k++,bP1++)
	     	 {	      
       	          x=0, smin=FLT_MAX; 

        	        for(JJ = -NN/2; JJ <= NN/2 ; JJ++)
         	          {	
	                     bP1=getRow_Image(imageP,j+JJ,i);
							          
  	                     for(II=-NN/2;II<=NN/2;II++,x++)
   	                       { 
    	                        minimum[x] = *(bP1+k+II);
     	                      }
      	             }                 
			
   	               for(JJ=0;JJ<NN*NN;JJ++)
    	               {
     	              if(minimum[JJ] < smin)
      	              smin = minimum[JJ];
	      	       } 
                                 					                                       
		*(bP + k)=(smin);

		}      
     	   	 }      
		} 
	  }
	  break;    
	case CVIP_DOUBLE:{
        	register double   *bP, *bP1;      
	        double minimum[121];    
		register double smin;
		for(i=0; i < bands; i++)      
 	        {      
  	         for(j=NN/2; j < (rows-NN/2); j++,bP++)      
   	         {      						      				         
    	         bP=getRow_Image(imageW,j,i); 

     	        for(k=NN/2; k < (cols-NN/2); k++,bP1++)
	     	 {	      
       	          x=0, smin=DBL_MAX; 

        	        for(JJ = -NN/2; JJ <= NN/2 ; JJ++)
         	          {	
	                     bP1=getRow_Image(imageP,j+JJ,i);
							          
  	                     for(II=-NN/2;II<=NN/2;II++,x++)
   	                       { 
    	                        minimum[x] = *(bP1+k+II);
     	                      }
      	             }                 
			
   	               for(JJ=0;JJ<NN*NN;JJ++)
    	               {
     	              if(minimum[JJ] < smin)
      	              smin = minimum[JJ];
	      	       } 
                                 					                                       
		*(bP + k)=(smin);

		}      
     	   	 }      
		} 
	  }
	  break;     	 
     }	   	
     delete_Image(imageP);
     return imageW;
}     
  
Image * mean_setup(Image *cvipImage)  
  {  
     int mask_size;  
   
 printf(" **********  THE MEAN FILTER  **********\n");           
  
do{  
	printf("\nType in an integer value [3,5,7,9 or 11] for mask size:");  
	scanf("%d",&mask_size);  
  
if(mask_size == 3) break;  
if(mask_size == 5) break;  
if(mask_size == 7) break;  
if(mask_size == 9) break;  
if(mask_size == 11) break;  
else printf("\nInvalid Selection !!!!!  Try Again !!!!!\n");  
}while(1);  
  
return mean_filter(cvipImage,mask_size);  
}  
  
Image * mean_filter(Image *imageW, int mask_size)  
       {  
	Image *imageP;
        byte   *bP1, *bP;  
	int    i, j, k;  
	int II, JJ, NN, sum,mean[121],a,MM;  	   
	unsigned bands, rows, cols;  
	float  *fP1, *fP;
	float 	fsum,fmean[121];


	bands = getNoOfBands_Image(imageW);  
	rows =  getNoOfRows_Image(imageW);  
	cols =  getNoOfCols_Image(imageW);  
  
	NN=mask_size;  
      
      if(imageW->bandP[0]->data_type != CVIP_BYTE){
	   if(imageW->bandP[0]->data_type != CVIP_FLOAT && cast_Image(imageW,CVIP_FLOAT)){
		fprintf(stderr,"Image is cast into float \n");
	   }
	   else if(imageW->bandP[0]->data_type != CVIP_FLOAT ){
		fprintf(stderr,"cast_Image failed..\n");
		delete_Image(imageW);
		return NULL;
	   }
	   imageP = duplicate_Image(imageW);
      	   for(i=0; i < bands; i++)  
		{  
		for(j=NN/2; j < (rows-NN/2); j++,fP++)  
		 {    

                   fP=(float*)getRow_Image(imageW,j,i); 

  		   for(k=NN/2; k < (cols-NN/2); k++, fP1++)   
  	           {  		      	                      
                                MM=0,fsum=0;
                               				
                               for(JJ=-NN/2;JJ<=NN/2;JJ++)
  			         {                                  					                                                                                                                                                                                                         
                                     fP1=(float*)getRow_Image(imageP,j+JJ,i);
						               						  
                                    for(a=-NN/2;a<=NN/2;a++,MM++)
                                    { 
                                      fmean[MM]=*(fP1+k+a);
                                      }
                                   }    

                        for(II = 0; II < NN*NN; II++) 
                            {
                           fsum += fmean[II];
                             }
                        

                *(fP+k) = (fsum/(NN*NN));
       }
      }  
    }  
      }
      else{
	   imageP = duplicate_Image(imageW);
      	   for(i=0; i < bands; i++)  
		{  
		for(j=NN/2; j < (rows-NN/2); j++,bP++)  
		 {    

                   bP=(byte*)getRow_Image(imageW,j,i); 

  		   for(k=NN/2; k < (cols-NN/2); k++, bP1++)   
  	           {  		      	                      
                                MM=0,sum=0;
                               				
                               for(JJ=-NN/2;JJ<=NN/2;JJ++)
  			         {                                  					                                                                                                                                                                                                         
                                     bP1=(byte*)getRow_Image(imageP,j+JJ,i);
						               						  
                                    for(a=-NN/2;a<=NN/2;a++,MM++)
                                    { 
                                      mean[MM]=*(bP1+k+a);
                                      }
                                   }    

                        for(II = 0; II < NN*NN; II++) 
                            {
                           sum += mean[II];
                             }
                        

                *(bP+k) = (byte)(sum/(NN*NN));
       }
      }  
    }  
  }  
  delete_Image(imageP);
  return imageW;
}  

  
Image *alpha_setup(Image *cvipImage){   
   int mask_size, p;   
   printf(" ***********   THE ALFA-TRIMMED MEAN FILTER  **********\n");  
   do{   
	printf("\nType in an integer value [3,5,7,9 or 11] for mask size:");   
	scanf("%d",&mask_size);      
	if(mask_size == 3) break;   
	if(mask_size == 5) break;   
	if(mask_size == 7) break;   
	if(mask_size == 9) break;   
	if(mask_size == 11) break;   
	else printf("\nInvalid Selection !!!!!  Try Again !!!!!\n");   
    }while(1);   
   
    do{   
	printf("\nType in an integer value [0-%d] for the trim size:",
		mask_size*mask_size/2);   
	scanf("%d",&p);
	if(p >= 0 && p <= mask_size*mask_size)
	    break;
	else 
	    printf("\nInvalid Selection !!!!!  Try Again !!!!!\n");   
    }while(1);   
      
    return alpha_filter(cvipImage,mask_size,p);   
}   
   
Image* alpha_filter(Image *imageW, int mask_size, int p){
   Image *imageP;
   byte   **bP,**bP1;   
   int    no_of_bands,i, j,JJ, II,x,area;           
   int  A, AR[121], sum;     
   unsigned bands, rows, cols; 
   float  **fP,**fP1;
   float  fAR[121],fsum,fA;

   bands = getNoOfBands_Image(imageW);   
   rows =  getNoOfRows_Image(imageW);   
   cols =  getNoOfCols_Image(imageW);   
   area = mask_size * mask_size;

   if(imageW->bandP[0]->data_type != CVIP_BYTE ){
	if(imageW->bandP[0]->data_type != CVIP_FLOAT && cast_Image(imageW,CVIP_FLOAT)){
	    fprintf(stderr,"Image is cast into float \n");
	}
	else if(imageW->bandP[0]->data_type != CVIP_FLOAT ){
	    fprintf(stderr,"cast_Image failed..\n");
		 delete_Image(imageW);
	    return NULL;
	}
	imageP = duplicate_Image(imageW);
     	for(no_of_bands=0; no_of_bands < bands; no_of_bands++){   
	    fP = getData_Image(imageP,no_of_bands);
	    fP1 = getData_Image(imageW,no_of_bands);
	    for(i = mask_size/2; i < rows - mask_size/2; i++){
		for(j = mask_size/2; j < cols - mask_size/2; j++){
		     x = 0;
		     for(II = i - mask_size/2; II <= i + mask_size/2; II++)
			 for(JJ = j - mask_size/2; JJ <= j + mask_size/2;JJ++)
				fAR[x++] = fP[II][JJ];
		     for(II = 0; II < area; II++){
			 for(JJ = II; JJ < area; JJ++){
			     if(fAR[II] > fAR[JJ]){
				  fA = fAR[JJ];
				  fAR[JJ] = fAR[II];
				  fAR[II] = fA;
			     }
			 }
		     }
		     fsum = 0.0;
		     for(II = p; II < area-p; II++)
			 fsum += fAR[II];
		     fsum /= (area - 2*p);
		     fP1[i][j] = fsum;
		}
	    }
	}	 
   }
   else{
	imageP = duplicate_Image(imageW);
     	for(no_of_bands=0; no_of_bands < bands; no_of_bands++){   
	    bP = getData_Image(imageP,no_of_bands);
	    bP1 = getData_Image(imageW,no_of_bands);
	    for(i = mask_size/2; i < rows - mask_size/2; i++){
		for(j = mask_size/2; j < cols - mask_size/2; j++){
		     x = 0;
		     for(II = i - mask_size/2; II <= i + mask_size/2; II++)
			 for(JJ = j - mask_size/2; JJ <= j + mask_size/2;JJ++)
				AR[x++] = bP[II][JJ];
		     for(II = 0; II < area; II++){
			 for(JJ = II; JJ < area; JJ++){
			     if(AR[II] > AR[JJ]){
				  A = AR[JJ];
				  AR[JJ] = AR[II];
				  AR[II] = A;
			     }
			 }
		     }
		     sum = 0;
		     for(II = p; II < area-p; II++)
			 sum += AR[II];
		     sum /= (area - 2*p);
		     bP1[i][j] = sum;
		}
	    }
	}		    
   }
   delete_Image(imageP);
   return imageW;
}   
      
Image* contra_setup(Image *cvipImage) { 
   int mask_size, p; 
   printf(" ***********  THE CONTRA - HARMONIC MEAN FILTER  **********\n");    
   do{ 
	printf("\nType in an integer value [3,5,7,9 or 11] for mask size:"); 
	scanf("%d",&mask_size); 
	if(mask_size == 3) break; 
	if(mask_size == 5) break; 
	if(mask_size == 7) break; 
	if(mask_size == 9) break; 
	if(mask_size == 11) break; 
	else printf("\nInvalid Selection !!!!!  Try Again !!!!!\n"); 
    }while(1); 
 
    do{   
  	fflush(stdin);
	printf("\nType in an integer value [(-5) to (+5)] for the desired filter order:");   
	scanf("%d",&p);   
	if(abs(p) == 1) break;   
	if(abs(p) == 2) break;   
	if(abs(p) == 3) break;  	
	if(abs(p) == 4) break;   
	if(abs(p) == 5) break; 
	else printf("\nInvalid Selection !!!!!  Try Again !!!!!\n");   
    }while(1);   

    return   contra_filter(cvipImage,mask_size,p); 
} 
 
Image * contra_filter(Image *imageW, int mask_size, int p) {
   Image *imageP;
   byte   **bP,**bP1;   
   int    no_of_bands,i, j,JJ, II,x,area;           
   unsigned bands, rows, cols; 
   float  **fP,**fP1;
   float  AR[121],sum,sum1,A;

   bands = getNoOfBands_Image(imageW);   
   rows =  getNoOfRows_Image(imageW);   
   cols =  getNoOfCols_Image(imageW);   
   area = mask_size * mask_size;

   if(imageW->bandP[0]->data_type != CVIP_BYTE ){
	if(imageW->bandP[0]->data_type != CVIP_FLOAT && cast_Image(imageW,CVIP_FLOAT)){
	    fprintf(stderr,"Image is cast into float \n");
	}
	else if(imageW->bandP[0]->data_type != CVIP_FLOAT ){
	    fprintf(stderr,"cast_Image failed..\n");
		 delete_Image(imageW);
	    return NULL;
	}
	imageP = duplicate_Image(imageW);
     	for(no_of_bands=0; no_of_bands < bands; no_of_bands++){   
	    fP = getData_Image(imageP,no_of_bands);
	    fP1 = getData_Image(imageW,no_of_bands);
	    for(i = mask_size/2; i < rows - mask_size/2; i++){
		for(j = mask_size/2; j < cols - mask_size/2; j++){
		     x = 0;
		     sum = sum1 = 0.0;
		     for(II = i - mask_size/2; II <= i + mask_size/2; II++)
			 for(JJ = j - mask_size/2; JJ <= j + mask_size/2;JJ++)
				AR[x++] = fP[II][JJ];
		     for(II = 0; II < area; II++){
			 sum += pow((double)AR[II],(double)(p+1));
			 sum1 +=pow((double)AR[II],(double)p);
		     }
		     if(sum1)
		         fP1[i][j] = sum / sum1;
		     else
			 fP1[i][j] = 0.0;
		}
	    }
	}	 
   }
   else{
	imageP = duplicate_Image(imageW);
     	for(no_of_bands=0; no_of_bands < bands; no_of_bands++){   
	    bP = getData_Image(imageP,no_of_bands);
	    bP1 = getData_Image(imageW,no_of_bands);
	    for(i = mask_size/2; i < rows - mask_size/2; i++){
		for(j = mask_size/2; j < cols - mask_size/2; j++){
		     sum1=sum=0.0;
		     x = 0;
		     for(II = i - mask_size/2; II <= i + mask_size/2; II++)
			 for(JJ = j - mask_size/2; JJ <= j + mask_size/2;JJ++)
				AR[x++] = (float)(bP[II][JJ]);
		     for(II = 0; II < area; II++){
			 sum += pow((double)AR[II],(double)(p+1));
			 sum1 +=pow((double)AR[II],(double)p);
		     }
		     if(sum1)
		         bP1[i][j] = (byte) (sum / sum1);
		     else
			 bP1[i][j] = 0;
		}
	    }
	}		    
   }
   delete_Image(imageP);
   return imageW;
}               

             

Image* geometric_setup(Image *cvipImage)                   
  {                   
     int mask_size;                   
                    
 printf(" **********  THE GEOMETRIC MEAN FILTER  **********\n");                            
                   
do{                   
	printf("\nType in an integer value [3,5,7,9 or 11] for mask size:");                   
	scanf("%d",&mask_size);                   
                   
if(mask_size == 3) break;                   
if(mask_size == 5) break;                   
if(mask_size == 7) break;                   
if(mask_size == 9) break;                   
if(mask_size == 11) break;                   
else printf("\nInvalid Selection !!!!!  Try Again !!!!!\n");                   
}while(1);                   
                   
return geometric_filter(cvipImage,mask_size);                   
   }                   
                   
Image* geometric_filter(Image *imageW, int mask_size)                   
       {    
	Image *imageP;               
	byte   *bP, *bP1;                   
	int    i, j, k, JJ, II, A;                   
	int mask[121], Z, NN, index, x;                   
	float PRODUCT, TAR[121];    
	float *fP, *fP1;
	float fmask[121],fZ;                  
	unsigned bands, rows, cols;                   
     
	bands = getNoOfBands_Image(imageW);                   
	rows =  getNoOfRows_Image(imageW);                   
	cols =  getNoOfCols_Image(imageW);                   
                   
	NN=mask_size;                   
       if(imageW->bandP[0]->data_type != CVIP_BYTE){
	   if(imageW->bandP[0]->data_type != CVIP_FLOAT && cast_Image(imageW,CVIP_FLOAT)){
		fprintf(stderr,"Image is cast into float \n");
	   }
	   else if(imageW->bandP[0]->data_type != CVIP_FLOAT ){
		fprintf(stderr,"cast_Image failed..\n");
		delete_Image(imageW);
		return NULL;
	   }
	imageP = duplicate_Image(imageW);
	for(i=0; i < bands; i++)                   
        {                   
         for(j=NN/2; j < (rows-NN/2); j++,fP++)                   
	 {                   
          fP=(float*)getRow_Image(imageW,j,i); 

             for(k=NN/2; k < (cols-NN/2); k++, fP1++)       
	   {       
       
	    x= 0;
            for(JJ=-NN/2; JJ<= NN/2; JJ++) 
             { 
               fP1 = (float *) getRow_Image(imageP, JJ+j, i);         
		            
	      for(II=-NN/2; II<= NN/2; II++, x++)       
                {              
	         fmask[x] = *(fP1 + k +II);      
	         }       
	      }                           

	         for(JJ=0; JJ <= NN*NN-1; JJ++)                   
		  {                   
		    if(fmask[JJ] <= 0)                   
		      {                   
		        fmask[JJ] = 1;                   
	               }                   
		        TAR[JJ] = pow((double)fmask[JJ],  
                              (double)(1.0/(float)(NN*NN)));                 			                 				                             				 
                   }

                     PRODUCT = 1.0;                   			              
		    for(JJ=0; JJ <= NN*NN-1; JJ++)                   
		      PRODUCT *= TAR[JJ];                   
			                        
                      *(fP + k ) = PRODUCT;                   
                   
             }                   
        }                   
    }
	}
	else{
           
        imageP = duplicate_Image(imageW);          
	for(i=0; i < bands; i++)                   
        {                   
         for(j=NN/2; j < (rows-NN/2); j++,bP++)                   
	 {                   
          bP=(byte*)getRow_Image(imageW,j,i); 

             for(k=NN/2; k < (cols-NN/2); k++, bP1++)       
	   {       
       
	    x= 0;
            for(JJ=-NN/2; JJ<= NN/2; JJ++) 
             { 
               bP1 = (byte *) getRow_Image(imageP, JJ+j, i);         
		            
	      for(II=-NN/2; II<= NN/2; II++, x++)       
                {              
	         mask[x] = *(bP1 + k +II);      
	         }       
	      }                           

	         for(JJ=0; JJ <= NN*NN-1; JJ++)                   
		  {                   
		    if(mask[JJ] <= 0)                   
		      {                   
		        mask[JJ] = 1;                   
	               }                   
		        TAR[JJ] = pow((double)mask[JJ],  
                              (double)(1.0/(float)(NN*NN)));                 			                 				                             				 
                   }

                     PRODUCT = 1.0;                   			              
		    for(JJ=0; JJ <= NN*NN-1; JJ++)                   
		      PRODUCT *= TAR[JJ];                   
			                        
		      if(PRODUCT > 255)                   
		         *(bP+k) = 255;                   
		           else                   
				   
                    	    *(bP + k ) = (byte) (unsigned char)PRODUCT;                   
                   
             }                   
        }                   
    }         
    }          
    delete_Image(imageP);
    return imageW;
}                   

Image * harmonic_setup(Image *cvipImage){ 
   int mask_size; 
   printf(" ***********  THE HARMONIC MEAN FILTER  **********\n");          
   do{ 
	printf("\nType in an integer value [3,5,7,9 or 11] for mask size:"); 
	scanf("%d",&mask_size);  
	if(mask_size == 3) break; 
	if(mask_size == 5) break; 
	if(mask_size == 7) break; 
	if(mask_size == 9) break; 
	if(mask_size == 11) break; 
	else printf("\nInvalid Selection !!!!!  Try Again !!!!!\n"); 
   }while(1);  
   return harmonic_filter(cvipImage,mask_size); 
} 
 
Image * harmonic_filter(Image *imageW, int mask_size){
   Image *imageP;
   byte   **bP,**bP1;   
   int    no_of_bands,i, j,JJ, II,x,area,count;           
   unsigned bands, rows, cols; 
   float  **fP,**fP1;
   float  AR[121],sum,A;

   bands = getNoOfBands_Image(imageW);   
   rows =  getNoOfRows_Image(imageW);   
   cols =  getNoOfCols_Image(imageW);   
   area = mask_size * mask_size;

   if(imageW->bandP[0]->data_type != CVIP_BYTE ){
	if(imageW->bandP[0]->data_type != CVIP_FLOAT && cast_Image(imageW,CVIP_FLOAT)){
	    fprintf(stderr,"Image is cast into float \n");
	}
	else if(imageW->bandP[0]->data_type != CVIP_FLOAT ){
	    fprintf(stderr,"cast_Image failed..\n");
		 delete_Image(imageW);
	    return NULL;
	}
	imageP = duplicate_Image(imageW);
     	for(no_of_bands=0; no_of_bands < bands; no_of_bands++){   
	    fP = getData_Image(imageP,no_of_bands);
	    fP1 = getData_Image(imageW,no_of_bands);
	    for(i = mask_size/2; i < rows - mask_size/2; i++){
		for(j = mask_size/2; j < cols - mask_size/2; j++){
		     x = 0;
		     sum = 0.0;
	 	     count = area;
		     for(II = i - mask_size/2; II <= i + mask_size/2; II++){
			 for(JJ = j - mask_size/2; JJ <= j + mask_size/2;JJ++){
				if(fP[II][JJ])
				    sum += 1.0 / fP[II][JJ];
				else
				    count--;
			 }
		     }
		     if(sum)
		         fP1[i][j] = (float) count / sum;
		     else
			 fP1[i][j] = 0.0;
		}
	    }
	}	 
   }
   else{
	imageP = duplicate_Image(imageW);
     	for(no_of_bands=0; no_of_bands < bands; no_of_bands++){   
	    bP = getData_Image(imageP,no_of_bands);
	    bP1 = getData_Image(imageW,no_of_bands);
	    for(i = mask_size/2; i < rows - mask_size/2; i++){
		for(j = mask_size/2; j < cols - mask_size/2; j++){
		     x = 0;
		     sum = 0.0;
	 	     count = area;
		     for(II = i - mask_size/2; II <= i + mask_size/2; II++){
			 for(JJ = j - mask_size/2; JJ <= j + mask_size/2;JJ++){
				if(bP[II][JJ])
				    sum += 1.0 / (float)(bP[II][JJ]);
				else
				    count--;
			 }
		     }
		     if(sum)
		         bP1[i][j] = (byte) (count / sum);
		     else
			 bP1[i][j] = 0;
		}
	    }
	}		    
   }
   delete_Image(imageP);
   return imageW;
}                              

Image* Ypmean_setup(Image *cvipImage){ 
   int mask_size, p; 
   printf(" **********  THE Yp MEAN FILTER  **********\n");          
   do{ 
	printf("\nType in an integer value [3,5,7,9 or 11] for mask size:"); 
	scanf("%d",&mask_size);  
	if(mask_size == 3) break;  
	if(mask_size == 5) break; 
	if(mask_size == 7) break; 
	if(mask_size == 9) break; 
	if(mask_size == 11) break; 
	else printf("\nInvalid Selection !!!!!  Try Again !!!!!\n");  
   }while(1); 
 
   do{ 
	printf("\nType in an integer value from [-5 0) to (0 5] for the desired filter order:"); 
	scanf("%d",&p); 
	if(p >= -5 && p <= 5 && p != 0) break; 
	else printf("\nInvalid Selection !!!!!  Try Again !!!!!\n"); 
   }while(1); 
    
   return Ypmean_filter(cvipImage,mask_size,p); 
} 
 
Image * Ypmean_filter(Image *imageW, int mask_size, int p){ 
   Image *imageP;
   byte   **bP,**bP1;   
   int    no_of_bands,i, j,JJ, II,x,area;           
   unsigned bands, rows, cols; 
   float  **fP,**fP1;
   float  AR[121],sum,A;

   bands = getNoOfBands_Image(imageW);   
   rows =  getNoOfRows_Image(imageW);   
   cols =  getNoOfCols_Image(imageW);   
   area = mask_size * mask_size;

   if(imageW->bandP[0]->data_type != CVIP_BYTE ){
	if(imageW->bandP[0]->data_type != CVIP_FLOAT && cast_Image(imageW,CVIP_FLOAT)){
	    fprintf(stderr,"Image is cast into float \n");
	}
	else if(imageW->bandP[0]->data_type != CVIP_FLOAT ){
	    fprintf(stderr,"cast_Image failed..\n");
		 delete_Image(imageW);
	    return NULL;
	}
	imageP = duplicate_Image(imageW);
     	for(no_of_bands=0; no_of_bands < bands; no_of_bands++){   
	    fP = getData_Image(imageP,no_of_bands);
	    fP1 = getData_Image(imageW,no_of_bands);
	    for(i = mask_size/2; i < rows - mask_size/2; i++){
		for(j = mask_size/2; j < cols - mask_size/2; j++){
		     x = 0;
		     sum = 0.0;
		     for(II = i - mask_size/2; II <= i + mask_size/2; II++){
			 for(JJ = j - mask_size/2; JJ <= j + mask_size/2;JJ++){
				sum +=  pow((double)fP[II][JJ],(double)p);
			 }
		     }
		     sum /= area;
		     sum = fabs(sum);
		     fP1[i][j] = pow((double)sum,(double)1/p);
		}
	    }
	}	 
   }
   else{
	imageP = duplicate_Image(imageW);
     	for(no_of_bands=0; no_of_bands < bands; no_of_bands++){   
	    bP = getData_Image(imageP,no_of_bands);
	    bP1 = getData_Image(imageW,no_of_bands);
	    for(i = mask_size/2; i < rows - mask_size/2; i++){
		for(j = mask_size/2; j < cols - mask_size/2; j++){
		     x = 0;
		     sum = 0.0;
		     for(II = i - mask_size/2; II <= i + mask_size/2; II++){
			 for(JJ = j - mask_size/2; JJ <= j + mask_size/2;JJ++){
				sum +=  pow((double)bP[II][JJ],(double)p);
			 }
		     }
		     sum /= area;
		     sum = (sum < 0)? -sum : sum;
		     bP1[i][j] = pow((double)sum,(double)1/p);
		}
	    }
	}		    
   }
   delete_Image(imageP);
   return imageW;
}  


Image* midpoint_setup(Image *cvipImage)       
  {       
     int mask_size;       
       
printf(" ************  THE MIDPOINT FILTER  **********\n");              
       
do{       
	printf("\nType in an integer value [3,5,7,9 or 11] for mask size:");       
	scanf("%d",&mask_size);       
       
if(mask_size == 3) break;       
if(mask_size == 5) break;       
if(mask_size == 7) break;       
if(mask_size == 9) break;       
if(mask_size == 11) break;       
else printf("\nInvalid Selection !!!!!  Try Again !!!!!\n");       
}while(1);       
       
return midpoint_filter(cvipImage,mask_size);       
   }       
       
Image *midpoint_filter(Image *imageW, int mask_size)       
       {       
	Image  *imageP;
        byte   *bP1, *bP2;       
	int    i, j, k, JJ, II, x, smin, smax, NN;       
	unsigned bands, rows, cols;       
        int Pixel[121];
	float *fP1, *fP2;
	float fPixel[121];
	float fsmin, fsmax;

	bands = getNoOfBands_Image(imageW);       
	rows =  getNoOfRows_Image(imageW);       
	cols =  getNoOfCols_Image(imageW);       

  	NN=mask_size;       
       if(imageW->bandP[0]->data_type != CVIP_BYTE ){
	   if(imageW->bandP[0]->data_type != CVIP_FLOAT && cast_Image(imageW,CVIP_FLOAT)){
		fprintf(stderr,"Image is cast into float \n");
	   }
	   else if(imageW->bandP[0]->data_type != CVIP_FLOAT ){
		fprintf(stderr,"cast_Image failed..\n");
		delete_Image(imageW);
		return NULL;
	   }
	imageP = duplicate_Image(imageW);
	for(i=0; i < bands; i++)       
	  {       
		for(j=NN/2; j < (rows-NN/2); j++)       
	          {        		  
                     fP1 = (float *) getRow_Image(imageW, j, i);
                        for(k=NN/2; k < (cols-NN/2); k++)       
			{       
       
			 fsmin=FLT_MAX; fsmax=FLT_MIN; x= 0;
                          for(JJ=-NN/2; JJ<= NN/2; JJ++) 
                           {
                            fP2 = (float *) getRow_Image(imageP, JJ+j, i);         		            
			 for(II=-NN/2; II<= NN/2;II++, x++)       
			  {              
			    fPixel[x] = *(fP2 + k +II);      
			   }       
                         }


			 for(JJ=0; JJ < NN*NN; JJ++)       
			    {       
			     if(fPixel[JJ] < fsmin)       
				 fsmin = fPixel[JJ];       
				       
			     }       
			  for(II=0; II < NN*NN; II++)       
			   {       
		            if(fPixel[II] > fsmax)       
				 fsmax = fPixel[II];       
				       
			     }       
       
			 *(fP1 + k) =((fsmin+fsmax)/2+0.5);       
                 }
       }       
      }
	}
	/*cast_Image(imageW,CVIP_BYTE);*/
	else{
	imageP = duplicate_Image(imageW);
	for(i=0; i < bands; i++)       
	  {       
		for(j=NN/2; j < (rows-NN/2); j++,bP1++)       
	          {        		  
                     bP1 = (byte *) getRow_Image(imageW, j, i);
                        for(k=NN/2; k < (cols-NN/2); k++,bP2++)       
			{       
       
			 smin=255, smax=0, x= 0;
                          for(JJ=-NN/2; JJ<= NN/2; JJ++) 
                           {
                            bP2 = (byte *) getRow_Image(imageP, JJ+j, i);         		            
			 for(II=-NN/2; II<= NN/2;II++, x++)       
			  {              
			    Pixel[x] = *(bP2 + k +II);      
			   }       
                         }


			 for(JJ=0; JJ < NN*NN; JJ++)       
			    {       
			     if(Pixel[JJ] < smin)       
				 smin = Pixel[JJ];       
				       
			     }       
			  for(II=0; II < NN*NN; II++)       
			   {       
		            if(Pixel[II] > smax)       
				 smax = Pixel[II];       
				       
			     }       
       
			 *(bP1 + k) = (byte) ((smin+smax)/2+0.5);       
                 }
       }       
      } 
   }    
   delete_Image(imageP);
   return imageW;
}                                

Image* maximum_setup(Image *cvipImage)   
  {   
     int mask_size;   
   
printf("   ************  THE MAXIMUM FILTER  **********\n");          
   
do{   
	printf("\nType in an integer value [3,5,7,9 or 11] for mask size:");   
	scanf("%d",&mask_size);   
   
if(mask_size == 3) break;   
if(mask_size == 5) break;   
if(mask_size == 7) break;   
if(mask_size == 9) break;   
if(mask_size == 11) break;   
else printf("\nInvalid Selection !!!!!  Try Again !!!!!\n");   
}while(1);   
   
   return maximum_filter(cvipImage,mask_size);   
   }   
   
Image *maximum_filter(Image *imageW, int mask_size)   
       {   
	Image *imageP;
        byte   *bP1, *bP;   
	int    i, j, k;   
        int JJ, II, smax, max[121],MM,a,NN;   
	float  *fP1, *fP;
	float fsmax,fmax[121];   
	unsigned bands, rows, cols;   
   
	bands = getNoOfBands_Image(imageW);   
	rows =  getNoOfRows_Image(imageW);   
	cols =  getNoOfCols_Image(imageW);    
	NN = mask_size;
       if(imageW->bandP[0]->data_type != CVIP_BYTE ){
	   if(imageW->bandP[0]->data_type != CVIP_FLOAT && cast_Image(imageW,CVIP_FLOAT)){
		fprintf(stderr,"Image is cast into float \n");
	   }
	   else if(imageW->bandP[0]->data_type != CVIP_FLOAT ){
		fprintf(stderr,"cast_Image failed..\n");
		delete_Image(imageW);
		return NULL;
	   }
	   imageP = duplicate_Image(imageW);
            for(i=0; i < bands; i++)   
		{   
		for(j=NN/2; j < (rows-NN/2); j++)   
			{   
		     
                         fP=(float*)getRow_Image(imageW,j,i); 

                        for(k=NN/2; k < cols-NN/2; k++)
				{
			        MM=0;
                                fsmax=FLT_MIN;
				for(JJ=-NN/2;JJ<=NN/2;JJ++)
  			         {
                                   					                                                                                                                                                                                                         
                                     fP1=(float*)getRow_Image(imageP,j+JJ,i);
						               						  
                                    for(a=-NN/2;a<=NN/2;a++,MM++)
                                    { fmax[MM]=*(fP1+k+a);}
                                        
                                 }    

				for(JJ=0;JJ<NN*NN;JJ++)
                                  {
                                   if(fmax[JJ] > fsmax)
                                    fsmax = fmax[JJ];
	                           }                                  					                                                                                        				                 
                           *(fP+k) = fsmax;

}
}
}

	}
	else{
	   imageP = duplicate_Image(imageW);
            for(i=0; i < bands; i++)   
		{   
		for(j=NN/2; j < (rows-NN/2); j++,bP++)   
			{   
		     
                         bP=(byte*)getRow_Image(imageW,j,i); 

                        for(k=NN/2; k < cols-NN/2; k++,bP1++)
				{
			        MM=0;
                                smax=0;
				for(JJ=-NN/2;JJ<=NN/2;JJ++)
  			         {
                                   					                                                                                                                                                                                                         
                                     bP1=(byte*)getRow_Image(imageP,j+JJ,i);
						               						  
                                    for(a=-NN/2;a<=NN/2;a++,MM++)
                                    { max[MM]=*(bP1+k+a);}
                                        
                                 }    

				for(JJ=0;JJ<NN*NN;JJ++)
                                  {
                                   if(max[JJ] > smax)
                                    smax = max[JJ];
	                           }                                  					                                                                                        				                 
                           *(bP+k) = (byte)smax;

}
}
}
}
delete_Image(imageP);
return imageW;
}

Image* ad_setup(Image *cvipImage){ 
   int iteration_num, speed, edge_height; 
   printf(" **********  THE ANISOTROPIC DIFFUSION FILTER  **********\n");          
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
    
   return ad_filter(cvipImage, iteration_num, speed, edge_height); 
}

Image* ad_filter(Image *inputImage, int iteration_num, int speed, int edge_height)
{
	//input parameters
	int nb_iter       =	iteration_num;	//20;    // Number of iterations
	int nb_smoothings =	speed;			//1;     // Number of smoothings per iteration
	double dt         = 20.0;  // Adapting time step
	float a1          = 0.5f;  // Diffusion limiter along minimal variations
	float a2          = 0.9f;  // Diffusion limiter along maximal variations
	int save          = 20;    // Iteration saving step
	float edgeheight  =	edge_height;	//5;     // edge threshold

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

	float 		**imagef; 	/* 2-d matrix data pointer */
	byte 		**imageb; 	/* 2-d matrix data pointer */

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

		//gets initial stats for later normalizing
		average = 0;
		pix_max = pix_min = ipf[0][0][0];
		for(bands=0; bands < no_of_bands; bands++) 
		{
			for(r = 0; r < no_of_rows; r++) 
			{
				for(col = 0; col < no_of_cols; col++) 
				{
					cur_pix = ipf[r][col][bands];
					if (cur_pix > pix_max) 
						pix_max = cur_pix;
					if (cur_pix < pix_min) 
						pix_min = cur_pix;
					average += cur_pix;
				}
			}
		}
		average /= (no_of_cols * no_of_rows*bands);

		//standard deviation
		stddev = 0;
		for(bands = 0; bands < no_of_bands; bands++) 
		{
			for(r = 0; r < no_of_rows; r++) 
			{
				for(col = 0; col < no_of_cols; col++) 
				{
					cur_pix = ipf[r][col][bands];
					stddev += (cur_pix - average)*(cur_pix - average);
				}
			}
		}
		stddev = sqrt(stddev / (no_of_cols * no_of_rows*bands));

		//normalization
		drange = (edgeheight * stddev) / 256.0;
		drange0 = (6*stddev) / 256.0;
		drange2 = drange * drange;

		//iteration loop
		for(iteration = 0; iteration < nb_iter; iteration ++)
		{
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

		//gets initial stats for later normalizing
		average = 0;
		pix_max = pix_min = ipf[0][0][0];
		for(bands=0; bands < no_of_bands; bands++) 
		{
			for(r = 0; r < no_of_rows; r++) 
			{
				for(col = 0; col < no_of_cols; col++) 
				{
					cur_pix = ipf[r][col][bands];
					if (cur_pix > pix_max) 
						pix_max = cur_pix;
					if (cur_pix < pix_min) 
						pix_min = cur_pix;
					average += cur_pix;
				}
			}
		}
		average /= (no_of_cols * no_of_rows*bands);

		//standard deviation
		stddev = 0;
		for(bands = 0; bands < no_of_bands; bands++) 
		{
			for(r = 0; r < no_of_rows; r++) 
			{
				for(col = 0; col < no_of_cols; col++) 
				{
					cur_pix = ipf[r][col][bands];
					stddev += (cur_pix - average)*(cur_pix - average);
				}
			}
		}
		stddev = sqrt(stddev / (no_of_cols * no_of_rows*bands));

		//normalization
		drange = (edgeheight * stddev) / 256.0;
		drange0 = (6*stddev) / 256.0;
		drange2 = drange * drange;

		//iteration loop
		for(iteration = 0; iteration < nb_iter; iteration ++)
		{
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

	return inputImage;
}
	
