#pragma once
#include <Edge.h>
class Verbindung :
	public Edge
{
private:
	int m_kosten;					//		3		|5			|3
	char id;					// b = brücke | t = tunnel | f = fähren
public:
	double getWeight() { return m_kosten; };
	char getVID() { return id; };
	Verbindung(char id, Node & rSrc, Node & rDst);
	~Verbindung();
};

