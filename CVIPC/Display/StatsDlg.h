#pragma once

// CStatsDlg dialog
class CStatsDlg : public CDialog
{
	DECLARE_DYNAMIC(CStatsDlg)

// Construction
public:
	CStatsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CStatsDlg();

// Dialog Data
	enum { IDD = IDD_STATSDLG };
	CString m_strTitle;

// Overrides
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
