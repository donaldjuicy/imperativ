# C Arrays - Komplet Eksamensguide

## Hvad er et Array?

Et array er en samling af elementer af **samme type**, gemt i sammenhængende hukommelse. Tænk på det som en række bokse ved siden af hinanden, hver med et nummer (index).

```c
int tal[5];  // 5 integer-bokse ved siden af hinanden
```

## Grundlæggende Array-Syntax

### 1. Deklaration og Initialisering

```c
// Deklaration uden initialisering (tilfældige værdier!)
int arr1[5];

// Deklaration med initialisering
int arr2[5] = {10, 20, 30, 40, 50};

// Delvis initialisering (resten bliver 0)
int arr3[5] = {10, 20};  // {10, 20, 0, 0, 0}

// Alle elementer til 0
int arr4[5] = {0};  // {0, 0, 0, 0, 0}

// Størrelse beregnes automatisk
int arr5[] = {1, 2, 3, 4};  // Størrelse er 4

// Multi-dimensionelle arrays
int matrix[3][4];  // 3 rækker, 4 kolonner
```

### 2. Tilgang til Array-Elementer

```c
int tal[5] = {10, 20, 30, 40, 50};

// Læsning
printf("%d\n", tal[0]);  // 10 (første element)
printf("%d\n", tal[4]);  // 50 (sidste element)

// Skrivning
tal[0] = 100;
tal[2] = tal[1] + tal[3];  // 20 + 40 = 60

// FARLIGT - out of bounds!
// tal[5] = 60;  // Fejl! Index går fra 0 til 4
```

**Vigtigt:** Arrays bruger 0-baseret indeksering. Et array med 5 elementer har indeks 0, 1, 2, 3, 4.

### 3. Array-Størrelse

```c
int arr[10];

int size = sizeof(arr) / sizeof(arr[0]);
printf("Array har %d elementer\n", size);  // 10

// sizeof(arr) = 40 bytes (10 * 4 bytes per int)
// sizeof(arr[0]) = 4 bytes (en int)
// 40 / 4 = 10 elementer
```

## Alle Array-Operationer med Eksempler

### 1. Gennemløb af Arrays (Loops)

#### For-loop (mest almindelig)

```c
int tal[5] = {10, 20, 30, 40, 50};

// Print alle elementer
for (int i = 0; i < 5; i++) {
    printf("tal[%d] = %d\n", i, tal[i]);
}

// Med beregnet størrelse
int size = sizeof(tal) / sizeof(tal[0]);
for (int i = 0; i < size; i++) {
    printf("%d ", tal[i]);
}
```

#### While-loop

```c
int i = 0;
while (i < 5) {
    printf("%d ", tal[i]);
    i++;
}
```

### 2. Søgning i Arrays

#### Lineær Søgning

```c
int findElement(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;  // Returnerer index
        }
    }
    return -1;  // Ikke fundet
}

int main() {
    int tal[] = {10, 25, 30, 45, 50};
    int index = findElement(tal, 5, 30);
    
    if (index != -1) {
        printf("Fundet på index %d\n", index);  // Fundet på index 2
    } else {
        printf("Ikke fundet\n");
    }
    return 0;
}
```

#### Find Minimum/Maximum

```c
int findMin(int arr[], int size) {
    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int findMax(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int main() {
    int tal[] = {34, 12, 78, 23, 56};
    printf("Min: %d\n", findMin(tal, 5));  // 12
    printf("Max: %d\n", findMax(tal, 5));  // 78
    return 0;
}
```

### 3. Sortering

#### Bubble Sort (Simplest)

```c
void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int tal[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(tal) / sizeof(tal[0]);
    
    printf("Før sortering: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", tal[i]);
    }
    
    bubbleSort(tal, size);
    
    printf("\nEfter sortering: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", tal[i]);
    }
    // Output: 11 12 22 25 34 64 90
    
    return 0;
}
```

#### Selection Sort

