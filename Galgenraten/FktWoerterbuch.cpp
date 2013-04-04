#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FktWoerterbuch.h"
#include "FktK.h"

// ''''''''''''''''''''''''''''''''''''''
// Funktionen zur Wortliste f�r die Ratew�rter
// ''''''''''''''''''''''''''''''''''''''

void printWoerter(struct wort *WortListe) {
	// Ausgabe aller W�rter einer Wortliste
    struct wort *liste;
    liste=WortListe;
    printf ("%s\n", liste->Zeichen);
    while (liste->next != NULL) {							// liste bis next = NULL durchlaufen
	
		liste=liste->next;									// n�chstes Listenelement
		printf ("%s\n", liste->Zeichen);					// listenelement ausgeben
    }
}

int anzWoerter(struct wort *WortListe) {
	// R�ckgabe der Wortanzahl einer Wortliste
    struct wort *liste;
    liste=WortListe;
	int anz = 1;
    while (liste->next != NULL) {							// liste bis next = NULL durchlaufen
		liste=liste->next;									// n�chstes Listenelement
		anz++;												// anz+1
    }
	return anz;
}
 
void hinzuWort(struct wort **lst, char Zeichen[]) {
	// Wort zur Wortliste hinzuf�gen
    struct wort *neueswort;
    struct wort *List_lauf = *lst;
 
    neueswort = (struct wort*)  calloc(1,sizeof(*neueswort));// hole  geleerten speicher f�r ein wort
	//if (neueswort) memset(neueswort,0,sizeof(*neueswort));
    strcpy(neueswort->Zeichen,  Zeichen);
    neueswort->next = NULL;									// Listenende
 
    if ( List_lauf != NULL ) {								// sind worte vorhanden
        while (List_lauf->next != NULL )						// suche das letzte wort
            List_lauf=List_lauf->next;
        List_lauf->next=neueswort;							// H�nge das wort hinten an
    }
    else													// wenn die liste leer ist, das erste wort
        *lst=neueswort;
}
 
struct wort readWoerter(char* pfad, int d){
	// W�rter aus einer Datei (pfad) einlesen
	FILE *datei;
	int defaultp=0;

	if (pfad == NULL){
		pfad = "default.txt";
		defaultp = 1;
	}
	
    struct wort *Liste;
	Liste = NULL;								// initialisiere leere liste

	char cRead[2] = {};							// Lesepuffervariable
	char cReadWort[28] = {};					//	gelesenes Wort
	
	datei = fopen(pfad, "r");
	
	if ((unbenutzteZeichen(pfad, "default.txt") < 1) && (datei == NULL)) {
		printf("Standardwortliste default.txt nicht gefunden oder leer. Programm wird beendet.");
		Taste(d);
		exit(1);
	}

	if(NULL == datei) 	{						// Falls Datei nicht gefunden
		Liste = (struct wort*)  calloc(1,sizeof(*Liste));
		//if (Liste) memset(Liste,0,sizeof(*Liste));
		*Liste = readWoerter(NULL, d);
		printf("\n\n\tDatei nicht gefunden.\n\t-> Es wurde die Standardliste geladen.\n\t (Weiter mit Tastendruck)\n");
		Taste(d);
	} else {									// sonst Schleife bis zum Dateiende
		if(d)printf("Debug: Datei %s wird ge�ffnet.\n", pfad);
		while (!feof(datei)){
			cRead[0] = ansi2ascii(getc(datei));				// ein char in cRead
			//printf("%c", cRead[0]);

			if (cRead[0] == 10)					// falls Zeilenumbruch
			{
				hinzuWort(&Liste, cReadWort);		// Wort aus cReadWort in Liste
				cReadWort[0]='\0';					// cReadWort leeren
			} else	{
				strcat_s (cReadWort, cRead);		// sonst char an ReadWort anh�ngen
			}
		}
		cReadWort[lenWort(cReadWort)-1] = '\0';	// sinnloses y (-1) am Dateiende entfernen
		hinzuWort(&Liste, cReadWort);			// letztes Wort hinzuf�gen
		fclose(datei);
		
		if (defaultp == 0) {
			printf("\n\n\tDatei %s geladen, Wortliste enth�lt %d Worte.\n\t (Weiter mit Tastendruck)\n", pfad, anzWoerter(Liste));
			Taste(d);
		}
	}
	

	if(d)printf("Debug: Datei %s geladen, Wortliste enth�lt %d Worte.\n", pfad, anzWoerter(Liste));
	if(d)printWoerter(Liste);
    return *Liste;
}

// ''''''''''''''''''''''''''''''''''''''
// Ascii Zeug
// ''''''''''''''''''''''''''''''''''''''

char ansi2ascii(char ansi) {
	// �ndern der entsprechenden Zeichen beim einlesen von Strings von ansi nach ascii
    switch (ansi)
    {
    case char(228): return char(132);                    // �
    case char(246): return char(148);                    // �
    case char(252): return char(129);                    // �
    case char(196): return char(142);                    // �
    case char(214): return char(153);                    // �
    case char(220): return char(154);                    // �
    case char(223): return char(225);                    // �
    default: return ansi;
    }
}