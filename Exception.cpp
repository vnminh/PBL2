#include "Exception.h"
Exception::Exception(const String & mess)
	: Message(mess)
{}
Exception::~Exception()
{}
const String& Exception::What() const
{
	return this->Message;
}