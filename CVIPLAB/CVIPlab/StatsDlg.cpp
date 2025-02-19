// StatsDlg.cpp : implementation file
//

#include "afxdialogex.h"
#include "resource.h"
#include "StatsDlg.h"

// CStatsDlg dialog
IMPLEMENT_DYNAMIC(CStatsDlg, CDialog)

CStatsDlg::CStatsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStatsDlg::IDD, pParent)
{
	m_strTitle = _T("");
}

CStatsDlg::~CStatsDlg()
{
}

void CStatsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TITLE, m_strTitle);
}

BEGIN_MESSAGE_MAP(CStatsDlg, CDialog)
END_MESSAGE_MAP()

// CStatsDlg message handlers
