#include <stdio.h>

/*
=========================================================
Funktion: quotient
Beregn dividend / divisor ved rekursion (gentagen subtraktion)

Parametre:
- dividend : tallet der skal divideres
- divisor  : tallet der dividerer (skal være > 0)

Returnerer:
- Kvotienten (heltal)
=========================================================
*/
int quotient(int dividend, int divisor)
{
    if (dividend < divisor)    // basistilfælde: dividend er mindre end divisor
        return 0;              // kan ikke trække mere → kvotient = 0
    return 1 + quotient(dividend - divisor, divisor); // træk divisor fra og rekursivt kald
}

/*
=========================================================
Funktion: modulus
Beregn dividend % divisor ved rekursion (gentagen subtraktion)

Parametre:
- dividend : tallet der skal divideres
- divisor  : tallet der dividerer (skal være > 0)

Returnerer:
- Resten efter division
=========================================================
*/
int modulus(int dividend, int divisor)
{
    if (dividend < divisor)    // basistilfælde: dividend er mindre end divisor
        return dividend;       // rest = dividend
    return modulus(dividend - divisor, divisor); // træk divisor fra og kald rekursivt
}

//=========================================================
// MAIN: eksempel på brug
//=========================================================
int main(void)
{
    int a = 17, b = 5;

    printf("Kvotient af %d / %d = %d\n", a, b, quotient(a, b));
    printf("Modulus af %d %% %d = %d\n", a, b, modulus(a, b));

    // Flere testeksempler
    printf("Kvotient af %d / %d = %d\n", 20, 4, quotient(20, 4));
    printf("Modulus af %d %% %d = %d\n", 20, 4, modulus(20, 4));

    printf("Kvotient af %d / %d = %d\n", 7, 3, quotient(7, 3));
    printf("Modulus af %d %% %d = %d\n", 7, 3, modulus(7, 3));

    return 0;
}
