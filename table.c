#include "table.h"

#include <stdlib.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "table.h"
#include "value.h"

void init_table(struct table *table) {
    table->count = 0;
    table->capacity = 0;
    table->entries = NULL;
}

void free_table(struct table *table) {
    FREE_ARRAY(struct entry, table->entries, table->capacity);
    init_table(table);
}

bool table_set(struct table *table, struct obj_string *key, value_t value) {
    if (table->count + 1 > table->capacity * TABLE_MAX_LOAD) {
        int capacity = GROW_CAPACITY(table->capacity);
        adjust_capacity(table, capacity);
    }
    struct entry *entry = find_entry(table->entries, table->capacity, key);
    bool is_new_key = entry->key == NULL;
    if (is_new_key) table->count++;

    entry->key = key;
    entry->value = value;
    return is_new_key;
}