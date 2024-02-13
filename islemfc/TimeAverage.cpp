#include "TimeAverage.h"

#include <legoinputmanager.h>
#include <legoomni.h>
#include <legovideomanager.h>
#include <mxtimer.h>

// FUNCTION: MAINR 0x004089b0
TimeAverage::TimeAverage()
{
	Init(0);
}

// FUNCTION: MAINR 0x00408a40
TimeAverage::TimeAverage(MxBool p_register)
{
	Init(p_register);
}

// FUNCTION: MAINR 0x00408ab0
TimeAverage::~TimeAverage()
{
	LegoOmni::GetInstance()->GetInputManager()->UnRegister(this);
	LegoOmni::GetInstance()->GetVideoManager()->UnregisterPresenter(*this);
}

// FUNCTION: MAINR 0x00408b30
void TimeAverage::Init(MxBool p_register)
{
	memset(m_unk0x54, 0, sizeof(m_unk0x54));
	m_unk0x50 = TRUE;
	if (p_register) {
		LegoOmni::GetInstance()->GetInputManager()->Register(this);
	} else {
		LegoOmni::GetInstance()->GetVideoManager()->RegisterPresenter(*this);
	}
}

// FUNCTION: MAINR 0x00408c60
MxLong TimeAverage::Notify(MxParam& p_param)
{
	MxNotificationParam& notif = (MxNotificationParam&) p_param;
	if (notif.GetType() == 1000) { // FIXME: magic value
		LegoEventNotificationParam& evnotif = (LegoEventNotificationParam&) notif;
		if (evnotif.GetKey() == 's' || evnotif.GetKey() == 'S') {
			LegoOmni::GetInstance()->GetVideoManager()->UnregisterPresenter(*this);
		}
		else if (evnotif.GetKey() == 'p' || evnotif.GetKey() == 'P') {
			LegoOmni::GetInstance()->GetVideoManager()->UnregisterPresenter(*this);
			WriteFrameTimes();
			m_unk0x50 = TRUE;
			return 0;
		}
	}
	return 0;
}

// FUNCTION: MAINR 0x00408b70
MxResult TimeAverage::Tickle()
{
#if 0
	// MxTimer::GetTime() is not exported from final LEGO1.DLL
	MxLong time = LegoOmni::GetInstance()->GetTimer()->GetTime();
#else
	MxLong time = LegoOmni::GetInstance()->GetTimer()->GetRealTime();
#endif
	if (m_unk0x50) {
		m_unk0x3c = 9999;
		m_unk0x40 = 0;
		m_unk0x48 = 0;
		m_unk0x4c = 0;
		m_unk0x50 = FALSE;
		m_unk0x44 = time;
	}
	MxLong passed = time - m_unk0x44;
	if (passed < 0) {
		passed = 0;
	}
	m_unk0x44 = time;
	m_unk0x48 = m_unk0x48 + passed;
	m_unk0x4c += 1;
	if (passed < m_unk0x3c) {
		m_unk0x3c = passed;
	}
	if (passed < m_unk0x40) {
		m_unk0x40 = passed;
	}
	int index = passed / 10;
	if (index >= _countof(m_unk0x54)) {
		index = _countof(m_unk0x54) - 1;
	}
	m_unk0x54[index] += 1;
	return 0;
}

// FUNCTION: MAINR 0x00408bf0
void TimeAverage::WriteFrameTimes()
{
	FILE* f = fopen("\\FRM_TIME.TXT", "w");
	if (f) {
		for (int i = 0; i < _countof(m_unk0x54); i++) {
			fprintf(f, "%d:\t%d\n", 10 * (i + 1), m_unk0x54[i]);
		}
		fclose(f);
	}
	memset(m_unk0x54, 0, sizeof(m_unk0x54));
}
