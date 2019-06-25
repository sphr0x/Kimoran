#include "UI.h"

int UI::checkInput(int input)
{
	while ((input <= 0) || (std::cin.fail())) {
		std::cin.clear();
		std::cin.ignore(30, '\n');
		std::cerr << "[ Fehler: Bitte eine positive Zahl eingeben: ]" << std::endl;
		std::cout << "\n[ Eingabe: ";
		std::cin >> input;
	}
		return input;
}
int UI::checkInputGameplay(int input, int islands)
{
	while ((input <= 0) || (std::cin.fail()) || input >= islands) {
		std::cin.clear();
		std::cin.ignore(30, '\n');
		std::cerr << "[ Fehler: Bitte eine positive Zahl eingeben: ]" << std::endl;
		std::cout << "\n[ Eingabe: ";
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
		std::cout << "\n[ Eingabe: ";
		std::cin >> choose;
		choose = checkInput(choose);

		switch (choose) {

		case 1:
			std::cout << "\n";
			for (auto node : karte.getNodes())std::cout <<"[ "<< node->getID() << " ]  ";
			std::cout << std::endl;
			//system("pause");
			break;
		case 2:
			std::cout << "\n";
			for (auto edge : karte.getEdges()) { 
				kind = dynamic_cast<Verbindung*>(edge);	
				std::cout << "[ "<< kind->toString()<< " ]  ist ein/e  " << " [" << kind->getMID() << "]" << std::endl;
			}
			//system("pause");
			break;
		case 3:
			std::cout << "[ ...gehe zurueck. ]" << std::endl;
			break;
		default:
			std::cerr << "[ Fehler: Bitte 1-6 waehlen! ]" << std::endl;
			//system("pause");
			break;
		}
		system("pause");
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
	std::string error;
	Filereading datei;
	Exception criticalError;

	// delay(printIntro());															// intro text activation
	system("PAUSE");
	while (choose != 2) {
		system("cls");
		std::cout << error << std::endl;
		delay(printInfo());
		std::cout << std::endl << "[1] [ Datein einlesen ]" << std::endl;
		std::cout <<"[2] [    Verlassen    ]" << std::endl;
		std::cout << "    \n[ Eingabe: ";
		std::cin >> choose;
		choose = checkInput(choose);
		try {
		if (choose == 1) {
			Graph* karte = new Graph();
			std::vector<Spieler*> players;
			Insel* ziel = nullptr;

			system("cls");
			std::string filename;

			std::cout << "[ Bitte Dateiname eingeben: ]" << std::endl;
			std::cout << "\n[ Eingabe: ";
			std::cin >> filename;
			try {
				ziel = datei.readMAP(*karte, filename, players);
				if (ziel == nullptr) {
					error = "[ Fehler: Spieler/Lager hat keinen oder falschen Geldwert ! ]";
					throw criticalError;
				}
				error.clear();
				menu3(*karte, players, *ziel);
				delete karte;
				players.clear();
			}
			catch (Exception exc) {
				std::cerr << exc.getError() << std::endl;
				system("pause");
				system("cls");
			}
			catch (...){					// catch other exceptions -> should not happen
				std::cout << "[ Unbekannter Fehler ! ]" << std::endl;
			}
		}
		if (choose > 2 || choose < 1) {
			error = "[ Fehler: Bitte 1 oder 2 eingeben! ]";
			criticalError.setError(std::to_string(choose));
			throw criticalError;
		}
		}
		catch (Exception exc) {
			std::cout << exc.getError() << std::endl;
			//system("pause");
		}
	}
	system("cls");
	delay("...beende Programm...");
}
void UI::menu3(Graph & karte, std::vector<Spieler*> players,Insel& ziel)						// pre-game menu 
{
	int choose = 0;
	std::deque<Insel*> path;
	std::string error = "[ Fehler : Bitte 1 - 3 eingeben ! ]";
	Exception criticalError;

	do{
		system("cls");
		std::cout << "[1] [   Karte zeigen  ]" << std::endl;
		std::cout << "[2] [     Spielen     ]" << std::endl;
		std::cout << "[3] [     Zurueck     ]" << std::endl;
		std::cout << "    \n[ Eingabe: ";
		std::cin >> choose;
		choose = checkInput(choose);
		if (choose == 3)break;
		if (choose == 1)MapMenu(karte);
		if (choose == 2) { 
			gameplay(karte,players,ziel);
			break;
		}
		if (choose >= 4) {
			criticalError.setError(error);
			throw criticalError;
		}
	}while (choose != 3);
		
	
}
void UI::gameplay(Graph& karte, std::vector<Spieler*> players, Insel& ziel)					// game menu
{
	int amount = 0;
	int additional;
	int islands = karte.getNodes().size();

	while (!gameOver(false)) {

	UI temp;
	double kosten;
	Spieler* player = players[amount % 2];														// if n player -> Spieler* player = players[a % n];
	Insel* dest = nullptr;
	std::deque<Insel*> convertedPath;
	std::deque<Insel*> pathCopy;
	std::deque<Node*> path;
	bool game = 0;
	additional = 0;

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
				std::cout << "\n[ Eingabe: ";				
				std::cin >> choose;
				choose = checkInputGameplay(choose,islands);
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
		for (auto node : path) {														// convert Node to Insel
			convertedPath.push_back(dynamic_cast<Insel*>(node));
		}
		if (player->getGeld() <= 2) {													// out of money ?
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
					"Manchmal laeuft es eben nicht so, wie es soll... goenn dir doch einfach mal ein wenig Ruhe. ]\n" << "[ Vielen Dank fuers Spielen ! ]" << std::endl;
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

			pathCopy = convertedPath;
			/*
			for (auto node : convertedPath)std::cout << node->getID() << std::endl;					// check path convertion -> works
			for (auto node : pathCopy)std::cout << node->getID() << std::endl;
			for (auto node : path)std::cout << node->getID() << std::endl;
			*/
			while (!convertedPath.empty()) {																	// is lager ? 
				additional = player->isLager2(convertedPath);
			}
			std::cout << "[ " << player->getName() << " ist am Zug: ]" << std::endl;
			player->printTurn(pathCopy, kosten, *dest);												// print route
			if (additional > 0) {
				std::cout << "[ Unterwegs insgesamt " << additional << " Taler gefunden! Weiter geht die Suche! ]" << std::endl;
			}
			player->deleteTurn(convertedPath);
			system("pause");
			system("cls");
			++amount; // -  -    -      -            -                    -                             -  switch from mensch to cpu
		}
		else if(player->getName() == "Mensch"){
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
