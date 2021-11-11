#include "memory.h"

#include "vm.h"

void *reallocate(void *pointer, size_t old_size, size_t new_size) {
  if (new_size == 0) {
    free(pointer);
    return NULL;
  }

  void *result = realloc(pointer, new_size);
  if (result == NULL)
    exit(1);
  return result;
}

static void free_object(struct obj *obj) {
  switch (obj->type) {
  case OBJ_STRING: {
    struct obj_string *string = (struct obj_string *)obj;
    FREE_ARRAY(char, string->chars, string->length + 1);
    FREE(struct obj_string, obj);
    break;
  }
  }
}

void free_objects() {
  struct obj *obj = vm.objects;
  while (obj != NULL) {
    struct obj *next = obj->next;
    free_object(obj);
    obj = next;
  }
}