#ifndef HASH_H
#define HASH_H

#include <stdbool.h>
#include "include/class.h"

extern const void * HashClass;

void hash_init(void);
bool hash_set(void * self, char * key, void * data);
void * hash_get(void * self, char * key);

#endif
