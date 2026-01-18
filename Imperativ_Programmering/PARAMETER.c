#include <stdio.h>      // Provides printf function
#include <stdlib.h>     // Provides malloc and free

/* ============================================================
   1. PASS BY VALUE (DEFAULT IN C)
   ============================================================ */
void pass_by_value(int x) {

    x = 100;            // Modifies local copy only
}

void demo_pass_by_value() {

    int a = 10;         // Declare variable

    pass_by_value(a);   // Pass value of 'a'

    printf("%d\n", a);  // Original value unchanged
}

/* ============================================================
   2. PASS BY REFERENCE (USING POINTER)
   ============================================================ */
void pass_by_reference(int *x) {

    *x = 100;           // Modify value at address
}

void demo_pass_by_reference() {

    int a = 10;         // Declare variable

    pass_by_reference(&a); // Pass address of 'a'

    printf("%d\n", a);  // Value changed
}

/* ============================================================
   3. ARRAY AS PARAMETER
   ============================================================ */
void array_parameter(int arr[], int size) {

    for (int i = 0; i < size; i++) {   // Loop through array
        printf("%d ", arr[i]);        // Access elements
    }
}

void demo_array_parameter() {

    int arr[3] = {1, 2, 3};           // Declare array

    array_parameter(arr, 3);          // Pass array to function
}

/* ============================================================
   4. ARRAY PARAMETER AS POINTER
   ============================================================ */
void array_as_pointer(int *arr, int size) {

    for (int i = 0; i < size; i++) {   // Loop through elements
        printf("%d ", *(arr + i));    // Pointer arithmetic
    }
}

/* ============================================================
   5. 2D ARRAY AS PARAMETER
   ============================================================ */
void two_d_array_param(int arr[][3], int rows) {

    for (int i = 0; i < rows; i++) {        // Loop rows
        for (int j = 0; j < 3; j++) {       // Loop columns
            printf("%d ", arr[i][j]);      // Access elements
        }
        printf("\n");
    }
}

void demo_2d_array_param() {

    int mat[2][3] = {{1,2,3},{4,5,6}};  // Declare 2D array

    two_d_array_param(mat, 2);          // Pass 2D array
}

/* ============================================================
   6. POINTER AS PARAMETER
   ============================================================ */
void pointer_parameter(int *p) {

    printf("%d\n", *p);    // Dereference pointer
}

/* ============================================================
   7. DOUBLE POINTER AS PARAMETER
   ============================================================ */
void double_pointer_parameter(int **pp) {

    printf("%d\n", **pp);  // Double dereference
}

/* ============================================================
   8. STRUCT AS PARAMETER (PASS BY VALUE)
   ============================================================ */
struct Student {

    int id;               // Student ID
    float marks;          // Student marks
};

void struct_by_value(struct Student s) {

    printf("%d %.1f\n", s.id, s.marks); // Access structure members
}

/* ============================================================
   9. STRUCT AS PARAMETER (PASS BY REFERENCE)
   ============================================================ */
void struct_by_reference(struct Student *s) {

    s->marks += 5;        // Modify structure member
}

/* ============================================================
   10. FUNCTION POINTER AS PARAMETER
   ============================================================ */
int add(int a, int b) {

    return a + b;         // Return sum
}

void function_pointer_param(int (*fp)(int, int)) {

    printf("%d\n", fp(2, 3));  // Call function via pointer
}

/* ============================================================
   11. VOID POINTER AS PARAMETER
   ============================================================ */
void void_pointer_param(void *vp, char type) {

    if (type == 'i') {                    // If integer
        printf("%d\n", *(int*)vp);        // Typecast and print
    }
    else if (type == 'f') {               // If float
        printf("%.1f\n", *(float*)vp);    // Typecast and print
    }
}

/* ============================================================
   12. CONST PARAMETER
   ============================================================ */
void const_parameter(const int x) {

    // x = 10;           // ❌ Cannot modify const parameter

    printf("%d\n", x);   // Can only read value
}

/* ============================================================
   13. POINTER TO CONST VS CONST POINTER
   ============================================================ */
void const_pointer_examples() {

    int a = 10;
    int b = 20;

    const int *p1 = &a;  // Pointer to constant integer
    // *p1 = 5;           // ❌ Cannot modify value
    p1 = &b;             // Allowed

    int *const p2 = &a;  // Constant pointer
    *p2 = 15;            // Allowed
    // p2 = &b;           // ❌ Cannot change address
}

/* ============================================================
   14. VARIABLE LENGTH ARGUMENTS (stdarg)
   ============================================================ */
#include <stdarg.h>      // Required for variable arguments

void variable_arguments(int count, ...) {

    va_list args;               // Declare argument list
    va_start(args, count);      // Initialize list

    for (int i = 0; i < count; i++) {
        printf("%d ", va_arg(args, int)); // Access each argument
    }

    va_end(args);               // Clean up
}

/* ============================================================
   MAIN FUNCTION
   ============================================================ */
int main() {

    demo_pass_by_value();            // Demonstrate pass by value

    demo_pass_by_reference();        // Demonstrate pass by reference

    demo_array_parameter();          // Demonstrate array parameter

    demo_2d_array_param();           // Demonstrate 2D array parameter

    int x = 50;
    pointer_parameter(&x);           // Pass pointer as parameter

    int *p = &x;
    double_pointer_parameter(&p);    // Pass double pointer

    struct Student s = {1, 90.0};
    struct_by_value(s);              // Pass struct by value
    struct_by_reference(&s);          // Pass struct by reference
    printf("%.1f\n", s.marks);        // Confirm modification

    function_pointer_param(add);      // Pass function as parameter

    int i = 10;
    float f = 5.5;
    void_pointer_param(&i, 'i');      // Pass int via void pointer
    void_pointer_param(&f, 'f');      // Pass float via void pointer

    const_parameter(25);              // Pass const parameter

    variable_arguments(3, 1, 2, 3);   // Pass variable arguments

    return 0;                         // End program
}
