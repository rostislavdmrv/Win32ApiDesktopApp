#include "stdafx.h"
#include"resource.h"



LRESULT CALLBACK About2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}/*
			if (LOWORD(wParam) == IDC_UPR2) // CHECK BUTTON 
			{
				if (IsDlgButtonChecked(hDlg,IDC_CHECK1)==BST_CHECKED )
					MessageBox(hDlg,"Check1 ","Message1",MB_OK);
				if (IsDlgButtonChecked(hDlg,IDC_CHECK2)==BST_CHECKED)
					MessageBox(hDlg,"Check2","Message2",MB_OK);

				return TRUE;
			}*/

				if (LOWORD(wParam) == IDC_UPR2) // COMBO BOX SE ZAPALVA SAS STRINGA OT EDIT,AKO CH1 
			{
				char string[81];
				GetDlgItemText(hDlg,IDC_EDIT2, string,sizeof(string));
				//GetDlgItemText(hDlg,IDC_EDIT3, string,sizeof(string));
				//GetDlgItemText(hDlg,IDC_EDIT4, string,sizeof(string));
				if(IsDlgButtonChecked(hDlg,IDC_CHECK1)==BST_CHECKED 
				&& (SendDlgItemMessage(hDlg,IDC_COMBO1,CB_FINDSTRING,0,(LPARAM)string)==(-1)))
				{
				   SendDlgItemMessage(hDlg,IDC_COMBO1,CB_ADDSTRING,0,(LPARAM)string);

				}
				if(IsDlgButtonChecked(hDlg,IDC_CHECK2)==BST_CHECKED
					&& (SendDlgItemMessage(hDlg,IDC_LIST1,LB_FINDSTRING,0,(LPARAM)string)==(-1)))
					SendDlgItemMessage(hDlg,IDC_LIST1,LB_ADDSTRING,0,(LPARAM)string);
			    

                return TRUE;

			}
				   if(LOWORD(wParam) == IDC_BTN2)
				   {char string[81];
				    SendDlgItemMessage(hDlg,IDC_COMBO1,CB_GETLBTEXT,SendDlgItemMessage(hDlg,IDC_COMBO1,CB_GETCURSEL,0,0),(LPARAM)string);	
                    SetDlgItemText(hDlg,IDC_EDIT3,string);
				   }

			break;
	}
    return FALSE;
}

