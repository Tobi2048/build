#pragma once

void AddControls(HWND hwnd);//prototyp
void AddListboxs(HWND hwnd);
void AddText(HWND hwnd);


#define button_id_open_soll 0
#define button_id_open_mess 1 
#define button_id_visu 2
#define button_id_visu_2 3
#define button_filter_stein_id 4
#define button_auswerten_id 5

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
HWND button_visu_2 = nullptr;
HWND button_filter_stein = nullptr;
HWND button_auswerten = nullptr;
HWND list_soll = nullptr;
HWND list_mess = nullptr;

void AddControls(HWND hwnd) {
	int size_x=149;
	int size_y=69;
	button_open_soll = CreateWindow("BUTTON", "Bestätigen ", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 276, 30, 199, size_y, hwnd, (HMENU)button_id_open_soll, NULL, NULL);
	button_open_mess = CreateWindow("BUTTON", "Bestätigen", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 725, 30, 199, size_y, hwnd, (HMENU)button_id_open_mess, NULL, NULL);
	button_visu = CreateWindow("BUTTON", "Anzeigen", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 25, 210, size_x, size_y, hwnd, (HMENU)button_id_visu, NULL, NULL);
	button_visu_2 = CreateWindow("BUTTON", "Anzeigen", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 475, 210, size_x, size_y, hwnd, (HMENU)button_id_visu_2, NULL, NULL);
	button_filter_stein= CreateWindow("BUTTON", "Stein filtern", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 475+size_x, 210, size_x, size_y, hwnd, (HMENU)button_filter_stein_id, NULL, NULL);
	button_auswerten= CreateWindow("BUTTON", "Auswerten", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 475 + 2*size_x, 210, size_x, size_y, hwnd, (HMENU)button_auswerten_id, NULL, NULL);
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
	int tabx = 100;  
	int taby = 35;
	text_edit = CreateWindow("Static", "", WS_VISIBLE | WS_CHILD | ES_LEFT, 25, 750, 900, 200, hwnd, 0, 0, 0);
	CreateWindow("Static", "Soll-Stein Daten", WS_VISIBLE | WS_CHILD | ES_CENTER, 25, 0, 450, 29, hwnd, 0, 0, 0);
	CreateWindow("Static", "Mess-Stein Daten", WS_VISIBLE | WS_CHILD | ES_CENTER, 476, 0, 450, 29, hwnd, 0, 0, 0);


	CreateWindow("Static", "Sollwerte", WS_VISIBLE | WS_CHILD | ES_CENTER, 25+tabx, 350, tabx, taby, hwnd, 0, 0, 0);
	CreateWindow("Static", "Länge", WS_VISIBLE | WS_CHILD | ES_CENTER, 25 , 350+taby, tabx, taby, hwnd, 0, 0, 0);
	CreateWindow("Static", "Breite", WS_VISIBLE | WS_CHILD | ES_CENTER, 25, 350 + taby*2, tabx, taby, hwnd, 0, 0, 0);
	CreateWindow("Static", "Höhe", WS_VISIBLE | WS_CHILD | ES_CENTER, 25, 350 + taby*3, tabx, taby, hwnd, 0, 0, 0);

	soll_text=CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, 276, 100, 198, 110, hwnd, 0, 0, 0);
	mess_text=CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, 726, 100, 198, 110, hwnd, 0, 0, 0);
}