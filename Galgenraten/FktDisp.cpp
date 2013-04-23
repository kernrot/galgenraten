#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

#include "FktDisp.h"
#include "FktK.h"

// ''''''''''''''''''''''''''''''''''''''
// Alles was auschließlich zeichnet
// ''''''''''''''''''''''''''''''''''''''

void DispHauptmenu(int Gk, int d){
	// Zeigt das Hauptmenu an, Gk für Anzeige der Groß/Kleinschreibung
	// nicht schön im Code aber toll auf dem Bildschirm
	teilTitel(d);

	printf("\n");	
	printf("\tHauptmenu\n\n");	
	printf("\t(n) Neues Spiel starten.");					nachM();	printSW(" \311\315\315\315\273 ");
	nachR();															printSW(" \263   \272 ");
	printf("\t(a) Anzeigen aller geratenen W\224rter.\t\t");			printSW("\134\235\57  \272 ");
	printf("\t(v) Anzeigen eines Rateverlaufs.\t\t");					printSW(" \333   \272 ");
	printf("\t(l) L\224schen eines Rateverlaufs.");			nachM();	printSW("\57 \134  \272 ");
	nachR();															printSW("     \272 ");
	printf("\t(w) Wortliste einlesen.\t");					nachM();	printSW("     \272 ");
	printf("\t(p) Protokoll laden.\t");						nachM();	printSW("    \315\312\315");
	printf("\t(s) Protokoll speichern unter..\n\n");
	printf("\t(g) Gro\341/Kleinschreibung ");
	if(Gk==1) { printf("[Aus]\n\n"); } if(Gk==-1) { printf("[Ein]\n\n"); } // Groß-/Kleinanzeige
	printf("\t(b) Beenden.\n");	
	printf("\n\n\t(Ausw\204hlen mit Tastendruck)\n");	
	return;
}

void DispRaten(int Fehler, char *Wort, char *Zeichen, int d){
	// Ratebildschirm
	teilTitel(d);
	printf("\n\n\n\tZu erratendes Wort:\n\t");
	teilWort(Wort, Zeichen);
	teilGalgen(Fehler);
	if (Fehler != 10) {
		printf("\tBisher geratene Zeichen: ");
		for (int i=0; i<lenWort(Zeichen); i++){ printf("%c",Zeichen[i]); }
		printf("\n\tBuchstabe tippen um zu raten.");
	} else {
		printf("\n\t(Enter) zum Hauptmenu zur\201ck zu kehren\n(Leertaste) ein weiteres Wort raten");
	}
}

void DispRatenVerlauf(int Fehler, char *Wort, char *Zeichen, int d){
	// modifizierter Ratebildschirm für Verlaufsanzeige
	teilTitel(d);
	printf("\n\n\tRaterverlauf f\201r Wort %s\n\n\t", Wort);
	teilWort(Wort, Zeichen);
	teilGalgen(Fehler);
	if (Fehler != 10) {
		printf("\tBisher geratene Zeichen: ");
		for (int i=0; i<lenWort(Zeichen); i++){ printf("%c",Zeichen[i]); }
		printf("\n\n\t(beliebige Taste) f\201r n\204chsten Rateschritt\n\t(Enter) zum Hauptmenu");
	} else {
		printf("\tgeratene Zeichen: ");
		for (int i=0; i<lenWort(Zeichen); i++){ printf("%c",Zeichen[i]); }
		printf("\n\n\t(beliebige Taste) um zum Hauptmenu zur\201ck zu kehren.");

	}
}

void DispGewonnen(int Fehler ,char *Wort, int d){
	// Bildschirm "Gewonnen"
	if(d!=1){ 
		teilTitel(d);
		printSW("\t #--_                                                      ");
		printSW("\t#       #----  #   #   #--#   #   #  #   #  #----  #   # ");
		printSW("\t#  __   #___   #   #  #    #  ##_ #  ##_ #  #___   ##_ # ");
		printSW("\t#    #  #      #_#_#  #    #  # -##  # -##  #      # -## ");
		printSW("\t #__#   #____  #- -#   #__#   #   #  #   #  #____  #   # ");
	}
	printf("\n\tGewonnen mit %d falschen Tipps, gesuchtes Wort war:\n\t\"%s\".\n\n", Fehler, Wort);
	teilGalgen(Fehler);
	//printf("\n\t(Enter) zum Hauptmenu zur\201ck zu kehren\n\t(Leertaste) ein weiteres Wort raten");

}

