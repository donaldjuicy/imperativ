/*
=========================================================
FORMÅL:
Programmet demonstrerer funktionspointere i C og gentagen
anvendelse af funktioner på en double-værdi.

PROGRAMMER:
1. multi_apply: Kalder en funktion f på en startværdi s, n gange
2. multi_apply_2: Kalder skiftevis funktionerne f og g på s, n gange

FAGORD:
- Funktionspointer: Pointer til en funktion (f, g)
- Parameter: Input til en funktion
- Call by value: Kopi af værdien sendes
- Return: Funktionen giver en værdi tilbage
- Loop: Gentager kode n gange
- Pointer dereference (*): Får adgang til værdien på adressen
=========================================================
*/

#include <stdio.h>

/*=========================================================
FUNKTION: multi_apply
Kalder funktionen f på startværdi s, n gange.
INPUT:
- f: pointer til funktion double->double
- n: antal gentagelser
- s: startværdi
OUTPUT:
- Returnerer resultatet af f(f(...f(s))) n gange
=========================================================*/
double multi_apply(double (*f)(double), int n, double s)
{
    double result = s;       // Starter med s
    for(int i = 0; i < n; i++)
    {
        result = f(result);  // Anvender f på resultatet
    }
    return result;           // Returnerer slutresultatet
}

/*=========================================================
Eksempel-funktion: halvér tallet
INPUT: x
OUTPUT: x/2
=========================================================*/
double half(double x)
{
    return x / 2.0;
}

/*=========================================================
FUNKTION: multi_apply_2
Kalder skiftevis f og g på startværdi s, n gange.
INPUT:
- f, g: pointere til funktioner double->double
- n: antal gentagelser
- s: startværdi
OUTPUT:
- Returnerer resultatet af f(g(f(g(...(f(g(s))))))) n gange
=========================================================*/
double multi_apply_2(double (*f)(double), double (*g)(double), int n, double s)
{
    double result = s;           // Starter med s
    for(int i = 0; i < n; i++)
    {
        result = g(result);      // Først g
        result = f(result);      // Derefter f
    }
    return result;               // Returnerer slutresultatet
}

/*=========================================================
Eksempel-funktion: læg 3 til tallet
INPUT: x
OUTPUT: x + 3
=========================================================*/
double add3(double x)
{
    return x + 3.0;
}

/*=========================================================
MAIN: Tester multi_apply og multi_apply_2
=========================================================*/
int main(void)
{
    // Test multi_apply med half
    double x1 = 16.0;
    double result1 = multi_apply(half, 4, x1);
    printf("multi_apply(half, 4, 16.0) = %.2f\n", result1);

    /*
    FORVENTET OUTPUT:
    16 -> 8 -> 4 -> 2 -> 1
    multi_apply(half, 4, 16.0) = 1.00
    */

    // Test multi_apply_2 med half og add3
    double x2 = 4.0;
    double result2 = multi_apply_2(half, add3, 2, x2);
    printf("multi_apply_2(half, add3, 2, 4.0) = %.2f\n", result2);

    /*
    FORVENTET OUTPUT:
    Beregning: 4 -> g(4)=7 -> f(7)=3.5 -> g(3.5)=6.5 -> f(6.5)=3.25
    multi_apply_2(half, add3, 2, 4.0) = 3.25
    */

    // Ekstra eksempel: multi_apply_2 med n=4, start=16
    double x3 = 16.0;
    double result3 = multi_apply_2(half, add3, 4, x3);
    printf("multi_apply_2(half, add3, 4, 16.0) = %.3f\n", result3);

    /*
    FORVENTET OUTPUT:
    16 -> g(16)=19 -> f(19)=9.5 -> g(9.5)=12.5 -> f(12.5)=6.25
        -> g(6.25)=9.25 -> f(9.25)=4.625 -> g(4.625)=7.625 -> f(7.625)=3.813
    multi_apply_2(half, add3, 4, 16.0) = 3.813
    */

    return 0;
}
