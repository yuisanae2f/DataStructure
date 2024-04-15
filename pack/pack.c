#include "pack.h"
#include <stdlib.h>
#include <memory.h>

void pack(ptr_pack p, int size) {
    if(size) {
        p->container = calloc(size, 1);
    } else {
        p->container = 0;
    }

    p->size = size;
}
void packkill(ptr_pack p) {
    free(p->container);
    p->size = 0;
}
void packrealloc(ptr_pack p, int size) {
    void* a = realloc(p->container, size);

    if(a) {
        if(a != p->container) {
            free(p->container);
            p->container = a;
        }

        p->size = size;
    }
}

cfun void packcpy(ptr_pack p, ptr_pack src) {
    memcpy(p->container, src->container, src->size);
}