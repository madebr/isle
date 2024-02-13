#if !defined(AFX_TIMINGDLG_H)
#define AFX_TIMINGDLG_H

#include "StdAfx.h"
#include "TimeAverage.h"

#include <mxcore.h>
#include <mxtypes.h>

#include <decomp.h>

// VTABLE 0x0040c560
class CTimingDialog : public CDialog, public MxCore {
public:
	CTimingDialog(CWnd* pParentWnd);
	static void MeasureBefore(MxU16 p_event);
	static void MeasureAfter(MxU16 p_unk1);

	void FUN_00409830(undefined4* p_unk);

private:
	void Synchronize();

protected:
	void DoDataExchange(CDataExchange* pDDx) override;
	BOOL OnInitDialog() override;
	afx_msg void OnClose();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	DECLARE_MESSAGE_MAP()

public:
	CStatic m_unk0x064;
	CStatic m_unk0x0a4;
	CSliderCtrl m_unk0x0e4;
	CStatic m_unk0x124;
	CStatic m_unk0x164;
	CStatic m_unk0x1a4;
	CStatic m_unk0x1e4;
	CStatic m_unk0x224;
	CStatic m_unk0x264;
	CStatic m_unk0x2a4;
	CStatic m_unk0x2e4;
	CStatic m_unk0x324;
	CStatic m_unk0x364;
	CStatic m_unk0x3a4;
	CStatic m_unk0x3e4;
	CStatic m_unk0x424;
	CStatic m_unk0x464;
	CStatic m_unk0x4a4;
	CStatic m_unk0x4e4;
	CStatic m_unk0x524;
	CStatic m_unk0x564;
	undefined4* m_unk0x5a4;
	TimeAverage m_input_presenter;
};

// SYNTHETIC: MAINR 0x004093b0
// CTimingDialog::`scalar deleting destructor'

// FUNCTION: MAINR 0x00409820
// CTimingDialog::GetMessageMap

// GLOBAL: MAINR 0x0040c4d8
// CTimingDialog::messageMap

// GLOBAL: MAINR 0x0040c4e0
// CTimingDialog::_messageEntries

#endif // !defined(AFX_TIMINGDLG_H)
