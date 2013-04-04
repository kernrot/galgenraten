#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <direct.h>	//für Debug: Arbeitsverzeichnis
//#include <Windows.h>	// nur für Sleep()

#include "FktDisp.h"	//Bildschirmanzeigen für Galgenraten
#include "FktGR.h"		//Funktionen für Galgenraten
#include "FktK.h"		//allgemeine Funktionen
#include "FktProtokoll.h"	//Funktionen für TippProtokoll
#include "FktWoerterbuch.h" //Funktionen für das Wörterbuch

void maina(){
	while(true) Taste(1);
}

void mainb(){
	int d = 0;
	struct WProtokoll *Protokoll;		// WProtokolldatei
	struct TProtokoll *tProtokoll;		// TProtokolldatei
	Protokoll = (struct WProtokoll*) calloc(1,sizeof(*Protokoll));
	tProtokoll = (struct TProtokoll*) calloc(1,sizeof(*tProtokoll));


	Protokoll = &lesenWProtokoll("protokoll.log",d);
	tProtokoll = Protokoll->TippProtokoll;
	//entferneTProtokoll(&tProtokoll);
	//entferneWProtokoll(&Protokoll);
	//printWProtokoll(&Protokoll,d);
	speichernWProtokoll(&Protokoll, "protokoll3.log",d);
	printf("%d", anzWProtokoll(&Protokoll,d));
	Taste(d);
}

void main(){
	int d = 0;
	
	struct wort *Woerter;				// Wortliste
	Woerter = (struct wort*) calloc(1,sizeof(*Woerter));
	//if (Woerter) memset(Woerter,0,sizeof(*Woerter));
	*Woerter = readWoerter(NULL, d);

	struct TProtokoll *TippProtokoll;		// TippProtokoll
	
	struct WProtokoll *WortProtokoll;		// WortProtokoll
	WortProtokoll = (struct WProtokoll*) calloc(1,sizeof(*WortProtokoll));
	//if (WortProtokoll) memset(WortProtokoll,0,sizeof(*WortProtokoll));
	*WortProtokoll = lesenWProtokoll(NULL,d);



	int GrossKlein = 1;					// Groß/Kleinschreibung 1 für unbeachtet -1 für beachtet
	int beenden = 0;
	char WahlTaste = ' ';

	while (beenden != 1){
		//if(d)printf("Debug: Arbeitsverzeichnis ist:\n %s\n\n",_getcwd(NULL,0));
		DispHauptmenu(GrossKlein, d);						// Hauptmenu zeichnen

		switch (Taste(d)){									// weiter je nach Tastendruck

			case 's':	if(d)printf("Debug: neues Spiel.\n");
				
				WahlTaste = ' ';
				while (WahlTaste == ' '){					// Schleife solange nach dem Spiel Leertaste gedrückt -> neues Spiel starten

					TippProtokoll = (struct TProtokoll*) calloc(1,sizeof(*TippProtokoll));
					//if (TippProtokoll) memset(TippProtokoll,0,sizeof(*TippProtokoll));
					TippProtokoll->Nummer = 0;	
				
					*TippProtokoll = neuGalgen(Woerter, TippProtokoll, GrossKlein, anzWProtokoll(&WortProtokoll,d)+1, d);				//neues Spiel
				
					if (TippProtokoll->Nummer != NULL){
						hinzuWProtokoll(&WortProtokoll,&TippProtokoll,d);									//nach Spiel TippProtokoll zum WortProtokoll hinzufügen
						if(d)printf("Debug: Das waren %d Tipps.\n", anzTProtokollTipps(&TippProtokoll,d));
					}else{
						if(d)printf("Debug: Kein TippProtokoll angehangen.\n");
					}

					WahlTaste = 0;
					while ((WahlTaste != '\r') && (WahlTaste != ' ')){	// Mit Enter zum Hauptmenu, Leertaste weiters Wort
						WahlTaste = Taste(d);
					}
				}


				break;		
			
			case 'w':	if(d)printf("Debug: eine eigene Wortliste benutzen\n"); 
				*Woerter=eigeneWortliste(d); break;											//andere Wortliste
			
			case 'p':	if(d)printf("Debug: ein anderes Protokoll laden\n"); 
				WortProtokoll = &eigenesWProtokoll(d);	break;							//anderes Protokoll
			

			case 'g':	if(d)printf("Debug: Gro%c/Kleinschreibung umschaltet\n", unsigned char(225)); 
				GrossKlein=GrossKlein*-1; break;				//GK umschalten
			
			case 'b':	if(d)printf("Debug: Ende des Programms\n"); 
				beenden=1;
				speichernWProtokoll(&WortProtokoll, "protokoll.log" ,d);	//Protokoll speichern
				break;								//Ende
			
			case 'a':	if(d)printf("Debug: geratene Woerter anzeigen\n"); 
				anzeigenWoerter(WortProtokoll,d);		//Wortprotokoll anzeigen
				break;								

			case 'v':	if(d)printf("Debug: Ratevorgang anzeigen\n"); 
				anzeigenVerlauf(WortProtokoll,d);		//Rateverlauf anzeigen
				break;								

			case 'd':	if(d){d=NULL;}else{d=1;} if(d)printf("\n\nDebuginganzeige umgeschaltet\n\n"); break;	
			
			default :	if(d)printf("Debug: falsche Taste\n");	//weiter im Hauptmenu
		}
	}
	if(d){printWProtokoll(&WortProtokoll,d); Taste(d);}

	free(Woerter);			// genutzte Speicherbereiche freigeben
	free(WortProtokoll);

	return;
}