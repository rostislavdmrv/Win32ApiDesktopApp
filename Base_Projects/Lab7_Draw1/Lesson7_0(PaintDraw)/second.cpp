// second.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "shape.h"
#include <vector>

using namespace std ;

#define MAX_LOADSTRING 100
typedef tagLOGBRUSH LOGBRUSH;
// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text
POINT pp[3];

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	Click(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	Again(HWND, UINT, WPARAM, LPARAM);


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SECOND, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_SECOND);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_SECOND);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_SECOND;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
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

   ShowWindow(hWnd, SW_MAXIMIZE);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
typedef vector<Shape*> SHPVECTOR;
Shape* CreateShape(SHPVECTOR& shpList, shpType type);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);
	
	static HBRUSH oldBrush;
	static HPEN oldPen;
	static HPEN newPen;
    static POINTS ptsPrevEnd;      
    static BOOL fPrevShp = FALSE; 
	static shpType type = line;
	static SHPVECTOR shpList;
	static Shape* current;
	static int x, y;
	SHPVECTOR::iterator iter;

	

	
	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
			
					case IDM_LI:
						{
							type=line;
						}
						 break;
					case IDM_RE:
					  {
			
						  type=rect;
						}
						 break;
					case IDM_OB:
						{
						SendMessage(hWnd, WM_CUT,0,0);
						}

						 break;
				break;

				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			RECT rt;
			GetClientRect(hWnd, &rt);
		//	HPEN hpen=CreatePen(PS_SOLID, 10, RGB(255,255,255));
			SetBkColor(hdc,RGB(120,220,180 ));  
			DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
		// Painting 2 rectangles	
			HBRUSH hBrush1=CreateSolidBrush(RGB(0xFF,0xFF,0x00));
			SelectObject(hdc, hBrush1);
			Rectangle(hdc, 134, 456, 324, 190);
			HBRUSH hBrush2=CreatePatternBrush(LoadBitmap(hInst, (const char*)IDB_BITMAP1));
			SelectObject(hdc, hBrush2);
			Rectangle(hdc, 634, 456, 340, 190);
		// Fill ellipse with user witmap image
			HBITMAP hBmp=LoadBitmap(hInst, (const char*)IDB_BITMAP2);
			HBRUSH hBrush4=CreatePatternBrush(hBmp);
			SelectObject(hdc, hBrush4);
			Ellipse(hdc, 134, 456, 324, 190);
			
			HBRUSH hBrush3=CreateHatchBrush(HS_CROSS,RGB(0x88,0x88,0x20));
			SelectObject(hdc, hBrush3);
			Ellipse(hdc, 590, 410, 370, 230);
		// ouput text in graphical window
			char* bla=" I can paint ";
			SetTextColor(hdc,RGB(0x5F,0x3F,0x11));  
			SetBkColor(hdc,RGB(0x48,0xAB, 0xFF));  // yellow RGB(255,255,0)
			TextOut(hdc, 150, 100, bla, strlen(bla));
		// four_angle 
			HBITMAP hBmp1=LoadBitmap(hInst, (const char*)IDB_BITMAP4);
			HBRUSH hBrush14=CreatePatternBrush(hBmp1);
			SelectObject(hdc, hBrush14);
			pp[0].x=760; pp[0].y=500;
			pp[1].x=925; pp[1].y=380;
			pp[2].x=990; pp[2].y=500;
			pp[3].x=890; pp[3].y=600;
			Polygon(hdc, pp,4);
		// END
			EndPaint(hWnd, &ps);
			break;
		}
// Line and Rectangle
			case WM_RBUTTONDOWN: 
            
            current = CreateShape(shpList, type);
			current->begin = MAKEPOINTS(lParam);
            return 0; 
        
        case WM_RBUTTONUP: 
            fPrevShp = FALSE;
		
            return 0;
		// I am painting 
		case WM_LBUTTONDOWN:
			x=LOWORD(lParam);
			y=HIWORD(lParam);
			break;
		case WM_MOUSEMOVE:
// Right buttonn
			if(wParam & MK_RBUTTON) 
            { 
                hdc = GetDC(hWnd); 
			
                SetROP2(hdc, R2_NOTXORPEN); 
                if(fPrevShp) 
                { 
					current->end = ptsPrevEnd;
					current->Draw(hdc);
                } 
				current->end = MAKEPOINTS(lParam);
				current->Draw(hdc);
                fPrevShp = TRUE; 
                ptsPrevEnd = current->end; 
		
                ReleaseDC(hWnd, hdc); 
            } 
	// LEFT button -> curve following user	
			if (wParam == MK_LBUTTON)
			{
				hdc = GetDC(hWnd);
				COLORREF color=RGB(0x10,0x10,0xF0);
				HPEN hPen=CreatePen(PS_DOT, 3, color);
				SelectObject(hdc, hPen);
				MoveToEx (hdc, x, y, NULL); // move graphical curcor to plase of pressin LB
				x=LOWORD(lParam); 
				y=HIWORD(lParam);
				LineTo (hdc, x, y);
			//	ReleaseDC(hWnd, hdc);
			};
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
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
	}
    return FALSE;
}
// New line or rectangle
Shape* CreateShape(SHPVECTOR& shpList, shpType type)
{
	SHPVECTOR::iterator iter;
	switch(type)
	{
		case line:
			shpList.push_back(new Line());
			break;
		case rect:
			shpList.push_back(new Rect());
	}
	
	if(shpList.size() > 0)         
	{
		iter = shpList.end();
		iter--;
        return (Shape*)(*iter);
	}
    else
        return NULL;
}
// Mesage handler for about box.
#include "stdafx.h"
#include "resource.h"

extern HINSTANCE hInst;

