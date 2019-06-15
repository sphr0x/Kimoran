#pragma once
#include <iostream>
#include "Graph.h"
#include "Verbindung.h"
#include "Spieler.h"
#include <string>
#include <iomanip>			// setw etc..
#include <stdlib.h>			// rand
#include <Windows.h>		// Sleep
#include <fstream>			// file

class UI
{
public:
	void dateiEinlesen();		// rückgabe typ ?
	void dateiSchreiben();		// -"-
	Node* getStart(Node & start) { return &start; };
	void menu(Graph& karte, Spieler bla, Node& schatz,Node& start);
	void karte(Graph & karte);			// ungerichteter graph
	std::string checkInput(std::string input);
	int checkInput(int input);
	void printMap(Graph& karte);
	void setnameofPlayer(Spieler& mensch,std::string name);
	bool foundTreasure(Node& location);
	UI();
	~UI();
};

