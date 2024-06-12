#include "stdafx.h"
#include "resource.h"


#define TIMER1 500

LRESULT CALLBACK functionMouse(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)  // pri startirane na about box
{
	static int step = 20;
	switch (message) {
		case WM_INITDIALOG:
			SetDlgItemInt(hDlg, IDC_TIMER, 0, NULL);
			InitCommonControls();
			SendDlgItemMessage(hDlg, IDC_PROGBAR, PBM_SETRANGE, 0, MAKELPARAM(0, 1000));
			SendDlgItemMessage(hDlg, IDC_PROGBAR, PBM_DELTAPOS, 100, 0);
			
			return TRUE;

		case WM_COMMAND: {
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			
			if (LOWORD(wParam) == IDC_TSTART) {
				SetTimer(hDlg, TIMER1, 20, NULL);
				break;
			}
			if (LOWORD(wParam) == IDC_TSTOP) {
				KillTimer(hDlg, TIMER1);
				SetDlgItemInt(hDlg, IDC_TIMER, 0, NULL);
				break;
			}
			if (LOWORD(wParam) == IDC_TPAUSE) {
				KillTimer(hDlg, TIMER1);
				break;
			}
			break;
		}		
			
		
		case WM_TIMER:
			{
				int counter = GetDlgItemInt(hDlg, IDC_TIMER, NULL, FALSE);
				counter+=5;
				SetDlgItemInt(hDlg, IDC_TIMER, counter, NULL);
				if (step > 0) {
					if (SendDlgItemMessage(hDlg, IDC_PROGBAR, PBM_GETPOS, 0, 0) >= 900) 
					{
						step = -20;
						SendDlgItemMessage(hDlg, IDC_PROGBAR, PBM_SETSTEP, step,0);
						SendDlgItemMessage(hDlg, IDC_PROGBAR, PBM_SETPOS, 900, 0);
						SendDlgItemMessage(hDlg, IDC_PROGBAR, PBM_DELTAPOS, -500,0);
						break;
					}
					SendDlgItemMessage(hDlg, IDC_PROGBAR, PBM_SETSTEP, step, 0);
					SendDlgItemMessage(hDlg, IDC_PROGBAR, PBM_STEPIT,0,0);
				}
				else {
					if (SendDlgItemMessage(hDlg, IDC_PROGBAR, PBM_GETPOS, 0, 0) <= 100) 
					{
						step = 20;
						SendDlgItemMessage(hDlg, IDC_PROGBAR, PBM_SETSTEP, step,0);
						SendDlgItemMessage(hDlg, IDC_PROGBAR, PBM_SETPOS, 100, 0);
						break;
					}
					SendDlgItemMessage(hDlg, IDC_PROGBAR, PBM_SETSTEP, step,0);
					SendDlgItemMessage(hDlg, IDC_PROGBAR, PBM_STEPIT,0,0);
				}		
			}
		
		
		
		case WM_MOUSEMOVE:
			{
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);
			SetDlgItemInt(hDlg, IDC_MOUSEX, x, TRUE);
			SetDlgItemInt(hDlg, IDC_MOUSEY, y, TRUE);
			break;
			}
		case WM_LBUTTONDOWN: 
		{
			
			if (wParam & MK_RBUTTON) {
				CheckDlgButton(hDlg, IDC_RBUTTON, BST_CHECKED);
			}
			if (wParam & MK_SHIFT) {
				CheckDlgButton(hDlg, IDC_CHECKSHIFT, BST_CHECKED);
			}
			if (wParam & MK_CONTROL) {
				CheckDlgButton(hDlg, IDC_CTRL, BST_CHECKED);
			}
		}
	}
	return FALSE;
}
	