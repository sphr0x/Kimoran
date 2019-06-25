#pragma once
#include <iostream>
#include "Spieler.h"
#include "Graph.h"
#include "Verbindung.h"
#include "Insel.h"
#include "Filereading.h"
#include <string>
#include <iomanip>				// setw etc..
#include <stdlib.h>				// rand
#include <Windows.h>			// Sleep
#include <fstream>				// file
#include <sstream>				// osstream
#include <stdlib.h>				// srand, rand 
#include <time.h>				// time 
#include <stdexcept>			// class invalid_argument // std::atoi

class Spieler;
class UI
{
public:
	Insel* getStart(Insel & start) { return &start; };
	int checkInput(int input);																		// control input of int
	//void setnameofPlayer(Spieler& mensch,std::string name);										// optional: set players name
	int checkInputGameplay(int input, int islands);																		// control input of int

	std::string printIntro();
	std::string printInfo();
	void delay(std::string a);																		// für RPG text speed
	void MapMenu(Graph& karte);																		// map submenu: node / edge / back 
	std::string printMapMenu();
	bool gameOver(bool end){return end;};															// game over fkt
	void menu2();																					// 1st menu: file / quit
	void menu3(Graph& karte,std::vector<Spieler*> players, Insel& ziel);								// 2nd menu: submenu map / play / quit				
	void gameplay(Graph& karte, std::vector<Spieler*> players, Insel& ziel);							// cpu / human turn
	UI();
	~UI();
};

