#pragma once
#include <Node.h>

class Insel :
	public Node
{
private:
	int m_gold;										// for kimoran
	bool m_goal;
public:
	void setGold(int value);							// for kimoran
	int getGold();
	void setGoal(bool treasure);
	bool isGoal() { return m_goal; };
	Insel(std::string id);
	Insel() {};
	~Insel();
};

