#pragma once
#include "../pack/pack.h"

#ifndef queue_
#define queue_

typedef struct queue {
    struct pack _;
    // front는 앞을 가리키는데 배열에서는 0번 인덱스라 만드는 의미 X
    int rear;
}* ptr_queue;
#endif

#ifndef queue_fun
#define queue_fun
cfun struct queue queue(int size);
cfun void queueen(ptr_queue q, void* e, int s);
cfun void queuede(ptr_queue q, int size);
cfun char queueempty(ptr_queue q);
cfun char queuefull(ptr_queue q);
cfun struct pack queuepeek(ptr_queue q, int size);
cfun void queuekill(ptr_queue q);
#endif

#ifdef cpp
#ifndef queue_cpp
#define queue_cpp
namespace edu {
    namespace Queue {
        class Plain;
    }

    template<typename T> class _QueueAncient;

    template<>
    class _QueueAncient<Queue::Plain> {
        private:
        struct queue obj;
        public:

        inline _QueueAncient(int size) 
        : obj(queue(size)) {}

        inline void en(void* e, int s) {
            return queueen(&this->obj, e, s);
        }

        inline void de(int size) {
            return queuede(&this->obj, size);
        }

        inline bool empty() {
            return queueempty(&this->obj);
        }

        inline bool full() {
            return queuefull(&this->obj);
        }

        inline struct pack peek(int size) {
            return queuepeek(&this->obj, size);
        }

        inline ~_QueueAncient() {
            queuekill(&this->obj);
        }
    };

    template<typename T, typename U = Queue::Plain>
    class QueueOrdered : private _QueueAncient<U> {
        public:
        inline QueueOrdered(int size)
        : _QueueAncient<U>(sizeof(T) * size) {}

        inline void en(T t) {
            return _QueueAncient<U>::en(((void*)&t), sizeof(T));
        }

        inline void de() {
            return _QueueAncient<U>::de(sizeof(T));
        }

        inline bool empty() {
            return _QueueAncient<U>::empty();
        }

        inline bool full() {
            return _QueueAncient<U>::full();
        }

        inline T peek() {
            return ((T*)_QueueAncient<U>::peek(sizeof(T)).container)[0];
        }
    };
}
#endif
#endif