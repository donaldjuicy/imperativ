# C Parametre og Structs - Komplet Eksamensguide

## Del 1: Funktionsparametre

### Hvad er Parametre?

Parametre er **værdier eller adresser** som sendes til en funktion. De gør funktioner fleksible og genanvendelige.

```c
// 'a' og 'b' er parametre
int add(int a, int b) {
    return a + b;
}

int main() {
    int sum = add(5, 3);  // 5 og 3 er argumenter
    printf("%d\n", sum);  // 8
    return 0;
}
```

**Terminologi:**
- **Parametre (Parameters):** Variablerne i funktionsdefinitionen (`int a, int b`)
- **Argumenter (Arguments):** De faktiske værdier sendt til funktionen (`5, 3`)

## Call by Value vs Call by Reference

### Call by Value (Værdi-kopiering)

Når du sender en variabel til en funktion, **kopieres værdien**. Ændringer i funktionen påvirker **ikke** originalen.

```c
void increment(int x) {
    x++;  // Øger KUN den lokale kopi
    printf("Inde i funktion: x = %d\n", x);  // 11
}

int main() {
    int num = 10;
    increment(num);
    printf("I main: num = %d\n", num);  // Stadig 10!
    return 0;
}
```

**Hvorfor?** Fordi `x` er en kopi af `num`. Funktionen får sin egen version.

### Call by Reference (Adresse-kopiering)

Når du sender en **adresse** (pointer), kan funktionen ændre den originale variabel.

```c
void increment(int *x) {
    (*x)++;  // Ændrer værdien på adressen
    printf("Inde i funktion: *x = %d\n", *x);  // 11
}

int main() {
    int num = 10;
    increment(&num);  // Send adressen!
    printf("I main: num = %d\n", num);  // 11 (ændret!)
    return 0;
}
```

**Hvorfor virker det?** Fordi funktionen får adressen og kan dereferere den for at ændre den originale værdi.

### Sammenligning Side om Side

```c
// Call by Value
void doubleValue(int x) {
    x = x * 2;
}

// Call by Reference
void doubleReference(int *x) {
    *x = *x * 2;
}

int main() {
    int a = 5, b = 5;
    
    doubleValue(a);
    printf("a = %d\n", a);  // 5 (uændret)
    
    doubleReference(&b);
    printf("b = %d\n", b);  // 10 (ændret)
    
    return 0;
}
```

## Arrays som Parametre

### Arrays Sendes ALTID som Reference

```c
void modifyArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;
    }
}

int main() {
    int tal[] = {1, 2, 3, 4, 5};
    
    modifyArray(tal, 5);  // Intet & nødvendigt!
    
    for (int i = 0; i < 5; i++) {
        printf("%d ", tal[i]);  // 2 4 6 8 10 (ændret!)
    }
    
    return 0;
}
```

**Hvorfor?** Array-navne er allerede pointere til første element.

### Forskellige Notationer (Alle Ækvivalente)

```c
// Alle disse er identiske:
void func1(int arr[], int size) { }
void func2(int *arr, int size) { }
void func3(int arr[10], int size) { }  // 10 ignoreres!

// Kaldes alle på samme måde:
int data[5] = {1, 2, 3, 4, 5};
func1(data, 5);
func2(data, 5);
func3(data, 5);
```

### 2D Arrays som Parametre

```c
// Første dimension kan udelades, resten skal specificeres
void printMatrix(int rows, int arr[][4]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    printMatrix(3, matrix);
    return 0;
}
```

## Returnere Multiple Værdier

### Metode 1: Brug Pointere

```c
void calculate(int a, int b, int *sum, int *diff, int *prod) {
    *sum = a + b;
    *diff = a - b;
    *prod = a * b;
}

int main() {
    int s, d, p;
    calculate(10, 5, &s, &d, &p);
    
    printf("Sum: %d\n", s);      // 15
    printf("Diff: %d\n", d);     // 5
    printf("Produkt: %d\n", p);  // 50
    
    return 0;
}
```

### Metode 2: Brug Structs (Se næste sektion!)

