#pragma once

void AddControls(HWND hwnd);//prototyp
void AddListboxs(HWND hwnd);
void AddText(HWND hwnd);


#define button_id_open_soll 10 
#define button_id_open_mess 11 
#define button_id_visu 2

#define list_soll_id 101
#define list_mess_id 102

HWND hwnd = nullptr;
//HWND 
HWND text_edit = nullptr;
HWND soll_text = nullptr;
HWND mess_text = nullptr;
HWND button_open_soll = nullptr;
HWND button_open_mess = nullptr;
HWND button_visu = nullptr;

HWND list_soll = nullptr;
HWND list_mess = nullptr;

void AddControls(HWND hwnd) {
	int size_x=99;
	int size_y=49;
	button_open_soll = CreateWindow("BUTTON", "Open", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 276, 30, size_x*2, size_y, hwnd, (HMENU)button_id_open_soll, NULL, NULL);
	button_open_mess = CreateWindow("BUTTON", "Open", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 725, 30, size_x*2, size_y, hwnd, (HMENU)button_id_open_mess, NULL, NULL);
	button_visu = CreateWindow("BUTTON", "View", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 100, 250, size_x, size_y, hwnd, (HMENU)button_id_visu, NULL, NULL);

	//-----------------------Texte----------------------------------------------------------------------------------



}

void AddListboxs(HWND hwnd) {
	int size_x = 250;
	int size_y = 180;
	list_soll = CreateWindowEx(WS_EX_CLIENTEDGE, "listbox", "", WS_VSCROLL | WS_VISIBLE | WS_CHILD, 25, 30, size_x, size_y, hwnd, (HMENU)list_soll_id, 0, 0);
	SendMessage(list_soll, LB_ADDSTRING, 0, (LPARAM)"Soll_A_gut");
	SendMessage(list_soll, LB_ADDSTRING, 0, (LPARAM)"Soll_A_kurz");
	SendMessage(list_soll, LB_ADDSTRING, 0, (LPARAM)"Soll_A_lang");
	SendMessage(list_soll, LB_ADDSTRING, 0, (LPARAM)"Soll_B_gut");
	SendMessage(list_soll, LB_ADDSTRING, 0, (LPARAM)"Soll_B_kurz");
	SendMessage(list_soll, LB_ADDSTRING, 0, (LPARAM)"Soll_B_lang");
	SendMessage(list_soll, LB_ADDSTRING, 0, (LPARAM)"Soll_C_gut");
	SendMessage(list_soll, LB_ADDSTRING, 0, (LPARAM)"Soll_C_kurz");
	SendMessage(list_soll, LB_ADDSTRING, 0, (LPARAM)"Soll_C_lang");

	list_mess = CreateWindowEx(WS_EX_CLIENTEDGE, "listbox", "", WS_VSCROLL | WS_VISIBLE | WS_CHILD, 475, 30, size_x, size_y, hwnd, (HMENU)list_mess_id, 0, 0);
	SendMessage(list_mess, LB_ADDSTRING, 0, (LPARAM)"Jokari.txt");
	SendMessage(list_mess, LB_ADDSTRING, 0, (LPARAM)"Jokaris.txt");
	SendMessage(list_mess, LB_ADDSTRING, 0, (LPARAM)"Jokarid.txt");
}
void AddText(HWND hwnd) {
	text_edit = CreateWindow("Static", "", WS_VISIBLE | WS_CHILD | ES_LEFT, 100, 600, 800, 200, hwnd, 0, 0, 0);
	CreateWindow("Static", "Soll-Stein Daten", WS_VISIBLE | WS_CHILD | ES_CENTER, 0, 0, 473, 29, hwnd, 0, 0, 0);
	CreateWindow("Static", "Mess-Stein Daten", WS_VISIBLE | WS_CHILD | ES_CENTER, 476, 0, 473, 29, hwnd, 0, 0, 0);

	soll_text=CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, 276, 100, 198, 110, hwnd, 0, 0, 0);
	mess_text=CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, 726, 100, 198, 110, hwnd, 0, 0, 0);
}