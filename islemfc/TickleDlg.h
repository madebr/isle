#if !defined(AFX_TICKLEDLG_H)
#define AFX_TICKLEDLG_H

#include "StdAfx.h"

#include <compat.h>

// VTABLE: MAINR 0x0040c2c8
class CTickleDialog : public CDialog {
public:
	CTickleDialog(CWnd* pParentWnd);

public:
	CString m_unk0x60;
	class MxTickleManager* m_tickle_manager;
	class LegoVideoManager* m_video_manager;
	class MxNotificationManager* m_notification_manager;
	class LegoSoundManager* m_sound_manager;
	class MxMusicManager* m_music_manager;
	class MxEventManager* m_event_manager;

protected:
	afx_msg void Synchronize();
	BOOL OnInitDialog() override;
	void OnOK() override;
	DECLARE_MESSAGE_MAP()
};

// SYNTHETIC: MAINR 0x00406180
// CTickleDialog::`scalar deleting destructor'

// FUNCTION: MAINR 0x004063e0
// CTickleDialog::GetMessageMap

// GLOBAL: MAINR 0x0040b510
// CTickleDialog::messageMap

// GLOBAL: MAINR 0x0040b518
// CTickleDialog::_messageEntries

#endif // !defined(AFX_TICKLEDLG_H)
