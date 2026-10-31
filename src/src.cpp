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
#include <iomanip>

#include "Ui.h"

int main() {
	//Changes console locate to support Turkish characters. 
	setlocale(LC_ALL, "Turkish");
	//Setting all direct number output to fixed-point values
	//with 2-decimal precision.
	std::cout << std::fixed << std::setprecision(2);
	//Shows main menu on the console.
	src::ui::NavigateToMainMenu();
}
