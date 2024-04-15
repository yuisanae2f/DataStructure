#pragma once
#include "../pack/pack.h"

#ifndef stack_
#define stack_

typedef struct stack {
	struct pack _;
	int index;
}* ptr_stack;

#endif

#ifndef stack_fun
#define stack_fun

cfun struct stack stack(int size);
cfun void stackkill(ptr_stack a);
cfun char stackIfFull(ptr_stack a);
#define stackIfEmpty(a) (!(a).index)
cfun char stackpush(ptr_stack a, void* b, int c);
cfun struct pack stackpeek(ptr_stack a, int c);
cfun void stackpop(ptr_stack a, int b);
#endif


#ifdef cpp
#ifndef stack_cpp
#define stack_cpp
namespace edu {
    namespace Stack {
        class Plain;
    }

    template<typename t> class _StackAncient;

    template<>
    class _StackAncient<Stack::Plain> {
        private:
        struct stack st;
        public:
        inline _StackAncient(int size) : st(stack(size)) {}
        inline bool ifFull() { return stackIfFull(&this->st); }
        inline bool ifEmpty() { return stackIfEmpty(this->st); }
        inline bool push(void* a, int b) { return stackpush(&this->st, a, b); }
        inline struct pack peek(int a) { return stackpeek(&this->st, a); }
        inline void pop(int a) { return stackpop(&this->st, a); }
        inline ~_StackAncient() { stackkill(&this->st); }
    };

    template<class T, class m = Stack::Plain>
    class StackOrdered : private _StackAncient<m> {
        public:
        inline StackOrdered(int count) : _StackAncient(sizeof(T) * count) {}
        inline bool ifFull() { return _StackAncient::ifFull(); }
        inline bool ifEmpty() { return _StackAncient::ifEmpty(); }
        inline bool push(T a) { return _StackAncient::push(&a, sizeof(T)); }
        inline T peek() {
            struct pack p = _StackAncient::peek(sizeof(T));
            return ((T*)p.container)[0];
        }

        inline void pop() {
            return _StackAncient::pop(sizeof(T));
        }
    };
}

#endif
#endif