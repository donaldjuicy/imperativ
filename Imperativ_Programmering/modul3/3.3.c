#include <stdio.h>  // Inkluderer standard input/output biblioteket

int main(void) {
    double ph;  // Variabel til pH-værdien

    // Input fra brugeren
    printf("Indtast pH-værdien: ");
    scanf("%lf", &ph);  // %lf bruges til double

    // Multiple-alternative if-else kæde
    if (ph <= 2) {
        printf("Very acidic\n"); // Gælder for ph i interval [ -∞ , 2 ]
    }
    else if (ph < 7) {
        printf("Acidic\n");      // Gælder for ph i interval (2 , 7)
    }
    else if (ph == 7) {
        printf("Neutral\n");     // Gælder kun for ph = 7
    }
    else if (ph < 12) {
        printf("Alkaline\n");    // Gælder for ph i interval (7 , 12)
    }
    else {
        printf("Very alkaline\n"); // Gælder for ph i interval [12 , +∞)
    }

    return 0;
}

/*
Forklaring linje for linje:

1. #include <stdio.h> : Gør det muligt at bruge printf og scanf.
2. double ph; : Vi laver en variabel ph med decimaler (double), da pH ofte ikke er heltal.
3. printf("Indtast pH-værdien: "); : Skriver prompt til brugeren.
4. scanf("%lf", &ph); : Læser et decimal-tal ind fra brugeren.
5. if (ph <= 2) { ... } : Hvis pH er 2 eller mindre, er det "Very acidic".
6. else if (ph < 7) { ... } : Hvis pH er større end 2 men mindre end 7, er det "Acidic".
7. else if (ph == 7) { ... } : Hvis pH er nøjagtig 7, er det "Neutral".
8. else if (ph < 12) { ... } : Hvis pH er større end 7 men mindre end 12, er det "Alkaline".
9. else { ... } : Hvis pH er 12 eller højere, er det "Very alkaline".

Kommentarer til intervaller:
- Very acidic : ph ≤ 2
- Acidic      : 2 < ph < 7
- Neutral     : ph = 7
- Alkaline    : 7 < ph < 12
- Very alkaline: ph ≥ 12

Eksempel på output:
Indtast pH-værdien: 1.5
Very acidic

Indtast pH-værdien: 6
Acidic

Indtast pH-værdien: 7
Neutral

Indtast pH-værdien: 10
Alkaline

Indtast pH-værdien: 13
Very alkaline
*/
