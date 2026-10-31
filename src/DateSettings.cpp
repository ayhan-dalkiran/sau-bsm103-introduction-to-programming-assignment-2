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

#include "Ui.h"
#include "Time.h"

using std::cout;
using std::endl;

using namespace src::time;

void src::ui::NavigateToDateSettings() {
	system("cls");
	cout << "========================" << endl;
	cout << "[1] Tarihi ileri çek" << endl;
	cout << "[-] Geri git" << endl;
	cout << "========================" << endl;
	cout << "Tarih: " << GetFormattedDate() << endl;
	cout << "========================" << endl;

	char choice = PromptGetInput<char>("Lütfen bir seçenek giriniz: ", "Geçersiz seçenek, lütfen yeniden seçiniz: ", {'1', '-'});

	if (choice == '1')
		PromptAdvanceDate();
	else
		NavigateToMainMenu();
}

void src::ui::PromptAdvanceDate() {
	//Checks if offset is not negative.
	const auto& is_valid_offset = [] (const day_t& offset) -> bool {
		return offset >= 0;
	};

	day_t offset = PromptGetInput<day_t>("Ýleri çekilecek gün sayýsý: ", "Geçersiz gün sayýsý, yeni bir deðer giriniz: ", is_valid_offset);

	cout << "Tarihi " << GetFormattedDate(offset) << " yapmak istediðinizden emin misiniz?" << endl;
	cout << "[1] Evet" << endl;
	cout << "[2] Hayýr" << endl;

	char choice = PromptGetInput<char>("Lütfen bir seçenek giriniz: ", "Geçersiz seçenek, lütfen yeniden seçiniz: ", {'1', '2'});

	if (choice == '1')
		AdvanceDay(offset);

	NavigateToDateSettings();
}