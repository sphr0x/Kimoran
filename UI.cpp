#include "UI.h"



void UI::dateiEinlesen()
{
}

void UI::dateiSchreiben()
{
}

void UI::menu(Graph& karte,Spieler bla, Node& schatz,Node& start)
{
	Spieler mensch(30,start);
	Spieler ki(30,start);
	int choose;
	std::string filename;
	Node* turn = nullptr;
	Node* location = nullptr;
	std::deque<Node*> path;
	double kosten;

	std::cout << "ihr name";
	std::cin >> filename;
	//hier checkinput auf "kein leerzeichen" ?
	setnameofPlayer(mensch,filename);
	while ((!foundTreasure(*location)) || mensch.getGeld()==0 || ki.getGeld()==0) {
		switch (choose) {

		case 1:
			// input filename freely
			std::cout << "bitte file" << std::endl;
			std::cin >> filename;
			filename = checkInput(filename);		// checkinput schreiben
			// open file -> read graph
			dateiEinlesen();						// schreiben
			break;
		case 2:
			// display karte -> node names,  neighbors of nodes & which kind, no lager/schatz
			printMap(karte);						// schreiben
			break;
		case 3:
			// next turn
			std::cout << "spielzug p1" << std::endl;
			std::cin >> choose;
			choose = checkInput(choose);
			// input zielnode -> dijkstra
			kosten = karte.findShortestPathDijkstra(path,*location,*turn);
			/* if(genug taler){
			walk/calculate route 
			-> if(lager){
			collect Taler
			if(found schatz){
			output "won" + end game 
			} 
			-> get route ->
			} */

			if (kosten <= mensch.getGeld()) {
			//walk
				if () {}										// HIER WEITER !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			}
			/* input zielnode für KI == random  -> dijkstra
			-> if(genug taler){
			walk/calculate route 
			-> if(lager){
			collect Taler}
			if(found schatz){
			output "won" + end game 
			} 
			*/
			break;
		case 4:
			//beenden
			break;
		default:

			break;
		}
	}
}

void UI::karte(Graph& karte)
{
	// read from file - works
	std::ifstream datei("Neues Textdokument.txt");
	std::string line;
	//datei.open("Neues Textdokument.txt"); anscheinend nicht nötig
	if (datei.is_open()&& !(datei.eof())) {
		while (getline(datei, line)) {
			std::cout << line << std::endl;
		}
	}
	else std::cout << "file was closed" << std::endl;

	datei.close();


}

std::string UI::checkInput(std::string input)
{	
	// check auf string + "." + "txt"
	/* 
	while (std::cin.fail() || choose < 1 || choose > 8 || choose == compare) {
		std::cin.clear();
		std::cin.ignore(30, '\n');
		if (choose == compare) {
			std::cerr << "\t\t\tFehler: Sie befinden sich bereits an diesem Ort - bitte nochmal! " << std::endl;
			std::cout << "\tEingabe: ";
		}
		else {
			std::cerr << "\t\t\tFehler: Bitte eine valide Ziffer eingeben: " << std::endl;
			std::cout << "\tEingabe: ";
		}
		std::cin >> choose;
		
	}
	return choose;
	*/
	return std::string();
}

int UI::checkInput(int input)
{
	return int;
}

void UI::printMap(Graph & karte)
{
	// display karte -> node names,  neighbors of nodes & which kind, no lager/schatz
	// == print nodes, edges , no treasure , no camp
}

void UI::setnameofPlayer(Spieler & mensch, std::string name)
{
	mensch.setName(name);
}

bool UI::foundTreasure(Node& location)
{
	if (location.getID == "Schatz")
		return true;
	return false;
}

UI::UI()
{
}


UI::~UI()
{
}
