#include "UI.h"



void UI::dateiEinlesen()
{
}

void UI::dateiSchreiben()
{
}

void UI::menu(/*Graph& karte,Spieler bla, Node& schatz,Node& start*/)
{
	Graph* karte = new Graph;
	int choose;
	std::string filename = "C23_Projekt_19SS_Inseln.txt";
	Node* turn = nullptr;
	Node* location = nullptr;
	std::deque<Node*> path;
	double kosten;
	std::vector<Spieler*> players; // pos 1 mensch pos 2 ki

	printIntro();
	printInfo();
	readMAP(*karte, filename, players);

	std::cout << "ihr name";
	std::cin >> filename;
	//hier checkinput auf "kein leerzeichen" ?
	
	//setnameofPlayer(mensch,filename);			// auf mensch via vector player zugreifen

	printMenu();

	while ((!foundTreasure(*location)) || mensch.getGeld()==0 || ki.getGeld()==0) { // auf spieler via vector
		std::cout << "Bitte Aktion waehlen:" << std::endl;
		std::cin >> choose;
		choose = checkInput(choose);
		switch (choose) {

		case 1:
			// input filename freely
			std::cout << "bitte file" << std::endl;
			std::cin >> filename;
			filename = checkInput(filename);		// checkinput schreiben
			readMAP(*karte, filename, players);
			break;
		case 2:
			// display karte -> node names,  neighbors of nodes & which kind, no lager/schatz
			printMap(*karte);						// schreiben
			break;
		case 3:
			// next turn
			std::cout << "spielzug p1" << std::endl;
			std::cin >> choose;
			choose = checkInput(choose);
			// input zielnode -> dijkstra
			kosten = karte->findShortestPathDijkstra(path,*location,*turn);
			/* if(genug taler){
			walk/calculate route  
			-> if(lager){
			collect Taler
			if(found schatz){	//  Suchen des Schatzes NUUUUUR auf der Zielinsel.
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
			delete karte;
			players.clear();
			break;
		case 5:
			printMenu();
			system("clear");
			std::cout << "Bildschirm bereinigt!" << std::endl;
		default:

			break;
		}
	}
	delete karte;
	players.clear();
}

Node* UI::readMAP(Graph& karte, std::string& filename,std::vector<Spieler*>& players)
{
	//source https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
	//source http://www.cplusplus.com/reference/string/string/size/

	Node* schatz = nullptr;
	std::ifstream file(filename);
	std::string line;
	std::string delimiter = " ";
	std::string delimiterEnd = "\n";
	/* is delimiter End not works -> try: std::string::npos
	This value, when used as the value for a len (or sublen) parameter in string's member functions,
	means "until the end of the string".
	*/
	std::string token;
	std::string token2;
	int position = 0;

	if (file.is_open()&& !(file.eof())) {
		while (std::getline(file, line)) {
			token = line.substr(0, line.find(delimiter));
			position = token.size();
			if (token == "Insel") {
				token = line.substr(position, line.find(delimiterEnd));
				karte.addNode(new Node(token));
			}
			else if (token == "Lager") {								
				int gold;
				token = line.substr(position, line.find(delimiter));
				token2 = line.substr(position + token.size(), line.find(delimiter));
				gold = std::stoi(token2);

				for (auto node : karte.getNodes) {
					if (node->getID() == token) {
						node.setGold(gold);
					}
				}
			}
			else if (token == "Tunnel"|| token == "Bruecke"|| token == "Faehre") {
				char kind;
				Node *n1 = nullptr;
				Node *n2 = nullptr;

				kind = token.front();
				token = line.substr(position, line.find(delimiter));
				token2 = line.substr(position + token.size(), line.find(delimiterEnd));
				n1 = new Node(token);
				n2 = new Node(token2);
				karte.addEdge(new Verbindung(kind,*n1,*n2));
			}
			else if (token == "Schatz") {
				token = line.substr(position, line.find(delimiterEnd));

				for (auto node : karte.getNodes) {
					if (node->getID() == token) {
						schatz = node;
					}
				}
			}
			else if (token == "Mensch"|| token == "Computer") {
				Spieler *p = nullptr;
				std::string kind = token;
				int gold;
				Node *start = nullptr;		

				token = line.substr(position, line.find(delimiterEnd));
				token2 = line.substr(position + token.size(), line.find(delimiter));
				gold = std::stoi(token2);

				for (auto node : karte.getNodes) {
					if (node->getID() == token2) {
						start = node;
					}
				}
				p = new Spieler(*start,gold);
				players.push_back(p);
			}
			else {
			//throw "cannot read file ( unknown keywords) " 
			}
		}
	}
	else{ // oder if, wenns nich geht
		std::cout << "file was closed / is empty" << std::endl;		// später throw 
	}
	file.close();
	return schatz;
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
	{
		return true;
	}

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
/*
void UI::setMAP(Graph & karte) {	// später in UI

	Node* kim = new Node("Kimoran_Berg");
	Node* ask = new Node("Askhora");
	Node* bera = new Node("Beramorin");
	Node* ost = new Node("Ostergaard");
	Node* uth = new Node("Uthenwold");
	Verbindung* t1 = new Verbindung('t', *bera, *ost);
	Verbindung* b1 = new Verbindung('b', *bera, *ost);
	Verbindung* b2 = new Verbindung('b', *ost, *ask);
	Verbindung* f1 = new Verbindung('f', *uth, *kim);
	Verbindung* f2 = new Verbindung('f', *uth, *ask);
	Verbindung* t2 = new Verbindung('t', *ask, *kim);
	Verbindung* b3 = new Verbindung('b', *ask, *kim);
	Verbindung* b4 = new Verbindung('b', *kim, *bera);
	Verbindung* t3 = new Verbindung('t', *ask, *bera);

	Verbindung* t4 = new Verbindung('t', *ost, *bera);
	Verbindung* b5 = new Verbindung('b', *ost, *bera);
	Verbindung* b6 = new Verbindung('b', *ask, *ost);
	Verbindung* f3 = new Verbindung('f', *kim, *uth);
	Verbindung* f4 = new Verbindung('f', *ask, *uth);
	Verbindung* t5 = new Verbindung('t', *kim, *ask);
	Verbindung* b7 = new Verbindung('b', *kim, *ask);
	Verbindung* b8 = new Verbindung('b', *bera, *kim);
	Verbindung* t6 = new Verbindung('t', *bera, *ask);

	karte.addNode(kim);
	karte.addNode(ask);
	karte.addNode(bera);
	karte.addNode(ost);
	karte.addNode(uth);

	karte.addEdge(t1);
	karte.addEdge(t2);
	karte.addEdge(t3);
	karte.addEdge(f1);
	karte.addEdge(f2);
	karte.addEdge(b1);
	karte.addEdge(b2);
	karte.addEdge(b3);
	karte.addEdge(b4);

	karte.addEdge(t4);
	karte.addEdge(t5);
	karte.addEdge(t6);
	karte.addEdge(f3);
	karte.addEdge(f4);
	karte.addEdge(b5);
	karte.addEdge(b6);
	karte.addEdge(b7);
	karte.addEdge(b8);
	/*
		Tunnel Beramorin Ostergaard
		Bruecke Kimoran_Berg Askhora
		Bruecke Askhora Ostergaard
		Faehre Askhora Uthenwold
		Faehre Uthenwold Kimoran_Berg
		Tunnel Beramorin Askhora
		Bruecke Ostergaard Beramorin
		Bruecke Beramorin Kimoran_Berg
		Schatz Beramorin
		Lager Ostergaard 15 Taler
		Lager Uthenwold 3 Taler
		Mensch Kimoran_Berg 30 Taler
		Computer Kimoran_Berg 30 Taler
		
}*/
void UI::printIntro()
{	// improive text
	std::cout << "Willkommen in der Welt von Kimoran \n Spielregeln \n Info: Die Standartspielkarte wurde geladen." << std::endl;
}
void UI::printInfo()
{
	// anfangs ( nach regeln in UI ) printen
	// gibt anleitung, dass reihenfolge bei eigenen txt eingehalten werden soll
	// grund: spieler brauchen Node als startpunkt
}
UI::UI()
{
}


UI::~UI()
{
}
