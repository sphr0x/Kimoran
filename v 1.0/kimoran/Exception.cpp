#include "Exception.h"

std::string Exception::getError() const
{
	return m_error;
}

void Exception::setError(std::string err)
{
	this->m_error = err;
}

Exception::Exception(std::string error)
	:m_error(error)
{
}

Exception::Exception()
{
}


Exception::~Exception()
{
}
