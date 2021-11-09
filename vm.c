#include "vm.h"

#include <stdio.h>

#include "debug.h"

struct vm vm;

static void reset_stack() {
  vm.stack_top = vm.stack;
}

static enum interpret_result run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

  for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
    printf("          ");
    for (value_t *slot = vm.stack; slot < vm.stack_top; ++slot) {
      printf("[ ");
      print_value(*slot);
      printf(" ]");
    }
    printf("\n");
    disassemble_instruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
    uint8_t instruction;
    switch (instruction = READ_BYTE()) {
    case OP_CONSTANT: {
      value_t constant = READ_CONSTANT();
      push(constant);
      break;
    }
    case OP_RETURN:
      print_value(pop());
      printf("\n");
      return INTERPRET_OK;
    }
  }

#undef READ_BYTE
#undef READ_CONSTANT
}

void init_vm() {
  reset_stack();
}

void free_vm() {}


enum interpret_result interpret(struct chunk *chunk) {
  vm.chunk = chunk;
  vm.ip = vm.chunk->code;
  return run();
}

void push(value_t value) {
  *vm.stack_top = value;
  ++vm.stack_top;
}

value_t pop() {
  return *--vm.stack_top;
}