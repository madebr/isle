#if !defined(AFX_MAINFRAMEWND_H)
#define AFX_MAINFRAMEWND_H

#include "StdAfx.h"
#include "compat.h"

#include <mxstreamer.h>

class CMainFrameWnd : public CFrameWnd {
public:
	CMainFrameWnd();

	LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam) override;
	void ConfigureWindow(int p_width, int p_height, BOOL p_not_topmost);
	void OpenIFF(MxStreamer::OpenMode p_mode);

	afx_msg void OnOpenIffFromDisk();
	afx_msg void OnOpenIffFromRAM();
	afx_msg void OnOpenPalette();
	afx_msg void OnSetMediaPath();
	afx_msg void OnGetVariable();
	afx_msg void OnSetVariable();
	afx_msg void OnSetSoundVolume();
	afx_msg void OnSetMusicVolume();
	afx_msg void OnActions();
	afx_msg void OnVideo();
	afx_msg void OnTickle();
	afx_msg void OnRealism();
	afx_msg void OnUpdateRealism(CCmdUI* pCmdUI);
	afx_msg void OnNavigation();
	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnExit();
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnPaint();
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

protected:
	DECLARE_MESSAGE_MAP()
};

// FUNCTION: MAINR 0x00407430
// CMainFrameWnd::GetMessageMap

// GLOBAL: MAINR 0x0040b548
// CMainFrameWnd::messageMap

// GLOBAL: MAINR 0x0040b550
// CMainFrameWnd::_messageEntries

#endif // !defined(AFX_MAINFRAMEWND_H)
