#pragma once

#include "CVIPimage.h"
#include "resource1.h"

class CStatsDlg;

// CRamViewerDlg dialog
class CRamViewerDlg : public CDialog
{
	DECLARE_DYNAMIC(CRamViewerDlg)

	// Construction
public:
	CRamViewerDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRamViewerDlg();

	// Dialog Data
	enum { IDD = IDD_RAMVIEWERDLG };

	// Overrides
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	// Implementation
public:
	char m_Filename[1000];
	CStatsDlg* m_pdlgStats;
	HDC m_dcMem;
	Image* m_imgDisplay;
	Image* m_imgOriginal;

	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
};
