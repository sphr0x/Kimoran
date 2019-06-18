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
	EVTL srand(time(NULL)); für richtigen random generator use.
	exceptions



	probleme : 
	
	berechnung der taler stimmt nicht -> 
	+ statt - / double in int /

	9 statt 8 brücken

	alle tunnel geht nicht

	alle fähren geht nicht

	std::string UI::checkInput(std::string input):
	liest keine gültigen dateien -> immer cin.fail(); execution
	(exception bei keiner bzw zu kurzen eingaben)

*/


