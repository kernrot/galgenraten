#include <stdio.h>
#include <stdlib.h>

#include "FktDisp.h"
#include "FktK.h"

// ''''''''''''''''''''''''''''''''''''''
// Alles was ausschließlich zeichnet
// ''''''''''''''''''''''''''''''''''''''

void DispHauptmenu(int Gk, int d){
	// Zeigt das Hauptmenu an, Gk für Anzeige der Groß/Kleinschreibung
	// nicht schön im Code aber toll auf dem Bildschirm
	teilTitel(d);

	printUeberschrift((char*)"Hauptmenu");
	printf("\t(n) Neues Spiel starten.");					nachM();	printSW((char*)" \311\315\315\315\273 ");
	nachR();															printSW((char*)" \263   \272 ");
	printf("\t(a) Anzeigen aller geratenen W\224rter.\t\t");			printSW((char*)"\134\235\57  \272 ");
	printf("\t(v) Anzeigen eines Rateverlaufs.\t\t");					printSW((char*)" \333   \272 ");
	printf("\t(l) L\224schen eines Rateverlaufs.");			nachM();	printSW((char*)"\57 \134  \272 ");
	nachR();															printSW((char*)"     \272 ");
	printf("\t(w) Wortliste einlesen.\t");					nachM();	printSW((char*)"     \272 ");
	printf("\t(p) Protokoll laden.\t");						nachM();	printSW((char*)"    \315\312\315");
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
	printUeberschrift((char*)"Raten");
	printf("\tZu erratendes Wort:\n\t");
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
	printUeberschrift((char*)"Raterverlauf");
	printf("\t f\201r Wort %s\n\n\t", Wort);
	teilWort(Wort, Zeichen);
	teilGalgen(Fehler);
	if (Fehler != 10) {
		printf("\tBisher geratene Zeichen: ");
		for (int i=0; i<lenWort(Zeichen); i++){ printf("%c",Zeichen[i]); }
		printf("\n\n\t(beliebige Taste) f\201r n\204chsten Rateschritt\n\t(Enter) zum Hauptmenu");
	} else {
		printf("\n\n\t(beliebige Taste) um zum Hauptmenu zur\201ck zu kehren.");
	}
}

void DispGewonnen(char *Wort, int d){
	// Bildschirm "Gewonnen"
	teilTitel(d);
	printUeberschrift((char*)"GEWONNEN!");
	printf("\tGl\201ckwunsch!\n\n");
	printf("\tDas gesuchte Wort war: %s\n\n", Wort);
	printSW((char*)"\t                     _---_   ");
	printSW((char*)"\t                    \57     \134 ");
	printSW((char*)"\t                   | () () | ");
	printSW((char*)"\t                    \134  ^  \57 ");
	printSW((char*)"\t                     |||||   ");
	printSW((char*)"\t                     |||||   ");

	//printf("\n\t(Enter) zum Hauptmenu zur\201ck zu kehren\n\t(Leertaste) ein weiteres Wort raten");
}

void DispVerloren(char *Wort, int d){
	// Bildschirm "Gewonnen"
	teilTitel(d);
	printUeberschrift((char*)"VERLOREN!");
	printf("\tSchade!\n\n");
	printf("\tDas gesuchte Wort war: %s\n\n", Wort);
	printSW((char*)"\t                    #----#   ");
	printSW((char*)"\t                    |    |   ");
	printSW((char*)"\t                    |  _---_ ");
	printSW((char*)"\t                    | \57     \134");
	printSW((char*)"\t                    | | () () |");
	printSW((char*)"\t                    |  \134  ^  \57 ");
	printSW((char*)"\t                    |   |||||  ");
	printSW((char*)"\t                    |   |||||  ");
	printSW((char*)"\t                    |          ");
	printSW((char*)"\t                 ___|___       ");

	//printf("\n\t(Enter) zum Hauptmenu zur\201ck zu kehren\n\t(Leertaste) ein weiteres Wort raten");
}

void DispStartbildschirm(){
	// Bildschirm "Start"
	teilTitel(0);
	printf("\n\n\tWillkommen zu\n\n");
	printSW((char*)"\t #--_                                                      ");
	printSW((char*)"\t#      _---_ #    #--_ #---- #   # #---_ _---_ --#-- #---- #   #");
	printSW((char*)"\t#  __  #___# #   #     #___  ##_ # #   # #___#   #   #___  ##_ #");
	printSW((char*)"\t#    # #   # #   #  -# #     # -## #--#  #   #   #   #     # -##");
	printSW((char*)"\t #__#  #   # #___ #__# #____ #   # #  -# #   #   #   #____ #   #");
}

void DispWortlistenEingabe(int d){
	// Bildschirm für eigene Wortliste
	teilTitel(d);
	printUeberschrift((char*)"eigene Wortliste benutzen");	
	printf("\tBitte den Dateinamen der eigenen Wortlliste eingeben\n\t(\"*.txt\" mit Enter best\204tigen.)\n\n\n");	
	return;
}

void DispProtokollEingabe(int d){
	// Bildschirm für Protokoll laden
	teilTitel(d);
	printUeberschrift((char*)"Protokoll laden");	
	printf("\tBitte den Dateinamen des zu ladenden Protokolls eingeben\n\t(Mit Enter best\204tigen.)\n\n\n");	
	return;
}

void DispProtokollSpeichern(int d){
	// Bildschirm für Protokoll speichern
	teilTitel(d);
	printUeberschrift((char*)"Protokoll speichern");	
	printf("\tBitte den Dateinamen eingeben unter dem das Protokoll gespeichert werden soll\n\t(Mit Enter best\204tigen.)\n\n\n");	
	return;
}

