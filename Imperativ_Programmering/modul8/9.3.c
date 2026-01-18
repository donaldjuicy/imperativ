/*
=========================================================
FORMÅL:
Programmet demonstrerer reduktion/kombination af et array
af doubles med en binær funktion (double,double)->double.

Vi implementerer to versioner:
1. combine_right: kombinerer elementerne fra højre mod venstre
2. combine_left: kombinerer elementerne fra venstre mod højre

FAGORD:
- Binær funktion: Funktion der tager to input og returnerer en output
- Funktionspointer: Pointer til en funktion, bruges til fleksibel kombination
- Reducering/accumulering: Gentagen anvendelse af en funktion til at samle flere værdier
=========================================================
*/

#include <stdio.h>

//==========================================================
// EKSEMPEL PÅ BINÆR FUNKTIONER
//==========================================================
double add(double x, double y) { return x + y; }    // Addition
double multiply(double x, double y) { return x * y; } // Multiplikation

//==========================================================
// FUNKTION: combine_right
// Kombinerer et array a[0..n-1] fra højre mod venstre
// Input: a[] array, n = antal elementer, combiner = funktionspointer
// Output: resultat af kombinationen
//==========================================================
double combine_right(double a[], int n, double (*combiner)(double,double))
{
    // Start med sidste element som initialværdi
    double result = a[n-1];

    // Loop fra næstsidste element ned til første element
    for(int i = n-2; i >= 0; i--)
    {
        // Anvend combiner på a[i] og den akkumulerede værdi
        result = combiner(a[i], result);
    }

    return result; // Returner den samlede værdi
}

//==========================================================
// FUNKTION: combine_left
// Kombinerer et array a[0..n-1] fra venstre mod højre
// Input: a[] array, n = antal elementer, combiner = funktionspointer
// Output: resultat af kombinationen
//==========================================================
double combine_left(double a[], int n, double (*combiner)(double,double))
{
    // Start med første element som initialværdi
    double result = a[0];

    // Loop fra andet element op til sidste element
    for(int i = 1; i < n; i++)
    {
        // Anvend combiner på den akkumulerede værdi og a[i]
        result = combiner(result, a[i]);
    }

    return result; // Returner den samlede værdi
}

//==========================================================
// MAIN: Tester combine_right og combine_left
//==========================================================
int main(void)
{
    double a[] = {1.0, 2.0, 3.0, 4.0}; // Test array
    int n = 4;

    // Test combine_right med add
    double sum_right = combine_right(a, n, add);
    printf("combine_right (add) = %.2f\n", sum_right); 
    // Forventet: 1+2+3+4 = 10

    // Test combine_left med add
    double sum_left = combine_left(a, n, add);
    printf("combine_left (add) = %.2f\n", sum_left);
    // Forventet: 1+2+3+4 = 10

    // Test combine_right med multiply
    double product_right = combine_right(a, n, multiply);
    printf("combine_right (multiply) = %.2f\n", product_right);
    // Forventet: 1*2*3*4 = 24

    // Test combine_left med multiply
    double product_left = combine_left(a, n, multiply);
    printf("combine_left (multiply) = %.2f\n", product_left);
    // Forventet: 1*2*3*4 = 24

    // Test med et andet array og add
    double b[] = {5.0, 10.0, 15.0};
    int m = 3;
    printf("combine_right b[] (add) = %.2f\n", combine_right(b,m,add)); // 5+10+15 = 30
    printf("combine_left b[] (add) = %.2f\n", combine_left(b,m,add));   // 5+10+15 = 30

    return 0;
}

/*
EKSEMPEL OUTPUT:

combine_right (add) = 10.00
combine_left (add) = 10.00
combine_right (multiply) = 24.00
combine_left (multiply) = 24.00
combine_right b[] (add) = 30.00
combine_left b[] (add) = 30.00
*/
