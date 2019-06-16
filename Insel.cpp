#include "Insel.h"
#include <string>

// iwie in node einfügen alles
bool Insel::hasStorage(int geld)
{
	if (geld == 0) {
		return false;
	}
	else {
		return true;
	}
}

void Insel::setTaler(int geld)
{
}

int Insel::getTaler()
{
	return 0;
}

void Insel::setGoal(std::string goal)
{
	ziel = goal;
}

Insel::Insel(std::string id, int geld)
	:Node(),taler(geld){

	if (this->hasStorage(geld)) {
		this->taler = geld;
	}
}


Insel::~Insel()
{
}
