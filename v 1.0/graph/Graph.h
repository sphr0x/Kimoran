#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <deque>
#include <string>
#include "Node.h"
#include "Edge.h"
#include <map>

class Graph
{
public:
	virtual ~Graph();

	Node& addNode(Node* pNewNode);
	Edge& addEdge(Edge* pNewEdge);
	void remove(Node& rNode);
	void remove(Edge& rEdge);
	const std::list<Node*>& getNodes() { return m_nodes; }
	const std::list<Edge*>& getEdges() { return m_edges; }
	Node* findNode(const std::string& id);
	std::vector<Edge*> findEdges(const Node& rSrc, const Node& rDst);
	double findShortestPathDijkstra(std::deque<Node*>& rPath, Node& rSrcNode, Node& rDstNode);
	// helper for dijkstra
	Node* minHelper(std::map<Node*,double>& map, std::list<Node*>& list );
	std::list<Node*> neighborHelper(Node& node);
	double minVector(Node& source, Node& dest);
	bool isInQueue(Node& key, std::list<Node*> queue);

protected:
	std::list<Node*> m_nodes;
	std::list<Edge*> m_edges;
};


//---------------------------------------------------------------------------------------------------------------------

#endif