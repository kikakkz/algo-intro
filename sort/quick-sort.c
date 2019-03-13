#include <stdio.h>
#include <stdlib.h>

#include "data.h"
#include "utils.c"

#define MAX(a, b)   ((a > b) ? a : b)
#define MIN(a, b)   ((a > b) ? b : a)

static void exchange(int *a, int *b)
{
    int temp = 0;
    temp = *a;
    *a = *b;
    *b = temp;
}

static int part(int *src, int start, int end)
{
    int pivot = src[end];
    int i = start, j = end - 1;

    while (i <= j) {
        while (src[i] < pivot && i <= j) i++;
        while (pivot <= src[j] && i <= j) j--;
        if (i <= j) exchange(&src[i], &src[j]);
    }
    exchange(&src[i], &src[end]);

    return i;
}

static void qqsort(int *src, int start, int end)
{
    int pid = end;
    int send = end;
    int mstart = start;

    if (start == end) {
        return;
    }

    pid = part(src, start, end);

    send = MAX(pid - 1, start);
    mstart = MIN(pid + 1, end);

    qqsort(src, start, send);
    qqsort(src, mstart, end);
}

int main(int argc, char *argv[])
{
#define SRC src
    int len = sizeof(SRC) / sizeof(SRC[0]);

    print(SRC, len, "ORIG");
    now();
    qqsort(SRC, 0, len - 1);
    now();
    print(SRC, len, "SORTED");

    return 0;
}
