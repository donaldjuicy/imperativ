/*
=========================================================
FORMÅL:
Programmet demonstrerer sortering af bøger i et array
ved brug af qsort fra stdlib.h.

Der implementeres to sorteringsfunktioner:

1) sort_books_by_title
   - Sorterer bøger alfabetisk efter titel

2) sort_books_by_kind_and_year
   - Først: skønlitteratur før lærebøger
   - Dernæst: stigende udgivelsesår inden for hver gruppe

Sorteringen foregår IN-PLACE (ingen kopier).
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>   // qsort
#include <string.h>   // strcmp

/*
=========================================================
STRUKTUR: book

title       : bogens titel
year        : udgivelsesår
textbook    : 1 hvis lærebog, 0 hvis skønlitteratur
=========================================================
*/
typedef struct {
    char title[100];
    int year;
    int textbook;
} book;

/*
=========================================================
HJÆLPEFUNKTION:
Udskriver én bog
=========================================================
*/
void print_book(const book *b)
{
    printf("Title: %s\n", b->title);
    printf("Year: %d\n", b->year);
    printf("University text book: %s\n\n",
           b->textbook ? "yes" : "no");
}

/*
=========================================================
COMPARE-FUNKTION TIL QSORT
Sorterer alfabetisk efter titel
=========================================================
*/
int compare_by_title(const void *a, const void *b)
{
    // Cast fra void pointer til book pointer
    const book *book1 = (const book *)a;
    const book *book2 = (const book *)b;

    // strcmp returnerer:
    // < 0 hvis book1 < book2
    // = 0 hvis ens
    // > 0 hvis book1 > book2
    return strcmp(book1->title, book2->title);
}

/*
=========================================================
SORTERINGSFUNKTION:
Sorterer bøger efter titel (alfabetisk)
=========================================================
*/
void sort_books_by_title(book shelf[], int last)
{
    // last + 1 er antallet af bøger i arrayet
    qsort(
        shelf,                 // arrayet
        last + 1,              // antal elementer
        sizeof(book),          // størrelse af ét element
        compare_by_title       // sammenligningsfunktion
    );
}

/*
=========================================================
COMPARE-FUNKTION:
1) Skønlitteratur før lærebøger
2) Inden for grupper: stigende år
=========================================================
*/
int compare_by_kind_and_year(const void *a, const void *b)
{
    const book *book1 = (const book *)a;
    const book *book2 = (const book *)b;

    /*
    -----------------------------------------------------
    Første sorteringskriterium:
    textbook == 0 (skønlitteratur) skal før
    textbook == 1 (lærebøger)
    -----------------------------------------------------
    */
    if (book1->textbook != book2->textbook)
    {
        return book1->textbook - book2->textbook;
    }

    /*
    -----------------------------------------------------
    Andet sorteringskriterium:
    Udgivelsesår (stigende)
    -----------------------------------------------------
    */
    return book1->year - book2->year;
}

/*
=========================================================
SORTERINGSFUNKTION:
Sorterer efter type (skøn/lærebog) og år
=========================================================
*/
void sort_books_by_kind_and_year(book shelf[], int last)
{
    qsort(
        shelf,                         // array
        last + 1,                      // antal bøger
        sizeof(book),                  // størrelse af book
        compare_by_kind_and_year       // compare-funktion
    );
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
    Array med fem bøger (shelf)
    -----------------------------------------------------
    */
    book shelf[] = {
        {"The C Programming Language", 1988, 1},
        {"C by Dissection", 2001, 1},
        {"Problem Solving and Program Design in C", 2010, 1},
        {"Pelle Erobreren", 1910, 0},
        {"Ditte Menneskebarn", 1917, 0}
    };

    int last = 4;   // indeks for sidste bog

    /*
    -----------------------------------------------------
    Sortér efter titel
    -----------------------------------------------------
    */
    sort_books_by_title(shelf, last);

    printf("=== Sorted by title ===\n\n");
    for (int i = 0; i <= last; i++)
    {
        print_book(&shelf[i]);
    }

    /*
    -----------------------------------------------------
    Sortér efter type og år
    -----------------------------------------------------
    */
    sort_books_by_kind_and_year(shelf, last);

    printf("=== Sorted by kind and year ===\n\n");
    for (int i = 0; i <= last; i++)
    {
        print_book(&shelf[i]);
    }

    return 0;
}