```c
typedef struct {
    int sum;
    int diff;
    int prod;
} Results;

Results calculate(int a, int b) {
    Results r;
    r.sum = a + b;
    r.diff = a - b;
    r.prod = a * b;
    return r;
}

int main() {
    Results res = calculate(10, 5);
    printf("Sum: %d\n", res.sum);      // 15
    printf("Diff: %d\n", res.diff);    // 5
    printf("Produkt: %d\n", res.prod); // 50
    return 0;
}
```

## Const Parametre

```c
// Kan ikke modificere værdien
void printValue(const int x) {
    printf("%d\n", x);
    // x = 10;  // FEJL!
}

// Kan ikke modificere array-elementerne
void printArray(const int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
        // arr[i] = 0;  // FEJL!
    }
}

// Pointer til konstant data
void process(const char *str) {
    printf("%s\n", str);
    // str[0] = 'X';  // FEJL!
}
```

**Hvorfor bruge const?**
- Dokumenterer at funktionen ikke ændrer data
- Compileren hjælper med at finde fejl
- Tillader optimiseringer

## Variable Antal Parametre (Avanceret)

```c
#include <stdarg.h>

int sum(int count, ...) {
    va_list args;
    va_start(args, count);
    
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);
    }
    
    va_end(args);
    return total;
}

int main() {
    printf("%d\n", sum(3, 10, 20, 30));  // 60
    printf("%d\n", sum(5, 1, 2, 3, 4, 5));  // 15
    return 0;
}
```

---

## Del 2: Structs (Strukturer)

### Hvad er en Struct?

En struct er en **sammensat datatype** der grupperer relaterede variable af forskellig type under ét navn.

```c
struct Person {
    char navn[50];
    int alder;
    float hojde;
};
```

**Analogi:** Tænk på en struct som en skabelon for en genstand. Ligesom en bil har mærke, farve, og årgang, kan en Person have navn, alder, og højde.

### Deklaration og Initialisering

#### Grundlæggende Struct

```c
// Definition af struct
struct Student {
    int id;
    char navn[50];
    float karakterer[5];
    float gennemsnit;
};

// Oprettelse af variable
struct Student s1;
struct Student s2, s3;
```

#### Initialisering

```c
// Metode 1: Medlem-for-medlem
struct Student s1;
s1.id = 101;
strcpy(s1.navn, "Anna");
s1.gennemsnit = 8.5;

// Metode 2: Ved deklaration
struct Student s2 = {102, "Peter", {7.0, 8.0, 9.0, 8.5, 7.5}, 8.0};

// Metode 3: Designated initializers (C99+)
struct Student s3 = {
    .id = 103,
    .navn = "Marie",
    .gennemsnit = 9.2
};  // Resten bliver 0/NULL
```

### Typedef - Forenkle Syntaxen

```c
// Uden typedef - lang syntax
struct Person {
    char navn[50];
    int alder;
};
struct Person p1;  // Skal skrive "struct" hver gang

// Med typedef - kort syntax
typedef struct {
    char navn[50];
    int alder;
} Person;
Person p1;  // Meget nemmere!

// ELLER kombinér:
typedef struct Person {
    char navn[50];
    int alder;
} Person;
```

**Best Practice:** Brug typedef for nemmere kode.

### Tilgang til Struct-Medlemmer

#### Med Dot Operator (.)

```c
typedef struct {
    int x;
    int y;
} Point;

int main() {
    Point p1;
    
    // Tildeling
    p1.x = 10;
    p1.y = 20;
    
    // Læsning
    printf("(%d, %d)\n", p1.x, p1.y);
    
    // Beregninger
    p1.x = p1.x + 5;
    
    return 0;
}
```

#### Med Arrow Operator (->)

Bruges når du har en **pointer** til en struct.

```c
typedef struct {
    int x;
    int y;
} Point;

int main() {
    Point p1 = {10, 20};
    Point *ptr = &p1;
    
    // Begge virker, men -> er nemmere:
    printf("%d\n", (*ptr).x);  // 10 (kluntet)
    printf("%d\n", ptr->x);    // 10 (nemt!)
    
    ptr->y = 30;
    printf("%d\n", p1.y);  // 30
    
    return 0;
}
```