```c
void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;
        
        // Find mindste element i usorteret del
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        
        // Swap mindste element med første usorteret element
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}
```

### 4. Reversere et Array

```c
void reverseArray(int arr[], int size) {
    int start = 0;
    int end = size - 1;
    
    while (start < end) {
        // Swap
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        
        start++;
        end--;
    }
}

int main() {
    int tal[] = {1, 2, 3, 4, 5};
    int size = sizeof(tal) / sizeof(tal[0]);
    
    reverseArray(tal, size);
    
    for (int i = 0; i < size; i++) {
        printf("%d ", tal[i]);  // 5 4 3 2 1
    }
    return 0;
}
```

### 5. Summere Elementer

```c
int sumArray(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

double averageArray(int arr[], int size) {
    return (double)sumArray(arr, size) / size;
}

int main() {
    int tal[] = {10, 20, 30, 40, 50};
    int size = 5;
    
    printf("Sum: %d\n", sumArray(tal, size));           // 150
    printf("Gennemsnit: %.2f\n", averageArray(tal, size));  // 30.00
    return 0;
}
```

### 6. Kopiere Arrays

```c
void copyArray(int source[], int dest[], int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = source[i];
    }
}

int main() {
    int original[] = {1, 2, 3, 4, 5};
    int kopi[5];
    
    copyArray(original, kopi, 5);
    
    // Modificer kopi
    kopi[0] = 100;
    
    printf("Original[0]: %d\n", original[0]);  // 1 (uændret)
    printf("Kopi[0]: %d\n", kopi[0]);          // 100
    
    return 0;
}
```

### 7. Sammenligne Arrays

```c
int arraysEqual(int arr1[], int arr2[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr1[i] != arr2[i]) {
            return 0;  // Ikke ens (false)
        }
    }
    return 1;  // Ens (true)
}

int main() {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {1, 2, 3, 4, 5};
    int c[] = {1, 2, 3, 4, 6};
    
    printf("%d\n", arraysEqual(a, b, 5));  // 1 (true)
    printf("%d\n", arraysEqual(a, c, 5));  // 0 (false)
    
    return 0;
}
```

### 8. Indsætte Element

```c
void insertElement(int arr[], int *size, int element, int position) {
    // Flyt elementer til højre
    for (int i = *size; i > position; i--) {
        arr[i] = arr[i - 1];
    }
    
    // Indsæt nyt element
    arr[position] = element;
    (*size)++;
}

int main() {
    int arr[10] = {10, 20, 30, 40, 50};
    int size = 5;
    
    insertElement(arr, &size, 25, 2);  // Indsæt 25 på position 2
    
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);  // 10 20 25 30 40 50
    }
    
    return 0;
}
```

### 9. Slette Element

```c
void deleteElement(int arr[], int *size, int position) {
    // Flyt elementer til venstre
    for (int i = position; i < *size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    (*size)--;
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    int size = 5;
    
    deleteElement(arr, &size, 2);  // Slet element på position 2 (30)
    
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);  // 10 20 40 50
    }
    
    return 0;
}
```

### 10. Rotere Array

```c
void rotateLeft(int arr[], int size) {
    int first = arr[0];
    for (int i = 0; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arr[size - 1] = first;
}

void rotateRight(int arr[], int size) {
    int last = arr[size - 1];
    for (int i = size - 1; i > 0; i--) {
        arr[i] = arr[i - 1];
    }
    arr[0] = last;
}

int main() {
    int tal[] = {1, 2, 3, 4, 5};
    
    rotateLeft(tal, 5);
    for (int i = 0; i < 5; i++) {
        printf("%d ", tal[i]);  // 2 3 4 5 1
    }
    
    printf("\n");
    
    rotateRight(tal, 5);
    for (int i = 0; i < 5; i++) {
        printf("%d ", tal[i]);  // 1 2 3 4 5
    }
    
    return 0;
}
```

## Character Arrays (Strings)

### String Basics

