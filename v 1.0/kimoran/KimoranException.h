#pragma once
#include <string>

class KimoranException : std::exception
{
private:
	std::string m_error;
public:
	std::string getError() const;
	void setError(std::string err);
	KimoranException(std::string error);
	KimoranException();
	~KimoranException();
};

