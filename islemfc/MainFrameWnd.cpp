#include "MainFrameWnd.h"

#include "ActionsDlg.h"
#include "GetVariableDlg.h"
#include "MainContextMenu.h"
#include "MediaPathDlg.h"
#include "NavigationDlg.h"
#include "SetMusicVolumeDlg.h"
#include "SetSoundVolumeDlg.h"
#include "SetVariableDlg.h"
#include "TickleDlg.h"
#include "TimingDlg.h"
#include "VideoDlg.h"
#include "islegame.h"
#include "res/resource.h"

#include <legoentity.h>
#include <legoinputmanager.h>
#include <legoomni.h>
#include <legosoundmanager.h>
#include <legovideomanager.h>
#include <mxbitmap.h>
#include <mxdsaction.h>
#include <mxmusicmanager.h>
#include <mxstreamer.h>
#include <mxtypes.h>

BEGIN_MESSAGE_MAP(CMainFrameWnd, CFrameWnd)
ON_COMMAND(IDA_OPEN_IFF_DISK, OnOpenIffFromDisk)
ON_COMMAND(IDA_OPEN_IFF_RAM, OnOpenIffFromRAM)
ON_COMMAND(IDA_OPEN_PALETTE, OnOpenPalette)
ON_COMMAND(IDA_DLG_SET_MEDIA_PATH, OnSetMediaPath)
ON_COMMAND(IDA_DLG_GET_VARIABLE, OnGetVariable)
ON_COMMAND(IDA_DLG_SET_VARIABLE, OnSetVariable)
ON_COMMAND(IDA_DLG_SOUND_VOLUME, OnSetSoundVolume)
ON_COMMAND(IDA_DLG_MUSIC_VOLUME, OnSetMusicVolume)
ON_COMMAND(IDA_DLG_ACTIONS, OnActions)
ON_COMMAND(IDA_DLG_VIDEO, OnVideo)
ON_COMMAND(IDA_DLG_TICKLE, OnTickle)
ON_COMMAND(IDA_DLG_REALISM, OnRealism)
ON_UPDATE_COMMAND_UI(IDA_DLG_REALISM, OnUpdateRealism)
ON_COMMAND(IDA_DLG_NAVIGATION, OnNavigation)
ON_COMMAND(IDA_DLG_START, OnStart)
ON_COMMAND(IDA_DLG_STOP, OnStop)
ON_COMMAND(IDA_DLG_EXIT, OnExit)
ON_WM_INITMENUPOPUP()
ON_WM_PAINT()
ON_WM_CLOSE()
ON_WM_QUERYNEWPALETTE()
ON_WM_PALETTECHANGED()
ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// FUNCTION: MAINR 0x00403880
CMainFrameWnd::CMainFrameWnd()
{
	Create(NULL, "Main");
}

// FUNCTION: MAINR 0x00403aa0
LRESULT CMainFrameWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	NotificationId notification;
	int keyCode = 0;
	switch (message) {
	case WM_KEYDOWN:
		notification = (NotificationId) 1000; // FIXME
		keyCode = (MxU8) wParam;
		if (wParam == VK_ESCAPE) {
			OnExit();
		}
		break;
	case WM_ACTIVATEAPP:
		if (g_game != NULL) {
			g_game->m_activated = wParam;
		}
		return CWnd::WindowProc(message, wParam, lParam);
	case WM_TIMER:
		notification = (NotificationId) 1008; // FIXME
		break;
	case WM_MOUSEMOVE:
		notification = (NotificationId) 1003; // FIXME
		break;
	case WM_LBUTTONDOWN:
		notification = (NotificationId) 1002; // FIXME
		if (wParam & (MK_CONTROL | MK_SHIFT) == MK_CONTROL | MK_SHIFT) {
			LegoEntity* entity = PickEntity(LOWORD(lParam), HIWORD(lParam));
			delete entity;
		}
		break;
	default:
		return CWnd::WindowProc(message, wParam, lParam);
	}
	CTimingDialog::MeasureBefore(notification);
	if (LegoOmni::GetInstance()->GetInputManager()) {
		LegoOmni::GetInstance()
			->GetInputManager()
			->QueueEvent(notification, wParam, LOWORD(lParam), HIWORD(lParam), keyCode);
	}
	CTimingDialog::MeasureAfter(notification);
	return 0;
}

