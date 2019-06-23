#pragma once
#include <string>
#include <iostream>
#include "Graph.h"
#include "Verbindung.h"
#include <string>
#include "UI.h"

class Spieler
{
private:
	int geld;
	std::string name;
	Node* standort;
public:
	std::string getName() { return name; };
	void setName(std::string name);
	int getGeld() { return geld; };
	void setGeld(int gold);
	Node* getStandort();
	void setStandort(Node& location);
	Node* setLocation(int& location, Graph& karte);
	void isLager2(std::deque<Node*>& path);
	void printTurn(std::deque<Node*>& actualRoute, double kosten, Node& dest);
	void deleteTurn(std::deque<Node*>& actualRoute);
	Spieler(Node& start, int taler, std::string eingabe = "KI");
	~Spieler();
};

