#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "utils.c"

#define SIZE    (sizeof(int) * 4)

static int fibonacci_matrix_mul(int fr[2][2], int ff[2][2])
{
    int frr[2][2];
    int i = 0, j = 0, k = 0;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            frr[i][j] = 0;
            for (k = 0; k < 2; k++) {
                frr[i][j] += fr[i][k] * ff[k][j];
            }
        }
    }
    memcpy(fr, frr, SIZE);
}

static int fibonacci_matrix_exp(int fr[2][2], int n)
{
    int fex[2][2];
    int dest = n;
    int extra = 0;

    if (0 == n) {
        return 0;
    } else if (1 == n) {
        return 1;
    }

    if (0 != n % 2) {
        dest = n - 1;
        extra = 2;
        memcpy(fex, fr, SIZE);
    }

    fibonacci_matrix_exp(fr, dest / 2);
    fibonacci_matrix_mul(fr, fr);
    if (0 != extra) {
        fibonacci_matrix_mul(fr, fex);
    }

    return fr[0][1];
}

static uint64_t fibonacci_rect(int n)
{
    int fr[2][2] = {{1, 1}, {1, 0}};
    return fibonacci_matrix_exp(fr, n);
}

static uint64_t fibonacci_recur(int n)
{
    if (0 == n) {
        return 0;
    } else if (1 == n) {
        return 1;
    }

    return fibonacci_recur(n - 1) + fibonacci_recur(n - 2);
}

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    uint64_t r = 0;

    now();
    r = fibonacci_recur(n);
    now();
    printf("F(%d) = %lu\n", n, r);

    now();
    r = fibonacci_rect(n);
    now();
    printf("F(%d) = %lu\n", n, r);

    return 0;
}