**Husk:** 
- `.` bruges på struct-variable
- `->` bruges på struct-pointere

## Structs i Funktioner

### Call by Value (Kopierer Hele Structen)

```c
typedef struct {
    int x;
    int y;
} Point;

void movePoint(Point p, int dx, int dy) {
    p.x += dx;
    p.y += dy;
    printf("Inde i funktion: (%d, %d)\n", p.x, p.y);
}

int main() {
    Point p1 = {10, 20};
    movePoint(p1, 5, 5);  // (15, 25) inde i funktion
    printf("I main: (%d, %d)\n", p1.x, p1.y);  // (10, 20) uændret!
    return 0;
}
```

**Problem:** Kopierer hele structen - kan være langsomt for store structs!

### Call by Reference (Med Pointer)

```c
void movePoint(Point *p, int dx, int dy) {
    p->x += dx;
    p->y += dy;
}

int main() {
    Point p1 = {10, 20};
    movePoint(&p1, 5, 5);
    printf("(%d, %d)\n", p1.x, p1.y);  // (15, 25) ændret!
    return 0;
}
```

**Fordel:** Hurtigere, ændrer original, ingen kopiering.

### Returnere Struct fra Funktion

```c
typedef struct {
    int x;
    int y;
} Point;

Point createPoint(int x, int y) {
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

Point addPoints(Point p1, Point p2) {
    Point result;
    result.x = p1.x + p2.x;
    result.y = p1.y + p2.y;
    return result;
}

int main() {
    Point a = createPoint(5, 10);
    Point b = createPoint(3, 7);
    Point c = addPoints(a, b);
    
    printf("(%d, %d)\n", c.x, c.y);  // (8, 17)
    return 0;
}
```

### Best Practice: Const Pointer for Store Structs

```c
typedef struct {
    char navn[100];
    int data[1000];
    double mere_data[500];
} BigStruct;

// DÅRLIGT - kopierer alt!
void process(BigStruct s) {
    // ...
}

// GODT - sender pointer, beskytter med const
void process(const BigStruct *s) {
    printf("%s\n", s->navn);
    // s->navn[0] = 'X';  // FEJL - const beskytter!
}

int main() {
    BigStruct big;
    strcpy(big.navn, "Test");
    process(&big);  // Hurtig, sikker
    return 0;
}
```

## Nested Structs (Indlejrede Strukturer)

```c
typedef struct {
    int dag;
    int maaned;
    int aar;
} Dato;

typedef struct {
    char navn[50];
    int alder;
    Dato fodselsdag;  // Struct inde i struct!
} Person;

int main() {
    Person p1;
    strcpy(p1.navn, "Anna");
    p1.alder = 25;
    
    // Tilgang til nested struct
    p1.fodselsdag.dag = 15;
    p1.fodselsdag.maaned = 6;
    p1.fodselsdag.aar = 1999;
    
    printf("%s er født %d/%d/%d\n", 
           p1.navn, 
           p1.fodselsdag.dag, 
           p1.fodselsdag.maaned, 
           p1.fodselsdag.aar);
    
    return 0;
}
```

### Med Pointer

```c
Person *ptr = &p1;
printf("%d\n", ptr->fodselsdag.dag);  // 15

// IKKE: ptr->fodselsdag->dag
// fordi fodselsdag IKKE er en pointer!
```

## Arrays af Structs

```c
typedef struct {
    int id;
    char navn[50];
    float karakter;
} Student;

int main() {
    Student klasse[3] = {
        {101, "Anna", 8.5},
        {102, "Peter", 9.0},
        {103, "Marie", 7.5}
    };
    
    // Print alle studerende
    for (int i = 0; i < 3; i++) {
        printf("ID: %d, Navn: %s, Karakter: %.1f\n",
               klasse[i].id,
               klasse[i].navn,
               klasse[i].karakter);
    }
    
    // Find bedste studerende
    int bestIndex = 0;
    for (int i = 1; i < 3; i++) {
        if (klasse[i].karakter > klasse[bestIndex].karakter) {
            bestIndex = i;
        }
    }
    
    printf("\nBedste studerende: %s med %.1f\n",
           klasse[bestIndex].navn,
           klasse[bestIndex].karakter);
    
    return 0;
}
```

