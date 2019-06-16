#pragma once
#include <string>
#include <iostream>
#include "Graph.h"
#include "Verbindung.h"
#include <string>

class Spieler
{
private:
	int geld;
	std::string name;
	Node* standort;
public:
	void spielzug();
	std::string getName() { return name; };
	void setName(std::string name);
	int getGeld() { return geld; };
	void setGeld(int gold);
	Node* getStandort();
	void setStandort(Node& location);
	Spieler(int taler, Node& start, std::string eingabe = "KI");
	~Spieler();
};

