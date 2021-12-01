#include "object.h"

#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "value.h"
#include "vm.h"

#define ALLOCATE_OBJ(type, object_type) \
  (type *)allocate_object(sizeof(type), object_type)

static void *allocate_object(size_t size, enum obj_type type) {
  struct obj *object = (struct obj *)reallocate(NULL, 0, size);
  object->type = type;
  object->next = vm.objects;
  vm.objects = object;
  return object;
}

static struct obj_string *allocate_string(char *chars, int length,
                                          uint32_t hash) {
  struct obj_string *string = ALLOCATE_OBJ(struct obj_string, OBJ_STRING);
  string->length = length;
  string->chars = chars;
  string->hash = hash;
  return string;
}

static uint32_t hash_string(const char *key, int length) {
  uint32_t hash = 2166136261u;
  for (int i=0; i<length; i++) {
    hash ^= (uint8_t) key[i];
    hash *= 16777619;
  }
  return hash;
}

struct obj_string *copy_string(const char *chars, int length) {
  uint32_t hash = hash_string(chars, length);
  char *heap_chars = ALLOCATE(char, length + 1);
  memcpy(heap_chars, chars, length);
  heap_chars[length] = '\0';
  return allocate_string(heap_chars, length, hash);
}

struct obj_string *take_string(char *chars, int length) {
  uint32_t hash = hash_string(chars, length);
  return allocate_string(chars, length, hash);
}

void print_object(value_t value) {
  switch (OBJ_TYPE(value)) {
    case OBJ_STRING:
      printf("%s", AS_CSTRING(value));
      break;
  }
}