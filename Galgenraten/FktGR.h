#ifndef FktGR // Präprozessoranweisung
#define FktGR

struct TProtokoll neuGalgen(struct wort *Wortliste, struct TProtokoll *Protokoll, int GrossKlein, int WortNummer, int debug); // einen neuen Rateversuch starten
struct wort eigeneWortliste(int debug);
struct WProtokoll eigenesWProtokoll(int d);
void eignesSpeicherzielWProtokoll(struct WProtokoll *WortProtokoll, int debug);

void anzeigenWoerter(struct WProtokoll *WortProtokoll, int debug);
void anzeigenTippVerlauf(struct WProtokoll *WortProtokoll, int debug);
void abspielenTippVerlauf(struct TProtokoll *TippProtokoll, int debug);
struct WProtokoll loeschenTippVerlauf(struct WProtokoll *WortProtokoll, int debug);

#endif

