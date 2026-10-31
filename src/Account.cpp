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
#include "Finance.h"

using namespace src::finance;

fiat_t Account::GetFiatBalance() const {
	return fiatBalance;
}
crypto_t Account::GetCryptoBalance() const {
	return cryptoBalance;
}

void Account::DepositFiat(fiat_t amount) {
	fiatBalance += amount;
}
void Account::WithdrawFiat(fiat_t amount) {
	fiatBalance -= amount;
}

void Account::DepositCrypto(crypto_t amount) {
	cryptoBalance += amount;
}
void Account::WithdrawCrypto(crypto_t amount) {
	cryptoBalance -= amount;
}

void Account::BuyCrypto(crypto_t amount) {
	fiatBalance -= Index.ConvertToFiat(amount);
	cryptoBalance += amount;
}
void Account::SellCrypto(crypto_t amount) {
	cryptoBalance -= amount;
	fiatBalance += Index.ConvertToFiat(amount);
}

//General Index singleton that goes up by 1% every day and drops by 5% every 15 days.
GeneralCryptoIndex general_index = GeneralCryptoIndex();
//Private Index singleton that goes up by 5% every day and drops by 10% for random 3 days of the month.
//A month is a 30-day period for implementation reasons.
PrivateCryptoIndex private_index = PrivateCryptoIndex();

GeneralAccount::GeneralAccount(account_number_t account_number) : Account(account_number, "Genel", general_index) {}
PrivateAccount::PrivateAccount(account_number_t account_number) : Account(account_number, "Özel", private_index) {}
