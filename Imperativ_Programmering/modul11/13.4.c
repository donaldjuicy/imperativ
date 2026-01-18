/*
=========================================================
FORMÅL:
Programmet håndterer matricer i to tekstbaserede 
repræsentationer:

1) Generel repræsentation:
   - Første linje: antal rækker og søjler
   - Derefter én linje per række, med alle elementer

2) Tynd (sparse) repræsentation:
   - Første linje: antal rækker og søjler
   - Hver efterfølgende linje: række, søjle, værdi (kun ikke-nul elementer)

Programmet indeholder to funktioner:
- general_to_sparse : konverterer fra generel til tynd
- sparse_to_general : konverterer fra tynd til generel

Eksempel: 
Generel matrix:
4 3
0.0 0.0 1.0
0.0 0.0 0.0
2.0 0.0 0.0
0.0 3.0 0.0

Sparse repræsentation:
4 3
1 3 1.000000
3 1 2.000000
4 2 3.000000
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>

/*
=========================================================
Funktion: general_to_sparse

Input:
- char *input_file  : navn på fil med generel matrix
- char *output_file : navn på fil til tynd matrix

Funktion:
- Læser matricen fra input_file
- Skriver kun ikke-nul elementer i output_file
=========================================================
*/
void general_to_sparse(const char *input_file, const char *output_file)
{
    FILE *ifp = fopen(input_file, "r");    // åbn input-fil til læsning
    if (!ifp) {
        printf("Kan ikke åbne inputfil %s\n", input_file);
        return;
    }

    FILE *ofp = fopen(output_file, "w");   // åbn output-fil til skrivning
    if (!ofp) {
        printf("Kan ikke åbne outputfil %s\n", output_file);
        fclose(ifp);
        return;
    }

    int rows, cols;
    fscanf(ifp, "%d %d", &rows, &cols);    // læs dimensioner

    // Skriv dimensioner på første linje i sparse-fil
    fprintf(ofp, "%d %d\n", rows, cols);

    // Allokér matrix dynamisk
    double **matrix = malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++)
        matrix[i] = malloc(cols * sizeof(double));

    // Læs alle elementer
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            fscanf(ifp, "%lf", &matrix[i][j]);

    // Skriv kun ikke-nul elementer
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (matrix[i][j] != 0.0)
                // bemærk: 1-baserede index
                fprintf(ofp, "%d %d %f\n", i+1, j+1, matrix[i][j]);

    // Frigør dynamisk hukommelse
    for (int i = 0; i < rows; i++)
        free(matrix[i]);
    free(matrix);

    fclose(ifp);
    fclose(ofp);
}

/*
=========================================================
Funktion: sparse_to_general

Input:
- char *input_file  : fil med tynd matrix
- char *output_file : fil til generel matrix

Funktion:
- Læser dimensioner og ikke-nul elementer
- Genererer fuld matrix, fylder nul hvor elementer ikke er angivet
- Skriver til output_file i generel form
=========================================================
*/
void sparse_to_general(const char *input_file, const char *output_file)
{
    FILE *ifp = fopen(input_file, "r");    // åbn input-fil til læsning
    if (!ifp) {
        printf("Kan ikke åbne inputfil %s\n", input_file);
        return;
    }

    FILE *ofp = fopen(output_file, "w");   // åbn output-fil til skrivning
    if (!ofp) {
        printf("Kan ikke åbne outputfil %s\n", output_file);
        fclose(ifp);
        return;
    }

    int rows, cols;
    fscanf(ifp, "%d %d", &rows, &cols);    // læs dimensioner

    // Allokér matrix og fyld med nul
    double **matrix = malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(double));
        for (int j = 0; j < cols; j++)
            matrix[i][j] = 0.0;
    }

    // Læs ikke-nul elementer indtil EOF
    int r, c;
    double val;
    while (fscanf(ifp, "%d %d %lf", &r, &c, &val) == 3) {
        matrix[r-1][c-1] = val;  // konverter til 0-baseret index
    }

    // Skriv fuld matrix til output-fil
    fprintf(ofp, "%d %d\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            fprintf(ofp, "%f ", matrix[i][j]);
        fprintf(ofp, "\n");
    }

    // Frigør hukommelse
    for (int i = 0; i < rows; i++)
        free(matrix[i]);
    free(matrix);

    fclose(ifp);
    fclose(ofp);
}

/*
=========================================================
MAIN: eksempel på brug
=========================================================
*/
int main(void)
{
    // Konverter fra generel til tynd repræsentation
    general_to_sparse("general_matrix.txt", "sparse_matrix.txt");

    // Konverter tilbage fra tynd til generel repræsentation
    sparse_to_general("sparse_matrix.txt", "general_matrix_out.txt");

    printf("Konvertering færdig.\n");

    return 0;
}
