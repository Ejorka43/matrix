#include <stdlib.h>
#include <stdio.h>
#include "struct.h"
Matrix* matrix_alloc(size_t rows, size_t cols) {
    if (rows == 0 || cols == 0) {
        return NULL;
    }
    Matrix* matrix = (Matrix*) malloc(sizeof(Matrix));
    if (matrix == NULL) {
        return NULL;
    }
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = (double*) calloc(rows * cols, sizeof(double));
    if (matrix->data == NULL) {
        free(matrix);
        return NULL;
    }
    return matrix;
}

void matrix_free(Matrix* matrix) {
    if (matrix != NULL) {
        free(matrix->data);
        free(matrix);
    }
}

Matrix* matrix_clone(const Matrix* m) {
    if (m == NULL) {
        return NULL;
    }
    Matrix* clone = matrix_alloc(m->rows, m->cols);
    if (clone == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < m->rows; i++) {
        for (size_t j = 0; j < m->cols; j++) {
            clone->data[i * m->cols + j] = m->data[i * m->cols + j];
        }
    }
    return clone;
}


Matrix* matrix_resize(Matrix* m, size_t rows, size_t cols) {
    if (m == NULL || rows == 0 || cols == 0) {
        return NULL;
    }
    free(m->data);
    m->data = (double*) malloc(rows * cols * sizeof(double));
    if (m->data == NULL) {
        return NULL;
    }
    m->rows = rows;
    m->cols = cols;
    return m;
}

void matrix_set(Matrix* matrix, size_t row, size_t col, double value) {
    if (matrix == NULL || row >= matrix->rows || col >= matrix->cols) {
        return; // �����, ���� ������� �� ��������� �������
    }
    size_t index = row * matrix->cols + col;
    matrix->data[index] = value;
}

double matrix_get(const Matrix* matrix, size_t row, size_t col) {
    if (matrix == NULL || row >= matrix->rows || col >= matrix->cols) {
        return 0.0; // ���������� 0, ���� ������� �� ��������� �������
    }
    size_t index = row * matrix->cols + col;
    return matrix->data[index];
}

double *matrix_get_elem(const Matrix* matrix, size_t i, size_t j) {
    if (matrix == NULL || i >= matrix->rows || j >= matrix->cols){
        return NULL;
    }
    return &matrix->data[i * matrix->cols + j];
}

void matrix_print(const Matrix* matrix) {
    if (matrix == NULL) {
        return;
    }
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->cols; j++) {
            printf("%-13lf", matrix_get(matrix, i, j));
        }
        printf("\n");
    }
}

Matrix* zero_matrix_set(Matrix* matrix) {
    if (matrix == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->cols; j++) {
            matrix->data[i * matrix->cols + j] = 0.0;
        }
    }
    return matrix;
}

Matrix* zero_matrix_alloc(size_t rows, size_t cols) {
    if (rows == 0 || cols == 0) {
        return NULL;
    }
    Matrix* matrix = matrix_alloc(rows, cols);
    if (matrix == NULL) {
        return NULL;
    }
    zero_matrix_set(matrix);
    return matrix;
}

Matrix* matrix_create_unit_square(size_t size) {
    Matrix* matrix = zero_matrix_alloc(size, size);
    if (matrix == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < size; i++) {
        double key = 1;
        matrix->data[i * size + i] = key;
    }
    return matrix;
}

Matrix* matrix_assign(Matrix* m1, const Matrix* m2) {
    if (m1 == NULL || m2 == NULL) {
        return NULL;
    }
    if (m1->rows != m2->rows || m1->cols != m2->cols) {
        return NULL;
    }
    for (size_t i = 0; i < m1->rows; ++i) {
        for (size_t j = 0; j < m1->cols; ++j) {
            double key = matrix_get(m2, i, j);
            matrix_set(m1, i, j, key);
        }
    }
    return m1;
}
