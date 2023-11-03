#ifndef EXCEPTION_H
#define EXCEPTION_H
#include "String.h"
class Exception
{
	public:
		Exception(const String &);
		~Exception();
		const String& What() const;
	private:
		const String Message;
};
#endif