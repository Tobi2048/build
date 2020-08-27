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
#define button_id_ausreißer 7

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
HWND sab_h = nullptr;
HWND sab_l = nullptr;
HWND sab_b = nullptr;

HWND gutb_l = nullptr;
HWND gutb_b = nullptr;
HWND gutb_h = nullptr;
HWND aufl = nullptr;

HWND button_open_soll = nullptr;
HWND button_open_mess = nullptr;
HWND button_visu = nullptr;
HWND button_visu_2 = nullptr;
HWND button_filter_stein = nullptr;
HWND button_auswerten = nullptr;
HWND button_ausreißer = nullptr;

HWND list_soll = nullptr;
HWND list_mess = nullptr;

HWND auswertung = nullptr;

void AddControls(HWND hwnd) {
	int size_x=149;
	int size_y=59;
	button_open_soll = CreateWindow("BUTTON", "Bestätigen ", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 276, 30, 199, size_y, hwnd, (HMENU)button_id_open_soll, NULL, NULL);
	button_open_mess = CreateWindow("BUTTON", "Bestätigen", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 725, 30, 199, size_y, hwnd, (HMENU)button_id_open_mess, NULL, NULL);
	button_visu = CreateWindow("BUTTON", "Anzeigen", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 26, 210, size_x, size_y, hwnd, (HMENU)button_id_visu, NULL, NULL);
	button_visu_2 = CreateWindow("BUTTON", "Anzeigen", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 475, 210, size_x, size_y, hwnd, (HMENU)button_id_visu_2, NULL, NULL);
	button_filter_stein= CreateWindow("BUTTON", "Stein filtern", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 475 + 2 * size_x, 210, size_x, size_y, hwnd, (HMENU)button_filter_stein_id, NULL, NULL);
	button_auswerten= CreateWindow("BUTTON", "Auswerten", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 588, 265 + size_y, size_x, size_y, hwnd, (HMENU)button_auswerten_id, NULL, NULL);
	button_ausreißer= CreateWindow("BUTTON", "Ausreißer entfernen", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 475 + size_x, 210, size_x, size_y , hwnd, (HMENU)button_id_ausreißer, NULL, NULL);
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
	int tabx = 104;  
	int taby = 40;
	int tab_start_y = 380;
	text_edit = CreateWindow("Static", "", WS_VISIBLE | WS_CHILD | ES_LEFT, 25, 700, 900, 250, hwnd, 0, 0, 0);
	CreateWindow("Static", "Soll-Stein Daten", WS_VISIBLE | WS_CHILD | ES_CENTER, 25, 0, 450, 29, hwnd, 0, 0, 0);
	CreateWindow("Static", "Mess-Stein Daten", WS_VISIBLE | WS_CHILD | ES_CENTER, 476, 0, 450, 29, hwnd, 0, 0, 0);
	int x =336,y= 100;
	CreateWindow("Static", " Eingabe Gutbereich in [mm] ", WS_VISIBLE | WS_CHILD | ES_CENTER, x+25, y + 210, 215, 19, hwnd, 0, 0, 0);
	CreateWindow("Static", " Länge :", WS_VISIBLE | WS_CHILD | ES_CENTER, x + 25, y + 230, 90, 19, hwnd, 0, 0, 0);
	CreateWindow("Static", " Breite :", WS_VISIBLE | WS_CHILD | ES_CENTER, x + 25, y + 250, 90, 19, hwnd, 0, 0, 0);
	CreateWindow("Static", " Höhe :", WS_VISIBLE | WS_CHILD | ES_CENTER, x + 25, y + 270, 90, 19, hwnd, 0, 0, 0);
	gutb_l=CreateWindow("Edit", " 6 ", WS_VISIBLE | WS_CHILD | ES_CENTER | WS_BORDER, x +120, y + 230, 120, 20, hwnd, 0, 0, 0);
	gutb_b = CreateWindow("Edit", " 5 ", WS_VISIBLE | WS_CHILD | ES_CENTER | WS_BORDER, x +120, y + 250, 120, 20, hwnd, 0, 0, 0);
	gutb_h = CreateWindow("Edit", " 3 ", WS_VISIBLE | WS_CHILD | ES_CENTER | WS_BORDER, x + 120, y + 270, 120, 20, hwnd, 0, 0, 0);

	CreateWindow("Static", " Eingabe der geforderten Auflösung \n Wertebereich (0-1) ", WS_VISIBLE | WS_CHILD | ES_CENTER, 25, y + 210, 200, 80, hwnd, 0, 0, 0);
	aufl= CreateWindow("Edit", " 0.4", WS_VISIBLE | WS_CHILD | ES_CENTER | WS_BORDER|ES_CENTER, 225, y + 210, 121, 80, hwnd, 0, 0, 0);

	int x_start =25;
	tabx = 109;
	taby = 40;
    tab_start_y = 440;
	CreateWindow("Static", "Sollwerte Ø\n [mm]", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start +tabx, tab_start_y, tabx-1, taby-1, hwnd, 0, 0, 0);
	CreateWindow("Static", "Länge", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start, tab_start_y+taby, tabx-1, taby-1, hwnd, 0, 0, 0);
	CreateWindow("Static", "Breite", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start, tab_start_y + taby*2, tabx-1, taby-1, hwnd, 0, 0, 0);
	CreateWindow("Static", "Höhe", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start, tab_start_y + taby*3, tabx-1, taby-1, hwnd, 0, 0, 0);

	soll_h = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + tabx, tab_start_y + taby*3, tabx-1, taby-1, hwnd, 0, 0, 0);
	soll_b = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + tabx, tab_start_y + taby*2, tabx-1, taby-1, hwnd, 0, 0, 0);
	soll_l = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + tabx, tab_start_y + taby, tabx-1, taby-1, hwnd, 0, 0, 0);
	CreateWindow("Static", "Messwerte Ø\n [mm]", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + tabx * 2, tab_start_y, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	mess_h = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + tabx*2, tab_start_y + taby * 3, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	mess_b = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + tabx*2, tab_start_y + taby * 2, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	mess_l = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + tabx*2, tab_start_y + taby, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	x_start = 35;
	CreateWindow("Static", "Abweichung Ø \n [mm]", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + tabx * 3, tab_start_y, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	ab_h = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + tabx * 3, tab_start_y + taby * 3, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	ab_b = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + tabx * 3, tab_start_y + taby * 2, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	ab_l = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + tabx * 3, tab_start_y + taby, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	
	CreateWindow("Static", "standartabw.\n [mm]", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + tabx * 4, tab_start_y, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	sab_h = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + tabx * 4, tab_start_y + taby * 3, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	sab_b = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + tabx * 4, tab_start_y + taby * 2, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	sab_l = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + tabx * 4, tab_start_y + taby, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	x_start = 30;
	CreateWindow("Static", "Gut \n [%]", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + 15 + tabx * 5, tab_start_y, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	gut_l = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start+ 15 + tabx * 5, tab_start_y + taby , tabx - 1, taby - 1, hwnd, 0, 0, 0);
	gut_b = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start +15 + tabx * 5, tab_start_y + taby*2, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	gut_h= CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + 15 + tabx * 5, tab_start_y + taby * 3, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	CreateWindow("Static", "Mangel \n [%]", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + 15 + tabx * 6, tab_start_y, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	mang_l = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + 15 + tabx * 6, tab_start_y + taby , tabx - 1, taby - 1, hwnd, 0, 0, 0);
	mang_b = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + 15 + tabx * 6, tab_start_y + taby*2, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	mang_h= CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + 15 + tabx * 6, tab_start_y + taby * 3, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	CreateWindow("Static", "Defect \n [%]", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start +15 + tabx * 7, tab_start_y, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	def_l = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + 15 + tabx * 7, tab_start_y + taby , tabx - 1, taby - 1, hwnd, 0, 0, 0);
	def_b = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + 15 + tabx * 7, tab_start_y + taby*2, tabx - 1, taby - 1, hwnd, 0, 0, 0);
	def_h= CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, x_start + 15 + tabx * 7, tab_start_y + taby * 3, tabx - 1, taby - 1, hwnd, 0, 0, 0);


	soll_text=CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, 276, 90, 198, 120, hwnd, 0, 0, 0);
	mess_text=CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER, 726, 90, 198, 120, hwnd, 0, 0, 0);

	CreateWindow("Static", "Der Stein ist : ", WS_VISIBLE | WS_CHILD | ES_CENTER, 428, 620, 150, 50, hwnd, 0, 0, 0);
	auswertung = CreateWindow("Static", " ", WS_VISIBLE | WS_CHILD | ES_CENTER | WS_BORDER, 578, 620, 150, 50, hwnd, 0, 0, 0);
}
#endif