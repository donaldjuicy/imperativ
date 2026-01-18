#include <stdio.h>

/*
=========================================================
FORMÅL:
Programmet indeholder to rekursive udgaver af Euclids algoritme:

1) gcd_mod(a, b)      - baseret på gentagen rest (%)
2) gcd_subtract(a, b) - baseret på gentagen subtraktion (-)

Begge funktioner returnerer den største fælles divisor (GCD)
af to positive heltal.
=========================================================
*/

//=========================================================
// Rekursiv version med modulus (%)
// a % b != 0 → kald gcd_mod(b, a % b)
// a % b == 0 → b er GCD
//=========================================================
unsigned int gcd_mod(unsigned int a, unsigned int b)
{
    if (b == 0)            // basistilfælde: resten er 0
        return a;          // GCD fundet
    return gcd_mod(b, a % b);  // rekursivt kald
}

//=========================================================
// Rekursiv version med subtraktion (-)
// Trækker den mindste fra den største indtil de bliver ens
//=========================================================
unsigned int gcd_subtract(unsigned int a, unsigned int b)
{
    if (a == b)             // basistilfælde: begge tal er ens
        return a;           // GCD fundet

    if (a > b)
        return gcd_subtract(a - b, b);  // træk b fra a
    else
        return gcd_subtract(a, b - a);  // træk a fra b
}

//=========================================================
// MAIN: eksempel på brug
//=========================================================
int main(void)
{
    unsigned int x = 48, y = 18;

    // Brug modulus version
    unsigned int g1 = gcd_mod(x, y);
    printf("GCD_mod(%u, %u) = %u\n", x, y, g1);

    // Brug subtraktion version
    unsigned int g2 = gcd_subtract(x, y);
    printf("GCD_subtract(%u, %u) = %u\n", x, y, g2);

    // Ekstra test
    x = 270; y = 192;
    printf("GCD_mod(%u, %u) = %u\n", x, y, gcd_mod(x, y));
    printf("GCD_subtract(%u, %u) = %u\n", x, y, gcd_subtract(x, y));

    return 0;
}
