#include "CVIPimage.h"

STDMETHODIMP __Render_DisplayImage(long dc, long *image, long *mem_dc)
{
 	HBITMAP hb;
	HDC hdc = (HDC)dc;
 	IMAGE *im;
 	int i, j;
 	int num_cols;
 	int num_rows;

	if((im = (IMAGE*)(*image)) == NULL) return S_OK;

	num_cols = im->bandP[0]->cols;
	num_rows = im->bandP[0]->rows;

 	/*Create Memory Device Context */
 	hb = CreateCompatibleBitmap(hdc, num_cols, num_rows);
 	hdc = CreateCompatibleDC(hdc);
 	SelectObject(hdc, hb);

 	for(i=0; i<num_rows; i++)
	{
 		for(j=0; j<num_cols; j++)
		{
 			switch(im->bands)
			{
 			case 1:
 				SetPixel(hdc, j, i,
						RGB(im->bandP[0]->rptr[i][j],
							im->bandP[0]->rptr[i][j],
							im->bandP[0]->rptr[i][j])
 						);
 				break;

 			case 3:
 				SetPixel(hdc, j, i,
						RGB(im->bandP[0]->rptr[i][j],
							im->bandP[1]->rptr[i][j],
							im->bandP[2]->rptr[i][j])
 						);
 				break;

 			default:
 				break;
 			}
 		}
 	}
 
 	*mem_dc = (long)hdc;
 	DeleteObject(hb);

	return S_OK;
}

STDMETHODIMP __Show_DisplayImage(long windowDC, long memoryDC, long windowWidth, long windowHeight, long memoryWidth, long memoryHeight)
{
   	HDC hdcWindow, hdcMemory, hdcScaled;
   	HBITMAP hbmScaled;
	
	  
	 
 	hdcWindow = (HDC)windowDC;
 	hdcMemory = (HDC)memoryDC;
	
	if(((memoryWidth == windowWidth) && (memoryHeight == windowHeight)) ||
		((windowWidth == 0) && (windowHeight == 0)))
	{
		BitBlt(hdcWindow, 0, 0, memoryWidth, memoryHeight, hdcMemory, 0, 0, SRCCOPY);
	}
	else
	{
		
		
   		hdcScaled = CreateCompatibleDC(hdcWindow);
 		hbmScaled = CreateCompatibleBitmap(hdcWindow, windowWidth, windowHeight);

 		if(hbmScaled == 0) return S_OK;
   		if(!SelectObject(hdcScaled, hbmScaled)) return S_OK;

		SetStretchBltMode(hdcScaled, HALFTONE);
		SetBrushOrgEx(hdcScaled, 0, 0, NULL);
   		StretchBlt(hdcScaled, 0, 0, windowWidth, windowHeight, hdcMemory, 0, 0, memoryWidth, memoryHeight, SRCCOPY);
   		BitBlt(hdcWindow, 0, 0, windowWidth, windowHeight, hdcScaled, 0, 0, SRCCOPY);

 		DeleteObject(hbmScaled);
 		DeleteDC(hdcScaled);
	}
	
	return S_OK;
}
