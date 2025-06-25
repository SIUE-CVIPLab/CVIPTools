

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Mon Jan 18 21:14:07 2038
 */
/* Compiler settings for CVIPCOM.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0628 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __CVIPCOM_i_h__
#define __CVIPCOM_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifndef __ICVIPTools_FWD_DEFINED__
#define __ICVIPTools_FWD_DEFINED__
typedef interface ICVIPTools ICVIPTools;

#endif 	/* __ICVIPTools_FWD_DEFINED__ */


#ifndef __CVIPTools_FWD_DEFINED__
#define __CVIPTools_FWD_DEFINED__

#ifdef __cplusplus
typedef class CVIPTools CVIPTools;
#else
typedef struct CVIPTools CVIPTools;
#endif /* __cplusplus */

#endif 	/* __CVIPTools_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ICVIPTools_INTERFACE_DEFINED__
#define __ICVIPTools_INTERFACE_DEFINED__

/* interface ICVIPTools */
/* [unique][nonextensible][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICVIPTools;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CFD37216-45A1-47C1-8E50-B9DF3B16FA42")
    ICVIPTools : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Ace2_Filter( 
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [in] */ double local_mean,
            /* [in] */ double local_gain,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Acuity_Nightvision_Filter( 
            /* [in] */ long *image,
            /* [in] */ long reason,
            /* [in] */ long threshold,
            /* [in] */ long acuity,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AD_Filter( 
            /* [in] */ long *image,
            /* [in] */ long iterations,
            /* [in] */ long speed,
            /* [in] */ long edge_height,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Adapt_Median_Filter( 
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Adaptive_Contrast_Filter( 
            /* [in] */ long *image,
            /* [in] */ double k1,
            /* [in] */ double k2,
            /* [in] */ long kernel_size,
            /* [in] */ double min_gain,
            /* [in] */ double max_gain,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add_Image( 
            /* [in] */ long *image1,
            /* [in] */ long *image2,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Alpha_Filter( 
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [in] */ long p,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE And_Image( 
            /* [in] */ long *image1,
            /* [in] */ long *image2,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Area( 
            /* [in] */ long *labeled_image,
            /* [in] */ int row,
            /* [in] */ int col,
            /* [retval][out] */ long *area) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Aspect( 
            /* [in] */ long *labeled_image,
            /* [in] */ int row,
            /* [in] */ int col,
            /* [retval][out] */ double *aspect) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Assemble_Bands( 
            /* [in] */ long bands[ 3 ],
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Auto_Threshold_Segment( 
            /* [in] */ long *image,
            /* [in] */ float limit,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Bilinear_Interp( 
            /* [in] */ long *image,
            /* [in] */ float factor,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Bilinear_Interp1( 
            /* [in] */ long *image,
            /* [in] */ float xfactor,
            /* [in] */ float yfactor,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Bintocvip( 
            /* [in] */ BSTR *filename,
            /* [in] */ long bands,
            /* [in] */ long color_order,
            /* [in] */ long interleaved,
            /* [in] */ int height,
            /* [in] */ int width,
            /* [in] */ long verbose,
            /* [retval][out] */ long *cvip_image) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Bit_Compress( 
            /* [in] */ BSTR *filename,
            /* [in] */ long *image,
            /* [in] */ long bitmask) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Bit_Decompress( 
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Boiecox_Filter( 
            /* [in] */ long *image,
            /* [in] */ double variance,
            /* [in] */ long do_threshold,
            /* [in] */ long do_hyst,
            /* [in] */ long do_thin,
            /* [in] */ double high_threshold,
            /* [in] */ double low_threshold,
            /* [in] */ long *threshhold_image,
            /* [in] */ long *hyst_image,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Btc_Compress( 
            /* [in] */ BSTR *filename,
            /* [in] */ long *image,
            /* [in] */ long blocksize) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Btc_Decompression( 
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Btc2_Compress( 
            /* [in] */ BSTR *filename,
            /* [in] */ long *image,
            /* [in] */ long blocksize) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Btc2_Decompress( 
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Btc3_Compress( 
            /* [in] */ BSTR *filename,
            /* [in] */ long *image,
            /* [in] */ long blocksize) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Btc3_Decompress( 
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Butterworth_Band_Pass( 
            /* [in] */ long *image,
            /* [in] */ long blocksize,
            /* [in] */ long keepdc,
            /* [in] */ long inner_cutoff,
            /* [in] */ long outer_cutoff,
            /* [in] */ long filter_order,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Butterworth_Band_Reject( 
            /* [in] */ long *image,
            /* [in] */ long blocksize,
            /* [in] */ long keepdc,
            /* [in] */ long inner_cutoff,
            /* [in] */ long outer_cutoff,
            /* [in] */ long filter_order,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Butterworth_High( 
            /* [in] */ long *image,
            /* [in] */ long blocksize,
            /* [in] */ long keepdc,
            /* [in] */ long cutoff,
            /* [in] */ long filter_order,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Butterworth_Low( 
            /* [in] */ long *image,
            /* [in] */ long blocksize,
            /* [in] */ long keepdc,
            /* [in] */ long cutoff,
            /* [in] */ long filter_order,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Canny_Filter( 
            /* [in] */ long *image,
            /* [in] */ double low_threshold,
            /* [in] */ double high_threshold,
            /* [in] */ double variance,
            /* [in] */ long *mag_image,
            /* [in] */ long *dir_image,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Cast_Image( 
            /* [in] */ long *image,
            /* [in] */ long datatype) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CentroID( 
            /* [in] */ long *labeled_image,
            /* [in] */ long row,
            /* [in] */ long col,
            /* [retval][out] */ VARIANT *centroid) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Cerchar_Filter( 
            /* [in] */ long *image,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Check_Bin( 
            /* [in] */ long *image,
            /* [retval][out] */ long *is_binary) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Check_xform_history( 
            /* [in] */ long *image,
            /* [in] */ int filter_type,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close_Consol( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close_Console( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Color_Contrast_Enhance( 
            /* [in] */ long *image,
            /* [in] */ long low_limit,
            /* [in] */ long high_limit,
            /* [in] */ float low_clip,
            /* [in] */ float high_clip,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ColorXform( 
            /* [in] */ long *image,
            /* [in] */ long color_space,
            /* [in] */ double *norm_vector,
            /* [in] */ double *white_reference,
            /* [in] */ long direction,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CondRemap_Image( 
            /* [in] */ long *image,
            /* [in] */ long datatype,
            /* [in] */ int min,
            /* [in] */ int max,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Contra_Filter( 
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [in] */ long p,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Copy_Paste( 
            /* [in] */ long *src_image,
            /* [in] */ long *dest_image,
            /* [in] */ int src_row,
            /* [in] */ int src_col,
            /* [in] */ int height,
            /* [in] */ int width,
            /* [in] */ int dest_row,
            /* [in] */ int dest_col,
            /* [in] */ long transparent,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Create_Black( 
            /* [in] */ int width,
            /* [in] */ int height,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Create_Checkboard( 
            /* [in] */ int width,
            /* [in] */ int height,
            /* [in] */ int start_col,
            /* [in] */ int start_row,
            /* [in] */ int blockx,
            /* [in] */ int blocky,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Create_Circle( 
            /* [in] */ int width,
            /* [in] */ int height,
            /* [in] */ int centerx,
            /* [in] */ int centery,
            /* [in] */ int radius,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Create_Cosine( 
            /* [in] */ int img_size,
            /* [in] */ int frequency,
            /* [in] */ int direction,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Create_Degenerate_Circle( 
            /* [in] */ int width,
            /* [in] */ int height,
            /* [in] */ int centerx,
            /* [in] */ int centery,
            /* [in] */ int radius,
            /* [in] */ int blur,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Create_Ellipse( 
            /* [in] */ int width,
            /* [in] */ int height,
            /* [in] */ int centerx,
            /* [in] */ int centery,
            /* [in] */ int shape_width,
            /* [in] */ int shape_height,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Create_Line( 
            /* [in] */ int width,
            /* [in] */ int height,
            /* [in] */ int tlx,
            /* [in] */ int tly,
            /* [in] */ int brx,
            /* [in] */ int bry,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Create_Mask( 
            /* [in] */ long width,
            /* [in] */ long height,
            /* [in] */ double *values,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Create_Mesh_Sine( 
            /* [in] */ int rows,
            /* [in] */ int cols,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Create_Rectangle( 
            /* [in] */ int width,
            /* [in] */ int height,
            /* [in] */ int tlx,
            /* [in] */ int tly,
            /* [in] */ int shape_width,
            /* [in] */ int shape_height,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Create_Sine( 
            /* [in] */ int img_size,
            /* [in] */ int frequency,
            /* [in] */ int direction,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Create_Squarewave( 
            /* [in] */ int img_size,
            /* [in] */ int frequency,
            /* [in] */ int direction,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Crop( 
            /* [in] */ long *image,
            /* [in] */ int start_row,
            /* [in] */ int start_col,
            /* [in] */ int rows,
            /* [in] */ int cols,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CVIP_OUTPUT( 
            /* [retval][out] */ BSTR *message) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CVIPhalftone( 
            /* [in] */ long *image,
            /* [in] */ int halftone_method,
            /* [in] */ int maxval,
            /* [in] */ float threshold,
            /* [in] */ long retain_image,
            /* [in] */ long verbose,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Cviptoccc( 
            /* [in] */ BSTR *filename,
            /* [in] */ long maxcolor,
            /* [in] */ long verbose,
            /* [in] */ long dermvis,
            /* [in] */ long *cvip_image) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Cviptoeps( 
            /* [in] */ BSTR *filename,
            /* [in] */ long *cvip_image,
            /* [in] */ double scale_x,
            /* [in] */ double scale_y,
            /* [in] */ long band,
            /* [in] */ long verbose) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Cviptogif( 
            /* [in] */ BSTR *filename,
            /* [in] */ long *cvip_image,
            /* [in] */ long interlace,
            /* [in] */ long verbose) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Cviptoiris( 
            /* [in] */ BSTR *filename,
            /* [in] */ long *cvip_image,
            /* [in] */ long verbose,
            /* [in] */ long prt_type) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Cviptoitex( 
            /* [in] */ BSTR *filename,
            /* [in] */ long *cvip_image,
            /* [in] */ BSTR *comment,
            /* [in] */ long verbose) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Cviptojpg( 
            /* [in] */ BSTR *filename,
            /* [in] */ long *cvip_image,
            /* [in] */ int quality,
            /* [in] */ long grayscale,
            /* [in] */ long optimize,
            /* [in] */ int smooth,
            /* [in] */ long verbose,
            /* [in] */ BSTR *qtablesFile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Cviptopnm( 
            /* [in] */ BSTR *filename,
            /* [in] */ long *cvip_image,
            /* [in] */ long verbose) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Cviptoras( 
            /* [in] */ BSTR *filename,
            /* [in] */ long *cvip_image,
            /* [in] */ long pr_type,
            /* [in] */ long verbose) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Cviptotiff( 
            /* [in] */ BSTR *filename,
            /* [in] */ long *cvip_image,
            /* [in] */ long compression,
            /* [in] */ long fillorder,
            /* [in] */ long g3options,
            /* [in] */ long predictor,
            /* [in] */ long rowsperstrip,
            /* [in] */ long verbose) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Cviptovip( 
            /* [in] */ BSTR *filename,
            /* [in] */ long *cvip_image,
            /* [in] */ long verbose,
            /* [in] */ long save_history,
            /* [in] */ long is_compressed) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Date_Range( 
            /* [in] */ long *image,
            /* [retval][out] */ VARIANT *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Dct_Transform( 
            /* [in] */ long *image,
            /* [in] */ long blocksize,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Delete_DisplayImage( 
            /* [in] */ long memory_dc) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Delete_Image( 
            /* [in] */ long *image) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Divide_Image( 
            /* [in] */ long *image1,
            /* [in] */ long *image2,
            /* [in] */ long zero2num,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Dpc_Compress( 
            /* [in] */ BSTR *filename,
            /* [in] */ long *image,
            /* [in] */ float ratio,
            /* [in] */ int bit_length,
            /* [in] */ int clipping,
            /* [in] */ int direction,
            /* [in] */ int origin,
            /* [in] */ float deviation) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Dpc_Decompress( 
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Draw_mesh( 
            /* [in] */ long *image,
            /* [in] */ long *mesh) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Duplicate_Image( 
            /* [in] */ long *image,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DynRLC_Compression( 
            /* [in] */ BSTR *filename,
            /* [in] */ long *image,
            /* [in] */ long window_size,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DynRLC_deCompression( 
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Edge_Detect_Filter( 
            /* [in] */ long *image,
            /* [in] */ long edge_detector,
            /* [in] */ long mask_type,
            /* [in] */ long masksize,
            /* [in] */ long keepdc,
            /* [in] */ long threshold,
            /* [in] */ long frei_projection,
            /* [in] */ long frei_threshold,
            /* [in] */ long frei_angle,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Edge_Link_Filter( 
            /* [in] */ long *binary_image,
            /* [in] */ long connection_distance,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Enlarge( 
            /* [in] */ long *image,
            /* [in] */ int rows,
            /* [in] */ int cols,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Epstocvip( 
            /* [in] */ BSTR *filename,
            /* [in] */ long verbose) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Euler( 
            /* [in] */ long *labeled_image,
            /* [in] */ long row,
            /* [in] */ long col,
            /* [retval][out] */ long *euler) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Exp_Ace_Filter( 
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [in] */ double local_mean,
            /* [in] */ double local_gain,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Extract_Band( 
            /* [in] */ long *image,
            /* [in] */ int band,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Fft_Mag( 
            /* [in] */ long *image,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Fft_Phase( 
            /* [in] */ long *image,
            /* [in] */ long remap_norm,
            /* [in] */ double k,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Fft_Transform( 
            /* [in] */ long *image,
            /* [in] */ long blocksize,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE File_To_Mesh( 
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Fractal_Compression( 
            /* [in] */ long *image,
            /* [in] */ BSTR *filename,
            /* [in] */ double tolerance,
            /* [in] */ long min_part,
            /* [in] */ long max_part,
            /* [in] */ long dom_type,
            /* [in] */ long dom_step,
            /* [in] */ long c1,
            /* [in] */ long c2,
            /* [in] */ long scalebits,
            /* [in] */ long offsetbits,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Fractal_deCompression( 
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Fuzzyc_Segment( 
            /* [in] */ long *image,
            /* [in] */ double variance,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Gamma_Noise( 
            /* [in] */ long *image,
            /* [in] */ double variance,
            /* [in] */ int alpha,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Gaussian_Blur_Filter( 
            /* [in] */ long *image,
            /* [in] */ long kernel_size,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Gaussian_Noise( 
            /* [in] */ long *image,
            /* [in] */ double variance,
            /* [in] */ double mean,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Geometric_Filter( 
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Geometric_Mean( 
            /* [in] */ long *degr_image,
            /* [in] */ long *degr_fn,
            /* [in] */ long *psd_noise,
            /* [in] */ long *psd_orig,
            /* [in] */ double gamma,
            /* [in] */ double alpha,
            /* [in] */ long max_gain,
            /* [in] */ long cutoff,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE get_hist_real( 
            /* [in] */ long *image,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Get_Histogram_Image( 
            /* [in] */ long *image,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Get_max_min_value( 
            /* [in] */ long *image,
            /* [in] */ double *min_max) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Get_Mesh_Points( 
            /* [in] */ long *mesh,
            /* [retval][out] */ VARIANT *points) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDataFormat_Image( 
            /* [in] */ long *image,
            /* [retval][out] */ long *format) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDataType_Image( 
            /* [in] */ long *image,
            /* [retval][out] */ long *datatype) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetImageInfo( 
            /* [in] */ long *image,
            /* [retval][out] */ VARIANT *info) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Getlast_Hist( 
            /* [in] */ long *image,
            /* [in] */ long *programs,
            /* [in] */ int num_programs,
            /* [retval][out] */ long *hist) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetNoOfBands_Image( 
            /* [in] */ long *image,
            /* [retval][out] */ long *bands) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetNoOfCols_Image( 
            /* [in] */ long *image,
            /* [retval][out] */ long *cols) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetNoOfRows_Image( 
            /* [in] */ long *image,
            /* [retval][out] */ long *rows) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPixel_Image( 
            /* [in] */ long *image,
            /* [in] */ long row,
            /* [in] */ long col,
            /* [retval][out] */ VARIANT *pixel) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE giftocvip( 
            /* [in] */ BSTR *filename,
            /* [in] */ long *unused,
            /* [in] */ long image_number,
            /* [in] */ long verbose) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Glr_Compress( 
            /* [in] */ BSTR *filename,
            /* [in] */ long *image,
            /* [in] */ long window_size) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Glr_Decompress( 
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Gray_Binary( 
            /* [in] */ long *image,
            /* [in] */ int direction,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Gray_Linear( 
            /* [in] */ long *image,
            /* [in] */ double start,
            /* [in] */ double end,
            /* [in] */ double new_start,
            /* [in] */ double slope,
            /* [in] */ int oor_handling,
            /* [in] */ int band,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Gray_Multiplication( 
            /* [in] */ long *image,
            /* [in] */ float ratio,
            /* [in] */ long byte_clipping,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Gray_Multiply( 
            /* [in] */ long *image,
            /* [in] */ float ratio,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Gray_Multiply2( 
            /* [in] */ long *image,
            /* [in] */ float ratio,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Gray_Quant_Segment( 
            /* [in] */ long *image,
            /* [in] */ long gray_levels,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Graylevel_Quant( 
            /* [in] */ long *image,
            /* [in] */ long gray_levels,
            /* [in] */ long choice,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Graylevel_Remap( 
            /* [in] */ long *image,
            /* [in] */ long r_selection,
            /* [in] */ long g_selection,
            /* [in] */ long b_selection,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GVFSnake_Segment( 
            /* [in] */ long *image,
            /* [in] */ long *coordinates,
            /* [in] */ long iterations,
            /* [in] */ double alpha,
            /* [in] */ double beta,
            /* [in] */ double kappa,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE H_image( 
            /* [in] */ long mask_type,
            /* [in] */ long height,
            /* [in] */ long width,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Haar_Transform( 
            /* [in] */ long *image,
            /* [in] */ long direction,
            /* [in] */ long blocksize,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Harmonic_Filter( 
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Harris_Corner_Filter( 
            /* [in] */ long *image,
            /* [in] */ float alpha,
            /* [in] */ long threshold,
            /* [in] */ long border,
            /* [in] */ float dmin,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE High_Freq_Emphasis( 
            /* [in] */ long *image,
            /* [in] */ long blocksize,
            /* [in] */ long keepdc,
            /* [in] */ long cutoff,
            /* [in] */ double alpha,
            /* [in] */ long filter_order,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Highboost( 
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [in] */ long center_value,
            /* [in] */ long add2original,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HighFreq_Emphasis( 
            /* [in] */ long *image,
            /* [in] */ long xform,
            /* [in] */ long cutoff,
            /* [in] */ long filter_order,
            /* [in] */ double offset,
            /* [in] */ long keepdc,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Highpass_Spatial( 
            /* [in] */ long *image,
            /* [in] */ long add2original,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Hist_Feature( 
            /* [in] */ long *image,
            /* [in] */ long *labeled_image,
            /* [in] */ long row,
            /* [in] */ long col,
            /* [retval][out] */ VARIANT *features) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Hist_Slide( 
            /* [in] */ long *image,
            /* [in] */ int slide,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Hist_Spec( 
            /* [in] */ long *image,
            /* [in] */ BSTR *r_histogram,
            /* [in] */ BSTR *g_histogram,
            /* [in] */ BSTR *b_histogram,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Hist_Stretch( 
            /* [in] */ long *image,
            /* [in] */ int low_limit,
            /* [in] */ int high_limit,
            /* [in] */ float low_clip,
            /* [in] */ float high_clip,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Hist_Thresh_Gray( 
            /* [in] */ long *image,
            /* [in] */ float tore,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Hist_Thresh_Segment( 
            /* [in] */ long *image,
            /* [in] */ float tore,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Histeq( 
            /* [in] */ long *image,
            /* [in] */ int band,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Histogram_Spec( 
            /* [in] */ long *image,
            /* [in] */ double *histogram,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE History_Add( 
            /* [in] */ long *image,
            /* [in] */ long *history) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE History_Check( 
            /* [in] */ long *image,
            /* [in] */ int program,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE History_Copy( 
            /* [in] */ long *source,
            /* [in] */ long *destination) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE history_create( 
            /* [in] */ long prog,
            /* [in] */ long type,
            /* [in] */ float value,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE history_create2( 
            /* [in] */ long prog,
            /* [in] */ long type,
            /* [in] */ int value1,
            /* [in] */ int value2,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE History_Delete_Program( 
            /* [in] */ long *image,
            /* [in] */ int program,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE History_Get( 
            /* [in] */ long *image,
            /* [in] */ int program,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE History_get_data( 
            /* [in] */ long *history,
            /* [in] */ int program,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE History_get_data2( 
            /* [in] */ long *history,
            /* [in] */ int program,
            /* [in] */ int index,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Homomorphic( 
            /* [in] */ long *image,
            /* [in] */ double upper_limit,
            /* [in] */ double lower_limit,
            /* [in] */ long cutoff,
            /* [in] */ long add2original,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Horizontal_Flip( 
            /* [in] */ long *image,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Hough_Filter( 
            /* [in] */ long *image,
            /* [in] */ BSTR *image_name,
            /* [in] */ BSTR *angles_of_interest,
            /* [in] */ long threshold,
            /* [in] */ long connection_distance,
            /* [in] */ long interactive,
            /* [in] */ long delta_length,
            /* [in] */ long segment_length,
            /* [in] */ long intermediate_result,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Huf_Compress( 
            /* [in] */ BSTR *filename,
            /* [in] */ long *image) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Huf_Decompress( 
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Idct_Transform( 
            /* [in] */ long *image,
            /* [in] */ long blocksize,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Ideal_Band_Pass( 
            /* [in] */ long *image,
            /* [in] */ long blocksize,
            /* [in] */ long keepdc,
            /* [in] */ long inner_cutoff,
            /* [in] */ long outer_cutoff,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Ideal_Band_Reject( 
            /* [in] */ long *image,
            /* [in] */ long blocksize,
            /* [in] */ long keepdc,
            /* [in] */ long inner_cutoff,
            /* [in] */ long outer_cutoff,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Ideal_High( 
            /* [in] */ long *image,
            /* [in] */ long blocksize,
            /* [in] */ long keepdc,
            /* [in] */ long cutoff,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Ideal_Low( 
            /* [in] */ long *image,
            /* [in] */ long blocksize,
            /* [in] */ long keepdc,
            /* [in] */ long cutoff,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Ifft_Transform( 
            /* [in] */ long *image,
            /* [in] */ long blocksize,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Igs_Segment( 
            /* [in] */ long *image,
            /* [in] */ long gray_levels,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Improved_Mmse_Filter( 
            /* [in] */ long *image,
            /* [in] */ float threshold,
            /* [in] */ long kernel_size,
            /* [in] */ float noise_variance,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Input_Mesh( 
            /* [in] */ long *points,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Intensity_Slicing( 
            /* [in] */ long *image,
            /* [in] */ long *lookup_table,
            /* [in] */ long options,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Inverse_Xformfilter( 
            /* [in] */ long *degr_image,
            /* [in] */ long *degr_fn,
            /* [in] */ long max_gain,
            /* [in] */ double cutoff,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Ipct( 
            /* [in] */ long *image,
            /* [in] */ long ignore_background,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Irregular( 
            /* [in] */ long *labeled_image,
            /* [in] */ int row,
            /* [in] */ int col,
            /* [retval][out] */ double *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Jp2_Decoder( 
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Jp2_Encoder( 
            /* [in] */ BSTR *filename,
            /* [in] */ long *image,
            /* [in] */ int rate,
            /* [in] */ int quality,
            /* [in] */ int layers,
            /* [in] */ int blocksize) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Jpg_Compress( 
            /* [in] */ BSTR *filename,
            /* [in] */ long *image,
            /* [in] */ int quality,
            /* [in] */ long grayscale,
            /* [in] */ long optimize,
            /* [in] */ int smooth,
            /* [in] */ long verbose,
            /* [in] */ BSTR *qtablesFile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Jpg_Decompress( 
            /* [in] */ BSTR *filename,
            /* [in] */ int num_colors,
            /* [in] */ long blocksmooth,
            /* [in] */ long grayscale,
            /* [in] */ long nodither,
            /* [in] */ long verbose,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Jpgtocvip( 
            /* [in] */ BSTR *filename,
            /* [in] */ int num_colors,
            /* [in] */ long blocksmooth,
            /* [in] */ long grayscale,
            /* [in] */ long nodither,
            /* [in] */ long verbose,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE K_Nearest_Neighbor( 
            /* [in] */ BSTR *test_set,
            /* [in] */ BSTR *training_set,
            /* [in] */ BSTR *outputfile,
            /* [in] */ int normalization,
            /* [in] */ int distance_measure,
            /* [in] */ int k,
            /* [in] */ float s_min,
            /* [in] */ float s_max,
            /* [in] */ float r_softmax,
            /* [in] */ float r_minkowski,
            /* [retval][out] */ long *error) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Krisch_Filter( 
            /* [in] */ long *image,
            /* [in] */ long *dir_image,
            /* [in] */ long filter_type,
            /* [in] */ long kernel_size,
            /* [in] */ long keepdc,
            /* [in] */ long threshold,
            /* [retval][out] */ long *mag_image) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Kuwahara_Filter( 
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Label( 
            /* [in] */ long *image,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Laws_Texture_Feature( 
            /* [in] */ long *image,
            /* [in] */ long *labeled_image,
            /* [in] */ int row,
            /* [in] */ int col,
            /* [in] */ int window_size,
            /* [in] */ int vector1,
            /* [in] */ int vector2,
            /* [retval][out] */ VARIANT *features) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Least_Squares( 
            /* [in] */ long *degr_image,
            /* [in] */ long *degr_fn,
            /* [in] */ long *smoothness_fn,
            /* [in] */ double gamma,
            /* [in] */ long max_gain,
            /* [in] */ long cutoff,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Local_Adaptive_Zoom( 
            /* [in] */ long *image,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Local_Histeq( 
            /* [in] */ long *image,
            /* [in] */ int blocksize,
            /* [in] */ int band,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Log_Ace_Filter( 
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [in] */ double local_mean,
            /* [in] */ double local_gain,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Log_Remap( 
            /* [in] */ long *image,
            /* [in] */ long band,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LogMap_Image( 
            /* [in] */ long *image,
            /* [in] */ int band,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Lum_Average( 
            /* [in] */ long *image,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Luminance_Image( 
            /* [in] */ long *image,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Make_Histogram( 
            /* [in] */ double *histogram,
            /* [in] */ long image_format,
            /* [in] */ long color_format,
            /* [in] */ long bands,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Marr_Hildreth_Filter( 
            /* [in] */ long *image,
            /* [in] */ float sigma,
            /* [in] */ int threshold,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Maximum_Filter( 
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Mean_Filter( 
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Median_Cut_Segment( 
            /* [in] */ long *image,
            /* [in] */ long num_colors,
            /* [in] */ long ignore_background,
            /* [in] */ long r_background,
            /* [in] */ long g_background,
            /* [in] */ long b_background,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Median_Filter( 
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Mesh_To_File( 
            /* [in] */ BSTR *filename,
            /* [in] */ long *mesh) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Mesh_Warping( 
            /* [in] */ long *image,
            /* [in] */ long *mesh,
            /* [in] */ long interpolation_method,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Mesh_WarpingRI( 
            /* [in] */ long *image,
            /* [in] */ long *mesh,
            /* [in] */ long interpolation_method,
            /* [in] */ long zero_missing,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Midpoint_Filter( 
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Minimum_Filter( 
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Mmse_Filter( 
            /* [in] */ long *image,
            /* [in] */ double noise_variance,
            /* [in] */ long kernel_size,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Moravec_Corner_Filter( 
            /* [in] */ long *image,
            /* [in] */ float threshold,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Morph_Hitmiss( 
            /* [in] */ long *binary_image,
            /* [in] */ long masksize,
            /* [in] */ double *mask_values,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Morph_Skeleton( 
            /* [in] */ long *binary_image,
            /* [in] */ long masksize,
            /* [in] */ double *mask_values,
            /* [in] */ long iterations,
            /* [in] */ long four_eight_mask,
            /* [in] */ long method,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Morph_Thinning( 
            /* [in] */ long *binary_image,
            /* [in] */ long masksize,
            /* [in] */ double *mask_values,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MorphClose( 
            /* [in] */ long *image,
            /* [in] */ int kernel_type,
            /* [in] */ int kernel_size,
            /* [in] */ int height,
            /* [in] */ int width,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MorphClose_Image( 
            /* [in] */ long *image,
            /* [in] */ long *matrix,
            /* [in] */ int userOrg,
            /* [in] */ int x,
            /* [in] */ int y,
            /* [in] */ int size,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MorphDilate( 
            /* [in] */ long *image,
            /* [in] */ int kernel_type,
            /* [in] */ int kernel_size,
            /* [in] */ int height,
            /* [in] */ int width,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MorphDilate_Image( 
            /* [in] */ long *image,
            /* [in] */ int *matrix,
            /* [in] */ int userOrg,
            /* [in] */ int x,
            /* [in] */ int y,
            /* [in] */ int size,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MorphErode( 
            /* [in] */ long *image,
            /* [in] */ int kernel_type,
            /* [in] */ int kernel_size,
            /* [in] */ int height,
            /* [in] */ int width,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MorphErode_Image( 
            /* [in] */ long *image,
            /* [in] */ long *matrix,
            /* [in] */ int userOrg,
            /* [in] */ int x,
            /* [in] */ int y,
            /* [in] */ int size,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Morpho( 
            /* [in] */ long *image,
            /* [in] */ BSTR *surrounds_string,
            /* [in] */ long rotation,
            /* [in] */ long boolfunc,
            /* [in] */ long connectedness,
            /* [in] */ long iterations,
            /* [in] */ long fields,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Morpho_com( 
            /* [in] */ long *image,
            /* [in] */ BSTR *surrounds_string,
            /* [in] */ long rotation,
            /* [in] */ long boolfunc,
            /* [in] */ long iterations,
            /* [in] */ long subfields,
            /* [in] */ long unused,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MorphOpen( 
            /* [in] */ long *image,
            /* [in] */ int kernel_type,
            /* [in] */ int kernel_size,
            /* [in] */ int height,
            /* [in] */ int width,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MorphOpen_Image( 
            /* [in] */ long *image,
            /* [in] */ long *matrix,
            /* [in] */ int userOrg,
            /* [in] */ int x,
            /* [in] */ int y,
            /* [in] */ int size,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Multi_Resolution_Segment( 
            /* [in] */ long *image,
            /* [in] */ long homogeneity_test,
            /* [in] */ double param1,
            /* [in] */ double param2,
            /* [in] */ long run_PCT,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Multiply_Image( 
            /* [in] */ long *image1,
            /* [in] */ long *image2,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Nearest_Centroid( 
            /* [in] */ BSTR *test_set,
            /* [in] */ BSTR *training_set,
            /* [in] */ BSTR *outputfile,
            /* [in] */ int normalization,
            /* [in] */ int distance_measure,
            /* [in] */ float s_min,
            /* [in] */ float s_max,
            /* [in] */ float r_softmax,
            /* [in] */ float r_minkowski,
            /* [retval][out] */ long *error) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Nearest_Neighbor( 
            /* [in] */ BSTR *test_set,
            /* [in] */ BSTR *training_set,
            /* [in] */ BSTR *outputfile,
            /* [in] */ int normalization,
            /* [in] */ int distance_measure,
            /* [in] */ float s_min,
            /* [in] */ float s_max,
            /* [in] */ float r_softmax,
            /* [in] */ float r_minkowski,
            /* [retval][out] */ long *error) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Neg_Exp_Noise( 
            /* [in] */ long *image,
            /* [in] */ double variance,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE New_Image( 
            /* [in] */ long image_format,
            /* [in] */ long color_space,
            /* [in] */ int bands,
            /* [in] */ int height,
            /* [in] */ int width,
            /* [in] */ long datatype,
            /* [in] */ long data_format,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Nonfft_Xformfilter( 
            /* [in] */ long *image,
            /* [in] */ long blocksize,
            /* [in] */ long keepdc,
            /* [in] */ long filter_type,
            /* [in] */ long p1,
            /* [in] */ double p2,
            /* [in] */ long filter_order,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Not_Image( 
            /* [in] */ long *image,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Notch( 
            /* [in] */ BSTR *filename,
            /* [in] */ long *cols,
            /* [in] */ long *rows,
            /* [in] */ long *radius,
            /* [in] */ long *image,
            /* [in] */ long num_points,
            /* [in] */ long interactive,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Object_Crop( 
            /* [in] */ long *image,
            /* [in] */ long *coordinates,
            /* [in] */ long format,
            /* [in] */ long r_value,
            /* [in] */ long g_value,
            /* [in] */ long b_value,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Open_Consol_Redirect_Output( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Or_Image( 
            /* [in] */ long *image1,
            /* [in] */ long *image2,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Orientation( 
            /* [in] */ long *labeled_image,
            /* [in] */ int row,
            /* [in] */ int col,
            /* [retval][out] */ long *orientation) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Otsu_Segment( 
            /* [in] */ long *image,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Param_AD_Filter( 
            /* [in] */ long *image,
            /* [in] */ long iterations,
            /* [in] */ long speed,
            /* [in] */ long edge_height,
            /* [in] */ long blocksize,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Parametric_Wiener( 
            /* [in] */ long *degr_image,
            /* [in] */ long *degr_fn,
            /* [in] */ long *psd_noise,
            /* [in] */ long *psd_orig,
            /* [in] */ double gamma,
            /* [in] */ long max_gain,
            /* [in] */ long cutoff,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Pct( 
            /* [in] */ long *image,
            /* [in] */ long ignore_background,
            /* [in] */ double *background,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Pct_Color( 
            /* [in] */ long *image,
            /* [in] */ long ignore_background,
            /* [in] */ double *background,
            /* [in] */ long choice,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Pct_Median_Segment( 
            /* [in] */ long *image,
            /* [in] */ long num_colors,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Perimeter( 
            /* [in] */ long *labeled_image,
            /* [in] */ int row,
            /* [in] */ int col,
            /* [retval][out] */ long *perimeter) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Pngtocvip( 
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Power_Spect_Eq( 
            /* [in] */ long *degr_image,
            /* [in] */ long *degr_fn,
            /* [in] */ long *psd_noise,
            /* [in] */ long *psd_orig,
            /* [in] */ long max_gain,
            /* [in] */ long cutoff,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Pratt_Merit( 
            /* [in] */ long *image1,
            /* [in] */ long *image2,
            /* [in] */ double scale_factor,
            /* [retval][out] */ double *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Prewitt_Filter( 
            /* [in] */ long *image,
            /* [in] */ long *dir_image,
            /* [in] */ long filter_type,
            /* [in] */ long kernel_size,
            /* [in] */ long keepdc,
            /* [in] */ long threshold,
            /* [retval][out] */ long *mag_image) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Print_Image( 
            /* [in] */ int dc,
            /* [in] */ long *image) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Projection( 
            /* [in] */ long *labeled_image,
            /* [in] */ int row,
            /* [in] */ int col,
            /* [in] */ int height,
            /* [in] */ int width,
            /* [retval][out] */ VARIANT *projections) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Pseudo_Remap( 
            /* [in] */ long *image,
            /* [in] */ long *lookup_table,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Pseudocol_Freq( 
            /* [in] */ long *image,
            /* [in] */ int low_cutoff,
            /* [in] */ int high_cutoff,
            /* [in] */ int lowpass_band,
            /* [in] */ int bandpass_band,
            /* [in] */ int highpass_band,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Raster_Deblur_Filter( 
            /* [in] */ long *image,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Rayleigh_Noise( 
            /* [in] */ long *image,
            /* [in] */ double variance,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Read_Image( 
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remap_Image( 
            /* [in] */ long *image,
            /* [in] */ long datatype,
            /* [in] */ long dmin,
            /* [in] */ long dmax,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE REMAPP( 
            /* [in] */ long *image,
            /* [in] */ long datatype,
            /* [in] */ long dmin,
            /* [in] */ long dmax,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Render_DisplayImage( 
            /* [in] */ long window_dc,
            /* [in] */ long *image,
            /* [retval][out] */ long *memory_dc) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Rms_Error( 
            /* [in] */ long *image1,
            /* [in] */ long *image2,
            /* [retval][out] */ VARIANT *rms_values) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Robinson_Filter( 
            /* [in] */ long *image,
            /* [in] */ long *dir_image,
            /* [in] */ long mask_type,
            /* [in] */ long masksize,
            /* [in] */ long keepdc,
            /* [in] */ long threshold,
            /* [retval][out] */ long *mag_image) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Rotate( 
            /* [in] */ long *image,
            /* [in] */ float degrees,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Rst_invariant( 
            /* [in] */ long *labeled_image,
            /* [in] */ long row,
            /* [in] */ long col,
            /* [retval][out] */ VARIANT *features) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save_Compressed_Data( 
            /* [in] */ long *image,
            /* [in] */ BSTR *filename) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Sct_Split_Segment( 
            /* [in] */ long *image,
            /* [in] */ long A_split,
            /* [in] */ long B_split,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Set_Console( 
            /* [in] */ long unused) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Sharpen_I( 
            /* [in] */ long *image,
            /* [in] */ long remap,
            /* [in] */ long mask_type,
            /* [in] */ long masksize,
            /* [in] */ float low_clip,
            /* [in] */ float high_clip,
            /* [in] */ long add2original,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Sharpen_II( 
            /* [in] */ long *image,
            /* [in] */ long add2original,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Sharpen_III( 
            /* [in] */ long *image,
            /* [in] */ long add2original,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Shen_Castan_Filter( 
            /* [in] */ long *image,
            /* [in] */ double smoothing_factor,
            /* [in] */ long window_size,
            /* [in] */ double low_threshold,
            /* [in] */ double high_threshold,
            /* [in] */ long thin_factor,
            /* [in] */ long *intermediate_image,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Show_DisplayImage( 
            /* [in] */ long window_dc,
            /* [in] */ long memory_dc,
            /* [in] */ long window_width,
            /* [in] */ long window_height,
            /* [in] */ long memory_width,
            /* [in] */ long memory_height) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Show_Image( 
            /* [in] */ int dc,
            /* [in] */ int x,
            /* [in] */ int y,
            /* [in] */ long *image) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Show_Image_Ex( 
            /* [in] */ int window_dc,
            /* [in] */ long *memory_dc,
            /* [in] */ int x,
            /* [in] */ int y,
            /* [in] */ long *image) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Shrink( 
            /* [in] */ long *image,
            /* [in] */ float factor,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Simple_Wiener( 
            /* [in] */ long *degr_image,
            /* [in] */ long *degr_fn,
            /* [in] */ double k,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Single_Filter( 
            /* [in] */ long *image,
            /* [in] */ double sizing_factor_x,
            /* [in] */ double sizing_factor_y,
            /* [in] */ long centerx,
            /* [in] */ long centery,
            /* [in] */ double rotation,
            /* [in] */ double beta,
            /* [in] */ long kernel_size,
            /* [in] */ double *kernel_data,
            /* [in] */ long choice,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Snr( 
            /* [in] */ long *image1,
            /* [in] */ long *image2,
            /* [retval][out] */ VARIANT *snr_values) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Sobel_Filter( 
            /* [in] */ long *image,
            /* [in] */ long *dir_image,
            /* [in] */ long filter_type,
            /* [in] */ long kernel_size,
            /* [in] */ long keepdc,
            /* [in] */ long threshold,
            /* [retval][out] */ long *mag_image) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Spatial_Quant( 
            /* [in] */ long *image,
            /* [in] */ int rows,
            /* [in] */ int cols,
            /* [in] */ int method,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Spec_Hist_Image( 
            /* [in] */ long *image,
            /* [in] */ BSTR *r_histogram,
            /* [in] */ BSTR *g_histogram,
            /* [in] */ BSTR *b_histogram,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Specify_Filter( 
            /* [in] */ long *image,
            /* [in] */ long mask_height,
            /* [in] */ long mask_width,
            /* [in] */ double *mask_values,
            /* [in] */ int normalization,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Speckle_Noise( 
            /* [in] */ long *image,
            /* [in] */ double psalt,
            /* [in] */ double ppepper,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Spectral_Feature( 
            /* [in] */ long *image,
            /* [in] */ long *labeled_image,
            /* [in] */ long rings,
            /* [in] */ long sectors,
            /* [in] */ long row,
            /* [in] */ long col,
            /* [retval][out] */ VARIANT *features) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Split_Merge_Segment( 
            /* [in] */ long *image,
            /* [in] */ long level,
            /* [in] */ long homogeneity_test,
            /* [in] */ double param1,
            /* [in] */ double param2,
            /* [in] */ long run_PCT,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Subtract_Image( 
            /* [in] */ long *image1,
            /* [in] */ long *image2,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TextureFeature( 
            /* [in] */ long *image,
            /* [in] */ long *labeled_image,
            /* [in] */ long row,
            /* [in] */ long col,
            /* [in] */ long distance,
            /* [in] */ long bitmask,
            /* [retval][out] */ VARIANT *features) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TextureFeature2( 
            /* [in] */ long *image,
            /* [in] */ long *labeled_image,
            /* [in] */ long band,
            /* [in] */ long row,
            /* [in] */ long col,
            /* [in] */ long distance,
            /* [in] */ long energy,
            /* [in] */ long inertia,
            /* [in] */ long correlation,
            /* [in] */ long inv_diff,
            /* [in] */ long entropy,
            /* [in] */ long include_zero_pairs,
            /* [retval][out] */ VARIANT *features) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Thinness( 
            /* [in] */ long *labeled_image,
            /* [in] */ int row,
            /* [in] */ int col,
            /* [retval][out] */ double *thinness) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Threshold_Segment( 
            /* [in] */ long *image,
            /* [in] */ long threshold,
            /* [in] */ long byte_remap,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Tifftocvip( 
            /* [in] */ BSTR *filename,
            /* [in] */ int verbose,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Tile_by_name( 
            /* [in] */ BSTR *filename) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Transform_Compression( 
            /* [in] */ long *image,
            /* [in] */ BSTR *filename,
            /* [in] */ BSTR *quantfile,
            /* [in] */ long color_space,
            /* [in] */ long xform,
            /* [in] */ long basis,
            /* [in] */ long blocksize,
            /* [in] */ long quantization,
            /* [in] */ long use_quant_table,
            /* [in] */ long use_vector_quant,
            /* [in] */ long datatype,
            /* [in] */ long remap_type,
            /* [in] */ long keepdc,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Transform_Sharpen( 
            /* [in] */ long *image,
            /* [in] */ long xform,
            /* [in] */ long cutoff,
            /* [in] */ long filter_type,
            /* [in] */ long filter_order,
            /* [in] */ long keepdc,
            /* [in] */ long add2original,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Transform_Smoothing( 
            /* [in] */ long *image,
            /* [in] */ long xform,
            /* [in] */ long cutoff,
            /* [in] */ long filter_type,
            /* [in] */ long filter_order,
            /* [in] */ long keepdc,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Translate( 
            /* [in] */ long *image,
            /* [in] */ long wrap,
            /* [in] */ int row_offset,
            /* [in] */ int col_offset,
            /* [in] */ int rows,
            /* [in] */ int cols,
            /* [in] */ int row_slide,
            /* [in] */ int col_slide,
            /* [in] */ float fill_val,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Uniform_Noise( 
            /* [in] */ long *image,
            /* [in] */ double variance,
            /* [in] */ double mean,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Unsharp_Filter( 
            /* [in] */ long *image,
            /* [in] */ long lower_limit,
            /* [in] */ long upper_limit,
            /* [in] */ double low_clip,
            /* [in] */ double high_clip,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Vertical_Flip( 
            /* [in] */ long *image,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Vq_Compress( 
            /* [in] */ long *image,
            /* [in] */ BSTR *filename,
            /* [in] */ long use_file_codebook,
            /* [in] */ long use_fixed_codebook,
            /* [in] */ double error_threshold,
            /* [in] */ BSTR *codebook_filename,
            /* [in] */ long num_entries,
            /* [in] */ long vector_height,
            /* [in] */ long vector_width,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Vq_Decompress( 
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Walhad_Transform( 
            /* [in] */ long *image,
            /* [in] */ long xform,
            /* [in] */ long blocksize,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Watershed_Segment( 
            /* [in] */ long *image,
            /* [in] */ int merge_result,
            /* [in] */ float threshold,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Wavdaub4_Transform( 
            /* [in] */ long *image,
            /* [in] */ long direction,
            /* [in] */ long low_band,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Wavhaar_Transform( 
            /* [in] */ long *image,
            /* [in] */ long direction,
            /* [in] */ long low_band,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Wiener( 
            /* [in] */ long *degr_image,
            /* [in] */ long *degr_fn,
            /* [in] */ long *psd_noise,
            /* [in] */ long *psd_orig,
            /* [in] */ long max_gain,
            /* [in] */ long cutoff,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Write_Image( 
            /* [in] */ long *image,
            /* [in] */ BSTR *filename,
            /* [in] */ long retain_image,
            /* [in] */ long run_setup,
            /* [in] */ long image_format,
            /* [in] */ long verbose) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Write_JPEG_Image( 
            /* [in] */ long *image,
            /* [in] */ BSTR *filename,
            /* [in] */ long retain_image,
            /* [in] */ long run_setup,
            /* [in] */ long image_format,
            /* [in] */ long verbose,
            /* [in] */ int ratio) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Xor_Error( 
            /* [in] */ long *image1,
            /* [in] */ long *image2,
            /* [retval][out] */ VARIANT *error_values) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Xor_Image( 
            /* [in] */ long *image1,
            /* [in] */ long *image2,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Xvq_Compress( 
            /* [in] */ long *image,
            /* [in] */ long xform,
            /* [in] */ long scheme,
            /* [in] */ BSTR *filename,
            /* [in] */ long output_data_type,
            /* [in] */ long remap_type,
            /* [in] */ long dc_term_handling,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Xvq_Decompress( 
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Ypmean_Filter( 
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [in] */ long p,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Zon_Compress( 
            /* [in] */ BSTR *filename,
            /* [in] */ long *image,
            /* [in] */ int blocksize,
            /* [in] */ int xform,
            /* [in] */ int mask_type,
            /* [in] */ float compression_ratio) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Zon_Decompress( 
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Zon2_Compress( 
            /* [in] */ BSTR *filename,
            /* [in] */ long *image,
            /* [in] */ int blocksize,
            /* [in] */ int xform,
            /* [in] */ int mask_type,
            /* [in] */ float compression_ratio) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Zon2_Decompress( 
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Zoom( 
            /* [in] */ long *image,
            /* [in] */ int quadrant,
            /* [in] */ int col,
            /* [in] */ int row,
            /* [in] */ int cols,
            /* [in] */ int rows,
            /* [in] */ float factor_requested,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Zvl_Compress( 
            /* [in] */ BSTR *filename,
            /* [in] */ long *image) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Zvl_Decompress( 
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Dice_Coef( 
            /* [in] */ long *image1,
            /* [in] */ long *image2,
            /* [retval][out] */ VARIANT *error_values) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Jaccard_Index( 
            /* [in] */ long *image1,
            /* [in] */ long *image2,
            /* [retval][out] */ VARIANT *error_values) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Overlap_Coef( 
            /* [in] */ long *image1,
            /* [in] */ long *image2,
            /* [retval][out] */ VARIANT *error_values) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CLAHE( 
            /* [in] */ long *image,
            /* [in] */ int blocksize,
            /* [in] */ double clippercent,
            /* [in] */ int band,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CLAHE_Grid( 
            /* [in] */ long *image,
            /* [in] */ int blocksize,
            /* [in] */ double clippercent,
            /* [in] */ int band,
            /* [retval][out] */ long *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE superPixel( 
            /* [in] */ long *image,
            /* [retval][out] */ long *result) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICVIPToolsVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICVIPTools * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICVIPTools * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICVIPTools * This);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfoCount)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICVIPTools * This,
            /* [out] */ UINT *pctinfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetTypeInfo)
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICVIPTools * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        DECLSPEC_XFGVIRT(IDispatch, GetIDsOfNames)
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICVIPTools * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        DECLSPEC_XFGVIRT(IDispatch, Invoke)
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICVIPTools * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Ace2_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Ace2_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [in] */ double local_mean,
            /* [in] */ double local_gain,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Acuity_Nightvision_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Acuity_Nightvision_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long reason,
            /* [in] */ long threshold,
            /* [in] */ long acuity,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, AD_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AD_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long iterations,
            /* [in] */ long speed,
            /* [in] */ long edge_height,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Adapt_Median_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Adapt_Median_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Adaptive_Contrast_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Adaptive_Contrast_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ double k1,
            /* [in] */ double k2,
            /* [in] */ long kernel_size,
            /* [in] */ double min_gain,
            /* [in] */ double max_gain,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Add_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Add_Image )( 
            ICVIPTools * This,
            /* [in] */ long *image1,
            /* [in] */ long *image2,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Alpha_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Alpha_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [in] */ long p,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, And_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *And_Image )( 
            ICVIPTools * This,
            /* [in] */ long *image1,
            /* [in] */ long *image2,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Area)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Area )( 
            ICVIPTools * This,
            /* [in] */ long *labeled_image,
            /* [in] */ int row,
            /* [in] */ int col,
            /* [retval][out] */ long *area);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Aspect)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Aspect )( 
            ICVIPTools * This,
            /* [in] */ long *labeled_image,
            /* [in] */ int row,
            /* [in] */ int col,
            /* [retval][out] */ double *aspect);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Assemble_Bands)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Assemble_Bands )( 
            ICVIPTools * This,
            /* [in] */ long bands[ 3 ],
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Auto_Threshold_Segment)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Auto_Threshold_Segment )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ float limit,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Bilinear_Interp)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Bilinear_Interp )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ float factor,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Bilinear_Interp1)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Bilinear_Interp1 )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ float xfactor,
            /* [in] */ float yfactor,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Bintocvip)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Bintocvip )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ long bands,
            /* [in] */ long color_order,
            /* [in] */ long interleaved,
            /* [in] */ int height,
            /* [in] */ int width,
            /* [in] */ long verbose,
            /* [retval][out] */ long *cvip_image);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Bit_Compress)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Bit_Compress )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ long *image,
            /* [in] */ long bitmask);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Bit_Decompress)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Bit_Decompress )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Boiecox_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Boiecox_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ double variance,
            /* [in] */ long do_threshold,
            /* [in] */ long do_hyst,
            /* [in] */ long do_thin,
            /* [in] */ double high_threshold,
            /* [in] */ double low_threshold,
            /* [in] */ long *threshhold_image,
            /* [in] */ long *hyst_image,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Btc_Compress)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Btc_Compress )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ long *image,
            /* [in] */ long blocksize);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Btc_Decompression)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Btc_Decompression )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Btc2_Compress)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Btc2_Compress )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ long *image,
            /* [in] */ long blocksize);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Btc2_Decompress)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Btc2_Decompress )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Btc3_Compress)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Btc3_Compress )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ long *image,
            /* [in] */ long blocksize);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Btc3_Decompress)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Btc3_Decompress )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Butterworth_Band_Pass)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Butterworth_Band_Pass )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long blocksize,
            /* [in] */ long keepdc,
            /* [in] */ long inner_cutoff,
            /* [in] */ long outer_cutoff,
            /* [in] */ long filter_order,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Butterworth_Band_Reject)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Butterworth_Band_Reject )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long blocksize,
            /* [in] */ long keepdc,
            /* [in] */ long inner_cutoff,
            /* [in] */ long outer_cutoff,
            /* [in] */ long filter_order,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Butterworth_High)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Butterworth_High )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long blocksize,
            /* [in] */ long keepdc,
            /* [in] */ long cutoff,
            /* [in] */ long filter_order,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Butterworth_Low)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Butterworth_Low )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long blocksize,
            /* [in] */ long keepdc,
            /* [in] */ long cutoff,
            /* [in] */ long filter_order,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Canny_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Canny_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ double low_threshold,
            /* [in] */ double high_threshold,
            /* [in] */ double variance,
            /* [in] */ long *mag_image,
            /* [in] */ long *dir_image,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Cast_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Cast_Image )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long datatype);
        
        DECLSPEC_XFGVIRT(ICVIPTools, CentroID)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CentroID )( 
            ICVIPTools * This,
            /* [in] */ long *labeled_image,
            /* [in] */ long row,
            /* [in] */ long col,
            /* [retval][out] */ VARIANT *centroid);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Cerchar_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Cerchar_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Check_Bin)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Check_Bin )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [retval][out] */ long *is_binary);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Check_xform_history)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Check_xform_history )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ int filter_type,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Close_Consol)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Close_Consol )( 
            ICVIPTools * This);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Close_Console)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Close_Console )( 
            ICVIPTools * This);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Color_Contrast_Enhance)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Color_Contrast_Enhance )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long low_limit,
            /* [in] */ long high_limit,
            /* [in] */ float low_clip,
            /* [in] */ float high_clip,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, ColorXform)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ColorXform )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long color_space,
            /* [in] */ double *norm_vector,
            /* [in] */ double *white_reference,
            /* [in] */ long direction,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, CondRemap_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CondRemap_Image )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long datatype,
            /* [in] */ int min,
            /* [in] */ int max,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Contra_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Contra_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [in] */ long p,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Copy_Paste)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Copy_Paste )( 
            ICVIPTools * This,
            /* [in] */ long *src_image,
            /* [in] */ long *dest_image,
            /* [in] */ int src_row,
            /* [in] */ int src_col,
            /* [in] */ int height,
            /* [in] */ int width,
            /* [in] */ int dest_row,
            /* [in] */ int dest_col,
            /* [in] */ long transparent,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Create_Black)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Create_Black )( 
            ICVIPTools * This,
            /* [in] */ int width,
            /* [in] */ int height,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Create_Checkboard)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Create_Checkboard )( 
            ICVIPTools * This,
            /* [in] */ int width,
            /* [in] */ int height,
            /* [in] */ int start_col,
            /* [in] */ int start_row,
            /* [in] */ int blockx,
            /* [in] */ int blocky,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Create_Circle)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Create_Circle )( 
            ICVIPTools * This,
            /* [in] */ int width,
            /* [in] */ int height,
            /* [in] */ int centerx,
            /* [in] */ int centery,
            /* [in] */ int radius,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Create_Cosine)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Create_Cosine )( 
            ICVIPTools * This,
            /* [in] */ int img_size,
            /* [in] */ int frequency,
            /* [in] */ int direction,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Create_Degenerate_Circle)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Create_Degenerate_Circle )( 
            ICVIPTools * This,
            /* [in] */ int width,
            /* [in] */ int height,
            /* [in] */ int centerx,
            /* [in] */ int centery,
            /* [in] */ int radius,
            /* [in] */ int blur,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Create_Ellipse)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Create_Ellipse )( 
            ICVIPTools * This,
            /* [in] */ int width,
            /* [in] */ int height,
            /* [in] */ int centerx,
            /* [in] */ int centery,
            /* [in] */ int shape_width,
            /* [in] */ int shape_height,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Create_Line)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Create_Line )( 
            ICVIPTools * This,
            /* [in] */ int width,
            /* [in] */ int height,
            /* [in] */ int tlx,
            /* [in] */ int tly,
            /* [in] */ int brx,
            /* [in] */ int bry,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Create_Mask)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Create_Mask )( 
            ICVIPTools * This,
            /* [in] */ long width,
            /* [in] */ long height,
            /* [in] */ double *values,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Create_Mesh_Sine)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Create_Mesh_Sine )( 
            ICVIPTools * This,
            /* [in] */ int rows,
            /* [in] */ int cols,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Create_Rectangle)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Create_Rectangle )( 
            ICVIPTools * This,
            /* [in] */ int width,
            /* [in] */ int height,
            /* [in] */ int tlx,
            /* [in] */ int tly,
            /* [in] */ int shape_width,
            /* [in] */ int shape_height,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Create_Sine)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Create_Sine )( 
            ICVIPTools * This,
            /* [in] */ int img_size,
            /* [in] */ int frequency,
            /* [in] */ int direction,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Create_Squarewave)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Create_Squarewave )( 
            ICVIPTools * This,
            /* [in] */ int img_size,
            /* [in] */ int frequency,
            /* [in] */ int direction,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Crop)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Crop )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ int start_row,
            /* [in] */ int start_col,
            /* [in] */ int rows,
            /* [in] */ int cols,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, CVIP_OUTPUT)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CVIP_OUTPUT )( 
            ICVIPTools * This,
            /* [retval][out] */ BSTR *message);
        
        DECLSPEC_XFGVIRT(ICVIPTools, CVIPhalftone)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CVIPhalftone )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ int halftone_method,
            /* [in] */ int maxval,
            /* [in] */ float threshold,
            /* [in] */ long retain_image,
            /* [in] */ long verbose,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Cviptoccc)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Cviptoccc )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ long maxcolor,
            /* [in] */ long verbose,
            /* [in] */ long dermvis,
            /* [in] */ long *cvip_image);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Cviptoeps)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Cviptoeps )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ long *cvip_image,
            /* [in] */ double scale_x,
            /* [in] */ double scale_y,
            /* [in] */ long band,
            /* [in] */ long verbose);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Cviptogif)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Cviptogif )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ long *cvip_image,
            /* [in] */ long interlace,
            /* [in] */ long verbose);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Cviptoiris)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Cviptoiris )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ long *cvip_image,
            /* [in] */ long verbose,
            /* [in] */ long prt_type);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Cviptoitex)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Cviptoitex )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ long *cvip_image,
            /* [in] */ BSTR *comment,
            /* [in] */ long verbose);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Cviptojpg)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Cviptojpg )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ long *cvip_image,
            /* [in] */ int quality,
            /* [in] */ long grayscale,
            /* [in] */ long optimize,
            /* [in] */ int smooth,
            /* [in] */ long verbose,
            /* [in] */ BSTR *qtablesFile);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Cviptopnm)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Cviptopnm )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ long *cvip_image,
            /* [in] */ long verbose);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Cviptoras)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Cviptoras )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ long *cvip_image,
            /* [in] */ long pr_type,
            /* [in] */ long verbose);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Cviptotiff)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Cviptotiff )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ long *cvip_image,
            /* [in] */ long compression,
            /* [in] */ long fillorder,
            /* [in] */ long g3options,
            /* [in] */ long predictor,
            /* [in] */ long rowsperstrip,
            /* [in] */ long verbose);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Cviptovip)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Cviptovip )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ long *cvip_image,
            /* [in] */ long verbose,
            /* [in] */ long save_history,
            /* [in] */ long is_compressed);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Date_Range)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Date_Range )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [retval][out] */ VARIANT *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Dct_Transform)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Dct_Transform )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long blocksize,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Delete_DisplayImage)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Delete_DisplayImage )( 
            ICVIPTools * This,
            /* [in] */ long memory_dc);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Delete_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Delete_Image )( 
            ICVIPTools * This,
            /* [in] */ long *image);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Divide_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Divide_Image )( 
            ICVIPTools * This,
            /* [in] */ long *image1,
            /* [in] */ long *image2,
            /* [in] */ long zero2num,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Dpc_Compress)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Dpc_Compress )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ long *image,
            /* [in] */ float ratio,
            /* [in] */ int bit_length,
            /* [in] */ int clipping,
            /* [in] */ int direction,
            /* [in] */ int origin,
            /* [in] */ float deviation);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Dpc_Decompress)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Dpc_Decompress )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Draw_mesh)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Draw_mesh )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long *mesh);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Duplicate_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Duplicate_Image )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, DynRLC_Compression)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DynRLC_Compression )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ long *image,
            /* [in] */ long window_size,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, DynRLC_deCompression)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DynRLC_deCompression )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Edge_Detect_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Edge_Detect_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long edge_detector,
            /* [in] */ long mask_type,
            /* [in] */ long masksize,
            /* [in] */ long keepdc,
            /* [in] */ long threshold,
            /* [in] */ long frei_projection,
            /* [in] */ long frei_threshold,
            /* [in] */ long frei_angle,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Edge_Link_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Edge_Link_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *binary_image,
            /* [in] */ long connection_distance,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Enlarge)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Enlarge )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ int rows,
            /* [in] */ int cols,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Epstocvip)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Epstocvip )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ long verbose);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Euler)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Euler )( 
            ICVIPTools * This,
            /* [in] */ long *labeled_image,
            /* [in] */ long row,
            /* [in] */ long col,
            /* [retval][out] */ long *euler);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Exp_Ace_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Exp_Ace_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [in] */ double local_mean,
            /* [in] */ double local_gain,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Extract_Band)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Extract_Band )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ int band,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Fft_Mag)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Fft_Mag )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Fft_Phase)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Fft_Phase )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long remap_norm,
            /* [in] */ double k,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Fft_Transform)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Fft_Transform )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long blocksize,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, File_To_Mesh)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *File_To_Mesh )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Fractal_Compression)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Fractal_Compression )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ BSTR *filename,
            /* [in] */ double tolerance,
            /* [in] */ long min_part,
            /* [in] */ long max_part,
            /* [in] */ long dom_type,
            /* [in] */ long dom_step,
            /* [in] */ long c1,
            /* [in] */ long c2,
            /* [in] */ long scalebits,
            /* [in] */ long offsetbits,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Fractal_deCompression)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Fractal_deCompression )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Fuzzyc_Segment)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Fuzzyc_Segment )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ double variance,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Gamma_Noise)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Gamma_Noise )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ double variance,
            /* [in] */ int alpha,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Gaussian_Blur_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Gaussian_Blur_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long kernel_size,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Gaussian_Noise)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Gaussian_Noise )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ double variance,
            /* [in] */ double mean,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Geometric_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Geometric_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Geometric_Mean)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Geometric_Mean )( 
            ICVIPTools * This,
            /* [in] */ long *degr_image,
            /* [in] */ long *degr_fn,
            /* [in] */ long *psd_noise,
            /* [in] */ long *psd_orig,
            /* [in] */ double gamma,
            /* [in] */ double alpha,
            /* [in] */ long max_gain,
            /* [in] */ long cutoff,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, get_hist_real)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *get_hist_real )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Get_Histogram_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Get_Histogram_Image )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Get_max_min_value)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Get_max_min_value )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ double *min_max);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Get_Mesh_Points)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Get_Mesh_Points )( 
            ICVIPTools * This,
            /* [in] */ long *mesh,
            /* [retval][out] */ VARIANT *points);
        
        DECLSPEC_XFGVIRT(ICVIPTools, GetDataFormat_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDataFormat_Image )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [retval][out] */ long *format);
        
        DECLSPEC_XFGVIRT(ICVIPTools, GetDataType_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetDataType_Image )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [retval][out] */ long *datatype);
        
        DECLSPEC_XFGVIRT(ICVIPTools, GetImageInfo)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetImageInfo )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [retval][out] */ VARIANT *info);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Getlast_Hist)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Getlast_Hist )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long *programs,
            /* [in] */ int num_programs,
            /* [retval][out] */ long *hist);
        
        DECLSPEC_XFGVIRT(ICVIPTools, GetNoOfBands_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetNoOfBands_Image )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [retval][out] */ long *bands);
        
        DECLSPEC_XFGVIRT(ICVIPTools, GetNoOfCols_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetNoOfCols_Image )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [retval][out] */ long *cols);
        
        DECLSPEC_XFGVIRT(ICVIPTools, GetNoOfRows_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetNoOfRows_Image )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [retval][out] */ long *rows);
        
        DECLSPEC_XFGVIRT(ICVIPTools, GetPixel_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetPixel_Image )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long row,
            /* [in] */ long col,
            /* [retval][out] */ VARIANT *pixel);
        
        DECLSPEC_XFGVIRT(ICVIPTools, giftocvip)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *giftocvip )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ long *unused,
            /* [in] */ long image_number,
            /* [in] */ long verbose);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Glr_Compress)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Glr_Compress )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ long *image,
            /* [in] */ long window_size);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Glr_Decompress)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Glr_Decompress )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Gray_Binary)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Gray_Binary )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ int direction,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Gray_Linear)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Gray_Linear )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ double start,
            /* [in] */ double end,
            /* [in] */ double new_start,
            /* [in] */ double slope,
            /* [in] */ int oor_handling,
            /* [in] */ int band,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Gray_Multiplication)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Gray_Multiplication )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ float ratio,
            /* [in] */ long byte_clipping,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Gray_Multiply)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Gray_Multiply )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ float ratio,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Gray_Multiply2)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Gray_Multiply2 )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ float ratio,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Gray_Quant_Segment)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Gray_Quant_Segment )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long gray_levels,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Graylevel_Quant)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Graylevel_Quant )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long gray_levels,
            /* [in] */ long choice,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Graylevel_Remap)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Graylevel_Remap )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long r_selection,
            /* [in] */ long g_selection,
            /* [in] */ long b_selection,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, GVFSnake_Segment)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GVFSnake_Segment )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long *coordinates,
            /* [in] */ long iterations,
            /* [in] */ double alpha,
            /* [in] */ double beta,
            /* [in] */ double kappa,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, H_image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *H_image )( 
            ICVIPTools * This,
            /* [in] */ long mask_type,
            /* [in] */ long height,
            /* [in] */ long width,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Haar_Transform)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Haar_Transform )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long direction,
            /* [in] */ long blocksize,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Harmonic_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Harmonic_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Harris_Corner_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Harris_Corner_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ float alpha,
            /* [in] */ long threshold,
            /* [in] */ long border,
            /* [in] */ float dmin,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, High_Freq_Emphasis)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *High_Freq_Emphasis )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long blocksize,
            /* [in] */ long keepdc,
            /* [in] */ long cutoff,
            /* [in] */ double alpha,
            /* [in] */ long filter_order,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Highboost)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Highboost )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [in] */ long center_value,
            /* [in] */ long add2original,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, HighFreq_Emphasis)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *HighFreq_Emphasis )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long xform,
            /* [in] */ long cutoff,
            /* [in] */ long filter_order,
            /* [in] */ double offset,
            /* [in] */ long keepdc,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Highpass_Spatial)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Highpass_Spatial )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long add2original,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Hist_Feature)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Hist_Feature )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long *labeled_image,
            /* [in] */ long row,
            /* [in] */ long col,
            /* [retval][out] */ VARIANT *features);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Hist_Slide)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Hist_Slide )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ int slide,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Hist_Spec)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Hist_Spec )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ BSTR *r_histogram,
            /* [in] */ BSTR *g_histogram,
            /* [in] */ BSTR *b_histogram,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Hist_Stretch)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Hist_Stretch )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ int low_limit,
            /* [in] */ int high_limit,
            /* [in] */ float low_clip,
            /* [in] */ float high_clip,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Hist_Thresh_Gray)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Hist_Thresh_Gray )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ float tore,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Hist_Thresh_Segment)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Hist_Thresh_Segment )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ float tore,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Histeq)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Histeq )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ int band,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Histogram_Spec)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Histogram_Spec )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ double *histogram,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, History_Add)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *History_Add )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long *history);
        
        DECLSPEC_XFGVIRT(ICVIPTools, History_Check)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *History_Check )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ int program,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, History_Copy)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *History_Copy )( 
            ICVIPTools * This,
            /* [in] */ long *source,
            /* [in] */ long *destination);
        
        DECLSPEC_XFGVIRT(ICVIPTools, history_create)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *history_create )( 
            ICVIPTools * This,
            /* [in] */ long prog,
            /* [in] */ long type,
            /* [in] */ float value,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, history_create2)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *history_create2 )( 
            ICVIPTools * This,
            /* [in] */ long prog,
            /* [in] */ long type,
            /* [in] */ int value1,
            /* [in] */ int value2,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, History_Delete_Program)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *History_Delete_Program )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ int program,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, History_Get)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *History_Get )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ int program,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, History_get_data)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *History_get_data )( 
            ICVIPTools * This,
            /* [in] */ long *history,
            /* [in] */ int program,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, History_get_data2)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *History_get_data2 )( 
            ICVIPTools * This,
            /* [in] */ long *history,
            /* [in] */ int program,
            /* [in] */ int index,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Homomorphic)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Homomorphic )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ double upper_limit,
            /* [in] */ double lower_limit,
            /* [in] */ long cutoff,
            /* [in] */ long add2original,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Horizontal_Flip)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Horizontal_Flip )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Hough_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Hough_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ BSTR *image_name,
            /* [in] */ BSTR *angles_of_interest,
            /* [in] */ long threshold,
            /* [in] */ long connection_distance,
            /* [in] */ long interactive,
            /* [in] */ long delta_length,
            /* [in] */ long segment_length,
            /* [in] */ long intermediate_result,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Huf_Compress)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Huf_Compress )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ long *image);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Huf_Decompress)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Huf_Decompress )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Idct_Transform)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Idct_Transform )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long blocksize,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Ideal_Band_Pass)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Ideal_Band_Pass )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long blocksize,
            /* [in] */ long keepdc,
            /* [in] */ long inner_cutoff,
            /* [in] */ long outer_cutoff,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Ideal_Band_Reject)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Ideal_Band_Reject )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long blocksize,
            /* [in] */ long keepdc,
            /* [in] */ long inner_cutoff,
            /* [in] */ long outer_cutoff,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Ideal_High)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Ideal_High )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long blocksize,
            /* [in] */ long keepdc,
            /* [in] */ long cutoff,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Ideal_Low)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Ideal_Low )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long blocksize,
            /* [in] */ long keepdc,
            /* [in] */ long cutoff,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Ifft_Transform)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Ifft_Transform )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long blocksize,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Igs_Segment)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Igs_Segment )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long gray_levels,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Improved_Mmse_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Improved_Mmse_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ float threshold,
            /* [in] */ long kernel_size,
            /* [in] */ float noise_variance,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Input_Mesh)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Input_Mesh )( 
            ICVIPTools * This,
            /* [in] */ long *points,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Intensity_Slicing)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Intensity_Slicing )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long *lookup_table,
            /* [in] */ long options,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Inverse_Xformfilter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Inverse_Xformfilter )( 
            ICVIPTools * This,
            /* [in] */ long *degr_image,
            /* [in] */ long *degr_fn,
            /* [in] */ long max_gain,
            /* [in] */ double cutoff,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Ipct)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Ipct )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long ignore_background,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Irregular)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Irregular )( 
            ICVIPTools * This,
            /* [in] */ long *labeled_image,
            /* [in] */ int row,
            /* [in] */ int col,
            /* [retval][out] */ double *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Jp2_Decoder)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Jp2_Decoder )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Jp2_Encoder)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Jp2_Encoder )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ long *image,
            /* [in] */ int rate,
            /* [in] */ int quality,
            /* [in] */ int layers,
            /* [in] */ int blocksize);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Jpg_Compress)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Jpg_Compress )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ long *image,
            /* [in] */ int quality,
            /* [in] */ long grayscale,
            /* [in] */ long optimize,
            /* [in] */ int smooth,
            /* [in] */ long verbose,
            /* [in] */ BSTR *qtablesFile);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Jpg_Decompress)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Jpg_Decompress )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ int num_colors,
            /* [in] */ long blocksmooth,
            /* [in] */ long grayscale,
            /* [in] */ long nodither,
            /* [in] */ long verbose,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Jpgtocvip)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Jpgtocvip )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ int num_colors,
            /* [in] */ long blocksmooth,
            /* [in] */ long grayscale,
            /* [in] */ long nodither,
            /* [in] */ long verbose,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, K_Nearest_Neighbor)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *K_Nearest_Neighbor )( 
            ICVIPTools * This,
            /* [in] */ BSTR *test_set,
            /* [in] */ BSTR *training_set,
            /* [in] */ BSTR *outputfile,
            /* [in] */ int normalization,
            /* [in] */ int distance_measure,
            /* [in] */ int k,
            /* [in] */ float s_min,
            /* [in] */ float s_max,
            /* [in] */ float r_softmax,
            /* [in] */ float r_minkowski,
            /* [retval][out] */ long *error);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Krisch_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Krisch_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long *dir_image,
            /* [in] */ long filter_type,
            /* [in] */ long kernel_size,
            /* [in] */ long keepdc,
            /* [in] */ long threshold,
            /* [retval][out] */ long *mag_image);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Kuwahara_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Kuwahara_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Label)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Label )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Laws_Texture_Feature)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Laws_Texture_Feature )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long *labeled_image,
            /* [in] */ int row,
            /* [in] */ int col,
            /* [in] */ int window_size,
            /* [in] */ int vector1,
            /* [in] */ int vector2,
            /* [retval][out] */ VARIANT *features);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Least_Squares)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Least_Squares )( 
            ICVIPTools * This,
            /* [in] */ long *degr_image,
            /* [in] */ long *degr_fn,
            /* [in] */ long *smoothness_fn,
            /* [in] */ double gamma,
            /* [in] */ long max_gain,
            /* [in] */ long cutoff,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Local_Adaptive_Zoom)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Local_Adaptive_Zoom )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Local_Histeq)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Local_Histeq )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ int blocksize,
            /* [in] */ int band,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Log_Ace_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Log_Ace_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [in] */ double local_mean,
            /* [in] */ double local_gain,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Log_Remap)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Log_Remap )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long band,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, LogMap_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LogMap_Image )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ int band,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Lum_Average)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Lum_Average )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Luminance_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Luminance_Image )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Make_Histogram)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Make_Histogram )( 
            ICVIPTools * This,
            /* [in] */ double *histogram,
            /* [in] */ long image_format,
            /* [in] */ long color_format,
            /* [in] */ long bands,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Marr_Hildreth_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Marr_Hildreth_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ float sigma,
            /* [in] */ int threshold,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Maximum_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Maximum_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Mean_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Mean_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Median_Cut_Segment)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Median_Cut_Segment )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long num_colors,
            /* [in] */ long ignore_background,
            /* [in] */ long r_background,
            /* [in] */ long g_background,
            /* [in] */ long b_background,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Median_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Median_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Mesh_To_File)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Mesh_To_File )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ long *mesh);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Mesh_Warping)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Mesh_Warping )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long *mesh,
            /* [in] */ long interpolation_method,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Mesh_WarpingRI)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Mesh_WarpingRI )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long *mesh,
            /* [in] */ long interpolation_method,
            /* [in] */ long zero_missing,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Midpoint_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Midpoint_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Minimum_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Minimum_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Mmse_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Mmse_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ double noise_variance,
            /* [in] */ long kernel_size,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Moravec_Corner_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Moravec_Corner_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ float threshold,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Morph_Hitmiss)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Morph_Hitmiss )( 
            ICVIPTools * This,
            /* [in] */ long *binary_image,
            /* [in] */ long masksize,
            /* [in] */ double *mask_values,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Morph_Skeleton)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Morph_Skeleton )( 
            ICVIPTools * This,
            /* [in] */ long *binary_image,
            /* [in] */ long masksize,
            /* [in] */ double *mask_values,
            /* [in] */ long iterations,
            /* [in] */ long four_eight_mask,
            /* [in] */ long method,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Morph_Thinning)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Morph_Thinning )( 
            ICVIPTools * This,
            /* [in] */ long *binary_image,
            /* [in] */ long masksize,
            /* [in] */ double *mask_values,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, MorphClose)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MorphClose )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ int kernel_type,
            /* [in] */ int kernel_size,
            /* [in] */ int height,
            /* [in] */ int width,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, MorphClose_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MorphClose_Image )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long *matrix,
            /* [in] */ int userOrg,
            /* [in] */ int x,
            /* [in] */ int y,
            /* [in] */ int size,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, MorphDilate)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MorphDilate )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ int kernel_type,
            /* [in] */ int kernel_size,
            /* [in] */ int height,
            /* [in] */ int width,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, MorphDilate_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MorphDilate_Image )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ int *matrix,
            /* [in] */ int userOrg,
            /* [in] */ int x,
            /* [in] */ int y,
            /* [in] */ int size,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, MorphErode)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MorphErode )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ int kernel_type,
            /* [in] */ int kernel_size,
            /* [in] */ int height,
            /* [in] */ int width,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, MorphErode_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MorphErode_Image )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long *matrix,
            /* [in] */ int userOrg,
            /* [in] */ int x,
            /* [in] */ int y,
            /* [in] */ int size,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Morpho)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Morpho )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ BSTR *surrounds_string,
            /* [in] */ long rotation,
            /* [in] */ long boolfunc,
            /* [in] */ long connectedness,
            /* [in] */ long iterations,
            /* [in] */ long fields,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Morpho_com)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Morpho_com )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ BSTR *surrounds_string,
            /* [in] */ long rotation,
            /* [in] */ long boolfunc,
            /* [in] */ long iterations,
            /* [in] */ long subfields,
            /* [in] */ long unused,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, MorphOpen)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MorphOpen )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ int kernel_type,
            /* [in] */ int kernel_size,
            /* [in] */ int height,
            /* [in] */ int width,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, MorphOpen_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *MorphOpen_Image )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long *matrix,
            /* [in] */ int userOrg,
            /* [in] */ int x,
            /* [in] */ int y,
            /* [in] */ int size,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Multi_Resolution_Segment)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Multi_Resolution_Segment )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long homogeneity_test,
            /* [in] */ double param1,
            /* [in] */ double param2,
            /* [in] */ long run_PCT,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Multiply_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Multiply_Image )( 
            ICVIPTools * This,
            /* [in] */ long *image1,
            /* [in] */ long *image2,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Nearest_Centroid)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Nearest_Centroid )( 
            ICVIPTools * This,
            /* [in] */ BSTR *test_set,
            /* [in] */ BSTR *training_set,
            /* [in] */ BSTR *outputfile,
            /* [in] */ int normalization,
            /* [in] */ int distance_measure,
            /* [in] */ float s_min,
            /* [in] */ float s_max,
            /* [in] */ float r_softmax,
            /* [in] */ float r_minkowski,
            /* [retval][out] */ long *error);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Nearest_Neighbor)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Nearest_Neighbor )( 
            ICVIPTools * This,
            /* [in] */ BSTR *test_set,
            /* [in] */ BSTR *training_set,
            /* [in] */ BSTR *outputfile,
            /* [in] */ int normalization,
            /* [in] */ int distance_measure,
            /* [in] */ float s_min,
            /* [in] */ float s_max,
            /* [in] */ float r_softmax,
            /* [in] */ float r_minkowski,
            /* [retval][out] */ long *error);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Neg_Exp_Noise)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Neg_Exp_Noise )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ double variance,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, New_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *New_Image )( 
            ICVIPTools * This,
            /* [in] */ long image_format,
            /* [in] */ long color_space,
            /* [in] */ int bands,
            /* [in] */ int height,
            /* [in] */ int width,
            /* [in] */ long datatype,
            /* [in] */ long data_format,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Nonfft_Xformfilter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Nonfft_Xformfilter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long blocksize,
            /* [in] */ long keepdc,
            /* [in] */ long filter_type,
            /* [in] */ long p1,
            /* [in] */ double p2,
            /* [in] */ long filter_order,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Not_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Not_Image )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Notch)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Notch )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ long *cols,
            /* [in] */ long *rows,
            /* [in] */ long *radius,
            /* [in] */ long *image,
            /* [in] */ long num_points,
            /* [in] */ long interactive,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Object_Crop)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Object_Crop )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long *coordinates,
            /* [in] */ long format,
            /* [in] */ long r_value,
            /* [in] */ long g_value,
            /* [in] */ long b_value,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Open_Consol_Redirect_Output)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Open_Consol_Redirect_Output )( 
            ICVIPTools * This);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Or_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Or_Image )( 
            ICVIPTools * This,
            /* [in] */ long *image1,
            /* [in] */ long *image2,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Orientation)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Orientation )( 
            ICVIPTools * This,
            /* [in] */ long *labeled_image,
            /* [in] */ int row,
            /* [in] */ int col,
            /* [retval][out] */ long *orientation);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Otsu_Segment)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Otsu_Segment )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Param_AD_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Param_AD_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long iterations,
            /* [in] */ long speed,
            /* [in] */ long edge_height,
            /* [in] */ long blocksize,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Parametric_Wiener)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Parametric_Wiener )( 
            ICVIPTools * This,
            /* [in] */ long *degr_image,
            /* [in] */ long *degr_fn,
            /* [in] */ long *psd_noise,
            /* [in] */ long *psd_orig,
            /* [in] */ double gamma,
            /* [in] */ long max_gain,
            /* [in] */ long cutoff,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Pct)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Pct )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long ignore_background,
            /* [in] */ double *background,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Pct_Color)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Pct_Color )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long ignore_background,
            /* [in] */ double *background,
            /* [in] */ long choice,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Pct_Median_Segment)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Pct_Median_Segment )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long num_colors,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Perimeter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Perimeter )( 
            ICVIPTools * This,
            /* [in] */ long *labeled_image,
            /* [in] */ int row,
            /* [in] */ int col,
            /* [retval][out] */ long *perimeter);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Pngtocvip)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Pngtocvip )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Power_Spect_Eq)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Power_Spect_Eq )( 
            ICVIPTools * This,
            /* [in] */ long *degr_image,
            /* [in] */ long *degr_fn,
            /* [in] */ long *psd_noise,
            /* [in] */ long *psd_orig,
            /* [in] */ long max_gain,
            /* [in] */ long cutoff,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Pratt_Merit)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Pratt_Merit )( 
            ICVIPTools * This,
            /* [in] */ long *image1,
            /* [in] */ long *image2,
            /* [in] */ double scale_factor,
            /* [retval][out] */ double *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Prewitt_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Prewitt_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long *dir_image,
            /* [in] */ long filter_type,
            /* [in] */ long kernel_size,
            /* [in] */ long keepdc,
            /* [in] */ long threshold,
            /* [retval][out] */ long *mag_image);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Print_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Print_Image )( 
            ICVIPTools * This,
            /* [in] */ int dc,
            /* [in] */ long *image);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Projection)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Projection )( 
            ICVIPTools * This,
            /* [in] */ long *labeled_image,
            /* [in] */ int row,
            /* [in] */ int col,
            /* [in] */ int height,
            /* [in] */ int width,
            /* [retval][out] */ VARIANT *projections);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Pseudo_Remap)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Pseudo_Remap )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long *lookup_table,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Pseudocol_Freq)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Pseudocol_Freq )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ int low_cutoff,
            /* [in] */ int high_cutoff,
            /* [in] */ int lowpass_band,
            /* [in] */ int bandpass_band,
            /* [in] */ int highpass_band,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Raster_Deblur_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Raster_Deblur_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Rayleigh_Noise)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Rayleigh_Noise )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ double variance,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Read_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Read_Image )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Remap_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Remap_Image )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long datatype,
            /* [in] */ long dmin,
            /* [in] */ long dmax,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, REMAPP)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *REMAPP )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long datatype,
            /* [in] */ long dmin,
            /* [in] */ long dmax,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Render_DisplayImage)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Render_DisplayImage )( 
            ICVIPTools * This,
            /* [in] */ long window_dc,
            /* [in] */ long *image,
            /* [retval][out] */ long *memory_dc);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Rms_Error)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Rms_Error )( 
            ICVIPTools * This,
            /* [in] */ long *image1,
            /* [in] */ long *image2,
            /* [retval][out] */ VARIANT *rms_values);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Robinson_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Robinson_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long *dir_image,
            /* [in] */ long mask_type,
            /* [in] */ long masksize,
            /* [in] */ long keepdc,
            /* [in] */ long threshold,
            /* [retval][out] */ long *mag_image);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Rotate)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Rotate )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ float degrees,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Rst_invariant)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Rst_invariant )( 
            ICVIPTools * This,
            /* [in] */ long *labeled_image,
            /* [in] */ long row,
            /* [in] */ long col,
            /* [retval][out] */ VARIANT *features);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Save_Compressed_Data)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Save_Compressed_Data )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ BSTR *filename);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Sct_Split_Segment)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Sct_Split_Segment )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long A_split,
            /* [in] */ long B_split,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Set_Console)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Set_Console )( 
            ICVIPTools * This,
            /* [in] */ long unused);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Sharpen_I)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Sharpen_I )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long remap,
            /* [in] */ long mask_type,
            /* [in] */ long masksize,
            /* [in] */ float low_clip,
            /* [in] */ float high_clip,
            /* [in] */ long add2original,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Sharpen_II)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Sharpen_II )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long add2original,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Sharpen_III)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Sharpen_III )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long add2original,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Shen_Castan_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Shen_Castan_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ double smoothing_factor,
            /* [in] */ long window_size,
            /* [in] */ double low_threshold,
            /* [in] */ double high_threshold,
            /* [in] */ long thin_factor,
            /* [in] */ long *intermediate_image,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Show_DisplayImage)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Show_DisplayImage )( 
            ICVIPTools * This,
            /* [in] */ long window_dc,
            /* [in] */ long memory_dc,
            /* [in] */ long window_width,
            /* [in] */ long window_height,
            /* [in] */ long memory_width,
            /* [in] */ long memory_height);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Show_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Show_Image )( 
            ICVIPTools * This,
            /* [in] */ int dc,
            /* [in] */ int x,
            /* [in] */ int y,
            /* [in] */ long *image);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Show_Image_Ex)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Show_Image_Ex )( 
            ICVIPTools * This,
            /* [in] */ int window_dc,
            /* [in] */ long *memory_dc,
            /* [in] */ int x,
            /* [in] */ int y,
            /* [in] */ long *image);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Shrink)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Shrink )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ float factor,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Simple_Wiener)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Simple_Wiener )( 
            ICVIPTools * This,
            /* [in] */ long *degr_image,
            /* [in] */ long *degr_fn,
            /* [in] */ double k,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Single_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Single_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ double sizing_factor_x,
            /* [in] */ double sizing_factor_y,
            /* [in] */ long centerx,
            /* [in] */ long centery,
            /* [in] */ double rotation,
            /* [in] */ double beta,
            /* [in] */ long kernel_size,
            /* [in] */ double *kernel_data,
            /* [in] */ long choice,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Snr)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Snr )( 
            ICVIPTools * This,
            /* [in] */ long *image1,
            /* [in] */ long *image2,
            /* [retval][out] */ VARIANT *snr_values);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Sobel_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Sobel_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long *dir_image,
            /* [in] */ long filter_type,
            /* [in] */ long kernel_size,
            /* [in] */ long keepdc,
            /* [in] */ long threshold,
            /* [retval][out] */ long *mag_image);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Spatial_Quant)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Spatial_Quant )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ int rows,
            /* [in] */ int cols,
            /* [in] */ int method,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Spec_Hist_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Spec_Hist_Image )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ BSTR *r_histogram,
            /* [in] */ BSTR *g_histogram,
            /* [in] */ BSTR *b_histogram,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Specify_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Specify_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long mask_height,
            /* [in] */ long mask_width,
            /* [in] */ double *mask_values,
            /* [in] */ int normalization,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Speckle_Noise)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Speckle_Noise )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ double psalt,
            /* [in] */ double ppepper,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Spectral_Feature)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Spectral_Feature )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long *labeled_image,
            /* [in] */ long rings,
            /* [in] */ long sectors,
            /* [in] */ long row,
            /* [in] */ long col,
            /* [retval][out] */ VARIANT *features);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Split_Merge_Segment)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Split_Merge_Segment )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long level,
            /* [in] */ long homogeneity_test,
            /* [in] */ double param1,
            /* [in] */ double param2,
            /* [in] */ long run_PCT,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Subtract_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Subtract_Image )( 
            ICVIPTools * This,
            /* [in] */ long *image1,
            /* [in] */ long *image2,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, TextureFeature)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *TextureFeature )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long *labeled_image,
            /* [in] */ long row,
            /* [in] */ long col,
            /* [in] */ long distance,
            /* [in] */ long bitmask,
            /* [retval][out] */ VARIANT *features);
        
        DECLSPEC_XFGVIRT(ICVIPTools, TextureFeature2)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *TextureFeature2 )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long *labeled_image,
            /* [in] */ long band,
            /* [in] */ long row,
            /* [in] */ long col,
            /* [in] */ long distance,
            /* [in] */ long energy,
            /* [in] */ long inertia,
            /* [in] */ long correlation,
            /* [in] */ long inv_diff,
            /* [in] */ long entropy,
            /* [in] */ long include_zero_pairs,
            /* [retval][out] */ VARIANT *features);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Thinness)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Thinness )( 
            ICVIPTools * This,
            /* [in] */ long *labeled_image,
            /* [in] */ int row,
            /* [in] */ int col,
            /* [retval][out] */ double *thinness);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Threshold_Segment)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Threshold_Segment )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long threshold,
            /* [in] */ long byte_remap,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Tifftocvip)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Tifftocvip )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ int verbose,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Tile_by_name)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Tile_by_name )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Transform_Compression)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Transform_Compression )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ BSTR *filename,
            /* [in] */ BSTR *quantfile,
            /* [in] */ long color_space,
            /* [in] */ long xform,
            /* [in] */ long basis,
            /* [in] */ long blocksize,
            /* [in] */ long quantization,
            /* [in] */ long use_quant_table,
            /* [in] */ long use_vector_quant,
            /* [in] */ long datatype,
            /* [in] */ long remap_type,
            /* [in] */ long keepdc,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Transform_Sharpen)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Transform_Sharpen )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long xform,
            /* [in] */ long cutoff,
            /* [in] */ long filter_type,
            /* [in] */ long filter_order,
            /* [in] */ long keepdc,
            /* [in] */ long add2original,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Transform_Smoothing)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Transform_Smoothing )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long xform,
            /* [in] */ long cutoff,
            /* [in] */ long filter_type,
            /* [in] */ long filter_order,
            /* [in] */ long keepdc,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Translate)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Translate )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long wrap,
            /* [in] */ int row_offset,
            /* [in] */ int col_offset,
            /* [in] */ int rows,
            /* [in] */ int cols,
            /* [in] */ int row_slide,
            /* [in] */ int col_slide,
            /* [in] */ float fill_val,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Uniform_Noise)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Uniform_Noise )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ double variance,
            /* [in] */ double mean,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Unsharp_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Unsharp_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long lower_limit,
            /* [in] */ long upper_limit,
            /* [in] */ double low_clip,
            /* [in] */ double high_clip,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Vertical_Flip)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Vertical_Flip )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Vq_Compress)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Vq_Compress )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ BSTR *filename,
            /* [in] */ long use_file_codebook,
            /* [in] */ long use_fixed_codebook,
            /* [in] */ double error_threshold,
            /* [in] */ BSTR *codebook_filename,
            /* [in] */ long num_entries,
            /* [in] */ long vector_height,
            /* [in] */ long vector_width,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Vq_Decompress)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Vq_Decompress )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Walhad_Transform)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Walhad_Transform )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long xform,
            /* [in] */ long blocksize,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Watershed_Segment)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Watershed_Segment )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ int merge_result,
            /* [in] */ float threshold,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Wavdaub4_Transform)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Wavdaub4_Transform )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long direction,
            /* [in] */ long low_band,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Wavhaar_Transform)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Wavhaar_Transform )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long direction,
            /* [in] */ long low_band,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Wiener)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Wiener )( 
            ICVIPTools * This,
            /* [in] */ long *degr_image,
            /* [in] */ long *degr_fn,
            /* [in] */ long *psd_noise,
            /* [in] */ long *psd_orig,
            /* [in] */ long max_gain,
            /* [in] */ long cutoff,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Write_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Write_Image )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ BSTR *filename,
            /* [in] */ long retain_image,
            /* [in] */ long run_setup,
            /* [in] */ long image_format,
            /* [in] */ long verbose);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Write_JPEG_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Write_JPEG_Image )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ BSTR *filename,
            /* [in] */ long retain_image,
            /* [in] */ long run_setup,
            /* [in] */ long image_format,
            /* [in] */ long verbose,
            /* [in] */ int ratio);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Xor_Error)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Xor_Error )( 
            ICVIPTools * This,
            /* [in] */ long *image1,
            /* [in] */ long *image2,
            /* [retval][out] */ VARIANT *error_values);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Xor_Image)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Xor_Image )( 
            ICVIPTools * This,
            /* [in] */ long *image1,
            /* [in] */ long *image2,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Xvq_Compress)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Xvq_Compress )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long xform,
            /* [in] */ long scheme,
            /* [in] */ BSTR *filename,
            /* [in] */ long output_data_type,
            /* [in] */ long remap_type,
            /* [in] */ long dc_term_handling,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Xvq_Decompress)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Xvq_Decompress )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Ypmean_Filter)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Ypmean_Filter )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ long masksize,
            /* [in] */ long p,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Zon_Compress)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Zon_Compress )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ long *image,
            /* [in] */ int blocksize,
            /* [in] */ int xform,
            /* [in] */ int mask_type,
            /* [in] */ float compression_ratio);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Zon_Decompress)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Zon_Decompress )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Zon2_Compress)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Zon2_Compress )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ long *image,
            /* [in] */ int blocksize,
            /* [in] */ int xform,
            /* [in] */ int mask_type,
            /* [in] */ float compression_ratio);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Zon2_Decompress)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Zon2_Decompress )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Zoom)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Zoom )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ int quadrant,
            /* [in] */ int col,
            /* [in] */ int row,
            /* [in] */ int cols,
            /* [in] */ int rows,
            /* [in] */ float factor_requested,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Zvl_Compress)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Zvl_Compress )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [in] */ long *image);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Zvl_Decompress)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Zvl_Decompress )( 
            ICVIPTools * This,
            /* [in] */ BSTR *filename,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Dice_Coef)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Dice_Coef )( 
            ICVIPTools * This,
            /* [in] */ long *image1,
            /* [in] */ long *image2,
            /* [retval][out] */ VARIANT *error_values);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Jaccard_Index)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Jaccard_Index )( 
            ICVIPTools * This,
            /* [in] */ long *image1,
            /* [in] */ long *image2,
            /* [retval][out] */ VARIANT *error_values);
        
        DECLSPEC_XFGVIRT(ICVIPTools, Overlap_Coef)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Overlap_Coef )( 
            ICVIPTools * This,
            /* [in] */ long *image1,
            /* [in] */ long *image2,
            /* [retval][out] */ VARIANT *error_values);
        
        DECLSPEC_XFGVIRT(ICVIPTools, CLAHE)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CLAHE )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ int blocksize,
            /* [in] */ double clippercent,
            /* [in] */ int band,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, CLAHE_Grid)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CLAHE_Grid )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [in] */ int blocksize,
            /* [in] */ double clippercent,
            /* [in] */ int band,
            /* [retval][out] */ long *result);
        
        DECLSPEC_XFGVIRT(ICVIPTools, superPixel)
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *superPixel )( 
            ICVIPTools * This,
            /* [in] */ long *image,
            /* [retval][out] */ long *result);
        
        END_INTERFACE
    } ICVIPToolsVtbl;

    interface ICVIPTools
    {
        CONST_VTBL struct ICVIPToolsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICVIPTools_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICVIPTools_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICVIPTools_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICVIPTools_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICVIPTools_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICVIPTools_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICVIPTools_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ICVIPTools_Ace2_Filter(This,image,masksize,local_mean,local_gain,result)	\
    ( (This)->lpVtbl -> Ace2_Filter(This,image,masksize,local_mean,local_gain,result) ) 

#define ICVIPTools_Acuity_Nightvision_Filter(This,image,reason,threshold,acuity,result)	\
    ( (This)->lpVtbl -> Acuity_Nightvision_Filter(This,image,reason,threshold,acuity,result) ) 

#define ICVIPTools_AD_Filter(This,image,iterations,speed,edge_height,result)	\
    ( (This)->lpVtbl -> AD_Filter(This,image,iterations,speed,edge_height,result) ) 

#define ICVIPTools_Adapt_Median_Filter(This,image,masksize,result)	\
    ( (This)->lpVtbl -> Adapt_Median_Filter(This,image,masksize,result) ) 

#define ICVIPTools_Adaptive_Contrast_Filter(This,image,k1,k2,kernel_size,min_gain,max_gain,result)	\
    ( (This)->lpVtbl -> Adaptive_Contrast_Filter(This,image,k1,k2,kernel_size,min_gain,max_gain,result) ) 

#define ICVIPTools_Add_Image(This,image1,image2,result)	\
    ( (This)->lpVtbl -> Add_Image(This,image1,image2,result) ) 

#define ICVIPTools_Alpha_Filter(This,image,masksize,p,result)	\
    ( (This)->lpVtbl -> Alpha_Filter(This,image,masksize,p,result) ) 

#define ICVIPTools_And_Image(This,image1,image2,result)	\
    ( (This)->lpVtbl -> And_Image(This,image1,image2,result) ) 

#define ICVIPTools_Area(This,labeled_image,row,col,area)	\
    ( (This)->lpVtbl -> Area(This,labeled_image,row,col,area) ) 

#define ICVIPTools_Aspect(This,labeled_image,row,col,aspect)	\
    ( (This)->lpVtbl -> Aspect(This,labeled_image,row,col,aspect) ) 

#define ICVIPTools_Assemble_Bands(This,bands,result)	\
    ( (This)->lpVtbl -> Assemble_Bands(This,bands,result) ) 

#define ICVIPTools_Auto_Threshold_Segment(This,image,limit,result)	\
    ( (This)->lpVtbl -> Auto_Threshold_Segment(This,image,limit,result) ) 

#define ICVIPTools_Bilinear_Interp(This,image,factor,result)	\
    ( (This)->lpVtbl -> Bilinear_Interp(This,image,factor,result) ) 

#define ICVIPTools_Bilinear_Interp1(This,image,xfactor,yfactor,result)	\
    ( (This)->lpVtbl -> Bilinear_Interp1(This,image,xfactor,yfactor,result) ) 

#define ICVIPTools_Bintocvip(This,filename,bands,color_order,interleaved,height,width,verbose,cvip_image)	\
    ( (This)->lpVtbl -> Bintocvip(This,filename,bands,color_order,interleaved,height,width,verbose,cvip_image) ) 

#define ICVIPTools_Bit_Compress(This,filename,image,bitmask)	\
    ( (This)->lpVtbl -> Bit_Compress(This,filename,image,bitmask) ) 

#define ICVIPTools_Bit_Decompress(This,filename,result)	\
    ( (This)->lpVtbl -> Bit_Decompress(This,filename,result) ) 

#define ICVIPTools_Boiecox_Filter(This,image,variance,do_threshold,do_hyst,do_thin,high_threshold,low_threshold,threshhold_image,hyst_image,result)	\
    ( (This)->lpVtbl -> Boiecox_Filter(This,image,variance,do_threshold,do_hyst,do_thin,high_threshold,low_threshold,threshhold_image,hyst_image,result) ) 

#define ICVIPTools_Btc_Compress(This,filename,image,blocksize)	\
    ( (This)->lpVtbl -> Btc_Compress(This,filename,image,blocksize) ) 

#define ICVIPTools_Btc_Decompression(This,filename,result)	\
    ( (This)->lpVtbl -> Btc_Decompression(This,filename,result) ) 

#define ICVIPTools_Btc2_Compress(This,filename,image,blocksize)	\
    ( (This)->lpVtbl -> Btc2_Compress(This,filename,image,blocksize) ) 

#define ICVIPTools_Btc2_Decompress(This,filename,result)	\
    ( (This)->lpVtbl -> Btc2_Decompress(This,filename,result) ) 

#define ICVIPTools_Btc3_Compress(This,filename,image,blocksize)	\
    ( (This)->lpVtbl -> Btc3_Compress(This,filename,image,blocksize) ) 

#define ICVIPTools_Btc3_Decompress(This,filename,result)	\
    ( (This)->lpVtbl -> Btc3_Decompress(This,filename,result) ) 

#define ICVIPTools_Butterworth_Band_Pass(This,image,blocksize,keepdc,inner_cutoff,outer_cutoff,filter_order,result)	\
    ( (This)->lpVtbl -> Butterworth_Band_Pass(This,image,blocksize,keepdc,inner_cutoff,outer_cutoff,filter_order,result) ) 

#define ICVIPTools_Butterworth_Band_Reject(This,image,blocksize,keepdc,inner_cutoff,outer_cutoff,filter_order,result)	\
    ( (This)->lpVtbl -> Butterworth_Band_Reject(This,image,blocksize,keepdc,inner_cutoff,outer_cutoff,filter_order,result) ) 

#define ICVIPTools_Butterworth_High(This,image,blocksize,keepdc,cutoff,filter_order,result)	\
    ( (This)->lpVtbl -> Butterworth_High(This,image,blocksize,keepdc,cutoff,filter_order,result) ) 

#define ICVIPTools_Butterworth_Low(This,image,blocksize,keepdc,cutoff,filter_order,result)	\
    ( (This)->lpVtbl -> Butterworth_Low(This,image,blocksize,keepdc,cutoff,filter_order,result) ) 

#define ICVIPTools_Canny_Filter(This,image,low_threshold,high_threshold,variance,mag_image,dir_image,result)	\
    ( (This)->lpVtbl -> Canny_Filter(This,image,low_threshold,high_threshold,variance,mag_image,dir_image,result) ) 

#define ICVIPTools_Cast_Image(This,image,datatype)	\
    ( (This)->lpVtbl -> Cast_Image(This,image,datatype) ) 

#define ICVIPTools_CentroID(This,labeled_image,row,col,centroid)	\
    ( (This)->lpVtbl -> CentroID(This,labeled_image,row,col,centroid) ) 

#define ICVIPTools_Cerchar_Filter(This,image,result)	\
    ( (This)->lpVtbl -> Cerchar_Filter(This,image,result) ) 

#define ICVIPTools_Check_Bin(This,image,is_binary)	\
    ( (This)->lpVtbl -> Check_Bin(This,image,is_binary) ) 

#define ICVIPTools_Check_xform_history(This,image,filter_type,result)	\
    ( (This)->lpVtbl -> Check_xform_history(This,image,filter_type,result) ) 

#define ICVIPTools_Close_Consol(This)	\
    ( (This)->lpVtbl -> Close_Consol(This) ) 

#define ICVIPTools_Close_Console(This)	\
    ( (This)->lpVtbl -> Close_Console(This) ) 

#define ICVIPTools_Color_Contrast_Enhance(This,image,low_limit,high_limit,low_clip,high_clip,result)	\
    ( (This)->lpVtbl -> Color_Contrast_Enhance(This,image,low_limit,high_limit,low_clip,high_clip,result) ) 

#define ICVIPTools_ColorXform(This,image,color_space,norm_vector,white_reference,direction,result)	\
    ( (This)->lpVtbl -> ColorXform(This,image,color_space,norm_vector,white_reference,direction,result) ) 

#define ICVIPTools_CondRemap_Image(This,image,datatype,min,max,result)	\
    ( (This)->lpVtbl -> CondRemap_Image(This,image,datatype,min,max,result) ) 

#define ICVIPTools_Contra_Filter(This,image,masksize,p,result)	\
    ( (This)->lpVtbl -> Contra_Filter(This,image,masksize,p,result) ) 

#define ICVIPTools_Copy_Paste(This,src_image,dest_image,src_row,src_col,height,width,dest_row,dest_col,transparent,result)	\
    ( (This)->lpVtbl -> Copy_Paste(This,src_image,dest_image,src_row,src_col,height,width,dest_row,dest_col,transparent,result) ) 

#define ICVIPTools_Create_Black(This,width,height,result)	\
    ( (This)->lpVtbl -> Create_Black(This,width,height,result) ) 

#define ICVIPTools_Create_Checkboard(This,width,height,start_col,start_row,blockx,blocky,result)	\
    ( (This)->lpVtbl -> Create_Checkboard(This,width,height,start_col,start_row,blockx,blocky,result) ) 

#define ICVIPTools_Create_Circle(This,width,height,centerx,centery,radius,result)	\
    ( (This)->lpVtbl -> Create_Circle(This,width,height,centerx,centery,radius,result) ) 

#define ICVIPTools_Create_Cosine(This,img_size,frequency,direction,result)	\
    ( (This)->lpVtbl -> Create_Cosine(This,img_size,frequency,direction,result) ) 

#define ICVIPTools_Create_Degenerate_Circle(This,width,height,centerx,centery,radius,blur,result)	\
    ( (This)->lpVtbl -> Create_Degenerate_Circle(This,width,height,centerx,centery,radius,blur,result) ) 

#define ICVIPTools_Create_Ellipse(This,width,height,centerx,centery,shape_width,shape_height,result)	\
    ( (This)->lpVtbl -> Create_Ellipse(This,width,height,centerx,centery,shape_width,shape_height,result) ) 

#define ICVIPTools_Create_Line(This,width,height,tlx,tly,brx,bry,result)	\
    ( (This)->lpVtbl -> Create_Line(This,width,height,tlx,tly,brx,bry,result) ) 

#define ICVIPTools_Create_Mask(This,width,height,values,result)	\
    ( (This)->lpVtbl -> Create_Mask(This,width,height,values,result) ) 

#define ICVIPTools_Create_Mesh_Sine(This,rows,cols,result)	\
    ( (This)->lpVtbl -> Create_Mesh_Sine(This,rows,cols,result) ) 

#define ICVIPTools_Create_Rectangle(This,width,height,tlx,tly,shape_width,shape_height,result)	\
    ( (This)->lpVtbl -> Create_Rectangle(This,width,height,tlx,tly,shape_width,shape_height,result) ) 

#define ICVIPTools_Create_Sine(This,img_size,frequency,direction,result)	\
    ( (This)->lpVtbl -> Create_Sine(This,img_size,frequency,direction,result) ) 

#define ICVIPTools_Create_Squarewave(This,img_size,frequency,direction,result)	\
    ( (This)->lpVtbl -> Create_Squarewave(This,img_size,frequency,direction,result) ) 

#define ICVIPTools_Crop(This,image,start_row,start_col,rows,cols,result)	\
    ( (This)->lpVtbl -> Crop(This,image,start_row,start_col,rows,cols,result) ) 

#define ICVIPTools_CVIP_OUTPUT(This,message)	\
    ( (This)->lpVtbl -> CVIP_OUTPUT(This,message) ) 

#define ICVIPTools_CVIPhalftone(This,image,halftone_method,maxval,threshold,retain_image,verbose,result)	\
    ( (This)->lpVtbl -> CVIPhalftone(This,image,halftone_method,maxval,threshold,retain_image,verbose,result) ) 

#define ICVIPTools_Cviptoccc(This,filename,maxcolor,verbose,dermvis,cvip_image)	\
    ( (This)->lpVtbl -> Cviptoccc(This,filename,maxcolor,verbose,dermvis,cvip_image) ) 

#define ICVIPTools_Cviptoeps(This,filename,cvip_image,scale_x,scale_y,band,verbose)	\
    ( (This)->lpVtbl -> Cviptoeps(This,filename,cvip_image,scale_x,scale_y,band,verbose) ) 

#define ICVIPTools_Cviptogif(This,filename,cvip_image,interlace,verbose)	\
    ( (This)->lpVtbl -> Cviptogif(This,filename,cvip_image,interlace,verbose) ) 

#define ICVIPTools_Cviptoiris(This,filename,cvip_image,verbose,prt_type)	\
    ( (This)->lpVtbl -> Cviptoiris(This,filename,cvip_image,verbose,prt_type) ) 

#define ICVIPTools_Cviptoitex(This,filename,cvip_image,comment,verbose)	\
    ( (This)->lpVtbl -> Cviptoitex(This,filename,cvip_image,comment,verbose) ) 

#define ICVIPTools_Cviptojpg(This,filename,cvip_image,quality,grayscale,optimize,smooth,verbose,qtablesFile)	\
    ( (This)->lpVtbl -> Cviptojpg(This,filename,cvip_image,quality,grayscale,optimize,smooth,verbose,qtablesFile) ) 

#define ICVIPTools_Cviptopnm(This,filename,cvip_image,verbose)	\
    ( (This)->lpVtbl -> Cviptopnm(This,filename,cvip_image,verbose) ) 

#define ICVIPTools_Cviptoras(This,filename,cvip_image,pr_type,verbose)	\
    ( (This)->lpVtbl -> Cviptoras(This,filename,cvip_image,pr_type,verbose) ) 

#define ICVIPTools_Cviptotiff(This,filename,cvip_image,compression,fillorder,g3options,predictor,rowsperstrip,verbose)	\
    ( (This)->lpVtbl -> Cviptotiff(This,filename,cvip_image,compression,fillorder,g3options,predictor,rowsperstrip,verbose) ) 

#define ICVIPTools_Cviptovip(This,filename,cvip_image,verbose,save_history,is_compressed)	\
    ( (This)->lpVtbl -> Cviptovip(This,filename,cvip_image,verbose,save_history,is_compressed) ) 

#define ICVIPTools_Date_Range(This,image,result)	\
    ( (This)->lpVtbl -> Date_Range(This,image,result) ) 

#define ICVIPTools_Dct_Transform(This,image,blocksize,result)	\
    ( (This)->lpVtbl -> Dct_Transform(This,image,blocksize,result) ) 

#define ICVIPTools_Delete_DisplayImage(This,memory_dc)	\
    ( (This)->lpVtbl -> Delete_DisplayImage(This,memory_dc) ) 

#define ICVIPTools_Delete_Image(This,image)	\
    ( (This)->lpVtbl -> Delete_Image(This,image) ) 

#define ICVIPTools_Divide_Image(This,image1,image2,zero2num,result)	\
    ( (This)->lpVtbl -> Divide_Image(This,image1,image2,zero2num,result) ) 

#define ICVIPTools_Dpc_Compress(This,filename,image,ratio,bit_length,clipping,direction,origin,deviation)	\
    ( (This)->lpVtbl -> Dpc_Compress(This,filename,image,ratio,bit_length,clipping,direction,origin,deviation) ) 

#define ICVIPTools_Dpc_Decompress(This,filename,result)	\
    ( (This)->lpVtbl -> Dpc_Decompress(This,filename,result) ) 

#define ICVIPTools_Draw_mesh(This,image,mesh)	\
    ( (This)->lpVtbl -> Draw_mesh(This,image,mesh) ) 

#define ICVIPTools_Duplicate_Image(This,image,result)	\
    ( (This)->lpVtbl -> Duplicate_Image(This,image,result) ) 

#define ICVIPTools_DynRLC_Compression(This,filename,image,window_size,result)	\
    ( (This)->lpVtbl -> DynRLC_Compression(This,filename,image,window_size,result) ) 

#define ICVIPTools_DynRLC_deCompression(This,filename,result)	\
    ( (This)->lpVtbl -> DynRLC_deCompression(This,filename,result) ) 

#define ICVIPTools_Edge_Detect_Filter(This,image,edge_detector,mask_type,masksize,keepdc,threshold,frei_projection,frei_threshold,frei_angle,result)	\
    ( (This)->lpVtbl -> Edge_Detect_Filter(This,image,edge_detector,mask_type,masksize,keepdc,threshold,frei_projection,frei_threshold,frei_angle,result) ) 

#define ICVIPTools_Edge_Link_Filter(This,binary_image,connection_distance,result)	\
    ( (This)->lpVtbl -> Edge_Link_Filter(This,binary_image,connection_distance,result) ) 

#define ICVIPTools_Enlarge(This,image,rows,cols,result)	\
    ( (This)->lpVtbl -> Enlarge(This,image,rows,cols,result) ) 

#define ICVIPTools_Epstocvip(This,filename,verbose)	\
    ( (This)->lpVtbl -> Epstocvip(This,filename,verbose) ) 

#define ICVIPTools_Euler(This,labeled_image,row,col,euler)	\
    ( (This)->lpVtbl -> Euler(This,labeled_image,row,col,euler) ) 

#define ICVIPTools_Exp_Ace_Filter(This,image,masksize,local_mean,local_gain,result)	\
    ( (This)->lpVtbl -> Exp_Ace_Filter(This,image,masksize,local_mean,local_gain,result) ) 

#define ICVIPTools_Extract_Band(This,image,band,result)	\
    ( (This)->lpVtbl -> Extract_Band(This,image,band,result) ) 

#define ICVIPTools_Fft_Mag(This,image,result)	\
    ( (This)->lpVtbl -> Fft_Mag(This,image,result) ) 

#define ICVIPTools_Fft_Phase(This,image,remap_norm,k,result)	\
    ( (This)->lpVtbl -> Fft_Phase(This,image,remap_norm,k,result) ) 

#define ICVIPTools_Fft_Transform(This,image,blocksize,result)	\
    ( (This)->lpVtbl -> Fft_Transform(This,image,blocksize,result) ) 

#define ICVIPTools_File_To_Mesh(This,filename,result)	\
    ( (This)->lpVtbl -> File_To_Mesh(This,filename,result) ) 

#define ICVIPTools_Fractal_Compression(This,image,filename,tolerance,min_part,max_part,dom_type,dom_step,c1,c2,scalebits,offsetbits,result)	\
    ( (This)->lpVtbl -> Fractal_Compression(This,image,filename,tolerance,min_part,max_part,dom_type,dom_step,c1,c2,scalebits,offsetbits,result) ) 

#define ICVIPTools_Fractal_deCompression(This,filename,result)	\
    ( (This)->lpVtbl -> Fractal_deCompression(This,filename,result) ) 

#define ICVIPTools_Fuzzyc_Segment(This,image,variance,result)	\
    ( (This)->lpVtbl -> Fuzzyc_Segment(This,image,variance,result) ) 

#define ICVIPTools_Gamma_Noise(This,image,variance,alpha,result)	\
    ( (This)->lpVtbl -> Gamma_Noise(This,image,variance,alpha,result) ) 

#define ICVIPTools_Gaussian_Blur_Filter(This,image,kernel_size,result)	\
    ( (This)->lpVtbl -> Gaussian_Blur_Filter(This,image,kernel_size,result) ) 

#define ICVIPTools_Gaussian_Noise(This,image,variance,mean,result)	\
    ( (This)->lpVtbl -> Gaussian_Noise(This,image,variance,mean,result) ) 

#define ICVIPTools_Geometric_Filter(This,image,masksize,result)	\
    ( (This)->lpVtbl -> Geometric_Filter(This,image,masksize,result) ) 

#define ICVIPTools_Geometric_Mean(This,degr_image,degr_fn,psd_noise,psd_orig,gamma,alpha,max_gain,cutoff,result)	\
    ( (This)->lpVtbl -> Geometric_Mean(This,degr_image,degr_fn,psd_noise,psd_orig,gamma,alpha,max_gain,cutoff,result) ) 

#define ICVIPTools_get_hist_real(This,image,result)	\
    ( (This)->lpVtbl -> get_hist_real(This,image,result) ) 

#define ICVIPTools_Get_Histogram_Image(This,image,result)	\
    ( (This)->lpVtbl -> Get_Histogram_Image(This,image,result) ) 

#define ICVIPTools_Get_max_min_value(This,image,min_max)	\
    ( (This)->lpVtbl -> Get_max_min_value(This,image,min_max) ) 

#define ICVIPTools_Get_Mesh_Points(This,mesh,points)	\
    ( (This)->lpVtbl -> Get_Mesh_Points(This,mesh,points) ) 

#define ICVIPTools_GetDataFormat_Image(This,image,format)	\
    ( (This)->lpVtbl -> GetDataFormat_Image(This,image,format) ) 

#define ICVIPTools_GetDataType_Image(This,image,datatype)	\
    ( (This)->lpVtbl -> GetDataType_Image(This,image,datatype) ) 

#define ICVIPTools_GetImageInfo(This,image,info)	\
    ( (This)->lpVtbl -> GetImageInfo(This,image,info) ) 

#define ICVIPTools_Getlast_Hist(This,image,programs,num_programs,hist)	\
    ( (This)->lpVtbl -> Getlast_Hist(This,image,programs,num_programs,hist) ) 

#define ICVIPTools_GetNoOfBands_Image(This,image,bands)	\
    ( (This)->lpVtbl -> GetNoOfBands_Image(This,image,bands) ) 

#define ICVIPTools_GetNoOfCols_Image(This,image,cols)	\
    ( (This)->lpVtbl -> GetNoOfCols_Image(This,image,cols) ) 

#define ICVIPTools_GetNoOfRows_Image(This,image,rows)	\
    ( (This)->lpVtbl -> GetNoOfRows_Image(This,image,rows) ) 

#define ICVIPTools_GetPixel_Image(This,image,row,col,pixel)	\
    ( (This)->lpVtbl -> GetPixel_Image(This,image,row,col,pixel) ) 

#define ICVIPTools_giftocvip(This,filename,unused,image_number,verbose)	\
    ( (This)->lpVtbl -> giftocvip(This,filename,unused,image_number,verbose) ) 

#define ICVIPTools_Glr_Compress(This,filename,image,window_size)	\
    ( (This)->lpVtbl -> Glr_Compress(This,filename,image,window_size) ) 

#define ICVIPTools_Glr_Decompress(This,filename,result)	\
    ( (This)->lpVtbl -> Glr_Decompress(This,filename,result) ) 

#define ICVIPTools_Gray_Binary(This,image,direction,result)	\
    ( (This)->lpVtbl -> Gray_Binary(This,image,direction,result) ) 

#define ICVIPTools_Gray_Linear(This,image,start,end,new_start,slope,oor_handling,band,result)	\
    ( (This)->lpVtbl -> Gray_Linear(This,image,start,end,new_start,slope,oor_handling,band,result) ) 

#define ICVIPTools_Gray_Multiplication(This,image,ratio,byte_clipping,result)	\
    ( (This)->lpVtbl -> Gray_Multiplication(This,image,ratio,byte_clipping,result) ) 

#define ICVIPTools_Gray_Multiply(This,image,ratio,result)	\
    ( (This)->lpVtbl -> Gray_Multiply(This,image,ratio,result) ) 

#define ICVIPTools_Gray_Multiply2(This,image,ratio,result)	\
    ( (This)->lpVtbl -> Gray_Multiply2(This,image,ratio,result) ) 

#define ICVIPTools_Gray_Quant_Segment(This,image,gray_levels,result)	\
    ( (This)->lpVtbl -> Gray_Quant_Segment(This,image,gray_levels,result) ) 

#define ICVIPTools_Graylevel_Quant(This,image,gray_levels,choice,result)	\
    ( (This)->lpVtbl -> Graylevel_Quant(This,image,gray_levels,choice,result) ) 

#define ICVIPTools_Graylevel_Remap(This,image,r_selection,g_selection,b_selection,result)	\
    ( (This)->lpVtbl -> Graylevel_Remap(This,image,r_selection,g_selection,b_selection,result) ) 

#define ICVIPTools_GVFSnake_Segment(This,image,coordinates,iterations,alpha,beta,kappa,result)	\
    ( (This)->lpVtbl -> GVFSnake_Segment(This,image,coordinates,iterations,alpha,beta,kappa,result) ) 

#define ICVIPTools_H_image(This,mask_type,height,width,result)	\
    ( (This)->lpVtbl -> H_image(This,mask_type,height,width,result) ) 

#define ICVIPTools_Haar_Transform(This,image,direction,blocksize,result)	\
    ( (This)->lpVtbl -> Haar_Transform(This,image,direction,blocksize,result) ) 

#define ICVIPTools_Harmonic_Filter(This,image,masksize,result)	\
    ( (This)->lpVtbl -> Harmonic_Filter(This,image,masksize,result) ) 

#define ICVIPTools_Harris_Corner_Filter(This,image,alpha,threshold,border,dmin,result)	\
    ( (This)->lpVtbl -> Harris_Corner_Filter(This,image,alpha,threshold,border,dmin,result) ) 

#define ICVIPTools_High_Freq_Emphasis(This,image,blocksize,keepdc,cutoff,alpha,filter_order,result)	\
    ( (This)->lpVtbl -> High_Freq_Emphasis(This,image,blocksize,keepdc,cutoff,alpha,filter_order,result) ) 

#define ICVIPTools_Highboost(This,image,masksize,center_value,add2original,result)	\
    ( (This)->lpVtbl -> Highboost(This,image,masksize,center_value,add2original,result) ) 

#define ICVIPTools_HighFreq_Emphasis(This,image,xform,cutoff,filter_order,offset,keepdc,result)	\
    ( (This)->lpVtbl -> HighFreq_Emphasis(This,image,xform,cutoff,filter_order,offset,keepdc,result) ) 

#define ICVIPTools_Highpass_Spatial(This,image,add2original,result)	\
    ( (This)->lpVtbl -> Highpass_Spatial(This,image,add2original,result) ) 

#define ICVIPTools_Hist_Feature(This,image,labeled_image,row,col,features)	\
    ( (This)->lpVtbl -> Hist_Feature(This,image,labeled_image,row,col,features) ) 

#define ICVIPTools_Hist_Slide(This,image,slide,result)	\
    ( (This)->lpVtbl -> Hist_Slide(This,image,slide,result) ) 

#define ICVIPTools_Hist_Spec(This,image,r_histogram,g_histogram,b_histogram,result)	\
    ( (This)->lpVtbl -> Hist_Spec(This,image,r_histogram,g_histogram,b_histogram,result) ) 

#define ICVIPTools_Hist_Stretch(This,image,low_limit,high_limit,low_clip,high_clip,result)	\
    ( (This)->lpVtbl -> Hist_Stretch(This,image,low_limit,high_limit,low_clip,high_clip,result) ) 

#define ICVIPTools_Hist_Thresh_Gray(This,image,tore,result)	\
    ( (This)->lpVtbl -> Hist_Thresh_Gray(This,image,tore,result) ) 

#define ICVIPTools_Hist_Thresh_Segment(This,image,tore,result)	\
    ( (This)->lpVtbl -> Hist_Thresh_Segment(This,image,tore,result) ) 

#define ICVIPTools_Histeq(This,image,band,result)	\
    ( (This)->lpVtbl -> Histeq(This,image,band,result) ) 

#define ICVIPTools_Histogram_Spec(This,image,histogram,result)	\
    ( (This)->lpVtbl -> Histogram_Spec(This,image,histogram,result) ) 

#define ICVIPTools_History_Add(This,image,history)	\
    ( (This)->lpVtbl -> History_Add(This,image,history) ) 

#define ICVIPTools_History_Check(This,image,program,result)	\
    ( (This)->lpVtbl -> History_Check(This,image,program,result) ) 

#define ICVIPTools_History_Copy(This,source,destination)	\
    ( (This)->lpVtbl -> History_Copy(This,source,destination) ) 

#define ICVIPTools_history_create(This,prog,type,value,result)	\
    ( (This)->lpVtbl -> history_create(This,prog,type,value,result) ) 

#define ICVIPTools_history_create2(This,prog,type,value1,value2,result)	\
    ( (This)->lpVtbl -> history_create2(This,prog,type,value1,value2,result) ) 

#define ICVIPTools_History_Delete_Program(This,image,program,result)	\
    ( (This)->lpVtbl -> History_Delete_Program(This,image,program,result) ) 

#define ICVIPTools_History_Get(This,image,program,result)	\
    ( (This)->lpVtbl -> History_Get(This,image,program,result) ) 

#define ICVIPTools_History_get_data(This,history,program,result)	\
    ( (This)->lpVtbl -> History_get_data(This,history,program,result) ) 

#define ICVIPTools_History_get_data2(This,history,program,index,result)	\
    ( (This)->lpVtbl -> History_get_data2(This,history,program,index,result) ) 

#define ICVIPTools_Homomorphic(This,image,upper_limit,lower_limit,cutoff,add2original,result)	\
    ( (This)->lpVtbl -> Homomorphic(This,image,upper_limit,lower_limit,cutoff,add2original,result) ) 

#define ICVIPTools_Horizontal_Flip(This,image,result)	\
    ( (This)->lpVtbl -> Horizontal_Flip(This,image,result) ) 

#define ICVIPTools_Hough_Filter(This,image,image_name,angles_of_interest,threshold,connection_distance,interactive,delta_length,segment_length,intermediate_result,result)	\
    ( (This)->lpVtbl -> Hough_Filter(This,image,image_name,angles_of_interest,threshold,connection_distance,interactive,delta_length,segment_length,intermediate_result,result) ) 

#define ICVIPTools_Huf_Compress(This,filename,image)	\
    ( (This)->lpVtbl -> Huf_Compress(This,filename,image) ) 

#define ICVIPTools_Huf_Decompress(This,filename,result)	\
    ( (This)->lpVtbl -> Huf_Decompress(This,filename,result) ) 

#define ICVIPTools_Idct_Transform(This,image,blocksize,result)	\
    ( (This)->lpVtbl -> Idct_Transform(This,image,blocksize,result) ) 

#define ICVIPTools_Ideal_Band_Pass(This,image,blocksize,keepdc,inner_cutoff,outer_cutoff,result)	\
    ( (This)->lpVtbl -> Ideal_Band_Pass(This,image,blocksize,keepdc,inner_cutoff,outer_cutoff,result) ) 

#define ICVIPTools_Ideal_Band_Reject(This,image,blocksize,keepdc,inner_cutoff,outer_cutoff,result)	\
    ( (This)->lpVtbl -> Ideal_Band_Reject(This,image,blocksize,keepdc,inner_cutoff,outer_cutoff,result) ) 

#define ICVIPTools_Ideal_High(This,image,blocksize,keepdc,cutoff,result)	\
    ( (This)->lpVtbl -> Ideal_High(This,image,blocksize,keepdc,cutoff,result) ) 

#define ICVIPTools_Ideal_Low(This,image,blocksize,keepdc,cutoff,result)	\
    ( (This)->lpVtbl -> Ideal_Low(This,image,blocksize,keepdc,cutoff,result) ) 

#define ICVIPTools_Ifft_Transform(This,image,blocksize,result)	\
    ( (This)->lpVtbl -> Ifft_Transform(This,image,blocksize,result) ) 

#define ICVIPTools_Igs_Segment(This,image,gray_levels,result)	\
    ( (This)->lpVtbl -> Igs_Segment(This,image,gray_levels,result) ) 

#define ICVIPTools_Improved_Mmse_Filter(This,image,threshold,kernel_size,noise_variance,result)	\
    ( (This)->lpVtbl -> Improved_Mmse_Filter(This,image,threshold,kernel_size,noise_variance,result) ) 

#define ICVIPTools_Input_Mesh(This,points,result)	\
    ( (This)->lpVtbl -> Input_Mesh(This,points,result) ) 

#define ICVIPTools_Intensity_Slicing(This,image,lookup_table,options,result)	\
    ( (This)->lpVtbl -> Intensity_Slicing(This,image,lookup_table,options,result) ) 

#define ICVIPTools_Inverse_Xformfilter(This,degr_image,degr_fn,max_gain,cutoff,result)	\
    ( (This)->lpVtbl -> Inverse_Xformfilter(This,degr_image,degr_fn,max_gain,cutoff,result) ) 

#define ICVIPTools_Ipct(This,image,ignore_background,result)	\
    ( (This)->lpVtbl -> Ipct(This,image,ignore_background,result) ) 

#define ICVIPTools_Irregular(This,labeled_image,row,col,result)	\
    ( (This)->lpVtbl -> Irregular(This,labeled_image,row,col,result) ) 

#define ICVIPTools_Jp2_Decoder(This,filename,result)	\
    ( (This)->lpVtbl -> Jp2_Decoder(This,filename,result) ) 

#define ICVIPTools_Jp2_Encoder(This,filename,image,rate,quality,layers,blocksize)	\
    ( (This)->lpVtbl -> Jp2_Encoder(This,filename,image,rate,quality,layers,blocksize) ) 

#define ICVIPTools_Jpg_Compress(This,filename,image,quality,grayscale,optimize,smooth,verbose,qtablesFile)	\
    ( (This)->lpVtbl -> Jpg_Compress(This,filename,image,quality,grayscale,optimize,smooth,verbose,qtablesFile) ) 

#define ICVIPTools_Jpg_Decompress(This,filename,num_colors,blocksmooth,grayscale,nodither,verbose,result)	\
    ( (This)->lpVtbl -> Jpg_Decompress(This,filename,num_colors,blocksmooth,grayscale,nodither,verbose,result) ) 

#define ICVIPTools_Jpgtocvip(This,filename,num_colors,blocksmooth,grayscale,nodither,verbose,result)	\
    ( (This)->lpVtbl -> Jpgtocvip(This,filename,num_colors,blocksmooth,grayscale,nodither,verbose,result) ) 

#define ICVIPTools_K_Nearest_Neighbor(This,test_set,training_set,outputfile,normalization,distance_measure,k,s_min,s_max,r_softmax,r_minkowski,error)	\
    ( (This)->lpVtbl -> K_Nearest_Neighbor(This,test_set,training_set,outputfile,normalization,distance_measure,k,s_min,s_max,r_softmax,r_minkowski,error) ) 

#define ICVIPTools_Krisch_Filter(This,image,dir_image,filter_type,kernel_size,keepdc,threshold,mag_image)	\
    ( (This)->lpVtbl -> Krisch_Filter(This,image,dir_image,filter_type,kernel_size,keepdc,threshold,mag_image) ) 

#define ICVIPTools_Kuwahara_Filter(This,image,masksize,result)	\
    ( (This)->lpVtbl -> Kuwahara_Filter(This,image,masksize,result) ) 

#define ICVIPTools_Label(This,image,result)	\
    ( (This)->lpVtbl -> Label(This,image,result) ) 

#define ICVIPTools_Laws_Texture_Feature(This,image,labeled_image,row,col,window_size,vector1,vector2,features)	\
    ( (This)->lpVtbl -> Laws_Texture_Feature(This,image,labeled_image,row,col,window_size,vector1,vector2,features) ) 

#define ICVIPTools_Least_Squares(This,degr_image,degr_fn,smoothness_fn,gamma,max_gain,cutoff,result)	\
    ( (This)->lpVtbl -> Least_Squares(This,degr_image,degr_fn,smoothness_fn,gamma,max_gain,cutoff,result) ) 

#define ICVIPTools_Local_Adaptive_Zoom(This,image,result)	\
    ( (This)->lpVtbl -> Local_Adaptive_Zoom(This,image,result) ) 

#define ICVIPTools_Local_Histeq(This,image,blocksize,band,result)	\
    ( (This)->lpVtbl -> Local_Histeq(This,image,blocksize,band,result) ) 

#define ICVIPTools_Log_Ace_Filter(This,image,masksize,local_mean,local_gain,result)	\
    ( (This)->lpVtbl -> Log_Ace_Filter(This,image,masksize,local_mean,local_gain,result) ) 

#define ICVIPTools_Log_Remap(This,image,band,result)	\
    ( (This)->lpVtbl -> Log_Remap(This,image,band,result) ) 

#define ICVIPTools_LogMap_Image(This,image,band,result)	\
    ( (This)->lpVtbl -> LogMap_Image(This,image,band,result) ) 

#define ICVIPTools_Lum_Average(This,image,result)	\
    ( (This)->lpVtbl -> Lum_Average(This,image,result) ) 

#define ICVIPTools_Luminance_Image(This,image,result)	\
    ( (This)->lpVtbl -> Luminance_Image(This,image,result) ) 

#define ICVIPTools_Make_Histogram(This,histogram,image_format,color_format,bands,result)	\
    ( (This)->lpVtbl -> Make_Histogram(This,histogram,image_format,color_format,bands,result) ) 

#define ICVIPTools_Marr_Hildreth_Filter(This,image,sigma,threshold,result)	\
    ( (This)->lpVtbl -> Marr_Hildreth_Filter(This,image,sigma,threshold,result) ) 

#define ICVIPTools_Maximum_Filter(This,image,masksize,result)	\
    ( (This)->lpVtbl -> Maximum_Filter(This,image,masksize,result) ) 

#define ICVIPTools_Mean_Filter(This,image,masksize,result)	\
    ( (This)->lpVtbl -> Mean_Filter(This,image,masksize,result) ) 

#define ICVIPTools_Median_Cut_Segment(This,image,num_colors,ignore_background,r_background,g_background,b_background,result)	\
    ( (This)->lpVtbl -> Median_Cut_Segment(This,image,num_colors,ignore_background,r_background,g_background,b_background,result) ) 

#define ICVIPTools_Median_Filter(This,image,masksize,result)	\
    ( (This)->lpVtbl -> Median_Filter(This,image,masksize,result) ) 

#define ICVIPTools_Mesh_To_File(This,filename,mesh)	\
    ( (This)->lpVtbl -> Mesh_To_File(This,filename,mesh) ) 

#define ICVIPTools_Mesh_Warping(This,image,mesh,interpolation_method,result)	\
    ( (This)->lpVtbl -> Mesh_Warping(This,image,mesh,interpolation_method,result) ) 

#define ICVIPTools_Mesh_WarpingRI(This,image,mesh,interpolation_method,zero_missing,result)	\
    ( (This)->lpVtbl -> Mesh_WarpingRI(This,image,mesh,interpolation_method,zero_missing,result) ) 

#define ICVIPTools_Midpoint_Filter(This,image,masksize,result)	\
    ( (This)->lpVtbl -> Midpoint_Filter(This,image,masksize,result) ) 

#define ICVIPTools_Minimum_Filter(This,image,masksize,result)	\
    ( (This)->lpVtbl -> Minimum_Filter(This,image,masksize,result) ) 

#define ICVIPTools_Mmse_Filter(This,image,noise_variance,kernel_size,result)	\
    ( (This)->lpVtbl -> Mmse_Filter(This,image,noise_variance,kernel_size,result) ) 

#define ICVIPTools_Moravec_Corner_Filter(This,image,threshold,result)	\
    ( (This)->lpVtbl -> Moravec_Corner_Filter(This,image,threshold,result) ) 

#define ICVIPTools_Morph_Hitmiss(This,binary_image,masksize,mask_values,result)	\
    ( (This)->lpVtbl -> Morph_Hitmiss(This,binary_image,masksize,mask_values,result) ) 

#define ICVIPTools_Morph_Skeleton(This,binary_image,masksize,mask_values,iterations,four_eight_mask,method,result)	\
    ( (This)->lpVtbl -> Morph_Skeleton(This,binary_image,masksize,mask_values,iterations,four_eight_mask,method,result) ) 

#define ICVIPTools_Morph_Thinning(This,binary_image,masksize,mask_values,result)	\
    ( (This)->lpVtbl -> Morph_Thinning(This,binary_image,masksize,mask_values,result) ) 

#define ICVIPTools_MorphClose(This,image,kernel_type,kernel_size,height,width,result)	\
    ( (This)->lpVtbl -> MorphClose(This,image,kernel_type,kernel_size,height,width,result) ) 

#define ICVIPTools_MorphClose_Image(This,image,matrix,userOrg,x,y,size,result)	\
    ( (This)->lpVtbl -> MorphClose_Image(This,image,matrix,userOrg,x,y,size,result) ) 

#define ICVIPTools_MorphDilate(This,image,kernel_type,kernel_size,height,width,result)	\
    ( (This)->lpVtbl -> MorphDilate(This,image,kernel_type,kernel_size,height,width,result) ) 

#define ICVIPTools_MorphDilate_Image(This,image,matrix,userOrg,x,y,size,result)	\
    ( (This)->lpVtbl -> MorphDilate_Image(This,image,matrix,userOrg,x,y,size,result) ) 

#define ICVIPTools_MorphErode(This,image,kernel_type,kernel_size,height,width,result)	\
    ( (This)->lpVtbl -> MorphErode(This,image,kernel_type,kernel_size,height,width,result) ) 

#define ICVIPTools_MorphErode_Image(This,image,matrix,userOrg,x,y,size,result)	\
    ( (This)->lpVtbl -> MorphErode_Image(This,image,matrix,userOrg,x,y,size,result) ) 

#define ICVIPTools_Morpho(This,image,surrounds_string,rotation,boolfunc,connectedness,iterations,fields,result)	\
    ( (This)->lpVtbl -> Morpho(This,image,surrounds_string,rotation,boolfunc,connectedness,iterations,fields,result) ) 

#define ICVIPTools_Morpho_com(This,image,surrounds_string,rotation,boolfunc,iterations,subfields,unused,result)	\
    ( (This)->lpVtbl -> Morpho_com(This,image,surrounds_string,rotation,boolfunc,iterations,subfields,unused,result) ) 

#define ICVIPTools_MorphOpen(This,image,kernel_type,kernel_size,height,width,result)	\
    ( (This)->lpVtbl -> MorphOpen(This,image,kernel_type,kernel_size,height,width,result) ) 

#define ICVIPTools_MorphOpen_Image(This,image,matrix,userOrg,x,y,size,result)	\
    ( (This)->lpVtbl -> MorphOpen_Image(This,image,matrix,userOrg,x,y,size,result) ) 

#define ICVIPTools_Multi_Resolution_Segment(This,image,homogeneity_test,param1,param2,run_PCT,result)	\
    ( (This)->lpVtbl -> Multi_Resolution_Segment(This,image,homogeneity_test,param1,param2,run_PCT,result) ) 

#define ICVIPTools_Multiply_Image(This,image1,image2,result)	\
    ( (This)->lpVtbl -> Multiply_Image(This,image1,image2,result) ) 

#define ICVIPTools_Nearest_Centroid(This,test_set,training_set,outputfile,normalization,distance_measure,s_min,s_max,r_softmax,r_minkowski,error)	\
    ( (This)->lpVtbl -> Nearest_Centroid(This,test_set,training_set,outputfile,normalization,distance_measure,s_min,s_max,r_softmax,r_minkowski,error) ) 

#define ICVIPTools_Nearest_Neighbor(This,test_set,training_set,outputfile,normalization,distance_measure,s_min,s_max,r_softmax,r_minkowski,error)	\
    ( (This)->lpVtbl -> Nearest_Neighbor(This,test_set,training_set,outputfile,normalization,distance_measure,s_min,s_max,r_softmax,r_minkowski,error) ) 

#define ICVIPTools_Neg_Exp_Noise(This,image,variance,result)	\
    ( (This)->lpVtbl -> Neg_Exp_Noise(This,image,variance,result) ) 

#define ICVIPTools_New_Image(This,image_format,color_space,bands,height,width,datatype,data_format,result)	\
    ( (This)->lpVtbl -> New_Image(This,image_format,color_space,bands,height,width,datatype,data_format,result) ) 

#define ICVIPTools_Nonfft_Xformfilter(This,image,blocksize,keepdc,filter_type,p1,p2,filter_order,result)	\
    ( (This)->lpVtbl -> Nonfft_Xformfilter(This,image,blocksize,keepdc,filter_type,p1,p2,filter_order,result) ) 

#define ICVIPTools_Not_Image(This,image,result)	\
    ( (This)->lpVtbl -> Not_Image(This,image,result) ) 

#define ICVIPTools_Notch(This,filename,cols,rows,radius,image,num_points,interactive,result)	\
    ( (This)->lpVtbl -> Notch(This,filename,cols,rows,radius,image,num_points,interactive,result) ) 

#define ICVIPTools_Object_Crop(This,image,coordinates,format,r_value,g_value,b_value,result)	\
    ( (This)->lpVtbl -> Object_Crop(This,image,coordinates,format,r_value,g_value,b_value,result) ) 

#define ICVIPTools_Open_Consol_Redirect_Output(This)	\
    ( (This)->lpVtbl -> Open_Consol_Redirect_Output(This) ) 

#define ICVIPTools_Or_Image(This,image1,image2,result)	\
    ( (This)->lpVtbl -> Or_Image(This,image1,image2,result) ) 

#define ICVIPTools_Orientation(This,labeled_image,row,col,orientation)	\
    ( (This)->lpVtbl -> Orientation(This,labeled_image,row,col,orientation) ) 

#define ICVIPTools_Otsu_Segment(This,image,result)	\
    ( (This)->lpVtbl -> Otsu_Segment(This,image,result) ) 

#define ICVIPTools_Param_AD_Filter(This,image,iterations,speed,edge_height,blocksize,result)	\
    ( (This)->lpVtbl -> Param_AD_Filter(This,image,iterations,speed,edge_height,blocksize,result) ) 

#define ICVIPTools_Parametric_Wiener(This,degr_image,degr_fn,psd_noise,psd_orig,gamma,max_gain,cutoff,result)	\
    ( (This)->lpVtbl -> Parametric_Wiener(This,degr_image,degr_fn,psd_noise,psd_orig,gamma,max_gain,cutoff,result) ) 

#define ICVIPTools_Pct(This,image,ignore_background,background,result)	\
    ( (This)->lpVtbl -> Pct(This,image,ignore_background,background,result) ) 

#define ICVIPTools_Pct_Color(This,image,ignore_background,background,choice,result)	\
    ( (This)->lpVtbl -> Pct_Color(This,image,ignore_background,background,choice,result) ) 

#define ICVIPTools_Pct_Median_Segment(This,image,num_colors,result)	\
    ( (This)->lpVtbl -> Pct_Median_Segment(This,image,num_colors,result) ) 

#define ICVIPTools_Perimeter(This,labeled_image,row,col,perimeter)	\
    ( (This)->lpVtbl -> Perimeter(This,labeled_image,row,col,perimeter) ) 

#define ICVIPTools_Pngtocvip(This,filename,result)	\
    ( (This)->lpVtbl -> Pngtocvip(This,filename,result) ) 

#define ICVIPTools_Power_Spect_Eq(This,degr_image,degr_fn,psd_noise,psd_orig,max_gain,cutoff,result)	\
    ( (This)->lpVtbl -> Power_Spect_Eq(This,degr_image,degr_fn,psd_noise,psd_orig,max_gain,cutoff,result) ) 

#define ICVIPTools_Pratt_Merit(This,image1,image2,scale_factor,result)	\
    ( (This)->lpVtbl -> Pratt_Merit(This,image1,image2,scale_factor,result) ) 

#define ICVIPTools_Prewitt_Filter(This,image,dir_image,filter_type,kernel_size,keepdc,threshold,mag_image)	\
    ( (This)->lpVtbl -> Prewitt_Filter(This,image,dir_image,filter_type,kernel_size,keepdc,threshold,mag_image) ) 

#define ICVIPTools_Print_Image(This,dc,image)	\
    ( (This)->lpVtbl -> Print_Image(This,dc,image) ) 

#define ICVIPTools_Projection(This,labeled_image,row,col,height,width,projections)	\
    ( (This)->lpVtbl -> Projection(This,labeled_image,row,col,height,width,projections) ) 

#define ICVIPTools_Pseudo_Remap(This,image,lookup_table,result)	\
    ( (This)->lpVtbl -> Pseudo_Remap(This,image,lookup_table,result) ) 

#define ICVIPTools_Pseudocol_Freq(This,image,low_cutoff,high_cutoff,lowpass_band,bandpass_band,highpass_band,result)	\
    ( (This)->lpVtbl -> Pseudocol_Freq(This,image,low_cutoff,high_cutoff,lowpass_band,bandpass_band,highpass_band,result) ) 

#define ICVIPTools_Raster_Deblur_Filter(This,image,result)	\
    ( (This)->lpVtbl -> Raster_Deblur_Filter(This,image,result) ) 

#define ICVIPTools_Rayleigh_Noise(This,image,variance,result)	\
    ( (This)->lpVtbl -> Rayleigh_Noise(This,image,variance,result) ) 

#define ICVIPTools_Read_Image(This,filename,result)	\
    ( (This)->lpVtbl -> Read_Image(This,filename,result) ) 

#define ICVIPTools_Remap_Image(This,image,datatype,dmin,dmax,result)	\
    ( (This)->lpVtbl -> Remap_Image(This,image,datatype,dmin,dmax,result) ) 

#define ICVIPTools_REMAPP(This,image,datatype,dmin,dmax,result)	\
    ( (This)->lpVtbl -> REMAPP(This,image,datatype,dmin,dmax,result) ) 

#define ICVIPTools_Render_DisplayImage(This,window_dc,image,memory_dc)	\
    ( (This)->lpVtbl -> Render_DisplayImage(This,window_dc,image,memory_dc) ) 

#define ICVIPTools_Rms_Error(This,image1,image2,rms_values)	\
    ( (This)->lpVtbl -> Rms_Error(This,image1,image2,rms_values) ) 

#define ICVIPTools_Robinson_Filter(This,image,dir_image,mask_type,masksize,keepdc,threshold,mag_image)	\
    ( (This)->lpVtbl -> Robinson_Filter(This,image,dir_image,mask_type,masksize,keepdc,threshold,mag_image) ) 

#define ICVIPTools_Rotate(This,image,degrees,result)	\
    ( (This)->lpVtbl -> Rotate(This,image,degrees,result) ) 

#define ICVIPTools_Rst_invariant(This,labeled_image,row,col,features)	\
    ( (This)->lpVtbl -> Rst_invariant(This,labeled_image,row,col,features) ) 

#define ICVIPTools_Save_Compressed_Data(This,image,filename)	\
    ( (This)->lpVtbl -> Save_Compressed_Data(This,image,filename) ) 

#define ICVIPTools_Sct_Split_Segment(This,image,A_split,B_split,result)	\
    ( (This)->lpVtbl -> Sct_Split_Segment(This,image,A_split,B_split,result) ) 

#define ICVIPTools_Set_Console(This,unused)	\
    ( (This)->lpVtbl -> Set_Console(This,unused) ) 

#define ICVIPTools_Sharpen_I(This,image,remap,mask_type,masksize,low_clip,high_clip,add2original,result)	\
    ( (This)->lpVtbl -> Sharpen_I(This,image,remap,mask_type,masksize,low_clip,high_clip,add2original,result) ) 

#define ICVIPTools_Sharpen_II(This,image,add2original,result)	\
    ( (This)->lpVtbl -> Sharpen_II(This,image,add2original,result) ) 

#define ICVIPTools_Sharpen_III(This,image,add2original,result)	\
    ( (This)->lpVtbl -> Sharpen_III(This,image,add2original,result) ) 

#define ICVIPTools_Shen_Castan_Filter(This,image,smoothing_factor,window_size,low_threshold,high_threshold,thin_factor,intermediate_image,result)	\
    ( (This)->lpVtbl -> Shen_Castan_Filter(This,image,smoothing_factor,window_size,low_threshold,high_threshold,thin_factor,intermediate_image,result) ) 

#define ICVIPTools_Show_DisplayImage(This,window_dc,memory_dc,window_width,window_height,memory_width,memory_height)	\
    ( (This)->lpVtbl -> Show_DisplayImage(This,window_dc,memory_dc,window_width,window_height,memory_width,memory_height) ) 

#define ICVIPTools_Show_Image(This,dc,x,y,image)	\
    ( (This)->lpVtbl -> Show_Image(This,dc,x,y,image) ) 

#define ICVIPTools_Show_Image_Ex(This,window_dc,memory_dc,x,y,image)	\
    ( (This)->lpVtbl -> Show_Image_Ex(This,window_dc,memory_dc,x,y,image) ) 

#define ICVIPTools_Shrink(This,image,factor,result)	\
    ( (This)->lpVtbl -> Shrink(This,image,factor,result) ) 

#define ICVIPTools_Simple_Wiener(This,degr_image,degr_fn,k,result)	\
    ( (This)->lpVtbl -> Simple_Wiener(This,degr_image,degr_fn,k,result) ) 

#define ICVIPTools_Single_Filter(This,image,sizing_factor_x,sizing_factor_y,centerx,centery,rotation,beta,kernel_size,kernel_data,choice,result)	\
    ( (This)->lpVtbl -> Single_Filter(This,image,sizing_factor_x,sizing_factor_y,centerx,centery,rotation,beta,kernel_size,kernel_data,choice,result) ) 

#define ICVIPTools_Snr(This,image1,image2,snr_values)	\
    ( (This)->lpVtbl -> Snr(This,image1,image2,snr_values) ) 

#define ICVIPTools_Sobel_Filter(This,image,dir_image,filter_type,kernel_size,keepdc,threshold,mag_image)	\
    ( (This)->lpVtbl -> Sobel_Filter(This,image,dir_image,filter_type,kernel_size,keepdc,threshold,mag_image) ) 

#define ICVIPTools_Spatial_Quant(This,image,rows,cols,method,result)	\
    ( (This)->lpVtbl -> Spatial_Quant(This,image,rows,cols,method,result) ) 

#define ICVIPTools_Spec_Hist_Image(This,image,r_histogram,g_histogram,b_histogram,result)	\
    ( (This)->lpVtbl -> Spec_Hist_Image(This,image,r_histogram,g_histogram,b_histogram,result) ) 

#define ICVIPTools_Specify_Filter(This,image,mask_height,mask_width,mask_values,normalization,result)	\
    ( (This)->lpVtbl -> Specify_Filter(This,image,mask_height,mask_width,mask_values,normalization,result) ) 

#define ICVIPTools_Speckle_Noise(This,image,psalt,ppepper,result)	\
    ( (This)->lpVtbl -> Speckle_Noise(This,image,psalt,ppepper,result) ) 

#define ICVIPTools_Spectral_Feature(This,image,labeled_image,rings,sectors,row,col,features)	\
    ( (This)->lpVtbl -> Spectral_Feature(This,image,labeled_image,rings,sectors,row,col,features) ) 

#define ICVIPTools_Split_Merge_Segment(This,image,level,homogeneity_test,param1,param2,run_PCT,result)	\
    ( (This)->lpVtbl -> Split_Merge_Segment(This,image,level,homogeneity_test,param1,param2,run_PCT,result) ) 

#define ICVIPTools_Subtract_Image(This,image1,image2,result)	\
    ( (This)->lpVtbl -> Subtract_Image(This,image1,image2,result) ) 

#define ICVIPTools_TextureFeature(This,image,labeled_image,row,col,distance,bitmask,features)	\
    ( (This)->lpVtbl -> TextureFeature(This,image,labeled_image,row,col,distance,bitmask,features) ) 

#define ICVIPTools_TextureFeature2(This,image,labeled_image,band,row,col,distance,energy,inertia,correlation,inv_diff,entropy,include_zero_pairs,features)	\
    ( (This)->lpVtbl -> TextureFeature2(This,image,labeled_image,band,row,col,distance,energy,inertia,correlation,inv_diff,entropy,include_zero_pairs,features) ) 

#define ICVIPTools_Thinness(This,labeled_image,row,col,thinness)	\
    ( (This)->lpVtbl -> Thinness(This,labeled_image,row,col,thinness) ) 

#define ICVIPTools_Threshold_Segment(This,image,threshold,byte_remap,result)	\
    ( (This)->lpVtbl -> Threshold_Segment(This,image,threshold,byte_remap,result) ) 

#define ICVIPTools_Tifftocvip(This,filename,verbose,result)	\
    ( (This)->lpVtbl -> Tifftocvip(This,filename,verbose,result) ) 

#define ICVIPTools_Tile_by_name(This,filename)	\
    ( (This)->lpVtbl -> Tile_by_name(This,filename) ) 

#define ICVIPTools_Transform_Compression(This,image,filename,quantfile,color_space,xform,basis,blocksize,quantization,use_quant_table,use_vector_quant,datatype,remap_type,keepdc,result)	\
    ( (This)->lpVtbl -> Transform_Compression(This,image,filename,quantfile,color_space,xform,basis,blocksize,quantization,use_quant_table,use_vector_quant,datatype,remap_type,keepdc,result) ) 

#define ICVIPTools_Transform_Sharpen(This,image,xform,cutoff,filter_type,filter_order,keepdc,add2original,result)	\
    ( (This)->lpVtbl -> Transform_Sharpen(This,image,xform,cutoff,filter_type,filter_order,keepdc,add2original,result) ) 

#define ICVIPTools_Transform_Smoothing(This,image,xform,cutoff,filter_type,filter_order,keepdc,result)	\
    ( (This)->lpVtbl -> Transform_Smoothing(This,image,xform,cutoff,filter_type,filter_order,keepdc,result) ) 

#define ICVIPTools_Translate(This,image,wrap,row_offset,col_offset,rows,cols,row_slide,col_slide,fill_val,result)	\
    ( (This)->lpVtbl -> Translate(This,image,wrap,row_offset,col_offset,rows,cols,row_slide,col_slide,fill_val,result) ) 

#define ICVIPTools_Uniform_Noise(This,image,variance,mean,result)	\
    ( (This)->lpVtbl -> Uniform_Noise(This,image,variance,mean,result) ) 

#define ICVIPTools_Unsharp_Filter(This,image,lower_limit,upper_limit,low_clip,high_clip,result)	\
    ( (This)->lpVtbl -> Unsharp_Filter(This,image,lower_limit,upper_limit,low_clip,high_clip,result) ) 

#define ICVIPTools_Vertical_Flip(This,image,result)	\
    ( (This)->lpVtbl -> Vertical_Flip(This,image,result) ) 

#define ICVIPTools_Vq_Compress(This,image,filename,use_file_codebook,use_fixed_codebook,error_threshold,codebook_filename,num_entries,vector_height,vector_width,result)	\
    ( (This)->lpVtbl -> Vq_Compress(This,image,filename,use_file_codebook,use_fixed_codebook,error_threshold,codebook_filename,num_entries,vector_height,vector_width,result) ) 

#define ICVIPTools_Vq_Decompress(This,filename,result)	\
    ( (This)->lpVtbl -> Vq_Decompress(This,filename,result) ) 

#define ICVIPTools_Walhad_Transform(This,image,xform,blocksize,result)	\
    ( (This)->lpVtbl -> Walhad_Transform(This,image,xform,blocksize,result) ) 

#define ICVIPTools_Watershed_Segment(This,image,merge_result,threshold,result)	\
    ( (This)->lpVtbl -> Watershed_Segment(This,image,merge_result,threshold,result) ) 

#define ICVIPTools_Wavdaub4_Transform(This,image,direction,low_band,result)	\
    ( (This)->lpVtbl -> Wavdaub4_Transform(This,image,direction,low_band,result) ) 

#define ICVIPTools_Wavhaar_Transform(This,image,direction,low_band,result)	\
    ( (This)->lpVtbl -> Wavhaar_Transform(This,image,direction,low_band,result) ) 

#define ICVIPTools_Wiener(This,degr_image,degr_fn,psd_noise,psd_orig,max_gain,cutoff,result)	\
    ( (This)->lpVtbl -> Wiener(This,degr_image,degr_fn,psd_noise,psd_orig,max_gain,cutoff,result) ) 

#define ICVIPTools_Write_Image(This,image,filename,retain_image,run_setup,image_format,verbose)	\
    ( (This)->lpVtbl -> Write_Image(This,image,filename,retain_image,run_setup,image_format,verbose) ) 

#define ICVIPTools_Write_JPEG_Image(This,image,filename,retain_image,run_setup,image_format,verbose,ratio)	\
    ( (This)->lpVtbl -> Write_JPEG_Image(This,image,filename,retain_image,run_setup,image_format,verbose,ratio) ) 

#define ICVIPTools_Xor_Error(This,image1,image2,error_values)	\
    ( (This)->lpVtbl -> Xor_Error(This,image1,image2,error_values) ) 

#define ICVIPTools_Xor_Image(This,image1,image2,result)	\
    ( (This)->lpVtbl -> Xor_Image(This,image1,image2,result) ) 

#define ICVIPTools_Xvq_Compress(This,image,xform,scheme,filename,output_data_type,remap_type,dc_term_handling,result)	\
    ( (This)->lpVtbl -> Xvq_Compress(This,image,xform,scheme,filename,output_data_type,remap_type,dc_term_handling,result) ) 

#define ICVIPTools_Xvq_Decompress(This,filename,result)	\
    ( (This)->lpVtbl -> Xvq_Decompress(This,filename,result) ) 

#define ICVIPTools_Ypmean_Filter(This,image,masksize,p,result)	\
    ( (This)->lpVtbl -> Ypmean_Filter(This,image,masksize,p,result) ) 

#define ICVIPTools_Zon_Compress(This,filename,image,blocksize,xform,mask_type,compression_ratio)	\
    ( (This)->lpVtbl -> Zon_Compress(This,filename,image,blocksize,xform,mask_type,compression_ratio) ) 

#define ICVIPTools_Zon_Decompress(This,filename,result)	\
    ( (This)->lpVtbl -> Zon_Decompress(This,filename,result) ) 

#define ICVIPTools_Zon2_Compress(This,filename,image,blocksize,xform,mask_type,compression_ratio)	\
    ( (This)->lpVtbl -> Zon2_Compress(This,filename,image,blocksize,xform,mask_type,compression_ratio) ) 

#define ICVIPTools_Zon2_Decompress(This,filename,result)	\
    ( (This)->lpVtbl -> Zon2_Decompress(This,filename,result) ) 

#define ICVIPTools_Zoom(This,image,quadrant,col,row,cols,rows,factor_requested,result)	\
    ( (This)->lpVtbl -> Zoom(This,image,quadrant,col,row,cols,rows,factor_requested,result) ) 

#define ICVIPTools_Zvl_Compress(This,filename,image)	\
    ( (This)->lpVtbl -> Zvl_Compress(This,filename,image) ) 

#define ICVIPTools_Zvl_Decompress(This,filename,result)	\
    ( (This)->lpVtbl -> Zvl_Decompress(This,filename,result) ) 

#define ICVIPTools_Dice_Coef(This,image1,image2,error_values)	\
    ( (This)->lpVtbl -> Dice_Coef(This,image1,image2,error_values) ) 

#define ICVIPTools_Jaccard_Index(This,image1,image2,error_values)	\
    ( (This)->lpVtbl -> Jaccard_Index(This,image1,image2,error_values) ) 

#define ICVIPTools_Overlap_Coef(This,image1,image2,error_values)	\
    ( (This)->lpVtbl -> Overlap_Coef(This,image1,image2,error_values) ) 

#define ICVIPTools_CLAHE(This,image,blocksize,clippercent,band,result)	\
    ( (This)->lpVtbl -> CLAHE(This,image,blocksize,clippercent,band,result) ) 

#define ICVIPTools_CLAHE_Grid(This,image,blocksize,clippercent,band,result)	\
    ( (This)->lpVtbl -> CLAHE_Grid(This,image,blocksize,clippercent,band,result) ) 

#define ICVIPTools_superPixel(This,image,result)	\
    ( (This)->lpVtbl -> superPixel(This,image,result) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Haar_Transform_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long direction,
    /* [in] */ long blocksize,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Haar_Transform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Harmonic_Filter_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long masksize,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Harmonic_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Harris_Corner_Filter_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ float alpha,
    /* [in] */ long threshold,
    /* [in] */ long border,
    /* [in] */ float dmin,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Harris_Corner_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_High_Freq_Emphasis_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long blocksize,
    /* [in] */ long keepdc,
    /* [in] */ long cutoff,
    /* [in] */ double alpha,
    /* [in] */ long filter_order,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_High_Freq_Emphasis_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Highboost_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long masksize,
    /* [in] */ long center_value,
    /* [in] */ long add2original,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Highboost_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_HighFreq_Emphasis_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long xform,
    /* [in] */ long cutoff,
    /* [in] */ long filter_order,
    /* [in] */ double offset,
    /* [in] */ long keepdc,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_HighFreq_Emphasis_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Highpass_Spatial_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long add2original,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Highpass_Spatial_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Hist_Feature_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long *labeled_image,
    /* [in] */ long row,
    /* [in] */ long col,
    /* [retval][out] */ VARIANT *features);


void __RPC_STUB ICVIPTools_Hist_Feature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Hist_Slide_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ int slide,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Hist_Slide_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Hist_Spec_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ BSTR *r_histogram,
    /* [in] */ BSTR *g_histogram,
    /* [in] */ BSTR *b_histogram,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Hist_Spec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Hist_Stretch_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ int low_limit,
    /* [in] */ int high_limit,
    /* [in] */ float low_clip,
    /* [in] */ float high_clip,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Hist_Stretch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Hist_Thresh_Gray_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ float tore,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Hist_Thresh_Gray_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Hist_Thresh_Segment_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ float tore,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Hist_Thresh_Segment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Histeq_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ int band,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Histeq_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Histogram_Spec_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ double *histogram,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Histogram_Spec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_History_Add_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long *history);


