#include "Matrix.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 3) { 
        fprintf(stderr, "You need to provide 2 arguments\n");
        exit(EXIT_FAILURE);
    }
    char* in_fname = argv[1];
    char* out_fname = argv[2];

    FILE *infile = fopen(in_fname, "r");
    if (infile == NULL) { 
        fprintf(stderr, "Error opening file\n");
        exit(EXIT_FAILURE);
    }

    int n, a, b;
    if(fscanf(infile, "%d %d %d\n", &n, &a, &b) != 3) 
        goto fileread_err;
    fscanf(infile, "\n");

    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);
    for(int i = 0; i < a; i++) {
        int r, c; double v;
        if(fscanf(infile, "%d %d %lf\n", &r, &c, &v) != 3) {
            freeMatrix(&A); freeMatrix(&B);
            goto fileread_err;
        }
        changeEntry(A, r, c, v);
    }
    fscanf(infile, "\n");
    for(int i = 0; i < b; i++) {
        int r, c; double v;
        if(fscanf(infile, "%d %d %lf\n", &r, &c, &v) != 3) {
            freeMatrix(&A); freeMatrix(&B);
            goto fileread_err;
        }
        changeEntry(B, r, c, v);
    }
    
    FILE* outfile = fopen(out_fname, "w");
    if (outfile == NULL) {
        fprintf(stderr, "Error opening output file\n");
        exit(EXIT_FAILURE);
    }
    
    fprintf(outfile, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(outfile, A);
    fprintf(outfile, "\n");

    fprintf(outfile, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(outfile, B);
    fprintf(outfile, "\n");
    
    Matrix C = scalarMult(1.5, A);
    fprintf(outfile, "(1.5)*A =\n");
    printMatrix(outfile, C);
    fprintf(outfile, "\n");

    Matrix D = sum(A, B);
    fprintf(outfile, "A+B =\n");
    printMatrix(outfile, D);
    fprintf(outfile, "\n");

    Matrix E = sum(A, A);
    fprintf(outfile, "A+A =\n");
    printMatrix(outfile, E);
    fprintf(outfile, "\n");
    
    Matrix F = diff(B, A);
    fprintf(outfile, "B-A =\n");
    printMatrix(outfile, F);
    fprintf(outfile, "\n");

    Matrix G = diff(A, A);
    fprintf(outfile, "A-A =\n");
    printMatrix(outfile, G);
    fprintf(outfile, "\n");

    Matrix H = transpose(A);
    fprintf(outfile, "Transpose(A) =\n");
    printMatrix(outfile, H);
    fprintf(outfile, "\n");

    Matrix I = product(A, B);
    fprintf(outfile, "A*B =\n");
    printMatrix(outfile, I);
    fprintf(outfile, "\n");

    Matrix J = product(B, B);
    fprintf(outfile, "B*B =\n");
    printMatrix(outfile, J);
    fprintf(outfile, "\n");

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    freeMatrix(&I);
    freeMatrix(&J);

    return EXIT_SUCCESS;

fileread_err:
    fprintf(stderr, "Error Parsing File\n");
    exit(EXIT_FAILURE);
}
