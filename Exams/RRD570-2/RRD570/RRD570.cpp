// RRD570.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "RRD570.h"
#include  <string>
#include "stdio.h"
#include <stdio.h>
#include "math.h"
#include "commctrl.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

double x1, x2, x3, x4, x5, sum, result;
int cbin, g1, g2, g3;
char data[10];

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    R(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    R1(HWND, UINT, WPARAM, LPARAM);


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
    int wmId, wmEvent;

    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR szHello[MAX_LOADSTRING];

    static HBRUSH oldBrush;
    static HPEN oldPen;
    static HPEN newPen;
    static POINTS ptsPrevEnd;
    static BOOL fPrevShp = FALSE;

    switch (message)
    {
    case WM_COMMAND:
        {
             wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case ID_TASK2_FUNCTION:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, R);
                break;
           /* case ID_TASK2_PROGRESSBAR:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG3), hWnd, R1);
                break;*/

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

            HPEN hpen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
            SelectObject(hdc, hpen);

            POINT vertices1[] = { {200, 200}, {300, 200},{250,400} };
            Polygon(hdc, vertices1, sizeof(vertices1) / sizeof(vertices1[0]));
            MoveToEx(hdc, 200, 200, NULL);
            LineTo(hdc, 150, 280);
            LineTo(hdc, 250, 400);
            LineTo(hdc, 350, 280);
            LineTo(hdc, 300, 200);
            MoveToEx(hdc, 150, 280, NULL);
            LineTo(hdc, 350, 280);



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
#define TIMER1 500

INT_PTR CALLBACK R(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    char t1[10], t11[10], t2[10], t22[10], t3[10], t4[10], * stopstring;
    char data[20];
    int c_index, l_index;
    int mID;
    int cbIndex;
    int lbIndex;

    static int step = 1;

    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        SetDlgItemText(hDlg, IDC_EDIT1, "1.1");
        SetDlgItemText(hDlg, IDC_EDIT2, "2.2");
        SetDlgItemText(hDlg, IDC_EDIT3, "3.3");
        l_index = SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)"2.3");
        l_index = SendDlgItemMessage(hDlg, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)"10.4");

        SetDlgItemInt(hDlg, IDC_EDIT5, 0, NULL);

        SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
        SendDlgItemMessage(hDlg, IDC_PROGRESS2, PBM_SETRANGE, 0, MAKELPARAM(0, 100));

        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        if (LOWORD(wParam) == IDC_BUTTON3) {
            SetTimer(hDlg, TIMER1, 1, NULL);
            break;
        }
        else if (LOWORD(wParam) == IDC_BUTTON1) {
            GetDlgItemText(hDlg, IDC_EDIT1, data, sizeof(data));
            if (!(SendDlgItemMessage(hDlg, IDC_COMBO1, CB_FINDSTRING, 0, (LPARAM)data) > -1))
            {
                c_index = SendDlgItemMessage(hDlg, IDC_COMBO1, CB_ADDSTRING, 0, (LPARAM)data);
                SendDlgItemMessage(hDlg, IDC_COMBO1, CB_SETCURSEL, c_index, 0);
            }
            else
            {
                MessageBox(hDlg, "The value is already in the combo box!", "Error", MB_OK);
            }

        }
        else if (LOWORD(wParam) == IDC_BUTTON2) {
            lbIndex = SendDlgItemMessage(hDlg, IDC_LIST1, LB_GETCURSEL, 0, 0);
            x3 = 0;
            if (lbIndex > -1)
            {
                
                    SendDlgItemMessage(hDlg, IDC_LIST1, LB_GETTEXT, lbIndex, (LPARAM)data);
                    x3 = strtod(data, &stopstring);
                

            }

            GetDlgItemText(hDlg, IDC_EDIT2, t1, 100);
            x1 = strtod(t1, &stopstring);

            GetDlgItemText(hDlg, IDC_EDIT3, t2, 100);
            x2 = strtod(t2, &stopstring);

            if (IsDlgButtonChecked(hDlg, IDC_RADIO1)) {

                if (x3 != 0)
                {
                    x5 = (x1 + x2) / x3;
                    sprintf_s(t11, "%8.3f", x5);
                    SetDlgItemText(hDlg, IDC_EDIT4, t11);
                    
                }
                else
                {
                    MessageBox(hDlg, "Cannot divide by zero!", "Error", MB_OK | MB_ICONERROR);
                }
            }
            if (IsDlgButtonChecked(hDlg, IDC_RADIO2)) {

                x4 = (x1 - x2) * (x3);
                sprintf_s(t22, "%8.3f", x4);
                SetDlgItemText(hDlg, IDC_EDIT4, t22);
            }

        }

        break;

       case WM_TIMER:
           int counter = GetDlgItemInt(hDlg, IDC_EDIT5, NULL, FALSE);
           counter += 1;
           SetDlgItemInt(hDlg, IDC_EDIT5, counter, NULL);

           if (SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_GETPOS, 0, 0) < 100)
           {
               SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETSTEP, step, 0);
               SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_STEPIT, 0, 0);
           }
           if (SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_GETPOS, 0, 0) == 100) {

               if (SendDlgItemMessage(hDlg, IDC_PROGRESS2, PBM_GETPOS, 0, 0) < 100)
               {
                   SendDlgItemMessage(hDlg, IDC_PROGRESS2, PBM_SETSTEP, step, 0);
                   SendDlgItemMessage(hDlg, IDC_PROGRESS2, PBM_STEPIT, 0, 0);
                   break;
               }
               else {
                   KillTimer(hDlg, TIMER1);
               }
           }
           break;

    }
    return (INT_PTR)FALSE;
}


/*INT_PTR CALLBACK R1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int step = 1;

    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        SetDlgItemInt(hDlg, IDC_EDIT1, 0, NULL);

        SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
        SendDlgItemMessage(hDlg, IDC_PROGRESS2, PBM_SETRANGE, 0, MAKELPARAM(0, 100));
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        if (LOWORD(wParam) == IDC_BUTTON1) {
            SetTimer(hDlg, TIMER1, 1, NULL);
            break;
        }

    case WM_TIMER:

        int counter = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, FALSE);
        counter += 1;
        SetDlgItemInt(hDlg, IDC_EDIT1, counter, NULL);

       

        if (SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_GETPOS, 0, 0) >= 100)
        {
            if (SendDlgItemMessage(hDlg, IDC_PROGRESS2, PBM_GETPOS, 0, 0) >= 100)
            {
                break;
            }
            SendDlgItemMessage(hDlg, IDC_PROGRESS2, PBM_SETSTEP, step, 0);
            SendDlgItemMessage(hDlg, IDC_PROGRESS2, PBM_STEPIT, 0, 0);
            break;
        }
        SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETSTEP, step, 0);
        SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_STEPIT, 0, 0);





        break;
    }
    return (INT_PTR)FALSE;
}*/
