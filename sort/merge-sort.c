#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "data.h"
#include "utils.c"

static int sort(int *src, int len, int *ts)
{
    int llen = 0;
    int rlen = 0;
    int i = 0, j = 0, k = 0, m = 0;
    int key = 0;

    if (len < 2) return 0;

    llen = len / 2;
    rlen = len - llen;

    sort(src, llen, ts);
    sort(src + llen, rlen, ts);

    while (i < llen && j < rlen) {
        if (src[i] < src[llen + j]) {
            ts[k++] = src[i++];
        } else {
            ts[k++] = src[llen + j++];
        }
    }
    for (m = i; m < llen; m++) {
        ts[k++] = src[m];
    }
    for (m = j; m < rlen; m++) {
        ts[k++] = src[llen + m];
    }
    memcpy(src, ts, len * sizeof(int));

    return 0;
}

int main(int argc, char *argv[])
{
#define SRC src
    int len = sizeof(SRC) / sizeof(SRC[0]);
    int *tmp = (int *)malloc(sizeof(SRC));

    now();
    sort(SRC, len, tmp);
    print(SRC, len, "SORTED");
    now();

    free(tmp);

    return 0;
}
