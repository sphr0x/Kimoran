#include <iostream>
#include "Graph.h"
#include "Route.h"
#include "Spieler.h"
#include "Verbindung.h"
#include "UI.h"

						/*		###	Projektaufgabe: Schatzsuche in Kimoran	###		*/

int main(){
	UI prog;

	prog.menu2();
	system("pause");
	return 0;
}

/*
	2do:

	 UI::readMAP
	 : no value lager -> kein throw

*/

/*	
	mögliche Stil - Verbesserung
	: m_membervari
	: s_staticmember  // zugriff auf s_xxx NUR mit Klasse::s_xxx
	: float vor double, bei kleinen datenwerten ( float a = 0.006f )
	: Eigene Klassen sollten nur in eine Richtung implizit konvertierbar sein. Das Schlüsselwort
	  explizit sollte bewusst eingesetzt werden. ( ??? )
	: virtual bei basis fkt, die überschrieben werden
	: Fehler nur mit exceptions abfangen -> eigene Exceptionklasse -> klasse werfen
	: versuchen nichts doppelt schreiben zu müssen

	speziell hier 
	: class Insel von node ableiten

*/


/*		
	Vorgegebene Datei: projekt.txt
	Testdatei:			 insel.txt
*/


