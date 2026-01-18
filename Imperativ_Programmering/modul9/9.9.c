/*
=========================================================
FORMÅL:
Dette program demonstrerer, hvordan man kan simulere
et associativt array i C ved hjælp af:
- Et almindeligt C-array
- En funktion h (hashfunktion), som oversætter
  en tekststreng (navn) til et heltalsindeks

Vi viser to varianter:
1) Lille univers af kendte navne (ingen kollisioner)
2) Stort univers (simpel hashfunktion med mulig kollision)

FAGORD:
- Associativt array: Struktur der knytter en "nøgle" til en værdi
- Hashfunktion: Funktion der mapper en nøgle til et indeks
- Kollision: Når to forskellige nøgler giver samme indeks
- Modulo (%): Operator der bruges til normalisering af indeks
=========================================================
*/

#include <stdio.h>
#include <string.h>

#define MAX_PERSON_INDEX 100   // Maksimalt antal mulige indeks

/*
=========================================================
DEL 1: LILLE UNIVERS (EKSPPLICIT h-FUNKTION)
Ingen kollisioner, fordi alle navne er kendt på forhånd
=========================================================
*/

/*
h_small:
- Input: navn (tekststreng)
- Output: entydigt indeks (int)
- Hvert navn returnerer sit eget faste indeks
*/
int h_small(const char *name)
{
    // strcmp sammenligner to strenge
    // returnerer 0 hvis de er ens

    if (strcmp(name, "Peter") == 0) return 0;
    if (strcmp(name, "Anna")  == 0) return 1;
    if (strcmp(name, "Jonas") == 0) return 2;
    if (strcmp(name, "Maria") == 0) return 3;

    // Hvis navnet ikke findes, returneres -1
    return -1;
}

/*
=========================================================
DEL 2: STORT UNIVERS (HASHFUNKTION)
Kan give kollisioner
=========================================================
*/

/*
h_hash:
- Input: navn (tekststreng)
- Output: indeks i intervallet [0, MAX_PERSON_INDEX-1]

Ide:
- Gå gennem hvert tegn i navnet
- Læg ASCII-værdien sammen
- Normaliser med modulo
*/
int h_hash(const char *name)
{
    int sum = 0;  // Akkumulator til summen af tegn

    // Gå gennem strengen tegn for tegn
    for (int i = 0; name[i] != '\0'; i++)
    {
        sum += name[i];  // ASCII-værdien lægges til
    }

    // Normaliser summen til gyldigt indeks
    return sum % MAX_PERSON_INDEX;
}

/*
=========================================================
MAIN
=========================================================
*/
int main(void)
{
    /*
    -----------------------------------------------------
    ASSOCIATIVT ARRAY: alder
    alder[index] = alder på personen
    -----------------------------------------------------
    */
    int alder[MAX_PERSON_INDEX];

    // Initialiser alle aldre til -1 (ukendt)
    for (int i = 0; i < MAX_PERSON_INDEX; i++)
        alder[i] = -1;

    /*
    -----------------------------------------------------
    DEL 1: LILLE UNIVERS
    -----------------------------------------------------
    */
    printf("=== Lille univers (ingen kollisioner) ===\n");

    // Indsæt aldre
    alder[h_small("Peter")] = 22;
    alder[h_small("Anna")]  = 24;
    alder[h_small("Jonas")] = 23;
    alder[h_small("Maria")] = 21;

    // Slå aldre op
    printf("Peter er %d aar gammel\n", alder[h_small("Peter")]);
    printf("Anna er %d aar gammel\n",  alder[h_small("Anna")]);
    printf("Jonas er %d aar gammel\n", alder[h_small("Jonas")]);
    printf("Maria er %d aar gammel\n", alder[h_small("Maria")]);

    /*
    -----------------------------------------------------
    DEL 2: STORT UNIVERS (HASH)
    -----------------------------------------------------
    */
    printf("\n=== Stort univers (hashfunktion) ===\n");

    // Navne i projektgruppen
    const char *names[] = {"Peter", "Anna", "Jonas", "Maria"};
    int ages[] = {22, 24, 23, 21};

    // Indsæt i hash-baseret array
    for (int i = 0; i < 4; i++)
    {
        int index = h_hash(names[i]);
        printf("Indsaetter %s paa index %d\n", names[i], index);
        alder[index] = ages[i];
    }

    // Slå op igen
    for (int i = 0; i < 4; i++)
    {
        int index = h_hash(names[i]);
        printf("%s findes paa index %d med alder %d\n",
               names[i], index, alder[index]);
    }

    /*
    -----------------------------------------------------
    OBSERVATION:
    Hvis to navne giver samme index, opstår kollision.
    Dette program overskriver blot værdien.
    -----------------------------------------------------
    */

    return 0;
}

/*
EKSEMPEL OUTPUT (kan variere):

=== Lille univers (ingen kollisioner) ===
Peter er 22 aar gammel
Anna er 24 aar gammel
Jonas er 23 aar gammel
Maria er 21 aar gammel

=== Stort univers (hashfunktion) ===
Indsaetter Peter paa index 12
Indsaetter Anna paa index 3
Indsaetter Jonas paa index 14
Indsaetter Maria paa index 11
Peter findes paa index 12 med alder 22
Anna findes paa index 3 med alder 24
Jonas findes paa index 14 med alder 23
Maria findes paa index 11 med alder 21
*/
