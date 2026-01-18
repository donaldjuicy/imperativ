/****************************************************
 * File: primes.h
 ****************************************************/

/* Header guard for at undgå dobbelt inklusion */
#ifndef PRIMES_H
#define PRIMES_H

/* Returnerer 1 hvis i er et primtal, ellers 0 */
int is_prime(int i);

#endif



/****************************************************
 * File: primes.c
 ****************************************************/

#include "primes.h"     // Gør is_prime kendt for andre filer
#include <math.h>       // Bruges til sqrt() og ceil()
#include <assert.h>     // Bruges til at kontrollere forudsætninger

/* Returnerer 1 hvis i er et primtal.
   Forudsætning: i er et ikke-negativt heltal */
int is_prime(int i){
   assert(i >= 0);      // Stopper programmet hvis i er negativ

   if (i == 1)          // 1 er ikke et primtal
     return 0;
   else if (i == 2)     // 2 er det mindste primtal
     return 1;
   else if (i % 2 == 0) // Lige tal større end 2 er ikke primtal
     return 0;
   else{
     int k, limit;                         // k er divisor, limit er øvre grænse
     limit = (int)(ceil(sqrt(i)));         // Tester kun op til kvadratroden af i
     for (k = 3; k <= limit; k += 2)       // Tester kun ulige divisorer
        if (i % k == 0)                    // Hvis i kan deles med k
           return 0;                       // er i ikke et primtal
     return 1;                             // Ellers er i et primtal
   }
}



/****************************************************
 * File: test-primes.c
 ****************************************************/

#include <stdio.h>      // Bruges til printf
#include "primes.h"    // Giver adgang til is_prime-funktionen

int main(void){
    int n = 100;        // Antal primtal der ønskes udskrevet
    int count = 0;      // Tæller hvor mange primtal der er fundet
    int i = 2;          // Starter ved 2, da 1 ikke er et primtal

    /* Finder og udskriver de første n primtal */
    while (count < n) {
        if (is_prime(i)) {                 // Tester om i er et primtal
            count++;                       // Ét primtal mere fundet
            printf("prime %d: %d\n",       // Udskriver primtal nummer og værdi
                   count, i);
        }
        i++;                               // Går videre til næste tal
    }

    return 0;           // Programmet afsluttes korrekt
}



/****************************************************
 * Kommentar til output:
 *
 * Programmet gennemløber alle heltal fra 2 og opefter
 * og tester hvert tal med funktionen is_prime.
 * Hver gang et primtal findes, udskrives det med
 * et løbenummer.
 *
 * Når de første 100 primtal er fundet, stopper programmet.
 * Det sidste output er:
 *
 * prime 100: 541
 *
 * hvilket er korrekt, da 541 er det 100. primtal.
 ****************************************************/
