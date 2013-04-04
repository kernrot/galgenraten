#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Windows.h>	// nur für Sleep()

#include "FktDisp.h"	//Bildschirmanzeigen für Galgenraten
#include "FktGR.h"		//Funktionen für Galgenraten
#include "FktK.h"		//allgemeine Funktionen
#include "FktProtokoll.h"
#include "FktWoerterbuch.h"

struct TProtokoll neuGalgen(struct wort *Wortliste, struct TProtokoll *Pr, int Gk, int Nummer, int d) {
	// einen neuen Rateversuch starten
	char Suchwort[28] = {};
	char Eingabe[28] = {};

	if(d)printf("Debug: Spiel startet.\n");
	char tmpTaste[2] = {};				// Nutzereingabe als Zeichenkette für einfache Handhabung von strcat_s
	int Fehler = 0;						// gemachte Fehler
	
	// ''''''''''''''''''''''''''''''''''''''
	// Ratewort Auswählen 
	// ''''''''''''''''''''''''''''''''''''''
	
	if(d)printf("Debug: Woerter in der Liste: %d\n", anzWoerter(Wortliste));

	struct wort *zWort;
	zWort = Wortliste;
	int znum = Zufall(anzWoerter(Wortliste)-1); // Zufallszahl zwischen 0 und Anzahl der Wörter in Liste (-1)
	
	for (int i=0; i<znum; i++)	{				// Zufälliges Wort aus der Wortliste wählen
			zWort=zWort->next;
	}
	strcpy(Suchwort, zWort->Zeichen);			// gewähltes Wort nach Suchwort
	if(d)printf("Debug: Zufaellig gewaehltes Wort %d: %s\n", znum, Suchwort);

	// ''''''''''''''''''''''''''''''''''''''
	// Rateschleife
	// ''''''''''''''''''''''''''''''''''''''

	while ((Fehler<10)	// Fehler kleiner 10
		&& ((fehlendeZeichen(charsGK(Suchwort,Gk), charsGK(Eingabe,Gk)) > 0 ) || (lenWort(Eingabe) == 0)))				// Nich alle Zeichen erraten, oder keine bisher Eingegeben
	{
		if(d)printf("Debug: Zufaellig gewaehltes Wort: %s\nDebug: Eingabe bisher: %s\nDebug: Fehler bisher: %d\n", Suchwort, Eingabe, Fehler);
		DispRaten(Fehler, Suchwort, Eingabe, d);
		tmpTaste[0] = Taste(d);									// Nutzereingabe als erstes Zeichen der Zeichenkette

			// ''''''''''''''''''''''''''''''''''''''
			
		if (tmpTaste[0] == 60) {
			// eine Eingabe Löschen (Taste < = 60)
			if (lenWort(Eingabe) != 0) {						// falls mindestens ein Buchstabe geraten
				Eingabe[lenWort(Eingabe)-1] = '\0';				// letzten Buchstaben in Eingabe entfernen
				entferneTProtokoll(&Pr,d);						// letzten TippProtokolleintrag entfernen
			}else{
				Pr->Nummer = 0;									// falls kein Buchstabe bisher geraten -> Ende und TippProtokoll mit Nr. 0 als leer kennzeichnen
				return *Pr;
			}
		} else {
			// ein Buchstabe geraten
			if (vorhandeneZeichen(Eingabe, tmpTaste) == 0) {	// falls Buchstabe tmpTaste noch nicht in Eingabe
				strcat_s(Eingabe, tmpTaste);					// anhängen an Eingabe
				hinzuTProtokoll(&Pr,Gk*Nummer,zWort->Zeichen,tmpTaste,d);	// TippProtokoll hinzufügen
			} 
		}
																// wenn tmpTaste noch nicht in Eingabe
		Fehler = unbenutzteZeichen(Suchwort, Eingabe);
	}

	// ''''''''''''''''''''''''''''''''''''''
	// Raten beendet
	// ''''''''''''''''''''''''''''''''''''''

	if (Fehler < 10) {
		DispGewonnen(Fehler,Suchwort, d);						// Gewonnen wenn weniger als 10 Fehler
		printf("\n\t(Enter) zum Hauptmenu zur\201ck zu kehren\n\t(Leertaste) ein weiters Wort raten");
	} else {
		DispVerloren(Fehler,Suchwort, d);
		printf("\n\t(Enter) zum Hauptmenu zur\201ck zu kehren\n\t(Leertaste) ein weiters Wort raten");
	}
	return *Pr;
}
 
