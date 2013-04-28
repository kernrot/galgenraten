#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FktProtokoll.h"
#include "FktK.h"

// ''''''''''''''''''''''''''''''''''''''
// Funktionen für die TippProtokollliste
// ''''''''''''''''''''''''''''''''''''''

struct TProtokoll hinzuTProtokoll(struct TProtokoll **lst, int Nummer, char Suchwort[28], char Eingabe[28], int d) {
	// Fügt einen Protokolleintrag hinzu

	struct TProtokoll *nElement;
	struct TProtokoll *List_lauf = *lst;

	nElement = (struct TProtokoll*) calloc(1,sizeof(TProtokoll)); // hole geleerten speicher für ein Element
	nElement->Nummer = Nummer;
	strcpy(nElement->Suchwort, Suchwort);
	strcpy(nElement->Eingabe, Eingabe);
	nElement->next = NULL;										// Folgeelement bzw Ende
	nElement->prev = NULL;										// vorhergehendes Element

	if ( List_lauf->Nummer != 0 ) {								// sind Elemente vorhanden
		while (List_lauf->next != NULL )						// suche das letzte Element						
			List_lauf=List_lauf->next;
		nElement->prev=List_lauf;								// letztes Element wird vorgänger des aktuellen
		List_lauf->next=nElement;								// Hänge das wort hinten an

	}
	else														// wenn die Liste leer ist, das erstes Element
		*lst=nElement;

	if(d)printf("Debug: Eintrag zu TippProtokoll hinzugefuegt: %d %s %s\n", nElement->Nummer,nElement->Suchwort,nElement->Eingabe);
	return *nElement;
}

struct TProtokoll entferneTProtokoll(struct TProtokoll **lst, int d) {
	// entfernt das letzte Element aus der Liste, gibt Liste zurück

	struct TProtokoll *List_lauf = *lst;

	if ( List_lauf->Nummer != 0 ) {								// sind Elemente vorhanden
		while (List_lauf->next != NULL )						// suche das letzte Element						
			List_lauf=List_lauf->next;
		if (List_lauf->prev != NULL) {
			List_lauf=List_lauf->prev;							// gehe ein Element zurück
			free(List_lauf->next);								// lösche das letzte Element
			List_lauf->next = NULL;								// setze neues Listenende
		} else {
			List_lauf->Nummer = 0;
		}
	}
	if(d)printf("Debug: Eintrag von TippProtokoll entfernt.\n");
	return **lst;
}

int anzTProtokollTipps(struct TProtokoll **lst, int d) {
	// gibt die Anzahl an Tipps zurück

	struct TProtokoll *List_lauf = *lst;
	int anz = 1;

	if ( List_lauf->Nummer != 0 ) {								// sind Elemente vorhanden
		while (List_lauf->next != NULL ){						// suche das letzte Element						
			List_lauf=List_lauf->next;
			anz++;
		}
	} else {
		anz = 0;
	}
	if(d)printf("Debug: Tippanzahl %d\n", anz);
	return anz;
}

void printTProtokoll(struct TProtokoll **lst, int d) {
	// print für ein TippProtokoll

	struct TProtokoll *List_lauf = *lst;

	if ( List_lauf->Nummer != 0 ) {								// sind Elemente vorhanden
		printf("\nNr. %d\t\t      Suchwort \302 Eingabe\n", List_lauf->Nummer);		//Tabellenkopf etc.
		printf("\t\t\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\305\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\n");
		printf("%30s \263 %-30s\n", List_lauf->Suchwort, List_lauf->Eingabe);
		while (List_lauf->next != NULL ){						// suche das letzte Element						
			List_lauf=List_lauf->next;
			printf("%30s \263 %-30s\n", List_lauf->Suchwort, List_lauf->Eingabe);
		}
	}
	if(d)printf("Debug: TippProtokoll ausgegeben.\n");
}


// ''''''''''''''''''''''''''''''''''''''
// Funktionen für die WortProtokollliste
// ''''''''''''''''''''''''''''''''''''''

struct WProtokoll hinzuWProtokoll(struct WProtokoll **lst, struct TProtokoll **an, int d) {
	// ein TippProtokoll zum WortProtokoll hinzufügen, gibt das hinzugefügte zurück

