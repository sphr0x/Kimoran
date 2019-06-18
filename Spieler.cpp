#include "Spieler.h"



Node* Spieler::spielzug()
{
	// aus UI extrahieren

	/*
	Node* zug = nullptr;
	zug = iwas 
	void setGeld(int gold);
	void setStandort(Node& location);
	
	return zug 
	*/
}

void Spieler::setName(std::string name)
{
	this->name = name;
}

void Spieler::setGeld(int gold)
{
	this->geld += gold;
}

Node * Spieler::getStandort()
{
	return nullptr;
}

void Spieler::setStandort(Node& location)
{
	this->standort = &location;
}

Spieler::Spieler(Node& start, int taler,std::string eingabe)
	:geld(taler), standort(&start), name(eingabe)
{

}


Spieler::~Spieler()
{
}
