#include "ActionsDlg.h"

#include "GeneralPropertyPage.h"
#include "LocationPropertyPage.h"
#include "TimePropertyPage.h"
#include "islegame.h"
#include "res/resource.h"

#include <mbstring.h>
#include <mxdsfile.h>
#include <mxutil.h>

BEGIN_MESSAGE_MAP(CActionsDialog, CDialog)
ON_COMMAND(IDC_ADD_BUTTON, OnAddButton)
ON_COMMAND(IDC_DELETE_BUTTON, OnDeleteButton)
ON_COMMAND(IDC_PROPERTIES_BUTTON, OnPropertiesButton)
ON_CBN_SELCHANGE(IDC_START_LIST, OnSourcesComboBox)
END_MESSAGE_MAP()

// FUNCTION: MAINR 0x00404850
CActionsDialog::CActionsDialog(CWnd* pParentWnd) : CDialog(IDD_ACTIONS, pParentWnd)
{
}

// FUNCTION: MAINR 0x00404990
BOOL CActionsDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	CComboBox* sources_combobox = (CComboBox*) GetDlgItem(IDC_SOURCES_COMBOBOX);
	POSITION pos;
	for (pos = g_game->m_paths.GetHeadPosition(); pos; g_game->m_paths.GetNext(pos)) {
		const IsleGame::PathModePair* path = (IsleGame::PathModePair*) g_game->m_paths.GetAt(pos);
		sources_combobox->AddString(path->m_path);
	}
	sources_combobox->SetCurSel(0);
	OnSourcesComboBox();

	CListCtrl* start_list = (CListCtrl*) GetDlgItem(IDC_START_LIST);
	start_list->InsertColumn(0, "Source");
	start_list->SetColumnWidth(0, 150);
	start_list->InsertColumn(1, "Action");
	start_list->SetColumnWidth(1, 100);
	int row = 0;
	for (pos = g_game->m_actions.GetHeadPosition(); pos; g_game->m_actions.GetNext(pos), row += 1) {
		const MxDSAction* action = (MxDSAction*) g_game->m_actions.GetAt(pos);
		start_list->InsertItem(row, action->GetSourceName());
		start_list->SetItemText(row, 1, action->GetObjectName());
	}
	start_list->SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
	Synchronize();
	return TRUE;
}

// FUNCTION: MAINR 0x00404ae0
void CActionsDialog::OnOK()
{
	LV_ITEM item;
	char buffer[256];

	CDialog::OnOK();

	memset(&item, 0, sizeof(item));
	item.pszText = buffer;
	item.mask = LVIF_TEXT;
	item.cchTextMax = sizeof(buffer);

	CListCtrl* start_list = (CListCtrl*) GetDlgItem(IDC_START_LIST);

	for (int i = 0; i < start_list->GetItemCount(); i++) {
		item.iItem = i;

		item.iSubItem = 0;
		start_list->GetItem(&item);
		CString source_name = buffer;

		item.iSubItem = 1;
		start_list->GetItem(&item);
		CString action_name = buffer;

		MxDSFile* file = new MxDSFile(source_name, 0);
		if (file->Open(0) == 0) {
			int count_buffers = file->GetStreamBuffersNum();
			for (int j = 0; j < count_buffers; j++) {
				MxDSObject* object = CreateStreamObject(file, j);
				if (object == NULL) {
					continue;
				}
				if (action_name.Compare(object->GetObjectName()) == 0) {
					MxDSAction* action = new MxDSAction;
#if 0
					// MXDSObject::SetSourceName is not exported from final LEGO1.DLL
					action->SetSourceName(source_name);
#endif
					action->SetObjectId(object->GetObjectId());
					action->SetObjectName(object->GetObjectName());
					action->SetUnk0x90(INT_MIN);
					g_game->m_actions.AddTail(object); // FIXME: or AddHead
				}
				if (object) {
					delete object;
				}
			}
		}
		delete file;
	}
}

