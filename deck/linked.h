#pragma once
#include "../pack/pack.h"

#ifndef deck_
#define deck_

// 앞뒤로 넣었다 뺐다가 가능하다
// front, rear 가지고 만드는 거 같다.
typedef struct deckchild {
    struct pack container;
    void* p[2];
}* ptr_deckchild;

typedef struct deck {
    ptr_deckchild wl, wr;
    int count;
}* ptr_deck;
#endif

#ifndef deck_fun
#define deck_fun
cfun void deck(ptr_deck d);
cfun void deckkill(ptr_deck base);

cfun void deckaddfront(ptr_deck base, ptr_pack l);
cfun void deckaddrear(ptr_deck base, ptr_pack r);

cfun void deckdelfront(ptr_deck base);
cfun void deckdelrear(ptr_deck base);

cfun struct pack deckpeekfront(ptr_deck base);
cfun struct pack deckpeekrear(ptr_deck base);

cfun char deckempty(ptr_deck base);
#endif

#ifdef cpp
#ifndef deck_cpp
#define deck_cpp
namespace edu {
    namespace Deck {
        class LinkedList;
    }

    template<typename T>
    class _DeckAncient;

    template<>
    class _DeckAncient<Deck::LinkedList> {
        private:
        struct deck obj;
        public:
        inline _DeckAncient() {
            deck(&this->obj);
        }

        inline ~_DeckAncient() {
            deckkill(&this->obj);
        }

        inline void addfront(ptr_pack a) {
            return deckaddfront(&this->obj, a);
        }

        inline void addrear(ptr_pack a) {
            return deckaddrear(&this->obj, a);
        } 

        inline void delfront() {
            return deckdelfront(&this->obj);
        }

        inline void delrear() {
            return deckdelrear(&this->obj);
        }

        inline int count() {
            return this->obj.count;
        }

        inline struct pack peekfront() {
            return deckpeekfront(&this->obj);
        }

        inline struct pack peekrear() {
            return deckpeekrear(&this->obj);
        }
    };

    template <typename T, typename U = Deck::LinkedList>
    class DeckOrdered : private _DeckAncient<U> {
        public:
        inline DeckOrdered() : _DeckAncient<U>() {}
        inline void addfront(T a) {
            _DeckAncient<U>::addfront(edu::Pack<T>(&a).addr());
        }
        inline void addrear(T a) {
            _DeckAncient<U>::addrear(edu::Pack<T>(&a).addr());
        }

        inline void delfront() {
            _DeckAncient<U>::delfront();
        }

        inline void delrear() {
            _DeckAncient<U>::delrear();
        }

        inline T peekfront() {
            return edu::Pack<T>(_DeckAncient<U>::peekfront()).el()[0];
        }

        inline T peekrear() {
            return edu::Pack<T>(_DeckAncient<U>::peekrear()).el()[0];
        }

        inline int count() {
            return _DeckAncient<U>::count();
        }
    };
}
#endif
#endif