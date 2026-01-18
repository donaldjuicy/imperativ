// Kode 1



#include <stdio.h>   // Giver adgang til printf

int main(void) {

  // sum1 bruger almindelige decimale tal (10-tals system)
  int sum1 =    10  +   11  +  12,

      // sum2 bruger tal med foranstillet 0 → tolkes som oktale tal (8-tals system)
      sum2  =  010 +   011 +  012,

      // sum3 bruger 0x foran → hexadecimale tal (16-tals system)
      sum3  = 0x10 +  0x11 + 0x12;

  // Udskriver sum1 som et decimalt heltal
  printf("sum1 =  %d\n", sum1);

  // Udskriver sum2 som et decimalt heltal
  printf("sum2 =  %d\n", sum2);

  // Udskriver sum3 som et decimalt heltal
  printf("sum3 =  %d\n", sum3);

  return 0;  // Programmet afsluttes korrekt
}




// Kode 2

#include <stdio.h>

int main(void) {

  int x, y, z, sum;   // Tre tal og deres sum

  printf("Enter three integers: ");

  // %d fortæller scanf at tallene skal læses som decimale tal
  scanf("%d %d %d", &x, &y, &z);

  sum = x + y + z;

  printf("sum =  %d\n", sum);

  return 0;
}




// Kode 3
#include <stdio.h>

int main(void) {

  int x, y, z, sum;

  printf("Enter three integers: ");

  // %o fortæller scanf at tallene er i oktal (8-tals system)
  scanf("%o %o %o", &x, &y, &z);

  sum = x + y + z;

  printf("sum =  %d\n", sum);

  return 0;
}



//Kode 4
#include <stdio.h>

int main(void) {

  int x, y, z, sum;

  printf("Enter three integers: ");

  // Læs tre oktale tal
  scanf("%o %o %o", &x, &y, &z);

  sum = x + y + z;

  // Udskriv summen som et oktalt tal
  printf("sum =  %o\n", sum);

  return 0;
}