void DispVerloren(int Fehler ,char *Wort,int d){
	// Bildschirm "Verloren"
	if(d!=1){ 
		teilTitel(d);
		printSW("\t#   #                                                       ");
		printSW("\t#   #  #----  #---#   #       #--#   #---#   #----  #   # ");
		printSW("\t#   #  #___   #    #  #      #    #  #    #  #___   ##_ # ");
		printSW("\t # #   #      #---#   #      #    #  #---#   #---   # -## ");
		printSW("\t  #    #____  #    #  #____   #__#   #    #  #____  #   # ");
	}
	printf("\n\tVerloren mit %d falschen Tipps, gesuchtes Wort war:\n\t\"%s\".\n\n", Fehler, Wort);
	teilGalgen(Fehler);
	//printf("\n\t(Enter) zum Hauptmenu zur\201ck zu kehren\n\t(Leertaste) ein weiteres Wort raten");

}

void DispWortlistenEingabe(int d){
	//Bildschrim für eigene Wortliste
	teilTitel(d);
	printf("\n");	
	printf("\teigene Wortliste benutzen\n\n");	
	printf("\tBitte den Dateinamen der eigenen Wortlliste eingeben\n\t(\"*.txt\" mit Enter bestätigen.)\n\n\n");	
	return;
}

void DispProtokollEingabe(int d){
	//Bildschrim für anderes Protokoll
	teilTitel(d);
	printf("\n");	
	printf("\tein anderes Protokoll laden\n\n");	
	printf("\tBitte den Dateinamen des Protokolls eingeben\n\t(\"*.log\" mit Enter bestätigen.)\n\n\n");	
	return;
}

void DispProtokollSpeichern(int d){
	//Bildschrim für anderes Protokoll
	teilTitel(d);
	printf("\n");	
	printf("\tProtokoll speichern\n\n");	
	printf("\tBitte den Zieldateinamen des Protokolls eingeben\n\t(\"*.log\" mit Enter bestätigen.)\n\n\n");	
	return;
}

void teilWort(char *Wort, char *Zeichen){
	//Gibt die bisher erratenen Zeichen (in Zeichen) des Worts (in Wort) aus

	for (int i=0; i<lenWort(Wort); i++)
	{
		int z=0;
		for (int j=0; j<lenWort(Zeichen); j++)
		{
			if (Wort[i] == Zeichen[j]) z=1;
		}	

		if (z == 1) { 
			printf("%c ", Wort[i]);
		} else {
			printf("_ ");
		}


	}
	printf("\n\n");
}


void teilTitel(int d){
	//Titelzeile ausgeben
	//cls();
	if(d!=1){ 
		system("CLS");
		printf("\n");
		nachM(); printf("Galgenraten von Conrad Henke\n");
		nachM(); printf("   galgenr\100conradhenke.de\n");
	}
}


