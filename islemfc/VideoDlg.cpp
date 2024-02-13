#include "VideoDlg.h"

#include "islegame.h"
#include "res/resource.h"

#include <legoomni.h>
#include <legovideomanager.h>

BEGIN_MESSAGE_MAP(CVideoDialog, CDialog)
ON_COMMAND(IDC_VIDEO_CHECKBOX_FULL_SCREEN, SynchronizeControls)
ON_COMMAND(IDC_VIDEO_CHECKBOX_FLIP_SURFACES, SynchronizeControls)
ON_COMMAND(IDC_VIDEO_CHECKBOX_BACK_BUFFERS, SynchronizeControls)
ON_COMMAND(IDC_VIDEO_RADIOBUTTON_8BPP, SynchronizeControls)
ON_COMMAND(IDC_VIDEO_RADIOBUTTON_16BPP, SynchronizeControls)
END_MESSAGE_MAP()

// FUNCTION: MAINR 0x00405c50
CVideoDialog::CVideoDialog(CWnd* pParentWnd) : CDialog(IDD_VIDEO, pParentWnd)
{
}

// FUNCTION: MAINR 0x00405d30
BOOL CVideoDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	CListBox* device_list = (CListBox*) GetDlgItem(IDC_VIDEO_LISTBOX_DEVICES);

#if 0
	// No access to Direct3DDeviceInfo* in final LEGO1.DLL
	MxDirect3D* d3d = ((LegoVideoManager*) LegoOmni::GetInstance()->GetVideoManager())->GetDirect3D();
	Direct3DDeviceInfo* dev_info = NULL;
	for (int i = 0; (dev_info = d3d->GetDeviceInfo(dev_info)); i += 1) {
		device_list->AddString(dev_info->m_deviceName);
		if (g_game->m_video_param->GetDeviceName() == dev_info->m_deviceName) {
			list_box->SetCurSel(i);
		}
	}
#else
	device_list->AddString("device");
	device_list->SetCurSel(0);
#endif
	CheckRadioButton(
		IDC_VIDEO_RADIOBUTTON_8BPP,
		IDC_VIDEO_RADIOBUTTON_16BPP,
		g_game->m_video_param.Flags().Get16Bit() ? IDC_VIDEO_RADIOBUTTON_16BPP : IDC_VIDEO_RADIOBUTTON_8BPP
	);

	CheckDlgButton(IDC_VIDEO_CHECKBOX_FULL_SCREEN, !!g_game->m_video_param.Flags().GetFullScreen());
	CheckDlgButton(IDC_VIDEO_CHECKBOX_FLIP_SURFACES, !!g_game->m_video_param.Flags().GetFlipSurfaces());
	CheckDlgButton(IDC_VIDEO_CHECKBOX_BACK_BUFFERS, !!g_game->m_video_param.Flags().GetBackBuffers());
	CheckDlgButton(IDC_VIDEO_CHECKBOX_WIDE_ANGLE, !!g_game->m_video_param.Flags().GetWideViewAngle());
	SynchronizeControls();
	return TRUE;
}

// FUNCTION: MAINR 0x00405ec0
void CVideoDialog::OnOK()
{
	CDialog::OnOK();
	g_game->m_video_param.Flags().SetFullScreen(IsDlgButtonChecked(IDC_VIDEO_CHECKBOX_FULL_SCREEN));
	g_game->m_video_param.Flags().SetFlipSurfaces(IsDlgButtonChecked(IDC_VIDEO_CHECKBOX_FLIP_SURFACES));
	g_game->m_video_param.Flags().SetBackBuffers(IsDlgButtonChecked(IDC_VIDEO_CHECKBOX_BACK_BUFFERS));
	g_game->m_video_param.Flags().Set16Bit(IsDlgButtonChecked(IDC_VIDEO_RADIOBUTTON_16BPP));
	g_game->m_video_param.Flags().SetWideViewAngle(IsDlgButtonChecked(IDC_VIDEO_CHECKBOX_WIDE_ANGLE));

	CListBox* device_list = (CListBox*) GetDlgItem(IDC_VIDEO_LISTBOX_DEVICES);
	int dev_i = device_list->GetCurSel();
	int dev_i_len = device_list->GetTextLen(dev_i);
	char* dev_name = new char[dev_i_len + 1];
	device_list->GetText(dev_i, dev_name);
#if 0
	// No access to Direct3DDeviceInfo* in final LEGO1.DLL
	MxDirect3D* d3d = ((LegoVideoManager*) LegoOmni::GetInstance()->GetVideoManager())->GetDirect3D();
	Direct3DDeviceInfo* dev_info = NULL;
	while ((dev_info = d3d->GetDeviceInfo(dev_info))) {
		if (strcmp(dev_info->m_deviceName, dev_name) == 0) {
			break;
		}
		device_list->AddString(dev_info->m_deviceName);
		if (g_game->m_video_param->GetDeviceName() == dev_info->m_deviceName) {
			list_box->SetCurSel(i);
		}
	}
	m_video_param->SetDirecdt3DDeviceInfo(dev_info);
	delete[] dev_name;
#else
	delete[] dev_name;
#endif
}

// FUNCTION: MAINR 0x00406010
void CVideoDialog::SynchronizeControls()
{
	if (!IsDlgButtonChecked(IDC_VIDEO_CHECKBOX_FULL_SCREEN)) {
		CheckDlgButton(IDC_VIDEO_CHECKBOX_FLIP_SURFACES, FALSE);
	}
	if (IsDlgButtonChecked(IDC_VIDEO_CHECKBOX_FLIP_SURFACES)) {
		CheckDlgButton(IDC_VIDEO_CHECKBOX_BACK_BUFFERS, TRUE);
	}
	GetDlgItem(IDC_VIDEO_CHECKBOX_FLIP_SURFACES)->EnableWindow(IsDlgButtonChecked(IDC_VIDEO_CHECKBOX_FULL_SCREEN));
	GetDlgItem(IDC_VIDEO_CHECKBOX_BACK_BUFFERS)->EnableWindow(!IsDlgButtonChecked(IDC_VIDEO_CHECKBOX_FLIP_SURFACES));
	GetDlgItem(IDC_VIDEO_RADIOBUTTON_8BPP)->EnableWindow(!IsDlgButtonChecked(IDC_VIDEO_CHECKBOX_FULL_SCREEN));
	GetDlgItem(IDC_VIDEO_RADIOBUTTON_16BPP)->EnableWindow(!IsDlgButtonChecked(IDC_VIDEO_CHECKBOX_FULL_SCREEN));
}
