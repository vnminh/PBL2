#ifndef OUTPUT_H
#define OUTPUT_H
#include <iostream>
#include "String.h"
namespace mnu
{
	const int WIDTH = 140;
	const String TITLE = "Minimart Management System";
	const int WAIT = 500;
	const int LEFTSPACE = (WIDTH - TITLE.GetLength()) / 2;
	static int SubMenu = -1;
	void DrawTitle(int, int = WIDTH, const String = TITLE);
	void DrawLine(int len, char c, std::ostream&);
	void CenterPrint(const String &, int, char, std::ostream&);
	void LeftPrint(const String &, int, char, std::ostream&);
	void LeftPrintForInput(const String &, int, char, std::ostream&);
	void PadLeftPrint(const String &, int, char, std::ostream&);
	template< typename T>
	bool InputAndCheck(const String&, const int &, void(*)(const String&, int, char, std::ostream&), T &);
}
#endif