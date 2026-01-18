/*
=========================================================
FORMÅL:
Programmet håndterer personer (struct person) og kan:

1) Udskrive en person på fil (tekstbaseret)
2) Læse en person fra fil (tekstbaseret)

Struktur:
- name : char array
- age  : int
- sex  : char ('m' eller 'f')

Vi viser også kommentarer om hvordan man kunne bruge
binær tilgang med fwrite/fread.
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_SIZE 50

//=========================================================
// Struct: person
//=========================================================
typedef struct person {
    char name[MAX_NAME_SIZE];  // person's name
    int age;                   // person's age
    char sex;                  // 'm' or 'f'
} person;

//=========================================================
// Funktion: print_person
// Udskriver en person på fil, tekstbaseret, linje for linje
// Parametre:
// - p   : pointer til person
// - ofp : pointer til åben fil for skrivning
//=========================================================
void print_person(person *p, FILE *ofp)
{
    if (p == NULL || ofp == NULL)
        return;

    // Udskriv i format: name age sex
    fprintf(ofp, "%s %d %c\n", p->name, p->age, p->sex);
}

//=========================================================
// Funktion: read_person
// Læser en person fra fil, tekstbaseret
// Parametre:
// - ifp : pointer til åben fil for læsning
// Returnerer: pointer til dynamically allocated person
//=========================================================
person *read_person(FILE *ifp)
{
    if (ifp == NULL)
        return NULL;

    // Alloker hukommelse til person
    person *p = malloc(sizeof(person));
    if (p == NULL)
        return NULL; // fejl hvis malloc fejler

    // Læs navn, alder og sex
    // "%49s" sikrer vi ikke overskrider buffer
    if (fscanf(ifp, "%49s %d %c", p->name, &p->age, &p->sex) != 3)
    {
        free(p);      // frigør hukommelse hvis læsning fejler
        return NULL;  // EOF eller fejl
    }

    return p;
}

//=========================================================
// MAIN: eksempel på brug
//=========================================================
int main(void)
{
    // Opret to personer
    person p1 = {"Alice", 25, 'f'};
    person p2 = {"Bob", 30, 'm'};

    // Åbn fil til skrivning
    FILE *ofp = fopen("persons.txt", "w");
    if (!ofp)
    {
        printf("Kan ikke åbne fil for skrivning\n");
        return 1;
    }

    // Udskriv personer på fil
    print_person(&p1, ofp);
    print_person(&p2, ofp);

    fclose(ofp);

    // Åbn fil til læsning
    FILE *ifp = fopen("persons.txt", "r");
    if (!ifp)
    {
        printf("Kan ikke åbne fil for læsning\n");
        return 1;
    }

    // Læs personer igen
    person *r1 = read_person(ifp);
    person *r2 = read_person(ifp);

    fclose(ifp);

    // Udskriv på skærm for verifikation
    if (r1)
        printf("Read person 1: %s %d %c\n", r1->name, r1->age, r1->sex);
    if (r2)
        printf("Read person 2: %s %d %c\n", r2->name, r2->age, r2->sex);

    // Frigør hukommelse
    free(r1);
    free(r2);

    return 0;
}
