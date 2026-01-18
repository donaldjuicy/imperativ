/*===========================================================
  PROGRAM: Summering af tal mellem m og n, delelige med k
  Formål: Eksempel på while-løkke og betingelser
  Kommentarer forklarer hvert trin for begyndere
===========================================================*/

#include <stdio.h>

int main(void) {

    // 1️⃣ Indtastning af tre positive heltal
    int m, n, k;
    printf("Indtast tre positive heltal m, n og k (k > 1):\n");
    scanf("%d %d %d", &m, &n, &k);

    // 2️⃣ Variabel til at gemme summen
    int sum = 0;

    // 3️⃣ Check om m <= n. Hvis ikke, summen forbliver 0
    if (m <= n) {
        int i = m;  // start tælleren fra m

        // while-løkke kører indtil i > n
        while (i <= n) {
            if (i % k == 0) { // tjek om i er deleligt med k
                sum = sum + i; // læg i til summen
            }
            i = i + 1; // gå til næste tal
        }
    }

    // 4️⃣ Udskriv resultatet
    printf("Summen af tal mellem %d og %d, der er delelige med %d, er: %d\n", m, n, k, sum);

    return 0;
}

/*===========================================================
  Forklaring:
  - i = m: starter fra det første tal
  - while(i <= n): kører så længe vi ikke har passeret n
  - if(i % k == 0): % er modulo, tjekker om i kan deles med k uden rest
  - sum = sum + i: lægger tallet til summen
  - i = i + 1: gå videre til næste tal
  - Hvis m > n: løkken køres ikke, sum forbliver 0
===========================================================*/

/* Eksempler:
   Input: m=5, n=13, k=3
   Output: 27 (6+9+12)

   Input: m=5, n=10, k=5
   Output: 15 (5+10)

   Input: m=10, n=5, k=3
   Output: 0
*/
