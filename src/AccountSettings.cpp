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
#include <map>
#include <string>

#include "Ui.h"
#include "Time.h"
#include "Finance.h"

using std::cout;
using std::endl;

using namespace src::finance;

//Stores created accounts.
std::map<Account::account_number_t, Account> account_map;

void src::ui::NavigateToAccountSettings() {
	system("cls");
	cout << "========================" << endl;
	cout << "[1] Yeni hesap aç" << endl;
	cout << "[2] Hesap seç" << endl;
	cout << "[3] Hesaplarý Listele" << endl;
	cout << "[-] Geri git " << endl;
	cout << "========================" << endl;
	cout << "Tarih: " << src::time::GetFormattedDate() << endl;
	cout << "========================" << endl;

	char choice = PromptGetInput<char>("Lütfen bir seçenek giriniz: ", "Geçersiz seçenek.", {'1', '2', '3', '-'});

	if (choice == '1')
		PromptCreateAccount();
	else if (choice == '2')
		PromptOpenAccountMenu();
	else if (choice == '3')
		ListAccounts();
	else
		NavigateToMainMenu();
}

void src::ui::PromptCreateAccount() {
	//Checks if account number is positive and doesn't already exist.
	const auto& is_account_number_valid = [] (const Account::account_number_t& account_number) -> bool {
		if (account_number <= 0)
			return false;

		if (account_map.find(account_number) != account_map.end())
			return false;

		return true;
	};

	Account::account_number_t account_number = PromptGetInput<Account::account_number_t>("Lütfen hesap numarasý giriniz: ", "Geçersiz hesap numarasý.", is_account_number_valid);

	cout << "Hesap tipi?" << endl;
	cout << "[1] Genel" << endl;
	cout << "[2] Özel" << endl;
	cout << "[-] Ýptal " << endl;

	char choice = PromptGetInput<char>("Lütfen bir seçenek giriniz: ", "Geçersiz seçenek.", {'1', '2', '-'});

	if (choice == '1')
		account_map.insert({account_number, GeneralAccount(account_number)});
	else if (choice == '2')
		account_map.insert({account_number, PrivateAccount(account_number)});

	NavigateToAccountSettings();
}
void src::ui::PromptOpenAccountMenu() {
	//Checks if choice is 0 or an existing account number.
	const auto& is_choice_valid = [] (const Account::account_number_t& choice) -> bool {
		if (choice == 0)
			return true;

		if (account_map.find(choice) != account_map.end())
			return true;

		return false;
	};

	cout << "========================" << endl;
	for (auto& i : account_map) {
		cout << "==========" << endl;
		cout << "[" << i.second.Account_Number << "]" << endl;
		cout << "Hesap Tipi: " << i.second.Account_Type << endl;
		cout << "TL Bakiyesi: " << i.second.GetFiatBalance() << endl;
		cout << "Kripto Bakiyesi: " << i.second.GetCryptoBalance() << endl;
		cout << "==========" << endl;
	}
	cout << "========================" << endl;
	cout << "[0] Ýptal" << endl;
	cout << "========================" << endl;

	Account::account_number_t choice = PromptGetInput<Account::account_number_t>("Lütfen bir seçenek giriniz: ", "Geçersiz seçenek.", is_choice_valid);

	if (choice == 0)
		NavigateToAccountSettings();
	else
		NavigateToAccountMenu(account_map.at(choice));
}

void src::ui::ListAccounts() {
	system("cls");
	cout << "========================" << endl;
	for (auto& i : account_map) {
		cout << "==========" << endl;
		cout << "Hesap Numarasý: " << i.second.Account_Number << endl;
		cout << "Hesap Tipi: " << i.second.Account_Type << endl;
		cout << "TL Bakiyesi: " << i.second.GetFiatBalance() << endl;
		cout << "Kripto Bakiyesi: " << i.second.GetCryptoBalance() << endl;
		cout << "==========" << endl;
	}
	cout << "========================" << endl;
	cout << "[-] Geri Git" << endl;
	cout << "========================" << endl;

	char choice = PromptGetInput<char>("Lütfen bir seçenek giriniz: ", "Geçersiz seçenek.", {'-'});
	NavigateToAccountSettings();
}