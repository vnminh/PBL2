#include "Date.h"
#include "Exception.h"
#include <iomanip>
using namespace std;
const int Date::DayOfMonth[13]{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
Date::Date(int d, int m, int y)
{
	SetDate(d, m, y);
}
Date::Date(const Date& date)
	:Date(date.Day,date.Month,date.Year)
{}
Date::Date(const String & s)
{
	String temp = s;
	char *token;
	String d, m, y;
	d=strtok_s(temp, "/", &token);
	m=strtok_s(NULL, "/", &token);
	y=strtok_s(NULL, "/", &token);
	d.ClearSpace();
	m.ClearSpace();
	y.ClearSpace();
	SetDate(atoi(d), atoi(m), atoi(y));
}
Date::~Date()
{}
int Date::GetDay() const
{
	return this->Day;
}
int Date::GetMonth() const
{
	return this->Month;
}
int Date::GetYear() const
{
	return this->Year;
}
void Date::SetDate(int d, int m, int y)
{
	SetYear(y);
	SetMonth(m);
	SetDay(d);
}
bool Date::isLeapYear(int y) const
{
	return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}
void Date::SetDay(int d)
{
	if (this->Month == 2)
	{
		if (d < 1 || d > Date::DayOfMonth[2])
			throw Exception("INVALID VALUE FOR DAY");
		else if (d == 29 && !isLeapYear(this->Year))
			throw Exception("INVALID VALUE FOR DAY");
		else this->Day = d;
	}
	else if (d < 1 || d > Date::DayOfMonth[this->Month])
	{
		throw Exception("INVALID VALUE FOR DAY");
	}
	else this->Day = d;
}
void Date::SetMonth(int m)
{
	if (m >= 1 && m <= 12)
	{
		this->Month = m;
	}
}
void Date::SetYear(int y)
{
	if (y > 0)
	{
		this->Year = y;
	}
}
bool Date::operator==(const Date& date) const
{
	return (this->Day == date.Day) && (this->Month == date.Month) && (this->Year == date.Year);
}
void Date::HelpIncrease()
{
	this->Day++;
	if (this->Day > DayOfMonth[2]) this->Month++;
	if (this->Month == 2)
	{
		 if (this->Day == 29 && !isLeapYear(this->Year)) this->Month++;
	}
	if (this->Month == 13) this->Year++;
}
Date& Date::operator++()
{
	Date::HelpIncrease();
	return *this;
}
const Date Date::operator++(int)
{
	Date temp = *this;
	Date::HelpIncrease();
	return temp;
}
const Date& Date::operator=(const Date& date)
{
	if (this != &date)
	{
		SetDate(date.Day, date.Month, date.Year);
	}
	return *this;
}
String Date::show()
{
	String d = this->Day;
	String m = this->Month;
	String y = this->Year;
	String ans = d + "/" + m + "/" + y;;
	if (this->Day < 10) ans = String("0") + ans;
	return ans;
}
ostream& operator<<(ostream &out, const Date& date)
{
	out << setw(2) << setfill('0') << date.Day << '/' << setw(2) << setfill('0') << date.Month << '/' << date.Year;
	return out;
}