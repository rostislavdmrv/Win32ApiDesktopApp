#include "stdafx.h"
#include "resource.h"

LRESULT CALLBACK Click(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
			CheckDlgButton(hDlg, IDC_CHECK1, BST_INDETERMINATE);
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK) 
			{
				MessageBox(hDlg, "That's ok", "Again...", MB_ICONQUESTION);
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			if (LOWORD(wParam) == IDC_BUTTON1)
			{
				MessageBox(hDlg, "You clicked me!", "Again...", MB_ICONQUESTION);
			}
			if (LOWORD(wParam) == IDC_BUTTON2)
			{
				char mass[100]={0};
				int ind;
				GetDlgItemText(hDlg, IDC_EDIT1, mass, sizeof(mass));
				ind = SendDlgItemMessage(hDlg, IDC_COMBO1, CB_FINDSTRING, 0, (LPARAM)mass);
				SendDlgItemMessage(hDlg, IDC_COMBO1, CB_DELETESTRING, ind, 0);
				ind = SendDlgItemMessage(hDlg, IDC_COMBO1, CB_ADDSTRING, 0, (LPARAM)mass);
				SendDlgItemMessage(hDlg, IDC_COMBO1, CB_SETCURSEL, ind, 0);
				MessageBox(hDlg, mass, "Again...", MB_APPLMODAL);
				return TRUE;
			}
			if (LOWORD(wParam) == IDC_BUTTON4)
			{
				char mass2[100]={0};
				SendDlgItemMessage(hDlg, IDC_COMBO1, CB_GETLBTEXT, 0, (LPARAM)mass2);
				SetDlgItemText(hDlg, IDC_EDIT2, mass2);
				return TRUE;
			}
			if (LOWORD(wParam) == IDC_CHECK1)
			{
				int check = IsDlgButtonChecked(hDlg, IDC_CHECK1);
				if (check == BST_CHECKED)
					MessageBox(hDlg, "Checked!", "Again...", MB_ICONQUESTION);
				if (check == BST_UNCHECKED)
					MessageBox(hDlg, "Not checked?", "Again...", MB_ICONQUESTION);
				if (check == BST_INDETERMINATE)
					MessageBox(hDlg, "Uhm... Don't know...", "Again...", MB_ICONQUESTION);
			}
			if (LOWORD(wParam) == IDC_BUTTON3)
			{
				int check = IsDlgButtonChecked(hDlg, IDC_CHECK1);
				if (check == BST_CHECKED)
					MessageBox(hDlg, "Checked!", "Again...", MB_ICONQUESTION);
				if (check == BST_UNCHECKED)
					MessageBox(hDlg, "Not checked?", "Again...", MB_ICONQUESTION);
				if (check == BST_INDETERMINATE)
					MessageBox(hDlg, "Uhm... Don't know...", "Again...", MB_ICONQUESTION);
			}
			break;
	}
    return FALSE;
}