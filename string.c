#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/string.h"

static struct String *
String_new(char * text) {
    struct String * class = malloc(sizeof(struct String));
    class->text = malloc(strlen(text) + 1);
    strcpy(class->text, text);
    return class;
}

static void
String_free(struct String * class) {
    free(class->text);
    free(class);
}

const struct StringConst String = {
    String_new,
    String_free
};
