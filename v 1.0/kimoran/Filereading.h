#pragma once
#include "Graph.h"
#include "Insel.h"
#include "Spieler.h"
#include <string>
#include <stdexcept>			// class invalid_argument // std::atoi
#include "Exception.h"

class Spieler;

class Filereading
{
public:
	Insel* readMAP(Graph & karte, std::string& filename, std::vector<Spieler*>& players);			// einlesen von jeder datei
	Filereading();
	~Filereading();
};

