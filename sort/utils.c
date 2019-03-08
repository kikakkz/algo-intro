#include <stdio.h>
#include <sys/time.h>

static void now(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    printf("%lu.%lu\n", tv.tv_sec, tv.tv_usec);
}

static void print(int *d, int len, char *info)
{
    int i = 0;
    printf("%s LEN: %d--\n", info, len);
    for (i = 0; i < len; i++) {
        printf("%d ", d[i]);
    }
    printf("\n");
}