void teilGalgen(int Fehlernummer){
	// Galgen und Männlein zeichen
	if (Fehlernummer == 10) {
		//  Komplett (Fehler 10)
		nachR(); printSW(" \311\315\315\315\273 ");
		nachR(); printSW(" \263   \272 ");
		nachR(); printSW("\134\235\57  \272 ");
		nachR(); printSW(" \333   \272 ");
		nachR(); printSW("\57 \134  \272 ");
		nachR(); printSW("     \272 ");
		nachR(); printSW("    \315\312\315");
		nachM(); printf("Vielleicht klappts das n\204chste Mal!\n\n");
	}

	if (Fehlernummer == 9) {
		//	Fehler 9
		nachR(); printSW(" \311\315\315\315\273 ");
		nachR(); printSW(" \263   \272 ");
		nachR(); printSW("\134\235\57  \272 ");
		nachR(); printSW(" \333   \272 ");
		nachR(); printSW("  \134  \272 ");
		nachR(); printSW("     \272 ");
		nachR(); printSW("    \315\312\315");
		nachM();printf("Noch ein Fehler m\224glich!\n\n");
	}

	if (Fehlernummer == 8) {
		//	Fehler 8
		nachR(); printSW(" \311\315\315\315\273 ");
		nachR(); printSW(" \263   \272 ");
		nachR(); printSW("\134\235\57  \272 ");
		nachR(); printSW(" \333   \272 ");
		nachR(); printSW("     \272 ");
		nachR(); printSW("     \272 ");
		nachR(); printSW("    \315\312\315");
		nachM(); printf("Fehler 8 von 10\n\n");
	}

	if (Fehlernummer == 7) {
		//	Fehler 7
		nachR(); printSW(" \311\315\315\315\273 ");
		nachR(); printSW(" \263   \272 ");
		nachR(); printSW(" \235\57  \272 ");
		nachR(); printSW(" \333   \272 ");
		nachR(); printSW("     \272 ");
		nachR(); printSW("     \272 ");
		nachR(); printSW("    \315\312\315");
		nachM(); printf("Fehler 7 von 10\n\n");
	}

	if (Fehlernummer == 6) {
		//	Fehler 6
		nachR(); printSW(" \311\315\315\315\273 ");
		nachR(); printSW(" \263   \272 ");
		nachR(); printSW(" \235   \272 ");
		nachR(); printSW(" \333   \272 ");
		nachR(); printSW("     \272 ");
		nachR(); printSW("     \272 ");
		nachR(); printSW("    \315\312\315");
		nachM(); printf("Fehler 6 von 10\n\n");
	}

	if (Fehlernummer == 5) {
		//	Fehler 5
		nachR(); printSW(" \311\315\315\315\273 ");
		nachR(); printSW(" \263   \272 ");
		nachR(); printSW(" \235   \272 ");
		nachR(); printSW("     \272 ");
		nachR(); printSW("     \272 ");
		nachR(); printSW("     \272 ");
		nachR(); printSW("    \315\312\315");
		nachM(); printf("Fehler 5 von 10\n\n");
	}

	if (Fehlernummer == 4) {
		//	Fehler 4
		nachR(); printSW(" \311\315\315\315\273 ");
		nachR(); printSW(" \263   \272 ");
		nachR(); printSW("     \272 ");
		nachR(); printSW("     \272 ");
		nachR(); printSW("     \272 ");
		nachR(); printSW("     \272 ");
		nachR(); printSW("    \315\312\315");
		nachM(); printf("Fehler 4 von 10\n\n");
	}

	if (Fehlernummer == 3) {
		//	Fehler 3
		nachR(); printSW("   \315\315\273 ");
		nachR(); printSW("     \272 ");
		nachR(); printSW("     \272 ");
		nachR(); printSW("     \272 ");
		nachR(); printSW("     \272 ");
		nachR(); printSW("     \272 ");
		nachR(); printSW("    \315\312\315");
		nachM(); printf("Fehler 3 von 10\n\n");
	}

	if (Fehlernummer == 2) {
		//	Fehler 2
		nachR(); printSW("       ");
		nachR(); printSW("       ");
		nachR(); printSW("       ");
		nachR(); printSW("     \272 ");
		nachR(); printSW("     \272 ");
		nachR(); printSW("     \272 ");
		nachR(); printSW("    \315\312\315");
		nachM(); printf("Fehler 2 von 10\n\n");
	}

	if (Fehlernummer == 1) {
		//	Fehler 1
		nachR(); printSW("       ");
		nachR(); printSW("       ");
		nachR(); printSW("       ");
		nachR(); printSW("       ");
		nachR(); printSW("       ");
		nachR(); printSW("       ");
		nachR(); printSW("    \315\312\315");
		nachM(); printf("Fehler 1 von 10\n\n");
	}

	if (Fehlernummer == 0) {
		//	Leer
		printf("\n\n\n\n\n\n\n");
		nachM(); printf("Fehler 0 von 10\n\n");
	}

}

//nach mitte einrücken
void nachM(){
	printf("\t\t\t");
}

//nach rechts einrücken
void nachR(){
	printf("\t\t\t\t\t\t\t");
}


