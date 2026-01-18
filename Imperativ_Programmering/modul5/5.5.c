/************************************************************
 * Program: leapyear.c
 * Formål:
 * Sammenligner to funktioner til bestemmelse af skudår:
 * 1) Klassisk version med if-else
 * 2) Ny version med && og || uden if-else
 ************************************************************/

#include <stdio.h>   // Giver adgang til printf

/* ----------------------------------------------------------
 * Klassisk skudårsfunktion med if-else
 * Returnerer 1 hvis year er skudår, ellers 0
 * ---------------------------------------------------------- */
int isLeapYear_if(int year){
    int res;                         // Variabel til resultat

    if (year % 400 == 0)             // År deleligt med 400 er skudår
        res = 1;
    else if (year % 100 == 0)        // År deleligt med 100 er ikke skudår
        res = 0;
    else if (year % 4 == 0)          // År deleligt med 4 er skudår
        res = 1;
    else                             // Alle andre år er ikke skudår
        res = 0;

    return res;                      // Returnerer resultatet
}

/* ----------------------------------------------------------
 * Ny skudårsfunktion uden if-else
 * Bruger kun && og ||
 * Returnerer 1 hvis year er skudår, ellers 0
 * ---------------------------------------------------------- */
int isLeapYear_logic(int year){
    /* 
       Et år er skudår hvis:
       - det er deleligt med 400
       ELLER
       - det er deleligt med 4 OG ikke deleligt med 100
    */
    return (year % 400 == 0) ||
           ((year % 4 == 0) && (year % 100 != 0));
}

/* ----------------------------------------------------------
 * main-funktion
 * Tester begge funktioner for år 1900 til 2100
 * ---------------------------------------------------------- */
int main(void){

    int year;                        // Variabel til gennemløb af årstal
    int leap1, leap2;                // Resultater fra de to funktioner

    /* Gennemløber alle år fra 1900 til 2100 */
    for (year = 1900; year <= 2100; year++) {

        leap1 = isLeapYear_if(year);     // Kalder if-else versionen
        leap2 = isLeapYear_logic(year);  // Kalder logisk version

        /* Hvis resultaterne ikke er ens */
        if (leap1 != leap2) {
            printf("Forskel fundet i år %d\n", year);
            return 0;                   // Programmet afsluttes
        }
    }

    /* Hvis ingen forskelle blev fundet */
    printf("Begge funktioner giver samme resultat for alle år fra 1900 til 2100\n");

    return 0;                           // Programmet afsluttes korrekt
}

/************************************************************
 * Kommentar til output:
 *
 * Programmet tester begge skudårsfunktioner for alle år
 * mellem 1900 og 2100.
 *
 * Hvis de to funktioner giver forskellige resultater
 * for et årstal, udskrives:
 *
 *   Forskel fundet i år <årstal>
 *
 * og programmet stopper.
 *
 * Hvis der ikke findes nogen forskelle, udskrives:
 *
 *   Begge funktioner giver samme resultat for alle år
 *   fra 1900 til 2100
 *
 * Dette viser, at den nye skudårsfunktion baseret på
 * && og || er korrekt og ækvivalent med if-else-versionen.
 ************************************************************/
