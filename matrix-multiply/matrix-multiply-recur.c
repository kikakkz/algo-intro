#include <stdio.h>
#include <stdlib.h>

#include "data.h"

static void print_matrix(int **a, int dim)
{
    int i = 0, j = 0;
    printf("----------------------\n");
    for (i = 0; i < dim; i++) {
        printf("|");
        for (j = 0; j < dim; j++) {
            printf("%3d ", a[i][j]);
        }
        printf("|\n");
    }
    printf("----------------------\n");
}

static void matrix_multiply(int **a, int **b, int **c, int rows, int cols)
{
    int n = rows / 2;
    int i = 0, j = 0;

    int **a11, **a12, **a21, **a22;
    int **b11, **b12, **b21, **b22;
    int **c111, **c121, **c211, **c221;
    int *cc = NULL, **ccc = NULL;
    int **c112, **c122, **c212, **c222;

    if (1 == rows) {
        c[0][0] = a[0][0] * b[0][0];
        return;
    }

    a11 = malloc(sizeof(int *) * n);
    a12 = malloc(sizeof(int *) * n);
    a21 = malloc(sizeof(int *) * n);
    a22 = malloc(sizeof(int *) * n);

    b11 = malloc(sizeof(int *) * n);
    b12 = malloc(sizeof(int *) * n);
    b21 = malloc(sizeof(int *) * n);
    b22 = malloc(sizeof(int *) * n);

    c111 = malloc(sizeof(int *) * n);
    c121 = malloc(sizeof(int *) * n);
    c211 = malloc(sizeof(int *) * n);
    c221 = malloc(sizeof(int *) * n);
    c112 = malloc(sizeof(int *) * n);
    c122 = malloc(sizeof(int *) * n);
    c212 = malloc(sizeof(int *) * n);
    c222 = malloc(sizeof(int *) * n);

    cc = malloc(sizeof(int) * cols * rows);
    ccc = malloc(sizeof(int *) * rows);

    for (i = 0; i < n; i++) {
        a11[i] = a[i];
        a12[i] = &a[i][n];
        a21[i] = a[i + n];
        a22[i] = &a[i + n][n];

        b11[i] = b[i];
        b12[i] = &b[i][n];
        b21[i] = b[i + n];
        b22[i] = &b[i + n][n];

        c111[i] = c[i];
        c121[i] = &c[i][n];
        c211[i] = c[i + n];
        c221[i] = &c[i + n][n];

        ccc[i] = &cc[cols * j++];
        ccc[i + n] = &cc[cols * j++];

        c112[i] = ccc[i];
        c122[i] = &ccc[i][n];
        c212[i] = ccc[i + n];
        c222[i] = &ccc[i + n][n];
    }

    matrix_multiply(a11, b11, c111, n, n);
    matrix_multiply(a12, b21, c112, n, n);

    matrix_multiply(a11, b12, c121, n, n);
    matrix_multiply(a12, b22, c122, n, n);

    matrix_multiply(a21, b11, c211, n, n);
    matrix_multiply(a22, b21, c212, n, n);

    matrix_multiply(a21, b12, c221, n, n);
    matrix_multiply(a22, b22, c222, n, n);

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            c[i][j] += ccc[i][j];
        }
    }

    free(a11);
    free(a12);
    free(a21);
    free(a22);

    free(b11);
    free(b12);
    free(b21);
    free(b22);

    free(c111);
    free(c121);
    free(c211);
    free(c221);
    free(c112);
    free(c122);
    free(c212);
    free(c222);

    free(cc);
    free(ccc);
}

int main(int argc, char *argv[])
{
    int a[4][4] = {{1, 7, 4, 5}, {2, 3, 6, 6}, {2, 6, 7, 8}, {2, 4, 6, 8}};
    int b[4][4] = {{2, 5, 3, 3}, {3, 6, 3, 5}, {8, 9, 1, 9}, {0, 9, 3, 6}};
    int c[4][4];

    int *aa[4] = {a[0], a[1], a[2], a[3]};
    int *bb[4] = {b[0], b[1], b[2], b[3]};
    int *cc[4] = {c[0], c[1], c[2], c[3]};

    matrix_multiply(aa, bb, cc, ROWS, ROWS);

    printf("|%d %d %d %d|   |%d %d %d %d|   |%3d %3d %3d %3d|\n",
            a[0][0], a[0][1], a[0][2], a[0][3],
            b[0][0], b[0][1], b[0][2], b[0][3],
            c[0][0], c[0][1], c[0][2], c[0][3]);
    printf("|%d %d %d %d| x |%d %d %d %d| = |%3d %3d %3d %3d|\n",
            a[1][0], a[1][1], a[1][2], a[1][3],
            b[1][0], b[1][1], b[1][2], b[1][3],
            c[1][0], c[1][1], c[1][2], c[1][3]);
    printf("|%d %d %d %d|   |%d %d %d %d|   |%3d %3d %3d %d|\n",
            a[2][0], a[2][1], a[2][2], a[2][3],
            b[2][0], b[2][1], b[2][2], b[2][3],
            c[2][0], c[2][1], c[2][2], c[2][3]);
    printf("|%d %d %d %d|   |%d %d %d %d|   |%3d %3d %3d %d|\n",
            a[3][0], a[3][1], a[3][2], a[3][3],
            b[3][0], b[3][1], b[3][2], b[3][3],
            c[3][0], c[3][1], c[3][2], c[3][3]);

    return 0;
}
