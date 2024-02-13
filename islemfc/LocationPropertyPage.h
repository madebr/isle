#if !defined(AFX_LOCATIONPROPERTYPAGE_H)
#define AFX_LOCATIONPROPERTYPAGE_H

#include "StdAfx.h"

#include <mxgeometry3d.h>

// VTABLE 0x0040bfe0
class CLocationPropertyPage : public CPropertyPage {
public:
	CLocationPropertyPage();

	BOOL OnInitDialog() override;

	Mx3DPointFloat m_unk0x90; // 0x90
	Mx3DPointFloat m_unk0xa4; // 0xa4
	Mx3DPointFloat m_unk0xb8; // 0zb8

protected:
	DECLARE_MESSAGE_MAP()
};

// SYNTHETIC: MAINR 0x00405bb0
// CLocationPropertyPage::`scalar deleting destructor'

// FUNCTION: MAINR 0x00405c40
// CLocationPropertyPage::GetMessageMap

// GLOBAL: MAINR 0x0040b458
// CLocationPropertyPage::messageMap

// GLOBAL: MAINR 0x0040b460
// CLocationPropertyPage::_messageEntries

#endif // defined(AFX_LOCATIONPROPERTYPAGE_H)
