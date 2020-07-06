#pragma once

void AddControls(HWND hwnd);//prototyp
void AddListboxs(HWND hwnd);
void AddText(HWND hwnd);


#define button_id_open_mess 1 
#define button_id_visu 2

#define list_soll_id 101

HWND hwnd = nullptr;
//HWND 
HWND text_edit = nullptr;

HWND button_open_mess = nullptr;
HWND button_visu = nullptr;

HWND list_soll = nullptr;

void AddControls(HWND hwnd) {
	int size_x=97;
	int size_y=48;
	button_open_mess = CreateWindow("BUTTON", "Open", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 0, 250, size_x, size_y, hwnd, (HMENU)button_id_open_mess, NULL, NULL);
	button_visu = CreateWindow("BUTTON", "View", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 100, 250, size_x, size_y, hwnd, (HMENU)button_id_visu, NULL, NULL);

	//-----------------------Texte----------------------------------------------------------------------------------



}

void AddListboxs(HWND hwnd) {
	int size_x = 250;
	int size_y = 200;
	list_soll = CreateWindowEx(WS_EX_CLIENTEDGE, "listbox", "", WS_VSCROLL | WS_VISIBLE | WS_CHILD, 0, 0, size_x, size_y, hwnd, (HMENU)list_soll_id, 0, 0);
	SendMessage(list_soll, LB_ADDSTRING, 0, (LPARAM)"Jokari.txt");
	SendMessage(list_soll, LB_ADDSTRING, 0, (LPARAM)"Jokaris.txt");
	SendMessage(list_soll, LB_ADDSTRING, 0, (LPARAM)"Jokarid.txt");
}
void AddText(HWND hwnd) {
	text_edit = CreateWindow("Static", "", WS_VISIBLE | WS_CHILD | ES_LEFT, 100, 600, 800, 200, hwnd, 0, 0, 0);
}