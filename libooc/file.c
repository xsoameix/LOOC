#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <libooc/string.conflict.h>

#include "file.struct.h"
#include "inttype.h"

O_DEF_CLASS(File, Object)

override
def(ctor, void : va_list * @args_ptr) {
    self->filename = va_arg(* args_ptr, char *);
    self->content = NULL;
    self->file = NULL;
}

override
def(dtor, void) {
    if(self->content != NULL) {
        void * content = self->content;
        free(inspect(content));
        delete(content);
        self->content = NULL;
    }
    free(self);
}

def(read, void *) {
    FILE * file = fopen(self->filename, "rb");
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
    void * content = new(String, buffer);
    self->content = content;
    return content;
}

def(open, void : const char * @mode . void (* @func)(void * self, void * file) . void * @_self_) {
    FILE * file = fopen(self->filename, mode);
    self->file = file;
    assert(file != NULL);
    func(_self_, self);
    fclose(file);
    self->file = NULL;
}

void
File_puts(void * _self, const char * string) {
    struct File * self = _self;
    fputs(string, self->file);
}

void
File_printf(void * _self, const char * format, ...) {
    struct File * self = _self;
    va_list ap;
    va_start(ap, format);
    vfprintf(self->file, format, ap);
    va_end(ap);
}
