#if !defined(AFX_VIDEODLG_H)
#define AFX_VIDEODLG_H

#include "StdAfx.h"

#include <mxvideoparam.h>

// VTABLE: MAINR 0x0040c1f0
class CVideoDialog : public CDialog {
public:
	CVideoDialog(CWnd* p_wnd);

protected:
	afx_msg void SynchronizeControls();

	BOOL OnInitDialog() override;
	void OnOK() override;
	DECLARE_MESSAGE_MAP()

public:
	MxVideoParam m_video_param;
};

// SYNTHETIC: MAINR 0x00405cc0
// CVideoDialog::`scalar deleting destructor'

// FUNCTION: MAINR 0x004060f0
// CVideoDialog::GetMessageMap

// GLOBAL: MAINR 0x0040b478
// CVideoDialog::messageMap

// GLOBAL: MAINR 0x0040b480
// CVideoDialog::_messageEntries

#endif // !defined(AFX_VIDEODLG_H)