void anzeigenWoerter(struct WProtokoll *WPr, int d){
	system("CLS");
	teilTitel(d);
	printf("\n\t\tAnzeigen aller im Protokoll vorhandenen W\224erter\n");
	printWProtokoll(&WPr,d);
}

void anzeigenVerlauf(struct WProtokoll *WPr, int d){
	
	int WortNummer = 1;
	int tmpTaste = 0;
	
	while (tmpTaste != '\r'){				// bis mit Enter bestätigt
		teilTitel(d);
		printf("\n\tWort f\201r Rateverlauf ausw\204hlen:\n\n");
		
		printWProtokollEinzelwoerter(&WPr, WortNummer, d);	// Liste der Wörter mit Marker auf WortNummer
		printf("\n\t(oben/unten)\tPfeiltasten Wort ausw\204hlen\n\t(Enter)\tRateverlauf f\201r Wort anzeigen\n");
		tmpTaste = Taste(d);

		if (tmpTaste == 72 && WortNummer > 1) { WortNummer--; printf("Debug: nach oben\n"); }		// Pfeiltaste nach oben
		if (tmpTaste == 80 && WortNummer < anzWProtokoll(&WPr,d)) { WortNummer++; printf("Debug: nach unten\n"); }	// unten
	}
	
	if(d) printf("Debug: Wortnummer %d\n", WortNummer);
	
	//WortNummer = char2intZahlenTasten(Taste(d));  // alte Wortauswahl

	if (WortNummer>0 && WortNummer<anzWProtokoll(&WPr,d)+1){
		struct WProtokoll *lauf = WPr;
		while(lauf->next != NULL && iPos(lauf->Nummer) != WortNummer){
			lauf=lauf->next;
		}
		if(d)printf("Debug: Wort Nummer %d gefunden.",WortNummer);
		if (lauf->Nummer != 0) abspielenVerlauf(lauf->TippProtokoll,d);
	}else{
		printf("\n\tWort nicht gefunden.");
		Taste(d);
	}
	
}

void abspielenVerlauf(struct TProtokoll *TPr, int d){
	
	struct TProtokoll *lauf = TPr;						// Startelement der Liste
	char Eingabe[28] = {};
	char Suchwort[28] = {};
	int Fehler = 0;
	int Gk=0;

	if (lauf->next != NULL){
		if(lauf->Nummer<0){	Gk = 1; }
		strcpy(Suchwort,lauf->Suchwort);
		while (lauf->next != NULL) {
			strcat(Eingabe,lauf->Eingabe);
			DispRatenVerlauf(unbenutzteZeichen(charsGK(Suchwort,Gk), charsGK(Eingabe,Gk)),lauf->Suchwort,Eingabe,d);
			lauf = lauf->next;
			if (Taste(d) == '\r') {
				return;
			}
		}
		strcat(Eingabe,lauf->Eingabe);
		if (unbenutzteZeichen(charsGK(Suchwort,Gk), charsGK(Eingabe,Gk)) < 10 ){
			DispGewonnen(unbenutzteZeichen(charsGK(Suchwort,Gk), charsGK(Eingabe,Gk)),Suchwort,d);
		} else {
			DispVerloren(unbenutzteZeichen(charsGK(Suchwort,Gk), charsGK(Eingabe,Gk)),Suchwort,d);
		}
		printf("\n\t(Enter) zum Hauptmenu zur\201ck zu kehren");
		char WahlTaste = 0;
		while ((WahlTaste != '\r')){	// Mit Enter weiter zum Hauptmenu
			WahlTaste = Taste(d);
		}
	}
}




struct wort eigeneWortliste(int d){
	
	char Pfad[256] = {};
	DispWortlistenEingabe(d);
	
	printf("\t Dateiname: ");
	scanf("%s", Pfad);

	return readWoerter(Pfad, d);
}

struct WProtokoll eigenesWProtokoll(int d){
	
	char Pfad[256] = {};
	DispProtokollEingabe(d);
	
	printf("\t Dateiname: ");
	scanf("%s", Pfad);

	return lesenWProtokoll(Pfad,d);
}

