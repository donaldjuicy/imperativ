#include <stdio.h>   // Inkluderer standard input/output-biblioteket
#include <math.h>    // Inkluderer matematikfunktioner, fx sqrt og fabs

int main() {
    // Deklaration af variabler
    double r, x, y;        // r = radius, x og y = punktets koordinater
    const double DELTA = 1e-6; // Tolerance for at afgøre om punktet er "på" cirklen

    // Input fra brugeren
    printf("Indtast radius r: ");
    scanf("%lf", &r);      // %lf bruges til at læse double
    printf("Indtast punktets x-koordinat: ");
    scanf("%lf", &x);
    printf("Indtast punktets y-koordinat: ");
    scanf("%lf", &y);

    // Beregning af afstanden fra punktet til origo (0,0)
    double afstand = sqrt(x*x + y*y); // Pythagoras sætning: sqrt(x^2 + y^2)

    // Logiske udtryk
    int inden_i = afstand < r - DELTA;             // Sand, hvis punktet er inden i cirklen
    int uden_for = afstand > r + DELTA;            // Sand, hvis punktet er udenfor cirklen
    int pa_periferien = fabs(afstand - r) <= DELTA; // Sand, hvis punktet er tæt på cirklen (|afstand-r| <= DELTA)

    // printf med betingede udtryk (?:)
    printf("Punktet er %s cirklen.\n",
           pa_periferien ? "på" : (inden_i ? "inden i" : "uden for"));

    return 0;
}

/*
Eksempel på output:

Indtast radius r: 5
Indtast punktets x-koordinat: 3
Indtast punktets y-koordinat: 4
Punktet er på cirklen.

Indtast radius r: 5
Indtast punktets x-koordinat: 1
Indtast punktets y-koordinat: 1
Punktet er inden i cirklen.

Indtast radius r: 5
Indtast punktets x-koordinat: 6
Indtast punktets y-koordinat: 0
Punktet er uden for cirklen.
*/
