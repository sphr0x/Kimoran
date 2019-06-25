#include "Verbindung.h"

Verbindung::Verbindung(std::string newID, Node & rSrc, Node & rDst)
:Edge(rSrc, rDst), m_mid(newID), m_kosten(3) {
	if ((newID == "Bruecke") || (newID == "Faehre"))
		this->m_kosten = 3;
	if (newID == "Tunnel")
		this->m_kosten = 5;
}
Verbindung::~Verbindung()
{
}