void __RPC_STUB ICVIPTools_History_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_History_Check_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ int program,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_History_Check_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_History_Copy_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *source,
    /* [in] */ long *destination);


void __RPC_STUB ICVIPTools_History_Copy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_history_create_Proxy( 
    ICVIPTools * This,
    /* [in] */ long prog,
    /* [in] */ long type,
    /* [in] */ float value,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_history_create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_history_create2_Proxy( 
    ICVIPTools * This,
    /* [in] */ long prog,
    /* [in] */ long type,
    /* [in] */ int value1,
    /* [in] */ int value2,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_history_create2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_History_Delete_Program_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ int program,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_History_Delete_Program_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_History_Get_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ int program,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_History_Get_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_History_get_data_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *history,
    /* [in] */ int program,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_History_get_data_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_History_get_data2_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *history,
    /* [in] */ int program,
    /* [in] */ int index,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_History_get_data2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Homomorphic_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ double upper_limit,
    /* [in] */ double lower_limit,
    /* [in] */ long cutoff,
    /* [in] */ long add2original,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Homomorphic_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Horizontal_Flip_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Horizontal_Flip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Hough_Filter_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ BSTR *image_name,
    /* [in] */ BSTR *angles_of_interest,
    /* [in] */ long threshold,
    /* [in] */ long connection_distance,
    /* [in] */ long interactive,
    /* [in] */ long delta_length,
    /* [in] */ long segment_length,
    /* [in] */ long intermediate_result,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Hough_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Huf_Compress_Proxy( 
    ICVIPTools * This,
    /* [in] */ BSTR *filename,
    /* [in] */ long *image);


void __RPC_STUB ICVIPTools_Huf_Compress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Huf_Decompress_Proxy( 
    ICVIPTools * This,
    /* [in] */ BSTR *filename,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Huf_Decompress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Idct_Transform_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long blocksize,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Idct_Transform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Ideal_Band_Pass_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long blocksize,
    /* [in] */ long keepdc,
    /* [in] */ long inner_cutoff,
    /* [in] */ long outer_cutoff,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Ideal_Band_Pass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Ideal_Band_Reject_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long blocksize,
    /* [in] */ long keepdc,
    /* [in] */ long inner_cutoff,
    /* [in] */ long outer_cutoff,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Ideal_Band_Reject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Ideal_High_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long blocksize,
    /* [in] */ long keepdc,
    /* [in] */ long cutoff,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Ideal_High_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Ideal_Low_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long blocksize,
    /* [in] */ long keepdc,
    /* [in] */ long cutoff,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Ideal_Low_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Ifft_Transform_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long blocksize,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Ifft_Transform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Igs_Segment_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long gray_levels,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Igs_Segment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Improved_Mmse_Filter_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ float threshold,
    /* [in] */ long kernel_size,
    /* [in] */ float noise_variance,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Improved_Mmse_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Input_Mesh_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *points,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Input_Mesh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Intensity_Slicing_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long *lookup_table,
    /* [in] */ long options,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Intensity_Slicing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Inverse_Xformfilter_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *degr_image,
    /* [in] */ long *degr_fn,
    /* [in] */ long max_gain,
    /* [in] */ double cutoff,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Inverse_Xformfilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Ipct_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long ignore_background,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Ipct_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Irregular_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *labeled_image,
    /* [in] */ int row,
    /* [in] */ int col,
    /* [retval][out] */ double *result);


void __RPC_STUB ICVIPTools_Irregular_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Jp2_Decoder_Proxy( 
    ICVIPTools * This,
    /* [in] */ BSTR *filename,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Jp2_Decoder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Jp2_Encoder_Proxy( 
    ICVIPTools * This,
    /* [in] */ BSTR *filename,
    /* [in] */ long *image,
    /* [in] */ int rate,
    /* [in] */ int quality,
    /* [in] */ int layers,
    /* [in] */ int blocksize);


void __RPC_STUB ICVIPTools_Jp2_Encoder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Jpg_Compress_Proxy( 
    ICVIPTools * This,
    /* [in] */ BSTR *filename,
    /* [in] */ long *image,
    /* [in] */ int quality,
    /* [in] */ long grayscale,
    /* [in] */ long optimize,
    /* [in] */ int smooth,
    /* [in] */ long verbose,
    /* [in] */ BSTR *qtablesFile);


void __RPC_STUB ICVIPTools_Jpg_Compress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Jpg_Decompress_Proxy( 
    ICVIPTools * This,
    /* [in] */ BSTR *filename,
    /* [in] */ int num_colors,
    /* [in] */ long blocksmooth,
    /* [in] */ long grayscale,
    /* [in] */ long nodither,
    /* [in] */ long verbose,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Jpg_Decompress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Jpgtocvip_Proxy( 
    ICVIPTools * This,
    /* [in] */ BSTR *filename,
    /* [in] */ int num_colors,
    /* [in] */ long blocksmooth,
    /* [in] */ long grayscale,
    /* [in] */ long nodither,
    /* [in] */ long verbose,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Jpgtocvip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_K_Nearest_Neighbor_Proxy( 
    ICVIPTools * This,
    /* [in] */ BSTR *test_set,
    /* [in] */ BSTR *training_set,
    /* [in] */ BSTR *outputfile,
    /* [in] */ int normalization,
    /* [in] */ int distance_measure,
    /* [in] */ int k,
    /* [in] */ float s_min,
    /* [in] */ float s_max,
    /* [in] */ float r_softmax,
    /* [in] */ float r_minkowski,
    /* [retval][out] */ long *error);


void __RPC_STUB ICVIPTools_K_Nearest_Neighbor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Krisch_Filter_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long *dir_image,
    /* [in] */ long filter_type,
    /* [in] */ long kernel_size,
    /* [in] */ long keepdc,
    /* [in] */ long threshold,
    /* [retval][out] */ long *mag_image);


void __RPC_STUB ICVIPTools_Krisch_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Kuwahara_Filter_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long masksize,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Kuwahara_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Label_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Label_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Laws_Texture_Feature_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long *labeled_image,
    /* [in] */ int row,
    /* [in] */ int col,
    /* [in] */ int window_size,
    /* [in] */ int vector1,
    /* [in] */ int vector2,
    /* [retval][out] */ VARIANT *features);


void __RPC_STUB ICVIPTools_Laws_Texture_Feature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Least_Squares_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *degr_image,
    /* [in] */ long *degr_fn,
    /* [in] */ long *smoothness_fn,
    /* [in] */ double gamma,
    /* [in] */ long max_gain,
    /* [in] */ long cutoff,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Least_Squares_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Local_Adaptive_Zoom_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Local_Adaptive_Zoom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Local_Histeq_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ int blocksize,
    /* [in] */ int band,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Local_Histeq_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Log_Ace_Filter_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long masksize,
    /* [in] */ double local_mean,
    /* [in] */ double local_gain,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Log_Ace_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Log_Remap_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long band,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Log_Remap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_LogMap_Image_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ int band,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_LogMap_Image_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Lum_Average_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Lum_Average_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Luminance_Image_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Luminance_Image_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Make_Histogram_Proxy( 
    ICVIPTools * This,
    /* [in] */ double *histogram,
    /* [in] */ long image_format,
    /* [in] */ long color_format,
    /* [in] */ long bands,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Make_Histogram_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Marr_Hildreth_Filter_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ float sigma,
    /* [in] */ int threshold,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Marr_Hildreth_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Maximum_Filter_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long masksize,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Maximum_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Mean_Filter_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long masksize,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Mean_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Median_Cut_Segment_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long num_colors,
    /* [in] */ long ignore_background,
    /* [in] */ long r_background,
    /* [in] */ long g_background,
    /* [in] */ long b_background,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Median_Cut_Segment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Median_Filter_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long masksize,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Median_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Mesh_To_File_Proxy( 
    ICVIPTools * This,
    /* [in] */ BSTR *filename,
    /* [in] */ long *mesh);


void __RPC_STUB ICVIPTools_Mesh_To_File_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Mesh_Warping_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long *mesh,
    /* [in] */ long interpolation_method,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Mesh_Warping_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Mesh_WarpingRI_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long *mesh,
    /* [in] */ long interpolation_method,
    /* [in] */ long zero_missing,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Mesh_WarpingRI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Midpoint_Filter_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long masksize,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Midpoint_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Minimum_Filter_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long masksize,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Minimum_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Mmse_Filter_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ double noise_variance,
    /* [in] */ long kernel_size,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Mmse_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Moravec_Corner_Filter_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ float threshold,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Moravec_Corner_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Morph_Hitmiss_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *binary_image,
    /* [in] */ long masksize,
    /* [in] */ double *mask_values,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Morph_Hitmiss_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Morph_Skeleton_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *binary_image,
    /* [in] */ long masksize,
    /* [in] */ double *mask_values,
    /* [in] */ long iterations,
    /* [in] */ long four_eight_mask,
    /* [in] */ long method,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Morph_Skeleton_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Morph_Thinning_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *binary_image,
    /* [in] */ long masksize,
    /* [in] */ double *mask_values,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Morph_Thinning_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_MorphClose_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ int kernel_type,
    /* [in] */ int kernel_size,
    /* [in] */ int height,
    /* [in] */ int width,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_MorphClose_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_MorphClose_Image_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long *matrix,
    /* [in] */ int userOrg,
    /* [in] */ int x,
    /* [in] */ int y,
    /* [in] */ int size,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_MorphClose_Image_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_MorphDilate_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ int kernel_type,
    /* [in] */ int kernel_size,
    /* [in] */ int height,
    /* [in] */ int width,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_MorphDilate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_MorphDilate_Image_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ int *matrix,
    /* [in] */ int userOrg,
    /* [in] */ int x,
    /* [in] */ int y,
    /* [in] */ int size,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_MorphDilate_Image_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_MorphErode_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ int kernel_type,
    /* [in] */ int kernel_size,
    /* [in] */ int height,
    /* [in] */ int width,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_MorphErode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_MorphErode_Image_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long *matrix,
    /* [in] */ int userOrg,
    /* [in] */ int x,
    /* [in] */ int y,
    /* [in] */ int size,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_MorphErode_Image_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Morpho_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ BSTR *surrounds_string,
    /* [in] */ long rotation,
    /* [in] */ long boolfunc,
    /* [in] */ long connectedness,
    /* [in] */ long iterations,
    /* [in] */ long fields,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Morpho_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Morpho_com_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ BSTR *surrounds_string,
    /* [in] */ long rotation,
    /* [in] */ long boolfunc,
    /* [in] */ long iterations,
    /* [in] */ long subfields,
    /* [in] */ long unused,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Morpho_com_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_MorphOpen_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ int kernel_type,
    /* [in] */ int kernel_size,
    /* [in] */ int height,
    /* [in] */ int width,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_MorphOpen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_MorphOpen_Image_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long *matrix,
    /* [in] */ int userOrg,
    /* [in] */ int x,
    /* [in] */ int y,
    /* [in] */ int size,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_MorphOpen_Image_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Multi_Resolution_Segment_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long homogeneity_test,
    /* [in] */ double param1,
    /* [in] */ double param2,
    /* [in] */ long run_PCT,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Multi_Resolution_Segment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Multiply_Image_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image1,
    /* [in] */ long *image2,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Multiply_Image_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Nearest_Centroid_Proxy( 
    ICVIPTools * This,
    /* [in] */ BSTR *test_set,
    /* [in] */ BSTR *training_set,
    /* [in] */ BSTR *outputfile,
    /* [in] */ int normalization,
    /* [in] */ int distance_measure,
    /* [in] */ float s_min,
    /* [in] */ float s_max,
    /* [in] */ float r_softmax,
    /* [in] */ float r_minkowski,
    /* [retval][out] */ long *error);


void __RPC_STUB ICVIPTools_Nearest_Centroid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Nearest_Neighbor_Proxy( 
    ICVIPTools * This,
    /* [in] */ BSTR *test_set,
    /* [in] */ BSTR *training_set,
    /* [in] */ BSTR *outputfile,
    /* [in] */ int normalization,
    /* [in] */ int distance_measure,
    /* [in] */ float s_min,
    /* [in] */ float s_max,
    /* [in] */ float r_softmax,
    /* [in] */ float r_minkowski,
    /* [retval][out] */ long *error);


void __RPC_STUB ICVIPTools_Nearest_Neighbor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Neg_Exp_Noise_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ double variance,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Neg_Exp_Noise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_New_Image_Proxy( 
    ICVIPTools * This,
    /* [in] */ long image_format,
    /* [in] */ long color_space,
    /* [in] */ int bands,
    /* [in] */ int height,
    /* [in] */ int width,
    /* [in] */ long datatype,
    /* [in] */ long data_format,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_New_Image_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Nonfft_Xformfilter_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long blocksize,
    /* [in] */ long keepdc,
    /* [in] */ long filter_type,
    /* [in] */ long p1,
    /* [in] */ double p2,
    /* [in] */ long filter_order,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Nonfft_Xformfilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Not_Image_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Not_Image_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Notch_Proxy( 
    ICVIPTools * This,
    /* [in] */ BSTR *filename,
    /* [in] */ long *cols,
    /* [in] */ long *rows,
    /* [in] */ long *radius,
    /* [in] */ long *image,
    /* [in] */ long num_points,
    /* [in] */ long interactive,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Notch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Object_Crop_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long *coordinates,
    /* [in] */ long format,
    /* [in] */ long r_value,
    /* [in] */ long g_value,
    /* [in] */ long b_value,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Object_Crop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Open_Consol_Redirect_Output_Proxy( 
    ICVIPTools * This);


void __RPC_STUB ICVIPTools_Open_Consol_Redirect_Output_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Or_Image_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image1,
    /* [in] */ long *image2,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Or_Image_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Orientation_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *labeled_image,
    /* [in] */ int row,
    /* [in] */ int col,
    /* [retval][out] */ long *orientation);


void __RPC_STUB ICVIPTools_Orientation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Otsu_Segment_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Otsu_Segment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Param_AD_Filter_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long iterations,
    /* [in] */ long speed,
    /* [in] */ long edge_height,
    /* [in] */ long blocksize,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Param_AD_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Parametric_Wiener_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *degr_image,
    /* [in] */ long *degr_fn,
    /* [in] */ long *psd_noise,
    /* [in] */ long *psd_orig,
    /* [in] */ double gamma,
    /* [in] */ long max_gain,
    /* [in] */ long cutoff,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Parametric_Wiener_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Pct_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long ignore_background,
    /* [in] */ double *background,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Pct_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Pct_Color_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long ignore_background,
    /* [in] */ double *background,
    /* [in] */ long choice,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Pct_Color_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Pct_Median_Segment_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long num_colors,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Pct_Median_Segment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Perimeter_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *labeled_image,
    /* [in] */ int row,
    /* [in] */ int col,
    /* [retval][out] */ long *perimeter);


void __RPC_STUB ICVIPTools_Perimeter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Pngtocvip_Proxy( 
    ICVIPTools * This,
    /* [in] */ BSTR *filename,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Pngtocvip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Power_Spect_Eq_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *degr_image,
    /* [in] */ long *degr_fn,
    /* [in] */ long *psd_noise,
    /* [in] */ long *psd_orig,
    /* [in] */ long max_gain,
    /* [in] */ long cutoff,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Power_Spect_Eq_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Pratt_Merit_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image1,
    /* [in] */ long *image2,
    /* [in] */ double scale_factor,
    /* [retval][out] */ double *result);


void __RPC_STUB ICVIPTools_Pratt_Merit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Prewitt_Filter_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long *dir_image,
    /* [in] */ long filter_type,
    /* [in] */ long kernel_size,
    /* [in] */ long keepdc,
    /* [in] */ long threshold,
    /* [retval][out] */ long *mag_image);


void __RPC_STUB ICVIPTools_Prewitt_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Print_Image_Proxy( 
    ICVIPTools * This,
    /* [in] */ int dc,
    /* [in] */ long *image);


void __RPC_STUB ICVIPTools_Print_Image_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Projection_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *labeled_image,
    /* [in] */ int row,
    /* [in] */ int col,
    /* [in] */ int height,
    /* [in] */ int width,
    /* [retval][out] */ VARIANT *projections);


void __RPC_STUB ICVIPTools_Projection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Pseudo_Remap_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long *lookup_table,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Pseudo_Remap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Pseudocol_Freq_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ int low_cutoff,
    /* [in] */ int high_cutoff,
    /* [in] */ int lowpass_band,
    /* [in] */ int bandpass_band,
    /* [in] */ int highpass_band,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Pseudocol_Freq_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Raster_Deblur_Filter_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Raster_Deblur_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Rayleigh_Noise_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ double variance,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Rayleigh_Noise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Read_Image_Proxy( 
    ICVIPTools * This,
    /* [in] */ BSTR *filename,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Read_Image_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Remap_Image_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long datatype,
    /* [in] */ long dmin,
    /* [in] */ long dmax,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Remap_Image_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_REMAPP_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long datatype,
    /* [in] */ long dmin,
    /* [in] */ long dmax,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_REMAPP_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Render_DisplayImage_Proxy( 
    ICVIPTools * This,
    /* [in] */ long window_dc,
    /* [in] */ long *image,
    /* [retval][out] */ long *memory_dc);


void __RPC_STUB ICVIPTools_Render_DisplayImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Rms_Error_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image1,
    /* [in] */ long *image2,
    /* [retval][out] */ VARIANT *rms_values);


void __RPC_STUB ICVIPTools_Rms_Error_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Robinson_Filter_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long *dir_image,
    /* [in] */ long mask_type,
    /* [in] */ long masksize,
    /* [in] */ long keepdc,
    /* [in] */ long threshold,
    /* [retval][out] */ long *mag_image);


void __RPC_STUB ICVIPTools_Robinson_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Rotate_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ float degrees,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Rst_invariant_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *labeled_image,
    /* [in] */ long row,
    /* [in] */ long col,
    /* [retval][out] */ VARIANT *features);


