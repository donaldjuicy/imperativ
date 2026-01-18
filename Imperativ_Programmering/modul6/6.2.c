/*
=========================================================
FORMÅL:
Programmet omregner et antal sekunder til:
- timer
- minutter
- sekunder

FAGORD (forklaret kort):
- Funktion: En genbrugelig blok kode
- Input-parameter: Data der sendes IND i funktionen
- Output-parameter: Data der sendes UD via pointere
- Pointer: En variabel der gemmer adressen på en anden variabel
- Call by value: En kopi af en værdi sendes til funktionen
- Call by reference: Funktionen kan ændre variabler i main
- & (adresse-operator): Giver adressen på en variabel
- * (dereference-operator): Giver adgang til værdien på adressen
=========================================================
*/

#include <stdio.h>   // Giver adgang til printf og scanf

/*
FUNKTION:
Omregner sekunder til timer, minutter og sekunder

PARAMETRE:
- total_seconds (int): input-parameter (call by value)
- hours (int*): output-parameter (pointer)
- minutes (int*): output-parameter (pointer)
- seconds (int*): output-parameter (pointer)

RETURN:
- void (alle resultater returneres via pointere)
*/
void hours_minutes_seconds(int total_seconds,
                           int *hours,
                           int *minutes,
                           int *seconds)
{
    // Beregner antal timer
    // 1 time = 3600 sekunder
    *hours = total_seconds / 3600;

    // Finder resterende sekunder efter timer er trukket fra
    int rest = total_seconds % 3600;

    // Beregner antal minutter
    // 1 minut = 60 sekunder
    *minutes = rest / 60;

    // Finder resterende sekunder
    *seconds = rest % 60;
}

int main(void)
{
    // Variabel til det samlede antal sekunder
    int total;

    // Variabler til output
    int h, m, s;

    // Beder brugeren om at indtaste antal sekunder
    printf("Indtast antal sekunder: ");

    // Læser brugerens input
    scanf("%d", &total);

    // Kalder funktionen
    // total sendes som værdi
    // &h, &m, &s sender adresserne på output-variablerne
    hours_minutes_seconds(total, &h, &m, &s);

    // Udskriver resultatet
    printf("%d sekunder svarer til %d timer, %d minutter og %d sekunder\n",
           total, h, m, s);

    // Programmet afsluttes korrekt
    return 0;
}
