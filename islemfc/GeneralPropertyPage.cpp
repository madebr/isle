#include "GeneralPropertyPage.h"

#include "res/resource.h"

#include <limits.h>

BEGIN_MESSAGE_MAP(CGeneralPropertyPage, CPropertyPage)
ON_COMMAND(IDC_CHECKBOX_PRELOAD_RESIDENT, OnCheckboxPreloadResident)
END_MESSAGE_MAP()

// FUNCTION: MAINR 0x004054d0
CGeneralPropertyPage::CGeneralPropertyPage() : CPropertyPage(IDD_GENERAL, IDS_GENERAL)
{
	m_preload = FALSE;
	m_time = INT_MIN;
}

// FUNCTION: MAINR 0x004055c0
BOOL CGeneralPropertyPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	Synchronize();
	return TRUE;
}

// FUNCTION: MAINR 0x004055e0
void CGeneralPropertyPage::Synchronize()
{
	CButton* preload_button = (CButton*) GetDlgItem(IDC_CHECKBOX_PRELOAD_RESIDENT);
	preload_button->SetCheck(!!m_preload);
	GetDlgItem(IDC_EDIT_MILLISECONDS)->EnableWindow(m_preload);
	if (m_time != INT_MIN) {
		SetDlgItemInt(IDC_EDIT_MILLISECONDS, m_time);
	}
	else {
		GetDlgItem(IDC_EDIT_MILLISECONDS)->SetWindowText("MxNAN_TIME");
	}
}

// FUNCTION: MAINR 0x00405660
void CGeneralPropertyPage::OnCheckboxPreloadResident()
{
	BOOL v;
	m_time = GetDlgItemInt(IDC_EDIT_MILLISECONDS, &v);
	if (!v) {
		m_time = INT_MIN;
	}
	m_preload = !m_preload;
	Synchronize();
}