// ''''''''''''''''''''''''''''''''''''''
// Bildschirmteile
// ''''''''''''''''''''''''''''''''''''''

void teilTitel(int d){
	// Schreibt Überschrift "Galgenraten"
	system("cls");				//Bildschirm leeren
	printf("\tGalgenraten\n\n");
	if(d)printf("Debugmodus Aktiv\n\n");
}

void teilWort(char *Wort, char *Zeichen){
	// Gibt das Wort aus, nicht geratene Buchstaben werden mit _ ersetzt
	for(int i=0; i<lenWort(Wort); i++){
		if(vorhandeneZeichen(&Wort[i], Zeichen) > 0){
			printf("%c ", Wort[i]);
		} else {
			printf("_ ");
		}
	}
	printf("\n\n");
}

void nachM(){
	// Bildschirmteil für Bildschirmausgabe nach Menü
	printf("\t\t");
}

void nachR(){
	// Bildschirmteil für Bildschirmausgabe nach Raten
	printf("\t\t\t\t\t\t");
}

void teilGalgen(int f){
	// Schreibt Galgen entsprechend den gemachten Fehlern (f)
	switch (f)	{
	case 9:
		nachR(); printSW((char*)" \311\315\315\315\273 ");
		nachR(); printSW((char*)" \263   \272 ");
		nachR(); printSW((char*)"\134\235\57  \272 ");
		nachR(); printSW((char*)" \333   \272 ");
		nachR(); printSW((char*)"\57 \134  \272 ");
		nachR(); printSW((char*)"     \272 ");
		nachR(); printSW((char*)"    \315\312\315");
		nachM(); printf("Vielleicht klappts das n\204chste Mal!\n\n");
		break;
	case 8:
		nachR(); printSW((char*)" \311\315\315\315\273 ");
		nachR(); printSW((char*)" \263   \272 ");
		nachR(); printSW((char*)"\134\235\57  \272 ");
		nachR(); printSW((char*)" \333   \272 ");
		nachR(); printSW((char*)"  \134  \272 ");
		nachR(); printSW((char*)"     \272 ");
		nachR(); printSW((char*)"    \315\312\315");
		nachM();printf("Noch ein Fehler m\224glich!\n\n");
		break;
	case 7:
		nachR(); printSW((char*)" \311\315\315\315\273 ");
		nachR(); printSW((char*)" \263   \272 ");
		nachR(); printSW((char*)"\134\235\57  \272 ");
		nachR(); printSW((char*)" \333   \272 ");
		nachR(); printSW((char*)"     \272 ");
		nachR(); printSW((char*)"     \272 ");
		nachR(); printSW((char*)"    \315\312\315");
		break;
	case 6:
		nachR(); printSW((char*)" \311\315\315\315\273 ");
		nachR(); printSW((char*)" \263   \272 ");
		nachR(); printSW((char*)" \235\57  \272 ");
		nachR(); printSW((char*)" \333   \272 ");
		nachR(); printSW((char*)"     \272 ");
		nachR(); printSW((char*)"     \272 ");
		nachR(); printSW((char*)"    \315\312\315");
		break;
	case 5:
		nachR(); printSW((char*)" \311\315\315\315\273 ");
		nachR(); printSW((char*)" \263   \272 ");
		nachR(); printSW((char*)" \235   \272 ");
		nachR(); printSW((char*)" \333   \272 ");
		nachR(); printSW((char*)"     \272 ");
		nachR(); printSW((char*)"     \272 ");
		nachR(); printSW((char*)"    \315\312\315");
		break;
	case 4:
		nachR(); printSW((char*)" \311\315\315\315\273 ");
		nachR(); printSW((char*)" \263   \272 ");
		nachR(); printSW((char*)" \235   \272 ");
		nachR(); printSW((char*)"     \272 ");
		nachR(); printSW((char*)"     \272 ");
		nachR(); printSW((char*)"     \272 ");
		nachR(); printSW((char*)"    \315\312\315");
		break;
	case 3:
		nachR(); printSW((char*)" \311\315\315\315\273 ");
		nachR(); printSW((char*)" \263   \272 ");
		nachR(); printSW((char*)"     \272 ");
		nachR(); printSW((char*)"     \272 ");
		nachR(); printSW((char*)"     \272 ");
		nachR(); printSW((char*)"     \272 ");
		nachR(); printSW((char*)"    \315\312\315");
		break;
	case 2:
		nachR(); printSW((char*)"   \315\315\273 ");
		nachR(); printSW((char*)"     \272 ");
		nachR(); printSW((char*)"     \272 ");
		nachR(); printSW((char*)"     \272 ");
		nachR(); printSW((char*)"     \272 ");
		nachR(); printSW((char*)"     \272 ");
		nachR(); printSW((char*)"    \315\312\315");
		break;
	case 1:
		nachR(); printSW((char*)"       ");
		nachR(); printSW((char*)"       ");
		nachR(); printSW((char*)"       ");
		nachR(); printSW((char*)"     \272 ");
		nachR(); printSW((char*)"     \272 ");
		nachR(); printSW((char*)"     \272 ");
		nachR(); printSW((char*)"    \315\312\315");
		break;
	case 0:
		nachR(); printSW((char*)"       ");
		nachR(); printSW((char*)"       ");
		nachR(); printSW((char*)"       ");
		nachR(); printSW((char*)"       ");
		nachR(); printSW((char*)"       ");
		nachR(); printSW((char*)"       ");
		nachR(); printSW((char*)"    \315\312\315");
		break;
	}
	printf("\n\n");
}