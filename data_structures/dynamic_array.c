/*
 * Dynamic array functions:
 * create, push, push_n, remove_at, reverse, destroy
 */


#include "../utils.h"

typedef struct {
    void         *elts;
    unsigned int  nelts;
    unsigned int  nalloc;
    size_t        size;
} array_t;

array_t *
array_create(int len, size_t size)
{
    array_t *a;
    void    *alloc;

    if (len < 1) {
        fprintf(stderr, "Array length cannot be less that 1");
        return 0;
    }

    a = xmalloc(sizeof (array_t));
    alloc = xmalloc(len * size);

    a->elts = alloc;
    a->nalloc = len;
    a->nelts = 0;
    a->size = size;

    return a;
}

void *
array_push(array_t *a)
{
    void   *elt, *new;
    size_t  size;

    if (a->nelts == a->nalloc) {
        size = a->size * a->nalloc;

        new = xmalloc(size * 2);
        memcpy(new, a->elts, size);
        free(a->elts);

        a->elts = new;
        a->nalloc *= 2;
    }

    elt = (unsigned char *) a->elts + a->size * a->nelts;
    a->nelts++;
    
    return elt;
}

void *
array_push_n(array_t *a, unsigned int n)
{
    void         *elt, *new;
    unsigned int  nalloc;

    if (a->nelts + n > a->nalloc) {
        nalloc = 2 * ((n >= a->nalloc) ? n : a->nalloc);
        
        new = xmalloc(nalloc * a->size);
        memcpy(new, a->elts, a->size * a->nelts);
        free(a->elts);

        a->elts = new;
        a->nalloc = nalloc;
    }

    elt = (unsigned char *) a->elts + a->size * a->nelts;
    a->nelts += n;

    return elt;
}

void
array_remove_at(array_t *a, unsigned int i)
{
    a->nelts--;
    if (i != a->nelts) {
        memmove(a->elts + i * a->size,
                a->elts + (i + 1) * a->size, 
                a->size * (a->nelts - i));
    }
    memset(a->elts + a->nelts * a->size, 0, a->size);
}

void
array_reverse(array_t *a)
{
    unsigned int  i;
    void         *new;

    new = xmalloc(a->nalloc * a->size);

    for (i = 0; i < a->nelts / 2; i++) {
        memcpy(new + i * a->size,
               a->elts + (a->nelts - i - 1) * a->size,
               a->size);
        memcpy(new + (a->nelts - i - 1) * a->size,
               a->elts + i * a->size,
               a->size);
    }

    if (a->nelts % 2) {
        memcpy(new + (a->nelts / 2) * a->size,
               a->elts + (a->nelts / 2) * a->size,
               a->size);
    }
    
    free(a->elts);
    a->elts = new;
}

void 
array_destroy(array_t *a)
{
    free(a->elts);
    free(a);
}

int main()
{
    int          *last;
    unsigned int  i;
    array_t      *a;
    
    a = array_create(1, sizeof (int));

    last = (int *) array_push(a);
    *last = 0;
    last = (int *) array_push_n(a, 4);

    for (i = 0; i < 4; i++) {
        *((int *) last + i) = 1 + i;
    }

    array_remove_at(a, 1);
    for (i = 0; i < a->nelts; i++) {
        printf("Array[%d]: %d\n", i, *((int *) a->elts + i));
    }

    array_reverse(a);
    for (i = 0; i < a->nelts; i++) {
        printf("Array[%d]: %d\n", i, *((int *) a->elts + i));
    }

    array_destroy(a);

    return 0;
}
