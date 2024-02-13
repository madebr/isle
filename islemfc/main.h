#if !defined(AFX_MAIN_H)
#define AFX_MAIN_H

#include "StdAfx.h"

#include <compat.h>

#define currentConfigApp ((CMainApp*) afxCurrentWinApp)

// VTABLE: MAINR 0x0040b798
// SIZE 0xcc
class CMainApp : public CWinApp {
public:
	BOOL InitInstance() override;
	int ExitInstance() override;
	int Run() override;

private:
	BOOL CMainApp::IsMouseMoveMessage(const MSG* p_msg) const;
	BOOL WriteReg(const char* p_key, const char* p_value) const;
	BOOL ReadReg(LPCSTR p_key, LPCSTR p_value, DWORD p_size) const;

private:
	char* m_diskpath; // 0xc4
	char* m_cdpath;   // 0xc8
};

// SYNTHETIC: MAINR 0x00402de0
// CMainApp::`scalar deleting destructor'

extern CMainApp g_theApp;

#endif // !defined(AFX_MAIN_H)
