#ifndef __TABLE_H__
#define __TABLE_H__

#include "common.h"
#include "value.h"

struct entry {
    struct obj_struct *key;
    value_t value;
};

struct table {
    int count;
    int capacity;
    struct entry *entries;
};

#endif // __TABLE_H__