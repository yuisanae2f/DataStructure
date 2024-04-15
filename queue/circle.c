#include <stdlib.h>
#include <stdio.h>
#include "circle.h"

struct queue_circle queue_circle(int size) {
    struct queue_circle q;
    q.base = queue(size);
    q.front = 0;

    return q;
}

// 6: 3, 5 -> 5
char queue_circle_en(ptr_queue_circle q, void* e, int s) {
    for(int i = 0; i < s; i++) {
        if((i + 1 + q->base.rear) % q->base._.size == q->front) {
            return 1;
        }

        q->base._.container[(i + q->base.rear) % q->base._.size] = ((char*)e)[i];
    }

    q->base.rear += s;

    return 0;
}
char queue_circle_de(ptr_queue_circle q, int size) {
    for(int i = 0; i < size; i++) {
        if(((q->front) + i) % q->base._.size == (q->base.rear)) {
            return 1;
        }
    }

    q->front = q->front = (q->front + size) % q->base._.size;

    return 0;
}
char queue_circle_empty(ptr_queue_circle q) {
    return q->base.rear == q->front;
}
char queue_circle_full(ptr_queue_circle q) {
    return ((q->front + 1) % q->base._.size) == q->base.rear;
}
void queue_circle_peek(ptr_queue_circle q, ptr_pack p) {
    for(int i = 0; i < p->size; i++) {
        p->container[i] = q->base._.container[(i + q->front) % q->base._.size];
    }
}
void queue_circle_kill(ptr_queue_circle q) {
    q->front = 0;
    return queuekill(&q->base);
}