	struct WProtokoll *nElement;
	struct WProtokoll *List_lauf = *lst;						// Startelement der Liste

	nElement = (struct WProtokoll*) calloc(1,sizeof(WProtokoll)); // hole geleerten speicher für ein Element
	nElement->TippProtokoll = *an;
	nElement->Nummer = nElement->TippProtokoll->Nummer;
	nElement->next = NULL;										// Folgeelement bzw Ende
	nElement->prev = NULL;										// vorhergehendes Element

	if ( List_lauf->Nummer != 0 ) {								// sind Elemente vorhanden
		while (List_lauf->next != NULL ) {						// suche das letzte Element						
			List_lauf=List_lauf->next;
		}
		nElement->prev=List_lauf;								// letztes Element wird vorgänger des aktuellen
		List_lauf->next=nElement;								// Hänge das wort hinten an

	}
	else														// wenn die Liste leer ist, das erstes Element
	{
		*lst=nElement;
	}
	return *nElement;
}

struct WProtokoll entferneWProtokoll(struct WProtokoll **lst, int d) {
	// entfernt das letzte Element aus der Liste, gibt Liste zurück

	struct WProtokoll *List_lauf = *lst;

	if ( List_lauf->Nummer != 0 ) {								// sind Elemente vorhanden
		while (List_lauf->next != NULL )						// suche das letzte Element						
			List_lauf=List_lauf->next;
		if (List_lauf->prev != NULL) {
			List_lauf=List_lauf->prev;							// gehe ein Element zurück
			free(List_lauf->next);								// lösche das letzte Element
			List_lauf->next = NULL;								// setze neues Listenende
		} else {
			List_lauf->Nummer = 0;
		}
	}
	if(d)printf("Debug: Eintrag von WortProtokoll entfernt.\n");
	return **lst;
}

struct WProtokoll entferneWProtokollNummer(struct WProtokoll **lst, int n, int d) {
	// entfernt das Element mit der entsp. Nummer aus der Liste gibt Liste zurück

	struct WProtokoll *List_lauf = *lst;

	if ( List_lauf->Nummer != 0 ) {								// sind Elemente vorhanden
		while ((List_lauf->next != NULL) && (List_lauf->Nummer != n) && (List_lauf->Nummer != n*-1))	// suche das zu löschende Element						
			List_lauf=List_lauf->next;

		if ((List_lauf->prev != NULL) && (List_lauf->next != NULL)) {	// Element in der Mitte der Liste
			List_lauf->prev->next = List_lauf->next;
			List_lauf->next->prev = List_lauf->prev;
			free(List_lauf);
		} else if ((List_lauf->prev != NULL) && (List_lauf->next == NULL)) { // letztes Element der Liste
			List_lauf->prev->next = NULL;
			free(List_lauf);
		} else if ((List_lauf->prev == NULL) && (List_lauf->next != NULL)) { // erstes Element der Liste
			*lst = List_lauf->next;
			(*lst)->prev = NULL;
			free(List_lauf);
		} else { // einziges Element der Liste
			List_lauf->Nummer = 0;
		}

	}
	if(d)printf("Debug: Eintrag %d von WortProtokoll entfernt.\n", n);
	return **lst;
}

int OLDanzWProtokoll(struct WProtokoll **lst, int d) {
	// Anzahl der TippProtokolle in einem WortProtokoll

	struct WProtokoll *List_lauf = *lst;
	int anz = 1;

	if ( List_lauf->Nummer != 0 ) {								// sind Elemente vorhanden
		while (List_lauf->next != NULL ){						// suche das letzte Element						
			List_lauf=List_lauf->next;
			anz++;
		}
	} else {
		anz = 0;
	}
	if(d)printf("Debug: Tippanzahl %d\n", anz);
	return anz;
}

struct WProtokoll letztesWProtokoll(struct WProtokoll **WPr, int d){
	// gibt das letzte Element des WProtokolls zurück
	struct WProtokoll *List_lauf = *WPr;

	while (List_lauf->next != NULL ){							// suche das letzte Element						
		List_lauf=List_lauf->next;
	}

