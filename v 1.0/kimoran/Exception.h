#pragma once
#include <string>

class Exception
{
private:
	std::string m_error;
public:
	std::string getError() const;
	void setError(std::string err);
	Exception(std::string error);
	Exception();
	~Exception();
};

