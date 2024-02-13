#include "TimePropertyPage.h"

#include "res/resource.h"

#include <limits.h>

BEGIN_MESSAGE_MAP(CTimePropertyPage, CPropertyPage)
ON_COMMAND(IDC_COMBO_LOOPING, OnLoopingRadioButton)
ON_COMMAND(IDC_COMBO_DURATION, OnDurationRadioButton)
END_MESSAGE_MAP()

// FUNCTION: MAINR
CTimePropertyPage::CTimePropertyPage() : CPropertyPage(IDD_TIME, IDS_TIME)
{
	m_unk0x90 = INT_MIN;
	m_unk0x94 = INT_MIN;
	m_unk0x9c = FALSE;
	m_unk0x98 = 1;
}

// FUNCTION: MAINR 0x004057e0
BOOL CTimePropertyPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	Synchronize();
	return TRUE;
}

// FUNCTION: MAINR 0x00405800
void CTimePropertyPage::Synchronize()
{
	if (m_unk0x90 == INT_MIN) {
		GetDlgItem(IDC_EDIT_TIME)->SetWindowText("MxNAN_TIME");
	}
	else {
		SetDlgItemInt(IDC_EDIT_TIME, m_unk0x90);
	}
	((CButton*) GetDlgItem(IDC_COMBO_LOOPING))->SetCheck(!m_unk0x9c);
	GetDlgItem(IDC_EDIT_LOOPING)->EnableWindow(!m_unk0x9c);
	((CButton*) GetDlgItem(IDC_COMBO_DURATION))->SetCheck(!!m_unk0x9c);
	GetDlgItem(IDC_EDIT_DURATION)->EnableWindow(!m_unk0x9c);
	if (m_unk0x94 == INT_MIN) {
		GetDlgItem(IDC_EDIT_DURATION)->SetWindowText("MxNAN_TIME");
	}
	else {
		SetDlgItemInt(IDC_EDIT_DURATION, m_unk0x94);
	}
	SetDlgItemInt(IDC_EDIT_LOOPING, m_unk0x98);
}

// FUNCTION: MAINR 0x00405980
void CTimePropertyPage::OnLoopingRadioButton()
{
	BOOL v = FALSE;
	m_unk0x9c = FALSE;

	m_unk0x94 = GetDlgItemInt(IDC_EDIT_DURATION, &v);
	if (!v) {
		m_unk0x94 = INT_MIN;
	}

	m_unk0x90 = GetDlgItemInt(IDC_EDIT_TIME, &v);
	if (!v) {
		m_unk0x90 = INT_MIN;
	}

	Synchronize();
}

// FUNCTION: MAINR 0x00405a00
void CTimePropertyPage::OnDurationRadioButton()
{
	BOOL v = FALSE;
	m_unk0x9c = FALSE;

	m_unk0x98 = GetDlgItemInt(IDC_EDIT_LOOPING, &v);
	if (!v) {
		m_unk0x98 = 1;
	}

	m_unk0x90 = GetDlgItemInt(IDC_EDIT_TIME, &v);
	if (!v) {
		m_unk0x90 = INT_MIN;
	}

	Synchronize();
}