// FUNCTION: MAINR 0x00404e10
void CActionsDialog::Synchronize()
{
	CListBox* actions_list = (CListBox*) GetDlgItem(IDC_ACTIONS_LIST);
	GetDlgItem(IDC_ADD_BUTTON)->EnableWindow(actions_list->GetSel(0) != -1);
	CListCtrl* start_list = (CListCtrl*) GetDlgItem(IDC_START_LIST);
	GetDlgItem(IDC_DELETE_BUTTON)->EnableWindow(start_list->GetNextItem(-1, LVNI_SELECTED) != -1);
	GetDlgItem(IDC_PROPERTIES_BUTTON)->EnableWindow(start_list->GetNextItem(-1, LVNI_SELECTED) != -1);
}

// FUNCTION: MAINR 0x00405010
void CActionsDialog::OnAddButton()
{
	CComboBox* sources = (CComboBox*) GetDlgItem(IDC_SOURCES_COMBOBOX);
	CString current_source;
	sources->GetLBText(sources->GetCurSel(), current_source);

	CListBox* actions_list = (CListBox*) GetDlgItem(IDC_ACTIONS_LIST);
	CString current_action;
	actions_list->GetText(actions_list->GetCurSel(), current_action);

	CListCtrl* start_list = (CListCtrl*) GetDlgItem(IDC_START_LIST);
	int pos_new_item = start_list->GetItemCount();
	start_list->InsertItem(pos_new_item, current_source);
	start_list->SetItemText(pos_new_item, 1, current_action);
	start_list->SetItemState(pos_new_item, LVIS_SELECTED, LVIS_SELECTED);
	Synchronize();
}

// FUNCTION: MAINR 0x00405150
void CActionsDialog::OnDeleteButton()
{
	CListCtrl* start_list = (CListCtrl*) GetDlgItem(IDC_START_LIST);
	int selected = start_list->GetNextItem(-1, LVNI_SELECTED);
	int new_count = start_list->GetItemCount();
	if (new_count == selected) {
		new_count -= 1;
	}
	start_list->SetItemState(selected, LVIS_SELECTED, LVIS_SELECTED);
	Synchronize();
}

// FUNCTION: MAINR 0x004051c0
void CActionsDialog::OnPropertiesButton()
{
	CListCtrl* start_list = (CListCtrl*) GetDlgItem(IDC_START_LIST);
	int selected = start_list->GetNextItem(-1, LVNI_SELECTED);
	if (selected != -1) {
		CString title;
		LVITEM item;
		char buffer[256];

		memset(&item, 0, sizeof(item));
		item.pszText = buffer;
		item.mask = LVIF_TEXT;
		item.cchTextMax = sizeof(buffer);

		item.iSubItem = 0;
		start_list->GetItem(&item);
		title = buffer;

		item.iSubItem = 1;
		start_list->GetItem(&item);
		title += " / ";
		title += buffer;
		title += " properties";

		CPropertySheet property_sheet(title, this);
		CGeneralPropertyPage general_page;
		CTimePropertyPage time_page;
		CLocationPropertyPage location_page;

		property_sheet.AddPage(&general_page);
		property_sheet.AddPage(&time_page);
		property_sheet.AddPage(&location_page);
		property_sheet.DoModal();

		Synchronize();
	}
}

// FUNCTION: MAINR 0x00404ec0
void CActionsDialog::OnSourcesComboBox()
{
	CComboBox* sources = (CComboBox*) GetDlgItem(IDC_SOURCES_COMBOBOX);
	CString source;
	sources->GetLBText(sources->GetCurSel(), source);
	source.ReverseFind('.');
	// FIXME: Create MxDSFile on heap to avoid missing symbols at link time
	MxDSFile* file = new MxDSFile(source, 0);
	if (file->Open(0) == 0) {
		CListBox* actions = (CListBox*) GetDlgItem(IDC_ACTIONS_LIST);
		actions->ResetContent();
		for (int i = 0; i < file->GetStreamBuffersNum(); i++) {
			MxDSObject* object = CreateStreamObject(file, i);
			if (object) {
				sources->AddString(object->GetObjectName());
				delete object;
			}
		}
		sources->SetCurSel(0);
	}
	delete file;
}
