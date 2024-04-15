#pragma once

#ifdef cpp
#define cfun extern "C"
#else
#define cfun
#endif

#ifndef pack_
#define pack_

typedef struct pack {
	int size;
	char* container;
}* ptr_pack;

#endif

#ifndef pack_fun
#define pack_fun
cfun void pack(ptr_pack p, int size);
cfun void packkill(ptr_pack p);
cfun void packrealloc(ptr_pack p, int size);
cfun void packcpy(ptr_pack p, ptr_pack src);
#endif

#ifdef cpp
#ifndef pack_cpp
#define pack_cpp
namespace edu {
	template<typename T>
	class Pack {
		private:
		struct pack obj;

		public:
		typedef ptr_pack ptr;
		inline Pack(T* el) {
			this->obj.size = sizeof(T);
			this->obj.container = (char*)el;
		}

		inline Pack(struct pack a) : obj(a) {}

		inline struct pack* addr() {
			return &this->obj;
		}

		inline T* el() {
			return (T*)this->obj.container;
		}
	};
}
#endif
#endif