	return *List_lauf;
}

int isInWProtokoll(struct WProtokoll **lst, int num, int d) {
	// prüft ob TippProtokoll mit laufender Nummer im Wortprotokoll vorhanden ist, return 1 für vorhanden, 0 für nicht
	struct WProtokoll *List_lauf = *lst;
	int is = 0;

	if ( List_lauf->Nummer != 0 ) {								// sind Elemente vorhanden
		while (List_lauf->next != NULL ){						// suche das letzte Element						
			if ((List_lauf->Nummer == num) || (List_lauf->Nummer == num*-1)) is = 1;
			List_lauf=List_lauf->next;
		}
		if ((List_lauf->Nummer == num) || (List_lauf->Nummer == num*-1)) is = 1;
	} else {
		is = 0;
	}
	return is;
}

void printWProtokoll(struct WProtokoll **WortProtokoll, int d){
	// printTProtokoll für alle TippProtokolle in einem WortProtokoll
	struct WProtokoll *List_lauf = *WortProtokoll;

	if ( List_lauf->Nummer != 0 ) {								// sind Elemente vorhanden
		printTProtokoll(&List_lauf->TippProtokoll, d);
		printf("\n\tbeliebige Taste dr\201cken f\201r n\204chstes Wort\n\n");
		Taste(d);
		while (List_lauf->next != NULL ){						// suche das letzte Element						
			List_lauf=List_lauf->next;
			printTProtokoll(&List_lauf->TippProtokoll, d);
			printf("\n\tbeliebige Taste dr\201cken f\201r n\204chstes Wort\n\n");
			Taste(d);
		}
	}
	return;
}

void printWProtokollEinzelwoerter(struct WProtokoll **lst, int numMarkiert, int d) {
	// alle TippProtokolle in einem WortProtokoll auflisten, mit optionalem Marker auf Wort->WortNummer
	struct WProtokoll *List_lauf = *lst;

	if ( List_lauf->Nummer != 0 ) {								// sind Elemente vorhanden
		if ((List_lauf->Nummer == numMarkiert) || (List_lauf->Nummer == numMarkiert*-1)){
			printf("\t--> Wort %2d: %s \n", intPositiv(List_lauf->Nummer), List_lauf->TippProtokoll->Suchwort);
		} else {
			printf("\t    Wort %2d: %s \n", intPositiv(List_lauf->Nummer), List_lauf->TippProtokoll->Suchwort);
		}
		while (List_lauf->next != NULL ){						// suche das letzte Element						
			List_lauf=List_lauf->next;
			if ((List_lauf->Nummer == numMarkiert) || (List_lauf->Nummer == numMarkiert*-1)){
				printf("\t--> Wort %2d: %s \n", intPositiv(List_lauf->Nummer), List_lauf->TippProtokoll->Suchwort);
			} else {
				printf("\t    Wort %2d: %s \n", intPositiv(List_lauf->Nummer), List_lauf->TippProtokoll->Suchwort);
			}
		}
	}
	return;
}

struct WProtokoll lesenWProtokoll(char* pfad, int d) {
	// WProtokoll aus Binärdatei lesen

	if (pfad == NULL) {				// ohne übergebenen pfad -> Standarddatei
		pfad = (char*)"protokoll.log";
	}

	struct TProtokoll *TPr;
	TPr = (struct TProtokoll*) calloc(1,sizeof(TProtokoll));
	if(TPr == NULL) { printf("Kein Arbeitsspeicher vorhanden.\n"); Taste(d); exit(1);}
	struct WProtokoll *WPr;
	WPr = (struct WProtokoll*) calloc(1,sizeof(WProtokoll));
	if(WPr == NULL) { printf("Kein Arbeitsspeicher vorhanden.\n"); Taste(d); exit(1);}

	FILE *datei;
	datei = fopen(pfad, "rb");									// Datei zum lesen öffnen

	int tNummer;												// temporäre einlese Variablen
	char tSuchwort[28];
	char tEingabe[28];

