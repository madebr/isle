#if !defined(AFX_TIMEPROPERTYPAGE_H)
#define AFX_TIMEPROPERTYPAGE_H

#include "StdAfx.h"

#include <compat.h>
#include <mxtypes.h>

// VTABLE 0x0040bee8
class CTimePropertyPage : public CPropertyPage {
public:
	CTimePropertyPage();

	BOOL OnInitDialog() override;

	void Synchronize();

	afx_msg void OnLoopingRadioButton();
	afx_msg void OnDurationRadioButton();

	MxLong m_unk0x90; // 0x90
	MxLong m_unk0x94; // 0x94
	int m_unk0x98;    // 0x98
	BOOL m_unk0x9c;   // 0x9c

protected:
	DECLARE_MESSAGE_MAP()
};

// SYNTHETIC: MAINR 0x00405770
// CTimePropertyPage::`scalar deleting destructor'

// FUNCTION: MAINR 0x00405a90
// CTimePropertyPage::GetMessageMap

// GLOBAL: MAINR 0x0040b408
// CTimePropertyPage::messageMap

// GLOBAL: MAINR 0x0040b410
// CTimePropertyPage::_messageEntries

#endif // defined(AFX_TIMEPROPERTYPAGE_H)
