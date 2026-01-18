#include <stdio.h>  // Standard input/output bibliotek

int main(void) {
    int value;  // Variabel til at gemme den værdi vi vil kategorisere
    int category; // Variabel til at gemme resultatet af if-else kæden

    // Læs input fra brugeren
    printf("Enter a value: ");
    scanf("%d", &value);

    // If-else kæde (fra mest specifik til mindst specifik)
    if (value >= 90)           // Mest restriktiv: højeste interval først
        category = 11;         // Gælder for value >= 90
    else if (value >= 82)      // Næste interval
        category = 10;         // Gælder for 82 <= value < 90
    else if (value >= 74)
        category = 9;          // Gælder for 74 <= value < 82
    else if (value >= 66)
        category = 8;          // Gælder for 66 <= value < 74
    else if (value >= 58)
        category = 7;          // Gælder for 58 <= value < 66
    else if (value >= 50)
        category = 6;          // Gælder for 50 <= value < 58
    else if (value >= 40)
        category = 5;          // Gælder for 40 <= value < 50
    else if (value >= 10)
        category = 3;          // Gælder for 10 <= value < 40
    else
        category = 0;          // Gælder for value < 10

    // Udskriv resultat
    printf("Value %d corresponds to category %d\n", value, category);

    return 0;
}

/*
Kommentarer til rækkefølge og logik:

- If-else kæden starter med den mest specifikke/højeste betingelse først.
- Når en betingelse er sand, springer programmet resten af kæden over.
- Hver "else if" fanger et interval, som ikke overlapper med de tidligere betingelser.
- Den sidste "else" fanger alle resterende værdier (mindste interval).

Fordel: Dette mønster kan bruges til alle typer multiple-alternative kategoriseringer, fx karakterer, aldersgrupper, eller pH-intervaller.
*/
