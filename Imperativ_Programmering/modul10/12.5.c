/*
=========================================================
FORMÅL:
Dette program implementerer en datatype "fraction"
(brøk) og funktioner til at arbejde med positive brøker.

Der implementeres funktioner til:
- Konstruktion af en brøk
- Forkortelse af en brøk
- Udskrivning af en brøk
- Multiplikation med heltal
- Multiplikation af to brøker
- Addition af to brøker

Alle resultater forkortes mest muligt.
=========================================================
*/

#include <stdio.h>

/*
=========================================================
STRUKTUR: fraction

numerator   : tæller (positivt heltal)
denominator : nævner (positivt heltal)

Bemærk:
- unsigned int sikrer kun ikke-negative værdier
=========================================================
*/
typedef struct {
    unsigned int numerator;     // tæller
    unsigned int denominator;   // nævner
} fraction;

/*
=========================================================
FUNKTION: gcd
Finder største fælles divisor (Greatest Common Divisor)
ved hjælp af Euclids algoritme
=========================================================
*/
unsigned int gcd(unsigned int large, unsigned int small)
{
    unsigned int remainder;     // rest ved division

    // Gentag så længe small ikke er nul
    while (small > 0)
    {
        remainder = large % small; // beregn resten
        large = small;             // flyt small til large
        small = remainder;         // resten bliver ny small
    }

    // Når small er 0, er large GCD
    return large;
}

/*
=========================================================
FUNKTION: make_fraction
Konstruerer og returnerer en brøk ud fra tæller og nævner
=========================================================
*/
fraction make_fraction(unsigned int num, unsigned int den)
{
    fraction f;                 // opret lokal brøk

    f.numerator = num;          // sæt tæller
    f.denominator = den;        // sæt nævner

    return f;                   // returnér brøken
}

/*
=========================================================
FUNKTION: reduce_fraction
Forkorter en brøk mest muligt
=========================================================
*/
fraction reduce_fraction(fraction f)
{
    // Find største fælles divisor
    unsigned int divisor = gcd(f.numerator, f.denominator);

    // Divider både tæller og nævner med GCD
    f.numerator /= divisor;
    f.denominator /= divisor;

    // Returnér den forkortede brøk
    return f;
}

/*
=========================================================
FUNKTION: print_fraction
Udskriver en brøk på formen "a/b"
=========================================================
*/
void print_fraction(fraction f)
{
    printf("%u/%u", f.numerator, f.denominator);
}

/*
=========================================================
FUNKTION: multiply_fraction_int
Ganger en brøk med et heltal
=========================================================
*/
fraction multiply_fraction_int(fraction f, unsigned int n)
{
    // Gange tælleren med heltallet
    f.numerator *= n;

    // Forkort resultatet
    return reduce_fraction(f);
}

/*
=========================================================
FUNKTION: multiply_fractions
Ganger to brøker sammen
=========================================================
*/
fraction multiply_fractions(fraction a, fraction b)
{
    fraction result;   // resultat-brøk

    // Gange tællere
    result.numerator = a.numerator * b.numerator;

    // Gange nævnere
    result.denominator = a.denominator * b.denominator;

    // Forkort resultatet
    return reduce_fraction(result);
}

/*
=========================================================
FUNKTION: add_fractions
Adderer to brøker
=========================================================
*/
fraction add_fractions(fraction a, fraction b)
{
    fraction result;   // resultat-brøk

    /*
    -----------------------------------------------------
    Find fælles nævner ved krydsmultiplikation
    -----------------------------------------------------
    */
    result.numerator =
        a.numerator * b.denominator +
        b.numerator * a.denominator;

    result.denominator =
        a.denominator * b.denominator;

    // Forkort resultatet
    return reduce_fraction(result);
}

/*
=========================================================
MAIN
Demonstrerer brugen af brøk-funktionerne
=========================================================
*/
int main(void)
{
    // Konstruer to brøker
    fraction f1 = make_fraction(2, 3);   // 2/3
    fraction f2 = make_fraction(4, 5);   // 4/5

    // Udskriv brøkerne
    printf("f1 = ");
    print_fraction(f1);
    printf("\n");

    printf("f2 = ");
    print_fraction(f2);
    printf("\n\n");

    // Multiplikation med heltal
    fraction f3 = multiply_fraction_int(f1, 6);
    printf("f1 * 6 = ");
    print_fraction(f3);
    printf("\n");

    // Multiplikation af to brøker
    fraction f4 = multiply_fractions(f1, f2);
    printf("f1 * f2 = ");
    print_fraction(f4);
    printf("\n");

    // Addition af to brøker
    fraction f5 = add_fractions(f1, f2);
    printf("f1 + f2 = ");
    print_fraction(f5);
    printf("\n");

    return 0;
}
