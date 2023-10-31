#ifndef STRING_H
#define STRING_H
#include <cstring>
#include <iostream>
class String
{
    friend std::istream& operator>>(std::istream&, String&);
    friend std::ostream& operator<<(std::ostream&, const String&);
    public:
        String(int=0);
		String(const char*);
        String(const String&);
        ~String();
		const String& operator=(const String&);
		operator char* () const;
		bool operator<(const String&) const;
        bool operator==(const String&) const;
		bool operator!=(const String& s) const;
        char& operator[](int);
        const char& operator[](int) const;
		void ClearSpace();
	private:
		char *ptr;
		int length;
};
#endif