## Dynamiske Structs

### Allokere Enkelt Struct

```c
typedef struct {
    int id;
    char navn[50];
} Person;

int main() {
    // Allokér en person
    Person *p = (Person*)malloc(sizeof(Person));
    
    if (p == NULL) {
        printf("Hukommelsen kunne ikke allokeres!\n");
        return 1;
    }
    
    // Brug arrow operator på pointer
    p->id = 1;
    strcpy(p->navn, "Anna");
    
    printf("%d: %s\n", p->id, p->navn);
    
    free(p);
    return 0;
}
```

### Allokere Array af Structs

```c
int main() {
    int antal = 5;
    Student *studerende = (Student*)malloc(antal * sizeof(Student));
    
    if (studerende == NULL) {
        printf("Fejl!\n");
        return 1;
    }
    
    // Fyld array
    for (int i = 0; i < antal; i++) {
        studerende[i].id = i + 1;
        sprintf(studerende[i].navn, "Student%d", i + 1);
        studerende[i].karakter = 7.0 + i * 0.5;
    }
    
    // Print
    for (int i = 0; i < antal; i++) {
        printf("%d: %s - %.1f\n",
               studerende[i].id,
               studerende[i].navn,
               studerende[i].karakter);
    }
    
    free(studerende);
    return 0;
}
```

## Struct med Pointer-Medlemmer

```c
typedef struct {
    char *navn;  // Pointer til dynamisk string
    int *scores;  // Pointer til dynamisk array
    int antalScores;
} Player;

int main() {
    Player p1;
    
    // Allokér plads til navn
    p1.navn = (char*)malloc(50 * sizeof(char));
    strcpy(p1.navn, "Anna");
    
    // Allokér plads til scores
    p1.antalScores = 5;
    p1.scores = (int*)malloc(p1.antalScores * sizeof(int));
    
    for (int i = 0; i < p1.antalScores; i++) {
        p1.scores[i] = (i + 1) * 100;
    }
    
    // Print
    printf("Spiller: %s\n", p1.navn);
    printf("Scores: ");
    for (int i = 0; i < p1.antalScores; i++) {
        printf("%d ", p1.scores[i]);
    }
    printf("\n");
    
    // Frigør BEGGE allokeringer!
    free(p1.navn);
    free(p1.scores);
    
    return 0;
}
```

## Linked List med Structs (Vigtig!)

```c
typedef struct Node {
    int data;
    struct Node *next;  // Pointer til næste node
} Node;

// Opret ny node
Node* createNode(int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Print liste
void printList(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    // Opret liste: 10 -> 20 -> 30
    Node *head = createNode(10);
    head->next = createNode(20);
    head->next->next = createNode(30);
    
    printList(head);  // 10 -> 20 -> 30 -> NULL
    
    // Frigør hukommelse (vigtigt!)
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    
    return 0;
}
```

## Struct Kopiering

### Shallow Copy (Overfladisk)

```c
typedef struct {
    int x;
    int y;
} Point;

int main() {
    Point p1 = {10, 20};
    Point p2 = p1;  // Shallow copy - virker fint for simple structs
    
    p2.x = 30;
    printf("p1: (%d, %d)\n", p1.x, p1.y);  // (10, 20)
    printf("p2: (%d, %d)\n", p2.x, p2.y);  // (30, 20)
    
    return 0;
}
```

### Deep Copy (Dyb) - Nødvendig med Pointere