// FUNCTION: MAINR 0x00403cd0
void CMainFrameWnd::OnOpenIffFromDisk()
{
	OpenIFF(MxStreamer::OpenMode::e_diskStream);
}

// FUNCTION: MAINR 0x00403ce0
void CMainFrameWnd::OnOpenIffFromRAM()
{
	OpenIFF(MxStreamer::OpenMode::e_RAMStream);
}

// FUNCTION: MAINR 0x00403cf0
void CMainFrameWnd::OnOpenPalette()
{
	CFileDialog file_dialog(
		1,
		"BMP",
		"*.BMP",
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST,
		"Bitmap Files  (*.bmp)|*.BMP||"
	);

	if (file_dialog.DoModal() == IDOK) {
		MxBitmap bitmap;
		if (bitmap.Read(file_dialog.GetPathName()) == 0) {
			MessageBoxA("Unable to open palette file");
		}
		else {
			delete g_game->m_video_param.GetPalette();
			g_game->m_video_param.SetPalette(bitmap.CreatePalette());
		}
	}
}

// FUNCTION: MAINR 0x00403e90
void CMainFrameWnd::OnSetMediaPath()
{
	CMediaPathDialog media_path_dialog;

	if (media_path_dialog.DoModal() == IDOK) {
		CString p = media_path_dialog.m_path;
		LegoOmni::GetInstance()->GetMediaPath() = p;
		WriteProfileStringA("Anventures on LEGO Island", "MediaPath", p);
	}
}

// FUNCTION: MAINR 0x00403fc0
void CMainFrameWnd::OnExit()
{
	DestroyWindow();
}

// FUNCTION: MAINR 0x00403fd0
void CMainFrameWnd::OnStart()
{
	g_game->Configure(g_game->m_video_param);

	for (POSITION pos = g_game->m_actions.GetHeadPosition(); pos; g_game->m_actions.GetNext(pos)) {
		MxDSAction* action = (MxDSAction*) g_game->m_actions.GetAt(pos);
		CString name = action->GetObjectName(); // FIXME: or GetSourceName() ?
		name.ReverseFind('.');
		if (LegoOmni::GetInstance()->Start(action) != SUCCESS) {
			MessageBoxA("LegoOmni:Start() failed");
		}
		g_game->m_running = TRUE;
		g_game->m_unk0x04 = 0;
	}
}

// FUNCTION: MAINR 0x004040c0
void CMainFrameWnd::OnStop()
{
	MxDSAction action;
	action.SetUnknown24(-2);
	LegoOmni::GetInstance()->DeleteObject(action);
	while (LegoOmni::GetInstance()->DoesEntityExist(action)) {
		g_game->MaybeTickle(TRUE);
	}
	g_game->m_running = FALSE;
}

// FUNCTION: MAINR 0x00404170
void CMainFrameWnd::OpenIFF(MxStreamer::OpenMode p_mode)
{
	CFileDialog file_dialog(
		TRUE,
		"SI",
		"*.SI",
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		"Interleaf Files  (*.si)|*.SI||"
	);
	if (file_dialog.DoModal() == IDOK) {
		CString path = file_dialog.GetPathName();
		path.MakeLower();
		int pos_dot = path.ReverseFind('.');
		if (pos_dot == -1) {
			pos_dot = path.GetLength();
		}
		CString name(path, pos_dot);
		MxStreamController* controller = LegoOmni::GetInstance()->GetStreamer()->Open(name, p_mode);
		if (!controller) {
			MessageBoxA("MxStreamer::Open() failed");
		}
		else {
			g_game->m_paths.AddTail(new IsleGame::PathModePair(path, p_mode));
		}
	}
}

