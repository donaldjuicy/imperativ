#include <stdio.h>      // Provides printf function for output
#include <stdlib.h>     // Provides dynamic memory allocation functions

/* ============================================================
   1. BASIC ARRAY DECLARATION & ACCESS
   ============================================================ */
void basic_array() {

    int arr[5] = {10, 20, 30, 40, 50};  // Declare integer array with 5 elements

    printf("%d\n", arr[0]);             // Access first element of array

    printf("%d\n", arr[4]);             // Access last element of array
}

/* ============================================================
   2. ARRAY TRAVERSAL USING LOOP
   ============================================================ */
void array_traversal() {

    int arr[4] = {1, 2, 3, 4};           // Declare array

    for (int i = 0; i < 4; i++) {        // Loop through array indices
        printf("%d ", arr[i]);           // Print each element
    }
}

/* ============================================================
   3. ARRAY & POINTER RELATION
   ============================================================ */
void array_pointer_relation() {

    int arr[3] = {5, 10, 15};            // Declare integer array

    printf("%d\n", arr[0]);              // Access using array notation

    printf("%d\n", *arr);                // Access first element using pointer

    printf("%d\n", *(arr + 1));           // Access second element using pointer arithmetic
}

/* ============================================================
   4. ARRAY AS FUNCTION ARGUMENT
   ============================================================ */
void print_array(int arr[], int size) {  // Function receiving array and size

    for (int i = 0; i < size; i++) {     // Loop through array
        printf("%d ", arr[i]);           // Print each element
    }
}

void array_as_argument() {

    int arr[3] = {7, 8, 9};              // Declare array

    print_array(arr, 3);                 // Pass array to function
}

/* ============================================================
   5. 2D ARRAY (MATRIX)
   ============================================================ */
void two_d_array() {

    int matrix[2][3] = {                 // Declare 2x3 matrix
        {1, 2, 3},                       // First row
        {4, 5, 6}                        // Second row
    };

    for (int i = 0; i < 2; i++) {         // Loop rows
        for (int j = 0; j < 3; j++) {     // Loop columns
            printf("%d ", matrix[i][j]);  // Print element
        }
        printf("\n");                    // New line after each row
    }
}

/* ============================================================
   6. POINTER TO 2D ARRAY
   ============================================================ */
void pointer_to_2d_array() {

    int arr[2][2] = {{1, 2}, {3, 4}};     // Declare 2D array

    int (*p)[2] = arr;                   // Pointer to array of 2 integers

    printf("%d\n", p[0][0]);              // Access element using pointer

    printf("%d\n", p[1][1]);              // Access another element
}

/* ============================================================
   7. ARRAY OF STRINGS
   ============================================================ */
void array_of_strings() {

    char *names[] = {"Alice", "Bob", "Charlie"}; // Array of string pointers

    for (int i = 0; i < 3; i++) {          // Loop through strings
        printf("%s\n", names[i]);          // Print each string
    }
}

/* ============================================================
   8. CHARACTER ARRAY (STRING)
   ============================================================ */
void char_array() {

    char str[] = "Hello";                 // Character array storing string

    printf("%s\n", str);                  // Print entire string

    printf("%c\n", str[0]);               // Print first character
}

/* ============================================================
   9. MULTIDIMENSIONAL ARRAY (3D)
   ============================================================ */
void three_d_array() {

    int arr[2][2][2] = {                  // Declare 3D array
        {{1, 2}, {3, 4}},
        {{5, 6}, {7, 8}}
    };

    printf("%d\n", arr[1][0][1]);          // Access specific element
}

/* ============================================================
   10. DYNAMIC ARRAY (malloc)
   ============================================================ */
void dynamic_array() {

    int n = 5;                            // Number of elements

    int *arr = (int*)malloc(n * sizeof(int)); // Allocate memory dynamically

    for (int i = 0; i < n; i++) {          // Initialize array
        arr[i] = i + 1;
    }

    for (int i = 0; i < n; i++) {          // Print array
        printf("%d ", arr[i]);
    }

    free(arr);                             // Free allocated memory
}

/* ============================================================
   11. ARRAY SIZE USING sizeof
   ============================================================ */
void array_size() {

    int arr[6] = {1,2,3,4,5,6};            // Declare array

    int size = sizeof(arr) / sizeof(arr[0]); // Calculate number of elements

    printf("%d\n", size);                  // Print size
}

/* ============================================================
   12. ARRAY INITIALIZATION METHODS
   ============================================================ */
void array_initialization() {

    int a[5] = {1, 2};                     // Remaining elements set to 0

    int b[5] = {0};                        // All elements set to 0

    for (int i = 0; i < 5; i++) {           // Loop through array
        printf("%d ", a[i]);               // Print array 'a'
    }
}

/* ============================================================
   13. COMMON ARRAY MISTAKES
   ============================================================ */
void array_errors() {

    int arr[3] = {1, 2, 3};                // Declare array

    // printf("%d", arr[5]);               // Out-of-bounds access (undefined behavior)

    // arr = NULL;                         // ❌ Arrays cannot be assigned
}

/* ============================================================
   14. ARRAY VS POINTER DIFFERENCE
   ============================================================ */
void array_vs_pointer() {

    int arr[3] = {1, 2, 3};                // Array declaration

    int *p = arr;                          // Pointer to first element

    printf("%lu\n", sizeof(arr));          // Total size of array in bytes

    printf("%lu\n", sizeof(p));            // Size of pointer (usually 8 bytes)
}

/* ============================================================
   MAIN FUNCTION
   ============================================================ */
int main() {

    basic_array();                         // Call basic array example

    array_traversal();                     // Call traversal example

    array_pointer_relation();              // Call pointer relation example

    array_as_argument();                   // Call array argument example

    two_d_array();                         // Call 2D array example

    pointer_to_2d_array();                 // Call pointer to 2D array

    array_of_strings();                    // Call array of strings

    char_array();                          // Call char array example

    three_d_array();                       // Call 3D array example

    dynamic_array();                       // Call dynamic array example

    array_size();                          // Call array size example

    array_initialization();                // Call initialization example

    array_errors();                        // Call array errors example

    array_vs_pointer();                    // Call array vs pointer example

    return 0;                              // End program
}
