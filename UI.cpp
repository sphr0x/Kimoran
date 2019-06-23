#include "UI.h"

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
	
	if (!file.is_open()) {											// exc
		std::string str="[ Fehler: Datei existiert nicht! ]";
		throw str;
	}
	if (file.is_open()) {
	
		while (std::getline(file, line)) {
			token = line.substr(0, line.find(delimiter));
			position = token.size();
			if (token == "Insel") {													
				token = line.substr((position+1), line.find(delimiterEnd));
				karte.addNode(new Node(token));
			}
			else if (token == "Lager") {								
				int gold;
				token = line.substr(line.find(delimiter) + 1, line.find(delimiter, line.find(delimiter) + 1) - (line.find(delimiter) + 1));		
				token2 = line.substr(line.find(delimiter, line.find(delimiter) + 1) + 1 , line.find(delimiter, line.find(delimiter, line.find(delimiter) + 1) + 1) - (line.find(delimiter, line.find(delimiter) + 1)));

				try {
					gold = std::stoi(token2);
				}
				catch (std::invalid_argument& a) {								// hier gecatched : string, but i want wrongvalue except!
					std::cerr << "[ Fehler: Lager hat keinen Geldwert ! ]";
					return nullptr;
				}
				std::string error = "[ Fehler: Insel kann nur ein Lager haben ! ]";			// exc
				for (auto node : karte.getNodes()) {
					if (node->getID() == token) {
						if (node->getGold() != 0)throw error;
						node->setGold(gold);
					}
				}
			}
			else if (token == "Tunnel"|| token == "Bruecke"|| token == "Faehre") { 
				std::string id;
				Node *n1 = nullptr;
				Node *n2 = nullptr;						
				id = token;
				token = line.substr(line.find(delimiter)+1, line.find(delimiter,line.find(delimiter)+1)- (line.find(delimiter) + 1)); 
				token2 = line.substr(line.find(delimiter, line.find(delimiter)+1)+1, line.find(delimiterEnd)); 
				/*	substr( posi= 1. LZ , länge = 2. LZ - 1. LZ )
					substr(startpkt,länge) | line.find(delimiter, line.find(delimiter)+1) = 2. delimiter !!
					line.find(delimiter,line.find(delimiter,line.find(delimiter)+1)+1)  // pos 3					*/												
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
				Edge *e = new Verbindung(id, *n1, *n2);
				karte.addEdge(e);
				e = new Verbindung(id, *n2, *n1);
				karte.addEdge(e);
			}
			else if (token == "Schatz") {			
				token = line.substr(position+1, line.find(delimiterEnd));
				for (auto node : karte.getNodes()) {
					if (node->getID() == token) {
						node->setGoal(1);
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
				token = line.substr(line.find(delimiter) + 1, line.find(delimiter, line.find(delimiter) + 1) - (line.find(delimiter) + 1)); 
				token2 = line.substr(line.find(delimiter, line.find(delimiter) + 1) + 1, line.find(delimiter, line.find(delimiter, line.find(delimiter) + 1) + 1) - (line.find(delimiter, line.find(delimiter) + 1)));
				gold = std::stoi(token2);

				for (auto node : karte.getNodes()) {
					if (node->getID() == token) {
						start = node;
						break;
					}
					else {
						token = "[ Fehler: Kein Startpunkt gesetzt! ]";				// exc
						throw token;
					}
				}
				p = new Spieler(*start,gold,name);
				players.push_back(p);
			}
			else {
				std::string str="[ Fehler: Datei unlesbar ( unbekannte oder fehlende Schluesselwoerter ) ! ]";	// exc
				throw str;
			}
		}
		int i = 0;											
		std::string error = "[ Fehler: Es kann nur EINEN geben !!! ( ...also nur einen Schatz im Spiel. ) ]";
		for (auto node : karte.getNodes()) {
			if (node->isGoal()) {
				++i;
			}
			if (i >= 2) {
				throw error;				// exc
			}
		}
	}
	else{ 
	token = "[ Fehler: Datei ist nicht offen bzw. leer ! ]";
	throw token;							// exc
	}/*
	for (auto node : karte.getNodes()) {
		if (!node->isGoal()) {
			int a, pick;
			a = karte.getNodes().size();
			srand(time(NULL));															// generate random treasure... later...
			pick = rand() % a + 1;
			// function to get n'th node
			n'th node->setGoal(1);
		}
	}
	*/
	file.close();
	return schatz;
}
int UI::checkInput(int input)
{
	while ((input <= 0) || (std::cin.fail())) {
		std::cin.clear();
		std::cin.ignore(30, '\n');
		std::cerr << "[ Fehler: Bitte eine positive Zahl eingeben: ]" << std::endl;
		std::cout << "[ Eingabe: ";
		std::cin >> input;
	}
		return input;
}
/*
void UI::setnameofPlayer(Spieler & mensch, std::string name)
{
	mensch.setName(name);
}*/
std::string UI::printIntro(){
	std::ostringstream out; 
	out << "\n[ Willkommen in der Welt von Kimoran ]\n\n" << "[ Spielregeln & Informationen: ]\n\n" << "[ Spielregeln: ]\n\n" <<
		"[ Kimoran ist eine geheimnisvolle Welt, die aus vergessenen Inseln besteht, welche mit morschen Bruecken, alten, \n" <<
		"  extrem schnellen Faehrwegen und einsturzgefaehrdeten Tunneln verbunden sind. \n" <<
		"  Auf einer dieser der Inseln gibt es einen Schatz von galaktischem Ausmass. Wer diesen zuerst entdeckt hat nicht nur \n" <<
		"  das Spiel gewonnen, sondern wird bis in alle Ewigkeit in Reichtum verweilen. Praktisch ! \n" <<
		"  Man gelangt von Insel zu Insel, indem man sich ueber die Bruecken, durch die Tunnel \n" <<
		"  oder mithilfe von Faehren fortbewegt. Das ist natuerlich nicht gratis! ( Warum solltes es auch ? ) Fuer jede \n" <<
		"  dieser Passagen sind Zoelle oder Transportkosten zu entrichten, denn auch im Kimoran ist der Kapitalismus schon\n" <<
		"  vor Jahrhunderten eingekehrt. Gut ist, dass alle Verbindungen in beide Richtungen nutzbar sind, schlecht ist, dass jede \n" <<
		"  neue Ueberquerung wieder einige Taler kostet. Noch schlechter ist, dass Sie gegen eine nahezu unschlagbare KI antretetn werden, \n" <<
		"  die auch auf der Suche nach ewigem Reichtum ist. ( Zitat der KI: \"I SUPERIOR, U SLAVE !!!\" ) \n" <<
		"  Tja, es geht immerhin um den Schatz der Schaetze und nicht um neue Freundschaften. Dafuer ist hier immer so richtig schoenes Wetter. Also dann, viel Spass!\n" 
		"\n\n[ Informationen: ]\n" << "[ Kosten fuer Bruecken & Faehren: 3 Taler ]\n" << "[ Kosten fuer Tunnel: 5 Taler ]\n" <<
		"[ Startkapital: 30 Taler ]*\n" << "[ Versteckte Lager mit Talern: ??? ]*\n\n" << 
		"\n[ * Diese Informationen gelten nur fuer die generierte Karte aus \"projekt.txt\" ! ]\n\n";
	return out.str();
}
std::string UI::printInfo(){
	std::ostringstream out;

	out << "\n\n[ Information zu eigenen geladenen Textdateien: ]\n\n"
		<< "[ Es koennen beliebig Inseln und Verbindungen im VORHANDEN FORMAT hinzugefuegt werden. \n"
		<< "  Es kann ( noch ) nicht mehr als [1] menschlicher Spieler spielen.\n"
		<< "  Das setzten weiterer Schaetze wird vom Programmierer nicht geschaetzt. ]\n\n";

	return out.str();
}
void UI::delay(std::string a)
{
	int i;
	for (i = 0;i <= a.size();++i) {
		std::cout << a[i];
		Sleep(5);
	}
	std::cout << std::endl;
}
void UI::MapMenu(Graph & karte)					// map menu
{
	system("cls");
	int choose = 0;
	Verbindung * kind = nullptr;

	//delay(printMapMenu());
	while (choose != 3) {
		system("cls");
		delay(printMapMenu());
		std::cout << "[ Bitte Aktion waehlen: ]" << std::endl;
		std::cout << "[ Eingabe: ";
		std::cin >> choose;
		choose = checkInput(choose);

		switch (choose) {

		case 1:
			std::cout << "\n";
			for (auto node : karte.getNodes())std::cout <<"[ "<< node->getID() << " ]  ";
			std::cout << std::endl;
			system("pause");
			break;
		case 2:
			std::cout << "\n";
			for (auto edge : karte.getEdges()) { 
				kind = dynamic_cast<Verbindung*>(edge);	
				std::cout << "[ "<< kind->toString()<< " ]  ist ein/e  " << " [" << kind->getMID() << "]" << std::endl;
			}
			system("pause");
			break;
		case 3:
			std::cout << "[ ...gehe zurueck. ]" << std::endl;
			break;
		default:
			std::cerr << "[ Fehler: Bitte 1-6 waehlen! ]" << std::endl;
			break;
		}
	}
}
std::string UI::printMapMenu(){
	std::ostringstream out;

	out << "    [ Bitte Aktion via Nummerierung waehlen ]\n\n" <<
		"[1] [         Alle Inseln ausgeben          ]\n"
		<< "[2] [          Alle Verbindungen            ] \n"
		<< "[3] [              Zurueck                  ]\n";
	return out.str();
}
void UI::menu2() {																	// input file menu
	int choose = 0;

	delay(printIntro());
	system("PAUSE");
	std::string error;

	while (choose != 2) {
		system("cls");
		std::cout << error << std::endl;
		delay(printInfo());
		std::cout << std::endl << "[1] [ Datein einlesen ]" << std::endl;
		std::cout <<"[2] [    Verlassen    ]" << std::endl;
		std::cout << "    [ Eingabe: ";
		std::cin >> choose;
		choose = checkInput(choose);
		try {
		if (choose == 1) {
			Graph* karte = new Graph();
			std::vector<Spieler*> players;
			Node* ziel = nullptr;

			system("cls");
			std::string filename;

			std::cout << "[ Bitte Dateiname eingeben: ]" << std::endl;
			std::cout << "[ Eingabe: ";
			std::cin >> filename;
			try {
				ziel = readMAP(*karte, filename, players);
				error.clear();
				menu3(*karte, players, *ziel);
				delete karte;
				players.clear();
			}
			catch (std::string str) {
				error = str;
			}
		}
		if (choose > 2) {
			throw choose;
		}
		}
		catch (int) {
		std::cerr << "[ Fehler: Bitte 1 oder 2 eingeben! ]" << std::endl;
		system("pause");
		}
}
}
void UI::menu3(Graph & karte, std::vector<Spieler*> players,Node& ziel)						// pre-game menu 
{
	int choose = 0;
	std::deque<Node*> path;
	do{
		system("cls");
		std::cout << "[1] [   Karte zeigen  ]" << std::endl;
		std::cout << "[2] [     Spielen     ]" << std::endl;
		std::cout << "[3] [ Spiel verlassen ]" << std::endl;
		std::cout << "    [ Eingabe: ";
		std::cin >> choose;
		choose = checkInput(choose);
		if (choose == 3)break;
		if (choose == 1)MapMenu(karte);
		if (choose == 2) { 
			gameplay(karte,players,ziel);
			break;
		}
	}while (choose != 3);
		
	
}
void UI::gameplay(Graph& karte, std::vector<Spieler*> players, Node& ziel)					// game menu
{
	int a = 0;

	while (!gameOver(false)) {

	UI temp;
	double kosten;
	Spieler* player = players[a % 2];														// if 3 player -> Spieler* player = players[a % 3];
	Node* dest = nullptr;
	std::deque<Node*> path;
	std::deque<Node*> pathCopy;
	bool game = 0;

		while (1) {
			system("cls");
			int choose = 1;
			if (player->getName() == "Mensch") {											// mensch turn
				std::cout << "\n[ Wo moechten wir nach dem Schatz suchen? ]\n" << std::endl;
				if(player->getName() == "Mensch")
				std::cout << "\n[ Sie sind gerade hier: " << player->getStandort()->getID() << " und haben " << player->getGeld() << " Taler ]\n" << std::endl;

				for (auto node : karte.getNodes()) {
					std::cout << "[ " << choose++ << " ] : " << node->getID() << std::endl;	// display options
				}
				std::cout << "[ Eingabe: ";
				std::cin >> choose;
				choose = temp.checkInput(choose);
				dest = player->setLocation(choose, karte);
			}
			if (player->getName() == "Computer") {											// cpu turn
				size_t n = karte.getNodes().size();
				srand(time(NULL));															// randomly generate destination
				choose = rand() % n + 1;
				choose = temp.checkInput(choose);
				dest = player->setLocation(choose, karte);
			}
			if (dest->getID() == player->getStandort()->getID()) {							// check if destination == source
				if (player->getName() == "Mensch") {
					std::cout << "[ Hey " << player->getName() << "! " <<
						"Auf der Stelle stehen macht weder Spass, noch wird man dadurch reich! ]\n" << "[ Neuer Versuch! ]" << std::endl;
					system("pause");
				}
			}
			else {
				break;
			}
		}
		system("cls");
		kosten = karte.findShortestPathDijkstra(path, *player->getStandort(), *dest);
		if (player->getGeld() <= 3) {													// out of money ?
			std::cout <<"[ " << player->getName() << " hat keinen mueden Penny mehr... und hat verloren. Schade, schade... ]\n\n" <<
				"[ Vielen Dank fuers Spielen ! ]" << std::endl;
			system("pause");
			gameOver(true);
			break;
		}
		if (kosten == 10000) {
			std::cerr << "[ Seit des Flugverbotes in Kimoran gibt es zu dieser Insel keine Verbindung mehr. " << player->getName() <<
				" hat seinen Zug vertan... ]" << std::endl;
			if (dest->getID() == ziel.getID()) {
				std::cout << "[ ...allerdings erfaehrst du gerade per mail, dass der Schatz dort vergraben sein soll." <<
					"Manchmal laeuft es eben nicht so, wie es soll... goenn dir doch einfach mal ein wenig Ruhe. ]" << std::endl;
				system("pause");
				gameOver(true);
				break;
			}
			system("pause");
		}
		if (kosten <= player->getGeld()) {													// is turn possible ?
			player->setStandort(*dest);														// new src = old dst
			player->setGeld(player->getGeld() - kosten);									// set geld
			if (dest->getID() == ziel.getID()) {											// is treasure ?
				srand(time(NULL));
				int n = rand() % 10000 + 0;
				std::cout <<"[ " << player->getName() << " hat den Schatz gefunden!!!" <<
					"Es waren unglaubliche " << n << " Taler in der Truhe. Wahnsinn ! ]" << std::endl;	// treasure random gold
				system("pause");
				gameOver(true);
				break;
			}
			pathCopy = path;
			while (!path.empty()) {															// is lager ? 
				player->isLager2(path);
			}
			std::cout << "[ " << player->getName() << " ist am Zug: ]" << std::endl;
			player->printTurn(pathCopy, kosten, *dest);										// print route
			player->deleteTurn(path);
			system("pause");
			system("cls");
			++a;	// -   -    -     -            -                   -                         -  switch from mensch to cpu
		}
		else {
			std::cerr <<"[ "<< player->getName() << " hat nicht genug Taler. Bitte neuen Zielort waehlen: ]" << std::endl;
			system("pause");
		}
	}
}

UI::UI()
{
}


UI::~UI()
{
}
