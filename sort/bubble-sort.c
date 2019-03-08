#include "data.h"
#include "utils.c"

static void sort(int *src, int len)
{
    int i = 0, j = 0;
    int key = 0;

    for (i = 0; i < len - 1; i++) {
        for (j = len - 1; i < j; j--) {
            if (src[j] < src[j - 1]) {
                key = src[j];
                src[j] = src[j - 1];
                src[j - 1] = key;
            }
        }
    }
}

int main(int argc, char *argv[])
{
#define SRC src
    int len = sizeof(SRC) / sizeof(SRC[0]);

    now();
    sort(SRC, len);
    now();

    return 0;
}
