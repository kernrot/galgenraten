#ifndef FktGR // Präprozessoranweisung
#define FktGR

struct TProtokoll neuGalgen(struct wort *Wortliste, struct TProtokoll *Protokoll, int GrossKlein, int WortNummer, int debug); // einen neuen Rateversuch starten
struct wort eigeneWortliste(int debug);
struct WProtokoll eigenesWProtokoll(int d);

void anzeigenWoerter(struct WProtokoll *WortProtokoll, int debug);
void anzeigenVerlauf(struct WProtokoll *WortProtokoll, int debug);
void abspielenVerlauf(struct TProtokoll *TippProtokoll, int debug);

#endif

