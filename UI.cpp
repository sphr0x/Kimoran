#include "UI.h"

void UI::menu(/*Graph& karte,Spieler bla, Node& schatz,Node& start*/)
{
	Graph* karte = new Graph;
	int choose;
	std::string filename = "C23_Projekt_19SS_Inseln.txt";
	Node* turn = nullptr;
	Node* start = nullptr;
	std::deque<Node*> path;
	double kosten;
	std::vector<Spieler*> players; // pos 1 mensch pos 2 ki
	int proceed=1;

	printIntro();
	readMAP(*karte, filename, players);
	start = players[0]->getStandort();

	std::cout << "ihr name";
	std::cin >> filename;
	while (filename.length() < 2) {
		std::cerr << "nochmal: ( keine eingabe )";		// no throw 
		std::cin >> filename;
	}
	setnameofPlayer(*players[0],filename);			
	printMenu();
	while ((gameOver(proceed)) || players[0]->getGeld() == 0 || players[1]->getGeld() == 0) {
		std::cout << "Bitte Aktion waehlen:" << std::endl;
		std::cin >> choose;
		choose = checkInput(choose);
		switch (choose) {

		case 1:
			// hier fehlt noch graph.clear()
			printInfo();
			std::cout << "bitte file" << std::endl;
			std::cin >> filename;
			filename = checkInput(filename);		// checkinput testen
			readMAP(*karte, filename, players);
			break;
		case 2:
			MapMenu(*karte);						// testen
			break;
		case 3:
			// next mensch turn
			proceed = players[0]->spielzug(*karte, path);		// testen
			gameOver(proceed);
			/*
			std::cout << "spielzug p1,wohin?" << std::endl;
			std::cout << "liste" << std::endl;
			for (auto node : karte->getNodes())std::cout << node->getID() << std::endl;

			std::cin >> choose;
			choose = checkInput(choose);
			// turn = players[0]->spielzug()
			kosten = karte->findShortestPathDijkstra(path,*location,*turn); // in spielzug() rein?
			/* if(genug taler){
			walk/calculate route  
			-> if(lager){
			collect Taler
			if(found schatz){	//  Suchen des Schatzes NUUUUUR auf der Zielinsel.
			output "won" + end game 
			} 
			-> get route ->
			} 

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
			*/

			// next KI turn

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
		// case 3,5: Statusausgabe spieler+ ki   ---> OPTIONAL
		case 4:
			//beenden
			delete karte;
			players.clear();
			gameOver(0);
			return;
		case 5:
			printMenu();
			system("cls");
			std::cout << "Bildschirm bereinigt!" << std::endl;
		default:
			std::cerr << "\t\t\tFehler: Bitte 1-5 waehlen!" << std::endl;
			break;
		}
	}
	delete karte;
	players.clear();
}

Node* UI::readMAP(Graph& karte, std::string& filename,std::vector<Spieler*>& players)
{
	//inspired by: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
	//source: http://www.cplusplus.com/reference/string/string/

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
	size_t position = 0;

	if (file.is_open()) {
	
		while (std::getline(file, line)) {
			token = line.substr(0, line.find(delimiter));
			position = token.size();
			if (token == "Insel") {													// ok
				token = line.substr((position+1), line.find(delimiterEnd));
				karte.addNode(new Node(token));
			}
			else if (token == "Lager") {								
				int gold;
													// ok
				token = line.substr(line.find(delimiter) + 1, line.find(delimiter, line.find(delimiter) + 1) - (line.find(delimiter) + 1));		// substr korrigieren
				token2 = line.substr(line.find(delimiter, line.find(delimiter) + 1) + 1 , line.find(delimiter, line.find(delimiter, line.find(delimiter) + 1) + 1) - (line.find(delimiter, line.find(delimiter) + 1)));
				gold = std::stoi(token2); 
				
				for (auto node : karte.getNodes()) {
					if (node->getID() == token) {
						node->setGold(gold);
						//std::cout << node->getID() << "hat" << node->getGold() << std::endl;
					}
				}
			}
			else if (token == "Tunnel"|| token == "Bruecke"|| token == "Faehre") { 
				char kind;
				Node *n1 = nullptr;
				Node *n2 = nullptr;

				kind = token.front();											// ok
				token = line.substr(line.find(delimiter)+1, line.find(delimiter,line.find(delimiter)+1)- (line.find(delimiter) + 1)); //substr( posi= 1. LZ , länge = 2. LZ - 1. LZ )
				token2 = line.substr(line.find(delimiter, line.find(delimiter)+1)+1, line.find(delimiterEnd)); 
				// substr(startpkt,länge) | line.find(delimiter, line.find(delimiter)+1) = 2. delimiter !!
				// line.find(delimiter,line.find(delimiter,line.find(delimiter)+1)+1)  // pos 3												
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
				//std::cout << e->toString() << std::endl;

				e = new Verbindung(kind, *n2, *n1);
				karte.addEdge(e);
				//std::cout << e->toString() << std::endl;
			}
			else if (token == "Schatz") {			// ok
				token = line.substr(position+1, line.find(delimiterEnd));

				for (auto node : karte.getNodes()) {
					if (node->getID() == token) {
						node->setGoal(1);
						schatz = node;
					}
				}
			}
			else if (token == "Mensch"|| token == "Computer") {	// ok
				Spieler *p = nullptr;
				std::string kind = token;
				int gold;
				Node *start = nullptr;		
				std::string name = token;

				token = line.substr(line.find(delimiter) + 1, line.find(delimiter, line.find(delimiter) + 1) - (line.find(delimiter) + 1)); 
				token2 = line.substr(line.find(delimiter, line.find(delimiter) + 1) + 1, line.find(delimiter, line.find(delimiter, line.find(delimiter) + 1) + 1) - (line.find(delimiter, line.find(delimiter) + 1)));
				gold = std::stoi(token2);

				for (auto node : karte.getNodes()) {
					if (node->getID() == token) {
						start = node;
					}
				}
				p = new Spieler(*start,gold,name);
				players.push_back(p);
			}
			else {
			//throw "cannot read file ( unknown keywords )";
			}
		}
	}
	else{ 
		// throw line = "file was closed / is empty";
		std::cerr << "file was closed / is empty" << std::endl;		// später throw 
	}
	file.close();
	return schatz;
}

