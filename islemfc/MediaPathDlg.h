#if !defined(AFX_MEDIAPATHDLG_H)
#define AFX_MEDIAPATHDLG_H

#include "StdAfx.h"

#include <compat.h>

// VTABLE: MAINR 0x0040b260
class CMediaPathDialog : public CDialog {
public:
	CMediaPathDialog();

	CString m_path;           // 0x60
	int m_icon_cd_drive;      // 0x64
	int m_icon_closed_folder; // 0x68
	int m_icon_computer;      // 0x6c
	int m_icon_hard_drive;    // 0x70
	int m_icon_open_folder;   // 0x74
	int m_icon_network_drive; // 0x78
	int m_icon_floppy_drive;  // 0x7c

private:
	void Initialize();
	void Synchronize();
	CImageList* LoadIcons();
	void ExpandPath(char* p_path);
	HTREEITEM FindDriveRootItem(char* p_drive);
	HTREEITEM FindChildItem(HTREEITEM p_parent, char* p_name);
	CString TreeItemToString(HTREEITEM item);

	void OnCollapse(HTREEITEM p_item);
	void OnExpand(HTREEITEM p_item);

protected:
	BOOL OnInitDialog() override;
	BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) override;
	void OnOK() override;
	void OnDestroy();
	DECLARE_MESSAGE_MAP()
};

// SYNTHETIC: MAINR 0x00401dd0
// CMediaPathDialog::`scalar deleting destructor'

// FUNCTION: MAINR 0x00402ce0
// CMediaPathDialog::GetMessageMap

// GLOBAL: MAINR 0x0040b228
// CMediaPathDialog::messageMap

// GLOBAL: MAINR 0x0040b230
// CMediaPathDialog::_messageEntries

#endif // !defined(AFX_MEDIAPATHDLG_H)
