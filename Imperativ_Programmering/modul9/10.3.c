/*
=========================================================
FORMÅL:
Programmet oversætter udvalgte engelske navneord
fra ental (singular) til flertal (plural) efter
følgende regler:

1) Ender ordet på 'y'  -> fjern 'y' og tilføj "ies"
2) Ender ordet på 's', "ch" eller "sh" -> tilføj "es"
3) Ellers -> tilføj "s"

Programmet udskriver hvert ord i både ental og flertal.

FAGORD:
- Tekststreng (C-string): char-array afsluttet med '\0'
- Input-parameter: const char* (ændres ikke)
- Output-parameter: char* (funktionen skriver resultat)
- Top-down programmering: opdeling i mindre delproblemer
=========================================================
*/

#include <stdio.h>
#include <string.h>   // strlen, strcpy, strcat

/*
=========================================================
FUNKTION: make_plural

Input:
- singular : entalsform (læses, må ikke ændres)

Output:
- plural   : flertalsform (skrives af funktionen)

Bemærk:
- const char* bruges til input for at markere,
  at funktionen ikke ændrer input-strengen
=========================================================
*/
void make_plural(const char *singular, char *plural)
{
    int len = strlen(singular);   // Længden af input-ordet

    /*
    -----------------------------------------------------
    Regel 1: Ender ordet på 'y'
    Eksempel: fly -> flies
    -----------------------------------------------------
    */
    if (len >= 1 && singular[len - 1] == 'y')
    {
        // Kopiér hele ordet undtagen det sidste tegn ('y')
        strncpy(plural, singular, len - 1);

        // Tilføj null-terminator manuelt
        plural[len - 1] = '\0';

        // Tilføj "ies"
        strcat(plural, "ies");
    }

    /*
    -----------------------------------------------------
    Regel 2: Ender ordet på "s", "ch" eller "sh"
    Eksempel: boss -> bosses
               church -> churches
               dish -> dishes
    -----------------------------------------------------
    */
    else if (
        (len >= 1 && singular[len - 1] == 's') ||
        (len >= 2 && singular[len - 2] == 'c' && singular[len - 1] == 'h') ||
        (len >= 2 && singular[len - 2] == 's' && singular[len - 1] == 'h')
    )
    {
        // Kopiér hele entalsordet
        strcpy(plural, singular);

        // Tilføj "es"
        strcat(plural, "es");
    }

    /*
    -----------------------------------------------------
    Regel 3: Alle andre tilfælde
    Eksempel: chair -> chairs
               dog   -> dogs
    -----------------------------------------------------
    */
    else
    {
        // Kopiér hele entalsordet
        strcpy(plural, singular);

        // Tilføj "s"
        strcat(plural, "s");
    }
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
    Array med entalsord (input)
    -----------------------------------------------------
    */
    const char *words[] = {
        "chair", "dairy", "boss", "circus",
        "fly", "dog", "church", "clue", "dish"
    };

    int count = sizeof(words) / sizeof(words[0]);

    /*
    -----------------------------------------------------
    Buffer til flertalsform (output)
    50 tegn er rigeligt til disse ord
    -----------------------------------------------------
    */
    char plural[50];

    /*
    -----------------------------------------------------
    Gennemløb alle ord og udskriv ental + flertal
    -----------------------------------------------------
    */
    for (int i = 0; i < count; i++)
    {
        make_plural(words[i], plural);

        printf("Singular: %-10s  Plural: %s\n",
               words[i], plural);
    }

    return 0;
}

/*
EKSEMPEL OUTPUT:

Singular: chair       Plural: chairs
Singular: dairy       Plural: dairies
Singular: boss        Plural: bosses
Singular: circus      Plural: circuses
Singular: fly         Plural: flies
Singular: dog         Plural: dogs
Singular: church      Plural: churches
Singular: clue        Plural: clues
Singular: dish        Plural: dishes
*/
