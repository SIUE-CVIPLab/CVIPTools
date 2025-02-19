// RamViewerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "afxwin.h"
#include "afxdialogex.h"
#include "resource.h"
#include "RamViewerDlg.h"
#include "StatsDlg.h"

extern "C"
{
	Image *condRemap_Image(const Image *imgP, CVIP_TYPE dtype, unsigned min, unsigned max);
	STDMETHODIMP __Render_DisplayImage(long dc, long *image, long *mem_dc);
	STDMETHODIMP __Show_DisplayImage(long windowDC, long memoryDC, long windowWidth, long windowHeight, long memoryWidth, long memoryHeight);
}

// CRamViewerDlg dialog
IMPLEMENT_DYNAMIC(CRamViewerDlg, CDialog)

CRamViewerDlg::CRamViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRamViewerDlg::IDD, pParent)
{
	m_dcMem = NULL;
	m_pdlgStats = NULL;
}

CRamViewerDlg::~CRamViewerDlg()
{
	if (m_pdlgStats != NULL)
	{
		delete(m_pdlgStats);
	}
}

void CRamViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRamViewerDlg, CDialog)
	ON_WM_KEYUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CRamViewerDlg message handlers

char * data_type_string[] = { "BYTE", "SHORT", "INTEGER", "FLOAT", "DOUBLE" };
char * data_format_string[] = { "REAL", "COMPLEX" };
char * image_format_string[] = { "PBM", "PGM", "PPM", "EPS", "TIF", "GIF", "RAS", \
"ITX", "IRIS", "CCC", "BIN", "VIP", "VIP/GLR", "VIP/BTC", "VIP/BRC", "VIP/HUF", \
"VIP/ZVL", "ARITH", "VIP/BTC2", "VIP/BTC3", "VIP/DPC", "VIP/ZON", "VIP/ZON2", \
"SAFVR", "JPEG", "VIP/WVQ", "VIP/FRA", "VIP/VQ", "VIP/XVQ", "VIP/TRCM", \
"PS", "BMP", "JP2", "PNG", NULL };
char * color_format_string[] = { "BINARY", "GRAY_SCALE", "RGB", "HSL", "HSV", \
"SCT", "CCT", "LUV", "LAB", "XYZ", NULL };

BOOL CRamViewerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetWindowPos(&wndNoTopMost,
		0,
		0,
		m_imgDisplay->bandP[0]->cols + 10,
		m_imgDisplay->bandP[0]->rows + 30,
		SWP_NOMOVE);

	SetWindowText(m_Filename);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CRamViewerDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	COLOR_FORMAT color_format;
	FORMAT data_format;
	CVIP_TYPE data_type;
	IMAGE_FORMAT image_format;
	CString msg, s;
	double curr_min, curr_max, min, max;
	int i, num_bands, num_cols, num_rows;
	unsigned imgsize;
	void **imgvecP = NULL;

	switch (nChar)
	{
	case 'q':
	case 'Q':
		OnOK();
		break;
	case 'i':
	case 'I':
		color_format = m_imgDisplay->color_space;
		data_format = m_imgDisplay->bandP[0]->data_format;
		data_type = m_imgDisplay->bandP[0]->data_type;
		image_format = m_imgDisplay->image_format;
		num_bands = m_imgDisplay->bands;
		num_cols = m_imgDisplay->bandP[0]->cols;
		num_rows = m_imgDisplay->bandP[0]->rows;
		imgsize = num_rows * num_cols;

		imgvecP = (void **)malloc(sizeof(void *) * num_bands);

		if (data_format != COMPLEX)
		{
			getBandVector_Image(m_imgDisplay, imgvecP);
		}

		for (i = 0; i<num_bands; i++)
		{
			if (data_format == COMPLEX)
			{
				imgvecP[i] = getImagRow_Image(m_imgDisplay, 0, i);
			}

			curr_min = findMinVal_Vector(imgvecP[i], imgsize, data_type);
			curr_max = findMaxVal_Vector(imgvecP[i], imgsize, data_type);

			if (i == 0)
			{
				min = curr_min;
				max = curr_max;
			}

			if (curr_min < min) min = curr_min;
			if (curr_max > max) max = curr_max;
		}

		free(imgvecP);

		msg.Format("Image Format: %s\r\nColor Format: %s\r\n", image_format_string[image_format], color_format_string[color_format]);
		s.Format("Band #: %d\r\nRow #: %d\r\nCol #: %d\r\n", num_bands, num_rows, num_cols);
		msg += s;
		s.Format("Data Type: %s\r\nData Format: %s\r\n", data_type_string[data_type], data_format_string[data_format]);
		msg += s;
		s.Format("Data Range: %.0f - %.0f\r\n", min, max);
		msg += s;

		MessageBox(msg, m_Filename);
		break;

	default:
		;
	}

	CDialog::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CRamViewerDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_pdlgStats == NULL)
	{
		m_pdlgStats = new CStatsDlg(this);
		m_pdlgStats->Create(IDD_STATSDLG, this);
	}

	RECT rect;
	GetWindowRect(&rect);

	m_pdlgStats->m_strTitle = "";
	m_pdlgStats->UpdateData(FALSE);
	m_pdlgStats->SetWindowPos(NULL, rect.right, rect.top, 100, 100, SW_SHOW);
	m_pdlgStats->ShowWindow(SW_SHOW);

	SetCapture();

	CDialog::OnLButtonDown(nFlags, point);
}

void CRamViewerDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_pdlgStats->ShowWindow(SW_HIDE);

	ReleaseCapture();

	CDialog::OnLButtonUp(nFlags, point);
}

void CRamViewerDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags == 1)
	{
		COLOR_FORMAT color_format;
		FORMAT data_format;
		CVIP_TYPE data_type;
		IMAGE_FORMAT image_format;
		CString s;
		double curr_min, curr_max, min, max;
		int i, col, row;
		unsigned imgsize;
		void **imgvecP = NULL;
		int num_bands, num_cols, num_rows;
		float pixel[3] = { -1,-1,-1 };

		col = point.x;
		row = point.y;
		color_format = m_imgOriginal->color_space;
		data_format = m_imgOriginal->bandP[0]->data_format;
		data_type = m_imgOriginal->bandP[0]->data_type;
		image_format = m_imgOriginal->image_format;
		num_bands = m_imgOriginal->bands;
		num_cols = m_imgOriginal->bandP[0]->cols;
		num_rows = m_imgOriginal->bandP[0]->rows;
		imgsize = num_rows * num_cols;

		imgvecP = (void **)malloc(sizeof(void *) * num_bands);

		if (data_format != COMPLEX)
		{
			getBandVector_Image(m_imgOriginal, imgvecP);
		}

		for (i = 0; i<num_bands; i++)
		{
			if (data_format == COMPLEX)
			{
				imgvecP[i] = getImagRow_Image(m_imgOriginal, 0, i);
			}

			curr_min = findMinVal_Vector(imgvecP[i], imgsize, data_type);
			curr_max = findMaxVal_Vector(imgvecP[i], imgsize, data_type);

			if (i == 0)
			{
				min = curr_min;
				max = curr_max;
			}

			if (curr_min < min) min = curr_min;
			if (curr_max > max) max = curr_max;
		}

		free(imgvecP);

		m_pdlgStats->m_strTitle.Format("Info for Image - %s\r\n\r\n", m_Filename);

		if ((row >= 0) && (row<num_rows) && (col >= 0) && (col<num_cols))
		{
			for (i = 0; i<num_bands; i++)
			{
				if (data_type == CVIP_BYTE) {
					pixel[i] = (float)getPixel_Image(m_imgOriginal, byte, col, row, i);
				}
				else if (data_type == CVIP_SHORT) {
					pixel[i] = (float)getPixel_Image(m_imgOriginal, short, col, row, i);
				}
				else if (data_type == CVIP_INTEGER) {
					pixel[i] = (float)getPixel_Image(m_imgOriginal, int, col, row, i);
				}
				else if (data_type == CVIP_FLOAT) {
					pixel[i] = (float)getPixel_Image(m_imgOriginal, float, col, row, i);
				}
				else if (data_type == CVIP_DOUBLE) {
					pixel[i] = (float)getPixel_Image(m_imgOriginal, double, col, row, i);
				}
			}

			if (num_bands == 1)
			{
				pixel[1] = pixel[0];
				pixel[2] = pixel[0];
			}

			s.Format("Row = %d, Col = %d\r\nRed = %.2f\r\nGreen = %.2f\r\nBlue = %.2f\r\n",
				row, col, pixel[0], pixel[1], pixel[2]);

			m_pdlgStats->m_strTitle += (s + "\r\n");
		}

		s.Format("Image Format: %s\r\nColor Format: %s\r\n", image_format_string[image_format], color_format_string[color_format]);
		m_pdlgStats->m_strTitle += s;
		s.Format("Number of Bands: %d\r\nNumber of Rows: %d\r\nNumber of Cols: %d\r\n", num_bands, num_rows, num_cols);
		m_pdlgStats->m_strTitle += s;
		s.Format("Data Type: %s\r\nData Format: %s\r\n", data_type_string[data_type], data_format_string[data_format]);
		m_pdlgStats->m_strTitle += s;
		s.Format("Data Range: %.0f - %.0f\r\n", min, max);
		m_pdlgStats->m_strTitle += s;
		m_pdlgStats->UpdateData(FALSE);
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CRamViewerDlg::OnPaint()
{
	if (m_imgDisplay != NULL)
	{
		CPaintDC dc(this); // device context for painting

		int num_cols = m_imgDisplay->bandP[0]->cols;
		int num_rows = m_imgDisplay->bandP[0]->rows;

		if (m_dcMem == NULL)
		{
			__Render_DisplayImage((int)dc.m_ps.hdc, (long*)&m_imgDisplay, (long*)&m_dcMem);
		}

		__Show_DisplayImage((int)dc.m_ps.hdc, (long)m_dcMem, 0, 0, num_cols, num_rows);
	}
}

extern "C"
{
	struct tmp_img_structure
	{
		Image* dispImage;
		Image* oriImage;
		char imagename[1000];
	};
	UINT ThreadProc(LPVOID lpParameter)
	{
		struct tmp_img_structure *t;
		CRamViewerDlg dlg;

		t = (struct tmp_img_structure *)lpParameter;
		dlg.m_imgDisplay = t->dispImage;
		dlg.m_imgOriginal = t->oriImage;
		strcpy(dlg.m_Filename, t->imagename);
		dlg.DoModal();
		delete_Image(dlg.m_imgDisplay);
		delete_Image(dlg.m_imgOriginal);
		free(t);

		return(0);
	}
	void view_Image(Image *dispImage, char *imagename)
	{
		struct tmp_img_structure *t;
		t = (struct tmp_img_structure *)malloc(sizeof(*t));
		t->oriImage = duplicate_Image(dispImage);
		t->dispImage = condRemap_Image(dispImage, (CVIP_TYPE)0, 0, 255);
		strcpy(t->imagename, imagename);
		AfxBeginThread(ThreadProc, t);

	}
}