```c
// Metode 1: Character array
char str1[6] = {'H', 'e', 'l', 'l', 'o', '\0'};

// Metode 2: String literal (lettere)
char str2[] = "Hello";  // Automatisk \0 tilføjet

// Metode 3: Fixed size
char str3[20] = "Hello";  // Resten fyldes med \0
```

### String Input/Output

```c
char navn[50];

// Input
printf("Indtast dit navn: ");
scanf("%s", navn);  // BEMÆRK: Ingen & foran array-navn!

// Eller med fgets (bedre - læser mellemrum)
fgets(navn, sizeof(navn), stdin);

// Output
printf("Hej, %s!\n", navn);
```

### String-Funktioner

```c
#include <string.h>

char str1[20] = "Hello";
char str2[20] = "World";
char str3[20];

// Længde
int len = strlen(str1);  // 5

// Kopiere
strcpy(str3, str1);  // str3 = "Hello"

// Sammenkædning
strcat(str1, str2);  // str1 = "HelloWorld"

// Sammenligning
if (strcmp(str1, str2) == 0) {
    printf("Strings er ens\n");
}
// < 0 hvis str1 < str2
// > 0 hvis str1 > str2
// == 0 hvis str1 == str2
```

### Manuel String-Operationer

```c
// Manuel strlen
int myStrlen(char str[]) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

// Manuel strcpy
void myStrcpy(char dest[], char src[]) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Manuel strcmp
int myStrcmp(char str1[], char str2[]) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}
```

## Multi-Dimensionelle Arrays

### 2D Arrays (Matricer)

```c
// Deklaration og initialisering
int matrix[3][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
};

// Tilgang til elementer
printf("%d\n", matrix[0][0]);  // 1
printf("%d\n", matrix[2][3]);  // 12

// Gennemløb med nested loops
for (int i = 0; i < 3; i++) {       // Rækker
    for (int j = 0; j < 4; j++) {   // Kolonner
        printf("%d ", matrix[i][j]);
    }
    printf("\n");
}
```

### 2D Array Operationer

#### Print Matrix

```c
void printMatrix(int rows, int cols, int matrix[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}
```

#### Matrix Addition

```c
void addMatrices(int rows, int cols, 
                 int a[rows][cols], 
                 int b[rows][cols], 
                 int result[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

int main() {
    int a[2][2] = {{1, 2}, {3, 4}};
    int b[2][2] = {{5, 6}, {7, 8}};
    int result[2][2];
    
    addMatrices(2, 2, a, b, result);
    
    printMatrix(2, 2, result);
    // 6  8
    // 10 12
    
    return 0;
}
```

#### Matrix Multiplikation

```c
void multiplyMatrices(int r1, int c1, int a[r1][c1],
                      int r2, int c2, int b[r2][c2],
                      int result[r1][c2]) {
    // c1 skal være lig med r2!
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < c1; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}
```

#### Transponere Matrix

```c
void transpose(int rows, int cols, 
               int matrix[rows][cols], 
               int result[cols][rows]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][i] = matrix[i][j];
        }
    }
}

int main() {
    int m[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int t[3][2];
    
    transpose(2, 3, m, t);
    
    printMatrix(3, 2, t);
    // 1 4
    // 2 5
    // 3 6
    
    return 0;
}
```

### 3D Arrays

```c
// 3D array: [layers][rows][cols]
int cube[2][3][4] = {
    {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    },
    {
        {13, 14, 15, 16},
        {17, 18, 19, 20},
        {21, 22, 23, 24}
    }
};

// Gennemløb
for (int i = 0; i < 2; i++) {
    printf("Layer %d:\n", i);
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 4; k++) {
            printf("%d ", cube[i][j][k]);
        }
        printf("\n");
    }
    printf("\n");
}
```

## Arrays og Pointere

### Array-Pointer Relation

