#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "utils.c"

static uint64_t exp_recur(int d, int n)
{
    int extra = 1;
    int dest = n;
    uint64_t r = 1;

    if (1 == n) {
        return d;
    }

    if (0 != n % 2) {
        extra = d;
        dest = n - 1;
    }

    r = exp_recur(d, dest / 2);

    return r * r * extra;
}

static uint64_t exp_loop(int d, int n)
{
    uint64_t r = 1;
    int i = 0;

    for (i = 0; i < n; i++) {
        r *= d;
    }

    return r;
}

int main(int argc, char *argv[])
{
    int d = atoi(argv[1]);
    int n = atoi(argv[2]);
    uint64_t r = 0;

    now();
    r = exp_loop(d, n);
    now();

    printf("LOOP: %d ^ %d = %lu\n", d, n, r);

    now();
    r = exp_recur(d, n);
    now();

    printf("RECUR: %d ^ %d = %lu\n", d, n, r);

    return 0;
}
