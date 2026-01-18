/*===========================================================
  PROGRAM: Eksamen-noter om while-løkker, ++i/i++ og *=
  Formål: Forklare hvordan løkker og udtryk fungerer i C
  Kommentarer er detaljerede, så en begynder kan forstå
===========================================================*/

#include <stdio.h>

int main(void) {

    /***********************
     * 1️⃣ Originalprogram
     ***********************/
    printf("1️⃣ Originalprogram:\n");
    int i = 0, power = 1;

    // while-løkke med ++i og power *= 2
    while (++i <= 10) {
        printf("%5d", power *= 2);  
        // ++i: øg i med 1 før sammenligning
        // power *= 2: fordoble power og brug det nye tal
    }
    printf("\n");
    // Output: 2 4 8 16 32 64 128 256 512 1024
    // Løkken kører 10 gange

    /***********************
     * 2️⃣ Hvis i++ bruges i stedet for ++i
     ***********************/
    printf("\n2️⃣ Med i++:\n");
    i = 0;
    power = 1;

    // while-løkke med i++ (brug først, så øg)
    while (i++ <= 10) {
        power *= 2;
        printf("%5d", power);
    }
    printf("\n");
    // Output: 2 4 8 16 32 64 128 256 512 1024 2048
    // Løkken kører 11 gange

    /***********************
     * 3️⃣ Omskrevet version uden ++ og *= i printf
     ***********************/
    printf("\n3️⃣ Klarere version (uden ++i og *= i printf):\n");
    i = 0;
    power = 1;

    while (i < 10) {       // kører 10 gange
        i = i + 1;          // øg i med 1
        power = power * 2;  // fordoble power
        printf("%5d", power);
    }
    printf("\n");
    // Output: 2 4 8 16 32 64 128 256 512 1024

    /***********************
     * 4️⃣ Version med for-løkke
     ***********************/
    printf("\n4️⃣ Version med for-løkke:\n");
    power = 1;

    for (int i = 1; i <= 10; i++) {
        power = power * 2;         // fordoble power
        printf("%5d", power);
    }
    printf("\n");
    // Output: 2 4 8 16 32 64 128 256 512 1024

    /***********************
     * 5️⃣ Forklaring:
     * - ++i: øger først, brug derefter værdien
     * - i++: brug først, øg derefter
     * - *=2: forkortelse for power = power * 2
     * - printf("%5d", power): skriv tallet med 5 pladser, pænt justeret
     ***********************/

    return 0;
}
