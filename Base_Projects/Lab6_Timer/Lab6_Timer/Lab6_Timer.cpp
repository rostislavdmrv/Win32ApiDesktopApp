// Lab6_Timer.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Lab6_Timer.h"
#include "commctrl.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Mouse(HWND, UINT, WPARAM, LPARAM);


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_LAB6_TIMER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB6_TIMER));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB6_TIMER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_LAB6_TIMER);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_D_D1:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Mouse);
			break;


		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


#define TIMER1 500

INT_PTR CALLBACK Mouse(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)  // pri startirane na about box
{
	static int step = 20;
	switch (message) {
		case WM_INITDIALOG:
			SetDlgItemInt(hDlg, IDC_TIMER, 0, NULL);
			
			SendDlgItemMessage(hDlg, IDC_PROGBAR, PBM_SETRANGE, 0, MAKELPARAM(0, 1000));
			SendDlgItemMessage(hDlg, IDC_PROGBAR, PBM_DELTAPOS, 100, 0); // да запачва да има отстояние 
			
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
					if (SendDlgItemMessage(hDlg, IDC_PROGBAR, PBM_GETPOS, 0, 0) >= 900) //ако е стигнало края 
					{
						step = -20;
						SendDlgItemMessage(hDlg, IDC_PROGBAR, PBM_SETSTEP, step,0);//задава стъпка за преместване
						//SendDlgItemMessage(hDlg, IDC_PROGBAR, PBM_SETPOS, 900, 0);//премества текущата позиция в п.б. на зададена позиция
						SendDlgItemMessage(hDlg, IDC_PROGBAR, PBM_DELTAPOS, -100,0);//дадено отстояние 
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