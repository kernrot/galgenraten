#ifndef FktDisp // Präprozessoranweisung
#define FktDisp

// ''''''''''''''''''''''''''''''''''''''
// Alles was auschließlich zeichnet
// ''''''''''''''''''''''''''''''''''''''

void DispHauptmenu(int GrossKlein, int debug);					// Zeigt das Hauptmenu an, GrossKlein für Anzeige der Groß/Kleinschreibung
void DispRaten(int Fehler, char* Wort, char* Zeichen, int debug);			// Ratebildschirm
void DispRatenVerlauf(int Fehler, char* Wort, char* Zeiche, int debug);	// modifizierter Ratebildschirm für Verlaufsanzeige
void DispGewonnen(int Fehler ,char* Wort, int debug);			// Bildschirm "Gewonnen"
void DispVerloren(int Fehler ,char* Wort, int debug);			// Bildschirm "Verloren"
void DispWortlistenEingabe(int debug);							// Bildschrim für eigene Wortliste
void DispProtokollEingabe(int debug);							// Bildschrim für anderes Protokoll
void DispProtokollSpeichern(int debug);							// Bildschrim um Protokoll zu speichern

void teilGalgen(int Fehler);		// Galgen und Männlein zeichen
void teilTitel(int debug);			// Titelzeile ausgeben
void teilWort(char* gesuchtesWort, char* Zeichen);	//Gibt die bisher erratenen Zeichen (in Zeichen) des Worts (in Wort) aus


void nachR();		// 7x \t Einrücken
void nachM();		// 3x \t Einrücken

#endif

