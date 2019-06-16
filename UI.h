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
	void dateiEinlesen();		// r�ckgabe typ ?
	void dateiSchreiben();		// -"-
	Node* getStart(Node & start) { return &start; };
	void menu();
	Node* readMAP(Graph & karte, std::string& filename, std::vector<Spieler*>& players);			// ungerichteter graph
	std::string checkInput(std::string input);
	int checkInput(int input);
	void printMap(Graph& karte);
	void setnameofPlayer(Spieler& mensch,std::string name);
	bool foundTreasure(Node& location);
	void printMenu();
	bool isLager(Node& lager);
	void printTurn(std::deque<Node*>& actualRoute, double kosten, Node& dest,Spieler mensch);
	void deleteTurn(std::deque<Node*>& actualRoute);
	//void setMAP(Graph & karte);			// sp�ter weg
	void printIntro();
	void printInfo();
	UI();
	~UI();
};

