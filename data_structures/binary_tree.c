#include "../utils.h"

/*
 * Binary tree functions:
 * create, insert, search, get_max, get_min, delete_node, print, 
 * copy (only printing), delete
 */

typedef struct tree_node_s tree_node_t;

struct tree_node_s {
    tree_node_t *left;
    tree_node_t *right;
    int          key;
    int          value;
};

static tree_node_t *
tree_node_create(int key, int value)
{
    tree_node_t *node;
    
    node = xmalloc(sizeof (tree_node_t));

    node->key = key;
    node->value = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

tree_node_t *
tree_insert(tree_node_t *node, int key, int value)
{
    if (node == NULL) {
        return tree_node_create(key, value);
    }
    if (key < node->key) {
        node->left = tree_insert(node->left, key, value);
    } else if (key > node->key) {
        node->right = tree_insert(node->right, key, value);
    }

    return node;
}

tree_node_t *
tree_search(tree_node_t *node, int key)
{
    if (node == NULL) {
        return NULL;
    }
    if (node->key == key) {
        return node;
    }

    return key < node->key 
           ? tree_search(node->left, key)
           : tree_search(node->right, key);
}

tree_node_t *
tree_get_min(tree_node_t *node)
{
    if (node == NULL) {
        return NULL;
    }
    if (node->left == NULL) {
        return node;
    }
    return tree_get_min(node->left);
}

tree_node_t *
tree_get_max(tree_node_t *node)
{
    if (node == NULL) {
        return NULL;
    }
    if (node->right == NULL) {
        return node;
    }
    return tree_get_max(node->right);
}

tree_node_t *
tree_delete_node(tree_node_t *node, int key)
{
    tree_node_t *maxleft;

    if (node == NULL) {
        return NULL;
    }
    if (node->key > key) {
        node->left = tree_delete_node(node->left, key);
    } else if (node->key < key) {
        node->right = tree_delete_node(node->right, key);
    } else {
        if (node->left == NULL || node->right == NULL) {
            node = node->left == NULL ? node->right : node->left;
        } else {
            maxleft = tree_get_max(node->left);
            node->key = maxleft->key;
            node->value = maxleft->value;
            node->right = tree_delete_node(node, maxleft->key);
        }
    }

    return node;
}

void
tree_print(tree_node_t *node)
{
    if (node == NULL) {
        return;
    }
    tree_print(node->left);
    printf("Node key: %d, value: %d\n", node->key, node->value);
    tree_print(node->right);
}

void 
tree_delete(tree_node_t *node)
{
    if (node == NULL) {
        return;
    }
    tree_delete(node->left);
    tree_delete(node->right);
    printf("Node key: %d, value: %d\n", node->key, node->value);
    free(node);
}

void
tree_copy(tree_node_t *node)
{
    if (node == NULL) {
        return;
    }
    printf("Node key: %d, value: %d\n", node->key, node->value);
    tree_copy(node->left);
    tree_copy(node->right);
}

int main()
{
    tree_node_t *root = NULL;

    root = tree_insert(root, 0, 6);

    tree_insert(root, 1, 4);
    tree_insert(root, 2, 8);
    tree_insert(root, 3, 7);
    
    tree_print(root);
    printf("\n");

    tree_delete_node(root, 2);
    tree_copy(root);
    printf("\n");
    tree_delete(root);

    return 0;
}