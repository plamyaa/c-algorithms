#include "hash_table.h"

static ht_item_t *
ht_create_item(const char *key, const char *value)
{
    ht_item_t *i;

    i = xmalloc(sizeof (ht_item_t));
    i->key = strdup(key);
    i->value = strdup(value);

    return i;
}

static ht_t *
ht_new_sized(const int base_size)
{
    ht_t *ht;

    ht = xmalloc(sizeof (ht_t));
    ht->base_size = base_size;
    ht->size = next_prime(ht->base_size);

    ht->count = 0;
    ht->items = xcalloc(ht->size, sizeof (ht_item_t *));

    return ht;
}

ht_t *
ht_create()
{
    return ht_new_sized(HT_INITIAL_SIZE);
}

static void 
ht_destroy_item(ht_item_t *i)
{
    free(i->key);
    free(i->value);
    free(i);
    i = NULL;
}

void
ht_destroy(ht_t *ht)
{
    ht_item_t    *item;
    unsigned int  i;

    for (i = 0; i < ht->size; i++) {
        item = ht->items[i];
        if (item != NULL && item != &HT_DELETED_ITEM) {
            ht_destroy_item(item);
        }
    }
    
    free(ht->items);
    free(ht);
}

static int
ht_hash(const char *key, const int a, const int mod)
{
    int  i;
    long hash;

    hash = 0;
    const int len_s = strlen(key);
    for (i = 0; i < len_s; i++) {
        hash += (long) pow(a, len_s - (i + 1)) * key[i];
        hash = hash % mod;
    }

    return (int) hash;
}

static int 
floor_mod(const int mod_num, const int check_num)
{
    return check_num % mod_num == 0 ? check_num - 1 : check_num;
}

static int
ht_get_hash(const char *key, const int num_buckets, const int attempt)
{
    const int hash_a = ht_hash(key, HT_PRIME_CONST1, num_buckets);
    const int hash_b = ht_hash(key, HT_PRIME_CONST2, num_buckets);
    const int mod_index = floor_mod(num_buckets, (hash_b + 1));
    return (hash_a + attempt * mod_index) % num_buckets;
}

void
ht_insert(ht_t *ht, const char *key, const char *value)
{
    ht_item_t *item, *curitem;
    int        index, i;

    const int load = ht->count * 100 / ht->size;
    if (load > 70) {
        ht_resize_up(ht);
    }

    item = ht_create_item(key, value);
    index = ht_get_hash(key, ht->size, 0);
    curitem = ht->items[index];

    i = 0;
    while (curitem != NULL) {
        if (curitem != &HT_DELETED_ITEM) {
            if (strcmp(key, item->key) == 0) {
                ht_destroy_item(item);
                ht->items[index] = item;
                return;
            }
        }

        index = ht_get_hash(key, ht->size, i);
        curitem = ht->items[index];
        i++;
    }

    ht->items[index] = item;
    ht->count++;
}

char *
ht_search(ht_t *ht, const char *key)
{
    ht_item_t *item;
    int        index, i;

    index = ht_get_hash(key, ht->size, 0);
    item = ht->items[index];

    i = 0;
    while (item != NULL && item != &HT_DELETED_ITEM) {
        if (strcmp(key, item->key) == 0) {
            return item->value;
        }

        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    }

    return NULL;
}

void
ht_delete(ht_t *ht, const char *key)
{
    ht_item_t *item;
    int        index, i;

    const int load = ht->count * 100 / ht->size;
    if (load < 10) {
        ht_resize_down(ht);
    }

    index = ht_get_hash(key, ht->size, 0);
    item = ht->items[index];
    
    i = 0;
    while (item != NULL) {
        if (item != &HT_DELETED_ITEM) {
            if (strcmp(item->key, key) == 0) {
                ht_destroy_item(item);
                ht->items[index] = &HT_DELETED_ITEM;
                ht->count--;
                return;
            }
        }

        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    }
}

static void 
ht_resize_up(ht_t *ht)
{
    const int new_size = ht->base_size * 2;
    ht_resize(ht, new_size);
}

static void 
ht_resize_down(ht_t *ht)
{
    const int new_size = ht->base_size / 2;
    ht_resize(ht, new_size);
}

static void
ht_resize(ht_t *ht, const int base_size)
{
    unsigned int   i;
    ht_t          *new_ht;
    ht_item_t      *item;
    ht_item_t    **tmp_items;

    if (base_size < HT_INITIAL_SIZE) {
        return;
    }

    new_ht = ht_new_sized(base_size);
    for (i = 0; i < ht->size; i++) {
        item = ht->items[i];
        if (item != NULL && item != &HT_DELETED_ITEM) {
            ht_insert(new_ht, item->key, item->value);
        }
    }

    ht->base_size = new_ht->base_size;
    ht->count = new_ht->count;

    const int tmp_size = ht->size;
    ht->size = new_ht->size;
    new_ht->size = tmp_size;

    tmp_items = ht->items;
    ht->items = new_ht->items;
    new_ht->items = tmp_items;

    ht_destroy(new_ht);
}

int main()
{
    ht_t *ht;
    char *search_value;

    ht = ht_create();

    ht_insert(ht, "1", "one");
    ht_insert(ht, "2", "two");
    ht_insert(ht, "3", "three");
    
    search_value = ht_search(ht, "2");

    ht_delete(ht, "2");
    search_value = ht_search(ht, "2");
    printf("%s\n", search_value);

    ht_destroy(ht);

    return 0;
}

