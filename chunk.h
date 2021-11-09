#ifndef __CHUNK_H__
#define __CHUNK_H__

#include "common.h"

enum opcode {
  OP_RETURN,
};

struct chunk {
  int count;
  int capacity;
  uint8_t *code;
};

void init_chunk(struct chunk *chunk);
void write_chunk(struct chunk *chunk, uint8_t byte);
void free_chunk(struct chunk *chunk);

#endif // __CHUNK_H__