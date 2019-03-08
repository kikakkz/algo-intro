#include <stdio.h>
#include <stdlib.h>

#include "data-sorted.h"
#include "utils.c"

static int bin_search(int *src, int start, int end, int target)
{
    int mid = (start + end) / 2;

    if (target == src[mid]) {
        return mid;
    }

    if (end == start) {
        return -1;
    }

    if (end == start + 1) {
        if (target != src[end]) {
            return -1;
        }
    }

    if (src[mid] < target) {
        start = mid;
    } else {
        end = mid;
    }

    return bin_search(src, start, end, target);
}

int main(int argc, char *argv[])
{
#define SRC src
    int len = sizeof(SRC) / sizeof(SRC[0]);
    int id = -1;
    int target = atoi(argv[1]);

    now();
    id = bin_search(SRC, 0, len - 1, target);
    now();
    printf("Find %d at %d\n", target, id);

    return 0;
}
