#include "exp.h"
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#define SIZE_MAXL 1000000
Matrix* matrix_power(const Matrix* A, size_t power, Matrix* res) {
    if (A == NULL) {
        return NULL;
    }
    if (power == 0) {
        matrix_free(res);
        res = matrix_create_unit_square(A->rows);
        if (res == NULL) {
            return NULL;
        }
        return res;
    }
    else if (power == 1) {
        matrix_free(res);
        res = matrix_clone(A);
        if (res == NULL) {
            return NULL;
        }
        return res;
    }
    else {
        Matrix* temp1 = matrix_clone(A);
        if (temp1 == NULL) {
            return NULL;
        }
        for (size_t i = 2; i <= power; i++) {
            matrix_free(res);
            res = matrix_multiply(temp1, A);
            if (res == NULL) {
                matrix_free(temp1);
                return NULL;
            }
            matrix_free(temp1);
            temp1 = matrix_clone(res);
            if (temp1 == NULL) {
                matrix_free(res);
                return NULL;
            }
        }
        matrix_free(temp1);
        return res;
    }
}

Matrix* matrix_exponential(const Matrix *A, double eps) {
    if (A == NULL) {
        return NULL;
    }
    Matrix *result = matrix_create_unit_square(A->rows);
    if (result == NULL) {
        return NULL;
    }
    Matrix *temp = matrix_clone(A);
    if (temp == NULL) {
        matrix_free(result);
        return NULL;
    }
    double n_factorial = 1;
    double norm_term = 0;
    for (size_t n = 1; n <= SIZE_MAXL; n++) {
        // Проверка на переполнение счетчика цикла
        if (n == SIZE_MAXL) {
            matrix_free(result);
            matrix_free(temp);
            return NULL;
        }
        matrix_power(A, n, temp);
        if (temp == NULL) {
            matrix_free(result);
            return NULL;
        }
        n_factorial *= n;
        matrix_multiply_scalar(temp, 1.0 / n_factorial);
        matrix_sum(result, result, temp);
        norm_term = max_row_norm(temp);
        if (norm_term < eps) {
            break;
        }
    }
    matrix_free(temp);
    return result;
}
