#include "Graph.h"
#include <list>
#include <fstream>
#include <algorithm>
#include <limits>
#include <iostream>
#include <map>


//---------------------------------------------------------------------------------------------------------------------

Node* Graph::findNode(const std::string& id){
	Node n1(id);

	for (auto it = m_nodes.begin();it != m_nodes.end();++it) {					// works
		if (n1.getID() == (*it)->getID()) {
			std::cout << "found: " << (*it)->getID() << std::endl;
			return *it;
		}
	}
	return nullptr;

    // TEST:
    // Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes und Edges in main.cpp erstellen
    // und anschließend ein paar Nodes im Graph suchen.
    // Prüfen Sie, ob der Node gefunden wurden und geben Sie die ID auf der Kommandozeile aus!
}


//---------------------------------------------------------------------------------------------------------------------

Node& Graph::addNode(Node* pNewNode){

	// Überprüfen Sie, ob schon ein Node mit der gegeben id im Graph vorhanden ist!
	// Falls ja:
	//  - Exception werfen
	// Falls nein:
	//  - den neuen Node 'pNewNode' in m_nodes einfügen
	//  - Referenz auf den neuen Node zurück geben

	for (auto it = m_nodes.begin(); it != m_nodes.end(); ++it) {				// works
		if (pNewNode->getID() == (*it)->getID()) {
			throw("exc");
		}
	}
	m_nodes.push_back(pNewNode);
	return *pNewNode;
	
    // TEST:
    // Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes in main.cpp erstellen
    // Testen Sie mit der Funktion 'findNode', ob die hinzugefügten Nodes im Graph vorhanden sind.
}


//---------------------------------------------------------------------------------------------------------------------

Edge& Graph::addEdge(Edge* pNewEdge){
    // - die neue Edge 'pNewEdge' in m_edges einfügen
    // - Referenz auf die neue Edge zurück geben
	// - Testen Sie ob der Source- und Destination-Node von 'pNewEdge' schon im Graph vorhanden ist.
	// -> fügen Sie diese Nodes hinzu, falls nicht (nutzen Sie dafür Graph::addNode)
	
	m_edges.push_back(pNewEdge);
	if(!isInQueue(pNewEdge->getSrcNode(),m_nodes))								// works
	addNode(&pNewEdge->getSrcNode());
	if (!isInQueue(pNewEdge->getDstNode(), m_nodes))
	addNode(&pNewEdge->getDstNode());

	return *pNewEdge;

    // TEST:
    // Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes und Edges in main.cpp erstellen
    // Testen Sie mit der Funktion 'findEdges', ob die hinzugefügten Edges im Graph vorhanden sind.
}


//---------------------------------------------------------------------------------------------------------------------

Graph::~Graph(){
    // - soll alle Edges im Graph löschen (delete)
    // - soll alle Nodes im Graph löschen (delete)

	for (auto edge : m_edges) {													// works
		delete edge;
	}
	for (auto node : m_nodes) {
		delete node;
	}
	std::cout << " Graph destroyed !" << std::endl;
}


//---------------------------------------------------------------------------------------------------------------------
void Graph::remove(Node& rNode){
    // - alle Edges, die mit rNode verbunden sind, müssen entfernt werden!
	// - finden sie den Pointer mit der Adresse von 'rNode' in m_nodes.
    // 		- der Pointer auf rNode soll aus m_nodes entfernt werden!
    // 		- der Pointer auf rNode muss mit 'delete' freigegeben werden!
	
	m_nodes.remove(&rNode);													// works
	delete(&rNode);

    // TEST:
    // Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes und Edges in main.cpp erstellen
    // und anschließend einzelne Nodes wieder löschen.
    // Testen Sie mit der Funktion 'findNode', ob die gelöschten Nodes noch im Graph vorhanden sind.
}


//---------------------------------------------------------------------------------------------------------------------

void Graph::remove(Edge& rEdge){
    // - der Pointer auf rEdge muss aus m_edges entfernt werden!
    // - der Pointer auf rEdge muss mit 'delete' freigegeben werden!

	m_edges.remove(&rEdge);													// works
	delete& rEdge;

    // TEST:
    // Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes und Edges in main.cpp erstellen
    // und anschließend einzelne Edges wieder löschen.
    // Testen Sie mit der Funktion 'findEdges', ob die gelöschten Edges noch im Graph vorhanden sind.
}


