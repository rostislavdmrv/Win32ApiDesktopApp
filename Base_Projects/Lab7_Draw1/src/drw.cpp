#include "stdafx.h"
#include "resource.h"

extern HINSTANCE hInst;

LRESULT CALLBACK DRW(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int x,y;
	static int p,z;

	HBRUSH ff;
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
			break;
		case WM_LBUTTONDOWN:
				x=p=LOWORD(lParam);
				y=z=HIWORD(lParam);
				break;
		case WM_MOUSEMOVE:
			if(wParam&MK_LBUTTON) {
	HDC hDC=GetDC(hDlg);
				COLORREF color=RGB(1,1,1);
				HPEN hPen=CreatePen(PS_DOT,1,color);
				SelectObject(hDC,hPen);
				SetROP2(hDC,R2_NOTXORPEN);
				SelectObject(hDC,GetStockObject(HOLLOW_BRUSH));
				Rectangle(hDC,x,y,p,z);
				p=LOWORD(lParam);
				z=HIWORD(lParam);
				Rectangle(hDC,x,y,p,z);
				ReleaseDC(hDlg,hDC);
			}
			break;
		case WM_LBUTTONUP:
	HDC hDC=GetDC(hDlg);
				HDC hdc=CreateCompatibleDC(hDC);
				HBITMAP hBit=LoadBitmap(hInst,(LPCTSTR)IDB_BOB);
				SelectObject(hdc,hBit);
				//BitBlt(hDC,x,y,p,z,hdc,0,0,SRCCOPY);
				StretchBlt(hDC,x,y,p,z,hdc,0,0,85,74,SRCCOPY);
			break;
	}
    return FALSE;
}