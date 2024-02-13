#if !defined(AFX_MAINCONTEXTMENU_H)
#define AFX_MAINCONTEXTMENU_H

#include "StdAfx.h"
#include "res/resource.h"

// VTABLE: MAINR 0x0040c3b8
class CMainContextMenu : public CMenu {
public:
	CMainContextMenu()
	{
		Attach(::LoadMenuA(AfxFindResourceHandle(MAKEINTRESOURCE(IDM_POPUP), RT_MENU), MAKEINTRESOURCE(IDM_POPUP)));
	}
};

// VTABLE: MAINR 0x004079b0
// CMainContextMenu::`scalar deleting destructor'

#endif // ~defined(AFX_MAINCONTEXTMENU_H)
