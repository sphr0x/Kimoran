#include "Verbindung.h"



Verbindung::Verbindung(char id, Node & rSrc, Node & rDst) 
	:Edge(rSrc, rDst), id('B'),m_kosten(3){
	if (id == ('B' || 'F')) {
		this->m_kosten = 3;
	}
	else if (id == 'T')
		this->m_kosten = 5;
}


Verbindung::~Verbindung()
{
}
