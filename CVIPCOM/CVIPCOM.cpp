// CVIPCOM.cpp : Implementation of DLL Exports.

#include "stdafx.h"
#include "resource.h"
#include "CVIPCOM_i.h"
#include "CVIPCOM.h"

CCVIPCOMModule _AtlModule;

class CCVIPCOMApp : public CWinApp
{
public:

// Overrides
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CCVIPCOMApp, CWinApp)
END_MESSAGE_MAP()

CCVIPCOMApp theApp;

BOOL CCVIPCOMApp::InitInstance()
{
	return CWinApp::InitInstance();
}

int CCVIPCOMApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}

// Used to determine whether the DLL can be unloaded by OLE.
STDAPI DllCanUnloadNow(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return (AfxDllCanUnloadNow()==S_OK && _AtlModule.GetLockCount()==0) ? S_OK : S_FALSE;
}

// Returns a class factory to create an object of the requested type.
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}

// DllRegisterServer - Adds entries to the system registry.
STDAPI DllRegisterServer(void)
{
	// registers object, typelib and all interfaces in typelib
	return _AtlModule.DllRegisterServer();
}

// DllUnregisterServer - Removes entries from the system registry.
STDAPI DllUnregisterServer(void)
{
	return _AtlModule.DllUnregisterServer();
}