```c
typedef struct {
    char *navn;
    int alder;
} Person;

Person* deepCopy(Person *original) {
    Person *copy = (Person*)malloc(sizeof(Person));
    
    // Kopier string ordentligt
    copy->navn = (char*)malloc(strlen(original->navn) + 1);
    strcpy(copy->navn, original->navn);
    
    copy->alder = original->alder;
    
    return copy;
}

int main() {
    Person p1;
    p1.navn = (char*)malloc(50);
    strcpy(p1.navn, "Anna");
    p1.alder = 25;
    
    Person *p2 = deepCopy(&p1);
    
    // Ændringer i p2 påvirker ikke p1
    strcpy(p2->navn, "Peter");
    p2->alder = 30;
    
    printf("p1: %s, %d\n", p1.navn, p1.alder);  // Anna, 25
    printf("p2: %s, %d\n", p2->navn, p2->alder);  // Peter, 30
    
    free(p1.navn);
    free(p2->navn);
    free(p2);
    
    return 0;
}
```

## Unions (Bonus Koncept)

En union ligner en struct, men alle medlemmer **deler samme hukommelse**.

```c
typedef union {
    int i;
    float f;
    char c;
} Data;

int main() {
    Data d;
    
    d.i = 10;
    printf("i: %d\n", d.i);  // 10
    
    d.f = 3.14;  // OVERSKRIVER d.i!
    printf("f: %f\n", d.f);  // 3.14
    printf("i: %d\n", d.i);  // Ugyldigt/korrupt!
    
    printf("Størrelse: %lu\n", sizeof(Data));  
    // Størrelse af største medlem (float = 4 bytes)
    
    return 0;
}
```

**Brug:** Når du kun behøver ÉN værdi ad gangen (spare hukommelse).

## Praktiske Eksempler

### Eksempel 1: Student Database

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int id;
    char navn[50];
    float karakterer[5];
    float gennemsnit;
} Student;

float beregnGennemsnit(float karakterer[], int antal) {
    float sum = 0;
    for (int i = 0; i < antal; i++) {
        sum += karakterer[i];
    }
    return sum / antal;
}

void printStudent(const Student *s) {
    printf("\n--- Student Info ---\n");
    printf("ID: %d\n", s->id);
    printf("Navn: %s\n", s->navn);
    printf("Karakterer: ");
    for (int i = 0; i < 5; i++) {
        printf("%.1f ", s->karakterer[i]);
    }
    printf("\nGennemsnit: %.2f\n", s->gennemsnit);
}

int main() {
    Student s1 = {
        .id = 101,
        .navn = "Anna Hansen",
        .karakterer = {7.0, 8.5, 9.0, 8.0, 7.5}
    };
    
    s1.gennemsnit = beregnGennemsnit(s1.karakterer, 5);
    printStudent(&s1);
    
    return 0;
}
```

### Eksempel 2: Geometriske Figurer

```c
typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point center;
    double radius;
} Circle;

typedef struct {
    Point topLeft;
    double width;
    double height;
} Rectangle;

double circleArea(const Circle *c) {
    return 3.14159 * c->radius * c->radius;
}

double rectangleArea(const Rectangle *r) {
    return r->width * r->height;
}

int pointInsideCircle(const Point *p, const Circle *c) {
    double dx = p->x - c->center.x;
    double dy = p->y - c->center.y;
    double distSquared = dx*dx + dy*dy;
    return distSquared <= c->radius * c->radius;
}

int main() {
    Circle c1 = {{0, 0}, 5.0};
    Rectangle r1 = {{-2, 2}, 4.0, 3.0};
    Point p1 = {3, 4};
    
    printf("Cirkel areal: %.2f\n", circleArea(&c1));
    printf("Rektangel areal: %.2f\n", rectangleArea(&r1));
    
    if (pointInsideCircle(&p1, &c1)) {
        printf("Punkt (%.0f,%.0f) er inde i cirklen\n", p1.x, p1.y);
    } else {
        printf("Punkt (%.0f,%.0f) er udenfor cirklen\n", p1.x, p1.y);
    }
    
    return 0;
}
```

### Eksempel 3: Simple Inventory System

```c
typedef struct {
    int id;
    char navn[50];
    int antal;
    double pris;
} Vare;

typedef struct {
    Vare *varer;
    int antal;
    int kapacitet;
} Lager;

