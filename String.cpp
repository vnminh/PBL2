#include "String.h"
#include "Exception.h"
#include <iostream>
#define MAX 100
using namespace std;
String::String()
	:length(0), ptr(nullptr)
{}
String::String(const char *ptr)
	: length(strlen(ptr))
{
	this->ptr = new char[(this->length) + 1];
	strcpy_s(this->ptr, this->length + 1, ptr);
}
String::String(const String& s)
    :length(s.length)
{
	this->ptr = new char[this->length + 1];
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
const String String::operator+(const String & s) const
{
	char temp[MAX]{};
	if (this->length != 0) strcpy_s(temp, this->length + 1, this->ptr);
	int len = this->length + s.length;
	strcat_s(temp, len + 1, s.ptr);
	return temp;
}
String::operator char *()
{
	return this->ptr;
}
String::operator const char* () const
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
long long String::to_ll() const
{
	long long res = 0;
	for (int i = this->length - 1; i >= 0; i++)
	{
		long long temp = (*this)[i] - '0';
		res = res * 10 + temp;
	}
	return res;
}
void String::Erase(int index)
{
	char temp[MAX];
	if (index != 0) strncpy_s(temp, index + 1, this->ptr, index);
	if (index != this->length - 1) strncpy_s(temp + index, this->length - index, this->ptr + index + 1, this->length - index - 1);
	this->length--;
	delete[] this->ptr;
	this->ptr = new char[this->length + 1];
	strcpy_s(this->ptr, this->length + 1, temp);
}
void String::GetLine(istream& inp, char delim)
{
	char temp[MAX]{};
	inp.getline(temp,MAX,delim);
	this->length = strlen(temp);
	delete[] this->ptr;
	this->ptr = new char[this->length + 1];
	strcpy_s(this->ptr, this->length + 1, temp);
}
int String::GetLength() const
{
	return this->length;
}
void String::DeleteFirstSpace()
{
	while ((*this)[0] == ' ')
	{
		this->Erase(0);
	}
}
void String::DeleteLastSpace()
{
	while ((*this)[this->length - 1] == ' ')
	{
		this->Erase(this->length - 1);
	}
}
String String::SubStr(const int &pos, const int&len) const
{
	char temp[MAX]{};
	for (int i = 0; i < len; i++)
	{
		temp[i] = (*this)[pos + i];
	}
	return String(temp);
}
istream& operator>>(istream& inp, String& s)
{
	char temp[MAX]{};
	inp >> temp;
	s.length = strlen(temp);
	delete[] s.ptr;
	s.ptr = new char [s.length + 1];
	strcpy_s(s.ptr, s.length + 1, temp);
	return inp;
}
ostream& operator<<(ostream& out, const String& s)
{
    out<<s.ptr;
    return out;
}
String String::to_string(int num, int width)
{
	char temp[MAX]{};
	int cnt = 0;
	while (num != 0)
	{
		int t = num % 10;
		temp[cnt++] = char(t + int('0'));
		num = num / 10;
	}
	for (int i = 0; i <= (cnt - 1) / 2; i++)
	{
		char t = temp[i];
		temp[i] = temp[cnt - 1 - i];
		temp[cnt - 1 - i] = t;
	}
	if (width > cnt)
	{
		int pad = width - cnt;
		for (int i = cnt-1; i >=0; i--)
		{
			temp[i + pad] = temp[i];
		}
		for (int i = 0; i < pad; i++)
		{
			temp[i] = '0';
		}
	}
	return String(temp);
}
