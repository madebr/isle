#include "MediaPathDlg.h"

#include "res/resource.h"

#include <legoomni.h>
#include <mxstring.h>

BEGIN_MESSAGE_MAP(CMediaPathDialog, CDialog)
ON_WM_DESTROY()
END_MESSAGE_MAP()

// FUNCTION: MAINR 0x00401d50
CMediaPathDialog::CMediaPathDialog() : CDialog(IDD_MEDIAPATH)
{
}

// FUNCTION: MAINR 0x00401f10
BOOL CMediaPathDialog::OnInitDialog()
{
	Initialize();
	Synchronize();
	return TRUE;
}

// FUNCTION: MAINR 0x00402320
void CMediaPathDialog::Initialize()
{
	CTreeCtrl* tree = (CTreeCtrl*) GetDlgItem(IDC_MEDIAPATH_TREE);
	CImageList* icon_list = LoadIcons();
	tree->SetImageList(LoadIcons(), TVSIL_NORMAL);
	HTREEITEM root_item = tree->InsertItem("My Computer", TVI_ROOT, TVI_LAST);
	tree->SetItemImage(root_item, m_icon_computer, m_icon_computer);

	char logical_drive[105];
	GetLogicalDriveStringsA(105, logical_drive);
	char drive_name[5];
	strcpy(drive_name, "( :)");
	char* path = logical_drive;
	while (path[0]) {
		drive_name[1] = toupper(path[0]);
		HTREEITEM drive_item = tree->InsertItem(drive_name, root_item, TVI_LAST);
		int icon;
		switch (GetDriveTypeA(path)) {
		case DRIVE_REMOVABLE:
			icon = m_icon_floppy_drive;
			break;
		default:
		case DRIVE_FIXED:
			icon = m_icon_hard_drive;
			break;
		case DRIVE_REMOTE:
			icon = m_icon_network_drive;
			break;
		case DRIVE_CDROM:
			icon = m_icon_cd_drive;
			break;
		}
		tree->SetItemImage(drive_item, icon, icon);
		tree->InsertItem("", drive_item, TVI_LAST);
		path += strlen(path) + 1;
	}
	CString media_path = LegoOmni::GetInstance()->GetMediaPath().GetData();
	if (media_path.Compare("") == 0) {
		char cwd[256];
		GetCurrentDirectoryA(sizeof(cwd), cwd);
		media_path = cwd;
	}
	ExpandPath((char*) (const char*) media_path);
}

// FUNCTION: MAINR 0x004022c0
void CMediaPathDialog::Synchronize()
{
	CTreeCtrl* tree = (CTreeCtrl*) GetDlgItem(IDC_MEDIAPATH_TREE);
	HTREEITEM selected = tree->GetSelectedItem();
	GetDlgItem(IDOK)->EnableWindow(selected && tree->GetRootItem() != selected);
}

// FUNCTION: MAINR 0x00402b40
CImageList* CMediaPathDialog::LoadIcons()
{
	CImageList* image_list = new CImageList;
	image_list->Create(16, 16, ILC_MASK, 8, 8);

	m_icon_cd_drive = image_list->Replace(
		-1,
		(HICON) LoadImageA(afxCurrentInstanceHandle, MAKEINTRESOURCE(IDI_CD_DRIVE), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR)
	);
	m_icon_closed_folder = image_list->Replace(
		-1,
		(HICON
		) LoadImageA(afxCurrentInstanceHandle, MAKEINTRESOURCE(IDI_CLOSED_FOLDER), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR)
	);
	m_icon_computer = image_list->Replace(
		-1,
		(HICON) LoadImageA(afxCurrentInstanceHandle, MAKEINTRESOURCE(IDI_COMPUTER), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR)
	);
	m_icon_hard_drive = image_list->Replace(
		-1,
		(HICON
		) LoadImageA(afxCurrentInstanceHandle, MAKEINTRESOURCE(IDI_HARD_DRIVE), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR)
	);
	m_icon_open_folder = image_list->Replace(
		-1,
		(HICON
		) LoadImageA(afxCurrentInstanceHandle, MAKEINTRESOURCE(IDI_OPEN_FOLDER), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR)
	);
	m_icon_network_drive = image_list->Replace(
		-1,
		(HICON
		) LoadImageA(afxCurrentInstanceHandle, MAKEINTRESOURCE(IDI_NETWORK_DRIVE), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR)
	);
	m_icon_floppy_drive = image_list->Replace(
		-1,
		(HICON
		) LoadImageA(afxCurrentInstanceHandle, MAKEINTRESOURCE(IDI_FLOPPY_DRIVE), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR)
	);

	return image_list;
}

// FUNCTION: MAINR 0x00402580
void CMediaPathDialog::ExpandPath(char* p_path)
{
	CTreeCtrl* tree = (CTreeCtrl*) GetDlgItem(IDC_MEDIAPATH_TREE);
	tree->Expand(tree->GetRootItem(), TVE_EXPAND);
	char* slash = strchr(p_path, '\\');
	*slash = '\0';
	HTREEITEM parent = FindDriveRootItem(p_path);
	char* path_part = slash + 1;
	tree->Expand(parent, TVE_EXPAND);
	while (*path_part != '\0') {
		slash = strchr(path_part, '\\');
		if (slash != NULL) {
			*slash = '\0';
		}
		HTREEITEM child = FindChildItem(parent, path_part);
		if (child == NULL) {
			child = tree->InsertItem(TVIF_TEXT, path_part, 0, 0, 0, 0, 0, parent, TVI_LAST);
		}
		tree->Expand(child, TVE_EXPAND);
		if (slash == NULL) {
			path_part += strlen(path_part);
		}
		else {
			path_part = slash + 1;
		}
		parent = child;
	}
}

