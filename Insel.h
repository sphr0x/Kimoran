#pragma once
#include <Node.h>

class Insel :
	public Node
{
private:
	int taler;
	std::string ziel;
public:
	bool hasStorage(int geld);  // alles weg , und funktionen in Node adden
	void setTaler(int geld);
	int getTaler();
	void setGoal(std::string goal);
	std::string getGoal() { return ziel; };
	Insel(std::string, int geld = 0);
	~Insel();
};

