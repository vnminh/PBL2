#include "Time.h"
#include "Exception.h"
#include <iomanip>
using namespace std;
Time::Time(int s, int m, int h)
	:Sec(s), Min(m), Hour(h)
{}
Time::~Time()
{}
void Time::SetSec(int s)
{
	if (s < 0 || s>59)
	{
		throw Exception("INVALID VALUE FOR SECOND");
	}
	this->Sec = s;
}
void Time::SetMin(int m)
{
	if (m < 0 || m>59)
	{
		throw Exception("INVALID VALUE FOR MINUTE");
	}
	this->Min = m;
}
void Time::SetHour(int h)
{
	if (h < 0 || h>23)
	{
		throw Exception("INVALID VALUE FOR HOUR");
	}
	this->Hour = h;
}
void Time::SetTime(int s, int m, int h)
{
	this->SetHour(h);
	this->SetMin(m);
	this->SetSec(s);
}
ostream &operator<<(ostream& out, const Time& t)
{
	out << setw(2) << setfill('0') << t.Hour << ':' << setw(2) << setfill('0') << t.Min << ':' << t.Sec;
	return out;
}
Time Now()
{
	Time res;
	time_t ttime = time(nullptr);
	tm t;
	localtime_s(&t, &ttime);
	res.Sec = t.tm_sec;
	res.Min = t.tm_min;
	res.Hour = t.tm_hour;
	return res;
}
istream& operator>>(istream& inp, Time& t)
{
	int s, m, h;
	inp >> h; inp.ignore();
	inp >> m; inp.ignore();
	inp >> s;
	t.SetTime(s, m, h);
	return inp;
}