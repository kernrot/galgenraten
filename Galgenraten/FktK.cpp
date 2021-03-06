#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#include "FktK.h"

// ''''''''''''''''''''''''''''''''''''''
// Allgemein n�tzlich Funktionen
// ''''''''''''''''''''''''''''''''''''''

int char2intZahlenTasten(char c) {
	// zu einer Zahlentaste das entsprechende int zur�ckgeben, -1 wenn keine Zahl
	int i=0;
	if (c<58 && c>47){
		i=c-48;
	}else{	
		i=-1;
	}
	return i;
}

int intPositiv(int i) {
	// Integer postiv machen
	if (i<0) i=i*-1;
	return i;
}

int Zufall(int max) {
	//gibt eine Zufallszahl zwischen 0 und max zur�ck
	return rand() % (max+1);
}

char Taste(int d) {
	// F�ngt einen Tastendruck ab und gibt das passende Zeichen zur�ck
	char key=0;
	while (key == 0) {
		_sleep(10);				// verringert die Schleifengeschwindgikeit und damit Prozessorauslastung
		key =  _kbhit();
	}
	key = getch();
	if (key == -32 || key == 0) key = _getch();		// Umgehung f�r Sondertasten
	if(d)printf("\nDebug: Taste: %d", key);
	return key;
}


char* charsKlein(char *c) {
	// gibt das einem Zeichen eintsprechende als kleingeschriebenes zur�ck
	for (int i=0; i<lenWort(c); i++){
		if ((c[i] > 64) && (c[i] < 91)){					// A-Z
			c[i] += 32;
		}
		switch (c[i]){
		case char(142) : c[i] = char(132); break;		// �
		case char(153) : c[i] = char(148); break;		// �
		case char(154) : c[i] = char(129); break;		// �
		}

	}
	return c;
}

char* charsGK(char *c, int gk){
	if (gk == 1) { charsKlein(c);}	
	return c;
}

int checkPfad(char* Pfad){
	//Pr�ft eine Zeichenkette (Dateiname) auf Sonderzeichen, return 0 wenn Sonderzeichen enthalten.
	int gueltig=1;
	int pfadLaenge = lenWort(Pfad);

	for (int i=0;i<pfadLaenge;i++){
		// if (Gro�buchstaben              ||oder  Kleinbuchstaben            ||   oder Punkt  || oder    Zahlen)
		if ((Pfad[i] < 91 && Pfad[i] > 64) || (Pfad[i] < 123 && Pfad[i] > 96) || Pfad[i] == 46 || (Pfad[i] < 58 && Pfad[i] > 47)){
			//g�ltiges Zeichen
			//printf("%d",Pfad[i],Pfad[i]);
		}else{
			//ung�ltiges Zeichen
			gueltig = 0;
		}
	}
	return gueltig;
}

// ''''''''''''''''''''''''''''''''''''''
// Funktionen zur Zeichenkettenverarbeitung
// ''''''''''''''''''''''''''''''''''''''

int lenWort(char *Wort) {
	// Gibt die Wortl�nge einer Zeichenkette zur�ck
	int i = 0; 
	int ende = 0;

	while (ende != 1){
		if (Wort[i] == '\0'){ 
			ende = 1;
		} else {
			i++;
		}
	}
	return i;
}

int vorhandeneZeichen (char *suchZeichen, char *Zeichenkette) {
	// Pr�ft ob ein Zeichen in einer Zeichenkette vorhanden ist, return Position oder -1 falls nicht
	int anz=0;
	for(int i=0;i<lenWort(Zeichenkette);i++){
		for (int j=0;j<lenWort(suchZeichen);j++){
			if (Zeichenkette[i] == suchZeichen[j]) {
				anz++;
			}
		}
	}
	return anz;
}


int fehlendeZeichen(char *Wort, char *Zeichen){
	// Pr�ft wieviele Zeichen in Wort und nicht in Zeichen enthalten sind.
	int fehlendeZeichen = 0;

	for (int i=0; i<lenWort(Wort); i++){
		fehlendeZeichen++;
		for(int j=0; j<lenWort(Zeichen); j++){

			if (Wort[i] == Zeichen[j]){
				fehlendeZeichen--;
			}
		}
	}

	//printf("Fehlende Zeichen %d\n",fehlendeZeichen);
	return fehlendeZeichen;
}

int unbenutzteZeichen(char *Wort, char *Zeichen){
	// Pr�ft wieviele Zeichen aus Zeichen nicht in Wort enthalten sind.

	int unbenutzteZeichen = lenWort(Zeichen);

	for (int i=0; i<lenWort(Zeichen) ; i++){
		for(int j=0; j<lenWort(Wort); j++){
			if (Wort[j] == Zeichen[i]){
				unbenutzteZeichen--;
				j = lenWort(Wort);
			}
		}
	}

	//printf("Unbenutzte Zeichen %d\n",unbenutzteZeichen);
	return unbenutzteZeichen;
}

void printSW(char line[80]){
	//Zeichenfunktion f�r einfache Bildschirmgrafik mit #-_ als ausgef�llte Bl�cke
	for (int i=0; i<lenWort(line); i++){
		switch (line[i]){
		case '#':	printf("%c",219); break;
		case '-':	printf("%c",223); break;
		case '_':	printf("%c",220); break;
		case '~':	printf("%c",196); break;
		case '�':	printf("%c",217); break;
		case '`':	printf("%c",192); break;
		case '|':	printf("%c",179); break;
		default:	printf("%c",line[i]); break;
		}

	}
	printf("\n");
}

void printUeberschrift(char* Text){
	// Schreibt Text mit Rahmen als �berschrift
	char Zeile1[80]={}, Zeile2[80]={};		// 2 Zeilen anlegen
	strcat(Zeile1,"\t| ");	strcat(Zeile1,Text);  strcat(Zeile1, " |");
	printSW(Zeile1);		// Zeile zusammenst�ckeln und ausgeben
	strcat(Zeile2,"\t`~");
	for (int i=0; i<lenWort(Text);i++) strcat(Zeile2,"~");  strcat(Zeile2, "~�\n");
	printSW(Zeile2);		// Zeile entsprechend l�nge zusammenst�ckeln und ausgeben
}