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
#include "Ui.h"
#include "Finance.h"
#include "Time.h"

using std::cout;
using std::endl;

using namespace src::finance;

void src::ui::NavigateToAccountMenu(Account& account) {
	system("cls");
	cout << "========================" << endl;
	cout << "Hesap numarasý: " << account.Account_Number << endl;
	cout << "Hesap tipi: " << account.Account_Type << endl;
	cout << "TL bakiyesi: " << account.GetFiatBalance() << endl;
	cout << "Kripto bakiyesi: " << account.GetCryptoBalance() << endl;
	cout << "Dönüþüm oraný: " << account.Index.GetIndex(src::time::GetCurrentDay()) << endl;
	cout << "========================" << endl;
	cout << "[1] TL ekle" << endl;
	cout << "[2] Kripto ekle" << endl;
	cout << "[3] TL çek" << endl;
	cout << "[4] Kripto çek" << endl;
	cout << "[5] Kripto al" << endl;
	cout << "[6] Kriptoya sat" << endl;
	cout << "[-] Geri git " << endl;
	cout << "========================" << endl;
	cout << "Tarih: " << src::time::GetFormattedDate() << endl;
	cout << "========================" << endl;

	char choice = PromptGetInput<char>("Lütfen bir seçenek giriniz: ", "Geçersiz seçenek.", {'1', '2', '3', '4', '5', '6', '-'});

	if (choice == '1')
		PromptDepositFiat(account);
	else if (choice == '2')
		PromptDepositCrypto(account);
	else if (choice == '3')
		PromptWithdrawFiat(account);
	else if (choice == '4')
		PromptWithdrawCrypto(account);
	else if (choice == '5')
		PromptBuyCrypto(account);
	else if (choice == '6')
		PromptSellCrypto(account);
	else
		NavigateToAccountSettings();
}

void src::ui::PromptDepositFiat(Account& account) {
	//Checks if deposit is positive.
	const auto& is_valid_amount = [] (const fiat_t& amount) -> bool {
		return amount > 0.0;
	};

	fiat_t amount = PromptGetInput<fiat_t>("Lütfen yüklenilecek TL miktarýný giriniz: ", "Geçersiz deðer.", is_valid_amount);
	account.DepositFiat(amount);
	NavigateToAccountMenu(account);
}
void src::ui::PromptDepositCrypto(Account& account) {
	//Checks if deposit is positive.
	const auto& is_valid_amount = [] (const crypto_t& amount) -> bool {
		return amount > 0.0;
	};

	crypto_t amount = PromptGetInput<crypto_t>("Lütfen yüklenilecek kripto miktarýný giriniz: ", "Geçersiz deðer.", is_valid_amount);
	account.DepositCrypto(amount);
	NavigateToAccountMenu(account);
}
void src::ui::PromptWithdrawFiat(Account& account) {
	//Checks if there is enough fiat currency in the account for withdrawal.
	const auto& is_valid_amount = [&account] (const fiat_t& amount) -> bool {
		return account.GetFiatBalance() >= amount;
	};

	fiat_t amount = PromptGetInput<fiat_t>("Lütfen çekilecek TL miktarýný giriniz: ", "Geçersiz deðer.", is_valid_amount);
	account.WithdrawFiat(amount);
	NavigateToAccountMenu(account);
}
void src::ui::PromptWithdrawCrypto(Account& account) {
	//Checks if there is enough crypto in the account for withdrawal.
	const auto& is_valid_amount = [&account] (const crypto_t& amount) -> bool {
		return account.GetCryptoBalance() >= amount;
	};

	crypto_t amount = PromptGetInput<crypto_t>("Lütfen çekilecek kripto miktarýný giriniz: ", "Geçersiz deðer.", is_valid_amount);
	account.WithdrawCrypto(amount);
	NavigateToAccountMenu(account);
}
void src::ui::PromptBuyCrypto(Account& account) {
	//Checks if there is enough fiat balance to buy requested amount of crypto
	const auto& is_valid_amount = [&account] (const crypto_t& amount) -> bool {
		return account.GetFiatBalance() >= account.Index.ConvertToFiat(amount);
	};

	crypto_t amount = PromptGetInput<crypto_t>("Lütfen satýn alýnacak kripto miktarýný giriniz: ", "Geçersiz deðer.", is_valid_amount);
	account.BuyCrypto(amount);
	NavigateToAccountMenu(account);
}
void src::ui::PromptSellCrypto(Account& account) {
	//Checks if there is enough crypto balance to sell.
	const auto& is_valid_amount = [&account] (const crypto_t& amount) -> bool {
		return account.GetCryptoBalance() >= amount;
	};

	crypto_t amount = PromptGetInput<crypto_t>("Lütfen satýlacak kripto miktarýný giriniz: ", "Geçersiz deðer.", is_valid_amount);
	account.SellCrypto(amount);
	NavigateToAccountMenu(account);
}
