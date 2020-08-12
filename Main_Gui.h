#pragma once
#ifdef _DEBUG
#define DEBUG
#endif

#ifndef DEBUG
void AddControls(HWND hwnd);//prototyp
void AddListboxs(HWND hwnd);
void AddText(HWND hwnd);


#define button_id_open_soll 6
#define button_id_open_mess 1 
#define button_id_visu 2
#define button_id_visu_2 3
#define button_filter_stein_id 4
#define button_auswerten_id 5
#define button_id_ausreiﬂer 7

#define list_soll_id 101
#define list_mess_id 102


HWND hwnd = nullptr;
//HWND 
HWND text_edit = nullptr;
HWND soll_text = nullptr;
HWND mess_text = nullptr;
HWND soll_h = nullptr;
HWND soll_b = nullptr;
HWND soll_l = nullptr;
HWND mess_h = nullptr;
HWND mess_b = nullptr;
HWND mess_l = nullptr;
HWND ab_h = nullptr;
HWND ab_b = nullptr;
HWND ab_l = nullptr;
HWND gut_l = nullptr;
HWND mang_l = nullptr;
HWND def_l = nullptr;
HWND gut_b = nullptr;
HWND mang_b = nullptr;
HWND def_b = nullptr;
HWND gut_h = nullptr;
HWND mang_h = nullptr;
HWND def_h = nullptr;

HWND gut_pr = nullptr;
HWND aufl = nullptr;

HWND button_open_soll = nullptr;
HWND button_open_mess = nullptr;
HWND button_visu = nullptr;
HWND button_visu_2 = nullptr;
HWND button_filter_stein = nullptr;
HWND button_auswerten = nullptr;
HWND button_ausreiﬂer = nullptr;

HWND list_soll = nullptr;
HWND list_mess = nullptr;

