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
	Node* spielzug();
	std::string getName() { return name; };
	void setName(std::string name);
	int getGeld() { return geld; };
	void setGeld(int gold);
	Node* getStandort();
	void setStandort(Node& location);
	Spieler(Node& start, int taler, std::string eingabe = "KI");
	~Spieler();
};

