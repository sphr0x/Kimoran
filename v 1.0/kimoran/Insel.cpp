#include "Insel.h"



void Insel::setGold(int value)
{
	this->m_gold = value;
}

int Insel::getGold()
{
	return this->m_gold;
}

void Insel::setGoal(bool treasure)
{
	this->m_goal = treasure;
}

Insel::Insel(std::string id)
	: Node(id),m_gold(0),m_goal(0)
{
}


Insel::~Insel()
{
}
