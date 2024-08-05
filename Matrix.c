#include "Matrix.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>

/* Helper Functions */
static
entry_t* create_entry(int c, double v) {
    entry_t* e = (entry_t*)malloc(sizeof(entry_t));
    if (e == NULL) {
        fprintf(stderr, "failed to allocate matrix entry\n");
        exit(EXIT_FAILURE);
    }
    e->value = v;
    e->col_index = c;
    return e;
}

enum Op { ADD, SUB };

static
void row_sum(List l, List r1, List r2, int op) {
    moveFront(r1); moveFront(r2);
    for(;!(index(r1)<0 && index(r2)<0);) {
        if (index(r1)<0) {
            entry_t* e = (entry_t*)get(r2);
            double val = op == ADD? e->value : -e->value;
            append(l, (void*)create_entry(e->col_index, val));
            moveNext(r2);
        } else if (index(r2)<0) {
            entry_t* e = (entry_t*)get(r1);
            append(l, (void*)create_entry(e->col_index, e->value));
            moveNext(r1);
        } else {
            entry_t* e1 = (entry_t*)get(r1);
            entry_t* e2 = (entry_t*)get(r2);
            if(e1->col_index == e2->col_index) {
                double sum = op == ADD ? e1->value + e2->value
                                       : e1->value - e2->value;
                if (!(sum == (double)(0) || sum == (double)(-0)))
                    append(l, (void*)create_entry(e1->col_index,sum));
                moveNext(r1); if (r1 != r2) moveNext(r2);
            } else if (e1->col_index < e2->col_index) {
                entry_t* e = (entry_t*)get(r1);
                append(l, (void*)create_entry(e->col_index,e->value));
                moveNext(r1);
            } else {
                entry_t* e = (entry_t*)get(r2);
                double val = op == ADD? e->value : -e->value;
                append(l, (void*)create_entry(e->col_index,val));
                moveNext(r2);
            }
        }
    }
}

static
void row_matrix_product(List l, List row, Matrix m) {
    const int max_column = m->n + 1;
    int min_column = max_column;
    moveFront(row);
    if (index(row) < 0) return;
    NodePtr curr = row->head;
    for(; curr != NULL; curr = curr->next) {
        entry_t* e = (entry_t*)curr->data;
        int col = e->col_index;
        List r = m->rows[col-1];
        moveFront(r);
        if(index(r)<0) continue;
        entry_t* e2 = (entry_t*)get(r);
        min_column = e2->col_index < min_column ? e2->col_index : min_column;
    }
    if (min_column == max_column) return;
    int curr_column = min_column;
    for(int left = 1; left == 1; curr_column = min_column) {
        left = 0;
        min_column = max_column;
        double dotprod = 0;
        curr = row->head;
        for(; curr != NULL; curr = curr->next) {
            entry_t* e = (entry_t*)curr->data;
            int col = e->col_index;
            List r = m->rows[col-1];
            if(index(r)<0) continue;
            entry_t* e2 = (entry_t*)get(r);
            int col2 = e2->col_index;
            if (col2 == curr_column) {
                dotprod += (e->value * e2->value);
                moveNext(r);
                if (!(index(r)<0)) {
                    left = 1;
                    e2 = (entry_t*)get(r);
                    col2 = e2->col_index;
                    min_column = col2 < min_column ? col2 : min_column;
                }
            } else {
                left = 1;
                min_column = col2 < min_column ? col2 : min_column;
            }
        }
        if (dotprod != (double)(0) && dotprod != (double)(-0))
            append(l, (void*)create_entry(curr_column, dotprod));
    }  
}
/*------------------*/

Matrix newMatrix(int n) {
    if (n <= 0) return NULL;
    matrix_t* m = (matrix_t*)malloc(sizeof(matrix_t));
    m->n = n;
    List *rows = (List*)malloc(n*sizeof(List));
    for(int i = 0; i < n; i++) { rows[i] = newList(); }
    m->rows = rows;
    return m;
}

void freeMatrix(Matrix *pM) {
    if (pM == NULL || *pM == NULL) return;
    const int n = (*pM)->n;
    makeZero(*pM);
    for(int i = 0; i < n; i++) {
        freeList((*pM)->rows + i); 
    }
    free((*pM)->rows);
    free(*pM);
    *pM = NULL;
}

int size(Matrix M) {
    if (M == NULL) return -1;
    return M->n;
}

int NNZ(Matrix M) {
    if (M == NULL) return -1;
    const int n = M->n;
    int nnz = 0;
    for(int i = 0; i < n; i++) {
        List row = M->rows[i];
        if (row == NULL) continue;
        nnz += length(M->rows[i]);
    }
    return nnz;
}

