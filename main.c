#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <locale.h>
#include <math.h>
#include "struct.h"
#include "operations.h"
#include "gauss.h"
#include "exp.h"

int main(){
    setlocale(LC_CTYPE, "Russian");
    while(1){
        printf("Выберите, что выполнить: \n");
        printf("1) Структура матрицы \n");
        printf("2) Операции с матрицами \n");
        printf("3) Метод Гаусса \n");
        printf("4) Матричная экспонента \n");
        printf("5) Выход \n");
        int choice;
        if (scanf("%d", &choice) != 1) { // Проверка успешного считывания
            printf("Ошибка ввода!\n");
            while (getchar() != '\n'); // Очистка входного буфера
            continue;
        }
        switch(choice){
        case 1:
            //Создание матрицы
            printf("Введите размер матрицы (первое — высота, второе — ширина):\n");
            size_t h1, w1;
            if (scanf("%zu %zu", &h1, &w1) != 2) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                continue;
            }
            Matrix* matrix = matrix_alloc(h1, w1);
            if (matrix == NULL) {
                printf("Ошибка выделения памяти!\n");
                return 1;
            }
            if (matrix != NULL) {
                printf("Матрица успешно создана.\n");
            }
            printf("Введите элементы матрицы:\n");
            for (size_t i = 0; i < h1; i++) {
                for (size_t j = 0; j < w1; j++) {
                    double element;
                    if (scanf("%lf", &element) != 1) {
                        printf("Ошибка ввода!\n");
                        matrix_free(matrix);
                        while (getchar() != '\n');
                        continue;
                    }
                    matrix_set(matrix, i, j, element);
                }
            }
            printf("Матрица:\n");
            matrix_print(matrix);

            printf("Введите индексы элемента матрицы к которым хотите получить доступ:\n");
            size_t row, col;
            if (scanf("%zu %zu", &row, &col) != 2) {
                printf("Ошибка ввода!\n");
                matrix_free(matrix);
                while (getchar() != '\n');
                continue;
            }
            printf("Элемент с i=%zu, j=%zu: %lf\n", row, col, *matrix_get_elem(matrix, row, col));

            //Клонирование матрицы
            Matrix* matrix2 = matrix_clone(matrix);
            if (matrix2 == NULL) {
                printf("Ошибка выделения памяти!\n");
                matrix_free(matrix);
                return 1;
            }
            printf("Клон матрицы:\n");
            matrix_print(matrix2);
            matrix_free(matrix);

            //Изменённая матрица
            printf("Введите измененный размер матрицы (сначала высота, затем ширина):\n");
            size_t h2, w2;
            if (scanf("%zu %zu", &h2, &w2) != 2) {
                printf("Ошибка ввода!\n");
                matrix_free(matrix2);
                while (getchar() != '\n');
                continue;
            }
            Matrix* matrix3 = matrix_resize(matrix2, h2, w2);
            if (matrix3 == NULL) {
                printf("Ошибка выделения памяти!\n");
                matrix_free(matrix2);
                return 1;
            }
            printf("Изменённая матрица:\n");
            matrix_print(matrix3);
            matrix_free(matrix3);

            //Нулевая матрица
            printf("Введите размер нулевой матрицы (сначала высота, затем ширина):\n");
            size_t h3, w3;
            if (scanf("%zu %zu", &h3, &w3) != 2) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                continue;
            }
            Matrix* matrix4 = zero_matrix_alloc(h3, w3);
            if (matrix4 == NULL) {
                printf("Ошибка выделения памяти!\n");
                return 1;
            }
            printf("Нулевая матрица:\n");
            matrix_print(matrix4);
            matrix_free(matrix4);

            //Единичная матрица
            printf("Введите размер единичной квадратной матрицы: \n");
            size_t size;
            if (scanf("%zu", &size) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                continue;
            }
            Matrix* matrix5 = matrix_create_unit_square(size);
            if (matrix5 == NULL) {
                printf("Ошибка выделения памяти!\n");
                return 1;
            }
            printf("Единичная матрица:\n");
            matrix_print(matrix5);
            matrix_free(matrix5);

            break;

        case 2:
            printf("Введите размер первой матрицы (сначала высота, затем ширина):\n");
            size_t h4, w4;
            if (scanf("%zu %zu", &h4, &w4) != 2) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                continue;
            }
            Matrix* matrix6 = matrix_alloc(h4, w4);
            if (matrix6 == NULL) {
                printf("Ошибка выделения памяти!\n");
                return 1;
            }
            printf("Матрица успешно создана.\n");
            printf("Введите элементы матрицы:\n");
            for (size_t i = 0; i < h4; i++) {
                for (size_t j = 0; j < w4; j++) {
                    double element;
                    if (scanf("%lf", &element) != 1) {
                        printf("Ошибка ввода!\n");
                        matrix_free(matrix6);
                        while (getchar() != '\n');
                        continue;
                    }
                    matrix_set(matrix6, i, j, element);
                }
            }

            printf("Введите размер второй матрицы (сначала высота, затем ширина):\n");
            size_t h5, w5;
            if (scanf("%zu %zu", &h5, &w5) != 2) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                continue;
            }
            Matrix* matrix7 = matrix_alloc(h5, w5);
            if (matrix7 == NULL) {
                printf("Ошибка выделения памяти!\n");
                return 1;
            }
            printf("Матрица успешно создана.\n");
            printf("Введите элементы матрицы:\n");
            for (size_t i = 0; i < h5; i++) {
                for (size_t j = 0; j < w5; j++) {
                    double element;
                    if (scanf("%lf", &element) != 1) {
                        printf("Ошибка ввода!\n");
                        matrix_free(matrix7);
                        while (getchar() != '\n');
                        continue;
                    }
                    matrix_set(matrix7, i, j, element);
                }
            }

            //Сумма матриц
            Matrix* matrix72 = matrix_alloc(h5, w5);
            if (matrix72 == NULL) {
                printf("Ошибка выделения памяти!\n");
                return 1;
            }
            Matrix* result1 = matrix_sum(matrix72, matrix6, matrix7);
            if (result1 == NULL) {
                printf("Ошибка вычисления суммы матриц!\n");
                matrix_free(matrix72);
                matrix_free(matrix6);
                matrix_free(matrix7);
                return 1;
            }
            printf("Сумма матриц:\n");
            matrix_print(matrix6);
            printf("+ \n");
            matrix_print(matrix7);
            printf("= \n");
            matrix_print(result1);
            matrix_free(result1);
            //matrix_free(matrix72);

            //Умножение матрицы на скаляр
            Matrix* matrix65 = matrix_clone(matrix6);
            if (matrix65 == NULL) {
                printf("Ошибка выделения памяти!\n");
                matrix_free(matrix6);
                matrix_free(matrix7);
                return 1;
            }
            printf("Введите скаляр на который будет умножена первая матрица: \n");
            double scalar;
            if (scanf("%lf", &scalar) != 1) {
                printf("Ошибка ввода!\n");
                matrix_free(matrix65);
                matrix_free(matrix6);
                matrix_free(matrix7);
                return 1;
            }
            matrix_multiply_scalar(matrix65, scalar);
            printf("Первая матрица умноженная на скаляр:\n");
            matrix_print(matrix65);
            matrix_free(matrix65);

            //Умножение матриц
            Matrix* result2 = matrix_multiply(matrix6, matrix7);
            if (result2 == NULL) {
                printf("Ошибка вычисления произведения матриц!\n");
                matrix_free(matrix6);
                matrix_free(matrix7);
                return 1;
            }
            printf("Перемноженные первая и вторая матрицы:\n");
            matrix_print(result2);
            matrix_free(result2);

            //Транспонирование матрицы
            Matrix* matrix66 = matrix_clone(matrix6);
            if (matrix66 == NULL) {
                printf("Ошибка выделения памяти!\n");
                matrix_free(matrix6);
                matrix_free(matrix7);
                return 1;
            }
            printf("Транспонирование первой матрицы двумя способами:\n");
            Matrix* result3 = matrix_alloc(h4, w4);
            if (result3 == NULL) {
                printf("Ошибка выделения памяти!\n");
                matrix_free(matrix66);
                matrix_free(matrix6);
                matrix_free(matrix7);
                return 1;
            }
            matrix_transpose(matrix66, result3);
            matrix_transpose_simple(matrix66);
            matrix_print(result3);
            printf("\n");
            matrix_print(matrix66);

            matrix_free(result3);
            matrix_free(matrix66);

            Matrix* matrix85 = matrix_clone(matrix7);
            if (matrix85 == NULL) {
                printf("Ошибка выделения памяти!\n");
                matrix_free(matrix6);
                matrix_free(matrix7);
                return 1;
            }
            Matrix* matrix86 = matrix_clone(matrix7);
            if (matrix86 == NULL) {
                printf("Ошибка выделения памяти!\n");
                matrix_free(matrix85);
                matrix_free(matrix6);
                matrix_free(matrix7);
                return 1;
            }
            Matrix* matrix87 = matrix_clone(matrix7);
            if (matrix87 == NULL) {
                printf("Ошибка выделения памяти!\n");
                matrix_free(matrix85);
                matrix_free(matrix86);
                matrix_free(matrix6);
                matrix_free(matrix7);
                return 1;
            }
            Matrix* matrix88 = matrix_clone(matrix7);
            if (matrix88 == NULL) {
                printf("Ошибка выделения памяти!\n");
                matrix_free(matrix85);
                matrix_free(matrix86);
                matrix_free(matrix87);
                matrix_free(matrix6);
                matrix_free(matrix7);
                return 1;
            }

            //Умножение строки на скаляр
            printf("Введите скаляр и номер строки второй матрицы (строка матрицы будет умножена на этот скаляр): \n");
            double scalar_row;
            size_t st0;
            if (scanf("%lf %zu", &scalar_row, &st0) != 2) {
                printf("Ошибка ввода!\n");
                matrix_free(matrix85);
                matrix_free(matrix86);
                matrix_free(matrix87);
                matrix_free(matrix88);
                matrix_free(matrix6);
                matrix_free(matrix7);
                return 1;
            }
            multiply_row(matrix85, scalar_row, st0);
            matrix_print(matrix85);
            matrix_free(matrix85);

            //Сумма двух строк
            printf("Выберите номера строк второй матрицы, которые будут суммироваться (к первой прибавится вторая): \n");
            size_t st1, st2;
            if (scanf("%zu %zu", &st1, &st2) != 2) {
                printf("Ошибка ввода!\n");
                matrix_free(matrix86);
                matrix_free(matrix87);
                matrix_free(matrix88);
                matrix_free(matrix6);
                matrix_free(matrix7);
                return 1;
            }
            add_strings(matrix86, st1, st2);
            matrix_print(matrix86);
            matrix_free(matrix86);

            //Перестановка строк
            printf("Выберите номера строк второй матрицы, которые будут переставлены: \n");
            size_t st3, st4;
            if (scanf("%zu %zu", &st3, &st4) != 2) {
                printf("Ошибка ввода!\n");
                matrix_free(matrix87);
                matrix_free(matrix88);
                matrix_free(matrix6);
                matrix_free(matrix7);
                return 1;
            }
            permute_string(matrix87, st3, st4);
            matrix_print(matrix87);
            matrix_free(matrix87);

            //Матричная норма
            printf("Матричная норма по строкам: \n");
            printf("%lf \n", max_row_norm(matrix88));

            printf("Матричная норма по столбцам: \n");
            printf("%lf \n", max_col_norm(matrix88));
            matrix_free(matrix88);

            //Выделение подматрицы
            printf("Выберите номера строки и столбца для исключения из матрицы: \n");
            size_t st5, st6;
            if (scanf("%zu %zu", &st5, &st6) != 2) {
                printf("Ошибка ввода!\n");
                matrix_free(matrix6);
                matrix_free(matrix7);
                return 1;
            }
            Matrix* submatrix = matrix_alloc(h5 - 1, w5 - 1);
            if (submatrix == NULL) {
                printf("Ошибка выделения памяти!\n");
                matrix_free(matrix6);
                matrix_free(matrix7);
                return 1;
            }
            allocate_submatrix(matrix7, st5, st6, submatrix);
            matrix_print(submatrix);
            matrix_free(submatrix);

            //Определитель матрицы
            printf("Определитель матрицы: \n");
            double det = matrix_determinant(matrix7);
            printf("%lf \n", det);
            matrix_free(matrix7);

            matrix_free(matrix6);
            break;

        case 3:
            printf("Введите размер квадратной матрицы:\n");
            size_t h6;
            if (scanf("%zu", &h6) != 1) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                continue;
            }
            Matrix* matrixA = matrix_alloc(h6, h6);
            if (matrixA == NULL) {
                printf("Ошибка выделения памяти!\n");
                return 1;
            }
            printf("Матрица успешно создана.\n");
            printf("Введите элементы матрицы A:\n");
            for (size_t i = 0; i < h6; i++) {
                for (size_t j = 0; j < h6; j++) {
                    double element;
                    if (scanf("%lf", &element) != 1) {
                        printf("Ошибка ввода!\n");
                        matrix_free(matrixA);
                        while (getchar() != '\n');
                        continue;
                    }
                    matrix_set(matrixA, i, j, element);
                }
            }
            matrix_print(matrixA);

            Matrix* matrixB = matrix_alloc(h6, 1);
            if (matrixB == NULL) {
                printf("Ошибка выделения памяти!\n");
                matrix_free(matrixA);
                return 1;
            }
            printf("Матрица успешно создана.\n");
            printf("Введите элементы матрицы B:\n");
            for (size_t i = 0; i < h6; i++) {
                for (size_t j = 0; j < 1; j++) {
                    double element;
                    if (scanf("%lf", &element) != 1) {
                        printf("Ошибка ввода!\n");
                        matrix_free(matrixB);
                        matrix_free(matrixA);
                        while (getchar() != '\n');
                        continue;
                    }
                    matrix_set(matrixB, i, j, element);
                }
            }
            matrix_print(matrixB);

            Matrix* matrixx = matrix_alloc(h6, 1);
            if (matrixx == NULL) {
                printf("Ошибка выделения памяти!\n");
                matrix_free(matrixB);
                matrix_free(matrixA);
                return 1;
            }
            Matrix* gauss_matrix = solve_system(matrixA, matrixB, matrixx);
            if (gauss_matrix != NULL) {
                printf("Матрица решений (x):\n");
                matrix_print(gauss_matrix);
                matrix_free(gauss_matrix);
            }
            else {
                printf("Нет единственного решения.\n");
            }
            matrix_free(matrixx);
            matrix_free(matrixB);
            matrix_free(matrixA);
            break;

        case 4:
            printf("Введите размер матрицы для операции exp:\n");
            size_t h10, w10;
            if (scanf("%zu %zu", &h10, &w10) != 2) {
                printf("Ошибка ввода!\n");
                while (getchar() != '\n');
                continue;
            }
            Matrix* matrix10 = matrix_alloc(h10, w10);
            if (matrix10 == NULL) {
                printf("Ошибка выделения памяти!\n");
                return 1;
            }
            printf("Матрица успешно создана.\n");
            printf("Введите элементы матрицы:\n");
            for (size_t i = 0; i < h10; i++) {
                for (size_t j = 0; j < w10; j++) {
                    double element;
                    if (scanf("%lf", &element) != 1) {
                        printf("Ошибка ввода!\n");
                        matrix_free(matrix10);
                        while (getchar() != '\n');
                        continue;
                    }
                    matrix_set(matrix10, i, j, element);
                }
            }
            Matrix* matrix11 = matrix_exponential(matrix10, 0.00000001);
            if (matrix11 == NULL) {
                printf("Ошибка вычисления экспоненциальной матрицы!\n");
                matrix_free(matrix10);
                return 1;
            }
            matrix_print(matrix11);
            matrix_free(matrix11);
            matrix_free(matrix10);
            break;
        case 5:
            printf("Выход из программы.\n");
            return 0;

        default:
            printf("Ошибка ввода!\n");
            while (getchar() != '\n');
            continue;
        }
    }
    return 0;
}
