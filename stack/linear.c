#include <stdlib.h>
#include <memory.h>

typedef struct pack {
	int size;
	char* container;
}* ptr_pack;

typedef struct stack {
	struct pack _;
	int index;
}* ptr_stack;

struct stack stack(int size) {
	struct stack a;

	a._.container = malloc(size);
	a.index = 0;
	a._.size = size;

	return a;
}

void stackkill(ptr_stack a) {
	free(a->_.container);
	a->_.container = 0;
	a->index = -1;
	return;
}

char stackIfFull(ptr_stack a) {
	return a->index == a->_.size;
}

/// <param name="a">: stack</param>
#define stackIfEmpty(a) (!(a).index)

char stackpush(ptr_stack a, void* b, int c) {
	if (!stackIfFull(a)) {
		memcpy(a->_.container + a->index, b, c);
		a->index += c;

		return 0;
	}

	return 1;
}

struct pack stackpeek(ptr_stack a, int c) {
	struct pack th = { 0, 0 };

	if (stackIfEmpty(*a)) {
		return th;
	}

	th.container = a->_.container + a->index - c;
	th.size = c;
}

void stackpop(ptr_stack a, int b) {
	a->index -= b;
}