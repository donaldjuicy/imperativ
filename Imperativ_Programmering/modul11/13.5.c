#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LGT 50       // max længde for navn/gade/by
#define MAX_PERSONS 100       // max antal personer i fil

//=========================================================
// Struct: person
//=========================================================
struct person {
    char fornavn[MAX_NAME_LGT];
    char efternavn[MAX_NAME_LGT];
    char vejnavn[MAX_NAME_LGT];
    int vejnummer;
    int postnummer;
    char bynavn[MAX_NAME_LGT];
};

//=========================================================
// Funktion: compare_efternavn
// Bruges af qsort til at sortere personer efter efternavn
//=========================================================
int compare_efternavn(const void *a, const void *b)
{
    struct person *p1 = (struct person *)a;
    struct person *p2 = (struct person *)b;

    return strcmp(p1->efternavn, p2->efternavn);
}

//=========================================================
// MAIN: læs personer, sorter, skriv output
//=========================================================
int main(void)
{
    struct person personer[MAX_PERSONS];  // array til personer
    int n = 0;                             // tæller antal personer læst

    FILE *ifp = fopen("input.txt", "r");   // åbn inputfil
    if (!ifp) {
        printf("Kan ikke åbne inputfil\n");
        return 1;
    }

    char line[256]; // buffer til linje
    while (fgets(line, sizeof(line), ifp) != NULL && n < MAX_PERSONS)
    {
        // Fjerne eventuel newline
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n')
            line[len-1] = '\0';

        // Brug scansets til at læse felter
        // %[^,] læser indtil et komma
        // første felt: fornavn efternavn
        char fullname[MAX_NAME_LGT*2];
        if (sscanf(line, " %[^,],", fullname) != 1)
            continue; // skip hvis fejl

        // Split fullname til fornavn og efternavn
        char *space = strchr(fullname, ' ');
        if (space == NULL)
            continue; // skip hvis ingen mellemrum
        *space = '\0'; // skill fornavn og efternavn
        strcpy(personer[n].fornavn, fullname);
        strcpy(personer[n].efternavn, space+1);

        // læs vejnavn og vejnummer
        char street[MAX_NAME_LGT];
        int nummer;
        if (sscanf(line + strlen(fullname) + 1, " %[^0-9]%d,", street, &nummer) != 2)
            continue;
        // fjern trailing space fra vejnavn hvis nødvendigt
        size_t street_len = strlen(street);
        if (street_len > 0 && street[street_len-1] == ' ')
            street[street_len-1] = '\0';
        strcpy(personer[n].vejnavn, street);
        personer[n].vejnummer = nummer;

        // læs postnummer og bynavn (sidste felt før punktum)
        int postnr;
        char by[MAX_NAME_LGT];
        if (sscanf(line + strlen(fullname) + 1 + strlen(street) + 10, " %d %[^.].", &postnr, by) != 2)
            continue;
        personer[n].postnummer = postnr;
        strcpy(personer[n].bynavn, by);

        n++; // næste person
    }

    fclose(ifp);

    // Sorter personer efter efternavn
    qsort(personer, n, sizeof(struct person), compare_efternavn);

    // Skriv outputfil i format: By: Efternavn
    FILE *ofp = fopen("output.txt", "w");
    if (!ofp) {
        printf("Kan ikke åbne outputfil\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        fprintf(ofp, "%s: %s\n", personer[i].bynavn, personer[i].efternavn);
    }

    fclose(ofp);

    printf("Færdig, %d personer skrevet til output.txt\n", n);
    return 0;
}
