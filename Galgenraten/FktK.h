#ifndef FktK // Präprozessoranweisung
#define FktK

// ''''''''''''''''''''''''''''''''''''''
// Allgemein nützlich Funktionen
// ''''''''''''''''''''''''''''''''''''''

int char2intZahlenTasten(char c);	// zu einer Zahlentaste das entsprechende int zurückgeben
int iPos (int Zahl);				// Integer postiv machen
int Zufall(int max);					// Zufallszahl zwischen 0 und max
char Taste(int debug);							// Gibt Tastendruck zurück							
char* charsKlein(char Zeichen[]);				// gibt einen Buchstaben kleingeschrieben zurück
char* charsGK(char Zeichen[], int klein);	// wie oben, jedoch nur bei klein = 1

// ''''''''''''''''''''''''''''''''''''''
// Funktionen zur Zeichenkettenverarbeitung
// ''''''''''''''''''''''''''''''''''''''

int lenWort(char[]);					// Wortlänge
int vorhandeneZeichen(char suchZeichen[], char Zeichenkette[]);	// Testet ob Zeichen in Zeichenkette vorhanden sind, return Anzahl
int fehlendeZeichen(char Wort[], char Zeichen[]); // Prüft wieviele Zeichen in Wort und nicht in Zeichen enthalten sind.
int unbenutzteZeichen(char Wort[], char Zeichen[]); // Prüft wieviele Zeichen aus Zeichen nicht in Wort enthalten sind.

// Ascii-Art Zeug
void printSW(char line[80]);

#endif

