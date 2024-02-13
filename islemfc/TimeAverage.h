#if !defined(TIMEAVERAGE_H)
#define TIMEAVERAGE_H

#include <compat.h>
#include <decomp.h>
#include <mxpresenter.h>

class TimeAverage : public MxPresenter {
public:
	TimeAverage();
	TimeAverage(MxBool p_register);
	~TimeAverage() override;
	void WriteFrameTimes();

	void Init(MxBool p_register);

	// FUNCTION: MAINR 0x00408db0
	inline const char* ClassName() const override
	{
		// STRING: MAINR 0x0040e66c
		return "TimeAverage";
	}
	MxLong Notify(MxParam& p_param) override;
	MxResult Tickle() override;

	MxLong m_unk0x3c;
	MxLong m_unk0x40;
	MxLong m_unk0x44;
	MxLong m_unk0x48;
	int m_unk0x4c;
	BOOL m_unk0x50;
	undefined4 m_unk0x54[100];
};

#endif // !defined(TIMEAVERAGE_H)
