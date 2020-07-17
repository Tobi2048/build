#include <windows.h>
#include<stdlib.h>
#include <cassert>

#include"Main_Gui.h"
#include"Master_prog.h"


const char szAnzeige[] = "Bild Anzeige";
//_______________________Fenster button ..  declarieren__________________________________
std::string datn = {};
std::string str = {};
std::string str2 = {};
std::vector<std::string> vec(20);
LPCSTR lpcstr = str.c_str();
LPCSTR lpcstr2 = str2.c_str();
std::string dat;

HWND hwnd1;
HWND hwnd2;
HWND hwnd3; HWND hwnd4;
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
				datn = "Jokari";
				
			}
			else {
				SetWindowText(mess_text, "Bitte erst eine Datei \n auswählen");
				break;
			}
			vec = Verteiler('c', datn);
			str2 = ("Die Datei :\n\n" + datn + " \n\n ist ausgewählt");
			lpcstr2 = str2.c_str();
			SetWindowText(mess_text, lpcstr2); str2 = {};
			str.insert(0, vec[0]);
			lpcstr = str.c_str();
			SetWindowText(text_edit, lpcstr);
			break;


		case button_id_open_soll:
			if (SendMessage(list_soll, LB_GETSEL, 0, 0) > 0) {
				datn = "Soll_A_gut";
				
			}
			else if (SendMessage(list_soll, LB_GETSEL, 1, 0) > 0) {
				datn = "Soll_A_kurz";
			}
			else if (SendMessage(list_soll, LB_GETSEL, 2, 0) > 0) {
				datn = "Soll_A_lang";
			}
			else if (SendMessage(list_soll, LB_GETSEL, 3, 0) > 0) {
				datn = "Soll_B_gut";
			}
			else if (SendMessage(list_soll, LB_GETSEL, 4, 0) > 0) {
				datn = "Soll_B_kurz";
			}
			else if (SendMessage(list_soll, LB_GETSEL, 5, 0) > 0) {
				datn = "Soll_B_lang";
			}
			else if (SendMessage(list_soll, LB_GETSEL, 6, 0) > 0) {
				datn = "Soll_C_gut";
			}
			else if (SendMessage(list_soll, LB_GETSEL, 7, 0) > 0) {
				datn = "Soll_C_kurz";
			}
			else if (SendMessage(list_soll, LB_GETSEL, 8, 0) > 0) {
				datn = "Soll_C_lang";
			}
			else {
				SetWindowText(soll_text, "Bitte erst eine Datei \n auswählen");
				break;
			}
			vec = Verteiler('s', datn);
			str2 = ("Die Datei :\n\n" + datn + " \n\n ist ausgewählt");
			lpcstr2 = str2.c_str();
			SetWindowText(soll_text, lpcstr2); str2 = {};
			str.insert(0, vec[0]);
			lpcstr = str.c_str();
			SetWindowText(text_edit, lpcstr); 
			str2.insert(0, vec[1]);
			lpcstr2 = str2.c_str();
			SetWindowText(soll_l, lpcstr2); str2 = {};
			str2.insert(0, vec[2]);
			lpcstr2 = str2.c_str();
			SetWindowText(soll_b, lpcstr2); str2 = {};
			str2.insert(0, vec[3]);
			lpcstr2 = str2.c_str();
			SetWindowText(soll_h, lpcstr2); str2 = {};
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
			hwnd3 = FindWindow(NULL, "Anzeige Auswertung Breite des Steins");
			if (hwnd3) {
				SetForegroundWindow(hwnd3);
				//keybd_event((BYTE)VkKeyScan('q'), 0, 0, 0);
				DestroyWindow(hwnd3);
			}
			hwnd4 = FindWindow(NULL, "Anzeige Auswertung Länge des Steins");
			if (hwnd4) {
				SetForegroundWindow(hwnd4);
				//keybd_event((BYTE)VkKeyScan('q'), 0, 0, 0);
				DestroyWindow(hwnd4);
			}
			vec = Verteiler('a');
			str.insert(0, vec[0]);
			lpcstr = str.c_str();
			SetWindowText(text_edit, lpcstr);
			str2.insert(0, vec[4]);
			lpcstr2 = str2.c_str();
			SetWindowText(mess_l, lpcstr2); str2 = {};
			str2.insert(0, vec[5]);
			lpcstr2 = str2.c_str();
			SetWindowText(mess_b, lpcstr2); str2 = {};
			/*str.insert(0, vec[6]);
			lpcstr = str.c_str();
			SetWindowText(soll_h, lpcstr); str = {};*/
			str2.insert(0, vec[7]);
			lpcstr2 = str2.c_str();
			SetWindowText(ab_l, lpcstr2); str2 = {}; 
			str2.insert(0, vec[8]);
			lpcstr2 = str2.c_str();
			SetWindowText(ab_b, lpcstr2); str2 = {};
			str2.insert(0, vec[9]);
			lpcstr2 = str2.c_str();
			SetWindowText(ab_h, lpcstr2); str2 = {};

			str2.insert(0, vec[10]);
			lpcstr2 = str2.c_str();
			SetWindowText(gut_l, lpcstr2); str2 = {};
			str2.insert(0, vec[11]);
			lpcstr2 = str2.c_str();
			SetWindowText(mang_l, lpcstr2); str2 = {};
			str2.insert(0, vec[12]);
			lpcstr2 = str2.c_str();
			SetWindowText(def_l, lpcstr2); str2 = {};

			str2.insert(0, vec[13]);
			lpcstr2 = str2.c_str();
			SetWindowText(gut_b, lpcstr2); str2 = {};
			str2.insert(0, vec[14]);
			lpcstr2 = str2.c_str();
			SetWindowText(mang_b, lpcstr2); str2 = {};
			str2.insert(0, vec[15]);
			lpcstr2 = str2.c_str();
			SetWindowText(def_b, lpcstr2); str2 = {};
			
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
		hwnd4 = FindWindow(NULL, "Anzeige Auswertung Länge des Steins");
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
		  hwnd4 = FindWindow(NULL, "Anzeige Auswertung Länge des Steins");
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
		"WindowClass", "Passstein Qualitätskontrolle", WS_VISIBLE | WS_OVERLAPPEDWINDOW,
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



