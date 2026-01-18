/*
=========================================================
FORMÅL:
Funktionen getwords læser op til k ord fra en tekstfil
og kopierer dem ind i en tekststreng, separeret med
et enkelt mellemrum.  

Parametre:
- FILE *ifp : pointer til åben fil
- int k     : maksimalt antal ord, der ønskes læst
- char *words : tekststreng hvor ordene gemmes (skal være allokeret af caller)

Returnerer:
- faktisk antal læste ord
=========================================================
*/

#include <stdio.h>
#include <ctype.h>  // isspace
#include <string.h> // strlen

int getwords(FILE *ifp, int k, char *words)
{
    int count = 0;           // tæller antal læste ord
    int c;                   // midlertidig karakter
    char word[100];          // buffer til ét ord
    int pos = 0;             // position i output-strengen 'words'

    if (ifp == NULL || words == NULL)
        return 0; // sikkerhed: fil eller buffer er ugyldig

    // Start med at nulstille output-strengen
    words[0] = '\0';

    // Læs ord én ad gangen
    while (count < k)
    {
        int i = 0;          // position i midlertidig ord-buffer

        // Spring whitespace over
        while ((c = fgetc(ifp)) != EOF && isspace(c))
            ; // tom loop

        // Hvis vi rammer EOF før ord
        if (c == EOF)
            break;

        // Læs ét ord tegn for tegn indtil whitespace eller EOF
        do {
            if (i < sizeof(word) - 1) // undgå buffer overflow
                word[i++] = (char)c;
        } while ((c = fgetc(ifp)) != EOF && !isspace(c));

        word[i] = '\0'; // afslut ordet med null

        // Kopier ordet til output-strengen 'words'
        // Tilføj et mellemrum hvis det ikke er det første ord
        if (count > 0)
            words[pos++] = ' '; // separator mellem ord

        strcpy(&words[pos], word);          // kopier ord
        pos += strlen(word);                // opdater position i 'words'

        count++;                            // øg antal læste ord

        // Hvis EOF rammes, stopper while-loop
        if (c == EOF)
            break;
    }

    // Afslut output-strengen med null
    words[pos] = '\0';

    return count; // returner antal læste ord
}

/*
=========================================================
EKSEMPEL PÅ MAIN TIL TEST

int main(void)
{
    FILE *fp = fopen("test.txt", "r");
    if (fp == NULL)
    {
        printf("Kan ikke åbne fil\n");
        return 1;
    }

    char buffer[1000]; // caller allokerer plads
    int n = getwords(fp, 10, buffer);

    printf("Antal læste ord: %d\n", n);
    printf("Ord: %s\n", buffer);

    fclose(fp);
    return 0;
}
=========================================================
*/
