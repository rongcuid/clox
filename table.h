#ifndef __TABLE_H__
#define __TABLE_H__

#include "common.h"
#include "value.h"

struct entry {
  struct obj_string *key;
  value_t value;
};

struct table {
  int count;
  int capacity;
  struct entry *entries;
};

void init_table(struct table *table);
void free_table(struct table *table);
bool table_set(struct table *table, struct obj_string *key, value_t value);

#endif  // __TABLE_H__