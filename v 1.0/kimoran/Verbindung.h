#pragma once
#include <Edge.h>

class Verbindung :
	public Edge
{
private:
	int m_kosten;
	std::string m_mid;
public:
	double getWeight() { return m_kosten; };					// not const -> virtual from class Edge is not const
	std::string getMID()const { return m_mid; };						
	Verbindung(std::string newID, Node & rSrc, Node & rDst);
	~Verbindung();
};