//---------------------------------------------------------------------------------------------------------------------

std::vector<Edge*> Graph::findEdges(const Node& rSrc, const Node& rDst){

    // - findet alle edges, mit rSrc als Source-Node und rDst als Destination-Node.
    // - füge die Zeiger der Edges in den vector 'ret' ein.
	std::vector<Edge*> ret;

  	for (auto it = m_edges.begin(); it != m_edges.end();++it) {								// works
		if ( ( (*it)->isConnectedTo(rSrc) ) && ( (*it)->isConnectedTo(rDst) ) ) { 
			ret.push_back(*it);
		}
	}
    return ret;

    // TEST:
    // Testen Sie die Funktion, indem Sie indem Sie einen Graph mit ein paar Nodes und Edges in main.cpp erstellen
    // und anschließend ein paar Edges im Graph suchen.
    // Prüfen Sie, ob Edges gefunden wurden und geben Sie die gefunden Edges auf der Kommandozeile aus!
}

//---------------------------------------------------------------------------------------------------------------------

double Graph::findShortestPathDijkstra(std::deque<Node*>& rPath, Node& rSrcNode, Node& rDstNode){
										/*
	// idee :
	{
	2x map ( dist, prev )
	1x list / queue _/ p-queue

	for(auto node:nodes){
	alle nodes mit wert in maps einfügen
	alle nodes in list
	}
	dist v source = 0

	while(!list not empty){
	u = node wiht min dist (helper function) // oder sort mintomax und pop front  // oder priority queue
	queue.remove(u)

	for(auto neighbor: neighbor(u)){
	dist=dist(u)+mninweg(neighbor->u)
	if(dist < dist(v)){
	dist(v)=dist
	prev(neighbor) = u
	}
	}
	}
	return dist[destination]
	}									*/

	std::list<Node*> queue; 
	std::map<Node*, double> distance;											// works
	std::map<Node*, Node*> previous;

	for (auto node : m_nodes) {
		queue.push_back(node);
		distance[node] = 10000;
		previous[node] = nullptr;
	}
	distance[&rSrcNode] = 0;
	while (!queue.empty()) {
		Node* u = minHelper(distance, queue);
		queue.remove(u);

		for (auto v : neighborHelper(*u)) {
			double minDistance = distance[u] + minVector(*u, *v);
			if (minDistance < distance[v]) {
				distance[v] = minDistance;
				previous[v] = u;
			}
		}
	}
	Node* dest = &rDstNode;
	rPath.push_front(dest);

	while (dest != &rSrcNode) {		
		dest = previous[dest];
		if (dest != nullptr) {
			rPath.push_front(dest);
		}
		else break;
	}
	return distance[&rDstNode];
}

	// Helper for Dijkstra // working

Node* Graph::minHelper(std::map<Node*, double>& map, std::list<Node*>& list){
	double dist = 10001;
	Node* key = nullptr;

	for (auto iwas : map) {
		if ((iwas.second < dist) && (isInQueue(*iwas.first,list))) {
			dist = iwas.second;
			key = iwas.first;
		}
	}
	return key;
}

std::list<Node*> Graph::neighborHelper(Node& node){
	std::list<Node*> result;

	for (auto edge : node.getOutEdges()) {
		if (!isInQueue(edge->getDstNode(), result)) {
			result.push_back(&edge->getDstNode());
		}
	}
	return result;
}

double Graph::minVector(Node& source, Node& dest){
	double result = 10002;
	std::vector<Edge*> edgeV = findEdges(source, dest);

	for (auto edge : edgeV) {
		if (result > edge->getWeight()) {
			result = edge->getWeight();
		}
	}
	return result;
}

bool Graph::isInQueue(Node& key, std::list<Node*> queue){
	for (auto search : queue) {
		if (search == &key) {
			return  true;
		}
	}
	return false;
}


//---------------------------------------------------------------------------------------------------------------------

