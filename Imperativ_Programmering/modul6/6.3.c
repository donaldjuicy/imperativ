/*
=========================================================
FORMÅL:
Programmet omregner et dollar-beløb til antallet af sedler:
- 100 dollar
- 50 dollar
- 20 dollar
- 10 dollar

Målet:
- Input: beløb, der kan deles med 10
- Output: så få sedler som muligt

EKSEMPEL PÅ INPUT:
380

FORVENTET OUTPUT:
3 x 100-dollar
1 x 50-dollar
1 x 20-dollar
1 x 10-dollar

FAGORD (forklaret kort):
- Funktion: Genbrugelig blok kode
- Input-parameter: Data sendt IND i funktionen
- Output-parameter: Data sendt UD via pointere
- Pointer: Variabel, der gemmer adressen på en anden variabel
- Call by value: Kopi af værdi sendes til funktionen
- Call by reference: Funktion kan ændre variabler i main
- & (adresse-operator): Giver adressen på en variabel
- * (dereference-operator): Giver adgang til værdien på adressen
=========================================================
*/

#include <stdio.h>

/*
FUNKTION:
Udregner antal sedler til et givet beløb

INPUT:
- amount (int): beløbet der skal veksles

OUTPUT (via pointere):
- *hundreds = antal 100-dollar sedler
- *fifties  = antal 50-dollar sedler
- *twenties = antal 20-dollar sedler
- *tens     = antal 10-dollar sedler
*/
void atm_cash(int amount,
              int *hundreds,
              int *fifties,
              int *twenties,
              int *tens)
{
    // Beregner antal 100-dollar sedler
    *hundreds = amount / 100;
    int remainder = amount % 100;  // Resterende beløb

    // Beregner antal 50-dollar sedler
    *fifties = remainder / 50;
    remainder = remainder % 50;

    // Beregner antal 20-dollar sedler
    *twenties = remainder / 20;
    remainder = remainder % 20;

    // Beregner antal 10-dollar sedler
    *tens = remainder / 10;
    // remainder % 10 = 0 fordi input er dividerbart med 10
}

int main(void)
{
    // Input: beløb
    int amount;

    // Output-variabler
    int h, f, t, te;

    // Beder brugeren om input
    printf("Indtast beløb (dividerbart med 10): ");
    // Eksempel-input: 380
    scanf("%d", &amount);

    // Kald funktion med pointere som output-parametre
    atm_cash(amount, &h, &f, &t, &te);

    // Udskriv resultat
    printf("%d x 100-dollar\n", h);
    printf("%d x 50-dollar\n", f);
    printf("%d x 20-dollar\n", t);
    printf("%d x 10-dollar\n", te);

    /*
    FORVENTET OUTPUT I TERMINALEN:

    Indtast beløb (dividerbart med 10): 380
    3 x 100-dollar
    1 x 50-dollar
    1 x 20-dollar
    1 x 10-dollar
    */

    return 0;
}
