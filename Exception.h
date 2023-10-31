#ifndef EXCEPTION_H
#define EXCEPTION_H
#include "String.h"
class Exception
{
	public:
		Exception(const String &);
		~Exception();
		virtual const String What() const;
	private:
		const String Message;
};
#endif