```c
int arr[5] = {10, 20, 30, 40, 50};

// Disse er ækvivalente:
printf("%d\n", arr[0]);    // 10
printf("%d\n", *arr);      // 10
printf("%d\n", *(arr+0));  // 10

printf("%d\n", arr[2]);    // 30
printf("%d\n", *(arr+2));  // 30

// Array-navn er en konstant pointer til første element
int *p = arr;  // OK
// arr = p;    // FEJL! Kan ikke ændre array-navn
```

### Gennemløb med Pointer

```c
int arr[] = {10, 20, 30, 40, 50};
int *ptr;

// Metode 1
for (ptr = arr; ptr < arr + 5; ptr++) {
    printf("%d ", *ptr);
}

// Metode 2
for (int i = 0; i < 5; i++) {
    printf("%d ", *(arr + i));
}
```

## Arrays og Funktioner

### Sende Array til Funktion

```c
// Metode 1: Med størrelse som parameter
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Metode 2: Med pointer notation
void printArray2(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Metode 3: Fixed size (sjældent brugt)
void printArray3(int arr[10]) {
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int tal[] = {1, 2, 3, 4, 5};
    printArray(tal, 5);   // Alle tre virker
    printArray2(tal, 5);
    
    return 0;
}
```

**Vigtigt:** Arrays sendes altid som reference (pointer). Ændringer inde i funktionen påvirker det originale array!

```c
void modifyArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;  // Doubler hvert element
    }
}

int main() {
    int tal[] = {1, 2, 3, 4, 5};
    
    modifyArray(tal, 5);
    
    for (int i = 0; i < 5; i++) {
        printf("%d ", tal[i]);  // 2 4 6 8 10 (ændret!)
    }
    
    return 0;
}
```

### Returnere Array fra Funktion

```c
// FORKERT - returnerer pointer til lokal variabel!
int* wrongFunction() {
    int arr[5] = {1, 2, 3, 4, 5};
    return arr;  // FARLIGT!
}

// RIGTIGT - Brug malloc
int* createArray(int size) {
    int *arr = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        arr[i] = i + 1;
    }
    return arr;
}

int main() {
    int *dynamicArr = createArray(5);
    for (int i = 0; i < 5; i++) {
        printf("%d ", dynamicArr[i]);
    }
    free(dynamicArr);  // Husk at frigive!
    
    return 0;
}

// ELLER - Modificer array sendt som parameter
void fillArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i * 10;
    }
}

int main() {
    int arr[5];
    fillArray(arr, 5);
    // Nu er arr fyldt med værdier
    
    return 0;
}
```

## Dynamiske Arrays

```c
#include <stdlib.h>

int main() {
    int size;
    printf("Hvor mange elementer? ");
    scanf("%d", &size);
    
    // Allokér hukommelse
    int *arr = (int*)malloc(size * sizeof(int));
    
    if (arr == NULL) {
        printf("Hukommelsen kunne ikke allokeres!\n");
        return 1;
    }
    
    // Brug arrayet
    for (int i = 0; i < size; i++) {
        arr[i] = i * 10;
    }
    
    // Print
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    
    // Frigør hukommelse
    free(arr);
    arr = NULL;
    
    return 0;
}
```

### Realloc - Ændre Array Størrelse

```c
int *arr = (int*)malloc(5 * sizeof(int));

// Fyld array
for (int i = 0; i < 5; i++) {
    arr[i] = i + 1;
}

// Øg størrelse til 10
arr = (int*)realloc(arr, 10 * sizeof(int));

// Fyld nye elementer
for (int i = 5; i < 10; i++) {
    arr[i] = i + 1;
}

free(arr);
```

## Almindelige Array-Fejl

### Fejl 1: Out of Bounds

```c
int arr[5] = {1, 2, 3, 4, 5};

// FARLIGT - udefineret opførsel!
arr[5] = 10;   // Index 5 eksisterer ikke (0-4)
arr[-1] = 20;  // Negativ index
```

### Fejl 2: Glemme \0 i Strings

