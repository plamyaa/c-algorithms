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
