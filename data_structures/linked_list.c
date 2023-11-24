#include "../utils.h"

/*
 * Linked list
 *
 */

typedef struct list_part_s list_part_t;

struct list_part_s {
    void         *elts;
    unsigned int  nelts;
    list_part_t  *next;
};

typedef struct {
    list_part_t  *last;
    list_part_t   part;
    unsigned int  nalloc;
    size_t        size;
} list_t;

void *
list_create(unsigned int n, size_t size)
{
    list_t *list;
    void   *alloc;

    list = xmalloc(sizeof (list_t));
    alloc = xmalloc(n * size);

    list->part.elts = alloc;
    list->part.nelts = 0;
    list->part.next = NULL;
    list->last = &list->part;
    list->nalloc = n;
    list->size = size;

    return list;
}

void *
list_push(list_t *l)
{
    void        *elt, *alloc;
    list_part_t *last;
    
    last = l->last;

    if (l->nalloc == last->nelts) {
        last = xmalloc(sizeof (list_part_t));
        alloc = xmalloc(l->nalloc * l->size);

        last->elts = alloc;
        last->nelts = 0;
        last->next = NULL;

        l->last->next = last;
        l->last = last;
    }

    elt = (unsigned char *) last->elts + last->nelts * l->size;
    last->nelts++;

    return elt;
}

void *
list_insert(list_t *l, unsigned char *bytes)
{
    unsigned int  i;
    list_part_t  *part, *new;
    void         *elt, *alloc;

    part = &l->part;

    while (part != NULL) {
        for (i = 0; i < part->nelts; i++) {
            if (memcmp(part->elts + i * l->size, bytes, l->size) == 0) {
                new = xmalloc(sizeof (list_part_t));
                alloc = xmalloc(l->nalloc * l->size);

                new->elts = alloc;
                new->nelts = 0;
                new->next = part->next;

                part->next = new;
                elt = (unsigned char *) new->elts + new->nelts * l->size;
                new->nelts++;

                return elt;
            }
        }
        part = part->next;
    }

    return NULL;
}

void
list_destroy_part(list_part_t *lp)
{
    free(lp->elts);
    free(lp);
}

void 
list_remove(list_t *l, unsigned char *bytes)
{
    unsigned int  i;
    list_part_t  *part, *prev;

    part = &l->part;
    while (part != NULL) {
        for (i = 0; i < part->nelts; i++) {
            if (memcmp(part->elts + i * l->size, bytes, l->size) == 0) {
                if (prev == NULL) {
                    l->part = *part->next;
                    list_destroy_part(part);
                    return;
                }

                if (part->next == NULL) {
                    prev->next = NULL;
                    list_destroy_part(part);
                    return;
                }

                prev->next = part->next;
                list_destroy_part(part);
                return;
            }
        }

        prev = part;
        part = part->next;
    }

    return;
}



int main()
{
    unsigned int  i, cmpval;
    list_t       *list;
    list_part_t  *part;
    int          *ptr;

    list = list_create(1, sizeof (int));

    ptr = (int *) list_push(list);
    *ptr = 0;

    ptr = (int *) list_push(list);
    *ptr = 1;

    ptr = (int *) list_push(list);
    *ptr = 3;

    cmpval = 1;
    ptr = (int *) list_insert(list, (unsigned char *) &cmpval);
    if (ptr != NULL) {
        *ptr = 2;
    }

    cmpval = 1;
    list_remove(list, (unsigned char *) &cmpval);

    part = &list->part;
    while (part != NULL) {
        for (i = 0; i < part->nelts; i++) {
            printf("List part %d: %d\n", i, ((int *)part->elts)[i]);
        }
        part = part->next;
    }
    return 0;
}