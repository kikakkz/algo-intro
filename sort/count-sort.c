#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"
#include "utils.c"

#define __MAX(a, b) ((a > b) ? a : b)
#define __MIN(a, b) ((a > b) ? b : a)

static void find_min_max(int *src, int len, int *min, int *max)
{
    int i = 0;

    *max = INT_MIN;
    *min = INT_MAX;

    for (i = 0; i < len; i++) {
        *max = __MAX(src[i], *max);
        *min = __MIN(src[i], *min);
    }
}

static void count(int *src, int len, int *carr, int clen, int min)
{
    int i = 0;
    int total = 0;

    memset(carr, 0x0, sizeof(int) * clen);
    for (i = 0; i < len; i++) {
        carr[src[i] - min]++;
    }
    for (i = 0; i < clen; i++) {
        total += carr[i];
        carr[i] = total;
    }
}

static void refill(int *src, int len, int *carr, int clen, int min)
{
    int i = 0;
    int *dst = (int *)malloc(sizeof(int) * len);

    for (i = len - 1; 0 <= i; i--) {
        dst[carr[src[i] - min]] = src[i];
        carr[src[i] - min]--;
    }

    memcpy(src, dst, sizeof(int) * len);
    free(dst);
}

int main(int argc, char *argv[])
{
#define SRC src_mini

    int max = 0;
    int min = 0;
    int len = sizeof(SRC) / sizeof(SRC[0]);
    int *carr = NULL;

    find_min_max(SRC, len, &min, &max);

    print(SRC, len, "ORIG");

    carr = (int *)malloc(sizeof(int) * (max - min + 1));
    if (NULL == carr) {
        return -1;
    }

    printf("MAX %d MIN %d\n", max, min);

    count(SRC, len, carr, max - min + 1, min);
    print(carr, max - min + 1, "COUNT");

    refill(SRC, len, carr, max - min + 1, min);

    print(SRC, len, "SORTED");

    free(carr);
    return 0;
}
