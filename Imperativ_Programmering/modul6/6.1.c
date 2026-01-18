/*
=========================================================
FORMÅL:
Programmet omregner en temperatur fra Celsius til Fahrenheit.

FAGORD (forklaret kort):
- Funktion: En blok kode der kan kaldes igen og igen
- Input-parameter: Data der sendes IND i en funktion
- Output-parameter: Data der sendes UD via en pointer
- Pointer: En variabel der gemmer adressen på en anden variabel
- Call by value: En kopi af en værdi sendes til funktionen
- & (adresse-operator): Giver adressen på en variabel
- * (dereference-operator): Giver adgang til værdien på adressen
=========================================================
*/

#include <stdio.h>   // Giver adgang til printf og scanf

/*
FUNKTION:
Omregner Celsius til Fahrenheit

PARAMETRE:
- celsius (float): input-parameter (call by value)
- fahrenheit (float*): output-parameter (pointer)

RETURN:
- void (returnerer intet, output sker via pointer)
*/
void celsiusToFahrenheit(float celsius, float *fahrenheit)
{
    // Beregner Fahrenheit ud fra formlen
    // *fahrenheit betyder: "gå hen til adressen og gem værdien der"
    *fahrenheit = (celsius * 9.0 / 5.0) + 32.0;
}

int main(void)
{
    // Variabel til at gemme Celsius-temperaturen
    float c;

    // Variabel til at gemme Fahrenheit-resultatet
    float f;

    // Beder brugeren indtaste en Celsius-temperatur
    printf("Indtast temperatur i Celsius: ");

    // Scanner input og gemmer det i variablen c
    scanf("%f", &c);

    // Kalder funktionen:
    // c sendes som værdi
    // &f sender ADRESSEN på f (så funktionen kan ændre den)
    celsiusToFahrenheit(c, &f);

    // Udskriver resultatet
    printf("%.2f grader Celsius er %.2f grader Fahrenheit\n", c, f);

    // Programmet sluttet korrekt
    return 0;
// EKSEMPEL PÅ INPUT:
// 3665 sekunder

// FORVENTET OUTPUT:
// 1 timer, 1 minutter og 5 sekunder
}
