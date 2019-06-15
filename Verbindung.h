#pragma once
#include <Edge.h>
class Verbindung :
	public Edge
{
private:
	int m_kosten;					//		3		|5			|3
	char id;					// b = brücke | t = tunnel | f = fähren
	std::string name;
public:
	double getWeight() { return m_kosten; };
	Verbindung(char id, Node & rSrc, Node & rDst);
	~Verbindung();
};

