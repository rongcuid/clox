#ifndef __VALUE_H__
#define __VALUE_H__

#include "common.h"

typedef double value_t;

struct value_array {
  int capacity;
  int count;
  value_t *values;
};

void init_value_array(struct value_array *array);
void write_value_array(struct value_array *array, value_t value);
void free_value_array(struct value_array *array);

void print_value(value_t value);

#endif // __VALUE_H__