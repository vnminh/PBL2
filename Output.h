#ifndef OUTPUT_H
#define OUTPUT_H
#include <iostream>
#include "String.h"
namespace mnu
{
	const int WIDTH = 130;
	const String TITLE = "Minimart Management System";
	const int WAIT = 500;
	const int LEFTSPACE = (WIDTH - TITLE.GetLength()) / 2;
	void DrawTitle(int = WIDTH, const String = TITLE);
	void DrawLine(int len, char c = '-');
	void CenterPrint(const String &, int, char = ' ');
	void LeftPrint(const String &, int, char = ' ');
	void LeftPrintForInput(const String &, int, char = ' ');
	void PadLeftPrint(const String &, int = LEFTSPACE, char = ' ');
	template< typename T>
	bool InputAndCheck(const String&, const int &,void (*)(const String&,int,char), T &);
}
#endif