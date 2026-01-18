/*
=========================================================
FORMÅL:
Simpel version af Unix 'grep' kommando.
Programmet søger efter alle linjer i en tekstfil, 
der indeholder et bestemt søgeord.

Eksempel på anvendelse:
./search programmering my-file.txt
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1024 // maks længde på en linje

/*
=========================================================
MAIN
Programmet bruger kommando-linje parametre:
argv[1] : søgeord (string)
argv[2] : filnavn
=========================================================
*/
int main(int argc, char *argv[])
{
    // 1. Kontroller at der er nok parametre
    if (argc != 3)
    {
        printf("Usage: %s <searchword> <filename>\n", argv[0]);
        return 1; // fejl
    }

    // 2. Gem søgeord og filnavn i variabler
    char *searchword = argv[1];
    char *filename   = argv[2];

    // 3. Åbn filen til læsning
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open file: %s\n", filename);
        return 1;
    }

    // 4. Buffer til at læse linjer
    char line[MAXLINE];

    // 5. Læs filen linje for linje
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        /*
        -----------------------------------------------------
        fgets læser inklusiv newline (\n), men det
        påvirker ikke strstr-søgning
        -----------------------------------------------------
        */

        // 6. Tjek om søgeord findes i linjen
        if (strstr(line, searchword) != NULL)
        {
            // 7. Udskriv linjen hvis søgeordet findes
            printf("%s", line); // line indeholder allerede newline
        }
    }

    // 8. Luk filen
    fclose(fp);

    return 0; // succes
}
