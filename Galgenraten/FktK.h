#ifndef FktK // Pr�prozessoranweisung
#define FktK

// ''''''''''''''''''''''''''''''''''''''
// Allgemein n�tzlich Funktionen
// ''''''''''''''''''''''''''''''''''''''

int char2intZahlenTasten(char c);	// zu einer Zahlentaste das entsprechende int zur�ckgeben
int intPositiv (int Zahl);	// Integer postiv machen
int Zufall(int max);	// Zufallszahl zwischen 0 und max
char Taste(int debug);	// Gibt Tastendruck zur�ck							
char* charsKlein(char *Zeichen);	// gibt einen Buchstaben kleingeschrieben zur�ck
char* charsGK(char *Zeichen, int klein);	// wie oben, jedoch nur bei klein = 1
int checkPfad(char* Pfad);	//Pr�ft eine Zeichenkette (Dateiname) auf Sonderzeichen, return 0 wenn Sonderzeichen enthalten.

// ''''''''''''''''''''''''''''''''''''''
// Funktionen zur Zeichenkettenverarbeitung
// ''''''''''''''''''''''''''''''''''''''

int lenWort(char*Zeichenkette);	// Wortl�nge
int vorhandeneZeichen(char *suchZeichen, char *Zeichenkette);	// Testet ob Zeichen in Zeichenkette vorhanden sind, return Anzahl
int fehlendeZeichen(char *Wort, char *Zeichen);	// Pr�ft wie viele Zeichen in Wort und nicht in Zeichen enthalten sind.
int unbenutzteZeichen(char *Wort, char *Zeichen);	// Pr�ft wie viele Zeichen aus Zeichen nicht in Wort enthalten sind.

// Ascii-Art Zeug
void printSW(char line[80]);	// Zeichenfunktion f�r einfache Bildschirmgrafik mit #-_ als ausgef�llte Bl�cke

#endif

