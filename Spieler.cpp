#include "Spieler.h"



void Spieler::spielzug()
{
}

void Spieler::setName(std::string name)
{
	this->name = name;
}

void Spieler::setGeld(int gold)
{
	this->geld = gold;
}

Node * Spieler::getStandort()
{
	return nullptr;
}

Spieler::Spieler(int taler,Node& start,std::string eingabe)
	:geld(taler), standort(&start), name(eingabe)
{

}


Spieler::~Spieler()
{
}