Lager* opretLager(int kapacitet) {
    Lager *l = (Lager*)malloc(sizeof(Lager));
    l->varer = (Vare*)malloc(kapacitet * sizeof(Vare));
    l->antal = 0;
    l->kapacitet = kapacitet;
    return l;
}

void tilfoejVare(Lager *l, int id, const char *navn, int antal, double pris) {
    if (l->antal < l->kapacitet) {
        Vare *v = &l->varer[l->antal];
        v->id = id;
        strcpy(v->navn, navn);
        v->antal = antal;
        v->pris = pris;
        l->antal++;
    }
}

void printLager(const Lager *l) {
    printf("\n=== Lager Oversigt ===\n");
    printf("ID   Navn           Antal   Pris\n");
    printf("-----------------------------------\n");
    for (int i = 0; i < l->antal; i++) {
        printf("%-4d %-15s %-7d %.2f kr\n",
               l->varer[i].id,
               l->varer[i].navn,
               l->varer[i].antal,
               l->varer[i].pris);
    }
}

void frigLager(Lager *l) {
    free(l->varer);
    free(l);
}

int main() {
    Lager *mineLager = opretLager(10);
    
    tilfoejVare(mineLager, 1, "Blyant", 50, 5.50);
    tilfoejVare(mineLager, 2, "Notesbog", 20, 25.00);
    tilfoejVare(mineLager, 3, "Viskelæder", 30, 3.00);
    
    printLager(mineLager);
    
    frigLager(mineLager);
    return 0;
}
```

## Almindelige Fejl

### Fejl 1: Glemme & ved Scanf

```c
typedef struct {
    int x;
} Point;

int main() {
    Point p;
    
    // FORKERT:
    // scanf("%d", p.x);
    
    // RIGTIGT:
    scanf("%d", &p.x);
    
    return 0;
}
```

### Fejl 2: Forvirring mellem . og ->

```c
Point p1 = {10, 20};
Point *ptr = &p1;

// FORKERT:
// ptr.x = 30;

// RIGTIGT:
ptr->x = 30;
// ELLER:
(*ptr).x = 30;
```

### Fejl 3: Ikke Frigive Dynamisk Hukommelse

```c
// FORKERT - memory leak!
void badFunction() {
    Person *p = (Person*)malloc(sizeof(Person));
    // Bruger p...
    // Glemmer free(p)!
}

// RIGTIGT:
void goodFunction() {
    Person *p = (Person*)malloc(sizeof(Person));
    // Bruger p...
    free(p);
}
```

## Cheat Sheet

### Parametre

| Type | Notation | Ændringer Påvirker Original? |
|------|----------|------------------------------|
| Call by Value | `void func(int x)` | Nej |
| Call by Reference | `void func(int *x)` | Ja |
| Array | `void func(int arr[])` | Ja (altid reference) |
| Struct by Value | `void func(Person p)` | Nej (kopieres) |
| Struct by Reference | `void func(Person *p)` | Ja |
| Const Parameter | `void func(const int *x)` | Nej (beskyttet) |

### Structs

| Operation | Notation | Eksempel |
|-----------|----------|----------|
| Definition | `struct Name { ... };` | `struct Point { int x, y; };` |
| Typedef | `typedef struct { ... } Name;` | `typedef struct { int x, y; } Point;` |
| Deklaration | `struct Name var;` eller `Name var;` | `Point p1;` |
| Member Access | `var.member` | `p1.x = 10;` |
| Pointer Access | `ptr->member` | `ptr->x = 10;` |
| Initialisering | `{val1, val2, ...}` | `Point p = {10, 20};` |

## Eksamenstips

### Parametre
1. **Husk &-tegnet:** Når du kalder en funktion med pointer-parametre, send adressen: `func(&var)`
2. **Arrays behøver ikke &:** Array-navn er allerede en pointer: `func(arr)`
3. **Størrelse skal sendes separat:** Arrays "glemmer" deres størrelse i funktioner
4. **Const for beskyttelse:** Brug `const` hvis funktionen ikke skal ændre data
5. **Stor struct = pointer:** Send store structs som pointere for at spare hukommelse

### Structs
1. **Dot vs Arrow:** `.` for variable, `->` for pointere
2. **Typedef gør det lettere:** Undgå at skrive "struct" hele tiden
3. **Nested structs:** Brug flere dots: `person.fodselsdag.dag`
4. **Dynamisk allokering:** Husk at frigive med `free()` 
5. **Deep copy med pointere:** Kopier også det som pointer-medlemmer peger på
6. **Linked lists:** Struct kan indeholde pointer til sig selv: `struct Node *next;`
7. **Always initialize:** Uninitialiserede struct-medlemmer har tilfældige værdier

## Quick Reference til Eksamen

### Hvornår bruges Call by Reference?
- Når funktionen skal **ændre** den originale variabel
- Når du vil **returnere flere værdier**
- Når struct/array er **stor** og du vil undgå kopiering

### Hvornår bruges Structs?
- Når du har **relaterede data** af forskellige typer
- Når du vil **gruppere information** (f.eks. Person = navn + alder + adresse)
- Når du bygger **data strukturer** (linked lists, trees, etc.)
- For at gøre kode mere **organiseret og læsbar**

## Avanceret: Struct med Funktions-Pointere

```c
typedef struct {
    double (*beregn)(double, double);
    char operator;
} Operation;

