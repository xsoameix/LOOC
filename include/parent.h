#ifndef PARENT_H
#define PARENT_H

#include "include/class.h"

struct Parent {
    const struct Class * class;
    int variable;
};

extern const void * ParentClass;

void parent_method(void * self);
void init_Parent(void);

#endif
