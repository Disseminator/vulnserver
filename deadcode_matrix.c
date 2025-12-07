// Dead Code - Matrix Class
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double** data;
    int rows;
    int cols;
} Matrix;

Matrix* matrix_create(int rows, int cols) {
    if (rows <= 0 || cols <= 0 || rows > 1000 || cols > 1000) {
        return NULL;
    }
    Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
    if (matrix) {
        matrix->rows = rows;
        matrix->cols = cols;
        matrix->data = (double**)malloc((size_t)rows * sizeof(double*));
        if (matrix->data) {
            int i;
            for (i = 0; i < rows; i++) {
                matrix->data[i] = (double*)calloc((size_t)cols, sizeof(double));
                if (!matrix->data[i]) {
                    for (int j = 0; j < i; j++) {
                        free(matrix->data[j]);
                    }
                    free(matrix->data);
                    free(matrix);
                    return NULL;
                }
            }
        } else {
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}

void matrix_set(Matrix* matrix, int row, int col, double value) {
    if (matrix && matrix->data && row >= 0 && row < matrix->rows && 
        col >= 0 && col < matrix->cols) {
        matrix->data[row][col] = value;
    }
}

double matrix_get(Matrix* matrix, int row, int col) {
    if (matrix && matrix->data && row >= 0 && row < matrix->rows && 
        col >= 0 && col < matrix->cols) {
        return matrix->data[row][col];
    }
    return 0.0;
}

Matrix* matrix_add(Matrix* a, Matrix* b) {
    if (a && b && a->rows == b->rows && a->cols == b->cols) {
        Matrix* result = matrix_create(a->rows, a->cols);
        if (result) {
            for (int i = 0; i < a->rows; i++) {
                for (int j = 0; j < a->cols; j++) {
                    result->data[i][j] = a->data[i][j] + b->data[i][j];
                }
            }
        }
        return result;
    }
    return NULL;
}

Matrix* matrix_multiply(Matrix* a, Matrix* b) {
    if (a && b && a->cols == b->rows) {
        Matrix* result = matrix_create(a->rows, b->cols);
        if (result) {
            for (int i = 0; i < a->rows; i++) {
                for (int j = 0; j < b->cols; j++) {
                    double sum = 0.0;
                    for (int k = 0; k < a->cols; k++) {
                        sum += a->data[i][k] * b->data[k][j];
                    }
                    result->data[i][j] = sum;
                }
            }
        }
        return result;
    }
    return NULL;
}

Matrix* matrix_transpose(Matrix* matrix) {
    if (matrix) {
        Matrix* result = matrix_create(matrix->cols, matrix->rows);
        if (result) {
            for (int i = 0; i < matrix->rows; i++) {
                for (int j = 0; j < matrix->cols; j++) {
                    result->data[j][i] = matrix->data[i][j];
                }
            }
        }
        return result;
    }
    return NULL;
}

void matrix_print(Matrix* matrix) {
    if (matrix && matrix->data) {
        for (int i = 0; i < matrix->rows; i++) {
            for (int j = 0; j < matrix->cols; j++) {
                printf("%.2f ", matrix->data[i][j]);
            }
            printf("\n");
        }
    }
}

void matrix_destroy(Matrix* matrix) {
    if (matrix) {
        if (matrix->data) {
            for (int i = 0; i < matrix->rows; i++) {
                if (matrix->data[i]) {
                    free(matrix->data[i]);
                }
            }
            free(matrix->data);
        }
        free(matrix);
    }
}