double add(double a, double b) { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }

int main() {
    Operation ops[] = {
        {add, '+'},
        {subtract, '-'},
        {multiply, '*'}
    };
    
    double a = 10, b = 5;
    
    for (int i = 0; i < 3; i++) {
        printf("%.1f %c %.1f = %.1f\n", 
               a, ops[i].operator, b, 
               ops[i].beregn(a, b));
    }
    // Output:
    // 10.0 + 5.0 = 15.0
    // 10.0 - 5.0 = 5.0
    // 10.0 * 5.0 = 50.0
    
    return 0;
}
```

## Komplekst Eksempel: Simpelt University System

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int id;
    char navn[50];
    float karakter;
} Student;

typedef struct {
    char navn[50];
    Student *studerende;
    int antalStuderende;
    int kapacitet;
} Kursus;

// Opret nyt kursus
Kursus* opretKursus(const char *navn, int kapacitet) {
    Kursus *k = (Kursus*)malloc(sizeof(Kursus));
    strcpy(k->navn, navn);
    k->studerende = (Student*)malloc(kapacitet * sizeof(Student));
    k->antalStuderende = 0;
    k->kapacitet = kapacitet;
    return k;
}

// Tilføj studerende til kursus
int tilfoejStuderende(Kursus *k, int id, const char *navn, float karakter) {
    if (k->antalStuderende >= k->kapacitet) {
        printf("Kursus er fuldt!\n");
        return 0;
    }
    
    Student *s = &k->studerende[k->antalStuderende];
    s->id = id;
    strcpy(s->navn, navn);
    s->karakter = karakter;
    k->antalStuderende++;
    
    return 1;
}

// Find studerende efter ID
Student* findStuderende(const Kursus *k, int id) {
    for (int i = 0; i < k->antalStuderende; i++) {
        if (k->studerende[i].id == id) {
            return &k->studerende[i];
        }
    }
    return NULL;
}

// Beregn gennemsnit for kurset
float kursusGennemsnit(const Kursus *k) {
    if (k->antalStuderende == 0) return 0.0;
    
    float sum = 0;
    for (int i = 0; i < k->antalStuderende; i++) {
        sum += k->studerende[i].karakter;
    }
    return sum / k->antalStuderende;
}

// Find bedste studerende
Student* findBedsteStuderende(const Kursus *k) {
    if (k->antalStuderende == 0) return NULL;
    
    Student *bedst = &k->studerende[0];
    for (int i = 1; i < k->antalStuderende; i++) {
        if (k->studerende[i].karakter > bedst->karakter) {
            bedst = &k->studerende[i];
        }
    }
    return bedst;
}

// Print kursus info
void printKursus(const Kursus *k) {
    printf("\n========== %s ==========\n", k->navn);
    printf("Antal studerende: %d/%d\n\n", k->antalStuderende, k->kapacitet);
    
    printf("ID    Navn                Karakter\n");
    printf("-------------------------------------\n");
    for (int i = 0; i < k->antalStuderende; i++) {
        printf("%-5d %-20s %.1f\n",
               k->studerende[i].id,
               k->studerende[i].navn,
               k->studerende[i].karakter);
    }
    
    printf("\nKursus gennemsnit: %.2f\n", kursusGennemsnit(k));
    
    Student *bedst = findBedsteStuderende(k);
    if (bedst != NULL) {
        printf("Bedste studerende: %s (%.1f)\n", bedst->navn, bedst->karakter);
    }
}

// Frigør kursus
void frigKursus(Kursus *k) {
    free(k->studerende);
    free(k);
}

int main() {
    // Opret kursus
    Kursus *programmering = opretKursus("Programmering 1", 5);
    
    // Tilføj studerende
    tilfoejStuderende(programmering, 101, "Anna Hansen", 8.5);
    tilfoejStuderende(programmering, 102, "Peter Nielsen", 9.0);
    tilfoejStuderende(programmering, 103, "Marie Jensen", 7.5);
    tilfoejStuderende(programmering, 104, "Lars Andersen", 8.0);
    
    // Print kursus
    printKursus(programmering);
    
    // Søg efter studerende
    printf("\n--- Søgning ---\n");
    Student *fundet = findStuderende(programmering, 102);
    if (fundet != NULL) {
        printf("Fandt studerende: %s med karakter %.1f\n", 
               fundet->navn, fundet->karakter);
    }
    
    // Opdater karakter
    fundet->karakter = 10.0;
    printf("Opdateret karakter til: %.1f\n", fundet->karakter);
    
    // Print opdateret kursus
    printKursus(programmering);
    
    // Ryd op
    frigKursus(programmering);
    
    return 0;
}
```

