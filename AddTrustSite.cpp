// AddTrustSite.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include <urlmon.h>
#include "AddTrustSite.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	HRESULT hr;
	IInternetSecurityManager *pSecurityMgr;
	IInternetZoneManager *pZoneMgr;
	ZONEATTRIBUTES zoneAttributes;

	LPCWSTR lpTrustSite = lpCmdLine;

	::CoInitialize (NULL);
	hr = CoCreateInstance(CLSID_InternetSecurityManager, NULL, CLSCTX_INPROC_SERVER, IID_IInternetSecurityManager, (void**)&pSecurityMgr);
	hr = CoCreateInstance(CLSID_InternetZoneManager,NULL,CLSCTX_INPROC_SERVER,IID_IInternetZoneManager,(void**)&pZoneMgr);
	pZoneMgr->GetZoneAttributes((DWORD)URLZONE_TRUSTED,&zoneAttributes);
	if((zoneAttributes.dwFlags & ZAFLAGS_REQUIRE_VERIFICATION) == ZAFLAGS_REQUIRE_VERIFICATION)
	{
		zoneAttributes.dwFlags &= ~ZAFLAGS_REQUIRE_VERIFICATION;
		pZoneMgr->SetZoneAttributes((DWORD)URLZONE_TRUSTED,&zoneAttributes);
		pSecurityMgr->SetZoneMapping((DWORD)URLZONE_TRUSTED, lpTrustSite, (DWORD)SZM_CREATE );		 
		zoneAttributes.dwFlags |= ZAFLAGS_REQUIRE_VERIFICATION;
		pZoneMgr->SetZoneAttributes((DWORD)URLZONE_TRUSTED,&zoneAttributes);
	}
	else
	{
		pSecurityMgr->SetZoneMapping((DWORD)URLZONE_TRUSTED, lpTrustSite, (DWORD)SZM_CREATE );		
	}	

	pSecurityMgr->Release();
	pZoneMgr->Release();

	return 0;
}



