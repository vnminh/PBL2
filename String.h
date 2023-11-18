#ifndef STRING_H
#define STRING_H
#include <cstring>
#include <iostream>
class String
{
	friend String MoneyFormat(const String &);
	friend std::istream& operator>>(std::istream&, String&);
    friend std::ostream& operator<<(std::ostream&, const String&);
    public:
		static String to_string(int, int = 0);
        String();
		String(const char*);
        String(const String&);
        ~String();
		const String& operator=(const String&);
		operator char* ();
		operator const char* () const;
		bool operator<(const String&) const;
		bool operator==(const String&) const;
		bool operator!=(const String&) const;
		const String operator+(const String&) const;
        char& operator[](int);
        const char& operator[](int) const;
		long long to_ll() const;
		void Erase(int);
		void GetLine(std::istream&, char = '\n');
		int GetLength() const;
		void DeleteFirstSpace();
		void DeleteLastSpace();
		void Insert(const int &, const char&);
		String SubStr(const int&, const int &) const;
	private:
		char *ptr;
		int length;
};
#endif