## Test Din Forståelse

### Quiz 1: Parametre
```c
void mystery(int a, int *b, int arr[]) {
    a = 10;
    *b = 20;
    arr[0] = 30;
}

int main() {
    int x = 1, y = 2, z[3] = {3, 4, 5};
    mystery(x, &y, z);
    printf("%d %d %d\n", x, y, z[0]);
    // Hvad printes? → 1 20 30
    return 0;
}
```

### Quiz 2: Structs
```c
typedef struct {
    int x;
    int *y;
} Test;

int main() {
    int val = 100;
    Test t1 = {10, &val};
    Test t2 = t1;  // Shallow copy
    
    t2.x = 20;
    *(t2.y) = 200;
    
    printf("%d %d %d\n", t1.x, *(t1.y), val);
    // Hvad printes? → 10 200 200
    // x er kopieret (uafhængig)
    // y peger på samme adresse (delt!)
    return 0;
}
```

### Quiz 3: Nested Structs og Pointere
```c
typedef struct {
    int dag;
} Dato;

typedef struct {
    Dato *d;
} Person;

int main() {
    Dato dato = {15};
    Person p1 = {&dato};
    
    p1.d->dag = 25;
    
    printf("%d\n", dato.dag);
    // Hvad printes? → 25
    return 0;
}
```

## Sidste Råd til Eksamen

1. **Tegn hukommelsen!** Især for pointere og structs - visualiser hvad der sker.

2. **Følg data-flowet:** Når en funktion kaldes, følg værdier ind og ud.

3. **Check pointer-typer:** Er det `Point` eller `Point*`? Det afgør om du bruger `.` eller `->`.

4. **Husk frigivelse:** Hver `malloc()` skal matches med en `free()`.

5. **Struct-kopiering:** Simple structs kan kopieres direkte. Med pointere skal du lave deep copy.

6. **Array = pointer i funktioner:** Arrays "forfremmes" til pointere når de sendes til funktioner.

7. **Const er din ven:** Beskyt data der ikke skal ændres og få compileren til at hjælpe.

8. **Læs opgaven grundigt:** Er der tale om call-by-value eller call-by-reference? Små detaljer betyder alt!

God forberedelse til eksamen! Du klarer det! 🎯🚀