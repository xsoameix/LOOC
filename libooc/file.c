#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <libooc/string.conflict.h>

#include "file.struct.h"
#include "inttype.h"
#include "object_type.h"

#define FILENAME self->filename
#define CONTENT self->content
#define FILE_PTR self->file

O_DEF_CLASS(File, Object)

override
def(ctor, void : va_list * @args_ptr) {
    FILENAME = va_arg(* args_ptr, char *);
    CONTENT = NULL;
    FILE_PTR = NULL;
}

override
def(dtor, void) {
    if(CONTENT != NULL) {
        free(inspect(CONTENT));
        delete(CONTENT);
        CONTENT = NULL;
    }
    free(self);
}

def(read, o) {
    FILE * file = fopen(FILENAME, "rb");
    assert(file != NULL);

    // obtain the size
    fseek(file, 0, SEEK_END);
    uint_t size = ftell(file);
    rewind(file);

    // read into buffer
    char * buffer = malloc(size + 1); // EOF = 1 char
    uint_t read = fread(buffer, 1, size, file);
    assert(read == size);

    // add EOF
    buffer[size] = '\0';

    fclose(file);
    o content = new(String, buffer);
    CONTENT = content;
    return content;
}

def(open, void : const char * @mode . void (* @func)(o file)) {
    FILE * file = fopen(FILENAME, mode);
    FILE_PTR = file;
    assert(file != NULL);
    func(self);
    fclose(file);
    FILE_PTR = NULL;
}

void
File_puts(o _self, const char * string) {
    struct File * self = _self;
    fputs(string, FILE_PTR);
}

void
File_printf(o _self, const char * format, ...) {
    struct File * self = _self;
    va_list ap;
    va_start(ap, format);
    vfprintf(FILE_PTR, format, ap);
    va_end(ap);
}
