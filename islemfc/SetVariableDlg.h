#if !defined(AFX_SETVARIABLEDLG_H)
#define AFX_SETVARIABLEDLG_H

#include "StdAfx.h"

#include <compat.h>

// VTABLE: MAINR 0x0040ba90
class CSetVariableDialog : public CDialog {
public:
	CSetVariableDialog(CWnd* pParentWnd);

protected:
	BOOL OnInitDialog() override;
	void OnOK() override;

public:
	CString m_name;
	CString m_value;
};

// SYNTHETIC: MAINR 0x00404550
// CSetVariableDialog::`scalar deleting destructor'

#endif // !defined(AFX_SETVARIABLEDLG_H)
