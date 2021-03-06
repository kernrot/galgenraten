#ifndef FktGR // Pr�prozessoranweisung
#define FktGR

struct TProtokoll neuGalgen(struct wort *Wortliste, struct TProtokoll *Protokoll, int GrossKlein, int WortNummer, int debug);	// einen neuen Rateversuch starten
struct wort eigeneWortliste(int debug);				// laden einer eigenen Wortliste (Ratew�rtern), gibt diese zur�ck
struct WProtokoll eigenesWProtokoll(int d);			// laden eines eigenen Protokolls, gibt dieses zur�ck
void eignesSpeicherzielWProtokoll(struct WProtokoll *WortProtokoll, int debug);  // Speichern eines WortProtokolls mit w�hlbarem Dateiname

int Wortauswahl(struct WProtokoll *WPr, int d);	// Anzeige der interaktiven Wortauswahlliste, gibt die Laufende Nummer des Worts zur�ck, 0 f�r nicht gefunden, -1 f�r Abbruch
void anzeigenWoerter(struct WProtokoll *WortProtokoll, int debug);		// gibt alle bisher im Protokoll enthaltenen W�rter aus
void anzeigenTippVerlauf(struct WProtokoll *WortProtokoll, int debug);	// gibt einen Rateverlauf f�r ein aus dem WPr w�hlbares Wort aus
void abspielenTippVerlauf(struct TProtokoll *TippProtokoll, int debug);  // Zeigt den TippVerlauf eines Wortes (TPr)
struct WProtokoll loeschenTippVerlauf(struct WProtokoll *WortProtokoll, int debug); // l�scht einen TippVerlauf, gibt Liste zur�ck

#endif

