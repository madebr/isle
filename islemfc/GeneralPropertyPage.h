#if !defined(AFX_GENERALPROPERTYPAGE_H)
#define AFX_GENERALPROPERTYPAGE_H

#include "StdAfx.h"

#include <compat.h>
#include <decomp.h>
#include <mxtypes.h>

// VTABLE 0x0040bdf0
class CGeneralPropertyPage : public CPropertyPage {
public:
	CGeneralPropertyPage();

	BOOL OnInitDialog() override;

	void Synchronize();

	afx_msg void OnCheckboxPreloadResident();

	MxLong m_time;  // 0x90
	BOOL m_preload; // 0x94

protected:
	DECLARE_MESSAGE_MAP()
};

// SYNTHETIC: MAINR 0x00405550
// CGeneralPropertyPage::`scalar deleting destructor'

// FUNCTION: MAINR 0x004056d0
// CGeneralPropertyPage::GetMessageMap

// GLOBAL: MAINR 0x0040b3d0
// CGeneralPropertyPage::messageMap

// GLOBAL: MAINR 0x0040b3d8
// CGeneralPropertyPage::_messageEntries

#endif // defined(AFX_GENERALPROPERTYPAGE_H)
