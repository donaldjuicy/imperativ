/*
=========================================================
FORMÅL:
Programmet konverterer dollar til euro, kroner, rubler og yen
ved hjælp af en funktion med én input-parameter og fire output-parametre.

FAGORD:
- Funktion: Genbrugelig blok kode
- Input-parameter: Data sendt IND i funktionen
- Output-parameter: Data sendt UD via pointere
- Pointer: Variabel der gemmer adressen på en anden variabel
- Call by value: Kopi af værdi sendes til funktionen
- Call by reference: Funktion kan ændre variabler i main
=========================================================
*/

#include <stdio.h>

/*=========================================================
FUNKTION: convert_currency
Konverterer dollar til euro, kroner, rubler og yen

INPUT:
- dollars: beløb i dollars (double)

OUTPUT:
- *euro: beløb i euro
- *kroner: beløb i danske kroner
- *rubler: beløb i russiske rubler
- *yen: beløb i japanske yen
=========================================================*/
void convert_currency(double dollars, double *euro, double *kroner, double *rubler, double *yen)
{
    *euro = dollars * 0.89;      // 1 USD = 0.89 EUR
    *kroner = dollars * 6.66;    // 1 USD = 6.66 DKK
    *rubler = dollars * 66.43;   // 1 USD = 66.43 RUB
    *yen = dollars * 119.9;      // 1 USD = 119.9 JPY
}

int main(void)
{
    // Variabler til de fire valutaer
    double euro, kroner, rubler, yen;

    // Udskriv tabelhoved
    printf("USD\tEuro\tKroner\tRubler\tYen\n");
    printf("-------------------------------------------\n");

    // Loop fra 1 til 100 dollars
    for(int usd = 1; usd <= 100; usd++)
    {
        // Kalder funktionen med pointere som output
        convert_currency((double)usd, &euro, &kroner, &rubler, &yen);

        // Udskriver rækken i tabellen
        printf("%3d\t%.2f\t%.2f\t%.2f\t%.2f\n", usd, euro, kroner, rubler, yen);
    }

    /*
    EKSEMPEL PÅ OUTPUT (første 5 rækker):

    USD     Euro    Kroner  Rubler  Yen
    -------------------------------------------
      1    0.89     6.66   66.43  119.90
      2    1.78    13.32  132.86  239.80
      3    2.67    19.98  199.29  359.70
      4    3.56    26.64  265.72  479.60
      5    4.45    33.30  332.15  599.50
    ...
    */

    return 0;
}
