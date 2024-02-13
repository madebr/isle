#include "MainCommandLineInfo.h"

#include "mxcriticalsection.h"

// FUNCTION: MAINR 0x004063f0
CMainCommandLineInfo::CMainCommandLineInfo()
{
	m_fullscreen = TRUE;
	m_flip = FALSE;
	m_use_smem = FALSE;
	m_d8 = FALSE;
	m_d16 = FALSE;
	m_rgb = FALSE;
	m_usehw = FALSE;
	m_ramstream = TRUE;
	m_action = 0;
	m_unk0x50 = NULL;
	m_unk0x54 = NULL;
	m_hd = FALSE;
	m_cd = FALSE;
	m_script = "LegoTestScript.si";
	m_help = FALSE;
}

// FUNCTION: MAINR 0x004064b0
CMainCommandLineInfo::~CMainCommandLineInfo()
{
}

// FUNCTION: CONFIG 0x00403bf0
void CMainCommandLineInfo::ParseParam(LPCSTR pszParam, BOOL bFlag, BOOL bLast)
{
	if (bFlag) {
		if (!lstrcmpiA(pszParam, "fs")) {
			m_fullscreen = TRUE;
		}
		else if (!lstrcmpiA(pszParam, "nfs")) {
			m_fullscreen = FALSE;
		}
		else if (!lstrcmpiA(pszParam, "flip")) {
			m_flip = TRUE;
		}
		else if (!lstrcmpiA(pszParam, "nflip")) {
			m_flip = FALSE;
		}
		else if (!lstrcmpiA(pszParam, "smem")) {
			m_use_smem = TRUE;
		}
		else if (!lstrcmpiA(pszParam, "vmem")) {
			m_use_smem = FALSE;
		}
		else if (!lstrcmpiA(pszParam, "d8")) {
			m_d8 = TRUE;
		}
		else if (!lstrcmpiA(pszParam, "d16")) {
			m_d16 = TRUE;
		}
		else if (!lstrcmpiA(pszParam, "rgb")) {
			m_rgb = TRUE;
		}
		else if (!lstrcmpiA(pszParam, "ramp")) {
			m_rgb = FALSE;
		}
		else if (!lstrcmpiA(pszParam, "usehw")) {
			m_usehw = TRUE;
		}
		else if (!lstrcmpiA(pszParam, "ramstream")) {
			m_ramstream = TRUE;
		}
		else if (!lstrcmpiA(pszParam, "diskstream")) {
			m_ramstream = FALSE;
		}
		else if (!lstrcmpiA(pszParam, "script")) {
			m_script = (char*) 0x0;
		}
		else if (!lstrcmpiA(pszParam, "action")) {
			m_action = -1;
		}
		else if (!lstrcmpiA(pszParam, "hd")) {
			m_hd = TRUE;
		}
		else if (!lstrcmpiA(pszParam, "cd")) {
			m_cd = TRUE;
		}
		else if (!lstrcmpiA(pszParam, "help")) {
			m_help = TRUE;
		}
		else if (!lstrcmpiA(pszParam, "mutex")) {
			MxCriticalSection::SetDoMutex();
		}
	}
	else {
		if (!m_script) {
			m_script = pszParam;
		}
		else if (m_action == -1) {
			m_action = atoi(pszParam);
		}
		else if (m_hd) {
			m_hd = FALSE;
			m_unk0x50 = pszParam;
		}
		else if (m_cd) {
			m_cd = FALSE;
			m_unk0x54 = pszParam;
		}
	}
	if (bLast && m_action == -1) {
		m_action = 0;
	}
}