void AddControls(HWND hwnd) {
	int size_x=149;
	int size_y=59;
	button_open_soll = CreateWindow("BUTTON", "Best‰tigen ", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 276, 30, 199, size_y, hwnd, (HMENU)button_id_open_soll, NULL, NULL);
	button_open_mess = CreateWindow("BUTTON", "Best‰tigen", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 725, 30, 199, size_y, hwnd, (HMENU)button_id_open_mess, NULL, NULL);
	button_visu = CreateWindow("BUTTON", "Anzeigen", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 28+2*size_x, 210, size_x, size_y, hwnd, (HMENU)button_id_visu, NULL, NULL);
	button_visu_2 = CreateWindow("BUTTON", "Anzeigen", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 475, 210, size_x, size_y, hwnd, (HMENU)button_id_visu_2, NULL, NULL);
	button_filter_stein= CreateWindow("BUTTON", "Stein filtern", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 475 + 2 * size_x, 210, size_x, size_y, hwnd, (HMENU)button_filter_stein_id, NULL, NULL);
	button_auswerten= CreateWindow("BUTTON", "Auswerten", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 475, 210 + size_y, size_x, size_y, hwnd, (HMENU)button_auswerten_id, NULL, NULL);
	button_ausreiﬂer= CreateWindow("BUTTON", "Ausreiﬂer entfernen", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 475 + size_x, 210, size_x, size_y , hwnd, (HMENU)button_id_ausreiﬂer, NULL, NULL);
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

	SendMessage(list_mess, LB_ADDSTRING, 0, (LPARAM)"1_A_gut");
	SendMessage(list_mess, LB_ADDSTRING, 0, (LPARAM)"2_A_schlecht");
	SendMessage(list_mess, LB_ADDSTRING, 0, (LPARAM)"3_A_schlecht");
	SendMessage(list_mess, LB_ADDSTRING, 0, (LPARAM)"4_A_gut");
	SendMessage(list_mess, LB_ADDSTRING, 0, (LPARAM)"5_A_schlecht_form");
	SendMessage(list_mess, LB_ADDSTRING, 0, (LPARAM)"6_B_gut");
	SendMessage(list_mess, LB_ADDSTRING, 0, (LPARAM)"7_B_gut_l");
	SendMessage(list_mess, LB_ADDSTRING, 0, (LPARAM)"8_C_gut");
	SendMessage(list_mess, LB_ADDSTRING, 0, (LPARAM)"9_C_schlecht");
	SendMessage(list_mess, LB_ADDSTRING, 0, (LPARAM)"10_B_schlecht");


}
void AddText(HWND hwnd) {
	int tabx = 120;  
	int taby = 44;
	text_edit = CreateWindow("Static", "", WS_VISIBLE | WS_CHILD | ES_LEFT, 25, 750, 900, 200, hwnd, 0, 0, 0);
	CreateWindow("Static", "Soll-Stein Daten", WS_VISIBLE | WS_CHILD | ES_CENTER, 25, 0, 450, 29, hwnd, 0, 0, 0);
	CreateWindow("Static", "Mess-Stein Daten", WS_VISIBLE | WS_CHILD | ES_CENTER, 476, 0, 450, 29, hwnd, 0, 0, 0);

	CreateWindow("Static", " Eingabe der tollerierten Abweichung in Prozent \nWertebereich (1-20) ", WS_VISIBLE | WS_CHILD | ES_CENTER, 25, 210, 200, 59, hwnd, 0, 0, 0);
	gut_pr=CreateWindow("Edit", " 5 ", WS_VISIBLE | WS_CHILD | ES_CENTER | WS_BORDER, 225, 210, 99, 59, hwnd, 0, 0, 0);

	CreateWindow("Static", " Eingabe der geforderten Auflˆsung \n Wertebereich (0-1) ", WS_VISIBLE | WS_CHILD | ES_CENTER, 25, 270, 200, 59, hwnd, 0, 0, 0);
	aufl= CreateWindow("Edit", "0.4", WS_VISIBLE | WS_CHILD | ES_CENTER | WS_BORDER, 225, 270, 99, 59, hwnd, 0, 0, 0);

	int x_start =50;

	int tab_start_y = 480;
	CreateWindow("Static", "Sollwerte\n [mm]", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start +tabx, tab_start_y, tabx-1, taby-1, hwnd, 0, 0, 0);
	CreateWindow("Static", "L‰nge", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start, tab_start_y+taby, tabx-1, taby-1, hwnd, 0, 0, 0);
	CreateWindow("Static", "Breite", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start, tab_start_y + taby*2, tabx-1, taby-1, hwnd, 0, 0, 0);
	CreateWindow("Static", "Hˆhe", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start, tab_start_y + taby*3, tabx-1, taby-1, hwnd, 0, 0, 0);

	soll_h = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + tabx, tab_start_y + taby*3, tabx-1, taby-1, hwnd, 0, 0, 0);
	soll_b = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + tabx, tab_start_y + taby*2, tabx-1, taby-1, hwnd, 0, 0, 0);
	soll_l = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + tabx, tab_start_y + taby, tabx-1, taby-1, hwnd, 0, 0, 0);
	CreateWindow("Static", "Messwerte\n [mm]", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + tabx * 2, tab_start_y, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	mess_h = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + tabx*2, tab_start_y + taby * 3, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	mess_b = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + tabx*2, tab_start_y + taby * 2, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	mess_l = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + tabx*2, tab_start_y + taby, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	CreateWindow("Static", "Standardabw.\n [mm]", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + tabx * 3, tab_start_y, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	ab_h = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + tabx * 3, tab_start_y + taby * 3, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	ab_b = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + tabx * 3, tab_start_y + taby * 2, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	ab_l = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + tabx * 3, tab_start_y + taby, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	CreateWindow("Static", "Gut \n [%]", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + 15 + tabx * 4, tab_start_y, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	gut_l = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start+ 15 + tabx * 4, tab_start_y + taby , tabx - 1, taby - 1, hwnd, 0, 0, 0);
	gut_b = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start +15 + tabx * 4, tab_start_y + taby*2, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	gut_h= CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + 15 + tabx * 4, tab_start_y + taby * 3, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	CreateWindow("Static", "Mangel \n [%]", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + 15 + tabx * 5, tab_start_y, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	mang_l = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + 15 + tabx * 5, tab_start_y + taby , tabx - 1, taby - 1, hwnd, 0, 0, 0);
	mang_b = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + 15 + tabx * 5, tab_start_y + taby*2, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	mang_h= CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + 15 + tabx * 5, tab_start_y + taby * 3, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	CreateWindow("Static", "Defect \n [%]", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start +15 + tabx * 6, tab_start_y, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	def_l = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + 15 + tabx * 6, tab_start_y + taby , tabx - 1, taby - 1, hwnd, 0, 0, 0);
	def_b = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + 15 + tabx * 6, tab_start_y + taby*2, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	def_h= CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + 15 + tabx * 6, tab_start_y + taby * 3, tabx - 1, taby - 1, hwnd, 0, 0, 0);


	soll_text=CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, 276, 90, 198, 120, hwnd, 0, 0, 0);
	mess_text=CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, 726, 90, 198, 120, hwnd, 0, 0, 0);
}
#endif