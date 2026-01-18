#include <stdio.h>  // Inkluderer standard input/output-biblioteket

int main(void){
    // Deklaration af variabler
    int a = 1, b = 2, c = 3;   // Tre heltal
    double x = 1.0;             // Et decimaltal
    int res1, res2, res3, res4; // Variabler til at gemme resultat af logiske udtryk

    // Logiske udtryk med parenteser, så man tydeligt ser operatorprioritering

    // res1 = a > b && c < x;
    // Operatorprioritet: > og < først, derefter &&
    res1 = ( (a > b) && (c < x) );

    // res2 = a < ! b || ! ! a;
    // Operatorprioritet: ! først, derefter <, derefter ! igen, til sidst ||
    // Bemærk: ! b bliver 0, fordi b = 2 (sand), ! ! a = ! (!1) = !0 = 1
    res2 = ( (a < (!b)) || (!(!a)) );

    // res3 = a + b < ! c + c;
    // Operatorprioritet: + først, derefter <, + igen
    // Bemærk: !c = !3 = 0 (fordi c != 0), så !c + c = 0 + 3 = 3
    res3 = ( ((a + b) < ((!c) + c)) );

    // res4 = a - x || b * c && b / a;
    // Operatorprioritet: * og / først, derefter &&, derefter ||
    // Her omskrevet med parenteser:
    res4 = ( ((a - x) != 0) || ( ((b * c) && (b / a)) != 0 ) );
    // Bemærk: i C tolkes ethvert tal forskelligt fra 0 som "sand" i logiske udtryk

    // Udskriv resultaterne
    printf("res1 = %d, res2 = %d, res3 = %d,  res4 = %d \n", 
        res1, res2, res3, res4);

    return 0;
}

/*
Forklaring af output:

res1 = (1 > 2 && 3 < 1) = (0 && 0) = 0
res2 = (1 < !2 || !!1) = (1 < 0 || 1) = (0 || 1) = 1
res3 = (1+2 < !3 + 3) = (3 < 0+3) = (3 < 3) = 0
res4 = (1-1.0 || 2*3 && 2/1) = (0 || 6 && 2) = (0 || 1) = 1
Bemærk: 
- I res4 tolkes 6 && 2 som 1, fordi begge er ikke-nul (sand)
- 0 || 1 = 1

Så programmet vil udskrive:
res1 = 0, res2 = 1, res3 = 0, res4 = 1
*/
