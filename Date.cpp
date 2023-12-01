#include <ctime>
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
Date::Date(const String & s, const String &delim)
{
	String temp = s;
	char *ptr;
	String d, m, y;
	d = strtok_s(temp, delim, &ptr);
	m = strtok_s(nullptr, delim, &ptr);
	y = strtok_s(nullptr, delim, &ptr);
	d.DeleteFirstSpace();
	d.DeleteLastSpace();
	m.DeleteFirstSpace();
	m.DeleteLastSpace();
	y.DeleteFirstSpace();
	y.DeleteLastSpace();
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
	if (m < 1 || m>12)
	{
		throw Exception("INVALID VALUE FOR MONTH");
	}
	this->Month = m;
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
bool Date::operator!=(const Date& date) const
{
	return !(*this == date);
}
bool Date::operator<=(const Date& date) const
{
	if (this->Year < date.Year) return true;
	else if (this->Year > date.Year) return false;
	else // ==
	{
		if (this->Month < date.Month) return true;
		else if (this->Month > date.Month) return false;
		else // == 
		{
			if (this->Day <= date.Day) return true;
			else return false;
		}
	}
}
bool Date::operator>=(const Date& date) const
{
	if (this->Year > date.Year) return true;
	else if (this->Year < date.Year) return false;
	else // ==
	{
		if (this->Month > date.Month) return true;
		else if (this->Month < date.Month) return false;
		else // == 
		{
			if (this->Day >= date.Day) return true;
			else return false;
		}
	}
}
void Date::HelpIncrease()
{
	this->Day++;
	if (this->Day > DayOfMonth[this->Month])
	{
		this->Month++;
		this->Day = 1;
	}
	if (this->Month == 2)
	{
		if (this->Day == 29 && !isLeapYear(this->Year))
		{
			this->Month++;
			this->Day = 1;
		}
	}
	if (this->Month == 13)
	{
		this->Year++;
		this->Month = 1;
	}
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
const Date Date::operator+(const int& d)
{
	Date res = *this;
	for (int i = 0; i < d; i++)
	{
		res.HelpIncrease();
	}
	return res;
}
const Date& Date::operator=(const Date& date)
{
	if (this != &date)
	{
		SetDate(date.Day, date.Month, date.Year);
	}
	return *this;
}
String Date::to_string() const
{
	String ans;
	if (this->Day < 10) ans = ans + "0";
	ans = ans + String::to_string(this->Day) + "/";
	if (this->Month < 10) ans = ans + String("0");
	ans = ans + String::to_string(this->Month) + "/" + String::to_string(this->Year);
	return ans;
}
ostream& operator<<(ostream &out, const Date& date)
{
	out << setw(2) << setfill('0') << date.Day << '/' << setw(2) << setfill('0') << date.Month << '/' << date.Year;
	return out;
}
istream& operator>>(istream &inp, Date& date)
{
	int d, m, y;
	inp >> d; inp.ignore();
	inp >> m; inp.ignore();
	inp >> y;
	date.SetDate(d, m, y);
	return inp;
}
Date Today()
{
	Date res;
	time_t ttime = time(nullptr);
	tm t;
	localtime_s(&t, &ttime);
	res.Day = t.tm_mday;
	res.Month = t.tm_mon + 1;
	res.Year = t.tm_year + 1900;
	return res;
}