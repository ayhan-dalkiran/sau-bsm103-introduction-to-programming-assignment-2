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
#include <ctime>
#include "Time.h"

using std::string;

using namespace src::time;

//Saves the start time at program's initialization.
const time_t start_time = time(nullptr);
day_t currentDay = 0;

day_t src::time::GetCurrentDay() {
	return currentDay;
}
void src::time::AdvanceDay(day_t amount) {
	currentDay += amount;
}

//Formats current day + offset in dd/mm/yyyy format.
string src::time::GetFormattedDate(day_t offset) {
	static tm* time_struct = new tm();

	//Getting local time in seconds by converting day offset to seconds
	//so that we could get date information from localtime_s.
	time_t raw_time = start_time + (currentDay + offset) * 24 * 60 * 60;
	localtime_s(time_struct, &raw_time);

	string day, month, year;

	if (time_struct->tm_mday < 10)
		day = "0";
	day += std::to_string(time_struct->tm_mday);

	//Very weird tm behaviour, tm_mon counts how many months
	//how many months have passed since January, which means
	//0 is January and 11 is December. This doesn't apply
	//for tm_mday.
	if (time_struct->tm_mon < 9)
		month = "0";
	month += std::to_string(time_struct->tm_mon + 1);

	//In tm, year starts from 1900, which is fair enough.
	year += std::to_string(time_struct->tm_year + 1900);

	return day + "/" + month + "/" + year;
}
