#include "GetVariableDlg.h"

#include "res/resource.h"

// FUNCTION: MAINR 0x00404370
CGetVariableDialog::CGetVariableDialog(CWnd* pParentWnd) : CDialog(IDD_GETVARIABLE)
{
}

// FUNCTION: MAINR 0x00404470
BOOL CGetVariableDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;
}

// FUNCTION: MAINR 0x00404ae0
void CGetVariableDialog::OnOK()
{
	GetDlgItem(IDC_EDIT_GETVARIABLE_NAME)->GetWindowText(m_name);
	CDialog::OnOK();
}
