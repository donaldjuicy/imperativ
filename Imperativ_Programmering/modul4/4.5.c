/*===========================================================
  PROGRAM: Euclids algoritme med og uden ombytning
  Formål: Beregning af GCD (største fælles divisor)
  Kommentarer forklarer hvert trin for begyndere
===========================================================*/

#include <stdio.h>

int main(void) {

    /***********************
     * 1️⃣ Originalversion: med ombytning
     ***********************/
    printf("1️⃣ Euclid med ombytning (small <= large):\n");

    int i, j, small, large, remainder;

    printf("Indtast to positive heltal: ");
    scanf("%d %d", &i, &j);

    // Bestem hvem der er lille og hvem der er stor
    small = i <= j ? i : j;  // small = det mindste af i og j
    large = i <= j ? j : i;  // large = det største af i og j

    // While-løkke fortsætter indtil small = 0
    while (small > 0) {
        remainder = large % small;  // find rest ved division
        large = small;              // flyt small til large
        small = remainder;          // flyt resten til small
    }

    printf("GCD af %d og %d er %d\n\n", i, j, large);
    // Output er korrekt uanset om i > j eller i < j

    /***********************
     * 2️⃣ Version uden ombytning
     ***********************/
    printf("2️⃣ Euclid uden ombytning:\n");

    int a, b;
    int x, y, r;

    printf("Indtast to positive heltal: ");
    scanf("%d %d", &a, &b);

    x = a;   // kopi af a
    y = b;   // kopi af b

    // While-løkke fortsætter indtil y = 0
    while (y > 0) {
        r = x % y; // find resten
        x = y;     // flyt y til x
        y = r;     // flyt resten til y
    }

    printf("GCD af %d og %d er %d\n\n", a, b, x);

    /***********************
     * Forklaring af forskellen:
     * 
     * 1️⃣ Originalversion:
     *   - Sørger for at small <= large før løkken starter
     *   - Forenkler første iteration og undgår negative/modulo problemer
     *
     * 2️⃣ Version uden ombytning:
     *   - Virker stadig korrekt i praksis
     *   - Euclids algoritme håndterer selv om x < y i starten
     *     fordi x % y returnerer x hvis x < y
     *   - Løkken convergerer stadig til GCD
     *
     * Konklusion: Ombytning er **ikke nødvendig**, men gør det mere tydeligt
     * og kan være lettere at forstå for begyndere.
     ***********************/

    return 0;
}

/* Eksempler:
   Input: 48 18
   Output: GCD = 6

   Input: 18 48 (uden ombytning)
   Output: GCD = 6

   Input: 101 103
   Output: GCD = 1
*/
