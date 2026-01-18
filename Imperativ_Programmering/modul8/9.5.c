/*
=========================================================
FORMÅL:
Programmet allokerer dynamisk plads til 100 doubles,
fylder dem med tilfældige tal, udskriver arrayet, sorterer
med qsort og udskriver arrayet igen for at se resultatet.

FAGORD:
- malloc: dynamisk hukommelsesallokering
- free: frigiver dynamisk hukommelse
- qsort: standardbibliotekets generiske sorteringsfunktion
- funktionspointer: pointer til en sammenligningsfunktion
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>  // Til malloc, free, qsort
#include <time.h>    // Til srand og time (til tilfældige tal)

//==========================================================
// Sammenligningsfunktion til qsort for doubles
// Returnerer -1 hvis a < b, 1 hvis a > b, 0 hvis a == b
//==========================================================
int cmp_double(const void *a, const void *b)
{
    double x = *(double*)a;  // Konverter void* til double*
    double y = *(double*)b;
    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

//==========================================================
// MAIN
//==========================================================
int main(void)
{
    double *array;  // Pointer til dynamisk array
    size_t n = 100; // Antal doubles

    // Initialiser tilfældige tal
    srand(time(NULL));

    // Alloker plads til 100 doubles
    array = (double*)malloc(n * sizeof(double));
    if(array == NULL) {
        // Check om allokering lykkedes
        fprintf(stderr, "Fejl: malloc mislykkedes\n");
        return 1; // Afslut program med fejl
    }

    // Fyld arrayet med 100 tilfældige doubles mellem 0 og 999
    for(size_t i = 0; i < n; i++) {
        array[i] = (double)(rand() % 1000); // Tilfældige tal 0..999
    }

    // Udskriv arrayet før sortering
    printf("Array før sortering:\n");
    for(size_t i = 0; i < n; i++) {
        printf("%.2f ", array[i]);
        if((i+1) % 10 == 0) printf("\n"); // Ny linje hver 10 tal
    }

    // Sorter arrayet med qsort
    qsort(array, n, sizeof(double), cmp_double);

    // Udskriv arrayet efter sortering
    printf("\nArray efter sortering:\n");
    for(size_t i = 0; i < n; i++) {
        printf("%.2f ", array[i]);
        if((i+1) % 10 == 0) printf("\n"); // Ny linje hver 10 tal
    }

    // Frigiv det dynamisk allokerede array
    free(array);

    return 0;
}

/*
EKSEMPEL OUTPUT (tilfældige tal):

Array før sortering:
123.00 456.00 789.00 12.00 ... 
Array efter sortering:
1.00 3.00 5.00 7.00 12.00 ...
*/
