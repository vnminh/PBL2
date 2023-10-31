#include "String.h"
#include "Exception.h"
#include <iostream>
using namespace std;
String::String(int len)
    :length(len)
{
    this->ptr=new char[len+1];// +1 la cho '\0'
}
String::String(const char *ptr)
	: length(strlen(ptr))
{
	this->ptr = new char[(this->length) + 1];
	strcpy_s(this->ptr, this->length+1, ptr);
}
String::String(const String& s)
    :length(s.length)
{
    this->ptr=new char[this->length+1];
	strcpy_s(this->ptr, this->length+1, s.ptr);
}
String::~String()
{
    delete[] this->ptr;
}
const String& String::operator=(const String& s){
    if (this!=&s){
        if (this->length!=s.length)
        {
            delete[] this->ptr;
            this->length=s.length;
            ptr=new char [this->length+1];
        }
		strcpy_s(this->ptr, this->length+1, s.ptr);
    }
    return *this;
}
String::operator char *() const
{
	return this->ptr;
}
bool String::operator<(const String& s) const
{
	int len = (this->length < s.length) ? this->length : s.length;
	for (int i = 0; i < len; i++)
	{
		if ((*this)[i] >= s[i])
		{
			return false;
		}
	}
	return true;
}
bool String::operator==(const String& s) const
{
    if (this->length!=s.length) return false;
    for(int i=0;i<this->length;i++)
        if ((*this)[i]!=s[i]) return false;
    return true;
}
bool String::operator!=(const String& s) const
{
	return !((*this) == s);
}
const char& String::operator[](int index) const
{
	if (index < 0 || index >= this->length)
	{
		throw Exception("OUT OF RANGE");
	}
	else return *(this->ptr + index);
}
char& String::operator[](int index)
{
	if (index < 0 || index >= this->length)
	{
		throw Exception("OUT OF RANGE");
	}
	else return *(this->ptr + index);
}
void String::ClearSpace()
{
	int l = -1, r = this->length;
	do
	{
		l++;
	} while ((*this)[l] == ' ');
	do
	{
		r--;
	} while ((*this)[r] == ' ');
	char * ptr = new char[r-l + 1 + 1];
	strncpy_s(ptr,r-l+1+1, this->ptr + l, r - l + 1 );
	delete[] this->ptr;
	this->length = strlen(ptr);
	this->ptr = ptr;
}
istream& operator>>(istream& inp, String& s)
{
    inp.getline(s.ptr,s.length + 1,'\n');
    return inp;
}
ostream& operator<<(ostream& out, const String& s)
{
    out<<s.ptr;
    return out;
}
