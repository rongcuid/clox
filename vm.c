#include "vm.h"

#include <stdio.h>

struct vm vm;

void init_vm() {}

void free_vm() {}

static enum interpret_result run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

  for (;;) {
    uint8_t instruction;
    switch (instruction = READ_BYTE()) {
    case OP_CONSTANT: {
      value_t constant = READ_CONSTANT();
      print_value(constant);
      printf("\n");
      break;
    }
    case OP_RETURN:
      return INTERPRET_OK;
    }
  }

#undef READ_BYTE
#undef READ_CONSTANT
}

enum interpret_result interpret(struct chunk *chunk) {
  vm.chunk = chunk;
  vm.ip = vm.chunk->code;
  return run();
}