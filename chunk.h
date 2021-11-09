#ifndef __CHUNK_H__
#define __CHUNK_H__

#include "common.h"

#include "value.h"

enum opcode {
  OP_CONSTANT,
  OP_NEGATE,
  OP_RETURN,
};

struct chunk {
  int count;
  int capacity;
  uint8_t *code;
  int *lines;
  struct value_array constants;
};

void init_chunk(struct chunk *chunk);
void write_chunk(struct chunk *chunk, uint8_t byte, int line);
void free_chunk(struct chunk *chunk);

int add_constant(struct chunk *chunk, value_t value);

#endif // __CHUNK_H__