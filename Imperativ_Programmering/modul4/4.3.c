/*===========================================================
  PROGRAM: Summering af tal i intervallet fra n til 2*n
  Formål: Vise brug af for-løkker og while-løkker med betingelser
  Kommentarer forklarer hvert trin for begyndere
===========================================================*/

#include <stdio.h>

int main(void) {

    int n;
    printf("Indtast et heltal n: ");
    scanf("%d", &n);  // læs et heltal fra brugeren

    int sum = 0;  // variabel til at gemme summen

    /***********************
     * 1️⃣ Version med for-løkke
     ***********************/
    printf("\nVersion med for-løkke:\n");

    if (n >= 0) {
        // Hvis n er ikke-negativ, adderes fra n til 2*n
        for (int i = n; i <= 2 * n; i++) {
            sum = sum + i;  // læg tallet til summen
        }
    } else {
        // Hvis n er negativ, adderes fra 2*n til n
        for (int i = 2 * n; i <= n; i++) {
            sum = sum + i;
        }
    }

    printf("Summen er: %d\n", sum);

    /***********************
     * 2️⃣ Version med while-løkke
     ***********************/
    printf("\nVersion med while-løkke:\n");

    sum = 0;  // nulstil summen
    int start, end;

    if (n >= 0) {
        start = n;
        end = 2 * n;
    } else {
        start = 2 * n;
        end = n;
    }

    int i = start;  // start tælleren
    while (i <= end) {
        sum = sum + i;  // læg tallet til summen
        i = i + 1;      // gå til næste tal
    }

    printf("Summen er: %d\n", sum);

    /***********************
     * Forklaring:
     * - for-løkke: kompakt måde at iterere fra start til slut
     * - while-løkke: gør det samme men med tydelig start, slut og tæller
     * - sum = sum + i: lægger hvert tal til summen
     * - Hvis n negativ: intervallet starter fra 2*n op til n
     * - Hvis n ikke-negativ: intervallet starter fra n op til 2*n
     ***********************/

    return 0;
}

/* Eksempler:
   Input: n = 3
   Output: 3+4+5+6 = 18

   Input: n = -2
   Output: -4+-3+-2 = -9
*/
