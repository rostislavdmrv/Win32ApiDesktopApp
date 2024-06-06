// MSV531.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "stdio.h"
#include "MSV531.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
int A, B, C, res;
double C_1;
double D, E,res_1,res_2;
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK   MyProg(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_MSV531, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MSV531));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MSV531));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MSV531);
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
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case ID_TEST1A_Y10:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, MyProg);
                break;
            case ID_TEST1A_Y4:
            {
                HMENU hMenu = GetMenu(hWnd);
                UINT res = GetMenuState(hMenu, ID_TEST1A_Y8, MF_BYCOMMAND);
                if (res & MF_CHECKED)
                    CheckMenuItem(hMenu, ID_TEST1A_Y8, MF_BYCOMMAND | MF_UNCHECKED);
                else
                    CheckMenuItem(hMenu, ID_TEST1A_Y8, MF_BYCOMMAND | MF_CHECKED);
            }
                break;
            case ID_TEST1A_Y6:
            {
                MessageBox(hWnd, _T("I'm y6"), _T("MSG"), MB_OK);
            }
                break;
            case ID_TEST1A_Y8:
            {
                MessageBox(hWnd, _T("I'm y8"), _T("MSG"), MB_OK);
            }
            break;
            case ID_POP_NEW:
            {
                MessageBox(hWnd, _T("I'm new"), _T("MSG"), MB_OK);
            }
            break;
             case ID_TEST1A_Y12:
                {
                    HMENU hMenu = GetMenu(hWnd);
                    if (GetMenuState(hMenu, ID_TEST1A_Y4 + 4, MF_BYCOMMAND) == -1)
                    {
                        MENUITEMINFO mii;
                        ZeroMemory(&mii, sizeof(mii));
                        mii.cbSize = sizeof(mii);
                        mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
                        mii.wID = ID_TEST1A_Y6;
                        mii.fType = MFT_STRING;
                        mii.dwTypeData = (LPSTR)TEXT("y7");
                        mii.fState = MFS_ENABLED;
                        InsertMenuItem(hMenu, ID_TEST1A_Y4, FALSE, &mii);
                    }
                }
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
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
    case WM_RBUTTONDOWN:
    {
        HMENU hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU1));
        HMENU hSubMenu = GetSubMenu(hMenu, 0);
        POINT pt = { LOWORD(lParam), HIWORD(lParam) };
        ClientToScreen(hWnd, &pt);
        TrackPopupMenu(hSubMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd, NULL);
        DestroyMenu(hMenu);
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

INT_PTR CALLBACK MyProg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    char DD[10], EE[10],CC[10],result_1[10], result_2[10], * stopstring;
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        SetDlgItemInt(hDlg, IDC_EDIT1, 15, TRUE);
        SetDlgItemInt(hDlg, IDC_EDIT2, 3, TRUE);
        SetDlgItemInt(hDlg, IDC_EDIT3, 8, TRUE);
        SetDlgItemText(hDlg, IDC_EDIT5, "2.33");
        SetDlgItemText(hDlg, IDC_EDIT6, "1.78");
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDC_BUTTON1)
        {

            BOOL* LPt = NULL;
            BOOL SIG = TRUE;
            A = 0;
            B = 0;
            C = 0;
            if (IsDlgButtonChecked(hDlg, IDC_CHECK1))
            {
                A = GetDlgItemInt(hDlg, IDC_EDIT1, LPt, SIG);
            }
            if (IsDlgButtonChecked(hDlg, IDC_CHECK2))
            {
                B = GetDlgItemInt(hDlg, IDC_EDIT2, LPt, SIG);
            }
            if (IsDlgButtonChecked(hDlg, IDC_CHECK3))
            {
                C= GetDlgItemInt(hDlg, IDC_EDIT3, LPt, SIG);
            }
            res = (C - A) * B;
            SetDlgItemInt(hDlg, IDC_EDIT4, res, TRUE);
        }
        else if (LOWORD(wParam) == IDC_BUTTON2)
        {
            BOOL* LPt = NULL;
            BOOL SIG = TRUE;
            A = 0;
            B = 0;
            C = 0;
            if (IsDlgButtonChecked(hDlg, IDC_CHECK1))
            {
                A = GetDlgItemInt(hDlg, IDC_EDIT1, LPt, SIG);
            }
            if (IsDlgButtonChecked(hDlg, IDC_CHECK2))
            {
                B = GetDlgItemInt(hDlg, IDC_EDIT2, LPt, SIG);
            }
            if (IsDlgButtonChecked(hDlg, IDC_CHECK3))
            {
                C = GetDlgItemInt(hDlg, IDC_EDIT3, LPt, SIG);
            }
            if (C != 0)
            {
                res = (A + B) / C;
                SetDlgItemInt(hDlg, IDC_EDIT4, res, TRUE);
            }
            else
            {
                MessageBox(hDlg, "C=0", "MSG", MB_OK | MB_ICONERROR);
            }
            
        }
        else if (LOWORD(wParam) == IDC_BUTTON3)
        {
            C_1 = 0;
            if (IsDlgButtonChecked(hDlg, IDC_CHECK3))
            {
                GetDlgItemText(hDlg, IDC_EDIT3, CC, 10);
                C_1= strtod(CC, &stopstring);
            }
            GetDlgItemText(hDlg, IDC_EDIT5,DD, 10);
            D = strtod(DD, &stopstring);
            GetDlgItemText(hDlg, IDC_EDIT6, EE, 10);
            E = strtod(EE, &stopstring);
            res_1 = 2 * (D * D - E) + 1.3;
            res_2 = 2*(C_1 * C_1 - D) + 4.45;
            sprintf_s(result_1, "%8.3f", res_1);
            SetDlgItemText(hDlg, IDC_EDIT7, result_1);
            sprintf_s(result_2, "%8.3f", res_2);
            SetDlgItemText(hDlg, IDC_EDIT8, result_2);
        }
        break;
    }
    return (INT_PTR)FALSE;
}

