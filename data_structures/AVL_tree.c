#include "../utils.h"

/*
 * AVL tree functions:
 * node_create, insert, node_delete
 */

typedef struct tree_node_s tree_node_t;

struct tree_node_s {
    tree_node_t *left;
    tree_node_t *right;
    int          key;
    int          value;
    int          height;
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
    node->height = 0;

    return node;
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

void
tree_update_height(tree_node_t *node)
{
    if (node->left && node->right) {
        node->height = max(node->left->height, node->right->height) + 1;
    }
}

int
tree_get_height(tree_node_t *node)
{
    return node == NULL ? -1 : node->height;
}

int
tree_get_balance(tree_node_t *node)
{
    return (node == NULL) 
           ? 0
           : tree_get_height(node->right) - tree_get_height(node->left);
}

void
tree_swap_nodes(tree_node_t* a, tree_node_t *b)
{
    int tmpkey, tmpvalue;
    tmpkey = a->key;
    tmpvalue = a->value;

    a->key = b->key;
    a->value = b->value;

    b->key = tmpkey;
    b->value = tmpvalue;
}

void
tree_right_rotate(tree_node_t* node)
{
    tree_node_t *buf;

    tree_swap_nodes(node, node->left);
    buf = node->right;

    node->right = node->left;
    node->left = node->right->left;  

    node->right->left = node->right->right;
    node->right->right = buf;

    tree_update_height(node->right);
    tree_update_height(node);
}

void
tree_left_rotate(tree_node_t* node)
{
    tree_node_t *buf;

    tree_swap_nodes(node, node->right);
    buf = node->left;

    node->left = node->right;
    node->right = node->left->right;  

    node->left->right = node->left->left;
    node->left->left = buf;

    tree_update_height(node->left);
    tree_update_height(node);
}

void
tree_balance(tree_node_t *node)
{
    int balance;

    balance = tree_get_balance(node);
    if (balance == -2) {
        if (tree_get_balance(node->left) == 1) {
            tree_left_rotate(node->left);
        }
        tree_right_rotate(node);
    } else if (balance == 2) {
        if (tree_get_balance(node->right) == -1) {
            tree_right_rotate(node->right);
        }
        tree_left_rotate(node);
    }
}

void
tree_insert(tree_node_t *node, int key, int value)
{
    if (key < node->key) {
        if (node->left == NULL) {
            node->left = tree_node_create(key, value);
        } else {
            tree_insert(node->left, key, value);
        }
    } else if (key >= node->key) {
        if (node->right == NULL) {
            node->right = tree_node_create(key, value);
        } else {
            tree_insert(node->right, key, value);
        }
    }

    tree_update_height(node);
    tree_balance(node);
}

void
tree_node_delete(tree_node_t *node, int key)
{
    tree_node_t *max_left, *temp;

    if (node == NULL) {
        return;
    } else if (key < node->key) {
        tree_node_delete(node->left, key);
    } else if (key > node->key) {
        tree_node_delete(node->right, key);
    } else {
        if (node->left == NULL || node->right == NULL) {
            temp = node->left ? node->left : node->right;

            if (temp == NULL) 
            { 
                temp = node; 
                node = NULL; 
            } 
            else {
                *node = *temp;
            }
            free(temp); 
        } else {
            max_left = tree_get_min(node->right);
            node->key = max_left->key;
            node->value = max_left->value;
            tree_node_delete(node->left, max_left->key);
        }
    }

    if (node != NULL) {
        tree_update_height(node);
        tree_balance(node);
    }
}

void tree_print(tree_node_t *node)
{
    if (node != NULL) {
        tree_print(node->left);
        printf("Node key: %d, value: %d\n", node->key, node->value);
        tree_print(node->right);
    }
}

int main()
{
    tree_node_t *root = NULL;

    root = tree_node_create(0, 1);

    tree_insert(root, 1, 5);
    tree_insert(root, 2, 4);
    tree_insert(root, 3, 6);
    tree_insert(root, 4, 8);

    tree_node_delete(root, 3);
    tree_print(root);

    return 0;
}