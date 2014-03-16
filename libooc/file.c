#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <libooc/string.conflict.h>

#include "file.struct.h"

def_class(File, Object)

override
def(ctor, void : va_list * @args_ptr) {
    self->filename = va_arg(* args_ptr, char *);
}

override
def(dtor, void) {
    void * content = self->content;
    free(inspect(content));
    delete(content);
    free(self);
}

def(read, void *) {
    FILE * file = fopen(self->filename, "rb");
    assert(file != NULL);

    // obtain the size
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    // read into buffer
    char * buffer = malloc(size + 1); // EOF = 1 char
    size_t read = fread(buffer, 1, size, file);
    assert(read == size);

    // add EOF
    buffer[(int) size] = '\0';

    fclose(file);
    void * content = new(String, buffer);
    self->content = content;
    return content;
}
