// CVIPCOM.h : Declaration of module class.

class CCVIPCOMModule : public ATL::CAtlDllModuleT< CCVIPCOMModule >
{
public :
	DECLARE_LIBID(LIBID_SERVERLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_CVIPCOM, "{D0C35BB6-39FD-4E47-AE75-207657D9BC41}")
};

extern class CCVIPCOMModule _AtlModule;
