#pragma once
#include <Edge.h>
#include <Graph.h>
#include <string>

class Route :
	public Edge
{
private:
	double m_distance;
public:
	Route(Node& rSrc, Node& rDst, double distance);
	Route(Node* Src, Node* Scr, double distance);
	Route(std::string src, std::string dst, double distance);
	std::string toString2();	// test
	double getWeight();  // fkt nicht const, da sonst nicht equal -> no virtual
	~Route();
};

