#include "utils.h"

void * 
xmalloc(size_t n)
{
    void *ptr;

    ptr = malloc(n * sizeof (int));
    if (!ptr) {
        fprintf(stderr, "malloc error");
        exit(1);
    }

    return ptr;
}
