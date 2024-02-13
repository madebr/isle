#include "NavigationDlg.h"

#include "res/resource.h"

#include <legonavcontroller.h>

BEGIN_MESSAGE_MAP(CNavigationDialog, CDialog)
ON_COMMAND(IDC_NAV_CHECKBOX_ROTVEL, OnCheckboxRotVel)
ON_WM_HSCROLL()
END_MESSAGE_MAP()

// FUNCTION: MAINR 0x00401000
CNavigationDialog::CNavigationDialog(CWnd* pParentWnd) : CDialog(IDD_NAVIGATION, pParentWnd)
{
	m_unk0x2e0 = FALSE;
}

// FUNCTION: MAINR 0x00401430
void CNavigationDialog::DoDataExchange(CDataExchange* pDDX)
{
	DDX_Control(pDDX, IDC_NAV_SLIDER_ROTVEL, m_unk0x060);
	DDX_Control(pDDX, IDC_NAV_SLIDER_RSENS, m_unk0x0a0);
	DDX_Control(pDDX, IDC_NAV_SLIDER_RACCEL, m_unk0x0e0);
	DDX_Control(pDDX, IDC_NAV_SLIDER_RACMIN, m_unk0x120);
	DDX_Control(pDDX, IDC_NAV_SLIDER_RDECCEL, m_unk0x160);
	DDX_Control(pDDX, IDC_NAV_SLIDER_LINVEL, m_unk0x1a0);
	DDX_Control(pDDX, IDC_NAV_SLIDER_LACCEL, m_unk0x1e0);
	DDX_Control(pDDX, IDC_NAV_SLIDER_LACMIN, m_unk0x220);
	DDX_Control(pDDX, IDC_NAV_SLIDER_LDECCEL, m_unk0x260);
	DDX_Control(pDDX, IDC_NAV_SLIDER_DEADZ, m_unk0x2a0);
	DDX_Check(pDDX, IDC_NAV_CHECKBOX_ROTVEL, m_unk0x2e0);
}

// FUNCTION: MAINR 0x00401960
BOOL CNavigationDialog::OnInitDialog()
{
	int mouseDeadZone;
	float movementMaxSpeed;
	float turnMaxSpeed;
	float movementMaxAccel;
	float turnMaxAccel;
	float movementDecel;
	float turnDecel;
	float movementMinAccel;
	float turnMinAccel;
	float rotationSensitivity;
	MxBool turnUseVelocity;

	CDialog::OnInitDialog();
	LegoNavController::GetDefaults(
		&mouseDeadZone,
		&movementMaxSpeed,
		&turnMaxSpeed,
		&movementMaxAccel,
		&turnMaxAccel,
		&movementDecel,
		&turnDecel,
		&movementMinAccel,
		&turnMinAccel,
		&rotationSensitivity,
		&turnUseVelocity
	);
	m_unk0x2e0 = turnUseVelocity;
	CheckDlgButton(IDC_NAV_CHECKBOX_ROTVEL, turnUseVelocity);

	m_unk0x2a0.SetRange(0, 100, FALSE);
	m_unk0x2a0.SetPos(mouseDeadZone);

	m_unk0x1a0.SetRange(0, 100, FALSE);
	m_unk0x1a0.SetPos((int) movementMaxSpeed);

	m_unk0x060.SetRange(0, 100, FALSE);
	m_unk0x060.SetPos((int) turnMaxSpeed);

	m_unk0x1e0.SetRange(0, 100, FALSE);
	m_unk0x1e0.SetPos((int) movementMaxAccel);

	m_unk0x0e0.SetRange(0, 100, FALSE);

	m_unk0x220.SetRange(0, 100, FALSE);
	m_unk0x220.SetPos((int) movementMinAccel);

	m_unk0x120.SetRange(0, 100, FALSE);
	m_unk0x120.SetPos((int) turnMinAccel);

	m_unk0x0e0.SetPos((int) turnMaxAccel);

	m_unk0x260.SetRange(0, 100, FALSE);
	m_unk0x260.SetPos((int) movementDecel);

	m_unk0x160.SetRange(0, 100, FALSE);
	m_unk0x160.SetPos((int) turnDecel);

	m_unk0x0a0.SetRange(0, 100, FALSE);
	m_unk0x0a0.SetPos((int) (100. * rotationSensitivity));

	SetDlgItemInt(IDC_NAV_STATIC_DEADZ, m_unk0x2a0.GetPos());
	SetDlgItemInt(IDC_NAV_STATIC_LINVEL, m_unk0x1a0.GetPos());
	SetDlgItemInt(IDC_NAV_STATIC_ROTVEL, m_unk0x060.GetPos());
	SetDlgItemInt(IDC_NAV_STATIC_LACCEL, m_unk0x1e0.GetPos());
	SetDlgItemInt(IDC_NAV_STATIC_RACCEL, m_unk0x0e0.GetPos());
	SetDlgItemInt(IDC_NAV_STATIC_LACMIN, m_unk0x220.GetPos());
	SetDlgItemInt(IDC_NAV_STATIC_RACMIN, m_unk0x120.GetPos());
	SetDlgItemInt(IDC_NAV_STATIC_LDECCEL, m_unk0x260.GetPos());
	SetDlgItemInt(IDC_NAV_STATIC_RDECCEL, m_unk0x160.GetPos());
	SetDlgItemInt(IDC_NAV_STATIC_RSENS, m_unk0x0a0.GetPos());

	return TRUE;
}

