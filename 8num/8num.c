#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <sys/time.h>

#define M

#ifdef M
#include <ncurses.h>
#endif

#define P(num, i, j, dim)   (num[i * dim + j])
#define ABS(a)              ((a) > 0 ? (a) : -(a))
#define MAX(a, b)           (a > b ? a : b)
#define MIN(a, b)           (a > b ? b : a)

#ifdef M
#define printf              printw
#endif

static void print(int *num, int dim)
{
    int i = 0, j = 0;

    for (i = 0; i < dim; i++) {
        printf("\n\t-------------\n\t|");
        for (j = 0; j < dim; j++) {
            if (0 == P(num, i, j, dim)) {
                printf("   |");
            } else {
                printf(" %d |", P(num, i, j, dim));
            }
        }
    }
    printf("\n\t-------------\n\n");
}

static int *g_num = NULL;

static void init(int *num, int dim)
{
    int i = 0, j = 0;
    int r = 0;
    int v = 0;
    struct timeval tv;

    gettimeofday(&tv, NULL);

    srand(tv.tv_sec + tv.tv_usec);
    v = rand() % (dim * dim);

    for (i = 0; i < dim * dim; i++) {
        if (i == v) {
            continue;
        }
L_RAND:
        r = rand() % (dim * dim);
        if (0 == r || r == dim * dim) {
            goto L_RAND;
        }

        for (j = 0; j < i; j++) {
            if (num[j] == r) {
                goto L_RAND;
            }
        }

        num[i] = r;
    }

    g_num = malloc(sizeof(int) * dim * dim);
    memcpy(g_num, num, sizeof(int) * dim * dim);
}

/**
 * Movable index
 */
typedef struct {
    int right;
    int left;
    int up;
    int down;
} mv_t;

static mv_t g_mv[] = {
    {.right = -1,   .left = 1,  .down = -1, .up = 3     },
    {.right = 0,    .left = 2,  .down = -1, .up = 4     },
    {.right = 1,    .left = -1, .down = -1, .up = 5     },
    {.right = -1,   .left = 4,  .down = 0,  .up = 6     },
    {.right = 3,    .left = 5,  .down = 1,  .up = 7     },
    {.right = 4,    .left = -1, .down = 2,  .up = 8     },
    {.right = -1,   .left = 7,  .down = 3,  .up = -1    },
    {.right = 6,    .left = 8,  .down = 4,  .up = -1    },
    {.right = 7,    .left = -1, .down = 5,  .up = -1    }
};

typedef enum {
    N_ACT_RIGHT,
    N_ACT_LEFT,
    N_ACT_UP,
    N_ACT_DOWN,

    N_ACT_INVALID
} act_t;

static int find_v(int *num, int dim)
{
    int i = 0;

    for (i = 0; i < dim * dim; i++) {
        if (0 == num[i]) {
            return i;
        }
    }

    return -1;
}

static mv_t *find_mv(int *num, int dim)
{
    return &g_mv[find_v(num, dim)];
}

static int __move(int target, int v, int *num)
{
    if (-1 != target) {
        num[v] = num[target];
        num[target] = 0;
        return 1;
    }
    return 0;
}

static int move2(int *num, int dim, act_t act)
{
    int v = find_v(num, dim);
    mv_t *mv = find_mv(num, dim);

    switch (act) {
    case N_ACT_RIGHT:   return __move(mv->right, v, num);
    case N_ACT_LEFT:    return __move(mv->left, v, num);
    case N_ACT_UP:      return __move(mv->up, v, num);
    case N_ACT_DOWN:    return __move(mv->down, v, num);
    }

    return 0;
}

static int win(int *num, int dim)
{
    int i = 0;
    for (i = 0; i < dim * dim - 1; i++) {
        if (num[i] != i + 1) {
            return 0;
        }
    }
    return 1;
}

static act_t act2action(int act)
{
    switch (act) {
    case 65:    return N_ACT_UP;
    case 66:    return N_ACT_DOWN;
    case 67:    return N_ACT_RIGHT;
    case 68:    return N_ACT_LEFT;
    }
    return N_ACT_INVALID;
}

static int find_target(int *num, int dim, act_t act)
{
    int v = find_v(num, dim);
    switch (act) {
    case N_ACT_RIGHT:   return g_mv[v].right;
    case N_ACT_UP:      return g_mv[v].up;
    case N_ACT_DOWN:    return g_mv[v].down;
    case N_ACT_LEFT:    return g_mv[v].left;
    }
    return -1;
}

static int mand(int *num, int dim, act_t act)
{
    int i = 0, j = 0;
    int md = 0;
    int v = find_v(num, dim);
    int target = find_target(num, dim, act);
    int row = 0;
    int col = 0;
    int row1 = 0;
    int col1 = 0;
    int number = 0;

    if (-1 == target) {
        return INT_MAX;
    }

    for (i = 0; i < dim * dim; i++) {
        if (i == target) {
            continue;
        }
        row = i / dim;
        col = i % dim;
        if (i == v) {
            number = num[target];
        } else {
            number = num[i];
        }
        row1 = (number - 1) / dim;
        col1 = (number - 1) % dim;

        md += ABS(row1 - row) + ABS(col1 - col);
    }

    return md;
}

static act_t autoaction(int *num, int dim)
{
    int mdr = mand(num, dim, N_ACT_RIGHT);
    int mdl = mand(num, dim, N_ACT_LEFT);
    int mdu = mand(num, dim, N_ACT_UP);
    int mdd = mand(num, dim, N_ACT_DOWN);
    int min = 0;

    min = mdr;
    min = MIN(min, mdl);
    min = MIN(min, mdu);
    min = MIN(min, mdd);

    if (min == mdr) return N_ACT_RIGHT;
    if (min == mdl) return N_ACT_LEFT;
    if (min == mdu) return N_ACT_UP;
    if (min == mdd) return N_ACT_DOWN;

    return N_ACT_INVALID;
}

int main(int argc, char *argv[])
{
    int num[9] = {0};
    mv_t mv = {-1, -1, -1, -1};
    int act = 0;
    act_t action = N_ACT_INVALID;
    int steps = 0;

#ifdef M
    initscr();
#endif

    init(num, 3);
    print(num, 3);

    do {
#ifdef M
        act = getch();
        action = act2action(act);
#else
        sleep(1);
        action = autoaction(num, 3);
#endif
        if (N_ACT_INVALID == action) {
            continue;
        }
        move2(num, 3, action);
        steps++;
#ifdef M
        clear();
#endif
        print(num, 3);
    } while (0 == win(num, 3));

    printf("WIN at %d steps\n", steps);

#ifdef M
    endwin();
#endif

    return 0;
}
