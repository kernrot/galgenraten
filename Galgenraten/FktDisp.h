#ifndef FktDisp // Pr�prozessoranweisung
#define FktDisp

// ''''''''''''''''''''''''''''''''''''''
// Alles was auschlie�lich zeichnet
// ''''''''''''''''''''''''''''''''''''''

void DispHauptmenu(int GrossKlein, int debug);					// Zeigt das Hauptmenu an, GrossKlein f�r Anzeige der Gro�/Kleinschreibung
void DispRaten(int Fehler, char* Wort, char* Zeichen, int debug);			// Ratebildschirm
void DispRatenVerlauf(int Fehler, char* Wort, char* Zeiche, int debug);	// modifizierter Ratebildschirm f�r Verlaufsanzeige
void DispGewonnen(int Fehler ,char* Wort, int debug);			// Bildschirm "Gewonnen"
void DispVerloren(int Fehler ,char* Wort, int debug);			// Bildschirm "Verloren"
void DispWortlistenEingabe(int debug);							// Bildschrim f�r eigene Wortliste
void DispProtokollEingabe(int debug);							// Bildschrim f�r anderes Protokoll
void DispProtokollSpeichern(int debug);							// Bildschrim um Protokoll zu speichern

void teilGalgen(int Fehler);		// Galgen und M�nnlein zeichen
void teilTitel(int debug);			// Titelzeile ausgeben
void teilWort(char* gesuchtesWort, char* Zeichen);	//Gibt die bisher erratenen Zeichen (in Zeichen) des Worts (in Wort) aus


void nachR();		// 7x \t Einr�cken
void nachM();		// 3x \t Einr�cken

#endif

