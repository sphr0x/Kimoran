#include "Edge.h"
#include <assert.h>
#include <list>
#include <iostream>
//---------------------------------------------------------------------------------------------------------------------


Edge::Edge(Node& rSrc, Node& rDst) : m_rSrc(rSrc), m_rDst(rDst)
{
    // fügt die Edge (this) in m_outgoingEdges des Source-Node ein.
    // fügt die Edge (this) in m_incomingEdges des Destination-Node ein.
	// Hinweis: die Funktionen Node::getOutEdges() und Node::getInEdges() verwenden!

	rSrc.getOutEdges().push_back(this);											// works
	rDst.getInEdges().push_back(this);

	//std::cout << "K" << std::endl; 
    // TEST:
    // Erstellen Sie in main.cpp eine Edge und prüfen Sie, ob die Edge
    // korrekt in m_outgoingEdges bzw. m_incomingEdges eingefügt wurde!			// works
}


//---------------------------------------------------------------------------------------------------------------------

Edge::Edge(const Edge& rOther) : m_rSrc(rOther.m_rSrc), m_rDst(rOther.m_rDst)
{
    // macht das Selbe wie 'Edge(Node& rSrc, Node& rDst)'

	rOther.m_rSrc.getOutEdges().push_back(this);								// works
	rOther.m_rDst.getInEdges().push_back(this);
	//std::cout << "CK" << std::endl;
}


//---------------------------------------------------------------------------------------------------------------------

Edge::~Edge()
{
    // - entfernt die Edge (this) aus m_outgoingEdges im Source-Node
    // - entfernt die Edge (this) aus m_incomingEdges im Destination-Node

	m_rSrc.getOutEdges().remove(this);											// works
	m_rDst.getInEdges().remove(this);
	//std::cout << "DEST" << std::endl;

    // TEST:																 
    // Erstellen Sie in main.cpp drei Edges, die jeweils den selben Source- und Destination-Node haben.		// works
    // Löschen Sie eine Edge wieder!
    // Prüfen Sie, ob die gelöschte Edge aus m_outgoingEdges bzw. m_incomingEdges entfernt wurde!
    // Hinweis: arbeiten Sie mit 'new' und 'delete'!
}


//---------------------------------------------------------------------------------------------------------------------

bool Edge::isConnectedTo(const Node& rNode) const
{
    // - gibt true zurück, wenn rNode entweder m_rSrc und m_rDst ist.
    // Hinweis: Adressen vergleichen, um zu gucken, ob es wirklich das selbe Objekt ist!
	const Node *ptr1 = &rNode;																// works
	const Node *ptr2 = &m_rSrc;
	const Node *ptr3 = &m_rDst;

	if ((ptr1 == ptr2)||(ptr1 == ptr3)) {
		//std::cout << "connected" << std::endl;
		return true;
	}
	//std::cerr << "NOT connected" << std::endl;
    return false;
}


//---------------------------------------------------------------------------------------------------------------------

std::string Edge::toString() const
{
    std::string result;
    result = m_rSrc.getID() + " -> " + m_rDst.getID();
    return result;
}


//---------------------------------------------------------------------------------------------------------------------