void __RPC_STUB ICVIPTools_Rst_invariant_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Save_Compressed_Data_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ BSTR *filename);


void __RPC_STUB ICVIPTools_Save_Compressed_Data_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Sct_Split_Segment_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long A_split,
    /* [in] */ long B_split,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Sct_Split_Segment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Set_Console_Proxy( 
    ICVIPTools * This,
    /* [in] */ long unused);


void __RPC_STUB ICVIPTools_Set_Console_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Sharpen_I_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long remap,
    /* [in] */ long mask_type,
    /* [in] */ long masksize,
    /* [in] */ float low_clip,
    /* [in] */ float high_clip,
    /* [in] */ long add2original,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Sharpen_I_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Sharpen_II_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long add2original,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Sharpen_II_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Sharpen_III_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long add2original,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Sharpen_III_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Shen_Castan_Filter_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ double smoothing_factor,
    /* [in] */ long window_size,
    /* [in] */ double low_threshold,
    /* [in] */ double high_threshold,
    /* [in] */ long thin_factor,
    /* [in] */ long *intermediate_image,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Shen_Castan_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Show_DisplayImage_Proxy( 
    ICVIPTools * This,
    /* [in] */ long window_dc,
    /* [in] */ long memory_dc,
    /* [in] */ long window_width,
    /* [in] */ long window_height,
    /* [in] */ long memory_width,
    /* [in] */ long memory_height);


