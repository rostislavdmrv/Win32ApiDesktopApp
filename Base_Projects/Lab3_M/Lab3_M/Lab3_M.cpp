// Lab3_M.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Lab3_M.h"

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
	LoadString(hInstance, IDC_LAB3_M, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB3_M));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB3_M));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_LAB3_M);
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
				case IDM_OPEN:
					MessageBox(hWnd, _T("Open"), _T("Info"), MB_OK | MB_ICONINFORMATION);
					break;
				case IDM_SAVE:
					MessageBox(hWnd, _T("Save"), _T("Info"), MB_OK | MB_ICONINFORMATION);
					break;
				case IDM_CHECK:
					{
						HMENU hMenu = GetMenu(hWnd);
						UINT res = GetMenuState(hMenu, IDM_CHECK, MF_BYCOMMAND);
						if(res & MF_CHECKED)
							CheckMenuItem(hMenu, IDM_CHECK, MF_BYCOMMAND | MF_UNCHECKED);
						else
							CheckMenuItem(hMenu, IDM_CHECK, MF_BYCOMMAND | MF_CHECKED);
					}
					break;
				case IDM_DISABLE:
					{
						HMENU hMenu = GetMenu(hWnd);
						EnableMenuItem(hMenu, IDM_DISABLE, MF_BYCOMMAND | MF_GRAYED);
					}
					break;
				case IDM_ENABLE:
					{
						HMENU hMenu = GetMenu(hWnd);
						UINT res = GetMenuState(hMenu, IDM_DISABLE, MF_BYCOMMAND);
						if(res & MF_GRAYED)
							EnableMenuItem(hMenu, IDM_DISABLE, MF_BYCOMMAND | MF_ENABLED);
						else
							EnableMenuItem(hMenu, IDM_DISABLE, MF_BYCOMMAND | MF_GRAYED);
					}
					break;
				case IDM_ADD:
					{
						HMENU hMenu = GetMenu(hWnd);
						
						if(GetMenuState(hMenu, IDM_ADD + 4, MF_BYCOMMAND) == -1) // or disable
						{
							MENUITEMINFO mii;
							ZeroMemory(&mii, sizeof(mii));
							mii.cbSize = sizeof(mii);
							mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
							mii.wID = IDM_ADD + 4;
							mii.fType = MFT_STRING;
							mii.dwTypeData = TEXT("Delete me");
							mii.fState = MFS_ENABLED;

							InsertMenuItem(hMenu, IDM_ADD, FALSE, &mii);
						}
					}
					break;
				case IDM_ADD + 4:
					{
						HMENU hMenu = GetMenu(hWnd);
						DeleteMenu(hMenu, IDM_ADD + 4, MF_BYCOMMAND);
					}
					break;
				case IDM_DO:
					MessageBox(hWnd, "Do Something else", "Title Message", MB_OK);
					break;
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_RBUTTONDOWN:
			{
				HMENU hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_POP));
				HMENU hSubMenu = GetSubMenu(hMenu, 0);
				POINT pt = {LOWORD(lParam), HIWORD(lParam)};
				ClientToScreen(hWnd, &pt);
				TrackPopupMenu(hSubMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd, NULL);
				DestroyMenu(hMenu);
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			RECT rt;
			GetClientRect(hWnd, &rt);
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
/*	switch (message)
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
	return 0; */
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
