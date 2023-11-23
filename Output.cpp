#include "Output.h"
#include "Exception.h"
#include "Phone.h"
#include "Date.h"
#include <conio.h>
#include <Windows.h>
void mnu::DrawTitle(int type, int w, const String t) // type = 0 1 2 3
{
	CenterPrint(t, w,' ',std::cout);
	std::cout << "\n\n" << '+'; DrawLine(w - 2, '=', std::cout); std::cout << '+' << std::endl;
	String title[4]{"PRODUCT MANAGEMENT", "CUSTOMER MANAGEMENT", "BILL MANAGEMENT", "BILL CALCULATE"};
	int subw = (mnu::WIDTH - 8) / 4;
	for (int i = 0; i < 4; i++)
	{
		if (i == type)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			std::cout << '|'; CenterPrint(title[0], subw, ' ', std::cout); std::cout << '|';
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
		else
		{
			std::cout << '|'; CenterPrint(title[0], subw, ' ', std::cout); std::cout << '|';
		}
	}
	std::cout << std::endl << '+'; DrawLine(w - 2, '=', std::cout); std::cout << '+' << "\n\n";
}
void mnu::DrawLine(int len, char c, std::ostream& out)
{
	for (int i = 1; i <= len; i++)
	{
		out << c;
	}
}
void mnu::CenterPrint(const String &s, int len, char pad, std::ostream& out)
{
	int temp = len - s.GetLength();
	if (temp <= 0)
	{
		out << s;
		return;
	}
	int before = floor(temp * 1.0 / 2);
	int after = ceil(temp * 1.0 / 2);
	DrawLine(before, pad,out);
	out << s;
	DrawLine(after, pad,out);
}
void mnu::LeftPrint(const String &s, int len, char pad, std::ostream& out)
{
	int remain = len - s.GetLength();
	out << s;
	if (remain < 0) return;
	DrawLine(remain, pad,out);
}
void mnu::LeftPrintForInput(const String &s, int len, char pad, std::ostream& out)
{
	int remain = len - s.GetLength();
	out << s;
	if (remain < 0)
	{
		out << ": ";
		return;
	}
	DrawLine(remain, pad,out);
	out << ": ";
}
void mnu::PadLeftPrint(const String &s, int padlen, char pad, std::ostream& out)
{
	DrawLine(padlen, pad,out);
	out << s;
}
template <typename T>
bool mnu::InputAndCheck(const String &mess, const int& width, void(*format)(const String&, int, char, std::ostream&), T& var)
{
	bool ok = false;
	do
	{
		(*format)(mess, width, ' ',std::cout);
		try
		{
			fflush(stdin);
			std::cin.clear();
			std::cin >> var;
			ok = true;
		}
		catch (Exception ex)
		{
			LeftPrint(ex.What(),0,' ',std::cout);
			std::cout << std::endl;
			LeftPrint("INPUT AGAIN, PLEASE\n",0,' ',std::cout);
		}
	} while (!ok);
	return true;
}
template bool mnu::InputAndCheck<Phone>(const String&, const int &, void(*)(const String&, int, char, std::ostream&), Phone&);
template bool mnu::InputAndCheck<Date>(const String&, const int &, void(*)(const String&, int, char, std::ostream&), Date&);