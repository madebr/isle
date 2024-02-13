#if !defined(AFX_SOUNDVOLUMEDLG_H)
#define AFX_SOUNDVOLUMEDLG_H

#include "StdAfx.h"

#include <compat.h>
#include <mxtypes.h>

// VTABLE: MAINR 0x0040bb68
class CSetSoundVolumeDialog : public CDialog {
public:
	CSetSoundVolumeDialog(CWnd* pParentWnd);

protected:
	BOOL OnInitDialog() override;
	void OnOK() override;

public:
	MxS32 m_volume; // 0x60
};

// SYNTHETIC: MAINR 0x004046a0
// CSetSoundVolumeDialog::`scalar deleting destructor'

#endif // !defined(AFX_SOUNDVOLUMEDLG_H)
