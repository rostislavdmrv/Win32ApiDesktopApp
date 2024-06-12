// Lab4_D2.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Lab4_D2.h"
#include  <string>
#include "stdafx.h"
#include "stdio.h"
#include <stdio.h>
#include "math.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
double x1,x2,x3, sum;
int cbin, g1, g2, g3;
char data[10];


// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	M_I(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	M_R(HWND, UINT, WPARAM, LPARAM);

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
	LoadString(hInstance, IDC_LAB4_D2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB4_D2));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB4_D2));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_LAB4_D2);
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
		case ID_CALC_INT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, M_I);
			break;
		case ID_CALC_REAL:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, M_R);
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
INT_PTR CALLBACK M_I(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{  // char data[10];
//	int in;
//	double result;


	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		SetDlgItemInt(hDlg,IDC_EDIT1, 10,TRUE);
		SetDlgItemInt(hDlg,IDC_EDIT2, 5,TRUE);
		CheckDlgButton(hDlg,IDC_RADIO1, MFS_CHECKED);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDC_BUTTON1) 
			{
				
			BOOL *LPt=NULL;
			BOOL SIG=TRUE;
			g1=GetDlgItemInt(hDlg,IDC_EDIT1,LPt, SIG);
			g2=GetDlgItemInt(hDlg,IDC_EDIT2,LPt, SIG);
			if (IsDlgButtonChecked(hDlg,IDC_RADIO1))
			g3=g1+g2;
			else
			g3=g1-g2;
			SetDlgItemInt(hDlg,IDC_EDIT3, g3,TRUE);
		}

		break;
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK M_R(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	char t1[10], t11[10],t2[10],t22[10],t3[10], *stopstring;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		
		CheckDlgButton(hDlg,IDC_CHECK1, MFS_CHECKED);
		CheckDlgButton(hDlg,IDC_CHECK2, MFS_CHECKED);
		CheckDlgButton(hDlg,IDC_CHECK3, MFS_CHECKED);
		SetDlgItemText(hDlg,IDC_EDIT1,"0.5");
		SetDlgItemText(hDlg,IDC_EDIT2,"1.51");
		SetDlgItemText(hDlg,IDC_EDIT3,"2.63");
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDC_BUTTON1) 
			{   sum=0;
				if (IsDlgButtonChecked(hDlg,IDC_CHECK1))
				{	GetDlgItemText(hDlg,IDC_EDIT1,t1,100);
				x1=strtod(t1,&stopstring);
				sum=sum+x1;}
				if (IsDlgButtonChecked(hDlg,IDC_CHECK2))
				{	GetDlgItemText(hDlg,IDC_EDIT2,t2,100);
				x2=strtod(t2,&stopstring);
				sum=sum+x2;}
				if (IsDlgButtonChecked(hDlg,IDC_CHECK3))
				{	GetDlgItemText(hDlg,IDC_EDIT3,t3,100);
				x3=strtod(t3,&stopstring);
				sum=sum+x3;}
			sprintf_s(t22, "%8.3f",sum);
			
			//MessageBox(hDlg, "ERROR ","Info", MB_OK);
			//	x3=x1+x2;	
				
			//	gcvt(x3,10,t3);
				SetDlgItemText(hDlg,IDC_EDIT4,t22);
				return TRUE;
			}
				break;
	}
	return (INT_PTR)FALSE;
}