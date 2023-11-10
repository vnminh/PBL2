#ifndef OUTPUT_H
#define OUTPUT_H
#include <iostream>
#include "String.h"
namespace mnu
{
	const int WIDTH = 100;
	const String TITLE = "Minimart Management System";
	const int LEFTSPACE = (WIDTH - TITLE.GetLength()) / 2;
	void DrawTitle(int = WIDTH, const String = TITLE);
	void DrawLine(int len, char c = '-');
	void CenterPrint(const String &, int, char = ' ');
	void LeftPrint(const String &, int, char = ' ');
	void PadLeftPrint(const String &, int = LEFTSPACE, char = ' ');
}
#endif