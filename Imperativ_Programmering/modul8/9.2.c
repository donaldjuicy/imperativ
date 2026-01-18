/*
=========================================================
FORMÅL:
Programmet repræsenterer et polynomium af grad n (maks 8)
som et array af koefficienter a0..an og beregner polynomiets
værdi for forskellige x-værdier. Brugeren kan evaluere
polynomiet flere gange for forskellige x-værdier.

FAGORD:
- Array: Sekventiel samling af værdier af samme type (double)
- Pointer: Variabel der indeholder adressen på en anden variabel
- Call by value: Funktionen får en kopi af værdien
- Call by reference: Funktionen kan ændre variabler i main via pointer
- Evaluer: Beregn polynomiets værdi for et givet x
=========================================================
*/

#include <stdio.h>   // Standard input/output biblioteker
#include <stdlib.h>  // Generelt bibliotek (bruges ikke direkte her)
#include <math.h>    // Matematikfunktioner (kan bruges til pow hvis ønsket)

// Maksimal grad af polynomium
#define MAX_DEGREE 8

//==========================================================
// FUNKTION: get_polynomium
// Læser polynomium fra brugeren og gemmer koefficienter i et array
// Input: ingen
// Output: 
//   coeff[]: array med koefficienter a0..an (call by reference)
//   degreep: pointer til int som sættes til graden af polynomiet
//==========================================================
void get_polynomium(double coeff[], int *degreep)
{
    int degree;  // Variabel til midlertidigt at holde brugerens input for graden

    // Gentag indtil brugeren indtaster en gyldig grad mellem 0 og MAX_DEGREE
    do {
        printf("Indtast graden af polynomiet (0-%d): ", MAX_DEGREE); // Prompt til bruger
        scanf("%d", &degree);  // Læs input som integer

        // Tjek om input er gyldigt
        if(degree < 0 || degree > MAX_DEGREE)
            printf("Ugyldig grad. Prøv igen.\n"); // Advarsel
    } while(degree < 0 || degree > MAX_DEGREE); // Loop fortsætter indtil gyldig grad

    *degreep = degree;  // Gem graden i den variable, der peges på af degreep

    // Læs koefficienterne a0..an fra brugeren
    for(int i = 0; i <= degree; i++)
    {
        printf("Indtast koefficient a%d: ", i);  // Prompt til bruger
        scanf("%lf", &coeff[i]);  // Gem input i arrayets i'te element
    }
}

//==========================================================
// FUNKTION: eval_polynomium
// Beregner værdien af polynomiet p(x) = a0 + a1*x + ... + an*x^n
// Input:
//   coeff[]: array med koefficienter
//   degree: graden af polynomiet
//   x: værdien som polynomiet evalueres for
// Output: polynomiets værdi for x
//==========================================================
double eval_polynomium(const double coeff[], int degree, double x)
{
    double result = 0.0; // Start med resultat = 0

    // For hvert led i polynomiet fra 0 til degree
    for(int i = 0; i <= degree; i++)
    {
        double term = coeff[i]; // Hent koefficient a_i
        double xpower = 1.0;    // Beregner x^i, start med x^0 = 1

        // Beregn x^i vha. loop
        for(int j = 0; j < i; j++)
        {
            xpower *= x;  // Gang x sammen i i antal gange
        }

        // Gang koefficient med x^i
        term *= xpower;

        // Tilføj leddet til resultatet
        result += term;
    }

    return result; // Returner den samlede værdi af polynomiet
}

//==========================================================
// MAIN: bruger interaktivt program
//==========================================================
int main(void)
{
    double coeff[MAX_DEGREE + 1]; // Array til koefficienter a0..a8
    int degree;                    // Variabel til graden
    double x;                      // Variabel til x-værdien
    char choice;                   // Variabel til om brugeren vil evaluere flere x

    // Læs polynomium fra brugeren
    get_polynomium(coeff, &degree); // Kald funktion og brug pointer til degree

    // Start loop for evaluering af forskellige x
    do {
        printf("Indtast x-værdi for evaluering af polynomiet: "); // Prompt
        scanf("%lf", &x); // Læs x-værdi

        // Beregn polynomiets værdi for x
        double y = eval_polynomium(coeff, degree, x);

        // Udskriv resultat med 4 decimaler
        printf("p(%.2f) = %.4f\n", x, y);

        // Spørg om brugeren vil evaluere endnu en x
        printf("Vil du evaluere et andet x? (j/n): ");
        scanf(" %c", &choice); // Bemærk mellemrum før %c for at fange newline
    } while(choice == 'j' || choice == 'J'); // Fortsæt hvis brugeren svarer 'j'

    return 0; // Programmet afsluttes korrekt
}

/*
EKSEMPEL PÅ KØRSEL:

Indtast graden af polynomiet (0-8): 2
Indtast koefficient a0: 1
Indtast koefficient a1: 2
Indtast koefficient a2: 3
Indtast x-værdi for evaluering af polynomiet: 1
p(1.00) = 6.0000
Vil du evaluere et andet x? (j/n): j
Indtast x-værdi for evaluering af polynomiet: 2
p(2.00) = 17.0000
Vil du evaluere et andet x? (j/n): n
*/
