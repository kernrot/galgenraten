#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FktProtokoll.h"
#include "FktK.h"

// ''''''''''''''''''''''''''''''''''''''
// Funktionen für die TippProtokoll
// ''''''''''''''''''''''''''''''''''''''

struct TProtokoll hinzuTProtokoll(struct TProtokoll **lst, int Nummer, char Suchwort[28], char Eingabe[28], int d) {
	// Fügt einen Protokolleintrag hinzu

    struct TProtokoll *nElement;
    struct TProtokoll *List_lauf = *lst;						// Startelement der Liste
 
    nElement = (struct TProtokoll*) calloc(1,sizeof(*nElement));// hole  geleerten speicher für ein Element
	//if (nElement) memset(nElement,0,sizeof(*nElement));
    strcpy(nElement->Suchwort,  Suchwort);
	strcpy(nElement->Eingabe,  Eingabe);
	nElement->Nummer = Nummer;
    nElement->next = NULL;										// Folgeelement bzw Ende
	nElement->prev = NULL;										// vorhergehendes Element
 
    if ( List_lauf->Nummer != NULL ) {							// sind Elemente vorhanden
        while (List_lauf->next != NULL )	{					// suche das letzte Element						
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

struct TProtokoll entferneTProtokoll(struct TProtokoll **lst, int d) {
	//entfernt das letzte Element aus der Liste, gibt Liste zurück

    struct TProtokoll *List_lauf = *lst;						// Startelement der Liste
 
    if ( List_lauf->Nummer != NULL ) {							// sind Elemente vorhanden
        while (List_lauf->next != NULL )	{					// suche das letzte Element						
			List_lauf=List_lauf->next;
		}
		if (List_lauf->prev != NULL) List_lauf->prev->next=NULL;// next Pointer des vorletzten Elements auf NULL								
	}
	return **lst;
}

int anzTProtokollTipps(struct TProtokoll **lst, int d) {
	//gibt die Anzahl an Tipps zurück

    struct TProtokoll *List_lauf = *lst;						// Startelement der Liste
	int anz = 0;
    if ( List_lauf->Nummer != NULL ) {			// sind Elemente vorhanden
		while (List_lauf->next != NULL )	{					// suche das letzte Element						
			List_lauf = List_lauf->next;
			anz++;
		}
	}
	return anz;
}

void printTProtokoll (struct TProtokoll **lst, int d) {
	//print für ein TippProtokoll, gibt Anzahl der Rateversuche zurück

    struct TProtokoll *List_lauf = *lst;						// Startelement der Liste
	int vers = 0;												// Summe der Versuche
    if ( List_lauf->Nummer != NULL ) {							// sind Elemente vorhanden
	
		printf("\nNr. %d\t\t      Suchwort \302 Eingabe\n", List_lauf->Nummer);		//Tabellenkopf etc.
		printf("\t\t\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\305\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\n");
		while (List_lauf->next != NULL )	{					// laufe bis zum letzen Element						
			List_lauf = List_lauf->next;
			printf("%30s \263 %-30s\n", List_lauf->Suchwort, List_lauf->Eingabe);
			vers++;
		}
		printf("\n\t\t\t%d Versuche.\n", vers);
	}
	else
	{
		printf("TProtokoll ist leer.\n");
	}
}


// ''''''''''''''''''''''''''''''''''''''
// Funktionen für die WortProtokollliste
// ''''''''''''''''''''''''''''''''''''''

struct WProtokoll hinzuWProtokoll(struct WProtokoll **lst, struct TProtokoll **an, int d) {
	//ein TippProtokoll zum WortProtokoll hinzufügen, gibt das hinzugefügte zurück

    struct WProtokoll *nElement;
    struct WProtokoll *List_lauf = *lst;						// Startelement der Liste
 
    nElement = (struct WProtokoll*)  calloc(1,sizeof(WProtokoll));	// hole  geleerten speicher für ein Element
	//if (nElement) memset(nElement,0,sizeof(*nElement));
	nElement->TippProtokoll = *an;
    nElement->Nummer = nElement->TippProtokoll->Nummer;
	nElement->next = NULL;										// Folgeelement bzw Ende
	nElement->prev = NULL;										// vorhergehendes Element
 
    if ( List_lauf->Nummer != NULL ) {			// sind Elemente vorhanden
        while (List_lauf->next != NULL )	{					// suche das letzte Element						
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
	//entfernt das letzte Element aus der Liste gibt Liste zurück

    struct WProtokoll *List_lauf = *lst;						// Startelement der Liste
	
    if ( List_lauf->Nummer != NULL ) {							// sind Elemente vorhanden
        while (List_lauf->next != NULL )	{					// suche das letzte Element						
			*List_lauf=*List_lauf->next;
		}
		*List_lauf=*List_lauf->prev;
		List_lauf->next=NULL;								// next Pointer des vorletzten Elements auf NULL								
    }
	return **lst;
}
int anzWProtokoll(struct WProtokoll **lst, int d) {
	// Anzahl der TippProtokolle in einem WortProtokoll

    struct WProtokoll *List_lauf = *lst;						// Startelement der Liste
	int anz = 0;

    if ( List_lauf->Nummer != NULL ) {							// sind Elemente vorhanden
		anz = 1;
        while (List_lauf->next != NULL )	{					// suche das letzte Element							
			List_lauf=List_lauf->next;
			anz++;
		}
    }
	return anz;
}

void printWProtokoll(struct WProtokoll **lst, int d) {
	// printTProtokoll für alle TippProtokolle in einem WortProtokoll

    struct WProtokoll *List_lauf = *lst;						// Startelement der Liste
	
    if ( List_lauf->Nummer != NULL ) {			// sind Elemente vorhanden
        printTProtokoll(&(List_lauf->TippProtokoll),d);
		printf("\n\tbeliebige Taste dr\201cken f\201r n\204chstes Wort\n\n");
		Taste(d);
		while (List_lauf->next != NULL )	{					// suche das letzte Element						
			List_lauf=List_lauf->next;
			printTProtokoll(&(List_lauf->TippProtokoll),d);
			printf("\n\tbeliebige Taste dr\201cken f\201r n\204chstes Wort\n\n");
			Taste(d);
		}
    }
	else
	{
		printf("WortProtokoll ist leer.\n");
		Taste(d);
	}
}

void printWProtokollEinzelwoerter(struct WProtokoll **lst, int numMarkiert, int d) {
	// alle TippProtokolle in einem WortProtokoll auflisten

    struct WProtokoll *List_lauf = *lst;		// Startelement der Liste
	char m;

    if ( List_lauf->Nummer != NULL ) {			// sind Elemente vorhanden
		if  (iPos(List_lauf->TippProtokoll->Nummer) == numMarkiert) { m = '>'; } else { m = ' '; }
		printf("\t%c %d\t %s\n",m , iPos(List_lauf->TippProtokoll->Nummer) , List_lauf->TippProtokoll->Suchwort);
		while (List_lauf->next != NULL )	{					// gehe bis letztes Element						
			List_lauf= List_lauf->next;
			if  (iPos(List_lauf->TippProtokoll->Nummer) == numMarkiert) { m = '>'; } else { m = ' '; }
			printf("\t%c %d\t %s\n", m, iPos(List_lauf->TippProtokoll->Nummer) , List_lauf->TippProtokoll->Suchwort);
		}
    }
	else
	{
		printf("WortProtokoll ist leer.\n");
	}
}

struct WProtokoll lesenWProtokoll(char* pfad, int d) {
	// WProtokoll aus binärdatei lesen

	if (pfad == NULL) {				// ohne übergebenen pfad -> Standarddatei
		pfad = "protokoll.log";
	}

	struct TProtokoll *TPr;
	TPr = (struct TProtokoll*)  calloc(1,sizeof(TProtokoll));
	//if (TPr) memset(TPr,0,sizeof(*TPr));
	struct WProtokoll *WPr;
	WPr = (struct WProtokoll*)  calloc(1,sizeof(WProtokoll));
	//if (WPr) memset(WPr,0,sizeof(*WPr));


	FILE *datei;
	datei = fopen(pfad, "r");									// Datei zum lesen öffnen

	int tNummer;												//temporäre einlese Variablen
	char tSuchwort[28];
	char tEingabe[28];

	
	if ((unbenutzteZeichen(pfad, "protokoll.log") < 1) && (datei == NULL)) {	// Falls Standarddatei leer Programmabbruch mit Fehlermeldung
		printf("Standardprotokoll protokoll.log nicht gefunden. Programm wird beendet.");
		Taste(d);
		exit(1);
	}

	if(NULL == datei) 	{						// Falls Datei nicht gefunden
		WPr = (struct WProtokoll*)  calloc(1,sizeof(WProtokoll));
		//if (WPr) memset(WPr,0,sizeof(*WPr));
		*WPr = lesenWProtokoll(NULL,d);
		printf("\n\n\tProtokolldatei nicht gefunden.\n\t-> Es wurde das Standardprotokoll geladen.\n\t (Weiter mit Tastendruck)\n");
		Taste(d);
	} else {
		while(!feof(datei))								// bis Dateiende
		{
			fread(&tNummer,sizeof(int),1,datei);		// Nummer
			fread(tSuchwort,sizeof(char[28]),1,datei);	// Suchwort
			fread(tEingabe,sizeof(char[28]),1,datei);	// Eingabe

			if(!feof(datei)){
				if(d)printf("Debug: Tipp gefunden: %d %s %s\n",tNummer,tSuchwort,tEingabe);

				if ((TPr->Nummer != NULL) && (tNummer != TPr->Nummer)) {		//Falls neues Wort und ein Tipp gelesen
					hinzuWProtokoll(&WPr,&TPr,d);						//Wort anhängen
					TPr = (struct TProtokoll*)  calloc(1,sizeof(TProtokoll));TPr->Nummer = NULL;
					//if (TPr) memset(TPr,0,sizeof(*TPr));
				}
				hinzuTProtokoll(&TPr,tNummer,tSuchwort,tEingabe,d);	//Tipp zum TippProtokoll
			}
		}
		fclose(datei);		// Datei zu
		if (TPr != NULL) hinzuWProtokoll(&WPr,&TPr,d);						// letztes hinzufügen
	}
	return *WPr;
}

void speichernWProtokoll(struct WProtokoll **s, char* pfad, int d) {
	// WProtokoll nach pfad binär speichern

	struct WProtokoll *ListW_lauf = *s;						//erster WortlistenEintrag
	struct TProtokoll *ListT_lauf = ListW_lauf->TippProtokoll;	//erster TippProtokollEintrag

	if ( ListT_lauf->Nummer != 0) {							//falls Wortliste nicht leer

		
		FILE *datei;
		datei = fopen(pfad, "w+");							//Datei zum schreiben öffnen

		while(ListT_lauf != NULL){
			if(d)printf("Debug: Tipp geeschrieben: %d %s %s\n", ListT_lauf->Nummer,ListT_lauf->Suchwort,ListT_lauf->Eingabe);
			fwrite(&ListT_lauf->Nummer,sizeof(ListT_lauf->Nummer),1,datei);				//Nummer
			fwrite(&ListT_lauf->Suchwort,sizeof(ListT_lauf->Suchwort),1,datei);			//Suchwort
			fwrite(&ListT_lauf->Eingabe,sizeof(ListT_lauf->Eingabe),1,datei);			//Tipp
			if ((ListT_lauf->next == NULL) && (ListW_lauf->next != NULL ))	// Wenn letzter Tipp und weiteres Wort vorhanden
			{
				ListW_lauf = ListW_lauf->next;								// nächster WortProtokollEintrag
				ListT_lauf = ListW_lauf->TippProtokoll;						// Erster TippProtokollEintrag
			} else {
				ListT_lauf=ListT_lauf->next;
			}
		}

		fclose(datei);
	} else { 
		if(d)printf("Debug: Nix zu schreiben.");
	}

}