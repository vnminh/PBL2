#ifndef TIME_H
#define TIME_H
#include <iostream>
#include "String.h"
class Time
{
	friend std::istream& operator>>(std::istream&, Time&);
private:
	int Sec;
	int Min;
	int Hour;
public:
	Time(int = 0, int = 0, int = 0);
	Time(const String&, const String & = ":");
	~Time();
	void SetSec(int);
	void SetMin(int);
	void SetHour(int);
	void SetTime(int, int, int);
	friend std::ostream & operator<< (std::ostream&, const Time&);
	friend Time Now();
};
#endif
