#include "data.h"
#include "utils.c"

static void sort(int *src, int len)
{
    int i = len - 2;
    int key = src[len - 1];

    if (len < 2) return;
    sort(src, len - 1);
    while (0 <= i && key < src[i]) {
        src[i + 1] = src[i];
        i--;
    }
    src[i + 1] = key;
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
