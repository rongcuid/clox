#include "vm.h"

#include <stdio.h>

#include "compiler.h"
#include "debug.h"

struct vm vm;

static void reset_stack() { vm.stack_top = vm.stack; }

static enum interpret_result run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(op)                                                          \
  do {                                                                         \
    value_t b = pop();                                                         \
    value_t a = pop();                                                         \
    push(a op b);                                                              \
  } while (false)

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
    case OP_NEGATE:
      push(-pop());
      break;

    case OP_ADD:
      BINARY_OP(+);
      break;
    case OP_SUBTRACT:
      BINARY_OP(-);
      break;
    case OP_MULTIPLY:
      BINARY_OP(*);
      break;
    case OP_DIVIDE:
      BINARY_OP(/);
      break;
    case OP_RETURN:
      print_value(pop());
      printf("\n");
      return INTERPRET_OK;
    }
  }

#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
}

void init_vm() { reset_stack(); }

void free_vm() {}

enum interpret_result interpret(const char *source) {
  struct chunk chunk;
  init_chunk(&chunk);

  if (!compile(source, &chunk)) {
    free_chunk(&chunk);
    return INTERPRET_COMPILE_ERROR;
  }

  vm.chunk = &chunk;
  vm.ip = vm.chunk->code;

  enum interpret_result result = run();

  free_chunk(&chunk);
  return result;
}

void push(value_t value) {
  *vm.stack_top = value;
  ++vm.stack_top;
}

value_t pop() { return *--vm.stack_top; }