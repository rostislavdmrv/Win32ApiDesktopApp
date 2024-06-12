// myWin32.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "supplementary.h"
#undef RAND_MAX
#define RAND_MAX 255

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	myFunction(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    myCheckFunction(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);  // pri startirane na about box
extern LRESULT CALLBACK functionMouse(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance,              // vhodna tochka na programata
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MYWIN32, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_MYWIN32);

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
	wcex.lpfnWndProc	= (WNDPROC)WndProc;          // WndProc - funkciq, chrez koqto stava prosledqvaneto
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_MYWIN32);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_MYWIN32;
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

   /* show window 
     |SW_MAXIMIZE -> qsno
	 HDC - handle device complect - za risuvane
	   hDC = GetDC(hWnd)

  MoveToEx (hDC, x, y) - mestene bez chertane na liniq
  LineTo(hDC, x, y) - ot tochkata s chertane na liniq
	 
   */	   
   ShowWindow(hWnd, nCmdShow|SW_MAXIMIZE);

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)  // 1 - handle na prozoreca, 2 - deistviq na potrebitelq, 3, 4 - parametri na syobshtenieto
{
	int wmId, wmEvent;
	static int xs, ys;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);
    
	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); // id na controla
			wmEvent = HIWORD(wParam); 
	
			// Parse the menu selections:
			
			switch (wmId)
			{
				case IDM_ABOUT: // id ot meniuto
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About); // startirane na dialog - 1 - handle na instanciqta, 2 - id na dialoga, 3 - roditelqt, 4 - funkciqta za obslujvane
				   break;
				case IDM_EXIT: // id na exit
				   DestroyWindow(hWnd);
				   break;
				case ID_TESTTIMER:
				   DialogBox(hInst, (LPCTSTR)IDD_DIALOG3, hWnd, (DLGPROC)functionMouse); // startirane na dialog - 1 - handle na instanciqta, 2 - id na dialoga, 3 - roditelqt, 4 - funkciqta za obslujvane
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT: {
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			RECT rt;
			GetClientRect(hWnd, &rt);
			
			HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
			SelectObject(hdc, hPen);
			MoveToEx(hdc, rt.left+10, rt.bottom-10, NULL);
			LineTo(hdc, rt.right-10, rt.bottom-10);
			MoveToEx(hdc, rt.left+10, rt.bottom-10, NULL);
			LineTo(hdc, rt.left+10, rt.top-10);

			hPen = CreatePen(PS_SOLID, 1, RGB(150, 50, 50));
			SelectObject(hdc, hPen);
			
//			HBRUSH hBrush = CreateSolidBrush(RGB(132, 123, 231));  // za zapylvane

			HBITMAP hBmp = LoadBitmap(hInst, (LPCTSTR)IDB_BITMAP1);
			HBRUSH bitmap = CreatePatternBrush(hBmp);
			SelectObject(hdc, bitmap);
			Rectangle(hdc, 120, 200, 250, rt.bottom-10);
			
			//hBrush = CreateSolidBrush(RGB(231, 132, 123));
			HBRUSH hatch = CreateHatchBrush( HS_CROSS, RGB(123,180,220));  // stil(HS_CROSS, HS_DIAGCROSS) i cvqt -> za .
			SelectObject(hdc, hatch);
			Ellipse(hdc, 300, 150, 400, 500);

			SetTextColor(hdc, RGB(190, 190, 190));
			TextOut(hdc, 600, 300, "text1", strlen("text1"));
			
			SetBkColor(hdc, RGB(100, 100, 100));
			
			TextOut(hdc, 600, 500, "text2", strlen("text2"));
			
			
			
//			Rectangle(hdc, 5, 5, 20, 20);
			char string[15];
			itoa(rt.right, string, 10);
			for (int i =0; i<15; i++) {
				if (!isdigit(string[i])) {
					string[i] = '\0';
					break;
				}
			}
			SetTextColor(hdc, RGB(2, 7, 251));
			SetBkColor(hdc, RGB(255, 78, 28));
			TextOut(hdc, rt.right-70, rt.top+20, string, strlen(string));

			itoa(rt.bottom, string, 10);
			for (i =0; i<15; i++) {
				if (!isdigit(string[i])) {
					string[i] = '\0';
					break;
				}
			}
			TextOut(hdc, rt.right-70, rt.top+35, string, strlen(string));

//			DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
//			DrawText(hdc, string, strlen(string), &rt, DT_RIGHT);
			
			
			EndPaint(hWnd, &ps);
			break;
		}
		
		
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		
		case WM_LBUTTONDOWN: {                       // za risuvane
			xs = LOWORD(lParam);
			ys = HIWORD(lParam);
			break;
		}
		
		case WM_MOUSEMOVE: {
			hdc = GetDC(hWnd);
			int r = rand();
			int g = rand();
			int b = rand();
			HPEN hPen = CreatePen(PS_SOLID, 1, RGB(r, g, b));
			SelectObject(hdc, hPen);
			MoveToEx(hdc, xs, ys, NULL);
			
			if (wParam & MK_LBUTTON) {
				xs = LOWORD(lParam);
			    ys = HIWORD(lParam);
				LineTo(hdc, xs, ys);
			}
			
			break;
		}


		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}


// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)  // pri startirane na about box
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


LRESULT CALLBACK myFunction(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)  // pri startirane na about box
{
	switch (message)
	{
		case WM_INITDIALOG:
			SetDlgItemText(hDlg, IDC_EDITFIELD, "default text");	
			return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			if (LOWORD(wParam) == IDMYBUTTON) {    // pri syzdaden buton se vika MessageBox, parametrite ot help
			    DialogBox(hInst, (LPCTSTR)IDD_NEWWINDIALOG, hDlg, (DLGPROC)myCheckFunction); // startirane na dialog - 1 - handle na instanciqta, 2 - id na dialoga, 3 - roditelqt, 4 - funkciqta za obslujvane	
				return TRUE;
				
			}
			if (LOWORD(wParam) == IDBUTTON1) {    // pri syzdaden buton se vika MessageBox, parametrite ot help
				int returnButtonID;
				returnButtonID = MessageBox(hDlg, "Pressed Button1", "Info", MB_YESNO | MB_ICONINFORMATION); // izrejdane na dopylnitelnite flagove, razdeleni s |
				switch (returnButtonID) { // MessageBox vryshta tipa na natisnatiq buton, proverka koi tochno e natisnat
					case IDYES:
						MessageBox(hDlg, "you pressed: yes", "info", MB_OK);
						break;
					case IDNO:
						MessageBox(hDlg, "you pressed: no", "info", MB_OK | MB_ICONINFORMATION);
						break;
				}
				return TRUE;
			}
			if (LOWORD (wParam) == IDC_READBUTTON) {
			    // tuk - chetene ot edit box
				char stringread[81];
				GetDlgItemText(hDlg, IDC_EDITFIELD, stringread, sizeof(stringread)); // prochita napisanoto v edit box-a
				if (!strlen(stringread)) strcpy(stringread, "no text typed");
				MessageBox(hDlg, stringread, "info", MB_OK | MB_ICONINFORMATION); // izvejda napisanoto v edit box-a
			}
			break;
	}
    return FALSE;
}

LRESULT CALLBACK myCheckFunction(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)  // pri startirane na about box
{
	switch (message)
	{
		case WM_INITDIALOG:
			SetDlgItemText(hDlg, IDC_EDITBOX2, "text");
			return TRUE;
	
		case WM_COMMAND:
			// if (LOWORD(wParam) == IDOK ) {				}
			if (LOWORD(wParam) == IDC_ADDTOBOX) {
				char stringread[81];
				GetDlgItemText(hDlg, IDC_EDITBOX2, stringread, sizeof(stringread)); // prochita napisanoto v edit box-a
				if (!strlen(stringread)) strcpy(stringread, "no text typed");
				
				if (IsDlgButtonChecked(hDlg, IDC_CHECKLEFT) == BST_CHECKED) {
					if (SendDlgItemMessage (hDlg, IDC_COMBOBOX, CB_FINDSTRING, 0, (LPARAM)stringread) == -1) {
						int position = SendDlgItemMessage (hDlg, IDC_COMBOBOX, CB_ADDSTRING, 0, (LPARAM)stringread);
						SendDlgItemMessage (hDlg, IDC_COMBOBOX, CB_SETCURSEL, position, 0);
					}
					else MessageBox(hDlg, "ima veche takyv string", "info", MB_OK);

				}				
				if (IsDlgButtonChecked(hDlg, IDC_CHECKRIGHT) == BST_CHECKED) {
					if (SendDlgItemMessage (hDlg, IDC_LISTBOX, LB_FINDSTRING, 0, (LPARAM)stringread) == -1) {
						int position = SendDlgItemMessage (hDlg, IDC_LISTBOX, LB_ADDSTRING, 0, (LPARAM)stringread);
						SendDlgItemMessage (hDlg, IDC_LISTBOX, CB_SETCURSEL, position, 0);
					}
					else MessageBox(hDlg, "ima veche takyv string", "info", MB_OK);
				}
			}
			else if (LOWORD(wParam) == IDCANCEL) {
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			else if (LOWORD(wParam) == IDC_INSERT) {
				int position = SendDlgItemMessage(hDlg, IDC_COMBOBOX, CB_GETCURSEL, 0, 0);
				if (position != -1) {
					char text[80];
					SendDlgItemMessage(hDlg, IDC_COMBOBOX, CB_GETLBTEXT, position, (LPARAM)text);
					SetDlgItemText(hDlg, IDC_EDITCOMBO, text);
				}
				position = SendDlgItemMessage(hDlg, IDC_LISTBOX, LB_GETCURSEL, 0, 0);
				if (position != -1) {
					char text[80];
					SendDlgItemMessage(hDlg, IDC_LISTBOX, LB_GETTEXT, position, (LPARAM)text);
					SetDlgItemText(hDlg, IDC_EDITLIST, text);
				}
			}
	}
	return FALSE;
}