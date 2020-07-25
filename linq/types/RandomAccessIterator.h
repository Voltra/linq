#ifndef LINQ_RANDOMACCESSITERATOR_H
#define LINQ_RANDOMACCESSITERATOR_H

#include <type_traits>
#include <iterator>
#include <utility>

#define self RandomAccessIterator<T>
#define constructor RandomAccessIterator
#define destructor ~RandomAccessIterator
#define className constructor
#define super std::iterator<std::random_access_iterator_tag, T>

namespace linq{
	namespace types{
		template <class T>
		class className : public super{
			public:
				using super::value_type;
				using super::difference_type;
				using super::iterator_category;
				using super::pointer;
				using super::reference;
				using iterator = RandomAccessIterator<T>;

			protected:
				typename self::pointer ptr;

			public:
				destructor(){}

				constructor() : ptr{nullptr}{
				}

				/*explicit*/ constructor(typename self::pointer p) : ptr{p} {
				}

				constructor(const self& other) : ptr{other.ptr} {
				}

				constructor(self&& other) noexcept : ptr{std::move(other.ptr)} {
				}

				self operator++(int){//postfix
					return self{ptr++};
				}

				self& operator++(){//prefix
					++ptr;
					return *this;
				}

				typename self::reference operator*() const{
					return *ptr;
				}

				typename self::pointer operator->() const{
					return ptr;
				}

				self operator+(typename self::difference_type delta){
					return self{ ptr + delta };
				}

				self operator-(typename self::difference_type delta){
					return self{ ptr - delta };
				}

				typename self::difference_type operator-(const self& rhs){
					return this->ptr - rhs.ptr;
				}

				bool operator==(const self& rhs){
					const self& lhs = *this;
					return lhs.ptr == rhs.ptr;
				}

				bool operator!=(const self& rhs){
					return !this->operator==(rhs);
				}

		};
	};
};

#undef self
#undef constructor
#undef className
#undef super
#undef destructor

#define thisNamespace linq::types
#define TEMPLATE template <class T>
#define self thisNamespace::RandomAccessIterator<T>

TEMPLATE
self begin(T* ptr){ return self{ptr}; }

template <class T, class Tsize>
self end(T* ptr, Tsize size){ return self{ptr + size}; }

#undef thisNamespace
#undef TEMPLATE
#undef self

#endif //LINQ_RANDOMACCESSITERATOR_H
