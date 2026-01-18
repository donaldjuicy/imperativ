/************************************************************
 * Program: goldbach.c
 * Formål:
 * Beviser variationen af Goldbachs formodning:
 * "Ethvert lige heltal større end 6 kan skrives som summen
 *  af to ulige primtal"
 ************************************************************/

#include <stdio.h>      // Giver adgang til printf
#include "primes.h"    // Giver adgang til funktionen is_prime

/* ----------------------------------------------------------
 * Funktion: check_goldbach
 * Undersøger om et lige tal n kan skrives som summen
 * af to ulige primtal.
 * Returnerer 1 hvis påstanden holder, ellers 0.
 * ---------------------------------------------------------- */
int check_goldbach(int n) {
    int i;                              // Variabel til at gennemløbe mulige primtal

    /* Gennemløber alle ulige tal fra 3 op til n/2 */
    for (i = 3; i <= n / 2; i += 2) {   // i øges med 2 for kun at teste ulige tal

        /* Tester om både i og n-i er primtal */
        if (is_prime(i) && is_prime(n - i)) {
            return 1;                  // Påstanden er bevist for n
        }
    }

    return 0;                          // Ingen gyldig sum fundet
}

/* ----------------------------------------------------------
 * main-funktion
 * Tester påstanden for alle lige tal mellem to grænser
 * ---------------------------------------------------------- */
int main(void) {

    int lower = 8;                     // Nedre grænse (skal være > 6)
    int upper = 2000000;               // Øvre grænse
    int n;                             // Variabel til gennemløb af lige tal

    /* Gennemløber alle lige tal mellem lower og upper */
    for (n = lower; n <= upper; n += 2) {   // n øges med 2 for kun at teste lige tal

        /* Tester Goldbachs formodning for tallet n */
        if (!check_goldbach(n)) {           // Hvis påstanden ikke holder
            printf("Modeksempel fundet: %d\n", n);
            return 0;                       // Programmet afsluttes straks
        }
    }

    /* Hvis ingen modeksempler blev fundet */
    printf("Goldbachs formodning holder for alle lige tal mellem %d og %d\n",
           lower, upper);

    return 0;                               // Programmet afsluttes korrekt
}

/************************************************************
 * Kommentar til output:
 *
 * Programmet tester alle lige heltal fra 8 til 2.000.000.
 * For hvert tal undersøges det, om det kan skrives som
 * summen af to ulige primtal.
 *
 * Hvis et modeksempel findes, udskrives:
 *
 *   Modeksempel fundet: <tal>
 *
 * og programmet stopper.
 *
 * Hvis ingen modeksempler findes (hvilket forventes),
 * udskrives:
 *
 *   Goldbachs formodning holder for alle lige tal mellem
 *   8 og 2000000
 *
 * Dette indikerer, at formodningen er empirisk bekræftet
 * for det angivne interval.
 ************************************************************/
