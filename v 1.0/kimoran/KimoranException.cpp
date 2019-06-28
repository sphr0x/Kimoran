#include "KimoranException.h"

std::string KimoranException::getError() const
{
	return m_error;
}

void KimoranException::setError(std::string err)
{
	this->m_error = err;
}

KimoranException::KimoranException(std::string error)
	:m_error(error)
{
}

KimoranException::KimoranException()
{
}


KimoranException::~KimoranException()
{
}
