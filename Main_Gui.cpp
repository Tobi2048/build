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

HWND hwnd1;
HWND hwnd2;

//----------------------Fenstergröße------------------------------------------------------------------
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
	static int z = 0;
	static int z1 = 0;
	switch (uMsg) {
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case button_id_open_mess:
			if (SendMessage(list_mess, LB_GETSEL, 0 , 0) > 0) {
				
				str.insert(0, Verteiler('c',"Jokari"));
				SetWindowText(mess_text, "Die Datei:\n ""Jokari""\nist ausgewählt");
				lpcstr = str.c_str();
				SetWindowText(text_edit, lpcstr);
				break;
			}
			else {
				SetWindowText(mess_text, "Bitte erst eine Datei \n auswählen");
				break;
			}
		case button_id_open_soll:
			if (SendMessage(list_soll, LB_GETSEL, 0, 0) > 0) {
				str.insert(0, Verteiler('s', "Soll_A_gut"));
				SetWindowText(soll_text, "Die Datei:\n ""Soll_A_gut"" \n ist  ausgewählt");
			}
			else if (SendMessage(list_soll, LB_GETSEL, 1, 0) > 0) {
				str.insert(0, Verteiler('s', "Soll_A_kurz"));
				SetWindowText(soll_text, "Die Datei:\n ""Soll_A_kurz"" \nist  ausgewählt");
			}
			else if (SendMessage(list_soll, LB_GETSEL, 2, 0) > 0) {
				str.insert(0, Verteiler('s', "Soll_A_lang"));
				SetWindowText(soll_text, "Die Datei:\n ""Soll_A_lang""\n ist ausgewählt");
			}
			else if (SendMessage(list_soll, LB_GETSEL, 3, 0) > 0) {
				str.insert(0, Verteiler('s', "Soll_B_gut"));
				SetWindowText(soll_text, "Die Datei:\n ""Soll_B_gut"" \nist ausgewählt");
			}
			else if (SendMessage(list_soll, LB_GETSEL, 4, 0) > 0) {
				str.insert(0, Verteiler('s', "Soll_B_kurz"));
				SetWindowText(soll_text, "Die Datei:\n ""Soll_B_kurz""\n ist ausgewählt");
			}
			else if (SendMessage(list_soll, LB_GETSEL, 5, 0) > 0) {
				str.insert(0, Verteiler('s', "Soll_B_lang"));
				SetWindowText(soll_text, "Die Datei:\n ""Soll_B_lang""\n ist ausgewählt");
			}
			else if (SendMessage(list_soll, LB_GETSEL, 6, 0) > 0) {
				str.insert(0, Verteiler('s', "Soll_C_gut"));
				SetWindowText(soll_text, "Die Datei:\n ""Soll_C_gut"" \nist ausgewählt");
			}
			else if (SendMessage(list_soll, LB_GETSEL, 7, 0) > 0) {
				str.insert(0, Verteiler('s', "Soll_C_kurz"));
				SetWindowText(soll_text, "Die Datei:\n ""Soll_C_kurz"" \nist ausgewählt");
			}
			else if (SendMessage(list_soll, LB_GETSEL, 8, 0) > 0) {
				str.insert(0, Verteiler('s', "Soll_C_lang"));
				SetWindowText(soll_text, "Die Datei:\n ""Soll_C_lang""\n ist ausgewählt");
			}
			else {
				SetWindowText(soll_text, "Bitte erst eine Datei \n auswählen");
			}

			lpcstr = str.c_str();
			SetWindowText(text_edit, lpcstr);
			break;
		case button_id_visu:
			hwnd1 = FindWindow(NULL, "Anzeige des Soll-Steins");
				if (hwnd1) 
					DestroyWindow(hwnd1);
				str.insert(0, Verteiler('v'));
				lpcstr = str.c_str();
				SetWindowText(text_edit, lpcstr);
				
			
			
				MessageBox(hwnd,"hallo","hallo",MB_OK);
				
				
				
			
			break;
		case button_id_visu_2:
			hwnd2 = FindWindow(NULL, "Anzeige des Mess-Steins");
			if (hwnd2)
				DestroyWindow(hwnd2);

				str.insert(0, Verteiler('V'));
				lpcstr = str.c_str();
				SetWindowText(text_edit, lpcstr);
				
			
			
				
				
				
			
			break;
		
		}
		break;

	case WM_CLOSE: // kreuz befehl
		PostQuitMessage(0);
		hwnd1 = FindWindow(NULL, "Anzeige des Soll-Steins");
		 if (hwnd1) {
			 DestroyWindow(hwnd1);
		 }
		 hwnd2 = FindWindow(NULL,"Anzeige des Mess-Steins");
		 if (hwnd2)
			 DestroyWindow(hwnd2);
		
		break;
	case WM_CREATE://Tastatureingabe
		AddControls(hwnd);
		AddListboxs(hwnd);
		AddText(hwnd);
		hhAnzeige = CreateWindow(szAnzeige,szAnzeige,WS_OVERLAPPEDWINDOW|WS_VISIBLE,1,1,1940,1000,0,NULL,((LPCREATESTRUCT)lParam)->hInstance,NULL);
		
		
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		DestroyWindow(hhAnzeige);
		hwnd1 = FindWindow(NULL, "Anzeige des Soll-Steins");
		 if (hwnd1) {
			 MessageBox(hwnd, "Programm konnte nicht gefunden werden!", "Error!", MB_OK);
			 DestroyWindow(hwnd1);
		 }
		 hwnd2 = FindWindow(NULL,"Anzeige des Mess-Steins");
		 if (hwnd2)
			 DestroyWindow(hwnd2);
		
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
		955, 0, 980, 1005, NULL, NULL, hInstance, NULL);
	
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



