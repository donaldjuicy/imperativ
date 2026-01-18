#include <stdio.h>

/*
=========================================================
Funktion: recursive_strcmp
Rekursiv version af strcmp fra string.h

Parametre:
- s1 : pointer til første tekststreng
- s2 : pointer til anden tekststreng

Returnerer:
- 0, hvis s1 og s2 er identiske
- negativt tal, hvis s1 < s2 (leksikografisk)
- positivt tal, hvis s1 > s2 (leksikografisk)
=========================================================
*/

int recursive_strcmp(const char *s1, const char *s2)
{
    // Basistilfælde 1: begge tegn er nul → end of string
    if (*s1 == '\0' && *s2 == '\0')
        return 0;

    // Basistilfælde 2: tegnene er forskellige → return forskellen
    if (*s1 != *s2)
        return (unsigned char)(*s1) - (unsigned char)(*s2);

    // Rekursivt kald på næste tegn
    return recursive_strcmp(s1 + 1, s2 + 1);
}

//=========================================================
// MAIN: eksempel på brug
//=========================================================
int main(void)
{
    const char *a = "apple";
    const char *b = "apricot";
    const char *c = "apple";

    int res1 = recursive_strcmp(a, b);
    int res2 = recursive_strcmp(a, c);
    int res3 = recursive_strcmp(b, a);

    printf("strcmp(\"%s\", \"%s\") = %d\n", a, b, res1);
    printf("strcmp(\"%s\", \"%s\") = %d\n", a, c, res2);
    printf("strcmp(\"%s\", \"%s\") = %d\n", b, a, res3);

    return 0;
}
