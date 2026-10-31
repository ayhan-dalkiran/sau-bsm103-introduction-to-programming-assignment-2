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
#pragma once
#include <vector>
#include <string>

#include "Time.h"

namespace src {
	namespace finance {
		using fiat_t = long double;
		using crypto_t = long double;
		using index_t = long double;

		//Base class for General and Private crypto indexes.
		class CryptoIndex {
		protected:
			//Daily index for conversion rate from crypto to fiat currency.
			std::vector<index_t> daily_index = {1.0};
			virtual void updateIndex() = 0;
		public:
			crypto_t ConvertToCrypto(fiat_t amount);
			fiat_t ConvertToFiat(crypto_t amount);
			index_t GetIndex(src::time::day_t day);
		};
		class GeneralCryptoIndex : public CryptoIndex {
		protected:
			void updateIndex();
		};
		class PrivateCryptoIndex : public CryptoIndex {
		protected:
			void updateIndex();
		};

		//Base class for General and Private accounts.
		class Account {
		public:
			using account_number_t = long long;

			const account_number_t Account_Number;
			const std::string Account_Type;

			CryptoIndex& Index;

			fiat_t GetFiatBalance() const;
			crypto_t GetCryptoBalance() const;

			void DepositFiat(fiat_t amount);
			void WithdrawFiat(fiat_t amount);

			void DepositCrypto(crypto_t amount);
			void WithdrawCrypto(crypto_t amount);

			void BuyCrypto(crypto_t amount);
			void SellCrypto(crypto_t amount);
		protected:
			fiat_t fiatBalance = 0;
			crypto_t cryptoBalance = 0;

			Account(account_number_t account_number, std::string account_type, CryptoIndex& index) : Account_Number(account_number), Account_Type(account_type), Index(index) {}
		};
		class GeneralAccount : public Account {
		public:
			GeneralAccount(account_number_t account_number);
		};
		class PrivateAccount : public Account {
		public:
			PrivateAccount(account_number_t account_number);
		};
	}
}