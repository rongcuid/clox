#ifndef __VALUE_H__
#define __VALUE_H__

#include "common.h"

enum value_type {
  VAL_BOOL,
  VAL_NIL,
  VAL_NUMBER,
};

typedef struct {
  enum value_type type;
  union {
    bool boolean;
    double number;
  } as;
} value_t;

struct value_array {
  int capacity;
  int count;
  value_t *values;
};

#define IS_BOOL(value) ((value).type == VAL_BOOL)
#define IS_NIL(value) ((value).type == VAL_NIL)
#define IS_NUMBER(value) ((value).type == VAL_NUMBER)

#define AS_BOOL(value) ((value).as.boolean)
#define AS_NUMBER(value) ((value).as.number)

#define BOOL_VAL(value) ((value_t){VAL_BOOL, {.boolean = value}})
#define NIL_VAL ((value_t){VAL_NIL, {.number = 0}})
#define NUMBER_VAL(value) ((value_t){VAL_NUMBER, {.number = value}})

void init_value_array(struct value_array *array);
void write_value_array(struct value_array *array, value_t value);
void free_value_array(struct value_array *array);

void print_value(value_t value);

#endif // __VALUE_H__