#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include <direct.h>	//für Debug: Arbeitsverzeichnis

#include "FktDisp.h"	//Bildschirmanzeigen für Galgenraten
#include "FktGR.h"		//Funktionen für Galgenraten
#include "FktK.h"		//allgemeine Funktionen
#include "FktProtokoll.h"	//Funktionen für TippProtokoll
#include "FktWoerterbuch.h" //Funktionen für das Wörterbuch


void main(){
	
	time_t t; time(&t); srand((unsigned int)t);	// Zufallsgenerator initialisieren
	int d = 0;	// Debugausgabe standardmäßig aus
	//if(d)printf("Debug: Arbeitsverzeichnis ist:\n %s\n\n",_getcwd(NULL,0));

	// Initialisierung der verketten Listen Wort, TProtokoll, WProtokoll

	struct wort *Woerter;				// Wortliste
	Woerter = (struct wort*) calloc(1,sizeof(*Woerter));
	//if (Woerter) memset(Woerter,0,sizeof(*Woerter));
	if(Woerter == NULL) { printf("Kein Arbeitsspeicher vorhanden.\n"); Taste(d); exit(1);}
	*Woerter = readWoerter(NULL, d);		// Wortliste einlesen

	struct TProtokoll *TippProtokoll;		// TippProtokoll
	TippProtokoll = (struct TProtokoll*) calloc(1,sizeof(*TippProtokoll));
	//if (WortProtokoll) memset(WortProtokoll,0,sizeof(*WortProtokoll));
	if(TippProtokoll == NULL) { printf("Kein Arbeitsspeicher vorhanden.\n"); Taste(d); exit(1);}

	struct WProtokoll *WortProtokoll;		// WortProtokoll
	WortProtokoll = (struct WProtokoll*) calloc(1,sizeof(*WortProtokoll));
	//if (WortProtokoll) memset(WortProtokoll,0,sizeof(*WortProtokoll));
	if(WortProtokoll == NULL) { printf("Kein Arbeitsspeicher vorhanden.\n"); Taste(d); exit(1);}
	*WortProtokoll = lesenWProtokoll(NULL,d);



	int GrossKlein = 1;					// Groß/Kleinschreibung 1 für unbeachtet -1 für beachtet
	int beenden = 0;
	char WahlTaste = ' ';

	while (beenden != 1){	//Bleibe im Hauptmenu bis beenden gesetzt ist
		
		DispHauptmenu(GrossKlein, d);						// Hauptmenu zeichnen

		switch (Taste(d)){									// weiter je nach Tastendruck

		case 'n':	if(d)printf("Debug: neues Spiel.\n");

			WahlTaste = ' ';
			while (WahlTaste == ' '){					// Schleife solange nach dem Spiel Leertaste gedrückt -> neues Spiel starten

				TippProtokoll = (struct TProtokoll*) calloc(1,sizeof(*TippProtokoll));
				if(TippProtokoll == NULL) { printf("Kein Arbeitsspeicher vorhanden.\n"); Taste(d); exit(1);}
				//if (TippProtokoll) memset(TippProtokoll,0,sizeof(*TippProtokoll));
				TippProtokoll->Nummer = 0;	

				*TippProtokoll = neuGalgen(Woerter, TippProtokoll, GrossKlein, (&letztesWProtokoll(&WortProtokoll,d))->Nummer+1, d);				//neues Spiel

				if (TippProtokoll->Nummer != NULL){
					hinzuWProtokoll(&WortProtokoll,&TippProtokoll,d);									//nach Spiel TippProtokoll zum WortProtokoll hinzufügen
					if(d)printf("Debug: Das waren %d Tipps.\n", anzTProtokollTipps(&TippProtokoll,d));
				}else{
					if(d)printf("Debug: Kein TippProtokoll angehangen.\n");
				}

				WahlTaste = 0;
				while ((WahlTaste != '\r') && (WahlTaste != ' ')){	// Mit Enter zum Hauptmenu, Leertaste weiteres Wort
					WahlTaste = Taste(d);
				}
			}


			break;		

		case 'w':	if(d)printf("Debug: eine eigene Wortliste benutzen\n"); 
			*Woerter=eigeneWortliste(d); break;											//andere Wortliste

		case 'p':	if(d)printf("Debug: ein anderes Protokoll laden\n"); 
			WortProtokoll = &eigenesWProtokoll(d);	break;							//anderes Protokoll

		case 's':	if(d)printf("Debug: Protokoll speichern unter\n"); 
			eignesSpeicherzielWProtokoll(WortProtokoll,d);	break;							//anderes Protokoll

		case 'g':	if(d)printf("Debug: Gro%c/Kleinschreibung umschaltet\n", unsigned char(225)); 
			GrossKlein=GrossKlein*-1; break;				//GK umschalten

		case 'b':	if(d)printf("Debug: Ende des Programms\n"); 
			beenden=1;
			break;								//Ende

		case 27:	if(d)printf("Debug: Ende des Programms (Esc)\n"); 
			beenden=1;
			break;								//Ende (Esc-Taste)

		case 'a':	if(d)printf("Debug: geratene W\224rter anzeigen\n"); 
			anzeigenWoerter(WortProtokoll,d);		//Wortprotokoll anzeigen
			break;								

		case 'v':	if(d)printf("Debug: Ratevorgang anzeigen\n"); 
			anzeigenTippVerlauf(WortProtokoll,d);		//Rateverlauf anzeigen
			break;

		case 'l':	if(d)printf("Debug: Ratevorgang l\224schen\n");
			*WortProtokoll = loeschenTippVerlauf(WortProtokoll,d);		//Rateverlauf anzeigen
			break;	

		case 'd':	if(d){d=NULL;}else{d=1;} if(d)printf("\n\nDebuginganzeige umgeschaltet\n\n"); break;	

		default :	if(d)printf("Debug: falsche Taste\n");	//weiter im Hauptmenu
		}
	}
	if(d){printWProtokoll(&WortProtokoll,d); Taste(d);}

	//speichernWProtokoll(&WortProtokoll, "protokoll.log" ,d);	//Protokoll speichern falls es nicht leer ist
	if(WortProtokoll->Nummer != NULL) eignesSpeicherzielWProtokoll(WortProtokoll,d); // mit Dateinamenswahl

	free(Woerter);			// genutzten Speicherbereich freigeben
	free(WortProtokoll);
	free(TippProtokoll);

	return;
}