// RRD570.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "RRD570.h"
#include  <string>
#include "stdio.h"
#include <stdio.h>
#include "math.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING]; 
// the main window class name
int x1, x2, x3, x4;
double x5,x6,x7, x8,x9,sum;
int cbin, g1, g2, g3, g4;
char data[10];

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    r(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_RRD570, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RRD570));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
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
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RRD570));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_RRD570);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
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
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
        PAINTSTRUCT ps;
        HDC hdc;
        int wmId = LOWORD(wParam);
        int wmEvent = HIWORD(wParam);
            
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case ID_TEST1A_Y4:
            {
                HMENU hMenu = GetMenu(hWnd);
                UINT res = GetMenuState(hMenu, ID_TEST1A_Y8, MF_BYCOMMAND);
                if (res & MF_CHECKED)
                    CheckMenuItem(hMenu, ID_TEST1A_Y8, MF_BYCOMMAND | MF_UNCHECKED);
                else
                    CheckMenuItem(hMenu, ID_TEST1A_Y8, MF_BYCOMMAND | MF_CHECKED);
                break;
            }
            break;
            case ID_TEST1A_Y6:
            {
                MessageBox(hWnd, _T("I am Y6"), _T("Info"), MB_OK | MB_ICONINFORMATION);
            }
            break;
            case ID_TEST1A_Y8:
            {
                MessageBox(hWnd, _T("I am Y8"), _T("Info"), MB_OK | MB_ICONINFORMATION);
            }
            break;
            case ID_TEST1A_Y10:
            {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, r);
            }
            break;
            case ID_TEST1A_Y12:
            {
                HMENU hMenu = GetMenu(hWnd);
                if (GetMenuState(hMenu, ID_TEST1A_Y12 +1, MF_BYCOMMAND) == -1)
                {
                    MENUITEMINFO mii;
                    ZeroMemory(&mii, sizeof(mii));
                    mii.cbSize = sizeof(mii);
                    mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
                    mii.wID = ID_TEST1A_Y6;
                    mii.fType = MFT_STRING;
                    mii.dwTypeData = (LPSTR)TEXT("Y7");
                    mii.fState = MFS_ENABLED;


                    InsertMenuItem(hMenu, ID_TEST1A_Y4, FALSE, &mii);
                }
            }
            break;
            case ID_XXX_NEW:
            {
                MessageBox(hWnd, _T("I am NEW"), _T("Info"), MB_OK | MB_ICONINFORMATION);

            }
            break;
            case ID_XXX_Y10:
            {
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, r);

            }
            break;
           /* case ID_XXX_Y12:
            {
                MessageBox(hWnd, _T("I am Y12"), _T("Info"), MB_OK | MB_ICONINFORMATION);

            }
            break;*/


            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_RBUTTONDOWN:
    {
        HMENU hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU1));
        HMENU hSubMenu = GetSubMenu(hMenu, 0);
        POINT pt = { LOWORD(lParam), HIWORD(lParam) };
        ClientToScreen(hWnd, &pt);
        TrackPopupMenu(hSubMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd,
            NULL);
        DestroyMenu(hMenu);

    }
    break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
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
INT_PTR CALLBACK r(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        SetDlgItemInt(hDlg, IDC_EDIT1, 15, TRUE);
        SetDlgItemInt(hDlg, IDC_EDIT2, 3, TRUE);
        SetDlgItemInt(hDlg, IDC_EDIT3, 8, TRUE);
        SetDlgItemText(hDlg, IDC_EDIT5, "2.23");
        SetDlgItemText(hDlg, IDC_EDIT6, "1.78");
        CheckDlgButton(hDlg, IDC_RADIO1, MFS_CHECKED);
        CheckDlgButton(hDlg, IDC_CHECK1, MFS_CHECKED);
        CheckDlgButton(hDlg, IDC_CHECK2, MFS_CHECKED);
        CheckDlgButton(hDlg, IDC_CHECK3, MFS_CHECKED);
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        
        else if (LOWORD(wParam) == IDC_BUTTON1)
        {
            //sedmica5 reshenie ! числата са int 
            BOOL* LPt = NULL;
            BOOL SIG = TRUE;
            x1 = 0;
            x2 = 0;
            x3 = 0;
            char t1[10], t11[10], t2[10], t22[10], t3[10], * stopstring;
            
            if (IsDlgButtonChecked(hDlg, IDC_CHECK1))
            {
                x1 = GetDlgItemInt(hDlg, IDC_EDIT1, LPt, SIG);
            }
            if (IsDlgButtonChecked(hDlg, IDC_CHECK2))
            {
                x2 = GetDlgItemInt(hDlg, IDC_EDIT2, LPt, SIG);
            }
            if (IsDlgButtonChecked(hDlg, IDC_CHECK3))
            {
                x3 = GetDlgItemInt(hDlg, IDC_EDIT3, LPt, SIG);
            }
        
            if (IsDlgButtonChecked(hDlg, IDC_RADIO1)) {
               
                x4 = (x3 - x1) *( x2);
                SetDlgItemInt(hDlg, IDC_EDIT4, x4, TRUE);
            }
            if (IsDlgButtonChecked(hDlg, IDC_RADIO1))
            {
                
                if (x3 != 0)
                {
                   x4 = (x1 + x2) / x3;
                    SetDlgItemInt(hDlg, IDC_EDIT4, x4, TRUE);
                }
                else
                {
                    MessageBox(hDlg, "Cannot divide by zero!", "Error", MB_OK | MB_ICONERROR);
                }

             }
            if (IsDlgButtonChecked(hDlg, IDC_RADIO2)) {

                x4 = (x1 - x2) * (x3);
                SetDlgItemInt(hDlg, IDC_EDIT4, x4, TRUE);
            }


        }
        else if (LOWORD(wParam) == IDC_BUTTON2)

        {
            BOOL* LPt = NULL;
            BOOL SIG = TRUE;
            
            char t19[10], t119[10], t29[10], t229[10], t39[10], t2299[10], * stopstring;

            GetDlgItemText(hDlg, IDC_EDIT5, t19, 100); x5 = strtod(t19, &stopstring);
            GetDlgItemText(hDlg, IDC_EDIT6, t29, 100); x6 = strtod(t29, &stopstring);
            GetDlgItemText(hDlg, IDC_EDIT3, t39, 100); x8 = strtod(t39, &stopstring);
            if (x5 == 0)
            {
                MessageBox(hDlg, "CANNOT", "MSG", MB_OK | MB_ICONERROR); break;
            }
            if (x6 == 0)
            {
                MessageBox(hDlg, "CANNOT", "MSG", MB_OK | MB_ICONERROR); break;
            }
            if (x8 == 0)
            {
                MessageBox(hDlg, "CANNOT", "MSG", MB_OK | MB_ICONERROR); break;
            }

            x7 = (2 * ((x5 * x5) - x6)) + 1.3;

            sprintf_s(t229, "%8.2f", x7);
            SetDlgItemText(hDlg, IDC_EDIT7, t229);

            x9 = (2 * ((x8 * x8) - x5)) + 4.45;

            sprintf_s(t2299, "%8.2f", x9);
            SetDlgItemText(hDlg, IDC_EDIT8, t2299);

        } 

        break;
    }
    return (INT_PTR)FALSE;
}
