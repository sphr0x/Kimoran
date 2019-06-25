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
	std::string getName() { return m_name; };
	void setName(std::string name);
	int getGeld() { return m_geld; };
	void setGeld(int gold);
	Insel* getStandort();
	void setStandort(Insel& location);
	Insel* setLocation(int& location, Graph& karte);
	int isLager2(std::deque<Insel*>& path);
	void printTurn(std::deque<Insel*>& actualRoute, double kosten, Insel& dest);
	void deleteTurn(std::deque<Insel*>& actualRoute);
	Spieler(Insel& start, int taler, std::string eingabe = "KI");
	~Spieler();
};

