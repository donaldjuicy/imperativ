/*
=========================================================
FORMÅL:
Dette program arbejder med datoer repræsenteret ved
en struct date.

Funktionen tomorrow tager en dato som input og
returnerer datoen for den efterfølgende dag.

Programmet kan bruges som del af et større program,
fx til at generere en kalender for et helt år.
=========================================================
*/

#include <stdio.h>

/*
=========================================================
STRUKTUR: date

day   : dag i måneden (1–31)
month : måned (1–12)
year  : årstal
=========================================================
*/
typedef struct {
    int day;     // dagnummer
    int month;   // månednummer
    int year;    // år
} date;

/*
=========================================================
HJÆLPEFUNKTION:
Afgør om et givent år er et skudår

Returnerer:
1 -> skudår
0 -> ikke skudår
=========================================================
*/
int is_leap_year(int year)
{
    // Et år er skudår hvis det er deleligt med 4
    // men ikke deleligt med 100,
    // medmindre det også er deleligt med 400
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        return 1;
    else
        return 0;
}

/*
=========================================================
FUNKTION: days_in_month

Returnerer antal dage i en given måned
for et bestemt år
=========================================================
*/
int days_in_month(int month, int year)
{
    // Februar kræver særbehandling pga. skudår
    if (month == 2)
    {
        if (is_leap_year(year))
            return 29;
        else
            return 28;
    }

    // Måneder med 31 dage
    if (month == 1 || month == 3 || month == 5 ||
        month == 7 || month == 8 || month == 10 || month == 12)
        return 31;

    // Alle øvrige måneder har 30 dage
    return 30;
}

/*
=========================================================
FUNKTION: tomorrow

Input:
  d - en dato (struct date)

Output:
  Returnerer datoen for dagen efter d

BEMÆRK:
- d er call-by-value (kopi)
- funktionen ændrer ikke den oprindelige dato
=========================================================
*/
date tomorrow(date d)
{
    // Opret en ny dato og start med at kopiere input-datoen
    date result = d;

    // Øg dagen med 1
    result.day++;

    // Find antal dage i den aktuelle måned
    int max_days = days_in_month(result.month, result.year);

    // Hvis dagen overstiger antal dage i måneden
    if (result.day > max_days)
    {
        // Start ny måned
        result.day = 1;

        // Gå til næste måned
        result.month++;

        // Hvis måneden overstiger december
        if (result.month > 12)
        {
            // Start nyt år
            result.month = 1;
            result.year++;
        }
    }

    // Returnér den beregnede dato
    return result;
}

/*
=========================================================
MAIN
Tester tomorrow-funktionen
=========================================================
*/
int main(void)
{
    // Opret en startdato
    date d = {31, 12, 2024};

    // Beregn næste dag
    date next = tomorrow(d);

    // Udskriv resultatet
    printf("Original date: %02d-%02d-%d\n", d.day, d.month, d.year);
    printf("Tomorrow:      %02d-%02d-%d\n", next.day, next.month, next.year);

    return 0;
}
