#include "Matrix.h"
#include <stdio.h>

int main() {

    Matrix A = newMatrix(3000);
    Matrix B = newMatrix(3000);
    
    changeEntry(A, 1,1,1); changeEntry(B, 1,1,1);
    changeEntry(A, 1,2,2); changeEntry(B, 1,2,0);
    changeEntry(A, 1,3,3); changeEntry(B, 1,3,1);
    changeEntry(A, 2,1,4); changeEntry(B, 2,1,0);
    changeEntry(A, 2,2,5); changeEntry(B, 2,2,1);
    changeEntry(A, 2,3,6); changeEntry(B, 2,3,0);
    changeEntry(A, 3,1,7); changeEntry(B, 3,1,1);
    changeEntry(A, 3,2,8); changeEntry(B, 3,2,1);
    changeEntry(A, 3,3,9); changeEntry(B, 3,3,1);
    printMatrix(stdout, A);
    printf("\n");
    printMatrix(stdout, B);
    printf("\n");
    Matrix C = sum(A, B);
    printMatrix(stdout, C);
    printf("\n");
    Matrix D = transpose(B);
    printMatrix(stdout, D);
    printf("\n");
    Matrix E = transpose(C);
    printMatrix(stdout, E);
    printf("\n");
    Matrix F = product(B, B);
    printMatrix(stdout, F);
    printf("\n");
    Matrix G = sum(F,F);
    printMatrix(stdout, G);
    printf("\n");
    Matrix H = diff(E,F);
    printMatrix(stdout, H);
    printf("\n");
    Matrix H_copy = copy(H);
    printMatrix(stdout, H_copy);
    printf("H_copy has %d non-zeros\n", NNZ(H_copy));
    printf("H, H_copy are equal? %d\n\n", equals(H, H_copy));
    Matrix I = scalarMult(0.5, H);
    printMatrix(stdout, I);
    printf("\n");

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    freeMatrix(&H_copy);
    freeMatrix(&I);
}
