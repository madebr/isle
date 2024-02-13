#if !defined(AFX_MAINCOMMANDLINEINFO_H)
#define AFX_MAINCOMMANDLINEINFO_H

#include "StdAfx.h"
#include "compat.h"
#include "decomp.h"

// VTABLE: MAINR xxxxx
// SIZE 0x24
class CMainCommandLineInfo : public CCommandLineInfo {
public:
	CMainCommandLineInfo();
	~CMainCommandLineInfo();

	void ParseParam(LPCSTR pszParam, BOOL bFlag, BOOL bLast) override;

	BOOL m_fullscreen;
	BOOL m_flip;
	BOOL m_use_smem;
	BOOL m_d8;
	BOOL m_d16;
	BOOL m_rgb;
	BOOL m_usehw;
	BOOL m_help;
	const char* m_script;
	BOOL m_ramstream;
	int m_action;
	const char* m_unk0x50;
	const char* m_unk0x54;
	BOOL m_hd;
	BOOL m_cd;
};

// VTABLE: MAINR 0x00406490
// CMainCommandLineInfo::`scalar deleting destructor'

#endif // !defined(AFX_MAINCOMMANDLINEINFO_H)
