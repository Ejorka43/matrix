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
        printf("��������, ��� ���������: \n");
        printf("1) ��������� ������� \n");
        printf("2) �������� � ��������� \n");
        printf("3) ����� ������ \n");
        printf("4) ��������� ���������� \n");
        printf("5) ����� \n");
        int choice;
        if (scanf("%d", &choice) != 1) { // �������� ��������� ����������
            printf("������ �����!\n");
            while (getchar() != '\n'); // ������� �������� ������
            continue;
        }
        switch(choice){
        case 1:
            //�������� �������
            printf("������� ������ ������� (������ � ������, ������ � ������):\n");
            size_t h1, w1;
            if (scanf("%zu %zu", &h1, &w1) != 2) {
                printf("������ �����!\n");
                while (getchar() != '\n');
                continue;
            }
            Matrix* matrix = matrix_alloc(h1, w1);
            if (matrix == NULL) {
                printf("������ ��������� ������!\n");
                return 1;
            }
            if (matrix != NULL) {
                printf("������� ������� �������.\n");
            }
            printf("������� �������� �������:\n");
            for (size_t i = 0; i < h1; i++) {
                for (size_t j = 0; j < w1; j++) {
                    double element;
                    if (scanf("%lf", &element) != 1) {
                        printf("������ �����!\n");
                        matrix_free(matrix);
                        while (getchar() != '\n');
                        continue;
                    }
                    matrix_set(matrix, i, j, element);
                }
            }
            printf("�������:\n");
            matrix_print(matrix);

            printf("������� ������� �������� ������� � ������� ������ �������� ������:\n");
            size_t row, col;
            if (scanf("%zu %zu", &row, &col) != 2) {
                printf("������ �����!\n");
                matrix_free(matrix);
                while (getchar() != '\n');
                continue;
            }
            printf("������� � i=%zu, j=%zu: %lf\n", row, col, *matrix_get_elem(matrix, row, col));

            //������������ �������
            Matrix* matrix2 = matrix_clone(matrix);
            if (matrix2 == NULL) {
                printf("������ ��������� ������!\n");
                matrix_free(matrix);
                return 1;
            }
            printf("���� �������:\n");
            matrix_print(matrix2);
            matrix_free(matrix);

            //��������� �������
            printf("������� ���������� ������ ������� (������� ������, ����� ������):\n");
            size_t h2, w2;
            if (scanf("%zu %zu", &h2, &w2) != 2) {
                printf("������ �����!\n");
                matrix_free(matrix2);
                while (getchar() != '\n');
                continue;
            }
            Matrix* matrix3 = matrix_resize(matrix2, h2, w2);
            if (matrix3 == NULL) {
                printf("������ ��������� ������!\n");
                matrix_free(matrix2);
                return 1;
            }
            printf("��������� �������:\n");
            matrix_print(matrix3);
            matrix_free(matrix3);

            //������� �������
            printf("������� ������ ������� ������� (������� ������, ����� ������):\n");
            size_t h3, w3;
            if (scanf("%zu %zu", &h3, &w3) != 2) {
                printf("������ �����!\n");
                while (getchar() != '\n');
                continue;
            }
            Matrix* matrix4 = zero_matrix_alloc(h3, w3);
            if (matrix4 == NULL) {
                printf("������ ��������� ������!\n");
                return 1;
            }
            printf("������� �������:\n");
            matrix_print(matrix4);
            matrix_free(matrix4);

            //��������� �������
            printf("������� ������ ��������� ���������� �������: \n");
            size_t size;
            if (scanf("%zu", &size) != 1) {
                printf("������ �����!\n");
                while (getchar() != '\n');
                continue;
            }
            Matrix* matrix5 = matrix_create_unit_square(size);
            if (matrix5 == NULL) {
                printf("������ ��������� ������!\n");
                return 1;
            }
            printf("��������� �������:\n");
            matrix_print(matrix5);
            matrix_free(matrix5);

            break;

        case 2:
            printf("������� ������ ������ ������� (������� ������, ����� ������):\n");
            size_t h4, w4;
            if (scanf("%zu %zu", &h4, &w4) != 2) {
                printf("������ �����!\n");
                while (getchar() != '\n');
                continue;
            }
            Matrix* matrix6 = matrix_alloc(h4, w4);
            if (matrix6 == NULL) {
                printf("������ ��������� ������!\n");
                return 1;
            }
            printf("������� ������� �������.\n");
            printf("������� �������� �������:\n");
            for (size_t i = 0; i < h4; i++) {
                for (size_t j = 0; j < w4; j++) {
                    double element;
                    if (scanf("%lf", &element) != 1) {
                        printf("������ �����!\n");
                        matrix_free(matrix6);
                        while (getchar() != '\n');
                        continue;
                    }
                    matrix_set(matrix6, i, j, element);
                }
            }

            printf("������� ������ ������ ������� (������� ������, ����� ������):\n");
            size_t h5, w5;
            if (scanf("%zu %zu", &h5, &w5) != 2) {
                printf("������ �����!\n");
                while (getchar() != '\n');
                continue;
            }
            Matrix* matrix7 = matrix_alloc(h5, w5);
            if (matrix7 == NULL) {
                printf("������ ��������� ������!\n");
                return 1;
            }
            printf("������� ������� �������.\n");
            printf("������� �������� �������:\n");
            for (size_t i = 0; i < h5; i++) {
                for (size_t j = 0; j < w5; j++) {
                    double element;
                    if (scanf("%lf", &element) != 1) {
                        printf("������ �����!\n");
                        matrix_free(matrix7);
                        while (getchar() != '\n');
                        continue;
                    }
                    matrix_set(matrix7, i, j, element);
                }
            }

            //����� ������
            Matrix* matrix72 = matrix_alloc(h5, w5);
            if (matrix72 == NULL) {
                printf("������ ��������� ������!\n");
                return 1;
            }
            Matrix* result1 = matrix_sum(matrix72, matrix6, matrix7);
            if (result1 == NULL) {
                printf("������ ���������� ����� ������!\n");
                matrix_free(matrix72);
                matrix_free(matrix6);
                matrix_free(matrix7);
                return 1;
            }
            printf("����� ������:\n");
            matrix_print(matrix6);
            printf("+ \n");
            matrix_print(matrix7);
            printf("= \n");
            matrix_print(result1);
            matrix_free(result1);
            //matrix_free(matrix72);

            //��������� ������� �� ������
            Matrix* matrix65 = matrix_clone(matrix6);
            if (matrix65 == NULL) {
                printf("������ ��������� ������!\n");
                matrix_free(matrix6);
                matrix_free(matrix7);
                return 1;
            }
            printf("������� ������ �� ������� ����� �������� ������ �������: \n");
            double scalar;
            if (scanf("%lf", &scalar) != 1) {
                printf("������ �����!\n");
                matrix_free(matrix65);
                matrix_free(matrix6);
                matrix_free(matrix7);
                return 1;
            }
            matrix_multiply_scalar(matrix65, scalar);
            printf("������ ������� ���������� �� ������:\n");
            matrix_print(matrix65);
            matrix_free(matrix65);

            //��������� ������
            Matrix* result2 = matrix_multiply(matrix6, matrix7);
            if (result2 == NULL) {
                printf("������ ���������� ������������ ������!\n");
                matrix_free(matrix6);
                matrix_free(matrix7);
                return 1;
            }
            printf("������������� ������ � ������ �������:\n");
            matrix_print(result2);
            matrix_free(result2);

            //���������������� �������
            Matrix* matrix66 = matrix_clone(matrix6);
            if (matrix66 == NULL) {
                printf("������ ��������� ������!\n");
                matrix_free(matrix6);
                matrix_free(matrix7);
                return 1;
            }
            printf("���������������� ������ ������� ����� ���������:\n");
            Matrix* result3 = matrix_alloc(h4, w4);
            if (result3 == NULL) {
                printf("������ ��������� ������!\n");
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
                printf("������ ��������� ������!\n");
                matrix_free(matrix6);
                matrix_free(matrix7);
                return 1;
            }
            Matrix* matrix86 = matrix_clone(matrix7);
            if (matrix86 == NULL) {
                printf("������ ��������� ������!\n");
                matrix_free(matrix85);
                matrix_free(matrix6);
                matrix_free(matrix7);
                return 1;
            }
            Matrix* matrix87 = matrix_clone(matrix7);
            if (matrix87 == NULL) {
                printf("������ ��������� ������!\n");
                matrix_free(matrix85);
                matrix_free(matrix86);
                matrix_free(matrix6);
                matrix_free(matrix7);
                return 1;
            }
            Matrix* matrix88 = matrix_clone(matrix7);
            if (matrix88 == NULL) {
                printf("������ ��������� ������!\n");
                matrix_free(matrix85);
                matrix_free(matrix86);
                matrix_free(matrix87);
                matrix_free(matrix6);
                matrix_free(matrix7);
                return 1;
            }

            //��������� ������ �� ������
            printf("������� ������ � ����� ������ ������ ������� (������ ������� ����� �������� �� ���� ������): \n");
            double scalar_row;
            size_t st0;
            if (scanf("%lf %zu", &scalar_row, &st0) != 2) {
                printf("������ �����!\n");
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

            //����� ���� �����
            printf("�������� ������ ����� ������ �������, ������� ����� ������������� (� ������ ���������� ������): \n");
            size_t st1, st2;
            if (scanf("%zu %zu", &st1, &st2) != 2) {
                printf("������ �����!\n");
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

            //������������ �����
            printf("�������� ������ ����� ������ �������, ������� ����� ������������: \n");
            size_t st3, st4;
            if (scanf("%zu %zu", &st3, &st4) != 2) {
                printf("������ �����!\n");
                matrix_free(matrix87);
                matrix_free(matrix88);
                matrix_free(matrix6);
                matrix_free(matrix7);
                return 1;
            }
            permute_string(matrix87, st3, st4);
            matrix_print(matrix87);
            matrix_free(matrix87);

            //��������� �����
            printf("��������� ����� �� �������: \n");
            printf("%lf \n", max_row_norm(matrix88));

            printf("��������� ����� �� ��������: \n");
            printf("%lf \n", max_col_norm(matrix88));
            matrix_free(matrix88);

            //��������� ����������
            printf("�������� ������ ������ � ������� ��� ���������� �� �������: \n");
            size_t st5, st6;
            if (scanf("%zu %zu", &st5, &st6) != 2) {
                printf("������ �����!\n");
                matrix_free(matrix6);
                matrix_free(matrix7);
                return 1;
            }
            Matrix* submatrix = matrix_alloc(h5 - 1, w5 - 1);
            if (submatrix == NULL) {
                printf("������ ��������� ������!\n");
                matrix_free(matrix6);
                matrix_free(matrix7);
                return 1;
            }
            allocate_submatrix(matrix7, st5, st6, submatrix);
            matrix_print(submatrix);
            matrix_free(submatrix);

            //������������ �������
            printf("������������ �������: \n");
            double det = matrix_determinant(matrix7);
            printf("%lf \n", det);
            matrix_free(matrix7);

            matrix_free(matrix6);
            break;

        case 3:
            printf("������� ������ ���������� �������:\n");
            size_t h6;
            if (scanf("%zu", &h6) != 1) {
                printf("������ �����!\n");
                while (getchar() != '\n');
                continue;
            }
            Matrix* matrixA = matrix_alloc(h6, h6);
            if (matrixA == NULL) {
                printf("������ ��������� ������!\n");
                return 1;
            }
            printf("������� ������� �������.\n");
            printf("������� �������� ������� A:\n");
            for (size_t i = 0; i < h6; i++) {
                for (size_t j = 0; j < h6; j++) {
                    double element;
                    if (scanf("%lf", &element) != 1) {
                        printf("������ �����!\n");
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
                printf("������ ��������� ������!\n");
                matrix_free(matrixA);
                return 1;
            }
            printf("������� ������� �������.\n");
            printf("������� �������� ������� B:\n");
            for (size_t i = 0; i < h6; i++) {
                for (size_t j = 0; j < 1; j++) {
                    double element;
                    if (scanf("%lf", &element) != 1) {
                        printf("������ �����!\n");
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
                printf("������ ��������� ������!\n");
                matrix_free(matrixB);
                matrix_free(matrixA);
                return 1;
            }
            Matrix* gauss_matrix = solve_system(matrixA, matrixB, matrixx);
            if (gauss_matrix != NULL) {
                printf("������� ������� (x):\n");
                matrix_print(gauss_matrix);
                matrix_free(gauss_matrix);
            }
            else {
                printf("��� ������������� �������.\n");
            }
            matrix_free(matrixx);
            matrix_free(matrixB);
            matrix_free(matrixA);
            break;

        case 4:
            printf("������� ������ ������� ��� �������� exp:\n");
            size_t h10, w10;
            if (scanf("%zu %zu", &h10, &w10) != 2) {
                printf("������ �����!\n");
                while (getchar() != '\n');
                continue;
            }
            Matrix* matrix10 = matrix_alloc(h10, w10);
            if (matrix10 == NULL) {
                printf("������ ��������� ������!\n");
                return 1;
            }
            printf("������� ������� �������.\n");
            printf("������� �������� �������:\n");
            for (size_t i = 0; i < h10; i++) {
                for (size_t j = 0; j < w10; j++) {
                    double element;
                    if (scanf("%lf", &element) != 1) {
                        printf("������ �����!\n");
                        matrix_free(matrix10);
                        while (getchar() != '\n');
                        continue;
                    }
                    matrix_set(matrix10, i, j, element);
                }
            }
            Matrix* matrix11 = matrix_exponential(matrix10, 0.00000001);
            if (matrix11 == NULL) {
                printf("������ ���������� ���������������� �������!\n");
                matrix_free(matrix10);
                return 1;
            }
            matrix_print(matrix11);
            matrix_free(matrix11);
            matrix_free(matrix10);
            break;
        case 5:
            printf("����� �� ���������.\n");
            return 0;

        default:
            printf("������ �����!\n");
            while (getchar() != '\n');
            continue;
        }
    }
    return 0;
}
