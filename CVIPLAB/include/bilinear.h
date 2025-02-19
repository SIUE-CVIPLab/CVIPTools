/*
*	Bilinear.h - header file for bilinear interpolation
*
*	Arve Kjoelen - Mon Oct 23 11:06:48 CDT 1995
*
*/
#if !defined ( CVIP_BILINEAR_DEFINED )
   #define CVIP_BILINEAR_DEFINED
#ifdef __cplusplus
extern "C"{
#endif 


   extern Image *bilinear_setup(Image *);
   extern Image *bilinear_interp(Image *, float);
   extern Image *bilinear_interp1(Image *, float, float);

   #define BILINEAR(dx,dy,f00,f01,f10,f11,type) ( \
        (type)((float)(type)f00 + \
        (float)((float)dx*((float)(type)f10-(float)(type)f00)) + \
        (float)((float)dy*((float)(type)f01-(float)(type)f00)) + \
        (float)((float)dx*(float)dy*((float)(type)f11+(float)(type)f00-(float)(type)f01-(float)(type)f10))))

   #define LOOP_BILINEAR(type,row,Mcol,int_map,delta_map,_Dptr, _Nptr) { \
	type **_Rowp=(type **)(_Dptr); \
	type *NEWP=(type *)(_Nptr); \
	int rI; \
	for(rI=0; rI < (int)Mcol ; rI++) { \
		*NEWP++=BILINEAR((float)delta_map[row],(float)delta_map[rI], \
			_Rowp[(int)int_map[row]][(int)int_map[rI]], \
			_Rowp[(int)int_map[row]][(int)int_map[rI+1]], \
			_Rowp[(int)int_map[row+1]][(int)int_map[rI]], \
			_Rowp[(int)int_map[row+1]][(int)int_map[rI+1]], type); \
	} \
   }
#ifdef __cplusplus
}
#endif 

#endif
