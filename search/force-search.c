#include <stdio.h>
#include <stdlib.h>

#include "data-sorted.h"
#include "utils.c"

int main(int argc, char *argv[])
{
#define SRC src
    int len = sizeof(SRC) / sizeof(SRC[0]);
    int i = 0;
    int target = strtoul(argv[1], NULL, 10);

    now();
    for (i = 0; i < len; i++) {
        if (target == SRC[i]) {
            now();
            printf("Find %d at %d\n", target, i);
            return 0;
        }
    }
    now();
    printf("CANNOT find\n");

    return 0;
}
