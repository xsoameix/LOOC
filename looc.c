#include "include/string.h"

int main(void) {
    struct String * la = String.new("la");
    puts(la->text);
    String.free(la);
    return 0;
}
