#if !defined(AFX_ACTIONSDLG_H)
#define AFX_ACTIONSDLG_H

#include "StdAfx.h"

#include <compat.h>

// VTABLE: MAINR 0x0040bd18
class CActionsDialog : public CDialog {
public:
	CActionsDialog(CWnd* pParentWnd);

	BOOL OnInitDialog() override;
	void OnOK() override;

	void Synchronize();

	afx_msg void OnAddButton();
	afx_msg void OnDeleteButton();
	afx_msg void OnPropertiesButton();
	afx_msg void OnSourcesComboBox();

	CPtrList m_actions;

protected:
	DECLARE_MESSAGE_MAP()
};

// SYNTHETIC: MAINR 0x00404910
// CActionsDialog::`scalar deleting destructor'

// FUNCTION: MAINR 0x004054c0
// CActionsDialog::GetMessageMap

// GLOBAL: MAINR 0x0040b350
// CActionsDialog::messageMap

// GLOBAL: MAINR 0x0040b358
// CActionsDialog::_messageEntries

#endif // !defined(AFX_ACTIONSDLG_H)
