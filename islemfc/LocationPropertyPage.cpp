#include "LocationPropertyPage.h"

#include "res/resource.h"

#include <float.h>

BEGIN_MESSAGE_MAP(CLocationPropertyPage, CPropertyPage)
END_MESSAGE_MAP()

// FUNCTION: MAINR 0x00405aa0
CLocationPropertyPage::CLocationPropertyPage() : CPropertyPage(IDD_LOCATION, IDS_LOCATION)
{
	float m = FLT_MAX;
	m_unk0x90.EqualsScalar(&m);
	m_unk0xa4.EqualsScalar(&m);
	m_unk0xb8.EqualsScalar(&m);
}

// FUNCTION: MAINR 0x00405c20
BOOL CLocationPropertyPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	return TRUE;
}
