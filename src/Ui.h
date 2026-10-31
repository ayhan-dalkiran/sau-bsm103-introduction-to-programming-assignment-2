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
#include <iostream>
#include <string>
#include <functional>

#include "Finance.h"

namespace src {
	namespace ui {
		void NavigateToMainMenu();
		void PromptExitProgram();

		void NavigateToAccountSettings();
		void PromptCreateAccount();
		void PromptOpenAccountMenu();
		void ListAccounts();

		void NavigateToAccountMenu(src::finance::Account& account);
		void PromptDepositFiat(src::finance::Account& account);
		void PromptDepositCrypto(src::finance::Account& account);
		void PromptWithdrawFiat(src::finance::Account& account);
		void PromptWithdrawCrypto(src::finance::Account& account);
		void PromptBuyCrypto(src::finance::Account& account);
		void PromptSellCrypto(src::finance::Account& account);

		void NavigateToDateSettings();
		void PromptAdvanceDate();

		//Here is a bit of knowledge that I've learned to learn about templates: they are, to put it politely, very vexing to work with.
		//This part of the source code was supposed to in its seperate source file called 'Ui.cpp', but templates made that nearly impossible
		//to do due to linkage issues, which only left me with two suboptimal options:
		//1. Combining all UI code under the same source file. This, while would've worked, would also have made the code, that is already hard enough
		//	 to read as it is, impossible to reason with.
		//2. Moving this part of the code to the header file, which is what I ultimately decided to do at the end. This is still not ideal but light-years
		//	 better than the other option.
		//
		//As to reason why I used templates in the first place, I initially thought they would be a whole lot more trivial to implement but I was wrong.
		//I don't have a whole lot time to refactor the already existing code as I'm writing this, so I've to roll with it.

		//Repeatedly prompts user to enter input with given type until the input is valid.
		template<typename T> 
		T PromptGetInput(const std::string& prompt, const std::string& errorMessage) {
			T input;
			bool is_fail;

			do {
				std::cout << prompt;
				std::cin >> input;
				is_fail = std::cin.fail();

				// Clearing istream buffer for one or two reasons depending on situation.
				// 
				// 1. If the input is not valid for given type of l-value, this will reset the stream
				// flags, so that istream can be read from again (only when is_fail is true)
				// 
				// 2. When we read the value, we want to ignore the rest of the line so that we don't
				// try to process the same input again (mainly applies for char type, where istream
				// tries to parse the input character by character)
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				if (is_fail)
					std::cout << errorMessage << std::endl;
			}
			while (is_fail);

			return input;
		}

		//Repeatedly prompts user to enter input with given type until the input is valid and is one of the valid options.
		template<typename T> 
		T PromptGetInput(const std::string& prompt, const std::string& errorMessage, const std::initializer_list<T>& validOptions) {
			while (true) {
				T input = PromptGetInput<T>(prompt, errorMessage);

				//Checking if value is one of the valid options.
				for (size_t i = 0; i < validOptions.size(); i++)
					if (*(validOptions.begin() + i) == input)
						return input;

				std::cout << errorMessage << std::endl;
			}
		}

		//Repeatedly prompts user to enter input with given type until the input is valid and satisfies the given custom conditional.
		template<typename T> 
		T PromptGetInput(const std::string& prompt, const std::string& errorMessage, std::function<bool (const T&)> conditional) {
			while (true) {
				T input = PromptGetInput<T>(prompt, errorMessage);

				//Checking if input satisfies the conditional
				if (conditional(input))
					return input;

				std::cout << errorMessage << std::endl;
			}
		}
	}
}
