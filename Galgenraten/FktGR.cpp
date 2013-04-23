#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include <Windows.h>	// nur für Sleep()

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
		
		DispRaten(Fehler, Suchwort, Eingabe, d);				//Ratebildschirm zeichen
		tmpTaste[0] = Taste(d);									// Nutzereingabe als erstes Zeichen der Zeichenkette

		// ''''''''''''''''''''''''''''''''''''''

		if (tmpTaste[0] == 60) {
			// eine Eingabe Löschen (Taste "<" = 60)
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
		printf("\n\t(Enter) zum Hauptmenu zur\201ck zu kehren\n\t(Leertaste) ein weiteres Wort raten");
	} else {
		DispVerloren(Fehler,Suchwort, d);
		printf("\n\t(Enter) zum Hauptmenu zur\201ck zu kehren\n\t(Leertaste) ein weiteres Wort raten");
	}
	return *Pr;
}


void anzeigenWoerter(struct WProtokoll *WPr, int d){
	// gibt alle bisher im Protokoll enthaltenen Wörter aus
	teilTitel(d);
	printUeberschrift("Anzeigen aller im Protokoll vorhandenen W\224erter");
	printWProtokoll(&WPr,d);		// Alle Wörter ausgeben
}


void anzeigenTippVerlauf(struct WProtokoll *WPr, int d){
	// lässt den Anwender ein Wort aus dem WPr auswählen und zeigt dann den Tippverlauf für dieses
	int WortNummer, firstWortNummer, lastWortNummer;

	WortNummer = firstWortNummer = intPositiv(WPr->TippProtokoll->Nummer);	// Indexnummer des ersten elements bestimmen
	lastWortNummer = (&letztesWProtokoll(&WPr,d))->Nummer;								// Indexnummer des letzten elements bestimmen

	int tmpTaste = 0;

	while (tmpTaste != '\r'){				// bis mit Enter bestätigt
		teilTitel(d);
		printUeberschrift("Rateverlauf anzeigen");
		printf("\tWort f\201r Rateverlauf ausw\204hlen:\n\n");

		printWProtokollEinzelwoerter(&WPr, WortNummer, d);	// Liste der Wörter mit Marker auf WortNummer
		printf("\n\t(oben/unten)\tPfeiltasten Wort ausw\204hlen\n\t(Enter)\tRateverlauf f\201r Wort anzeigen\t(Esc)\tAbbrechen\n");
		tmpTaste = Taste(d);

		if (tmpTaste == 27) return;	// vorgang abbrechen

		if (tmpTaste == 72 && WortNummer > firstWortNummer) { // Pfeiltaste nach oben
			WortNummer--;
			while (isInWProtokoll(&WPr,WortNummer,d) == 0){
				WortNummer--;		// Index für das nächste setzen (relevant element gelöscht)
			}
			if(d)printf("Debug: nach oben\n"); 
		}		

		if (tmpTaste == 80 && WortNummer < lastWortNummer) { // unten
			WortNummer++;
			while (isInWProtokoll(&WPr,WortNummer,d) == 0){
				WortNummer++;		// Index für das vorherige setzen (relevant element gelöscht)
			}
			if(d)printf("Debug: nach unten\n"); 
		}	
	}

	//WortNummer = char2intZahlenTasten(Taste(d));  // alte Wortauswahl

	if (WortNummer>0){
		struct WProtokoll *lauf = WPr;
		while(lauf->next != NULL && intPositiv(lauf->Nummer) != WortNummer){
			lauf=lauf->next;
		}
		if(d)printf("Debug: Wort Nummer %d gefunden.",WortNummer);
		if (lauf->Nummer != 0) abspielenTippVerlauf(lauf->TippProtokoll,d);
	}else{
		printf("\n\tWort nicht gefunden.");
		Taste(d);
	}

}


struct WProtokoll loeschenTippVerlauf(struct WProtokoll *WPr, int d){
	// löscht einen TippVerlauf, gibt Liste zurück

	int WortNummer, firstWortNummer, lastWortNummer;

	WortNummer = firstWortNummer = intPositiv(WPr->TippProtokoll->Nummer);	// Indexnummer des ersten elements bestimmen
	lastWortNummer = (&letztesWProtokoll(&WPr,d))->Nummer;

	int tmpTaste = 0;

