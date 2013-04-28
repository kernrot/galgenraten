#ifndef FktGR // Präprozessoranweisung
#define FktGR

struct wort eigeneWortliste(int debug);		// einlesen einer eigenen Wortliste, gibt diese zurück
struct WProtokoll eigenesWProtokoll(int debug);	// laden eines eigenen Protokolls, gibt dieses zurück
void eignesSpeicherzielWProtokoll(struct WProtokoll *WortProtokoll, int debug);	// Speichern eines WortProtokolls mit wählbarem Dateiname

struct TProtokoll neuGalgen(struct wort *Wortliste, struct TProtokoll *TippProtokoll, int GrossKlein, int Nummer, int debug); // ein neues Spiel starten
void anzeigenWoerter(struct WProtokoll *WortProtokoll, int debug);				// Anzeigen aller geratenen Wörter
void anzeigenTippVerlauf(struct WProtokoll *WortProtokoll, int debug);			// Anzeigen des Rateverlaufs für ein Wort
struct WProtokoll loeschenTippVerlauf(struct WProtokoll *WortProtokoll, int debug);	// Löschen eines Rateverlaufs

int Wortauswahl(struct WProtokoll *WortProtokoll, int debug);					// Auswahldialog für ein Wort im WortProtokoll

#endif