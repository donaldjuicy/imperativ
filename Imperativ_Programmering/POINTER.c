#include <stdio.h>      // Includes standard input/output functions like printf
#include <stdlib.h>     // Includes memory allocation functions like malloc, free

/* ============================================================
   1. BASIC POINTER
   ============================================================ */
void basic_pointer() {

    int a = 10;                 // Declare an integer variable 'a' and assign value 10

    int *p = &a;                // Declare pointer 'p' that stores address of 'a'

    printf("a = %d\n", a);      // Prints value stored in variable 'a'

    printf("&a = %p\n", &a);    // Prints address of variable 'a'

    printf("p = %p\n", p);      // Prints address stored inside pointer 'p'

    printf("*p = %d\n", *p);    // Dereference pointer 'p' to get value at that address
}

/* ============================================================
   2. POINTER ARITHMETIC
   ============================================================ */
void pointer_arithmetic() {

    int arr[3] = {10, 20, 30};  // Declare integer array with 3 elements

    int *p = arr;               // Pointer points to first element of array

    printf("%d\n", *p);         // Prints value at arr[0]

    printf("%d\n", *(p + 1));   // Moves pointer to next integer and prints arr[1]

    printf("%d\n", *(p + 2));   // Moves pointer two positions and prints arr[2]
}

/* ============================================================
   3. POINTER & ARRAY RELATION
   ============================================================ */
void array_pointer_relation() {

    int arr[5] = {1,2,3,4,5};   // Declare array of 5 integers

    printf("%d\n", arr[0]);     // Access first element using array index

    printf("%d\n", *(arr));     // Access first element using pointer notation

    printf("%d\n", *(arr + 3)); // Access 4th element using pointer arithmetic
}

/* ============================================================
   4. POINTER TO STRING
   ============================================================ */
void string_pointer() {

    char *str = "Hello";        // Pointer pointing to string literal stored in read-only memory

    printf("%s\n", str);        // Prints entire string

    printf("%c\n", *str);       // Prints first character of string

    printf("%c\n", *(str + 1)); // Prints second character of string
}

/* ============================================================
   5. DOUBLE POINTER
   ============================================================ */
void double_pointer() {

    int a = 10;                 // Declare integer variable

    int *p = &a;                // Pointer 'p' stores address of 'a'

    int **pp = &p;              // Double pointer stores address of pointer 'p'

    printf("%d\n", a);          // Prints value of 'a'

    printf("%d\n", *p);         // Dereferencing 'p' gives value of 'a'

    printf("%d\n", **pp);       // Double dereference gives value of 'a'
}

/* ============================================================
   6. TRIPLE POINTER
   ============================================================ */
void triple_pointer() {

    int a = 5;                  // Declare integer variable

    int *p = &a;                // Pointer to integer

    int **pp = &p;              // Pointer to pointer

    int ***ppp = &pp;           // Pointer to pointer to pointer

    printf("%d\n", ***ppp);     // Triple dereference gives value of 'a'
}

/* ============================================================
   7. POINTER TO ARRAY
   ============================================================ */
void pointer_to_array() {

    int arr[3] = {10,20,30};    // Declare array of 3 integers

    int (*p)[3] = &arr;         // Pointer that points to entire array of 3 integers

    printf("%d\n", (*p)[0]);    // Access first element of array using pointer

    printf("%d\n", (*p)[1]);    // Access second element

    printf("%d\n", (*p)[2]);    // Access third element
}

/* ============================================================
   8. ARRAY OF POINTERS
   ============================================================ */
void array_of_pointers() {

    int a = 1, b = 2, c = 3;    // Declare three integer variables

    int *arr[3] = {&a, &b, &c}; // Array that stores addresses of integers

    printf("%d\n", *arr[0]);    // Dereference pointer at index 0

    printf("%d\n", *arr[1]);    // Dereference pointer at index 1

    printf("%d\n", *arr[2]);    // Dereference pointer at index 2
}

/* ============================================================
   9. POINTER TO FUNCTION
   ============================================================ */
int add(int x, int y) {

    return x + y;               // Return sum of two integers
}

void function_pointer() {

    int (*fp)(int, int) = add;  // Declare function pointer and assign address of add()

    printf("%d\n", fp(2, 3));   // Call function using function pointer
}

/* ============================================================
   10. FUNCTION RETURNING POINTER
   ============================================================ */
int* return_pointer() {

    int *p = (int*)malloc(sizeof(int)); // Allocate memory for one integer

    *p = 100;                  // Store value 100 in allocated memory

    return p;                  // Return pointer to allocated memory
}

void function_returning_pointer() {

    int *p = return_pointer();  // Receive pointer returned by function

    printf("%d\n", *p);         // Print value stored at returned address

    free(p);                    // Free dynamically allocated memory
}

/* ============================================================
   11. POINTER WITH STRUCT
   ============================================================ */
struct Student {

    int id;                     // Structure member for student ID

    float marks;                // Structure member for marks
};

void struct_pointer() {

    struct Student s = {1, 95.5}; // Initialize structure variable

    struct Student *p = &s;      // Pointer to structure

    printf("%d\n", p->id);       // Access structure member using arrow operator

    printf("%.2f\n", p->marks); // Access float member
}

/* ============================================================
   12. VOID POINTER
   ============================================================ */
void void_pointer() {

    int a = 10;                 // Declare integer variable

    float b = 5.5;              // Declare float variable

    void *vp;                   // Declare void pointer

    vp = &a;                    // Store address of integer in void pointer

    printf("%d\n", *(int*)vp);  // Typecast and dereference void pointer

    vp = &b;                    // Store address of float in void pointer

    printf("%.1f\n", *(float*)vp); // Typecast and dereference again
}

/* ============================================================
   13. DYNAMIC MEMORY ALLOCATION
   ============================================================ */
void dynamic_memory() {

    int *p = (int*)malloc(3 * sizeof(int)); // Allocate memory for 3 integers

    p[0] = 1;                   // Store value at first position

    p[1] = 2;                   // Store value at second position

    p[2] = 3;                   // Store value at third position

    for(int i = 0; i < 3; i++)   // Loop through allocated memory
        printf("%d ", p[i]);    // Print each element

    free(p);                    // Free allocated memory
}

/* ============================================================
   14. COMMON POINTER ERRORS
   ============================================================ */
void pointer_errors() {

    int *p = NULL;              // NULL pointer (safe until dereferenced)

    // printf("%d", *p);        // Dereferencing NULL causes segmentation fault

    int *wild;                  // Wild pointer (uninitialized, dangerous)

    int a = 10;                 // Declare integer

    int *dangling = &a;         // Pointer points to local variable

    // When function ends, 'a' is destroyed → dangling pointer
}

/* ============================================================
   MAIN FUNCTION
   ============================================================ */
int main() {

    basic_pointer();            // Call basic pointer example

    pointer_arithmetic();       // Call pointer arithmetic example

    array_pointer_relation();   // Call array-pointer relation example

    string_pointer();           // Call string pointer example

    double_pointer();           // Call double pointer example

    triple_pointer();           // Call triple pointer example

    pointer_to_array();         // Call pointer-to-array example

    array_of_pointers();        // Call array of pointers example

    function_pointer();         // Call function pointer example

    function_returning_pointer();// Call function returning pointer example

    struct_pointer();           // Call structure pointer example

    void_pointer();             // Call void pointer example

    dynamic_memory();           // Call dynamic memory example

    pointer_errors();           // Call pointer errors example

    return 0;                   // End of program
}
