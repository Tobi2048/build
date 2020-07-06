#include <windows.h>
#include<stdlib.h>
#include <cassert>

#include"Main_Gui.h"
#include"Master_prog.h"


const char szAnzeige[] = "Bild Anzeige";
//_______________________Fenster button ..  declarieren__________________________________

std::string str;
LPCSTR lpcstr = str.c_str();
std::string dat;




//----------------------Fenstergr��e------------------------------------------------------------------
LRESULT CALLBACK AnzeigeProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static RECT rect;
	SIZE size;
	HDC hDC;
	PAINTSTRUCT ps;
	switch (message)
	{
	case WM_SIZE:

		rect.right = LOWORD(lParam);
		rect.bottom = HIWORD(lParam);
		break;

	case WM_PAINT:

		break;

	case WM_CLOSE:
		// kreuz befehl
		PostQuitMessage(0);
		break;
	default:
		break;
	}
		return DefWindowProc(hWnd, message, wParam, lParam);
	
}


LRESULT CALLBACK MessageHandler(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	static HWND hhAnzeige;
	static HWND uhhAnzeige;
	switch (uMsg) {
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case button_id_open_mess:
			if (SendMessage(list_soll, LB_GETSEL, 0 , 0) > 0) {
				
				str.insert(0, Verteiler('c',"Jokari"));
				lpcstr = str.c_str();
				SetWindowText(text_edit, lpcstr);
				break;
			}
			else {
				MessageBox(hwnd, "", "doof", MB_OK);
				break;
			}
		case button_id_visu:
			str.insert(0, Verteiler('v'));
			lpcstr = str.c_str();
			SetWindowText(text_edit, lpcstr);
			break;
		
		}
		break;

	case WM_CLOSE: // kreuz befehl
		PostQuitMessage(0);
		
		break;
	case WM_CREATE://Tastatureingabe
		AddControls(hwnd);
		AddListboxs(hwnd);
		AddText(hwnd);
		hhAnzeige = CreateWindow(szAnzeige,
			szAnzeige,
			WS_OVERLAPPEDWINDOW|WS_VISIBLE,
			1,
			1,
			1940,
			1000,
			0,
			NULL,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL);
		
		
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(WNDCLASS));
	
	wc.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = MessageHandler;//auf events reagieren
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszClassName = "WindowClass";
	RegisterClass(&wc);

	wc.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hIcon = NULL;
	wc.lpfnWndProc = AnzeigeProc;
	wc.lpszClassName = szAnzeige;

	

	RegisterClass(&wc);
	//--------------------------Hauptfenster-----------------------------------
	hwnd = CreateWindow(
		"WindowClass", "Erste Fenster", WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		965, 0, 960, 1000, NULL, NULL, hInstance, NULL);
	
	if (hwnd == nullptr) {
		DWORD errVal = GetLastError();
	}
	//-----------------------------------------------------------------------------------------------------------

	//----------------------Buttons----------------------------------------------------------------------




	MSG msg;
	bool running = true;
	while (running) {
		while (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				running = false;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//render frame update frame

	}
}



