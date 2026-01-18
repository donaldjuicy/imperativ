/************************************************************
 * Program: my_sqrt.c
 * Formål:
 * Implementerer egen kvadratrodsfunktion ved brug af
 * Newtons metode og sammenligner med sqrt fra math.h
 ************************************************************/

#include <stdio.h>     // Giver adgang til printf
#include <math.h>      // Giver adgang til sqrt

/* ----------------------------------------------------------
 * Funktion: my_sqrt
 * Beregner kvadratroden af a ved Newtons metode
 * Parameter: a (double)
 * Returnerer: kvadratroden af a som double
 * ---------------------------------------------------------- */
double my_sqrt(double a) {

    double x;                          // Nuværende tilnærmelse
    double next_x;                     // Næste tilnærmelse
    double epsilon = 1e-10;            // Tolerance for stopkriterium

    /* Hvis input er negativt */
    if (a < 0.0) {
        return -1.0;                   // Returnerer -1 som fejlindikator
    }

    /* Hvis input er 0, er kvadratroden også 0 */
    if (a == 0.0) {
        return 0.0;
    }

    x = a;                             // Startgæt (kan være a selv)

    /* Newtons metode: gentag indtil konvergens */
    while (1) {
        next_x = 0.5 * (x + a / x);    // Newtons formel: x_{n+1} = 1/2(x_n + a/x_n)

        /* Stop hvis forskellen er meget lille */
        if (fabs(next_x - x) < epsilon) {
            break;
        }

        x = next_x;                   // Opdater til næste iteration
    }

    return next_x;                    // Returnerer den beregnede kvadratrod
}

/* ----------------------------------------------------------
 * main-funktion
 * Udskriver tabel over a, my_sqrt(a) og sqrt(a)
 * ---------------------------------------------------------- */
int main(void) {

    double a;                          // Variabel til værdier af a

    /* Udskriver tabeloverskrift */
    printf("a\tmy_sqrt(a)\tsqrt(a)\n");
    printf("---------------------------------\n");

    /* Gennemløber alle heltal fra 0 til 25 */
    for (a = 0.0; a <= 25.0; a += 1.0) {

        /* Udskriver a, egen kvadratrod og math.h sqrt */
        printf("%.0f\t%.10f\t%.10f\n",
               a,
               my_sqrt(a),
               sqrt(a));
    }

    return 0;                          // Programmet afsluttes korrekt
}

/************************************************************
 * Kommentar til output:
 *
 * Programmet udskriver en tabel med tre kolonner:
 *
 *  - a            : Tallet der beregnes kvadratrod af
 *  - my_sqrt(a)   : Kvadratrod beregnet med Newtons metode
 *  - sqrt(a)      : Kvadratrod beregnet med math.h
 *
 * Tabellen indeholder værdier for alle heltal fra 0 til 25.
 *
 * Resultaterne fra my_sqrt(a) og sqrt(a) vil være næsten
 * identiske (kun meget små afrundingsforskelle kan forekomme),
 * hvilket viser at Newtons metode leverer meget præcise
 * resultater.
 *
 * Hvis funktionen kaldes med et negativt input, returnerer
 * my_sqrt -1.0 for at indikere en ugyldig beregning.
 ************************************************************/
