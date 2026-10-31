/****************************************************************************
**							SAKARYA ÜNÝVERSÝTESÝ
**				  BÝLGÝSAYAR VE BÝLÝÞÝM BÝLÝMLERÝ FAKÜLTESÝ
**					   BÝLGÝSAYAR MÜHENDÝSLÝÐÝ BÖLÜMÜ
**						PROGRAMLAMAYA GÝRÝÞÝ DERSÝ
**
**				ÖDEV NUMARASI....: 2
**				ÖÐRENCÝ ADI......: Ayhan Dalkýran
**				ÖÐRENCÝ NUMARASI.: G221210020
**				DERS GRUBU.......: 2. Öðretim C
****************************************************************************/
#include <iostream>
#include <string>

#include "Ui.h"
#include "Time.h"

using std::cout;
using std::endl;

void src::ui::NavigateToMainMenu() {
	system("cls");
	cout << "========================" << endl;
	cout << "[1] Hesap ayarlarý" << endl;
	cout << "[2] Tarih ayarlarý" << endl;
	cout << "[-] Programdan çýk " << endl;
	cout << "========================" << endl;
	cout << "Tarih: " << src::time::GetFormattedDate() << endl;
	cout << "========================" << endl;

	char choice = PromptGetInput<char>("Lütfen bir seçenek giriniz: ", "Geçersiz seçenek.", {'1', '2', '-'});

	if (choice == '1')
		NavigateToAccountSettings();
	else if (choice == '2')
		NavigateToDateSettings();
	else
		PromptExitProgram();
}

void src::ui::PromptExitProgram() {
	cout << "Çýkmak istediðinizden emin misiniz?" << endl;
	cout << "[1] Evet" << endl;
	cout << "[2] Hayýr" << endl;

	char choice = PromptGetInput<char>("Lütfen bir seçenek giriniz: ", "Geçersiz seçenek.", {'1', '2'});

	if (choice == '1')
		std::exit(EXIT_SUCCESS);

	NavigateToMainMenu();
}
