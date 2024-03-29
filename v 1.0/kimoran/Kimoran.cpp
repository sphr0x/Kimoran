#include <iostream>
#include "Graph.h"
#include "Spieler.h"
#include "Verbindung.h"
#include "UI.h"
#include "Insel.h"


						/*		###	Projektaufgabe: Schatzsuche in Kimoran	###		*/

int main(){
	UI prog;

	prog.mainMenu();
	system("pause");
	return 0;
}

/*
	2do:

	 UI::readMAP
	 X no value lager -> kein throw

*/

/*	
	m�gliche Stil - Verbesserung - best practice
	X m_membervari
	: s_staticmember  // zugriff auf s_xxx NUR mit Klasse::s_xxx
	: float vor double, bei kleinen datenwerten ( float a = 0.006f )
	: Eigene Klassen sollten nur in eine Richtung implizit konvertierbar sein. Das Schl�sselwort
	  explizit sollte bewusst eingesetzt werden. ( ??? )
	: virtual bei basis fkt, die �berschrieben werden
	: Fehler nur mit exceptions abfangen -> eigene Exceptionklasse -> klasse werfen
	: versuchen nichts doppelt schreiben zu m�ssen

	speziell hier 
	X wenn comp nciht genug geld hat, dann kein output 
	X class Insel von node ableiten
	X lager geld info sollte erst NACH "spielzug: computer/mensch" kommen
	X eine insel-klasse statt der node - modifikation
	X eine fileread klasse ( = parsing )
	X eine exception klass
	X UI einige funktionen in private verschieben ( alle, bis auf mainMenu )
	X alle fkt, die nix ver�ndern -> const
	X ein gutes UML erstellen
		X alle const raus
		X neue ver�nderungen mit paint berichtigen 
		X static unterschreichen
	X dokumentation mit screnns XD 
	(
	Alle Exceptions -> n
	Einlesen mit eigenener Datei -> 1
	Ausgabe der Welt -> 2
	Spielzug -> 10
	X erfolgreicher Zug
	X erfolgloser Zug
	X besuchte Lager
	X gefundener Schatz Mensch
	X gefundener Schatz Computer
	X Der Fall: Ein Spieler hat kein Geld mehr
	X Zug des Computers
	X Gewanderter Pfad
	X Beenden des Programms
	X Zum Abfangen von falschen bzw. fehlerhaften Eingaben innerhalb der Men�s wird die Funktion "int UI::checkInput" bzw "int UI::checkInputGameplay" genutzt 
	  und nicht das KimoranException-Prinzip.
		X 1-2 tests
	)
	X wenn out of money -> sofort beenden
	X UI.cpp  Z 258 if player->name  == computer -> info ( berechne m�glichen CPU zug ! )
	X set name fkt l�schen aus UI



	evtl verbessern:

2>UI.cpp
2>c:\users\uni\source\repos\kimoran\kimoran\ui.cpp(42): warning C4101: "a": Unreferenzierte lokale Variable
2>c:\users\uni\source\repos\kimoran\kimoran\ui.cpp(358): warning C4244: "Argument": Konvertierung von "time_t" in "unsigned int", m�glicher Datenverlust
2>c:\users\uni\source\repos\kimoran\kimoran\ui.cpp(397): warning C4244: "Argument": Konvertierung von "double" in "int", m�glicher Datenverlust
2>c:\users\uni\source\repos\kimoran\kimoran\ui.cpp(399): warning C4244: "Argument": Konvertierung von "time_t" in "unsigned int", m�glicher Datenverlust

*/


/*		
	Vorgegebene Datei: projekt.txt
	Testdatei:			 insel.txt
*/


