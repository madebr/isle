#if !defined(AFX_CONFIG_H)
#define AFX_CONFIG_H

#include "compat.h"
#include "decomp.h"

#include <afxwin.h>
#include <d3d.h>

class MxDeviceEnumerate;
struct MxDevice;
struct MxDriver;

#define currentConfigApp ((CConfigApp*) afxCurrentWinApp)

// SIZE 0x10c
class CConfigApp : public CWinApp {
public:
	CConfigApp();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigApp)

public:
	void Serialize(CArchive& ar) override {}
	void AssertValid() const override {}
	void Dump(CDumpContext& dc) const override {}
	BOOL InitInstance() override;
	int ExitInstance() override;
	//}}AFX_VIRTUAL

	// Implementation

	BOOL WriteReg(const char* p_key, const char* p_value) const;
	BOOL ReadReg(LPCSTR p_key, LPCSTR p_value, DWORD p_size) const;
	BOOL ReadRegBool(LPCSTR p_key, BOOL* p_bool) const;
	BOOL ReadRegInt(LPCSTR p_key, int* p_value) const;
	BOOL FUN_004033d0() const;
	D3DCOLORMODEL GetHardwareDeviceColorModel() const;
	BOOL IsPrimaryDriver() const;
	BOOL ReadRegisterSettings();
	BOOL ValidateSettings();
	DWORD FUN_004037a0() const;
	DWORD FUN_004037e0() const;
	BOOL FUN_00403810();
	void CConfigApp::WriteRegisterSettings() const;

	//{{AFX_MSG(CConfigApp)
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL IsLegoNotRunning();

public:
	MxDeviceEnumerate* m_device_enumerator; // 0x0c4
	MxDriver* m_driver;                     // 0x0c8
    MxDevice* m_device;                     // 0x0cc
	int m_display_bit_depth;                // 0x0d0
	BOOL m_flip_surfaces;                   // 0x0d4
	BOOL m_full_screen;                     // 0x0d8
	BOOL m_3d_video_ram;                    // 0x0dc
	BOOL m_wide_view_angle;                 // 0x0e0
	BOOL m_3d_sound;                        // 0x0e4
	BOOL m_draw_cursor;                     // 0x0e8
	BOOL m_use_joystick;                    // 0x0ec
	int m_joystick_index;                   // 0x0f0
	BOOL m_run_config_dialog;               // 0x0f4
	int m_model_quality;                    // 0x0f8
	int m_texture_quality;                  // 0x0fc
	undefined m_unk0x100[4];                // 0x100
	BOOL m_music;                           // 0x104
    undefined m_unk[4];
};

#endif // !defined(AFX_CONFIG_H)
