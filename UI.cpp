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
	//hier checkinput auf "kein leerzeichen" !
	// filename=checkInput(filename);
	
	//setnameofPlayer(mensch,filename);			// auf mensch via vector player zugreifen

	printMenu();

	while ((!foundTreasure(*location)) || players[0]->getGeld()==0 || players[1]->getGeld()==0) { // auf spieler via vector
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

			if (kosten <= players[0]->getGeld()) {
			//mensch.walkTo(turn);// walkTo in Spieler.h schreiben
				if (isLager(*turn)) {
					players[0]->setGeld(turn->getGold()); // bis jetzt nur dst node nach lager geprüft / mit path check machen
					turn->setGold(0);
				}
				if (foundTreasure(*turn)) {
					std::cout << players[0]->getName() << " hat gewonnen. juhu!" << std::endl;
					return;
				}
				printTurn(path,kosten,*turn,*players[0]);
				players[0]->setStandort(*turn);
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
	/* if delimiter End not works -> try: std::string::npos
	This value, when used as the value for a len (or sublen) parameter in string's member functions,
	means "until the end of the string".
	*/
	std::string token;
	std::string token2;
	std::string addLength;
	size_t position = 0;

	//file.open(filename);
	if (file.is_open()/*&& !(file.eof())*/) {
	
		while (std::getline(file, line)) {
			token = line.substr(0, line.find(delimiter));
			position = token.size();
			if (token == "Insel") {													// ok
				token = line.substr((position+1), line.find(delimiterEnd));
				karte.addNode(new Node(token));
			}
			else if (token == "Lager") {								
				int gold;
				token = line.substr((position+1), line.find(delimiter)); // hier weder find noch rfind -> has 2be solved !
				token2 = line.substr((position + 2 + token.size()), line.rfind(delimiter));
				gold = std::stoi(token2);

				for (auto node : karte.getNodes()) {
					if (node->getID() == token) {
						node->setGold(gold);
					}
				}
			}
			else if (token == "Tunnel"|| token == "Bruecke"|| token == "Faehre") { 
				char kind;
				Node *n1 = nullptr;
				Node *n2 = nullptr;

				//addLength = token +

				kind = token.front();
				token = line.substr((position + 1), line.find(delimiter));		// hier fehler: token findet immer den _ersten_ delimiter -> substr(a,b) a anpassen und b anpassen
				token2 = line.substr((position + 2 + token.size()), line.find(delimiterEnd));

				// throwed hier iwann exception
																	
				n2 = new Node(token2);			

				for (auto node : karte.getNodes()) { 
					if (node->getID() == token){
						n1 = node;
					}
				}
				for (auto node : karte.getNodes()) {
					if (node->getID() == token2) {
						n2 = node;
					}
				}
				if (n1 == nullptr) {
					n1 = new Node(token);
				}
				if (n2 == nullptr) {
					n2 = new Node(token2);
				}
				Edge *e = new Verbindung(kind, *n1, *n2);
				karte.addEdge(e);
				e = new Verbindung(kind, *n2, *n1);
				karte.addEdge(e);
			}
			else if (token == "Schatz") {
				token = line.substr((position+1), line.find(delimiterEnd));

				for (auto node : karte.getNodes()) {
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
				std::string name = token;

				token = line.substr((position+1), line.find(delimiterEnd)); // not ok delim @
				token2 = line.substr((position + 2 +  token.size()), line.find(delimiter)); // not ok
				gold = std::stoi(token2);

				for (auto node : karte.getNodes()) {
					if (node->getID() == token2) {
						start = node;
					}
				}
				p = new Spieler(*start,gold,name);
				players.push_back(p);
			}
			else {
			//throw "cannot read file ( unknown keywords) " 
			}
			// test ab hier

			// for (auto node : karte.getNodes())std::cout << node->getID() << std::endl;
			// for (auto node : karte.getNodes())std::cout << node->getGold() << std::endl;
			// for (auto node : karte.getNodes())std::cout << node->isGoal() << std::endl;
			for (auto edge : karte.getEdges())std::cout << edge->getID() << std::endl;

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
	// << std::fixed << std::setprecision(2) == dezimal auf 2 stellen (nach komma?)
	const char seperate = ' ';
	const char seperate2 = '-';
	const int width = 8;
	const int widthField = 40;
	const int widthNode = 12;
	std::ostringstream out;

	out << " " << std::setw(widthField)<< std::setfill(seperate2) <<" "<< std::endl <<

	"| " << std::setw(widthField) << std::setfill(seperate) << "Inseln: | " << std::endl <<
	"| " << std::endl <<
	"| " << std::endl <<
	"| " << std::endl <<
	"| " << std::endl <<
	"| " << std::endl <<
	"| " << std::endl <<


		  " " << std::setw(widthField) << std::setfill(seperate2) << " " << std::endl;

	std::cout << out.str();
}

void UI::setnameofPlayer(Spieler & mensch, std::string name)
{
	mensch.setName(name);
}

bool UI::foundTreasure(Node& location)
{
	if (location.isGoal()){
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

void UI::printTurn(std::deque<Node*>& actualRoute, double kosten, Node& dest, Spieler& mensch) {
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
void UI::delay(std::string a)
{
	int i;
	for (i = 0;a.length();++i) {
		std::cout << a[i];
		Sleep(20);
	}
}
UI::UI()
{
}


UI::~UI()
{
}