	while (tmpTaste != '\r'){				// bis mit Enter bestätigt
		teilTitel(d);
		printUeberschrift("Rateverlauf l\224schen");
		printf("\tzu l\224schenden f\201r Rateverlauf ausw\204hlen:\n\n");

		printWProtokollEinzelwoerter(&WPr, WortNummer, d);	// Liste der Wörter mit Marker auf WortNummer
		printf("\n\t(oben/unten)\tPfeiltasten Wort ausw\204hlen\n\t(Enter)\tRateverlauf f\201r Wort l\224schen\n\t(Esc)\tAbbrechen\n");
		tmpTaste = Taste(d);

		if (tmpTaste == 27) return *WPr;	// vorgang abbrechen
		if (tmpTaste == 72 && WortNummer > firstWortNummer) { // Pfeiltaste nach oben
			WortNummer--;
			while (isInWProtokoll(&WPr,WortNummer,d) == 0){
				WortNummer--;		// Index für das nächste setzen (relevantes Element gelöscht/nicht vorhanden)
			}
			if(d)printf("Debug: nach oben\n"); 
		}		
		if (tmpTaste == 80 && WortNummer < lastWortNummer) { // unten
			WortNummer++;
			while (isInWProtokoll(&WPr,WortNummer,d) == 0){
				WortNummer++;		// Index für das vorherige setzen (relevantes Element gelöscht/nicht vorhanden)
			}
			if(d)printf("Debug: nach unten\n"); 
		}	
	}

	if(d) printf("Debug: Wortnummer %d\n", WortNummer);

	//WortNummer = char2intZahlenTasten(Taste(d));  // alte Wortauswahl

	if (WortNummer>0){
		struct WProtokoll *lauf = WPr;
		while(lauf->next != NULL && intPositiv(lauf->Nummer) != WortNummer){
			lauf=lauf->next;
		}
		if(d)printf("Debug: Wort Nummer %d gefunden.",WortNummer);

		if (lauf->Nummer != 0) {
			*WPr = entferneWProtokollNummer(&WPr,WortNummer,d);		// Entfernt das gewählte Element
		}
	}else{
		printf("\n\tWort nicht gefunden.");
		Taste(d);
	}
	return *WPr;
}


void abspielenTippVerlauf(struct TProtokoll *TPr, int d){
	// Zeigt den TippVerlauf eines Wortes (TPr)
	struct TProtokoll *lauf = TPr;						// Startelement der Liste
	char Eingabe[28] = {};
	char Suchwort[28] = {};
	int Fehler = 0;
	int Gk=0;

	if (lauf->next != NULL){						// falls wort nicht leer
		if(lauf->Nummer<0){	Gk = 1; }				// GroßKlein beachten?
		strcpy(Suchwort,lauf->Suchwort);			// Suchwort aus dem Tippprotokoll kopieren
		while (lauf->next != NULL) {				// Solange weiterer Tipp im TippProtokoll
			strcat(Eingabe,lauf->Eingabe);			// Zur Einhabe hinzu
			DispRatenVerlauf(unbenutzteZeichen(charsGK(Suchwort,Gk), charsGK(Eingabe,Gk)),lauf->Suchwort,Eingabe,d);	// Bildschirm zeichnen
			lauf = lauf->next;						// zum nächsten buchstaben
			if (Taste(d) == '\r') {
				return;
			}
		}
		strcat(Eingabe,lauf->Eingabe);				// letzter Tipp
		if (unbenutzteZeichen(charsGK(Suchwort,Gk), charsGK(Eingabe,Gk)) < 10 ){	// Gewonnen/Verloren anhand der gemachten Fehler
			DispGewonnen(unbenutzteZeichen(charsGK(Suchwort,Gk), charsGK(Eingabe,Gk)),Suchwort,d);	// Schlussbildschrim Gewonnen
		} else {
			DispVerloren(unbenutzteZeichen(charsGK(Suchwort,Gk), charsGK(Eingabe,Gk)),Suchwort,d);  // Schlussbildschrim Gewonnen
		}
		printf("\n\t(Enter) zum Hauptmenu zur\201ck zu kehren");
		char WahlTaste = 0;
		while ((WahlTaste != '\r')){	// Mit Enter weiter zum Hauptmenu
			WahlTaste = Taste(d);
		}
	}
}


struct wort eigeneWortliste(int d){
	// laden einer eigenen Wortliste, gibt diese zurück
	char Pfad[256] = {};

	while ((checkPfad(Pfad) == 0) || lenWort(Pfad) == 0){
		DispWortlistenEingabe(d);

		if ((checkPfad(Pfad) == 0) && lenWort(Pfad) != 0){
			printf("\tBitte eine g\201ltigen Dateinamen eingeben.\n\t(Buchstaben, Punkte, Zahlen)\n\n");
		}

		printf("\t Dateiname: ");
		scanf("%s", Pfad);
	}

	return readWoerter(Pfad, d);
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

		printf("\tDateiname: ");
		scanf("%s", Pfad);
	}

	speichernWProtokoll(&WPr,Pfad,d);
}