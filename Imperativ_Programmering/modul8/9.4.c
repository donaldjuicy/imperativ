/*
=========================================================
FORMÅL:
Dette program implementerer en generel bubblesort (bsort),
som kan sortere et array af vilkårlig datatype. Algoritmen
er stadig bubblesort, men parametrene og byttefunktionen
gør den generel, ligesom qsort.

FAGORD:
- void*: Pointer til "vilkårlig type" (generisk pointer)
- size_t: Unsigned integer type, ofte brugt til størrelser
- Funktionspointer: Pointer til en sammenligningsfunktion
- memcpy: Kopierer byte-for-byte fra en adresse til en anden
=========================================================
*/

#include <stdio.h>
#include <string.h>  // Til memcpy
#include <stdlib.h>  // Til malloc og free

//==========================================================
// bsort: generaliseret bubblesort
// base: pointer til array
// n: antal elementer
// size: størrelse af hvert element i bytes
// compar: pointer til sammenligningsfunktion
//==========================================================
void bsort(void *base, size_t n, size_t size,
           int (*compar)(const void *, const void *))
{
    // Opret midlertidig buffer til at bytte elementer
    void *temp = malloc(size);
    if(temp == NULL) {
        fprintf(stderr, "Fejl: malloc mislykkedes\n");
        return;
    }

    // Pointer til array som char*, så vi kan beregne byte-offset
    char *arr = (char*)base;

    // Bubble sort: ydre loop for antal gennemløb
    for(size_t i = 0; i < n-1; i++)
    {
        // Indre loop: sammenlign naboelementer
        for(size_t j = 0; j < n-1-i; j++)
        {
            // Pointer til element j og j+1
            void *elem1 = arr + j*size;
            void *elem2 = arr + (j+1)*size;

            // Hvis elem1 > elem2 ifølge compar, byt dem
            if(compar(elem1, elem2) > 0)
            {
                // Brug temp som midlertidig buffer
                memcpy(temp, elem1, size);  // gem elem1 i temp
                memcpy(elem1, elem2, size); // kopier elem2 til elem1
                memcpy(elem2, temp, size);  // kopier temp til elem2
            }
        }
    }

    // Frigiv temp buffer
    free(temp);
}

//==========================================================
// EKSEMPEL PÅ SAMMENLIGNINGSFUNKTIONER
//==========================================================

// Sammenlign int
int cmp_int(const void *a, const void *b)
{
    int x = *(int*)a;
    int y = *(int*)b;
    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

// Sammenlign double
int cmp_double(const void *a, const void *b)
{
    double x = *(double*)a;
    double y = *(double*)b;
    if(x < y) return -1;
    if(x > y) return 1;
    return 0;
}

//==========================================================
// MAIN: Test af bsort
//==========================================================
int main(void)
{
    int arr[] = {5, 2, 9, 1, 5};
    size_t n = sizeof(arr)/sizeof(arr[0]);

    printf("Før sortering: ");
    for(size_t i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    // Kald bsort med int sammenligning
    bsort(arr, n, sizeof(int), cmp_int);

    printf("Efter sortering: ");
    for(size_t i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    // Eksempel med double
    double darr[] = {3.2, 1.5, 4.7, 0.9};
    size_t m = sizeof(darr)/sizeof(darr[0]);

    printf("Før sortering: ");
    for(size_t i = 0; i < m; i++)
        printf("%.2f ", darr[i]);
    printf("\n");

    bsort(darr, m, sizeof(double), cmp_double);

    printf("Efter sortering: ");
    for(size_t i = 0; i < m; i++)
        printf("%.2f ", darr[i]);
    printf("\n");

    return 0;
}

/*
EKSEMPEL OUTPUT:

Før sortering: 5 2 9 1 5 
Efter sortering: 1 2 5 5 9 
Før sortering: 3.20 1.50 4.70 0.90 
Efter sortering: 0.90 1.50 3.20 4.70
*/
