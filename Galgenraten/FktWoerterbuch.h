#ifndef FktWoerterbuch // Präprozessoranweisung
#define FktWoerterbuch

// ''''''''''''''''''''''''''''''''''''''
// Funktionen zur Wortliste für die Ratewörter
// ''''''''''''''''''''''''''''''''''''''

struct wort {
    char Zeichen[28];		// der Text des Worts
    struct wort *next;		// das nächste Wort
};

struct wort readWoerter(char* pfad, int debug);			// Wörter aus einer Datei (pfad) einlesen
void hinzuWort(struct wort **lst, char Zeichen[28]);	// Wort zur Wortliste hinzufügen
void printWoerter(struct wort *l);						// Ausgabe aller Wörter einer Wortliste
int anzWoerter(struct wort *l);							// Rückgabe der Wortanzahl einer Wortliste


char ansi2ascii(char ansi);								// Zeichensatz von Ansi (txt) nach Ascii (für Umlaute)

#endif