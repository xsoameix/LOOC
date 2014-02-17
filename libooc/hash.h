#ifndef HASH_H
#define HASH_H

#include <stdbool.h>

#include <libooc/class.h>

extern const void * Hash;

void   hash_init(void);
bool   hash_set(void * self, void * key, void * data);
void * hash_get(void * self, void * key);

#endif