std::string UI::checkInput(std::string input)
{	// bal.txt
	// check auf string + "." + "txt"
	// hier string zerteilen und check
	std::string temp,temp2;

	temp = input.substr(0, input.find("."));			// so noch except = fkt für not find ?
	if (!(input.find("."))) {	
		temp = "nix";
		temp2 = "iwas";
	}
	temp2 = input.substr(input.find("."), (input.length() - temp.length())); 

	// wenn kein . drinne -> temp2 exception
	//nur .txt-> ok
	// iwas.txt -> ok
	while(!((temp.length() > 1) && (temp2 == ".txt"))) {
		std::cin.clear();
		std::cin.ignore(30, '\n');
		std::cerr << "Aus der Eingabe ist keine .txt - Datei herauszufiltern! " << std::endl;
		std::cout << "\tEingabe: ";
		std::cin >> input;
	}
	temp = input.substr(0, input.find("."));
	temp2 = input.substr(input.find("."), (input.length() - temp.length()));
	input = temp + temp2;
	return input;
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
}

int UI::checkInput(int input)
{
	while ((input <= 0) || (std::cin.fail())) {
		std::cin.clear();
		std::cin.ignore(30, '\n');
		std::cerr << "\t\t\tFehler: Bitte eine positive Zahl eingeben: " << std::endl;
		std::cout << "\tEingabe: ";
		std::cin >> input;
	}
		return input;
}

