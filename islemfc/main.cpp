#include "main.h"

#include "MainCommandLineInfo.h"
#include "MainFrameWnd.h"
#include "StdAfx.h"
#include "islegame.h"

#include <legoomni.h>

// GLOBAL: MAINR 0x0040e700
CMainApp g_theApp;

// FUNCTION: MAINR 0x00407440
BOOL CMainApp::InitInstance()
{
	char diskpath[512];
	char cdpath[512];

	m_pMainWnd = new CMainFrameWnd;
	m_pMainWnd->ShowWindow(FALSE);
	if (!ReadReg("diskpath", diskpath, sizeof(diskpath))) {
		strcpy(diskpath, MxOmni::GetHD());
		WriteReg("diskpath", diskpath);
	}
	m_diskpath = _strdup(diskpath);
	MxOmni::SetHD(diskpath);
	if (!ReadReg("cdpath", diskpath, sizeof(diskpath))) {
		strcpy(diskpath, MxOmni::GetCD());
		WriteReg("cdpath", diskpath);
	}
	m_cdpath = _strdup(cdpath);
	MxOmni::SetCD(cdpath);
	CMainCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	g_game = new IsleGame;
	if (cmdInfo.m_help) {
		MessageBoxA(
			NULL,
			"Command line arguments:\n"
			"\n"
			"/FS\t\t\t- fullscreen (default)\n"
			"/NFS\t\t\t- windowed\n/FLIP\t\t\t- use display surface flipping\n"
			"/NFLIP\t\t\t- use display surface blit (default)\n/SMEM\t\t\t- back buffer in system memory\n"
			"/VMEM\t\t\t- back buffer in video memory (default)\n/D8\t\t\t- 8 bit display depth (full screen only)\n"
			"/D16\t\t\t- 16 bit display depth (full screen only)\n/RGB\t\t\t- use rgb color model (software rendering "
			"only)\n"
			"/RAMP\t\t\t- use mono ramp mode (software rendering only)\n/USEHW\t\t\t- use 3d hardware if available\n"
			"/SCRIPT <filename>\t- auto load startup script\n/RAMSTREAM\t\t- stream <filename> from ram (default)\n"
			"/DISKSTREAM\t\t- stream <filename> from disk\n/ACTION <num>\t\t- start action <num> in <filename> "
			"(default is 0)\n"
			"/HELP\t\t\t- display this message\n"
			"\n"
			"If a 3D accelerator is identified, it will be used if USEHW is specified.\n"
			"RGB color model is always used with hardware 3D.\n"
			"Only 8 and 16 bit display depths are supported.\n",
			"Lego Demo",
			MB_ICONASTERISK
		);
		exit(0);
	}
	g_game->SetFlags(
		cmdInfo.m_fullscreen,
		cmdInfo.m_flip,
		cmdInfo.m_use_smem,
		cmdInfo.m_d8,
		cmdInfo.m_d16,
		cmdInfo.m_rgb,
		cmdInfo.m_usehw
	);
	g_game->SetupLegoOmni();
	m_pMainWnd->ShowWindow(m_nCmdShow);
	::UpdateWindow(m_pMainWnd->m_hWnd);
	return TRUE;
}

// FUNCTION: MAINR 0x004076b0
int CMainApp::ExitInstance()
{
	delete g_game;
	delete m_diskpath;
	delete m_cdpath;
	return 0;
}

// FUNCTION: MAINR 0x00407700
int CMainApp::Run()
{
	unsigned char idle = 1;
	int idle_count = 0;
#if _MSC_VER < 1920
	MSG* msg = &m_msgCur;
#else
	MSG *msg = AfxGetCurrentMessage();
#endif

	for (;;) {
		while (idle) {
			if (PeekMessageA(msg, NULL, 0, 0, 0)) {
				break;
			}
			g_game->MaybeTickle(TRUE);
			idle_count += 1;
			if (!OnIdle(idle_count)) {
				idle = 0;
			}
		}
		for (;;) {
			g_game->MaybeTickle(FALSE);
			if (!PeekMessageA(msg, NULL, 0, 0, 0)) {
				break;
			}
			if (!GetMessageA(msg, NULL, 0, 0)) {
				return ExitInstance();
			}
			if (LegoOmni::GetInstance() && LegoOmni::GetInstance()->GetExit()) {
				g_game->m_pMainWnd->OnExit();
				return ExitInstance();
			}
			if (!PreTranslateMessage(msg)) {
				if (!IsMouseMoveMessage(msg)) {
					TranslateMessage(msg);
					DispatchMessageA(msg);
				}
			}
			if (IsIdleMessage(msg)) {
				idle = 1;
				idle_count = 0;
			}
		}
	}
}

// FUNCTION: MAINR 0x00407800
BOOL CMainApp::IsMouseMoveMessage(const MSG* p_msg) const
{
	MSG msg;

	return p_msg->message == WM_MOUSEMOVE && PeekMessageA(&msg, NULL, 0, 0, 0) && msg.message == WM_MOUSEMOVE;
}

// FUNCTION: MAINR 0x00407850
BOOL CMainApp::WriteReg(const char* p_key, const char* p_value) const
{
	HKEY hKey;
	DWORD pos;

	if (RegCreateKeyExA(
			HKEY_LOCAL_MACHINE,
			"SOFTWARE\\Mindscape\\Adventures on LEGO Island",
			0,
			"string",
			0,
			KEY_READ | KEY_WRITE,
			NULL,
			&hKey,
			&pos
		) == ERROR_SUCCESS) {
		if (RegSetValueExA(hKey, p_key, 0, REG_SZ, (LPBYTE) p_value, strlen(p_value)) == ERROR_SUCCESS) {
			if (RegCloseKey(hKey) == ERROR_SUCCESS) {
				return TRUE;
			}
		}
		else {
			RegCloseKey(hKey);
		}
	}
	return FALSE;
}

// FUNCTION: MAINR 0x004078e0
BOOL CMainApp::ReadReg(LPCSTR p_key, LPCSTR p_value, DWORD p_size) const
{
	HKEY hKey;
	DWORD valueType;

	BOOL out = FALSE;
	DWORD size = p_size;
	if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Mindscape\\Adventures on LEGO Island", 0, KEY_READ, &hKey) ==
		ERROR_SUCCESS) {
		if (RegQueryValueExA(hKey, p_key, NULL, &valueType, (LPBYTE) p_value, &size) == ERROR_SUCCESS) {
			if (RegCloseKey(hKey) == ERROR_SUCCESS) {
				out = TRUE;
			}
		}
	}
	return out;
}
