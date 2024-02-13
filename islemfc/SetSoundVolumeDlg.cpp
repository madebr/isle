#include "SetSoundVolumeDlg.h"

#include "res/resource.h"

// FUNCTION: MAINR 0x00404630
CSetSoundVolumeDialog::CSetSoundVolumeDialog(CWnd* pParentWnd) : CDialog(IDD_SOUND_VOLUME, pParentWnd)
{
}

// FUNCTION: MAINR 0x00404710
BOOL CSetSoundVolumeDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	return TRUE;
}

// FUNCTION: MAINR 00404720
void CSetSoundVolumeDialog::OnOK()
{
	m_volume = GetDlgItemInt(IDC_EDIT_SOUND_VOLUME_VOLUME, NULL, TRUE);
	CDialog::OnOK();
}
