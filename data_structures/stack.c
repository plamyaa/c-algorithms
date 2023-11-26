#include "../utils.h"

/*
 * Stack functions:
 * create, push, pop, is_empty, destroy_node, destroy
 */

typedef struct stack_node_s stack_node_t;

struct stack_node_s {
    void         *elts;
    stack_node_t *next;
};

typedef struct {
    stack_node_t *top;
    size_t        size;
} _stack_t;

void *
stack_create(size_t size)
{
    _stack_t *s;

    s = xmalloc(sizeof (_stack_t));
    s->size = size;
    s->top = NULL;
    
    return s;
}

int
is_empty(_stack_t *s)
{
    return s->top ? 0 : 1;
}

void *
stack_push(_stack_t *s)
{
    stack_node_t *new;
    void         *alloc, *elt;

    new = xmalloc(sizeof (stack_node_t));
    alloc = xmalloc(s->size);
    new->elts = alloc;

    new->next = s->top;
    s->top = new;

    elt = new->elts;
    return elt;
}

void
stack_destroy_node(stack_node_t *n)
{
    free(n->elts);
    free(n);
}

void 
stack_pop(_stack_t *s, void *dest)
{
    stack_node_t *top;

    if (!is_empty(s)) {
        top = s->top;
        s->top = top->next;

        memcpy(dest, top->elts, s->size);
        stack_destroy_node(top);
    } else {
        dest = NULL;
    }
}

void
stack_destroy(_stack_t *s)
{
    stack_node_t *next, *top;
    top = s->top;

    while (top) {
        next = top->next;
        stack_destroy_node(top);
        top = next;
    }
    free(s);
}

int main()
{
    _stack_t     *s;
    stack_node_t *node;
    int          *ptr, popval;

    s = stack_create(sizeof (int));

    ptr = (int *) stack_push(s);
    *ptr = 0;

    ptr = (int *) stack_push(s);
    *ptr = 1;

    ptr = (int *) stack_push(s);
    *ptr = 2;

    stack_pop(s, &popval);

    node = s->top;

    while (node) {
        printf("Stack value: %d\n", *((int *)node->elts));
        node = node->next;
    }

    stack_destroy(s);

    return 0;
}