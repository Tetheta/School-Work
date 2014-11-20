/*****************************************************************************
Program file name: Assignment #2 			OS: windows 8          		Assignment #: 2
Programmer: Travis Crumley 			Class: 	Data Structures II			Date: 1/17/2014
Compiler: Visual Studio 2013

Assistance/references: In class work posted on common drive (K:\common)
Description: This program allows you to input almost any date and figure out which day of the week that date corresponds to, as well as many other date manipulation functions

Inputs: Month, Day, year
Outputs: Day of the week in string or int form, days in the month of a date, if a date is a leap year or not, and it also allows comparison and cin cout with overloaded operators.

Special Comments:

~~~~~~~~~~~~~~~~~~~~~~~~~~Grading Criteria~~~~~~~~~~~~~~~~~~~~~~~~~~
Assignment Requirements ___/3.0
Code Format/Cosmetics ___/3.0
Header & Code Comments: ___/2.0
Output Format/Cosmetics ___/2.0

***Does Not Compile***: ___ (-10.0)
***Late Work Deduction***: ___ (-0.5/day)
Total Grade: ___/10.0

*****************************************************************************/

#include "Date.h"

//Definining friend functions
//An easier way to do this would be to imitate the packDate function then simply
//Use the operator we are overloading on the resultings ints to compare.
bool operator< (const Date& date1, const Date& date2)
{
	if (date1.year < date2.year)
		return true;
	else if (date1.year == date2.year && (date1.month < date2.month))
		return true;
	else if (date1.year == date2.year && date1.month == date2.month && (date1.day < date2.day))
		return true;
	else
		return false;
}
bool operator> (const Date& date1, const Date& date2)
{
	if (date1.year > date2.year)
		return true;
	else if (date1.year == date2.year && (date1.month > date2.month))
		return true;
	else if (date1.year == date2.year && date1.month == date2.month && (date1.day > date2.day))
		return true;
	else
		return false;
}
bool operator==(const Date & date1, const Date & date2)
{
	//Return if everything is equal
	return date1.year == date2.year && date1.month == date2.month && date1.day == date2.day;
}

ostream& operator<<(ostream& stream, const Date& date) {
	return cout << date.month << "/" << date.day << "/" << date.year;
}
istream& operator>>(istream& stream, Date& date) {
	int mm, yyyy, dd; //Temp variables
	cin >> mm;
	cin.ignore(1); //Used to ignore the '/'
	cin >> dd;
	cin.ignore(1);
	cin >> yyyy;
	date.setDate(mm, dd, yyyy);
	return stream;
}

int main()
{
	Date d(1, 1, 2014);
	//Main Loop, this allows testing of all functionality except for showDate, which is deprecated because of cout.
	while (true) {
		Date testDate;
		cout << "Please enter in a date: mm/dd/yyyy" << endl;
		cin >> testDate;
		cout << "Your date is" << testDate << endl;
		cout << "Your packed Date is: " << testDate.packDate() << endl;
		if (testDate.leapYearDate())
		{
			cout << "The date year is a leap year" << endl;
		}
		cout << "The date month has " << testDate.daysInMonthOfDate() << " days in it" << endl;
		cout << "The day of the week of your date is " << testDate.intDayOfWkDate() << ", " << testDate.stringDayOfWkDate() << endl;
		if (testDate < d)
		{
			cout << "Your date is earlier than 1/1/2014" << endl;
		}
		if (testDate > d)
		{
			cout << "Your date is later than 1/1/2014" << endl;
		}
		if (testDate == d)
		{
			cout << "Your date is 1/1/2014" << endl;
		}
	}
}
