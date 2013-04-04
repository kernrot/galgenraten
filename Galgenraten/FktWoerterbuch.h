#ifndef FktWoerterbuch // Pr�prozessoranweisung
#define FktWoerterbuch

// ''''''''''''''''''''''''''''''''''''''
// Funktionen zur Wortliste f�r die Ratew�rter
// ''''''''''''''''''''''''''''''''''''''

struct wort {
    char Zeichen[28];		// der Text des Worts
    struct wort *next;		// das n�chste Wort
};

struct wort readWoerter(char* pfad, int debug);			// W�rter aus einer Datei (pfad) einlesen
void hinzuWort(struct wort **lst, char Zeichen[28]);	// Wort zur Wortliste hinzuf�gen
void printWoerter(struct wort *l);						// Ausgabe aller W�rter einer Wortliste
int anzWoerter(struct wort *l);							// R�ckgabe der Wortanzahl einer Wortliste


char ansi2ascii(char ansi);								// Zeichensatz von Ansi (txt) nach Ascii (f�r Umlaute)

#endif