#pragma once
#include <iostream>
#include "Spieler.h"
#include "Graph.h"
#include "Verbindung.h"
#include <string>
#include <iomanip>			// setw etc..
#include <stdlib.h>			// rand
#include <Windows.h>		// Sleep
#include <fstream>			// file
#include <sstream>			// osstream
#include <filesystem>		// file next try
class Spieler;
class UI
{
public:
	Node* getStart(Node & start) { return &start; };
	void menu();
	Node* readMAP(Graph & karte, std::string& filename, std::vector<Spieler*>& players);			// ungerichteter graph
	std::string checkInput(std::string input);
	int checkInput(int input);
	void setnameofPlayer(Spieler& mensch,std::string name);
	bool foundTreasure(Node& location);
	void printMenu();
	//bool isLager(Node& lager);
	//void printTurn(std::deque<Node*>& actualRoute, double kosten, Node& dest,Spieler& mensch);
	//void deleteTurn(std::deque<Node*>& actualRoute);
	void printIntro();
	void printInfo();
	void delay(std::string a);				// für RPG text speed
	void MapMenu(Graph& karte);
	void printMapMenu();
	bool gameOver(bool end){return end;};
	UI();
	~UI();
};

