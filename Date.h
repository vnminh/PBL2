#ifndef DATE_H
#define DATE_H
#include <iostream>
#include "String.h"
class Date
{
	friend Date Today();
    friend std::istream& operator>>(std::istream&, Date&);
	friend std::ostream& operator<<(std::ostream&, const Date&);
    private:
        int Day,Month,Year;
		static const int DayOfMonth[13];
		bool isLeapYear(int) const;
		void HelpIncrease();
    public:
		Date(int = 1, int = 1, int = 1990);
		Date(const String&, const String & ="/");
        Date(const Date&);
        ~Date();
        int GetDay() const;
        void SetDay(int);
        int GetMonth() const;
        void SetMonth(int);
        int GetYear() const;
        void SetYear(int);
		void SetDate(int, int, int);
        bool operator==(const Date&) const;
		bool operator!=(const Date&) const;
		bool operator<=(const Date&) const;
		bool operator>=(const Date&) const;
		const Date& operator=(const Date&);
        Date& operator++();
        const Date operator++(int);
		const Date operator+ (const int&);
		String to_string() const;
};
#endif