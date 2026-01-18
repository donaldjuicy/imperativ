# C Pointere - Komplet Eksamensguide

## Hvad er en Pointer?

En pointer er en variabel der gemmer **adressen** til en anden variabel i hukommelsen. I stedet for at gemme en værdi (som 42), gemmer en pointer positionen i RAM hvor værdien er gemt.

```c
int tal = 42;        // Normal variabel
int *ptr = &tal;     // Pointer der peger på 'tal'
```

## Grundlæggende Syntax

### Deklaration af Pointere

```c
int *p1;           // Pointer til int
char *p2;          // Pointer til char
double *p3;        // Pointer til double
float *p4;         // Pointer til float
```

**Vigtigt:** Stjernen (*) i deklarationen betyder "pointer til".

### Address-of Operatoren (&)

Brug `&` til at få adressen på en variabel:

```c
int x = 10;
int *ptr = &x;     // ptr gemmer adressen til x

printf("Værdi af x: %d\n", x);           // 10
printf("Adresse af x: %p\n", &x);        // f.eks. 0x7ffc8b4a5b2c
printf("Værdi af ptr: %p\n", ptr);       // Samme adresse
```

### Dereference Operatoren (*)

Brug `*` til at få værdien som pointeren peger på:

```c
int y = 20;
int *ptr = &y;

printf("ptr peger på adresse: %p\n", ptr);   // Adresse
printf("Værdien på adressen: %d\n", *ptr);   // 20

*ptr = 30;  // Ændrer værdien af y gennem pointeren!
printf("Ny værdi af y: %d\n", y);            // 30
```

## Alle Mulige Eksamens-Scenarier

### 1. Hvad printer dette program?

```c
int a = 5;
int *p = &a;
*p = 10;
printf("%d\n", a);  // Hvad printer dette?
```

**Svar:** 10 - fordi vi ændrede værdien gennem pointeren.

### 2. Pointer Aritmetik

```c
int arr[] = {10, 20, 30, 40};
int *ptr = arr;  // Peger på første element

printf("%d\n", *ptr);      // 10
printf("%d\n", *(ptr+1));  // 20
printf("%d\n", *(ptr+2));  // 30

ptr++;  // Flytter pointer til næste int
printf("%d\n", *ptr);      // 20
```

**Vigtigt:** Når du lægger 1 til en int-pointer, flytter den sig `sizeof(int)` bytes (typisk 4 bytes).

### 3. Pointer til Pointer

```c
int x = 100;
int *p1 = &x;       // Pointer til x
int **p2 = &p1;     // Pointer til pointer

printf("%d\n", x);       // 100
printf("%d\n", *p1);     // 100
printf("%d\n", **p2);    // 100

**p2 = 200;  // Ændrer x gennem dobbelt-pointer
printf("%d\n", x);       // 200
```

### 4. NULL Pointere

```c
int *ptr = NULL;  // Pointer der ikke peger på noget

if (ptr == NULL) {
    printf("Pointer er NULL - sikker at bruge!\n");
}

// FARLIGT - giver segmentation fault:
// *ptr = 10;
```

**Best Practice:** Initialiser altid pointere til NULL hvis de ikke peger på noget endnu.

### 5. Swap Funktion med Pointere

```c
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 5, y = 10;
    printf("Før: x=%d, y=%d\n", x, y);
    
    swap(&x, &y);  // Send adresser!
    
    printf("Efter: x=%d, y=%d\n", x, y);  // x=10, y=5
    return 0;
}
```

**Hvorfor virker det?** Fordi funktionen får adresserne og kan ændre de originale variable.

### 6. Returnere Multiple Værdier

```c
void beregn(int a, int b, int *sum, int *produkt) {
    *sum = a + b;
    *produkt = a * b;
}

int main() {
    int s, p;
    beregn(5, 3, &s, &p);
    printf("Sum: %d, Produkt: %d\n", s, p);  // Sum: 8, Produkt: 15
    return 0;
}
```

### 7. Arrays og Pointere

```c
int tal[] = {1, 2, 3, 4, 5};
int *p = tal;  // Array-navn er en pointer til første element

// Disse er ækvivalente:
printf("%d\n", tal[0]);   // 1
printf("%d\n", *tal);     // 1
printf("%d\n", *p);       // 1

printf("%d\n", tal[2]);   // 3
printf("%d\n", *(tal+2)); // 3
printf("%d\n", *(p+2));   // 3
printf("%d\n", p[2]);     // 3 - ja, du kan bruge [] på pointere!
```

### 8. Dynamisk Hukommelse (malloc)

```c
#include <stdlib.h>

int *arr = (int*)malloc(5 * sizeof(int));  // Allokér plads til 5 ints

if (arr == NULL) {
    printf("Hukommelsen kunne ikke allokeres!\n");
    return 1;
}

// Brug arrayet
for (int i = 0; i < 5; i++) {
    arr[i] = i * 10;
}

// Husk at frigive hukommelsen!
free(arr);
arr = NULL;  // God praksis
```

### 9. Const Pointere - Fire Variationer

```c
int x = 10, y = 20;

// 1. Pointer til konstant int - kan ikke ændre værdien
const int *p1 = &x;
// *p1 = 15;  // FEJL!
p1 = &y;      // OK - kan pege på noget andet

// 2. Konstant pointer til int - kan ikke pege på noget andet
int *const p2 = &x;
*p2 = 15;     // OK - kan ændre værdien
// p2 = &y;   // FEJL!

// 3. Konstant pointer til konstant int - ingen kan ændres
const int *const p3 = &x;
// *p3 = 15;  // FEJL!
// p3 = &y;   // FEJL!

// 4. Normal pointer (til sammenligning)
int *p4 = &x;
*p4 = 15;     // OK
p4 = &y;      // OK
```

