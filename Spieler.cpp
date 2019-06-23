#include "Spieler.h"

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
	return standort;
}
void Spieler::setStandort(Node& location)
{
	this->standort = &location;
}
Node * Spieler::setLocation(int & location, Graph& karte)
{
	Node* loc;
	auto it2 = std::next(karte.getNodes().begin(), location - 1);		// sync nodes to position
	return loc = *it2;
}
void Spieler::isLager2(std::deque<Node*>& path)
{
	for (auto node : path) {
		if (node->getGold() != 0) {
			std::cout << "[ " << node->getGold() << " Taler gefunden. Famos!! ]\n" << std::endl;
			this->geld += node->getGold();								// playergeld anpassen
			node->setGold(0);											// lager leeren
		}
		path.pop_front();
	}
}
 void Spieler::printTurn(std::deque<Node*>& actualRoute, double kosten, Node& dest) {
	std::cout << "\n[ Zurueckgelegter Pfad: ";
	for (auto node : actualRoute) {
		if (dest.getID() == node->getID()) {
			std::cout << node->getID() << "(= neuer Standort) ]" << std::endl;
		}
		else {
			std::cout << node->getID() << " --> ";
		}
	}
	std::cout << "\n";
	std::cout << "[ Ausgegebene Taler: " << kosten <<" ]" << std::endl;
	std::cout << "[ Verbleibene Taler: " << this->geld <<" ]"<< std::endl;
}
 void Spieler::deleteTurn(std::deque<Node*>& actualRoute) {
	 actualRoute.clear();
 }
Spieler::Spieler(Node& start, int taler,std::string eingabe)
	:geld(taler), standort(&start), name(eingabe){

}


Spieler::~Spieler()
{
}
