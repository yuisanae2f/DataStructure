#include "./linked.h"
#include <stdlib.h>
#include <stdio.h>

static inline void child(ptr_deckchild a, int s) {
    pack(&a->container, s);
    a->p[0] = a->p[1] = 0;
}

static inline void kill(ptr_deckchild a, char b) {
    if(!a) return;
    if(a->p[b]) kill(a->p[b], b);

    packkill(&a->container);
    free(a);
}

void deck(ptr_deck d) {
    d->wl = d->wr = malloc(sizeof(struct deckchild));
    d->count = 0;
    child(d->wl, 0);
}

void deckkill(ptr_deck base) {
    kill(base->wl, 1);
}

cfun void deckaddfront(ptr_deck base, ptr_pack l) {
    if(!base->count) {
        packrealloc(&base->wl->container, l->size);
        packcpy(&base->wl->container, l);

        base->count++;
        return;
    }


    ptr_deckchild new = malloc(sizeof(struct deckchild));

    child(new, l->size);
    packcpy(&new->container, l);

    new->p[1] = base->wl;
    base->wl->p[0] = new;
    base->wl = new;

    base->count++;
}
cfun void deckaddrear(ptr_deck base, ptr_pack r) {

    if(!base->count) {
        packrealloc(&base->wl->container, r->size);
        packcpy(&base->wl->container, r);

        base->count++;
        return;
    }

    ptr_deckchild new = malloc(sizeof(struct deckchild));

    child(new, r->size);
    packcpy(&new->container, r);

    new->p[0] = base->wr;
    base->wr = base->wr->p[1] = new;

    base->count++;
}

cfun void deckdelfront(ptr_deck base) {
    if(!(base->count--)) {
        base->count++;
        return;
    }

    ptr_deckchild tokill = base->wl;
    base->wl = tokill->p[1];
    base->wl->p[0] = 0;

    kill(tokill, 0);
}

cfun void deckdelrear(ptr_deck base) {
    if(!(base->count--)) {
        base->count++;
        return;
    }

    ptr_deckchild tokill = base->wr;
    base->wr = tokill->p[0];
    base->wr->p[1] = 0;
    

    kill(base->wr->p[1], 1);
}

cfun struct pack deckpeekfront(ptr_deck base) {
    return base->wl->container;
}
cfun struct pack deckpeekrear(ptr_deck base) {
    return base->wr->container;
}

char deckempty(ptr_deck base) {
    return !base->count;
}