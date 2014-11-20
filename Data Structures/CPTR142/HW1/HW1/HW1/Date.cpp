#include "Date.h"

Date::Date(int mm, int dd, int yyyy) {
	month = mm;
	day = dd;
	year = yyyy;
}

void Date::setDate(int mm, int dd, int yyyy) {
	month = mm;
	day = dd;
	year = yyyy;
}

void Date::showDate() {
	cout << month << '/' << day << '/' << year;
}

long Date::packDate() {
	return 10000 * year + 100 * month + day;
}
bool Date::leapYearDate() {
	if ((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0))) {
		return true;
	}
	else
		return false;
}

int Date::daysInMonthOfDate() {
	//Check if the month has 31 days
	if ((month % 2 != 0 && month < 8) || (month % 2 == 0 && month > 8)) {
		return 31;
	}
	//If month isn't February, return 30
	else if (month != 2) {
		return 30;
	}
	//Check to see if it's a leap year
	else if ((year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0))) {
		return 29;
	}
	//Only remaining case is normal February
	else {
		return 28;
	}
}

int Date::intDayOfWkDate() {
	//Using Zeller's Algorithm (could not find a more up to date version)
	int y = year;
	int A = 0;
	int B = 0;
	A = 23 * month / 9 + day + 4;
	if (month < 3)
		B = y--;
	else
		B = y - 2;
	return ((A + B + y / 4 - y / 100 + y / 400) % 7);
}

string Date::stringDayOfWkDate() {
	//Use Zeller's Algorithm and then convert the resulting
	//Number into a string to return
	int y = year;
	int A = 0;
	int B = 0;
	A = 23 * month / 9 + day + 4;
	if (month < 3)
		B = y--;
	else
		B = y - 2;
	int dayOfWeek = ((A + B + y / 4 - y / 100 + y / 400) % 7);
	switch (dayOfWeek) {
	case 0: 
		return "Sunday";
		break;
	case 1: 
		return "Monday";
		break;
	case 2:
		return "Tuesday";
		break;
	case 3:
		return "Wednesday";
		break;
	case 4:
		return "Thursday";
		break;
	case 5:
		return "Friday";
		break;
	case 6:
		return "Saturday";
		break;
	default:
		return "Error";
	}
}