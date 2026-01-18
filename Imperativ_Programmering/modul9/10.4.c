/*
=========================================================
FORMÅL:
Programmet finder den længste fælles endelse (suffix)
af to ord (tekststrenge).

Eksempel:
"datalogi" og "biologi"  ->  "logi"
"program" og "diagram"  ->  "gram"

FAGORD:
- Tekststreng (C-string): char-array afsluttet med '\0'
- Input-parameter: parameter som funktionen ikke ændrer
- Output-parameter: parameter som funktionen skriver resultat i
- const: markerer at data ikke må ændres
- Suffix: fælles endelse af to ord
=========================================================
*/

#include <stdio.h>
#include <string.h>   // strlen, strcpy

/*
=========================================================
FUNKTION: longest_common_suffix

Input-parametre:
- word1: første ord (læses, ændres ikke)
- word2: andet ord (læses, ændres ikke)

Output-parameter:
- suffix: tekststreng hvor den fælles endelse gemmes

Bemærk:
- word1 og word2 er const char*, dvs. input
- suffix er char*, dvs. output
=========================================================
*/
void longest_common_suffix(const char *word1,
                           const char *word2,
                           char *suffix)
{
    // Find længden af de to input-strenge
    int len1 = strlen(word1);
    int len2 = strlen(word2);

    // Start fra slutningen af begge ord
    int i = len1 - 1;  // peger på sidste tegn i word1
    int j = len2 - 1;  // peger på sidste tegn i word2

    // Tæller hvor mange tegn der matcher fra slutningen
    int count = 0;

    // Sammenlign tegn bagfra så længe:
    // - vi ikke løber ud af strengene
    // - tegnene er ens
    while (i >= 0 && j >= 0 && word1[i] == word2[j])
    {
        count++;  // ét fælles suffix-tegn fundet
        i--;      // gå et tegn mod venstre i word1
        j--;      // gå et tegn mod venstre i word2
    }

    // Hvis ingen fælles endelse findes
    if (count == 0)
    {
        suffix[0] = '\0';  // tom streng
        return;
    }

    // Kopiér den fælles endelse til output-strengen
    // Startpositionen er len1 - count
    for (int k = 0; k < count; k++)
    {
        suffix[k] = word1[len1 - count + k];
    }

    // Husk null-terminator
    suffix[count] = '\0';
}

/*
=========================================================
MAIN: Tester longest_common_suffix
=========================================================
*/
int main(void)
{
    // Testord
    char word1[] = "datalogi";
    char word2[] = "biologi";

    // Output-buffer:
    // Maks længde kan aldrig være længere end det korteste ord
    char suffix[100];

    // Kald funktionen
    longest_common_suffix(word1, word2, suffix);

    // Udskriv resultatet
    printf("Laengste faelles endelse af \"%s\" og \"%s\" er: \"%s\"\n",
           word1, word2, suffix);

    // Ekstra test
    char w3[] = "program";
    char w4[] = "diagram";

    longest_common_suffix(w3, w4, suffix);
    printf("Laengste faelles endelse af \"%s\" og \"%s\" er: \"%s\"\n",
           w3, w4, suffix);

    return 0;
}

/*
EKSEMPEL OUTPUT:

Laengste faelles endelse af "datalogi" og "biologi" er: "logi"
Laengste faelles endelse af "program" og "diagram" er: "gram"
*/
