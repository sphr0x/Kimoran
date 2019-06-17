#include <iostream>
#include "Graph.h"
#include "Route.h"
#include "Spieler.h"
#include "Verbindung.h"
#include "UI.h"



int main()
{
	UI prog;
	//prog.menu();

	//std::string a = "C23_Projekt_19SS_Inseln.txt";
	std::string a = "Neues Textdokument.txt";
	Graph* karte = new Graph;
	std::vector<Spieler*> players;
	prog.readMAP(*karte,a,players);
	for (auto edge : karte->getEdges()) std::cout << edge->toString() << std::endl;


	delete karte;

	system("pause");
	return 0;
}
/* 2do
	EVTL srand(time(NULL)); für richtigen random generator use.
	exceptions


*/


