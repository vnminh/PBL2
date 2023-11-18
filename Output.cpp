#include "Output.h"
#include "Exception.h"
#include "Phone.h"
#include "Date.h"
#include <type_traits>
void mnu::DrawTitle(int w, const String t)
{
	CenterPrint(t, w);
	std::cout << "\n\n" << '+'; DrawLine(w - 2, '='); std::cout << '+' << "\n\n";
}
void mnu::DrawLine(int len, char c )
{
	for (int i = 1; i <= len; i++)
	{
		std::cout << c;
	}
}
void mnu::CenterPrint(const String &s, int len, char pad )
{
	int temp = len - s.GetLength();
	if (temp <= 0)
	{
		std::cout << s;
		return;
	}
	int before = floor(temp * 1.0 / 2);
	int after = ceil(temp * 1.0 / 2);
	DrawLine(before, pad);
	std::cout << s;
	DrawLine(after, pad);
}
void mnu::LeftPrint(const String &s, int len, char pad)
{
	int remain = len - s.GetLength();
	std::cout << s;
	if (remain < 0) return;
	DrawLine(remain, pad);
}
void mnu::LeftPrintForInput(const String &s, int len, char pad)
{
	int remain = len - s.GetLength();
	std::cout << s;
	if (remain < 0)
	{
		std::cout << ": ";
		return;
	}
	DrawLine(remain, pad);
	std::cout << ": ";
}
void mnu::PadLeftPrint(const String &s, int padlen, char pad )
{
	DrawLine(padlen, pad);
	std::cout << s;
}
template <typename T>
bool mnu::InputAndCheck(const String &mess, const int& width, void (*format)(const String&, int, char), T& var)
{
	bool ok = false;
	do
	{
		(*format)(mess, width, ' ');
		try
		{
			std::cin.clear();
			std::cin >> var;
			ok = true;
		}
		catch (Exception ex)
		{
			LeftPrint(ex.What(),0);
			std::cout << std::endl;
			LeftPrint("INPUT AGAIN, PLEASE\n",0);
		}
	} while (!ok);
	return true;
}
template bool mnu::InputAndCheck<Phone>(const String&, const int &, void(*)(const String&, int, char), Phone&);
template bool mnu::InputAndCheck<Date>(const String&, const int &, void(*)(const String&, int, char), Date&);