// Lab5_D3.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Lab5_D3.h"

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

INT_PTR CALLBACK	func_NewDiag(HWND, UINT, WPARAM, LPARAM);

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
	LoadString(hInstance, IDC_LAB5_D3, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB5_D3));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB5_D3));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_LAB5_D3);
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
			case ID_D_D3:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, func_NewDiag);
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
INT_PTR CALLBACK func_NewDiag(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	char data[20];
	int c_index, l_index;
	int mID;
	int cbIndex;
	int lbIndex;
	mID=LOWORD(wParam);
	switch(message)
	{
	case WM_INITDIALOG:
		// combo box
		c_index=SendDlgItemMessage(hDlg,IDC_COMBO1,CB_ADDSTRING,0,(LPARAM) "Row 1 in Combo Box");
		c_index=SendDlgItemMessage(hDlg,IDC_COMBO1,CB_ADDSTRING,0,(LPARAM) "Row 2 in Combo Box");
		c_index=SendDlgItemMessage(hDlg,IDC_COMBO1,CB_ADDSTRING,0,(LPARAM) "Row 3 in Combo Box");
		SendDlgItemMessage(hDlg,IDC_COMBO1,CB_SELECTSTRING,-1,(LPARAM) "Row 2 in Combo Box");
		// list box
		l_index=SendDlgItemMessage(hDlg,IDC_LIST1,LB_ADDSTRING,0,(LPARAM)"List row 1");
		l_index=SendDlgItemMessage(hDlg,IDC_LIST1,LB_ADDSTRING,0,(LPARAM)"List row 2");
		l_index=SendDlgItemMessage(hDlg,IDC_LIST1,LB_ADDSTRING,0,(LPARAM)"List row 3");
		SendDlgItemMessage(hDlg,IDC_LIST1,LB_SETCURSEL,0,0);
		return true;
		break;
	case WM_COMMAND:
		if(mID==IDCANCEL)
			EndDialog(hDlg,mID);
		else if(mID==IDC_BUTTON3)
		{
			if(!(IsDlgButtonChecked(hDlg,IDC_CHECK1)+IsDlgButtonChecked(hDlg,IDC_CHECK2)))
				MessageBox(hDlg,"no checked added","asd",MB_OK);
			else
				GetDlgItemText(hDlg,IDC_ToAdd,data,sizeof(data));
			if(IsDlgButtonChecked(hDlg,IDC_CHECK1)&&!(SendDlgItemMessage(hDlg,IDC_COMBO1,CB_FINDSTRING,0,(LPARAM)data)>-1))
			{
				c_index=SendDlgItemMessage(hDlg,IDC_COMBO1,CB_ADDSTRING,0,(LPARAM)data);
				SendDlgItemMessage(hDlg,IDC_COMBO1,CB_SETCURSEL,c_index,0);
				//MessageBox(hDlg,"added in combo box","asd",MB_OK);
			}
			if(IsDlgButtonChecked(hDlg,IDC_CHECK2)&&!(SendDlgItemMessage(hDlg,IDC_LIST1,LB_FINDSTRING,0,(LPARAM)data)>-1))
			{
				l_index=SendDlgItemMessage(hDlg,IDC_LIST1,LB_ADDSTRING,0,(LPARAM)data);
				SendDlgItemMessage(hDlg,IDC_LIST1,LB_SETCURSEL,l_index,0);
				//MessageBox(hDlg,"added in list box","asd",MB_OK);
			} 
		}
		else if(mID==IDC_BUTTON1)
		{
			cbIndex=SendDlgItemMessage(hDlg,IDC_COMBO1,CB_GETCURSEL,0,0);
		
			if(cbIndex>-1)
			{
				SendDlgItemMessage(hDlg,IDC_COMBO1,CB_GETLBTEXT,cbIndex,(LPARAM)data);
				SetDlgItemText(hDlg,IDC_COMBO_SEL,data);
			}
		}
	
		else if(mID==IDC_BUTTON2)
		{
			lbIndex=SendDlgItemMessage(hDlg,IDC_LIST1,LB_GETCURSEL,0,0);
			if(lbIndex>-1)
			{
				SendDlgItemMessage(hDlg,IDC_LIST1,LB_GETTEXT,lbIndex,(LPARAM)data);
				SetDlgItemText(hDlg,IDC_LIST_SEL,data);
			}
		}
		break;
	}
	return false;
}
