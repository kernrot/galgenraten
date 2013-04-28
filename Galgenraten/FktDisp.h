#ifndef FktDisp // Präprozessoranweisung
#define FktDisp

// ''''''''''''''''''''''''''''''''''''''
// Bildschirmanzeigen für Galgenraten
// ''''''''''''''''''''''''''''''''''''''

void DispHauptmenu(int GrossKlein, int debug);
void DispRaten(int Fehler, char *Wort, char *Zeichen, int debug);
void DispRatenVerlauf(int Fehler, char *Wort, char *Zeichen, int debug);
void DispGewonnen(char *Wort, int debug);
void DispVerloren(char *Wort, int debug);
void DispStartbildschirm();

void DispWortlistenEingabe(int debug);
void DispProtokollEingabe(int debug);
void DispProtokollSpeichern(int debug);

// ''''''''''''''''''''''''''''''''''''''
// Bildschirmteile
// ''''''''''''''''''''''''''''''''''''''

void teilTitel(int debug);
void teilGalgen(int fehler);
void teilWort(char *Wort, char *Zeichen);
void nachM();
void nachR();

#endif