#include <stdio.h>   // Giver adgang til printf-funktionen

int main(void) {     // Programmet starter her

  // Opretter tre heltals-variabler og giver dem startværdier
  int i = 3;         // i starter med værdien 3
  int j = 4;         // j starter med værdien 4
  int k = 5;         // k starter med værdien 5

  // Opretter tre variabler til at gemme resultater i
  int res1, res2, res3;

  // i++ : øg i med 1 (post-increment)
  i++;               // i går fra 3 til 4

  // j-- : mindsk j med 1 (post-decrement)
  j--;               // j går fra 4 til 3

  // ++k : øg k med 1 (pre-increment)
  ++k;               // k går fra 5 til 6

  // Udskriver de nuværende værdier af i, j og k
  printf("i: %d, j: %d, k: %d\n", i, j, k);

  // --i : mindsk i med 1 FØR værdien bruges
  res1 = --i;        // i bliver 3, res1 får værdien 3

  // j++ : brug værdien af j FØR den øges
  res2 = j++;        // res2 får 3, derefter bliver j til 4

  // --k : mindsk k med 1 FØR værdien bruges
  res3 = --k;        // k bliver 5, res3 får værdien 5

  // Udskriver værdierne gemt i res1, res2 og res3
  printf("res1: %d, res2: %d, res3: %d\n", res1, res2, res3);

  // Udskriver de endelige værdier af i, j og k
  printf("i: %d, j: %d, k: %d\n", i, j, k);

  return 0;          // Programmet slutter korrekt
}
