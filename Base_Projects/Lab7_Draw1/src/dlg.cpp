#include "stdafx.h"
#include "resource.h"

LRESULT CALLBACK SRC2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
			}
			if(LOWORD(wParam)==IDC_CHECK1) {
				switch(IsDlgButtonChecked(hDlg,IDC_CHECK1)) {
				case BST_CHECKED: 
					MessageBox(hDlg,"Check box is checked.","msg",MB_OK);
					break;
				case BST_UNCHECKED:
					MessageBox(hDlg,"Check box is unchecked.","msg",MB_OK);
					break;
				}
			}
			char buff[200];
			if(LOWORD(wParam)== IDC_READ) {
				GetDlgItemText(hDlg,IDC_ED,buff,sizeof(buff));
				if(IsDlgButtonChecked(hDlg,IDC_CHECK1)==BST_CHECKED) {
					//MessageBox(hDlg,buff,"msg",MB_OK);
					//SendDlgItemMessage(hDlg,IDC_COMBO1,CB_ADDSTRING,0,(LPARAM)buff);
					if(SendDlgItemMessage(hDlg,IDC_COMBO1,CB_FINDSTRING,0,(LPARAM)buff)==-1){
					SendDlgItemMessage(hDlg,IDC_COMBO1,CB_SETCURSEL,SendDlgItemMessage(hDlg,IDC_COMBO1,CB_ADDSTRING,0,(LPARAM)buff),0);
					}
				}
			}
			if(LOWORD(wParam)==IDC_SEND) {
				SendDlgItemMessage(hDlg,IDC_COMBO1,CB_GETLBTEXT,SendDlgItemMessage(hDlg,IDC_COMBO1,CB_GETCURSEL,0,0),(LPARAM)buff);
				SetDlgItemText(hDlg,IDC_ED1,buff);
			}
			break;
			
	}
    return FALSE;
}