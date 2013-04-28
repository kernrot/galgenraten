#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FktWoerterbuch.h"
#include "FktK.h"

// ''''''''''''''''''''''''''''''''''''''
// Funktionen zur Wortliste für die Ratewörter
// ''''''''''''''''''''''''''''''''''''''

void printWoerter(struct wort *WortListe) {
	// Ausgabe aller Wörter einer Wortliste
	struct wort *liste;
	liste=WortListe;
	printf ("%s\n", liste->Zeichen);
	while (liste->next != NULL) {							// liste bis next = NULL durchlaufen
		liste=liste->next;									// nächstes Listenelement
		printf ("%s\n", liste->Zeichen);					// listenelement ausgeben
	}
}

int anzWoerter(struct wort *WortListe) {
	// Rückgabe der Wortanzahl einer Wortliste
	struct wort *liste;
	liste=WortListe;
	int anz = 1;
	while (liste->next != NULL) {							// liste bis next = NULL durchlaufen
		liste=liste->next;									// nächstes Listenelement
		anz++;												// anz+1
	}
	return anz;
}

void hinzuWort(struct wort **lst, char Zeichen[]) {
	// Wort zur Wortliste hinzufügen
	struct wort *neueswort;
	struct wort *List_lauf = *lst;

	neueswort = (struct wort*) calloc(1,sizeof(*neueswort)); // hole geleerten speicher für ein wort
	strcpy(neueswort->Zeichen, Zeichen);
	neueswort->next = NULL;									// Listenende

	if ( List_lauf != NULL ) {								// sind worte vorhanden
		while (List_lauf->next != NULL )					// suche das letzte wort
			List_lauf=List_lauf->next;
		List_lauf->next=neueswort;							// Hänge das wort hinten an
	}
	else													// wenn die liste leer ist, das erste wort
		*lst=neueswort;
}

int readCharFromFile(FILE *datei) {
	int c = getc(datei);
	if (c == EOF) return EOF;
	unsigned char ch = (unsigned char)c;

	// UTF-8 2-Byte Sequenzen (0xC3 ...)
	if (ch == 0xC3) {
		int c2 = getc(datei);
		if (c2 == EOF) return EOF;
		unsigned char next = (unsigned char)c2;
		switch (next) {
			case 0xA4: return (char)132; // ä
			case 0xB6: return (char)148; // ö
			case 0xBC: return (char)129; // ü
			case 0x84: return (char)142; // Ä
			case 0x96: return (char)153; // Ö
			case 0x9C: return (char)154; // Ü
			case 0x9F: return (char)225; // ß
			default: return (char)next;
		}
	}

	// ANSI / Windows-1252 / ISO-8859-1
	switch (ch) {
		case 228: return (char)132; // ä
		case 246: return (char)148; // ö
		case 252: return (char)129; // ü
		case 196: return (char)142; // Ä
		case 214: return (char)153; // Ö
		case 220: return (char)154; // Ü
		case 223: return (char)225; // ß
		default: return (char)ch;
	}
}

struct wort readWoerter(char* pfad, int d){
	// Wörter aus einer Datei (pfad) einlesen
	FILE *datei;
	int defaultp=0;

	if (pfad == NULL){					// Standardliste falls kein Pfad übergeben
		pfad = (char*)"ratewoerter.txt";
		defaultp = 1;
	}

	struct wort *Liste;
	Liste = NULL;								// initialisiere leere liste

	char cRead[2] = {};							// Lesepuffervariable
	char cReadWort[28] = {};					// gelesenes Wort

	datei = fopen(pfad, "r");

	if ((unbenutzteZeichen(pfad, (char*)"ratewoerter.txt") < 1) && (datei == NULL)) {
		printf("Standardwortliste ratewoerter.txt nicht gefunden oder leer. Programm wird beendet.");
		Taste(d);
		exit(1);
	}

	if(NULL == datei) 	{						// Falls Datei nicht gefunden
		Liste = (struct wort*) calloc(1,sizeof(*Liste));
		*Liste = readWoerter(NULL, d);
		printf("\n\n\tDatei nicht gefunden.\n\t-> Es wurde die Standardliste geladen.\n\t (Weiter mit Tastendruck)\n");
		Taste(d);
	} else {									// sonst Schleife bis zum Dateiende
		if(d)printf("Debug: Datei %s wird geöffnet.\n", pfad);
		int c;
		while ((c = readCharFromFile(datei)) != EOF){
			if (c == 13) continue;				// CR überspringen
			if (c == 10)						// falls Zeilenumbruch LF
			{
				if (lenWort(cReadWort) > 0) {
					hinzuWort(&Liste, cReadWort);	// Wort aus cReadWort in Liste
					cReadWort[0] = '\0';			// cReadWort leeren
				}
			} else {
				cRead[0] = (char)c;
				cRead[1] = '\0';
				strcat(cReadWort, cRead);		// sonst char an ReadWort anhängen
			}
		}
		if (lenWort(cReadWort) > 0) {
			hinzuWort(&Liste, cReadWort);		// letztes Wort hinzufügen
		}
		fclose(datei);

		if (defaultp == 0) {
			printf("\n\n\tDatei %s geladen, Wortliste enthält %d Worte.\n\t (Weiter mit Tastendruck)\n", pfad, anzWoerter(Liste));
			Taste(d);
		}
	}

	if(d)printf("Debug: Datei %s geladen, Wortliste enthält %d Worte.\n", pfad, anzWoerter(Liste));
	if(d)printWoerter(Liste);
	return *Liste;
}

// ''''''''''''''''''''''''''''''''''''''
// Ascii Zeug
// ''''''''''''''''''''''''''''''''''''''

char ansi2ascii(char ansi) {
	// Ändern der entsprechenden Zeichen beim einlesen von Strings von ansi nach ascii
	switch ((unsigned char)ansi)
	{
	case 228: return (char)132;                    // ä
	case 246: return (char)148;                    // ö
	case 252: return (char)129;                    // ü
	case 196: return (char)142;                    // Ä
	case 214: return (char)153;                    // Ö
	case 220: return (char)154;                    // Ü
	case 223: return (char)225;                    // ß
	default: return ansi;
	}
}