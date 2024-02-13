#include "SetMusicVolumeDlg.h"

#include "res/resource.h"

// FUNCTION: MAINR 0x00404740
CSetMusicVolumeDialog::CSetMusicVolumeDialog(CWnd* pParentWnd) : CDialog(IDD_MUSIC_VOLUME, pParentWnd)
{
}

// FUNCTION: MAINR 0x00404820
BOOL CSetMusicVolumeDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;
}

// FUNCTION: MAINR 0x00404830
void CSetMusicVolumeDialog::OnOK()
{
	m_volume = GetDlgItemInt(IDC_EDIT_MUSIC_VOLUME_VOLUME, NULL, TRUE);
	CDialog::OnOK();
}
