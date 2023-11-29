#include "utils.h"

void * 
xmalloc(size_t size)
{
    void *ptr;

    ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "malloc error");
        exit(1);
    }

    return ptr;
}

void *
xcalloc(size_t n, size_t size)
{
    void *ptr;

    ptr = calloc(n, size);
        if (!ptr) {
        fprintf(stderr, "calloc error");
        exit(1);
    }

    return ptr;
}

int 
is_prime(const int x)
{
    if (x < 2) { 
        return -1;
    }
    if (x < 4) {
        return 1;
    }
    if ((x % 2) == 0) {
        return 0;
    }

    for (int i = 3; i <= floor(sqrt((double) x)); i += 2) {
        if ((x % i) == 0) {
            return 0;
        }
    }
    return 1;
}

int 
next_prime(int x)
{
    while (is_prime(x) != 1) {
        x++;
    }
    return x;
}