	if (datei == NULL) {
		if (unbenutzteZeichen(pfad, (char*)"protokoll.log") < 1) {
			// Falls Standardprotokoll noch nicht existiert (Erststart): Leere Datei erzeugen und leeres Protokoll zurückgeben
			FILE *neu = fopen("protokoll.log", "wb");
			if (neu != NULL) fclose(neu);
			return *WPr;
		} else {
			printf("\n\n\tProtokolldatei %s nicht gefunden.\n\t-> Es wird das Standardprotokoll verwendet.\n\t (Weiter mit Tastendruck)\n", pfad);
			Taste(d);
			return lesenWProtokoll(NULL, d);
		}
	} else {
		while(!feof(datei))								// bis Dateiende
		{
			if (fread(&tNummer,sizeof(int),1,datei) != 1) break;
			if (fread(tSuchwort,sizeof(char[28]),1,datei) != 1) break;
			if (fread(tEingabe,sizeof(char[28]),1,datei) != 1) break;

			if(d)printf("Debug: Tipp gefunden: %d %s %s\n",tNummer,tSuchwort,tEingabe);

			if ((TPr->Nummer != 0) && (tNummer != TPr->Nummer)) {		// Falls neues Wort und ein Tipp gelesen
				hinzuWProtokoll(&WPr,&TPr,d);						// Wort anhängen
				TPr = (struct TProtokoll*) calloc(1,sizeof(TProtokoll));
				if(TPr == NULL) { printf("Kein Arbeitsspeicher vorhanden.\n"); Taste(d); exit(1);}
			}
			hinzuTProtokoll(&TPr,tNummer,tSuchwort,tEingabe,d);	// Tipp zum TippProtokoll
		}
		fclose(datei);		// Datei zu
		if (TPr != NULL && TPr->Nummer != 0) hinzuWProtokoll(&WPr,&TPr,d); // letztes hinzufügen
	}
	return *WPr;
}

void speichernWProtokoll(struct WProtokoll **s, char* pfad, int d) {
	// WProtokoll nach pfad binär speichern 

	struct WProtokoll *ListW_lauf = *s;						// erster WortlistenEintrag
	struct TProtokoll *ListT_lauf = ListW_lauf->TippProtokoll; // erster TippProtokollEintrag

	if ( ListT_lauf->Nummer != 0) {							// falls Wortliste nicht leer

		FILE *datei;
		datei = fopen(pfad, "wb");							// Datei zum schreiben öffnen

		while(ListT_lauf != NULL){
			if(d)printf("Debug: Tipp geschrieben: %d %s %s\n", ListT_lauf->Nummer,ListT_lauf->Suchwort,ListT_lauf->Eingabe);
			fwrite(&ListT_lauf->Nummer,sizeof(ListT_lauf->Nummer),1,datei);				// Nummer
			fwrite(&ListT_lauf->Suchwort,sizeof(ListT_lauf->Suchwort),1,datei);			// Suchwort
			fwrite(&ListT_lauf->Eingabe,sizeof(ListT_lauf->Eingabe),1,datei);			// Eingabe
			ListT_lauf=ListT_lauf->next;
		}

		while (ListW_lauf->next != NULL ){					// durchlaufe Wortprotokolle
			ListW_lauf=ListW_lauf->next;
			ListT_lauf = ListW_lauf->TippProtokoll;
			while(ListT_lauf != NULL){
				if(d)printf("Debug: Tipp geschrieben: %d %s %s\n", ListT_lauf->Nummer,ListT_lauf->Suchwort,ListT_lauf->Eingabe);
				fwrite(&ListT_lauf->Nummer,sizeof(ListT_lauf->Nummer),1,datei);			// Nummer
				fwrite(&ListT_lauf->Suchwort,sizeof(ListT_lauf->Suchwort),1,datei);		// Suchwort
				fwrite(&ListT_lauf->Eingabe,sizeof(ListT_lauf->Eingabe),1,datei);		// Eingabe
				ListT_lauf=ListT_lauf->next;
			}
		}
		fclose(datei);
		printf("\n\n\tProtokoll gespeichert in %s\n\t (Weiter mit Tastendruck)\n", pfad);
		Taste(d);
	} else {
		if(d)printf("Debug: Nix zu schreiben.\n");
	}
}