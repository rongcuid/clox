#ifndef __COMPILER_H__
#define __COMPILER_H__

#include "common.h"
#include "object.h"
#include "vm.h"

bool compile(const char *source, struct chunk *chunk);

#endif // __COMPILER_H__