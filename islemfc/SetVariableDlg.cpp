#include "SetVariableDlg.h"

#include "res/resource.h"

// FUNCTION: MAINR 0x004044b0
CSetVariableDialog::CSetVariableDialog(CWnd* pParentWnd) : CDialog(IDD_SETVARIABLE, pParentWnd)
{
}

// FUNCTION: MAINR 0x004045e0
BOOL CSetVariableDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;
}

// FUNCTION: MAINR 0x004045f0
void CSetVariableDialog::OnOK()
{
	GetDlgItem(IDC_EDIT_SETVARIABLE_NAME)->GetWindowText(m_name);
	GetDlgItem(IDC_EDIT_SETVARIABLE_VALUE)->GetWindowText(m_value);
	CDialog::OnOK();
}
