#include "Phone.h"
#include "Exception.h"
using namespace std;
Phone::Phone(const String num)
	:number(num)
{
}
Phone::~Phone()
{
}
void Phone::SetNumber(const String & num)
{
	if (num.GetLength() != 10)
	{
		throw Exception("INVALID PHONE NUMBER - EXPECTED 10 NUMBERS");
	}
	this->number = num;
}
bool Phone::operator==(const Phone& p) const
{
	return this->number == p.number;
}
bool Phone::operator!=(const Phone &p) const
{
	return this->number != p.number;
}
String Phone::GetNumber()const
{
	return this->number;
}
String Phone::to_string() const
{
	return this->number;
}
ostream& operator<<(ostream& out, const Phone& p)
{
	out << p.number;
	return out;
}
istream& operator>>(istream& inp, Phone& p)
{
	String temp;
	cin >> temp;
	p.SetNumber(temp);
	return inp;
}