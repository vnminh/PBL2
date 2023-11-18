#ifndef PHONE_H
#define PHONE_H
#include "String.h"
#include <iostream>
class Phone
{
	friend std::ostream& operator<< (std::ostream&, const Phone &);
	friend std::istream& operator>> (std::istream&, Phone &);
private:
	String number;
public:
	Phone(const String ="0000000000");
	~Phone();
	void SetNumber(const String &);
	bool operator==(const Phone&) const;
	bool operator!=(const Phone&) const;
	String GetNumber() const;
	String to_string() const;
};
#endif
