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
HWND hwnd3; HWND hwnd4;
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
		hwnd1 = FindWindow(NULL, "Anzeige des Soll-Steins");
		if (hwnd1) {
			SetForegroundWindow(hwnd1);
			keybd_event((BYTE)VkKeyScan('q'), 0, 0, 0);
			DestroyWindow(hwnd1);
		}
		hwnd2 = FindWindow(NULL, "Anzeige des Mess-Steins");
		if (hwnd2) {
			SetForegroundWindow(hwnd2);
			keybd_event((BYTE)VkKeyScan('q'), 0, 0, 0);
			DestroyWindow(hwnd2);
			hwnd3 = FindWindow(NULL, "Anzeige Auswertung breite des Steins");
		}
		if (hwnd3) {
			SetForegroundWindow(hwnd3);
			keybd_event((BYTE)VkKeyScan('q'), 0, 0, 0);
			DestroyWindow(hwnd3);
		}
		hwnd4 = FindWindow(NULL, "Anzeige Auswertung laenge des Steins");
		if (hwnd4) {
			SetForegroundWindow(hwnd4);
			keybd_event((BYTE)VkKeyScan('q'), 0, 0, 0);
			DestroyWindow(hwnd4);
		}
		
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
			if (SendMessage(list_mess, LB_GETSEL, 0, 0) > 0) {

				str.insert(0, Verteiler('c', "Jokari")[0]);
				SetWindowText(mess_text, "Die Datei:\n ""Jokari""\nist ausgew�hlt");
				lpcstr = str.c_str();
				SetWindowText(text_edit, lpcstr);
				break;
			}
			else {
				SetWindowText(mess_text, "Bitte erst eine Datei \n ausw�hlen");
				break;
			}
		case button_id_open_soll:
			if (SendMessage(list_soll, LB_GETSEL, 0, 0) > 0) {
				str.insert(0, Verteiler('s', "Soll_A_gut")[0]);
				SetWindowText(soll_text, "Die Datei:\n ""Soll_A_gut"" \n ist  ausgew�hlt");
			}
			else if (SendMessage(list_soll, LB_GETSEL, 1, 0) > 0) {
				str.insert(0, Verteiler('s', "Soll_A_kurz")[0]);
				SetWindowText(soll_text, "Die Datei:\n ""Soll_A_kurz"" \nist  ausgew�hlt");
			}
			else if (SendMessage(list_soll, LB_GETSEL, 2, 0) > 0) {
				str.insert(0, Verteiler('s', "Soll_A_lang")[0]);
				SetWindowText(soll_text, "Die Datei:\n ""Soll_A_lang""\n ist ausgew�hlt");
			}
			else if (SendMessage(list_soll, LB_GETSEL, 3, 0) > 0) {
				str.insert(0, Verteiler('s', "Soll_B_gut")[0]);
				SetWindowText(soll_text, "Die Datei:\n ""Soll_B_gut"" \nist ausgew�hlt");
			}
			else if (SendMessage(list_soll, LB_GETSEL, 4, 0) > 0) {
				str.insert(0, Verteiler('s', "Soll_B_kurz")[0]);
				SetWindowText(soll_text, "Die Datei:\n ""Soll_B_kurz""\n ist ausgew�hlt");
			}
			else if (SendMessage(list_soll, LB_GETSEL, 5, 0) > 0) {
				str.insert(0, Verteiler('s', "Soll_B_lang")[0]);
				SetWindowText(soll_text, "Die Datei:\n ""Soll_B_lang""\n ist ausgew�hlt");
			}
			else if (SendMessage(list_soll, LB_GETSEL, 6, 0) > 0) {
				str.insert(0, Verteiler('s', "Soll_C_gut")[0]);
				SetWindowText(soll_text, "Die Datei:\n ""Soll_C_gut"" \nist ausgew�hlt");
			}
			else if (SendMessage(list_soll, LB_GETSEL, 7, 0) > 0) {
				str.insert(0, Verteiler('s', "Soll_C_kurz")[0]);
				SetWindowText(soll_text, "Die Datei:\n ""Soll_C_kurz"" \nist ausgew�hlt");
			}
			else if (SendMessage(list_soll, LB_GETSEL, 8, 0) > 0) {
				str.insert(0, Verteiler('s', "Soll_C_lang")[0]);
				SetWindowText(soll_text, "Die Datei:\n ""Soll_C_lang""\n ist ausgew�hlt");
			}
			else {
				SetWindowText(soll_text, "Bitte erst eine Datei \n ausw�hlen");
			}

			lpcstr = str.c_str();
			SetWindowText(text_edit, lpcstr);
			break;
		case button_id_visu:
			hwnd1 = FindWindow(NULL, "Anzeige des Soll-Steins");
				if (hwnd1) 
				SetForegroundWindow(hwnd1);
				keybd_event((BYTE)VkKeyScan('q'), 0, 0, 0);
					DestroyWindow(hwnd1);
				str.insert(0, Verteiler('v')[0]);
				lpcstr = str.c_str();
				SetWindowText(text_edit, lpcstr);
			break;
		case button_id_visu_2:
			hwnd2 = FindWindow(NULL, "Anzeige des Mess-Steins");
			if (hwnd2)
				SetForegroundWindow(hwnd2);
				keybd_event((BYTE)VkKeyScan('q'), 0, 0, 0);
				DestroyWindow(hwnd2);
				str.insert(0, Verteiler('V')[0]);
				lpcstr = str.c_str();
				SetWindowText(text_edit, lpcstr);
			break;
		case button_filter_stein_id:
			str.insert(0, Verteiler('o')[0]);
			lpcstr = str.c_str();
			SetWindowText(text_edit, lpcstr);
			break;
		case button_auswerten_id:
			hwnd3 = FindWindow(NULL, "Anzeige Auswertung breite des Steins");
			if (hwnd3) {
				SetForegroundWindow(hwnd3);
				keybd_event((BYTE)VkKeyScan('q'), 0, 0, 0);
				DestroyWindow(hwnd3);
			}
			hwnd4 = FindWindow(NULL, "Anzeige Auswertung laenge des Steins");
			if (hwnd4) {
				SetForegroundWindow(hwnd4);
				keybd_event((BYTE)VkKeyScan('q'), 0, 0, 0);
				DestroyWindow(hwnd4);
			}
			str.insert(0, Verteiler('a')[0]);
			lpcstr = str.c_str();
			SetWindowText(text_edit, lpcstr);
			break;
		}
		break;

	case WM_CLOSE: // kreuz befehl
		
		hwnd1 = FindWindow(NULL, "Anzeige des Soll-Steins");
		 if (hwnd1) {
			 SetForegroundWindow(hwnd1);
			 keybd_event((BYTE)VkKeyScan('q'), 0, 0, 0);
			 DestroyWindow(hwnd1);
		 }
		 hwnd2 = FindWindow(NULL,"Anzeige des Mess-Steins");
		 if (hwnd2) {
			 SetForegroundWindow(hwnd2);
			 keybd_event((BYTE)VkKeyScan('q'), 0, 0, 0);
			 DestroyWindow(hwnd2);
			 hwnd3 = FindWindow(NULL, "Anzeige Auswertung Breite des Steins");
		 }
		 if (hwnd3) {
				 SetForegroundWindow(hwnd3);
				 keybd_event((BYTE)VkKeyScan('q'), 0, 0, 0);
				 DestroyWindow(hwnd3);
		 }
		hwnd4 = FindWindow(NULL, "Anzeige Auswertung L�nge des Steins");
		 if (hwnd4) {
				 SetForegroundWindow(hwnd4);
				 keybd_event((BYTE)VkKeyScan('q'), 0, 0, 0);
				 DestroyWindow(hwnd4);
		 }
		 DestroyWindow(hhAnzeige);
		 PostQuitMessage(0);
		
		break;
	case WM_CREATE://Tastatureingabe
		AddControls(hwnd);
		AddListboxs(hwnd);
		AddText(hwnd);
		hhAnzeige = CreateWindow(szAnzeige,szAnzeige,WS_OVERLAPPEDWINDOW|WS_VISIBLE,1,1,1940,1005,0,NULL,((LPCREATESTRUCT)lParam)->hInstance,NULL);
		
		
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		DestroyWindow(hhAnzeige);
		hwnd1 = FindWindow(NULL, "Anzeige des Soll-Steins");
		 if (hwnd1) {
			 SetForegroundWindow(hwnd1);
			 keybd_event((BYTE)VkKeyScan('q'), 0, 0, 0);
			 DestroyWindow(hwnd1);
		 }
		 hwnd2 = FindWindow(NULL,"Anzeige des Mess-Steins");
		 if (hwnd2) {
			 SetForegroundWindow(hwnd2);
			 keybd_event((BYTE)VkKeyScan('q'), 0, 0, 0);
			 DestroyWindow(hwnd2);
		 }
		  hwnd3 = FindWindow(NULL, "Anzeige Auswertung Breite des Steins");
		  if (hwnd3) {
			SetForegroundWindow(hwnd3);
			keybd_event((BYTE)VkKeyScan('q'), 0, 0, 0);
			DestroyWindow(hwnd3);
		  }
		  hwnd4 = FindWindow(NULL, "Anzeige Auswertung L�nge des Steins");
		  if (hwnd4) {
			SetForegroundWindow(hwnd4);
			keybd_event((BYTE)VkKeyScan('q'), 0, 0, 0);
			DestroyWindow(hwnd4);
		  }
		
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
		"WindowClass", "Passstein Qualit�tskontrolle", WS_VISIBLE | WS_OVERLAPPEDWINDOW,
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


