#include <iostream>
#include "Graph.h"
#include "Route.h"
#include "Spieler.h"
#include "Verbindung.h"
#include "UI.h"



int main()
{
	UI prog;

	/*
	std::string a = "C23_Projekt_19SS_Inseln.txt";		// test build graph+player -> ok !
	Graph* karte = new Graph;
	std::vector<Spieler*> players;
	prog.readMAP(*karte,a,players);
	for (auto edge : karte->getEdges()) std::cout << edge->toString() << std::endl;
	delete karte;
	*/


	prog.menu();
	system("pause");
	return 0;
}
/* 2do

	(EVTL srand(time(NULL)); für richtigen random generator use.
	exceptions)



	probleme : 
	
	berechnung der taler stimmt nicht -> 
	+ statt - / double in int /

	KI spielzug fehlt

	9 statt 8 brücken

	alle tunnel geht nicht

	alle fähren geht nicht

	case 1 fix:

	delete graph, sonst double node push etc.

	std::string UI::checkInput(std::string input):
	(exception bei ungültigen eingaben)

*/