```c
char str[5] = {'H', 'e', 'l', 'l', 'o'};  // FARLIGT!
printf("%s\n", str);  // Læser forbi array!

// RIGTIGT:
char str[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
// ELLER:
char str[] = "Hello";  // Automatisk \0
```

### Fejl 3: sizeof i Funktioner

```c
void printSize(int arr[]) {
    int size = sizeof(arr) / sizeof(arr[0]);  // FORKERT!
    printf("%d\n", size);  // Giver forkert resultat
    // sizeof(arr) er størrelsen af en pointer, ikke arrayet!
}

int main() {
    int arr[10];
    int size = sizeof(arr) / sizeof(arr[0]);  // RIGTIGT her!
    printf("%d\n", size);  // 10
    
    printSize(arr);  // Giver forkert resultat
    
    return 0;
}
```

### Fejl 4: Array Sammenligning

```c
int arr1[] = {1, 2, 3};
int arr2[] = {1, 2, 3};

if (arr1 == arr2) {  // FORKERT! Sammenligner pointere, ikke værdier
    printf("Ens\n");
}

// RIGTIGT - sammenlign element for element
int equal = 1;
for (int i = 0; i < 3; i++) {
    if (arr1[i] != arr2[i]) {
        equal = 0;
        break;
    }
}
```

## Praktiske Eksempler

### Histogram

```c
void printHistogram(int data[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%2d: ", data[i]);
        for (int j = 0; j < data[i]; j++) {
            printf("*");
        }
        printf("\n");
    }
}

int main() {
    int scores[] = {5, 3, 8, 2, 7};
    printHistogram(scores, 5);
    /*
     5: *****
     3: ***
     8: ********
     2: **
     7: *******
    */
    return 0;
}
```

### Fjerne Dubletter

```c
int removeDuplicates(int arr[], int size) {
    int newSize = 0;
    
    for (int i = 0; i < size; i++) {
        int isDuplicate = 0;
        
        // Check om elementet allerede er i "nye" delen
        for (int j = 0; j < newSize; j++) {
            if (arr[i] == arr[j]) {
                isDuplicate = 1;
                break;
            }
        }
        
        if (!isDuplicate) {
            arr[newSize] = arr[i];
            newSize++;
        }
    }
    
    return newSize;
}

int main() {
    int arr[] = {1, 2, 3, 2, 4, 1, 5, 3};
    int size = 8;
    
    size = removeDuplicates(arr, size);
    
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);  // 1 2 3 4 5
    }
    
    return 0;
}
```

## Array Cheat Sheet

| Operation | Kode | Kompleksitet |
|-----------|------|--------------|
| Deklaration | `int arr[10];` | - |
| Initialisering | `int arr[] = {1,2,3};` | - |
| Tilgang | `arr[i]` | O(1) |
| Søgning | Loop gennem array | O(n) |
| Sortering | Bubble/Selection sort | O(n²) |
| Reversering | Swap fra begge ender | O(n) |
| Kopiering | Loop element-for-element | O(n) |
| Indsættelse | Flyt elementer til højre | O(n) |
| Sletning | Flyt elementer til venstre | O(n) |

## Eksamenstips

1. **Husk 0-indeksering:** Første element er arr[0], sidste er arr[size-1]

2. **sizeof trick:** `int size = sizeof(arr) / sizeof(arr[0]);` virker kun i samme scope som deklarationen!

3. **Arrays er pointere:** Når du sender et array til en funktion, sendes en pointer. Ændringer påvirker originalen.

4. **Strings skal ende med \0:** Altid husk null-terminatoren i character arrays.

5. **Bounds checking:** C checker ikke array bounds automatisk - det er dit ansvar!

6. **2D arrays i funktioner:** Kun første dimension kan udelades: `void func(int arr[][4], int rows)`

7. **Dynamisk hukommelse:** Husk altid at frigive med `free()` det du allokerer med `malloc()`

God forberedelse til eksamen! 🎯