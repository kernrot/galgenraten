#ifndef FktProtokoll // Pr�prozessoranweisung
#define FktProtokoll

// ''''''''''''''''''''''''''''''''''''''
// Funktionen f�r die Protokollliste
// ''''''''''''''''''''''''''''''''''''''

struct TProtokoll {		// TippProtkoll
	int Nummer;						// Laufende Nummer eines geratenen Wortes  negative Nummer: Gro�/Kleinschreibung beachten 
	char Suchwort[28];				// Das zu ratende Wort
	char Eingabe[28];				// Eingegebene Buchstabe
	struct TProtokoll *prev;		// Pointer vorheriges Element
	struct TProtokoll *next;		// Pointer n�chstes Element
};

struct TProtokoll hinzuTProtokoll(struct TProtokoll **TippProtokoll, int Nummer, char Suchwort[28], char Eingabe[28], int debug);	// F�gt einen Protokolleintrag hinzu
struct TProtokoll entferneTProtokoll(struct TProtokoll **TippProtokoll, int debug);	// entfernt das letzte Element aus der Liste, gibt Liste zur�ck

int anzTProtokollTipps(struct TProtokoll **TippProtokoll, int debug);				// gibt die Anzahl an Tipps zur�ck

void printTProtokoll(struct TProtokoll **TippProtokoll, int debug);					// print f�r ein TippProtokoll, gibt Anzahl der Rateversuche zur�ck



// ''''''''''''''''''''''''''''''''''''''
// Funktionen f�r die WortProtokollliste
// ''''''''''''''''''''''''''''''''''''''

struct WProtokoll {		// WortProtkoll
	int Nummer;						// Laufende Nummer 
	struct TProtokoll *TippProtokoll;	// Pointer zum TippProtokoll
	struct WProtokoll *prev;		// Pointer vorheriges Element
	struct WProtokoll *next;		// Pointer n�chstes Element
};

struct WProtokoll hinzuWProtokoll(struct WProtokoll **WoerterProtokoll, struct TProtokoll **anzuh�ngendesTippProtokoll, int debug);	// ein TippProtokoll zum WortProtokoll hinzuf�gen, gibt das hinzugef�gte zur�ck
struct WProtokoll entferneWProtokoll(struct WProtokoll **WoerterProtokoll, int debug);		// entfernt das letzte Element aus der Liste gibt Liste zur�ck
struct WProtokoll lesenWProtokoll(char* pfad, int debug);									// WProtokoll aus bin�rdatei lesen

int anzWProtokoll(struct WProtokoll **lst, int debug);										// Anzahl der TippProtokolle in einem WortProtokoll

void speichernWProtokoll(struct WProtokoll **s, char* pfad, int debug);						// WProtokoll nach pfad bin�r speichern
void printWProtokoll(struct WProtokoll **WortProtokoll, int debug);							// printTProtokoll f�r alle TippProtokolle in einem WortProtokoll
void printWProtokollEinzelwoerter(struct WProtokoll **WortProtokoll, int numMarkiert, int debug);			// alle TippProtokolle in einem WortProtokoll auflisten, mit optionalem Marker auf Wort->WortNummer


#endif