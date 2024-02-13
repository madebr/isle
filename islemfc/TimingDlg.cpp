#include "TimingDlg.h"

#include <legoomni.h>
#include <legovideomanager.h>
#include <mxticklemanager.h>
#include <realtimeview.h>

#include "res/resource.h"

struct event_measurement {
	int start;
	int time;
	int count;
};

// GLOBAL: MAINR 0x0040e678
event_measurement g_event_lbutton_down;

// GLOBAL: MAINR 0x0x0040e684
event_measurement g_event_mouse_move;

BEGIN_MESSAGE_MAP(CTimingDialog, CDialog)
ON_WM_HSCROLL()
ON_WM_CLOSE()
END_MESSAGE_MAP()

// FUNCTION: MAINR 0x00408dc0
CTimingDialog::CTimingDialog(CWnd* pParentWnd) : CDialog(IDD_TIMING)
{
}

// FUNCTION: MAINR 0x004098b0
BOOL CTimingDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_unk0x0e4.SetRange(0, 5000);
	m_unk0x0e4.SetTicFreq(1000);
	m_unk0x0e4.SetPageSize(100);
	m_unk0x0e4.SetPos(1000 * RealtimeView::GetUserMaxLOD());
	LegoOmni::GetInstance()->GetTickleManager()->SetClientTickleInterval(this, 2000);
	CString s;
	s.Format("%06f", RealtimeView::GetPartsThreshold());
	m_unk0x524.SetWindowText(s);
	Synchronize();
	return TRUE;
}

// FUNCTION: MAINR 0x00409fb0
void CTimingDialog::MeasureBefore(MxU16 p_event)
{
	switch (p_event) {
	case 1002:
		g_event_lbutton_down.start = GetTickCount();
		break;
	case 1003:
		g_event_mouse_move.start = GetTickCount();
		break;
	}
}

// FUNCTION: MAINR 0x00409680
void CTimingDialog::DoDataExchange(CDataExchange* pDDx)
{
	DDX_Control(pDDx, IDC_STATIC_AVG_3DRENDER, m_unk0x064);
	DDX_Control(pDDx, IDC_STATIC_UNK1063, m_unk0x0a4);
	DDX_Control(pDDx, IDC_SLIDER_SPEED, m_unk0x0e4);
	DDX_Control(pDDx, IDC_STATIC_MIN_FRAMETIME, m_unk0x124);
	DDX_Control(pDDx, IDC_STATIC_MAX_FRAMETIME, m_unk0x164);
	DDX_Control(pDDx, IDC_STATIC_AVG_FRAMETIME, m_unk0x1a4);
	DDX_Control(pDDx, IDC_STATIC_REQ_FRAMETIME, m_unk0x1e4);
	DDX_Control(pDDx, IDC_STATIC_MIN_FRAMERATE, m_unk0x224);
	DDX_Control(pDDx, IDC_STATIC_MAX_FRAMERATE, m_unk0x264);
	DDX_Control(pDDx, IDC_STATIC_AVG_FRAMERATE, m_unk0x2a4);
	DDX_Control(pDDx, IDC_STATIC_REQ_FRAMERATE, m_unk0x2e4);
	DDX_Control(pDDx, IDC_STATIC_QTY_BUTTON_DOWN, m_unk0x324);
	DDX_Control(pDDx, IDC_STATIC_TIM_BUTTON_DOWN, m_unk0x364);
	DDX_Control(pDDx, IDC_STATIC_TIM_EVNT_BUTTON_DOWN, m_unk0x3a4);
	DDX_Control(pDDx, IDC_STATIC_TIM_FRM_BUTTON_DOWN, m_unk0x3e4);
	DDX_Control(pDDx, IDC_STATIC_QTY_MOUSEMOVE, m_unk0x424);
	DDX_Control(pDDx, IDC_STATIC_TIM_MOUSEMOVE, m_unk0x464);
	DDX_Control(pDDx, IDC_STATIC_TIM_EVNT_MOUSEMOVE, m_unk0x4a4);
	DDX_Control(pDDx, IDC_STATIC_TIM_FRM_MOUSEMOVE, m_unk0x4e4);
	DDX_Control(pDDx, IDC_EDIT_PARTS_THRESHOLD, m_unk0x524);
	DDX_Control(pDDx, IDC_STATIC_POLYGON_RATE, m_unk0x564);
}

// FUNCTION: MAINR 0x00409fe0
void CTimingDialog::MeasureAfter(MxU16 p_event)
{
	switch (p_event) {
	case 1002:
		g_event_lbutton_down.count += 1;
		g_event_lbutton_down.time += GetTickCount() - g_event_lbutton_down.start;
		break;
	case 1003:
		g_event_mouse_move.count += 1;
		g_event_mouse_move.time += GetTickCount() - g_event_mouse_move.start;
		break;
	}
}

