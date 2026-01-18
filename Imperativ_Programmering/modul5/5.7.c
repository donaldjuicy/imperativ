/************************************************************
 * Program: abstraction_examples.c
 * Formål:
 * Viser brug af funktioner til:
 * 1) Summation af heltal fra 1 til n
 * 2) Befolkningsfremskrivning med vækst
 ************************************************************/

#include <stdio.h>   // Giver adgang til printf

/* ----------------------------------------------------------
 * Funktion: sum_iter
 * Beregner summen af alle heltal fra 1 til n iterativt
 * ---------------------------------------------------------- */
int sum_iter(int n) {
    int sum = 0;                 // Initialiserer summen til 0
    int i;                       // Løbevariabel

    for (i = 1; i <= n; i++) {   // Gennemløber alle tal fra 1 til n
        sum += i;                // Lægger i til summen
    }

    return sum;                  // Returnerer den beregnede sum
}

/* ----------------------------------------------------------
 * Funktion: sum_formula
 * Beregner summen af 1 til n ved brug af formlen
 * (n + 1) * n / 2
 * ---------------------------------------------------------- */
int sum_formula(int n) {
    return (n + 1) * n / 2;      // Returnerer resultatet af formlen
}

/* ----------------------------------------------------------
 * Funktion: population_projection
 * Beregner hvor mange år det tager for en befolkning
 * at overstige en given grænse
 * ---------------------------------------------------------- */
int population_projection(double start,
                          double growth_percent,
                          double limit) {

    int years = 0;               // Tæller antal år
    double population = start;   // Aktuel befolkning

    /* Gentages indtil befolkningen overstiger grænsen */
    while (population <= limit) {
        population += population * (growth_percent / 100.0);
                                    // Øger befolkningen med vækstprocent
        years++;                   // Ét år er gået
    }

    return years;                 // Returnerer antal år
}

/* ----------------------------------------------------------
 * main-funktion
 * Tester alle funktionerne
 * ---------------------------------------------------------- */
int main(void) {

    int n = 100;                 // Testværdi for summation
    int s1, s2;                  // Resultater fra summationsfunktioner
    int years;                   // Antal år for befolkningstilvækst

    /* Kalder summationsfunktionerne */
    s1 = sum_iter(n);            // Beregner summen iterativt
    s2 = sum_formula(n);         // Beregner summen med formel

    /* Udskriver resultaterne */
    printf("Sum fra 1 til %d (iterativ): %d\n", n, s1);
    printf("Sum fra 1 til %d (formel):   %d\n", n, s2);

    /* Sammenligner resultaterne */
    if (s1 == s2) {
        printf("Resultaterne er ens\n\n");
    } else {
        printf("Resultaterne er forskellige\n\n");
    }

    /* Kalder befolkningsfunktionen med værdierne fra bogen */
    years = population_projection(9870, 10.0, 30000);

    /* Udskriver resultatet */
    printf("Det tager %d år for befolkningen at overstige 30000\n",
           years);

    return 0;                    // Programmet afsluttes korrekt
}

/************************************************************
 * Kommentar til output:
 *
 * Programmet består af to dele.
 *
 * Første del beregner summen af alle heltal fra 1 til 100
 * på to forskellige måder:
 *  - ved en iterativ løkke
 *  - ved brug af den matematiske formel (n + 1)*n/2
 *
 * De to resultater vil være ens, hvilket bekræfter
 * at formlen er korrekt.
 *
 * Anden del beregner hvor mange år det tager for en
 * befolkning på 9870 personer at vokse med 10% om året
 * indtil den overstiger 30000.
 *
 * Outputtet viser, at dette tager 13 år.
 ************************************************************/
