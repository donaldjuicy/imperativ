/*
=========================================================
FORMÅL:
Simulerer kast med n terninger, hvor n kan variere. 
Funktionen roll_multiple_dice allokerer dynamisk et array,
fylder det med tilfældige kast (1-6) og returnerer pointeren
til arrayet. Main kalder funktionen 10 gange og udskriver 
resultaterne.

FAGORD:
- Dynamisk hukommelse: Allokeres under kørsel med malloc
- free: Frigiver dynamisk allokeret hukommelse
- rand: Genererer pseudo-tilfældige tal
- Arrays: Samling af n kast
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//==========================================================
// Funktion: roll_multiple_dice
// Input: n = antal terninger
// Output: pointer til array af n ints med terningekast
//==========================================================
int* roll_multiple_dice(int n)
{
    // Alloker dynamisk plads til n ints
    int *dice = (int*)malloc(n * sizeof(int));
    if(dice == NULL) {
        fprintf(stderr, "Fejl: malloc mislykkedes\n");
        return NULL;
    }

    // Fyld array med terningekast: 1-6
    for(int i = 0; i < n; i++)
    {
        dice[i] = (rand() % 6) + 1;  // rand() % 6 giver 0-5, +1 -> 1-6
    }

    // Returner pointeren til arrayet
    return dice;
}

//==========================================================
// MAIN
//==========================================================
int main(void)
{
    int n;  // Antal terninger pr. kast

    // Seed tilfældige tal med systemtid
    srand(time(NULL));

    // Spørg brugeren om antal terninger
    printf("Indtast antal terninger (n): ");
    scanf("%d", &n);
    if(n <= 0) {
        printf("Antal terninger skal være positivt.\n");
        return 1;
    }

    // Kald roll_multiple_dice 10 gange
    for(int k = 1; k <= 10; k++)
    {
        int *kast = roll_multiple_dice(n); // Alloker array og kast terninger
        if(kast == NULL) {
            return 1; // Stop hvis malloc fejler
        }

        // Udskriv resultatet af kast k
        printf("Kast %d: ", k);
        for(int i = 0; i < n; i++)
        {
            printf("%d ", kast[i]);
        }
        printf("\n");

        free(kast); // Frigiv dynamisk hukommelse
    }

    return 0;
}

/*
EKSEMPEL PÅ KØRSEL:

Indtast antal terninger (n): 5
Kast 1: 3 6 1 4 2 
Kast 2: 5 2 6 1 3 
Kast 3: 4 4 2 6 5 
Kast 4: 1 2 3 4 5 
Kast 5: 6 6 1 2 3 
Kast 6: 2 5 4 1 6 
Kast 7: 3 2 6 5 1 
Kast 8: 4 1 2 3 6 
Kast 9: 5 3 6 2 4 
Kast 10: 1 4 5 6 2
*/
