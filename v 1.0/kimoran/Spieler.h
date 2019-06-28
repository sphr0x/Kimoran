#pragma once
#include <string>
#include <iostream>
#include "Graph.h"
#include "Verbindung.h"
#include <string>
#include "UI.h"
#include "Insel.h"


class Spieler
{
private:
	int m_geld;
	std::string m_name;
	Insel* m_standort;
public:
	std::string getName()const { return m_name; };
	void setName(std::string name);
	int getGeld()const { return m_geld; };
	void setGeld(int gold);
	Insel* getStandort()const;
	void setStandort(Insel& location);
	Insel* setLocation(int& location, Graph& karte);								// sync nodes to position
	int lootLagerOnPath(std::deque<Insel*>& path);											// check if Lager is in path and set Lager gold to 0
	void printTurn(std::deque<Insel*>& actualRoute, double kosten, Insel& dest);
	void deleteTurn(std::deque<Insel*>& actualRoute);
	Spieler(Insel& start, int taler, std::string eingabe = "KI");
	~Spieler();
};

