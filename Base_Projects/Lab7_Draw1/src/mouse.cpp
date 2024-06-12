#include "stdafx.h"
#include "resource.h"
#include <commctrl.h>
#define ID_TIME1 1
#define ID_TIME2 2

LRESULT CALLBACK D(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int br=0,br1=0;;
	switch (message)
	{
		case WM_INITDIALOG:
				InitCommonControls();
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			if(LOWORD(wParam) == IDC_BUTTON1) {
			SetTimer(hDlg,ID_TIME1,500,NULL);
			SetTimer(hDlg,ID_TIME2,1000,NULL);
			}
			if(LOWORD(wParam) == IDC_BUTTON3) {
			KillTimer(hDlg,ID_TIME1);
			KillTimer(hDlg,ID_TIME2);
			br=0;
			br1=0;
			SetDlgItemInt(hDlg,IDC_EDIT3,br,TRUE);
			SetDlgItemInt(hDlg,IDC_EDIT4,br1,TRUE);
			}
			if(LOWORD(wParam) == IDC_BUTTON4) {
			KillTimer(hDlg,ID_TIME1);
			KillTimer(hDlg,ID_TIME2);
			}
			break;
		case WM_MOUSEMOVE:
			SetDlgItemInt(hDlg,IDC_EDIT1,LOWORD(lParam),TRUE);
			SetDlgItemInt(hDlg,IDC_EDIT2,HIWORD(lParam),TRUE);
			break;
		case WM_TIMER:
			switch(wParam) {
			case ID_TIME1:
				br++;
				SetDlgItemInt(hDlg,IDC_EDIT3,br,TRUE);
				SendDlgItemMessage(hDlg,IDC_PSS,PBM_SETRANGE,0,MAKELPARAM(0,100));
				SendDlgItemMessage(hDlg,IDC_PSS,PBM_SETSTEP,1,0);
				SendDlgItemMessage(hDlg,IDC_PSS,PBM_STEPIT,0,0);
				break;
			case ID_TIME2:			
				br1++;
				SetDlgItemInt(hDlg,IDC_EDIT4,br1,TRUE);
				SendDlgItemMessage(hDlg,IDC_PSS2,PBM_SETRANGE,0,MAKELPARAM(0,100));
				SendDlgItemMessage(hDlg,IDC_PSS2,PBM_SETSTEP,1,0);
				SendDlgItemMessage(hDlg,IDC_PSS2,PBM_STEPIT,0,0);
				break;
			}
			break;
		case WM_LBUTTONDOWN:
			if(wParam&MK_CONTROL) {
				CheckDlgButton(hDlg,IDC_CHECK1,BST_CHECKED);
			}
			if(wParam&MK_SHIFT) {
				CheckDlgButton(hDlg,IDC_CHECK2,BST_CHECKED);
			}
		
			break;
		case WM_LBUTTONUP:
			if(wParam&MK_CONTROL) {
				CheckDlgButton(hDlg,IDC_CHECK1,BST_UNCHECKED);
			}
			if(wParam&MK_SHIFT) {
				CheckDlgButton(hDlg,IDC_CHECK2,BST_UNCHECKED);
			}
			break;
	}
    return FALSE;
}