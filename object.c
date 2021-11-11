#include "object.h"

#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "value.h"
#include "vm.h"

#define ALLOCATE_OBJ(type, object_type)                                        \
  (type *)allocate_object(sizeof(type), object_type)

static void *allocate_object(size_t size, enum obj_type type) {
  struct obj *object = (struct obj *)reallocate(NULL, 0, size);
  object->type = type;
  object->next = vm.objects;
  vm.objects = object;
  return object;
}

static struct obj_string *allocate_string(char *chars, int length) {
  struct obj_string *string = ALLOCATE_OBJ(struct obj_string, OBJ_STRING);
  string->length = length;
  string->chars = chars;
  return string;
}

struct obj_string *copy_string(const char *chars, int length) {
  char *heap_chars = ALLOCATE(char, length + 1);
  memcpy(heap_chars, chars, length);
  heap_chars[length] = '\0';
  return allocate_string(heap_chars, length);
}

struct obj_string *take_string(char *chars, int length) {
  return allocate_string(chars, length);
}

void print_object(value_t value) {
  switch (OBJ_TYPE(value)) {
  case OBJ_STRING:
    printf("%s", AS_CSTRING(value));
    break;
  }
}