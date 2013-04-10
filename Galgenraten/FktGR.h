#ifndef FktGR // Präprozessoranweisung
#define FktGR

struct TProtokoll neuGalgen(struct wort *Wortliste, struct TProtokoll *Protokoll, int GrossKlein, int WortNummer, int debug);	// einen neuen Rateversuch starten
struct wort eigeneWortliste(int debug);				// laden einer eigenen Wortliste (Ratewörtern), gibt diese zurück
struct WProtokoll eigenesWProtokoll(int d);			// laden eines eigenen Protokolls, gibt dieses zurück
void eignesSpeicherzielWProtokoll(struct WProtokoll *WortProtokoll, int debug);  // Speichern eines WortProtokolls mit wählbarem Dateiname

void anzeigenWoerter(struct WProtokoll *WortProtokoll, int debug);		// gibt alle bisher im Protokoll enthaltenen Wörter aus
void anzeigenTippVerlauf(struct WProtokoll *WortProtokoll, int debug);	// gibt einen Rateverlauf für ein aus dem WPr wählbares Wort aus
void abspielenTippVerlauf(struct TProtokoll *TippProtokoll, int debug); 
struct WProtokoll loeschenTippVerlauf(struct WProtokoll *WortProtokoll, int debug);

#endif

