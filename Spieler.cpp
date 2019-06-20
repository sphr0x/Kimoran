#include "Spieler.h"



int Spieler::spielzug(Graph& karte, std::deque<Node*>& path)
{

	UI temp;
	Node* ziel = nullptr;
	int choose;
	double kosten;
	//int pastgold = this->geld;

	while (1) {																			// hier fehler !!!!
		choose = 1;
		std::cout << "spielzug p1,wohin?" << std::endl;	// display options
		for (auto node : karte.getNodes()) {
			std::cout << "[ " << choose++ << " ] : " << node->getID() << std::endl;
		}
		std::cin >> choose;
		choose = temp.checkInput(choose);	// evtl gehts mit UI nicht -> checkinput in spieler
		ziel = setLocation(choose, karte);  // hier ziel gesetzt
		if (ziel->getID() == this->standort->getID()) {	// check ob ziel == standort
			std::cout << "Auf der Stelle stehen macht weder Spass, noch wird man dadurch reich!" << std::endl;	
		}
		else {
			break;
		}
	}
		kosten = karte.findShortestPathDijkstra(path, *this->standort, *ziel);	// testen ob zug geht
		if (kosten <= this->geld) {			// wenn ja
			this->standort = ziel;			// neuer standort = altes ziel
			setGeld(this->geld - kosten);	// geld anpassen
			if (temp.foundTreasure(*ziel)) {									// testen ob schatz
				std::cout << this->name << " hat den Schatz gefunden!!!" <<
					"Es waren unglaubliche X Taler in der Truhe. Wahnsinn !" << std::endl; // X hier rand generator ! OPTIONAL
				temp.foundTreasure(*ziel);
				return 0;						// komplett end | mit return; oder foundTreas... ?
			}
			/*			nur für zielort lager
			else if(isLager(*ziel,karte)) {	// wenn lager
				this->geld += ziel->getGold();	// playergeld anpassen
				std::cout << "Lager gefunden mit " << this->geld - pastgold << "Taler! Famos!" << std::endl;
				ziel->setGold(0);	// lager leeren
			}
			*/
			//für alle lager auf der strecke
			while (!path.empty()) {			// wenn lager
				isLager2(path);
			};
			printTurn(path, kosten, *ziel);	// route anzeigen
			deleteTurn(path);
		}
		else {
			std::cout << this->name << ", also DU, hast keinen mueden Penny mehr...\n" <<
				"Die uebermaechtige KI gewinnt!\n\n\n" << "Vielen Dank fuers Spielen !" << std::endl;
			return 0;
		}
		return 1;
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
	return standort;
}

void Spieler::setStandort(Node& location)
{
	this->standort = &location;
}

Node * Spieler::setLocation(int & location, Graph& karte)		// works maybe only with graph g* karte
{
	Node* loc;
	auto it2 = std::next(karte.getNodes().begin(), location - 1); // sync nodes to position
	return loc = *it2;
}

bool Spieler::isLager(Node& ziel, Graph& karte)
{
	//int pastgold = this->geld;
	if (karte.findNode(ziel.getID())->getGold() != 0) {
		return true;
	}
	/*
	for (auto node : karte.getNodes()) {
		if (node->getID != 0){
			this->geld += node->getGold();
			std::cout << this->geld - pastgold << "Taler! Famos!" << std::endl;
			pastgold = this->geld;
			node->setGold(0);
			return true;
		}
		
	}*/

	return false;
}
void Spieler::isLager2(std::deque<Node*>& path)
{
	//int pastgold = this->geld;
	for (auto node : path) {
		if (node->getGold() != 0) {
			std::cout << node->getGold() << " Taler gefunden. Famos! " << std::endl;
			this->geld += node->getGold();		// playergeld anpassen
			node->setGold(0);					// lager leeren
			
			/*
			this->geld += node->getGold();
			std::cout << this->geld - pastgold << "Taler! Famos!" << std::endl;
			pastgold = this->geld;
			node->setGold(0);
			return true;*/
		}
		path.pop_front();
	}
}
 void Spieler::printTurn(std::deque<Node*>& actualRoute, double kosten, Node& dest) {
	std::cout << "\n\t\t\t Zurueckgelegter Pfad: ";
	for (auto node : actualRoute) {
		if (dest.getID() == node->getID()) {
			std::cout << node->getID() << "(= aktueller Standort)" << std::endl;
		}
		else {
			std::cout << node->getID() << " --> ";
		}
	}
	std::cout << "\n";
	std::cout << "\t\t\tAusgegebene Taler: " << kosten  << std::endl;
	std::cout << "\t\t\tVerbleibene Taler: " << this->geld << std::endl;
}
 void Spieler::deleteTurn(std::deque<Node*>& actualRoute) {
	 actualRoute.clear();
 }
/*
bool Spieler::foundTreasure(Node& location)
{
	if (location.isGoal()) {
		return true;
	}
	return false;
}*/
Spieler::Spieler(Node& start, int taler,std::string eingabe)
	:geld(taler), standort(&start), name(eingabe)
{

}


Spieler::~Spieler()
{
}