void __RPC_STUB ICVIPTools_Show_DisplayImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Show_Image_Proxy( 
    ICVIPTools * This,
    /* [in] */ int dc,
    /* [in] */ int x,
    /* [in] */ int y,
    /* [in] */ long *image);


void __RPC_STUB ICVIPTools_Show_Image_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Show_Image_Ex_Proxy( 
    ICVIPTools * This,
    /* [in] */ int window_dc,
    /* [in] */ long *memory_dc,
    /* [in] */ int x,
    /* [in] */ int y,
    /* [in] */ long *image);


void __RPC_STUB ICVIPTools_Show_Image_Ex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Shrink_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ float factor,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Shrink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Simple_Wiener_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *degr_image,
    /* [in] */ long *degr_fn,
    /* [in] */ double k,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Simple_Wiener_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Single_Filter_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ double sizing_factor_x,
    /* [in] */ double sizing_factor_y,
    /* [in] */ long centerx,
    /* [in] */ long centery,
    /* [in] */ double rotation,
    /* [in] */ double beta,
    /* [in] */ long kernel_size,
    /* [in] */ double *kernel_data,
    /* [in] */ long choice,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Single_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Snr_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image1,
    /* [in] */ long *image2,
    /* [retval][out] */ VARIANT *snr_values);


