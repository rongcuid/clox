#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "common.h"

#include "value.h"

#define OBJ_TYPE(value) (AS_OBJ(value)->type)

#define IS_STRING(value) is_obj_type(value, OBJ_STRING)

#define AS_STRING(value) ((struct obj_string *)AS_OBJ(value))
#define AS_CSTRING(value) (((struct obj_string *)AS_OBJ(value))->chars)

enum obj_type {
  OBJ_STRING,
};

struct obj {
  enum obj_type type;
  struct obj *next;
};

struct obj_string {
  struct obj obj;
  int length;
  char *chars;
};

static inline bool is_obj_type(value_t value, enum obj_type type) {
  return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

struct obj_string *copy_string(const char *chars, int length);
struct obj_string *take_string(char *chars, int length);

void print_object(value_t value);

#endif // __OBJECT_H__