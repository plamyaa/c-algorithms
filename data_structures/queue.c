#include "../utils.h"

/*
 * Queue functions:
 * create, push, pop, destroy_node, destroy
 */

typedef struct queue_node_s queue_node_t;

struct queue_node_s {
    void         *elts;
    queue_node_t *next;
};

typedef struct {
    queue_node_t *back;
    queue_node_t *front;
    size_t        size;
    unsigned int  nnodes;
} queue_t;

queue_t *
queue_create(size_t size)
{
    queue_t *q;

    q = xmalloc(sizeof(queue_t));

    q->size = size;
    q->nnodes = 0;

    return q;
}

void *
queue_push(queue_t *q)
{
    queue_node_t *new;
    void         *alloc, *elt;

    new = xmalloc(sizeof(queue_node_t));
    alloc = xmalloc(q->size);

    new->elts = alloc;
    new->next = q->back;
    q->back = new;
    
    if (q->nnodes == 0) {
        q->front = new;
    }
    
    elt = new->elts;
    q->nnodes++;
    return elt;
}

void
queue_destroy_node(queue_node_t *n)
{
    free(n->elts);
    free(n);
}

void
queue_pop(queue_t *q, void *dest)
{
    queue_node_t *front, *prevfront;
    unsigned int i;

    if (q->nnodes) {
        front = q->front;
        prevfront = q->back;

        if (q->nnodes == 1) {
            q->front = NULL;
            q->back = NULL;
        } else {
            for (i = 0; i < q->nnodes - 2; i++) {
                prevfront = prevfront->next;
            }
            q->front = prevfront;
            q->front->next = NULL;
        }

        memcpy(dest, front->elts, q->size);
        queue_destroy_node(front);
        q->nnodes--;
    } else {
        dest = NULL;
    }
}

void
queue_destroy(queue_t *q)
{
    queue_node_t *back, *next;

    if (q->nnodes) {
        back = q->back;
        while (back) {
            next = back->next;
            queue_destroy_node(back);
            back = next;
        }
    }

    free(q);
}

int main()
{
    queue_t      *q;
    queue_node_t *node;
    int           *ptr, popval;

    q = queue_create(sizeof (int));

    ptr = (int *) queue_push(q);
    *ptr = 0;

    ptr = (int *) queue_push(q);
    *ptr = 1;
    
    ptr = (int *) queue_push(q);
    *ptr = 2;

    queue_pop(q, &popval);

    node = q->back;

    while (node) {
        printf("Queue value: %d\n", *((int *)node->elts));
        node = node->next;
    }

    return 0;
}