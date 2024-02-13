#include "TickleDlg.h"

#include "islegame.h"
#include "legoomni.h"
#include "legosoundmanager.h"
#include "legovideomanager.h"
#include "mxeventmanager.h"
#include "mxmusicmanager.h"
#include "mxnotificationmanager.h"
#include "mxticklemanager.h"
#include "res/resource.h"

BEGIN_MESSAGE_MAP(CTickleDialog, CDialog)
ON_COMMAND(IDC_TICKLE_BUTTON_READ, Synchronize)
END_MESSAGE_MAP()

// FUNCTION: MAINR 0x00406100
CTickleDialog::CTickleDialog(CWnd* pParentWnd) : CDialog(IDD_TICKLE, pParentWnd)
{
}

// FUNCTION: MAINR 0x00406200
BOOL CTickleDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_tickle_manager = LegoOmni::GetInstance()->GetTickleManager();
	m_video_manager = LegoOmni::GetInstance()->GetVideoManager();
	m_notification_manager = LegoOmni::GetInstance()->GetNotificationManager();
	m_sound_manager = LegoOmni::GetInstance()->GetSoundManager();
	m_music_manager = LegoOmni::GetInstance()->GetMusicManager();
	m_event_manager = LegoOmni::GetInstance()->GetEventManager();
	Synchronize();
	return TRUE;
}

// FUNCTION: MAINR 0x00406260
void CTickleDialog::OnOK()
{
	g_game->m_unk0x08 = GetDlgItemInt(IDC_TICKLE_EDIT_TICKLE, NULL, FALSE);
	m_tickle_manager->SetClientTickleInterval(m_video_manager, GetDlgItemInt(IDC_TICKLE_EDIT_VIDEO, NULL, FALSE));
	m_tickle_manager->SetClientTickleInterval(
		m_notification_manager,
		GetDlgItemInt(IDC_TICKLE_EDIT_NOTIFICATION, NULL, FALSE)
	);
	m_tickle_manager->SetClientTickleInterval(m_sound_manager, GetDlgItemInt(IDC_TICKLE_EDIT_SOUND, NULL, FALSE));
	m_tickle_manager->SetClientTickleInterval(m_music_manager, GetDlgItemInt(IDC_TICKLE_EDIT_MUSIC, NULL, FALSE));
	m_tickle_manager->SetClientTickleInterval(m_event_manager, GetDlgItemInt(IDC_TICKLE_EDIT_EVENT, NULL, FALSE));
	CDialog::OnOK();
}

// FUNCTION: MAINR 0x00406320
void CTickleDialog::Synchronize()
{
	SetDlgItemInt(IDC_TICKLE_EDIT_TICKLE, g_game->m_unk0x08);
	SetDlgItemInt(IDC_TICKLE_EDIT_VIDEO, m_tickle_manager->GetClientTickleInterval(m_video_manager));
	SetDlgItemInt(IDC_TICKLE_EDIT_NOTIFICATION, m_tickle_manager->GetClientTickleInterval(m_notification_manager));
	SetDlgItemInt(IDC_TICKLE_EDIT_SOUND, m_tickle_manager->GetClientTickleInterval(m_sound_manager));
	SetDlgItemInt(IDC_TICKLE_EDIT_MUSIC, m_tickle_manager->GetClientTickleInterval(m_music_manager));
	SetDlgItemInt(IDC_TICKLE_EDIT_EVENT, m_tickle_manager->GetClientTickleInterval(m_event_manager));
}