// FUNCTION: MAINR 0x00406750
void CMainFrameWnd::OnGetVariable()
{
	CGetVariableDialog dialog(this);
	char buffer[128];

	if (dialog.DoModal() == IDOK) {
		const char* val = LegoOmni::GetInstance()->GetVariableTable()->GetVariable(dialog.m_name);
		if (val[0] == '\0') {
			sprintf(buffer, "%s is undefined", (const char*) dialog.m_name);
		}
		else {
			sprintf(buffer, "%s = %s", (const char*) dialog.m_name, val);
		}
		MessageBoxA(buffer, "Variable");
	}
}

// FUNCTION: MAINR 0x00406890
void CMainFrameWnd::OnSetVariable()
{
	CSetVariableDialog dialog(this);

	if (dialog.DoModal() == IDOK) {
		LegoOmni::GetInstance()->GetVariableTable()->SetVariable(dialog.m_name, dialog.m_value);
	}
}

// FUNCTION: MAINR 0x00406990
void CMainFrameWnd::OnSetSoundVolume()
{
	CSetSoundVolumeDialog dialog(this);

	if (dialog.DoModal() == IDOK) {
		LegoOmni::GetInstance()->GetSoundManager()->SetVolume(dialog.m_volume);
	}
}

// FUNCTION: MAINR 0x00406a60
void CMainFrameWnd::OnSetMusicVolume()
{
	CSetMusicVolumeDialog dialog(this);

	if (dialog.DoModal() == IDOK) {
		LegoOmni::GetInstance()->GetMusicManager()->SetVolume(dialog.m_volume);
	}
}

// FUNCTION: MAINR 0x00406b30
void CMainFrameWnd::OnActions()
{
	CActionsDialog dialog(this);

	if (dialog.DoModal() == IDOK) {
		for (POSITION pos = g_game->m_actions.GetHeadPosition(); pos; g_game->m_actions.GetNext(pos)) {
			delete (MxDSAction*) g_game->m_actions.GetAt(pos);
		}
		g_game->m_actions.RemoveAll();
		// FIXME: THIS IS WRONG!!!!
		while (dialog.m_actions.GetHead() != NULL) {
			g_game->m_actions.AddTail(dialog.m_actions.RemoveHead());
		}
	}
}

// FUNCTION: MAINR 0x00406d40
void CMainFrameWnd::OnVideo()
{
	CVideoDialog dialog(this);

	if (dialog.DoModal() == IDOK) {
		g_game->m_video_param = dialog.m_video_param;
	}
}

// FUNCTION: MAINR 0x00406e40
void CMainFrameWnd::OnTickle()
{
	CTickleDialog dialog(this);

	dialog.DoModal();
}

// FUNCTION: MAINR 0x00407240
void CMainFrameWnd::OnRealism()
{
	if (!g_game->m_timing_dialog) {
		g_game->m_timing_dialog = new CTimingDialog(NULL);
		g_game->m_timing_dialog->Create(MAKEINTRESOURCE(IDD_TIMING));
		// FIXME: what is passed to FUN_00409830?
		// Perhaps LegoOmni::GetInstance()-GetVideoManager()->GetVideoParam().GetVideoParam()->dwRefreshRate ???
		g_game->m_timing_dialog->FUN_00409830(NULL);
	}
	g_game->m_timing_dialog->ShowWindow(::IsWindowVisible(g_game->m_timing_dialog->m_hWndOwner) ? SW_HIDE : SW_SHOW);
}

// FUNCTION: MAINR 0x00407240
void CMainFrameWnd::OnUpdateRealism(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(g_game->m_timing_dialog && ::IsWindowVisible(g_game->m_timing_dialog->m_hWndOwner) ? 1 : 0);
}

// FUNCTION: MAINR 0x00407360
void CMainFrameWnd::OnNavigation()
{
	if (!g_game->m_navigation_dialog) {
		g_game->m_navigation_dialog = new CNavigationDialog(this);
		g_game->m_navigation_dialog->Create(MAKEINTRESOURCE(IDD_NAVIGATION));
	}
	g_game->m_navigation_dialog->ShowWindow(g_game->m_navigation_dialog->IsWindowVisible() ? SW_HIDE : SW_SHOW);
}

