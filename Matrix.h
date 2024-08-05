#ifndef _MATRIX_H_INCLUDE_
#define _MATRIX_H_INCLUDE_
#include "List.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct entry {
    int col_index;
    double value;
} entry_t;

typedef struct matrix {
    int n;
    List *rows;
} matrix_t;

typedef matrix_t* Matrix;

// These are explained in the pdf
Matrix newMatrix(int n);
void freeMatrix(Matrix *pM);
int size(Matrix M);
int NNZ(Matrix M);
int equals(Matrix A, Matrix B);
void changeEntry(Matrix M, int i, int j, double x);
void makeZero(Matrix M);
Matrix copy(Matrix A);
Matrix transpose(Matrix A);
Matrix scalarMult(double x, Matrix A);
Matrix sum(Matrix A, Matrix B);
Matrix diff(Matrix A, Matrix B);
Matrix product(Matrix A, Matrix B);
void printMatrix(FILE *out, Matrix M); 


#endif // !_MATRIX_H_INCLUDE_