// FUNCTION: MAINR 0x00402690
HTREEITEM CMediaPathDialog::FindDriveRootItem(char* p_drive)
{
	CTreeCtrl* tree = (CTreeCtrl*) GetDlgItem(IDC_MEDIAPATH_TREE);
	HTREEITEM root = tree->GetRootItem();
	HTREEITEM child = tree->GetChildItem(root);
	while (child != NULL) {
		CString child_text = tree->GetItemText(child);
		if (toupper(child_text[1] == *p_drive)) {
			return child;
		}
		child = tree->GetNextSiblingItem(child);
	}
	return child;
}

// FUNCTION: MAINR 0x00402790
HTREEITEM CMediaPathDialog::FindChildItem(HTREEITEM p_parent, char* p_name)
{
	CTreeCtrl* tree = (CTreeCtrl*) GetDlgItem(IDC_MEDIAPATH_TREE);
	HTREEITEM child = tree->GetChildItem(p_parent);
	while (child != NULL) {
		CString child_text = tree->GetItemText(child);
		if (child_text.Compare(p_name) == 0) {
			return child;
		}
		child = tree->GetNextSiblingItem(child);
	}
	return child;
}

// FUNCTION: MAINR 0x00402280
void CMediaPathDialog::OnDestroy()
{
	CTreeCtrl* tree = (CTreeCtrl*) GetDlgItem(IDC_MEDIAPATH_TREE);
	tree->DeleteAllItems();
	CImageList* image_list = tree->GetImageList(0);
	if (image_list) {
		delete image_list;
	}
}

// FUNCTION: MAINR 0x00402870
CString CMediaPathDialog::TreeItemToString(HTREEITEM item)
{
	CString result;
	CTreeCtrl* tree = (CTreeCtrl*) GetDlgItem(IDC_MEDIAPATH_TREE);
	for (;;) {
		CString text = tree->GetItemText(item);
		if (text[0] == '(') {
			result = text.Mid(1, 2) + "/" + result;
			return result;
		}
		result = text + "/" + result;
		item = tree->GetParentItem(item);
	}
}

// FUNCTION: MAINR 0x00401e50
void CMediaPathDialog::OnOK()
{
	CTreeCtrl* tree = (CTreeCtrl*) GetDlgItem(IDC_MEDIAPATH_TREE);
	CString s = TreeItemToString(tree->GetSelectedItem());
	m_path = s;
	EndDialog(1);
}

// FUNCTION: MAINR 0x00402210
BOOL CMediaPathDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	if (wParam == IDC_MEDIAPATH_TREE) {
		NMTREEVIEW* treeview = (NMTREEVIEW*) lParam;
		switch (treeview->hdr.code) {
		case TVN_ITEMEXPANDING:
			if (treeview->action == TVE_COLLAPSE) {
				OnCollapse(treeview->itemNew.hItem);
			}
			else if (treeview->action == TVE_EXPAND) {
				OnExpand(treeview->itemNew.hItem);
			}
			*pResult = 0;
			return TRUE;
		case TVN_SELCHANGED:
			Synchronize();
			return FALSE;
		}
	}
	return FALSE;
}

// FUNCTION: MAINR 0x00402190
void CMediaPathDialog::OnCollapse(HTREEITEM p_item)
{
	CTreeCtrl* tree = (CTreeCtrl*) GetDlgItem(IDC_MEDIAPATH_TREE);
	HTREEITEM root_item = tree->GetRootItem();
	if (p_item != root_item) {
		for (;;) {
			HTREEITEM child = tree->GetChildItem(p_item);
			if (!child) {
				break;
			}
			tree->DeleteItem(child);
		}
		tree->InsertItem("", p_item, TVI_LAST);
	}
}

// FUNCTION: MAINR 0x00402a20
int PathHasSubFolders(const char* p_path)
{
	CString path = p_path;
	if (path.Right(1).Compare("\\")) {
		path += "\\";
	}
	path += "*.*";
	WIN32_FIND_DATA find_data;
	HANDLE hFind = FindFirstFile(path, &find_data);
	int result = 0;
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if ((find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && find_data.cFileName[0] != '.') {
				result = 1;
				break;
			}
		} while (FindNextFile(hFind, &find_data));

		FindClose(hFind);
	}
	return result;
}

// FUNCTION: MAINR 0x00401f40
void CMediaPathDialog::OnExpand(HTREEITEM p_item)
{
	CWaitCursor waitCursor;
	CTreeCtrl* tree = (CTreeCtrl*) GetDlgItem(IDC_MEDIAPATH_TREE);
	HTREEITEM root = tree->GetRootItem();
	if (root == p_item) {
		return;
	}
	for (;;) {
		HTREEITEM child = tree->GetChildItem(p_item);
		if (!child) {
			break;
		}
		tree->DeleteItem(child);
	}
	CString path = TreeItemToString(p_item);
	path += "*.*";
	WIN32_FIND_DATA find_data;
	HANDLE hFind = FindFirstFile(path, &find_data);
	if (hFind != INVALID_HANDLE_VALUE) {
		path = path.Left(path.GetLength() - 3);
		do {
			if ((find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && find_data.cFileName[0] != '.') {
				HTREEITEM new_item = tree->InsertItem(find_data.cFileName, p_item, TVI_LAST);
				tree->SetItemImage(new_item, m_icon_closed_folder, m_icon_open_folder);
				if (PathHasSubFolders(path)) {
					tree->InsertItem("", new_item, TVI_LAST);
				}
			}
		} while (FindNextFile(hFind, &find_data));

		FindClose(hFind);
	}
	tree->SortChildren(p_item);
}
