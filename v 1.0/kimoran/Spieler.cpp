#include "Spieler.h"

void Spieler::setName(std::string name)
{
	this->m_name = name;
}
void Spieler::setGeld(int gold)
{
	this->m_geld = gold;
}
Insel * Spieler::getStandort()const
{
	return this->m_standort;
}
void Spieler::setStandort(Insel& location)
{
	this->m_standort = &location;
}
Insel * Spieler::setLocation(int & location, Graph& karte)
{
	Insel* loc;
	auto it2 = std::next(karte.getNodes().begin(), location - 1);		
	loc = dynamic_cast<Insel*>(*it2);
	return loc;
}
int Spieler::lootLagerOnPath(std::deque<Insel*>& path)
{
	int change = 0;
	for (auto node : path) {
		if (node->getGold() != 0) {
			change += node->getGold();
			this->m_geld += node->getGold();								
			node->setGold(0);											
		}
		path.pop_front();
	}
	return change;
}
 void Spieler::printTurn(std::deque<Insel*>& actualRoute, double kosten, Insel& dest) {
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
	std::cout << "[ Verbleibene Taler: " << this->m_geld <<" ]"<< std::endl;
}
 void Spieler::deleteTurn(std::deque<Insel*>& actualRoute) {
	 actualRoute.clear();
 }
Spieler::Spieler(Insel& start, int taler,std::string eingabe)
	:m_geld(taler), m_standort(&start), m_name(eingabe){

}


Spieler::~Spieler()
{
}
