#include <string>
#include <sstream>
#include <iomanip>
#include <cctype>
#include "Node.h"

// static initialization
int Node::s_numInstances = 0;

Node::Node()
{
	s_numInstances++;
	std::stringstream s;
	s << "Node_" << std::setw(4) << std::setfill('0') << s_numInstances;
	m_id = s.str();
}

void Node::setGold(int value)
{
	this->gold = value;
}

int Node::getGold()
{
	return this->gold;
}

void Node::setGoal(bool treasure)
{
	this->goal = treasure;
}
