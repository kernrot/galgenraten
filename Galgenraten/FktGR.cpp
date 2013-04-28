#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FktDisp.h"	// Bildschirmanzeigen für Galgenraten
#include "FktGR.h"		// Funktionen für Galgenraten
#include "FktK.h"		// allgemeine Funktionen
#include "FktProtokoll.h"
#include "FktWoerterbuch.h"

struct TProtokoll neuGalgen(struct wort *Wortliste, struct TProtokoll *Pr, int Gk, int Nummer, int d) {
	// einen neuen Rateversuch starten
	char Suchwort[28] = {};
	char Eingabe[28] = {};

	if(d)printf("Debug: Spiel startet.\n");
	char tmpTaste[2] = {};				// Nutzereingabe als Zeichenkette für einfache Handhabung von strcat
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
		&& ((fehlendeZeichen(charsGK(Suchwort,Gk), Eingabe)) != 0) // und noch Zeichen zu raten
		&& (tmpTaste[0] != 27)) {								// und nicht Esc gedrückt

			DispRaten(Fehler, Suchwort, Eingabe, d);			// Ratebildschirm zeichnen
			tmpTaste[0] = Taste(d); tmpTaste[1] = '\0'; charsGK(tmpTaste, Gk);					// Tastendruck abfangen

			if (tmpTaste[0] != 27) {							// wenn nicht Esc gedrückt wurde
				if (vorhandeneZeichen(tmpTaste, charsGK(Suchwort,Gk)) == 0){ // war das geratene Zeichen im Wort vorhanden
					Fehler++;
				}
				strcat(Eingabe, tmpTaste);					// anhängen an Eingabe
				hinzuTProtokoll(&Pr, Nummer*Gk, Suchwort, Eingabe, d); // Tipp zum Tippprotokoll hinzufügen
			}
	}

	// ''''''''''''''''''''''''''''''''''''''
	// Auswertung
	// ''''''''''''''''''''''''''''''''''''''

	if (Fehler == 10){
		DispVerloren(Suchwort, d);
		printf("\n\t(Enter) zum Hauptmenu zur\201ck zu kehren\n\t(Leertaste) ein weiteres Wort raten");
	} else if(tmpTaste[0] != 27) {
		DispGewonnen(Suchwort, d);
		printf("\n\t(Enter) zum Hauptmenu zur\201ck zu kehren\n\t(Leertaste) ein weiteres Wort raten");
	}

	return *Pr;
}

void anzeigenWoerter(struct WProtokoll *WPr, int d){
	// Anzeigen aller im Protokoll vorhandenen Wörter
	teilTitel(d);
	printUeberschrift((char*)"Anzeigen aller im Protokoll vorhandenen W\224erter");
	printWProtokollEinzelwoerter(&WPr, 0, d);
	Taste(d);
	return;
}

int Wortauswahl(struct WProtokoll *WPr, int d){
	// Listet alle Wörter auf und gibt die Nummer des mit Pfeiltasten gewählten Wortes zurück
	int lastWortNummer = 0;
	lastWortNummer = intPositiv((letztesWProtokoll(&WPr,d)).Nummer); // Indexnummer des letzten elements bestimmen
	int Wahl = 1;
	char TasteWahl = ' ';

	while (TasteWahl != 13 && TasteWahl != 27){
		teilTitel(d);
		printUeberschrift((char*)"Rateverlauf anzeigen");
		printf("\tWort f\201r Rateverlauf ausw\204hlen:\n\n");
		printWProtokollEinzelwoerter(&WPr, Wahl, d);
		if(d)printf("Debug: Ausgewaehltes Wort: %d\n", Wahl);
		printf("\n\t(oben/unten)\tPfeiltasten Wort ausw\204hlen\n\t(Enter)\tRateverlauf f\201r Wort anzeigen\t(Esc)\tAbbrechen\n");

		TasteWahl = Taste(d);

		switch (TasteWahl){
		case 80:	// Pfeiltaste unten
			do{
				Wahl++;
				if (Wahl > lastWortNummer) {
					Wahl = 1;
				}
			}while((isInWProtokoll(&WPr, Wahl, d) != 1) && (isInWProtokoll(&WPr, Wahl*-1, d) != 1));
			break;

		case 72:	// Pfeiltaste oben
			do{
				Wahl--;
				if (Wahl < 1) {
					Wahl = lastWortNummer;
				}
			}while((isInWProtokoll(&WPr, Wahl, d) != 1) && (isInWProtokoll(&WPr, Wahl*-1, d) != 1));
			break;

		default: break;
		}

	}
	if(TasteWahl == 27) Wahl = 0;
	return Wahl;
}

