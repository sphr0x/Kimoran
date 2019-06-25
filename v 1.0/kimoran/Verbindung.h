#pragma once
#include <Edge.h>

class Verbindung :
	public Edge
{
private:
	int m_kosten;
	std::string m_mid;
public:
	double getWeight() { return m_kosten; };
	std::string getMID() { return m_mid; };
	Verbindung(std::string newID, Node & rSrc, Node & rDst);
	~Verbindung();
};

