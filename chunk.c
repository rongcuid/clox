#include "chunk.h"
#include "memory.h"

void init_chunk(struct chunk *chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  init_value_array(&chunk->constants);
}

void write_chunk(struct chunk *chunk, uint8_t byte) {
  if (chunk->capacity < chunk->count + 1) {
    int old_capacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(old_capacity);
    chunk->code =
        GROW_ARRAY(uint8_t, chunk->code, old_capacity, chunk->capacity);
  }
  chunk->code[chunk->count] = byte;
  chunk->count++;
}

void free_chunk(struct chunk *chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  free_value_array(&chunk->constants);
  init_chunk(chunk);
}

int add_constant(struct chunk *chunk, value_t value) {
  write_value_array(&chunk->constants, value);
  return chunk->constants.count - 1;
}