// FUNCTION: MAINR 0x00401690
void CNavigationDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

	SetDlgItemInt(IDC_NAV_STATIC_DEADZ, m_unk0x2a0.GetPos());
	SetDlgItemInt(IDC_NAV_STATIC_LINVEL, m_unk0x1a0.GetPos());
	SetDlgItemInt(IDC_NAV_STATIC_ROTVEL, m_unk0x060.GetPos());
	SetDlgItemInt(IDC_NAV_STATIC_LACCEL, m_unk0x1e0.GetPos());
	SetDlgItemInt(IDC_NAV_STATIC_RACCEL, m_unk0x0e0.GetPos());
	SetDlgItemInt(IDC_NAV_STATIC_LACMIN, m_unk0x220.GetPos());
	SetDlgItemInt(IDC_NAV_STATIC_RACMIN, m_unk0x120.GetPos());
	SetDlgItemInt(IDC_NAV_STATIC_LDECCEL, m_unk0x260.GetPos());
	SetDlgItemInt(IDC_NAV_STATIC_RDECCEL, m_unk0x160.GetPos());
	SetDlgItemInt(IDC_NAV_STATIC_RSENS, m_unk0x0a0.GetPos());
	LegoNavController::SetDefaults(
		m_unk0x2a0.GetPos(),
		(float) m_unk0x1a0.GetPos(),
		(float) m_unk0x060.GetPos(),
		(float) m_unk0x1e0.GetPos(),
		(float) m_unk0x0e0.GetPos(),
		(float) m_unk0x260.GetPos(),
		(float) m_unk0x160.GetPos(),
		(float) m_unk0x220.GetPos(),
		(float) m_unk0x120.GetPos(),
		(float) (m_unk0x0a0.GetPos() * 0.01),
		m_unk0x2e0
	);
}

// FUNCTION : MAINR 0x00401520
void CNavigationDialog::OnCheckboxRotVel()
{
	m_unk0x2e0 = !m_unk0x2e0;
	LegoNavController::SetDefaults(
		m_unk0x2a0.GetPos(),
		(float) m_unk0x1a0.GetPos(),
		(float) m_unk0x060.GetPos(),
		(float) m_unk0x1e0.GetPos(),
		(float) m_unk0x0e0.GetPos(),
		(float) m_unk0x260.GetPos(),
		(float) m_unk0x160.GetPos(),
		(float) m_unk0x220.GetPos(),
		(float) m_unk0x120.GetPos(),
		(float) m_unk0x0a0.GetPos(),
		m_unk0x2e0
	);
}
