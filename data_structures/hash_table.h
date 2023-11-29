#include "../utils.h"

#define HT_INITIAL_SIZE 50
#define HT_PRIME_CONST1 151
#define HT_PRIME_CONST2 163


typedef struct {
    char *key;
    char *value;
} ht_item_t;

static ht_item_t HT_DELETED_ITEM = {NULL, NULL};

typedef struct {
    size_t         size;
    int            base_size;
    unsigned int   count;
    ht_item_t    **items;
} ht_t;


ht_t *ht_create();
void ht_insert(ht_t *ht, const char *key, const char *value);
char *ht_search(ht_t *ht, const char *key);
void ht_delete(ht_t *ht, const char *key);
void ht_destroy(ht_t *ht);

static ht_item_t *ht_create_item(const char *key, const char *value);
static ht_t *ht_new_sized(const int base_size);
static int ht_hash(const char *key, const int a, const int mod);
static int floor_mod(const int mod_num, const int check_num);
static int ht_get_hash(const char *key, const int num_bucket, const int attempt);
static void ht_destroy_item(ht_item_t *i);
static void ht_resize_up(ht_t *ht);
static void ht_resize_down(ht_t *ht);
static void ht_resize(ht_t *ht, const int base_size);