#include <iostream>
#include <string>

using namespace std;
class Date {
private:
	int month, day, year;
public:
	Date(int = 1, int = 17, int = 2014);
	void setDate(int, int, int);
	void showDate();
	long packDate();

	bool leapYearDate();
	int daysInMonthOfDate();
	int intDayOfWkDate();
	string stringDayOfWkDate();

	friend bool operator< (const Date&, const Date&);
	friend bool operator> (const Date&, const Date&);
	friend bool operator==(const Date&, const Date&);

	friend ostream& operator<<(ostream&, const Date&);
	friend istream& operator>>(istream&, Date&);
};