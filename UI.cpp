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
	printMenu();

	while ((!foundTreasure(*location)) || mensch.getGeld()==0 || ki.getGeld()==0) {
		std::cout << "Bitte Aktion waehlen:" << std::endl;
		std::cin >> choose;
		choose = checkInput(choose);
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
			//mensch.walkTo(turn);// walkTo in Spieler.h schreiben
				if (isLager(*turn)) {
					mensch.setGeld(turn->getLagerGeld()); // get /  fkt schreiben in node bzw Insel
					turn->setLagerGeld(0);
				}
				if (foundTreasure(*turn)) {
					std::cout << mensch.getName() << " hat gewonnen. juhu!" << std::endl;
					// hier return; bzw ende init iwie
				}
				printTurn(path,kosten,*turn,mensch);
				mensch.setStandort(*turn);
			}
			deleteTurn(path);
			
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
		case 5:
			printMenu();
			system("clear");
			std::cout << "Bildschirm bereinigt!" << std::endl;
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
	// hier string zerteilen und check
	/*
	while (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(50, '\n');
		if (choose == compare) {
			std::cerr << "\t\t\tFehler: Sie befinden sich bereits an diesem Ort - bitte nochmal! " << std::endl;
			std::cout << "\tEingabe: ";
		}
		else {
			std::cerr << "\t\t\tFehler: Bitte den Namen einer Textdatei eingeben: ( name.txt )" << std::endl;
			std::cout << "\tEingabe: ";
		}
		std::cin >> input;
		
	}*/
	return input;
}

int UI::checkInput(int input)
{
	while ((input < 0) || (std::cin.fail())) {
		std::cin.clear();
		std::cin.ignore(30, '\n');
		std::cerr << "\t\t\tFehler: Bitte eine positive Zahl eingeben: " << std::endl;
		std::cout << "\tEingabe: ";
		std::cin >> input;
	}
		return input;
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
	if (location.getID == "Schatz") // not ID but Vari bool m_schatz = true
		return true;
	return false;
}

void UI::printMenu()
{
	// format via stringstream !
	Sleep(500);
	std::cout << "\n\t\t\t    ->  [            Schatzsuche in Kimoran            ]  <- \n" << std::endl;
	Sleep(500);
	std::cout << "\n\t\t\t    ->  [    Bitte Aktion via Nummerierung waehlen   ]  <- \n\n" << "\t\t\t[1] ->  [        Karte von Datei einlesen        ]  <-\n";
	Sleep(500);
	std::cout << "\t\t\t[2] ->  [        Karte & Verbindungen Anzeigen       ]  <-\n" << "\t\t\t[3] ->  [                   Spielzug                  ]  <-\n";
	Sleep(500);
	std::cout << "\t\t\t[4] ->  [             Spiel beenden           ]  <-\n" << "\t\t\t[5] ->  [                  Bildschirm bereinigen & Auswahl anzeigen                  ]  <-\n" << std::endl;
}

bool UI::isLager(Node& lager)
{
	// evtl vererbung node auf insel mit m_vari bool lager
	// und 2 x static int für die 2 werte
	/*
	if (lager.getLagerState())
	{
		lager.sethiddenmoney(0);
		return true;
	}*/
	return false;
}

void UI::printTurn(std::deque<Node*>& actualRoute, double kosten, Node& dest, Spieler mensch) {
	std::cout << "\n\t\t\tRoute: ";
	for (auto node : actualRoute) {
		if (dest.getID() == node->getID()) {
			std::cout << node->getID() << "(= Zielort)" << std::endl;
		}
		else {
			std::cout << node->getID() << " --> ";
		}
	}
	std::cout << "\n";
	std::cout << "\t\t\tAusgegebene Taler: " << kosten  << std::endl;
	std::cout << "\t\t\tVerbleibene Taler: " << mensch.getGeld() << std::endl;
}

void UI::deleteTurn(std::deque<Node*>& actualRoute){
	actualRoute.clear();
}

UI::UI()
{
}


UI::~UI()
{
}
