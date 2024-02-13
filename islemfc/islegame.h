#if !defined(ISLEGAME_H)
#define ISLEGAME_H

#include "StdAfx.h"

#include <mxstreamer.h>
#include <mxtypes.h>
#include <mxvideoparam.h>

#include <decomp.h>

class CMainFrameWnd;
class CNavigationDialog;
class CTimingDialog;
class TimeAverage;

class IsleGame {
public:
    IsleGame();
	void SetFlags(BOOL p_fullscreen, BOOL p_flip, BOOL p_use_smem, BOOL p_d8, BOOL p_d16, BOOL p_rgb, BOOL p_usehw);
	void Configure(MxVideoParam& p_video_params);
	void SetupLegoOmni();
	void MaybeTickle(BOOL p_sleep);

	struct PathModePair {
		PathModePair(CString p_path, MxStreamer::OpenMode p_mode) : m_path(p_path), m_mode(p_mode) {}
		CString m_path;
		MxStreamer::OpenMode m_mode;
	};

private:
    static void IsleGame::Error(const char* p_message, int p_message_type);
public:

	BOOL m_running;
	undefined4 m_unk0x04;
	MxLong m_unk0x08;
	MxVideoParam m_video_param;
	CTimingDialog* m_timing_dialog;
	CNavigationDialog* m_navigation_dialog;
	TimeAverage* m_time_average;
	undefined4 m_unk0x38;
	CPtrList m_actions;
	CPtrList m_paths;
	CMainFrameWnd* m_pMainWnd;
	undefined4 m_unk0x78;
	BOOL m_activated;
};

// GLOBAL: MAINR 0x0040e7cc
extern IsleGame* g_game;

#endif // !defined(ISLEGAME_H)
