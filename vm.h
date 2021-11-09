#ifndef __VM_H__
#define __VM_H__

#include "chunk.h"

struct vm {
  struct chunk *chunk;
  uint8_t *ip;
};

enum interpret_result {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR,
};

void init_vm();
void free_vm();

enum interpret_result interpret(struct chunk *chunk);

#endif // __VM_H__