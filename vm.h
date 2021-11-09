#ifndef __VM_H__
#define __VM_H__

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

struct vm {
  struct chunk *chunk;
  uint8_t *ip;
  value_t stack[STACK_MAX];
  value_t *stack_top;
};

enum interpret_result {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR,
};

void init_vm();
void free_vm();

enum interpret_result interpret(struct chunk *chunk);
void push(value_t value);
value_t pop();

#endif // __VM_H__