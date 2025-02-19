#ifndef _CVIP_DISPLAY
#define _CVIP_DISPLAY 

#ifdef __cplusplus
extern "C"{
#endif

    STDMETHODIMP __Render_DisplayImage(long dc, long* image, long* memory_dc);
    STDMETHODIMP __Show_DisplayImage(long window_dc, long memory_dc, long window_width, long window_height, long memory_width, long memory_height);

#ifdef __cplusplus
}
#endif
#endif