int equals(Matrix A, Matrix B) {
    if (A == B) return 1;
    if (A == NULL || B == NULL) return 0;
    const int n = A->n;
    if(n != B->n) return 0;
    for(int i = 0; i < n; i++) {
        List l1 = A->rows[i];
        List l2 = B->rows[i];
        moveFront(l1); moveFront(l2);
        if(index(l1) != index(l2)) return 0;
        if (index(l1)<0) continue;
        for(;;moveNext(l1), moveNext(l2)) {
            if(index(l1) != index(l2)) return 0;
            if(index(l1)<0) break;
            entry_t* e1 = (entry_t*)get(l1);
            entry_t* e2 = (entry_t*)get(l2);
            if (e1->col_index != e2->col_index) return 0;
            if (e1->value != e2->value) return 0;
        }
    }
    return 1;
}

void changeEntry(Matrix M, int i, int j, double x) {
    if (M == NULL) return;
    const int n = M->n;
    if (i <= 0 || j <= 0 || i > n || j > n) return;
    List row = (M->rows)[i-1];
    if(length(row) < 0) return;
    if(length(row) == 0) {
        if(x == (double)(0)) { return; }
        prepend(row, (void*)create_entry(j, x));
        return;
    }
    moveFront(row);
    for(;;) {
        if(index(row) < 0) {
            if(x == (double)(0)) return;
            append(row, (void*)create_entry(j, x));
            return;
        }
        entry_t* e = (entry_t*)get(row);
        if(e->col_index == j) {
            if (x == (double)(0)) { free(e); delete(row); }
            else e->value = x;
            return;
        } else if (e->col_index > j) {
            if(x == (double)(0)) return;
            insertBefore(row, (void*)create_entry(j, x));
            return;
        }
        moveNext(row);
    }
}

void makeZero(Matrix M) {
    if (M == NULL) return;
    const int n = M->n;
    for(int i = 0; i < n; i++) {
        List row = M->rows[i];
        if(row == NULL) continue;
        moveFront(row);
        for(; !(index(row)<0);) {
            entry_t* e = (entry_t*)get(row);
            free(e); delete(row);
            moveFront(row);
        }
    }
}

Matrix copy(Matrix M) {
    if (M == NULL) return NULL;
    const int n = M->n;
    Matrix result = newMatrix(n);
    for(int i = 0; i < n; i++) {
        List row = M->rows[i];
        moveFront(row);
        for(; !(index(row)<0); moveNext(row)) {
            entry_t* e = (entry_t*)get(row);
            int c = e->col_index;
            int v = e->value;
            append(result->rows[i], (void*)create_entry(c,v));
        }
    }
    return result;
}

Matrix transpose(Matrix A) {
    if (A == NULL) return NULL;
    const int n = A->n;
    if (n == 0) return NULL;
    Matrix result = newMatrix(n);
    for(int i = 0; i < n; i++) {
        List row = A->rows[i];
        moveFront(row);
        for(; !(index(row)<0); moveNext(row)) {
            entry_t* e = (entry_t*)get(row);
            int row_num = e->col_index;
            int col_num = i+1;
            append(result->rows[row_num-1], 
                   (entry_t*)create_entry(col_num, e->value));
        }
    }
    return result;
}

Matrix scalarMult(double x, Matrix A) {
    if (A == NULL) return NULL;
    const int n = A->n;
    Matrix result = newMatrix(n);
    if (x == (double)(0) || x == (double)(-0)) return result;
    for(int i = 0; i < n; i++) {
        List row = A->rows[i];
        moveFront(row);
        for(; !(index(row)<0); moveNext(row)) {
            entry_t* e = (entry_t*)get(row);
            append(result->rows[i], (entry_t*)create_entry(e->col_index, 
                                                           x*e->value));
        }
    }
    return result;
}

Matrix sum(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) return NULL;
    const int n = A->n;
    if (n != B->n) {
        fprintf(stderr, "Error: Adding incompatible matrices\n");
        return NULL;
    }
    Matrix result = newMatrix(n);
    for(int i = 0; i < n; i++) {
        row_sum(result->rows[i], A->rows[i], B->rows[i], ADD);
    }
    return result;
}

Matrix diff(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) return NULL;
    const int n = A->n;
    if (n != B->n) {
        fprintf(stderr, "Error: Adding incompatible matrices\n");
        return NULL;
    }
    Matrix result = newMatrix(n);
    for(int i = 0; i < n; i++) {
        row_sum(result->rows[i], A->rows[i], B->rows[i], SUB);
    }
    return result;
}

Matrix product(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) return NULL;
    const int n = A->n;
    if (n != B->n) { 
        fprintf(stderr, "Error: Multiplying incompatible matrices\n");
        return NULL;
    }
    Matrix result = newMatrix(n);
    for (int i = 0; i < n; i++) {
        row_matrix_product(result->rows[i], A->rows[i], B);
    }
    return result;
}

void printMatrix(FILE *out, Matrix M) {
    if (M == NULL) return;
    const int n = M->n;
    for(int i = 0; i < n; i++){
        List row = (M->rows)[i];
        if (row == NULL) continue;
        if (length(row) > 0) {
            fprintf(out, "%d: ", i+1);
            moveFront(row);
            for(; index(row) >= 0; moveNext(row)) {
                entry_t* e = (entry_t*)get(row);
                fprintf(out, "(%d, %.1f) ", e->col_index, e->value);
            }
            fprintf(out, "\n");
        }
    }
}

