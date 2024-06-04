// Drawing.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Drawing.h"
#include "shape.h"
#include <vector>
#include "stdafx.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_DRAWING, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAWING));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAWING));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DRAWING);
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
    static shpType type = line;


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

            //HOUSE
            HBRUSH hBrush1 = CreateSolidBrush(RGB(255, 0, 255));
            SelectObject(hdc, hBrush1);

            Rectangle(hdc, 300, 300, 600, 650);

            //DOOR
            hBrush1 = CreateSolidBrush(RGB(255, 69, 0));
            SelectObject(hdc, hBrush1);

            Rectangle(hdc, 450, 450, 550, 650);

            //WINDOW
            hBrush1 = CreateHatchBrush(HS_VERTICAL, RGB(255, 69, 0));
            SelectObject(hdc, hBrush1);

            Rectangle(hdc, 325, 350, 425, 450);

            //ROOF

            hBrush1 = CreateHatchBrush(HS_DIAGCROSS, RGB(0, 255, 255));
            SelectObject(hdc, hBrush1);

            POINT vertices[] = { {200, 300}, {450, 150}, {700, 300} };
            Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));

            //FENCE
            HPEN hpen = CreatePen(PS_SOLID, 10, RGB(47, 79, 79));
            SelectObject(hdc, hpen);

            POINT vertices2[] = { {600, 450}, {1200, 450} };
            Polygon(hdc, vertices2, sizeof(vertices2) / sizeof(vertices2[0]));

            POINT vertices3[] = { {600, 600}, {1200, 600} };
            Polygon(hdc, vertices3, sizeof(vertices3) / sizeof(vertices3[0]));

            POINT vertices4[] = { {800, 400}, {800, 650} };
            Polygon(hdc, vertices4, sizeof(vertices4) / sizeof(vertices4[0]));

            POINT vertices5[] = { {1000, 400}, {1000, 650} };
            Polygon(hdc, vertices5, sizeof(vertices5) / sizeof(vertices5[0]));

            POINT vertices6[] = { {1200, 400}, {1200, 650} };
            Polygon(hdc, vertices6, sizeof(vertices6) / sizeof(vertices6[0]));


            //LAKE
            hpen = CreatePen(PS_SOLID, 1, RGB(128, 64, 0));
            SelectObject(hdc, hpen);
            hBrush1 = CreateSolidBrush(RGB(0x00, 0X00, 0x255));
            SelectObject(hdc, hBrush1);
            Ellipse(hdc, 500, 700, 800, 800);

            //Rectangle(hdc, 300, 200, 400, 400);


            //Rectangle(hdc, 300, 300, 600, 600);

            HBRUSH hBrush2 = CreateSolidBrush(RGB(0xFF, 0xFF, 0x80));
            SelectObject(hdc, hBrush2);
            //Rectangle(hdc, 634, 456, 340, 190);
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

extern HINSTANCE hInst;