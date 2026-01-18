# Comprehensive C Programming Notes

## Table of Contents
1. [Pointers](#1-pointers)
2. [Arrays](#2-arrays)
3. [Memory Allocation](#3-memory-allocation)
4. [Linked Lists](#4-linked-lists)
5. [Recursion](#5-recursion)
6. [Structs](#6-structs)

---

## 1. POINTERS

### 1.1 Fundamental Concepts

**What is a Pointer?**
- A variable that stores a memory address
- Size depends on system architecture (4 bytes on 32-bit, 8 bytes on 64-bit)
- Can point to any data type

**Declaration Syntax Variations:**
```c
int *p1;           // pointer to int
int* p2;           // same (style preference)
int * p3;          // same (style preference)
int *p4, *p5;      // two pointers
int* p6, p7;       // p6 is pointer, p7 is int (CAREFUL!)
```

**Key Operators:**
- `&` (address-of): Gets the memory address of a variable
- `*` (dereference): Accesses the value at a memory address

### 1.2 Pointer Initialization and NULL

```c
int x = 10;
int *p1 = &x;        // Initialized pointer
int *p2;             // Uninitialized (DANGEROUS - wild pointer)
int *p3 = NULL;      // Null pointer (safe initialization)
int *p4 = 0;         // Same as NULL

// Modern C (since C23)
int *p5 = nullptr;   // C23 standard

// Checking for NULL
if (p3 == NULL) {
    printf("Pointer is null\n");
}

// Dereferencing NULL causes undefined behavior (usually crash)
// *p3 = 5;  // CRASH!
```

### 1.3 Pointer Arithmetic

**Rules:**
- Adding to a pointer moves it by `n * sizeof(type)` bytes
- Subtracting pointers gives the number of elements between them
- Only works with pointers of the same type

```c
int arr[5] = {10, 20, 30, 40, 50};
int *p = arr;

// Pointer addition
printf("%d\n", *p);       // 10
printf("%d\n", *(p + 1)); // 20
printf("%d\n", *(p + 2)); // 30

// Incrementing
p++;
printf("%d\n", *p);       // 20

// Moving backwards
p--;
printf("%d\n", *p);       // 10

// Pointer subtraction
int *start = &arr[0];
int *end = &arr[4];
ptrdiff_t distance = end - start;  // 4 elements
printf("Distance: %td\n", distance);

// Invalid operations
// int *p1, *p2;
// int result = p1 + p2;  // ERROR: can't add pointers
// int result = p1 * 2;   // ERROR: can't multiply
```

### 1.4 Pointers to Pointers (Multiple Indirection)

```c
int x = 42;
int *p = &x;        // pointer to int
int **pp = &p;      // pointer to pointer to int
int ***ppp = &pp;   // pointer to pointer to pointer

// Dereferencing chain
printf("%d\n", x);      // 42
printf("%d\n", *p);     // 42
printf("%d\n", **pp);   // 42
printf("%d\n", ***ppp); // 42

// Memory addresses
printf("%p\n", (void*)&x);   // address of x
printf("%p\n", (void*)p);    // address of x (value in p)
printf("%p\n", (void*)&p);   // address of p
printf("%p\n", (void*)pp);   // address of p (value in pp)

// Modifying through double pointer
**pp = 100;
printf("%d\n", x);  // 100
```

**Common Use Cases:**
1. Modifying a pointer in a function
2. Dynamic 2D arrays
3. Function parameters that need to allocate memory

```c
// Example: Function that allocates memory
void allocate_memory(int **ptr, int size) {
    *ptr = (int*)malloc(size * sizeof(int));
}

int main() {
    int *arr = NULL;
    allocate_memory(&arr, 5);
    
    if (arr != NULL) {
        arr[0] = 10;
        free(arr);
    }
    return 0;
}
```

### 1.5 const and Pointers (Four Combinations)

```c
int x = 10, y = 20;

// 1. Pointer to const data (can't change data, can change pointer)
const int *p1 = &x;
// *p1 = 15;   // ERROR
p1 = &y;       // OK

// 2. Const pointer (can change data, can't change pointer)
int * const p2 = &x;
*p2 = 15;      // OK
// p2 = &y;    // ERROR

// 3. Const pointer to const data (can't change either)
const int * const p3 = &x;
// *p3 = 15;   // ERROR
// p3 = &y;    // ERROR

// 4. Regular pointer (can change both)
int *p4 = &x;
*p4 = 15;      // OK
p4 = &y;       // OK
```

**Reading Complex Declarations:**
- Read from right to left
- `const int *p` = "p is a pointer to a const int"
- `int * const p` = "p is a const pointer to an int"

### 1.6 Void Pointers (Generic Pointers)

```c
void *vp;
int x = 10;
double y = 3.14;
char c = 'A';

// Can point to any type
vp = &x;
vp = &y;
vp = &c;

// Must cast before dereferencing
vp = &x;
printf("%d\n", *(int*)vp);  // Cast to int* first

// Cannot do pointer arithmetic on void*
// vp++;  // ERROR

// Common use: malloc returns void*
int *arr = (int*)malloc(5 * sizeof(int));
```

### 1.7 Function Pointers

```c
// Function that takes two ints and returns int
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

// Function pointer declaration
int (*operation)(int, int);

// Assignment
operation = add;
printf("%d\n", operation(5, 3));  // 8

operation = subtract;
printf("%d\n", operation(5, 3));  // 2

// Array of function pointers
int (*operations[2])(int, int) = {add, subtract};
printf("%d\n", operations[0](10, 5));  // 15
printf("%d\n", operations[1](10, 5));  // 5
```

### 1.8 Dangling Pointers and Memory Safety

```c
int *create_dangling() {
    int x = 10;
    return &x;  // DANGEROUS: returns address of local variable
}

void example_dangling() {
    int *p;
    {
        int x = 10;
        p = &x;
    }  // x goes out of scope
    // p is now dangling
    // printf("%d\n", *p);  // UNDEFINED BEHAVIOR
}

// Safe practice
int *safe_pointer = NULL;
int x = 10;
safe_pointer = &x;

// After using:
safe_pointer = NULL;  // Prevent dangling
```

### 1.9 Pointer Comparison

```c
int arr[5] = {1, 2, 3, 4, 5};
int *p1 = &arr[0];
int *p2 = &arr[3];

// Relational comparisons (only valid for pointers to same array)
if (p2 > p1) {
    printf("p2 points to a later element\n");
}

// Equality
if (p1 == &arr[0]) {
    printf("p1 points to first element\n");
}

// Distance
printf("Elements between: %td\n", p2 - p1);  // 3

// Comparing with NULL
if (p1 != NULL) {
    printf("Pointer is valid\n");
}
```

---

## 2. ARRAYS

### 2.1 Array Fundamentals

**Declaration and Initialization:**
```c
// Various declaration styles
int arr1[5];                          // Uninitialized (garbage values)
int arr2[5] = {1, 2, 3, 4, 5};       // Fully initialized
int arr3[5] = {1, 2};                // Partial: {1, 2, 0, 0, 0}
int arr4[] = {1, 2, 3};              // Size inferred: 3 elements
int arr5[5] = {0};                   // All zeros: {0, 0, 0, 0, 0}
int arr6[5] = {[0]=1, [4]=5};        // Designated initializers

// Common mistake
int size = 5;
// int arr[size];  // ERROR in older C (OK in C99+ as VLA)
```

### 2.2 Array Decay to Pointer

**Critical Concept:** Array names decay to pointers in most contexts

```c
int arr[5] = {10, 20, 30, 40, 50};

// These are equivalent:
int *p1 = arr;
int *p2 = &arr[0];

// Array name is NOT a pointer variable
// arr++;  // ERROR: can't modify array name
// arr = p1;  // ERROR: can't assign to array name

// But can be used like a pointer
printf("%d\n", *arr);       // 10
printf("%d\n", *(arr + 2)); // 30

// Exceptions where array doesn't decay:
// 1. sizeof operator
printf("%zu\n", sizeof(arr));     // 20 (5 * 4 bytes)
printf("%zu\n", sizeof(p1));      // 8 (on 64-bit system)

// 2. Address-of operator
int (*ptr_to_array)[5] = &arr;    // Pointer to entire array
```

### 2.3 Array Indexing vs Pointer Arithmetic

```c
int arr[5] = {10, 20, 30, 40, 50};
int *p = arr;

// These are all equivalent:
arr[2];
*(arr + 2);
p[2];
*(p + 2);
2[arr];  // Valid! arr[i] == i[arr]

// Proof that arr[i] is *(arr + i)
printf("%d\n", arr[3]);      // 40
printf("%d\n", *(arr + 3));  // 40
printf("%d\n", 3[arr]);      // 40 (weird but legal!)
```

### 2.4 Multi-Dimensional Arrays

**2D Array Memory Layout:**
```c
int matrix[3][4] = {
    {1,  2,  3,  4},
    {5,  6,  7,  8},
    {9, 10, 11, 12}
};

// Memory is contiguous (row-major order):
// [1][2][3][4][5][6][7][8][9][10][11][12]

// Accessing elements
printf("%d\n", matrix[1][2]);  // 7

// Pointer arithmetic
int *p = &matrix[0][0];
for (int i = 0; i < 12; i++) {
    printf("%d ", *(p + i));
}

// Understanding the dimensions
printf("%zu\n", sizeof(matrix));        // 48 bytes (3*4*4)
printf("%zu\n", sizeof(matrix[0]));     // 16 bytes (4*4)
printf("%zu\n", sizeof(matrix[0][0]));  // 4 bytes
```

**Pointer to Array vs Array of Pointers:**
```c
// Pointer to an array of 4 ints
int (*ptr_to_array)[4];
ptr_to_array = matrix;
printf("%d\n", (*ptr_to_array)[2]);  // 3

// Array of pointers (different!)
int *array_of_ptrs[3];
int a = 1, b = 2, c = 3;
array_of_ptrs[0] = &a;
array_of_ptrs[1] = &b;
array_of_ptrs[2] = &c;
```

### 2.5 Passing Arrays to Functions

**Critical: Arrays are always passed by reference (as pointers)**

```c
// These function declarations are equivalent:
void func1(int arr[10]);
void func1(int arr[]);
void func1(int *arr);

void modify_array(int arr[], int size) {
    arr[0] = 999;  // Modifies original array!
}

int main() {
    int numbers[5] = {1, 2, 3, 4, 5};
    
    modify_array(numbers, 5);
    printf("%d\n", numbers[0]);  // 999
    
    // Inside function, sizeof(arr) gives pointer size, not array size
    // Must pass size separately
    return 0;
}
```

**Passing 2D Arrays:**
```c
// Column size MUST be specified
void print_matrix(int rows, int cols, int matrix[][4]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Alternative: pointer to array
void print_matrix2(int rows, int cols, int (*matrix)[4]) {
    // Same implementation
}

// Using void* for generic size
void print_generic(int rows, int cols, int *matrix) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", *(matrix + i * cols + j));
        }
        printf("\n");
    }
}
```

### 2.6 Variable Length Arrays (VLA) - C99+

```c
void create_vla(int n) {
    int arr[n];  // Size determined at runtime
    
    for (int i = 0; i < n; i++) {
        arr[i] = i * 10;
    }
    
    // VLAs are automatically deallocated when out of scope
    // DON'T use free() on VLAs
}

// 2D VLA
void create_2d_vla(int rows, int cols) {
    int matrix[rows][cols];
    
    // Initialize
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j;
        }
    }
}

// Note: VLAs have potential stack overflow risk with large sizes
```

### 2.7 Strings as Character Arrays

```c
// String initialization
char str1[] = "Hello";          // {'H','e','l','l','o','\0'} - 6 bytes
char str2[10] = "Hello";        // Remaining bytes are '\0'
char str3[] = {'H','i','\0'};   // Manual null terminator

// Important: Always null-terminated!
char str4[5] = {'H','e','l','l','o'};  // NO null terminator - DANGEROUS

// String length vs array size
printf("%zu\n", strlen(str1));   // 5 (doesn't count '\0')
printf("%zu\n", sizeof(str1));   // 6 (includes '\0')

// String manipulation
char dest[20];
strcpy(dest, "Hello");
strcat(dest, " World");
printf("%s\n", dest);  // "Hello World"

// Safe versions
strncpy(dest, "Hello", sizeof(dest) - 1);
dest[sizeof(dest) - 1] = '\0';  // Ensure null termination
```

### 2.8 Array Bounds and Buffer Overflow

```c
int arr[5] = {1, 2, 3, 4, 5};

// No bounds checking in C!
arr[5] = 100;   // OUT OF BOUNDS - Undefined Behavior
arr[-1] = 200;  // OUT OF BOUNDS - Undefined Behavior
arr[100] = 300; // CRASH or memory corruption

// Common buffer overflow scenario
char buffer[10];
char input[50] = "This string is too long for the buffer";
strcpy(buffer, input);  // BUFFER OVERFLOW!

// Safe approach
strncpy(buffer, input, sizeof(buffer) - 1);
buffer[sizeof(buffer) - 1] = '\0';
```

---

## 3. MEMORY ALLOCATION

### 3.1 Memory Segments

```c
// Diagram of process memory layout (high to low address):
// ┌─────────────────────┐
// │   Stack             │ ← Local variables, function calls
// │   (grows down)      │
// ├─────────────────────┤
// │   ↓                 │
// │                     │
// │   Free Memory       │
// │                     │
// │   ↑                 │
// ├─────────────────────┤
// │   Heap              │ ← Dynamic allocation (malloc)
// │   (grows up)        │
// ├─────────────────────┤
// │   BSS Segment       │ ← Uninitialized global/static
// ├─────────────────────┤
// │   Data Segment      │ ← Initialized global/static
// ├─────────────────────┤
// │   Text/Code         │ ← Program instructions
// └─────────────────────┘

int global_init = 10;       // Data segment
int global_uninit;          // BSS segment
static int static_var = 5;  // Data segment

void function() {
    int local = 20;              // Stack
    static int static_local = 30; // Data segment
    int *heap_ptr = malloc(sizeof(int)); // heap_ptr on stack, data on heap
    free(heap_ptr);
}
```

### 3.2 malloc() - Memory Allocation

```c
#include <stdlib.h>

// Syntax: void* malloc(size_t size)
// Returns: pointer to allocated memory, or NULL on failure

int *p = (int*)malloc(sizeof(int));
if (p == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
}

*p = 42;
printf("%d\n", *p);
free(p);
p = NULL;  // Good practice

// Allocating arrays
int n = 10;
int *arr = (int*)malloc(n * sizeof(int));
if (arr == NULL) {
    // Handle error
}

for (int i = 0; i < n; i++) {
    arr[i] = i * 10;
}

free(arr);
arr = NULL;

// Common mistakes
// 1. Wrong size calculation
int *wrong = (int*)malloc(n);  // WRONG: allocates n bytes, not n ints
int *correct = (int*)malloc(n * sizeof(int));  // CORRECT

// 2. Not checking NULL
int *unsafe = (int*)malloc(sizeof(int));
*unsafe = 10;  // CRASH if malloc failed!

// 3. Memory leak
void leak_example() {
    int *p = (int*)malloc(sizeof(int));
    *p = 10;
    // Missing free(p) - MEMORY LEAK!
}
```

### 3.3 calloc() - Contiguous Allocation

```c
// Syntax: void* calloc(size_t num, size_t size)
// Difference from malloc: initializes memory to zero

int *arr1 = (int*)malloc(5 * sizeof(int));
// arr1 contains garbage values

int *arr2 = (int*)calloc(5, sizeof(int));
// arr2 contains {0, 0, 0, 0, 0}

for (int i = 0; i < 5; i++) {
    printf("%d ", arr2[i]);  // Prints: 0 0 0 0 0
}

free(arr1);
free(arr2);

// When to use calloc vs malloc:
// - Use calloc when you need zero-initialized memory
// - Use malloc when you'll immediately overwrite the values
// - calloc may be slightly slower due to initialization
```

### 3.4 realloc() - Resize Allocation

```c
// Syntax: void* realloc(void *ptr, size_t new_size)
// Returns: pointer to resized memory (may be different address!)

int *arr = (int*)malloc(5 * sizeof(int));
for (int i = 0; i < 5; i++) {
    arr[i] = i;
}

// Expand to 10 elements
int *temp = (int*)realloc(arr, 10 * sizeof(int));
if (temp == NULL) {
    // Reallocation failed, arr still valid
    free(arr);
    exit(1);
}
arr = temp;  // Update pointer only if successful

// Original 5 elements preserved, next 5 are uninitialized
for (int i = 5; i < 10; i++) {
    arr[i] = i;
}

// Shrink to 3 elements
arr = (int*)realloc(arr, 3 * sizeof(int));
// First 3 elements preserved

free(arr);

// Special cases of realloc:
realloc(NULL, size);  // Equivalent to malloc(size)
realloc(ptr, 0);      // Equivalent to free(ptr), returns NULL

// Common mistake: losing original pointer
int *data = (int*)malloc(5 * sizeof(int));
data = (int*)realloc(data, 10 * sizeof(int));  // WRONG if realloc fails!
// Correct:
int *new_data = (int*)realloc(data, 10 * sizeof(int));
if (new_data != NULL) {
    data = new_data;
} else {
    free(data);  // Clean up original
}
```

### 3.5 free() - Deallocation

```c
int *p = (int*)malloc(sizeof(int));
*p = 42;

free(p);  // Deallocates memory
p = NULL; // Prevent dangling pointer

// Common mistakes:

// 1. Double free
int *ptr = (int*)malloc(sizeof(int));
free(ptr);
free(ptr);  // CRASH! Undefined behavior

// 2. Freeing stack memory
int x = 10;
int *ptr2 = &x;
free(ptr2);  // CRASH! Can only free heap memory

// 3. Using after free
int *ptr3 = (int*)malloc(sizeof(int));
free(ptr3);
*ptr3 = 10;  // Undefined behavior!

// 4. Freeing part of allocated block
int *arr = (int*)malloc(10 * sizeof(int));
free(arr + 5);  // WRONG! Must free the original pointer

// 5. Forgetting to free (memory leak)
void create_leak() {
    int *p = (int*)malloc(sizeof(int));
    // Function ends without free(p) - LEAK!
}
```

### 3.6 Dynamic 2D Arrays

**Method 1: Array of Pointers (Non-contiguous)**
```c
int rows = 3, cols = 4;

// Allocate array of pointers
int **matrix = (int**)malloc(rows * sizeof(int*));

// Allocate each row
for (int i = 0; i < rows; i++) {
    matrix[i] = (int*)malloc(cols * sizeof(int));
}

// Use the matrix
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        matrix[i][j] = i * cols + j;
    }
}

// Free the matrix
for (int i = 0; i < rows; i++) {
    free(matrix[i]);
}
free(matrix);
```

**Method 2: Single Allocation (Contiguous)**
```c
int rows = 3, cols = 4;

// Allocate as single block
int *matrix = (int*)malloc(rows * cols * sizeof(int));

// Access using pointer arithmetic
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        matrix[i * cols + j] = i * cols + j;
    }
}

// Single free
free(matrix);
```

**Method 3: Array of Pointers with Single Allocation**
```c
int rows = 3, cols = 4;

// Allocate data block
int *data = (int*)malloc(rows * cols * sizeof(int));

// Allocate pointer array
int **matrix = (int**)malloc(rows * sizeof(int*));

// Point each row to correct location in data
for (int i = 0; i < rows; i++) {
    matrix[i] = data + (i * cols);
}

// Use with familiar syntax
matrix[1][2] = 42;

// Free both
free(data);
free(matrix);
```

### 3.7 Memory Leaks Detection

```c
// Common leak patterns:

// Pattern 1: Lost reference
void leak1() {
    int *p = (int*)malloc(sizeof(int));
    p = (int*)malloc(sizeof(int));  // First allocation lost!
    free(p);  // Only frees second allocation
}

// Pattern 2: Early return
void leak2(int condition) {
    int *p = (int*)malloc(sizeof(int));
    
    if (condition) {
        return;  // LEAK! Forgot to free
    }
    
    free(p);
}

// Pattern 3: Exception in loop
void leak3() {
    for (int i = 0; i < 10; i++) {
        int *p = (int*)malloc(sizeof(int));
        
        if (some_condition) {
            break;  // LEAK! Loop iterations leaked
        }
        
        free(p);
    }
}

// Correct version
void no_leak() {
    int *p = NULL;
    
    for (int i = 0; i < 10; i++) {
        p = (int*)malloc(sizeof(int));
        
        if (some_condition) {
            free(p);
            break;  // Now safe
        }
        
        free(p);
    }
}
```

### 3.8 Memory Alignment and Padding

```c
#include <stddef.h>

struct Example {
    char c;    // 1 byte
    int i;     // 4 bytes
    char d;    // 1 byte
};

// Actual memory layout with padding:
// [c][pad][pad][pad][i][i][i][i][d][pad][pad][pad]
// Total: 12 bytes (not 6!)

printf("Size: %zu\n", sizeof(struct Example));  // Likely 12

// Better ordering to minimize padding:
struct Optimized {
    int i;     // 4 bytes
    char c;    // 1 byte
    char d;    // 1 byte
};
// [i][i][i][i][c][d][pad][pad]
// Total: 8 bytes

// Checking alignment
printf("Alignment of int: %zu\n", _Alignof(int));
```

---

## 4. LINKED LISTS

### 4.1 Singly Linked List - Basic Structure

```c
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Why "struct Node*" and not "Node*" inside?
// Because Node typedef isn't complete yet during definition!

// Creating a node
Node* create_node(int value) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    
    new_node->data = value;
    new_node->next = NULL;
    
    return new_node;
}
```

### 4.2 List Operations - Insert

**Insert at Beginning (O(1))**
```c
void insert_at_beginning(Node **head, int value) {
    Node *new_node = create_node(value);
    
    new_node->next = *head;
    *head = new_node;
}

// Usage:
Node *list = NULL;
insert_at_beginning(&list, 10);
insert_at_beginning(&list, 20);
insert_at_beginning(&list, 30);
// List: 30 -> 20 -> 10 -> NULL
```

**Insert at End (O(n))**
```c
void insert_at_end(Node **head, int value) {
    Node *new_node = create_node(value);
    
    // Empty list case
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    
    // Traverse to end
    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = new_node;
}
```

**Insert at Position (O(n))**
```c
void insert_at_position(Node **head, int value, int position) {
    // Position 0 means insert at beginning
    if (position == 0) {
        insert_at_beginning(head, value);
        return;
    }
    
    Node *new_node = create_node(value);
    Node *current = *head;
    
    // Traverse to position - 1
    for (int i = 0; i < position - 1 && current != NULL; i++) {
        current = current->next;
    }
    
    // Position out of bounds
    if (current == NULL) {
        free(new_node);
        printf("Position out of bounds\n");
        return;
    }
    
    new_node->next = current->next;
    current->next = new_node;
}
```

**Insert in Sorted Order (O(n))**
```c
void insert_sorted(Node **head, int value) {
    Node *new_node = create_node(value);
    
    // Empty list or insert at beginning
    if (*head == NULL || (*head)->data >= value) {
        new_node->next = *head;
        *head = new_node;
        return;
    }
    
    // Find insertion point
    Node *current = *head;
    while (current->next != NULL && current->next->data < value) {
        current = current->next;
    }
    
    new_node->next = current->next;
    current->next = new_node;
}
```

### 4.3 List Operations - Delete

**Delete from Beginning (O(1))**
```c
void delete_from_beginning(Node **head) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    Node *temp = *head;
    *head = (*head)->next;
    free(temp);
}
```

**Delete from End (O(n))**
```c
void delete_from_end(Node **head) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    // Only one node
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    
    // Find second-to-last node
    Node *current = *head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    
    free(current->next);
    current->next = NULL;
}
```

**Delete Specific Value (O(n))**
```c
void delete_value(Node **head, int value) {
    if (*head == NULL) {
        return;
    }
    
    // If head contains the value
    if ((*head)->data == value) {
        Node *temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }
    
    // Search for node
    Node *current = *head;
    while (current->next != NULL && current->next->data != value) {
        current = current->next;
    }
    
    // Value not found
    if (current->next == NULL) {
        printf("Value not found\n");
        return;
    }
    
    // Delete node
    Node *temp = current->next;
    current->next = current->next->next;
    free(temp);
}
```

**Delete at Position (O(n))**
```c
void delete_at_position(Node **head, int position) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    // Delete head
    if (position == 0) {
        Node *temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }
    
    // Find node before target
    Node *current = *head;
    for (int i = 0; i < position - 1 && current != NULL; i++) {
        current = current->next;
    }
    
    // Position out of bounds
    if (current == NULL || current->next == NULL) {
        printf("Position out of bounds\n");
        return;
    }
    
    Node *temp = current->next;
    current->next = current->next->next;
    free(temp);
}
```

### 4.4 List Traversal and Search

**Print List (O(n))**
```c
void print_list(Node *head) {
    Node *current = head;
    
    printf("List: ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}
```

**Search (O(n))**
```c
Node* search(Node *head, int value) {
    Node *current = head;
    
    while (current != NULL) {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    }
    
    return NULL;  // Not found
}

// Search with position
int search_position(Node *head, int value) {
    Node *current = head;
    int position = 0;
    
    while (current != NULL) {
        if (current->data == value) {
            return position;
        }
        current = current->next;
        position++;
    }
    
    return -1;  // Not found
}
```

**Get Length (O(n))**
```c
int get_length(Node *head) {
    int count = 0;
    Node *current = head;
    
    while (current != NULL) {
        count++;
        current = current->next;
    }
    
    return count;
}
```

### 4.5 Advanced List Operations

**Reverse List (O(n))**
```c
void reverse_list(Node **head) {
    Node *prev = NULL;
    Node *current = *head;
    Node *next = NULL;
    
    while (current != NULL) {
        next = current->next;  // Store next
        current->next = prev;  // Reverse link
        prev = current;        // Move prev forward
        current = next;        // Move current forward
    }
    
    *head = prev;
}
```

**Find Middle (Two-Pointer Technique, O(n))**
```c
Node* find_middle(Node *head) {
    if (head == NULL) {
        return NULL;
    }
    
    Node *slow = head;
    Node *fast = head;
    
    while (fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;
}
```

**Detect Cycle (Floyd's Algorithm, O(n))**
```c
int has_cycle(Node *head) {
    if (head == NULL) {
        return 0;
    }
    
    Node *slow = head;
    Node *fast = head;
    
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            return 1;  // Cycle detected
        }
    }
    
    return 0;  // No cycle
}
```

**Remove Duplicates from Sorted List (O(n))**
```c
void remove_duplicates(Node *head) {
    if (head == NULL) {
        return;
    }
    
    Node *current = head;
    
    while (current->next != NULL) {
        if (current->data == current->next->data) {
            Node *temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
}
```

**Merge Two Sorted Lists (O(m+n))**
```c
Node* merge_sorted(Node *list1, Node *list2) {
    // Create dummy node to simplify code
    Node dummy;
    dummy.next = NULL;
    Node *tail = &dummy;
    
    while (list1 != NULL && list2 != NULL) {
        if (list1->data <= list2->data) {
            tail->next = list1;
            list1 = list1->next;
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }
    
    // Attach remaining nodes
    if (list1 != NULL) {
        tail->next = list1;
    } else {
        tail->next = list2;
    }
    
    return dummy.next;
}
```

### 4.6 Doubly Linked List

```c
typedef struct DNode {
    int data;
    struct DNode *next;
    struct DNode *prev;
} DNode;

DNode* create_dnode(int value) {
    DNode *new_node = (DNode*)malloc(sizeof(DNode));
    if (new_node == NULL) {
        exit(1);
    }
    
    new_node->data = value;
    new_node->next = NULL;
    new_node->prev = NULL;
    
    return new_node;
}

void insert_at_beginning_doubly(DNode **head, int value) {
    DNode *new_node = create_dnode(value);
    
    if (*head != NULL) {
        (*head)->prev = new_node;
    }
    
    new_node->next = *head;
    *head = new_node;
}

void insert_at_end_doubly(DNode **head, int value) {
    DNode *new_node = create_dnode(value);
    
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    
    DNode *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = new_node;
    new_node->prev = current;
}

void delete_node_doubly(DNode **head, DNode *node) {
    if (*head == NULL || node == NULL) {
        return;
    }
    
    // If node is head
    if (*head == node) {
        *head = node->next;
    }
    
    // Update previous node's next
    if (node->prev != NULL) {
        node->prev->next = node->next;
    }
    
    // Update next node's prev
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
    
    free(node);
}

void print_doubly_forward(DNode *head) {
    DNode *current = head;
    printf("Forward: ");
    while (current != NULL) {
        printf("%d <-> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void print_doubly_backward(DNode *head) {
    if (head == NULL) {
        return;
    }
    
    // Go to end
    DNode *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    // Print backward
    printf("Backward: NULL");
    while (current != NULL) {
        printf(" <-> %d", current->data);
        current = current->prev;
    }
    printf("\n");
}
```

### 4.7 Circular Linked List

```c
typedef struct CNode {
    int data;
    struct CNode *next;
} CNode;

void insert_circular(CNode **head, int value) {
    CNode *new_node = create_node(value);
    
    if (*head == NULL) {
        new_node->next = new_node;  // Points to itself
        *head = new_node;
        return;
    }
    
    // Find last node
    CNode *current = *head;
    while (current->next != *head) {
        current = current->next;
    }
    
    new_node->next = *head;
    current->next = new_node;
}

void print_circular(CNode *head) {
    if (head == NULL) {
        return;
    }
    
    CNode *current = head;
    printf("Circular: ");
    
    do {
        printf("%d -> ", current->data);
        current = current->next;
    } while (current != head);
    
    printf("(back to %d)\n", head->data);
}
```

### 4.8 Memory Management for Lists

```c
// Free entire list
void free_list(Node **head) {
    Node *current = *head;
    Node *next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    *head = NULL;
}

// Deep copy a list
Node* copy_list(Node *head) {
    if (head == NULL) {
        return NULL;
    }
    
    Node *new_head = create_node(head->data);
    Node *current_old = head->next;
    Node *current_new = new_head;
    
    while (current_old != NULL) {
        current_new->next = create_node(current_old->data);
        current_new = current_new->next;
        current_old = current_old->next;
    }
    
    return new_head;
}
```

---

## 5. RECURSION

### 5.1 Recursion Fundamentals

**Key Components:**
1. **Base Case**: Condition that stops recursion
2. **Recursive Case**: Function calls itself with modified input
3. **Progress**: Each call must move toward base case

```c
// Simple example: Factorial
int factorial(int n) {
    // Base case
    if (n <= 1) {
        return 1;
    }
    
    // Recursive case
    return n * factorial(n - 1);
}

// Call stack visualization for factorial(4):
// factorial(4)
//   |-> 4 * factorial(3)
//         |-> 3 * factorial(2)
//               |-> 2 * factorial(1)
//                     |-> returns 1
//               |-> returns 2 * 1 = 2
//         |-> returns 3 * 2 = 6
//   |-> returns 4 * 6 = 24
```

### 5.2 Types of Recursion

**Direct Recursion**
```c
void direct() {
    // Function calls itself
    direct();
}
```

**Indirect Recursion**
```c
void function_a();
void function_b();

void function_a() {
    function_b();  // Calls B
}

void function_b() {
    function_a();  // Calls A (cycle)
}
```

**Tail Recursion** (Last operation is recursive call)
```c
int tail_factorial(int n, int accumulator) {
    if (n <= 1) {
        return accumulator;
    }
    return tail_factorial(n - 1, n * accumulator);
}

// Can be optimized by compiler to iteration
```

**Non-Tail Recursion** (Operations after recursive call)
```c
int non_tail_factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * non_tail_factorial(n - 1);  // Multiplication after call
}
```

### 5.3 Classic Recursion Examples

**Fibonacci Sequence**
```c
// Naive recursive (SLOW - O(2^n))
int fibonacci_recursive(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

// Call tree for fib(5) - notice repeated calculations:
//                    fib(5)
//                 /          \
//           fib(4)             fib(3)
//          /      \           /      \
//      fib(3)   fib(2)    fib(2)   fib(1)
//     /    \    /    \    /    \
// fib(2) fib(1) fib(1) fib(0) fib(1) fib(0)
// / \
//fib(1) fib(0)

// Optimized with memoization
int fib_memo(int n, int *memo) {
    if (n <= 1) {
        return n;
    }
    
    if (memo[n] != -1) {
        return memo[n];  // Return cached result
    }
    
    memo[n] = fib_memo(n - 1, memo) + fib_memo(n - 2, memo);
    return memo[n];
}

int fibonacci_optimized(int n) {
    int *memo = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++) {
        memo[i] = -1;  // Initialize cache
    }
    
    int result = fib_memo(n, memo);
    free(memo);
    return result;
}
```

**Power Function**
```c
// Basic recursion - O(n)
int power_basic(int base, int exp) {
    if (exp == 0) {
        return 1;
    }
    return base * power_basic(base, exp - 1);
}

// Optimized with divide and conquer - O(log n)
int power_optimized(int base, int exp) {
    if (exp == 0) {
        return 1;
    }
    
    int half = power_optimized(base, exp / 2);
    
    if (exp % 2 == 0) {
        return half * half;
    } else {
        return base * half * half;
    }
}

// Example: power(2, 8)
// power(2, 8) -> half = power(2, 4) -> half * half
//   power(2, 4) -> half = power(2, 2) -> half * half
//     power(2, 2) -> half = power(2, 1) -> half * half
//       power(2, 1) -> half = power(2, 0) = 1 -> 2 * 1 * 1 = 2
```

**Sum of Array**
```c
int sum_array(int arr[], int n) {
    if (n == 0) {
        return 0;
    }
    return arr[n - 1] + sum_array(arr, n - 1);
}

// Alternative: helper with index
int sum_helper(int arr[], int index, int size) {
    if (index >= size) {
        return 0;
    }
    return arr[index] + sum_helper(arr, index + 1, size);
}

int sum_array_alt(int arr[], int size) {
    return sum_helper(arr, 0, size);
}
```

**String Reverse**
```c
void reverse_string(char *str, int start, int end) {
    if (start >= end) {
        return;
    }
    
    // Swap characters
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    
    // Recurse on smaller problem
    reverse_string(str, start + 1, end - 1);
}

void reverse(char *str) {
    int len = strlen(str);
    reverse_string(str, 0, len - 1);
}
```

**Palindrome Check**
```c
int is_palindrome(char *str, int start, int end) {
    if (start >= end) {
        return 1;  // Base case: single char or empty
    }
    
    if (str[start] != str[end]) {
        return 0;  // Mismatch found
    }
    
    return is_palindrome(str, start + 1, end - 1);
}

int check_palindrome(char *str) {
    int len = strlen(str);
    return is_palindrome(str, 0, len - 1);
}
```

### 5.4 Recursion with Arrays

**Binary Search**
```c
int binary_search_recursive(int arr[], int left, int right, int target) {
    if (left > right) {
        return -1;  // Not found
    }
    
    int mid = left + (right - left) / 2;
    
    if (arr[mid] == target) {
        return mid;
    } else if (arr[mid] > target) {
        return binary_search_recursive(arr, left, mid - 1, target);
    } else {
        return binary_search_recursive(arr, mid + 1, right, target);
    }
}

int binary_search(int arr[], int size, int target) {
    return binary_search_recursive(arr, 0, size - 1, target);
}
```

**Merge Sort**
```c
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Create temp arrays
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));
    
    // Copy data
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }
    
    // Merge back
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    
    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }
    
    free(L);
    free(R);
}

void merge_sort_helper(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        // Sort halves
        merge_sort_helper(arr, left, mid);
        merge_sort_helper(arr, mid + 1, right);
        
        // Merge sorted halves
        merge(arr, left, mid, right);
    }
}

void merge_sort(int arr[], int size) {
    merge_sort_helper(arr, 0, size - 1);
}
```

**Quick Sort**
```c
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            // Swap
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    // Place pivot in correct position
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    
    return i + 1;
}

void quick_sort_helper(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        // Recursively sort elements
        quick_sort_helper(arr, low, pi - 1);
        quick_sort_helper(arr, pi + 1, high);
    }
}

void quick_sort(int arr[], int size) {
    quick_sort_helper(arr, 0, size - 1);
}
```

### 5.5 Recursion with Linked Lists

**Recursive Print**
```c
void print_list_recursive(Node *head) {
    if (head == NULL) {
        printf("NULL\n");
        return;
    }
    
    printf("%d -> ", head->data);
    print_list_recursive(head->next);
}

// Print in reverse
void print_reverse_recursive(Node *head) {
    if (head == NULL) {
        return;
    }
    
    print_reverse_recursive(head->next);
    printf("%d ", head->data);
}
```

**Recursive Length**
```c
int length_recursive(Node *head) {
    if (head == NULL) {
        return 0;
    }
    return 1 + length_recursive(head->next);
}
```

**Recursive Search**
```c
Node* search_recursive(Node *head, int target) {
    if (head == NULL) {
        return NULL;
    }
    
    if (head->data == target) {
        return head;
    }
    
    return search_recursive(head->next, target);
}
```

**Recursive Reverse**
```c
Node* reverse_recursive(Node *head) {
    // Base cases
    if (head == NULL || head->next == NULL) {
        return head;
    }
    
    // Reverse rest of list
    Node *rest = reverse_recursive(head->next);
    
    // Make next node point back
    head->next->next = head;
    head->next = NULL;
    
    return rest;
}
```

### 5.6 Tower of Hanoi

```c
void tower_of_hanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        printf("Move disk 1 from %c to %c\n", from, to);
        return;
    }
    
    // Move n-1 disks from 'from' to 'aux' using 'to'
    tower_of_hanoi(n - 1, from, aux, to);
    
    // Move nth disk from 'from' to 'to'
    printf("Move disk %d from %c to %c\n", n, from, to);
    
    // Move n-1 disks from 'aux' to 'to' using 'from'
    tower_of_hanoi(n - 1, aux, to, from);
}

// For 3 disks:
// tower_of_hanoi(3, 'A', 'C', 'B')
// Output:
// Move disk 1 from A to C
// Move disk 2 from A to B
// Move disk 1 from C to B
// Move disk 3 from A to C
// Move disk 1 from B to A
// Move disk 2 from B to C
// Move disk 1 from A to C
```

### 5.7 Recursion Pitfalls

**Stack Overflow**
```c
// Infinite recursion - NO BASE CASE
void infinite() {
    infinite();  // CRASH after ~10,000-100,000 calls
}

// Too deep recursion
int too_deep(int n) {
    if (n == 0) {
        return 0;
    }
    return too_deep(n - 1);
}
// Calling too_deep(1000000) may overflow stack
```

**Incorrect Base Case**
```c
int buggy_factorial(int n) {
    if (n == 0) {
        return 1;
    }
    return n * buggy_factorial(n - 1);
}
// buggy_factorial(-5) causes infinite recursion!

// Correct version:
int correct_factorial(int n) {
    if (n <= 1) {  // Handles negative and zero
        return 1;
    }
    return n * correct_factorial(n - 1);
}
```

**Not Making Progress**
```c
int no_progress(int n) {
    if (n == 0) {
        return 0;
    }
    return no_progress(n);  // BUG: n doesn't change!
}
```

### 5.8 Recursion vs Iteration

**When to Use Recursion:**
- Problem is naturally recursive (trees, divide-and-conquer)
- Code is much simpler/cleaner
- Performance isn't critical

**When to Use Iteration:**
- Simple repetitive tasks
- Performance critical
- Deep recursion risks stack overflow
- Tail recursion (compiler may optimize anyway)

```c
// Factorial - Both versions
int factorial_recursive(int n) {
    return (n <= 1) ? 1 : n * factorial_recursive(n - 1);
}

int factorial_iterative(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// Performance: iterative is typically faster (no function call overhead)
// Readability: recursive is more elegant for this problem
```

---

## 6. STRUCTS

### 6.1 Structure Basics

**Declaration and Definition**
```c
// Method 1: Define type and declare variables separately
struct Point {
    int x;
    int y;
};

struct Point p1, p2;

// Method 2: Define and declare together
struct Circle {
    int radius;
    struct Point center;
} c1, c2;

// Method 3: Anonymous struct (no reuse)
struct {
    int id;
    char name[50];
} employee1;

// Method 4: Using typedef
typedef struct {
    double real;
    double imag;
} Complex;

Complex c1, c2;  // No need for 'struct' keyword
```

**Initialization**
```c
struct Point {
    int x;
    int y;
};

// Method 1: Ordered initialization
struct Point p1 = {10, 20};

// Method 2: Designated initializers (C99+)
struct Point p2 = {.y = 30, .x = 40};

// Method 3: Partial initialization (rest are zero)
struct Point p3 = {50};  // x=50, y=0

// Method 4: Zero initialization
struct Point p4 = {0};  // x=0, y=0
```

### 6.2 Accessing Members

```c
struct Student {
    int id;
    char name[50];
    float gpa;
};

struct Student s1 = {101, "Alice", 3.8};

// Dot operator for struct variables
printf("ID: %d\n", s1.id);
printf("Name: %s\n", s1.name);
printf("GPA: %.2f\n", s1.gpa);

// Modifying members
s1.id = 102;
strcpy(s1.name, "Bob");
s1.gpa = 3.9;

// Nested access
struct Course {
    char code[10];
    struct Student instructor;
};

struct Course cs101 = {"CS101", {201, "Dr. Smith", 4.0}};
printf("Instructor: %s\n", cs101.instructor.name);
```

### 6.3 Pointers to Structures

```c
struct Point {
    int x;
    int y;
};

struct Point p = {10, 20};
struct Point *ptr = &p;

// Method 1: Dereference then use dot operator
printf("x = %d\n", (*ptr).x);

// Method 2: Arrow operator (preferred)
printf("x = %d\n", ptr->x);
printf("y = %d\n", ptr->y);

// Modifying through pointer
ptr->x = 30;
ptr->y = 40;

printf("Updated: (%d, %d)\n", p.x, p.y);  // (30, 40)
```

### 6.4 Structures and Functions

**Passing by Value (Copy)**
```c
struct Rectangle {
    int width;
    int height;
};

// Entire struct is copied (can be expensive for large structs)
int area_by_value(struct Rectangle r) {
    return r.width * r.height;
}

int main() {
    struct Rectangle rect = {10, 20};
    printf("Area: %d\n", area_by_value(rect));
    return 0;
}
```

**Passing by Pointer (Reference)**
```c
// More efficient - only pointer is copied
int area_by_pointer(struct Rectangle *r) {
    return r->width * r->height;
}

// Can modify original
void scale_by_pointer(struct Rectangle *r, int factor) {
    r->width *= factor;
    r->height *= factor;
}

int main() {
    struct Rectangle rect = {10, 20};
    
    printf("Area: %d\n", area_by_pointer(&rect));
    
    scale_by_pointer(&rect, 2);
    printf("Scaled: %d x %d\n", rect.width, rect.height);
    
    return 0;
}
```

**Returning Structures**
```c
// Return by value
struct Point create_point(int x, int y) {
    struct Point p = {x, y};
    return p;  // Entire struct is copied
}

// Return pointer (DANGEROUS if returning local variable)
struct Point* create_point_bad() {
    struct Point p = {10, 20};
    return &p;  // WRONG: p is destroyed after function
}

// Return pointer (CORRECT - dynamic allocation)
struct Point* create_point_good(int x, int y) {
    struct Point *p = (struct Point*)malloc(sizeof(struct Point));
    if (p != NULL) {
        p->x = x;
        p->y = y;
    }
    return p;
}

int main() {
    struct Point p1 = create_point(5, 10);
    
    struct Point *p2 = create_point_good(15, 20);
    if (p2 != NULL) {
        printf("(%d, %d)\n", p2->x, p2->y);
        free(p2);
    }
    
    return 0;
}
```

### 6.5 Nested Structures

```c
struct Date {
    int day;
    int month;
    int year;
};

struct Employee {
    int id;
    char name[50];
    struct Date hire_date;
    struct Date birth_date;
};

int main() {
    struct Employee emp = {
        .id = 1001,
        .name = "John Doe",
        .hire_date = {15, 3, 2020},
        .birth_date = {20, 5, 1990}
    };
    
    printf("Hired: %d/%d/%d\n", 
        emp.hire_date.day,
        emp.hire_date.month,
        emp.hire_date.year);
    
    return 0;
}
```

### 6.6 Arrays of Structures

```c
struct Student {
    int id;
    char name[50];
    float gpa;
};

int main() {
    // Array of structures
    struct Student class[3] = {
        {101, "Alice", 3.8},
        {102, "Bob", 3.5},
        {103, "Charlie", 3.9}
    };
    
    // Access elements
    for (int i = 0; i < 3; i++) {
        printf("ID: %d, Name: %s, GPA: %.2f\n",
            class[i].id,
            class[i].name,
            class[i].gpa);
    }
    
    // Dynamic array of structures
    int n = 5;
    struct Student *students = 
        (struct Student*)malloc(n * sizeof(struct Student));
    
    if (students != NULL) {
        // Use students array
        students[0].id = 201;
        strcpy(students[0].name, "David");
        students[0].gpa = 3.7;
        
        free(students);
    }
    
    return 0;
}
```

### 6.7 Structures with Pointers

```c
struct Node {
    int data;
    struct Node *next;  // Self-referential structure
};

struct Person {
    char *name;  // Pointer to dynamically allocated string
    int age;
};

int main() {
    struct Person p;
    
    // Allocate memory for name
    p.name = (char*)malloc(50 * sizeof(char));
    if (p.name != NULL) {
        strcpy(p.name, "Alice");
        p.age = 25;
        
        printf("Name: %s, Age: %d\n", p.name, p.age);
        
        free(p.name);  // Don't forget to free!
    }
    
    return 0;
}
```

### 6.8 Structure Padding and Alignment

```c
#include <stddef.h>

struct Example1 {
    char c;    // 1 byte
    int i;     // 4 bytes
    char d;    // 1 byte
};
// Memory: [c][pad][pad][pad][i][i][i][i][d][pad][pad][pad]
// Total: 12 bytes (not 6!)

struct Example2 {
    char c;    // 1 byte
    char d;    // 1 byte
    int i;     // 4 bytes
};
// Memory: [c][d][pad][pad][i][i][i][i]
// Total: 8 bytes

int main() {
    printf("Size of Example1: %zu\n", sizeof(struct Example1));  // 12
    printf("Size of Example2: %zu\n", sizeof(struct Example2));  // 8
    
    // Checking member offsets
    printf("Offset of c in Example1: %zu\n", offsetof(struct Example1, c));  // 0
    printf("Offset of i in Example1: %zu\n", offsetof(struct Example1, i));  // 4
    printf("Offset of d in Example1: %zu\n", offsetof(struct Example1, d));  // 8
    
    return 0;
}

// Pragma pack to control padding (compiler-specific)
#pragma pack(1)
struct Packed {
    char c;
    int i;
    char d;
};
#pragma pack()
// Size would be 6 bytes (no padding)
```

### 6.9 Bit Fields

```c
struct Flags {
    unsigned int flag1 : 1;  // 1 bit
    unsigned int flag2 : 1;  // 1 bit
    unsigned int value : 6;  // 6 bits
};

int main() {
    struct Flags f = {0};
    
    f.flag1 = 1;
    f.flag2 = 0;
    f.value = 42;
    
    printf("Size: %zu bytes\n", sizeof(struct Flags));  // Typically 4 bytes
    printf("flag1: %u, flag2: %u, value: %u\n", 
        f.flag1, f.flag2, f.value);
    
    return 0;
}

// Common use: packing multiple flags efficiently
struct Permission {
    unsigned int read : 1;
    unsigned int write : 1;
    unsigned int execute : 1;
    unsigned int : 5;  // Unnamed bit field (padding)
};
```

### 6.10 Union vs Struct

```c
struct StructExample {
    int i;
    float f;
    char c;
};
// All members have separate memory

union UnionExample {
    int i;
    float f;
    char c;
};
// All members share the same memory

int main() {
    struct StructExample s = {10, 3.14, 'A'};
    printf("Struct size: %zu\n", sizeof(s));  // 12 bytes
    printf("i=%d, f=%.2f, c=%c\n", s.i, s.f, s.c);  // All valid
    
    union UnionExample u;
    u.i = 10;
    printf("Union size: %zu\n", sizeof(u));  // 4 bytes (size of largest member)
    printf("i=%d\n", u.i);  // 10
    
    u.f = 3.14;
    printf("f=%.2f\n", u.f);  // 3.14
    printf("i=%d\n", u.i);    // GARBAGE (overwritten by float)
    
    return 0;
}
```

### 6.11 typedef with Structures

```c
// Without typedef
struct Point {
    int x;
    int y;
};
struct Point p1;  // Must use 'struct' keyword

// With typedef
typedef struct {
    int x;
    int y;
} Point;
Point p2;  // Cleaner

// typedef with named struct
typedef struct NodeStruct {
    int data;
    struct NodeStruct *next;  // Must use struct name here
} Node;
Node *head;  // Can use typedef name

// Multiple typedefs
typedef struct Point Point2D;
typedef struct Point Coordinate;
Point2D p3;
Coordinate p4;
```

### 6.12 Structure Comparison

```c
struct Point {
    int x;
    int y;
};

int main() {
    struct Point p1 = {10, 20};
    struct Point p2 = {10, 20};
    
    // WRONG: Can't compare structures directly
    // if (p1 == p2) { }  // ERROR
    
    // CORRECT: Compare member by member
    if (p1.x == p2.x && p1.y == p2.y) {
        printf("Points are equal\n");
    }
    
    // Or use memcmp (be careful with padding!)
    if (memcmp(&p1, &p2, sizeof(struct Point)) == 0) {
        printf("Points are equal\n");
    }
    
    // Better: write comparison function
    int points_equal(struct Point *a, struct Point *b) {
        return a->x == b->x && a->y == b->y;
    }
    
    if (points_equal(&p1, &p2)) {
        printf("Points are equal\n");
    }
    
    return 0;
}
```

### 6.13 Flexible Array Members (C99+)

```c
struct Buffer {
    int size;
    char data[];  // Flexible array member (must be last)
};

int main() {
    int n = 10;
    
    // Allocate structure plus array space
    struct Buffer *buf = 
        (struct Buffer*)malloc(sizeof(struct Buffer) + n * sizeof(char));
    
    if (buf != NULL) {
        buf->size = n;
        strcpy(buf->data, "Hello");
        
        printf("Size: %d, Data: %s\n", buf->size, buf->data);
        
        free(buf);
    }
    
    return 0;
}
```

### 6.14 Anonymous Structures and Unions (C11+)

```c
struct Shape {
    int type;  // 1 = circle, 2 = rectangle
    
    union {  // Anonymous union
        struct {  // Anonymous struct
            int radius;
        };
        struct {  // Anonymous struct
            int width;
            int height;
        };
    };
};

int main() {
    struct Shape circle;
    circle.type = 1;
    circle.radius = 10;  // Direct access (no union name needed)
    
    struct Shape rect;
    rect.type = 2;
    rect.width = 20;
    rect.height = 30;
    
    return 0;
}
```

---

## ADDITIONAL CRITICAL CONCEPTS

### Memory Debugging Tips

```c
// 1. Always initialize pointers
int *p = NULL;  // Not: int *p;

// 2. Check malloc return value
int *arr = (int*)malloc(n * sizeof(int));
if (arr == NULL) {
    // Handle error
}

// 3. Free in reverse order of allocation
int *a = malloc(sizeof(int));
int *b = malloc(sizeof(int));
free(b);
free(a);

// 4. Set to NULL after free
free(ptr);
ptr = NULL;

// 5. Use valgrind to detect leaks
// Compile: gcc -g program.c -o program
// Run: valgrind --leak-check=full ./program
```

### Common MCQ Traps

```c
// 1. Array decay
int arr[5];
sizeof(arr);     // 20 bytes (5 * 4)
sizeof(&arr);    // 8 bytes (pointer size on 64-bit)
sizeof(&arr[0]); // 8 bytes (pointer size)

// 2. Pointer arithmetic
int arr[5] = {1, 2, 3, 4, 5};
int *p = arr + 2;
printf("%d\n", p[-1]);  // Prints 2 (arr[1])

// 3. Function pointers and parentheses
int (*pf)(int, int);  // Pointer to function
int *pf(int, int);    // Function returning pointer

// 4. Precedence
int *p[10];    // Array of 10 pointers to int
int (*p)[10];  // Pointer to array of 10 ints

// 5. String literals
char *s = "Hello";
s[0] = 'h';  // UNDEFINED BEHAVIOR (modifying literal)

char s[] = "Hello";
s[0] = 'h';  // OK (array is modifiable)

// 6. Sizeof with pointers
void func(int arr[10]) {
    sizeof(arr);  // Returns sizeof(int*), NOT 40!
}

// 7. Const placement
const int *p;      // Can't change *p
int * const p;     // Can't change p
const int * const p;  // Can't change either

// 8. Structure size
struct {char c; int i;} s;
sizeof(s);  // Usually 8, not 5 (due to padding)

// 9. Post-increment with pointers
int arr[] = {1, 2, 3};
int *p = arr;
printf("%d\n", *p++);  // Prints 1, then increments p

// 10. NULL pointer dereference
int *p = NULL;
if (p) { *p = 5; }  // Safe
if (!p) {} else { *p = 5; }  // Also safe
*p = 5;  // CRASH

// 11. Dangling else
if (condition1)
    if (condition2)
        statement1;
else  // Associates with inner if, not outer!
    statement2;

// 12. Recursion without base case
int factorial(int n) {
    return n * factorial(n - 1);  // Missing base case!
}

// 13. Off-by-one in loops
for (int i = 0; i <= 5; i++) {
    arr[i] = 0;  // Bug if arr has size 5
}

// 14. Memory leak in loop
for (int i = 0; i < 1000; i++) {
    int *p = malloc(sizeof(int));
    // Missing free(p) - leaks 1000 allocations!
}

// 15. Returning local address
int* bad_function() {
    int x = 10;
    return &x;  // DANGEROUS - x is destroyed
}
```

### Performance Considerations

```c
// 1. Pass large structs by pointer
void process_by_value(struct LargeStruct s);  // Slow (copies entire struct)
void process_by_pointer(struct LargeStruct *s);  // Fast

// 2. Use const to prevent modification
void process(const struct LargeStruct *s);  // Efficient + safe

// 3. Cache locality
// Better: access array elements sequentially
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        matrix[i][j] = 0;  // Good cache usage
    }
}

// Worse: column-major access in row-major layout
for (int j = 0; j < cols; j++) {
    for (int i = 0; i < rows; i++) {
        matrix[i][j] = 0;  // Poor cache usage
    }
}

// 4. Recursion vs iteration
// Iteration is typically faster (no function call overhead)
// Recursion can be clearer for naturally recursive problems

// 5. Memory allocation overhead
// Allocate once, reuse
int *arr = malloc(1000 * sizeof(int));
// Better than allocating 1000 times in a loop
```

---

## QUICK REFERENCE TABLES

### Pointer Operations
| Operation | Syntax | Description |
|-----------|--------|-------------|
| Declare | `int *p;` | Pointer to int |
| Address-of | `p = &x;` | Get address of x |
| Dereference | `*p = 5;` | Set value at address |
| Arithmetic | `p + 1` | Move to next element |
| Array access | `p[i]` | Same as `*(p + i)` |
| Compare | `p1 == p2` | Check if same address |
| NULL check | `if (p)` | True if not NULL |

### Array vs Pointer Differences
| Feature | Array | Pointer |
|---------|-------|---------|
| sizeof | Size of entire array | Size of pointer |
| Modification | Can't reassign | Can reassign |
| Initialization | `int a[5] = {0};` | `int *p = NULL;` |
| As parameter | Decays to pointer | Remains pointer |
| Address | &a is ptr to array | &p is ptr to pointer |

### Memory Allocation Functions
| Function | Description | Initialization | Returns |
|----------|-------------|----------------|---------|
| malloc(size) | Allocate size bytes | Uninitialized | void* |
| calloc(n, size) | Allocate n*size bytes | Zero-initialized | void* |
| realloc(ptr, size) | Resize allocation | Preserves data | void* |
| free(ptr) | Deallocate memory | N/A | void |

### Recursion Checklist
- [ ] Base case defined
- [ ] Recursive case makes progress toward base
- [ ] No infinite recursion
- [ ] Stack depth reasonable
- [ ] Consider iterative alternative
- [ ] Understand call stack behavior

### Structure Memory Tips
- Order members largest to smallest to minimize padding
- Use `offsetof()` to check member positions
- Be aware of alignment requirements
- Use `#pragma pack` only when necessary
- Understand union vs struct memory layout

---

## END OF NOTES

These comprehensive notes cover all major aspects of pointers, arrays, memory allocation, linked lists, recursion, and structures in C. Use these as a reference during your MCQ exam to quickly look up syntax, common patterns, edge cases, and potential pitfalls.
