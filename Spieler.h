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
	int spielzug(Graph& karte, std::deque<Node*>& path);
	std::string getName() { return name; };
	void setName(std::string name);
	int getGeld() { return geld; };
	void setGeld(int gold);
	Node* getStandort();
	void setStandort(Node& location);
	Node* setLocation(int& location, Graph& karte);
	bool isLager(Node& ziel, Graph& karte);
	void isLager2(std::deque<Node*>& path);
	void printTurn(std::deque<Node*>& actualRoute, double kosten, Node& dest);
	void deleteTurn(std::deque<Node*>& actualRoute);
	//bool foundTreasure(Node& location);
	Spieler(Node& start, int taler, std::string eingabe = "KI");
	~Spieler();
};

