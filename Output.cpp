#include "Output.h"
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
	int before = floor(temp * 1.0 / 2);
	int after = ceil(temp * 1.0 / 2);
	DrawLine(before, pad);
	std::cout << s;
	DrawLine(after, pad);
}
void mnu::LeftPrint(const String &s, int padlen, char pad )
{
	DrawLine(padlen, pad);
	std::cout << s;
}