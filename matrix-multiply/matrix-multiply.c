#include <stdio.h>

#include "data.h"

int main(int argc, char *argv[])
{
    int c[4][4];

    int i = 0, j = 0, k = 0;

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < ROWS; j++) {
            c[i][j] = 0;
            for (k = 0; k < ROWS; k++) {
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }
        }
    }

    printf("|%d %d %d %d|   |%d %d %d %d|   |%3d %3d %3d %3d|\n",
            a[0][0], a[0][1], a[0][2], a[0][3],
            b[0][0], b[0][1], b[0][2], b[0][3],
            c[0][0], c[0][1], c[0][2], c[0][3]);
    printf("|%d %d %d %d| x |%d %d %d %d| = |%3d %3d %3d %3d|\n",
            a[1][0], a[1][1], a[1][2], a[1][3],
            b[1][0], b[1][1], b[1][2], b[1][3],
            c[1][0], c[1][1], c[1][2], c[1][3]);
    printf("|%d %d %d %d|   |%d %d %d %d|   |%3d %3d %3d %d|\n",
            a[2][0], a[2][1], a[2][2], a[2][3],
            b[2][0], b[2][1], b[2][2], b[2][3],
            c[2][0], c[2][1], c[2][2], c[2][3]);
    printf("|%d %d %d %d|   |%d %d %d %d|   |%3d %3d %3d %d|\n",
            a[3][0], a[3][1], a[3][2], a[3][3],
            b[3][0], b[3][1], b[3][2], b[3][3],
            c[3][0], c[3][1], c[3][2], c[3][3]);

    return 0;
}
