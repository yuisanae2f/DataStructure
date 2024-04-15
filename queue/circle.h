#pragma once
#include "linear.h"

#ifndef queue_circle_
typedef struct queue_circle {
    struct queue base;
    // front의 위치를 줘서 de 넣을 때마다 모두를 옮기는 병신같은 짓을 그만둬 보자
    int front;
}* ptr_queue_circle;
#endif

#ifndef queue_circle_fun
cfun struct queue_circle queue_circle(int size);
cfun char queue_circle_en(ptr_queue_circle q, void* e, int s);
cfun char queue_circle_de(ptr_queue_circle q, int size);
cfun char queue_circle_empty(ptr_queue_circle q);
cfun char queue_circle_full(ptr_queue_circle q);
cfun void queue_circle_peek(ptr_queue_circle q,  ptr_pack p);
cfun void queue_circle_kill(ptr_queue_circle q);
#endif

#ifdef cpp
#ifndef queue_circle_cpp
namespace edu {
    namespace Queue {
        class Circle;
    }
    template<>
    class _QueueAncient<Queue::Circle> {
        private:
        struct queue_circle obj;
        struct pack buff;

        public:
        inline _QueueAncient(int s)
        : obj(queue_circle(s)), buff{ 0, 0 } {}

        inline void en(void* e, int s) {
            queue_circle_en(&this->obj, e, s);
        }

        inline void de(int s) {
            queue_circle_de(&this->obj, s);
        }

        inline void empty() {
            queue_circle_empty(&this->obj);
        }

        inline void full() {
            queue_circle_full(&this->obj);
        }

        inline struct pack peek(int size) {
            packrealloc(&this->buff, size);
            queue_circle_peek(&this->obj, &this->buff);
            return this->buff;
        }

        inline ~_QueueAncient() {
            queue_circle_kill(&this->obj);
            packkill(&this->buff);
        }
    };
}
#endif
#endif