// CVIPtools.h : Declaration of the CCVIPtools

#pragma once
#include "resource.h"       // main symbols
#include "CVIPCOM_i.h"

using namespace ATL;

// CCVIPtools
class ATL_NO_VTABLE CCVIPtools :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CCVIPtools, &CLSID_CVIPTools>,
	public IDispatchImpl<ICVIPTools, &IID_ICVIPTools, &LIBID_SERVERLib, /*wMajor =*/ 2, /*wMinor =*/ 0>
{
public:
	CCVIPtools()
    {
        fpStdout = NULL;
        fpStderr = NULL;
        hStdout = NULL;
        hStderr = NULL;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CVIPTOOLS)

BEGIN_COM_MAP(CCVIPtools)
	COM_INTERFACE_ENTRY(ICVIPTools)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	void FinalRelease()
	{
	}

private:
    static const int nBufferSize = 81920;
    HANDLE hStdout;
    HANDLE hStderr;
    FILE* fpStdout;
    FILE* fpStderr;

// ICVIPTools
public:
    STDMETHOD(superPixel)(/*[in]*/ long* image, /*[out,retval]*/ long* result);
    STDMETHOD(Ace2_Filter)(/*[in]*/ long* image, /*[in]*/ long masksize, /*[in]*/ double local_mean, /*[in]*/ double local_gain, /*[out,retval]*/ long* result);
    STDMETHOD(Acuity_Nightvision_Filter)(/*[in]*/ long* image, /*[in]*/ long reason, /*[in]*/ long threshold, /*[in]*/ long acuity, /*[out,retval]*/ long* result);
    STDMETHOD(AD_Filter)(/*[in]*/ long* image, /*[in]*/ long iterations, /*[in]*/ long speed, /*[in]*/ long edge_height, /*[out,retval]*/ long* result);
    STDMETHOD(Adapt_Median_Filter)(/*[in]*/ long* image, /*[in]*/ long masksize, /*[out,retval]*/ long* result);
    STDMETHOD(Adaptive_Contrast_Filter)(/*[in]*/ long* image, /*[in]*/ double k1, /*[in]*/ double k2, /*[in]*/ long kernel_size, /*[in]*/ double min_gain, /*[in]*/ double max_gain, /*[out,retval]*/ long* result);
    STDMETHOD(Add_Image)(/*[in]*/ long* image1, /*[in]*/ long* image2, /*[out,retval]*/ long* result);
    STDMETHOD(Alpha_Filter)(/*[in]*/ long* image, /*[in]*/ long masksize, /*[in]*/ long p, /*[out,retval]*/ long* result);
    STDMETHOD(And_Image)(/*[in]*/ long* image1, /*[in]*/ long* image2, /*[out,retval]*/ long* result);
    STDMETHOD(Area)(/*[in]*/ long* labeled_image, /*[in]*/ int row, /*[in]*/ int col, /*[out,retval]*/ long* area);
    STDMETHOD(Aspect)(/*[in]*/ long* labeled_image, /*[in]*/ int row, /*[in]*/ int col, /*[out,retval]*/ double* aspect);
    STDMETHOD(Assemble_Bands)(/*[in]*/ long bands[3], /*[out,retval]*/ long* result);
    STDMETHOD(Auto_Threshold_Segment)(/*[in]*/ long* image, /*[in]*/ float limit, /*[out,retval]*/ long* result);
    STDMETHOD(Bilinear_Interp)(/*[in]*/ long* image, /*[in]*/ float factor, /*[out,retval]*/ long* result);
    STDMETHOD(Bilinear_Interp1)(/*[in]*/ long* image, /*[in]*/ float xfactor, /*[in]*/ float yfactor, /*[out,retval]*/ long* result);
    STDMETHOD(Bintocvip)(/*[in]*/ BSTR* filename, /*[in]*/ long bands, /*[in]*/ long color_order, /*[in]*/ long interleaved, /*[in]*/ int height, /*[in]*/ int width, /*[in]*/ long verbose, /*[out,retval]*/ long* cvip_image);
    STDMETHOD(Bit_Compress)(/*[in]*/ BSTR* filename, /*[in]*/ long* image, /*[in]*/ long bitmask);
    STDMETHOD(Bit_Decompress)(/*[in]*/ BSTR* filename, /*[out,retval]*/ long* result);
    STDMETHOD(Boiecox_Filter)(/*[in]*/ long* image, /*[in]*/ double variance, /*[in]*/ long do_threshold, /*[in]*/ long do_hyst, /*[in]*/ long do_thin, /*[in]*/ double high_threshold, /*[in]*/ double low_threshold, /*[in]*/ long* threshhold_image, /*[in]*/ long* hyst_image, /*[out,retval]*/ long* result);
    STDMETHOD(Btc_Compress)(/*[in]*/ BSTR* filename, /*[in]*/ long* image, /*[in]*/ long blocksize);
    STDMETHOD(Btc_Decompression)(/*[in]*/ BSTR* filename, /*[out,retval]*/ long* result);
    STDMETHOD(Btc2_Compress)(/*[in]*/ BSTR* filename, /*[in]*/ long* image, /*[in]*/ long blocksize);
    STDMETHOD(Btc2_Decompress)(/*[in]*/ BSTR* filename, /*[out,retval]*/ long* result);
    STDMETHOD(Btc3_Compress)(/*[in]*/ BSTR* filename, /*[in]*/ long* image, /*[in]*/ long blocksize);
    STDMETHOD(Btc3_Decompress)(/*[in]*/ BSTR* filename, /*[out,retval]*/ long* result);
    STDMETHOD(Butterworth_Band_Pass)(/*[in]*/ long* image, /*[in]*/ long blocksize, /*[in]*/ long keepdc, /*[in]*/ long inner_cutoff, /*[in]*/ long outer_cutoff, /*[in]*/ long filter_order, /*[out,retval]*/ long* result);
    STDMETHOD(Butterworth_Band_Reject)(/*[in]*/ long* image, /*[in]*/ long blocksize, /*[in]*/ long keepdc, /*[in]*/ long inner_cutoff, /*[in]*/ long outer_cutoff, /*[in]*/ long filter_order, /*[out,retval]*/ long* result);
    STDMETHOD(Butterworth_High)(/*[in]*/ long* image, /*[in]*/ long blocksize, /*[in]*/ long keepdc, /*[in]*/ long cutoff, /*[in]*/ long filter_order, /*[out,retval]*/ long* result);
    STDMETHOD(Butterworth_Low)(/*[in]*/ long* image, /*[in]*/ long blocksize, /*[in]*/ long keepdc, /*[in]*/ long cutoff, /*[in]*/ long filter_order, /*[out,retval]*/ long* result);
    STDMETHOD(Canny_Filter)(/*[in]*/ long* image, /*[in]*/ double low_threshold, /*[in]*/ double high_threshold, /*[in]*/ double variance, /*[in]*/ long* mag_image, /*[in]*/ long* dir_image, /*[out,retval]*/ long* result);
    STDMETHOD(Cast_Image)(/*[in]*/ long* image, /*[in]*/ long datatype);
    STDMETHOD(CentroID)(/*[in]*/ long* labeled_image, /*[in]*/ long row, /*[in]*/ long col, /*[out,retval]*/ VARIANT* centroid);
    STDMETHOD(Cerchar_Filter)(/*[in]*/ long* image, /*[out,retval]*/ long* result);
    STDMETHOD(Check_Bin)(/*[in]*/ long* image, /*[out,retval]*/ long* is_binary);
    STDMETHOD(Check_xform_history)(/*[in]*/ long* image, /*[in]*/ int filter_type, /*[out,retval]*/ long* result);
    STDMETHOD(CLAHE)(/*[in]*/ long* image, /*[in]*/ int blocksize, /*[in]*/ double clippercent, /*[in]*/ int band,  /*[out,retval]*/ long* result);
    STDMETHOD(CLAHE_Grid)(/*[in]*/ long* image, /*[in]*/ int blocksize, /*[in]*/ double clippercent, /*[in]*/ int band,  /*[out,retval]*/ long* result);
    STDMETHOD(Close_Consol)();
    STDMETHOD(Close_Console)();
    STDMETHOD(Color_Contrast_Enhance)(/*[in]*/ long* image, /*[in]*/ long low_limit, /*[in]*/ long high_limit, /*[in]*/ float low_clip, /*[in]*/ float high_clip, /*[out,retval]*/ long* result);
    STDMETHOD(ColorXform)(/*[in]*/ long* image, /*[in]*/ long color_space, /*[in]*/ double* norm_vector, /*[in]*/ double* white_reference, /*[in]*/ long direction, /*[out,retval]*/ long* result);
    STDMETHOD(CondRemap_Image)(/*[in]*/ long* image, /*[in]*/ long datatype, /*[in]*/ int min, /*[in]*/ int max, /*[out,retval]*/ long* result);
    STDMETHOD(Contra_Filter)(/*[in]*/ long* image, /*[in]*/ long masksize, /*[in]*/ long p, /*[out,retval]*/ long* result);
    STDMETHOD(Copy_Paste)(/*[in]*/ long* src_image, /*[in]*/ long* dest_image, /*[in]*/ int src_row, /*[in]*/ int src_col, /*[in]*/ int height, /*[in]*/ int width, /*[in]*/ int dest_row, /*[in]*/ int dest_col, /*[in]*/ long transparent, /*[out,retval]*/ long* result);
    STDMETHOD(Create_Black)(/*[in]*/ int width, /*[in]*/ int height, /*[out,retval]*/ long* result);
    STDMETHOD(Create_Checkboard)(/*[in]*/ int width, /*[in]*/ int height, /*[in]*/ int start_col, /*[in]*/ int start_row, /*[in]*/ int blockx, /*[in]*/ int blocky, /*[out,retval]*/ long* result);
    STDMETHOD(Create_Circle)(/*[in]*/ int width, /*[in]*/ int height, /*[in]*/ int centerx, /*[in]*/ int centery, /*[in]*/ int radius, /*[out,retval]*/ long* result);
    STDMETHOD(Create_Cosine)(/*[in]*/ int img_size, /*[in]*/ int frequency, /*[in]*/ int direction, /*[out,retval]*/ long* result);
    STDMETHOD(Create_Degenerate_Circle)(/*[in]*/ int width, /*[in]*/ int height, /*[in]*/ int centerx, /*[in]*/ int centery, /*[in]*/ int radius, /*[in]*/ int blur, /*[out,retval]*/ long* result);
    STDMETHOD(Create_Ellipse)(/*[in]*/ int width, /*[in]*/ int height, /*[in]*/ int centerx, /*[in]*/ int centery, /*[in]*/ int shape_width, /*[in]*/ int shape_height, /*[out,retval]*/ long* result);
    STDMETHOD(Create_Line)(/*[in]*/ int width, /*[in]*/ int height, /*[in]*/ int tlx, /*[in]*/ int tly, /*[in]*/ int brx, /*[in]*/ int bry, /*[out,retval]*/ long* result);
    STDMETHOD(Create_Mask)(/*[in]*/ long width, /*[in]*/ long height, /*[in]*/ double* values, /*[out,retval]*/ long* result);
    STDMETHOD(Create_Mesh_Sine)(/*[in]*/ int rows, /*[in]*/ int cols, /*[out,retval]*/ long* result);
    STDMETHOD(Create_Rectangle)(/*[in]*/ int width, /*[in]*/ int height, /*[in]*/ int tlx, /*[in]*/ int tly, /*[in]*/ int shape_width, /*[in]*/ int shape_height, /*[out,retval]*/ long* result);
    STDMETHOD(Create_Sine)(/*[in]*/ int img_size, /*[in]*/ int frequency, /*[in]*/ int direction, /*[out,retval]*/ long* result);
    STDMETHOD(Create_Squarewave)(/*[in]*/ int img_size, /*[in]*/ int frequency, /*[in]*/ int direction, /*[out,retval]*/ long* result);
    STDMETHOD(Crop)(/*[in]*/ long* image, /*[in]*/ int start_row, /*[in]*/ int start_col, /*[in]*/ int rows, /*[in]*/ int cols, /*[out,retval]*/ long* result);
    STDMETHOD(CVIP_OUTPUT)(/*[out,retval]*/ BSTR* message);
    STDMETHOD(CVIPhalftone)(/*[in]*/ long* image, /*[in]*/ int halftone_method, /*[in]*/ int maxval, /*[in]*/ float threshold, /*[in]*/ long retain_image, /*[in]*/ long verbose, /*[out,retval]*/ long* result);
    STDMETHOD(Cviptoccc)(/*[in]*/ BSTR* filename, /*[in]*/ long maxcolor, /*[in]*/ long verbose, /*[in]*/ long dermvis, /*[in]*/ long* cvip_image);
    STDMETHOD(Cviptoeps)(/*[in]*/ BSTR* filename, /*[in]*/ long* cvip_image, /*[in]*/ double scale_x, /*[in]*/ double scale_y, /*[in]*/ long band, /*[in]*/ long verbose);
    STDMETHOD(Cviptogif)(/*[in]*/ BSTR* filename, /*[in]*/ long* cvip_image, /*[in]*/ long interlace, /*[in]*/ long verbose);
    STDMETHOD(Cviptoiris)(/*[in]*/ BSTR* filename, /*[in]*/ long* cvip_image, /*[in]*/ long verbose, /*[in]*/ long prt_type);
    STDMETHOD(Cviptoitex)(/*[in]*/ BSTR* filename, /*[in]*/ long* cvip_image, /*[in]*/ BSTR* comment, /*[in]*/ long verbose);
    STDMETHOD(Cviptojpg)(/*[in]*/ BSTR* filename, /*[in]*/ long* cvip_image, /*[in]*/ int quality, /*[in]*/ long grayscale, /*[in]*/ long optimize, /*[in]*/ int smooth, /*[in]*/ long verbose, /*[in]*/ BSTR* qtablesFile);
    STDMETHOD(Cviptopnm)(/*[in]*/ BSTR* filename, /*[in]*/ long* cvip_image, /*[in]*/ long verbose);
    STDMETHOD(Cviptoras)(/*[in]*/ BSTR* filename, /*[in]*/ long* cvip_image, /*[in]*/ long pr_type, /*[in]*/ long verbose);
    STDMETHOD(Cviptotiff)(/*[in]*/ BSTR* filename, /*[in]*/ long* cvip_image, /*[in]*/ long compression, /*[in]*/ long fillorder, /*[in]*/ long g3options, /*[in]*/ long predictor, /*[in]*/ long rowsperstrip, /*[in]*/ long verbose);
    STDMETHOD(Cviptovip)(/*[in]*/ BSTR* filename, /*[in]*/ long* cvip_image, /*[in]*/ long verbose, /*[in]*/ long save_history, /*[in]*/ long is_compressed);
    STDMETHOD(Date_Range)(/*[in]*/ long* image, /*[out,retval]*/ VARIANT* result);
    STDMETHOD(Dct_Transform)(/*[in]*/ long* image, /*[in]*/ long blocksize, /*[out,retval]*/ long* result);
    STDMETHOD(Delete_DisplayImage)(/*[in]*/ long memory_dc);
    STDMETHOD(Delete_Image)(/*[in]*/ long* image);
    STDMETHOD(Dice_Coef)(/*[in]*/long* image1, /*[in]*/long* image2, /*[out,retval]*/VARIANT* error_values);
    STDMETHOD(Divide_Image)(/*[in]*/ long* image1, /*[in]*/ long* image2, /*[in]*/ long zero2num, /*[out,retval]*/ long* result);
    STDMETHOD(Dpc_Compress)(/*[in]*/ BSTR* filename, /*[in]*/ long* image, /*[in]*/ float ratio, /*[in]*/ int bit_length, /*[in]*/ int clipping, /*[in]*/ int direction, /*[in]*/ int origin, /*[in]*/ float deviation);
    STDMETHOD(Dpc_Decompress)(/*[in]*/ BSTR* filename, /*[out,retval]*/ long* result);
    STDMETHOD(Draw_mesh)(/*[in]*/ long* image, /*[in]*/ long* mesh);
    STDMETHOD(Duplicate_Image)(/*[in]*/ long* image, /*[out,retval]*/ long* result);
    STDMETHOD(DynRLC_Compression)(/*[in]*/ BSTR* filename, /*[in]*/ long* image, /*[in]*/ long window_size, /*[out,retval]*/ long* result);
    STDMETHOD(DynRLC_deCompression)(/*[in]*/ BSTR* filename, /*[out,retval]*/ long* result);
    STDMETHOD(Edge_Detect_Filter)(/*[in]*/ long* image, /*[in]*/ long edge_detector, /*[in]*/ long mask_type, /*[in]*/ long masksize, /*[in]*/ long keepdc, /*[in]*/ long threshold, /*[in]*/ long frei_projection, /*[in]*/ long frei_threshold, /*[in]*/ long frei_angle, /*[out,retval]*/ long* result);
    STDMETHOD(Edge_Link_Filter)(/*[in]*/ long* binary_image, /*[in]*/ long connection_distance, /*[out,retval]*/ long* result);
    STDMETHOD(Enlarge)(/*[in]*/ long* image, /*[in]*/ int rows, /*[in]*/ int cols, /*[out,retval]*/ long* result);
    STDMETHOD(Epstocvip)(/*[in]*/ BSTR* filename, /*[in]*/ long verbose);
    STDMETHOD(Euler)(/*[in]*/ long* labeled_image, /*[in]*/ long row, /*[in]*/ long col, /*[out,retval]*/ long* euler);
    STDMETHOD(Exp_Ace_Filter)(/*[in]*/ long* image, /*[in]*/ long masksize, /*[in]*/ double local_mean, /*[in]*/ double local_gain, /*[out,retval]*/ long* result);
    STDMETHOD(Extract_Band)(/*[in]*/ long* image, /*[in]*/ int band, /*[out,retval]*/ long* result);
    STDMETHOD(Fft_Mag)(/*[in]*/ long* image, /*[out,retval]*/ long* result);
    STDMETHOD(Fft_Phase)(/*[in]*/ long* image, /*[in]*/ long remap_norm, /*[in]*/ double k, /*[out,retval]*/ long* result);
    STDMETHOD(Fft_Transform)(/*[in]*/ long* image, /*[in]*/ long blocksize, /*[out,retval]*/ long* result);
    STDMETHOD(File_To_Mesh)(/*[in]*/ BSTR* filename, /*[out,retval]*/ long* result);
    STDMETHOD(Fractal_Compression)(/*[in]*/ long* image, /*[in]*/ BSTR* filename, /*[in]*/ double tolerance, /*[in]*/ long min_part, /*[in]*/ long max_part, /*[in]*/ long dom_type, /*[in]*/ long dom_step, /*[in]*/ long c1, /*[in]*/ long c2, /*[in]*/ long scalebits, /*[in]*/ long offsetbits, /*[out,retval]*/ long* result);
    STDMETHOD(Fractal_deCompression)(/*[in]*/ BSTR* filename, /*[out,retval]*/ long* result);
    STDMETHOD(Fuzzyc_Segment)(/*[in]*/ long* image, /*[in]*/ double variance, /*[out,retval]*/ long* result);
    STDMETHOD(Gamma_Noise)(/*[in]*/ long* image, /*[in]*/ double variance, /*[in]*/ int alpha, /*[out,retval]*/ long* result);
    STDMETHOD(Gaussian_Blur_Filter)(/*[in]*/ long* image, /*[in]*/ long kernel_size, /*[out,retval]*/ long* result);
    STDMETHOD(Gaussian_Noise)(/*[in]*/ long* image, /*[in]*/ double variance, /*[in]*/ double mean, /*[out,retval]*/ long* result);
    STDMETHOD(Geometric_Filter)(/*[in]*/ long* image, /*[in]*/ long masksize, /*[out,retval]*/ long* result);
    STDMETHOD(Geometric_Mean)(/*[in]*/ long* degr_image, /*[in]*/ long* degr_fn, /*[in]*/ long* psd_noise, /*[in]*/ long* psd_orig, /*[in]*/ double gamma, /*[in]*/ double alpha, /*[in]*/ long max_gain, /*[in]*/ long cutoff, /*[out,retval]*/ long* result);
    STDMETHOD(get_hist_real)(/*[in]*/ long* image, /*[out,retval]*/ long* result);
    STDMETHOD(Get_Histogram_Image)(/*[in]*/ long* image, /*[out,retval]*/ long* result);
    STDMETHOD(Get_max_min_value)(/*[in]*/ long* image, /*[in]*/ double* min_max);
    STDMETHOD(Get_Mesh_Points)(/*[in]*/ long* mesh, /*[out,retval]*/ VARIANT* points);
    STDMETHOD(GetDataFormat_Image)(/*[in]*/ long* image, /*[out,retval]*/ long* format);
    STDMETHOD(GetDataType_Image)(/*[in]*/ long* image, /*[out,retval]*/ long* datatype);
    STDMETHOD(GetImageInfo)(/*[in]*/ long* image, /*[out,retval]*/ VARIANT* info);
    STDMETHOD(Getlast_Hist)(/*[in]*/ long* image, /*[in]*/ long* programs, /*[in]*/ int num_programs, /*[out,retval]*/ long* hist);
    STDMETHOD(GetNoOfBands_Image)(/*[in]*/ long* image, /*[out,retval]*/ long* bands);
    STDMETHOD(GetNoOfCols_Image)(/*[in]*/ long* image, /*[out,retval]*/ long* cols);
    STDMETHOD(GetNoOfRows_Image)(/*[in]*/ long* image, /*[out,retval]*/ long* rows);
    STDMETHOD(GetPixel_Image)(/*[in]*/ long* image, /*[in]*/ long row, /*[in]*/ long col, /*[out,retval]*/ VARIANT* pixel);
    STDMETHOD(giftocvip)(/*[in]*/ BSTR* filename, /*[in]*/ long* unused, /*[in]*/ long image_number, /*[in]*/ long verbose);
    STDMETHOD(Glr_Compress)(/*[in]*/ BSTR* filename, /*[in]*/ long* image, /*[in]*/ long window_size);
    STDMETHOD(Glr_Decompress)(/*[in]*/ BSTR* filename, /*[out,retval]*/ long* result);
    STDMETHOD(Gray_Binary)(/*[in]*/ long* image, /*[in]*/ int direction, /*[out,retval]*/ long* result);
    STDMETHOD(Gray_Linear)(/*[in]*/ long* image, /*[in]*/ double start, /*[in]*/ double end, /*[in]*/ double new_start, /*[in]*/ double slope, /*[in]*/ int oor_handling, /*[in]*/ int band, /*[out,retval]*/ long* result);
    STDMETHOD(Gray_Multiplication)(/*[in]*/ long* image, /*[in]*/ float ratio, /*[in]*/ long byte_clipping, /*[out,retval]*/ long* result);
    STDMETHOD(Gray_Multiply)(/*[in]*/ long* image, /*[in]*/ float ratio, /*[out,retval]*/ long* result);
    STDMETHOD(Gray_Multiply2)(/*[in]*/ long* image, /*[in]*/ float ratio, /*[out,retval]*/ long* result);
    STDMETHOD(Gray_Quant_Segment)(/*[in]*/ long* image, /*[in]*/ long gray_levels, /*[out,retval]*/ long* result);
    STDMETHOD(Graylevel_Quant)(/*[in]*/ long* image, /*[in]*/ long gray_levels, /*[in]*/ long choice, /*[out,retval]*/ long* result);
    STDMETHOD(Graylevel_Remap)(/*[in]*/ long* image, /*[in]*/ long r_selection, /*[in]*/ long g_selection, /*[in]*/ long b_selection, /*[out,retval]*/ long* result);
    STDMETHOD(GVFSnake_Segment)(/*[in]*/ long* image, /*[in]*/ long* coordinates, /*[in]*/ long iterations, /*[in]*/ double alpha, /*[in]*/ double beta, /*[in]*/ double kappa, /*[out,retval]*/ long* result);
    STDMETHOD(H_image)(/*[in]*/ long mask_type, /*[in]*/ long height, /*[in]*/ long width, /*[out,retval]*/ long* result);
    STDMETHOD(Haar_Transform)(/*[in]*/ long* image, /*[in]*/ long direction, /*[in]*/ long blocksize, /*[out,retval]*/ long* result);
    STDMETHOD(Harmonic_Filter)(/*[in]*/ long* image, /*[in]*/ long masksize, /*[out,retval]*/ long* result);
    STDMETHOD(Harris_Corner_Filter)(/*[in]*/ long* image, /*[in]*/ float alpha, /*[in]*/ long threshold, /*[in]*/ long border, /*[in]*/ float dmin, /*[out,retval]*/ long* result);
    STDMETHOD(High_Freq_Emphasis)(/*[in]*/ long* image, /*[in]*/ long blocksize, /*[in]*/ long keepdc, /*[in]*/ long cutoff, /*[in]*/ double alpha, /*[in]*/ long filter_order, /*[out,retval]*/ long* result);
    STDMETHOD(Highboost)(/*[in]*/ long* image, /*[in]*/ long masksize, /*[in]*/ long center_value, /*[in]*/ long add2original, /*[out,retval]*/ long* result);
    STDMETHOD(HighFreq_Emphasis)(/*[in]*/ long* image, /*[in]*/ long xform, /*[in]*/ long cutoff, /*[in]*/ long filter_order, /*[in]*/ double offset, /*[in]*/ long keepdc, /*[out,retval]*/ long* result);
    STDMETHOD(Highpass_Spatial)(/*[in]*/ long* image, /*[in]*/ long add2original, /*[out,retval]*/ long* result);
    STDMETHOD(Hist_Feature)(/*[in]*/ long* image, /*[in]*/ long* labeled_image, /*[in]*/ long row, /*[in]*/ long col, /*[out,retval]*/ VARIANT* features);
    STDMETHOD(Hist_Slide)(/*[in]*/ long* image, /*[in]*/ int slide, /*[out,retval]*/ long* result);
    STDMETHOD(Hist_Spec)(/*[in]*/ long* image, /*[in]*/ BSTR* r_histogram, /*[in]*/ BSTR* g_histogram, /*[in]*/ BSTR* b_histogram, /*[out,retval]*/ long* result);
    STDMETHOD(Hist_Stretch)(/*[in]*/ long* image, /*[in]*/ int low_limit, /*[in]*/ int high_limit, /*[in]*/ float low_clip, /*[in]*/ float high_clip, /*[out,retval]*/ long* result);
	STDMETHOD(Hist_Thresh_Gray)(/*[in]*/ long* image, /*[in]*/ float tore, /*[out,retval]*/ long* result);
    STDMETHOD(Hist_Thresh_Segment)(/*[in]*/ long* image,/*[in]*/ float tore, /*[out,retval]*/ long* result);
    STDMETHOD(Histeq)(/*[in]*/ long* image, /*[in]*/ int band, /*[out,retval]*/ long* result);
    STDMETHOD(Histogram_Spec)(/*[in]*/ long* image, /*[in]*/ double* histogram, /*[out,retval]*/ long* result);
    STDMETHOD(History_Add)(/*[in]*/ long* image, /*[in]*/ long* history);
    STDMETHOD(History_Check)(/*[in]*/ long* image, /*[in]*/ int program, /*[out,retval]*/ long* result);
    STDMETHOD(History_Copy)(/*[in]*/ long* source, /*[in]*/ long* destination);
    STDMETHOD(history_create)(/*[in]*/ long prog, /*[in]*/ long type, /*[in]*/ float value, /*[out,retval]*/ long* result);
    STDMETHOD(history_create2)(/*[in]*/ long prog, /*[in]*/ long type, /*[in]*/ int value1, /*[in]*/ int value2, /*[out,retval]*/ long* result);
    STDMETHOD(History_Delete_Program)(/*[in]*/ long* image, /*[in]*/ int program, /*[out,retval]*/ long* result);
    STDMETHOD(History_Get)(/*[in]*/ long* image, /*[in]*/ int program, /*[out,retval]*/ long* result);
    STDMETHOD(History_get_data)(/*[in]*/ long* history, /*[in]*/ int program, /*[out,retval]*/ long* result);
    STDMETHOD(History_get_data2)(/*[in]*/ long* history, /*[in]*/ int program, /*[in]*/ int index, /*[out,retval]*/ long* result);
    STDMETHOD(Homomorphic)(/*[in]*/ long* image, /*[in]*/ double upper_limit, /*[in]*/ double lower_limit, /*[in]*/ long cutoff, /*[in]*/ long add2original, /*[out,retval]*/ long* result);
    STDMETHOD(Horizontal_Flip)(/*[in]*/ long* image, /*[out,retval]*/ long* result);
    STDMETHOD(Hough_Filter)(/*[in]*/ long* image, /*[in]*/ BSTR* image_name, /*[in]*/ BSTR* angles_of_interest, /*[in]*/ long threshold, /*[in]*/ long connection_distance, /*[in]*/ long interactive, /*[in]*/ long delta_length, /*[in]*/ long segment_length, /*[in]*/ long intermediate_result, /*[out,retval]*/ long* result);
    STDMETHOD(Huf_Compress)(/*[in]*/ BSTR* filename, /*[in]*/ long* image);
    STDMETHOD(Huf_Decompress)(/*[in]*/ BSTR* filename, /*[out,retval]*/ long* result);
    STDMETHOD(Idct_Transform)(/*[in]*/ long* image, /*[in]*/ long blocksize, /*[out,retval]*/ long* result);
    STDMETHOD(Ideal_Band_Pass)(/*[in]*/ long* image, /*[in]*/ long blocksize, /*[in]*/ long keepdc, /*[in]*/ long inner_cutoff, /*[in]*/ long outer_cutoff, /*[out,retval]*/ long* result);
    STDMETHOD(Ideal_Band_Reject)(/*[in]*/ long* image, /*[in]*/ long blocksize, /*[in]*/ long keepdc, /*[in]*/ long inner_cutoff, /*[in]*/ long outer_cutoff, /*[out,retval]*/ long* result);
    STDMETHOD(Ideal_High)(/*[in]*/ long* image, /*[in]*/ long blocksize, /*[in]*/ long keepdc, /*[in]*/ long cutoff, /*[out,retval]*/ long* result);
    STDMETHOD(Ideal_Low)(/*[in]*/ long* image, /*[in]*/ long blocksize, /*[in]*/ long keepdc, /*[in]*/ long cutoff, /*[out,retval]*/ long* result);
    STDMETHOD(Ifft_Transform)(/*[in]*/ long* image, /*[in]*/ long blocksize, /*[out,retval]*/ long* result);
    STDMETHOD(Igs_Segment)(/*[in]*/ long* image, /*[in]*/ long gray_levels, /*[out,retval]*/ long* result);
    STDMETHOD(Improved_Mmse_Filter)(/*[in]*/ long* image, /*[in]*/ float threshold, /*[in]*/ long kernel_size, /*[in]*/ float noise_variance, /*[out,retval]*/ long* result);
    STDMETHOD(Input_Mesh)(/*[in]*/ long* points, /*[out,retval]*/ long* result);
    STDMETHOD(Intensity_Slicing)(/*[in]*/ long* image, /*[in]*/ long* lookup_table, /*[in]*/ long options, /*[out,retval]*/ long* result);
    STDMETHOD(Inverse_Xformfilter)(/*[in]*/ long* degr_image, /*[in]*/ long* degr_fn, /*[in]*/ long max_gain, /*[in]*/ double cutoff, /*[out,retval]*/ long* result);
    STDMETHOD(Ipct)(/*[in]*/ long* image, /*[in]*/ long ignore_background, /*[out,retval]*/ long* result);
    STDMETHOD(Irregular)(/*[in]*/ long* labeled_image, /*[in]*/ int row, /*[in]*/ int col, /*[out,retval]*/ double* result);
    STDMETHOD(Jaccard_Index)(/*[in]*/long* image1, /*[in]*/long* image2, /*[out,retval]*/VARIANT* error_values);
    STDMETHOD(Jp2_Decoder)(/*[in]*/ BSTR* filename, /*[out,retval]*/ long* result);
    STDMETHOD(Jp2_Encoder)(/*[in]*/ BSTR* filename, /*[in]*/ long* image, /*[in]*/ int rate, /*[in]*/ int quality, /*[in]*/ int layers, /*[in]*/ int blocksize);
    STDMETHOD(Jpg_Compress)(/*[in]*/ BSTR* filename, /*[in]*/ long* image, /*[in]*/ int quality, /*[in]*/ long grayscale, /*[in]*/ long optimize, /*[in]*/ int smooth, /*[in]*/ long verbose, /*[in]*/ BSTR* qtablesFile);
    STDMETHOD(Jpg_Decompress)(/*[in]*/ BSTR* filename, /*[in]*/ int num_colors, /*[in]*/ long blocksmooth, /*[in]*/ long grayscale, /*[in]*/ long nodither, /*[in]*/ long verbose, /*[out,retval]*/ long* result);
    STDMETHOD(Jpgtocvip)(/*[in]*/ BSTR* filename, /*[in]*/ int num_colors, /*[in]*/ long blocksmooth, /*[in]*/ long grayscale, /*[in]*/ long nodither, /*[in]*/ long verbose, /*[out,retval]*/ long* result);
    STDMETHOD(K_Nearest_Neighbor)(/*[in]*/ BSTR* test_set, /*[in]*/ BSTR* training_set, /*[in]*/ BSTR* outputfile, /*[in]*/ int normalization, /*[in]*/ int distance_measure, /*[in]*/ int k, /*[in]*/ float s_min, /*[in]*/ float s_max, /*[in]*/ float r_softmax, /*[in]*/ float r_minkowski, /*[out,retval]*/ long* error);
    STDMETHOD(Krisch_Filter)(/*[in]*/ long* image, /*[in]*/ long* dir_image, /*[in]*/ long filter_type, /*[in]*/ long kernel_size, /*[in]*/ long keepdc, /*[in]*/ long threshold, /*[out,retval]*/ long* mag_image);
    STDMETHOD(Kuwahara_Filter)(/*[in]*/ long* image, /*[in]*/ long masksize, /*[out,retval]*/ long* result);
    STDMETHOD(Label)(/*[in]*/ long* image, /*[out,retval]*/ long* result);
    STDMETHOD(Laws_Texture_Feature)(/*[in]*/ long* image, /*[in]*/ long* labeled_image, /*[in]*/ int row, /*[in]*/ int col, /*[in]*/ int window_size, /*[in]*/ int vector1, /*[in]*/ int vector2, /*[out,retval]*/ VARIANT* features);
    STDMETHOD(Least_Squares)(/*[in]*/ long* degr_image, /*[in]*/ long* degr_fn, /*[in]*/ long* smoothness_fn, /*[in]*/ double gamma, /*[in]*/ long max_gain, /*[in]*/ long cutoff, /*[out,retval]*/ long* result);
    STDMETHOD(Local_Adaptive_Zoom)(/*[in]*/ long* image, /*[out,retval]*/ long* result);
    STDMETHOD(Local_Histeq)(/*[in]*/ long* image, /*[in]*/ int blocksize, /*[in]*/ int band, /*[out,retval]*/ long* result);
    STDMETHOD(Log_Ace_Filter)(/*[in]*/ long* image, /*[in]*/ long masksize, /*[in]*/ double local_mean, /*[in]*/ double local_gain, /*[out,retval]*/ long* result);
    STDMETHOD(Log_Remap)(/*[in]*/ long* image, /*[in]*/ long band, /*[out,retval]*/ long* result);
    STDMETHOD(LogMap_Image)(/*[in]*/ long* image, /*[in]*/ int band, /*[out,retval]*/ long* result);
    STDMETHOD(Lum_Average)(/*[in]*/ long* image, /*[out,retval]*/ long* result);
    STDMETHOD(Luminance_Image)(/*[in]*/ long* image, /*[out,retval]*/ long* result);
    STDMETHOD(Make_Histogram)(/*[in]*/ double* histogram, /*[in]*/ long image_format, /*[in]*/ long color_format, /*[in]*/ long bands, /*[out,retval]*/ long* result);
    STDMETHOD(Marr_Hildreth_Filter)(/*[in]*/ long* image, /*[in]*/ float sigma, /*[in]*/ int threshold, /*[out,retval]*/ long* result);
    STDMETHOD(Maximum_Filter)(/*[in]*/ long* image, /*[in]*/ long masksize, /*[out,retval]*/ long* result);
    STDMETHOD(Mean_Filter)(/*[in]*/ long* image, /*[in]*/ long masksize, /*[out,retval]*/ long* result);
    STDMETHOD(Median_Cut_Segment)(/*[in]*/ long* image, /*[in]*/ long num_colors, /*[in]*/ long ignore_background, /*[in]*/ long r_background, /*[in]*/ long g_background, /*[in]*/ long b_background, /*[out,retval]*/ long* result);
    STDMETHOD(Median_Filter)(/*[in]*/ long* image, /*[in]*/ long masksize, /*[out,retval]*/ long* result);
    STDMETHOD(Mesh_To_File)(/*[in]*/ BSTR* filename, /*[in]*/ long* mesh);
    STDMETHOD(Mesh_Warping)(/*[in]*/ long* image, /*[in]*/ long* mesh, /*[in]*/ long interpolation_method, /*[out,retval]*/ long* result);
    STDMETHOD(Mesh_WarpingRI)(/*[in]*/ long* image, /*[in]*/ long* mesh, /*[in]*/ long interpolation_method, /*[in]*/ long zero_missing, /*[out,retval]*/ long* result);
    STDMETHOD(Midpoint_Filter)(/*[in]*/ long* image, /*[in]*/ long masksize, /*[out,retval]*/ long* result);
    STDMETHOD(Minimum_Filter)(/*[in]*/ long* image, /*[in]*/ long masksize, /*[out,retval]*/ long* result);
    STDMETHOD(Mmse_Filter)(/*[in]*/ long* image, /*[in]*/ double noise_variance, /*[in]*/ long kernel_size, /*[out,retval]*/ long* result);
    STDMETHOD(Moravec_Corner_Filter)(/*[in]*/ long* image, /*[in]*/ float threshold, /*[out,retval]*/ long* result);
    STDMETHOD(Morph_Hitmiss)(/*[in]*/ long* binary_image, /*[in]*/ long masksize, /*[in]*/ double* mask_values, /*[out,retval]*/ long* result);
    STDMETHOD(Morph_Skeleton)(/*[in]*/ long* binary_image, /*[in]*/ long masksize, /*[in]*/ double* mask_values, /*[in]*/ long iterations, /*[in]*/ long four_eight_mask, /*[in]*/ long method, /*[out,retval]*/ long* result);
    STDMETHOD(Morph_Thinning)(/*[in]*/ long* binary_image, /*[in]*/ long masksize, /*[in]*/ double* mask_values, /*[out,retval]*/ long* result);
    STDMETHOD(MorphClose)(/*[in]*/ long* image, /*[in]*/ int kernel_type, /*[in]*/ int kernel_size, /*[in]*/ int height, /*[in]*/ int width, /*[out,retval]*/ long* result);
	STDMETHOD(MorphClose_Image)(/*[in]*/ long* image, /*[in]*/ long* matrix, /*[in]*/ int userOrg, /*[in]*/ int x, /*[in]*/ int y,  /*[in]*/ int size,/*[out,retval]*/ long* result);
	STDMETHOD(MorphDilate)(/*[in]*/ long* image, /*[in]*/ int kernel_type, /*[in]*/ int kernel_size, /*[in]*/ int height, /*[in]*/ int width, /*[out,retval]*/ long* result);
	STDMETHOD(MorphDilate_Image)(/*[in]*/ long* image, /*[in]*/ int* matrix, /*[in]*/ int userOrg, /*[in]*/ int x, /*[in]*/ int y,  /*[in]*/ int size,/*[out,retval]*/ long* result);
    STDMETHOD(MorphErode)(/*[in]*/ long* image, /*[in]*/ int kernel_type, /*[in]*/ int kernel_size, /*[in]*/ int height, /*[in]*/ int width, /*[out,retval]*/ long* result);
	STDMETHOD(MorphErode_Image)(/*[in]*/ long* image, /*[in]*/ long* matrix, /*[in]*/ int userOrg, /*[in]*/ int x, /*[in]*/ int y,  /*[in]*/ int size,/*[out,retval]*/ long* result);
	STDMETHOD(Morpho)(/*[in]*/ long* image, /*[in]*/ BSTR* surrounds_string, /*[in]*/ long rotation, /*[in]*/ long boolfunc, /*[in]*/ long connectedness, /*[in]*/ long iterations, /*[in]*/ long fields, /*[out,retval]*/ long* result);
    STDMETHOD(Morpho_com)(/*[in]*/ long* image, /*[in]*/ BSTR* surrounds_string, /*[in]*/ long rotation, /*[in]*/ long boolfunc, /*[in]*/ long iterations, /*[in]*/ long subfields, /*[in]*/ long unused, /*[out,retval]*/ long* result);
    STDMETHOD(MorphOpen)(/*[in]*/ long* image, /*[in]*/ int kernel_type, /*[in]*/ int kernel_size, /*[in]*/ int height, /*[in]*/ int width, /*[out,retval]*/ long* result);
	STDMETHOD(MorphOpen_Image)(/*[in]*/ long* image, /*[in]*/ long* matrix, /*[in]*/ int userOrg, /*[in]*/ int x, /*[in]*/ int y,  /*[in]*/ int size,/*[out,retval]*/ long* result);
	STDMETHOD(Multi_Resolution_Segment)(/*[in]*/ long* image, /*[in]*/ long homogeneity_test, /*[in]*/ double param1, /*[in]*/ double param2, /*[in]*/ long run_PCT, /*[out,retval]*/ long* result);
    STDMETHOD(Multiply_Image)(/*[in]*/ long* image1, /*[in]*/ long* image2, /*[out,retval]*/ long* result);
    STDMETHOD(Nearest_Centroid)(/*[in]*/ BSTR* test_set, /*[in]*/ BSTR* training_set, /*[in]*/ BSTR* outputfile, /*[in]*/ int normalization, /*[in]*/ int distance_measure, /*[in]*/ float s_min, /*[in]*/ float s_max, /*[in]*/ float r_softmax, /*[in]*/ float r_minkowski, /*[out,retval]*/ long* error);
    STDMETHOD(Nearest_Neighbor)(/*[in]*/ BSTR* test_set, /*[in]*/ BSTR* training_set, /*[in]*/ BSTR* outputfile, /*[in]*/ int normalization, /*[in]*/ int distance_measure, /*[in]*/ float s_min, /*[in]*/ float s_max, /*[in]*/ float r_softmax, /*[in]*/ float r_minkowski, /*[out,retval]*/ long* error);
    STDMETHOD(Neg_Exp_Noise)(/*[in]*/ long* image, /*[in]*/ double variance, /*[out,retval]*/ long* result);
    STDMETHOD(New_Image)(/*[in]*/ long image_format, /*[in]*/ long color_space, /*[in]*/ int bands, /*[in]*/ int height, /*[in]*/ int width, /*[in]*/ long datatype, /*[in]*/ long data_format, /*[out,retval]*/ long* result);
    STDMETHOD(Nonfft_Xformfilter)(/*[in]*/ long* image, /*[in]*/ long blocksize, /*[in]*/ long keepdc, /*[in]*/ long filter_type, /*[in]*/ long p1, /*[in]*/ double p2, /*[in]*/ long filter_order, /*[out,retval]*/ long* result);
    STDMETHOD(Not_Image)(/*[in]*/ long* image, /*[out,retval]*/ long* result);
    STDMETHOD(Notch)(/*[in]*/ BSTR* filename, /*[in]*/ long* cols, /*[in]*/ long* rows, /*[in]*/ long* radius, /*[in]*/ long* image, /*[in]*/ long num_points, /*[in]*/ long interactive, /*[out,retval]*/ long* result);
    STDMETHOD(Object_Crop)(/*[in]*/ long* image, /*[in]*/ long* coordinates, /*[in]*/ long format, /*[in]*/ long r_value, /*[in]*/ long g_value, /*[in]*/ long b_value, /*[out,retval]*/ long* result);
    STDMETHOD(Open_Consol_Redirect_Output)();
    STDMETHOD(Or_Image)(/*[in]*/ long* image1, /*[in]*/ long* image2, /*[out,retval]*/ long* result);
    STDMETHOD(Orientation)(/*[in]*/ long* labeled_image, /*[in]*/ int row, /*[in]*/ int col, /*[out,retval]*/ long* orientation);
    STDMETHOD(Otsu_Segment)(/*[in]*/ long* image, /*[out,retval]*/ long* result);
    STDMETHOD(Overlap_Coef)(/*[in]*/long* image1, /*[in]*/long* image2, /*[out,retval]*/VARIANT* error_values);
    STDMETHOD(Param_AD_Filter)(/*[in]*/ long* image, /*[in]*/ long iterations, /*[in]*/ long speed, /*[in]*/ long edge_height, /*[in]*/ long blocksize, /*[out,retval]*/ long* result);
    STDMETHOD(Parametric_Wiener)(/*[in]*/ long* degr_image, /*[in]*/ long* degr_fn, /*[in]*/ long* psd_noise, /*[in]*/ long* psd_orig, /*[in]*/ double gamma, /*[in]*/ long max_gain, /*[in]*/ long cutoff, /*[out,retval]*/ long* result);
    STDMETHOD(Pct)(/*[in]*/ long* image, /*[in]*/ long ignore_background, /*[in]*/ double* background, /*[out,retval]*/ long* result);
    STDMETHOD(Pct_Color)(/*[in]*/ long* image, /*[in]*/ long ignore_background, /*[in]*/ double* background, /*[in]*/ long choice, /*[out,retval]*/ long* result);
    STDMETHOD(Pct_Median_Segment)(/*[in]*/ long* image, /*[in]*/ long num_colors, /*[out,retval]*/ long* result);
    STDMETHOD(Perimeter)(/*[in]*/ long* labeled_image, /*[in]*/ int row, /*[in]*/ int col, /*[out,retval]*/ long* perimeter);
    STDMETHOD(Pngtocvip)(/*[in]*/ BSTR* filename, /*[out,retval]*/ long* result);
    STDMETHOD(Power_Spect_Eq)(/*[in]*/ long* degr_image, /*[in]*/ long* degr_fn, /*[in]*/ long* psd_noise, /*[in]*/ long* psd_orig, /*[in]*/ long max_gain, /*[in]*/ long cutoff, /*[out,retval]*/ long* result);
    STDMETHOD(Pratt_Merit)(/*[in]*/ long* image1, /*[in]*/ long* image2, /*[in]*/ double scale_factor, /*[out,retval]*/ double* result);
    STDMETHOD(Prewitt_Filter)(/*[in]*/ long* image, /*[in]*/ long* dir_image, /*[in]*/ long filter_type, /*[in]*/ long kernel_size, /*[in]*/ long keepdc, /*[in]*/ long threshold, /*[out,retval]*/ long* mag_image);
    STDMETHOD(Print_Image)(/*[in]*/ int dc, /*[in]*/ long* image);
    STDMETHOD(Projection)(/*[in]*/ long* labeled_image, /*[in]*/ int row, /*[in]*/ int col, /*[in]*/ int height, /*[in]*/ int width, /*[out,retval]*/ VARIANT* projections);
    STDMETHOD(Pseudo_Remap)(/*[in]*/ long* image, /*[in]*/ long* lookup_table, /*[out,retval]*/ long* result);
    STDMETHOD(Pseudocol_Freq)(/*[in]*/ long* image, /*[in]*/ int low_cutoff, /*[in]*/ int high_cutoff, /*[in]*/ int lowpass_band, /*[in]*/ int bandpass_band, /*[in]*/ int highpass_band, /*[out,retval]*/ long* result);
    STDMETHOD(Raster_Deblur_Filter)(/*[in]*/ long* image, /*[out,retval]*/ long* result);
    STDMETHOD(Rayleigh_Noise)(/*[in]*/ long* image, /*[in]*/ double variance, /*[out,retval]*/ long* result);
    STDMETHOD(Read_Image)(/*[in]*/ BSTR* filename, /*[out,retval]*/ long* result);
    STDMETHOD(Remap_Image)(long* image, long datatype, long dmin, long dmax, long* result);
    STDMETHOD(REMAPP)(long* image, long datatype, long dmin, long dmax, long* result);
    STDMETHOD(Render_DisplayImage)(/*[in]*/ long window_dc, /*[in]*/ long* image, /*[out,retval]*/ long* memory_dc);
    STDMETHOD(Rms_Error)(/*[in]*/ long* image1, /*[in]*/ long* image2, /*[out,retval]*/ VARIANT* rms_values);
    STDMETHOD(Robinson_Filter)(/*[in]*/ long* image, /*[in]*/ long* dir_image, /*[in]*/ long mask_type, /*[in]*/ long masksize, /*[in]*/ long keepdc, /*[in]*/ long threshold, /*[out,retval]*/ long* mag_image);
    STDMETHOD(Rotate)(/*[in]*/ long* image, /*[in]*/ float degrees, /*[out,retval]*/ long* result);
    STDMETHOD(Rst_invariant)(/*[in]*/ long* labeled_image, /*[in]*/ long row, /*[in]*/ long col, /*[out,retval]*/ VARIANT* features);
    STDMETHOD(Save_Compressed_Data)(/*[in]*/ long* image, /*[in]*/ BSTR* filename);
    STDMETHOD(Sct_Split_Segment)(/*[in]*/ long* image, /*[in]*/ long A_split, /*[in]*/ long B_split, /*[out,retval]*/ long* result);
    STDMETHOD(Set_Console)(/*[in]*/ long unused);
    STDMETHOD(Sharpen_I)(/*[in]*/ long* image, /*[in]*/ long remap, /*[in]*/ long mask_type, /*[in]*/ long masksize, /*[in]*/ float low_clip, /*[in]*/ float high_clip, /*[in]*/ long add2original, /*[out,retval]*/ long* result);
    STDMETHOD(Sharpen_II)(/*[in]*/ long* image, /*[in]*/ long add2original, /*[out,retval]*/ long* result);
	STDMETHOD(Sharpen_III)(/*[in]*/ long* image, /*[in]*/ long add2original, /*[out,retval]*/ long* result);
    STDMETHOD(Shen_Castan_Filter)(/*[in]*/ long* image, /*[in]*/ double smoothing_factor, /*[in]*/ long window_size, /*[in]*/ double low_threshold, /*[in]*/ double high_threshold, /*[in]*/ long thin_factor, /*[in]*/ long* intermediate_image, /*[out,retval]*/ long* result);
    STDMETHOD(Show_DisplayImage)(/*[in]*/ long window_dc, /*[in]*/ long memory_dc, /*[in]*/ long window_width, /*[in]*/ long window_height, /*[in]*/ long memory_width, /*[in]*/ long memory_height);
    STDMETHOD(Show_Image)(/*[in]*/ int dc, /*[in]*/ int x, /*[in]*/ int y, /*[in]*/ long* image);
    STDMETHOD(Show_Image_Ex)(/*[in]*/ int window_dc, /*[in]*/ long* memory_dc, /*[in]*/ int x, /*[in]*/ int y, /*[in]*/ long* image);
    STDMETHOD(Shrink)(/*[in]*/ long* image, /*[in]*/ float factor, /*[out,retval]*/ long* result);
    STDMETHOD(Simple_Wiener)(/*[in]*/ long* degr_image, /*[in]*/ long* degr_fn, /*[in]*/ double k, /*[out,retval]*/ long* result);
    STDMETHOD(Single_Filter)(/*[in]*/ long* image, /*[in]*/ double sizing_factor_x, /*[in]*/ double sizing_factor_y, /*[in]*/ long centerx, /*[in]*/ long centery, /*[in]*/ double rotation, /*[in]*/ double beta, /*[in]*/ long kernel_size, /*[in]*/ double* kernel_data, /*[in]*/ long choice, /*[out,retval]*/ long* result);
    STDMETHOD(Snr)(/*[in]*/ long* image1, /*[in]*/ long* image2, /*[out,retval]*/ VARIANT* snr_values);
    STDMETHOD(Sobel_Filter)(/*[in]*/ long* image, /*[in]*/ long* dir_image, /*[in]*/ long filter_type, /*[in]*/ long kernel_size, /*[in]*/ long keepdc, /*[in]*/ long threshold, /*[out,retval]*/ long* mag_image);
    STDMETHOD(Spatial_Quant)(/*[in]*/ long* image, /*[in]*/ int rows, /*[in]*/ int cols, /*[in]*/ int method, /*[out,retval]*/ long* result);
    STDMETHOD(Spec_Hist_Image)(/*[in]*/ long* image, /*[in]*/ BSTR* r_histogram, /*[in]*/ BSTR* g_histogram, /*[in]*/ BSTR* b_histogram, /*[out,retval]*/ long* result);
    STDMETHOD(Specify_Filter)(/*[in]*/ long* image, /*[in]*/ long mask_height, /*[in]*/ long mask_width, /*[in]*/ double* mask_values, /*[in]*/ int normalization, /*[out,retval]*/ long* result);
    STDMETHOD(Speckle_Noise)(/*[in]*/ long* image, /*[in]*/ double psalt, /*[in]*/ double ppepper, /*[out,retval]*/ long* result);
    STDMETHOD(Spectral_Feature)(/*[in]*/ long* image, /*[in]*/ long* labeled_image, /*[in]*/ long rings, /*[in]*/ long sectors, /*[in]*/ long row, /*[in]*/ long col, /*[out,retval]*/ VARIANT* features);
    STDMETHOD(Split_Merge_Segment)(/*[in]*/ long* image, /*[in]*/ long level, /*[in]*/ long homogeneity_test, /*[in]*/ double param1, /*[in]*/ double param2, /*[in]*/ long run_PCT, /*[out,retval]*/ long* result);
    STDMETHOD(Subtract_Image)(/*[in]*/ long* image1, /*[in]*/ long* image2, /*[out,retval]*/ long* result);
    STDMETHOD(TextureFeature)(/*[in]*/ long* image, /*[in]*/ long* labeled_image, /*[in]*/ long row, /*[in]*/ long col, /*[in]*/ long distance, /*[in]*/ long bitmask, /*[out,retval]*/ VARIANT* features);
    STDMETHOD(TextureFeature2)(/*[in]*/ long* image, /*[in]*/ long* labeled_image, /*[in]*/ long band, /*[in]*/ long row, /*[in]*/ long col, /*[in]*/ long distance, /*[in]*/ long energy, /*[in]*/ long inertia, /*[in]*/ long correlation, /*[in]*/ long inv_diff, /*[in]*/ long entropy, /*[in]*/ long include_zero_pairs, /*[out,retval]*/ VARIANT* features);
    STDMETHOD(Thinness)(/*[in]*/ long* labeled_image, /*[in]*/ int row, /*[in]*/ int col, /*[out,retval]*/ double* thinness);
    STDMETHOD(Threshold_Segment)(/*[in]*/ long* image, /*[in]*/ long threshold, /*[in]*/ long byte_remap, /*[out,retval]*/ long* result);
    STDMETHOD(Tifftocvip)(/*[in]*/ BSTR* filename, /*[in]*/ int verbose, /*[out,retval]*/ long* result);
    STDMETHOD(Tile_by_name)(/*[in]*/ BSTR* filename);
    STDMETHOD(Transform_Compression)(/*[in]*/ long* image, /*[in]*/ BSTR* filename, /*[in]*/ BSTR* quantfile, /*[in]*/ long color_space, /*[in]*/ long xform, /*[in]*/ long basis, /*[in]*/ long blocksize, /*[in]*/ long quantization, /*[in]*/ long use_quant_table, /*[in]*/ long use_vector_quant, /*[in]*/ long datatype, /*[in]*/ long remap_type, /*[in]*/ long keepdc, /*[out,retval]*/ long* result);
    STDMETHOD(Transform_Sharpen)(/*[in]*/ long* image, /*[in]*/ long xform, /*[in]*/ long cutoff, /*[in]*/ long filter_type, /*[in]*/ long filter_order, /*[in]*/ long keepdc, /*[in]*/ long add2original, /*[out,retval]*/ long* result);
    STDMETHOD(Transform_Smoothing)(/*[in]*/ long* image, /*[in]*/ long xform, /*[in]*/ long cutoff, /*[in]*/ long filter_type, /*[in]*/ long filter_order, /*[in]*/ long keepdc, /*[out,retval]*/ long* result);
    STDMETHOD(Translate)(/*[in]*/ long* image, /*[in]*/ long wrap, /*[in]*/ int row_offset, /*[in]*/ int col_offset, /*[in]*/ int rows, /*[in]*/ int cols, /*[in]*/ int row_slide, /*[in]*/ int col_slide, /*[in]*/ float fill_val, /*[out,retval]*/ long* result);
    STDMETHOD(Uniform_Noise)(/*[in]*/ long* image, /*[in]*/ double variance, /*[in]*/ double mean, /*[out,retval]*/ long* result);
    STDMETHOD(Unsharp_Filter)(/*[in]*/ long* image, /*[in]*/ long lower_limit, /*[in]*/ long upper_limit, /*[in]*/ double low_clip, /*[in]*/ double high_clip, /*[out,retval]*/ long* result);
    STDMETHOD(Vertical_Flip)(/*[in]*/ long* image, /*[out,retval]*/ long* result);
    STDMETHOD(Vq_Compress)(/*[in]*/ long* image, /*[in]*/ BSTR* filename, /*[in]*/ long use_file_codebook, /*[in]*/ long use_fixed_codebook, /*[in]*/ double error_threshold, /*[in]*/ BSTR* codebook_filename, /*[in]*/ long num_entries, /*[in]*/ long vector_height, /*[in]*/ long vector_width, /*[out,retval]*/ long* result);
    STDMETHOD(Vq_Decompress)(/*[in]*/ BSTR* filename, /*[out,retval]*/ long* result);
    STDMETHOD(Walhad_Transform)(/*[in]*/ long* image, /*[in]*/ long xform, /*[in]*/ long blocksize, /*[out,retval]*/ long* result);
    STDMETHOD(Watershed_Segment)(/*[in]*/ long* image, /*[in]*/ int merge_result, /*[in]*/ float threshold, /*[out,retval]*/ long* result);
    STDMETHOD(Wavdaub4_Transform)(/*[in]*/ long* image, /*[in]*/ long direction, /*[in]*/ long low_band, /*[out,retval]*/ long* result);
    STDMETHOD(Wavhaar_Transform)(/*[in]*/ long* image, /*[in]*/ long direction, /*[in]*/ long low_band, /*[out,retval]*/ long* result);
    STDMETHOD(Wiener)(/*[in]*/ long* degr_image, /*[in]*/ long* degr_fn, /*[in]*/ long* psd_noise, /*[in]*/ long* psd_orig, /*[in]*/ long max_gain, /*[in]*/ long cutoff, /*[out,retval]*/ long* result);
    STDMETHOD(Write_Image)(/*[in]*/ long* image, /*[in]*/ BSTR* filename, /*[in]*/ long retain_image, /*[in]*/ long run_setup, /*[in]*/ long image_format, /*[in]*/ long verbose);
    STDMETHOD(Write_JPEG_Image)(/*[in]*/ long* image, /*[in]*/ BSTR* filename, /*[in]*/ long retain_image, /*[in]*/ long run_setup, /*[in]*/ long image_format, /*[in]*/ long verbose, /*[in]*/ int ratio);
    STDMETHOD(Xor_Error)(/*[in]*/ long* image1, /*[in]*/ long* image2, /*[out,retval]*/ VARIANT* error_values);
    STDMETHOD(Xor_Image)(/*[in]*/ long* image1, /*[in]*/ long* image2, /*[out,retval]*/ long* result);
    STDMETHOD(Xvq_Compress)(/*[in]*/ long* image, /*[in]*/ long xform, /*[in]*/ long scheme, /*[in]*/ BSTR* filename, /*[in]*/ long output_data_type, /*[in]*/ long remap_type, /*[in]*/ long dc_term_handling, /*[out,retval]*/ long* result);
    STDMETHOD(Xvq_Decompress)(/*[in]*/ BSTR* filename, /*[out,retval]*/ long* result);
    STDMETHOD(Ypmean_Filter)(/*[in]*/ long* image, /*[in]*/ long masksize, /*[in]*/ long p, /*[out,retval]*/ long* result);
    STDMETHOD(Zon_Compress)(/*[in]*/ BSTR* filename, /*[in]*/ long* image, /*[in]*/ int blocksize, /*[in]*/ int xform, /*[in]*/ int mask_type, /*[in]*/ float compression_ratio);
    STDMETHOD(Zon_Decompress)(/*[in]*/ BSTR* filename, /*[out,retval]*/ long* result);
    STDMETHOD(Zon2_Compress)(/*[in]*/ BSTR* filename, /*[in]*/ long* image, /*[in]*/ int blocksize, /*[in]*/ int xform, /*[in]*/ int mask_type, /*[in]*/ float compression_ratio);
    STDMETHOD(Zon2_Decompress)(/*[in]*/ BSTR* filename, /*[out,retval]*/ long* result);
    STDMETHOD(Zoom)(/*[in]*/ long* image, /*[in]*/ int quadrant, /*[in]*/ int col, /*[in]*/ int row, /*[in]*/ int cols, /*[in]*/ int rows, /*[in]*/ float factor_requested, /*[out,retval]*/ long* result);
    STDMETHOD(Zvl_Compress)(/*[in]*/ BSTR* filename, /*[in]*/ long* image);
    STDMETHOD(Zvl_Decompress)(/*[in]*/ BSTR* filename, /*[out,retval]*/ long* result);
};

OBJECT_ENTRY_AUTO(__uuidof(CVIPTools), CCVIPtools)
