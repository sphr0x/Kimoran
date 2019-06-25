#include <iostream>
#include "Graph.h"
#include "Spieler.h"
#include "Verbindung.h"
#include "UI.h"
#include "Insel.h"


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
	mögliche Stil - Verbesserung - best practice
	X m_membervari
	: s_staticmember  // zugriff auf s_xxx NUR mit Klasse::s_xxx
	: float vor double, bei kleinen datenwerten ( float a = 0.006f )
	: Eigene Klassen sollten nur in eine Richtung implizit konvertierbar sein. Das Schlüsselwort
	  explizit sollte bewusst eingesetzt werden. ( ??? )
	: virtual bei basis fkt, die überschrieben werden
	: Fehler nur mit exceptions abfangen -> eigene Exceptionklasse -> klasse werfen
	: versuchen nichts doppelt schreiben zu müssen

	speziell hier 
	X wenn comp nciht genug geld hat, dann kein output 
	X class Insel von node ableiten
	X lager geld info sollte erst NACH "spielzug: computer/mensch" kommen
	X eine insel-klasse statt der node - modifikation
	X eine fileread klasse ( = parsing )
	X eine exception klass
	: UI einige funktionen in private verschiebe
	X ein gutes UML erstellen
	: dokumentation mit screnns XD 
	(
	Alle Exceptions -> n
	Einlesen mit eigenener Datei -> 1
	Ausgabe der Welt -> 2
	Spielzug -> 10
	: erfolgreicher Zug
	: erfolgloser Zug
	: besuchte Lager
	: gefundener Schatz Mensch
	: gefundener Schatz Computer
	: Der Fall: Ein Spieler hat kein Geld mehr
	: Zug des Computers
	: Gewanderter Pfad
	: Beenden des Programms
	: Zum Abfangen von falschen bzw. fehlerhaften Eingaben innerhalb der Menüs wird die Funktion "int UI::checkInput" bzw "int UI::checkInputGameplay" genutzt 
	  und nicht das Exception-Prinzip.
		: 1-2 tests
	)
	: wenn out of money -> sofort beenden




2>UI.cpp
2>c:\users\uni\source\repos\kimoran\kimoran\ui.cpp(42): warning C4101: "a": Unreferenzierte lokale Variable
2>c:\users\uni\source\repos\kimoran\kimoran\ui.cpp(358): warning C4244: "Argument": Konvertierung von "time_t" in "unsigned int", möglicher Datenverlust
2>c:\users\uni\source\repos\kimoran\kimoran\ui.cpp(397): warning C4244: "Argument": Konvertierung von "double" in "int", möglicher Datenverlust
2>c:\users\uni\source\repos\kimoran\kimoran\ui.cpp(399): warning C4244: "Argument": Konvertierung von "time_t" in "unsigned int", möglicher Datenverlust

*/


/*		
	Vorgegebene Datei: projekt.txt
	Testdatei:			 insel.txt
*/


