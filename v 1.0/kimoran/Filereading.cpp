#include "Filereading.h"

Insel* Filereading::readMAP(Graph& karte, std::string& filename, std::vector<Spieler*>& players)
{
	//inspired by: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
	//source of functions: http://www.cplusplus.com/reference/string/string/

	/*						understanding token principle:

		line.substr( position == 1st "space" , length = 2nd "space" - 1st "space" )
		substr(start position, length) | line.find(delimiter, line.find(delimiter)+1) == 2nd delimiter ( "space" )
		line.find(delimiter,line.find(delimiter,line.find(delimiter)+1)+1)  == the 3. position == the string after 2nd "space"

	*/
	
	Insel* schatz = nullptr;
	Insel* converted = nullptr;
	std::ifstream file(filename);
	std::string line;
	std::string delimiter = " ";
	std::string delimiterEnd = "\n";
	/* if delimiter End does not works -> try: std::string::npos
	This value, when used as the value for a len (or sublen) parameter in string's member functions,
	means "until the end of the string".
	*/
	std::string token;
	std::string token2;
	std::string error = "";
	Exception criticalError;

	size_t position = 0;

	if (!file.is_open()) {													// exception : existing file -> works
		error = "[ Fehler: Datei existiert nicht! ]";
		criticalError.setError(error);
		throw criticalError;
	}
	if (file.is_open()) {

		while (std::getline(file, line)) {
			token = line.substr(0, line.find(delimiter));
			position = token.size();
			if (token == "Insel") {
				token = line.substr((position + 1), line.find(delimiterEnd));
				karte.addNode(new Insel(token));
			}
			else if (token == "Lager") {
				int gold;
				token = line.substr(line.find(delimiter) + 1, line.find(delimiter, line.find(delimiter) + 1) - (line.find(delimiter) + 1));
				token2 = line.substr(line.find(delimiter, line.find(delimiter) + 1) + 1, line.find(delimiter, line.find(delimiter, line.find(delimiter) + 1) + 1) - (line.find(delimiter, line.find(delimiter) + 1)));
				
				try {
					gold = std::stoi(token2);
				}
				catch (std::invalid_argument& gold) {											// exception : wrong value for Lager-gold -> works
					return nullptr;
				}
				if (gold <= 0) {
					error = "[ Fehler: Ein Lager kann kein negativen bzw. 0 als Geldwert haben ...wo kommen wir denn da hin? ]"; // exception : negative value for Lager-gold -> works
					criticalError.setError(error);
					throw criticalError;
				}
				for (auto node : karte.getNodes()) {
					converted = dynamic_cast<Insel*>(node);
					if (converted->getID() == token) {
						if (converted->getGold() != 0) {
							error = "[ Fehler: Insel kann nur ein Lager haben ! ]";			// exception : only 1 Lager / Insel -> works
							criticalError.setError(error);
							throw criticalError;
						}
						converted->setGold(gold);
					}
				}
			}
			else if (token == "Tunnel" || token == "Bruecke" || token == "Faehre") {
				std::string id;
				Insel *n1 = nullptr;
				Insel *n2 = nullptr;
				id = token;
				token = line.substr(line.find(delimiter) + 1, line.find(delimiter, line.find(delimiter) + 1) - (line.find(delimiter) + 1));
				token2 = line.substr(line.find(delimiter, line.find(delimiter) + 1) + 1, line.find(delimiterEnd));

				n2 = new Insel(token2);
				for (auto node : karte.getNodes()) {
					if (node->getID() == token) {
						n1 = dynamic_cast<Insel*>(node);
					}
				}
				for (auto node : karte.getNodes()) {
					if (node->getID() == token2) {
						n2 = dynamic_cast<Insel*>(node);
					}
				}
				if (n1 == nullptr) {
					// n1 = dynamic_cast<Insel*>(new Node(token)); oder
					n1 = new Insel(token);
				}
				if (n2 == nullptr) {
					// n2 = dynamic_cast<Insel*>(new Node(token2)); oder
					n1 = new Insel(token2);
				}
				Edge *e = new Verbindung(id, *n1, *n2);
				karte.addEdge(e);
				e = new Verbindung(id, *n2, *n1);
				karte.addEdge(e);
			}
			else if (token == "Schatz") {
				token = line.substr(position + 1, line.find(delimiterEnd));
				for (auto node : karte.getNodes()) {
					converted = dynamic_cast<Insel*>(node);
					if (converted->getID() == token) {					// set treasure to Insel by conversion
						converted->setGoal(1);
						schatz = dynamic_cast<Insel*>(node);
					}
				}
			}
			else if (token == "Mensch" || token == "Computer") {
				Spieler *p = nullptr;
				std::string kind = token;
				int gold;
				Insel *start = nullptr;
				std::string name = token;

				token = line.substr(line.find(delimiter) + 1, line.find(delimiter, line.find(delimiter) + 1) - (line.find(delimiter) + 1));
				token2 = line.substr(line.find(delimiter, line.find(delimiter) + 1) + 1, line.find(delimiter, line.find(delimiter, line.find(delimiter) + 1) + 1) - (line.find(delimiter, line.find(delimiter) + 1)));
				try {
					gold = std::stoi(token2);
				}
				catch (std::invalid_argument& gold) {											// exception : wrong value for startgold -> works
					return nullptr;
				}
				if (gold <= 0) {
					error = "[ Fehler: Ein Spieler kann kein negativen bzw. 0 als Geldwert haben ...wo kommen wir denn da hin? ]"; // exception : negative value for startgold -> works
					criticalError.setError(error);
					throw criticalError;
				}
				for (auto node : karte.getNodes()) {
					if (node->getID() == token) {
						start = dynamic_cast<Insel*>(node);
						break;
					}
					else if(node->getID() != token) {
						error = "[ Fehler: Kein Startpunkt gesetzt! ]";				// exception : wrong or no node to start from -> works
						criticalError.setError(error);
						throw criticalError;
					}
				}
				p = new Spieler(*start, gold, name);
				players.push_back(p);
			}
			else {
				error = "[ Fehler: Datei unlesbar ( unbekannte, doppelte oder fehlende Schluesselwoerter ) ! ]";	// exception : double treasure, Lager: no or wrong value -> works
				criticalError.setError(error);
				throw criticalError;
			}
		}
	}
	else {
		error = "[ Fehler: Datei ist nicht offen bzw. leer ! ]";
		criticalError.setError(error);
		throw criticalError;							// exc
	}/*
	for (auto node : karte.getNodes()) {
		if (!node->isGoal()) {
			// cast to insel			  // 2do
			int a, pick;
			a = karte.getNodes().size();
			srand(time(NULL));															// generate random treasure... optional/later...
			pick = rand() % a + 1;
			// function to get n'th node  // 2do
			n'th node->setGoal(1);		  // 2do
		}
	}
	*/
	file.close();
	std::cout << "[ Datei erfolgreich gelesen ]" << std::endl;
	system("pause");
	system("cls");
	return schatz;
}


Filereading::Filereading()
{
}


Filereading::~Filereading()
{
}
