#ifndef FktProtokoll // Präprozessoranweisung
#define FktProtokoll

// ''''''''''''''''''''''''''''''''''''''
// Funktionen für die Protokollliste
// ''''''''''''''''''''''''''''''''''''''

struct TProtokoll {		// TippProtkoll
	int Nummer;						// Laufende Nummer eines geratenen Wortes  negative Nummer: Groß/Kleinschreibung beachten 
	char Suchwort[28];				// Das zu ratende Wort
	char Eingabe[28];				// Eingegebene Buchstabe
	struct TProtokoll *prev;		// Pointer vorheriges Element
	struct TProtokoll *next;		// Pointer nächstes Element
};

struct TProtokoll hinzuTProtokoll(struct TProtokoll **TippProtokoll, int Nummer, char Suchwort[28], char Eingabe[28], int debug);	// Fügt einen Protokolleintrag hinzu
struct TProtokoll entferneTProtokoll(struct TProtokoll **TippProtokoll, int debug);	// entfernt das letzte Element aus der Liste, gibt Liste zurück

int anzTProtokollTipps(struct TProtokoll **TippProtokoll, int debug);				// gibt die Anzahl an Tipps zurück

void printTProtokoll(struct TProtokoll **TippProtokoll, int debug);					// print für ein TippProtokoll, gibt Anzahl der Rateversuche zurück



// ''''''''''''''''''''''''''''''''''''''
// Funktionen für die WortProtokollliste
// ''''''''''''''''''''''''''''''''''''''

struct WProtokoll {		// WortProtkoll
	int Nummer;						// Laufende Nummer 
	struct TProtokoll *TippProtokoll;	// Pointer zum TippProtokoll
	struct WProtokoll *prev;		// Pointer vorheriges Element
	struct WProtokoll *next;		// Pointer nächstes Element
};

struct WProtokoll hinzuWProtokoll(struct WProtokoll **WoerterProtokoll, struct TProtokoll **anzuhängendesTippProtokoll, int debug);	// ein TippProtokoll zum WortProtokoll hinzufügen, gibt das hinzugefügte zurück
struct WProtokoll entferneWProtokoll(struct WProtokoll **WoerterProtokoll, int debug);		// entfernt das letzte Element aus der Liste gibt Liste zurück
struct WProtokoll lesenWProtokoll(char* pfad, int debug);									// WProtokoll aus binärdatei lesen

int anzWProtokoll(struct WProtokoll **lst, int debug);										// Anzahl der TippProtokolle in einem WortProtokoll

void speichernWProtokoll(struct WProtokoll **s, char* pfad, int debug);						// WProtokoll nach pfad binär speichern
void printWProtokoll(struct WProtokoll **WortProtokoll, int debug);							// printTProtokoll für alle TippProtokolle in einem WortProtokoll
void printWProtokollEinzelwoerter(struct WProtokoll **WortProtokoll, int numMarkiert, int debug);			// alle TippProtokolle in einem WortProtokoll auflisten, mit optionalem Marker auf Wort->WortNummer


#endif