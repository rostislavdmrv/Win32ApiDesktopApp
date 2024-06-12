#include "stdafx.h"
#include "resource.h"
#include "commctrl.h"
int time=0,time2=0;

LRESULT CALLBACK Again(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:{
		   
			SetDlgItemInt(hDlg,IDC_EDIT3,0,FALSE);
		   SetDlgItemInt(hDlg,IDC_EDIT4,0,FALSE);
		   InitCommonControls();
				return TRUE;
		}

		case WM_COMMAND:
			{
				if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
				{
					EndDialog(hDlg, LOWORD(wParam));
					return TRUE;
				}
				if (LOWORD(wParam) == IDC_START) {
					SetTimer(hDlg, 2 , 200 , NULL);
					SetTimer(hDlg, 1 , 1000, NULL);
				}
				if (LOWORD(wParam) == IDC_STOP) {
					time=0;time2=0;
					SetDlgItemInt(hDlg,IDC_EDIT3,0,FALSE);
					SetDlgItemInt(hDlg,IDC_EDIT4,0,FALSE);
					KillTimer(hDlg,1);
					KillTimer(hDlg,2);
				}
				if (LOWORD(wParam) == IDC_PAUSE) {
					KillTimer(hDlg,1);
					KillTimer(hDlg,2);
				}
			}
			break;	
		case WM_MOUSEMOVE:
			{
				SetDlgItemInt (hDlg, IDC_EDIT1, LOWORD(lParam), TRUE);
				SetDlgItemInt (hDlg, IDC_EDIT2, HIWORD(lParam), TRUE);
			}
			break;
		case WM_LBUTTONDOWN:
			{
				if(wParam & MK_CONTROL) CheckDlgButton(hDlg,IDC_CHECK1,BST_CHECKED);
				if(wParam & MK_SHIFT) CheckDlgButton(hDlg,IDC_CHECK2,BST_CHECKED);
				if(wParam & MK_RBUTTON) CheckDlgButton(hDlg,IDC_CHECK3,BST_CHECKED);
			}
			break;
		case WM_LBUTTONUP:
			{
				if(wParam & MK_CONTROL) CheckDlgButton(hDlg,IDC_CHECK1,BST_UNCHECKED);
				if(wParam & MK_SHIFT) CheckDlgButton(hDlg,IDC_CHECK2,BST_UNCHECKED);
				if(wParam & MK_RBUTTON) CheckDlgButton(hDlg,IDC_CHECK3,BST_UNCHECKED);
			}
			break;
        case WM_TIMER: 
			{ 
				if(wParam == 1)
				{
					SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETSTEP, 2, 0);
				    SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_STEPIT, 0, 0);
					SetDlgItemInt(hDlg,IDC_EDIT3,++time,TRUE);
				}
			    if(wParam == 2)
					SetDlgItemInt(hDlg,IDC_EDIT4,++time2,TRUE);
			}
	}
    return FALSE;
}

