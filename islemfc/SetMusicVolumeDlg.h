#if !defined(AFX_MUSICVOLUMEDLG_H)
#define AFX_MUSICVOLUMEDLG_H

#include "StdAfx.h"

#include <compat.h>
#include <mxtypes.h>

// VTABLE: MAINR 0x0040bc40
class CSetMusicVolumeDialog : public CDialog {
public:
	CSetMusicVolumeDialog(CWnd* pParentWnd);

protected:
	BOOL OnInitDialog() override;
	void OnOK() override;

public:
	MxS32 m_volume; // 0x60
};

// SYNTHETIC: MAINR 0x004047b0
// CSetMusicVolumeDialog::`scalar deleting destructor'

#endif // !defined(AFX_MUSICVOLUMEDLG_H)
