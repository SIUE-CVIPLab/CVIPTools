// test.cpp : Defines the entry point for the console application.
//

#include "StdAfx.h"
#include "CVIPlab_Project.h"
#include "process.h"

#include "CVIPimage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern "C"
{
	void main_cviplab();
	Image *remap_Image(const Image *mapP, CVIP_TYPE dtype, long dmin,
		long dmax);
}





/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;
int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		CString strHello;
		//		strHello.LoadString(IDS_HELLO);
		cout << (LPCTSTR)strHello << endl;
	}
	main_cviplab();
	return nRetCode;
}