void __RPC_STUB ICVIPTools_Snr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Sobel_Filter_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long *dir_image,
    /* [in] */ long filter_type,
    /* [in] */ long kernel_size,
    /* [in] */ long keepdc,
    /* [in] */ long threshold,
    /* [retval][out] */ long *mag_image);


void __RPC_STUB ICVIPTools_Sobel_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Spatial_Quant_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ int rows,
    /* [in] */ int cols,
    /* [in] */ int method,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Spatial_Quant_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Spec_Hist_Image_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ BSTR *r_histogram,
    /* [in] */ BSTR *g_histogram,
    /* [in] */ BSTR *b_histogram,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Spec_Hist_Image_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Specify_Filter_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long mask_height,
    /* [in] */ long mask_width,
    /* [in] */ double *mask_values,
    /* [in] */ int normalization,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Specify_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Speckle_Noise_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ double psalt,
    /* [in] */ double ppepper,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Speckle_Noise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Spectral_Feature_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long *labeled_image,
    /* [in] */ long rings,
    /* [in] */ long sectors,
    /* [in] */ long row,
    /* [in] */ long col,
    /* [retval][out] */ VARIANT *features);


void __RPC_STUB ICVIPTools_Spectral_Feature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Split_Merge_Segment_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long level,
    /* [in] */ long homogeneity_test,
    /* [in] */ double param1,
    /* [in] */ double param2,
    /* [in] */ long run_PCT,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Split_Merge_Segment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Subtract_Image_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image1,
    /* [in] */ long *image2,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Subtract_Image_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_TextureFeature_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long *labeled_image,
    /* [in] */ long row,
    /* [in] */ long col,
    /* [in] */ long distance,
    /* [in] */ long bitmask,
    /* [retval][out] */ VARIANT *features);