### 10. Pointere i Loops

```c
int arr[] = {10, 20, 30, 40, 50};
int *p;

// Metode 1: Traditionel
for (p = arr; p < arr + 5; p++) {
    printf("%d ", *p);
}
// Output: 10 20 30 40 50

// Metode 2: Med end-pointer
int *end = arr + 5;
for (p = arr; p < end; p++) {
    *p *= 2;  // Doubler hver værdi
}
```

### 11. String Pointere

```c
char *str1 = "Hello";  // Pointer til string literal (read-only!)
char str2[] = "World"; // Array af chars (kan modificeres)

// str1[0] = 'h';  // FARLIGT - kan crashe!
str2[0] = 'w';     // OK

// Traversere string med pointer
char *p = str2;
while (*p != '\0') {
    printf("%c", *p);
    p++;
}
```

### 12. Funktions-Pointere

```c
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int main() {
    int (*operation)(int, int);  // Deklarerer funktions-pointer
    
    operation = add;
    printf("5 + 3 = %d\n", operation(5, 3));  // 8
    
    operation = subtract;
    printf("5 - 3 = %d\n", operation(5, 3));  // 2
    
    return 0;
}
```

### 13. Almindelige Fejl og Hvordan Man Undgår Dem

#### Fejl 1: Uninitialiserede Pointere

```c
// FORKERT:
int *p;
*p = 10;  // p peger på en tilfældig adresse - CRASH!

// RIGTIGT:
int x;
int *p = &x;
*p = 10;  // OK
```

#### Fejl 2: Dangling Pointer

```c
// FORKERT:
int *p = (int*)malloc(sizeof(int));
*p = 42;
free(p);
printf("%d\n", *p);  // p peger på frigivet hukommelse - FARLIGT!

// RIGTIGT:
int *p = (int*)malloc(sizeof(int));
*p = 42;
printf("%d\n", *p);
free(p);
p = NULL;  // Marker som ugyldig
```

#### Fejl 3: Returnere Pointer til Lokal Variabel

```c
// FORKERT:
int* getNumber() {
    int x = 10;
    return &x;  // x bliver destrueret når funktionen slutter!
}

// RIGTIGT - Brug malloc:
int* getNumber() {
    int *x = (int*)malloc(sizeof(int));
    *x = 10;
    return x;  // Caller skal bruge free()!
}
```

### 14. Pointer Størrelse og sizeof

```c
int x = 10;
int *p = &x;

printf("sizeof(int): %lu\n", sizeof(int));      // 4 (typisk)
printf("sizeof(int*): %lu\n", sizeof(int*));    // 8 på 64-bit system
printf("sizeof(p): %lu\n", sizeof(p));          // 8 på 64-bit system
printf("sizeof(*p): %lu\n", sizeof(*p));        // 4 (size af int)

// Alle pointere har samme størrelse uanset type!
printf("%lu\n", sizeof(char*));    // 8
printf("%lu\n", sizeof(double*));  // 8
printf("%lu\n", sizeof(void*));    // 8
```

### 15. Void Pointere (Generic Pointere)

```c
void printValue(void *p, char type) {
    switch(type) {
        case 'i':
            printf("%d\n", *(int*)p);
            break;
        case 'd':
            printf("%f\n", *(double*)p);
            break;
        case 'c':
            printf("%c\n", *(char*)p);
            break;
    }
}

int main() {
    int i = 10;
    double d = 3.14;
    char c = 'A';
    
    printValue(&i, 'i');  // 10
    printValue(&d, 'd');  // 3.14
    printValue(&c, 'c');  // A
    
    return 0;
}
```

## Pointer Cheat Sheet

| Operation | Syntax | Beskrivelse |
|-----------|--------|-------------|
| Deklaration | `int *p;` | Deklarer pointer til int |
| Få adresse | `&x` | Adresse af variabel x |
| Dereference | `*p` | Værdi som p peger på |
| NULL pointer | `int *p = NULL;` | Pointer der ikke peger nogen steder |
| Pointer aritmetik | `p + 1` | Næste element (baseret på type) |
| Array-pointer | `int *p = arr;` | Pointer til første element |
| Malloc | `malloc(n * sizeof(type))` | Allokér dynamisk hukommelse |
| Free | `free(p);` | Frigør allokeret hukommelse |

## Eksamenstips

1. **Tegn altid hukommelsen!** Lav bokse for variable og skriv adresser ved siden af.

2. **Følg typen:** En `int*` peger på en int. En `char*` peger på en char. Type-systemet hjælper dig!

3. **Ved pointer aritmetik:** Husk at pointere springer baseret på `sizeof(type)`, ikke bare 1 byte.

4. **Check for NULL:** Før du dereferencer en pointer fra malloc eller en funktion, check om den er NULL.

5. **Free hvad du malloc'er:** Hver malloc skal have en tilsvarende free for at undgå memory leaks.

6. **& og * er modsætninger:** `&` giver adresse, `*` giver værdi. De "annullerer" hinanden: `*(&x)` er bare `x`.

7. **Arrays er pointere:** Array-navn kan bruges som pointer til første element.

## Hurtig Test - Kan Du Svare?

```c
int x = 5;
int *p1 = &x;
int **p2 = &p1;

**p2 = 10;  // Hvad er x nu?        → 10
printf("%p %p", p1, &x);  // Samme? → Ja
printf("%d", *p1);        // Hvad?  → 10
```

God forberedelse til eksamen! 🎯