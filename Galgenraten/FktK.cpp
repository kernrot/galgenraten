#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <time.h>
#include <conio.h>

#include "FktK.h"

// ''''''''''''''''''''''''''''''''''''''
// Allgemein nützlich Funktionen
// ''''''''''''''''''''''''''''''''''''''

int char2intZahlenTasten(char c) {
	// zu einer Zahlentaste das entsprechende int zurückgeben, -1 wenn keine Zahl
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
	 //gibt eine Zufallszahl zwischen 0 und max zurück

    time_t t;
    time(&t);
    srand((unsigned int)t);              // Zufallsgenerator
	return rand() % (max+1);
  }

char Taste(int d) {
	// Fängt einen Tastendruck ab und gibt das passende Zeichen zurück
	char key=0;
	while (key == 0) {
		_sleep(100);
		key =  kbhit();
	}
	key = getch();
	if (key == -32 || key == 0) key = getch();		// Umgehung für Sondertasten
	if(d)printf("\nDebug: Taste: %d", key);
	return key;
}


char* charsKlein(char c[]) {
	// gibt das einem Zeichen eintsprechende als kleingeschriebenes zurück
	for (int i=0; i<lenWort(c); i++){
		if ((c[i] > 64) && (c[i] < 91)){					// A-Z
			c[i] += 32;
		}
		switch (c[i]){
			case char(142) : c[i] = char(132); break;		// Ä
			case char(153) : c[i] = char(148); break;		// Ö
			case char(154) : c[i] = char(129); break;		// Ü
		}

	}
	return c;
}

char* charsGK(char c[], int gk){
	if (gk == 1) { charsKlein(c);}	
	return c;
}

// ''''''''''''''''''''''''''''''''''''''
// Funktionen zur Zeichenkettenverarbeitung
// ''''''''''''''''''''''''''''''''''''''

int lenWort(char Wort[]) {
	// Gibt die Wortlänge einer Zeichenkette zurück
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

int vorhandeneZeichen (char suchZeichen[], char Zeichenkette[]) {
	// Prüft ob ein Zeichen in einer Zeichenkette vorhanden ist, return Position oder -1 falls nicht
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


int fehlendeZeichen(char Wort[], char Zeichen[]){
	// Prüft wieviele Zeichen in Wort und nicht in Zeichen enthalten sind.
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

int unbenutzteZeichen(char Wort[], char Zeichen[]){
	// Prüft wieviele Zeichen aus Zeichen nicht in Wort enthalten sind.
	
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
	for (int i=0; i<lenWort(line); i++){
		switch (line[i]){
		case '#':	printf("%c",219); break;
		case '-':	printf("%c",223); break;
		case '_':	printf("%c",220); break;
		default:	printf("%c",line[i]); break;
		}

	}
		printf("\n");
}
