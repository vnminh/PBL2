#ifndef OUTPUT_H
#define OUTPUT_H
#include <iostream>
#include "String.h"
namespace mnu
{
	const int TIME_WAIT = 1000;
	const int WIDTH = 100;
	const String TITLE = "Minimart Management System";
	const int LEFTSPACE = (WIDTH - TITLE.GetLength()) / 2;
	void DrawTitle(int = WIDTH, const String = TITLE);
	void DrawLine(int len, char c = '-');
	void CenterPrint(const String &s, int, char = ' ');
	void LeftPrint(const String &s, int = LEFTSPACE, char = ' ');
}
#endif