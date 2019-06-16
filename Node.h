#ifndef NODE_H
#define NODE_H

#include <string>
#include <list>
#include <iostream>


// forward-deklaration

class Edge;

class Node
{
public:
	Node();
	Node(std::string id) : m_id(id) { s_numInstances++; }
	virtual ~Node() { /*std::cout << m_id << " deleted!" << std::endl;*/ }

	std::string getID() const { return m_id; }
	std::list<Edge*>& getOutEdges() { return m_outgoingEdges; }
	std::list<Edge*>& getInEdges() { return m_incomingEdges; }
	void setGold(int value);							// for kimoran
	int getGold();
	void setGoal(bool treasure);
	bool isGoal() { return goal; };
private:
	std::string m_id;
	std::list<Edge*> m_outgoingEdges;
	std::list<Edge*> m_incomingEdges;
	static int s_numInstances;
	int gold = 0;										// for kimoran
	bool goal = 0;
};

#endif