// FUNCTION: MAINR 0x00409830
void CTimingDialog::FUN_00409830(undefined4* p_unk)
{
	m_unk0x5a4 = p_unk;
	Synchronize();
}

// FUNCTION: MAINR 0x004099d0
void CTimingDialog::OnClose()
{
	CWnd::ShowWindow(FALSE);
}

// FUNCTION: MAINR 0x00409850
void CTimingDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	RealtimeView::SetUserMaxLOD(m_unk0x0e4.GetPos() * 0.001);
	Synchronize();
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

// FUNTION: MAINR 0x004099e0
void CTimingDialog::Synchronize()
{
	CString max_lod;
	CString unk0x54;
	CString input_ms;
	CString input_fps;
	CString input2_ms;
	CString input2_fps;
	CString input3_ms;
	CString input3_fps;
	CString video_ms;
	CString video_fps;

	float v;
	if (m_unk0x5a4) {
		// v = m_unk0x054->m_unk0x29c; // FIXME: what is m_unk0x54?
		v = 0.f;
	}
	else {
		v = 0.f;
	}
	max_lod.Format("%f", RealtimeView::GetUserMaxLOD());
	unk0x54.Format("%ld ms", v);
	input_ms.Format("%4d ms", m_input_presenter.m_unk0x3c);
	if (m_input_presenter.m_unk0x3c) {
		input_fps.Format("%3.1f fps", 1000.f / m_input_presenter.m_unk0x3c);
	}
	input2_ms.Format("%4d ms", m_input_presenter.m_unk0x40);
	if (m_input_presenter.m_unk0x40) {
		input2_fps.Format("%3.1f fps", 1000.f / m_input_presenter.m_unk0x40);
	}
	int d;
	if (m_input_presenter.m_unk0x4c) {
		d = m_input_presenter.m_unk0x48 / m_input_presenter.m_unk0x4c;
	}
	else {
		d = 0;
	}
	input3_ms.Format("%d ms", d);
	if (d) {
		input3_fps.Format("%3.1f fps", 1000.f / d);
	}
	int vid_ms =
		LegoOmni::GetInstance()->GetTickleManager()->GetClientTickleInterval(LegoOmni::GetInstance()->GetVideoManager()
		);
	video_ms.Format("%4d ms", vid_ms);
	if (vid_ms) {
		video_fps.Format("%3.1f fps", 1000.f / vid_ms);
	}
	m_input_presenter.m_unk0x50 = TRUE;
	m_unk0x0a4.SetWindowTextA(max_lod);
	m_unk0x064.SetWindowTextA(unk0x54);
	m_unk0x124.SetWindowTextA(input_ms);
	m_unk0x164.SetWindowTextA(input2_ms);
	m_unk0x1a4.SetWindowTextA(input3_ms);
	m_unk0x1e4.SetWindowTextA(video_ms);
	m_unk0x224.SetWindowTextA(input_fps);
	m_unk0x264.SetWindowTextA(input2_fps);
	m_unk0x2a4.SetWindowTextA(input3_fps);
	m_unk0x2e4.SetWindowTextA(video_fps);
	m_unk0x564.SetWindowTextA("not measured");

	CString s;

	s.Format("%d", g_event_lbutton_down.count);
	m_unk0x324.SetWindowTextA(s);
	s.Format("%d", g_event_lbutton_down.time);
	m_unk0x364.SetWindowTextA(s);
	if (g_event_lbutton_down.count) {
		s.Format("%d ms", g_event_lbutton_down.time / g_event_lbutton_down.count);
	}
	else {
		s.Format("* ms");
	}
	m_unk0x3a4.SetWindowTextA(s);
	s.Format("* ms");
	m_unk0x3e4.SetWindowTextA(s);

	s.Format("%d", g_event_mouse_move.count);
	m_unk0x424.SetWindowTextA(s);
	s.Format("%d", g_event_mouse_move.time);
	m_unk0x464.SetWindowTextA(s);
	if (g_event_mouse_move.count) {
		s.Format("%d ms", g_event_mouse_move.time / g_event_mouse_move.count);
	}
	else {
		s.Format("* ms");
	}
	m_unk0x4a4.SetWindowTextA(s);
	s.Format("* ms");
	m_unk0x4e4.SetWindowTextA(s);
	GetDlgItemTextA(IDC_EDIT_PARTS_THRESHOLD, s);
	float f = atof(s);
	if (f < 0.f) {
		f = 0;
		s.Format("06f", 0.f);
		m_unk0x524.SetWindowTextA(s);
	}
	RealtimeView::SetPartsThreshold(f);
}
