#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <libooc/string.conflict.h>

#include "file.struct.h"
#include "file.h"

struct FileClass {
    const struct Class class;
    void * (* file_read)(void * self);
};

static const void * FileClass;
       const void * File;

static void   FileClass_ctor(void * self, va_list * args_ptr);
static void   File_ctor(void * self, va_list * args_ptr);
static void   File_dtor(void * self);
static void * File_read(void * _self);

void
file_init(void) {
    if(!FileClass) {
        FileClass = new(
                Class,
                Class,
                "FileClass",
                sizeof(struct FileClass),
                false,
                Object_ctor,   FileClass_ctor,
                0);
    }
    if(!File) {
        File = new(
                FileClass,
                Object,
                "File",
                sizeof(struct File),
                false,
                Object_ctor,   File_ctor,
                Object_dtor,   File_dtor,
                file_read,     File_read,
                0);
    }
}

static void
FileClass_ctor(void * self, va_list * args_ptr) {
    struct FileClass * class = self;

    // inherit
    const struct Class * superclass = super_of(class);
    superclass->ctor(class, args_ptr);

    // override
    va_list args;
    va_copy(args, * args_ptr);
    typedef void (* func)();
    func select;
    while(select = va_arg(args, func)) {
        func method = va_arg(args, func);
        if(select == (func) file_read) {
            *(func *) &class->file_read = method;
        }
    }
}

static void
File_ctor(void * self, va_list * args_ptr) {
    struct File * file = self;
    file->filename = va_arg(* args_ptr, char *);
}

static void
File_dtor(void * self) {
    struct File * file = self;
    void * content = file->content;
    free(Object_inspect(content));
    delete(content);
    free(file);
}

void *
file_read(void * self) {
    struct File * file = self;
    const struct FileClass * class = (struct FileClass *) file->class;
    return class->file_read(file);
}

static void *
File_read(void * _self) {
    struct File * self = _self;
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
