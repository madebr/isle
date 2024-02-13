#if !defined(AFX_NAVIGATIONDLG_H)
#define AFX_NAVIGATIONDLG_H

#include "StdAfx.h"

#include <compat.h>

// VTABLE: MAINR 0x0040b078
class CNavigationDialog : public CDialog {
public:
	CNavigationDialog(CWnd* pParentWnd);

protected:
	void DoDataExchange(CDataExchange* pDDX) override;
	BOOL OnInitDialog() override;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	afx_msg void OnCheckboxRotVel();
	DECLARE_MESSAGE_MAP()

public:
	CSliderCtrl m_unk0x060; // 0x060
	CSliderCtrl m_unk0x0a0; // 0x060
	CSliderCtrl m_unk0x0e0; // 0x060
	CSliderCtrl m_unk0x120; // 0x120
	CSliderCtrl m_unk0x160; // 0x160
	CSliderCtrl m_unk0x1a0; // 0x1a0
	CSliderCtrl m_unk0x1e0; // 0x1e0
	CSliderCtrl m_unk0x220; // 0x220
	CSliderCtrl m_unk0x260; // 0x260
	CSliderCtrl m_unk0x2a0; // 0x2a0
	BOOL m_unk0x2e0;        // 0x2e0
};

// SYNTHETIC: MAINR 0x004012e0
// CNavigationDialog::`scalar deleting destructor'

// FUNCTION: MAINR 0x00401510
// CNavigationDialog::GetMessageMap

// GLOBAL: MAINR 0x0040b018
// CNavigationDialog::messageMap

// GLOBAL: MAINR 0x0040b020
// CNavigationDialog::_messageEntries

#endif // !defined(AFX_NAVIGATIONDLG_H)
