#include "include/parent.h"

char * class_name_of(void * obj) {
    struct Object * object = obj;
    return object->class->name;
}

int main(void) {
    init_Parent();
    struct Parent * parent = new(ParentClass, 2);
    parent_method(parent);
    puts(class_name_of(parent));
    return 0;
}
