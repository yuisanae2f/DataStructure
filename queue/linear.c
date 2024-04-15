#include "linear.h"
#include <stdlib.h>
#include <memory.h>

struct queue queue(int size) {
    struct queue q;

    q._.container = malloc(size);
    q._.size = size;
    q.rear = 0;

    return q;
}

void queueen(ptr_queue q, void* e, int s) {
    memcpy(q->_.container + q->rear, e, s);
    q->rear += s;
}
void queuede(ptr_queue q, int size) {
    memcpy(q->_.container, q->_.container + size, q->rear - size);
    q->rear -= size;
}
char queueempty(ptr_queue q) {
    return q->rear == 0;
}
char queuefull(ptr_queue q) {
    return q->rear == q->_.size;
}
struct pack queuepeek(ptr_queue q, int size) {
    struct pack p;

    p.container = q->_.container;
    p.size = size;

    return p;
}
void queuekill(ptr_queue q) {
    free(q->_.container);
    q->_.size = q->rear = q->_.container = 0;
}