void anzeigenTippVerlauf(struct WProtokoll *WPr, int d){
	// Zeigt den Rateverlauf eines Wortes Schritt für Schritt an
	int wahl = Wortauswahl(WPr, d);
	if (wahl == 0) return;

	struct WProtokoll *lauf = WPr;

	while((lauf->Nummer != wahl) && (lauf->Nummer != wahl*-1) && (lauf->next != NULL)){ // zu wahl entsprechendem Wortprotokollelement laufen
		lauf=lauf->next;
	}

	struct TProtokoll *Tlauf = lauf->TippProtokoll; // Startelement Tippprotokoll

	int fehler = 0;
	int weiter = 1;
	char eingabe[28]={};
	char tmptaste[2]={};

	while(weiter == 1){

		if (Tlauf != NULL){
			fehler = unbenutzteZeichen(Tlauf->Suchwort, Tlauf->Eingabe); // Fehler bestimmen
			DispRatenVerlauf(fehler, Tlauf->Suchwort, Tlauf->Eingabe, d); // Bildschirm für Verlaufsanzeige zeichnen
			if(Tlauf->next != NULL) {
				Tlauf=Tlauf->next;
			} else {
				weiter = 0;
			}
		}

		if (Taste(d) == 13) weiter = 0; // mit Enter abbrechen
	}

	// Abschlussbildschirm je nach Ausgang
	int Gk = -1;
	if(lauf->Nummer<0){ Gk = 1; } // GroßKlein beachten?
	if(fehler == 10){
		DispVerloren(Tlauf->Suchwort, d);
	} else if (fehlendeZeichen(charsGK(Tlauf->Suchwort,Gk), Tlauf->Eingabe) == 0){
		DispGewonnen(Tlauf->Suchwort, d);
	}
	printf("\n\t(Enter) zum Hauptmenu zur\201ck zu kehren");
	while(Taste(d) != 13){}
	return;
}

struct WProtokoll loeschenTippVerlauf(struct WProtokoll *WPr, int d){
	// Löscht ein Element aus dem Protokoll
	int wahl = Wortauswahl(WPr, d);
	if (wahl == 0) return *WPr;

	entferneWProtokollNummer(&WPr, wahl, d);
	return *WPr;
}

struct wort eigeneWortliste(int d){
	// einlesen einer eigenen Wortliste, gibt diese zurück
	char Pfad[256] = {};

	while ((checkPfad(Pfad) == 0) || lenWort(Pfad) == 0){
		DispWortlistenEingabe(d);

		if ((checkPfad(Pfad) == 0) && lenWort(Pfad) != 0){
			printf("\tBitte eine g\201ltigen Dateinamen eingeben.\n\t(Buchstaben, Punkte, Zahlen)\n\n");
		}

		printf("\t Dateiname: ");
		scanf("%s", Pfad);
	}

	return readWoerter(Pfad,d);
}

struct WProtokoll eigenesWProtokoll(int d){
	// laden eines eigenen Protokolls, gibt dieses zurück
	char Pfad[256] = {};

	while ((checkPfad(Pfad) == 0) || lenWort(Pfad) == 0){
		DispProtokollEingabe(d);

		if ((checkPfad(Pfad) == 0) && lenWort(Pfad) != 0){
			printf("\tBitte eine g\201ltigen Dateinamen eingeben.\n\t(Buchstaben, Punkte, Zahlen)\n\n");
		}

		printf("\t Dateiname: ");
		scanf("%s", Pfad);
	}

	return lesenWProtokoll(Pfad,d);
}

void eignesSpeicherzielWProtokoll(struct WProtokoll *WPr, int d){
	// Speichern eines WortProtokolls mit wählbarem Dateiname
	char Pfad[256] = {};

	while ((checkPfad(Pfad) == 0) || lenWort(Pfad) == 0){
		DispProtokollSpeichern(d);

		if ((checkPfad(Pfad) == 0) && lenWort(Pfad) != 0){
			printf("\tBitte eine g\201ltigen Dateinamen eingeben.\n\t(Buchstaben, Punkte, Zahlen)\n\n");
		}

		printf("\t Dateiname: ");
		scanf("%s", Pfad);
	}

	speichernWProtokoll(&WPr,Pfad,d);
}