void __RPC_STUB ICVIPTools_TextureFeature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_TextureFeature2_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long *labeled_image,
    /* [in] */ long band,
    /* [in] */ long row,
    /* [in] */ long col,
    /* [in] */ long distance,
    /* [in] */ long energy,
    /* [in] */ long inertia,
    /* [in] */ long correlation,
    /* [in] */ long inv_diff,
    /* [in] */ long entropy,
    /* [in] */ long include_zero_pairs,
    /* [retval][out] */ VARIANT *features);


void __RPC_STUB ICVIPTools_TextureFeature2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Thinness_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *labeled_image,
    /* [in] */ int row,
    /* [in] */ int col,
    /* [retval][out] */ double *thinness);


void __RPC_STUB ICVIPTools_Thinness_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Threshold_Segment_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long threshold,
    /* [in] */ long byte_remap,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Threshold_Segment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Tifftocvip_Proxy( 
    ICVIPTools * This,
    /* [in] */ BSTR *filename,
    /* [in] */ int verbose,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Tifftocvip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Tile_by_name_Proxy( 
    ICVIPTools * This,
    /* [in] */ BSTR *filename);


void __RPC_STUB ICVIPTools_Tile_by_name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Transform_Compression_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ BSTR *filename,
    /* [in] */ BSTR *quantfile,
    /* [in] */ long color_space,
    /* [in] */ long xform,
    /* [in] */ long basis,
    /* [in] */ long blocksize,
    /* [in] */ long quantization,
    /* [in] */ long use_quant_table,
    /* [in] */ long use_vector_quant,
    /* [in] */ long datatype,
    /* [in] */ long remap_type,
    /* [in] */ long keepdc,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Transform_Compression_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Transform_Sharpen_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long xform,
    /* [in] */ long cutoff,
    /* [in] */ long filter_type,
    /* [in] */ long filter_order,
    /* [in] */ long keepdc,
    /* [in] */ long add2original,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Transform_Sharpen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Transform_Smoothing_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long xform,
    /* [in] */ long cutoff,
    /* [in] */ long filter_type,
    /* [in] */ long filter_order,
    /* [in] */ long keepdc,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Transform_Smoothing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Translate_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long wrap,
    /* [in] */ int row_offset,
    /* [in] */ int col_offset,
    /* [in] */ int rows,
    /* [in] */ int cols,
    /* [in] */ int row_slide,
    /* [in] */ int col_slide,
    /* [in] */ float fill_val,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Translate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Uniform_Noise_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ double variance,
    /* [in] */ double mean,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Uniform_Noise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Unsharp_Filter_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long lower_limit,
    /* [in] */ long upper_limit,
    /* [in] */ double low_clip,
    /* [in] */ double high_clip,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Unsharp_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Vertical_Flip_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Vertical_Flip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Vq_Compress_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ BSTR *filename,
    /* [in] */ long use_file_codebook,
    /* [in] */ long use_fixed_codebook,
    /* [in] */ double error_threshold,
    /* [in] */ BSTR *codebook_filename,
    /* [in] */ long num_entries,
    /* [in] */ long vector_height,
    /* [in] */ long vector_width,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Vq_Compress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Vq_Decompress_Proxy( 
    ICVIPTools * This,
    /* [in] */ BSTR *filename,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Vq_Decompress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Walhad_Transform_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long xform,
    /* [in] */ long blocksize,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Walhad_Transform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Watershed_Segment_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ int merge_result,
    /* [in] */ float threshold,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Watershed_Segment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Wavdaub4_Transform_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long direction,
    /* [in] */ long low_band,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Wavdaub4_Transform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Wavhaar_Transform_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long direction,
    /* [in] */ long low_band,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Wavhaar_Transform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Wiener_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *degr_image,
    /* [in] */ long *degr_fn,
    /* [in] */ long *psd_noise,
    /* [in] */ long *psd_orig,
    /* [in] */ long max_gain,
    /* [in] */ long cutoff,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Wiener_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Write_Image_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ BSTR *filename,
    /* [in] */ long retain_image,
    /* [in] */ long run_setup,
    /* [in] */ long image_format,
    /* [in] */ long verbose);


void __RPC_STUB ICVIPTools_Write_Image_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Write_JPEG_Image_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ BSTR *filename,
    /* [in] */ long retain_image,
    /* [in] */ long run_setup,
    /* [in] */ long image_format,
    /* [in] */ long verbose,
    /* [in] */ int ratio);


