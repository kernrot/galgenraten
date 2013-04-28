#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) && !defined(__CYGWIN__)
#include <conio.h>
#include <windows.h>
#define _sleep(ms) Sleep(ms)
#elif defined(__CYGWIN__) || defined(__linux__)
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#define _sleep(ms) usleep((ms)*1000)
#else
#include <conio.h>
#endif

#include "FktK.h"

// ''''''''''''''''''''''''''''''''''''''
// Allgemein nützliche Funktionen
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
	// Integer positiv machen
	if (i<0) i=i*-1;
	return i;
}

int Zufall(int max) {
	// gibt eine Zufallszahl zwischen 0 und max zurück
	return rand() % (max+1);
}

char Taste(int d) {
	// Fängt einen Tastendruck ab und gibt das passende Zeichen zurück
	char key=0;
#if defined(__CYGWIN__) || defined(__linux__)
	struct termios oldt, newt;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	int r = read(STDIN_FILENO, &key, 1);
	if (r <= 0) key = 0;

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#else
	while (key == 0) {
		_sleep(10);				// verringert die Schleifengeschwindigkeit und damit Prozessorauslastung
		key =  _kbhit();
	}
	key = getch();
	if (key == -32 || key == 0) key = _getch();		// Umgehung für Sondertasten
#endif
	if(d)printf("\nDebug: Taste: %d", key);
	return key;
}


char* charsKlein(char *c) {
	// gibt das einem Zeichen entsprechende als kleingeschriebenes zurück
	for (int i=0; i<lenWort(c); i++){
		if ((c[i] > 64) && (c[i] < 91)){					// A-Z
			c[i] += 32;
		}
		switch ((unsigned char)c[i]){
		case 142 : c[i] = (char)132; break;		// Ä -> ä
		case 153 : c[i] = (char)148; break;		// Ö -> ö
		case 154 : c[i] = (char)129; break;		// Ü -> ü
		}

	}
	return c;
}

char* charsGK(char *c, int gk){
	if (gk == 1) { charsKlein(c);}	
	return c;
}

int checkPfad(char* Pfad){
	// Prüft eine Zeichenkette (Dateiname) auf Sonderzeichen, return 0 wenn Sonderzeichen enthalten.
	int gueltig=1;
	int pfadLaenge = lenWort(Pfad);

	for (int i=0;i<pfadLaenge;i++){
		// if (Großbuchstaben ||oder Kleinbuchstaben || oder Punkt || oder Zahlen)
		if ((Pfad[i] < 91 && Pfad[i] > 64) || (Pfad[i] < 123 && Pfad[i] > 96) || Pfad[i] == 46 || (Pfad[i] < 58 && Pfad[i] > 47)){
			// gültiges Zeichen
		}else{
			// ungültiges Zeichen
			gueltig = 0;
		}
	}
	return gueltig;
}

// ''''''''''''''''''''''''''''''''''''''
// Funktionen zur Zeichenkettenverarbeitung
// ''''''''''''''''''''''''''''''''''''''

int lenWort(char *Wort) {
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

int vorhandeneZeichen (char *suchZeichen, char *Zeichenkette) {
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


int fehlendeZeichen(char *Wort, char *Zeichen){
	// Prüft wie viele Zeichen in Wort und nicht in Zeichen enthalten sind.
	int fehlendeZeichen = 0;

	for (int i=0; i<lenWort(Wort); i++){
		fehlendeZeichen++;
		for(int j=0; j<lenWort(Zeichen); j++){

			if (Wort[i] == Zeichen[j]){
				fehlendeZeichen--;
			}
		}
	}

	return fehlendeZeichen;
}

int unbenutzteZeichen(char *Wort, char *Zeichen){
	// Prüft wie viele Zeichen aus Zeichen nicht in Wort enthalten sind.

	int unbenutzteZeichen = lenWort(Zeichen);

	for (int i=0; i<lenWort(Zeichen) ; i++){
		for(int j=0; j<lenWort(Wort); j++){
			if (Wort[j] == Zeichen[i]){
				unbenutzteZeichen--;
				j = lenWort(Wort);
			}
		}
	}

	return unbenutzteZeichen;
}

void printSW(char line[80]){
	// Zeichenfunktion für einfache Bildschirmgrafik mit #-_ als ausgefüllte Blöcke
	for (int i=0; i<lenWort(line); i++){
		switch ((unsigned char)line[i]){
		case '#':	printf("%c",219); break;
		case '-':	printf("%c",223); break;
		case '_':	printf("%c",220); break;
		case '~':	printf("%c",196); break;
		case 180:	printf("%c",217); break;
		case 96:	printf("%c",192); break;
		case '|':	printf("%c",179); break;
		default:	printf("%c",line[i]); break;
		}

	}
	printf("\n");
}

void printUeberschrift(char* Text){
	// Schreibt Text mit Rahmen als Überschrift
	char Zeile1[80]={}, Zeile2[80]={};		// 2 Zeilen anlegen
	strcat(Zeile1,"\t| ");	strcat(Zeile1,Text);  strcat(Zeile1, " |");
	printSW(Zeile1);		// Zeile zusammenstückeln und ausgeben
	strcat(Zeile2,"\t~");
	for (int i=0; i<lenWort(Text);i++) strcat(Zeile2,"~");  strcat(Zeile2, "~?\n");
	printSW(Zeile2);		// Zeile entsprechend länge zusammenstückeln und ausgeben
}