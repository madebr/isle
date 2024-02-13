#include "islegame.h"

#include "main.h"
#include "MainFrameWnd.h"
#include "TimeAverage.h"

#include <legoomni.h>
#include <legovideomanager.h>
#include <mxdirectx/mxdirectdraw.h>
#include <mxomnicreateflags.h>
#include <mxomnicreateparam.h>
#include <mxticklemanager.h>
#include <mxtimer.h>
#include <mxutil.h>

IsleGame* g_game;

// FUNCTION: MAINR 0x00402e50
IsleGame::IsleGame() {
    m_activated = TRUE;
    SetOmniUserMessage(Error);
    m_running = FALSE;
    m_unk0x04 = 0;
    m_timing_dialog = NULL;
    m_navigation_dialog = NULL;
    m_time_average = NULL;
    m_unk0x38 = 0;
    m_unk0x08 = 10;
//    MxRect32 (0, 0, 640, 480);
    MxVideoParam video_param(MxRect32(0, 0, 640, 480), NULL, 1, MxVideoParamFlags());
    m_video_param = video_param;
    m_video_param.Flags().Set16Bit(MxDirectDraw::GetPrimaryBitDepth() == 16);
    m_pMainWnd = (CMainFrameWnd*)g_theApp.m_pMainWnd;
    LegoOmni::CreateInstance();
}

// FUNCTION: MAINR 0x00407950
void IsleGame::Error(const char* p_message, int p_message_type)
{
	int type;

	switch (p_message_type) {
	case 0:
		type = MB_ICONASTERISK;
		break;
	case 1:
		type = MB_ICONHAND;
		break;
	case 2:
		type = MB_ICONHAND | MB_OKCANCEL;
		break;
	}
	int res = MessageBoxA(NULL, p_message, "Lego Critical Error", type);
	if (p_message_type == 1 || res == IDCANCEL) {
		abort();
	}
}

// FUNCTION: MAINR 0x004034b0
void IsleGame::SetFlags(
	BOOL p_fullscreen,
	BOOL p_flip,
	BOOL p_use_smem,
	BOOL p_d8,
	BOOL p_d16,
	BOOL p_rgb,
	BOOL p_usehw
)
{
	m_video_param.Flags().SetFullScreen(p_fullscreen);
	m_video_param.Flags().SetFlipSurfaces(p_flip);
	m_video_param.Flags().SetBackBuffers(p_use_smem);
	m_video_param.Flags().SetF1bit4(p_rgb);
	m_video_param.Flags().SetF1bit7(p_usehw);
	m_video_param.Flags().SetWideViewAngle(p_d8);
	m_video_param.Flags().Set16Bit(p_d16);
}

// FUNCTION: MAINR 0x004032f0
void IsleGame::SetupLegoOmni()
{
	char media_path[256];
	GetProfileStringA("Anventures on LEGO Island", "MediaPath", "", media_path, sizeof(media_path));
	m_pMainWnd->ConfigureWindow(
		m_video_param.GetRect().GetRight() - m_video_param.GetRect().GetLeft(),
		m_video_param.GetRect().GetBottom() - m_video_param.GetRect().GetTop(),
		!m_video_param.Flags().GetFullScreen()
	);
	HWND wnd = NULL;
	if (m_pMainWnd) {
		wnd = m_pMainWnd->m_hWnd;
	}
	MxOmniCreateParam create_param(media_path, wnd, m_video_param, MxOmniCreateFlags());
	MxResult result = LegoOmni::GetInstance()->Create(create_param);
#if 1
	if (result != SUCCESS) {
		MessageBoxA(NULL, "LegoOmni::Create failed", "LegoOmni::Create failed", MB_OK);
	}
#endif
	m_time_average = new TimeAverage(TRUE);
	LegoOmni::GetInstance()->GetTickleManager()->SetClientTickleInterval(
		LegoOmni::GetInstance()->GetVideoManager(),
		10
	);
}

// GLOBAL: MAINR 0x0040e040
MxLong g_prev_time;

// FUNCTION: MAINR 0x004037e0
void IsleGame::MaybeTickle(BOOL p_sleep)
{
	if (LegoOmni::GetInstance() && LegoOmni::GetInstance()->GetTickleManager()
			&& LegoOmni::GetInstance() && LegoOmni::GetInstance()->GetTimer()) {
#if 0
		// MxTimer::GetTime() is an inlined function, using non-exported symbols
		MxS32 time = LegoOmni::GetInstance()->GetTimer()->GetTime();
#else
		MxS32 time = LegoOmni::GetInstance()->GetTimer()->GetRealTime();
#endif
		if (time < g_prev_time) {
			g_prev_time = -g_game->m_unk0x08;
		}
		if (g_game->m_unk0x08 + g_prev_time < time) {
			LegoOmni::GetInstance()->GetTickleManager()->Tickle();
			g_prev_time = time;
		}
	}
}

// FUNCTION: MAINR 0x004036d0
void IsleGame::Configure(MxVideoParam& p_video_param)
{
	MxVideoParam& current_video_param = LegoOmni::GetInstance()->GetVideoManager()->GetVideoParam();
	MxRect32& current_rect = current_video_param.GetRect();
	MxRect32& new_rect = p_video_param.GetRect();

	MxVideoParamFlags& current_flags = current_video_param.Flags();
	MxVideoParamFlags& new_flags = p_video_param.Flags();

	int changed =
		current_rect.GetLeft() != new_rect.GetLeft() || current_rect.GetTop() != new_rect.GetTop() ||
		current_rect.GetRight() != new_rect.GetRight() || current_rect.GetBottom() != new_rect.GetBottom() ||
		(current_flags.GetFullScreen() != new_flags.GetFullScreen() ||
		 current_flags.GetFlipSurfaces() != new_flags.GetFlipSurfaces() ||
		 current_flags.GetBackBuffers() != new_flags.GetBackBuffers()) ||
		(p_video_param.GetPalette() != NULL && !(*current_video_param.GetPalette() == *p_video_param.GetPalette())) ||
		(current_flags.Get16Bit() != new_flags.Get16Bit() ||
		 current_flags.GetWideViewAngle() != new_flags.GetWideViewAngle());
	if (changed) {
		LegoOmni::GetInstance()->GetVideoManager()->Destroy();
		MxS32 width = new_rect.GetRight() - new_rect.GetLeft();
		MxS32 height = new_rect.GetBottom() - new_rect.GetTop();
		if (new_flags.GetF1bit3()) {
			width *= 2;
			height *= 2;
		}
		int not_topmost = !new_flags.GetFullScreen() &&
						  (GetSystemMetrics(SM_CXSCREEN) != width || GetSystemMetrics(SM_CYSCREEN) != height);
		m_pMainWnd->ConfigureWindow(width, height, not_topmost);
		m_pMainWnd->ShowWindow(SW_SHOW);
		LegoOmni::GetInstance()->GetVideoManager()->Create(p_video_param, 100, FALSE);
	}
}
