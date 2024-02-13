#if !defined(AFX_GETVARIABLEDLG_H)
#define AFX_GETVARIABLEDLG_H

#include "StdAfx.h"

#include <compat.h>

// VTABLE: MAINR 0x0040b9b8
class CGetVariableDialog : public CDialog {
public:
	CGetVariableDialog(CWnd* pParentWnd);

	afx_msg BOOL OnInitDialog() override;
	afx_msg void OnOK() override;

	CString m_name;
};

// GLOBAL: MAINR 0x0040b358
// CGetVariableDialog::_messageEntries

#endif // !defined(AFX_GETVARIABLEDLG_H)
