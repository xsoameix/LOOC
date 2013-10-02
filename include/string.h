#ifndef STRING_H
#define STRING_H

extern const struct StringConst String;

struct StringConst {
    struct String * (* new) (char * name);
    void (* free) (struct String *);
};

struct String {
    char * text;
};

#endif
