#include "stdafx.h"
#include "dlg.h"

void InitDialog(HWND);
void SetGroup1(HWND);

// Mesage handler for dialog
LRESULT CALLBACK Dlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				InitDialog(hDlg);
				return TRUE;

		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDC_CHECK_CTRL:
					SetGroup1(hDlg); 
					break;
				case IDC_COMBO_CTRL:
					if(HIWORD(wParam) == CBN_SELCHANGE)
					{
						int index = SendMessage((HWND)lParam /*hwndComboBox*/, CB_GETCURSEL, 0, 0);
						if(index != CB_ERR)
						{
							char text[MAX_PATH];
							SendMessage((HWND)lParam, CB_GETLBTEXT, index, (LPARAM)text);
							SetDlgItemText(hDlg, IDC_STATIC_CTRL, text);
						}					
					}
					break;
				case IDC_EDIT_CTRL:
					if(HIWORD(wParam) == EN_CHANGE)
					{
						char text[MAX_PATH];
						GetDlgItemText(hDlg, IDC_EDIT_CTRL, text, MAX_PATH);
						SetDlgItemText(hDlg, IDC_STATIC_CTRL, text);
					}
					break;
				case IDOK:
				case IDCANCEL:
					EndDialog(hDlg, LOWORD(wParam));
					return TRUE;
			}
			break;
	}
    return FALSE;
}

void InitDialog(HWND hDlg)
{
// *** init edit box ***
	SetDlgItemText(hDlg, IDC_EDIT_CTRL, "Some text"); // => SetWindowText(...)

// *** init combo ***
	SendMessage(GetDlgItem(hDlg, IDC_COMBO_CTRL), CB_ADDSTRING, 0, (LPARAM) "String 1");
	SendMessage(GetDlgItem(hDlg, IDC_COMBO_CTRL), CB_ADDSTRING, 0, (LPARAM) "String 2");
	SendMessage(GetDlgItem(hDlg, IDC_COMBO_CTRL), CB_ADDSTRING, 0, (LPARAM) "String 3");
	SendMessage(GetDlgItem(hDlg, IDC_COMBO_CTRL), CB_SETCURSEL, 1, 0); //=> SendDlgItemMessage(...)

// *** init static ***
	char text[MAX_PATH];
	GetDlgItemText(hDlg, IDC_EDIT_CTRL, text, MAX_PATH);
	SetDlgItemText(hDlg, IDC_STATIC_CTRL, text);

// *** init check ***
	CheckDlgButton(hDlg, IDC_CHECK_CTRL, BST_CHECKED); // => SendMessage(<BM_SETCHECK>)

// *** init group 1 ***
	CheckDlgButton(hDlg, IDC_A, BST_CHECKED); // => CheckRadioButton(...)
	SetGroup1(hDlg);

// *** init group 2 ***
	CheckDlgButton(hDlg, IDC_B1, BST_CHECKED);
}

void SetGroup1(HWND hDlg)
{
	UINT state = IsDlgButtonChecked(hDlg, IDC_CHECK_CTRL); // SendMessage(<BM_GETCHECK>);
	EnableWindow(GetDlgItem(hDlg, IDC_A), state);
	EnableWindow(GetDlgItem(hDlg, IDC_B), state);
	EnableWindow(GetDlgItem(hDlg, IDC_C), state);
}
