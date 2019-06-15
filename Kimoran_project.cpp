#include <iostream>
#include "Graph.h"
#include "Route.h"
#include "Spieler.h"
#include "Verbindung.h"
#include "UI.h"

void setMAP(Graph & karte);

int main()
{
	UI prog;
	Graph* karte = new Graph; // graph später in UI
	prog.karte(*karte);
	prog.menu();

	delete karte;
	system("pause");
	return 0;
}


void setMAP(Graph & karte){	// später in UI

	Node* kim = new Node("Kimoran_Berg");
	Node* ask = new Node("Askhora");
	Node* bera = new Node("Beramorin");
	Node* ost = new Node("Ostergaard");
	Node* uth = new Node("Uthenwold");
	Verbindung* t1 = new Verbindung('t',*bera,*ost);
	Verbindung* b1 = new Verbindung('b',*bera,*ost);
	Verbindung* b2 = new Verbindung('b',*ost, *ask);
	Verbindung* f1 = new Verbindung('f', *uth, *kim);
	Verbindung* f2 = new Verbindung('f', *uth, *ask);
	Verbindung* t2 = new Verbindung('t', *ask, *kim);
	Verbindung* b3 = new Verbindung('b', *ask, *kim);
	Verbindung* b4 = new Verbindung('b', *kim, *bera);
	Verbindung* t3 = new Verbindung('t', *ask, *bera);

	Verbindung* t4 = new Verbindung('t', *ost, *bera);
	Verbindung* b5 = new Verbindung('b',*ost,*bera);
	Verbindung* b6 = new Verbindung('b',*ask, *ost);
	Verbindung* f3 = new Verbindung('f',*kim, *uth);
	Verbindung* f4 = new Verbindung('f',*ask, *uth);
	Verbindung* t5 = new Verbindung('t',*kim, *ask);
	Verbindung* b7 = new Verbindung('b',*kim, *ask);
	Verbindung* b8 = new Verbindung('b',*bera, *kim);
	Verbindung* t6 = new Verbindung('t',*bera, *ask);

	karte.addNode(kim);
	karte.addNode(ask);
	karte.addNode(bera);
	karte.addNode(ost);
	karte.addNode(uth);

	karte.addEdge(t1);
	karte.addEdge(t2);
	karte.addEdge(t3);
	karte.addEdge(f1);
	karte.addEdge(f2);
	karte.addEdge(b1);
	karte.addEdge(b2);
	karte.addEdge(b3);
	karte.addEdge(b4);

	karte.addEdge(t4);
	karte.addEdge(t5);
	karte.addEdge(t6);
	karte.addEdge(f3);
	karte.addEdge(f4);
	karte.addEdge(b5);
	karte.addEdge(b6);
	karte.addEdge(b7);
	karte.addEdge(b8);
	/*
		Tunnel Beramorin Ostergaard
		Bruecke Kimoran_Berg Askhora
		Bruecke Askhora Ostergaard
		Faehre Askhora Uthenwold
		Faehre Uthenwold Kimoran_Berg
		Tunnel Beramorin Askhora
		Bruecke Ostergaard Beramorin
		Bruecke Beramorin Kimoran_Berg
		Schatz Beramorin
		Lager Ostergaard 15 Taler
		Lager Uthenwold 3 Taler
		Mensch Kimoran_Berg 30 Taler
		Computer Kimoran_Berg 30 Taler
		*/
}