void __RPC_STUB ICVIPTools_Write_JPEG_Image_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Xor_Error_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image1,
    /* [in] */ long *image2,
    /* [retval][out] */ VARIANT *error_values);


void __RPC_STUB ICVIPTools_Xor_Error_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Xor_Image_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image1,
    /* [in] */ long *image2,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Xor_Image_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Xvq_Compress_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long xform,
    /* [in] */ long scheme,
    /* [in] */ BSTR *filename,
    /* [in] */ long output_data_type,
    /* [in] */ long remap_type,
    /* [in] */ long dc_term_handling,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Xvq_Compress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Xvq_Decompress_Proxy( 
    ICVIPTools * This,
    /* [in] */ BSTR *filename,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Xvq_Decompress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Ypmean_Filter_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ long masksize,
    /* [in] */ long p,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Ypmean_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Zon_Compress_Proxy( 
    ICVIPTools * This,
    /* [in] */ BSTR *filename,
    /* [in] */ long *image,
    /* [in] */ int blocksize,
    /* [in] */ int xform,
    /* [in] */ int mask_type,
    /* [in] */ float compression_ratio);


void __RPC_STUB ICVIPTools_Zon_Compress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Zon_Decompress_Proxy( 
    ICVIPTools * This,
    /* [in] */ BSTR *filename,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Zon_Decompress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Zon2_Compress_Proxy( 
    ICVIPTools * This,
    /* [in] */ BSTR *filename,
    /* [in] */ long *image,
    /* [in] */ int blocksize,
    /* [in] */ int xform,
    /* [in] */ int mask_type,
    /* [in] */ float compression_ratio);


void __RPC_STUB ICVIPTools_Zon2_Compress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Zon2_Decompress_Proxy( 
    ICVIPTools * This,
    /* [in] */ BSTR *filename,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Zon2_Decompress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Zoom_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ int quadrant,
    /* [in] */ int col,
    /* [in] */ int row,
    /* [in] */ int cols,
    /* [in] */ int rows,
    /* [in] */ float factor_requested,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Zoom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Zvl_Compress_Proxy( 
    ICVIPTools * This,
    /* [in] */ BSTR *filename,
    /* [in] */ long *image);


void __RPC_STUB ICVIPTools_Zvl_Compress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Zvl_Decompress_Proxy( 
    ICVIPTools * This,
    /* [in] */ BSTR *filename,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_Zvl_Decompress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Dice_Coef_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image1,
    /* [in] */ long *image2,
    /* [retval][out] */ VARIANT *error_values);


void __RPC_STUB ICVIPTools_Dice_Coef_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Jaccard_Index_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image1,
    /* [in] */ long *image2,
    /* [retval][out] */ VARIANT *error_values);


void __RPC_STUB ICVIPTools_Jaccard_Index_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_Overlap_Coef_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image1,
    /* [in] */ long *image2,
    /* [retval][out] */ VARIANT *error_values);


void __RPC_STUB ICVIPTools_Overlap_Coef_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_CLAHE_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ int blocksize,
    /* [in] */ double clippercent,
    /* [in] */ int band,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_CLAHE_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_CLAHE_Grid_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [in] */ int blocksize,
    /* [in] */ double clippercent,
    /* [in] */ int band,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_CLAHE_Grid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICVIPTools_superPixel_Proxy( 
    ICVIPTools * This,
    /* [in] */ long *image,
    /* [retval][out] */ long *result);


void __RPC_STUB ICVIPTools_superPixel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICVIPTools_INTERFACE_DEFINED__ */



#ifndef __SERVERLib_LIBRARY_DEFINED__
#define __SERVERLib_LIBRARY_DEFINED__

/* library SERVERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_SERVERLib;

EXTERN_C const CLSID CLSID_CVIPTools;

#ifdef __cplusplus

class DECLSPEC_UUID("FE0D49C6-136B-4775-B885-F87095347642")
CVIPTools;
#endif
#endif /* __SERVERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

unsigned long             __RPC_USER  BSTR_UserSize64(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal64(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal64(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree64(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize64(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal64(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal64(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree64(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