// FUNCTION: MAINR 0x00407150
void CMainFrameWnd::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (LegoOmni::GetInstance()->GetVideoManager()->GetVideoParam().Flags().GetFlipSurfaces()) {
		// FIXME: no way to get MxDirectDraw object
		// LegoOmni::GetInstance()->GetVideoManager()->GetDirectDraw()->FlipToGDISurface();
	}
	ClientToScreen(&point);
	;
	CMainContextMenu menu;
	menu.GetSubMenu(0)->TrackPopupMenu(TPM_RIGHTBUTTON, point.x, point.y, this);
}

// FUNCTION: MAINR 0x00407110
void CMainFrameWnd::OnPaletteChanged(CWnd* pFocusWnd)
{
	if (this != pFocusWnd) {
		MxVideoManager* video_manager = LegoOmni::GetInstance()->GetVideoManager();
		if (video_manager) {
			video_manager->RealizePalette(NULL);
			Invalidate(FALSE);
		}
	}
}

// FUNCTION: MAINR 0x004070d0
BOOL CMainFrameWnd::OnQueryNewPalette()
{
	if (LegoOmni::GetInstance()) {
		if (LegoOmni::GetInstance()->GetVideoManager()) {
			LegoOmni::GetInstance()->GetVideoManager()->RealizePalette(NULL);
			Invalidate(FALSE);
			return TRUE;
		}
	}
	return FALSE;
}

// FUNCTION: MAINR 0x00407060
void CMainFrameWnd::OnPaint()
{
	PAINTSTRUCT p;
	CDC* dc = BeginPaint(&p);
	MxRect32 cr;
	::GetClientRect(m_hWndOwner, (RECT*) &cr);
	if (LegoOmni::GetInstance() && LegoOmni::GetInstance()->GetVideoManager()) {
		LegoOmni::GetInstance()->GetVideoManager()->InvalidateRect(cr);
	}
	EndPaint(&p);
}

// FUNCTION: MAINR 0x00406f20
void CMainFrameWnd::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	for (int i = 0; i < pPopupMenu->GetMenuItemCount(); i++) {
		int grayed = 0;
		switch (pPopupMenu->GetMenuItemID(i)) {
		case IDA_DLG_START:
		case IDA_DLG_ACTIONS:
			grayed = g_game->m_running || g_game->m_actions.IsEmpty();
			break;
		case IDA_DLG_STOP:
			grayed = !g_game->m_running;
			break;
		case IDA_DLG_GET_VARIABLE:
		case IDA_DLG_SET_VARIABLE:
		case IDA_OPEN_IFF_DISK:
		case IDA_OPEN_IFF_RAM:
			grayed = g_game->m_running;
			break;
		default:
			continue;
		}
		pPopupMenu->EnableMenuItem(i, MF_BYPOSITION | (grayed ? MF_GRAYED : 0));
	}
}

// FUNCTION: MAINR 0x00403970
void CMainFrameWnd::ConfigureWindow(int p_width, int p_height, BOOL p_not_topmost)
{
	int style, exstyle;
	if (p_not_topmost) {
		style = WS_VISIBLE | WS_BORDER | WS_DLGFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
		exstyle = WS_EX_CLIENTEDGE;
	}
	else {
		style = WS_VISIBLE;
		exstyle = 0;
	}
	// or m_hWnd???
	::SetWindowLongA(m_hWnd, GWL_STYLE, style);
	::SetWindowLongA(m_hWnd, GWL_EXSTYLE, exstyle);
	UpdateWindow();
	GetStyle();
	GetExStyle();
	RECT window_rect;
	::GetWindowRect(m_hWndOwner, &window_rect);
	RECT client_rect;
	GetWindowRect(&client_rect);
	SetWindowPos(
		p_not_topmost ? &CWnd::wndNoTopMost : &CWnd::wndTopMost,
		(GetSystemMetrics(SM_CXSCREEN) - p_width) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - p_height) / 2,
		p_width + window_rect.right - client_rect.right - (window_rect.left - client_rect.left),
		p_height + window_rect.top - client_rect.top - (window_rect.bottom - client_rect.bottom),
		SWP_HIDEWINDOW
	);
}
