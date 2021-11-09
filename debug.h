#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "chunk.h"

void disassemble_chunk(struct chunk *chunk, const char *name);
int disassemble_instruction(struct chunk *chunk, int offset);

#endif // __DEBUG_H__