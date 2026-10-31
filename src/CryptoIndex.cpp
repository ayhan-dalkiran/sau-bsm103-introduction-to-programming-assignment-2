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
#include "Time.h"

using src::time::day_t;
using src::time::GetCurrentDay;

using namespace src::finance;

crypto_t CryptoIndex::ConvertToCrypto(fiat_t amount) {
	updateIndex();

	index_t convertion_rate = daily_index.at(GetCurrentDay());
	//Diving fiat by crypto to fiat conversion rate to get crypto equivalent.
	return amount / convertion_rate;
}
fiat_t CryptoIndex::ConvertToFiat(crypto_t amount) {
	updateIndex();

	index_t convertion_rate = daily_index.at(GetCurrentDay());
	//Multiplying crypto by crypto to fiat conversion rate to get fiat equivalent.
	return amount * convertion_rate;
}
index_t CryptoIndex::GetIndex(day_t day) {
	updateIndex();

	return daily_index.at(day);
}

void GeneralCryptoIndex::updateIndex() {
	while (daily_index.size() < src::time::GetCurrentDay()) {
		//The daily	1% increase for 14 days.
		for (day_t i = 0; i < 14; i++) {
			daily_index.emplace_back(daily_index.back() * 1.01);
		}
		//The 5% drop at day 15.
		daily_index.emplace_back(daily_index.back() * 0.95);
	}
}
void PrivateCryptoIndex::updateIndex() {
	while (daily_index.size() < src::time::GetCurrentDay()) {
		//Stores how many bad days
		//that is yet to happen
		//in the 30-day period.
		day_t remainingDays = 3;

		for (day_t i = 30; i > 0; i--) {
			//This will increase the chance
			//of a bad day happening unless
			//all 3 bad days have happened
			//already in the 30-day period.
			if (rand() % i < remainingDays) {
				remainingDays--;
				daily_index.emplace_back(daily_index.back() * 0.90);
			}
			else {
				daily_index.emplace_back(daily_index.back() * 1.05);
			}
		}
	}
}
