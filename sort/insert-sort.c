#include "data.h"
#include "utils.c"

int main(int argc, char *argv[])
{
#define SRC src
    int len = sizeof(SRC) / sizeof(SRC[0]);
    int i = 0, j = 0;
    int key = SRC[0];

    now();

    for (i = 1; i < len; i++) {
        key = SRC[i];
        j = i - 1;
        while (0 <= j && key < src[j]) {
            SRC[j + 1] = SRC[j];
            j--;
        }
        SRC[j + 1] = key;
    }

    now();

    return 0;
}