void UI::setnameofPlayer(Spieler & mensch, std::string name)
{
	mensch.setName(name);
}
bool UI::foundTreasure(Node& location)
{
	if (location.isGoal()) {
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
/*
void UI::printTurn(std::deque<Node*>& actualRoute, double kosten, Node& dest, Spieler& mensch) {
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
	std::cout << "\t\t\tVerbleibene Taler: " << mensch.getGeld() << std::endl;
}

void UI::deleteTurn(std::deque<Node*>& actualRoute){
	actualRoute.clear();
}*/
void UI::printIntro()
{	// improve text:
	// ostringstream out; 
	// alles auf out << "...\n" 
	// delay(out.str());
	std::cout << "Willkommen in der Welt von Kimoran" << std::endl;
	std::cout << "Spielregeln & Informationen:" << std::endl;
	std::cout << "Spielregeln:" << std::endl;
	std::cout << "Kimoran ist eine geheimnisvolle Welt, die aus vergessenen Inseln besteht welche mit morschen Bruecken, alten, aber \n" <<
		"extrem schnellen Faehrwegen und einsturzgefaehrdeten Tunneln verbunden sind. \n" <<
		"Auf einer dieser der Inseln gibt es einen Schatz von galaktischem Ausmass. Wer diesen zuerst entdeckt hat nicht nur \n" <<
		"das Spiel gewonnen, sondern wird bis in alle Ewigkeit in Reichtum verweilen. Praktisch ! " << std::endl;
	std::cout << "Man gelangt von Insel zu Insel, indem man sich ueber die Bruecken, durch die Tunnel \n" <<
		"oder mithilfe von Faehren fortbewegt. Das ist natuerlich nicht gratis! ( Warum solltes es auch ? ) Für jede \n" <<
		"dieser Passagen sind Zoelle oder Transportkosten zu entrichten, denn auch im Kimoran ist der Kapitalismus schon\n" <<
		" vor Jahrhunderten eingekehrt. Gut ist, dass alle Verbindungen in beide Richtungen nutzbar sind, schlecht ist, dass jede \n" <<
		"neue Ueberquerung wieder einige Taler kostet. Noch schlechter ist, dass Sie gegen eine nahezu unschlagbare KI antretetn werden, \n" <<
		"die auch auf der Suche nach ewigem Reichtum ist. ( Zitat der KI: \"I SUPERIOR, U SLAVE !!!\" ) \n" <<
		"Tja, es geht immerhin um den Schatz der Schaetze und nicht um neue Freundschaften. Dafuer ist hier immer so richtig schoenes Wetter. Also dann, viel Spass!" << std::endl;
	std::cout << "\n\nInformationen:" << std::endl;
	std::cout << "Kosten fuer Bruecken & Faehren: 3 Taler" << std::endl;
	std::cout << "Kosten fuer Tunnel: 5 Taler" << std::endl;
	std::cout << "Startkapital: 30 Taler" << std::endl;
	std::cout << "Versteckte Lager mit Talern: 2" << std::endl;
	std::cout << "( Diese Informationen gelten nur für die Standart-Karte von Kimoran !)" << std::endl;
}
void UI::printInfo()
{
	// anfangs ( nach regeln in UI ) printen
	// gibt anleitung, dass reihenfolge bei eigenen txt eingehalten werden soll
	// grund: spieler brauchen Node als startpunkt

	std::cout << "Information zu eigenen geladenen Textdateien:" << std::endl;
	std::cout << "Es koennen beliebig Objekte im VORHANDEN FORMAT hinzugefuegt werden. " << std::endl;
	std::cout << "Es koennen ( noch ) KEINE Spieler hinzugefügt werden." << std::endl;
	std::cout << "Das hinzufügen weiterer Schaetze wird vom Programmierer nicht geschaetzt." << std::endl;

}
void UI::delay(std::string a)
{
	int i;
	for (i = 0;a.length();++i) {
		std::cout << a[i];
		Sleep(20);
	}
}
void UI::MapMenu(Graph & karte)
{
	int choose;
	Verbindung * kind = nullptr;

	printMapMenu();
	while (1) {
		std::cout << "Bitte Aktion waehlen:" << std::endl;
		std::cin >> choose;
		choose = checkInput(choose);

		switch (choose) {

		case 1:
			for (auto node : karte.getNodes())std::cout << node->getID() << std::endl;
			break;
		case 2:
			for (auto edge : karte.getEdges()) { 
				kind = dynamic_cast<Verbindung*>(edge);		// evtl static_cast<>
				if (kind->getVID() == 'B') {
					std::cout << edge->toString() << std::endl;
				}
			}
			break;
		case 3:
			for (auto edge : karte.getEdges()) {
				kind = dynamic_cast<Verbindung*>(edge);
				if (kind->getVID() == 'T') {
					std::cout << edge->toString() << std::endl;
				}
			}
			break;
		case 4:
			for (auto edge : karte.getEdges()) {
				kind = dynamic_cast<Verbindung*>(edge);
				if (kind->getVID() == 'F') {
					std::cout << edge->toString() << std::endl;
				}
			}
			break;
		case 5:
			std::cerr << "Dieses Feature ist noch nicht verfügbar!" << std::endl;
			break;
		case 6:
			std::cout << "...gehe zurueck." << std::endl;
			return;
		default:
			std::cerr << "\t\t\tFehler: Bitte 1-6 waehlen!" << std::endl;
			break;
		}
	}
}
void UI::printMapMenu()
{// format via stringstream !
	Sleep(500);
	std::cout << "\n\t\t\t    ->  [            Ausgabe waehlen             ]  <- \n" << std::endl;
	Sleep(500);
	std::cout << "\n\t\t\t    ->  [    Bitte Aktion via Nummerierung waehlen   ]  <- \n\n" << "\t\t\t[1] ->  [        Inseln ausgeben       ]  <-\n";
	Sleep(500);
	std::cout << "\t\t\t[2] ->  [                  Alle Bruecken                 ]  <-\n";
	Sleep(500);
	std::cout << "\t\t\t[3] ->  [            Alle Tunnel        ]  <-\n" << "\t\t\t[4] ->  [                 Alle Faehren                  ]  <-\n";
	std::cout << "\t\t\t[5] ->  [             Gesamte Karte          ]  <-\n" << "\t\t\t[6] ->  [               Zurueck            ]  <-\n" << std::endl;

}
UI::UI()
{
}


UI::~UI()
{
}
